#include "../../src/bubble_sort_lib/bubble_sort.hpp"
#include "../../src/counting_sort_lib/counting_sort.hpp"
#include "../../src/heap_sort_lib/heap_sort.hpp"
#include "../../src/insert_sort_lib/insert_sort.hpp"
#include "../../src/merge_sort_lib/merge_sort.hpp"
#include "../../src/quick_sort_lib/quick_sort.hpp"

#include <gtest/gtest.h>

TEST(Sortings, SortAlgs)
{
    int arr_size = 10;

    // Bubble sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        bubble_sort(arr, arr_size);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(arr[i], i);
        }

        delete[] arr;
    }

    // Insertion sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        insertion_sort(arr, arr_size);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(arr[i], i);
        }

        delete[] arr;
    }

    // Merge sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        merge_sort(arr, 0, arr_size - 1);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(arr[i], i);
        }

        delete[] arr;
    }

    // Heap sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        heap_sort(arr, arr_size);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(arr[i], i);
        }

        delete[] arr;
    }

    // Quick sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        quick_sort(arr, 0, arr_size - 1);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(arr[i], i);
        }

        delete[] arr;
    }

    // Counting sort
    {
        int* arr = new int[arr_size]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        int* out = counting_sort(arr, arr_size);

        for (int i = 0; i != arr_size; ++i) {
            ASSERT_EQ(out[i], i);
        }

        delete[] arr;
        delete[] out;
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
