#include "ConsumptionModel.h"

// współczynniki do dopasowania

namespace {
constexpr double K_ECO    = 0.0012;   // ~4–5 L/100km
constexpr double K_NORMAL = 0.0018;   // ~6–7 L/100km
constexpr double K_SPORT  = 0.0025;   // ~9–10 L/100km
}

// to samo dla wszystkich modeli, różne tylko K
static double baseFuelFlow(double k, double throttle, double v_kmh)
{
    if (throttle <= 0.0 && v_kmh <= 0.1) {
        // bieg jałowy = 0
        return 0.0;
    }

    if (throttle < 0.0) throttle = 0.0;
    if (throttle > 1.0) throttle = 1.0;
    if (v_kmh   < 0.0) v_kmh   = 0.0;

    // im większy gaz i prędkość, tym większy przepływ
    double factor = 1.0 + v_kmh / 100.0;   // np. 100 km/h → ×2
    return k * throttle * factor;         // L/s
}

double EcoConsumption::fuelFlowLps(double throttle, double v_kmh) const
{
    return baseFuelFlow(K_ECO, throttle, v_kmh);
}

double NormalConsumption::fuelFlowLps(double throttle, double v_kmh) const
{
    return baseFuelFlow(K_NORMAL, throttle, v_kmh);
}

double SportConsumption::fuelFlowLps(double throttle, double v_kmh) const
{
    return baseFuelFlow(K_SPORT, throttle, v_kmh);
}
