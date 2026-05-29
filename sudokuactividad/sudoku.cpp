#include "crearsudoku.hpp"
#include <thread> //para los hilos
#include <atomic> //para las variables atómicas
#include <mutex> //para los mutex

int main() {
    Sudoku juego(1, 1, 1);
    
    juego.crearSudoku();
    
    juego.imprimirSolucion();
    juego.imprimirSudoku();
    auto a = juego.obtenerSudokuJuego();
    /*
    std::cout << "=== JUEGO ===\n";
    for (const auto& fila : a) {
        for (const auto& celda : fila) {
            std::cout << celda << " ";
        }
        std::cout << "\n";
    }
    */

    bool ok = juego.resolverSudokuParalelo(a);

    std::cout <<ok << "\n";

    if (ok) {

        std::cout << "\n=== RESUELTO ===\n";

        for (const auto& fila : a) {

            for (const auto& celda : fila) {

                std::cout << celda << " ";
            }

            std::cout << "\n";
        }

    } else {

        std::cout << "No se pudo resolver\n";
    }

    return 0;
}