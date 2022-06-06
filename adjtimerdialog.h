#ifndef ADJTIMERDIALOG_H
#define ADJTIMERDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class adjTimerDialog;
}

class adjTimerDialog : public QDialog
{
    Q_OBJECT

public:
    adjTimerDialog(QWidget *parent = nullptr);
    ~adjTimerDialog();

private:
    Ui::adjTimerDialog *ui;

protected:
    void reject();
};

#endif // ADJTIMERDIALOG_H
