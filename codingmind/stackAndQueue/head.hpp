#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <limits.h>
#include <deque>

template <class T>
void printVec(const std::vector<T> &vec)
{
    for (auto u : vec)
    {
        std::cout << u << " ";
    }
    std::cout << std::endl;
}