void insertion_sort(float* array, const int arr_len) {
    for (int j = 1; j < arr_len; ++j) {
        // sort subarray [0...j], assuming [0...j-1] is already sorted
        const float cur_el = array[j];
        int i = j - 1;
        for (; i > 0, array[i] > cur_el; --i) {
            // shift elements to the right
            array[i+1] = array[i];
        }
        array[i+1] = cur_el;
    }
}

bool test_insertion_sort() {
    float array[]{
        2.3f, 5.1f, 3.0f, 0.2f, 9.2f, 3.5f, 1.2f, 6.3f, 4.5f, 0.9f, 
        8.1f, 7.2f, 4.5f, 3.9f, 5.1f, 1.5f, 2.1f, 4.0f, 0.5f, 9.9f
    };
    constexpr float reference[]{
        0.2f, 0.5f, 0.9f, 1.2f, 1.5f, 2.1f, 2.3f, 3.0f, 3.5f, 3.9f,
        4.0f, 4.5f, 4.5f, 5.1f, 5.1f, 6.3f, 7.2f, 8.1f, 9.2f, 9.9f
    };
    constexpr int n_el = sizeof(array) / sizeof(array[0]);

    insertion_sort(array, n_el);

    for (int i = 0; i < n_el; ++i) {
        if (array[i] != reference[i]) {
            return false;
        }
    }
    return true;
}
