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
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint;
    double c, b, t;
    double tam_c, tam_b, tam_t, tint = -1;
    double tam = INFINITY;
    c = intersecta_corpo(r);
    b = intersecta_base(r);
    t = intersecta_tampa(r);
    tam_c = modulo(subP(addPV(p0, prodVetorC(dr, c)), p0));
    tam_b = modulo(subP(addPV(p0, prodVetorC(dr, b)), p0));
    tam_t = modulo(subP(addPV(p0, prodVetorC(dr, t)), p0));

    if (b != -1 && tam_b < tam)
    {
        tam = tam_b;
        tint = b;
    }

    if (t != -1 && tam_t < tam)
    {
        tam = tam_t;
        tint = t;
    }

    if (c != -1 && tam_c < tam)
    {
        tam = tam_c;
        tint = c;
    }
    return tint;
}

Vetor Cilindro::normalCorpo(Raio r, double tint)
{
    Vetor v, pv, n;
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
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
    double tam_c, tam_b, tam_t, tint;
    double tam = INFINITY;
    Vetor n;
    c = intersecta_corpo(r);
    b = intersecta_base(r);
    t = intersecta_tampa(r);
    tam_c = modulo(subP(addPV(p0, prodVetorC(dr, c)), p0));
    tam_b = modulo(subP(addPV(p0, prodVetorC(dr, b)), p0));
    tam_t = modulo(subP(addPV(p0, prodVetorC(dr, t)), p0));

    if (b != -1 && tam_b < tam)
    {
        tam = tam_b;
        tint = b;
        n = prodVetorC(dr, -1);
    }

    if (t != -1 && tam_t < tam)
    {
        tam = tam_t;
        tint = t;
        n = dr;
    }

    if (c != -1 && tam_c < tam)
    {
        tam = tam_c;
        tint = c;
        n = normalCorpo(r, c);
    }

    if (tint < 0)
        return bgColor;

    pint = addPV(p0, prodVetorC(dr, tint));
    return (i.iluminarObjeto(n, pint, dr, Ke, Kd, Ka, m, ehiluminado));
}

double Cilindro::intersecta_corpo(Raio r)
{
    Ponto p0 = r.pin;
    Vetor w = subP(p0, cb);
    Vetor dr = r.dr;
    double aux;
    double tint;
    double a = innerProd(dr, dr) - (innerProd(dr, dc) * innerProd(dr, dc));
    if (a == 0)
    { // TEM COMO INTERSECTAR, DPS VE SE PRECISA
        // não é uma equação do segundo grau...
        return -1;
    }
    double b = 2 * innerProd(w, dr) - (2 * innerProd(w, dc) * innerProd(dr, dc));
    double c = innerProd(w, w) - (innerProd(w, dc) * innerProd(w, dc)) - (rc * rc);
    double delta = b * b - 4 * a * c;
    if (delta >= 0)
    {
        double t1 = (-sqrt(delta) - b) / (2 * a);
        double t2 = (sqrt(delta) - b) / (2 * a);
        if (t1 < t2)
            tint = t1;
        else
            tint = t2;
        if (tint > 0)
        {
            Ponto pint = addPV(p0, prodVetorC(dr, tint));
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
    if ((tamanho <= rc))
    {
        return tint;
    }
    return -1;
}

double Cilindro::intersecta_tampa(Raio r)
{
    Vetor n = dc;
    Vetor w = subP(r.pin, ct);
    double a = innerProd(n, r.dr);
    if (a == 0)
    {
        return -1;
    }
    double tint = -(innerProd(n, w) / a);
    Ponto pint = addPV(r.pin, prodVetorC(r.dr, tint));
    Vetor auxiliar = subP(pint, ct);
    double tamanho = sqrt(innerProd(auxiliar, auxiliar));
    if ((tamanho <= rc))
    {
        return tint;
    }
    return -1;
}