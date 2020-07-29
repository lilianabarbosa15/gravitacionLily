#ifndef ALIADO_H
#define ALIADO_H


#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include "cuerpo.h"
#include "bala.h"
#include "meteorito.h"

#define Gravedad 9.8
#define Pi 3.14159
#define paso 10
#define V 2600


class Aliado: public cuerpo, public QGraphicsPixmapItem
{
public:
    Aliado(int x);
    void dibujarItem() override;

    void calcularmovimiento(int evento);
    void moverX(int evento);
    void moverY(unsigned short int tipo=1); //Predeterminadamente salta //SOLO SE USA EN EL NIVEL 1
    void actualizarcoordenadas(int posY_barra);
    void moverArma(float posibleangulo, int direccion);
    void actualizarDisparos();
    void disparar() override;

    void verificarMovimiento() override;
    void verificarChoques(unsigned short int tipo=1);

public:
    bool saltando = false, colision_barra = false;
    int posinicialY_barra = 400, posinicialX_barra = 0;

    //unsigned short int vidas_jugador = 0; // puntos = 0;
    bool next_nivel = false;
    bool vivo = true;
    QVector<Bala*> balas_lanzadas = {};

private:
    unsigned short int jugador;
    short int ancho = 25, alto = 40;
    int posicion_x = 0, posicion_y = 360;
    int posicioninicial_x = 0, posicioninicial_y = 360;
    float Vy, velocidad = V;

    float tiempo = 0.4;
    float theta = Pi/180.0;
    float angulo_disparo = 90.0*(Pi/180.0);
    int posicionx_bala = posicion_x+(ancho/2);
    int posiciony_bala = posicion_y;
    int posicion_arma [7][2] = {};  //Posiciones de izquierda a derecha
    int indica_posicion_arma = 3;
    Bala *bala;

    unsigned int barra=0;
    unsigned short int friccion = 0;

    short int pixX = 0, pixY = 0;
    QPixmap aparienciaR, aparienciaL;
    //QPixmap aparienciaS;

};


#endif // ALIADO_H
