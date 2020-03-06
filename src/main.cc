#include "apath.hh"

int main() {
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto board = ReadBoardFile("../data/1.board");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}