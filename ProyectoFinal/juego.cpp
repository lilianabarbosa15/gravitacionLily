#include "juego.h"
#include <QDebug> //

extern QGraphicsScene *escena;

#include <escritor.h>
extern infoArchivo infoUsuario;

extern Juego *juego;

Juego::Juego(QObject *parent): QObject{parent}
{
    if(infoUsuario.string1=="<M>")
        multijugador=true;
    else
        multijugador=false;
    puntaje = infoUsuario.int1;
    localizacion = infoUsuario.int2;

    if(localizacion==1){
        estrella = new Moneda(0,15,10,530,60,0.2);
        estrellas.push_back(estrella);
        escena->addItem(estrella);

        escena->setBackgroundBrush(QBrush(QImage(":/primera/Spaceport_.jpg").scaled(680,400)));
        vidas = 5;
        plataformas.push_back(new Plataforma(680,1,0,400,0,0,0,0,0));         //PLATAFORMA DEL SUELO QUE NO SE VE
        escena->addItem(plataformas.back());
        plataformas.push_back(new Plataforma(80,10,60,335,0,-0.5,320,7,0));  //PLATAFORMA QUE SE MUEVE CONSTANTEMENTE
        plataformas.at(1)->setFlag(QGraphicsItem::ItemIsFocusable);
        escena->addItem(plataformas.back());
        for(unsigned int n=210; n<=510; n+=150){
            plataformas.push_back(new Plataforma(80,10,n,335,0,0,0,5,0));
            escena->addItem(plataformas.back());
            plataformas.push_back(new Plataforma(90,10,n-25,180,0,0,0,5,0));
            escena->addItem(plataformas.back());
        }
    }else if(localizacion==3){
        escena->setBackgroundBrush(QBrush(QImage(":/segunda/Space.png").scaled(680,400)));
        vidas = 5;
    }else if(localizacion==5){
        escena->setBackgroundBrush(QBrush(QImage(":/tercera/Newplanet.jpg").scaled(680,400)));
        vidas = 5;
    }

    if(localizacion%2==1){       //AÑADE PERSONAJES A LA ESCENA
        jugadores.push_back(new Aliado(localizacion, vidas));
        if(multijugador == true)
            jugadores.push_back(new Aliado(localizacion+1, vidas));
        for(short int u=0; u<jugadores.size(); u++){
            escena->addItem(jugadores.at(u));
            jugadores.at(u)->setFlag(QGraphicsItem::ItemIsFocusable);
        }
    }
}

void Juego::actualizar()
{
    if(localizacion==1) //NIVEL1
    {
        for(unsigned int n=0; n<(unsigned)estrellas.size(); n++)
            estrellas.at(n)->Mover();
        for(unsigned short int u=0; u<(unsigned)meteoritos.size(); u++){
            if(meteoritos.at(u)->getPosicionY()<=400){
                meteoritos.at(u)->ActualizarVelocidad();
                meteoritos.at(u)->ActualizarPosicion();
            }else{
                meteoritos.at(u)->Desaparecer();
                meteoritos.remove(u);
            }
        }
        for(int i=0; i<plataformas.size();i++)
            plataformas.at(i)->Mover();
        for(unsigned short int u=0; u<(unsigned)jugadores.size(); u++){
            jugadores.at(u)->verificarChoques(2);   //¿Choca con un meteorito?
            if(jugadores.at(u)->posinicialX_barra==60)     //¿Sobre plataforma en movimiento?
                jugadores.at(u)->actualizarcoordenadas(plataformas.at(1)->getPosY());
            if(jugadores.at(u)->saltando == true)
                jugadores.at(u)->moverY();  //Salta
            else if(jugadores.at(u)->colision_barra==false)
                jugadores.at(u)->moverY(0); //Cae
        }
    }
    else if(localizacion == 3 || localizacion==5)   //NIVEL2 O NIVEL3
    {
        //DISPAROS DEL PERSONAJE
        for(unsigned short int u=0; u<(unsigned)jugadores.size(); u++)
            jugadores.at(u)->actualizarDisparos();
    }
}

void Juego::NuevosMeteoritos()
{
    x_random = rand() % 680 + 10;
    meteorito_alien = new Meteorito(0,9,x_random,0,20);
    meteoritos.push_back(meteorito_alien);
    escena->addItem(meteorito_alien);
}

void Juego::NuevosPuntos()
{
    x_random = rand() % 650 + 10;
    estrella = new Moneda(20,9.2,3.5,x_random,370,0.1);
    estrellas.push_back(estrella);
    escena->addItem(estrella);
}

unsigned short Juego::getNivel()
{
    if(localizacion==1) //Significa que se encuentra en el nivel 1
        return localizacion;
    else if(localizacion==3) //Significa que se encuentra en el nivel 2
        return localizacion-1;
    else if(localizacion==5) //Significa que se encuentra en el nivel 3
        return localizacion-2;
    else
        return 100; //No se encuentra en ningun nivel
}

void Juego::CambioNivel()
{
    if(localizacion<6)
        juego->localizacion +=1;
    else if(localizacion==6)
        juego->localizacion = 0;
}
