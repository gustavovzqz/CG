#pragma once
#include "alinear.h"
#include "esfera.h"
#include "canvas.h"

class Raio {
    public:
    Ponto pin;
    Vetor dr;
    Raio();
    Raio(Ponto pin, Ponto pr);
};


bool intersecta(Raio r, Esfera e);

// Posteriormente a Esfera será substituida por uma classe objeto.
Cor raycasting(Esfera esf, Canvas c, Ponto pj);