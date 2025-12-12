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

// koło / napęd
constexpr double WHEEL_RADIUS_M   = 0.30;   // ~60 cm średnicy
constexpr double DRIVELINE_EFF    = 0.90;   // sprawność przeniesienia napędu

// RPM
constexpr double IDLE_RPM         = 900.0;
constexpr double REDLINE_RPM      = 6500.0;

// moment (bardzo uproszczony)
constexpr double TORQUE_MAX_NM    = 220.0;  // maks. moment
constexpr double RPM_TORQUE_PEAK  = 4000.0; // gdzie jest "najlepiej"
constexpr double RPM_TORQUE_WIDTH = 2500.0; // szerokość krzywej


#endif // CONSTANTS_H
