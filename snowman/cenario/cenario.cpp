#include "cenario.h"
#include <cmath>

Objeto* Cenario::escolherObjeto(Raio r){
    double min, t;
    int indice = 0;
    min = INFINITY; 
    for (int i = 0; i < cena.size(); i++){
        t = cena[i]->tInt(r);
        if (t < min && t >= 0){
            min = t;
            indice = i;
        }
    }
    return cena[indice];
}

bool Cenario::ehIluminado(Ponto p, Ponto pj, Objeto *obj, Vetor dr){
    Raio r = Raio(p, pj);   

    double t_objeto = obj->tInt(r); 
    double t;
    Ponto pint = addPV(p, prodVetorC(dr, t_objeto));

    Vetor l = prodVetorC(normalizar(subP(p, pint)), -1);

    for (int i = 0; i < cena.size(); i++){
        t = cena[i]->tInt(r);
        if (t < t_objeto && t >= 0){
            return false;
        }
    }
    return true;


}


