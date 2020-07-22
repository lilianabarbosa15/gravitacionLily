#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "aliado.h"
#include "plataforma.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void niveL1(); //-------------------------ÉSTO HAY QUE MOVERLO A UNA CLASE

private slots:
    void on_inicioJuego_clicked();  //--------YA HAY UN BOTÓN, SÓLO HAY QUE PROGRAMARLO CON LAS MISMAS INSTRUCCIONES
    void on_pausaJuego_clicked();   //--------YA HAY UN BOTÓN, SÓLO HAY QUE PROGRAMARLO CON LAS MISMAS INSTRUCCIONES

public slots:
    void actualizar();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena = new QGraphicsScene(this);  //La escena del juego como tal
    QSet<int> pressedKeys;                              //Para el filtrado de eventos
    QTimer *timer;                                      //Crea el timer
    float dt = 15;                                      //Rapidez con la que se ejecutan los saltos
    bool multijugador = false;
    bool estado_juego = false;                          //Determina si se leen las letras presionadas o no

protected:
    bool eventFilter(QObject *obj, QEvent *event);

};
#endif // MAINWINDOW_H
