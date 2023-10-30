#include "alinear.h"

// (1) - Definição dos construtores

Intensidade::Intensidade() {}
Vetor::Vetor() {}
Ponto::Ponto() {}
Cor::Cor() {}
Numero_vetor::Numero_vetor() {}

Numero_vetor::Numero_vetor(double num, Vetor v)
{
    this->num = num;
    this->v = v;
}

Vetor::Vetor(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Intensidade::Intensidade(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Ponto::Ponto(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Cor::Cor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// (2) - Definições dos métodos "set" para o ponto.

void Ponto::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
};

void Ponto::setX(float x)
{
    this->x = x;
};

void Ponto::setY(float y)
{
    this->y = y;
};

void Ponto::setZ(float z)
{
    this->z = z;
};

// (3) - Definições de funções úteis

Vetor subP(Ponto p1, Ponto p2)
{
    return Vetor(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Vetor subV(Vetor v1, Vetor v2)
{
    return Vetor(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vetor addV(Vetor v1, Vetor v2)
{
    return Vetor(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vetor prodVetorC(Vetor v1, float t)
{
    return Vetor(v1.x * t, v1.y * t, v1.z * t);
}

Vetor divVetorC(Vetor v1, float t)
{
    return Vetor(v1.x / t, v1.y / t, v1.z / t);
}

Ponto addPV(Ponto p1, Vetor v1)
{
    return Ponto(p1.x + v1.x, p1.y + v1.y, p1.z + v1.z);
}

float innerProd(Vetor v1, Vetor v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float modulo(Vetor v1)
{
    return sqrt(innerProd(v1, v1));
}

Vetor normalizar(Vetor v1)
{
    return divVetorC(v1, modulo(v1));
}

Intensidade arroba(Intensidade i1, Intensidade i2)
{
    return Intensidade(i1.r * i2.r, i1.g * i2.g, i1.b * i2.b);
}

Intensidade prodIntC(Intensidade i1, float t)
{
    return Intensidade(i1.r * t, i1.g * t, i1.b * t);
}

Intensidade somaI(Intensidade i1, Intensidade i2)
{
    return Intensidade(i1.r + i2.r, i1.g + i2.g, i1.b + i2.b);
}

Cor prodICor(Intensidade i1, Cor c1)
{
    return Cor(i1.r * c1.r, i1.g * c1.g, i1.b * c1.b);
}

Vetor vetorial(Vetor v1, Vetor v2)
{
    return Vetor(v1.y * v2.z - v2.y * v1.z,
                 v2.x * v1.z - v2.z * v1.x,
                 v1.x * v2.y - v2.x * v1.y);
}

Intensidade make_eye(Intensidade i1, Intensidade i2, Intensidade i3)
{
    return Intensidade(i1.r + i2.r + i3.r,
                       i1.g + i2.g + i3.g,
                       i1.b + i2.b + i3.b);
}
