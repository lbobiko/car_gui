#ifndef CAR_H
#define CAR_H

#include <string>
#include <algorithm>
#include <QString>

#include "Brake.h"
#include "Engine.h"
#include "FuelTank.h"
#include "ConsumptionModel.h"
#include "Constants.h"
#include "TripComputer.h"
#include "Transmission.h"
#include "SurfaceModel.h"   // Strategy: SurfaceModel + klasy pochodne

class Car {
private:
    std::string name;
    double throttle = 0.0;

    Brake  brake;
    Engine engine;

    double v_mps = 0.0;   // prędkość [m/s]
    double x_m   = 0.0;   // pozycja [m]

    FuelTank fuelTank_;
    double   fuelUsedTotal_ = 0.0;

    ConsumptionModel* consumption_ = nullptr;   // Strategy spalania

    TripComputer tripComputer_;
    bool fuelWarningShown_ = false;

    Transmission transmission_;
    double computeRpm() const;
    double engineTorque(double rpm) const;

    // --- Etap 5: ABS / TCS ---
    bool absEnabled_ = false;
    bool tcsEnabled_ = false;
    bool absActive_  = false;
    bool tcsActive_  = false;

    double absTime_ = 0.0;   // do pulsowania ABS

    // --- Etap 6: nachylenie + nawierzchnia (Strategy) ---
    double gradePercent_ = 0.0;  // np. -20 .. +20

    SurfaceModel* surfaceModel_ = nullptr; // aktywna strategia
    AsphaltDry  asphaltDry_;
    AsphaltWet  asphaltWet_;
    Gravel      gravel_;
    Ice         ice_;

public:
    Car();

    // podstawowe
    std::string getName() const;
    double getCurrentSpeed() const; // km/h
    double getThrottle() const;
    double getDistance() const;

    void update(double dt);

    // silnik / hamulec / gaz
    bool getEngineStatus() const;
    void setEngineStatus(bool s);

    bool getBrakeStatus() const;
    void setBrakeStatus(bool b);

    void setThrottle(double t);

    // paliwo
    double getFuelLevel() const;
    double getFuelCapacity() const;
    double getFuelUsedTotal() const;
    void   refuel(double liters);

    // spalanie (Strategy)
    void setConsumptionModel(ConsumptionModel* model);

    // trip computer
    double getTripDistanceKm() const;
    double getTripAvgConsumption() const;
    double getTripTimeMinutes() const;
    double getTripAvgSpeedKmh() const;
    void resetTrip();

    // ostrzeżenie paliwa
    bool shouldShowFuelWarning() const;
    void resetFuelWarning();

    // skrzynia
    int getGear() const { return transmission_.gear(); }
    ShiftMode getShiftMode() const { return transmission_.mode(); }
    double getRpm() const { return computeRpm(); }

    void toggleShiftMode() { transmission_.toggleMode(); }
    void shiftUp()   { transmission_.shiftUp(); }
    void shiftDown() { transmission_.shiftDown(); }

    // ABS/TCS
    void setAbsEnabled(bool on) { absEnabled_ = on; }
    void setTcsEnabled(bool on) { tcsEnabled_ = on; }

    bool absEnabled() const { return absEnabled_; }
    bool tcsEnabled() const { return tcsEnabled_; }
    bool absActive()  const { return absActive_; }
    bool tcsActive()  const { return tcsActive_; }

    // nachylenie
    void setGradePercent(double g);
    double gradePercent() const;

    // nawierzchnia (Strategy)
    void setSurfaceModel(SurfaceModel* model) { surfaceModel_ = model; }
    //double getMu() const { return surfaceModel_ ? surfaceModel_->mu() : 0.95; }
    //QString getSurfaceName() const { return surfaceModel_ ? surfaceModel_->name() : "Asphalt (Dry)"; }

    // preset do klawiszy/GUI: 0..3
    void setSurfacePreset(int idx);

    double getMu() const;
    QString getSurfaceName() const;

    void resetAll();
};

#endif
