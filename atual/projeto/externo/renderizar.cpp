#include "renderizar.h"

// Retorna uma matriz colorida!
void colorirMatriz(Camera cam, Janela janela, Canvas *canvas, Cenario cenario, int dJanela)
{
    Ponto obs = cam.obs;
    float JyM = janela.jyMax;
    float jxMin = janela.jxMin;
    float dy = janela.dY;
    float dx = janela.dX;
    int nLin = canvas->nLines;
    int nCol = canvas->nCol;
    Cor bgColor = canvas->bgColor;
    Raio raio;
    float yL;
    float xC;
    Ponto pJ;
    Objeto *obj;

    for (int l = 0; l < nLin; l++)
    {
        yL = JyM - dy / 2 - l * dy;
        for (int c = 0; c < nCol; c++)
        {
            xC = jxMin + dx / 2 + c * dx;
            pJ = Ponto(xC, yL, -dJanela);
            pJ = prodMP(cam.mc, pJ);
            raio = Raio(obs, pJ);
            obj = cenario.escolherObjeto(raio);
            if (obj == nullptr)
            {
                canvas->matriz[l][c] = bgColor;
            }
            else
            {
                Ponto pint_objeto = addPV(raio.pin, prodVetorC(raio.dr, obj->tInt(raio)));
                /* A gente passa pro objeto o Cenário
                   A função de iluminação do objeto será do próprio cenário...*/
                canvas->matriz[l][c] = cenario.iluminarObjeto(raio, pint_objeto, obj, bgColor);
            } // Esfera será uma lista de objetos (cenário)
        }
    }
}

// Usa a matriz de cores para exibir a imagem na tela usando o SDL
void renderizar(SDL_Renderer *renderer, Canvas canvas)
{

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
            SDL_RenderDrawPoint(renderer, c, l);          // Pinta propriamante
        }
    }
    SDL_RenderPresent(renderer); // Atualizamos com o renderer que acabamos de pintar
}