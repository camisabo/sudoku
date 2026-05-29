#include "sorting.hpp"
#include <iostream>

namespace sorting {

std::vector<int> generateRandomArray(size_t size, int minValue, int maxValue) {
    std::vector<int> arr;
    arr.reserve(size);
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    for (size_t i = 0; i < size; ++i) {
        arr.push_back(dist(engine));
    }
    return arr;
}

void printArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i + 1 < arr.size()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void quicksort(std::vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    std::function<void(int, int)> quickSortRecursive;
    quickSortRecursive = [&](int left, int right) {
        if (left >= right) {
            return;
        }

        int pivot = arr[(left + right) / 2];
        int i = left;
        int j = right;

        while (i <= j) {
            while (arr[i] < pivot) {
                ++i;
            }
            while (arr[j] > pivot) {
                --j;
            }
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                ++i;
                --j;
            }
        }

        if (left < j) {
            quickSortRecursive(left, j);
        }
        if (i < right) {
            quickSortRecursive(i, right);
        }
    };

    quickSortRecursive(0, static_cast<int>(arr.size() - 1));
}

void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    mergeSortRecursive(arr, left, middle);
    mergeSortRecursive(arr, middle + 1, right);
    merge(arr, left, middle, right);
}

void mergesort(std::vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }
    mergeSortRecursive(arr, 0, static_cast<int>(arr.size() - 1));
}

double measureSortTime(std::vector<int> arr, const std::function<void(std::vector<int>&)>& sortFunc) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

} // namespace sorting
