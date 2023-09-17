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