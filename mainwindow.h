#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "Car.h"
#include <QKeyEvent>
#include <QShortcut>
#include "Dashboard.h"
#include "ConsumptionModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private slots:
    void engineButtonClicked();
    void throttleButtonClicked();
    void brakeButtonClicked();
    void quitButtonClicked();
    void showHelpDialog();
    void refuelButtonClicked();

private:
    Ui::MainWindow *ui;
    Car car;
    EcoConsumption    ecoModel_;
    NormalConsumption normalModel_;
    SportConsumption  sportModel_;
    void updateSimulation();
    void setStatus(QLabel* lbl, const QString& text, const QString& color);
    QTimer *timer;
    Dashboard* dashboard = nullptr;


};
#endif // MAINWINDOW_H
