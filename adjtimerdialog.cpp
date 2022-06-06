#include "adjtimerdialog.h"
#include "ui_adjtimerdialog.h"

adjTimerDialog::adjTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adjTimerDialog)
{
    ui->setupUi(this);
}


adjTimerDialog::~adjTimerDialog() { delete ui; }


void adjTimerDialog::reject()
{
    qDebug() << this->parentWidget();
    this->parentWidget()->show();
    QDialog::reject();
}
