#include "alinear.h"
#include "raio.h"
#include "esfera.h"
#include "canvas.h"
#include "janela.h"
#include <iostream>
#include <SDL2/SDL.h>

// Retorna uma matriz colorida! 
void colorirMatriz(Ponto obs, Janela janela, Canvas *canvas, Esfera esfera, int dJanela){
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
            canvas -> matriz[l][c] = raycasting(esfera, *canvas, pJ, obs);
            
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
            int r, g, b;
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
    int rEsfera = 40;
    int wJanela = 200;
    int hJanela = 200;
    int nLin = 200;
    int nCol = 200;

    Ponto cJanela = Ponto(0, 0, -dJanela);
    Ponto pObs = Ponto(0, 0, 0);
    Esfera esf = Esfera(Ponto(0, 0, -(dJanela + rEsfera)), rEsfera, Cor(255, 255, 0));
    Canvas c = Canvas(nLin, nCol, Cor(150, 150, 255));
    Janela J = Janela(wJanela, hJanela, c);

    colorirMatriz(pObs, J, &c, esf, dJanela);

    bool isRunning = true; //variável de controle do loop
    SDL_Event event; //variável para checar os eventos da janela
 // Inicializar a biblioteca para poder usar suas funções

    


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Não foi possível inicializar o SDL! SDL_Error: %s", SDL_GetError());
        return 1;
    }

     // Criar uma janela
    SDL_Window* window = SDL_CreateWindow(
        "CG I - Raycaster",       // Título da Janela
        SDL_WINDOWPOS_UNDEFINED,        // Posição inicial X
        SDL_WINDOWPOS_UNDEFINED,        // Posição inicial Y
        200,                           // Largura da janela em pixels
        200,                            // Altura da janela em pixels
        SDL_WINDOW_SHOWN                // Flags
    );

     if (!window) {
        SDL_Log("Criação da janela falhou! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Criação do renderer falhou! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (isRunning){
     while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
    }
SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

