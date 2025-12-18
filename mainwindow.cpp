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
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>

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
        ui->shiftModeInfo,
        ui->absCheckBox,
        ui->tcsCheckBox,
        ui->surfaceCombo,
        ui->absStatusInfo,
        ui->tcsStatusInfo,
        ui->gradeInfo

        );


    ui->absCheckBox->setChecked(true);
    ui->tcsCheckBox->setChecked(true);
    ui->surfaceCombo->setCurrentIndex(0); // Dry

    // pierwsze odświeżenie, żeby UI nie było puste
    dashboard->refresh(car);

    // żeby okno łapało klawisze
    this->setFocusPolicy(Qt::StrongFocus);

    // ABS
    connect(ui->absCheckBox, &QCheckBox::toggled, this, [this](bool on){
        car.setAbsEnabled(on);
    });

    connect(ui->tcsCheckBox, &QCheckBox::toggled, this, [this](bool on){
        car.setTcsEnabled(on);
    });

    connect(ui->surfaceCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int idx){
                car.setSurfacePreset(idx);   // 0..3
            });
    car.setAbsEnabled(ui->absCheckBox->isChecked());
    car.setTcsEnabled(ui->tcsCheckBox->isChecked());
    car.setSurfacePreset(ui->surfaceCombo->currentIndex());

    // nachylenie - etap 6
    auto scGradeDown = new QShortcut(QKeySequence(Qt::Key_BracketLeft), this);   // [
    auto scGradeUp   = new QShortcut(QKeySequence(Qt::Key_BracketRight), this);  // ]

    scGradeDown->setContext(Qt::ApplicationShortcut);
    scGradeUp->setContext(Qt::ApplicationShortcut);

    connect(scGradeDown, &QShortcut::activated, this, [this]{
        car.setGradePercent(car.gradePercent() - 1.0);
        dashboard->refresh(car);
    });

    connect(scGradeUp, &QShortcut::activated, this, [this]{
        car.setGradePercent(car.gradePercent() + 1.0);
        dashboard->refresh(car);
    });

    // P: pauza / wznowienie
    auto scPause = new QShortcut(QKeySequence(Qt::Key_P), this);
    scPause->setContext(Qt::ApplicationShortcut);
    connect(scPause, &QShortcut::activated, this, [this]{
        paused_ = !paused_;
        if (paused_) {
            timer->stop();
            ui->pauseInfo->setText("PAUSED!");}
        else         {
            timer->start(DT * 1000);
            ui->pauseInfo->setText("");}

        ui->pauseInfo->setAlignment(Qt::AlignCenter);
        ui->pauseInfo->setStyleSheet(
            "font-size: 28px;"
            "font-weight: bold;"
            "color: orange;"
            );
    });
    // RESET
    auto scReset = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    scReset->setContext(Qt::ApplicationShortcut);
    connect(scReset, &QShortcut::activated, this, [this]{
        paused_ = false;
        timer->start(DT * 1000);

        car.resetAll();

        // reset ustawień GUI
        ui->absCheckBox->setChecked(true);
        ui->tcsCheckBox->setChecked(true);
        ui->surfaceCombo->setCurrentIndex(0);
        ui->modeCombo->setCurrentIndex(1);

        car.setAbsEnabled(ui->absCheckBox->isChecked());
        car.setTcsEnabled(ui->tcsCheckBox->isChecked());
        car.setSurfacePreset(ui->surfaceCombo->currentIndex());

        dashboard->refresh(car);
    });

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

    // strzałki - sterowanie throttle
    auto keyUp   = new QShortcut(QKeySequence(Qt::Key_Up), this);
    auto keyDown = new QShortcut(QKeySequence(Qt::Key_Down), this);
    connect(keyUp,   &QShortcut::activated, this, [this]{ car.setThrottle(1.0); });
    connect(keyDown, &QShortcut::activated, this, [this]{ car.setThrottle(0.0); });
    auto scThrottleUp = new QShortcut(QKeySequence(Qt::Key_W), this);
    auto scThrottleDn = new QShortcut(QKeySequence(Qt::Key_S), this);
    scThrottleUp->setContext(Qt::ApplicationShortcut);
    scThrottleDn->setContext(Qt::ApplicationShortcut);

    connect(scThrottleUp, &QShortcut::activated, this, [this]{
        car.setThrottle(car.getThrottle() + 0.1);   // +10%
        dashboard->refresh(car);
    });

    connect(scThrottleDn, &QShortcut::activated, this, [this]{
        car.setThrottle(car.getThrottle() - 0.1);   // -10%
        dashboard->refresh(car);
    });

    // Klawisz q
    auto keyQuit = new QShortcut(QKeySequence(Qt::Key_Q), this);
    keyQuit->setContext(Qt::ApplicationShortcut);
    connect(keyQuit, &QShortcut::activated, this, &MainWindow::quitButtonClicked);

    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpDialog);
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

    // Surface presets (Etap 6)
    // 4..7: wybór nawierzchni (index jak w setSurfacePreset)
    auto scSurf0 = new QShortcut(QKeySequence(Qt::Key_4), this);
    auto scSurf1 = new QShortcut(QKeySequence(Qt::Key_5), this);
    auto scSurf2 = new QShortcut(QKeySequence(Qt::Key_6), this);
    auto scSurf3 = new QShortcut(QKeySequence(Qt::Key_7), this);

    scSurf0->setContext(Qt::ApplicationShortcut);
    scSurf1->setContext(Qt::ApplicationShortcut);
    scSurf2->setContext(Qt::ApplicationShortcut);
    scSurf3->setContext(Qt::ApplicationShortcut);

    auto setSurfaceIdx = [this](int idx){
        car.setSurfacePreset(idx);
        if (ui->surfaceCombo) {
            QSignalBlocker b(ui->surfaceCombo);
            ui->surfaceCombo->setCurrentIndex(idx);
        }
        dashboard->refresh(car);
    };

    connect(scSurf0, &QShortcut::activated, this, [=]{ setSurfaceIdx(0); }); // Asphalt Dry
    connect(scSurf1, &QShortcut::activated, this, [=]{ setSurfaceIdx(1); }); // Asphalt Wet
    connect(scSurf2, &QShortcut::activated, this, [=]{ setSurfaceIdx(2); }); // Gravel
    connect(scSurf3, &QShortcut::activated, this, [=]{ setSurfaceIdx(3); }); // Ice

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
    helpDialog.setWindowTitle("Pomoc – Sterowanie symulatorem");
    helpDialog.setModal(true);

    helpDialog.resize(800, 520);

    // ===== Tytuł =====
    QLabel *title = new QLabel("Sterowanie symulatorem");
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 4);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // ===== Treść =====
    QLabel *content = new QLabel;
    content->setText(R"(
<b>Podstawowe sterowanie</b><br>
• <b>E</b> – uruchom / wyłącz silnik (blokada wyłączenia w trakcie jazdy)<br>
• <b>Strzałka ↑</b> – gaz 100%<br>
• <b>Strzałka ↓</b> – gaz 0%<br>
• <b>W / S</b> – zwiększ / zmniejsz gaz o +/- 10%<br>
• <b>Spacja</b> – hamowanie (działa tylko gdy trzymasz)<br>
• <b>R</b> – tankowanie +5 L<br>
• <b>Q</b> – wyjście z programu<br>
• <b>P</b> – pauza<br>
• <b>Backspace</b> – reset do ustawień początkowych<br>
<br>

<b>Skrzynia biegów</b><br>
• <b>M</b> – przełącz tryb Auto / Manual<br>
• <b>A</b> – bieg w górę (tylko Manual)<br>
• <b>Z</b> – bieg w dół (tylko Manual)<br>
Uwaga: na luzie (Gear 0) auto nie przyspiesza.<br>
<br>

<b>Tryb spalania</b><br>
• <b>1</b> – Eco<br>
• <b>2</b> – Normal<br>
• <b>3</b> – Sport<br>
<br>

<b>Etap 5 – ABS / TCS</b><br>
• Checkbox <b>ABS</b> – włącza / wyłącza system ABS<br>
• Checkbox <b>TCS</b> – włącza / wyłącza kontrolę trakcji<br>
• Kontrolki <b>ABS ACTIVE</b> i <b>TCS ACTIVE</b> zapalają się tylko, gdy system faktycznie zadziała<br>
<br>

<b>Nawierzchnia (Strategy)</b><br>
• <b>4</b> – Asphalt (Dry)<br>
• <b>5</b> – Asphalt (Wet)<br>
• <b>6</b> – Gravel<br>
• <b>7</b> – Ice<br>
Aktualna nawierzchnia wpływa na maksymalną siłę hamowania i trakcję.<br>
<br>

<b>Etap 6 – Nachylenie terenu</b><br>
• <b>[</b> – zmniejsz nachylenie (bardziej z górki)<br>
• <b>]</b> – zwiększ nachylenie (bardziej pod górę)<br>
• Aktualne nachylenie wyświetlane jest w GUI jako <b>Grade: …%</b><br>
<br>

<b>Trip Computer</b><br>
• mierzy czas jazdy, dystans, średnią prędkość i spalanie<br>
• reset danych: przycisk <b>Reset trip</b><br>
<br>

Symulacja aktualizowana co 20 ms (DT = 0.02 s).
)");
    content->setWordWrap(true);
    content->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // ===== Scroll =====
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->addWidget(content);
    scrollLayout->addStretch();
    scrollWidget->setLayout(scrollLayout);

    scroll->setWidget(scrollWidget);

    // ===== Przycisk =====
    QPushButton *closeBtn = new QPushButton("Zamknij");
    connect(closeBtn, &QPushButton::clicked, &helpDialog, &QDialog::accept);

    // ===== Layout główny =====
    QVBoxLayout *layout = new QVBoxLayout(&helpDialog);
    layout->addWidget(title);
    layout->addWidget(scroll, 1);
    layout->addWidget(closeBtn, 0, Qt::AlignRight);

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


