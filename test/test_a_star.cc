#include <gtest/gtest.h>
#include "apath.hh"

TEST(ASTar, testHeuristic) {
    ASSERT_EQ(4, Heuristic(1, 2, 3, 4));
    ASSERT_EQ(8, Heuristic(2, -1, 4, -7));
}