#ifndef METEORITO_H
#define METEORITO_H

//#include <QGraphicsPixmapItem>
#include <QObject>

#include <QGraphicsRectItem>

class Meteorito: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Meteorito(QGraphicsItem * parent=0);
    ~Meteorito();

public slots:
    void move();
    //void acelerar(float px2_, float py2_);
    //void actualizar(float dt);

private:
    //QTimer * timer = new QTimer();
    float velocidad_x, velocidad_y;
    float aceleracion_x, aceleracion_y;
};

#endif // METEORITO_H
