#pragma once
#include "../objeto/objeto.h"
#include <vector>

class Cenario {
    public:
    std::vector<Objeto*> cena;
    Objeto* escolherObjeto(Raio r);
    bool ehIluminado(Ponto p, Ponto pj, Objeto *obj, Vetor dr);
};
