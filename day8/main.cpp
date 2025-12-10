#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

struct t_point
{
    long long x;
    long long y;
    long long z;
};

struct t_distance
{
    t_point a;
    t_point b;
    int distance;
};

bool    operator==(t_point& a, t_point& b)
{
    if (a.x == b.x && a.y == b.y && a.z == b.z)
        return (true);
    return (false);
}

bool    operator==(t_distance& a, t_distance& b)
{
    if (a.distance == b.distance)
        return (true);
    return (false);
}

bool    operator<(t_distance& a, t_distance& b)
{
    if (a.distance < b.distance)
        return (true);
    return (false);
}

bool    operator>(t_distance& a, t_distance& b)
{
    if (a.distance > b.distance)
        return (true);
    return (false);
}

long long calculateDistance(t_point a, t_point b)
{
    long long dx = b.x - a.x;
    long long dy = b.y - a.y;
    long long dz = b.z - a.z;
    long long distance = dx*dx + dy*dy + dz*dz;
    return (long long)sqrt(distance);
}


class   DSU
{
    public:
        DSU(std::vector<t_point> points);
        ~DSU();
        std::vector<t_distance> getDistances();
        void    unite(t_point &a, t_point &b);
        std::vector<int> getParentLengths();

    private:
        std::vector<t_point>    _parents;
        std::vector<t_point>    _points;
        std::vector<t_distance> _distances;
        
        t_point&    find(t_point& a);
};



std::vector<t_distance> DSU::getDistances()
{
    return (_distances);
}

std::vector<t_distance> createDistances(std::vector<t_point> points)
{
    std::vector<t_distance> res;
    size_t i = 0;
    size_t j = 1;
    while (i < points.size())
    {
        j = i + 1;
        while (j < points.size())
        {
            t_distance dist;
            dist.a = points[i];
            dist.b = points[j];
            dist.distance = calculateDistance(points[i], points[j]);
            res.push_back(dist);
            j++;
        }
        std::cout << "Finished calculating distances for point number " << i << "\n";
        i++;
    }
    std::sort(res.begin(), res.end());
    return (res);
}


DSU::DSU(std::vector<t_point> points)
{
    _points = points;
    _parents.resize(_points.size());
    for (size_t i = 0; i < _parents.size(); i++)
    {
        _parents[i] = _points[i];
    }

    _distances = createDistances(_points);
}

DSU::~DSU()
{}

t_point &DSU::find(t_point& a)
{
    size_t i = 0;
    while (i < _points.size())
    {
        if (a == _points[i])
            break ;
        i++;
    }
    if (_parents[i] == a)
        return (a);
    return (find(_parents[i]));

}

std::vector<int> DSU::getParentLengths()
{
    std::vector<int> numChildren(_parents.size(), 0);
    for (size_t i = 0; i < _points.size(); i++)
    {
        t_point currentParent = find(_points[i]);
        int j = 0;
        while (j < _parents.size())
        {
            if (_parents[j] == currentParent)
                break;
            j++;
        }
        numChildren[j] += 1;
    }
    return (numChildren);
}


void DSU::unite(t_point& a, t_point& b)
{
    t_point aParent = find(a);
    t_point bParent = find(b);
    size_t i = 0;
    while (i < _points.size())  // Search in _points, not _parents
    {
        if (bParent == _points[i])
            break;
        i++;
    }
    _parents[i] = aParent;
    std::cout << "United " << a.x << "," << a.y << "," << a.z << " with " << b.x << "," << b.y << "," << b.z << "\n";
}


t_point createPoint(std::string line)
{
    t_point res;

    std::string xStr = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);
    std::string yStr = line.substr(0, line.find(','));
    line = line.substr(line.find(',')+ 1);
    std::string zStr = line;

    res.x = atol(xStr.c_str());
    res.y = atol(yStr.c_str());
    res.z = atol(zStr.c_str());

    std::cout << "Created point with x: " << res.x << " y: " << res.y << " z: " << res.z << "\n";
    // std::cout << res.x << "," << res.y << "," << res.z << "\n";
    return (res);
}



int main(int argc, char ** argv)
{
    std::ifstream inputFile(argv[1]);
    std::string line;

    if (argc < 3)
    {
        std::cout << "Usage: ./a.out \"input file\" number_of_joins\n";
        return (1);
    }

    std::vector<t_point> points;
    while (std::getline(inputFile, line))
    {
        points.push_back(createPoint(line));
    }
    DSU graph = DSU(points);
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        graph.unite(graph.getDistances()[i].a, graph.getDistances()[i].b);
    }
    std::vector<int> lengths = graph.getParentLengths();
    std::sort(lengths.begin(), lengths.end());
    for (int i = 0; i < lengths.size(); i++)
    {
        std::cout << lengths[i] << std::endl;
    }

}