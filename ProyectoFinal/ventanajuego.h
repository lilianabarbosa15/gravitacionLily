#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H


#include <QLabel>
#include <QDialog>

#include <QTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

//#include "aliado.h"
//#include "plataforma.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaJuego; }
QT_END_NAMESPACE


class VentanaJuego : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaJuego(QWidget *parent = nullptr);
    ~VentanaJuego();

public slots:
    void on_actionMusica_triggered();
    void on_actionSobrePersonajes_triggered();
    void on_inicioJuego_clicked();
    void on_pausaJuego_clicked();

public slots:
    void actualizar();

private:
    Ui::VentanaJuego *ui;
    QSet<int> pressedKeys;                              //Para el filtrado de eventos
    float dt = 15;                                      //Rapidez con la que se ejecutan los saltos
    bool estado = false;                          //Determina si se leen las letras presionadas o no

protected:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // VENTANAJUEGO_H
