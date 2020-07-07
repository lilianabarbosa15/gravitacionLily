#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QTimer>
#include "jugador.h"
#include "meteorito.h"

namespace Ui { class Juego; }

class Juego : public QMainWindow {
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

    Jugador *jugador;
    Meteorito *meteorito;

private slots:
    void actualizar();          // NO SÉ SI SEA NECESARIA
    void on_inicioJuego_clicked();
    void on_pausaJuego_clicked();

private:
    Ui::Juego *ui;

};

#endif // JUEGO_H
