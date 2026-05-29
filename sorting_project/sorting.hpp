#ifndef SORTING_HPP
#define SORTING_HPP

#include <chrono>
#include <functional>
#include <random>
#include <vector>

namespace sorting {

std::vector<int> generateRandomArray(size_t size, int minValue = 0, int maxValue = 100000);
void printArray(const std::vector<int>& arr);

void quicksort(std::vector<int>& arr);
void mergesort(std::vector<int>& arr);

double measureSortTime(std::vector<int> arr, const std::function<void(std::vector<int>&)>& sortFunc);

} // namespace sorting

#endif // SORTING_HPP
