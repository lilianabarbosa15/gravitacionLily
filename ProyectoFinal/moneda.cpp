#include "moneda.h"
#include "aliado.h"
#include "juego.h"
#include <QDebug> //

extern Juego *juego;

Moneda::Moneda(int _valor, double radio_moneda, double radio_giro, double x_inicial, double y_inicial, double _velAngular, int _tiempo)
{
    valor=_valor;   //Cantidad de puntos que tendrá la moneda
    radioMoneda=radio_moneda;
    radioGiro=radio_giro;
    posX=x_inicial;
    posY=y_inicial;
    Xinicial=x_inicial;
    Yinicial=y_inicial;
    velAngular=_velAngular;
    tiempo=_tiempo;
    if(valor==0)
        apariencia = QPixmap(":/primera/Star1.png");
    else
        apariencia = QPixmap(":/primera/Star2.png");
    Aparecer();
}

void Moneda::Aparecer()
{
    //Colocando moneda en su posición inicial
    setPos(posX,posY);
}

void Moneda::Mover()
{
    //Actualizando ángulo y posiciones de la moneda
    angulo+=velAngular;
    posX=Xinicial+radioGiro*cos(angulo);
    posY=Yinicial+radioGiro*sin(angulo);
    Aparecer();
}

QRectF Moneda::boundingRect() const
{
  return QRectF(-radioMoneda,-radioMoneda,2*radioMoneda,2*radioMoneda);

}

void Moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),apariencia,apariencia.rect());
}

int Moneda::getTiempo() const
{
    return tiempo;
}

void Moneda::setTiempo(int value)
{
    tiempo = value;
}

bool Moneda::getInScene() const
{
    return InScene;
}

void Moneda::setInScene(bool value)
{
    InScene = value;
}

void Moneda::AumentarPuntaje()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        qDebug() << "chocó";
        if(typeid(*(colliding_items[i]))==typeid(Aliado)){
            if(this->valor>0){
                juego->puntajeNivel += this->valor;
                this->hide();
                scene()->removeItem(this);
            }
            colliding_items.clear();
            qDebug() << "CHOCA CON estrella";
        }
    }
}


