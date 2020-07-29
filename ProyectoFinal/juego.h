#ifndef JUEGO_H
#define JUEGO_H


#include <QGraphicsRectItem>

#include "aliado.h"
//#include "enemigo.h"
#include "meteorito.h"
#include "plataforma.h"
#include "moneda.h"
#include "enemigo.h"

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
    //void DisminuirVidas();
    void AumentarPuntaje();

private:
    bool multijugador = false;
    int puntaje = 0;
    unsigned short int localizacion = 0;    //Historia/Juego
    int x_random;
    int duracion=3900;
    unsigned long long int contTime=0;

    QGraphicsTextItem *Score = new QGraphicsTextItem;   //Puntaje que se va llevando en el nivel
    QGraphicsTextItem *Lives1 = new QGraphicsTextItem;  //Vidas del personaje 1 en el nivel
    QGraphicsTextItem *Lives2 = new QGraphicsTextItem;  //Vidas del personaje 2 en el nivel
    QGraphicsTextItem *Time = new QGraphicsTextItem;    //Tiempo que le queda al usuario para completar el nivel

    QVector<Aliado *> jugadores = {};

    QVector<Plataforma *> plataformas = {};
    int cantidadMonedas = 0;
    int y_nE;

public:
    int puntajeNivel = 0;
    //short int vidas = 0;

    QTimer *timer;                                      //Crea el timer
    QVector<QTimer*> temporizadores = {};

    bool J_vivo[2]={true,false};
    unsigned short int J_vidas[2]={0,0};

    Meteorito *meteorito_alien;
    QVector<Meteorito *> meteoritos = {};
    Moneda *estrella;
    QVector<Moneda *> estrellas = {};

    QVector<Enemigo*> Enemigos = {};
    QVector<Meteorito*> disparosEnemigos = {};

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
