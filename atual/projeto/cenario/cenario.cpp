#include "cenario.h"
#include <iostream>
#include <cmath>
using namespace std;

Cenario::Cenario() {}

Cenario::Cenario(Intensidade newI)
{
    iAmb = newI;
}

Objeto *Cenario::escolherObjeto(Raio r)
{
    double min, t;
    int indice = -1;
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
    if (indice == -1)
        return nullptr;
    return cena[indice];
}

void Cenario::atualizarCenarioMC(Camera cam)
{
    for (Objeto *obj : cena)
    {
        obj->appMatrix(cam.mc);
    }

    for (Luz *luz : luzes)
    {
        luz->appMatrix(cam.mc);
    }
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

void Cenario::pick(Camera *cam, Janela janela, int dJanela, int l, int c)
{
    Ponto obs{0, 0, 0};
    float JyM = janela.jyMax;
    float jxMin = janela.jxMin;
    float dy = janela.dY;
    float dx = janela.dX;
    Raio raio;
    float yL;
    float xC;
    Ponto pJ;
    Objeto *obj;

    yL = JyM - dy / 2 - l * dy;
    xC = jxMin + dx / 2 + c * dx;
    pJ = Ponto(xC, yL, -dJanela);
    raio = Raio(obs, pJ);
    // Arrumar depois para se não tiver objeto
    obj = escolherObjeto(raio);
    if (obj == nullptr)
    {
        cout << "Nenhum objeto foi selecionado.\n";
        return;
    }
    alterarObjeto(obj);
    // Se for um nullptr a gente não faz nada, dá um aviso. Apartir daqui a gente trata:
    // Funão fazer alguma coisa com o objeto
}

void Cenario::alterarObjeto(Objeto *obj)
{
    int escolha;
    cout << "Objeto selecionado!\n";
    cout << "Menu de alteração:\n1 - Aplicar matriz\n2 - Alterar propriedades\n";
    obj->appMatrix(Cxy(tan(35)));
};