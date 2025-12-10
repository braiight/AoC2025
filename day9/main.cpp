#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

struct t_tile
{
    int x;
    int y;
};



t_tile createTile(std::string line)
{
    t_tile res;
    std::string xStr = line.substr(0, line.find(','));
    std::string yStr = line.substr(line.find(',') + 1);
    res.x = atoi(xStr.c_str());
    res.y = atoi(yStr.c_str());
    std::cout << "created tile with coordinates " << res.x << "," << res.y << "\n";
    return (res);
}


size_t getArea(t_tile a, t_tile b)
{
    int width = abs(a.x - b.x) + 1;
    int height = abs(a.y - b.y) + 1;
    size_t res = static_cast<size_t>(width) * static_cast<size_t>(height);
    return (res);
}


int main(int argc, char **argv)
{
    std::ifstream inputFile(argv[1]);
    std::string line;

    std::vector<t_tile> tiles;
    while (std::getline(inputFile, line))
    {
        tiles.push_back(createTile(line));
    }
    size_t maxArea = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = i + 1; j < tiles.size(); j++)
        {
            if (getArea(tiles[i], tiles[j]) > maxArea)
            {
                std::cout << "New max area found: point " << tiles[i].x << "," << tiles[i].y << " and " << tiles[j].x << "," << tiles[j].y << "\n";
                maxArea = getArea(tiles[i], tiles[j]);
            }
        }
    }
    std::cout << "Max area found: " << maxArea << "\n";
}