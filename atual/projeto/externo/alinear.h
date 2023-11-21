#pragma once
#include <cmath>

// (1) - Definindo as classes e construtores.

class Intensidade
{
public:
    double r, g, b;
    Intensidade();
    Intensidade(double r, double g, double b);
};

class Vetor
{
public:
    double x, y, z, h;
    Vetor();
    Vetor(double x, double y, double z);
    Vetor(double x, double y, double z, double h);
};

class Ponto
{
public:
    double x, y, z, h;
    Ponto();
    Ponto(double x, double y, double z);
    Ponto(double x, double y, double z, double h);
    void set(double x, double y, double z);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
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
    double r, g, b;
    Cor();
    Cor(double x, double y, double z);
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

class Matriz
{
public:
    Vetor v1, v2, v3, v4; // Vamos assumir que os vetores são vetores colunas... (abstratamente)
    Matriz();
    Matriz(Vetor v1, Vetor v2, Vetor v3, Vetor v4);
};

// (2) - Definições de funções úteis

// Funções básicas PONTO VETOR
Vetor subP(Ponto p1, Ponto p2);
Vetor subV(Vetor v1, Vetor v2);
Vetor addV(Vetor v1, Vetor v2);
Vetor prodVetorC(Vetor v1, double t);
Vetor divVetorC(Vetor v1, double t);
Vetor vetorial(Vetor v1, Vetor v2);
Ponto addPV(Ponto p1, Vetor v1);
double modulo(Vetor v1);
Vetor normalizar(Vetor v1);
double innerProd(Vetor v1, Vetor v2);

// Funções básicas INTENSIDADE e COR
Intensidade arroba(Intensidade i1, Intensidade i2);
Intensidade prodIntC(Intensidade i1, double t);
Intensidade somaI(Intensidade i1, Intensidade i2);
Intensidade make_eye(Intensidade i1, Intensidade i2, Intensidade i3);
Cor prodICor(Intensidade i1, Cor c1);

// Funções básicas operações com matrizes
Vetor prodVM(Vetor v, Matriz m);
Vetor prodMV(Matriz m, Vetor v);
Ponto prodMP(Matriz m, Ponto p);
Matriz prodMM(Matriz m1, Matriz m2);

// Declarando propriamente as matrizes

Matriz mE(double sx, double xy, double sz);
Matriz mT(double tx, double ty, double tz);
Matriz rX(double a);
Matriz rY(double a);
Matriz rZ(double a);
Matriz Exz();
Matriz Eyz();
Matriz Exy();
Matriz Cxy(double gama);
Matriz Cyx(double gama);
Matriz Czx(double gama);
Matriz Cxz(double gama);
Matriz Cyz(double gama);
Matriz Czy(double gama);

Matriz id();