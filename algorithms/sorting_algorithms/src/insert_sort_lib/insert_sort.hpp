#include <iostream>

template <typename T>
void insertion_sort(T*& arr, int size)
{
    for (int i = 1; i < size; ++i) {
        int swapping_cnter = i;
        while (arr[swapping_cnter] < arr[swapping_cnter - 1]) {
            std::swap(arr[swapping_cnter], arr[swapping_cnter - 1]);
            --swapping_cnter;
        }
    }
}
