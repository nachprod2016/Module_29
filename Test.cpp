#include "Test.h"

Test::Test(FineGrainedQueue & q, int n) : queue(q), numbers(n) 
{
    srand(time(NULL));
    for (int i = 0; i < numbers; i++)
    {
        int value = rand() % 80 + 10;
        int position = rand() % 10;
        std::future<void> f;
        values.push_back(value);
        positions.push_back(position);
        streams.push_back(std::move(f));
    }
}

void Test::runTest()
{
    std::cout << "Числа для вставки: " << std::endl;
    for (int i = 0; i < numbers; i++)
    {
        std::cout << "Поток " << i << " - число: " << values[i] << "   позиция: " << positions[i] << std::endl;;
    }
    std::cout << std::endl;
    for (int i = 0; i < numbers; i++)
    {
        streams[i] = std::async(std::launch::async, [i, this]()
        {
            std::string str1, str2;
            str1 += "Поток " + std::to_string(i);
            str2 += " запущен\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << str1 + str2;
            str2.clear();
            queue.insertIntoMiddle(values[i], positions[i]);
            str2 += " завершен\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << str1 + str2;
        });
    }
    for (int i = 0; i < numbers; i++)
    {
        streams[i].get();
    }
}