#include "pal.h"

Pal::Pal(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    idlePix = QPixmap(":/imgs/res/imgs/idle.png");
    alertPix = QPixmap(":/imgs/res/imgs/alert.png");
    setPixmap(idlePix);
}

Pal::~Pal() {}


void Pal::idle() { setPixmap(idlePix);}


void Pal::alert() { setPixmap(alertPix);}
