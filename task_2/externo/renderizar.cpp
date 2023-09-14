#include "renderizar.h"

// Retorna uma matriz colorida! 
void colorirMatriz(Ponto obs, Janela janela, Canvas *canvas, Esfera cl, int dJanela, Iluminacao i){ // Posteriormente passaremos o objeto Cenário
    double JyM = janela.jyMax;
    double jxMin = janela.jxMin;
    double dy = janela.dY;
    double dx = janela.dX;
    int nLin = canvas->nLines;
    int nCol = canvas->nCol;
    double yL;
    double xC;
    Ponto pJ;
    
    for (int l = 0; l < nLin; l++){
        yL = JyM - dy/2 - l*dy;
        for (int c = 0; c < nCol; c++){
            xC = jxMin + dx/2 + c*dx;
            pJ.set(xC, yL, -dJanela); 
            canvas -> matriz[l][c] = cl.intersecta(Raio(obs, pJ), i); // Esfera será uma lista de objetos (cenário)
            
        }
    }
}

// Usa a matriz de cores para exibir a imagem na tela usando o SDL
void renderizar(SDL_Renderer* renderer, Canvas canvas){ 

    int nLin = canvas.nLines;
    int nCol = canvas.nCol;

    SDL_RenderClear(renderer);
    for (int l = 0; l < nLin; l++)
    {
        for (int c = 0; c < nCol; c++)
        {
            int r, g, b;
            r = canvas.matriz[l][c].r;
            g = canvas.matriz[l][c].g;
            b = canvas.matriz[l][c].b;
            SDL_SetRenderDrawColor(renderer, r, g, b, 0); // Seta a cor, ignoramos o último parâmetro - RGBA
            SDL_RenderDrawPoint(renderer, c, l); // Pinta propriamante
            
        }
    }
    SDL_RenderPresent(renderer); // Atualizamos com o renderer que acabamos de pintar
}
