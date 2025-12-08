#include <string>
#include <fstream>
#include <iostream>



void    processLine(std::string& line, std::string &previousLine, size_t *res)
{
    size_t i = 0;
    while (i < line.length())
    {
        if (previousLine[i] == '|' && line[i] == '.')
            line[i] = '|';
        else if (previousLine[i] == '|' && line[i] == '^')
        {
            line[i - 1] = '|';
            line[i + 1] = '|';
            *res += 1;
        }
        i++;
    }
    previousLine = line;
}





int main(int argc, char **argv)
{
    std::ifstream inputFile(argv[1]);
    std::string line;
    std::string previousLine;

    size_t res = 0;
    std::getline(inputFile, previousLine);
    while (std::getline(inputFile, line))
    {
        std::cout << line << "\n";
        processLine(line, previousLine, &res);
        std::cout << "becomes \n" << line << "\n";
    }
    std::cout << "line is: " << line << "\n";
    std::cout << "beam was split: " << res << " times\n";
}