#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

thread_local int count=0;

void customer (int value, int &count)
{    
    for (auto i = 0; i < value; i++)
    {
        std::this_thread::sleep_for(1000ms);
        count++;
        std::cout << count << " ";        
    }
}

void operater (int value, int &count)
{    
    for (auto i = value; i > 0; i--)
    {
        std::this_thread::sleep_for(2000ms);
        count--;
        std::cout << count << " ";
    }
}

int main()
{
    setlocale(0, "");
    
    std::cout << "\n\t\tЗадача №1. Очередь клиентов.\n\n";
    
    int value = 10;

    std::cout << "\nКоличество клиентов на запись: " << value;

    std::cout << "\n\nОчередь клиентов: ";

    std::thread th1(customer, value, std::ref(count));
    std::this_thread::sleep_for(10ms);
    std::thread th2(operater, value, std::ref(count));

    th1.join();
    th2.join();

    std::cout << "\n\nОбработка очереди завершена.\n";

    return 0;
}