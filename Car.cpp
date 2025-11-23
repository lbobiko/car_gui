#include "Car.h"
#include "Brake.h"
#include "Engine.h"
#include <string>
#include <algorithm>
#include "Constants.h"


Car::Car()
    : name("Toyota"),
    throttle(0.0),
    brake(),
    engine(),
    v_mps(0.0),
    x_m(0.0)
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
    double F_eng;   // siła napędowa silnika
    double F_roll;  // opór toczenia
    double F_drag;  // opór powietrza
    double F_brake; // siła hamowania
    double v = v_mps;

    if (getEngineStatus()){
        F_eng = K_THROTTLE * throttle;
    } else {
        F_eng = 0.0;
    }
    if (v > 0.0) {
        F_roll = C_ROLL;                      // opór toczenia
        F_drag = C_DRAG * v * v;              // opór aero
    } else {
        F_roll = 0.0;
        F_drag = 0.0;
    }
    if (getBrakeStatus()) {
        F_brake = K_BRAKE;                    // hamulec tylko gdy wciśnięty
    } else {
        F_brake = 0.0;
    }

    // Suma sił
    double F = F_eng - F_roll - F_drag - F_brake;
    if (v <= 0.0 && F < 0.0) {
        F = 0.0;
    }

    double a = F / MASS_KG;    // m/s^2
    double vNew = v + a * dt;     // m/s

    // ograniczenia 0 ≤ v ≤ VMAX
    if (vNew < 0.0) {
        vNew = 0.0;
    }
    if (vNew > VMAX_MPS) {
        vNew = VMAX_MPS;
    }

    // pozycja
    x_m += vNew * dt;

    // nowa predkosc
    v_mps = vNew;

}
