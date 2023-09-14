#include "esfera.h"
#include <math.h>

Esfera::Esfera() {}

Esfera::Esfera(Ponto c, double r, Cor cor){
    this -> cEsfera = c;
    this -> rEsfera = r;
    this -> corEsfera = cor;
}



Cor Esfera::intersecta(Raio r, Iluminacao i){
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Vetor w = subP(p0, cEsfera); 
    Ponto pint;
    Vetor nLuz;
    w = prodVetorC(w, -1);
    double bBarra = innerProd(w, dr);
    double c = innerProd(w, w) - (rEsfera * rEsfera);
    double delta = (bBarra * bBarra) - c;
    if (delta >= 0){
        double tint = (-bBarra - sqrt(delta));
        Ponto pint = addPV(p0, prodVetorC(dr, tint));
        nLuz = divVetorC(subP(pint, cEsfera), rEsfera);
        return (i.corLuz(pint, nLuz, Vetor(1,1,1), Vetor(1,1,1), dr)); // TODO: Os 'K' precisa ser um atributo do objeto esfera
    }
    else {
        return Cor(100,100,100); // TODO: Colocar para retornar a cor BG padrão do canvas
    }
}
