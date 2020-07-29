#include "juego.h"
#include <QDebug> //

extern QGraphicsScene *escena;
extern Juego *juego;

#include <escritor.h>
extern infoArchivo infoUsuario;

void Juego::ActualizarCountdown()
{
    Time->setPlainText(QString("Time: ")+TimeAsSting());
}

QString Juego::TimeAsSting()
{
    int minutos=0, segundos=0;
    minutos=((duracion-contTime)/65)/60;
    segundos=((duracion-contTime)/65)%60;
    if(segundos>9)
        return QString(QString::number(minutos)+":"+QString(QString::number(segundos)));
    else
         return QString(QString::number(minutos)+":0"+QString(QString::number(segundos)));
}

Juego::Juego(QObject *parent): QObject{parent}
{
    if(infoUsuario.string1=="<M>"){
        multijugador=true;
        J_vidas[1] = J_vidas[0] = 5;
    }else{
        multijugador=false;
        J_vidas[0] = 5;
    }
    puntaje = infoUsuario.int1;
    localizacion = infoUsuario.int2;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(localizacion==1)     //............................NIVEL 1
    {
        estrella = new Moneda(0,15,10,530,60,0.2);
        estrellas.push_back(estrella);
        escena->addItem(estrella);

        escena->setBackgroundBrush(QBrush(QImage(":/primera/Spaceport_.jpg").scaled(680,400)));

        if(multijugador==true){
            J_vivo[1]=true;
        }

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
    }else if(localizacion==3)   //............................NIVEL 2
    {
        escena->setBackgroundBrush(QBrush(QImage(":/segunda/Space.jpg").scaled(680,400)));
        y_nE = 10;
        if(multijugador==true){
            cantidadMonedas = 60;
            J_vivo[1]=true;
        }else
            cantidadMonedas = 30;
        for(unsigned int c=100; c<501; c+=100){ //Se crean los enemigos
            Enemigos.push_back( new Enemigo(1,2,3,c,y_nE,c+30,60,0,0,0,0,0,10,0));
            escena->addItem(Enemigos.back());
            qDebug() << "Nuevo personaje";
        }

    }else if(localizacion==5)   //............................NIVEL 3
    {
        escena->setBackgroundBrush(QBrush(QImage(":/tercera/Newplanet.jpg").scaled(680,400)));
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(localizacion%2==1){                                  //AÑADE PERSONAJES A LA ESCENA
        jugadores.push_back(new Aliado(localizacion));
        if(multijugador == true)
            jugadores.push_back(new Aliado(localizacion+1));
        for(short int u=0; u<jugadores.size(); u++){
            escena->addItem(jugadores.at(u));
            jugadores.at(u)->setFlag(QGraphicsItem::ItemIsFocusable);
        }
        Trackers();
    }
}

void Juego::actualizar()
{
    for(unsigned short int o=0; o<(unsigned)jugadores.size(); o++)
        jugadores.at(o)->verificarChoques(2);   //¿Choca con un meteorito?

    AumentarPuntaje();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(localizacion==1) //............................NIVEL 1
    {
        for(unsigned int n=0; n<(unsigned)estrellas.size(); n++){
            estrellas.at(n)->Mover();
            estrellas.at(n)->AumentarPuntaje();
        }
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
            if(jugadores.at(u)->posinicialX_barra==60)     //¿Sobre plataforma en movimiento?
                jugadores.at(u)->actualizarcoordenadas(plataformas.at(1)->getPosY());
            if(jugadores.at(u)->saltando == true)
                jugadores.at(u)->moverY();  //Salta
            else if(jugadores.at(u)->colision_barra==false)
                jugadores.at(u)->moverY(0); //Cae
        }
    }else if(localizacion == 3) //............................NIVEL 2
    {
        contTime++;
        ActualizarCountdown();  //Para que se vea el tiempo en pantalla
        if(contTime%50==0)
            DisparosEnemigos();     //Elección de qué enemigos dispararán

        for(unsigned short int u=0; u<(unsigned)jugadores.size(); u++){  //DISPAROS DEL PERSONAJE
            jugadores.at(u)->actualizarDisparos();
            for(unsigned int n=0; n<(unsigned)jugadores.at(u)->balas_lanzadas.size(); n++){ //¿Algún disparo chocó con una nave?
                if(((int)(jugadores.at(u)->balas_lanzadas.at(n)->y())<(y_nE+10)) &&
                        ((int)(jugadores.at(u)->balas_lanzadas.at(n)->y())>2)){     // Evalua si chocó con una nave enemiga
                    qDebug() << "POSICIÓN ARMA: " <<
                                "PosX: " << (int)jugadores.at(u)->balas_lanzadas.at(n)->x() <<
                                "PosY: " << (int)jugadores.at(u)->balas_lanzadas.at(n)->y();
                    for(int i=0; i<Enemigos.size();i++){
                        if(juego->Enemigos.at(i)->IsColliding()){
                            Enemigo *enem=Enemigos.at(i);
                            Enemigos.removeAt(i);
                            delete enem;
                        }
                    }
                }
            }
        }

        for(unsigned int dE=0; dE<(unsigned)disparosEnemigos.size(); dE++){
            //disparosEnemigos.at(dE)->verificarChoques(dE, jugadores);
            disparosEnemigos.at(dE)->ActualizarVelocidad();
            disparosEnemigos.at(dE)->ActualizarPosicion();
        }
        //DisminuirVidas();




/*
    if(contTime<duracion && (J_vivo[0]|| J_vivo[1])){
        if(contTime%(duracion/cantidadMonedas)==0){
            NuevaMoneda();
        }
        //Actualización de tiempos de monedas
        if(Monedas.size()!=0){
            for(int i=0; i<Monedas.size();i++){
                if(Monedas.at(i)->getTiempo()>0) Monedas.at(i)->setTiempo(Monedas.at(i)->getTiempo()-1);
                else{
                    Scene->removeItem(Monedas.at(i));
                    Moneda *moneda=Monedas.at(i);
                    Monedas.removeAt(i);
                    delete moneda;


                }
            }
        }

        // jugadores.at(0)->actualizarDisparos();
           for(int i=0; i<jugadores.size();i++){
               if(jugadores.at(i)->VerificarVida()){
                   //jugadores.at(i)->actualizarDisparos();
                   if(jugadores.at(i)->saltando)
                       jugadores.at(i)->saltar();
               }
               else{
                   Scene->removeItem(jugadores.at(i));
                   jugadores.at(i)->setVidas(0);
                   J_vivo[i]=false;
                   //jugadores.remove(i);
               }
           }
        //--------------------------------------------------------------------------------
     }
    else{
        timer->stop();
        estado_juego=!estado_juego;
        //LimpiarEscena();
    }
*/

    }else if(localizacion==5)   //NIVEL3
    {
        contTime++;
        ActualizarCountdown();  //Para que se vea el tiempo en pantalla

        for(unsigned short int u=0; u<(unsigned)jugadores.size(); u++)  //DISPAROS DEL PERSONAJE
            jugadores.at(u)->actualizarDisparos();
    }

}

void Juego::Trackers()
{
    Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
    Score->setDefaultTextColor(Qt::white);
    Score->setFont(QFont("Book Antiqua", 14));
    Score->setPos(Score->x(),Score->y()+5);
    escena->addItem(Score);

    Lives1->setPlainText(QString("Lives P1: ")+QString::number(J_vidas[0]));
    Lives1->setDefaultTextColor(Qt::white);
    Lives1->setFont(QFont("Book Antiqua", 14));
    Lives1->setPos(Lives1->x(),Lives1->y()+25);
    escena->addItem(Lives1);
    if(multijugador==true){
        Lives2->setPlainText(QString("Lives P2: ")+QString::number(J_vidas[1]));
        Lives2->setDefaultTextColor(Qt::white);
        Lives2->setFont(QFont("Book Antiqua", 14));
        Lives2->setPos(Lives2->x(),Lives2->y()+45);
        escena->addItem(Lives2);
    }

    if(this->getNivel()!=1)
    {
        Time->setFont(QFont("Book Antiqua", 16));
        Time->setPlainText(QString("Time: ")+TimeAsSting());
        Time->setDefaultTextColor(Qt::white);
        Time->setPos(Time->x()+565,Time->y()+10);
        escena->addItem(Time);
    }
}

void Juego::DisparosEnemigos()
{
    //Nivel 2
    if(contTime%10==0 && Enemigos.size()>0){
        int EnemDisparando=rand()%(Enemigos.size()+1);
        for(int i=0;i<=EnemDisparando;i++){
            Enemigos.at(rand()%(Enemigos.size()))->disparar();
        }
    }
}

/*
void Juego::DisminuirVidas()
{
    Lives1->setPlainText(QString("Lives P1: ")+QString::number(J_vidas[0]));
    qDebug() << "Vidas jugador 1: " << J_vidas[0];
    if(multijugador==true){
        Lives2->setPlainText(QString("Lives P2: ")+QString::number(J_vidas[1]));
        qDebug() << "Vidas jugador 2: " << J_vidas[1];
    }
}
*/

void Juego::AumentarPuntaje()
{
    Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
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
