#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "Car.h"

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

private slots:
    void engineButtonClicked();
    void throttleButtonClicked();
    void brakeButtonClicked();

private:
    Ui::MainWindow *ui;
    Car car;
    void refreshUI();  // odświeża wszystkie labele
    void setStatus(QLabel* lbl, const QString& text, const QString& color);


};
#endif // MAINWINDOW_H
