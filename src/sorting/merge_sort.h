#include <algorithm>
#include <cstring>
#include <limits>
#include <iostream>


void merge(float* const arr, const int low, const int mid, const int high, float* const buffer) {
    const int num_l = mid - low;
    const int num_r = high - mid;
    
    float* const l_arr = buffer;
    float* const r_arr = &buffer[num_l + 1];

    memcpy(l_arr, &arr[low], num_l * sizeof(float));
    memcpy(r_arr, &arr[mid], num_r * sizeof(float));

    // set last auxiliary elements to infinity.
    const float inf = std::numeric_limits<float>::infinity();
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

void merge(float* const arr, const int low, const int mid, const int high) {
    float* const buffer = new float[high - low + 2];
    merge(arr, low, mid, high, buffer);
    delete[] buffer;
}

void merge_sort(float* const arr, const int low, const int high) {
    if (high - low > 1) {
        const int mid = (low + high) / 2;

        merge_sort(arr, low, mid);
        merge_sort(arr, mid, high);
        merge(arr, low, mid, high);
    }
}

void merge_sort(float* const arr, const int low, const int high, float* const buffer) {
    if (high - low > 1) {
        const int mid = (low + high) / 2;

        merge_sort(arr, low, mid, buffer);
        merge_sort(arr, mid, high, buffer);
        merge(arr, low, mid, high, buffer);
    }
}

void merge_sort_shared_buffer(float* const arr, const int low, const int high) {
    const int mid = (low + high) / 2;
    const int buf_len = std::max(high - mid, mid - low) + 2;

    if (buf_len > 0) {
        float* const buffer = new float[buf_len];
        merge_sort(arr, low, high, buffer);
    }
}

void test_merge() {

    float arr[]{
        0.0f, 0.5f, 1.5f, 2.0f, 2.5f, 
        8.7f, 3.2f, 0.2f, 9.0f, 6.2f,
        3.0f, 3.5f, 4.0f, 8.0f, 9.9f, 
        7.1f, 3.9f, 5.2f, 1.8f, 8.6f,
        0.1f, 0.7f, 1.1f, 1.7f, 2.3f, 
        2.7f, 3.9f, 4.2f, 6.1f, 9.2f
    };

    constexpr int num_el = sizeof(arr) / sizeof(arr[0]);

    merge_sort_shared_buffer(arr, 0, num_el);

    for (int i = 0; i < num_el; ++i) {
        std::cout << i << ": " << arr[i] << std::endl;
    }
}
