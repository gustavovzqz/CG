#pragma once
#include "../objeto/objeto.h"
#include "../externo/luz.h"
#include "../tela/janela.h"
#include "../tela/camera.h"
#include <vector>

class Cenario
{
public:
    Intensidade iAmb;
    std::vector<Objeto *> cena;
    std::vector<Luz *> luzes;
    Objeto *escolherObjeto(Raio r);
    bool ehIluminado(Luz l, Ponto pj, Objeto *obj);
    Cenario();
    Cenario(Intensidade iAmb);
    Cor iluminarObjeto(Raio r, Ponto pint_objeto, Objeto *obj, Cor bgColor);
    void pick(Camera *cam, Janela janela, int djanela, int x, int y, int &opt);
    void alterarCenario(Camera *cam, Janela *j, int &djanela, int &opt);
    void atualizarCenarioMC(Camera cam);
    void atualizarCenarioCM(Camera cam);

private:
    void alterarObjeto(Objeto *obj, Camera *cam);
};
