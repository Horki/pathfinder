#include "apath.hh"

int main() {
    std::pair<int, int> init = std::make_pair(0, 0);
    std::pair<int, int> goal = std::make_pair(4, 5);
    auto board = ReadBoardFile("../data/1.board");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}