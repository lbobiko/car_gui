#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#pragma once
#include <vector>

enum class ShiftMode { Manual, Auto };

class Transmission {
public:
    Transmission();

    int gear() const { return gear_; }                 // 0 = luz
    int maxGear() const { return static_cast<int>(gears_.size()) - 1; } // bo [0]=luz
    ShiftMode mode() const { return mode_; }
    void setMode(ShiftMode m) { mode_ = m; }
    void toggleMode();

    void shiftUp();
    void shiftDown();

    double currentRatio() const;                       // przełożenie biegu (g1..gN) albo 0 na luzie
    double finalDrive() const { return finalDrive_; }
    double totalRatio() const;                         // currentRatio * finalDrive

    // automat: prosta polityka zmiany biegów wg RPM
    void updateAuto(double rpm, double throttle);

private:
    std::vector<double> gears_;                        // [0]=luz, [1]=1 bieg
    double finalDrive_ = 3.9;
    int gear_ = 0;
    ShiftMode mode_ = ShiftMode::Auto;

    // proste progi
    double upRpm_   = 4500.0;
    double downRpm_ = 1800.0;
};

#endif // TRANSMISSION_H
