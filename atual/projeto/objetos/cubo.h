#pragma once
#include "../objetos/malha.h"

class Cubo : public Malha
{
public:
    Cubo();
    Cubo(double a, Ponto c, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    void inicializar(double a, Ponto c);
};
