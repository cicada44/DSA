// #include "../../bubble_sort_lib/bubble_sort.hpp"
// #include "../../insert_sort_lib/insert_sort.hpp"

#include "../../merge_sort_lib/merge_sort.hpp"

#include "../../quick_sort_lib/quick_sort.hpp"

#include <iostream>

#include <string>

int main()
{
    int* arr = new int[10]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // for (int x = 0; x < 10; x++) {
    //     std::cin >> arr[x];
    // }

    // merge_sort(arr, 0, 10);
    quick_sort(arr, 0, 9);

    for (int x = 0; x < 10; x++) {
        std::cout << arr[x] << ' ';
    }

    std::cout << '\n';

    delete[] arr;

    return 0;
}