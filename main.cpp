#include "waterapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaterApp w;
    w.show();
    return a.exec();
}
