#pragma once
#include "alinear.h"
#include "../ray/raio.h"
#include "../objetos/esfera.h"
#include "../tela/canvas.h"
#include "../tela/janela.h"
#include "../cenario/cenario.h"
#include "../tela/camera.h"
#include <SDL2/SDL.h>

void colorirMatriz(Janela janela, Canvas *canvas, Cenario cenario, int dJanela);
void renderizar(SDL_Renderer *renderer, Canvas canvas);