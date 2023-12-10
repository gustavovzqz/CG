#include "alinear.h"
#include "iostream"

// (1) - Definição dos construtores

Intensidade::Intensidade() {}
Vetor::Vetor() {}
Ponto::Ponto() {}
Cor::Cor() {}
Aresta::Aresta() {}
Face::Face() {}
Vertice::Vertice() {}
Numero_vetor::Numero_vetor(){};
Matriz::Matriz() {}

Matriz::Matriz(Vetor v1, Vetor v2, Vetor v3, Vetor v4)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v4 = v4;
}

Vetor::Vetor(double x, double y, double z, double h)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->h = h;
}

Vetor::Vetor(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->h = 0;
}
Intensidade::Intensidade(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Ponto::Ponto(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->h = 1;
}

Ponto::Ponto(double x, double y, double z, double h)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->h = h;
}

Cor::Cor(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// (2) - Definições dos métodos "set" para o ponto.

void Ponto::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
};

void Ponto::setX(double x)
{
    this->x = x;
};

void Ponto::setY(double y)
{
    this->y = y;
};

void Ponto::setZ(double z)
{
    this->z = z;
};

// (3) - Declaração dos objetos para a malha
Aresta::Aresta(double id, double v1, double v2)
{
    this->id = id;
    this->v1 = v1;
    this->v2 = v2;
};

Face::Face(int id, int a1, int a2, int a3)
{
    this->id = id;
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
};

Vertice::Vertice(double id, Ponto p)
{
    this->id = id;
    this->p = p;
};

Numero_vetor::Numero_vetor(double num, Vetor v)
{
    this->num = num;
    this->v = v;
};

void Face::setV(Vetor r1, Vetor r2, Vetor n)
{
    this->r1 = r1;
    this->r2 = r2;
    this->n = n;
}

void Face::setCommon(Ponto vc)
{
    this->vc = vc;
}

void Face::setRX(Vetor rx)
{
    this->rx = rx;
}

// (4) - Definições de funções úteis

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

Vetor prodVetorC(Vetor v1, double t)
{
    return Vetor(v1.x * t, v1.y * t, v1.z * t);
}

Vetor divVetorC(Vetor v1, double t)
{
    return Vetor(v1.x / t, v1.y / t, v1.z / t);
}

Ponto addPV(Ponto p1, Vetor v1)
{
    return Ponto(p1.x + v1.x, p1.y + v1.y, p1.z + v1.z);
}

double innerProd(Vetor v1, Vetor v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double modulo(Vetor v1)
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

Intensidade prodIntC(Intensidade i1, double t)
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

// Matrizes ...

Vetor prodMV(Matriz m, Vetor v)
{
    return (Vetor(m.v1.x * v.x + m.v2.x * v.y + m.v3.x * v.z + m.v4.x * v.h,
                  m.v1.y * v.x + m.v2.y * v.y + m.v3.y * v.z + m.v4.y * v.h,
                  m.v1.z * v.x + m.v2.z * v.y + m.v3.z * v.z + m.v4.z * v.h,
                  m.v1.h * v.x + m.v2.h * v.y + m.v3.h * v.z + m.v4.h * v.h));
}

Vetor prodVM(Vetor v, Matriz m)
{

    return Vetor(v.x * m.v1.x + v.y * m.v1.y + v.z * m.v1.z + v.h * m.v1.h,
                 v.x * m.v2.x + v.y * m.v2.y + v.z * m.v2.z + v.h * m.v2.h,
                 v.x * m.v3.x + v.y * m.v3.y + v.z * m.v3.z + v.h * m.v3.h,
                 v.x * m.v4.x + v.y * m.v4.y + v.z * m.v4.z + v.h + m.v4.h);
}

Ponto prodMP(Matriz m, Ponto p)
{
    return Ponto(m.v1.x * p.x + m.v2.x * p.y + m.v3.x * p.z + m.v4.x * p.h,
                 m.v1.y * p.x + m.v2.y * p.y + m.v3.y * p.z + m.v4.y * p.h,
                 m.v1.z * p.x + m.v2.z * p.y + m.v3.z * p.z + m.v4.z * p.h,
                 m.v1.h * p.x + m.v2.h * p.y + m.v3.h * p.z + m.v4.h * p.h);
}

double innerProdV4(Vetor v1, Vetor v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.h * v2.h));
}

Vetor auxMult(Vetor x, Vetor y, Vetor z, Vetor h, Vetor b)
{
    return (Vetor(innerProdV4(x, b), innerProdV4(y, b), innerProdV4(z, b), innerProdV4(h, b)));
}

Matriz prodMM(Matriz m1, Matriz m2)
{
    Vetor x, y, z, h, v1, v2, v3, v4;
    x = Vetor(m1.v1.x, m1.v2.x, m1.v3.x, m1.v4.x);
    y = Vetor(m1.v1.y, m1.v2.y, m1.v3.y, m1.v4.y);
    z = Vetor(m1.v1.z, m1.v2.z, m1.v3.z, m1.v4.z);
    h = Vetor(m1.v1.h, m1.v2.h, m1.v3.h, m1.v4.h);
    v1 = auxMult(x, y, z, h, m2.v1);
    v2 = auxMult(x, y, z, h, m2.v2);
    v3 = auxMult(x, y, z, h, m2.v3);
    v4 = auxMult(x, y, z, h, m2.v4);
    return (Matriz(v1, v2, v3, v4));
}

Matriz id()
{
    return Matriz(Vetor(1, 0, 0, 0), Vetor(0, 1, 0, 0), Vetor(0, 0, 1, 0), Vetor(0, 0, 0, 1));
}

Matriz mT(double tx, double ty, double tz)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(tx, ty, tz, 1));
}

Matriz mE(double sx, double sy, double sz)
{
    return Matriz(Vetor(sx, 0, 0, 0),
                  Vetor(0, sy, 0, 0),
                  Vetor(0, 0, sz, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz rX(double a)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, cos(a), sin(a), 0),
                  Vetor(0, -sin(a), cos(a), 0),
                  Vetor(0, 0, 0, 1));
}

Matriz rY(double a)
{
    return Matriz(Vetor(cos(a), 0, -sin(a), 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(sin(a), 0, cos(a), 0),
                  Vetor(0, 0, 0, 1));
}
Matriz rZ(double a)
{
    return Matriz(Vetor(cos(a), sin(a), 0, 0),
                  Vetor(-sin(a), cos(a), 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Exy()
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, 0, -1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Exz()
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, -1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Eyz()
{
    return Matriz(Vetor(-1, 0, 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Cyx(double gama)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(tan(gama), 1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Cxy(double gama)
{
    return Matriz(Vetor(1, tan(gama), 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Cxz(double gama)
{
    return Matriz(Vetor(1, 0, tan(gama), 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Czx(double gama)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(tan(gama), 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Czy(double gama)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, 1, 0, 0),
                  Vetor(0, tan(gama), 1, 0),
                  Vetor(0, 0, 0, 1));
}

Matriz Cyz(double gama)
{
    return Matriz(Vetor(1, 0, 0, 0),
                  Vetor(0, 1, tan(gama), 0),
                  Vetor(0, 0, 1, 0),
                  Vetor(0, 0, 0, 1));
}

// Quaternions ou o outro.

Matriz Raxis(double x, double y, double z, double ang)
{

    double seno = sin(ang / 2);
    double w = cos(ang / 2); // O ângulo nos cálculos deve ser equivalente a metade.
    x = seno * x;
    y = seno * y;
    z = seno * z;
    double w2 = w * w;
    double x2 = x * x;
    double y2 = y * y;
    double z2 = z * z;
    return Matriz(Vetor(w2 + x2 - y2 - z2, 2 * x * y + 2 * w * z, 2 * x * z - 2 * w * y, 0),
                  Vetor(2 * x * y - 2 * w * z, w2 - x2 + y2 - z2, 2 * y * z + 2 * x * w, 0),
                  Vetor(2 * x * z + 2 * w * y, 2 * y * z - 2 * w * x, w2 - x2 - y2 + z2, 0),
                  Vetor(0, 0, 0, w2 + x2 + y2 + z2));
}