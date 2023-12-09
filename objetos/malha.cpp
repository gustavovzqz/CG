#include "malha.h"
#include <iostream>
Malha::Malha() {}

Malha::Malha(Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
}

void Malha::initFace(Face *f)
{
    int idVertice11 = arestas[f->a1]->v1;
    int idVertice12 = arestas[f->a1]->v2;

    int idVertice21 = arestas[f->a2]->v1;
    int idVertice22 = arestas[f->a2]->v2;

    int v1, v2, v3, n1, n;
    n1 = (idVertice11 + 1) * (idVertice12 + 1); // + 1 já que o vetor começa em 0
    n = n1 / (idVertice21 + 1);

    if (n == (idVertice11 + 1) || n == (idVertice12 + 1))
    {
        v1 = idVertice21;
        v2 = idVertice22;
        v3 = n - 1;
    }
    else
    {
        v1 = idVertice22;
        v2 = idVertice21;
        v3 = (n1 / (v1 + 1)) - 1;
    }

    Ponto p1 = vertices[v1]->p;
    Ponto p2 = vertices[v2]->p;
    Ponto p3 = vertices[v3]->p;

    Vetor r1 = subP(p2, p1);
    Vetor r2 = subP(p3, p1);
    Vetor rx = vetorial(r1, r2);
    Vetor normal = normalizar(rx);

    f->setV(r1, r2, normal);
    f->setRX(rx);
    f->setCommon(p1);
}

void Malha::initNormais()
{
    for (Face *f : faces)
    {
        initFace(f);
    }
}

Numero_vetor Malha::tIntaux(Raio r)
{
    Vetor dr = r.dr;
    Ponto p0 = r.pin;
    Vetor n, v, nmin;
    Ponto pint;
    double aux, t1, c1, c2, c3;
    double min = INFINITY;
    for (Face *face : faces)
    {
        n = face->n;
        aux = innerProd(dr, n);
        if (aux < 0)
        {
            t1 = -(innerProd(subP(p0, face->vc), n) / aux);
            if (t1 > 0)
            {
                pint = addPV(p0, prodVetorC(dr, t1));
                v = subP(pint, face->vc);
                aux = innerProd(face->rx, n);
                if (aux != 0)
                {
                    c1 = innerProd(vetorial(v, face->r2), n) / aux;
                    c2 = innerProd(vetorial(face->r1, v), n) / aux;
                    c3 = 1 - c1 - c2;
                    if (c1 >= 0 && c2 >= 0 && c3 >= 0 && t1 < min)
                    {
                        // std::cout << "SOMA:" << (c1 + c2 + c3) << std::endl;
                        // std::cout << "T1:" << t1;

                        min = t1;
                        nmin = n;
                    }
                }
            }
        }
    }
    if (min != INFINITY)
        return Numero_vetor(min, nmin);

    // std::cout << "retornou -1\n";
    return Numero_vetor(-1, Vetor(-1, -1, -1));
}

void Malha::appMatrix(Matriz m)
{

    for (Vertice *v : vertices)
        v->p = prodMP(m, v->p);

    initNormais();
}

void Malha::escalar(double r1, double r2, double r3)
{
    Matriz escala = mE(r1, r2, r3);
    appMatrix(escala);
}
double Malha::tInt(Raio r)
{
    Numero_vetor aux = tIntaux(r);
    return (aux.num);
}

Intensidade Malha::intersecta(Raio r, Luz i)
{
    Numero_vetor tint_n = tIntaux(r);

    Ponto pint = addPV(r.pin, prodVetorC(r.dr, tint_n.num));

    return (i.iluminarObjeto(tint_n.v, pint, r.dr, Ke, Kd, m));
}
