#include <gtest/gtest.h>

#include <vector>

#include "apath.hh"

TEST(ASTar, testHeuristic) {
  ASSERT_EQ(4, Heuristic(1, 2, 3, 4));
  ASSERT_EQ(8, Heuristic(2, -1, 4, -7));
}

TEST(Astar, testCompare) {
  std::vector<int> test_1{1, 2, 5, 6};
  std::vector<int> test_2{1, 3, 5, 7};
  std::vector<int> test_3{1, 2, 5, 8};
  std::vector<int> test_4{1, 3, 5, 7};
  ASSERT_FALSE(Compare(test_1, test_2));
  ASSERT_TRUE(Compare(test_3, test_4));
}

TEST(AStar, testAddToOpen) {
  int x = 3;
  int y = 0;
  int g = 5;
  int h = 7;
  cells_matrix open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
  cells_matrix solution_open = open;  // copy
  solution_open.push_back(std::vector<int>{3, 0, 5, 7});
  state_matrix grid{
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty,
       State::kObstacle, State::kEmpty},
  };
  state_matrix solution_grid = grid;  // copy
  solution_grid[3][0] = State::kClosed;
  AddToOpen(x, y, g, h, open, grid);
  ASSERT_EQ(solution_open, open);
  ASSERT_EQ(solution_grid, grid);
}

// TODO: fix test later
TEST(DISABLED_AStar, testSearch) {
  matrix_point goal = std::make_pair(4, 5);
  auto board = ReadBoardFile("../../../data/1.board");
  //    std::cout.setstate(std::ios_base::failbit); // Disable cout
  //    std::cout.clear(); // Enable cout
  bool result = Search(board, goal, goal);

  state_matrix solution{
      {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty,
       State::kObstacle, State::kPath},
  };
  ASSERT_TRUE(result);
  ASSERT_EQ(solution, board);
}

TEST(AStar, testValidCell) {
  state_matrix grid{
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty,
       State::kObstacle, State::kEmpty},
  };
  matrix_point point_1 = std::make_pair(0, 0);
  matrix_point point_2 = std::make_pair(4, 2);
  ASSERT_FALSE(CheckValidCell(point_1, grid));
  ASSERT_TRUE(CheckValidCell(point_2, grid));
}

TEST(AStar, testExpandNeighbors) {
  std::vector<int> current{4, 2, 7, 3};
  matrix_point goal = std::make_pair(4, 5);
  cells_matrix open{{4, 2, 7, 3}};
  cells_matrix solution_open = open;  // copy
  solution_open.push_back(std::vector<int>{3, 2, 8, 4});
  solution_open.push_back(std::vector<int>{4, 3, 8, 2});
  state_matrix grid{{State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kClosed, State::kEmpty,
                     State::kEmpty, State::kObstacle, State::kEmpty}};
  state_matrix solution_grid = grid;
  solution_grid[3][2] = State::kClosed;
  solution_grid[4][3] = State::kClosed;
  ExpandNeighbors(current, goal, open, grid);
  CellSort(&open);
  CellSort(&solution_open);
  ASSERT_EQ(solution_open, open);
  ASSERT_EQ(solution_grid, grid);
}
