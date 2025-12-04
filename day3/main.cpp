#include <iostream>
#include <string>
#include <fstream>
#include <stack>

int main(void)
{
    std::ifstream inputFile("input.txt");
    std::string line;
    int res = 0;
    std::stack<char> current;
    while (std::getline(inputFile, line))
    {
        int i = 0;
        while (!current.empty())
        {
            current.pop();
        }
        current.push(line[i]);
        char currentTens = line[i];
        i++;
        current.push(line[i]);
        char currentUnits = line[i];
        while (i < line.length())
        {
            if (line[i] > currentTens && i < line.length() - 1)
            {
                while (!current.empty())
                    current.pop();
                current.push(line[i]);
                currentTens = line[i];
                current.push(line[i + 1]);
                currentUnits = line[i + 1];
                i++;
                continue;
            }
            if (line[i] > current.top())
            {
                current.pop();
                if (line[i] > current.top() && i < line.length() - 1)
                {
                    current.pop();
                    current.push(line[i]);
                    current.push(line[i + 1]);
                    currentTens = line[i];
                    currentUnits = line[i + 1];
                }
                else
                {
                    current.push(line[i]);
                    currentUnits = line[i];
                }
            }
            i++;
        }
        std::cout << "finished reading, maximum is: " << currentTens << currentUnits << std::endl;
        res += (current.top() - 48);
        current.pop();
        res += ((current.top() - 48) * 10);
        // std::cout << "res is :" << res << std::endl;
    }
    std::cout << res;
}