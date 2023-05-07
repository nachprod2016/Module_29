#pragma once

#include "FineGrainedQueue.h"
#include <vector>
#include <future>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

class Test
{
private:
    FineGrainedQueue & queue;
    std::vector<int> values;
    std::vector<int> positions;
    std::vector<std::future<void>> streams;
    int numbers;
public:
    Test(FineGrainedQueue &, int);
    ~Test() = default;
    void runTest();
};