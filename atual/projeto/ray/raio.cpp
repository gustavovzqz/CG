#include "raio.h"
Raio::Raio() {}

Raio::Raio(Ponto pin, Vetor dr)
{
    this->pin = pin;
    this->dr = dr;
}

Raio::Raio(Ponto pin, Ponto pr)
{
    this->pin = pin;
    this->dr = normalizar(subP(pr, pin));
}