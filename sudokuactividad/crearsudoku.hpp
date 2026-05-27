#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread> //para los hilos
#include <atomic> //para las variables atómicas
#include <mutex> //para los mutex

class Sudoku {
public:

    Sudoku(unsigned int sem1, unsigned int sem2, unsigned int sem3)
        : seed1(sem1),
          seed2(sem2),
          seed3(sem3),
          gen1(sem1),
          gen2(sem2),
          gen3(sem3)
    {
        tablero = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    }

    void crearSudoku();
    void imprimirSolucion() const;
    void imprimirSudoku() const;
    std::vector<std::vector<std::string>> obtenerSudokuJuego() const;
    bool resolverSudokuParalelo(std::vector<std::vector<std::string>>& sudokuJuego);

private:

    unsigned int seed1, seed2, seed3;

    std::mt19937 gen1;
    std::mt19937 gen2;
    std::mt19937 gen3;

    std::vector<std::vector<int>> tablero;
    std::vector<std::vector<int>> mascara;

    std::vector<std::vector<std::vector<int>>> tensor3D;

private:

    bool llenarSudoku(int fila, int columna);

    bool esValido(int fila, int columna, int numero) const;

    std::vector<int> numerosAleatorios();

    void generarMascaraBinaria();

    void construirTensor();

    bool resolverBacktracking(
        std::vector<std::vector<int>>& tableroResolver,
        int fila,
        int columna
    );

    bool esValidoParalelo(
        const std::vector<std::vector<int>>& tableroResolver,
        int fila,
        int columna,
        int numero
    ) const;
};

std::vector<std::vector<int>> convertirJuegoAEnteros(
    const std::vector<std::vector<std::string>>& juego
) {

    std::vector<std::vector<int>> t(9, std::vector<int>(9, 0));

    for (int i = 0; i < 9; ++i) {

        for (int j = 0; j < 9; ++j) {

            if (juego[i][j] != "[]")
                t[i][j] = std::stoi(juego[i][j]);
        }
    }

    return t;
}

std::vector<std::vector<std::string>> Sudoku::obtenerSudokuJuego() const {

    std::vector<std::vector<std::string>> matriz(
        9,
        std::vector<std::string>(9)
    );

    for (int i = 0; i < 9; ++i) {

        for (int j = 0; j < 9; ++j) {

            if (tensor3D[1][i][j] == 1) {

                matriz[i][j] = std::to_string(tensor3D[0][i][j]);

            } else {

                matriz[i][j] = "[]";
            }
        }
    }

    return matriz;
}

// ======================================================
// Genera vector 1..9 mezclado usando semillas
// ======================================================

std::vector<int> Sudoku::numerosAleatorios() {

    std::vector<int> nums = {1,2,3,4,5,6,7,8,9};

    std::shuffle(nums.begin(), nums.end(), gen1);

    return nums;
}





// ======================================================
// Verifica legalidad
// ======================================================

bool Sudoku::esValido(int fila, int columna, int numero) const {

    // fila
    for (int j = 0; j < 9; ++j) {
        if (tablero[fila][j] == numero)
            return false;
    }

    // columna
    for (int i = 0; i < 9; ++i) {
        if (tablero[i][columna] == numero)
            return false;
    }

    // submatriz
    int inicioFila = (fila / 3) * 3;
    int inicioCol = (columna / 3) * 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {

            if (tablero[inicioFila + i][inicioCol + j] == numero)
                return false;
        }
    }

    return true;
}





// ======================================================
// Backtracking principal
// ======================================================

bool Sudoku::llenarSudoku(int fila, int columna) {

    // terminó
    if (fila == 9)
        return true;

    // siguiente posición
    int siguienteFila = fila;
    int siguienteColumna = columna + 1;

    if (siguienteColumna == 9) {
        siguienteColumna = 0;
        siguienteFila++;
    }

    // orden aleatorio por semilla
    std::vector<int> nums = numerosAleatorios();

    // intenta números
    for (int numero : nums) {

        if (esValido(fila, columna, numero)) {

            tablero[fila][columna] = numero;

            if (llenarSudoku(siguienteFila, siguienteColumna))
                return true;

            // revertir
            tablero[fila][columna] = 0;
        }
    }

    return false;
}





// ======================================================
// Máscara
// ======================================================

void Sudoku::generarMascaraBinaria() {

    mascara = std::vector<std::vector<int>>(9, std::vector<int>(9));

    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < 9; ++i) {

        for (int j = 0; j < 9; ++j) {

            mascara[i][j] = (dist(gen3) <= 25) ? 1 : 0;
        }
    }
}





// ======================================================
// Tensor
// ======================================================

void Sudoku::construirTensor() {

    tensor3D.clear();

    tensor3D.push_back(tablero);

    tensor3D.push_back(mascara);
}





// ======================================================
// Crear Sudoku
// ======================================================

void Sudoku::crearSudoku() {

    llenarSudoku(0, 0);

    generarMascaraBinaria();

    construirTensor();
}





// ======================================================
// Imprimir solución
// ======================================================

void Sudoku::imprimirSolucion() const {

    std::cout << "=== SOLUCION ===\n";

    for (int i = 0; i < 9; ++i) {

        if (i % 3 == 0 && i != 0)
            std::cout << "------+-------+------\n";

        for (int j = 0; j < 9; ++j) {

            if (j % 3 == 0 && j != 0)
                std::cout << "| ";

            std::cout << tensor3D[0][i][j] << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}





// ======================================================
// Imprimir juego
// ======================================================

void Sudoku::imprimirSudoku() const {

    std::cout << "=== JUEGO ===\n";

    for (int i = 0; i < 9; ++i) {

        if (i % 3 == 0 && i != 0)
            std::cout << "------+-------+------\n";

        for (int j = 0; j < 9; ++j) {

            if (j % 3 == 0 && j != 0)
                std::cout << "| ";

            if (tensor3D[1][i][j] == 1)
                std::cout << tensor3D[0][i][j] << " ";
            else
                std::cout << "[]";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

bool Sudoku::esValidoParalelo(
    const std::vector<std::vector<int>>& t,
    int fila,
    int columna,
    int numero
) const {

    std::atomic<bool> valido(true);

    // ==========================================
    // HILO FILA
    // ==========================================

    std::thread hiloFila([&]() {

        for (int j = 0; j < 9; ++j) {

            if (t[fila][j] == numero) {

                valido = false;
                return;
            }
        }
    });

    // ==========================================
    // HILO COLUMNA
    // ==========================================

    std::thread hiloColumna([&]() {

        for (int i = 0; i < 9; ++i) {

            if (t[i][columna] == numero) {

                valido = false;
                return;
            }
        }
    });

    // ==========================================
    // HILO SUBMATRIZ
    // ==========================================

    std::thread hiloSubmatriz([&]() {

        int inicioFila = (fila / 3) * 3;
        int inicioCol = (columna / 3) * 3;

        for (int i = 0; i < 3; ++i) {

            for (int j = 0; j < 3; ++j) {

                if (t[inicioFila + i][inicioCol + j] == numero) {

                    valido = false;
                    return;
                }
            }
        }
    });

    hiloFila.join();
    hiloColumna.join();
    hiloSubmatriz.join();

    return valido;
} 

bool Sudoku::resolverBacktracking(
    std::vector<std::vector<int>>& t,
    int fila,
    int columna
) {

    if (fila == 9)
        return true;

    int siguienteFila = fila;
    int siguienteCol = columna + 1;

    if (siguienteCol == 9) {

        siguienteCol = 0;
        siguienteFila++;
    }

    if (t[fila][columna] != 0) {

        return resolverBacktracking(
            t,
            siguienteFila,
            siguienteCol
        );
    }

    for (int num = 1; num <= 9; ++num) {

        if (esValidoParalelo(t, fila, columna, num)) {

            t[fila][columna] = num;

            if (resolverBacktracking(
                t,
                siguienteFila,
                siguienteCol
            )) {
                return true;
            }

            t[fila][columna] = 0;
        }
    }

    return false;
}

bool Sudoku::resolverSudokuParalelo(
    std::vector<std::vector<std::string>>& sudokuJuego
) {

    auto tableroResolver =
        convertirJuegoAEnteros(sudokuJuego);

    bool resuelto =
        resolverBacktracking(
            tableroResolver,
            0,
            0
        );

    if (!resuelto)
        return false;

    // copiar solución
    for (int i = 0; i < 9; ++i) {

        for (int j = 0; j < 9; ++j) {

            sudokuJuego[i][j] =
                std::to_string(tableroResolver[i][j]);
        }
    }

    return true;
}
