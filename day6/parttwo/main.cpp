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



size_t  doOperation(size_t *i, std::string firstLine, std::string secondLine, std::string thirdLine, std::string fourthLine, std::string opLine)
{
    size_t pos = *i;
    char Op = opLine[pos];
    std::vector<std::vector<size_t> > nums;
    size_t res = 0;
    while (pos < opLine.length() && (!isspace(firstLine[pos]) || !isspace(secondLine[pos]) || !isspace(thirdLine[pos]) || !isspace(fourthLine[pos]) || !isspace(opLine[pos])))
    {
        std::vector<char> currentNums;
        if (isdigit(firstLine[pos]))
            currentNums.push_back(firstLine[pos]);
        if (isdigit(secondLine[pos]))
            currentNums.push_back(secondLine[pos]);
        if (isdigit(thirdLine[pos]))
            currentNums.push_back(thirdLine[pos]);
        if (isdigit(fourthLine[pos]))
            currentNums.push_back(fourthLine[pos]);
        size_t fullNum = 0;
        size_t pow = 1;
        for (std::vector<char>::reverse_iterator ite = currentNums.rbegin(); ite != currentNums.rend(); ite++)
        {
            fullNum += ((*ite) - 48) * pow;
            pow *= 10;
        }
        if (Op == '+')
            res += fullNum;
        else
        {
            if (res == 0)
                res = fullNum;
            else
                res *= fullNum;
        }
        pos++;
    }
    *i = pos + 1;
    return (res);

}



int main(int argc, char **argv)
{
    std::ifstream inputFile(argv[1]);

    std::string firstLine;
    std::string secondLine;
    std::string thirdLine;
    std::string fourthLine;
    std::string opLine;
    size_t res = 0;


    std::getline(inputFile, firstLine);
    std::getline(inputFile, secondLine);
    std::getline(inputFile, thirdLine);
    std::getline(inputFile, fourthLine);
    std::getline(inputFile, opLine);

    size_t i = 0;
    while (i < firstLine.length())
    {
        std::cout << "current result is " << res << std::endl;
        res += doOperation(&i, firstLine, secondLine, thirdLine, fourthLine, opLine);
    }

    std::cout << "Sum of operations is: " << res << "\n";
    return (0);

}