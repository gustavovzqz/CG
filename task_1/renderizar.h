#pragma once 
#include "alinear.h"
#include "raio.h"
#include "esfera.h"
#include "canvas.h"
#include "janela.h"
#include <SDL2/SDL.h>

void colorirMatriz(Ponto obs, Janela janela, Canvas *canvas, Esfera esfera, int dJanela);
void renderizar(SDL_Renderer* renderer, Canvas canvas);