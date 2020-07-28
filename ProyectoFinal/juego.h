#ifndef JUEGO_H
#define JUEGO_H


#include <QGraphicsRectItem>

#include "aliado.h"
//#include "enemigo.h"
#include "meteorito.h"
#include "plataforma.h"
#include "moneda.h"

class Juego: public QObject
{
    Q_OBJECT
public:
    Juego(QObject *parent=nullptr);
    void actualizar();

private:
    bool multijugador = false;
    int puntaje = 0;
    int puntajeNivel = 0;
    unsigned short int localizacion = 0;    //Historia/Juego
    short int vidas = 0;
    int x_random;

    QVector<Aliado *> jugadores = {};
    QVector<Plataforma *> plataformas = {};

public:
    QTimer *timer;                                      //Crea el timer
    QVector<QTimer*> temporizadores = {};

    Meteorito *meteorito_alien;
    QVector<Meteorito *> meteoritos = {};
    Moneda *estrella;
    QVector<Moneda *> estrellas = {};

    /*
    //QVector<Moneda *> monedas = {};
    QVector<Enemigo *> enemigos = {};
    */

public slots:
    void NuevosMeteoritos();
    void NuevosPuntos();

public:
    bool getModoJuego() { return multijugador; }
    QVector<Aliado *> getJugadores() { return jugadores; }
    QVector<Plataforma *> getPlataformas() { return plataformas; }
    unsigned short int getNivel();

    void CambioNivel();

};

#endif // JUEGO_H
