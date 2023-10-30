#include "luz.h"
#include <cmath>
#include <iostream>

Luz::Luz() {}

Luz::Luz(Ponto pF, Intensidade iAmb, Intensidade iF)
{
    this->pF = pF;
    this->iAmb = iAmb;
    this->iF = iF;
}

Cor Luz::iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, Intensidade Ka, float m, bool ehiluminado)
{
    Cor max_cor = Cor(255, 255, 255);
    Intensidade ambiente = arroba(iAmb, Ka);

    // Precisamos testar antes se intersecta com o objeto ou não.
    if (ehiluminado)
    {
        Vetor l = normalizar(subP(pF, pint));
        Vetor r = subV(prodVetorC(n, (2 * innerProd(l, n))), l);
        Vetor v = prodVetorC(dr, -1);

        Intensidade esp = Intensidade(0, 0, 0);
        double fesp = 0;
        if (innerProd(r, v) > 0)
            fesp = pow((innerProd(r, v)), m);
        if (fesp > 0)
            esp = prodIntC(arroba(iF, Ke), fesp);
        // std::cout << fesp << std::endl;

        Intensidade dif = Intensidade(0, 0, 0);

        double fdif = innerProd(l, n);
        if (fdif > 0)
            dif = prodIntC(arroba(iF, Kd), fdif);

        Intensidade eye = make_eye(ambiente, dif, esp);
        // Truncando
        if (eye.r > 1)
            eye.r = 1;
        if (eye.g > 1)
            eye.g = 1;
        if (eye.b > 1)
            eye.b = 1;

        return prodICor(eye, max_cor);
    }
    return prodICor(ambiente, max_cor);
}