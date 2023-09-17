#pragma once
#include "canvas.h"

class Janela {
    public:
    double jyMax;
    double jxMin; 
    double wJanela;
    double hJanela;
    double dX;
    double dY;
    Janela();
    Janela(double wJanela, double hJanela, Canvas a);

};