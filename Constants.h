#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MAX_SPEED = 200;  // km/h
constexpr int MASS_KG = 1200;   // kg
constexpr double DT = 0.02;
constexpr double ACCELERATION = 8.0; // per tick
constexpr double COAST_DECEL   = 0.0;   // km/h na tick (gdy throttle=0)
constexpr double BRAKE_DECEL   = 20.0;  // gdy wcisniety hamulec
// Ustawienia dla sterowania w pętli (czas „trzymania” hamulca)
constexpr double BRAKE_HOLD_SEC = 0.12; // jeśli SPACE był wciśnięty w ostatnich 120 ms, hamulec jest aktywny

#endif // CONSTANTS_H
