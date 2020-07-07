#include "jugador.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "meteorito.h"

extern bool estado;

extern bool EVALUACION; //


#include <QDebug> //

Jugador::Jugador(QGraphicsItem *parent): QObject(), QGraphicsRectItem() {
    setRect(0,0,25,40);
}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    if(estado == true){
        if (event->key() == Qt::Key_Left){
            if(pos().x() > 0)
            setPos(x()-10,y());
        }
        else if (event->key() == Qt::Key_Right){
            if(pos().x() + 30 < 580)
            setPos(x()+10,y());
        }
    }
}

void Jugador::spawn()
{
    if(EVALUACION == true){             //
    //create enemies
    qDebug() << "Jugador::spawn()";
    Meteorito *meteorito = new Meteorito();
    scene()->addItem(meteorito);


    //qDebug() << "POSICIÓN X DE METEORITO:              " << meteorito->x();

    //EVALUACION = false;                 //
    }                                   //
}



