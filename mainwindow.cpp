#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include "Car.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->engineInfo->setText("Engine OFF");
    ui->engineInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->throttleInfo->setText("Throttle: 0");
    ui->throttleInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->brakeInfo->setText("Brake OFF");
    ui->brakeInfo->setStyleSheet("color: red; font-weight: bold;");
    refreshUI();

    // startButton to objectName przycisku w .ui
    connect(ui->engineButton, &QPushButton::clicked, this, &MainWindow::engineButtonClicked);
    connect(ui->throttleButton, &QPushButton::clicked, this, &MainWindow::throttleButtonClicked);
    connect(ui->brakeButton, &QPushButton::clicked, this, &MainWindow::brakeButtonClicked);
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
    if(car.getThrottle() == 0){
        setStatus(ui->throttleInfo, "Throttle: 0", "red");
    } else {
        setStatus(ui->throttleInfo, "Throttle: 1", "green");
    }
    // brake
    if(!car.getBrakeStatus()){
        setStatus(ui->brakeInfo, "Brake OFF", "green");
    } else {
        setStatus(ui->brakeInfo, "Brake ON", "red");
    }


}
void MainWindow::engineButtonClicked(){
    if(car.getEngineStatus()){
        car.setEngineStatus(false);
        refreshUI();
    } else {
        car.setEngineStatus(true);
        refreshUI();
    }
}

void MainWindow::throttleButtonClicked() {
    if(car.getThrottle() == 0.0){
        car.setThrottle(1.0);
    } else {
        car.setThrottle(0.0);
    }
    refreshUI();

}

void MainWindow::brakeButtonClicked() {
    if(!car.getBrakeStatus()){
        car.setBrakeStatus(true);
    } else {
        car.setBrakeStatus(false);
    }
    refreshUI();
}

