#include "Car.h"
#include "Brake.h"
#include "Engine.h"
#include <string>


Car::Car()
    : name("Toyota"),
    currentSpeed(0.0),
    throttle(0.0),
    distance(0.0),
    brake(),
    engine()
{

}

bool Car::getEngineStatus(){
    return engine.getEngineStatus();
}

void Car::setEngineStatus(bool s){
    engine.setEngineStatus(s);
}

double Car::getThrottle(){
    return throttle;
}

void Car::setThrottle(double t){
    this->throttle = t;
}

bool Car::getBrakeStatus(){
    return brake.getBrakePressed();
}

void Car::setBrakeStatus(bool b){
    brake.setBrakePressed(b);
}

double getDistance(){
    return distance;
}
