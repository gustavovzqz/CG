#include "esfera.h"
#include "math.h"

Esfera::Esfera() {}

Esfera::Esfera(Ponto centro, float raio, Cor cor, Intensidade Ke, Intensidade Ka, Intensidade Kd, float m){
    this -> cor = cor;
    this -> raio = raio;
    this -> centro = centro;
    this -> Ke = Ke;
    this -> Ka = Ka;
    this -> Kd = Kd;
    this -> m = m;
}

Cor Esfera::intersecta(Raio r, Luz i, Cor bgColor){
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint;


    Vetor w = subP(p0, centro); // Subtração dos pontos p0 e centro da esfera
    float bBarra = innerProd(w, dr); // Produto interno de w e dr
    float c = innerProd(w,w) - (raio * raio);
    float delta = (bBarra * bBarra) - c;

    if (delta < 0)
        return bgColor; // Se não intersecta, retorna a cor padrão.
    
    float t1 = -bBarra - sqrt(delta);
    float t2 = -bBarra + sqrt(delta);

    Ponto p1 = addPV(p0, prodVetorC(dr, t1)); // P(t) = P0 + dr*t
    Ponto p2 = addPV(p0, prodVetorC(dr, t2));

    float tam_p1 = modulo(subP(p0, p1));
    float tam_p2 = modulo(subP(p0, p2));
        
    // Encontra o ponto que intersecta PRIMEIRO (em relação ao observador, o mais próximo)
    if (tam_p1 < tam_p2) 
        pint = p1;
    else 
        pint = p2;

    Vetor n = divVetorC(subP(pint, centro), raio);
    
    // Aqui, já temos o ponto de intersecção correto.
    // Basta chamar a função de iluminação para sabermos a cor correta.
    return (i.iluminarObjeto(n, pint, dr, Ke, Kd, Ka, m, cor));
}
