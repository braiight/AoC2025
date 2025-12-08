#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

std::vector<std::vector<char>> createGrid(const char* file)
{
    std::vector<std::vector<char>> grid;
    std::ifstream inputFile(file);

    std::string line;
    while (std::getline(inputFile, line))
    {
        grid.push_back(std::vector<char>(line.begin(), line.end()));
    }
    inputFile.close();
    return grid;
}

// Function to serialize the state for memoization
std::string serializeState(size_t row, const std::vector<size_t>& beamPositions)
{
    std::ostringstream key;
    key << row << ":";
    for (size_t pos : beamPositions) {
        key << pos << ",";
    }
    return key.str();
}

// Recursive function
size_t processMap(const std::vector<std::vector<char>>& map, size_t row, const std::vector<size_t>& beamPositions, std::unordered_map<std::string, size_t>& memo)
{
    // Base case: last line reached, end of a timeline
    if (row >= map.size())
        return 1;

    // Serialize current state and return if already calculated
    std::string key = serializeState(row, beamPositions);
    if (memo.find(key) != memo.end())
        return memo[key];

    // Calculate the next row's beam positions
    std::vector<size_t> nextBeamPositions;
    size_t totalTimelines = 0;

    for (size_t pos : beamPositions)
    {
        if (map[row][pos] == '.')
        {
            // Beam continues downward
            nextBeamPositions.push_back(pos);
        } 
        else if (map[row][pos] == '^')
        {
            // Beam splits into two timelines
            if (pos > 0 && map[row][pos - 1] == '.')
            {
                std::vector<size_t> leftBeam = { pos - 1 };
                totalTimelines += processMap(map, row + 1, leftBeam, memo);
            }
            if (pos + 1 < map[row].size() && map[row][pos + 1] == '.')
            {
                std::vector<size_t> rightBeam = { pos + 1 };
                totalTimelines += processMap(map, row + 1, rightBeam, memo);
            }
        }
    }

    // Process the next row for beams that continue downward
    if (!nextBeamPositions.empty())
        totalTimelines += processMap(map, row + 1, nextBeamPositions, memo);

    // Store the result in the memoization table
    memo[key] = totalTimelines;
    return totalTimelines;
}

int main(int argc, char** argv)
{
    std::vector<std::vector<char>> map = createGrid(argv[1]);

    // Draw the initial map (optional for debugging)
    for (const auto& row : map) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // Initialize the starting beam positions (first row)
    std::vector<size_t> initialBeamPositions;
    for (size_t col = 0; col < map[0].size(); col++)
    {
        if (map[0][col] == '|') 
            initialBeamPositions.push_back(col);
    }

    // Memoization table
    std::unordered_map<std::string, size_t> memo;

    // Process the map and count the total timelines
    size_t result = processMap(map, 1, initialBeamPositions, memo);

    // Output the result
    std::cout << "Total Timelines: " << result << std::endl;

    return 0;
}