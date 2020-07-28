#include "moneda.h"


Moneda::Moneda(int _valor, double radio_moneda, double radio_giro, double x_inicial, double y_inicial, double _velAngular)
{
    valor=_valor;
    radioMoneda=radio_moneda;
    radioGiro=radio_giro;
    posX=x_inicial;
    posY=y_inicial;
    Xinicial=x_inicial;
    Yinicial=y_inicial;
    velAngular=_velAngular;
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
    setPos(posX,posY);

}

QRectF Moneda::boundingRect() const
{
  return QRectF(-radioMoneda,-radioMoneda,2*radioMoneda,2*radioMoneda);

}

void Moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),apariencia,apariencia.rect());
}
