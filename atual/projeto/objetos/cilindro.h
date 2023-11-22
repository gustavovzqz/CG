#pragma once
#include "../objeto/objeto.h"
#include "../tela/textura.h"

class Cilindro : public Objeto
{
public:
    double h;
    double rc;
    Vetor dc;
    Ponto cb;
    Ponto ct;
    Cilindro();
    Cilindro(Ponto cb, Ponto ct, double r, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Cilindro(Ponto cb, Vetor dc, double rc, double h, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Intensidade intersecta(Raio r, Luz i);
    void escalar(double, double, double);
    double intersecta_corpo(Raio r);
    double intersecta_tampa(Raio r);
    double intersecta_base(Raio r);
    void appMatrix(Matriz m);
    double tInt(Raio r);
    Vetor normalCorpo(Raio r, double tint);
};
