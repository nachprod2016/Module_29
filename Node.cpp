#include "Node.h"

Node::Node(int value) : value(value), next(nullptr)
{
    node_mutex = new std::mutex();
}

Node::~Node()
{
    delete node_mutex;
}