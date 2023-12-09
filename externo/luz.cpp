#include "luz.h"
#include <cmath>

Luz::Luz() {}

/* Aqui vai ter O tipo Luz
                       Luz pontual
                       Luz spot
                       Luz direcional
                       (Hierarquia de classes)

    Tem um método de iluminação que retorna o Eye sem a ambiente
    O método é comum de todas as classes que herdam luz, mas com uma implementação diferente
    para cada tipo (pontual, spot...)*/
Luz::Luz(Ponto pF, Intensidade iF)
{
    this->pF = pF;
    this->iF = iF;
    ehSpot = false;
    ehPontual = true;
    ehDirecional = false;
}

Luz::Luz(Intensidade iF, Vetor ds)
{
    this->iF = iF;
    this->ds = ds;
    ehSpot = false;
    ehPontual = false;
    ehDirecional = true;
}

Luz::Luz(Ponto pF, Intensidade iF, Vetor ds, double alfa)
{
    this->pF = pF;
    this->iF = iF;
    this->ds = normalizar(ds);
    this->alfa = alfa;
    ehSpot = true;
    ehPontual = false;
    ehDirecional = false;
}

void Luz::alterariF(Intensidade iF)
{
    this->iF = iF;
}

Intensidade Luz::iluminarSpot(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m)
{
    // Precisamos testar antes se intersecta com o objeto ou não.

    Vetor l = normalizar(subP(pF, pint));
    Vetor r = subV(prodVetorC(n, (2 * innerProd(l, n))), l);
    Vetor v = prodVetorC(dr, -1);
    double lds = innerProd(l, ds);
    Intensidade is = prodIntC(iF, -lds);
    Intensidade esp = Intensidade(0, 0, 0);
    double fesp = 0;
    if (innerProd(r, v) > 0)
        fesp = pow((innerProd(r, v)), m);
    if (fesp > 0)
        esp = prodIntC(arroba(is, Ke), fesp);
    // std::cout << fesp << std::endl;

    Intensidade dif = Intensidade(0, 0, 0);

    double fdif = innerProd(l, n);
    if (fdif > 0)
        dif = prodIntC(arroba(is, Kd), fdif);

    // std::cout << "R:" << e.r << " G:" << e.g << " B:" << e.b << '\n';

    return somaI(dif, esp);
}

void Luz::appMatrix(Matriz m)
{
    if (ehDirecional || ehSpot)
    {
        ds = prodMV(m, ds);
    }
    if (ehSpot || ehPontual)
    {
        pF = prodMP(m, pF);
    }
}

Intensidade Luz::iluminarPontual(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m)
{
    // Precisamos testar antes se intersecta com o objeto ou não.

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

    // std::cout << "R:" << e.r << " G:" << e.g << " B:" << e.b << '\n';

    return somaI(dif, esp);
}

Intensidade Luz::iluminarDirecional(Vetor n, Vetor dr, Intensidade Ke, Intensidade Kd, float m)
{
    // Precisamos testar antes se intersecta com o objeto ou não.

    Vetor l = prodVetorC(ds, -1);
    Vetor r = subV(prodVetorC(n, (2 * innerProd(l, n))), l);
    Vetor v = prodVetorC(dr, -1);

    Intensidade esp = Intensidade(0, 0, 0);
    double fesp = 0;
    if (innerProd(r, v) > 0)
        fesp = pow((innerProd(r, v)), m);
    if (fesp >= 0)
        esp = prodIntC(arroba(iF, Ke), fesp);
    // std::cout << fesp << std::endl;

    Intensidade dif = Intensidade(0, 0, 0);

    double fdif = innerProd(l, n);
    if (fdif > 0)
        dif = prodIntC(arroba(iF, Kd), fdif);

    // std::cout << "R:" << e.r << " G:" << e.g << " B:" << e.b << '\n';

    return somaI(dif, esp);
}

Intensidade Luz::iluminarObjeto(Vetor n, Ponto pint, Vetor dr, Intensidade Ke, Intensidade Kd, float m)
{
    if (ehPontual)
        return iluminarPontual(n, pint, dr, Ke, Kd, m);
    if (ehSpot)
        return iluminarSpot(n, pint, dr, Ke, Kd, m);
    if (ehDirecional)
        return iluminarDirecional(n, dr, Ke, Kd, m);

    return Intensidade(0, 0, 0);
}
