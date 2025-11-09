#ifndef DASHBOARD_H
#define DASHBOARD_H
#pragma once
#include <QWidget>
#include <QLabel>
#include <QString>

class Car; // forward

class Dashboard {
public:
    Dashboard(QLabel* engineInfo,
              QLabel* throttleInfo,
              QLabel* throttleDetail,
              QLabel* brakeInfo,
              QLabel* speedInfo,
              QLabel* distanceInfo);

    void refresh(const Car& car);

private:
    QLabel* engineInfo_    = nullptr;
    QLabel* throttleInfo_  = nullptr;
    QLabel* throttleDet_   = nullptr;
    QLabel* brakeInfo_     = nullptr;
    QLabel* speedInfo_     = nullptr;
    QLabel* distanceInfo_  = nullptr;

    void setStatus(QLabel* lbl, const QString& text, const QString& color);
};
#endif // DASHBOARD_H
