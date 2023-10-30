#include "renderizar.h"

// Retorna uma matriz colorida! 
void colorirMatriz(Ponto obs, Janela janela, Canvas *canvas, Cenario cenario, int dJanela, Luz i){ // Posteriormente passaremos o objeto Cenário
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
    Objeto* obj;
    bool ehiluminado;
    
    for (int l = 0; l < nLin; l++){
        yL = JyM - dy/2 - l*dy;
        for (int c = 0; c < nCol; c++){
            xC = jxMin + dx/2 + c*dx;
            pJ.set(xC, yL, -dJanela); 
            raio = Raio(obs, pJ);
            obj = cenario.escolherObjeto(raio);
            Ponto pint_objeto = addPV(raio.pin, prodVetorC(raio.dr, obj->tInt(raio)));
            ehiluminado = cenario.ehIluminado(i.pF, pint_objeto, obj, raio.dr);
            canvas -> matriz[l][c] = obj->intersecta(raio, i, bgColor, ehiluminado); // Esfera será uma lista de objetos (cenário)
            
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