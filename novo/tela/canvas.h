#pragma once
#include "../externo/alinear.h"

class Canvas {
    public:
    int nLines;
    int nCol;
    Cor bgColor;
    Cor** matriz;
    Canvas();
    Canvas(int nLines, int nCol, Cor bg); 
};