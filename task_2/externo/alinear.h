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
    void set(double x, double y, double z);
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);
};

class Matriz {
    public:
    Vetor l1, l2, l3;
    Matriz();
    Matriz(Vetor l1, Vetor l2, Vetor l3);

};


class Cor{
    public:
    int r, g, b;
    Cor();
    Cor(int x, int y, int z);
};

Ponto addPV (Ponto p1, Vetor v1);
Vetor subP (Ponto p1, Ponto p2);
Vetor addV (Vetor v1, Vetor v2);
double innerProd (Vetor v1, Vetor v2);
Vetor prodVetorC (Vetor v1, double t);
Vetor divVetorC (Vetor v1, double t);
Matriz prodV(Vetor v1, Vetor v2);
Matriz subM(Matriz m1, Matriz m2);
Vetor prodVM(Vetor v1, Matriz m1);
Vetor arroba(Vetor v1, Vetor v2);
Vetor subV (Vetor v1, Vetor v2);
Cor make_eye(Vetor v1, Vetor v2, Vetor v3);
Cor prodCor(Cor c1, Cor c2);
Vetor normalizar(Vetor v1);

