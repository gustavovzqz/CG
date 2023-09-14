#include "iluminacao.h"
#include <iostream>

Iluminacao::Iluminacao() {}

Iluminacao::Iluminacao(Ponto pf, Vetor i_f, Vetor i_a){
    this -> pf = pf;
    this -> i_f = i_f;
    this -> i_a = i_a;
}

Cor Iluminacao::corLuz(Ponto pint, Vetor n, Vetor kDif, Vetor kEsp, Vetor dr){ // Polidez do material?
        Vetor l = normalizar(subP(pf, pint));
        Vetor iDif;
        Vetor iEsp;
        double fDif = innerProd(l, n);
        iDif = prodVetorC(arroba(i_f, kDif), fDif);
        Vetor r = subV(prodVetorC(n, (2 * innerProd(l, n))), l);
        Vetor v = prodVetorC(dr, -1);
        double fEsp = innerProd(v, r);
        iEsp = prodVetorC(arroba(i_f, kEsp), fEsp);
        Cor teste = make_eye(iDif, iEsp, i_a);
        std::cout << "r: " << teste.r << " g: " << teste.g << " b: " << teste.b << std::endl;
        return prodCor(teste, Cor(255,0,0));
}