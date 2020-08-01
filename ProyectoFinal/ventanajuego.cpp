#include "ventanajuego.h"
#include "ui_ventanajuego.h"
#include "juego.h"

#include <QMediaPlayer>
extern QMediaPlayer *musica;
extern QGraphicsScene *escena;
extern Juego *juego;

VentanaJuego::VentanaJuego(QWidget *parent) : QMainWindow(parent), ui(new Ui::VentanaJuego)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,680,400);
    ui->Grafica->setScene(escena);
    ui->Grafica->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Grafica->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->installEventFilter(this);
    srand(unsigned(time(nullptr)));

    qDebug() << "NUEVO JUEGO";
}

VentanaJuego::~VentanaJuego()
{
    delete ui;
}

void VentanaJuego::on_actionMusica_triggered()
{
    if(musica->state() == QMediaPlayer::PlayingState)
        musica->stop();
    else
        musica->play();
}

void VentanaJuego::on_actionSobrePersonajes_triggered()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/iconos/iconW_nave.png"));
    dialog->setWindowTitle("Información de personajes");
    dialog->setGeometry(this->x(),this->y(),500,500);
    dialog->setFixedSize(500,500);
    dialog->setStyleSheet("background-color:black;");
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel *label = new QLabel(dialog);
    label->setPixmap(QPixmap(":/info/Personajes_SinDescripcion.png").scaled(500,500));

    dialog->setModal(true);
    dialog->setVisible(true);
}

void VentanaJuego::on_inicioJuego_clicked()
{
    if((juego->getNivel()>0 && juego->getNivel()<4) && (juego->estado_juego==false)){
        juego->timer = new QTimer;
        connect(juego->timer,SIGNAL(timeout()),this,SLOT(actualizar()));
        juego->timer->start(dt);
        estado=juego->estado_juego = true;
    }
}

void VentanaJuego::on_pausaJuego_clicked()
{
    if((juego->getNivel()>0 && juego->getNivel()<4) && (juego->estado_juego==true)){
        juego->timer->stop();
        estado=juego->estado_juego = false;
    }
}

void VentanaJuego::actualizar()
{
    juego->actualizar();
}

bool VentanaJuego::eventFilter(QObject *obj, QEvent *event)
{
    if (!estado)
        return false;
    if((event->type()==QEvent::KeyPress && (juego->getNivel()>0 && juego->getNivel()<4)) && juego->estado_juego==true)
    {
        pressedKeys += ((QKeyEvent*)event)->key();
        ///////////////////////////////////////////////////////// IZQUIERDA
        if(pressedKeys.contains(Qt::Key_A) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_A);
        if((pressedKeys.contains(Qt::Key_H) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_A);
        ///////////////////////////////////////////////////////// DERECHA
        if(pressedKeys.contains(Qt::Key_S) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_S);
        if((pressedKeys.contains(Qt::Key_J) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_S);
        ///////////////////////////////////////////////////////// SALTAR
        if(pressedKeys.contains(Qt::Key_W) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_W);
        if((pressedKeys.contains(Qt::Key_U) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_W);
        ///////////////////////////////////////////////////////// DISPARAR
        if(pressedKeys.contains(Qt::Key_D) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_D);
        if((pressedKeys.contains(Qt::Key_K) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_D);
        ///////////////////////////////////////////////////////// MOVER-ARMA DERECHA
        if(pressedKeys.contains(Qt::Key_R) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_R);
        if((pressedKeys.contains(Qt::Key_O) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_R);
        ///////////////////////////////////////////////////////// MOVER-ARMA IZQUIERDA
        if(pressedKeys.contains(Qt::Key_F) && juego->J_vivo[0]==true)
            juego->jugadores.at(0)->calcularmovimiento(Qt::Key_F);
        if((pressedKeys.contains(Qt::Key_L) && juego->getModoJuego()==true) && juego->J_vivo[1]==true)
            juego->jugadores.at(1)->calcularmovimiento(Qt::Key_F);
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }
    return false;
}
