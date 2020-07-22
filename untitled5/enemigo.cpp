#include "enemigo.h"

Enemigo::Enemigo(unsigned int tipo, unsigned short int tipo_b, unsigned short life, int posX, int posY, int posX_arma, int posY_arma, int pos_inicialX, int pos_inicialY, float vel, float a, float theta_disparo, int radio_bala, float vel_bala)
{
    enemigo = tipo;
    disparo = tipo_b,
    vidas = life;
    posicion_x = posicioninicial_x = posX;
    posicion_y = posicioninicial_y = posY;
    posicionX_arma = posX_arma;
    posicionY_arma = posY_arma;
    velocidad =  vel;
    aceleracion = a;
    angulo_b = theta_disparo;
    radio_b = radio_bala;
    velocidad_b = vel_bala;
    dibujarItem();
    setPos(posicion_x, posicion_y);
}

void Enemigo::dibujarItem()
{
    if(enemigo == 1)    //Naves
    {
        setBrush(Qt::black);
    }
    if(enemigo == 2)    //Aliens
    {
        setBrush(Qt::darkGreen);
        alto = 40;
        //DEPENDIENDO DEL ANGULO DE DISPARO SE ELIGE EL SPRITE
    }
    setRect(0,0,ancho,alto);
}

void Enemigo::disparar()
{
    bala = new Meteorito(disparo,radio_b,posicionX_arma,posicionY_arma,velocidad_b, angulo_b);
    disparos.push_back(bala);
    bala->setFlag(QGraphicsItem::ItemIsFocusable);
    scene()->addItem(bala);
}

void Enemigo::mover(int evento)
{
    if(enemigo == 1)
    {
        //MRU hacia abajo
    }
    else
    {
        //MRUA hacia abajo
        //posicion_y = posicioninicial_y - short( velocidad * abs(sin(theta)) * tiempo + ( Gravedad * (tiempo*tiempo) / 2.0));
        //theta-=0.09;
        //float tiempo = 0.4;
    }
}

void Enemigo::verificarMovimiento()
{
}
