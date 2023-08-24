#include "alinear.h"
#include "raio.h"
#include "esfera.h"
#include "canvas.h"
#include "janela.h"
#include <SDL.h>

// Retorna uma matriz colorida! 
void mainLoop(Ponto observador, Janela janela, Canvas *canvas, Esfera esfera, int dJanela){
    double JyM = janela.JyMax;
    double dy = janela.dY;
    double dx = janela.dX
    int nLin = canvas.nLines;
    int nCol = canvas.nCol;
    double yL;
    double xC;
    Ponto pJ;
    
    for (int l = 0; l < nLin; l++){
        yL = JyM - dy/2 - l*dy;
        for (int c = 0; c < nCol; c++){
            xC = jxMin + dx/2 + c*dx;
            pJ.set(xC, yL, -dJanela); 
            canvas -> matriz[l][c] = raycasting(esfera, canvas, pJ)
            
        }
    }
}

void renderizar(SDL_Renderer* renderer, Canvas canvas){

    int nLin = canvas.nLines;
    int nCol = canvas.nCol;

    SDL_RenderClear(renderer);
    for (int l = 0; l < nLin; l++)
    {
        for (int c = 0; c < nCol; c++)
        {
            Cor r, g, b;
            r = canvas.matriz[l][c].r; // Talvez não esteja certo.
            g = canvas.matriz[l][c].g;
            b = canvas.matriz[l][c].b;
            SDL_SetRenderDrawColor(renderer, r, g, b, 0); // Seta a cor, ignoramos o último parâmetro - RGBA
            SDL_RenderDrawPoint(renderer, l, c); // Pinta propriamante
            
        }
    }
    SDL_RenderPresent(renderer); // Atualizamos com o renderer que acabamos de pintar
}

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