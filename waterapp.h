#ifndef WATERAPP_H
#define WATERAPP_H

#include <QMainWindow>
#include <QTimer>
#include <time.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMouseEvent>
#include "pal.h"
#include <QDialog>
#include "adjtimerdialog.h"

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

    void on_actionResetTimer_triggered();

    void on_actionAdjustTimer_triggered();

    void on_actionClickthrough_triggered();

private:
    Ui::WaterApp *ui;
    QTimer *timerUpdater;
    int timeInterval;
    time_t lastTime;
    time_t currTime;
    struct tm timeLeft;
    QSystemTrayIcon trayIcon;
    QIcon icon;
    QMenu trayMenu;
    adjTimerDialog *adjustTimerDialog;
    bool isMoving;
    QPoint pressPos;
    QAction clickThrough;
    bool movable = true;
    bool moved = false;
    Pal pal;

protected:
    void mousePressEvent(QMouseEvent *event)
    {
        if (movable)
        {
            pressPos = event->pos();
            isMoving = true;
            moved = false;
        }
    }


    void mouseReleaseEvent(QMouseEvent* event)
    {
        if (movable)
        {
            isMoving = false;
            moved = false;
        }
    }


    void mouseMoveEvent(QMouseEvent *event)
    {
        if (movable && isMoving)
        {
            QPoint diff = event->pos() - pressPos;
            this->move(window()->pos()+diff);
            moved = true;
        }
    }

};
#endif // WATERAPP_H
