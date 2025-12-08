#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

int main(int argc, char **argv)
{
    std::ifstream inputFile(argv[1]);

    std::string line;
    std::vector<std::pair<size_t, size_t> > ranges;

    while (std::getline(inputFile, line))
    {
        size_t  separator = line.find('-');
        if (separator == std::string::npos)
        {
            std::cout << "finished building pairs\n";
            break;
        }
        std::string rangeLow = line.substr(0, separator);
        std::string rangeHigh = line.substr(separator + 1);
        std::cout << "range goes from " << rangeLow << " to " << rangeHigh << std::endl;
        std::pair<size_t, size_t> currentRange = std::make_pair(atol(rangeLow.c_str()), atol(rangeHigh.c_str()));
        ranges.push_back(currentRange);

    }

    int sum = 0;

    while (std::getline(inputFile, line))
    {
        size_t toCheck = atol(line.c_str());
        for (std::vector<std::pair<size_t, size_t> >::iterator it = ranges.begin(); it != ranges.end(); it++)
        {
            if (toCheck >= (*it).first && toCheck <= (*it).second)
            {
                std::cout << toCheck << " is fresh\n";
                sum++;
                break;
            }
        }
    }
    std::cout << "total fresh ingredients: " << sum << std::endl;
    return (0);

}