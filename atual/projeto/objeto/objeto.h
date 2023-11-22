#pragma once
#include "../externo/alinear.h"
#include "../externo/luz.h"
#include "../ray/raio.h"

class Objeto
{
public: // Podemos adicionar coisas bases ao objeto posteriormente.
    Intensidade Ka, Kd, Ke;
    float m;
    // Não recebe mais é ilumando, não recebe mais luz. Recebe somente CENÁRIO, com uma função nova chamada
    // ilumnar objeto
    virtual Intensidade intersecta(Raio r, Luz i) = 0;
    virtual double tInt(Raio r) = 0;
    virtual void escalar(double r1, double r2, double r3) = 0;
    virtual void appMatrix(Matriz m) = 0;
};
