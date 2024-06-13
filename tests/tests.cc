#include <gtest/gtest.h>

#include <map.h>

TEST(Constructor, Ctor1) {
  EXPECT_EQ(1, 1);

  vr::map<int, int> m;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}