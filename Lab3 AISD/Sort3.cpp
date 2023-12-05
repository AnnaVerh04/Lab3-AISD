#include <iostream>
#include <vector>
#include <string>
#include "Sort1.h"

int main()
{
    stats sortingState;


    std::vector<std::string> vec = { "a", "d", "w", "h", "e"};
    sortingState = shellSort(vec.begin(), vec.end());


    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    std::cout << sortingState.comparison_count << "\n";
    std::cout << sortingState.copy_count << "\n";


}