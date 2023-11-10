#pragma once
#include "../externo/alinear.h"

class Camera
{
public:
    Ponto obs;
    Matriz mc;
    Camera();
    Camera(Ponto e, Ponto up, Ponto at);
    void atualizar(Ponto e, Ponto up, Ponto at);
};