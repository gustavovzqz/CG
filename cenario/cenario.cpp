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
    alterarObjeto(obj, cam);
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

void Cenario::alterarCenario(Camera *cam, int &djanela)
{
    int escolha;
    cout << "O que deseja alterar no cenário?\n";
    cout << "1 - Alterar câmera\n2 - Alterar luzes\n";
    cin >> escolha;
    if (escolha == 1)
    {
        cout << "1- Mudar o ponto de vista\n2- Alterar distância focal\n3- Pontos salvos\n";
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
        else if (escolha == 3)
        {
            int choice = 0;
            Ponto e, vup, lookat;
            cout << "1- Lateral snowman\n2- Câmera\n3- Traseira snowman\n4- Luminária\n5- Teto\n6- Quina\n";
            cin >> choice;
            if (choice == 1)
            {
                e = Ponto(100, 300, 600);
                vup = Ponto(100, 301, 600);
                lookat = Ponto(101, 300, 600);
            }
            else if (choice == 2)
            {
                e = Ponto(600, 280, 286);
                vup = Ponto(600, 281, 286);
                lookat = Ponto(600, 280, 287);
            }
            else if (choice == 3)
            {
                e = Ponto(600, 300, 1100);
                vup = Ponto(600, 301, 1100);
                lookat = Ponto(600, 300, 1099);
            }
            else if (choice == 4)
            {
                e = Ponto(600, 600, 300);
                vup = Ponto(600, 601, 300);
                lookat = Ponto(600, 600, 301);
            }
            else if (choice == 5)
            {
                e = Ponto(600, 670, 600);
                vup = Ponto(601, 670, 600);
                lookat = Ponto(600, 180, 600);
            }
            else if (choice == 6)
            {
                e = Ponto(1, 300, 1);
                vup = Ponto(1, 301, 1);
                lookat = Ponto(2, 300, 2);
            }
            atualizarCenarioCM(*cam);
            cam->atualizar(e, vup, lookat);
            atualizarCenarioMC(*cam);
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

void Cenario::alterarObjeto(Objeto *obj, Camera *cam)
{
    int escolha;
    cout << "Objeto selecionado!\n";
    cout << "Menu de alteração:\n1- Aplicar matriz\n2- Alterar propriedades\n";
    cin >> escolha;
    if (escolha == 2)
    {
        Intensidade ka, ke, kd;
        cout << "Insira o Ka:\n";
        ka = receberIntensidade();
        cout << "Insira o Ke:\n";
        ke = receberIntensidade();
        cout << "Insira o Kd:\n";
        kd = receberIntensidade();
        obj->Ka = ka;
        obj->Ke = ke;
        obj->Kd = kd;
    }
    else if (escolha == 1)
    {
        int choice;
        cout << "1- Rotação\n2- Escala\n3- Cisalhamento\n4- Espelho\n5- Translação\n";
        cin >> choice;
        if (choice == 1)
        {
            int n;
            double angulo;
            cout << "Insira o eixo de rotação:\n";
            cout << "1- X\n2- Y\n3- Z\n4- Arbitrário\n";
            cin >> n;
            cout << "Insira o ângulo: ";
            cin >> angulo;
            if (n == 1)
            {
                atualizarCenarioCM(*cam);
                obj->appMatrix(rX(angulo));
                atualizarCenarioMC(*cam);
            }
            else if (n == 2)
            {
                atualizarCenarioCM(*cam);
                obj->appMatrix(rY(angulo));
                atualizarCenarioMC(*cam);
            }
            else if (n == 3)
            {
                atualizarCenarioCM(*cam);
                obj->appMatrix(rZ(angulo));
                atualizarCenarioMC(*cam);
            }

            else if (n == 4)
            {
                double x, y, z;
                cout << "Insira o eixo: (x, y, z)\n";
                cin >> x;
                cin >> y;
                cin >> z;
                atualizarCenarioCM(*cam);
                obj->appMatrix(Raxis(x, y, z, angulo));
                atualizarCenarioMC(*cam);
            }
        }
        else if (choice == 2)
        {
            double fx, fy, fz;
            cout << "Insira o fator de escala em X, Y e Z\n";
            cin >> fx;
            cin >> fy;
            cin >> fz;
            atualizarCenarioCM(*cam);
            obj->appMatrix(mE(fx, fy, fz));
            atualizarCenarioMC(*cam);
        }
        else if (choice == 3)
        {
            double gama;
            int opt;
            Matriz m = id();
            cout << "Insira o gama pra cisalhamento: ";
            cin >> gama;
            cout << "1- yx\n2- xy\n3- xz\n4- zx\n5- zy\n";
            cin >> opt;
            switch (opt)
            {
            case 1:
                m = Cyx(gama);
                break;
            case 2:
                m = Cxy(gama);
                break;
            case 3:
                m = Cxz(gama);
                break;
            case 4:
                m = Czx(gama);
                break;
            case 5:
                m = Czy(gama);
                break;
            default:
                break;
            }
            atualizarCenarioCM(*cam);
            obj->appMatrix(m);
            atualizarCenarioMC(*cam);
        }
        else if (choice == 4)
        {
            int opt;
            Matriz m = id();
            cout << "Insira o plano espelho:\n";
            cout << "1- xy\n2- xz\n3- yz\n";
            cin >> opt;
            if (opt == 1)
            {
                m = Exy();
            }
            else if (opt == 2)
            {
                m = Exz();
            }
            else if (opt == 3)
            {
                m = Eyz();
            }
            atualizarCenarioCM(*cam);
            obj->appMatrix(m);
            atualizarCenarioMC(*cam);
        }

        else if (choice == 5)
        {
            double fx, fy, fz;
            cout << "Insira o fator de translação em (x, y, z): ";
            cin >> fx;
            cin >> fy;
            cin >> fz;
            atualizarCenarioCM(*cam);
            obj->appMatrix(mT(fx, fy, fz));
            atualizarCenarioMC(*cam);
        }
    }
}
