#include "juego.h"
#include "ui_juego.h"

extern bool estado;

#include <QDebug> //

//extern QGraphicsScene *escena;
extern float dt;
extern QTimer *timer;

extern QGraphicsScene *scene;

Juego::Juego(QWidget *parent) : QMainWindow(parent), ui(new Ui::Juego){
    ui->setupUi(this);

/*
    dt = 1;
    timer = new QTimer(this);                       //Crear el timer
    timer->stop();                                  //Parar el timer
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));


    escena = new QGraphicsScene(this);              //Crear la escena
    ui->Grafica->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setScene(escena);
*/
    srand(time(NULL));

    //Create a Scene
    scene = new QGraphicsScene(this);              //Crear la escena
    scene->setSceneRect(0,0,580,340);
    ui->Grafica->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setScene(scene);

    //Create an Item to put into the scene
    jugador = new Jugador();
    jugador->setRect(0,0,25,40);
    scene->addItem(jugador);

    //make rect focusable
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();

    jugador->setPos(0,300);   //  <<------------<<< PARA QUE SE VEA EN UNA POSICIÓN INICIAL


    //Spawn enemies
    timer = new QTimer();
    timer->stop();
    connect(timer,SIGNAL(timeout()), jugador, SLOT(spawn()));

    show();
}

Juego::~Juego(){
    delete ui;
    delete timer;
    delete jugador;                 // <<------------------------------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}

void Juego::actualizar(){   //Función que se ejecuta constantemente ya que está conectada al timer
    qDebug() << "pasa";
}

void Juego::on_inicioJuego_clicked(){
    timer->start(500);     //Iniciar el timer
    estado=true;            //Comienza los demás timers
}

void Juego::on_pausaJuego_clicked(){
    timer->stop();      //Pausar el timer
    estado=false;       //Paraliza los demás timers
}
