#include "cenario.h"
#include <cmath>

Objeto *Cenario::escolherObjeto(Raio r)
{
    double min, t;
    int indice = 0;
    min = INFINITY;
    for (int i = 0; i < cena.size(); i++)
    {
        t = cena[i]->tInt(r);
        if (t < min && t >= 0)
        {
            min = t;
            indice = i;
        }
    }
    return cena[indice];
}

bool Cenario::ehIluminado(Ponto p, Ponto pint_objeto, Objeto *obj)
{
    Raio r = Raio(p, pint_objeto); // P é ponto de luz e o pint do objeto, formamos o raio de luz

    double t_objeto = obj->tInt(r);
    double t;

    for (int i = 0; i < cena.size(); i++)
    {
        t = cena[i]->tInt(r);
        if (t < t_objeto && t > 0)
        {
            return false;
        }
    }
    return true;
}