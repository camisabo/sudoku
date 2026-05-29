#include "sorting.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<size_t> sizes = {1000, 5000, 20000};

    std::cout << "Mergesort - Medicion simple de tiempos" << std::endl;
    for (size_t size : sizes) {
        auto arr = sorting::generateRandomArray(size, 0, 100000);
        double ms = sorting::measureSortTime(arr, sorting::mergesort);
        std::cout << "Tamanio " << size << " -> " << ms << " ms" << std::endl;
    }

    std::vector<int> sample = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
    std::cout << "\nEjemplo corto antes:" << std::endl;
    sorting::printArray(sample);
    sorting::mergesort(sample);
    std::cout << "Despues:" << std::endl;
    sorting::printArray(sample);

    return 0;
}
