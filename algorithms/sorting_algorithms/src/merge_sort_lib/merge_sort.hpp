#include <iostream>

template <typename A>
void merge(A* arr, int left, int mid, int right)
{
    A copy_arr[right + 1];
    for (int x = left; x <= right; ++x) {
        copy_arr[x] = arr[x];
    }

    int l = left, r = mid + 1;

    int i = left;

    while (l <= mid && r <= right) {
        if (copy_arr[l] <= copy_arr[r]) {
            arr[i] = copy_arr[l];
            ++l;
        } else {
            arr[i] = copy_arr[r];
            ++r;
        }
        ++i;
    }

    while (l <= mid) {
        arr[i] = copy_arr[l];
        ++i;
        ++l;
    }

    while (r <= right) {
        arr[i] = copy_arr[r];
        ++i;
        ++r;
    }
}

template <typename A>
void merge_sort(A* arr, int beg, int end)
{
    if (beg < end) {
        int l = 0, r = end - 1, mid = (l + r) / 2;

        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }
}