#include "luz.h"

Luz::Luz(){}

Luz::Luz(Ponto pF, Intensidade iAmb, Intensidade iF){
    this -> pF = pF;
    this -> iAmb = iAmb;
    this -> iF = iF;
}

Cor Luz::iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, Intensidade Ka, double m, Cor cor){
    Intensidade total = Intensidade(0,0,0);

    Vetor l = normalizar(subP(pF, pint));
    Vetor r = subV(prodVetorC(n, 2* innerProd(l,n)), l);
    Vetor v = divVetorC(dr, -modulo(dr));

    double fdif = innerProd(l, n);

    double fesp = 0;
    if (innerProd(r, v) > 0)
        fesp = pow(innerProd(r, v), m);
    
    Intensidade dif = Intensidade(0,0,0);
    if (fdif > 0)
        dif = prodIntC(arroba(iF, Kd), fdif);
    
    Intensidade esp = Intensidade(0,0,0);

    if (fesp > 0)
        esp = prodIntC(arroba(iF, Ke), fesp);

    Intensidade ambiente = arroba(iAmb, Ka);
    Intensidade eye = make_eye(ambiente, dif, esp);
    
    if (eye.r > 1)
        eye.r = 1;
    if (eye.g > 1)
        eye.g = 1;
    if (eye.b > 1)
        eye.b = 1;
    
    return prodICor(eye, cor);
}