#include "cone.h"
#include <cmath>

Cone::Cone() {}

Cone::Cone(Ponto cb, double r, Vetor dc, double h, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->h = h;
    this->cb = cb;
    this->rb = r;
    this->dc = dc;
    this->v = addPV(cb, prodVetorC(dc, h));
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

Cone::Cone(Ponto cb, double r, Ponto v, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->cb = cb;
    this->rb = r;
    this->dc = normalizar(subP(v, cb));
    this->h = modulo(subP(v, cb));
    this->v = v;
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

Vetor Cone::normalCorpo(Raio r, double tint)
{
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint = addPV(p0, prodVetorC(dr, tint));
    Vetor pintv = subP(v, pint);
    Vetor n = normalizar(vetorial(vetorial(pintv, dc), pintv));
    return n;
}

// Repetição de código do tint com o intersecta pode ser removida usando a mesma solução usada na Malha
double Cone::tInt(Raio r)
{
    double t1 = intersecta_base(r);
    double t2 = intersecta_corpo(r);
    double tint;
    if (t1 == -1 && t2 == -1)
        tint = -1;
    else if (t1 != -1 && t2 == -1)
    {
        tint = t1;
    }
    else if (t2 != -1 && t1 == -1)
    {
        tint = t2;
    }
    else if (t2 <= t1)
    {
        tint = t2;
    }
    else
    {
        tint = t1;
    }
    return tint;
}

Intensidade Cone::intersecta(Raio r, Luz i)
{
    double t1 = intersecta_base(r);
    double t2 = intersecta_corpo(r);
    double tint = -1;
    Vetor n;
    Ponto pint;

    // Ta feito caso a caso saporra, da pra melhorar com certeza.
    if (t1 == -1 && t2 == -1)
        tint = -1;
    else if (t1 != -1 && t2 == -1)
    {
        tint = t1;
        n = prodVetorC(dc, -1);
    }
    else if (t2 != -1 && t1 == -1)
    {
        tint = t2;
        n = normalCorpo(r, tint);
    }
    else if (t2 <= t1)
    {
        tint = t2;
        n = normalCorpo(r, tint);
    }
    else
    {
        tint = t1;
        n = prodVetorC(dc, -1);
    }

    pint = addPV(r.pin, prodVetorC(r.dr, tint));
    return (i.iluminarObjeto(n, pint, r.dr, Ke, Kd, m));
}

double Cone::intersecta_base(Raio r)
{
    Vetor n = dc, w = subP(r.pin, cb), auxiliar;
    Ponto pint;
    double a = innerProd(n, r.dr), tint, tamanho;
    if (a == 0)
    {
        return -1;
    }
    tint = -(innerProd(n, w) / a);
    pint = addPV(r.pin, prodVetorC(r.dr, tint));
    auxiliar = subP(pint, cb);
    tamanho = sqrt(innerProd(auxiliar, auxiliar));
    if ((tamanho < rb))
    {
        return tint;
    }
    return -1;
}

double Cone::intersecta_corpo(Raio r)
{
    Ponto p0 = r.pin, pi;
    Vetor dr = r.dr;
    Vetor v1 = subP(v, p0);
    double cos2, dn, a, b, c, delta, t1, t2, aux, x;
    cos2 = (h * h) / (rb * rb + h * h);
    dn = innerProd(dr, dc);

    a = dn * dn - innerProd(dr, dr) * cos2;
    b = 2 * (innerProd(v1, dr) * cos2 - innerProd(v1, dc) * dn);
    c = innerProd(v1, dc) * innerProd(v1, dc) - innerProd(v1, v1) * cos2;

    delta = (b * b) - (4 * a * c);
    if ((delta < 0) || (a == 0))
        return -1;

    t1 = (-b - sqrt(delta)) / (2 * a);
    t2 = (-b + sqrt(delta)) / (2 * a);

    if (t1 > t2)
        x = t2;
    else
        x = t1;

    if (x > 0)
    {
        pi = addPV(p0, prodVetorC(dr, x));
        aux = innerProd(subP(v, pi), dc);
        if ((aux >= 0) && (aux <= h))
            return x;
    }

    return -1;
}
