#pragma once
#include "alinear.h"

class Iluminacao{
    public:
    Ponto pf; // Fonte pontual
    Vetor i_f; // Intensidade luminosa
    Vetor i_a; // Iluminação ambiente
    Iluminacao();
    Iluminacao(Ponto pf, Vetor i_f, Vetor i_a);
    Cor corLuz(Ponto pint, Vetor n, Vetor kDif, Vetor kEsp, Vetor dr);
};