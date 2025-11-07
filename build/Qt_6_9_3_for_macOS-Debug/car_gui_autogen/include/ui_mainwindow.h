/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *engineButton;
    QPushButton *throttleButton;
    QPushButton *brakeButton;
    QLabel *speedInfo;
    QLabel *speedText;
    QLabel *distanceText;
    QLabel *distanceInfo;
    QLabel *engineInfo;
    QLabel *throttleInfo;
    QLabel *throttleDetail;
    QLabel *brakeInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        engineButton = new QPushButton(centralwidget);
        engineButton->setObjectName("engineButton");
        engineButton->setGeometry(QRect(30, 460, 151, 41));
        throttleButton = new QPushButton(centralwidget);
        throttleButton->setObjectName("throttleButton");
        throttleButton->setGeometry(QRect(590, 460, 151, 41));
        brakeButton = new QPushButton(centralwidget);
        brakeButton->setObjectName("brakeButton");
        brakeButton->setGeometry(QRect(410, 460, 151, 41));
        speedInfo = new QLabel(centralwidget);
        speedInfo->setObjectName("speedInfo");
        speedInfo->setGeometry(QRect(210, 280, 111, 41));
        speedText = new QLabel(centralwidget);
        speedText->setObjectName("speedText");
        speedText->setGeometry(QRect(210, 340, 131, 31));
        distanceText = new QLabel(centralwidget);
        distanceText->setObjectName("distanceText");
        distanceText->setGeometry(QRect(10, 10, 141, 41));
        distanceInfo = new QLabel(centralwidget);
        distanceInfo->setObjectName("distanceInfo");
        distanceInfo->setGeometry(QRect(160, 10, 111, 41));
        engineInfo = new QLabel(centralwidget);
        engineInfo->setObjectName("engineInfo");
        engineInfo->setGeometry(QRect(30, 400, 121, 41));
        throttleInfo = new QLabel(centralwidget);
        throttleInfo->setObjectName("throttleInfo");
        throttleInfo->setGeometry(QRect(590, 370, 151, 41));
        throttleDetail = new QLabel(centralwidget);
        throttleDetail->setObjectName("throttleDetail");
        throttleDetail->setGeometry(QRect(590, 410, 151, 41));
        brakeInfo = new QLabel(centralwidget);
        brakeInfo->setObjectName("brakeInfo");
        brakeInfo->setGeometry(QRect(410, 410, 151, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 34));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        engineButton->setText(QCoreApplication::translate("MainWindow", "Engine ON/OFF", nullptr));
        throttleButton->setText(QCoreApplication::translate("MainWindow", "Throttle", nullptr));
        brakeButton->setText(QCoreApplication::translate("MainWindow", "Brake", nullptr));
        speedInfo->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        speedText->setText(QCoreApplication::translate("MainWindow", "SPEED", nullptr));
        distanceText->setText(QCoreApplication::translate("MainWindow", "Distance travelled:", nullptr));
        distanceInfo->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        engineInfo->setText(QCoreApplication::translate("MainWindow", "Engine OFF", nullptr));
        throttleInfo->setText(QString());
        throttleDetail->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        brakeInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
