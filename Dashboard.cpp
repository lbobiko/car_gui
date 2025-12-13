#include "Dashboard.h"
#include "Car.h"

Dashboard::Dashboard(QLabel* engineInfo,
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
                     QLabel* tcsStatusInfo)
    : engineInfo_(engineInfo),
    throttleInfo_(throttleInfo),
    throttleDet_(throttleDetail),
    brakeInfo_(brakeInfo),
    speedInfo_(speedInfo),
    distanceInfo_(distanceInfo),
    fuelInfo_(fuelInfo),
    tripDistanceInfo_(tripDistanceInfo),
    tripAvgConsInfo_(tripAvgConsInfo),
    tripTimeInfo_(tripTimeInfo),
    tripAvgSpeedInfo_(tripAvgSpeedInfo),
    fuelBar_(fuelBar),
    gearInfo_(gearInfo),
    rpmInfo_(rpmInfo),
    shiftModeInfo_(shiftModeInfo),
    absCheck_(absCheck),
    tcsCheck_(tcsCheck),
    surfaceCombo_(surfaceCombo),
    absStatusInfo_(absStatusInfo),
    tcsStatusInfo_(tcsStatusInfo)
{
    // opcjonalne startowe wartości/formaty
    if (speedInfo_) {
        speedInfo_->setStyleSheet("font-size:28px; font-weight:bold; font-family:'Courier New';");
    }
    if (fuelBar_) {
        fuelBar_->setRange(0, 100);
        fuelBar_->setValue(0);
        fuelBar_->setTextVisible(false);
    }

    if (surfaceCombo_) {
        surfaceCombo_->clear();
        surfaceCombo_->addItem("Dry",  0);
        surfaceCombo_->addItem("Wet",  1);
        surfaceCombo_->addItem("Ice",  2);
    }
}

void Dashboard::setStatus(QLabel* lbl, const QString& text, const QString& color) {
    if (!lbl) return;
    lbl->setText(text);
    lbl->setStyleSheet(QString("color:%1; font-weight:bold;").arg(color));
}

void Dashboard::refresh(const Car& car) {
    // Engine
    const bool eng = car.getEngineStatus();
    if (eng) {
        setStatus(engineInfo_, "Engine ON", "green");
    } else {
        setStatus(engineInfo_, "Engine OFF", "red");
    }

    // Throttle
    const double t = car.getThrottle();
    if (t > 0.0) {
        setStatus(throttleInfo_, "Throttle", "green");
    } else {
        setStatus(throttleInfo_, "Throttle", "red");
    }

    if (throttleDet_) {
        const QString pct = QString::number(t * 100.0, 'f', 0) + "%";
        throttleDet_->setText(pct);
        if (t > 0.0) {
            throttleDet_->setStyleSheet("color: green; font-weight: bold;");
        } else {
            throttleDet_->setStyleSheet("color: red; font-weight: bold;");
        }
    }

    // Brake
    const bool br = car.getBrakeStatus();
    if (br) {
        setStatus(brakeInfo_, "Brake ON", "red");
    } else {
        setStatus(brakeInfo_, "Brake OFF", "green");
    }

    // Speed - kolor
    if (speedInfo_) {
        const double v = car.getCurrentSpeed(); // km/h
        QString color;
        if (v < 100.0) {
            color = "green";
        } else if (v < 150.0) {
            color = "orange";
        } else {
            color = "red";
        }

        speedInfo_->setStyleSheet(
            "color: " + color + "; font-size:28px; font-weight:bold; font-family:'Courier New';"
            );
        speedInfo_->setText(QString::number(v, 'f', 2));
    }

    // Distance metry -> km
    if (distanceInfo_) {
        const double dKm = car.getDistance() / 1000.0;
        distanceInfo_->setText(QString::number(dKm, 'f', 2) + " km");
    }
    // --- Fuel ---
    if (fuelInfo_) {
        double level = car.getFuelLevel();     // L
        double cap   = car.getFuelCapacity();  // L
        double perc  = (cap > 0.0) ? (level / cap) * 100.0 : 0.0;

        QString text = QString("Fuel: %1 L (%2%)")
                           .arg(level, 0, 'f', 3)
                           .arg(perc,  0, 'f', 1);

        QString color;
        if (perc > 50.0) {
            color = "green";
        } else if (perc > 20.0) {
            color = "orange";
        } else {
            color = "red";    // rezerwa
        }

        fuelInfo_->setStyleSheet(
            QString("color:%1; font-weight:bold;").arg(color));
        fuelInfo_->setText(text);
    }

    // Pasek paliwa
    if (fuelBar_) {
        double level = car.getFuelLevel();
        double cap   = car.getFuelCapacity();
        int percInt  = 0;

        if (cap > 0.0) {
            percInt = static_cast<int>((level / cap) * 100.0 + 0.5); // zaokrąglenie
        }

        if (percInt < 0)   percInt = 0;
        if (percInt > 100) percInt = 100;

        fuelBar_->setValue(percInt);

        // opcjonalnie: zmiana koloru w zależności od poziomu
        if (percInt > 50) {
            fuelBar_->setStyleSheet(
                "QProgressBar { border: 1px solid gray; border-radius: 3px; }"
                "QProgressBar::chunk { background-color: #00cc00; }");
        } else if (percInt > 20) {
            fuelBar_->setStyleSheet(
                "QProgressBar { border: 1px solid gray; border-radius: 3px; }"
                "QProgressBar::chunk { background-color: #ffcc00; }");
        } else {
            fuelBar_->setStyleSheet(
                "QProgressBar { border: 1px solid gray; border-radius: 3px; }"
                "QProgressBar::chunk { background-color: #ff0000; }");
        }
    }
    // ------------Gears------------------
    gearInfo_->setText(QString("Gear: %1").arg(car.getGear()));
    rpmInfo_->setText(QString("RPM: %1").arg((int)car.getRpm()));
    shiftModeInfo_->setText(
        QString("Mode: %1").arg(car.getShiftMode() == ShiftMode::Auto ? "Auto" : "Manual")
        );

        // ---------- TripComputer ----------
    if (tripDistanceInfo_) {
        double dKm = car.getTripDistanceKm();
        tripDistanceInfo_->setText(QString::number(dKm, 'f', 2) + " km");
    }

    if (tripAvgConsInfo_) {
        double avgL100 = car.getTripAvgConsumption();
        tripAvgConsInfo_->setText(QString::number(avgL100, 'f', 1) + " L/100km");
    }

    if (tripTimeInfo_) {
        double minutes = car.getTripTimeMinutes();
        tripTimeInfo_->setText(QString::number(minutes, 'f', 1) + " min");
    }

    if (tripAvgSpeedInfo_) {
        double vAvg = car.getTripAvgSpeedKmh();
        tripAvgSpeedInfo_->setText(QString::number(vAvg, 'f', 1) + " km/h");
    }
    if (tripTimeInfo_) {
        double minutes = car.getTripTimeMinutes();
        if (minutes <= 0.001) {
            tripTimeInfo_->setText("--");
        } else {
            tripTimeInfo_->setText(QString::number(minutes, 'f', 1) + " min");
        }
    }
    // Etap 5


    if (absStatusInfo_) {
        if (car.absActive()) setStatus(absStatusInfo_, "ABS ACTIVE", "orange");
        else                 setStatus(absStatusInfo_, "ABS", "gray");
    }

    if (tcsStatusInfo_) {
        if (car.tcsActive()) setStatus(tcsStatusInfo_, "TCS ACTIVE", "orange");
        else                 setStatus(tcsStatusInfo_, "TCS", "gray");
    }



}
