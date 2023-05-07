#include "FineGrainedQueue.h"

FineGrainedQueue::FineGrainedQueue() : head(nullptr)
{
    srand(time(NULL));
    queue_mutex = new std::mutex();
}

FineGrainedQueue::~FineGrainedQueue()
{
    queue_mutex->lock();
    Node * ptr = head;
    while (head != nullptr)
    {
        head = head->next;
        delete ptr;
        ptr = head;
    }
    queue_mutex->unlock();
    delete queue_mutex;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    if (pos < 0)
    {
        return;
    }
    queue_mutex->lock();
    if (head == nullptr)
    {
        head = new Node(value);
        queue_mutex->unlock();
        return;
    }
    if (pos < 0)
    {
        queue_mutex->unlock();
        return;
    }
    if (pos == 0)
    {
        Node * buf = head;
        head = new Node(value);
        head->next = buf;
        queue_mutex->unlock();
        return;
    }
    Node * prev = head; 
    Node * cur = head->next;
    prev->node_mutex->lock();
    if (cur != nullptr)
    {
        cur->node_mutex->lock();
    }
    else
    {
        head->next = new Node(value);
        prev->node_mutex->unlock();
        queue_mutex->unlock();
        return;
    }
    queue_mutex->unlock();
    int count = 1;
    while (true)
    {
        if (count == pos)
        {
            Node * new_node = new Node(value);
            new_node->next = cur;
            prev->next = new_node;
            prev->node_mutex->unlock();
            cur->node_mutex->unlock();
            break;
        }
        if (cur->next == nullptr)
        {
            cur->next = new Node(value);
            prev->node_mutex->unlock();
            cur->node_mutex->unlock();
            break;
        }
        Node * old_prev = prev;
        prev = cur;
        cur = cur->next;
        old_prev->node_mutex->unlock();
        cur->node_mutex->lock();
        count++;
    }
}

void FineGrainedQueue::showNodes()
{
    Node * ptr = head;
    while (ptr != nullptr)
    {
        std::cout << ptr->value << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}