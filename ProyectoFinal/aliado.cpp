#include "aliado.h"
#include <QDebug>
#include <math.h>
#include "plataforma.h"

#include "juego.h"
extern Juego *juego;

Aliado::Aliado(int tipo, int life)      // tipo: 1 o 2 astronautas del nivel 1, 3 o 4 a naves, 5 o 6 astronautas del nivel 3.
{
    jugador = tipo;
    vidas = life;
    dibujarItem();
    setPos(posicion_x, posicion_y);
}
void Aliado::dibujarItem()
{
    if(jugador == 1){
        aparienciaR = QPixmap(":/aliado/Astronaut_Right_01.png");
        aparienciaL = QPixmap(":/aliado/Astronaut_Left_01.png");
    }
    if(jugador == 2){
        aparienciaR = QPixmap(":/aliado/Astronaut_Right_02.png");
        aparienciaL = QPixmap(":/aliado/Astronaut_Left_02.png");
        posicion_x = posicioninicial_x = 30;
    }
    if(jugador == 3){
        aparienciaR = QPixmap(":/aliado/Spaceship_01.png").scaled(ancho,alto);
        posicion_x = posicioninicial_x = 305;
    }
    if(jugador == 4){
        aparienciaR = QPixmap(":/aliado/Spaceship_02.png").scaled(ancho,alto);
        posicion_x = posicioninicial_x = 350;
    }
    if(jugador == 5){
        aparienciaR = QPixmap(":/aliado/Astronaut_Right_01.png");
        aparienciaL = QPixmap(":/aliado/Astronaut_Left_01.png");
        posicion_x = posicioninicial_x = 50;
    }
    if(jugador == 6){
        aparienciaR = QPixmap(":/aliado/Astronaut_Right_02.png");
        aparienciaL = QPixmap(":/aliado/Astronaut_Left_02.png");
        posicion_x = posicioninicial_x = 605;
    }

    setPixmap(aparienciaR.copy(pixX,pixY,ancho+8,alto));
    setPos(posicion_x,posicion_y);
}

void Aliado::calcularmovimiento(int evento)
{
    //Controla los metodos se deben ejecutar dependiendo de la tecla presionada
    if(evento == Qt::Key_A)     //SE MUEVE A LA IZQUIERDA
        moverX(evento);
    if(evento == Qt::Key_S)     //SE MUEVE A LA DERECHA
        moverX(evento);
    if(evento == Qt::Key_W && jugador<=2)     //SALTA (Sólo para el nivel 1)
        saltando = true;
    if(evento == Qt::Key_D && jugador>2)      //DISPARA (Para los niveles 2 y 3)
        disparar();
    if(evento == Qt::Key_R && jugador>4)      //MUEVE EL ARMA HACIA DERECHA (Sólo para el nivel 3)
        moverArma(angulo_disparo-45.0*(Pi/180.0), evento);
    if(evento == Qt::Key_F && jugador>4)      //MUEVE EL ARMA HACIA IZQUIERDA (Sólo para el nivel 3)
        moverArma(angulo_disparo+45.0*(Pi/180.0), evento);
}

void Aliado::moverX(int evento)
{
    pixX+=33;
    if(pixX>165)
        pixX=0;

    if(evento==Qt::Key_A){
        if(juego->getNivel()!=2)
            setPixmap(aparienciaL.copy(pixX,pixY,ancho+8,alto));
        posicion_x-=(paso-friccion);
    }
    if(evento==Qt::Key_S){
        if(juego->getNivel()!=2)
            setPixmap(aparienciaR.copy(pixX,pixY,ancho+8,alto));
        posicion_x+=(paso-friccion);
    }
    verificarMovimiento();
}

void Aliado::moverY(unsigned short tipo)    //SOLO SE USA EN EL NIVEL 1
{
    if(tipo==1 && ((juego->getPlataformas().at(barra)->getPosX()<=this->x()+ancho) &&
       (juego->getPlataformas().at(barra)->getPosX()+juego->getPlataformas().at(barra)->getAncho()>this->x())))
    {
        Vy=velocidad*sin(theta)-Gravedad*tiempo;
        velocidad=sqrt(Vy*Vy);
        theta=atan2(Vy,0);
        posicion_y-=Vy*tiempo-(0.5*Gravedad*tiempo*tiempo);
        if(juego->getPlataformas().at(barra)->getPosY()<=posicion_y+alto)
        {
            saltando = false;
            velocidad = V;
            theta = Pi/180.0;
            actualizarcoordenadas(juego->getPlataformas().at(barra)->getPosY());
        }
        verificarMovimiento();
    }
    else
    {
        Vy=-2.5*Gravedad*tiempo;    //Le puse un x2.5 para que caiga más rápido
        posicion_y-=Vy*tiempo-(0.5*Gravedad*tiempo*tiempo);
        verificarMovimiento();
    }
}

void Aliado::actualizarcoordenadas(int posY_barra)  //SOLO SE USA EN EL NIVEL 1
{
    if((juego->getPlataformas().at(barra)->getPosX()<=this->x()+ancho))
    {
        posicion_y = posicioninicial_y = (posY_barra-alto);
        setPos(posicion_x,posicion_y);
    }
}

void Aliado::moverArma(float posibleangulo, int direccion)
{
    //Dependiendo de la tecla presionada mueve el arma y la posición de ella respecto al jugador
    if(direccion == Qt::Key_R){
        if(posibleangulo>(-46.0*(Pi/180.0))){
            angulo_disparo = posibleangulo;
            indica_posicion_arma+=1;
        }
    }else{
        if(posibleangulo<(226.0*(Pi/180.0))){
            angulo_disparo = posibleangulo;
            indica_posicion_arma-=1;
        }
    }
}

void Aliado::actualizarDisparos()
{
    // Desaparece o actualiza la bala lanzada, dependiendo de la ubicación de esta
    for(int n=0; n<this->balas_lanzadas.size(); n++)
    {
        if(this->balas_lanzadas.at(n)->getPosicionY()>0 &&
                (this->balas_lanzadas.at(n)->getPosicionX()>-20 && this->balas_lanzadas.at(n)->getPosicionX()<680)){
            this->balas_lanzadas.at(n)->ActualizarVelocidad();
            this->balas_lanzadas.at(n)->ActualizarPosicion();
        }else{
            this->balas_lanzadas.at(n)->Desaparecer();
            this->balas_lanzadas.remove(n);
        }
    }
}

void Aliado::disparar()
{
    //Si se encuentra en el nivel 3 se ejecuta la primera serie de instrucciones
    if(juego->getNivel()==3)
    {
        for(int j=0;j<7;j++){
            posicion_arma[j][0] = posicion_x;
            posicion_arma[j][1] = posicion_y;
            if(j==0 || j==6)
                posicion_arma[j][1] += ancho;
            if(j==1 || j==5)
                posicion_arma[j][1] += (ancho/2);
            if(j==3)
                posicion_arma[j][0] += (ancho/2);
            if(j>3 && j<7)
                posicion_arma[j][0] += ancho;
        }
        bala = new Meteorito(1,5,posicion_arma[indica_posicion_arma][0],posicion_arma[indica_posicion_arma][1],100, angulo_disparo);
    }
    else
        bala = new Meteorito(1,7,posicion_x+(ancho/2),posicion_y,100, angulo_disparo);  //SÓLO ESTÁ DISPARANDO EN 90 GRADOS
    balas_lanzadas.push_back(bala);
    bala->setFlag(QGraphicsItem::ItemIsFocusable);
    scene()->addItem(bala);
}

void Aliado::verificarMovimiento()
{
    if(juego->getNivel()==1)    //SOLO SE USA EN EL NIVEL 1
    {
        colision_barra = false;
        posinicialY_barra = 400;
        posinicialX_barra = 0;
    }

    verificarChoques();

    if((colision_barra==true || this->y()+alto>400) && juego->getNivel()==1)    //SOLO SE USA EN EL NIVEL 1
    {
        //Para que el personaje no caiga más del suelo de la escena
        //Actualiza si se encuentra en una plataforma
        saltando = false;
        actualizarcoordenadas(posinicialY_barra);
        velocidad = V;
        theta = Pi/180.0;
    }
    if(juego->getNivel()!=1)                                    //SOLO SE USA CUANDO NO SE ENCUENTRA EN EL NIVEL 1
    {
        posicionx_bala = posicion_x+(ancho/2);
        posiciony_bala = posicion_y;
    }

    if(posicion_x+ancho>680)                                //Para que no se salga el personaje por la derecha de la escena
        posicion_x -=(paso-friccion);
    if(posicion_x<0)                                        //Para que no se salga el personaje por la izquierda de la escena
        posicion_x +=(paso-friccion);
    setPos(posicion_x,posicion_y);

}

void Aliado::verificarChoques(unsigned short int tipo)
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        qDebug() << "chocó";
        if((typeid(*(colliding_items[i]))==typeid (Plataforma)) && tipo==1){  //SOLO SE USA EN EL NIVEL 1
            posinicialY_barra = (int)(colliding_items.at(i)->pos().y()*10000);  //x10000 para darle la posición real de la barra
            posinicialX_barra = (int)(colliding_items.at(i)->pos().x()*10000);
            for(unsigned int i=0; i<(unsigned)juego->getPlataformas().size(); i++){
                if(juego->getPlataformas().at(i)->getPosX() == posinicialX_barra){
                    barra = i;
                    friccion = juego->getPlataformas().at(barra)->getFrictionC();
                    break;
                }
            }
            if(((this->y()+alto)-(posinicialY_barra))<=5 && ((this->y()+alto)-(posinicialY_barra))>0)  //¿SOBRE UNA PLATAFORMA?
                colision_barra = true;
        }

        if((typeid(*(colliding_items[i]))==typeid(Meteorito)) && tipo==2){  //SOLO SE USA EN EL NIVEL 1
            colliding_items.at(i)->hide();
            this->vidas -=1;
            qDebug() << "CHOCA CON METEORO" << " ------vidas: " << this->vidas;
        }

        if((typeid(*(colliding_items[i]))==typeid(Moneda)) && tipo==2){  //SOLO SE USA EN EL NIVEL 1
            if(colliding_items.at(i)->y()>180){
                colliding_items.at(i)->hide();
                this->puntos += 20;
            }
            else
                this->next_nivel = true;
            qDebug() << "CHOCA CON estrella" << ": " << this->puntos << "estado: " << this->next_nivel;
        }


        qDebug() << "chocó con plataforma   -------->  pos_y " << this->y()+alto <<
                                                     " pos_x " << this->x() <<
                                                     " posinicialY_barra " <<posinicialY_barra <<
                                                     " posinicialX_barra " <<posinicialX_barra <<
                                                     " saltando " <<saltando <<
                                                     " colision_barra "<< colision_barra;

    }
}