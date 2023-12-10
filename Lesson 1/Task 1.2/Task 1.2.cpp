#include <iostream>
#include <thread>
#include <chrono>
#include <execution>
#include <random>
#include <iterator>
#include <vector>

using namespace std::chrono_literals;

void sum_vector(std::vector <int> vec1, std::vector <int> vec2)
{ 
    auto sum = 0;
    auto start = std::chrono::steady_clock::now();
    for (auto it : vec1) { sum += it; }
    for (auto it : vec2) { sum += it; }
    auto finish = std::chrono::steady_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << result.count() << "ms\t\t";
}

int main()
{
    setlocale(0, "");

    std::cout << "\n\t\tЗадача №2. Параллельные вычисления.\n\n";

    std::cout << "Колличество аппаратных ядер - " << std::thread::hardware_concurrency() << ".\n";

    std::cout << "\n\n\t\t" << "1 000\t\t" << "10 000\t\t" << "100 000\t\t" << "1 000 000\n";

    for (int thread = 1; thread <= 16; thread *= 2)
    {
        std::cout << thread << " потоков\t";

        for (int i = 1; i <= thread; i++)
        {          
            for (size_t size = 1000; size <= 1000000; size *= 10)
            {
                std::vector<int> vec1(size);
                std::mt19937 gen1;
                std::uniform_int_distribution<int> dist1(0, size);
                std::generate(std::execution::par, vec1.begin(), vec1.end(), [&]() { return dist1(gen1); });

                std::vector<int> vec2(size);
                std::mt19937 gen2;
                std::uniform_int_distribution<int> dist2(0, size);
                std::generate(std::execution::par, vec2.begin(), vec2.end(), [&]() { return dist2(gen2); });

                std::thread th[i](sum_vector, vec1, vec2);
                th[i].join();
            }
            std::cout << std::endl;
        }
    }
    return 0;
}