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
    }else{
        multijugador=false;
    }
    puntaje = infoUsuario.int1;
    localizacion = infoUsuario.int2;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(localizacion==1)     //............................NIVEL 1
    {
        //estrella = new Moneda(0,15,10,530,60,0.2);
        //estrella = new Moneda(0,15,10,530,360,0.2,1,duracion);
        //NuevosPuntos();
        escena->setBackgroundBrush(QBrush(QImage(":/primera/Spaceport_.jpg").scaled(680,400)));

        if(multijugador==true){
            cantidadMonedas = 80;
            J_vivo[1]=true;
        }else
            cantidadMonedas = 50;

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
        jugadores.push_back(new Aliado(localizacion, 2));
        if(multijugador == true)
            jugadores.push_back(new Aliado(localizacion+1, 2));
        for(short int u=0; u<jugadores.size(); u++){
            escena->addItem(jugadores.at(u));
            jugadores.at(u)->setFlag(QGraphicsItem::ItemIsFocusable);
        }
        Trackers();
    }
}

void Juego::actualizar()
{
    //for(unsigned short int o=0; o<(unsigned)jugadores.size(); o++)
    //    jugadores.at(o)->verificarChoques(2);   //¿Choca con un meteorito?

    contTime++;
    AumentarPuntaje();
    DisminuirVidas();       //Para actualizar las vidas de los personajes
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(localizacion==1) //............................NIVEL 1
    {
        //if(contTime%10==0)
        //    NuevosPuntos();
        if(contTime%70==0)
            NuevosMeteoritos();
        for(int tipo_a=0; tipo_a<jugadores.size(); tipo_a++){
            for(unsigned int m_cae=0; m_cae<(unsigned)meteoritos.size(); m_cae++){
                juego->jugadores.at(tipo_a)->actualizarVida(tipo_a);  //¿Algún meteoro chocó con el personaje?
            }
        }
        /*
        for(unsigned int n=0; n<(unsigned)estrellas.size(); n++){
            estrellas.at(n)->Mover();
            estrellas.at(n)->AumentarPuntaje();
        }
        */
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

    }else if(localizacion == 3) //............................NIVEL 2               //HAY QUE EVALUAR EL ESTADO DEL PROGRAMA!!!!!!!!!!!!!!!!!!!!!!!
    {
        ActualizarCountdown();  //Para que se vea el tiempo en pantalla
        if(contTime%20==0)
            DisparosEnemigos();     //Elección de qué enemigos dispararán

        ////////////////////////////////////Se puede poner en una pantilla////////////////////////////////////
        for(unsigned short int bala_j=0; bala_j<(unsigned)disparosAliados.size(); bala_j++){
            for(int tipo_e=0; tipo_e<Enemigos.size(); tipo_e++)
                juego->Enemigos.at(tipo_e)->actualizarVida(bala_j,tipo_e);  //¿Algún disparo chocó con una nave enemiga?

            if(disparosAliados.at(bala_j)->y()<0){
                escena->removeItem(disparosAliados.at(0));
                disparosAliados.pop_front();
            }else{
                disparosAliados.at(bala_j)->ActualizarVelocidad();
                disparosAliados.at(bala_j)->ActualizarPosicion();
            }
        }
        for(unsigned int bala_e=0; bala_e<(unsigned)disparosEnemigos.size(); bala_e++){ //Actualización de las balas del enemigo
            for(int tipo_a=0; tipo_a<jugadores.size(); tipo_a++)
                juego->jugadores.at(tipo_a)->actualizarVida(tipo_a);  //¿Algún disparo chocó con una nave enemiga?

            if(disparosEnemigos.at(bala_e)->y()>400){
                escena->removeItem(disparosEnemigos.at(0));
                disparosEnemigos.pop_front();
            }else{
                disparosEnemigos.at(bala_e)->ActualizarVelocidad();
                disparosEnemigos.at(bala_e)->ActualizarPosicion();
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////
    }




    else if(localizacion==5)   //NIVEL3
    {
        contTime++;
        ActualizarCountdown();  //Para que se vea el tiempo en pantalla

        //for(unsigned short int u=0; u<(unsigned)jugadores.size(); u++)  //DISPAROS DEL PERSONAJE
            //jugadores.at(u)->actualizarDisparos();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    //Actualización de tiempos de monedas
    if(estrellas.size()!=0 && estrellas.at(0)->getValor()>0){
        for(int i=0; i<estrellas.size();i++){
            if(estrellas.at(i)->getTiempo()>0)
                estrellas.at(i)->setTiempo(estrellas.at(i)->getTiempo()-1);
            else{
                escena->removeItem(estrellas.at(i));
                estrellas.at(i)->hide();
                estrellas.removeAt(i);
            }
        }
    }
    if(contTime<duracion && (J_vivo[0] || J_vivo[1])){
        for(unsigned int n=0; n<(unsigned)estrellas.size(); n++){
            estrellas.at(n)->Mover();
            estrellas.at(n)->AumentarPuntaje(n);
        }
        if(contTime%(duracion/cantidadMonedas)==0)
            NuevosPuntos();
    }else{
        timer->stop();
        J_vivo[0]=J_vivo[1]=false;
    }

}

void Juego::Trackers()
{
    Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
    Score->setDefaultTextColor(Qt::white);
    Score->setFont(QFont("Book Antiqua", 14));
    Score->setPos(Score->x(),Score->y()+5);
    escena->addItem(Score);

    Lives1->setPlainText(QString("Lives P1: ")+QString::number(jugadores.at(0)->vidas));
    Lives1->setDefaultTextColor(Qt::white);
    Lives1->setFont(QFont("Book Antiqua", 14));
    Lives1->setPos(Lives1->x(),Lives1->y()+25);
    escena->addItem(Lives1);
    if(multijugador==true){
        Lives2->setPlainText(QString("Lives P2: ")+QString::number(jugadores.at(1)->vidas));
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
    int n = rand()%(Enemigos.size());
    if(contTime%10==0 && Enemigos.size()>0){
        int EnemDisparando=rand()%(Enemigos.size()+1);
        for(int i=0;i<=EnemDisparando;i++){
            if(Enemigos.at(n)->vivo==true)
                Enemigos.at(n)->disparar();
        }
    }
}

void Juego::DisminuirVidas()
{
    if(jugadores.size()>0){
        Lives1->setPlainText(QString("Lives P1: ")+QString::number(jugadores.at(0)->vidas));
        if(multijugador==true){
            Lives2->setPlainText(QString("Lives P2: ")+QString::number(jugadores.at(1)->vidas));
        }
    }
}

void Juego::AumentarPuntaje()
{
    Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
}

void Juego::NuevosMeteoritos()
{
    meteorito_alien = new Meteorito(0,9,(rand() % 650 + 10),0,20);
    meteoritos.push_back(meteorito_alien);
    escena->addItem(meteorito_alien);
}

void Juego::NuevosPuntos()
{
    //x_random = rand() % 650 + 10;
    //estrella = new Moneda(20,9.2,3.5,x_random,370,0.1);
    //estrella = new Moneda(20,9.2,3.5,x_random,y_random,0.1,tiempo_estrella);

    /*
        //estrella = new Moneda(0,15,10,530,60,0.2);
        //estrella = new Moneda(0,15,10,530,360,0.2,1,duracion);
        NuevosPuntos();
     */
    if(juego->getNivel()==1 && estrellas.size()==0)
        estrella = new Moneda(0,15,10,530,360,0.2,1,duracion+10);
    else if(juego->getNivel()==1 && estrellas.size()>0)
        estrella = new Moneda(20,9.2,3.5,rand() % 650 + 10,370,0.1, 2, 100);
    else if(juego->getNivel()==2)
        estrella = new Moneda(50,9,6,5+(std::rand()%(671)),110+(std::rand()%(271-110)),0.1, 3, 150);
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
