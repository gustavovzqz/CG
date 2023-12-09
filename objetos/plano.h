#pragma once
#include "../objeto/objeto.h"
#include "../tela/textura.h"
#include <string>

class Plano : public Objeto
{
public:
    Textura *text;
    Ponto p_pi, id, se;
    int h, w;
    Vetor n_bar;
    Plano();
    Plano(Ponto p_pi, Vetor n_bar, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Plano(const std::string path, Ponto p_pi, Vetor n_bar, float m);
    Intensidade intersecta(Raio r, Luz i);
    void appMatrix(Matriz m);
    void escalar(double, double, double);
    double tInt(Raio r);
    ~Plano();
};
