#ifndef ALIADO_H
#define ALIADO_H


#include <QGraphicsRectItem>
//#include <QKeyEvent>
#include <QTimer>
#include "cuerpo.h"
#include "meteorito.h"

#define Gravedad 9.8
#define Pi 3.14159

class Aliado: public QGraphicsRectItem, public cuerpo
{
public:
    Aliado(int x, int life);
    void dibujarItem() override;

    void mover(int evento) override;
    void disparar() override;
    void saltar();
    void moverArma(float posibleangulo, int direccion);
    void actualizarDisparos();
    void verificarMovimiento() override;

public:
    bool saltando = false;
    unsigned short int vidas;
    QVector<Meteorito*> balas_lanzadas = {};

private:
    unsigned short int jugador;
    int ancho = 25, alto = 40;
    int posicion_x = 0;
    int posicion_y = 360;
    int posicioninicial_x = 0;
    int posicioninicial_y = 360;
    float Vy, velocidad = 2600;
    float V = 2600;             //Si se cambia el valor de velocidad, éste valor también debe ser cambiado
    float tiempo = 0.4;
    float theta = Pi/180.0;

    float angulo_disparo = 90.0*(Pi/180.0);
    int posicionx_bala = posicion_x+(ancho/2);
    int posiciony_bala = posicion_y;
    int posicion_arma [7][2] = {};  //Posiciones de izquierda a derecha
    int indica_posicion_arma = 3;

    Meteorito *bala;

    bool colision = false;
    int posY_barra;
};


#endif // ALIADO_H
