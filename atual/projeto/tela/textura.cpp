#include "textura.h"
#include <iostream>
using std::string;
Textura::Textura() {}

Textura::Textura(const string path)
{
    SDL_Surface *image = IMG_Load(path.c_str());

    if (image == nullptr)
    {
        std::cout << "erro on load the image\n";
        return;
    }

    int lockSurfaceResult = SDL_LockSurface(image);

    if (lockSurfaceResult != 0)
    {
        std::cout << "error on lock the texture bytes\n";
        SDL_FreeSurface(image);
        return;
    }

    if (this->image != nullptr)
        SDL_FreeSurface(this->image);

    this->image = image;
    this->h = image->h;
    this->w = image->w;

    std::cout << "foi! Image dimensions: " << image->w << " x " << image->h << '\n';
}

Intensidade Textura::getIntensity(Ponto pint)
{ // Esse cálculo está errado, e tem que ser um para cada objeto.
    int x, y;
    // Como definir quem é o x e o y?

    Cor p = getColor(x, y);
    return (Intensidade((double)p.r / 255, (double)p.g / 255, (double)p.b / 255));
}

Cor Textura::getColor(int x, int y)
{
    int selectedPixel;
    int bytesPerPixel = image->format->BytesPerPixel;

    Uint8 *pixel = (Uint8 *)this->image->pixels + y * this->image->pitch + x * bytesPerPixel;

    switch (bytesPerPixel)
    {
    case 1:
        selectedPixel = *pixel;
        break;
    case 2:
        selectedPixel = *((Uint16 *)pixel);
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            selectedPixel = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
        }
        else
        {
            selectedPixel = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
        }
        break;
    case 4:
        selectedPixel = *((Uint32 *)pixel);
        break;
    default:
        selectedPixel = 0;
    }

    SDL_Color rgb;
    SDL_GetRGB(selectedPixel, image->format, &rgb.r, &rgb.g, &rgb.b);

    return Cor(rgb.r, rgb.g, rgb.b);
}

Textura::~Textura()
{
    SDL_UnlockSurface(this->image);
    SDL_FreeSurface(this->image);
}