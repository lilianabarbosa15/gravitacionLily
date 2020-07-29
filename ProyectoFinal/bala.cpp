#include "bala.h"
#include <QDebug> //
#include "enemigo.h"


void Bala::verificarChoques()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        qDebug() << "la bala chocó";
        if(typeid(*(colliding_items[i]))==typeid(Enemigo)){  //SOLO SE USA EN EL NIVEL 1
            colliding_items.at(i)->hide();
            qDebug() << "CHOCA CON ENEMIGO";
        }
    }
}
