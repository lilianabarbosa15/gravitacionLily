#ifndef JUEGO_H
#define JUEGO_H


#include <QGraphicsRectItem>

#include "aliado.h"
#include "meteorito.h"
#include "plataforma.h"
#include "moneda.h"
#include "enemigo.h"
#include "bala.h"

class Juego: public QObject
{
    Q_OBJECT
private:
    void ActualizarCountdown();
    QString TimeAsSting();

public:
    Juego(QObject *parent=nullptr);
    void actualizar();
    void Trackers();
    void DisparosEnemigos();
    void DisminuirVidas();
    void AumentarPuntaje();

    void NuevosPuntos();
    void NuevosMeteoritos();

private:
    void cambiarLocalizacion();

    bool multijugador = false;
    int puntaje = 0;
    unsigned short int localizacion = 0;    //Historia/Juego
    unsigned long int contTime=0, duracion=3900;

    QGraphicsTextItem *Score = new QGraphicsTextItem;   //Puntaje que se va llevando en el nivel
    QGraphicsTextItem *Lives1 = new QGraphicsTextItem;  //Vidas del personaje 1 en el nivel
    QGraphicsTextItem *Lives2 = new QGraphicsTextItem;  //Vidas del personaje 2 en el nivel
    QGraphicsTextItem *Time = new QGraphicsTextItem;    //Tiempo que le queda al usuario para completar el nivel



    QVector<Plataforma *> plataformas = {};
    int cantidadMonedas = 1;
    int y_nE;

public:
    QVector<Aliado *> jugadores = {};
    QVector<Enemigo*> Enemigos = {};

    int puntajeNivel = 0;

    QTimer *timer;                                      //Crea el timer
    QVector<QTimer*> temporizadores = {};

    bool J_vivo[2]={true,false};

    Meteorito *meteorito_alien;
    QVector<Meteorito *> meteoritos = {};
    Moneda *estrella;
    QVector<Moneda *> estrellas = {};


    QVector<Meteorito*> disparosEnemigos = {};
    QVector<Bala*> disparosAliados = {};

public:
    bool getModoJuego() { return multijugador; }
    QVector<Plataforma *> getPlataformas() { return plataformas; }
    unsigned short int getNivel();

    void CambioNivel();

};

#endif // JUEGO_H
