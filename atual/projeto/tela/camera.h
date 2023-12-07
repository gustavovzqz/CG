#pragma once
#include "../externo/alinear.h"

class Camera
{
public:
    Matriz mc;
    Matriz cm;
    Camera();
    Camera(Ponto e, Ponto up, Ponto at);
    void atualizar(Ponto e, Ponto up, Ponto at);
};