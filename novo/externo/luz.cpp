#include "luz.h"
#include <cmath>

Luz::Luz(){}

Luz::Luz(Ponto pF, Intensidade iAmb, Intensidade iF){
    this -> pF = pF;
    this -> iAmb = iAmb;
    this -> iF = iF;
}

Cor Luz::iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, Intensidade Ka, float m, Cor cor){
    Intensidade total = Intensidade(0,0,0);

    Vetor l = normalizar(subP(pF, pint)); // L = (pF - pint) / || pF - pint ||
    Vetor r = subV(prodVetorC(n, 2 * innerProd(l,n)), l); // R = 2n(l . n) - l
    Vetor v = prodVetorC(dr, -1); // V = -dr

    float fdif = innerProd(l, n); // Fdif = (l.n)

    float fesp = 0;
    if (innerProd(r, v) > 0)
        fesp = pow(innerProd(v, r)), m); // fesp = (v.r)^m
    
    Intensidade dif = Intensidade(0,0,0); // 
    if (fdif > 0)
        dif = prodIntC(arroba(iF, Kd), fdif);
    
    Intensidade esp = Intensidade(0,0,0);

    if (fesp > 0)
        esp = prodIntC(arroba(iF, Ke), fesp); // (IF @ KE) * KESP

    Intensidade ambiente = arroba(iAmb, Ka); // Iambiente = Ia @ Ka
    Intensidade eye = make_eye(ambiente, dif, esp); // EYE = Iambiente + Idifusa + Iespecular

    
    return prodICor(eye, cor);
}
