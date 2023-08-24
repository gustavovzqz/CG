#pragma once
#include "math.h"

class Vetor{
    public:
    double x, y, z;
    Vetor();
    Vetor(double x, double y, double z);
};

class Ponto{
    public:
    double x, y, z;
    Ponto();
    Ponto(double x, double y, double z);
};


class Cor{
    public:
    int x, y, z;
    Cor();
    Cor(int x, int y, int z);
};


Vetor subP (Ponto p1, Ponto p2);
Vetor addV (Vetor v1, Vetor v2);
double innerProd (Vetor v1, Vetor v2);
Vetor prodVetorC (Vetor v1, double t);
Vetor divVetorC (Vetor v1, double t);


