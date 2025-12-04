#include <iostream>
#include <string>
#include <fstream>
#include <stack>


char find_highest(std::string line, int *newStart, int endingPos)
{
    int startingPos = *newStart;
    char highest = line[startingPos];
    *newStart = startingPos + 1;
    while (startingPos <= endingPos)
    {
        if (highest < line[startingPos])
        {
            highest = line[startingPos];
            *newStart = startingPos + 1;
        }
        startingPos++;
    }
    return (highest);
}




int main(void)
{
    std::ifstream inputFile("input.txt");
    std::string line;
    long long unsigned int res = 0;
    std::stack<char> current;
    while (std::getline(inputFile, line))
    {
        int i = 0;
        int lastPos = 0;
        while (current.size() < 12)
        {
            char highest = find_highest(line, &lastPos, line.length() - (12 - current.size()));
            current.push(highest);
        }

        long long unsigned int pow = 1;
        while (!current.empty())
        {
            // std::cout << "res is : " << res << std::endl;
            res += ((current.top() - 48) * pow);
            current.pop();
            pow *= 10;
        }
        // std::cout << "res is :" << res << std::endl;
    }
    std::cout << res;
}