#include "alinear.h"
#include "raio.h"
#include "esfera.h"
#include "canvas.h"
#include "janela.h"
#include "renderizar.h"
#include <SDL2/SDL.h>


int main(int argc, char* argv[]){
    int dJanela = 3000; // Se tender ao infinito remove a distorção do movimento
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
        nCol,                           // Largura da janela em pixels
        nLin,                            // Altura da janela em pixels
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
        colorirMatriz(pObs, J, &c, esf, dJanela);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}

