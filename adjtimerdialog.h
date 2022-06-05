#ifndef ADJTIMERDIALOG_H
#define ADJTIMERDIALOG_H

#include <QDialog>

namespace Ui {
class adjTimerDialog;
}

class adjTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adjTimerDialog(QWidget *parent = nullptr);
    ~adjTimerDialog();

private:
    Ui::adjTimerDialog *ui;
};

#endif // ADJTIMERDIALOG_H
