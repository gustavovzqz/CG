#include "alinear.h"
#include "raio.h"
#include "esfera.h"
#include "canvas.h"
#include "janela.h"

int main(int argc, char* argv[]){
    int dJanela = 3000;
    int rEsfera = 100;
    int wJanela = 200;
    int hJanela = 200;
    int nLin = 200;
    int nCol = 200;

    Ponto cJanela = Ponto(0, 0, -dJanela);
    Ponto pObs = Ponto(0, 0, 0);
    Esfera esf = Esfera(Ponto(0, 0, -(dJanela + rEsfera)), rEsfera, Cor(255, 0, 0));
    Canvas c = Canvas(nLin, nCol, Cor(100, 100, 100));
    Janela J = Janela(wJanela, hJanela, c);
}