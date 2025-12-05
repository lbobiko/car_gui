#ifndef TRIPCOMPUTER_H
#define TRIPCOMPUTER_H

class TripComputer
{
private:
    double distance_m_;     // przejechany dystans (metry)
    double fuelUsed_l_;     // zużyte paliwo (litry)
    double engineTime_s_;   // czas pracy silnika (sekundy)

public:
    TripComputer();

    void reset();

    void addSample(double dx_m, double fuel_l, double dt, bool engineOn);

    // Gettery
    double getDistanceKm() const;
    double getFuelUsedLiters() const;
    double getEngineTimeSeconds() const;
    double getEngineTimeMinutes() const;
    double getAvgSpeedKmh() const;
    double getAvgConsumptionLPer100km() const;
};

#endif // TRIPCOMPUTER_H
