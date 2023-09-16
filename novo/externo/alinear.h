#pragma once 
#include "math.h"


// (1) - Definindo as classes e construtores.

class Intensidade {
    public:
    float r, g, b;
    Intensidade();
    Intensidade(float r, float g, float b);
};

class Vetor{
    public:
    float x, y, z;
    Vetor();
    Vetor(float x, float y, float z);
};

class Ponto{
    public:
    float x, y, z;
    Ponto();
    Ponto(float x, float y, float z);
    void set(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
};

class Cor{
    public:
    float r, g, b;
    Cor();
    Cor(float x, float y, float z);
};

// (2) - Definições de funções úteis

Vetor subP (Ponto p1, Ponto p2);
Vetor subV (Vetor v1, Vetor v2);
Vetor addV (Vetor v1, Vetor v2);
Vetor prodVetorC(Vetor v1, float t);
Vetor divVetorC(Vetor v1, float t);
Ponto addPV(Ponto p1, Vetor v1);
float modulo(Vetor v1);
Vetor normalizar(Vetor v1);
float innerProd(Vetor v1, Vetor v2);
Intensidade arroba(Intensidade i1, Intensidade i2);
Intensidade prodIntC(Intensidade i1, float t);
Intensidade somaI(Intensidade i1, Intensidade i2);
Intensidade make_eye(Intensidade i1, Intensidade i2, Intensidade i3);
Cor prodICor(Intensidade i1, Cor c1);






