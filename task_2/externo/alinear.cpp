#include "alinear.h"

Vetor::Vetor() {}
Ponto::Ponto() {}
Cor::Cor(){}
Matriz::Matriz(){}

Vetor::Vetor(double a, double b, double c){
    this -> x = a;
    this -> y = b;
    this -> z = c;
}

Ponto::Ponto(double a, double b, double c){
    this -> x = a;
    this -> y = b;
    this -> z = c;
}

Matriz::Matriz(Vetor l1, Vetor l2, Vetor l3){
    this -> l1 = l1;
    this -> l2 = l2;
    this -> l3 = l3;
}

void Ponto::set(double x, double y, double z){
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

void Ponto::setX(double newX) {
    this->x = newX;
}

void Ponto::setY(double newY) {
    this->y = newY;
}

void Ponto::setZ(double newZ) {
    this->z = newZ;
}

Cor::Cor(int a, int b, int c){
    this -> r = a;
    this -> g = b;
    this -> b = c;
}


Vetor subP (Ponto p1, Ponto p2){
    return Vetor(p1.x - p2.x, p1.y - p2.y, p1.z-p2.z);
}

Vetor addV (Vetor v1, Vetor v2){
    return Vetor(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

double innerProd (Vetor v1, Vetor v2){
    return ((v1.x * v2.x ) + (v1.y * v2.y) + (v1.z * v2.z));
}

Vetor prodVetorC (Vetor v1, double t){
    return Vetor(t * v1.x, t * v1.y, t*v1.z);
}

Vetor divVetorC (Vetor v1, double t){
    return Vetor(v1.x / t, v1.y / t, v1.z / t);
}

Vetor subV (Vetor v1, Vetor v2){
    return Vetor(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Ponto addPV (Ponto p1, Vetor v1){
    return Ponto(p1.x + v1.x, p1.y + v1.y, p1.z + v1.z);
}

Matriz prodV(Vetor v1, Vetor v2){ // Multiplica dois vetores e gera uma matriz (um linha e um coluna)
    return Matriz(
    Vetor((v1.x*v2.x),(v1.x*v2.y),(v1.x*v2.z)), 
    Vetor((v1.y*v2.x),(v1.y*v2.y),(v1.y*v2.z)), 
    Vetor((v1.z*v2.x),(v1.z*v2.y),(v1.z*v2.z)));
}

Matriz subM(Matriz m1, Matriz m2){
    return Matriz(
        Vetor(subV(m1.l1,m2.l1)),
        Vetor(subV(m1.l2,m2.l2)),
        Vetor(subV(m1.l3,m2.l3))
    );
}

Vetor prodVM(Vetor v1, Matriz m1){ // Assume que o vetor inserido é do tipo linha
    double x = v1.x * m1.l1.x + v1.y + m1.l2.x + v1.z * m1.l3.x;
    double y = v1.x * m1.l1.y + v1.y + m1.l2.y + v1.z * m1.l3.y;
    double z = v1.x * m1.l1.z + v1.y + m1.l2.z + v1.z * m1.l3.z;
    return Vetor(x, y, z);
}

Vetor arroba(Vetor v1, Vetor v2){
    return(Vetor(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

Cor make_eye(Vetor v1, Vetor v2, Vetor v3){
    return Cor(v1.x + v2.x + v3.x, 
               v1.y + v2.y + v3.y,
               v1.z + v2.z + v3.z);
}

Cor prodCor(Cor c1, Cor c2){
    return Cor(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

Vetor normalizar(Vetor v1){
    return divVetorC(v1, sqrt(innerProd(v1, v1)));
}