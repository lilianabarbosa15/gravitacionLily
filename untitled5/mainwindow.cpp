#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meteorito.h"

#include <QDebug>

extern QVector<Aliado *> jugadores;
extern QVector<Plataforma *> elementosNivel1;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena->setSceneRect(0,0,680,400);
    ui->Grafica->setScene(escena);
    ui->Grafica->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    niveL1();   //ÉSTO SE DEBE ARREGLAR PARA QUE NO SEA UN NIVEL PREDETERMINADO SINO QUE INGRESE AL NIVEL GUARDADO
    this->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::niveL1()
{
    jugadores.push_back(new Aliado(3, 5));
    escena->addItem(jugadores.back());
    jugadores.at(0)->setFlag(QGraphicsItem::ItemIsFocusable);
    jugadores.push_back(new Aliado(4, 5));        //Multijugador (BOTÓN)
    escena->addItem(jugadores.back());            //Multijugador (BOTÓN)
    jugadores.at(1)->setFlag(QGraphicsItem::ItemIsFocusable);

    /*
    elementosNivel1.push_back(new Plataforma(80,10,50,170,0,0,0,50));
    elementosNivel1.push_back(new Plataforma(80,10,130,170,0,0,0,50));
    elementosNivel1.push_back(new Plataforma(80,10,210,170,0,-0.2,200,80));
    elementosNivel1.at(0)->setFlag(QGraphicsItem::ItemIsFocusable);
    elementosNivel1.at(1)->setFlag(QGraphicsItem::ItemIsFocusable);
    elementosNivel1.at(2)->setFlag(QGraphicsItem::ItemIsFocusable);
    escena->addItem(elementosNivel1.at(0));
    escena->addItem(elementosNivel1.at(1));
    escena->addItem(elementosNivel1.at(2));
    */

    //elementosNivel1.push_back(new Plataforma(80,10,0,180,0,0,0,50));
    //escena->addItem(elementosNivel1.at(3));

    if(jugadores.size()>1)
        multijugador = true;    //VARIABLE GLOBAL
    qDebug() << jugadores.size() << "   multijugador:" << multijugador;
}

void MainWindow::on_inicioJuego_clicked()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    timer->start(dt);
    estado_juego = true;
}

void MainWindow::on_pausaJuego_clicked()
{
    timer->stop();
    delete timer;
    estado_juego = false;
}

void MainWindow::actualizar()   //ORDENAR ESTO CON UNA CLASE NIVEL
{
    //PARA LAS PLATAFORMAS
    for(int i=0; i<elementosNivel1.size();i++)
        elementosNivel1.at(i)->Mover();

    //PARA LOS SALTOS Y LOS DISPAROS DEL PERSONAJE
    jugadores.at(0)->actualizarDisparos();
    if(jugadores.at(0)->saltando == true)
        jugadores.at(0)->saltar();
    if(multijugador == true){
        jugadores.at(1)->actualizarDisparos();
        if(jugadores.at(1)->saltando == true)
            jugadores.at(1)->saltar();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (!estado_juego)
        return false;
    if(event->type()==QEvent::KeyPress)
    {
        pressedKeys += ((QKeyEvent*)event)->key();
        ///////////////////////////////////////////////////////// IZQUIERDA
        if(pressedKeys.contains(Qt::Key_A))
            jugadores.at(0)->mover(Qt::Key_A);
        if(pressedKeys.contains(Qt::Key_H) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_A);
        ///////////////////////////////////////////////////////// DERECHA
        if(pressedKeys.contains(Qt::Key_S))
            jugadores.at(0)->mover(Qt::Key_S);
        if(pressedKeys.contains(Qt::Key_J) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_S);
        ///////////////////////////////////////////////////////// SALTAR
        if(pressedKeys.contains(Qt::Key_W))
            jugadores.at(0)->mover(Qt::Key_W);
        if(pressedKeys.contains(Qt::Key_U) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_W);
        ///////////////////////////////////////////////////////// DISPARAR
        if(pressedKeys.contains(Qt::Key_D))
            jugadores.at(0)->mover(Qt::Key_D);
        if(pressedKeys.contains(Qt::Key_K) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_D);
        ///////////////////////////////////////////////////////// MOVER-ARMA DERECHA
        if(pressedKeys.contains(Qt::Key_R))
            jugadores.at(0)->mover(Qt::Key_R);
        if(pressedKeys.contains(Qt::Key_O) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_R);
        ///////////////////////////////////////////////////////// MOVER-ARMA IZQUIERDA
        if(pressedKeys.contains(Qt::Key_F))
            jugadores.at(0)->mover(Qt::Key_F);
        if(pressedKeys.contains(Qt::Key_L) && multijugador==true)
            jugadores.at(1)->mover(Qt::Key_F);
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }
    return false;
}
