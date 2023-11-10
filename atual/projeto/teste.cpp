#include "externo/alinear.h"
#include <iostream>
using namespace std;

void printar_matriz(Matriz m)
{
    cout << m.v1.x << " " << m.v2.x << " " << m.v3.x << " " << m.v4.x << '\n';
    cout << m.v1.y << " " << m.v2.y << " " << m.v3.y << " " << m.v4.y << '\n';
    cout << m.v1.z << " " << m.v2.z << " " << m.v3.z << " " << m.v4.z << '\n';
    cout << m.v1.h << " " << m.v2.h << " " << m.v3.h << " " << m.v4.h << '\n';
}

int main()
{
    Vetor v1 = Vetor(1, 2, 3, 4);
    Vetor v2 = Vetor(5, 6, 7, 8);
    Matriz m = Matriz(v1, v2, v1, v2);
    Matriz m2 = Matriz(v2, v1, v2, v2);
    printar_matriz(m);
    printar_matriz(m2);
    printar_matriz(prodMM(m, m2));
}