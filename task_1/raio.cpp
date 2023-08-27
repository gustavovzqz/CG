#include "raio.h"
Raio::Raio() {}

Raio::Raio(Ponto pin, Ponto pr){
    this -> pin = pin;
    Vetor a = subP(pr, pin);
    this -> dr = divVetorC(a, sqrt(innerProd(a, a)));

}

bool intersecta(Raio r, Esfera e){
    Vetor w = subP(r.pin, e.cEsfera);
    double a = innerProd(r.dr, r.dr);
    double b = 2 * innerProd(w, r.dr);
    double c = innerProd(w, w) - (e.rEsfera * e.rEsfera);
    double delta = b * b - 4 * a * c;
    return (delta >= 0);
}

Cor raycasting(Esfera esf, Canvas c, Ponto pj, Ponto obs){
    Raio a = Raio(obs, pj);
    if (intersecta(a, esf))
        return esf.corEsfera;
    else 
        return c.bgColor;
}