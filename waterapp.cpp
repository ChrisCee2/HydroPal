#include "waterapp.h"
#include "ui_waterapp.h"

WaterApp::WaterApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WaterApp)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);

    icon = QIcon(":/imgs/res/imgs/icon.png");
    idlePix = QPixmap(":/imgs/res/imgs/idle.png");
    alertPix = QPixmap(":/imgs/res/imgs/alert.png");
    trayMenu.addAction("Close", this, &WaterApp::on_actionClose_triggered);


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
    resize(164, 164);
    this->setFixedSize(this->size());

    // Time interval in seconds
    timeInterval = 10;
    timeLeft = {0};
    resetTimer();

    timerUpdater = new QTimer(this);
    connect(timerUpdater, SIGNAL(timeout()), this, SLOT(checkTimer()));
    // Timer works in milliseconds
    timerUpdater->start(1000);

    // Icon stuff
    ui->pal->setPixmap(idlePix);
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

