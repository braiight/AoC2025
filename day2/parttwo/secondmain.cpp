#include <fstream>
#include <string>
#include <iostream>

int main(void)
{
    std::ifstream inputFile("allnums.txt");
    std::string line;
    unsigned long res = 0;
    while (std::getline(inputFile, line))
    {
        unsigned long current = atol(line.c_str());
        res += current;
    }
    std::cout << res;
    inputFile.close();
}