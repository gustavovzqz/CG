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
#include "tela/camera.h"
#include <SDL2/SDL.h>

int main()
{
    int dJanela = 30;
    int wJanela = 60;
    int hJanela = 60;
    int nCol = 500;
    int nLin = 500;

    // Iambiente              / IPontual
    Camera cam = Camera(Ponto(0, 0, 0), Ponto(0, 1, 0), Ponto(0, 0, -1));

    // Iambiente              / IPontual
    // Luz(Ponto pF, Intensidade iF, Vetor ds, double alfa);
    Luz luz = Luz(Ponto(0, 0, 0), Intensidade(0.3, 0.3, 0.3), Vetor(0, 0, -1), 0.6);
    Luz luz1 = Luz(Ponto(0, 60, -30), Intensidade(0.5, 0.5, 0.5));
    Luz luz3 = Luz(Intensidade(0.7, 0.7, 0.7), Vetor(0, -1, 0));

    // Intensidades esfera
    Intensidade kd_e = Intensidade(0.7, 0.2, 0.2);
    Intensidade ke_e = Intensidade(0.7, 0.2, 0.2);
    Intensidade ka_e = Intensidade(0.7, 0.2, 0.2);
    // ke ka kd
    Esfera esf = Esfera(Ponto(0, 0, -100), 40, ke_e, ka_e, kd_e, 10);

    // Intensidades Cilindro
    Intensidade kd_ci = Intensidade(0.2, 0.3, 0.8);

    // Direção
    Vetor dc = Vetor(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3));

    Cilindro ci = Cilindro(Ponto(0, 0, -100), dc, 40 / 3, 120, kd_ci, kd_ci, kd_ci, 10);

    // Intensidades plano chao
    Intensidade kd_pc = Intensidade(0.2, 0.7, 0.2);
    Intensidade ke_pc = Intensidade(0.0, 0.0, 0.0);
    Intensidade ka_pc = Intensidade(0.2, 0.7, 0.2);

    Plano chao = Plano(Ponto(0, -40, 0), Vetor(0, 1, 0), ke_pc, ka_pc, kd_pc, 10);

    // Intensidades plano fundo
    Intensidade kd_pf = Intensidade(0.3, 0.3, 0.7);
    Intensidade ke_pf = Intensidade(0.0, 0.0, 0.0);
    Intensidade ka_pf = Intensidade(0.3, 0.3, 0.7);

    // Cone:
    Intensidade k_cone = Intensidade(0.8, 0.3, 0.2);
    // Cone(Ponto cb, double r, Vetor dc, double h, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m);
    Cone con = Cone(ci.ct, 60, dc, 20, k_cone, k_cone, k_cone, 10);

    Plano fundo = Plano(Ponto(0, 0, -200), Vetor(0, 0, 1), ke_pf, ka_pf, kd_pf, 1);

    Canvas c = Canvas(nLin, nCol, Cor(255, 255, 255));
    Janela J = Janela(wJanela, hJanela, c);

    Cenario cenario{Intensidade(0.2, 0.2, 0.2)};
    cenario.cena.push_back(&esf);
    cenario.cena.push_back(&fundo);
    cenario.cena.push_back(&chao);
    cenario.cena.push_back(&ci);
    cenario.cena.push_back(&con);
    cenario.luzes.push_back(&luz3);
    cenario.luzes.push_back(&luz);
    cenario.luzes.push_back(&luz1);

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
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                // Verificar se o evento é um clique do botão esquerdo do mouse
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    cenario.pick(&cam, J, dJanela, y, x);
                }
            }
            // Se o evento for de clique...
        }
        colorirMatriz(cam, J, &c, cenario, dJanela);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}