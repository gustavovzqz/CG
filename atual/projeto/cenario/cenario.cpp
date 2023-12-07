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

void Cenario::atualizarCenarioCM(Camera cam)
{
    for (Objeto *obj : cena)
    {
        obj->appMatrix(cam.cm);
    }

    for (Luz *luz : luzes)
    {
        luz->appMatrix(cam.cm);
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

    Intensidade Ka;

    Intensidade intensity{0., 0., 0.};
    for (std::vector<Objeto *>::size_type i = 0; i < luzes.size(); ++i)
    {
        Luz l = *luzes[i];
        if (ehIluminado(l, pint_objeto, obj))
        {
            intensity = somaI(obj->intersecta(raio, l), intensity);
        }
    }
    obj->intersecta(raio, *luzes[0]);
    Ka = obj->Ka;
    intensity = somaI(arroba(Ka, iAmb), intensity);

    if (intensity.r > 1)
        intensity.r = 1;
    if (intensity.g > 1)
        intensity.g = 1;
    if (intensity.b > 1)
        intensity.b = 1;

    // std::cout << "R:" << intensity.r << " G:" << intensity.g << " B:" << intensity.b << '\n';

    return prodICor(intensity, Cor(255, 255, 255));
}

void Cenario::pick(Janela janela, int dJanela, int l, int c)
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

Ponto receberPonto()
{
    double x, y, z;
    cout << "Insira o X: ";
    cin >> x;
    cout << "Insira o Y: ";
    cin >> y;
    cout << "Insira o Z: ";
    cin >> z;
    return Ponto(x, y, z);
}

Intensidade receberIntensidade()
{
    double r, g, b;
    cout << "r: ";
    cin >> r;
    cout << "g: ";
    cin >> g;
    cout << "b: ";
    cin >> b;
    return Intensidade(r, g, b);
}

void Cenario::alterarCenario(Camera *cam, Janela janela, int &djanela)
{
    int escolha;
    cout << "O que deseja alterar no cenário?\n";
    cout << "1 - Alterar câmera\n2 - Alterar luzes\n";
    cin >> escolha;
    if (escolha == 1)
    {
        cout << "1- Mudar o ponto de vista\n2- Alterar distância focal\n";
        cin >> escolha;
        if (escolha == 1)
        {
            cout << "Insira o eye point:\n";
            Ponto e = receberPonto();
            cout << "Insira o view up:\n";
            Ponto vup = receberPonto();
            cout << "Insira o look at:\n";
            Ponto lookat = receberPonto();
            atualizarCenarioCM(*cam);
            cam->atualizar(e, vup, lookat);
            atualizarCenarioMC(*cam);
        }
        else if (escolha == 2)
        {
            cout << "Insira a nova distância focal: ";
            cin >> djanela;
        }
    }
    else if (escolha == 2)
    {
        int indice = 0;
        cout << "Escolha o índice da luz a ser alterada: ";
        cout << "\n0- Luz na lâmpada\n1- Luz spot\n2- Luz pontual lâmpada\n3- Luz ambiente\n: ";
        cin >> indice;
        cout << "Escolha os novos parâmetros para a luz:\n";

        Intensidade k = receberIntensidade();
        if (indice == 3)
            iAmb = k;
        else
            luzes[indice]->alterariF(k);
    }
}

void Cenario::alterarObjeto(Objeto *obj)
{
    int escolha;
    cout << "Objeto selecionado!\n";
    cout << "Menu de alteração:\n1 - Aplicar matriz\n2 - Alterar propriedades\n";
};