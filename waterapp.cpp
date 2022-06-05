#include "waterapp.h"
#include "ui_waterapp.h"

WaterApp::WaterApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WaterApp)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);
    // Hide title bar
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    icon = QIcon(":/imgs/res/imgs/icon.png");
    idlePix = QPixmap(":/imgs/res/imgs/idle.png");
    alertPix = QPixmap(":/imgs/res/imgs/alert.png");
    trayMenu.addAction("Adjust Water Timer", this, SLOT(on_actionAdjustTimer_triggered()));
    trayMenu.addAction("Consume Water", this, SLOT(on_actionResetTimer_triggered()));
    clickThrough.setCheckable(true);
    clickThrough.setText("Clickthrough");
    connect(&clickThrough, SIGNAL(triggered()), this, SLOT(on_actionClickthrough_triggered()));
    trayMenu.addAction(&clickThrough);
    trayMenu.addAction("Close", this, SLOT(on_actionClose_triggered()));


    // Store in system tray
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        // Store into tray
        trayIcon.setIcon(icon);
        trayIcon.show();
        trayIcon.setContextMenu(&trayMenu);
        trayIcon.setToolTip("HydroPal");
    }

    // Decorate window stuff
    resize(minimumSizeHint());
    this->setFixedSize(this->size());
    this->adjustSize();
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->timer->setStyleSheet("QLabel {color: white;}");

    // Time interval in seconds
    timeInterval = 10;
    timeLeft = {0};
    resetTimer();

    timerUpdater = new QTimer(this);
    connect(timerUpdater, SIGNAL(timeout()), this, SLOT(checkTimer()));
    // Timer works in milliseconds
    timerUpdater->start(1000);

    // Pal pic stuff
    ui->pal->setPixmap(idlePix);
    ui->pal->resize(idlePix.size());
}

WaterApp::~WaterApp()
{
    delete ui;
}


void WaterApp::on_resetTimer_released()
{
    timerUpdater->stop();
    resetTimer();
    timerUpdater->start(1000);
}


void WaterApp::alert()
{
    // Display alert image / animation
    ui->pal->setPixmap(alertPix);
    ui->pal->resize(alertPix.size());
}


void WaterApp::setTimeLeft(int s)
{
    timeLeft.tm_hour = (timeInterval - s) / 3600;
    timeLeft.tm_min = ((timeInterval - s) - (timeLeft.tm_hour * 3600)) / 60;
    timeLeft.tm_sec = (timeInterval - s) - ((timeLeft.tm_hour * 3600) + (timeLeft.tm_min * 60));
}


QString WaterApp::timeLeftToQString()
{
    QString hour = (timeLeft.tm_hour > 9) ? QString::number(timeLeft.tm_hour) : "0" + QString::number(timeLeft.tm_hour);
    QString min = (timeLeft.tm_min > 9) ? QString::number(timeLeft.tm_min) : "0" + QString::number(timeLeft.tm_min);
    QString sec = (timeLeft.tm_sec > 9) ? QString::number(timeLeft.tm_sec) : "0" + QString::number(timeLeft.tm_sec);
    return hour + ":" + min + ":" + sec;
}


void WaterApp::resetTimer()
{
    time(&lastTime);
    time(&currTime);
    setTimeLeft(difftime(currTime, lastTime));
    ui->timer->setText(timeLeftToQString());

    // Reset icon
    ui->pal->setPixmap(idlePix);
    ui->pal->resize(idlePix.size());
}


void WaterApp::updateTimer()
{
    time(&currTime);
    setTimeLeft(difftime(currTime, lastTime));
    ui->timer->setText(timeLeftToQString());
}


void WaterApp::checkTimer()
{
    if (timeLeft.tm_hour <= 0 && timeLeft.tm_min <= 0 && timeLeft.tm_sec <= 0)
    {
        stopTimer();
        alert();
    }
    else
    {
        updateTimer();
    }
}


void WaterApp::stopTimer()
{
    timerUpdater->stop();
}

void WaterApp::on_actionClose_triggered()
{
    QApplication::quit();
}


void WaterApp::on_actionResetTimer_triggered()
{
    timerUpdater->stop();
    resetTimer();
    timerUpdater->start(1000);
}


void WaterApp::on_actionAdjustTimer_triggered()
{
    hide();
    adjTimerDialog = new QDialog(this);
    adjTimerDialog->show();
}

void WaterApp::on_actionClickthrough_triggered()
{
    this->setWindowFlag(Qt::WindowTransparentForInput, clickThrough.isChecked());
//    ui->resetTimer->setAttribute(Qt::WA_TransparentForMouseEvents, clickThrough.isChecked());
//    movable = !clickThrough.isChecked();
}

