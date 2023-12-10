#pragma once
#include "../externo/alinear.h"

class Camera
{
public:
    Vetor obq;
    Vetor orto;
    Matriz mc;
    Matriz cm;
    Ponto e, up, at;
    Vetor e_at;
    Camera();
    Camera(Ponto e, Ponto up, Ponto at);
    void atualizar(Ponto e, Ponto up, Ponto at);
    void atualizarDS(Vetor ds);
};