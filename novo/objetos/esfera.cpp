#include "esfera.h"
#include "math.h"

Esfera::Esfera() {}

Esfera::Esfera(Ponto centro, double raio, Cor cor, Intensidade Ke, Intensidade Ka, Intensidade Kd, double m){
    this -> cor = cor;
    this -> raio = raio;
    this -> centro = centro;
    this -> Ke = Ke;
    this -> Ka = Ka;
    this -> Kd = Kd;
    this -> m = m;
}


Vetor Esfera::makeN(Ponto pint, Vetor dr){
    return(divVetorC(subP(pint, centro), raio)); // Verificar se precisa do "this ->"
}

Cor Esfera::intersecta(Raio r, Luz i, Cor bgColor){
    Ponto p0 = r.pin;
    Vetor dr = r.dr;
    Ponto pint;


    Vetor w = subP(p0, centro);
    double a = innerProd(dr, dr); // Sempre será um  
    double b = 2 * innerProd(w, dr);
    double c = innerProd(w,w) - (raio * raio);
    double delta = (b * b) - (4 * a * c);

    if (delta < 0)
        return bgColor; // Se não intersecta, retorna a cor padrão.
    
    double t1 = (-b - sqrt(delta) / (2 * a));
    double t2 = (-b + sqrt(delta) / (2 * a));

    Ponto p1 = addPV(p0, prodVetorC(dr, t1));
    Ponto p2 = addPV(p0, prodVetorC(dr, t2));

    double tam_p1 = modulo(subP(p0, p1));
    double tam_p2 = modulo(subP(p0, p2));
        
    // Encontra o ponto que intersecta PRIMEIRO (em relação ao observador, o mais próximo)
    if (tam_p1 < tam_p2) 
        pint = p1;
    else 
        pint = p2;
    
    // Aqui, já temos o ponto de intersecção correto.
    // Basta chamar a função de iluminação para sabermos a cor correta.
    return (i.iluminarObjeto(makeN(pint,dr), pint, dr, Ke, Kd, Ka, m, cor));
}