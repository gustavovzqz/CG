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
    int rEsfera = 7;
    int wJanela = 60;
    int hJanela = 60;
    int nCol = 500;
    int nLin = 500;
                                  // Iambiente              / IPontual
    Luz luz = Luz(Ponto(0, 0, 0), Intensidade(0,0,0), Intensidade(0.7,0.7,0.7));
    Ponto cJanela = Ponto(0, 0, -dJanela);
    Ponto pObs = Ponto(0, 0, 0);
    Intensidade kd = Intensidade(1, 1, 1);
    Intensidade ke = Intensidade(1, 1, 1);
    Intensidade ka = Intensidade(0.1, 0.1, 0.1);
    
    Esfera esf2 = Esfera(Ponto(0, 10, -(dJanela + rEsfera)), rEsfera, Cor(255, 255, 255), ke, ke, ke, 10);
    Esfera esf = Esfera(Ponto(0, 0, -(dJanela + rEsfera)), rEsfera, Cor(255, 255, 255), ke, ke, ke, 10);
    Esfera esf3 = Esfera(Ponto(0, -10, -(dJanela + rEsfera)), rEsfera, Cor(255, 255, 255), ke, ke, ke, 10);
    Esfera olho1 = Esfera(Ponto(2.5, 10, -(dJanela + rEsfera)+7), 1, Cor(0, 0, 0), ke, ke, ke, 10);
    Esfera olho2 = Esfera(Ponto(-2.5, 10, -(dJanela + rEsfera)+7), 1, Cor(0, 0, 0), ke, ke, ke, 10);

    Canvas c = Canvas(nLin, nCol, Cor(50, 50, 50));
    Janela J = Janela(wJanela, hJanela, c);

    Cenario cenario;
    cenario.cena.push_back(&esf);
    cenario.cena.push_back(&esf2);
    cenario.cena.push_back(&esf3);
    cenario.cena.push_back(&olho1);
    cenario.cena.push_back(&olho2);









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
        colorirMatriz(pObs, J, &c, cenario, dJanela, luz);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
        }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}