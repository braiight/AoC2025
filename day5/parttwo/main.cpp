#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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

    size_t freshIDSum = 0;
    std::sort(ranges.begin(), ranges.end());
    std::cout << "finished sorting pairs!\n";

    freshIDSum += ((*ranges.begin()).second - (*ranges.begin()).first) + 1;

    size_t biggest = (*ranges.begin()).second;

    int lineCount = 0;
    for (std::vector<std::pair<size_t, size_t> >::iterator it = ranges.begin() + 1; it != ranges.end(); it++)
    {
        std::cout << "Currently on line: " << lineCount << "\n";
        if ((*it).first > biggest)
        {
            freshIDSum += ((*it).second - (*it).first) + 1;
        }
        else if ((*it).second <= biggest)
            continue;
        else
        {
            freshIDSum += (*it).second - biggest;
        }

        if (biggest < (*it).second)
            biggest = (*it).second;

        lineCount++;

    }
    std::cout << "Sum of Fresh IDs: " << freshIDSum << std::endl;
    return (0);

}

//wrong answer: 354421761261318