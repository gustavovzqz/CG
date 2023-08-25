#include "raio.h"
#include "alinear.h"
#include "math.h"
#include <iostream>

Raio::Raio() {}

Raio::Raio(Ponto pin, Ponto pr){
    this -> pin = pin;
    this -> dr = subP(pr, Ponto(0,0,0)); // que porra é essa
    // divVetorC(subP(pr, pin), sqrt(innerProd(subP(pr, pin), subP(pr, pin))));

}

bool intersecta(Raio r, Esfera e){
    Vetor w = subP(r.pin, e.cEsfera);
    double a = innerProd(r.dr, r.dr);
    std:: cout << "TEM QUE SER UM : " << a << std :: endl;
    double b = 2 * innerProd(w, r.dr);
    std:: cout << "Raio da esfera: " << e.rEsfera << std :: endl;
    double c = innerProd(w, w) - (e.rEsfera * e.rEsfera);
    double delta = b * b - 4 * a * c;
     std::cout << "b: " << b << " c: " << c << " delta: " << delta << std::endl;
     return (delta >= 0);
}

Cor raycasting(Esfera esf, Canvas c, Ponto pj, Ponto obs){
    Raio a = Raio(obs, pj);
    if (intersecta(a, esf))
        return esf.corEsfera;
    else 
        return c.bgColor;
}