#pragma once
#include "../objeto/objeto.h"
#include "../externo/luz.h"
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
};

// TODO: colocar construtor do cenário para iAmb...