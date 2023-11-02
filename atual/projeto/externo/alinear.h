#pragma once
#include "math.h"

// (1) - Definindo as classes e construtores.

class Intensidade
{
public:
    float r, g, b;
    Intensidade();
    Intensidade(float r, float g, float b);
};

class Vetor
{
public:
    float x, y, z;
    Vetor();
    Vetor(float x, float y, float z);
};

class Ponto
{
public:
    float x, y, z;
    Ponto();
    Ponto(float x, float y, float z);
    void set(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
};

class Numero_vetor
{
public:
    double num;
    Vetor v;
    Numero_vetor();
    Numero_vetor(double num, Vetor v);
};

class Cor
{
public:
    float r, g, b;
    Cor();
    Cor(float x, float y, float z);
};

class Vertice
{
public:
    int id;
    Ponto p;
    Vertice();
    Vertice(double id, Ponto p);
};

class Aresta
{
public:
    int id, v1, v2;
    Aresta();
    Aresta(double id, double v1, double v2);
};

class Face
{
public:
    int id, a1, a2, a3;
    Vetor r1, r2, rx, n;
    Ponto vc;
    Face();
    Face(int id, int a1, int a2, int a3);
    void setRX(Vetor rx);
    void setCommon(Ponto vc);
    void setV(Vetor r1, Vetor r2, Vetor n);
};

// (2) - Definições de funções úteis

Vetor subP(Ponto p1, Ponto p2);
Vetor subV(Vetor v1, Vetor v2);
Vetor addV(Vetor v1, Vetor v2);
Vetor prodVetorC(Vetor v1, float t);
Vetor divVetorC(Vetor v1, float t);
Vetor vetorial(Vetor v1, Vetor v2);
Ponto addPV(Ponto p1, Vetor v1);
float modulo(Vetor v1);
Vetor normalizar(Vetor v1);
float innerProd(Vetor v1, Vetor v2);
Intensidade arroba(Intensidade i1, Intensidade i2);
Intensidade prodIntC(Intensidade i1, float t);
Intensidade somaI(Intensidade i1, Intensidade i2);
Intensidade make_eye(Intensidade i1, Intensidade i2, Intensidade i3);
Cor prodICor(Intensidade i1, Cor c1);
