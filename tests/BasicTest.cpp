#include <gtest/gtest.h>

// A simple test case to verify that the Google Test framework is working.
TEST(BasicTestSuite, SimpleTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(BasicTestSuite, AnotherSimpleTest) {
    EXPECT_TRUE(true);
}
