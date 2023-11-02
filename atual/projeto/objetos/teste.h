#pragma once
#include "../objetos/malha.h"

class Teste : public Malha
{
public:
    Teste();
    Teste(double a, Ponto c, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    void inicializar(double a, Ponto c);
};
