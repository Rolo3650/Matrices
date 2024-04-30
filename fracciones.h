#ifndef FRACCIONES_H
#define FRACCIONES_H

#include <stdio.h>
#include "numeros.h"

typedef struct {
    Entero e;
    Entero n;
    Entero d;
} Frac;

Entero MCD(Entero a, Entero b) {
    int temporal;

    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }

    return a;
}

Frac entero_a_Frac(int a){
    Frac f;

    f.e = a;
    f.d = 1;
    f.n = 0;

    return f;
}

void impFrac(Frac a) {
    if(a.n == 0)
        printf(" %d[] ", a.e);
    else
        printf(" %d[%d/%d] ", a.e, a.n, a.d);
}

void impMatFrac(Frac a[20][20], Entero r) {
    int i, j;
    printf("-------------------------------\n");
    for(i=0; i<r; i++){
        for(j=0; j<=r; j++){
            if(a[i][j].n == 0)
                printf("%d[]     \t", a[i][j].e);
            else
                printf("%d[%d|%d]\t", a[i][j].e, a[i][j].n, a[i][j].d);

        }
        printf("\n-------------------------------\n");
    }

}

Frac leeFrac() {
    Frac t;

    printf("Ingresa una fraccion\n");
    scanf("%d%d%d", &t.e, &t.n, &t.d);

    if(t.e == 0 && t.n == 0 && t.d == 0){
        printf("INDETERMINADOOOOOOOO!!!!!\n\n");
        t.e = 0;
        t.n = 0;
        t.d = 0;
        return t;
    }

    return t;
}

Frac mix_a_Imp(Frac a) {
    Frac t;
    t.e = 0;
    t.n = !EsNegativo(a.e) ? a.e * a.d + a.n : a.e * a.d - a.n;
    if (EsNegativo(a.e) || EsNegativo(a.n))
        t.n = -t.n;
    a.e = t.e;
    a.n = t.n;

    return a;
}

Frac imp_a_Mix(Frac a) {
    Frac t = a;
    t.e = a.e + (a.n / a.d);
    t.n = (a.n % a.d);
    if(a.n < 0)
        t.e = -t.e;

    return t;
}

Frac reduceFrac(Frac a) {
    Frac t = imp_a_Mix(a);
    if (t.d == 0) {
        printf("Error: Denominador cero.\n");
        exit(1);
    }
    Entero m = MCD(t.n, t.d);

    t.n = t.n / m;

    if((EsNegativo(t.d) && !EsNegativo(t.n)) || (EsNegativo(t.n) && !EsNegativo(t.e)))
        t.e = cambiarSigno(t.e);

    if(EsNegativo(t.e))
        t.n = Abs(t.n);

    return t;
}

Entero MCM(Entero a, Entero b) {
    return (a * b) / MCD(a, b);
}

Frac suma_Fracs(Frac a, Frac b) {
    Frac t;
    a = mix_a_Imp(a);
    b = mix_a_Imp(b);

    t.e = 0;
    t.n = (a.n * b.d) + (b.n * a.d);
    t.d = a.d * b.d;

    return reduceFrac(t);
}

Frac resta_Fracs(Frac a, Frac b) {
    Frac t;
    a = mix_a_Imp(a);
    b = mix_a_Imp(b);

    t.e = 0;
    t.n = (a.n * b.d) - (b.n * a.d);
    t.d = a.d * b.d;

    return reduceFrac(t);
}

Frac mult_Fracs(Frac a, Frac b) {
    Frac t;
    a = mix_a_Imp(a);
    b = mix_a_Imp(b);

    t.e = 0;
    t.n = a.n * b.n;
    t.d = a.d * b.d;

    return reduceFrac(t);
}

Frac div_Fracs(Frac a, Frac b) {
    Frac t;
    a = mix_a_Imp(a);
    b = mix_a_Imp(b);
    
    if ((b.n == 0)) {
        printf("Error: División por cero.\n");
        exit(1);
    }

    t.e = 0;
    t.n = a.n * b.d;
    t.d = a.d * b.n;

    if (t.d < 0) {
        t.n = -t.n;
        t.d = -t.d;
    }

    return reduceFrac(t);
}


#endif
