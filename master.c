#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define RESET   "\033[0m"   
#define ROJO    "\033[31m"  
#define VERDE   "\033[32m"  
#define MORADO  "\033[0;35m"
/*
Input: (grafo)
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
int GradoMáximo(Grafo* g){
    int grado_maximo = 0;
    int aux = 0;
    for (int i = 0; i < g->vertices; i++){
        for (int j = 0; j < g->vertices; j++){
                if (g->adyacencia[i][j] != 0){
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
int GradoMínimo(Grafo* g){
    int grado_minimo = 0;
    int aux = 0;
    for (int i = 0; i < g->vertices; i++){
        for (int j = 0; j < g->vertices; j++){
                if (g->adyacencia[i][j] != 0){
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

// Función para crear un grafo desde un archivo
Grafo* crearGrafoDesdeArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return NULL;
    }


    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    
    // Leer número de vértices
    fscanf(archivo, "%d\n", &g->vertices);
    
    // Asignar memoria para la matriz de adyacencia
    g->adyacencia = (int**)malloc(g->vertices * sizeof(int*));
    for (int i = 0; i < g->vertices; i++) {
        g->adyacencia[i] = (int*)calloc(g->vertices, sizeof(int));
    }


    // Buffer para leer cada línea
    char linea[256];
    int vertice;
    
    // Leer cada línea del archivo
    while (fgets(linea, sizeof(linea), archivo)) {
        char* token = strtok(linea, ":"); // Separar el número del vértice
        if (token != NULL) {
            vertice = atoi(token) - 1; // Convertir a base 0
            
            // Obtener los vértices adyacentes
            token = strtok(NULL, ",");
            while (token != NULL) {
                int adyacente = atoi(token) - 1; // Convertir a base 0
                if (adyacente >= 0 && adyacente < g->vertices) {
                    g->adyacencia[vertice][adyacente] = 1;
                    g->adyacencia[adyacente][vertice] = 1;
                }
                token = strtok(NULL, ",");
            }
        }
    }


    fclose(archivo);
    return g;
}

// Función para imprimir el grafo
void imprimirGrafo(Grafo* g) {
    printf("\nRepresentación del grafo:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("Vértice %d: ", i + 1);
        for (int j = 0; j < g->vertices; j++) {
            if (g->adyacencia[i][j] == 1) {
                printf("%d ", j + 1);
            }
        }
        printf("\n");
    }
}


// Funcion para determinar la conexidad
bool conexidad(Grafo g){
    // Crear lista para guardar los nodos visitados, rellenarla con 0 para evitar conflicto
    int nodos_visitados[g.vertices];
    for (int i = 0; i < g.vertices; i++){
        nodos_visitados[i] = 0;
    }

    nodos_visitados[0] = g.adyacencia[0][0]; // Marcar el nodo 1 como visitado
    // Luego visitar los n nodos que tiene adyacente el nodo 1

    // Añadir todos estos nodos de adyacencia a la lista de nodos_visitados, de manera ordenada (El 2 en el puesto 2, etc)
    for (int i = 0; i < g.vertices; i++){
        if (g.adyacencia[0][i] != 0){
            nodos_visitados[(g.adyacencia[0][i]) - 1] = g.adyacencia[0][i];
        }
    }
    // Repetir el mismo paso para los vértices de adyacencia de 1, pero sólo los que no estén en la lista
    // Verificar si está o no en la lista
    
}

// Función para verificar si un grafo es conexo usando BFS
bool esConexo(Grafo* g, bool* verticesEliminados) {
    if (g->vertices <= 0) return false;
    
    // Array para marcar vértices visitados
    bool* visitado = (bool*)calloc(g->vertices, sizeof(bool));
    if (!visitado) return false;
    
    // Cola para BFS
    int* cola = (int*)malloc(g->vertices * sizeof(int));
    if (!cola) {
        free(visitado);
        return false;
    }
    
    // Encontrar el primer vértice no eliminado para empezar BFS
    int inicio = -1;
    for (int i = 0; i < g->vertices; i++) {
        if (!verticesEliminados[i]) {
            inicio = i;
            break;
        }
    }
    
    if (inicio == -1) {
        free(visitado);
        free(cola);
        return false;
    }
    
    // Inicializar BFS
    int frente = 0, final = 0;
    cola[final++] = inicio;
    visitado[inicio] = true;
    
    // Realizar BFS
    while (frente < final) {
        int actual = cola[frente++];
        
        for (int i = 0; i < g->vertices; i++) {
            if (g->adyacencia[actual][i] && !verticesEliminados[i] && !visitado[i]) {
                visitado[i] = true;
                cola[final++] = i;
            }
        }
    }
    
    // Verificar si todos los vértices no eliminados fueron visitados
    bool esConexo = true;
    for (int i = 0; i < g->vertices; i++) {
        if (!verticesEliminados[i] && !visitado[i]) {
            esConexo = false;
            break;
        }
    }
    
    free(visitado);
    free(cola);
    return esConexo;
}

// Función recursiva para generar todas las combinaciones posibles de k-1 vértices
bool verificarCombinaciones(Grafo* g, bool* verticesEliminados, int k, int inicio, int count) {
    // Si ya seleccionamos k-1 vértices, verificar si el grafo resultante es conexo
    if (count == k - 1) {
        return esConexo(g, verticesEliminados);
    }
    
    // Si no hay suficientes vértices restantes para alcanzar k-1
    if (g->vertices - inicio < k - 1 - count) {
        return true;
    }
    
    // Para cada vértice restante desde 'inicio'
    for (int i = inicio; i < g->vertices; i++) {
        // Marcar vértice como eliminado
        verticesEliminados[i] = true;
        
        // Verificar recursivamente con este vértice eliminado
        if (!verificarCombinaciones(g, verticesEliminados, k, i + 1, count + 1)) {
            return false;  // Si encontramos una combinación que desconecta el grafo
        }
        
        // Desmarcar vértice (backtracking)
        verticesEliminados[i] = false;
    }
    
    return true;
}

// Función principal para verificar si el grafo es k-conexo
bool esKConexo(Grafo* g, int k) {
    // Verificar condiciones básicas
    if (g == NULL || k < 1 || g->vertices <= k) {
        return false;
    }
    
    // Si k es 1, solo necesitamos verificar si el grafo es conexo
    if (k == 1) {
        bool* verticesEliminados = (bool*)calloc(g->vertices, sizeof(bool));
        if (!verticesEliminados) return false;
        
        bool resultado = esConexo(g, verticesEliminados);
        free(verticesEliminados);
        return resultado;
    }
    
    // Array para marcar vértices eliminados
    bool* verticesEliminados = (bool*)calloc(g->vertices, sizeof(bool));
    if (!verticesEliminados) return false;
    
    // Verificar todas las posibles combinaciones de k-1 vértices
    bool resultado = verificarCombinaciones(g, verticesEliminados, k, 0, 0);
    
    free(verticesEliminados);
    return resultado;
}

// Función para liberar la memoria del grafo
void liberarGrafo(Grafo* g) {
    for (int i = 0; i < g->vertices; i++) {
        free(g->adyacencia[i]);
    }
    free(g->adyacencia);
    free(g);
}

int main() {
    Grafo* grafo = NULL;
    char nombreArchivo[256];
    char opcion;
    
    do {
        printf("\n       Menú de opciones\n");
        printf("1. Cargar grafo desde archivo\n");
        printf("2. Mostrar grafo\n");
        printf("3. Calcular grado máximo y mínimo\n");
        printf("4. Verificar k-conexidad\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);


        switch(opcion) {
            case '1':
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", nombreArchivo);
                if (grafo != NULL) {
                    liberarGrafo(grafo);
                }
                grafo = crearGrafoDesdeArchivo(nombreArchivo);
                if (grafo != NULL) {
                    printf(VERDE "\nGrafo cargado exitosamente.\n" RESET);
                }
                break;


            case '2':
                if (grafo != NULL) {
                    imprimirGrafo(grafo);
                } else {
                    printf(ROJO "\nPrimero debe cargar un grafo.\n" RESET);
                }
                break;


            case '3':
                if (grafo != NULL) {
                    printf(VERDE "\nEl grado máximo del grafo es: %d\n", GradoMáximo(grafo));
                    printf("\nEl grado mínimo del grafo es: %d\n"RESET, GradoMínimo(grafo));
                } else {
                    printf(ROJO "\nPrimero debe cargar un grafo.\n" RESET);
                }
                break;

            case '4':
                if (grafo != NULL) {
                    int k;
                    printf("Ingrese el valor de k: ");
                    scanf("%d", &k);
                    if (esKConexo(grafo, k)) {
                        printf(VERDE"\nEl grafo es %d-conexo.\n"RESET, k);
                    } else {
                        printf(ROJO "\nEl grafo no es %d-conexo.\n"RESET, k);
                    }
                } else {
                    printf(ROJO "\nPrimero debe cargar un grafo.\n" RESET);
                }
                break;


            case '5':
                printf(MORADO "Saliendo del programa...\n");
                break;


            default:
                printf(ROJO"\nOpción no válida.\n"RESET);
                break;
        }


        if (opcion != '5') {
            printf("\n¿Desea realizar otra acción? (" VERDE"s"RESET"/"ROJO"n"RESET"): ");
            scanf(" %c", &opcion);
            if (opcion == 'n' || opcion == 'N') {
                printf(MORADO "\nSaliendo del programa...\n");
                break;
            }
        }

    } while (opcion != '5');


    if (grafo != NULL) {
        liberarGrafo(grafo);
    }


    return 0;
}