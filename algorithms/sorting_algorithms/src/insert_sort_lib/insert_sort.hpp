#include <iostream>

template <typename T>
void insertion_sort(T*& arr, int size)
{
    int swapping_cnter;
    for (int i = 1; i < size; ++i) {
        swapping_cnter = i;
        while (swapping_cnter != 0
               && arr[swapping_cnter] < arr[swapping_cnter - 1]) {
            std::swap(arr[swapping_cnter - 1], arr[swapping_cnter]);
            --swapping_cnter;
        }
    }
}
