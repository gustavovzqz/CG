#include "plano.h"
#include <iostream>
using std::cout;

Plano::Plano() {}
Plano::~Plano() { delete text; }

Plano::Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m)
{
    this->p_pi = p_pi;
    this->n_bar = n_bar;
    this->Ke = Ke;
    this->Ka = Ka;
    this->Kd = Kd;
    this->m = m;
    text = nullptr;
}

Plano::Plano(const std::string path, Ponto p_pi, Vetor n_bar, float m)
{

    this->w = id.x - se.x;
    this->h = se.y - id.y;
    this->text = new Textura{path};
    this->p_pi = p_pi;
    this->n_bar = n_bar;
    this->m = m;
    std::cout << "Construiu!\n";
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
    se = prodMP(m, se);
    id = prodMP(m, id);
    w = id.x - se.x;
    h = se.y - id.y;
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
        Vetor normal = n_bar;
        Vetor piMinusPPI = subP(pint, p_pi);

        if (normal.x != 0 || normal.z != 0)
        {
            double a = (sqrt(pow(normal.x, 2) + pow(normal.z, 2)));
            double alpha = -asin(normal.x / a);
            Vetor normalWithYRotatedY = prodMV(rY(alpha), normal);
            Vetor aux = prodMV(rY(alpha), piMinusPPI);
            piMinusPPI = prodMV(rX(-acos(normalWithYRotatedY.y)), aux);
        }

        int x = piMinusPPI.x;
        int z = piMinusPPI.z;
        int image_w = text->w;
        int image_h = text->h;
        int imageX;
        int imageY;
        if (x == 0)
            imageX = 0;
        if (z == 0)
            imageY = 0;

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
            imageX = abs(z) % image_h;
        }

        Intensidade nova = text->getIntensity(imageX, imageY);
        Ke = nova;
        Ka = nova;
        Kd = nova;
    }

    return (i.iluminarObjeto(n_bar, pint, dr, Ke, Kd, m));
}