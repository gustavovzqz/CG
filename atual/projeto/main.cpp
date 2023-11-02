#include "externo/alinear.h"
#include "ray/raio.h"
#include "objetos/esfera.h"
#include "objetos/cilindro.h"
#include "objetos/cone.h"
#include "tela/canvas.h"
#include "externo/luz.h"
#include "tela/janela.h"
#include "externo/renderizar.h"
#include "objetos/plano.h"
#include "objetos/malha.h"
#include "objetos/teste.h"
#include <SDL2/SDL.h>

int main()
{
    int dJanela = 30;
    int wJanela = 60;
    int hJanela = 60;
    int nCol = 600;
    int nLin = 600;
    // Iambiente              / IPontual
    Luz luz = Luz(Ponto(0, 0, -30), Intensidade(0.3, 0.3, 0.3), Intensidade(0.7, 0.7, 0.7));
    Ponto pObs = Ponto(0, 0, 0);

    // Intensidades esfera
    Intensidade kd_e = Intensidade(1, 1, 1);
    Intensidade ke_e = Intensidade(0.2, 0.2, 0.2);
    Intensidade ka_e = Intensidade(1, 1, 1);
    // ke ka kd
    Esfera b1 = Esfera(Ponto(0, -10, -100), 28, ke_e, ka_e, kd_e, 10);
    Esfera b2 = Esfera(Ponto(0, 30, -100), 20, ke_e, ka_e, kd_e, 10);

    // Intensidades Cilindro
    Intensidade kd_ci = Intensidade(0.2, 0.3, 0.8);

    Cilindro chapeu = Cilindro(Ponto(0, 40, -100), Ponto(0, 42, -100), 20, kd_ci, kd_ci, kd_ci, 10);
    Cilindro chapeu2 = Cilindro(Ponto(0, 42, -100), Ponto(0, 60, -100), 14, kd_ci, kd_ci, kd_ci, 10);

    // Olhos
    Intensidade ko = Intensidade(0.3, 0.3, 0.3);
    Esfera o1 = Esfera(Ponto(7, 30, -81), 2.5, ko, ko, ko, 10);
    Esfera o2 = Esfera(Ponto(-7, 30, -81), 2.5, ko, ko, ko, 10);

    // Nariz
    Intensidade kn = Intensidade(0.7, 0.2, 0.2);

    Cone nariz = Cone(Ponto(0, 25, -80), 3, Ponto(0, 30, -74), kn, kn, kn, 10);

    // Botões
    Intensidade bn = Intensidade(0.2, 0.7, 0.2);

    Esfera bt1 = Esfera(Ponto(0, -10, -72), 2.5, bn, bn, bn, 10);
    Esfera bt2 = Esfera(Ponto(0, -20, -74), 2.5, bn, bn, bn, 10);
    Esfera bt3 = Esfera(Ponto(0, -0, -72), 2.5, bn, bn, bn, 10);

    // Intensidades plano chao
    Intensidade kd_pc = Intensidade(0.2, 0.7, 0.2);
    Intensidade ke_pc = Intensidade(0.0, 0.0, 0.0);
    Intensidade ka_pc = Intensidade(0.2, 0.7, 0.2);

    Plano chao = Plano(Ponto(-120, -60, 0), Vetor(0, 1, 0), ke_pc, ka_pc, kd_pc, 10);

    // Intensidades plano fundo
    Intensidade kd_pf = Intensidade(0.3, 0.3, 0.7);
    Intensidade ke_pf = Intensidade(0.0, 0.0, 0.0);
    Intensidade ka_pf = Intensidade(0.3, 0.3, 0.7);

    Plano fundo = Plano(Ponto(0, 0, -200), Vetor(0, 0, 1), ke_pf, ka_pf, kd_pf, 1);

    Canvas c = Canvas(nLin, nCol, Cor(255, 255, 255));
    Janela J = Janela(wJanela, hJanela, c);
    Cenario cenario;
    Teste tst = Teste(40, Ponto(0, -80, -100), kn, kn, kn, 10);
    cenario.cena.push_back(&fundo);
    cenario.cena.push_back(&chao);

    cenario.cena.push_back(&tst);
    cenario.cena.push_back(&b1);
    cenario.cena.push_back(&b2);
    cenario.cena.push_back(&chapeu);
    cenario.cena.push_back(&chapeu2);
    cenario.cena.push_back(&o1);
    cenario.cena.push_back(&o2);
    cenario.cena.push_back(&nariz);
    cenario.cena.push_back(&bt1);
    cenario.cena.push_back(&bt2);
    cenario.cena.push_back(&bt3);

    // ------ Comandos SDL para inicializar a tela -------------

    bool isRunning = true; // variável de controle do loop
    SDL_Event event;       // variável para checar os eventos da janela
    // Inicializar a biblioteca para poder usar suas funções

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Não foi possível inicializar o SDL! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    // Criar uma janela
    SDL_Window *window = SDL_CreateWindow(
        "CG I - Raycaster",      // Título da Janela
        SDL_WINDOWPOS_UNDEFINED, // Posição inicial X
        SDL_WINDOWPOS_UNDEFINED, // Posição inicial Y
        nCol,                    // Largura da janela em pixels
        nLin,                    // Altura da janela em pixels
        SDL_WINDOW_SHOWN         // Flags
    );

    if (!window)
    {
        SDL_Log("Criação da janela falhou! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Criação do renderer falhou! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
        // Luz luz = Luz(Ponto(0, k, 0), Intensidade(0.2,0.2,0.2), Intensidade(0.7,0.7,0.7));
        // k+=3;
        colorirMatriz(pObs, J, &c, cenario, dJanela, luz);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}