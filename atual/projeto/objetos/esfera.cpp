#include "esfera.h"
#include "math.h"

Esfera::Esfera() {}

Esfera::Esfera(Ponto centro, float raio, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->raio = raio;
    this->centro = centro;
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

double Esfera::tInt(Raio r)
{
    Ponto p0 = r.pin;
    Vetor dr = r.dr, w;
    double bBarra, c, delta, t1, t2;

    w = subP(p0, centro);
    bBarra = innerProd(w, dr);
    c = innerProd(w, w) - (raio * raio);
    delta = (bBarra * bBarra) - c;

    if (delta < 0)
        return -1; // Se não intersecta, retorna a cor padrão.

    t1 = -bBarra - sqrt(delta);
    t2 = -bBarra + sqrt(delta);
    if (t1 <= t2 && t1 > 0)
        return t1;
    if (t1 > t2 && t2 > 0)
        return t2;
    return -1;
}

Cor Esfera::intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado)
{
    Ponto p0 = r.pin, pint;
    Vetor dr = r.dr, n;
    double tint = tInt(r);
    if (tint < 0)
        return bgColor;
    pint = addPV(p0, prodVetorC(dr, tint));
    n = divVetorC(subP(pint, centro), raio);
    // Aqui, já temos o ponto de intersecção correto.
    // Basta chamar a função de iluminação para sabermos a cor correta.
    return (i.iluminarObjeto(n, pint, dr, Ke, Kd, Ka, m, ehiluminado));
}