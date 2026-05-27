#include "crearsudoku.hpp"
#include <thread> //para los hilos
#include <atomic> //para las variables atómicas
#include <mutex> //para los mutex

int main() {
    // Pasamos 3 semillas numéricas cualesquiera
    Sudoku juego(12341, 5678, 91011);
    
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