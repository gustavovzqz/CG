#pragma once 
#include "../externo/alinear.h"
#include "../externo/iluminacao.h"
#include "../ray/raio.h"
class Objeto {
    public: // Por enquanto o objeto está só assim, mas temos algumas propriedades comuns a todos os objetos por exemplo cores
    virtual Cor intersecta(Raio r, Iluminacao i) = 0;
};