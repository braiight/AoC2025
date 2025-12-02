#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>



int main(void)
{
    std::ifstream inputFile("halfparsed.txt");
    std::ofstream output("secondpass.txt");
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::string leftNum = line.substr(0, line.find('-'));
        std::string rightNum = line.substr(line.find('-') + 1);
        long low = atol(leftNum.c_str());
        long high = atol(rightNum.c_str());
        while (low <= high)
        {
            output << low << "\n";
            low++;
        }
    }
    inputFile.close();
    output.close();
    return (0);
}