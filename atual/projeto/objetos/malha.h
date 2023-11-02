#pragma once
#include <vector>
#include "../objeto/objeto.h"
class Malha : public Objeto
{
public:
    std::vector<Vertice *> vertices;
    std::vector<Aresta *> arestas;
    std::vector<Face *> faces;
    Malha();
    Malha(Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    void initFace(Face *f);
    void initNormais();
    Numero_vetor tIntaux(Raio r);
    double tInt(Raio r);
    Cor intersecta(Raio r, Luz i, Cor bgColor, bool ehiluminado) override;
};
