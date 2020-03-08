#ifndef APATH_H_
#define APATH_H_

#include <string>
#include <vector>

enum class State {
    kEmpty,
    kObstacle,
    kClosed,
    kPath
};

// directional deltas
constexpr int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::ostream & operator<<(std::ostream & os, const State & cell);

std::vector<State> ParseLine(const std::string & line);

std::vector<std::vector<State>> ReadBoardFile(const std::string & path);

/**
 * Compare the F values of two cells.
 */
bool Compare(const std::vector<int> & a, const std::vector<int> & b);

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(std::vector<std::vector<int>> * v);

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2);

/**
 * Check that a cell is valid: on the grid, not an obstacle, and clear.
 */
bool CheckValidCell(int x, int y, const std::vector<std::vector<State>> & grid);

/**
 * Add a node to the open list and mark it as open.
 */
void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> & openlist,
               std::vector<std::vector<State>> & grid);


/**
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const std::vector<int> & current, const std::pair<int, int> & goal,
                     std::vector<std::vector<int>> & openlist,
                     std::vector<std::vector<State>> & grid);


/**
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> & grid,
                                       const std::pair<int, int> & init,
                                       const std::pair<int, int> & goal);

void PrintBoard(const std::vector<std::vector<State>> & board);

#endif