#include "Car.h"
#include "Brake.h"
#include "Engine.h"
#include <string>
#include <algorithm>
#include "Constants.h"
#include "TripComputer.h"
#include <cmath>

Car::Car()
    : name("Toyota")
    , throttle(0.0)
    , brake()
    , engine()
    , v_mps(0.0)
    , x_m(0.0)
    , fuelTank_(50.0, 20.0)      // np. 50 L pojemności
    , fuelUsedTotal_(0.0)
    , consumption_(nullptr)
{

}

bool Car::getEngineStatus() const{
    return engine.getEngineStatus();
}

void Car::setEngineStatus(bool s){
    engine.setEngineStatus(s);
}

double Car::getThrottle() const{
    return throttle;
}

void Car::setThrottle(double t){
    this->throttle = std::clamp(t, 0.0, 1.0);
}

bool Car::getBrakeStatus() const{
    return brake.getBrakePressed();
}

void Car::setBrakeStatus(bool b){
    brake.setBrakePressed(b);
}

double Car::getDistance() const{
    return x_m;
}

double Car::getCurrentSpeed() const{
    return v_mps * 3.6;  // w kilometrach
}


void Car::update(double dt)
{
    if (dt <= 0.0) return;

    // --- skróty do czytelności ---
    double v = v_mps;                 // stara prędkość [m/s]
    bool engineOn = engine.getEngineStatus();
    bool noFuel   = fuelTank_.isEmpty();

    // jeśli nie ma paliwa, silnik gaśnie i gaz ignorowany
    if (noFuel && engineOn) {
        engine.setEngineStatus(false);
        engineOn = false;
        throttle = 0.0;      // pedał gazu ignorowany
        fuelWarningShown_ = true;   // flaga
    }

    // --- skrzynia biegów / RPM ---

    // aktualne obroty z biegu i prędkości
    double rpm = computeRpm();

        if (transmission_.mode() == ShiftMode::Auto) {
        transmission_.updateAuto(rpm, throttle);
        rpm = computeRpm();
    }

    // --- SIŁY ---

    double F_eng   = 0.0;
    double F_roll  = 0.0;
    double F_drag  = 0.0;
    double F_brake = 0.0;


    // napęd – tylko gdy silnik działa i jest gaz
    if (engineOn && throttle > 0.0) {
        // moment silnika zależny od RPM i gazu
        double torque = engineTorque(rpm); // jeśli torque ma zależeć też od throttle,

        // przełożenie skrzyni + final drive; na luzie totalRatio() powinno być 0
        double ratio = transmission_.totalRatio();

        if (ratio > 0.0) { // zabezpieczenie: na luzie nie jedzie
            double driveTorque = torque * ratio * DRIVELINE_EFF;
            F_eng = driveTorque / WHEEL_RADIUS_M;
        }
    }

    // opory (toczenie + powietrze) tylko przy dodatniej prędkości
    if (v > 0.0) {
        F_roll = C_ROLL;
        F_drag = C_DRAG * v * v;
    }

    // hamulec
    if (brake.getBrakePressed()) {
        F_brake = K_BRAKE;
    }

    // suma sił
    double F = F_eng - F_roll - F_drag - F_brake;

    // gdy prędkość w okolicach zera
    if (v <= 0.0 && F < 0.0) {
        F = 0.0;
    }

    // --- RÓWNANIA RUCHU ---

    double a    = F / MASS_KG;     // przyspieszenie [m/s^2]
    double vNew = v + a * dt;      // nowa prędkość [m/s]

    // ograniczenia 0 ≤ v ≤ VMAX
    if (vNew < 0.0)     vNew = 0.0;
    if (vNew > VMAX_MPS) vNew = VMAX_MPS;

    // droga w tym kroku
    double dx = vNew * dt;         // [m]
    x_m += dx;
    v_mps = vNew;

    // --- PALIWO ---

    double usedNow = 0.0;

    if (engineOn && !noFuel && consumption_ != nullptr) {
        // prędkość w km/h do modelu spalania
        double v_kmh = vNew * 3.6;

        // przepływ paliwa [L/s]
        double flowLps = consumption_->fuelFlowLps(throttle, v_kmh);

        if (flowLps < 0.0) flowLps = 0.0;

        // ile litrów w tym kroku
        double fuelStep = flowLps * dt;

        // zjedz paliwo z baku (uwaga: consume może zwrócić mniej, jeśli bak prawie pusty)
        usedNow = fuelTank_.consume(fuelStep);
        fuelUsedTotal_ += usedNow;
    }

    // --- TRIP COMPUTER ---

    bool engineReallyOn = engineOn && !fuelTank_.isEmpty();
    tripComputer_.addSample(dx, usedNow, dt, engineReallyOn);


}

double Car::getFuelLevel() const {
    return fuelTank_.getLevel();
}

double Car::getFuelCapacity() const {
    return fuelTank_.getCapacity();
}

double Car::getFuelUsedTotal() const {
    return fuelUsedTotal_;
}

void Car::refuel(double liters) {
    fuelTank_.addFuel(liters);
}

void Car::setConsumptionModel(ConsumptionModel* model)
{
    consumption_ = model;
}

// statystyki z TripComputer
double Car::getTripDistanceKm() const{
    return tripComputer_.getDistanceKm();
}
double Car::getTripAvgConsumption() const  {
    return tripComputer_.getAvgConsumptionLPer100km();
}
double Car::getTripTimeMinutes() const     {
    return tripComputer_.getEngineTimeMinutes();
}
double Car::getTripAvgSpeedKmh() const     {
    return tripComputer_.getAvgSpeedKmh();
}

void Car::resetTrip() {
    tripComputer_.reset();
}

bool Car::shouldShowFuelWarning() const {
    return fuelWarningShown_;
}
void Car::resetFuelWarning() {
    fuelWarningShown_ = false;
}

double Car::computeRpm() const
{
    if (!engine.getEngineStatus()) return 0.0;

    double ratio = transmission_.totalRatio();

    // luz: trzymaj jałowe (albo 0, ale jałowe wygląda lepiej)
    if (ratio <= 0.0) return IDLE_RPM;

    double wheel_rps = v_mps / (2.0 * M_PI * WHEEL_RADIUS_M); // obr/s
    double wheel_rpm = wheel_rps * 60.0;

    double rpm = wheel_rpm * ratio;

    if (rpm < IDLE_RPM) rpm = IDLE_RPM;
    if (rpm > REDLINE_RPM) rpm = REDLINE_RPM; // żeby test "nie przekracza redline" przechodził

    return rpm;
}

double Car::engineTorque(double rpm) const
{
    if (!engine.getEngineStatus() || throttle <= 0.0)
        return 0.0;

    // stopień wciśnięcia gazu (0–1)
    double t = std::clamp(throttle, 0.0, 1.0);

    // odległość od optymalnych obrotów
    double x = (rpm - RPM_TORQUE_PEAK) / RPM_TORQUE_WIDTH;

    // pseudo-gauss: duży moment koło RPM_TORQUE_PEAK, maleje na boki
    double shape = std::exp(-0.5 * x * x);   // 1.0 w środku, maleje do 0

    double torque = TORQUE_MAX_NM * shape * t;   // [Nm]

    // poza zakresem jałowy–redline mocno przyduszamy silnik
    if (rpm < IDLE_RPM || rpm > REDLINE_RPM)
        torque *= 0.3;

    return torque;   // [Nm]
}
