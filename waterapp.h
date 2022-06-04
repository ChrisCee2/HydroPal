#ifndef WATERAPP_H
#define WATERAPP_H

#include <QMainWindow>
#include <QTimer>
#include <time.h>
#include <QSystemTrayIcon>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class WaterApp; }
QT_END_NAMESPACE

class WaterApp : public QMainWindow
{
    Q_OBJECT

public:
    WaterApp(QWidget *parent = nullptr);
    ~WaterApp();

private slots:
    void on_resetTimer_released();
    void checkTimer();
    void updateTimer();
    void stopTimer();
    void resetTimer();
    void setTimeLeft(int s);
    QString timeLeftToQString();
    void alert();

    void on_actionClose_triggered();

private:
    Ui::WaterApp *ui;
    QTimer *timerUpdater;
    int timeInterval;
    time_t lastTime;
    time_t currTime;
    struct tm timeLeft;
    QSystemTrayIcon trayIcon;
    QPixmap idlePix;
    QPixmap alertPix;
    QIcon icon;
    QMenu trayMenu;

};
#endif // WATERAPP_H
