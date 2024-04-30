#ifndef NUMEROS_H
#define NUMEROS_H

typedef int Entero;

Entero EsNegativo(Entero a){
    if(a < 0)
        return 1;
    else
        return 0;
}

Entero cambiarSigno(Entero a){
    return a * -1;
}

Entero Abs(Entero a){
    if(EsNegativo(a))
        a = cambiarSigno(a);
    return a;
}

float Potencia(float a, float p){
    if(p == 0)
        return 1.0;

    while(p>1.0){
        a = a * a;
        p--;
    }
    return a;
}




#endif
