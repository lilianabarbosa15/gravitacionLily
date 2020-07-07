#ifndef JUGADOR_H
#define JUGADOR_H

//#include <QGraphicsPixmapItem>
#include <QObject>

//#include <QPainter>
//#include <QKeyEvent>

#include <QGraphicsRectItem>


class Jugador: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Jugador(QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);

public slots:
    void spawn();
};

#endif // JUGADOR_H
