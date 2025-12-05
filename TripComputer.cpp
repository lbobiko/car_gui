#include "TripComputer.h"

// Konstruktor
TripComputer::TripComputer()
    : distance_m_(0.0),
    fuelUsed_l_(0.0),
    engineTime_s_(0.0)
{
}

void TripComputer::reset()
{
    distance_m_   = 0.0;
    fuelUsed_l_   = 0.0;
    engineTime_s_ = 0.0;
}

void TripComputer::addSample(double dx_m, double fuel_l, double dt, bool engineOn)
{
    if (dx_m   < 0.0) dx_m   = 0.0;
    if (fuel_l < 0.0) fuel_l = 0.0;
    if (dt     < 0.0) dt     = 0.0;

    distance_m_ += dx_m;
    fuelUsed_l_ += fuel_l;

    if (engineOn) {
        engineTime_s_ += dt;
    }
}

double TripComputer::getDistanceKm() const
{
    return distance_m_ / 1000.0;
}

double TripComputer::getFuelUsedLiters() const
{
    return fuelUsed_l_;
}

double TripComputer::getEngineTimeSeconds() const
{
    return engineTime_s_;
}

double TripComputer::getEngineTimeMinutes() const
{
    return engineTime_s_ / 60.0;
}

double TripComputer::getAvgSpeedKmh() const
{
    if (engineTime_s_ <= 0.0) return 0.0;

    double v_mps = distance_m_ / engineTime_s_;
    return v_mps * 3.6;
}

double TripComputer::getAvgConsumptionLPer100km() const
{
    if (distance_m_ < 10.0) {
        return 0.0;
    }

    double dist_km = distance_m_ / 1000.0;
    return (fuelUsed_l_ / dist_km) * 100.0;
}
