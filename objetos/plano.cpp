#include "plano.h"
#include <iostream>
using std::cout;

Plano::Plano() {}
Plano::~Plano() { delete text; }

Plano::Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->vText = Vetor(0,0,0);
    this->p_pi = p_pi;
    this->n_bar = n_bar;
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
    text = nullptr;
}

Plano::Plano(const std::string path, Ponto p_pi, Vetor n_bar, Vetor vText, float m)
{

    this->vText = vText;
    this->vX = vetorial(n_bar, vText);
    this->vY = vText; 
    this->text = new Textura{path};
    this->p_pi = p_pi;
    this->n_bar = n_bar;
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
    vText = prodMV(m, vText);
    vX = prodMV(m, vX);
    vY = prodMV(m, vY);
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

    if (text)
    {
        Vetor piMinusPPI = subP(pint, p_pi);

        int x = innerProd(vX, piMinusPPI);
        int z = innerProd(vY, piMinusPPI);
        int image_w = text->w;
        int image_h = text->h;
        int imageY = 0; 
        int imageX = 0;
       
        if (x < 0)
        {
            imageX = image_w - (abs(x) % image_w);
        }
        else if (x > 0)
        {
            imageX = abs(x) % image_w;
        }

        if (z < 0)
        {
            imageY = image_h - (abs(z) % image_h);
        }
        else if (z > 0)
        {
            imageY = abs(z) % image_h;
        }

        Intensidade nova = text->getIntensity(imageX, imageY);
        Ke = nova;
        Ka = nova;
        Kd = nova;
    }

    return (i.iluminarObjeto(n_bar, pint, dr, Ke, Kd, m));
}