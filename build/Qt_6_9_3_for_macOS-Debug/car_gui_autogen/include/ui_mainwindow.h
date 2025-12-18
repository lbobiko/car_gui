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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QLabel *distanceText;
    QLabel *distanceInfo;
    QLabel *engineInfo;
    QLabel *throttleInfo;
    QLabel *throttleDetail;
    QLabel *brakeInfo;
    QPushButton *quitButton;
    QPushButton *helpButton;
    QLabel *fuelInfo;
    QPushButton *refuelButton;
    QTableWidget *tableWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *resetTripButton;
    QLabel *tripTimeInfo;
    QLabel *tripDistanceInfo;
    QLabel *tripAvgSpeedInfo;
    QLabel *tripAvgConsInfo;
    QComboBox *modeCombo;
    QLabel *label_6;
    QLabel *modeLabel;
    QProgressBar *fuelBar;
    QLabel *gearInfo;
    QLabel *rpmInfo;
    QLabel *shiftModeInfo;
    QPushButton *btnShiftUp;
    QPushButton *btnShiftDown;
    QPushButton *btnToggleShiftMode;
    QFrame *frame;
    QComboBox *surfaceCombo;
    QCheckBox *absCheckBox;
    QCheckBox *tcsCheckBox;
    QLabel *absStatusInfo;
    QLabel *tcsStatusInfo;
    QFrame *frame_2;
    QLabel *gradeInfo;
    QLabel *label_7;
    QLabel *pauseInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 662);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        engineButton = new QPushButton(centralwidget);
        engineButton->setObjectName("engineButton");
        engineButton->setGeometry(QRect(10, 550, 151, 41));
        throttleButton = new QPushButton(centralwidget);
        throttleButton->setObjectName("throttleButton");
        throttleButton->setGeometry(QRect(590, 550, 151, 41));
        brakeButton = new QPushButton(centralwidget);
        brakeButton->setObjectName("brakeButton");
        brakeButton->setGeometry(QRect(400, 550, 151, 41));
        speedInfo = new QLabel(centralwidget);
        speedInfo->setObjectName("speedInfo");
        speedInfo->setGeometry(QRect(40, 110, 151, 41));
        distanceText = new QLabel(centralwidget);
        distanceText->setObjectName("distanceText");
        distanceText->setGeometry(QRect(10, 10, 141, 41));
        distanceInfo = new QLabel(centralwidget);
        distanceInfo->setObjectName("distanceInfo");
        distanceInfo->setGeometry(QRect(160, 10, 111, 41));
        engineInfo = new QLabel(centralwidget);
        engineInfo->setObjectName("engineInfo");
        engineInfo->setGeometry(QRect(10, 500, 121, 41));
        throttleInfo = new QLabel(centralwidget);
        throttleInfo->setObjectName("throttleInfo");
        throttleInfo->setGeometry(QRect(590, 480, 151, 41));
        throttleDetail = new QLabel(centralwidget);
        throttleDetail->setObjectName("throttleDetail");
        throttleDetail->setGeometry(QRect(590, 510, 151, 41));
        brakeInfo = new QLabel(centralwidget);
        brakeInfo->setObjectName("brakeInfo");
        brakeInfo->setGeometry(QRect(400, 500, 151, 41));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(640, 10, 150, 41));
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName("helpButton");
        helpButton->setGeometry(QRect(640, 60, 151, 41));
        fuelInfo = new QLabel(centralwidget);
        fuelInfo->setObjectName("fuelInfo");
        fuelInfo->setGeometry(QRect(10, 300, 180, 41));
        refuelButton = new QPushButton(centralwidget);
        refuelButton->setObjectName("refuelButton");
        refuelButton->setGeometry(QRect(210, 550, 151, 41));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(540, 120, 256, 241));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(620, 130, 111, 20));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(550, 190, 81, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(550, 250, 91, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(550, 160, 58, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(550, 220, 91, 16));
        resetTripButton = new QPushButton(centralwidget);
        resetTripButton->setObjectName("resetTripButton");
        resetTripButton->setGeometry(QRect(690, 320, 100, 32));
        tripTimeInfo = new QLabel(centralwidget);
        tripTimeInfo->setObjectName("tripTimeInfo");
        tripTimeInfo->setGeometry(QRect(670, 160, 71, 16));
        tripDistanceInfo = new QLabel(centralwidget);
        tripDistanceInfo->setObjectName("tripDistanceInfo");
        tripDistanceInfo->setGeometry(QRect(670, 190, 81, 16));
        tripAvgSpeedInfo = new QLabel(centralwidget);
        tripAvgSpeedInfo->setObjectName("tripAvgSpeedInfo");
        tripAvgSpeedInfo->setGeometry(QRect(670, 220, 81, 16));
        tripAvgConsInfo = new QLabel(centralwidget);
        tripAvgConsInfo->setObjectName("tripAvgConsInfo");
        tripAvgConsInfo->setGeometry(QRect(670, 250, 81, 16));
        modeCombo = new QComboBox(centralwidget);
        modeCombo->addItem(QString());
        modeCombo->addItem(QString());
        modeCombo->addItem(QString());
        modeCombo->setObjectName("modeCombo");
        modeCombo->setGeometry(QRect(550, 320, 103, 32));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(550, 290, 91, 16));
        modeLabel = new QLabel(centralwidget);
        modeLabel->setObjectName("modeLabel");
        modeLabel->setGeometry(QRect(10, 200, 141, 41));
        fuelBar = new QProgressBar(centralwidget);
        fuelBar->setObjectName("fuelBar");
        fuelBar->setGeometry(QRect(10, 250, 118, 23));
        fuelBar->setValue(40);
        fuelBar->setTextVisible(true);
        gearInfo = new QLabel(centralwidget);
        gearInfo->setObjectName("gearInfo");
        gearInfo->setGeometry(QRect(210, 310, 58, 16));
        rpmInfo = new QLabel(centralwidget);
        rpmInfo->setObjectName("rpmInfo");
        rpmInfo->setGeometry(QRect(320, 110, 201, 41));
        shiftModeInfo = new QLabel(centralwidget);
        shiftModeInfo->setObjectName("shiftModeInfo");
        shiftModeInfo->setGeometry(QRect(350, 310, 151, 16));
        btnShiftUp = new QPushButton(centralwidget);
        btnShiftUp->setObjectName("btnShiftUp");
        btnShiftUp->setGeometry(QRect(640, 420, 131, 32));
        btnShiftDown = new QPushButton(centralwidget);
        btnShiftDown->setObjectName("btnShiftDown");
        btnShiftDown->setGeometry(QRect(640, 450, 131, 32));
        btnToggleShiftMode = new QPushButton(centralwidget);
        btnToggleShiftMode->setObjectName("btnToggleShiftMode");
        btnToggleShiftMode->setGeometry(QRect(640, 390, 131, 32));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(260, 390, 341, 91));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        surfaceCombo = new QComboBox(frame);
        surfaceCombo->setObjectName("surfaceCombo");
        surfaceCombo->setGeometry(QRect(120, 50, 141, 32));
        absCheckBox = new QCheckBox(frame);
        absCheckBox->setObjectName("absCheckBox");
        absCheckBox->setGeometry(QRect(130, 10, 85, 20));
        absCheckBox->setChecked(true);
        tcsCheckBox = new QCheckBox(frame);
        tcsCheckBox->setObjectName("tcsCheckBox");
        tcsCheckBox->setGeometry(QRect(240, 10, 85, 20));
        tcsCheckBox->setChecked(true);
        absStatusInfo = new QLabel(frame);
        absStatusInfo->setObjectName("absStatusInfo");
        absStatusInfo->setGeometry(QRect(10, 10, 81, 31));
        tcsStatusInfo = new QLabel(frame);
        tcsStatusInfo->setObjectName("tcsStatusInfo");
        tcsStatusInfo->setGeometry(QRect(10, 60, 91, 21));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 390, 221, 91));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gradeInfo = new QLabel(frame_2);
        gradeInfo->setObjectName("gradeInfo");
        gradeInfo->setGeometry(QRect(20, 10, 181, 31));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 60, 191, 16));
        pauseInfo = new QLabel(centralwidget);
        pauseInfo->setObjectName("pauseInfo");
        pauseInfo->setGeometry(QRect(300, 10, 121, 31));
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
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        engineButton->setToolTip(QCoreApplication::translate("MainWindow", "Engine ON or OFF", nullptr));
#endif // QT_CONFIG(tooltip)
        engineButton->setText(QCoreApplication::translate("MainWindow", "Engine ON/OFF", nullptr));
#if QT_CONFIG(tooltip)
        throttleButton->setToolTip(QCoreApplication::translate("MainWindow", "Press throttle", nullptr));
#endif // QT_CONFIG(tooltip)
        throttleButton->setText(QCoreApplication::translate("MainWindow", "Throttle", nullptr));
#if QT_CONFIG(tooltip)
        brakeButton->setToolTip(QCoreApplication::translate("MainWindow", "Press brake", nullptr));
#endif // QT_CONFIG(tooltip)
        brakeButton->setText(QCoreApplication::translate("MainWindow", "Brake", nullptr));
        speedInfo->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        distanceText->setText(QCoreApplication::translate("MainWindow", "Distance travelled:", nullptr));
        distanceInfo->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        engineInfo->setText(QCoreApplication::translate("MainWindow", "Engine OFF", nullptr));
        throttleInfo->setText(QString());
        throttleDetail->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        brakeInfo->setText(QString());
#if QT_CONFIG(tooltip)
        quitButton->setToolTip(QCoreApplication::translate("MainWindow", "Quit simmulation", nullptr));
#endif // QT_CONFIG(tooltip)
        quitButton->setText(QCoreApplication::translate("MainWindow", "Quit program", nullptr));
#if QT_CONFIG(tooltip)
        helpButton->setToolTip(QCoreApplication::translate("MainWindow", "Show help window", nullptr));
#endif // QT_CONFIG(tooltip)
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        fuelInfo->setText(QCoreApplication::translate("MainWindow", "fuel", nullptr));
#if QT_CONFIG(tooltip)
        refuelButton->setToolTip(QCoreApplication::translate("MainWindow", "Add 5L. of fuel", nullptr));
#endif // QT_CONFIG(tooltip)
        refuelButton->setText(QCoreApplication::translate("MainWindow", "Refuel +5L", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Trip computer", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Distance", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Avg. cons.", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Avg. speed", nullptr));
#if QT_CONFIG(tooltip)
        resetTripButton->setToolTip(QCoreApplication::translate("MainWindow", "Reset current trip", nullptr));
#endif // QT_CONFIG(tooltip)
        resetTripButton->setText(QCoreApplication::translate("MainWindow", "Reset trip", nullptr));
        tripTimeInfo->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
        tripDistanceInfo->setText(QCoreApplication::translate("MainWindow", "dist", nullptr));
        tripAvgSpeedInfo->setText(QCoreApplication::translate("MainWindow", "avg sp", nullptr));
        tripAvgConsInfo->setText(QCoreApplication::translate("MainWindow", "avg cons", nullptr));
        modeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Eco", nullptr));
        modeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Normal", nullptr));
        modeCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Sport", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "Mode change:", nullptr));
        modeLabel->setText(QCoreApplication::translate("MainWindow", "Mode: normal", nullptr));
        gearInfo->setText(QCoreApplication::translate("MainWindow", "Gear", nullptr));
        rpmInfo->setText(QCoreApplication::translate("MainWindow", "rpm", nullptr));
        shiftModeInfo->setText(QCoreApplication::translate("MainWindow", "shift", nullptr));
#if QT_CONFIG(tooltip)
        btnShiftUp->setToolTip(QCoreApplication::translate("MainWindow", "Shift up (Manual)", nullptr));
#endif // QT_CONFIG(tooltip)
        btnShiftUp->setText(QCoreApplication::translate("MainWindow", "Gear +", nullptr));
#if QT_CONFIG(tooltip)
        btnShiftDown->setToolTip(QCoreApplication::translate("MainWindow", "Shift down (Manual)", nullptr));
#endif // QT_CONFIG(tooltip)
        btnShiftDown->setText(QCoreApplication::translate("MainWindow", "Gear -", nullptr));
#if QT_CONFIG(tooltip)
        btnToggleShiftMode->setToolTip(QCoreApplication::translate("MainWindow", "Toggle shift mode", nullptr));
#endif // QT_CONFIG(tooltip)
        btnToggleShiftMode->setText(QCoreApplication::translate("MainWindow", "Auto/Manual", nullptr));
#if QT_CONFIG(tooltip)
        surfaceCombo->setToolTip(QCoreApplication::translate("MainWindow", "Pick a suface for simmulation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        absCheckBox->setToolTip(QCoreApplication::translate("MainWindow", "Enable/Disable ABS", nullptr));
#endif // QT_CONFIG(tooltip)
        absCheckBox->setText(QCoreApplication::translate("MainWindow", "ABS", nullptr));
#if QT_CONFIG(tooltip)
        tcsCheckBox->setToolTip(QCoreApplication::translate("MainWindow", "Enable/Disable TCS", nullptr));
#endif // QT_CONFIG(tooltip)
        tcsCheckBox->setText(QCoreApplication::translate("MainWindow", "TCS", nullptr));
        absStatusInfo->setText(QCoreApplication::translate("MainWindow", "ABS check", nullptr));
        tcsStatusInfo->setText(QCoreApplication::translate("MainWindow", "TCS check", nullptr));
        gradeInfo->setText(QCoreApplication::translate("MainWindow", "Grade: 0%", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Use '[' and ']' to change grade", nullptr));
        pauseInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
