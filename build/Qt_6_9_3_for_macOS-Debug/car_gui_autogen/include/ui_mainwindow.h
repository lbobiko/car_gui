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
#include <QtWidgets/QHBoxLayout>
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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *engineButton;
    QPushButton *throttleButton;
    QPushButton *brakeButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *engineInfo;
    QLabel *throttleInfo;
    QLabel *brakeInfo;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *speedText;
    QLabel *speedInfo;
    QLabel *distanceText;
    QLabel *distanceInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(30, 420, 751, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        engineButton = new QPushButton(horizontalLayoutWidget);
        engineButton->setObjectName("engineButton");

        horizontalLayout->addWidget(engineButton);

        throttleButton = new QPushButton(horizontalLayoutWidget);
        throttleButton->setObjectName("throttleButton");

        horizontalLayout->addWidget(throttleButton);

        brakeButton = new QPushButton(horizontalLayoutWidget);
        brakeButton->setObjectName("brakeButton");

        horizontalLayout->addWidget(brakeButton);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(30, 340, 751, 71));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        engineInfo = new QLabel(horizontalLayoutWidget_2);
        engineInfo->setObjectName("engineInfo");

        horizontalLayout_2->addWidget(engineInfo);

        throttleInfo = new QLabel(horizontalLayoutWidget_2);
        throttleInfo->setObjectName("throttleInfo");

        horizontalLayout_2->addWidget(throttleInfo);

        brakeInfo = new QLabel(horizontalLayoutWidget_2);
        brakeInfo->setObjectName("brakeInfo");

        horizontalLayout_2->addWidget(brakeInfo);

        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(30, 220, 751, 91));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        speedText = new QLabel(horizontalLayoutWidget_3);
        speedText->setObjectName("speedText");

        horizontalLayout_3->addWidget(speedText);

        speedInfo = new QLabel(horizontalLayoutWidget_3);
        speedInfo->setObjectName("speedInfo");

        horizontalLayout_3->addWidget(speedInfo);

        distanceText = new QLabel(horizontalLayoutWidget_3);
        distanceText->setObjectName("distanceText");

        horizontalLayout_3->addWidget(distanceText);

        distanceInfo = new QLabel(horizontalLayoutWidget_3);
        distanceInfo->setObjectName("distanceInfo");

        horizontalLayout_3->addWidget(distanceInfo);

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
        engineInfo->setText(QString());
        throttleInfo->setText(QString());
        brakeInfo->setText(QString());
        speedText->setText(QCoreApplication::translate("MainWindow", "Current speed:", nullptr));
        speedInfo->setText(QString());
        distanceText->setText(QCoreApplication::translate("MainWindow", "Distance travelled:", nullptr));
        distanceInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
