#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <string>

void reverseString(std::string &str, int start, int end)
{
    for (int i = start, j = end; i < j; i++, j--)
    {
        std::swap(str[i], str[j]);
    }
}