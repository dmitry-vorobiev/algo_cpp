#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class MaxHeap
{
private:
    std::vector<T> m_data;

public:
    MaxHeap() {}

    MaxHeap(const std::vector<T>&& values)
        :m_data(values)
    {
        _build_heap();
    }

    std::size_t size() const noexcept 
    {
        return m_data.size();
    }

    void add(T value) 
    {
        m_data.push_back(value);

        size_t i = size() - 1;
        size_t parent = (i - 1) / 2;

        while (i > 0 && m_data[parent] < m_data[i])
        {
            _swap_nodes(i, parent);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    T pop_max() 
    {
        T first;

        if (size() > 1)
        {
            first = m_data[0];
            // TODO: replace next two lines with something more elegant
            std::rotate(m_data.begin(), m_data.begin() + 1, m_data.end());
            m_data.pop_back();
            _build_heap();
        }
        else
        {
            first = m_data.size() > 0 ? m_data[0] : 0;
            m_data.empty();
        }
        return first;
    }

private:
    void _build_heap()
    {
        for (size_t i = size() + 1 / 2; i > 0; i--)
            _heapify(i - 1);
    }

    void _heapify(size_t i)
    {
        size_t l_child;
        size_t r_child;
        size_t largest;

        for (;;)
        {
            auto n_el = size();

            l_child = 2 * i + 1;
            r_child = 2 * i + 2;
            largest = i;

            if (l_child < n_el && m_data[l_child] > m_data[largest]) 
                largest = l_child;

            if (r_child < n_el && m_data[r_child] > m_data[largest])
                largest = r_child;

            if (largest == i) 
                break;

            _swap_nodes(i, largest);
            i = largest;
        }
    }

    inline void _swap_nodes(size_t i, size_t j)
    {
        T temp = m_data[i];
        m_data[i] = m_data[j];
        m_data[j] = temp;
    }
};

bool test_heap() {

    std::vector<int> initial_values{
        2, 3, 10, 1, -12, -5, 0, 24, 3, 9, 
        15, 25, 1, 20, 27, 18, 6, -1, 8, 11,
        31, 16, 14, 7, -2, -4, -8, -9, -13, 4
    };
    MaxHeap<int> heap {std::move(initial_values)};

    int added_values[] {
        28, -72, 31, 10, 12, -15, -9, 52, 42, -2,
        29, -35, 45, 19, -8
    };

    for (int value : added_values) {
        heap.add(value);
    }

    auto n_el = heap.size();
    std::cout << "Size: " << n_el << "." << std::endl;

    int last_value = 9000;
    for (int i = 0; i < n_el; i++)
    {
        auto cur_value = heap.pop_max();
        if (last_value < cur_value)
            return false;
        
        last_value = cur_value;
        std::cout << "Max value: " << cur_value << "." << std::endl;
    }
    return true;
}
