#include <iostream>

template <typename T>
size_t partition(T* arr, size_t beg, size_t end)
{
    T pivot = arr[end];
    size_t i = beg;
    for (size_t x = beg; x != end; ++x) {
        if (arr[x] < pivot) {
            std::swap(arr[x], arr[i]);
            ++i;
        }
    }
    std::swap(arr[i], arr[end]);
    return i;
}

template <typename T>
void quick_sort(T* arr, size_t beg, size_t end)
{
    if (beg < end) {
        size_t pivot = partition(arr, beg, end);
        quick_sort(arr, beg, pivot - 1);
        quick_sort(arr, pivot + 1, end);
    }
}
