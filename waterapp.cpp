#include "waterapp.h"
#include "ui_waterapp.h"

WaterApp::WaterApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WaterApp)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);

    // Decorate window stuff
    resize(200, 200);

    // Time interval in seconds
    timeInterval = 3600;
    timeLeft = {0};
    resetTimer();

    timerUpdater = new QTimer(this);
    connect(timerUpdater, SIGNAL(timeout()), this, SLOT(updateTimer()));
    // Timer works in milliseconds
    timerUpdater->start(1000);
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

}


void WaterApp::setTimeLeft(int s)
{
    timeLeft.tm_hour = s / 3600;
    timeLeft.tm_min = (s - (timeLeft.tm_hour * 3600)) / 60;
    timeLeft.tm_sec = s - ((s - (timeLeft.tm_hour * 3600)) + (s - (timeLeft.tm_min * 60)));
}


QString WaterApp::timeLeftToQString()
{
    QString tLeft(QString::number(timeLeft.tm_hour) + ":" + QString::number(timeLeft.tm_min) + ":" + QString::number(timeLeft.tm_sec));
    return tLeft;
}


void WaterApp::resetTimer()
{
    time(&lastTime);
    time(&currTime);
    setTimeLeft(difftime(lastTime, currTime));
    ui->timer->setText(timeLeftToQString());
}


void WaterApp::updateTimer()
{
    time(&currTime);
    setTimeLeft(difftime(lastTime, currTime));
    ui->timer->setText(timeLeftToQString());
}
