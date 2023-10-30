#pragma once 
#include "../objeto/objeto.h"

class Esfera : public Objeto {
public:
    Ponto centro; 
    float raio;
    Cor cor;
    Esfera();
    Esfera(Ponto centro, float raio, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Cor intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado) override;
    double tInt(Raio r);

};