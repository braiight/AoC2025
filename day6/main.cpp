#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>


std::vector<size_t> parseNumbers(const std::string& line)
{
    std::vector<size_t> numbers;
    std::istringstream stream(line);
    size_t number;

    // Extract numbers from the stream
    while (stream >> number)
    {
        numbers.push_back(number);
    }

    return (numbers);
}

std::vector<char> parseOperator(const std::string& line)
{
    std::vector<char> operators;
    std::istringstream stream(line);
    char op;

    // Extract non-whitespace characters
    while (stream >> op)
    {
        operators.push_back(op);
    }
    return (operators);
}

int main(int argc, char **argv)
{
    std::ifstream inputFile(argv[1]);

    std::string line;

    std::getline(inputFile, line);
    std::vector<size_t> firstLine = parseNumbers(line);
    std::getline(inputFile, line);
    std::vector<size_t> secondLine = parseNumbers(line);
    std::getline(inputFile, line);
    std::vector<size_t> thirdLine = parseNumbers(line);
    std::getline(inputFile, line);
    std::vector<size_t> fourthLine = parseNumbers(line);
    std::getline(inputFile, line);
    std::vector<char> whichOp = parseOperator(line);

    size_t i = 0;
    size_t res = 0;
    while (i < firstLine.size())
    {
        if (whichOp[i] == '+')
        {
            res += firstLine[i];
            res += secondLine[i];
            res += thirdLine[i];
            res += fourthLine[i];
        }
        else
        {
            size_t temp = firstLine[i] * secondLine[i] * thirdLine[i] * fourthLine[i];
            res += temp;
        }
        i++;
    }
    std::cout << "Sum of operations is: " << res << "\n";
    return (0);

}