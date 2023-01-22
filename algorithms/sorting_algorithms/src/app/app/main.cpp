// #include "../../bubble_sort_lib/bubble_sort.hpp"
// #include "../../insert_sort_lib/insert_sort.hpp"

#include "../../merge_sort_lib/merge_sort.hpp"

#include <iostream>

#include <string>

int main()
{
    std::string* arr = new std::string[10];

    for (int x = 0; x < 10; x++) {
        std::cin >> arr[x];
    }

    merge_sort(arr, 0, 10);

    for (int x = 0; x < 10; x++) {
        std::cout << arr[x] << ' ';
    }

    std::cout << '\n';

    delete[] arr;

    return 0;
}