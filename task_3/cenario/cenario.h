#pragma once
#include "../objeto/objeto.h"
#include <vector>

class Cenario {
    public:
    std::vector<Objeto*> cena;
    Objeto* escolherObjeto(Raio r);
};