# Sorting Project

Proyecto simple en C++ con una librería para generar arreglos de distintos tamaños y medir tiempos de ejecución para Quicksort y Mergesort.

## Archivos

- `sorting.hpp` - Declaraciones de la librería.
- `sorting.cpp` - Implementación de generación, Quicksort, Mergesort y medición de tiempo.
- `quicksort_main.cpp` - Programa que ejecuta Quicksort y muestra tiempos.
- `mergesort_main.cpp` - Programa que ejecuta Mergesort y muestra tiempos.

## Compilar

Usa estos comandos desde la carpeta `sorting_project`:

```bash
g++ -std=c++17 quicksort_main.cpp sorting.cpp -o quicksort
g++ -std=c++17 mergesort_main.cpp sorting.cpp -o mergesort
```

## Ejecutar

```bash
./quicksort
./mergesort
```
