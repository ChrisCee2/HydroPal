#ifndef PAL_H
#define PAL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class Pal : public QLabel
{
    Q_OBJECT

public:
    explicit Pal(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~Pal();

signals:
    void clicked();

public slots:
    void alert();
    void idle();

private:
    bool moved = false;
    QPixmap idlePix;
    QPixmap alertPix;
};

#endif // PAL_H
