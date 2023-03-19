#include <algorithm>
#include <iostream>

template <typename T>
T* counting_sort(T*& arr, const size_t size)
{
    int helper_size = *std::max_element(arr, (arr + size)) + 1;
    T *helper = new T[helper_size], *out = new T[size];
    std::for_each(out, out + size, [](T& elem) { elem = 0; });
    std::for_each(helper, helper + helper_size, [](T& elem) { elem = 0; });
    std::for_each(arr, arr + size, [&helper](const T& val) { ++helper[val]; });

    for (size_t i = 1; i != helper_size; ++i) {
        helper[i] += helper[i - 1];
    }

    for (int i = 0; i < size; ++i) {
        out[--helper[arr[i]]] = arr[i];
    }

    delete[] helper;

    return out;
}
