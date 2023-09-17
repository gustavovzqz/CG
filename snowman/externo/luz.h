#pragma once 
#include "alinear.h"

class Luz {
    public:
    Ponto pF; 
    Intensidade iAmb, iF;

    Luz();
    Luz(Ponto pF, Intensidade iAmb, Intensidade iF);
    Cor iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, Intensidade Ka, float m, Cor cor, bool ehiluminado);
};
