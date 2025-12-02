#include <fstream>
#include <iostream>
#include <string>

int main(void)
{
    std::ifstream inputFile("halfparsed.txt");
    std::string line;
    unsigned long long int res = 0;
    while (std::getline(inputFile, line))
    {
        std::string leftNum = line.substr(0, line.find('-'));
        std::string rightNum = line.substr(line.find('-') + 1);
        long low = atol(leftNum.c_str());
        long high = atol(rightNum.c_str());
        while (low <= high)
        {
            std::string current = std::to_string(low);
            if (current.length() % 2)
            {
                low++;
                continue;
            }
            size_t  halfWay = current.length() / 2;
            std::string firstHalf = current.substr(0, halfWay);
            std::string secondHalf = current.substr(halfWay);
            if (firstHalf == secondHalf)
                res += low;
            low++;
        }
    }
    inputFile.close();
    std::cout << res;
    return (0);
}