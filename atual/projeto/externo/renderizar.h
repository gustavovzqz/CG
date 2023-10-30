#pragma once 
#include "alinear.h"
#include "../ray/raio.h"
#include "../objetos/esfera.h"
#include "../tela/canvas.h"
#include "../tela/janela.h"
#include "../cenario/cenario.h"
#include <SDL2/SDL.h>

void colorirMatriz(Ponto obs, Janela janela, Canvas *canvas, Cenario cenario, int dJanela, Luz i);
void renderizar(SDL_Renderer* renderer, Canvas canvas);