#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Sudoku {

public:
    Sudoku(int l)
        : llave(l), gen(l)
    {}

    void crearSudoku();

private:

    std::vector<int> numerosAleatorios(int n);

    void imprimirSudoku(
        const std::vector<std::vector<int>>& sudoku
    );

    void intercambiarFilas(
        std::vector<std::vector<int>>& sudoku,
        int r1,
        int r2
    );

    void intercambiarColumnas(
        std::vector<std::vector<int>>& sudoku,
        int c1,
        int c2
    );

    void intercambiarBandas(
        std::vector<std::vector<int>>& sudoku,
        int b1,
        int b2
    );

    void intercambiarStacks(
        std::vector<std::vector<int>>& sudoku,
        int s1,
        int s2
    );

    void transponer(
        std::vector<std::vector<int>>& sudoku
    );

    void permutarNumeros(
        std::vector<std::vector<int>>& sudoku
    );

private:
    int llave;
    std::mt19937 gen;
    std::vector<std::vector<int>> sudoku;
};





std::vector<int> Sudoku::numerosAleatorios(int n) {

    std::vector<int> numeros;

    for (int i = 1; i <= n; i++) {
        numeros.push_back(i);
    }

    std::shuffle(
        numeros.begin(),
        numeros.end(),
        gen
    );

    return numeros;
}





void Sudoku::imprimirSudoku(
    const std::vector<std::vector<int>>& sudoku
) {

    for (int i = 0; i < 9; i++) {

        if (i % 3 == 0 && i != 0) {
            std::cout << "------+-------+------\n";
        }

        for (int j = 0; j < 9; j++) {

            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }

            std::cout << sudoku[i][j] << ' ';
        }

        std::cout << '\n';
    }
}





void Sudoku::intercambiarFilas(
    std::vector<std::vector<int>>& sudoku,
    int r1,
    int r2
) {
    std::swap(sudoku[r1], sudoku[r2]);
}





void Sudoku::intercambiarColumnas(
    std::vector<std::vector<int>>& sudoku,
    int c1,
    int c2
) {

    for (int i = 0; i < 9; i++) {
        std::swap(
            sudoku[i][c1],
            sudoku[i][c2]
        );
    }
}





void Sudoku::intercambiarBandas(
    std::vector<std::vector<int>>& sudoku,
    int b1,
    int b2
) {

    for (int i = 0; i < 3; i++) {

        intercambiarFilas(
            sudoku,
            b1 * 3 + i,
            b2 * 3 + i
        );
    }
}





void Sudoku::intercambiarStacks(
    std::vector<std::vector<int>>& sudoku,
    int s1,
    int s2
) {

    for (int i = 0; i < 3; i++) {

        intercambiarColumnas(
            sudoku,
            s1 * 3 + i,
            s2 * 3 + i
        );
    }
}





void Sudoku::transponer(
    std::vector<std::vector<int>>& sudoku
) {

    for (int i = 0; i < 9; i++) {

        for (int j = i + 1; j < 9; j++) {

            std::swap(
                sudoku[i][j],
                sudoku[j][i]
            );
        }
    }
}





void Sudoku::permutarNumeros(
    std::vector<std::vector<int>>& sudoku
) {

    std::vector<int> nums =
        numerosAleatorios(9);

    for (auto& fila : sudoku) {

        for (auto& num : fila) {

            num = nums[num - 1];
        }
    }
}





inline void Sudoku::crearSudoku() {

    std::vector<std::vector<int>> sudoku(
        9,
        std::vector<int>(9)
    );

    // Sudoku base válido
    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            sudoku[i][j] =
                (i * 3 + i / 3 + j) % 9 + 1;
        }
    }

    std::uniform_int_distribution<int>
        dist(0, 2);

    std::uniform_int_distribution<int>
        boolDist(0, 1);

    int iteraciones =
        100 + (llave % 200);

    for (int k = 0; k < iteraciones; k++) {

        int operacion =
            std::uniform_int_distribution<int>(0, 4)(gen);

        switch (operacion) {

        // intercambiar filas
        case 0: {

            int banda = dist(gen);

            int r1 =
                banda * 3 + dist(gen);

            int r2 =
                banda * 3 + dist(gen);

            intercambiarFilas(
                sudoku,
                r1,
                r2
            );

            break;
        }

        // intercambiar columnas
        case 1: {

            int stack = dist(gen);

            int c1 =
                stack * 3 + dist(gen);

            int c2 =
                stack * 3 + dist(gen);

            intercambiarColumnas(
                sudoku,
                c1,
                c2
            );

            break;
        }

        // intercambiar bandas
        case 2: {

            int b1 = dist(gen);
            int b2 = dist(gen);

            intercambiarBandas(
                sudoku,
                b1,
                b2
            );

            break;
        }

        // intercambiar stacks
        case 3: {

            int s1 = dist(gen);
            int s2 = dist(gen);

            intercambiarStacks(
                sudoku,
                s1,
                s2
            );

            break;
        }

        // transponer
        case 4: {

            if (boolDist(gen)) {

                transponer(sudoku);
            }

            break;
        }

        }
    }

    // cambia visualmente los números
    permutarNumeros(sudoku);

    imprimirSudoku(sudoku);
}