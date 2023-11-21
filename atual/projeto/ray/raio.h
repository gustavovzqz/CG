#pragma once
#include "../externo/alinear.h"
#include "../tela/canvas.h"

class Raio
{
public:
    Ponto pin;
    Vetor dr;
    Raio();
    Raio(Ponto pin, Ponto pr);
    Raio(Ponto pin, Vetor dr);
};