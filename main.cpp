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
#include "objetos/cubo.h"
#include "tela/camera.h"
#include <SDL2/SDL.h>

#include <iostream>
using namespace std;

int main()
{
    int dJanela = 30;
    int wJanela = 60;
    int hJanela = 60;
    int nCol = 500;
    int nLin = 500;

    // Posição inicial da câmera.
    // Camera cam = Camera(Ponto(600, 300, 100), Ponto(600, 301, 100), Ponto(600, 300, 101));
    // Camera cam = Camera(Ponto(600, 700, 600), Ponto(601, 700, 600), Ponto(600, 180, 600));
    Camera cam = Camera(Ponto(600, 280, 286), Ponto(600, 281, 286), Ponto(600, 280, 287));

    // Camera cam = Camera(Ponto(600, 400, 1100), Ponto(600, 401, 1100), Ponto(600, 400, 1099));

    Luz luz_na_lampada = Luz(Ponto(600, 670, 600), Intensidade(0.9, 0.9, 0.1), Vetor(0, 1, 0), 0.53);
    Luz luz_da_lampada = Luz(Ponto(600, 670, 600), Intensidade(0.5, 0.5, 0.1), Vetor(0, -1, 0), 0.35);
    Luz luz_pontual_lampada = Luz(Ponto(600, 620, 600), Intensidade(0.1, 0.1, 0.1));
    Luz spot_camera = Luz(Ponto(600, 265, 286), Intensidade(0.4, 0.4, 0.2), Vetor(0, 0, 1), 0.35);

    // DEFINIÇÃO DOS PLANOS (PAREDE / CHÃO / TETO)
    // Plano chao = Plano("assets/concreto.png", Ponto(0, 0, 0), Vetor(0, 1, 0), 1);
    Intensidade i_chao{0.4, 0.4, 0.4};
    Plano chao = Plano(Ponto(0, 0, 0), Vetor(0, 1, 0), i_chao, i_chao, i_chao, 3);

    Plano fundo = Plano("assets/tijolos.png", Ponto(0, 0, 1200), Vetor(0, 0, -1), 10);
    Plano frente = Plano("assets/tijolos.png", Ponto(0, 0, 0), Vetor(0, 0, 1), 10);
    Plano parede_esq = Plano("assets/tijolos.png", Ponto(0, 0, 0), Vetor(1, 0, 0), 10);
    Plano parede_dir = Plano("assets/tijolos.png", Ponto(1200, 0, 0), Vetor(-1, 0, 0), 10);
    Plano teto = Plano("assets/tijolos.png", Ponto(0, 800, 0), Vetor(0, -1, 0), 10);

    // LUMINÁRIA NO TETO
    Intensidade k_lum = Intensidade(0.3, 0.3, 0.3);
    Cilindro cabo_luminaria = Cilindro(Ponto(600, 800, 600), Ponto(600, 760, 600), 4, k_lum, k_lum, k_lum, 10);
    Cone luminaria = Cone(Ponto(600, 700, 600), 35, Ponto(600, 770, 600), k_lum, k_lum, k_lum, 10);
    Intensidade k_luz = Intensidade(1, 1, 1);
    Esfera lampada = Esfera(Ponto(600, 700, 600), 15, k_luz, k_luz, k_luz, 1);

    // Cadeira
    Intensidade k_cadeira{0.5, 0.3, 0};
    Cubo perna1 = Cubo(23, Ponto(650, 50, 650), k_cadeira, k_cadeira, k_cadeira, 1);
    perna1.appMatrix(mE(1, 5, 1));
    perna1.appMatrix(mT(0, -250, 0));
    Cubo perna2 = Cubo(23, Ponto(650, 50, 550), k_cadeira, k_cadeira, k_cadeira, 1);
    perna2.appMatrix(mE(1, 5, 1));
    perna2.appMatrix(mT(0, -250, 0));
    Cubo perna3 = Cubo(23, Ponto(550, 50, 650), k_cadeira, k_cadeira, k_cadeira, 1);
    perna3.appMatrix(mE(1, 5, 1));
    perna3.appMatrix(mT(0, -250, 0));
    Cubo perna4 = Cubo(23, Ponto(550, 50, 550), k_cadeira, k_cadeira, k_cadeira, 1);
    perna4.appMatrix(mE(1, 5, 1));
    perna4.appMatrix(mT(0, -250, 0));
    Cubo base = Cubo(124, Ponto(600, 100, 600), k_cadeira, k_cadeira, k_cadeira, 1);
    base.appMatrix(mE(1, 0.1, 1));
    base.appMatrix(mT(0, 100, 0));
    Cubo encosto = Cubo(124, Ponto(600, 160, 650), k_cadeira, k_cadeira, k_cadeira, 1);
    encosto.appMatrix(mE(1, 1.3, 0.1));
    encosto.appMatrix(mT(0, -95, 590));

    // Sdowbem na cadeira
    Intensidade sdow{1, 1, 1};
    Esfera bola1 = Esfera(Ponto(600, 170, 590), 53, sdow, sdow, sdow, 10);
    Esfera bola2 = Esfera(Ponto(600, 230, 590), 46, sdow, sdow, sdow, 10);
    Esfera bola3 = Esfera(Ponto(600, 290, 590), 40, sdow, sdow, sdow, 10);

    Intensidade i_c{0.2, 0.2, 0.2};
    Cilindro bcartola = Cilindro(Ponto(600, 320, 590), Ponto(600, 330, 590), 42, i_c, i_c, i_c, 10);
    Cilindro cartola = Cilindro(Ponto(600, 330, 590), Ponto(600, 380, 590), 30, i_c, i_c, i_c, 10);
    Intensidade i_f{0.7, 0, 0};
    Cilindro faixa = Cilindro(Ponto(600, 330, 590), Ponto(600, 340, 590), 31, i_f, i_f, i_f, 10);

    Intensidade olho{0, 0, 0};
    Esfera olho1 = Esfera(Ponto(585, 295, 565), 13, olho, olho, olho, 20);
    Esfera olho2 = Esfera(Ponto(615, 295, 565), 13, olho, olho, olho, 20);

    Intensidade i_nariz{0.8, 0.5, 0.2};
    // Cone nariz = Cone(Ponto(600, 290, 555), 8, Ponto(600, 280, 520), i_nariz, i_nariz, i_nariz, 10); //
    Cilindro nariz = Cilindro(Ponto(600, 290, 555), Ponto(600, 290, 530), 4, i_nariz, i_nariz, i_nariz, 10); //

    Intensidade k_chicol{1, 0.3, 0.3};
    Cilindro cachecol = Cilindro(Ponto(600, 260, 590), Ponto(600, 276, 590), 40, k_chicol, k_chicol, k_chicol, 10);

    Esfera botao1 = Esfera(Ponto(600, 245, 547), 6, olho, olho, olho, 20);

    Esfera botao2 = Esfera(Ponto(600, 215, 547), 6, olho, olho, olho, 20);

    Esfera botao3 = Esfera(Ponto(600, 180, 538), 6, olho, olho, olho, 20);

    // Ambiente sequestro
    Intensidade k_butija{1, 0, 0};
    Cilindro butijao = Cilindro(Ponto(600, 0, 200), Ponto(600, 240, 200), 100, k_butija, k_butija, k_butija, 2);
    Intensidade k_cam{0.5, 0.5, 0.5};
    Cubo cam_seq = Cubo(50, Ponto(600, 240, 250), k_cam, k_cam, k_cam, 10);
    Cilindro cam_cabo = Cilindro(Ponto(600, 265, 275), Ponto(600, 265, 285), 15, olho, olho, olho, 10);

    Intensidade k_galpao{0.1, 0.3, 0.1};
    Cilindro galpao = Cilindro(Ponto(1050, 0, 1050), Ponto(1050, 300, 1050), 150, k_galpao, k_galpao, k_galpao, 10);
    //
    //
    Canvas c = Canvas(nLin, nCol, Cor(255, 255, 255));
    Janela J = Janela(wJanela, hJanela, c);
    cam = Camera(Ponto(430, 190, 430), Ponto(431, 191, 431), Ponto(431, 189, 431));
    Cenario cenario{Intensidade(0.2, 0.2, 0.2)};

    cenario.cena.push_back(&fundo);
    cenario.cena.push_back(&frente);
    cenario.cena.push_back(&parede_esq);
    cenario.cena.push_back(&parede_dir);
    cenario.cena.push_back(&teto);
    cenario.cena.push_back(&chao);
    cenario.cena.push_back(&cabo_luminaria);
    cenario.cena.push_back(&luminaria);
    cenario.cena.push_back(&lampada);
    cenario.cena.push_back(&butijao);
    cenario.cena.push_back(&perna1);
    cenario.cena.push_back(&perna2);
    cenario.cena.push_back(&perna3);
    cenario.cena.push_back(&perna4);
    cenario.cena.push_back(&bola1);
    cenario.cena.push_back(&bola2);
    cenario.cena.push_back(&bola3);
    cenario.cena.push_back(&bcartola);
    cenario.cena.push_back(&cartola);
    cenario.cena.push_back(&faixa);
    cenario.cena.push_back(&olho1);
    cenario.cena.push_back(&olho2);
    cenario.cena.push_back(&nariz);
    cenario.cena.push_back(&cachecol);
    cenario.cena.push_back(&botao1);
    cenario.cena.push_back(&botao2);
    cenario.cena.push_back(&botao3);
    cenario.cena.push_back(&cam_seq);
    cenario.cena.push_back(&cam_cabo);
    cenario.cena.push_back(&galpao);

    cenario.cena.push_back(&base);
    // cenario.cena.push_back(&encosto);
    cenario.luzes.push_back(&luz_na_lampada);
    cenario.luzes.push_back(&luz_da_lampada);
    cenario.luzes.push_back(&luz_pontual_lampada);
    cenario.luzes.push_back(&spot_camera);

    cenario.atualizarCenarioMC(cam);
    // Atualiza para coordenadas de câmera

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
        colorirMatriz(J, &c, cenario, dJanela);
        renderizar(renderer, c);
        SDL_RenderPresent(renderer);
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
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    cenario.alterarCenario(&cam, dJanela);
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
            {
                Vetor maior = prodVetorC(cam.e_at, 100);
                cenario.atualizarCenarioCM(cam);
                cam.atualizar(addPV(cam.e, maior), addPV(cam.up, maior), addPV(cam.at, maior));
                cenario.atualizarCenarioMC(cam);
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
            {
                Vetor maior = prodVetorC(cam.e_at, -100);
                cenario.atualizarCenarioCM(cam);
                cam.atualizar(addPV(cam.e, maior), addPV(cam.up, maior), addPV(cam.at, maior));
                cenario.atualizarCenarioMC(cam);
            }
            // Se o evento for de clique...
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}