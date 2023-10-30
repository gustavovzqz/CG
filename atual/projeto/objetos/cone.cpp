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
    if (innerProd(n, dr) > 0)
        return prodVetorC(n, -1);
    return n;
}
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

Cor Cone::intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado)
{
    double t1 = intersecta_base(r);
    double t2 = intersecta_corpo(r);
    double tint = -1;
    Vetor n;
    Ponto pint;

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

    if (tint == -1)
    {
        return bgColor;
    }

    pint = addPV(r.pin, prodVetorC(r.dr, tint));
    return (i.iluminarObjeto(n, pint, r.dr, Ke, Kd, Ka, m, ehiluminado));
}

double Cone::intersecta_base(Raio r)
{
    Vetor n = dc;
    Vetor w = subP(r.pin, cb);
    double a = innerProd(n, r.dr);
    if (a == 0)
    {
        return -1;
    }
    double tint = -(innerProd(n, w) / a);
    Ponto pint = addPV(r.pin, prodVetorC(r.dr, tint));
    Vetor auxiliar = subP(pint, cb);
    double tamanho = sqrt(innerProd(auxiliar, auxiliar));
    if ((tamanho < rb))
    {
        return tint;
    }
    return -1;
}

double Cone::intersecta_corpo(Raio r)
{
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Vetor v1 = subP(v, p0);
    double cos2 = (h * h) / (rb * rb + h * h);
    double dn = innerProd(dr, dc);

    double a = dn * dn - innerProd(dr, dr) * cos2;
    double b = 2 * (innerProd(v1, dr) * cos2 - innerProd(v1, dc) * dn);
    double c = innerProd(v1, dc) * innerProd(v1, dc) - innerProd(v1, v1) * cos2;

    double delta = (b * b) - (4 * a * c);
    if ((delta < 0) || (a == 0))
        return -1;

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);

    double aux;
    double x;

    if (t1 > t2)
        x = t2;
    else
        x = t1;

    Ponto pi;

    if (x > 0)
    {
        pi = addPV(p0, prodVetorC(dr, x));
        aux = innerProd(subP(v, pi), dc);
        if ((aux >= 0) && (aux <= h))
            return x;
    }

    return -1;
}
