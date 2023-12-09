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
    void escalar(double, double, double);
    Numero_vetor tIntaux(Raio r);
    void appMatrix(Matriz m);
    double tInt(Raio r);
    Intensidade intersecta(Raio r, Luz i);
};
