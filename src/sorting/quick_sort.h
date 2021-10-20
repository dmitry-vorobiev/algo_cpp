#include <iostream>

template <typename T>
void quick_sort(T* const arr, const int low, const int high) {
    int i = low;
    int j = high;
    int pivot_idx = (low + high) / 2;
    T pivot = arr[pivot_idx];

    while (i <= j) {
        for (; arr[i] < pivot; i++);
        for (; arr[j] > pivot; j--);

        if (i <= j) {
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (low < j)
        quick_sort(arr, low, j);

    if (i < high)
        quick_sort(arr, i, high);
}

bool test_quick_sort() 
{
    double arr[]{
        8.2, 3.5, 3.4, 2.0, 2.2, 1.4, 0.2, 0.9, 9.2, 6.3, 
        7.2, 5.4, 5.5, 3.8, 2.6, 8.4, 9.2, 4.6, 5.1, 5.8, 
        3.2, 2.6, 5.2, 6.2, 9.9, 2.7, 3.1, 0.1, 4.2, 7.4, 
        3.8, 8.2, 9.3, 0.2, 8.7, 2.2, 7.9, 2.7, 8.1, 3.2, 
        7.7, 7.9, 3.1, 9.6, 1.6, 4.3, 5.2, 3.9, 7.7, 6.4, 
        5.8, 6.2, 4.6, 4.0, 0.2, 1.7, 8.5, 7.3, 7.0, 6.6, 
        5.2, 3.2, 2.1, 0.9, 0.8, 9.8, 9.7, 0.6, 0.0, 5.3, 
        4.1, 6.2, 7.7, 4.2, 4.3, 6.1, 8.6, 0.6, 3.2, 1.5
    };

    constexpr double ref_arr[]{
        0.0, 0.1, 0.2, 0.2, 0.2, 0.6, 0.6, 0.8, 0.9, 0.9, 
        1.4, 1.5, 1.6, 1.7, 2.0, 2.1, 2.2, 2.2, 2.6, 2.6, 
        2.7, 2.7, 3.1, 3.1, 3.2, 3.2, 3.2, 3.2, 3.4, 3.5, 
        3.8, 3.8, 3.9, 4.0, 4.1, 4.2, 4.2, 4.3, 4.3, 4.6, 
        4.6, 5.1, 5.2, 5.2, 5.2, 5.3, 5.4, 5.5, 5.8, 5.8, 
        6.1, 6.2, 6.2, 6.2, 6.3, 6.4, 6.6, 7.0, 7.2, 7.3, 
        7.4, 7.7, 7.7, 7.7, 7.9, 7.9, 8.1, 8.2, 8.2, 8.4, 
        8.5, 8.6, 8.7, 9.2, 9.2, 9.3, 9.6, 9.7, 9.8, 9.9
    };

    constexpr int num_el = sizeof(arr) / sizeof(arr[0]);
    static_assert(sizeof(ref_arr) / sizeof(ref_arr[0]) == num_el);

    quick_sort(arr, 0, num_el - 1);

    for (int i = 0; i < num_el; ++i) 
    {
        if (arr[i] != ref_arr[i])
            return false;
    }
    return true;
}