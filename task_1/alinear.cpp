#include "alinear.h"

Vetor::Vetor() {}
Ponto::Ponto() {}
Cor::Cor(){}

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

void Ponto::set(double x, double y, double z){
    this -> x = x;
    this -> y = y;
    this -> z = z;
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
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vetor prodVetorC (Vetor v1, double t){
    return Vetor(t * v1.x, t * v1.y, t*v1.z);
}

Vetor divVetorC (Vetor v1, double t){
    return Vetor(t / v1.x, t / v1.y, t / v1.z);
}