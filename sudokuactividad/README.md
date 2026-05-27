# Sudoku Generator & Parallel Solver (C++)

Un generador y solucionador de Sudoku hecho en C++ usando:

* generación procedural con semillas,
* backtracking,
* validación matemática,
* computación paralela con `std::thread`,
* máscaras de visibilidad,
* tensor 3D para almacenamiento.

---

# Características

* Generación reproducible mediante semillas.
* Generación matemática real de Sudoku.
* Solver mediante backtracking.
* Validación paralela:

  * filas,
  * columnas,
  * submatrices.
* Máscara binaria para ocultar celdas.
* Tensor 3D:

  * solución completa,
  * tablero visible.
* Compatible con:

  * Linux,
  * WSL,
  * MinGW,
  * GCC,
  * Clang.

---

# Estructura General

El sistema tiene 3 etapas principales:

```text
1. Generación del Sudoku
2. Construcción de máscara visual
3. Resolución paralela
```

---

# Flujo General

```text
Semillas
   ↓
Generación del tablero válido
   ↓
Creación de máscara
   ↓
Construcción del tensor
   ↓
Impresión o resolución
```

---

# Librerías Utilizadas

## `<iostream>`

Permite imprimir texto en consola.

Uso:

```cpp
std::cout << "Hola";
```

Se usa para:

* imprimir el Sudoku,
* imprimir soluciones,
* depuración.

---

## `<vector>`

Permite usar arreglos dinámicos.

Uso:

```cpp
std::vector<int> numeros;
```

Se usa para:

* tablero 9x9,
* tensor 3D,
* submatrices,
* máscaras.

---

## `<random>`

Permite generar números pseudoaleatorios usando semillas.

Uso:

```cpp
std::mt19937 gen(seed);
```

Se usa para:

* mezclar números,
* crear Sudokus distintos,
* generar máscaras.

---

## `<algorithm>`

Contiene algoritmos estándar.

Uso:

```cpp
std::shuffle(...)
```

Se usa para:

* mezclar números del 1 al 9.

---

## `<thread>`

Permite crear hilos.

Uso:

```cpp
std::thread hilo(...);
```

Se usa para:

* validación paralela.

---

## `<atomic>`

Permite compartir variables entre hilos de forma segura.

Uso:

```cpp
std::atomic<bool> valido;
```

Se usa para:

* sincronización entre hilos.

---

# Clase `Sudoku`

La clase principal del proyecto.

```cpp
class Sudoku
```

Contiene:

* generación,
* solución,
* impresión,
* tensor,
* validación.

---

# Constructor

```cpp
Sudoku(unsigned int sem1,
       unsigned int sem2,
       unsigned int sem3)
```

Inicializa:

* semillas,
* generadores aleatorios,
* tablero vacío.

---

# Generación del Sudoku

## `crearSudoku()`

Función principal.

### Responsabilidades

1. Generar Sudoku válido.
2. Crear máscara binaria.
3. Construir tensor 3D.

---

# Backtracking

## `llenarSudoku()`

```cpp
bool llenarSudoku(int fila, int columna);
```

Genera el Sudoku.

---

## Lógica

Recorre el tablero:

```text
fila por fila
columna por columna
```

Para cada celda:

1. prueba números del 1 al 9,
2. verifica legalidad,
3. avanza recursivamente,
4. si falla:

   * revierte,
   * intenta otro número.

---

# Validación

## `esValido()`

```cpp
bool esValido(...)
```

Verifica:

* fila,
* columna,
* submatriz.

---

## Validación de fila

```text
No puede repetirse un número
```

---

## Validación de columna

```text
No puede repetirse un número
```

---

## Validación de submatriz

```text
Cada bloque 3x3 debe contener
1..9 sin repetición
```

---

# Máscara Binaria

## `generarMascaraBinaria()`

Crea una matriz 9x9 con:

```text
1 = visible
0 = oculto
```

---

## Ejemplo

```text
1 0 0 1 0
```

---

# Tensor 3D

## `construirTensor()`

Construye:

```text
tensor3D[0] -> solución completa
tensor3D[1] -> máscara visual
```

---

# Impresión

## `imprimirSolucion()`

Muestra:

```text
Sudoku completo
```

---

## `imprimirSudoku()`

Muestra:

```text
Sudoku jugable
```

Las celdas ocultas aparecen como:

```text
[]
```

---

# Obtener matriz jugable

## `obtenerSudokuJuego()`

Devuelve:

```cpp
std::vector<std::vector<std::string>>
```

Ejemplo:

```text
5 [] 2 [] 9
```

---

# Solver Paralelo

## `resolverSudokuParalelo()`

Resuelve el Sudoku usando:

* backtracking,
* validación paralela.

---

# Paralelismo

La validación usa 3 hilos:

| Hilo | Función           |
| ---- | ----------------- |
| 1    | Revisar fila      |
| 2    | Revisar columna   |
| 3    | Revisar submatriz |

---

# `esValidoParalelo()`

Crea:

```cpp
std::thread
```

para cada validación.

---

# Sincronización

Se usa:

```cpp
std::atomic<bool>
```

para compartir el estado entre hilos.

---

# Resolver Sudoku

## `resolverBacktracking()`

Backtracking recursivo:

```text
poner número
↓
validar
↓
continuar
↓
si falla:
retroceder
```

---

# Semillas

El proyecto usa 3 semillas independientes.

| Semilla | Uso                   |
| ------- | --------------------- |
| `seed1` | mezcla de números     |
| `seed2` | expansión futura      |
| `seed3` | máscara y variaciones |

---

# Reproducibilidad

Las mismas semillas producen:

```text
exactamente el mismo Sudoku
```

---

# Compilar en WSL

## Instalar GCC

```bash
sudo apt update
sudo apt install g++
```

---

# Verificar instalación

```bash
g++ --version
```

---

# Estructura recomendada

```text
proyecto/
│
├── main.cpp
├── crearsudoku.hpp
```

---

# Compilar

```bash
g++ main.cpp -std=c++17 -pthread -O2
```

---

# Explicación de flags

| Flag         | Función         |
| ------------ | --------------- |
| `-std=c++17` | usar C++17      |
| `-pthread`   | habilitar hilos |
| `-O2`        | optimización    |

---

# Ejecutar

```bash
./a.out
```

---

# Ejemplo de salida

```text
=== SOLUCION ===

5 3 4 | 6 7 8 | 9 1 2
...

=== JUEGO ===

5 [] [] | 6 [] 8 | [] [] 2
...
```

---

# Complejidad

## Generación

Backtracking:

```text
O(9^(n²))
```

aunque en práctica es mucho menor.

---

# Solver

También usa backtracking.

La paralelización reduce tiempo de validación.

---

# Posibles Mejoras

* OpenMP.
* CUDA.
* Heurísticas MRV.
* Dancing Links.
* UI gráfica.
* Exportar a JSON.
* Multiplayer.
* Generador de dificultad real.

---

# WSL

## ¿Qué es?

Windows Subsystem for Linux.

Permite correr Linux dentro de Windows.

---

# Instalar WSL

Abrir PowerShell como administrador:

```powershell
wsl --install
```

Reiniciar.

---

# Abrir Ubuntu

Desde inicio:

```text
Ubuntu
```

---

# Navegar a tus archivos de Windows

```bash
cd /mnt/c/
```

Ejemplo:

```bash
cd /mnt/c/Users/TuUsuario/Desktop/proyecto
```

---

# Compilar desde WSL

```bash
g++ main.cpp -std=c++17 -pthread -O2
```

---

# Ejecutar

```bash
./a.out
```

---

# Requisitos

* GCC 11+
* C++17
* Linux o WSL

---

# Autor

Proyecto educativo de:

* generación procedural,
* algoritmos,
* backtracking,
* concurrencia,
* estructuras de datos,
* C++ moderno.
