#include "Transmission.h"
#include <algorithm>
#include <QDebug>

Transmission::Transmission() {
    // 0 = luz
    gears_ = {0.0, 3.50, 2.20, 1.50, 1.10, 0.90, 0.75}; // 7 elementów -> maxGear=6
    gear_ = 0;
}

void Transmission::toggleMode() {
    mode_ = (mode_ == ShiftMode::Auto) ? ShiftMode::Manual : ShiftMode::Auto;
}

double Transmission::currentRatio() const {
    if (gear_ < 0 || gear_ >= (int)gears_.size()) return 0.0;
    return gears_[gear_];
}

double Transmission::totalRatio() const {
    if (gear_ == 0) return 0.0;
    return currentRatio() * finalDrive_;
}

void Transmission::shiftUp() {
    if (gear_ < maxGear()) gear_++;
}

void Transmission::shiftDown() {
    if (gear_ > 0) gear_--;
}

void Transmission::updateAuto(double rpm, double throttle)
{
    if (mode_ != ShiftMode::Auto) return;

    // Jak stoi i jest gaz -> wrzuca 1 żeby ruszyć
    if (gear_ == 0 && throttle > 0.05) {
        gear_ = 1;
        return;
    }

    // Bazowe progi
    double up   = upRpm_;
    double down = downRpm_;

    // Gaz wpływa na zmianę
    if (throttle > 0.7) { up += 600; down += 200; }
    if (throttle < 0.2) { up -= 600; down -= 150; }

    // Zabezpieczenie żeby down zawsze było sensownie niżej niż up
    if (down > up - 500) down = up - 500;

    // Upshift: tylko jeśli nie jesteśmy na najwyższym
    if (rpm > up && gear_ < maxGear()) {
        gear_++;
        return;
    }

    // Downshift: nie schodzi poniżej 1 (automat nie powinien wrzucać luzu w trakcie jazdy)
    if (rpm < down && gear_ > 1) {
        gear_--;
        return;
    }
    //qDebug() << "AUTO gear=" << gear_ << " rpm=" << rpm << " up=" << up << " max=" << maxGear();

}

