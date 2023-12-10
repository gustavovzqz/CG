#pragma once
#include "canvas.h"

class Janela
{
public:
    double jyMax;
    double jxMin;
    double wJanela;
    double hJanela;
    double dX;
    double dY;
    Canvas c;
    Janela();
    Janela(double wJanela, double hJanela, Canvas a);
    void update(double wJanela, double hJanela);
};