import random
from datetime import datetime


def generar_archivo_grafo_aleatorio(nombre_archivo="grafo_aleatorio.txt"):
    """
    Genera un archivo txt con un grafo aleatorio no dirigido,
    asegurando que las conexiones sean bidireccionales
    """

    num_vertices = 5

    # Diccionario para almacenar las conexiones de cada vértice
    conexiones = {i: set() for i in range(1, num_vertices + 1)}

    # Generar conexiones aleatorias
    for vertice in range(1, num_vertices + 1):
        # Decidir número de nuevas conexiones para este vértice
        conexiones_existentes = len(conexiones[vertice])
        nuevas_conexiones_max = min(3 - conexiones_existentes, num_vertices - 1 - conexiones_existentes)

        if nuevas_conexiones_max > 0:
            # Generar posibles conexiones (excluyendo el vértice actual y conexiones existentes)
            posibles_conexiones = set(range(1, num_vertices + 1)) - {vertice} - conexiones[vertice]
            num_nuevas = random.randint(1, nuevas_conexiones_max)
            nuevas = random.sample(list(posibles_conexiones), min(num_nuevas, len(posibles_conexiones)))

            # Agregar conexiones bidireccionales
            for otro in nuevas:
                conexiones[vertice].add(otro)
                conexiones[otro].add(vertice)

    # Escribir al archivo
    with open(nombre_archivo, 'w') as f:
        f.write(f"{num_vertices}\n")
        for vertice in range(1, num_vertices + 1):
            conexiones_ordenadas = sorted(conexiones[vertice])
            f.write(f"{vertice}: {', '.join(map(str, conexiones_ordenadas))}\n")


def verificar_consistencia(nombre_archivo):
    """
    Verifica que el grafo sea no dirigido (conexiones bidireccionales)
    """
    conexiones = {}

    # Leer el archivo
    with open(nombre_archivo, 'r') as f:
        num_vertices = int(f.readline().strip())
        for linea in f:
            vertice, conexs = linea.strip().split(':')
            vertice = int(vertice)
            conexiones[vertice] = set()
            if conexs.strip():  # si hay conexiones
                conexiones[vertice] = set(int(x.strip()) for x in conexs.split(','))

    # Verificar bidireccionalidad
    inconsistencias = []
    for v1 in conexiones:
        for v2 in conexiones[v1]:
            if v1 not in conexiones[v2]:
                inconsistencias.append((v1, v2))

    return len(inconsistencias) == 0, inconsistencias


# Ejemplo de uso
if __name__ == "__main__":
    fecha= datetime.now().strftime("%H-%M-%S")
    nombre_archivo = f"grafo_aleatorio_{fecha}.txt"
    generar_archivo_grafo_aleatorio(nombre_archivo)

    # Verificar la consistencia
    es_consistente, inconsistencias = verificar_consistencia(nombre_archivo)

    print(f"Archivo de grafo aleatorio generado: {nombre_archivo}")
    if es_consistente:
        print("El grafo es consistente (todas las conexiones son bidireccionales)")
    else:
        print("Se encontraron las siguientes inconsistencias:")
        for v1, v2 in inconsistencias:
            print(f"El vértice {v1} conecta con {v2}, pero {v2} no conecta con {v1}")