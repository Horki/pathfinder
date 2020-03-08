#include "apath.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>


std::ostream & operator<<(std::ostream & os, const State & cell) {
    switch (cell) {
        case State::kObstacle: return os << "⛰️   ";
        case State::kPath:     return os << "🚗   ";
        default:               return os << "0    ";
    }
}

std::vector<State> ParseLine(const std::string & line) {
    std::istringstream sline(line);
    int n;
    char c;
    std::vector<State> row;
    while (sline >> n >> c && c == ',') {
        if (n == 0) {
            row.push_back(State::kEmpty);
        } else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}


std::vector<std::vector<State>> ReadBoardFile(const std::string & path) {
    std::ifstream myfile(path);
    std::vector<std::vector<State>> board;
    if (myfile) {
        std::string line;
        while (getline(myfile, line)) {
            std::vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}


/**
 * Compare the F values of two cells.
 */
bool Compare(const std::vector<int> & a, const std::vector<int> & b) {
    int f1 = a[2] + a[3]; // f1 = g1 + h1
    int f2 = b[2] + b[3]; // f2 = g2 + h2
    return f1 > f2;
}


/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(std::vector<std::vector<int>> * v) {
    std::sort(v->begin(), v->end(), Compare);
}


// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}


/**
 * Check that a cell is valid: on the grid, not an obstacle, and clear.
 */
bool CheckValidCell(int x, int y, const std::vector<std::vector<State>> & grid) {
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y) {
        return grid[x][y] == State::kEmpty;
    }
    return false;
}


/**
 * Add a node to the open list and mark it as open.
 */
void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> & openlist,
               std::vector<std::vector<State>> & grid) {
    // Add node to open vector, and mark grid cell as closed.
    openlist.push_back(std::vector<int>{x, y, g, h});
    grid[x][y] = State::kClosed;
}


/**
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const std::vector<int> & current, const std::pair<int, int> & goal,
                     std::vector<std::vector<int>> & openlist,
                     std::vector<std::vector<State>> & grid) {
    // Get current node's data.
    int x = current[0];
    int y = current[1];
    int g = current[2];

    // Loop through current node's potential neighbors.
    for (size_t i = 0; i < 4; ++i) {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];

        // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
        if (CheckValidCell(x2, y2, grid)) {
            // Increment g value and add neighbor to open list.
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal.first, goal.second);
            AddToOpen(x2, y2, g2, h2, openlist, grid);
        }
    }
}


/**
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> & grid,
                                       const std::pair<int, int> & init,
                                       const std::pair<int, int> & goal) {
    // Create the vector of open nodes.
    std::vector<std::vector<int>> open;

    // Initialize the starting node.
    int x = init.first;
    int y = init.second;
    int g = 0;
    int h = Heuristic(x, y, goal.first, goal.second);
    AddToOpen(x, y, g, h, open, grid);

    while (open.size() > 0) {
        // Get the next node
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        x = current[0];
        y = current[1];
        grid[x][y] = State::kPath;

        // Check if we're done.
        if (x == goal.first && y == goal.second) {
            return grid;
        }

        // If we're not done, expand search to current node's neighbors.
        ExpandNeighbors(current, goal, open, grid);
    }

    // We've run out of new nodes to explore and haven't found a path.
    std::cerr << "No path found!\n";
    return std::vector<std::vector<State>>();
}


void PrintBoard(const std::vector<std::vector<State>> & board) {
    for (const auto & row : board) {
        std::copy(row.begin(), row.end(), std::ostream_iterator<State>(std::cout, ""));
        std::cout << std::endl;
    }
}