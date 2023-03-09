#include <iostream>

template <typename T>
size_t partition(T* arr, int low, int high)
{
    size_t pivot = arr[high];
    size_t i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    return (i + 1);
}

template <typename T>
void quick_sort(T* arr, int low, int high)
{
    if (low < high) {
        size_t pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
