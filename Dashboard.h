#ifndef DASHBOARD_H
#define DASHBOARD_H
#pragma once
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

class Car;

class Dashboard {
public:
    Dashboard(QLabel* engineInfo,
              QLabel* throttleInfo,
              QLabel* throttleDetail,
              QLabel* brakeInfo,
              QLabel* speedInfo,
              QLabel* distanceInfo,
              QLabel* fuelInfo,
              QLabel* tripDistanceInfo,
              QLabel* tripAvgConsInfo,
              QLabel* tripTimeInfo,
              QLabel* tripAvgSpeedInfo,
              QProgressBar* fuelBar,
              QLabel* gearInfo,
              QLabel* rpmInfo,
              QLabel* shiftModeInfo,
              QCheckBox* absCheck,
              QCheckBox* tcsCheck,
              QComboBox* surfaceCombo,
              QLabel* absStatusInfo,
              QLabel* tcsStatusInfo,
              QLabel* gradeInfo);

    void refresh(const Car& car);

private:
    QLabel* engineInfo_    = nullptr;
    QLabel* throttleInfo_  = nullptr;
    QLabel* throttleDet_   = nullptr;
    QLabel* brakeInfo_     = nullptr;
    QLabel* speedInfo_     = nullptr;
    QLabel* distanceInfo_  = nullptr;
    QLabel* fuelInfo_      = nullptr;
    QLabel* gearInfo_      = nullptr;
    QLabel* rpmInfo_      = nullptr;
    QLabel* shiftModeInfo_      = nullptr;

    QLabel* tripDistanceInfo_ = nullptr;
    QLabel* tripAvgConsInfo_  = nullptr;
    QLabel* tripTimeInfo_     = nullptr;
    QLabel* tripAvgSpeedInfo_ = nullptr;

    QProgressBar* fuelBar_   = nullptr;

    QCheckBox* absCheck_ = nullptr;
    QCheckBox* tcsCheck_ = nullptr;
    QComboBox* surfaceCombo_ = nullptr;
    QLabel* absStatusInfo_ = nullptr;
    QLabel* tcsStatusInfo_ = nullptr;

    QLabel* gradeInfo_ = nullptr;

    void setStatus(QLabel* lbl, const QString& text, const QString& color);
};
#endif // DASHBOARD_H
