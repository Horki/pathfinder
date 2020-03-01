#include <gtest/gtest.h>

TEST(Basic, test) {
    int a = 2 + 3;
    ASSERT_EQ(5, a);
}