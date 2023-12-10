#include <iostream>
#include <vector>
#include <string>
#include <random>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};


stats selectionSort(std::vector<int>& data) {

    stats sortingState;

    int minIndex = 0;

    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        minIndex = i;
        for (size_t j = i + 1; j < data.size(); ++j) {
            ++sortingState.comparison_count;
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }

        std::swap(data[i], data[minIndex]);
        ++sortingState.copy_count;
    }

    return sortingState;
}


template<typename Iterator>
stats selectionSort(Iterator begin, Iterator end) {

    stats sortingState;

    auto minIndex = begin;

    for (auto i = begin; i != end; ++i)
    {
        minIndex = i;

        for (auto j = i + 1; j != end; ++j) {
            ++sortingState.comparison_count;
            if (*j < *minIndex) {
                minIndex = j;
            }
        }

        std::iter_swap(i, minIndex);
        ++sortingState.copy_count;
    }

    return sortingState;
}


stats shellSort(std::vector<int>& data) {
    stats sortingState;

    for (int s = data.size() / 2; s > 0; s /= 2)    
    {
        for (int i = s; i < data.size(); ++i) { 
            for (int j = i - s; j >= 0; j -= s)   
            {
                ++sortingState.comparison_count;
                if (data[j] > data[j + s])
                {
                    std::swap(data[j], data[j + s]);
                    ++sortingState.copy_count;
                }
            }
        }
    }

    return sortingState;
}

template <typename Iterator>
stats shellSort(Iterator begin, Iterator end) {
    stats sorting_stats;

    auto n = std::distance(begin, end);

    for (auto s = n / 2; s > 0; s /= 2) {
        for (auto i = begin + s; i != end; ++i) {
            for (auto j = i; j >= begin + s && *j < *(j - s); j -= s) {
                ++sorting_stats.comparison_count;
                std::iter_swap(j, j - s);
                ++sorting_stats.copy_count;
            }
        }
    }

    return sorting_stats;
}

void heapfy(std::vector<int>& data, int n, int i, stats& sortingState) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    ++sortingState.comparison_count;
    if (left < n && data[left] > data[largest]) {
        largest = left;
    }

    ++sortingState.comparison_count;
    if (right < n && data[right] > data[largest])
    {
        largest = right;
    }

    ++sortingState.comparison_count;
    if (largest != i)
    {
        std::swap(data[i], data[largest]);
        ++sortingState.copy_count;
        heapfy(data, n, largest, sortingState);
    }

}

stats heapSort(std::vector<int>& data) {

    stats sortingState;


    int n = data.size();

    for (int i = n / 2 - 1; i >= 0; --i)  
    {
        heapfy(data, n, i, sortingState);
    }

    for (int i = n - 1; i > 0; --i)
    {
        std::swap(data[0], data[i]);
        ++sortingState.copy_count;
        heapfy(data, i, 0, sortingState);
    }


    return sortingState;

}


template <typename Iterator>
void heapify(Iterator begin, Iterator end, size_t n, size_t i, stats& sortingState) {
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;

    ++sortingState.comparison_count;
    if (left < n && *(begin + left) > *(begin + largest)) {
        largest = left;
    }

    ++sortingState.comparison_count;
    if (right < n && *(begin + right) > *(begin + largest)) {
        largest = right;
    }

    ++sortingState.comparison_count;
    if (largest != i) {
        std::swap(*(begin + i), *(begin + largest));
        ++sortingState.copy_count;
        heapify(begin, end, n, largest, sortingState);
    }
}

template <typename Iterator>
stats heapSort(Iterator begin, Iterator end) {
    stats sortingState;

    auto n = std::distance(begin, end);

    for (auto i = n / 2 - 1; i >= 0; --i) {
        heapify(begin, end, n, i, sortingState);
    }

    for (auto i = n - 1; i > 0; --i) {
        std::swap(*begin, *(begin + i));
        ++sortingState.copy_count;
        heapify(begin, end, i, 0, sortingState);
    }

    return sortingState;
}

int random(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(x, y);
    return dist(gen);
}

std::vector<int> generateRandomArray(size_t size) {
    std::vector<int> res;

    for (size_t i = 0; i < size; i++)
    {
        res.push_back(random(0, 100));
    }
    return res;
}


std::vector<int> generateSortArray(size_t size) {
    std::vector<int> res;

    for (size_t i = 0; i < size; i++)
    {
        res.push_back(i);
    }
    return res;
}


std::vector<int> generateReverseSortArray(size_t size) {
    std::vector<int> res;

    for (size_t i = size; i > 0; --i)
    {
        res.push_back(i);
    }
    return res;
}

stats runExperiment(std::vector<int>& data, int scenario, stats(*pointerToSort)(std::vector<int>& data)) {
    stats sortingState;

    if (scenario == 1) {
        data = generateRandomArray(data.size());
    }
    else if (scenario == 2) {
        data = generateSortArray(data.size());
    }
    else if (scenario == 3) {
        data = generateReverseSortArray(data.size());
    }

    sortingState = pointerToSort(data);

    return sortingState;
}