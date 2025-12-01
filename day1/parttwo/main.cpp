#include <iostream>
#include <string>
#include <fstream>

int main(void)
{
    std::ifstream inputFile("input.txt");

    std::string line;
    bool direction;

    int current = 50;
    int res = 0;
    int step = 0;
    while (std::getline(inputFile, line))
    {
        step++;
        std::cout << "Starting step " << step << ": arrow pointing at : " << current << "\n";
        if (line[0] == 'L')
            direction = false;
        else
            direction = true;
        

        std::cout << "current line is : " << line << "\n";

        std::string num = line.substr(1);
        int numnum = atoi(num.c_str());


        if (direction)
        {
            std::cout << "adding " << numnum << " to " << current << "\n";
            current += numnum;
            while (current >= 100)
            {
                std::cout << "Pointing at 0!\n";
                current -= 100;
                res++;
            }
        }
        else
        {
            if (current == 0)
                res--;
            std::cout << "subtracting " << numnum << " from " << current << "\n";
            current -= numnum;
            while (current < 0)
            {
                std::cout << "Pointing at 0!\n";
                current += 100;
                res++;
            }
            if (current == 0)
            {
                std::cout << "Ending on 0 after subtraction\n";
                res++;
            }
        }
    }
    std::cout << res;
}