#pragma once
#include "../cenario/cenario.h"

class Pick
{
public:
    Cenario *cenario;
    Pick();
    Pick(Cenario *cenario);
    void pick(int x, int y);
};