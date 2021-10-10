#pragma once

void insertion_sort(float* const arr, const int num_el) {
    for (int j = 1; j < num_el; ++j) {
        // sort subarray [0...j], assuming [0...j-1] is already sorted
        const float cur_el = arr[j];
        int i = j - 1;
        for (; i > 0, arr[i] > cur_el; --i) {
            // shift elements to the right
            arr[i+1] = arr[i];
        }
        arr[i+1] = cur_el;
    }
}

bool test_insertion_sort() {
    float arr[]{
        2.3f, 5.1f, 3.0f, 0.2f, 9.2f, 3.5f, 1.2f, 6.3f, 4.5f, 0.9f, 
        8.1f, 7.2f, 4.5f, 3.9f, 5.1f, 1.5f, 2.1f, 4.0f, 0.5f, 9.9f
    };
    constexpr float ref_arr[]{
        0.2f, 0.5f, 0.9f, 1.2f, 1.5f, 2.1f, 2.3f, 3.0f, 3.5f, 3.9f,
        4.0f, 4.5f, 4.5f, 5.1f, 5.1f, 6.3f, 7.2f, 8.1f, 9.2f, 9.9f
    };
    constexpr int num_el = sizeof(arr) / sizeof(arr[0]);

    insertion_sort(arr, num_el);

    for (int i = 0; i < num_el; ++i) {
        if (arr[i] != ref_arr[i]) {
            return false;
        }
    }
    return true;
}
