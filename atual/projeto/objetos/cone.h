#pragma once
#include "../objeto/objeto.h"

class Cone : public Objeto
{
public:
    double h;
    double rb;
    Vetor dc;
    Ponto cb;
    Ponto v;
    Cone();
    Cone(Ponto cb, double r, Vetor dc, double h, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Cone(Ponto cb, double r, Ponto vc, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Intensidade intersecta(Raio r, Luz i);
    void escalar(double, double, double);
    double intersecta_corpo(Raio r);
    double intersecta_base(Raio r);
    void appMatrix(Matriz m);
    double tInt(Raio r);
    Vetor normalCorpo(Raio r, double tint);
};
