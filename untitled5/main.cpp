#include "mainwindow.h"

#include <QApplication>

QVector<Aliado *> jugadores;
QVector<Plataforma *> elementosNivel1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
