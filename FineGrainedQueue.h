#pragma once

#include "Node.h"
#include <iostream>
#include <cstdio>
#include <ctime>

class FineGrainedQueue
{
private:
    Node * head;
    std::mutex* queue_mutex;
public:
    FineGrainedQueue();
    ~FineGrainedQueue();
    void insertIntoMiddle(int, int);
    void showNodes();
};