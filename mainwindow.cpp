#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include "Car.h"
#include "Constants.h"
#include <algorithm> // std::max
#include <QKeyEvent>
#include <QShortcut>
#include <QDialog>
#include <QLabel>
#include "Dashboard.h"
#include <QVBoxLayout>
#include "ConsumptionModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    car.setConsumptionModel(&normalModel_);

    // Combo z wyborem trybu
    ui->modeCombo->setCurrentIndex(1); // 0=Eco, 1=Normal, 2=Sport
    connect(ui->modeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(modeChanged(int)));

    ui->modeLabel->setText("Mode: Normal");
    ui->modeLabel->setStyleSheet("color: #00ccff; font-weight: bold; font-size: 16px;");

    ui->fuelBar->setRange(0, 100);        // procent paliwa
    ui->fuelBar->setValue(0);             // na start 0%
    ui->fuelBar->setTextVisible(false);   // bez napisu na pasku

    // żeby było widać na ciemnym tle
    ui->fuelBar->setStyleSheet(
        "QProgressBar {"
        "  border: 1px solid #555;"
        "  border-radius: 4px;"
        "  background-color: #222;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: #0f0;"
        "}"
        );

    // efekt przezroczystości dla modeLabel
    modeLabelEffect = new QGraphicsOpacityEffect(this);
    modeLabelEffect->setOpacity(1.0);
    ui->modeLabel->setGraphicsEffect(modeLabelEffect);

    dashboard = new Dashboard(
        ui->engineInfo,
        ui->throttleInfo,
        ui->throttleDetail,
        ui->brakeInfo,
        ui->speedInfo,
        ui->distanceInfo,
        ui->fuelInfo,
        ui->tripDistanceInfo,
        ui->tripAvgConsInfo,
        ui->tripTimeInfo,
        ui->tripAvgSpeedInfo,
        ui->fuelBar,
        ui->gearInfo,
        ui->rpmInfo,
        ui->shiftModeInfo

        );

    // pierwsze odświeżenie, żeby UI nie było puste
    dashboard->refresh(car);

    // żeby okno łapało klawisze
    this->setFocusPolicy(Qt::StrongFocus);

    // --- Skrzynia biegów: GUI ---

    // Zmiana trybu Auto / Manual
    connect(ui->btnToggleShiftMode, &QPushButton::clicked, this, [this]() {
        car.toggleShiftMode();
        dashboard->refresh(car);
        ui->btnToggleShiftMode->setText(
            car.getShiftMode() == ShiftMode::Auto ? "Switch to Manual" : "Switch to Auto"
            );
    });

    // Bieg w górę (tylko Manual)
    connect(ui->btnShiftUp, &QPushButton::clicked, this, [this]() {
        if (car.getShiftMode() == ShiftMode::Manual) {
            car.shiftUp();
            dashboard->refresh(car);
        }
    });

    // Bieg w dół (tylko Manual)
    connect(ui->btnShiftDown, &QPushButton::clicked, this, [this]() {
        if (car.getShiftMode() == ShiftMode::Manual) {
            car.shiftDown();
            dashboard->refresh(car);
        }
    });

    // przycisk Refuel
    connect(ui->refuelButton, &QPushButton::clicked,
            this, &MainWindow::refuelButtonClicked);

    // skrót klawiaturowy R
    auto keyRefuel = new QShortcut(QKeySequence(Qt::Key_R), this);
    keyRefuel->setContext(Qt::ApplicationShortcut);
    connect(keyRefuel, &QShortcut::activated,
            this, &MainWindow::refuelButtonClicked);

    // Skrót klawiszowy F1
    auto scHelp = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(scHelp, &QShortcut::activated, this, &MainWindow::showHelpDialog);

    // Klawisz E
    auto keyEngine = new QShortcut(QKeySequence(Qt::Key_E), this);
    keyEngine->setContext(Qt::ApplicationShortcut); // działa niezależnie od focusu
    connect(keyEngine, &QShortcut::activated, this, &MainWindow::engineButtonClicked);

    // strzałki
    auto keyUp   = new QShortcut(QKeySequence(Qt::Key_Up), this);
    auto keyDown = new QShortcut(QKeySequence(Qt::Key_Down), this);
    connect(keyUp,   &QShortcut::activated, this, [this]{ car.setThrottle(1.0); });
    connect(keyDown, &QShortcut::activated, this, [this]{ car.setThrottle(0.0); });

    // Klawisz q
    auto keyQuit = new QShortcut(QKeySequence(Qt::Key_Q), this);
    keyQuit->setContext(Qt::ApplicationShortcut);
    connect(keyQuit, &QShortcut::activated, this, &MainWindow::quitButtonClicked);

    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpDialog);

    // startButton to objectName przycisku w .ui
    connect(ui->engineButton, &QPushButton::clicked, this, &MainWindow::engineButtonClicked);
    connect(ui->throttleButton, &QPushButton::clicked, this, &MainWindow::throttleButtonClicked);

    // hamulec
    connect(ui->brakeButton, &QPushButton::pressed,  this, [this]{
        car.setBrakeStatus(true);
    });
    connect(ui->brakeButton, &QPushButton::released, this, [this]{
        car.setBrakeStatus(false);
    });

    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::quitButtonClicked);

    // M: Auto/Manual
    auto scToggleShift = new QShortcut(QKeySequence(Qt::Key_M), this);
    scToggleShift->setContext(Qt::ApplicationShortcut);
    connect(scToggleShift, &QShortcut::activated, this, [this]{
        car.toggleShiftMode();
        dashboard->refresh(car);
    });

    // A: bieg w górę (tylko manual)
    auto scUpGear = new QShortcut(QKeySequence(Qt::Key_A), this);
    scUpGear->setContext(Qt::ApplicationShortcut);
    connect(scUpGear, &QShortcut::activated, this, [this]{
        if (car.getShiftMode() == ShiftMode::Manual) car.shiftUp();
        dashboard->refresh(car);
    });

    // Z: bieg w dół (tylko manual)
    auto scDownGear = new QShortcut(QKeySequence(Qt::Key_Z), this);
    scDownGear->setContext(Qt::ApplicationShortcut);
    connect(scDownGear, &QShortcut::activated, this, [this]{
        if (car.getShiftMode() == ShiftMode::Manual) car.shiftDown();
        dashboard->refresh(car);
    });

    // Skróty zmiany trybu jazdy
    auto scModeEco    = new QShortcut(QKeySequence(Qt::Key_1), this);
    auto scModeNormal = new QShortcut(QKeySequence(Qt::Key_2), this);
    auto scModeSport  = new QShortcut(QKeySequence(Qt::Key_3), this);

    connect(scModeEco,    &QShortcut::activated, this, [this]{
        ui->modeCombo->setCurrentIndex(0); // Eco
    });

    connect(scModeNormal, &QShortcut::activated, this, [this]{
        ui->modeCombo->setCurrentIndex(1); // Normal
    });

    connect(scModeSport,  &QShortcut::activated, this, [this]{
        ui->modeCombo->setCurrentIndex(2); // Sport
    });

    // Reset button
    connect(ui->resetTripButton, &QPushButton::clicked,
            this, [this]{
                car.resetTrip();
                dashboard->refresh(car);
            });

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation,
            Qt::UniqueConnection);
    timer->start(DT * 1000); // co 20 ms
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (e->isAutoRepeat()) {
        QMainWindow::keyPressEvent(e);
        return;
    }

    if (e->key() == Qt::Key_Space) {
        car.setBrakeStatus(true);
        e->accept();
        return;
    }

    QMainWindow::keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
    if (e->isAutoRepeat()) {
        QMainWindow::keyReleaseEvent(e);
        return;
    }

    if (e->key() == Qt::Key_Space) {
        car.setBrakeStatus(false);
        e->accept();
        return;
    }

    QMainWindow::keyReleaseEvent(e);
}

void MainWindow::setStatus(QLabel* lbl, const QString& text, const QString& color)
{
    lbl->setText(text);
    lbl->setStyleSheet(QString("color: %1; font-weight: bold;").arg(color));
}


void MainWindow::updateSimulation()
{
    car.update(DT);
    dashboard->refresh(car);

    if (car.shouldShowFuelWarning()) {
        QMessageBox::warning(
            this,
            "Brak paliwa!",
            "Silnik został wyłączony z powodu braku paliwa.\n"
            "Zatankuj, aby kontynuować jazdę."
            );

        car.resetFuelWarning();
    }

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
        {car.setEngineStatus(true);
    }
    else
        car.setEngineStatus(false);
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
}
void MainWindow::quitButtonClicked(){
    QMessageBox::warning(
        this,
        "Koniec!",
        "Do widzenia!"
        );
    QApplication::quit();
}


void MainWindow::showHelpDialog()
{
    QDialog helpDialog(this);
    helpDialog.setWindowTitle("Pomoc – Sterowanie Symulatorem");
    helpDialog.setModal(true);
    helpDialog.resize(500, 460);
    helpDialog.setStyleSheet(
        "background-color: #111;"
        "color: #eee;"
        "font-family: 'Courier New';"
        "font-size: 14px;"
        "border: 2px solid #0f0;"
        );

    QLabel *info = new QLabel(&helpDialog);
    info->setText(
        "<h3 style='color:#0f0;'>🧭 Sterowanie symulatorem</h3>"
        "<p>"
        "🟢 <b>E</b> – Uruchom / wyłącz silnik<br>"
        "🔼 <b>Strzałka w górę</b> – Gaz 100%<br>"
        "🔽 <b>Strzałka w dół</b> – Gaz 0%<br>"
        "⎵ <b>Spacja</b> – Hamowanie (działa tylko gdy trzymasz)<br>"
        "🔄 <b>R</b> – Tankowanie +5 L<br>"
        "<br>"

        "🕹️ <b>Skrzynia biegów</b>:<br>"
        "🔁 <b>M</b> – Przełącz tryb: <b>Auto</b> / <b>Manual</b><br>"
        "⬆️ <b>A</b> – Bieg w górę (tylko w Manual)<br>"
        "⬇️ <b>Z</b> – Bieg w dół (tylko w Manual)<br>"
        "<span style='color:#ccc;'>Uwaga: na luzie (Gear 0) auto nie przyspiesza.</span><br>"
        "<br>"

        "⚙️ <b>Tryb spalania</b>:<br>"
        "&nbsp;&nbsp;&nbsp;① <b>1</b> – Eco<br>"
        "&nbsp;&nbsp;&nbsp;② <b>2</b> – Normal<br>"
        "&nbsp;&nbsp;&nbsp;③ <b>3</b> – Sport<br>"
        "<br>"

        "⛽ <b>Pasek paliwa</b>: kolor zmienia się przy niskim poziomie<br>"
        "&nbsp;&nbsp;&nbsp;• zielony – &gt;20%<br>"
        "&nbsp;&nbsp;&nbsp;• pomarańczowy – 10–20%<br>"
        "&nbsp;&nbsp;&nbsp;• czerwony – &lt;10%<br>"
        "<br>"

        "📊 <b>Trip Computer</b> mierzy:<br>"
        "&nbsp;&nbsp;&nbsp;• czas jazdy<br>"
        "&nbsp;&nbsp;&nbsp;• dystans<br>"
        "&nbsp;&nbsp;&nbsp;• średnią prędkość<br>"
        "&nbsp;&nbsp;&nbsp;• średnie zużycie paliwa<br>"
        "Możesz go wyzerować przyciskiem <b>Reset trip</b>."
        "</p>"
        "<hr>"
        "<p style='color:#ccc;'>Symulator aktualizuje stan co 20 ms (DT = 0.02 s).</p>"
        );

    info->setWordWrap(true);
    info->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QPushButton *closeBtn = new QPushButton("Zamknij", &helpDialog);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #0f0; color: black; font-weight: bold; "
        "padding: 6px 12px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1f1; }"
        );
    connect(closeBtn, &QPushButton::clicked, &helpDialog, &QDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(&helpDialog);
    layout->addWidget(info);
    layout->addWidget(closeBtn, 0, Qt::AlignCenter);

    helpDialog.setLayout(layout);
    helpDialog.exec();
}

void MainWindow::refuelButtonClicked()
{
    car.refuel(5.0);          // debug: +5 L
    dashboard->refresh(car);  // odśwież GUI
}

void MainWindow::modeChanged(int index)
{
    if (index == 0) {
        car.setConsumptionModel(&ecoModel_);
        ui->modeLabel->setStyleSheet("color: #00ff00; font-weight: bold; font-size: 16px;");
        ui->modeLabel->setText("Mode: Eco");
    }
    else if (index == 1) {
        car.setConsumptionModel(&normalModel_);
        ui->modeLabel->setStyleSheet("color: #00ccff; font-weight: bold; font-size: 16px;");
        ui->modeLabel->setText("Mode: Normal");
    }
    else if (index == 2) {
        car.setConsumptionModel(&sportModel_);
        ui->modeLabel->setStyleSheet("color: #ff0000; font-weight: bold; font-size: 16px;");
        ui->modeLabel->setText("Mode: Sport");
    }

    // <<< tu:
    animateModeLabel();
}

void MainWindow::animateModeLabel()
{
    if (!modeLabelEffect) return;

    // animacja "rozbłysku": z 0.2 do 1.0 opacity
    auto* anim = new QPropertyAnimation(modeLabelEffect, "opacity", this);
    anim->setDuration(250);              // 0.25 s – krótki efekt
    anim->setStartValue(0.2);            // prawie zniknięte
    anim->setEndValue(1.0);              // pełna widoczność
    anim->setEasingCurve(QEasingCurve::OutQuad);

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}


