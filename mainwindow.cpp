#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include "Car.h"
#include "Constants.h"
#include <QMessageBox>
#include <algorithm> // std::max

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->engineInfo->setText("Engine OFF");
    ui->engineInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->throttleInfo->setText("Throttle");
    ui->throttleInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->brakeInfo->setText("Brake OFF");
    ui->brakeInfo->setStyleSheet("color: red; font-weight: bold;");
    refreshUI();

    // startButton to objectName przycisku w .ui
    connect(ui->engineButton, &QPushButton::clicked, this, &MainWindow::engineButtonClicked);
    connect(ui->throttleButton, &QPushButton::clicked, this, &MainWindow::throttleButtonClicked);
    connect(ui->brakeButton, &QPushButton::clicked, this, &MainWindow::brakeButtonClicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(DT * 1000); // czyli co 20 ms
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatus(QLabel* lbl, const QString& text, const QString& color)
{
    lbl->setText(text);
    lbl->setStyleSheet(QString("color: %1; font-weight: bold;").arg(color));
}

void MainWindow::refreshUI()
{
    // silnik
    if (car.getEngineStatus()){
        setStatus(ui->engineInfo,   "Engine ON",  "green");
    } else {
        setStatus(ui->engineInfo,   "Engine OFF", "red");
    }
    // throttle
    double thr = car.getThrottle() * 100.0;  // przeliczanie na %
    QString thrString = QString::number(thr, 'f', 0); // konwersja double na string

    if(car.getThrottle() == 0){
        setStatus(ui->throttleInfo, "Throttle", "red");
        ui->throttleDetail->setStyleSheet("color: red; font-weight: bold;");

    } else {
        setStatus(ui->throttleInfo, "Throttle", "green");
        ui->throttleDetail->setStyleSheet("color: green; font-weight: bold;");
    }
    ui->throttleDetail->setText(thrString + "%");

    // brake
    if(!car.getBrakeStatus()){
        setStatus(ui->brakeInfo, "Brake OFF", "green");
    } else {
        setStatus(ui->brakeInfo, "Brake ON", "red");
    }
    // predkosc
    double speed = car.getCurrentSpeed();
    QString speedString = QString::number(speed, 'f', 2);
    ui->speedInfo->setStyleSheet("color: green; font-weight: bold; font-size: 28px; font-family: 'Courier New';");
    ui->speedInfo->setText(speedString);
    QString color = (speed < 100.0) ? "green" : (speed < 150.0) ? "orange" : "red";
    ui->speedInfo->setStyleSheet(QString("color: %1; font-weight: bold; font-size: 28px; font-family: 'Courier New';").arg(color));

    // dystans w kilometrach
    QString distString = QString::number(car.getDistance() / 1000.0, 'f', 2);
    ui->distanceInfo->setText(distString + " km");
    // ui->lcdDistance->display(car.getDistance() / 1000.0); // km

}

void MainWindow::updateSimulation()
{
    car.update(DT);
    refreshUI();
}

void Car::update(double dt)
{
    // gaz
    if (throttle > 0 && !brake.getBrakePressed() && engine.getEngineStatus())
        currentSpeed += ACCELERATION * dt;

    // hamulec
    if (brake.getBrakePressed()) {
        currentSpeed = std::max(0.0, currentSpeed - BRAKE_DECEL * dt);
    }

    // opory toczenia
    if (throttle == 0 && !brake.getBrakePressed())
        currentSpeed -= COAST_DECEL * dt;

    // ograniczenia
    if (currentSpeed < 0)
        currentSpeed = 0;
    if (currentSpeed > MAX_SPEED)
        currentSpeed = MAX_SPEED;

    // dystans
    distance += currentSpeed * dt / 3.6; // km/h → m/s
}


void MainWindow::engineButtonClicked() {
    if (car.getEngineStatus() && car.getCurrentSpeed() > 0) {
        QMessageBox::warning(
            this,                                // rodzic - okno główne
            "ODMOWA!",                          // tytuł okna
            "Nie można wyłączyć silnika w trakcie jazdy!" // treść komunikatu
            );
        return;
    }

    if (!car.getEngineStatus())
        car.setEngineStatus(true);
    else
        car.setEngineStatus(false);

    //refreshUI();
}

void MainWindow::throttleButtonClicked() {
    if (!car.getEngineStatus()){
        QMessageBox::warning(
            this,
            "ODMOWA!",
            "Silnik jest wyłączony!"
            );
        return;
    }

    if(car.getThrottle() == 0.0){
        car.setThrottle(1.0);
    } else {
        car.setThrottle(0.0);
    }

}

void MainWindow::brakeButtonClicked() {
    if(!car.getBrakeStatus()){
        car.setBrakeStatus(true);
    } else {
        car.setBrakeStatus(false);
    }
    //refreshUI();
}

