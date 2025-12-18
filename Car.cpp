#include "Car.h"

#include <cmath>
#include <algorithm>
#include <QString>
#include "ConsumptionModel.h"

Car::Car()
    : name("Toyota")
    , throttle(0.0)
    , brake()
    , engine()
    , v_mps(0.0)
    , x_m(0.0)
    , fuelTank_(50.0, 20.0)
    , fuelUsedTotal_(0.0)
    , consumption_(nullptr)
    , gradePercent_(0.0)
    , surfaceModel_(nullptr)
{
    surfaceModel_ = &asphaltDry_; // domyślnie
}

std::string Car::getName() const { return name; }

bool Car::getEngineStatus() const { return engine.getEngineStatus(); }
void Car::setEngineStatus(bool s) { engine.setEngineStatus(s); }

double Car::getThrottle() const { return throttle; }
void Car::setThrottle(double t) { throttle = std::clamp(t, 0.0, 1.0); }

bool Car::getBrakeStatus() const { return brake.getBrakePressed(); }
void Car::setBrakeStatus(bool b) { brake.setBrakePressed(b); }

double Car::getDistance() const { return x_m; }
double Car::getCurrentSpeed() const { return v_mps * 3.6; } // km/h

double Car::getFuelLevel() const { return fuelTank_.getLevel(); }
double Car::getFuelCapacity() const { return fuelTank_.getCapacity(); }
double Car::getFuelUsedTotal() const { return fuelUsedTotal_; }
void   Car::refuel(double liters) { fuelTank_.addFuel(liters); }

void Car::setConsumptionModel(ConsumptionModel* model) { consumption_ = model; }

double Car::getTripDistanceKm() const { return tripComputer_.getDistanceKm(); }
double Car::getTripAvgConsumption() const { return tripComputer_.getAvgConsumptionLPer100km(); }
double Car::getTripTimeMinutes() const { return tripComputer_.getEngineTimeMinutes(); }
double Car::getTripAvgSpeedKmh() const { return tripComputer_.getAvgSpeedKmh(); }
void   Car::resetTrip() { tripComputer_.reset(); }

bool Car::shouldShowFuelWarning() const { return fuelWarningShown_; }
void Car::resetFuelWarning() { fuelWarningShown_ = false; }

void Car::setGradePercent(double g) { gradePercent_ = std::clamp(g, -20.0, 20.0); }
double Car::gradePercent() const { return gradePercent_; }

void Car::setSurfacePreset(int idx)
{
    switch (idx) {
    case 0: surfaceModel_ = &asphaltDry_; break;
    case 1: surfaceModel_ = &asphaltWet_; break;
    case 2: surfaceModel_ = &gravel_;     break;
    case 3: surfaceModel_ = &ice_;        break;
    default: surfaceModel_ = &asphaltDry_; break;
    }
}

double Car::computeRpm() const
{
    if (!engine.getEngineStatus()) return 0.0;

    double ratio = transmission_.totalRatio();
    if (ratio <= 0.0) return IDLE_RPM;

    double wheel_rps = v_mps / (2.0 * M_PI * WHEEL_RADIUS_M);
    double wheel_rpm = wheel_rps * 60.0;

    double rpm = wheel_rpm * ratio;

    if (rpm < IDLE_RPM) rpm = IDLE_RPM;
    if (rpm > REDLINE_RPM) rpm = REDLINE_RPM;

    return rpm;
}

double Car::engineTorque(double rpm) const
{
    if (!engine.getEngineStatus() || throttle <= 0.0)
        return 0.0;

    double t = std::clamp(throttle, 0.0, 1.0);
    double x = (rpm - RPM_TORQUE_PEAK) / RPM_TORQUE_WIDTH;

    double shape = std::exp(-0.5 * x * x);
    double torque = TORQUE_MAX_NM * shape * t;

    if (rpm < IDLE_RPM || rpm > REDLINE_RPM)
        torque *= 0.3;

    return torque;
}

void Car::update(double dt)
{
    if (dt <= 0.0) return;

    double v = v_mps;
    bool engineOn = engine.getEngineStatus();
    bool noFuel   = fuelTank_.isEmpty();

    // hamulec -> odpuszczamy gaz
    if (brake.getBrakePressed()) {
        throttle = 0.0;
    }

    // --- Etap 5: reset flag ABS/TCS ---
    absActive_ = false;
    tcsActive_ = false;

    // --- Strategy nawierzchni ---
    const double mu = getMu();
    const double F_max = mu * MASS_KG * 9.81;

    // brak paliwa -> gaś silnik
    if (noFuel && engineOn) {
        engine.setEngineStatus(false);
        engineOn = false;
        throttle = 0.0;
        fuelWarningShown_ = true;
    }

    // --- skrzynia / rpm ---
    double rpm = computeRpm();

    if (transmission_.mode() == ShiftMode::Auto) {
        transmission_.updateAuto(rpm, throttle);
        rpm = computeRpm();
    }

    // --- siły ---
    double F_eng   = 0.0;
    double F_roll  = 0.0;
    double F_drag  = 0.0;
    double F_brake = 0.0;

    // napęd
    if (engineOn && throttle > 0.0) {
        double torque = engineTorque(rpm);
        double ratio  = transmission_.totalRatio();

        if (ratio > 0.0) {
            double driveTorque = torque * ratio * DRIVELINE_EFF;
            F_eng = driveTorque / WHEEL_RADIUS_M;
        }
    }

    // TCS: jeśli siła napędowa > przyczepność, ogranicz
    if (tcsEnabled_ && v > MIN_SPEED_FOR_SLIP && F_eng > F_max) {
        tcsActive_ = true;
        F_eng = F_max * TCS_REDUCE_FACTOR;
    }

    // opory
    if (v > 0.0) {
        F_roll = C_ROLL;
        F_drag = C_DRAG * v * v;
    }

    // hamowanie + ABS
    if (brake.getBrakePressed()) {
        double desiredBrake = K_BRAKE;

        if (desiredBrake > F_max && v > 0.5) {
            if (absEnabled_) {
                absActive_ = true;

                absTime_ += dt;
                double period = 1.0 / ABS_PULSE_HZ;
                bool release = std::fmod(absTime_, period) < (0.5 * period);

                desiredBrake = F_max * (release ? ABS_RELEASE_FACTOR : 1.0);
            } else {
                // bez ABS: blokada kół → gorsze hamowanie
                desiredBrake = F_max * 0.60;
            }
        } else {
            desiredBrake = std::min(desiredBrake, F_max);
            absTime_ = 0.0;
        }

        F_brake = desiredBrake;
    }

    // --- Etap 6: nachylenie terenu ---
    double alpha = std::atan(gradePercent_ / 100.0);
    double F_grade = MASS_KG * 9.81 * std::sin(alpha);

    // suma sił
    double F = F_eng - F_roll - F_drag - F_brake - F_grade;

    // blokada “poniżej zera”
    if (v <= 0.0 && F < 0.0) {
        F = 0.0;
    }

    // ruch
    double a    = F / MASS_KG;
    double vNew = v + a * dt;

    if (vNew < 0.0)      vNew = 0.0;
    if (vNew > VMAX_MPS) vNew = VMAX_MPS;

    double dx = vNew * dt;
    x_m   += dx;
    v_mps  = vNew;

    // paliwo
    double usedNow = 0.0;

    if (engineOn && !noFuel && consumption_ != nullptr) {
        double v_kmh  = vNew * 3.6;
        double flowLps = consumption_->fuelFlowLps(throttle, v_kmh);
        if (flowLps < 0.0) flowLps = 0.0;

        double fuelStep = flowLps * dt;
        usedNow = fuelTank_.consume(fuelStep);
        fuelUsedTotal_ += usedNow;
    }

    // trip computer
    bool engineReallyOn = engineOn && !fuelTank_.isEmpty();
    tripComputer_.addSample(dx, usedNow, dt, engineReallyOn);
}

// ---------- Strategy nawierzchni: metody pomocnicze ----------
double Car::getMu() const
{
    return surfaceModel_ ? surfaceModel_->mu() : 0.95;
}

QString Car::getSurfaceName() const
{
    return surfaceModel_ ? surfaceModel_->name() : "Asphalt (Dry)";
}

void Car::resetAll()
{
    throttle = 0.0;
    v_mps = 0.0;
    x_m = 0.0;

    brake.setBrakePressed(false);
    engine.setEngineStatus(false);

    transmission_ = Transmission(); // reset skrzyni do domyślnego stanu
    absActive_ = false;
    tcsActive_ = false;
    absTime_ = 0.0;

    gradePercent_ = 0.0;

    fuelTank_ = FuelTank(50.0, 20.0); // startowe 20L
    fuelUsedTotal_ = 0.0;
    fuelWarningShown_ = false;

    tripComputer_.reset();

    surfaceModel_ = &asphaltDry_;
}
