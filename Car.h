#ifndef CAR_H
#define CAR_H
#include "Brake.h"
#include "Engine.h"
#include <string>

class Car
{
private:
    std::string name;
    double throttle;
    Brake brake;
    Engine engine;
    double v_mps = 0.0;    // predkosc w metrach/s
    double x_m = 0.0;      // pozycja



public:
    Car();
    std::string getName();
    double getCurrentSpeed() const;
    double getThrottle() const;
    void setThrottle(double);
    double getDistance() const;
    void update(double dt);
    bool getEngineStatus() const;
    void setEngineStatus(bool s);
    bool getBrakeStatus() const;
    void setBrakeStatus(bool);


};

#endif // CAR_H
