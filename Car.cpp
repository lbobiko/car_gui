#include "Car.h"
#include "Brake.h"
#include "Engine.h"
#include <string>
#include <algorithm>
#include "Constants.h"


Car::Car()
    : name("Toyota"),
    currentSpeed(0.0),
    throttle(0.0),
    distance(0.0),
    brake(),
    engine()
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
    return distance;
}

double Car::getCurrentSpeed() const{
    return currentSpeed;
}

void Car::update(double dt)
{
    // gaz
    if (throttle > 0 && !brake.getBrakePressed() && engine.getEngineStatus())
        currentSpeed += ACCELERATION * throttle * dt;

    // hamulec
    if (brake.getBrakePressed())
        currentSpeed = std::max(0.0, currentSpeed - BRAKE_DECEL * dt);

    // opory toczenia
    if (throttle == 0 && !brake.getBrakePressed())
        currentSpeed -= COAST_DECEL * dt;

    // ograniczenia
    if (currentSpeed < 0)
        currentSpeed = 0;
    if (currentSpeed > MAX_SPEED)
        currentSpeed = MAX_SPEED;

    // dystans
    distance += currentSpeed * dt / 3.6; // km/h → m/s
}
