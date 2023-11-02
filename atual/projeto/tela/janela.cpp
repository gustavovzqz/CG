#include "janela.h"

Janela::Janela() {}

Janela::Janela(double wJanela, double hJanela, Canvas c)
{
    // Talvez seja preciso determinar o CENTRO da janela. Isso será preciso mesmo?
    this->jyMax = hJanela / 2;
    this->jxMin = -(wJanela / 2);
    this->wJanela = wJanela;
    this->hJanela = hJanela;
    this->dX = wJanela / c.nCol;
    this->dY = hJanela / c.nLines;
}