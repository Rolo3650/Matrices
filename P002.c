#include <stdio.h>
#include <stdlib.h>
#include "./fracciones.h"

void darDimensiones(int*, int*);
Frac** crearMatriz(int, int);
void llenarMatriz(Frac**, int, int);
void llenarMatrizIdentidad(Frac**, int);
void impMats(Frac**, Frac**, int, int);
void gaussJordan(Frac**, Frac**, int);
void liberarMemoria(Frac**, Frac**, int);

int main(){

    int fil, col;

    //Dimension de las matrices.
    darDimensiones(&fil, &col);

    //Otorga el espacio en memoria a las matrices.
    Frac** matriz = crearMatriz(fil, col);
    Frac** matrizInversa = crearMatriz(fil, col);

    //Pide los datos para llenar la matriz.
    llenarMatriz(matriz, fil, col);
    llenarMatrizIdentidad(matrizInversa, fil);

    //Imprime las matrices.
    impMats(matriz, matrizInversa, fil, col);

    //Deja en Gauss Jordan a la primer matriz y deja en inversa a la identidad.
    gaussJordan(matriz, matrizInversa, fil);

    printf("\n-------------------------------------\n\tMatriz Inversa\n");
    impMats(matriz, matrizInversa, fil, col);

    liberarMemoria(matriz, matrizInversa, fil);
    return 0;
}

void darDimensiones(int* fil, int* col){
    printf("Ingresa el numero de filas de la matriz: ");
    scanf("%d", fil);
    printf("Ingresa el numero de columnas de la matriz: ");
    scanf("%d", col);
}

Frac** crearMatriz(int fil, int col){
    Frac** mat = (Frac**)malloc(fil*sizeof(Frac*));

    if(!mat){
        printf("\nError: No se asigno memoria a la matriz\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<fil;i++){
        mat[i] = (Frac*)malloc(col*sizeof(Frac));
        if(!mat[i]){
            printf("\nError: No se asigno memoria a la fila %d de la matriz\n", i);
            for(int j=0; j<i; j++) {
                free(mat[j]); // Liberar memoria asignada previamente
            }
            free(mat); // Liberar memoria de la matriz
            exit(EXIT_FAILURE);
        }
    }

    return mat;
}

void llenarMatriz(Frac** mat, int fil, int col){
    for(int i=0; i<fil; i++){
        printf("Ingresa la fila %d : ", i+1);
        for(int j=0; j<col; j++){
            int num;
            scanf("%d", &num);
            mat[i][j] = entero_a_Frac(num);
        }
    }
    putchar('\n');
}

void llenarMatrizIdentidad(Frac** mat, int fil){
    for(int i = 0; i < fil; i++){
        mat[i] = (Frac*)malloc(fil * sizeof(Frac));
        if(!mat[i]){
            printf("\nError: No se asigno memoria a la fila %d de la matriz identidad\n", i);
            for(int j = 0; j < i; j++){
                free(mat[j]); // Liberar memoria asignada previamente
            }
            free(mat); // Liberar memoria de la matriz
            exit(EXIT_FAILURE);
        }
        for(int j = 0; j < fil; j++){
            if(i == j)
                mat[i][j] = entero_a_Frac(1);
            else
                mat[i][j] = entero_a_Frac(0);
        }
    }
}

void impMats(Frac** mat, Frac** matInversa, int fil, int col){
    for(int i=0;i<fil;i++){
        printf(" | ");
        for(int j=0;j<col;j++)
            impFrac(mat[i][j]);

        printf("|");

        for(int j=0;j<col;j++)
            impFrac(matInversa[i][j]);

        printf(" | ");
        putchar('\n');
    }
    putchar('\n');
}

void gaussJordan(Frac** matriz, Frac** matrizInversa, int dim){
    Frac aux;

    // Aplicar eliminación gaussiana
    for(int i = 0; i < dim; i++){
        // Dividir la fila i por el elemento diagonal
        aux = matriz[i][i];
        // impFrac(aux);
        
        if(aux.e == 0 && aux.n == 0) {
            printf("\nError: División por cero. #forDeFila:%d\n", i);
            impFrac(aux);
            exit(EXIT_FAILURE);
        }
        for(int j = 0; j < dim; j++){
            matriz[i][j] = div_Fracs(matriz[i][j], aux);
            matrizInversa[i][j] = div_Fracs(matrizInversa[i][j], aux);
        }

        // Hacer ceros debajo del elemento diagonal
        for(int k = 0; k < dim; k++){
            if(k != i){
                Frac factor = matriz[k][i]; // Factor por el que se debe multiplicar la fila i
                for(int j = 0; j < dim; j++){
                    matriz[k][j] = resta_Fracs(matriz[k][j], mult_Fracs(matriz[i][j], factor));
                    matrizInversa[k][j] = resta_Fracs(matrizInversa[k][j], mult_Fracs(matrizInversa[i][j], factor));
                }
            }
        }
    }
    impFrac(matriz[0][0]);
    impFrac(matriz[0][1]);
    impFrac(matriz[1][0]);
    impFrac(matriz[1][1]);

    //Hacer ceros en el triángulo superior
    for(int i = dim - 1; i >= 0; i--){
        for(int k = i - 1; k >= 0; k--){
            Frac factor = matriz[k][i]; // Factor por el que se debe multiplicar la fila i
            Frac mult_factor = mult_Fracs(matriz[i][i], factor); // Multiplicación de la fila i por el factor
            Frac mult_factor_inv = mult_Fracs(matrizInversa[i][i], factor); // Multiplicación de la fila i de la inversa por el factor
            for(int j = 0; j < dim; j++){
                matriz[k][j] = resta_Fracs(matriz[k][j], mult_factor); // Resta de la fila k multiplicada por el factor
                matrizInversa[k][j] = resta_Fracs(matrizInversa[k][j], mult_factor_inv); // Resta de la fila k de la inversa multiplicada por el factor
            }
        }
    }
}

void liberarMemoria(Frac** mat, Frac** mat2, int dim){
    for(int i=0;i<dim;i++){
        free(mat[i]);
        free(mat2[i]);
    }

    free(mat);
    free(mat2);

    printf("\n--Memoria liberada--\n");
}
