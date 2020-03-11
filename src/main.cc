#include "apath.hh"

int main() {
    matrix_point init = std::make_pair(0, 0);
    matrix_point goal = std::make_pair(4, 5);
    auto board = ReadBoardFile("../data/1.board");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}