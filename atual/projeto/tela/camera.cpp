#include "camera.h"

Camera::Camera() {}

Camera::Camera(Ponto e, Ponto up, Ponto at)
{
    Vetor i, j, k, ev;
    k = normalizar(subP(e, at));
    i = normalizar(vetorial(subP(up, e), k));
    j = vetorial(k, i);
    ev = Vetor(e.x, e.y, e.z, 1);
    this->mc = Matriz(i, j, k, ev);
    this->obs = prodMP(mc, Ponto(0, 0, 0, 1));
}

void Camera::atualizar(Ponto e, Ponto up, Ponto at)
{
    Vetor i, j, k, ev;
    k = normalizar(subP(e, at));
    i = normalizar(vetorial(subP(up, e), k));
    j = vetorial(k, i);
    ev = Vetor(e.x, e.y, e.z);
    this->mc = Matriz(i, j, k, ev);
    this->obs = prodMP(mc, Ponto(0, 0, 0, 1));
}
