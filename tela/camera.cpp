#include "camera.h"

Camera::Camera() {}

Camera::Camera(Ponto e, Ponto up, Ponto at)
{
    Vetor i, j, k, ev;
    this->e = e;
    this->up = up;
    this->at = at;
    k = normalizar(subP(e, at));
    this->e_at = k;
    i = normalizar(vetorial(subP(up, e), k));
    j = vetorial(k, i);
    ev = Vetor(e.x, e.y, e.z, 1);
    this->mc = Matriz{Vetor{i.x, j.x, k.x, 0},
                      Vetor{i.y, j.y, k.y, 0},
                      Vetor{i.z, j.z, k.z, 0},
                      Vetor{-innerProd(i, ev), -innerProd(j, ev), -innerProd(k, ev), 1}};
    this->cm = Matriz(i, j, k, ev);
    this->orto = normalizar(prodMV(mc, subP(at, e)));
}

void Camera::atualizar(Ponto e, Ponto up, Ponto at)
{
    Vetor i, j, k, ev;
    this->e = e;
    this->up = up;
    this->at = at;
    k = normalizar(subP(e, at));
    this->e_at = k;
    i = normalizar(vetorial(subP(up, e), k));
    j = vetorial(k, i);
    ev = Vetor(e.x, e.y, e.z, 1);
    this->mc = Matriz{Vetor{i.x, j.x, k.x, 0},
                      Vetor{i.y, j.y, k.y, 0},
                      Vetor{i.z, j.z, k.z, 0},
                      Vetor{-innerProd(i, ev), -innerProd(j, ev), -innerProd(k, ev), 1}};
    this->cm = Matriz(i, j, k, ev);
    this->orto = normalizar(prodMV(mc, subP(at, e)));
}

void Camera::atualizarDS(Vetor ds)
{

    this->obq = normalizar(ds);
}