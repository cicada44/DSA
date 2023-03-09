// #include "../../bubble_sort_lib/bubble_sort.hpp"
// #include "../../insert_sort_lib/insert_sort.hpp"
// #include "../../quick_sort_lib/quick_sort.hpp"
// #include "../../merge_sort_lib/merge_sort.hpp"
// #include "../../heap_sort_lib/heap_sort.hpp"

#include <iostream>

int main()
{
    int* arr = new int[10]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // merge_sort(arr, 0, 9);
    // heap_sort(arr, 10);

    for (int x = 0; x < 10; x++) {
        std::cout << arr[x] << ' ';
    }

    std::cout << '\n';

    delete[] arr;

    return 0;
}