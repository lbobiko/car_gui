#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H
#include <QString>

class SurfaceModel {
public:
    virtual ~SurfaceModel() = default;
    virtual double mu() const = 0;          // współczynnik przyczepności
    virtual QString name() const = 0;       // do GUI/debug
};

// --- Konkretne strategie ---

class AsphaltDry : public SurfaceModel {
public:
    double mu() const override { return 0.95; }
    QString name() const override { return "Asphalt (Dry)"; }
};

class AsphaltWet : public SurfaceModel {
public:
    double mu() const override { return 0.60; }
    QString name() const override { return "Asphalt (Wet)"; }
};

class Gravel : public SurfaceModel {
public:
    double mu() const override { return 0.55; } // do dostrojenia
    QString name() const override { return "Gravel"; }
};

class Ice : public SurfaceModel {
public:
    double mu() const override { return 0.15; }
    QString name() const override { return "Ice"; }
};


#endif // SURFACEMODEL_H
