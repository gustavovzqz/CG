#pragma once 
#include "../objeto/objeto.h"

class Esfera : public Objeto {
public:
    Ponto centro; 
    double raio;
    Cor cor;
    Esfera();
    Esfera(Ponto centro, double raio, Cor cor, Intensidade Ke, Intensidade Ka, Intensidade Kd, double m);
    Cor intersecta(Raio r, Luz i, Cor bgColor) override;

    Vetor makeN(Ponto pint, Vetor dr) override;
};