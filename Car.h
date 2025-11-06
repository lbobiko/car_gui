#ifndef CAR_H
#define CAR_H
#include "Brake.h"
#include "Engine.h"
#include <string>

class Car
{
private:
    std::string name;
    double currentSpeed;
    double throttle;
    Brake brake;
    Engine engine;
    double distance = 0.0;



public:
    Car();
    std::string getName();
    double getCurrentSpeed();
    double getThrottle();
    void setThrottle(double);
    double getDistance();
    void update(double dt);
    bool getEngineStatus();
    void setEngineStatus(bool s);
    bool getBrakeStatus();
    void setBrakeStatus(bool);


};

#endif // CAR_H
