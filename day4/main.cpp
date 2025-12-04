#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<char> >  createGrid(const char *file)
{
    std::vector<std::vector<char> > grid;
    std::ifstream inputFile(file);

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<char> current;
        for (int i = 0; i < line.length(); i++)
            current.push_back(line[i]);
        grid.push_back(current);
    }
    inputFile.close();
    return(grid);
}

void    drawMap(std::vector<std::vector<char> > map)
{
    for (std::vector<std::vector<char> >::iterator it = map.begin(); it != map.end(); it++)
    {
        std::vector<char> current = *it;
        for (std::vector<char>::iterator its = current.begin(); its != current.end(); its++)
        {
            std::cout << *its;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


bool    isRoll(int x, int y, std::vector<std::vector<char> >map)
{
    if (map[y][x] == '@')
        return (true);
    return (false);
}

int numNeighbors(int x, int y, std::vector<std::vector<char> >map)
{
    int y_limit = map.size() - 1;
    int x_limit = (*map.begin()).size() - 1;

    int res = 0;

    //check three neighbors above
    if (y > 0)
    {
        if (x > 0)
        {
            if (isRoll(x - 1, y - 1, map))
                res++;
        }
        if (isRoll(x, y - 1, map))
            res++;
        if (x < x_limit)
        {
            if (isRoll(x + 1, y - 1, map))
                res++;
        }
    }
    //check to the left and right
    if (x > 0)
    {
        if (isRoll(x - 1, y, map))
            res++;
    }
    if (x < x_limit)
    {
        if (isRoll(x + 1, y, map))
            res++;
    }
    //check neighbors below
    if (y < y_limit)
    {
        if (x > 0)
        {
            if (isRoll(x - 1, y + 1, map))
                res++;
        }
        if (isRoll(x, y + 1, map))
            res++;
        if (x < x_limit)
        {
            if (isRoll(x + 1, y + 1, map))
                res++;
        }
    }
    return (res);
}

int getTotalFreeRolls(std::vector<std::vector<char> > &map)
{
    int y_limit = map.size();
    int x_limit = (*map.begin()).size();
    
    int x = 0;
    int y = 0;
    int res = 0;

    std::vector<std::vector<char> > copy(map);
    while (y < y_limit)
    {
        x = 0;
        while (x < x_limit)
        {
            if (isRoll(x, y, map) && numNeighbors(x, y, map) < 4)
            {
                res++;
                copy[y][x] = '.';
            }
            x++;
        }
        y++;
    }
    std::cout << "\n\n";
    // drawMap(copy);
    std::cout << "\n\n";
    map = copy;
    return (res);
}


//wrong answer 8675

int main(void)
{
    std::vector<std::vector<char> > map = createGrid("input.txt");
    // drawMap(map);

    int res = 0;
    int finished = 1;
    
    while (finished)
    {
        finished = getTotalFreeRolls(map);
        res += finished;
        drawMap(map);
    }
    std::cout << res << std::endl;


}