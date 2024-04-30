#include <stdio.h>
#include <stdlib.h>

#define TAM 100

void inicializarMatriz(float matriz[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            matriz[j][i] = 0;
        }
    }
}

void imprimirMatriz(float matriz[TAM][TAM], int filas, int columnas, int separador)
{
    for (int i = 0; i < filas; i++)
    {
        printf("[ ");
        for (int j = 0; j < columnas; j++)
        {
            printf(" %.0f ", matriz[i][j]);
            if (separador != 0 && (separador - 1) == j)
                printf(" | ");
        }
        printf(" ]\n");
    }
    printf("\n");
}

void ingresarDatos(float matriz[TAM][TAM], int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        printf("Ingresa los datos de la fila %d:\n", i + 1);
        for (int j = 0; j < columnas; j++)
        {
            scanf("%f", &matriz[i][j]);
        }
        printf("\n");
    }
}

void transposicion(float matriz[TAM][TAM])
{
    int fila1, fila2;
    float aux;
    puts("Ingresa las filas que deseas sumar, y la cantidad por la que lo deseas sumar (R1 * n R2 * m)");
    scanf("%d %d", &fila1, &fila2);

    for (int i = 0; i < TAM; i++)
    {
        aux = matriz[fila1 - 1][i];
        matriz[fila1 - 1][i] = matriz[fila2 - 1][i];
        matriz[fila2 - 1][i] = aux;
    }
}

void suma(float matriz[TAM][TAM])
{
    int fila1, fila2;
    float coef1, coef2;
    puts("Ingresa las filas que deseas sumar, y la cantidad por la que lo deseas sumar (R1 * n R2 * m)");
    scanf("%d %f %d %f", &fila1, &coef1, &fila2, &coef2);

    for (int i = 0; i < TAM; i++)
    {
        matriz[fila1 - 1][i] = (matriz[fila1 - 1][i] * coef1) + (matriz[fila2 - 1][i] * coef2);
    }
}

void multiplicacion(float matriz[TAM][TAM])
{
    int fila1;
    float coef1;
    float div1;
    puts("Ingresa la fila y su coeficiente (R1 * n / m)");
    scanf("%d %f/%f", &fila1, &coef1, &div1 );

    for (int i = 0; i < TAM; i++)
    {
        matriz[fila1 - 1][i] = (matriz[fila1 - 1][i] * (coef1 / div1));
    }
}

int main()
{
    float mat[TAM][TAM];
    int filas, columnas, separador = 0, menu;

    inicializarMatriz(mat);

    puts("Ingresa la cantidad de filas");
    scanf("%d", &filas);
    puts("Ingresa la cantidad de columnas");
    scanf("%d", &columnas);
    puts("Ingresa el separador de la igualdad");
    scanf("%d", &separador);

    imprimirMatriz(mat, filas, columnas, separador);
    ingresarDatos(mat, filas, columnas);
    imprimirMatriz(mat, filas, columnas, separador);

    while (1)
    {
        puts("Ingresa la operación que deseas realizar: \n 1) Transposición\n 2) Suma \n 3) Resta\n");
        scanf("%d", &menu);

        if (menu == 1)
        {
            transposicion(mat);
            imprimirMatriz(mat, filas, columnas, separador);
        }
        if (menu == 2)
        {
            suma(mat);
            imprimirMatriz(mat, filas, columnas, separador);
        }
        if (menu == 3)
        {
            multiplicacion(mat);
            imprimirMatriz(mat, filas, columnas, separador);
        }
    }

    return 0;
}
