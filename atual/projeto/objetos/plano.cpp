#include "plano.h"
#include <iostream>

Plano::Plano() {}

Plano::Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->p_pi = p_pi;
    this->n_bar = n_bar;
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

double Plano::tInt(Raio r)
{
    Ponto p0 = r.pin;
    Vetor dr = r.dr, w = subP(p0, p_pi);
    return (-(innerProd(n_bar, w) / innerProd(n_bar, dr)));
}
void Plano::escalar(double r1, double r2, double r3)
{
    (void)r1;
    (void)r2;
    (void)r3;
}

void Plano::appMatrix(Matriz m)
{
    p_pi = prodMP(m, p_pi);
    n_bar = prodMV(m, n_bar);
}

Intensidade Plano::intersecta(Raio r, Luz i)
{
    double tint;
    Ponto p0 = r.pin, pint;
    Vetor dr = r.dr;

    tint = tInt(r);
    pint = addPV(p0, prodVetorC(dr, tint));

    return (i.iluminarObjeto(n_bar, pint, dr, Ke, Kd, m));
}