#ifndef CONSUMPTION_MODEL_H
#define CONSUMPTION_MODEL_H

class ConsumptionModel {
public:
    virtual ~ConsumptionModel() = default;

    // przepływ paliwa [L/s]
    virtual double fuelFlowLps(double throttle, double v_kmh) const = 0;
};

class EcoConsumption : public ConsumptionModel {
public:
    double fuelFlowLps(double throttle, double v_kmh) const override;
};

class NormalConsumption : public ConsumptionModel {
public:
    double fuelFlowLps(double throttle, double v_kmh) const override;
};

class SportConsumption : public ConsumptionModel {
public:
    double fuelFlowLps(double throttle, double v_kmh) const override;
};

#endif
