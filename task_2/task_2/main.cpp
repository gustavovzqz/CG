#include "externo/alinear.h"
#include "ray/raio.h"
#include "objetos/esfera.h"
#include "tela/canvas.h"
#include "externo/luz.h"
#include "tela/janela.h"
#include "externo/renderizar.h"
#include <SDL2/SDL.h>


int main(int argc, char* argv[]){
    int dJanela = 30; // Se tender ao infinito remove a distorção do movimento
    int rEsfera = 50;
    int wJanela = 60;
    int hJanela = 60;
    int nCol = 500;
    int nLin = 500;
                                  // Iambiente              / IPontual
    Luz luz = Luz(Ponto(0, 5, 0), Intensidade(0,0,0), Intensidade(0.7,0.7,0.7));
    Ponto cJanela = Ponto(0, 0, -dJanela);
    Ponto pObs = Ponto(0, 0, 0);
    Intensidade kd = Intensidade(1, 1, 1);
    Intensidade ke = Intensidade(0.7, 0.2, 0.2);
    Intensidade ka = Intensidade(0.1, 0.1, 0.1);

    Esfera esf = Esfera(Ponto(0, 0, -(dJanela + rEsfera)), rEsfera, Cor(255, 0, 0), ke, ke, ke, 10);
    Canvas c = Canvas(nLin, nCol, Cor(100, 100, 100));
    Janela J = Janela(wJanela, hJanela, c);







// ------ Comandos SDL para inicializar a tela -------------



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
        }    
        colorirMatriz(pObs, J, &c, esf, dJanela, luz);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
        }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}