#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MASS_KG = 1200;   // kg
constexpr double DT            = 0.02;          // s
constexpr double ACCELERATION  = 10.0;          // km/h na sekundę
constexpr double BRAKE_DECEL   = 27.0;          // km/h na sekundę
constexpr double COAST_DECEL   = 0.5;             // km/h na sekundę
constexpr double VMAX_KMH      = 200.0;           // km/h
constexpr double VMAX_MPS      = VMAX_KMH / 3.6;  // max predkosc w metrach na sekunde

constexpr double K_THROTTLE    = 3000;      // siła napędu przy max throttle w N
constexpr double C_ROLL     = 150.0;        // opór toczenia w N
constexpr double C_DRAG     = 0.50;         // opór aerodynamiczny
constexpr double K_BRAKE    = 4500.0;       // siła hamowania


#endif // CONSTANTS_H
