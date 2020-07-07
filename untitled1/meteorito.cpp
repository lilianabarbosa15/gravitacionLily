#include "meteorito.h"
#include <QTimer>
#include <QGraphicsScene>

//#include <QList>
//#include <stdlib.h>
#include "juego.h"

extern QTimer *timer;

extern Juego *juego;
extern bool estado;

#include <QDebug> //


Meteorito::Meteorito(QGraphicsItem * parent): QObject(), QGraphicsRectItem(){
    //set random posicion
    int random_number = rand() % 485; //PARA EL PRIMER NIVEL
    setPos(random_number,0);          //PRIMER NIVEL

    //Dibujar el meteorito
    setRect(0,0,15,15);


    timer = new QTimer();
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);



    velocidad_x = 0;
    velocidad_y = 0;

    aceleracion_x = 0;
    aceleracion_y = 9.8;

}

Meteorito::~Meteorito(){
    //delete timer;
}

void Meteorito::move(){

    if(estado == true){
        //move meteorito
        setPos(x(),y()+velocidad_y);
        qDebug() << "y()+velocidad_y: " << y()+velocidad_y;
        velocidad_y += aceleracion_y;
        velocidad_x += aceleracion_x;
    }
}
