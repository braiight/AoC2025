#include <iostream>
#include <string>
#include <fstream>

int main(void)
{
    std::ifstream inputFile("test.txt");

    std::string line;
    bool direction;

    int current = 50;
    int res = 0;
    while (std::getline(inputFile, line))
    {
        if (line[0] == 'L')
            direction = false;
        else
            direction = true;
        std::string num = line.substr(1);
        int numnum = atoi(num.c_str());
        numnum = numnum % 100;
        if (direction)
            current += numnum;
        else
        {
            current -= numnum;
            if (current < 0)
                current += 100;
        }
        current = current % 100;
        if (current == 0)
            res++;
    }
    std::cout << res;
}