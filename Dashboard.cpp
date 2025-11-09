#include "Dashboard.h"
#include "Car.h"

Dashboard::Dashboard(QLabel* engineInfo,
                     QLabel* throttleInfo,
                     QLabel* throttleDetail,
                     QLabel* brakeInfo,
                     QLabel* speedInfo,
                     QLabel* distanceInfo)
    : engineInfo_(engineInfo),
    throttleInfo_(throttleInfo),
    throttleDet_(throttleDetail),
    brakeInfo_(brakeInfo),
    speedInfo_(speedInfo),
    distanceInfo_(distanceInfo)
{
    // opcjonalne startowe wartości/formaty
    if (speedInfo_) speedInfo_->setStyleSheet(
            "font-size:28px; font-weight:bold; font-family:'Courier New';");
}

void Dashboard::setStatus(QLabel* lbl, const QString& text, const QString& color) {
    if (!lbl) return;
    lbl->setText(text);
    lbl->setStyleSheet(QString("color:%1; font-weight:bold;").arg(color));
}

void Dashboard::refresh(const Car& car) {
    // Engine
    const bool eng = car.getEngineStatus();
    setStatus(engineInfo_, eng ? "Engine ON" : "Engine OFF", eng ? "green" : "red");

    // Throttle
    const double t = car.getThrottle();
    setStatus(throttleInfo_, "Throttle", t > 0.0 ? "green" : "red");
    if (throttleDet_) {
        throttleDet_->setText(QString::number(t * 100.0, 'f', 0) + "%");
        throttleDet_->setStyleSheet(
            QString("color:%1; font-weight:bold;").arg(t > 0.0 ? "green" : "red"));
    }

    // Brake
    const bool br = car.getBrakeStatus();
    setStatus(brakeInfo_, br ? "Brake ON" : "Brake OFF", br ? "red" : "green");

    // Speed (kolor w zależności od zakresu)
    const double v = car.getCurrentSpeed();
    if (speedInfo_) {
        const QString vColor = (v < 100.0) ? "green" : (v < 150.0) ? "orange" : "red";
        speedInfo_->setStyleSheet(
            QString("color:%1; font-size:28px; font-weight:bold; font-family:'Courier New';")
                .arg(vColor));
        speedInfo_->setText(QString::number(v, 'f', 2));
    }

    // Distance
    if (distanceInfo_) {
        const double dKm = car.getDistance() / 1000.0;
        distanceInfo_->setText(QString::number(dKm, 'f', 2) + " km");
    }
}
