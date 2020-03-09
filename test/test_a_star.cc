#include <vector>
#include <gtest/gtest.h>
#include "apath.hh"

TEST(ASTar, testHeuristic) {
    ASSERT_EQ(4, Heuristic(1, 2, 3, 4));
    ASSERT_EQ(8, Heuristic(2, -1, 4, -7));
}

TEST(Astar, testCompare) {
    std::vector<int> test_1 {1, 2, 5, 6};
    std::vector<int> test_2 {1, 3, 5, 7};
    std::vector<int> test_3 {1, 2, 5, 8};
    std::vector<int> test_4 {1, 3, 5, 7};
    ASSERT_FALSE(Compare(test_1, test_2));
    ASSERT_TRUE(Compare(test_3, test_4));
}

TEST(AStar, testAddToOpen) {
    int x = 3;
    int y = 0;
    int g = 5;
    int h = 7;
    std::vector<std::vector<int>> open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
    std::vector<std::vector<int>> solution_open = open; // copy
    solution_open.push_back(std::vector<int>{3, 0, 5, 7});
    std::vector<std::vector<State>> grid {
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty},
    };
    std::vector<std::vector<State>> solution_grid = grid; // copy
    solution_grid[3][0] = State::kClosed;
    AddToOpen(x, y, g, h, open, grid);
    ASSERT_EQ(solution_open, open);
    ASSERT_EQ(solution_grid, grid);
}

// TODO: fix test later
TEST(DISABLED_AStar, testSearch) {
    std::pair<int, int> goal = std::make_pair(4, 5);
    auto board = ReadBoardFile("../../../data/1.board");
//    std::cout.setstate(std::ios_base::failbit); // Disable cout
//    std::cout.clear(); // Enable cout
    auto output = Search(board, goal, goal);

    std::vector<std::vector<State>> solution {
        {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kPath},
    };
    ASSERT_EQ(solution, output);
}

TEST(AStar, testValidCell) {
    std::vector<std::vector<State>> grid {
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
        {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty},
    };
    std::pair<int, int> point_1 = std::make_pair(0, 0);
    std::pair<int, int> point_2 = std::make_pair(4, 2);
    ASSERT_FALSE(CheckValidCell(point_1, grid));
    ASSERT_TRUE(CheckValidCell(point_2, grid));
}