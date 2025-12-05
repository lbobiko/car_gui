#include "FuelTank.h"
#include <algorithm>

FuelTank::FuelTank(double capacity_l, double level_l)
    : capacity_l_(capacity_l),
    level_l_(level_l)
{
    if (capacity_l_ < 0.0) capacity_l_ = 0.0;
    if (level_l_   < 0.0) level_l_   = 0.0;
    if (level_l_   > capacity_l_) level_l_ = capacity_l_;
}

double FuelTank::getCapacity() const{
    return capacity_l_;
}

double FuelTank::getLevel() const{
    return level_l_;
}

void FuelTank::addFuel(double liters)
{
    if (liters <= 0.0) return;
    level_l_ += liters;
    if (level_l_ > capacity_l_) {
        level_l_ = capacity_l_;
    }
}

double FuelTank::consume(double liters)
{
    if (liters <= 0.0 || level_l_ <= 0.0) {
        return 0.0;
    }

    double used = liters;
    if (used > level_l_) {
        used = level_l_;
    }

    level_l_ -= used;
    return used;
}

bool FuelTank::isEmpty() const{
    return level_l_ <= 0.0;
}
