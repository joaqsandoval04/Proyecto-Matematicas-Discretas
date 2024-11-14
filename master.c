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


int main(){
    Grafo g;
    g.vertices = 3;

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

}
int tamaño_grafo = 5;

bool EliminarVértices(int k){
    if (tamaño_grafo <= k){
        return false;
    }
}