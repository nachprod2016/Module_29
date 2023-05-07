#pragma once

#include <mutex>

struct Node
{
  int value;
  Node * next;
  std::mutex* node_mutex;
  Node(int);
  ~Node();
};