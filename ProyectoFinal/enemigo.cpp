#include "enemigo.h"
#include "juego.h"
#include <QDebug>

extern Juego *juego;

Enemigo::Enemigo(unsigned int tipo, unsigned short int tipo_b, unsigned short life, int posX, int posY, int posX_arma, int posY_arma, int pos_inicialX, int pos_inicialY, float vel, float a, float theta_disparo, int radio_bala, float vel_bala)
{
    enemigo = tipo;
    disparo = tipo_b;
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
    if(enemigo==1)    //Naves
    {
        apariencia = QPixmap(":/Enemigo/SpaceshipE.png").scaled(ancho,alto);
        //setBrush(Qt::blue);
    }
    else if(enemigo==2)    //Aliens DEPENDIENDO DEL ANGULO DE DISPARO SE ELIGE EL SPRITE
    {
        //apariencia = QPixmap("");
        //setBrush(Qt::green);
        alto = 40;
    }
    setPixmap(apariencia.copy(posX,posY,ancho,alto));
    //setRect(0,0,ancho,alto);
}

void Enemigo::disparar()
{
    if(enemigo==1)
        bala = new Meteorito(2,radio_b,posicionX_arma,posicionY_arma,velocidad_b, angulo_b);
    else if(enemigo==2)
        bala = new Meteorito(3, radio_b,posicionX_arma,posicionY_arma,velocidad_b, angulo_b);

    juego->disparosEnemigos.push_back(bala);
    bala->setA(15);
    bala->setFlag(QGraphicsItem::ItemIsFocusable);
    scene()->items().push_back(bala);
    scene()->addItem(bala);
}


void Enemigo::verificarMovimiento()
{
    if(vidas>0){
        ColisionBala();
    }
    else{
        scene()->removeItem(this);
    }
}

bool Enemigo::ActualizarPosicion()
{
    if(posicion_y<400){
        posicion_y+=velocidad+(aceleracion/2);
        posicionY_arma=posicion_y+alto;
        setPos(posicion_x,posicion_y);
        return false;
    }
    else return true;
}

void Enemigo::ColisionBala()
{
    QList<QGraphicsItem*>Colision=collidingItems();
    for(int i=0; i<Colision.size();i++){
        if(typeid(*Colision.at(i))==typeid(Bala)){
            if(vidas==0){
                Colision.removeAt(i);
                this->hide();
            }
            else
                vidas--;
            qDebug()<<"Colision con enemigo"<< ".....VIDAS: " << vidas << endl;
        }
    }

}

bool Enemigo::IsColliding()
{
    if(vidas>0){
        ColisionBala();
    }
    else{
        //puntajeNivel+=100;
        scene()->removeItem(this);
        return true;
    }
    return false;

}

int Enemigo::getPosicion_x() const
{
    return posicion_x;
}

int Enemigo::getPosicion_y() const
{
    return posicion_y;
}
