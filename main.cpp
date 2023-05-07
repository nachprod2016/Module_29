#include <iostream>
#include <string>
#include "Test.h"

int main()
{
    std::string buf;
    while (true)
    {
        std::cout << "1 - Запустить тест списка" << std::endl;
        std::cout << "0 - Завершить программу" << std::endl;
        std::cin >> buf;
        if (buf == "1")
        {
            std::cout << "Введите количество узлов списка: ";
            std::cin >> buf;
            int num = atoi(&buf[0]);
            if (num == 0)
            {
                continue;
            }
            FineGrainedQueue f;
            Test test(f, num);
            test.runTest();
            std::cout << "Содержимое списка: ";
            f.showNodes();
        }
        else if (buf == "0")
        {
            break;
        }
    }
    return 0;
}