#ifndef BALA_H
#define BALA_H

#include "meteorito.h"

class Bala: public Meteorito//, public QObject
{
    using Meteorito::Meteorito;
    void verificarChoques();
};

#endif // BALA_H