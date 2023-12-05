#pragma once
#include "../externo/alinear.h"
#include <SDL2/SDL_image.h>
#include <string>

class Textura
{
public:
    SDL_Surface *image = nullptr;
    int h, w;
    void loadImage(std::string path);
    Intensidade getIntensity(int x, int y);
    Cor getColor(int x, int y);
    Textura(std::string path);
    Textura();
    ~Textura();
};