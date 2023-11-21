#pragma once
#include "../objeto/objeto.h"

class Plano : public Objeto
{
public:
    Ponto p_pi;
    Vetor n_bar;
    Plano();
    Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Intensidade intersecta(Raio r, Luz i) override;
    double tInt(Raio r);
};
