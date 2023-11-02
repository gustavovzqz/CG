#include "cilindro.h"
#include <cmath>
#include <iostream>

Cilindro::Cilindro() {}

Cilindro::Cilindro(Ponto cb, Ponto ct, double r, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->cb = cb;
    this->ct = ct;
    this->rc = r;
    Vetor altura = subP(ct, cb);
    this->h = modulo(altura);
    this->dc = normalizar(altura);
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

Cilindro::Cilindro(Ponto cb, Vetor dc, double rc, double h, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->cb = cb;
    this->dc = dc;
    this->rc = rc;
    this->h = h;
    this->ct = addPV(cb, prodVetorC(dc, h));
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

double Cilindro::tInt(Raio r)
{
    double c, b, t, tint = INFINITY;
    c = intersecta_corpo(r);
    b = intersecta_base(r);
    t = intersecta_tampa(r);

    if (b != -1 && b < tint)
    {
        tint = b;
    }

    if (t != -1 && t < tint)
    {
        tint = t;
    }

    if (c != -1 && c < tint)
    {
        tint = c;
    }
    if (tint == INFINITY)
        return -1;
    return tint;
}

Vetor Cilindro::normalCorpo(Raio r, double tint)
{
    Vetor v, pv, n;
    Ponto pint = addPV(r.pin, prodVetorC(r.dr, tint));
    v = subP(pint, cb);
    pv = prodVetorC(dc, innerProd(v, dc));
    n = divVetorC(subV(v, pv), rc);

    return n;
}

Cor Cilindro::intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado)
{
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint;
    double c, b, t;
    double tint = INFINITY;
    Vetor n;
    c = intersecta_corpo(r);
    b = intersecta_base(r);
    t = intersecta_tampa(r);

    if (b != -1 && b < tint)
    {
        tint = b;
        n = prodVetorC(dr, -1);
    }

    if (t != -1 && t < tint)
    {
        tint = t;
        n = dr;
    }

    if (c != -1 && c < tint)
    {
        tint = c;
        n = normalCorpo(r, c);
    }

    if (tint < 0 || tint == INFINITY)
        return bgColor;

    pint = addPV(p0, prodVetorC(dr, tint));
    return (i.iluminarObjeto(n, pint, dr, Ke, Kd, Ka, m, ehiluminado));
}

double Cilindro::intersecta_corpo(Raio r)
{
    Ponto p0 = r.pin, pint;
    Vetor w = subP(p0, cb);
    Vetor dr = r.dr;
    double aux, tint, a, b, c, delta, t1, t2;
    a = innerProd(dr, dr) - (innerProd(dr, dc) * innerProd(dr, dc));
    if (a == 0)
    { // TEM COMO INTERSECTAR, DPS VE SE PRECISA
        // não é uma equação do segundo grau...
        return -1;
    }
    b = 2 * innerProd(w, dr) - (2 * innerProd(w, dc) * innerProd(dr, dc));
    c = innerProd(w, w) - (innerProd(w, dc) * innerProd(w, dc)) - (rc * rc);
    delta = b * b - 4 * a * c;
    if (delta >= 0)
    {
        t1 = (-sqrt(delta) - b) / (2 * a);
        t2 = (sqrt(delta) - b) / (2 * a);
        if (t1 < t2)
            tint = t1;
        else
            tint = t2;
        if (tint > 0)
        {
            pint = addPV(p0, prodVetorC(dr, tint));
            aux = innerProd(subP(pint, cb), dc);

            if (aux >= 0 && aux <= h)
            {
                // std::cout << tint << std::endl;
                return tint;
            }
            return -1;
        }
        return -1;
    }
    return -1;
}

double Cilindro::intersecta_base(Raio r)
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
    if ((tamanho <= rc))
    {
        return tint;
    }
    return -1;
}

double Cilindro::intersecta_tampa(Raio r)
{
    Vetor n = dc, w = subP(r.pin, ct), auxiliar;
    Ponto pint;
    double a = innerProd(n, r.dr), tint, tamanho;
    if (a == 0)
    {
        return -1;
    }
    tint = -(innerProd(n, w) / a);
    pint = addPV(r.pin, prodVetorC(r.dr, tint));
    auxiliar = subP(pint, ct);
    tamanho = sqrt(innerProd(auxiliar, auxiliar));
    if ((tamanho <= rc))
    {
        return tint;
    }
    return -1;
}