#include <iostream>
#include <vector>
#include <iterator>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

void swap(int& i, int& j) {
    int temp = i;

    i = j;
    j = temp;
}

template <typename Iterator>
void mySwap(Iterator i, Iterator j) {
    auto temp = *i;
    *i = *j;
    *j = temp;
}


stats selectionSort(std::vector<int>& data) {

    stats sorting_stats;

    size_t minIndex = 0;
    for (size_t i = 0; i < data.size() - 1; ++i) {
        minIndex = i;

        for (size_t j = i + 1; j < data.size(); ++j) {
            ++sorting_stats.comparison_count;
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }

        swap(data[i], data[minIndex]);
        ++sorting_stats.copy_count;
    }

    return sorting_stats;
}

template <typename Iterator>
stats selectionSort(Iterator begin, Iterator end) {
    stats sorting_stats;

    for (auto i = begin; i != end; ++i) {
        auto minIndex = i;

        for (auto j = i + 1; j != end; ++j) {
            ++sorting_stats.comparison_count;
            if (*j < *minIndex) {
                minIndex = j;
            }
        }

        mySwap(i, minIndex);
        ++sorting_stats.copy_count;
    }

    return sorting_stats;
}
