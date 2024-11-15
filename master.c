#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Input:
5
1: 2, 3, 5
2: 1, 4
3: 1, 5
4: 2
5: 1, 3

*/

// Estructura para representar un grafo
typedef struct {
    int vertices;
    int **adyacencia;
} Grafo;

// Función para obtener el grado máximo de un grafo
int GradoMáximo(Grafo g){
    int grado_maximo = 0;
    int aux = 0;
    for (int i = 0; i < g.vertices; i++){
        for (int j = 0; j < g.vertices; j++){
                if (g.adyacencia[i][j] != 0){
                    aux += 1;
                }
        }
        if (aux > grado_maximo){
            grado_maximo = aux;
        }
        aux = 0;
    }

    return grado_maximo;
}

// Función para obtener el grado máximo de un grafo
int GradoMínimo(Grafo g){
    int grado_minimo = 0;
    int aux = 0;
    for (int i = 0; i < g.vertices; i++){
        for (int j = 0; j < g.vertices; j++){
                if (g.adyacencia[i][j] != 0){
                    aux += 1;
                }
        }
        if (i == 0){
            grado_minimo = aux;
            continue;
        }
        if (aux < grado_minimo){
            grado_minimo = aux;
        }
        aux = 0;
    }

    return grado_minimo;
}


int main(){
    Grafo g;

    scanf("%d", &g.vertices);

    g.adyacencia = (int**)malloc(g.vertices * sizeof(int*));
    for (int i = 0; i < g.vertices; i++) {
        g.adyacencia[i] = (int*)malloc(g.vertices * sizeof(int));
    }

    // Inicializar puntos de adyacencia en 0
        for (int i = 0; i < g.vertices; i++){
            for (int j = 0; j < g.vertices; j++){
                g.adyacencia[i][j] = 0;
        }
    }

    // Ingresar puntos de adyacencia a cada vértice
    for (int i = 0; i < g.vertices; i++){
        for (int j = 0; j < g.vertices; j++){
            scanf("%d", &g.adyacencia[i][j]);
        }
    }

    // Imprimir grafo

    printf("Cantidad de vertices: %d \n", g.vertices);
    for (int i = 0; i < g.vertices; i++){
            printf("Vértice[%d]: ", (i+1));
        for (int j = 0; j < g.vertices; j++){
                if (g.adyacencia[i][j] != 0){
                    printf("%d ", g.adyacencia[i][j]);
                }
        }
        printf("\n");
    }

    // Imprimir grado máximo del grafo
    printf("Grado Maximo: %d\n", GradoMáximo(g));

    // Imprimir grado mínimo del grafo
    printf("Grado Minimo: %d", GradoMínimo(g));

}