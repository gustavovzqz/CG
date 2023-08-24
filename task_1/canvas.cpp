#include "canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(int nLines, int nCol, Cor bg) {
    this->nLines = nLines;
    this->nCol = nCol;
    this->bgColor = bg;
    
    // Inicializando a matriz com a cor de fundo
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nCol; j++) {
            matriz[i][j] = bg;  // Defina a cor de fundo em cada célula da matriz
        }
    }
}
