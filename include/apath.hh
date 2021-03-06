#ifndef APATH_H_
#define APATH_H_

#include <string>
#include <vector>

enum class State {
  kEmpty,
  kObstacle,
  kClosed,
  kPath,
  kStart,
  kFinish,
};

using matrix_point = std::pair<unsigned, unsigned>;
using state_matrix = std::vector<std::vector<State>>;
using cells_matrix = std::vector<std::vector<int>>;

// directional deltas
constexpr int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::ostream& operator<<(std::ostream& os, const State& cell);

std::vector<State> ParseLine(const std::string& line);

state_matrix ReadBoardFile(const std::string& path);

/**
 * Compare the F values of two cells.
 */
bool Compare(const std::vector<int>& a, const std::vector<int>& b);

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(cells_matrix* v);

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2);
int Heuristic(const matrix_point& point_x, const matrix_point& point_y);

/**
 * Check that a cell is valid: on the grid, not an obstacle, and clear.
 */
bool CheckValidCell(const matrix_point& point, const state_matrix& grid);

/**
 * Add a node to the open list and mark it as open.
 */
void AddToOpen(int x, int y, int g, int h, cells_matrix& openlist,
               state_matrix& grid);

/**
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const std::vector<int>& current, const matrix_point& goal,
                     cells_matrix& openlist, state_matrix& grid);

/**
 * Implementation of A* search algorithm
 */
bool Search(state_matrix& grid, const matrix_point& init,
            const matrix_point& goal);

void PrintBoard(const state_matrix& board);

#endif
