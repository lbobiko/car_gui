#ifndef CAR_H
#define CAR_H

#include <string>
#include "Brake.h"
#include "Engine.h"
#include "FuelTank.h"
#include "ConsumptionModel.h"
#include "Constants.h"
#include "TripComputer.h"
#include "Transmission.h"

class Car {
private:
    std::string name;
    double throttle = 0.0;

    Brake  brake;
    Engine engine;

    double v_mps = 0.0;   // prędkość w m/s
    double x_m   = 0.0;   // pozycja w m

    FuelTank fuelTank_;
    double   fuelUsedTotal_ = 0.0;

    ConsumptionModel* consumption_ = nullptr;   // ← tylko wskaźnik

    TripComputer tripComputer_;

    bool fuelWarningShown_ = false;

    Transmission transmission_;
    double computeRpm() const;
    double engineTorque(double rpm) const;

public:
    Car();

    std::string getName() const;
    double getCurrentSpeed() const;
    double getThrottle() const;
    double getDistance() const;

    void   update(double dt);

    bool getEngineStatus() const;
    void setEngineStatus(bool s);

    bool getBrakeStatus() const;
    void setBrakeStatus(bool b);

    double getFuelLevel() const;
    double getFuelCapacity() const;
    double getFuelUsedTotal() const;
    void   refuel(double liters);

    void   setThrottle(double t);

    // zmiana strategii spalania
    void setConsumptionModel(ConsumptionModel* model);

    // statystyki z TripComputer
    double getTripDistanceKm() const;
    double getTripAvgConsumption() const;
    double getTripTimeMinutes() const;
    double getTripAvgSpeedKmh() const;

    void resetTrip();

    bool shouldShowFuelWarning() const;
    void resetFuelWarning();
    int getGear() const { return transmission_.gear(); }
    ShiftMode getShiftMode() const { return transmission_.mode(); }
    double getRpm() const { return computeRpm(); }

    void toggleShiftMode() { transmission_.toggleMode(); }
    void shiftUp()   { transmission_.shiftUp(); }
    void shiftDown() { transmission_.shiftDown(); }
};

#endif
