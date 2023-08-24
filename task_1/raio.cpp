#include "raio.h"
#include "alinear.h"
#include "math.h"

Raio::Raio() {}

Raio::Raio(Ponto pin, Ponto pr){
    this -> pin = pin;
    this -> dr = divVetorC(subP(pr, pin), sqrt(innerProd(subP(pr, pin), subP(pr, pin))));

}

bool intersecta(Raio r, Esfera e){
    Vetor w = subP(r.pin, e.cEsfera);
    double bBarra = innerProd(w, r.dr);
    double c = innerProd(w, w) - (e.rEsfera * e.rEsfera);
    double delta = bBarra * bBarra - c;
    return (delta >= 0);
    }

Cor raycasting(Esfera esf, Canvas c, Ponto pj, Ponto obs){
    Raio a = Raio(obs, pj);
    if (intersecta(a, esf))
        return esf.corEsfera;
    else 
        return c.bgColor;
}