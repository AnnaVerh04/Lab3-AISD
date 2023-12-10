#include "Sort1.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>





int main()
{
    std::vector<int> data;
    std::vector<size_t> vecSize = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };
    std::vector<int> scenarios = { 1,2,3 };

    for (auto scenario : scenarios)
    {
        switch (scenario)
        {
        case 1:
            for (auto size : vecSize)
            {
                data.resize(size);
                stats avgStats;

                for (size_t i = 0; i < 100; i++)
                {
                    stats experimentStats = runExperiment(data, scenario, selectionSort);

                    avgStats.comparison_count += experimentStats.comparison_count;
                    avgStats.copy_count += experimentStats.copy_count;
                }

                avgStats.comparison_count /= 100;
                avgStats.copy_count /= 100;

                std::cout << "Vec size: " << size << ", Average comparison_count: " << avgStats.comparison_count << ", Average copy_count: " << avgStats.copy_count << std::endl;
            }
            break;

        case 2:
            data.clear();
            for (auto size : vecSize)
            {
                data.resize(size);
                stats experimentStats = runExperiment(data, scenario, selectionSort);
                std::cout << "Vec size: " << size << ", comparison_count:" << experimentStats.comparison_count << ", copy_count:" << experimentStats.copy_count << std::endl;
            }
            break;

        case 3:
            data.clear();
            for (auto size : vecSize)
            {
                data.resize(size);
                stats experimentStats = runExperiment(data, scenario, selectionSort);
                std::cout << "Vec size: " << size << ", comparison_count:" << experimentStats.comparison_count << ", copy_count:" << experimentStats.copy_count << std::endl;
            }
            break;

        }
    }
}