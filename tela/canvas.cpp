#include "canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(int nLines, int nCol, Cor bg)
{
    this->nLines = nLines;
    this->nCol = nCol;
    this->bgColor = bg;
    matriz = new Cor *[nLines];
    for (int i = 0; i < nLines; i++)
    {
        matriz[i] = new Cor[nCol];
    }
}