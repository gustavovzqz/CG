#include "cenario.h"
#include <cmath>

Cenario::Cenario() {}

Cenario::Cenario(Intensidade newI)
{
    iAmb = newI;
}

Objeto *Cenario::escolherObjeto(Raio r)
{
    double min, t;
    int indice = 0;
    min = INFINITY;
    for (std::vector<Objeto *>::size_type i = 0; i < cena.size(); i++)
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
/* Não vai ter mais isso, vai ser uma função Iluminar Objeto, que simplesmente já itera sobre o objeto
e colore ele corretamente*/
bool Cenario::ehIluminado(Luz l, Ponto pint_objeto, Objeto *obj)
{

    if (l.ehDirecional)
    {
        Ponto p = pint_objeto;

        Raio r = Raio(p, prodVetorC(l.ds, -1));
        double t_objeto = obj->tInt(r);
        for (std::vector<Objeto *>::size_type i = 0; i < cena.size(); i++)
        {
            double t = cena[i]->tInt(r);
            if (t > 0 && t != t_objeto)
            {
                return false;
            }
        }
        return true;
    };

    Ponto p = l.pF;
    Raio r = Raio(p, pint_objeto); // P é ponto de luz e o pint do objeto, formamos o raio de luz
    Vetor le = normalizar(subP(p, pint_objeto));

    if (l.ehSpot)
    {
        double lds = innerProd(le, l.ds);
        if (-lds < cos(l.alfa))
            return false;
    }

    double t_objeto = obj->tInt(r);
    double t;

    for (std::vector<Objeto *>::size_type i = 0; i < cena.size(); i++)
    {

        t = cena[i]->tInt(r);
        if (t < t_objeto && t > 0)
        {
            return false;
        }
    }
    return true;
}

Cor Cenario::iluminarObjeto(Raio raio, Ponto pint_objeto, Objeto *obj, Cor bgColor)
{
    if (obj->tInt(raio) <= 0)
        return bgColor;

    Intensidade intensity{0., 0., 0.};
    for (std::vector<Objeto *>::size_type i = 0; i < luzes.size(); ++i)
    {
        Luz l = *luzes[i];
        if (ehIluminado(l, pint_objeto, obj))
        {
            intensity = somaI(obj->intersecta(raio, l), intensity);
        }
    }
    intensity = somaI(arroba(obj->Ka, iAmb), intensity);

    if (intensity.r > 1)
        intensity.r = 1;
    if (intensity.g > 1)
        intensity.g = 1;
    if (intensity.b > 1)
        intensity.b = 1;

    // std::cout << "R:" << intensity.r << " G:" << intensity.g << " B:" << intensity.b << '\n';

    return prodICor(intensity, Cor(255, 255, 255));
}