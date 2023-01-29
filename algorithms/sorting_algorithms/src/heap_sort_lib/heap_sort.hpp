#include <iostream>

#include "Heap.hpp"

template <typename T>
void heap_sort(T*& arr, size_t size)
{
    Heap<T, bool> heap(size);

    for (size_t x = 0; x < size; ++x) {
        heap.insert(arr[x], 0);
    }

    for (int i = size - 1; i >= 0; --i) {
        arr[i] = heap.extract_max().first;
    }
}
