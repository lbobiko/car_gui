#include "Car.h"
#include "Brake.h"
#include "Engine.h"
#include <string>
#include <algorithm>
#include "Constants.h"


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

/*void Car::update(double dt)
{
    // --- Bieżący stan ----------------------------------------
    double v = v_mps;                         // prędkość w m/s
    bool   engineOn = engine.getEngineStatus();
    bool   noFuel   = fuelTank_.isEmpty();

    // Jeśli bak pusty, a silnik jeszcze "ON" → zgaś go i wyzeruj gaz
    if (noFuel && engineOn) {
        engine.setEngineStatus(false);
        engineOn = false;
        throttle = 0.0;
    }

    // --- Siły -------------------------------------------------
    double F_eng   = 0.0;                    // siła napędowa
    double F_roll  = 0.0;                    // opór toczenia
    double F_drag  = 0.0;                    // opór powietrza
    double F_brake = 0.0;                    // siła hamowania

    // Napęd silnika tylko gdy silnik pracuje, jest paliwo i gaz > 0
    if (engineOn && !noFuel && throttle > 0.0) {
        F_eng = K_THROTTLE * throttle;       // [N]
    }

    // Opory tylko gdy jedziemy do przodu
    if (v > 0.0) {
        F_roll = C_ROLL;                     // [N]
        F_drag = C_DRAG * v * v;             // [N]
    }

    // Hamulec – tylko gdy wciśnięty
    if (getBrakeStatus()) {
        F_brake = K_BRAKE;                   // [N]
    }

    // Suma sił (napęd dodatni, reszta ujemna)
    double F = F_eng - F_roll - F_drag - F_brake;

    // Jeśli stoimy i siła "ciągnie w tył" → obcinamy do 0
    if (v <= 0.0 && F < 0.0) {
        F = 0.0;
    }

    // --- Równania ruchu --------------------------------------
    double a    = F / MASS_KG;               // przyspieszenie [m/s^2]
    double vNew = v + a * dt;                // nowa prędkość [m/s]

    // Ograniczenia 0 ≤ v ≤ VMAX
    if (vNew < 0.0)      vNew = 0.0;
    if (vNew > VMAX_MPS) vNew = VMAX_MPS;

    // Aktualizacja położenia (x w metrach)
    x_m   += vNew * dt;
    v_mps  = vNew;

    // Jeśli wciąż masz gdzieś currentSpeed w km/h, to możesz go aktualizować:
    // currentSpeed = v_mps * 3.6;

    // --- Zużycie paliwa (Strategy + FuelTank) ----------------
    if (engineOn && !noFuel && consumption_ != nullptr) {
        double speedKmh = vNew * 3.6;        // strategia liczy w km/h
        double flow_lps = consumption_->fuelFlowLps(throttle, speedKmh); // [l/s]

        if (flow_lps < 0.0)
            flow_lps = 0.0;

        double requested = flow_lps * dt;                // ile chcemy spalić [l]
        double taken     = fuelTank_.consume(requested); // ile faktycznie pobrano

        fuelUsedTotal_ += taken;

        // Jeśli nie udało się pobrać całej ilości → skończyło się paliwo w trakcie kroku
        if (taken + 1e-9 < requested) {
            engine.setEngineStatus(false);
            throttle = 0.0;
        }
    }
}
*/

void Car::update(double dt)
{
    double F_eng = 0.0;
    double F_roll = 0.0;
    double F_drag = 0.0;
    double F_brake = 0.0;

    double v = v_mps;
    bool engineOn = engine.getEngineStatus();
    bool noFuel   = fuelTank_.isEmpty();

    // brak paliwa → gasimy silnik
    if (noFuel && engineOn) {
        engine.setEngineStatus(false);
        engineOn = false;
        throttle = 0.0;
    }

    // SIŁY MECHANICZNE
    if (engineOn && throttle > 0.0) {
        F_eng = K_THROTTLE * throttle;
    }

    if (v > 0.0) {
        F_roll = C_ROLL;
        F_drag = C_DRAG * v * v;
    }

    if (brake.getBrakePressed()) {
        F_brake = K_BRAKE;
    }

    double F = F_eng - F_roll - F_drag - F_brake;
    if (v <= 0.0 && F < 0.0) F = 0.0;

    double a    = F / MASS_KG;
    double vNew = v + a * dt;

    if (vNew < 0.0)      vNew = 0.0;
    if (vNew > VMAX_MPS) vNew = VMAX_MPS;

    x_m   += vNew * dt;
    v_mps  = vNew;

    // --------- PALIWO -----------
    double fuelFlow = 0.0;
    if (engineOn && consumption_) {
        double v_kmh = vNew * 3.6;
        fuelFlow = consumption_->fuelFlowLps(throttle, v_kmh);  // L/s
    }

    double used = fuelTank_.consume(fuelFlow * dt); // L
    fuelUsedTotal_ += used;
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
