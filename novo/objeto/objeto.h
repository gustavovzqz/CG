#pragma once 
#include "../externo/alinear.h"
#include "../externo/luz.h"
#include "../ray/raio.h"

class Objeto {
    public: // Podemos adicionar coisas bases ao objeto posteriormente.
    Intensidade Ka, Kd, Ke;
    double m;
    virtual Cor intersecta(Raio r, Luz i, Cor bgColor) = 0;
    virtual Vetor makeN(Ponto pint, Vetor dr) = 0;
};
