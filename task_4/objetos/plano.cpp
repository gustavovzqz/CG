#include "plano.h"
#include <iostream>

Plano::Plano(){}

Plano::Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m){
    this -> p_pi = p_pi;
    this -> n_bar = n_bar;
    this -> Ke = Ke;
    this -> Ka = Ka;
    this -> Kd = Kd; 
    this -> m = m;
}

double Plano::tInt(Raio r){
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Vetor w = subP(p0, p_pi);
    return (-(innerProd(n_bar, w)/innerProd(n_bar, dr)));
}
    
Cor Plano::intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado){
    double tint;
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint;
    double condicao;

    tint = tInt(r);
    if (tint < 0)
        return bgColor;
    pint = addPV(p0, prodVetorC(dr, tint));
    condicao = innerProd(subP(pint, p_pi), n_bar);

    return (i.iluminarObjeto(n_bar, pint, dr, Ke, Kd, Ka, m, ehiluminado));
}