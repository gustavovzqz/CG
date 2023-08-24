#pragma once
#include "alinear.h"

class Esfera {
    public:
    Ponto cEsfera;
    double rEsfera;
    Cor corEsfera;
    Esfera();
    Esfera(Ponto c, double r, Cor corEsfera);
};