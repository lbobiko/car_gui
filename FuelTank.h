#ifndef FUELTANK_H
#define FUELTANK_H

class FuelTank
{
private:
    double capacity_l_;
    double level_l_;

public:
    FuelTank(double capacity_l, double level_l);
    double getCapacity() const;
    double getLevel() const;
    bool isEmpty() const;
    void addFuel(double liters);
    double consume(double liters);
};

#endif // FUELTANK_H
