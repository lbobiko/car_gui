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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dashboard = new Dashboard(
        ui->engineInfo,
        ui->throttleInfo,
        ui->throttleDetail,
        ui->brakeInfo,
        ui->speedInfo,
        ui->distanceInfo
        );

    // pierwsze odświeżenie, żeby UI nie było puste
    dashboard->refresh(car);

    // żeby okno łapało klawisze
    this->setFocusPolicy(Qt::StrongFocus);

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

    ui->engineInfo->setText("Engine OFF");
    ui->engineInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->throttleInfo->setText("Throttle");
    ui->throttleInfo->setStyleSheet("color: red; font-weight: bold;");
    ui->brakeInfo->setText("Brake OFF");
    ui->brakeInfo->setStyleSheet("color: red; font-weight: bold;");
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpDialog);
    //refreshUI();

    // startButton to objectName przycisku w .ui
    connect(ui->engineButton, &QPushButton::clicked, this, &MainWindow::engineButtonClicked);
    connect(ui->throttleButton, &QPushButton::clicked, this, &MainWindow::throttleButtonClicked);
    //connect(ui->brakeButton, &QPushButton::clicked, this, &MainWindow::brakeButtonClicked);
    connect(ui->brakeButton, &QPushButton::pressed,  this, [this]{
        car.setBrakeStatus(true);
    });

    connect(ui->brakeButton, &QPushButton::released, this, [this]{
        car.setBrakeStatus(false);
    });
    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::quitButtonClicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation,
            Qt::UniqueConnection);
    timer->start(DT * 1000); // czyli co 20 ms
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (e->isAutoRepeat()) { QMainWindow::keyPressEvent(e);
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
    if (e->isAutoRepeat()) { QMainWindow::keyReleaseEvent(e);
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
        //refreshUI();
    }
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
void MainWindow::quitButtonClicked(){
    QMessageBox::warning(
        this,
        "Koniec!",
        "Do widzenia!"
        );
    QApplication::quit();
}

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

void MainWindow::showHelpDialog()
{
    // okno dialogowe
    QDialog helpDialog(this);
    helpDialog.setWindowTitle("Pomoc – Sterowanie Symulatorem");
    helpDialog.setModal(true);
    helpDialog.resize(400, 320);
    helpDialog.setStyleSheet(
        "background-color: #111;"
        "color: #eee;"
        "font-family: 'Courier New';"
        "font-size: 14px;"
        "border: 2px solid #0f0;"
        );

    //  etykieta  HTML
    QLabel *info = new QLabel(&helpDialog);
    info->setText(
        "<h3 style='color:#0f0;'>🧭 Sterowanie symulatorem</h3>"
        "<p>"
        "🟢 <b>E</b> – Uruchom / wyłącz silnik<br>"
        "🔼 <b>Strzałka w górę</b> – Dodaj gazu<br>"
        "🔽 <b>Strzałka w dół</b> – Odejmij gazu<br>"
        "⎵ <b>Spacja</b> – Hamulec<br>"
        "⏻ <b>Q</b> – Zakończ program<br>"
        "❓ <b>F1</b> – Pokaż pomoc"
        "</p>"
        "<hr>"
        "<p style='color:#ccc;'>Wskazówka: Możesz używać myszki lub klawiatury.<br>"
        "Symulator aktualizuje stan co 20 ms (DT = 0.02 s).</p>"
        );
    info->setWordWrap(true);
    info->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Przycisk zamknięcia
    QPushButton *closeBtn = new QPushButton("Zamknij", &helpDialog);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #0f0; color: black; font-weight: bold; "
        "padding: 6px 12px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #1f1; }"
        );
    connect(closeBtn, &QPushButton::clicked, &helpDialog, &QDialog::accept);

    // Układ
    QVBoxLayout *layout = new QVBoxLayout(&helpDialog);
    layout->addWidget(info);
    layout->addWidget(closeBtn, 0, Qt::AlignCenter);

    helpDialog.setLayout(layout);
    helpDialog.exec();
}
