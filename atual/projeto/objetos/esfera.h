#pragma once
#include "../objeto/objeto.h"

class Esfera : public Objeto
{
public:
    Ponto centro;
    float raio;
    Cor cor;
    Esfera();
    Esfera(Ponto centro, float raio, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Intensidade intersecta(Raio r, Luz i) override;
    double tInt(Raio r);
};