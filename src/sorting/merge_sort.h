#include <algorithm>
#include <cstring>
#include <limits>

template <typename T>
void merge(T* const arr, const int low, const int mid, const int high, T* const buffer) {
    const int num_l = mid - low;
    const int num_r = high - mid;
    
    T* const l_arr = buffer;
    T* const r_arr = &buffer[num_l + 1];

    memcpy(l_arr, &arr[low], num_l * sizeof(arr[0]));
    memcpy(r_arr, &arr[mid], num_r * sizeof(arr[0]));

    // set last auxiliary elements to infinity.
    const T inf = std::numeric_limits<T>::infinity();
    l_arr[num_l] = inf;
    r_arr[num_r] = inf;

    for (int i = 0, j = 0, k = low; k < high; ++k) {
        if (l_arr[i] <= r_arr[j]) {
            arr[k] = l_arr[i];
            ++i;
        } else {
            arr[k] = r_arr[j];
            ++j;
        }
    }
}

template <typename T>
void merge(T* const arr, const int low, const int mid, const int high) {
    T* const buffer = new T[high - low + 2];
    merge(arr, low, mid, high, buffer);
    delete[] buffer;
}

template <typename T>
void merge_sort(T* const arr, const int low, const int high) {
    if (high - low > 1) {
        const int mid = (low + high) / 2;

        merge_sort(arr, low, mid);
        merge_sort(arr, mid, high);
        merge(arr, low, mid, high);
    }
}

template <typename T>
void merge_sort(T* const arr, const int low, const int high, T* const buffer) {
    if (high - low > 1) {
        const int mid = (low + high) / 2;

        merge_sort(arr, low, mid, buffer);
        merge_sort(arr, mid, high, buffer);
        merge(arr, low, mid, high, buffer);
    }
}

template <typename T>
void merge_sort_shared_buffer(T* const arr, const int low, const int high) {
    const int mid = (low + high) / 2;
    const int buf_len = std::max(high - mid, mid - low) + 2;

    if (buf_len > 2) {
        T* const buffer = new T[buf_len];
        merge_sort(arr, low, high, buffer);
    }
}

bool test_merge_sort() {

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

    merge_sort_shared_buffer(arr, 0, num_el);

    for (int i = 0; i < num_el; ++i) 
    {
        if (arr[i] != ref_arr[i])
            return false;
    }
    return true;
}
