#pragma once
#include "alinear.h"

class Canvas {
    public:
    int nLines;
    int nCol;
    Cor bgColor;
    Cor matriz[200][200];
    Canvas();
    Canvas(int nLines, int nCol, Cor bg); 
};