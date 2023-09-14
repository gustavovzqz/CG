#pragma once
#include "../objeto/objeto.h"
class Esfera : public Objeto {
    public:
    Ponto cEsfera;
    double rEsfera;
    Cor corEsfera;
    Esfera();
    Esfera(Ponto c, double r, Cor corEsfera);
    Cor intersecta(Raio r, Iluminacao i);
};