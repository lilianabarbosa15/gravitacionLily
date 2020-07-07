#include "juego.h"
#include <QApplication>
#include <QGraphicsView>

//QGraphicsScene *escena;     //Escena que muestra los objetos animados
float dt;                   //Intervalo de tiempo entre frames
Juego *juego;
QTimer *timer;

QGraphicsScene *scene;
bool estado = false;        //El juego comienza pausado


bool EVALUACION = true; //ES EVALUACIÓN         //





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Juego w;
    w.show();
    return a.exec();
}
