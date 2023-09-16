#pragma once 
#include "math.h"


// (1) - Definindo as classes e construtores.

class Intensidade {
    public:
    double r, g, b;
    Intensidade();
    Intensidade(double r, double g, double b);
};

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
    void setX(double x);
    void setY(double y);
    void setZ(double z);
};

class Cor{
    public:
    double r, g, b;
    Cor();
    Cor(double x, double y, double z);
};

// (2) - Definições de funções úteis

Vetor subP (Ponto p1, Ponto p2);
Vetor subV (Vetor v1, Vetor v2);
Vetor addV (Vetor v1, Vetor v2);
Vetor prodVetorC(Vetor v1, double t);
Vetor divVetorC(Vetor v1, double t);
Ponto addPV(Ponto p1, Vetor v1);
double modulo(Vetor v1);
Vetor normalizar(Vetor v1);
double innerProd(Vetor v1, Vetor v2);
Intensidade arroba(Intensidade i1, Intensidade i2);
Intensidade prodIntC(Intensidade i1, double t);
Intensidade somaI(Intensidade i1, Intensidade i2);
Intensidade make_eye(Intensidade i1, Intensidade i2, Intensidade i3);
Cor prodICor(Intensidade i1, Cor c1);






