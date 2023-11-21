#pragma once
#include "alinear.h"

class Luz
{
public:
    Ponto pF;
    Intensidade iF;
    Vetor ds;
    double alfa;
    bool ehPontual, ehDirecional, ehSpot;
    Luz();
    Luz(Ponto pF, Intensidade iF); // Construtor pontual
    Luz(Ponto pF, Intensidade iF, Vetor ds, double alfa);
    Luz(Intensidade iF, Vetor ds);
    Intensidade iluminarDirecional(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m);
    Intensidade iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m);
    Intensidade iluminarSpot(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m);
    Intensidade iluminarPontual(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m);
};
