#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

// T& at( const Key& key );
TEST(map, element_access_1) {
  {
    s21::map<int, int> map;
    EXPECT_THROW(map.at(0), std::out_of_range);
  }
  {
    s21::map<char, int> map;
    EXPECT_THROW(map.at('0'), std::out_of_range);
  }
}
TEST(map, element_access_2) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  ASSERT_EQ(std_map.at(1), map.at(1));
  ASSERT_EQ(std_map.at(2), map.at(2));
  ASSERT_EQ(std_map.at(3), map.at(3));

  std_map.at(2) = 100;
  map.at(2) = 100;
  ASSERT_EQ(std_map.at(2), map.at(2));

  EXPECT_THROW(map.at(4), std::out_of_range);
}
TEST(map, element_access_3) {
  std::map<char, int> std_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::map<char, int> map = {{'a', 1}, {'b', 2}, {'c', 3}};

  ASSERT_EQ(std_map.at('a'), map.at('a'));
  ASSERT_EQ(std_map.at('b'), map.at('b'));
  ASSERT_EQ(std_map.at('c'), map.at('c'));

  std_map.at('a') = 100;
  map.at('a') = 100;
  ASSERT_EQ(std_map.at('a'), map.at('a'));

  EXPECT_THROW(map.at('d'), std::out_of_range);
}

// const T& at( const Key& key ) const;
TEST(map, element_access_4) {
  {
    const s21::map<int, int> map;
    EXPECT_THROW(map.at(0), std::out_of_range);
  }
  {
    const s21::map<char, int> map;
    EXPECT_THROW(map.at('0'), std::out_of_range);
  }
}
TEST(map, element_access_5) {
  const std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  const s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  ASSERT_EQ(std_map.at(1), map.at(1));
  ASSERT_EQ(std_map.at(2), map.at(2));
  ASSERT_EQ(std_map.at(3), map.at(3));
  EXPECT_THROW(map.at(4), std::out_of_range);
}
TEST(map, element_access_6) {
  const std::map<char, int> std_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  const s21::map<char, int> map = {{'a', 1}, {'b', 2}, {'c', 3}};

  ASSERT_EQ(std_map.at('a'), map.at('a'));
  ASSERT_EQ(std_map.at('b'), map.at('b'));
  ASSERT_EQ(std_map.at('c'), map.at('c'));
  EXPECT_THROW(map.at('d'), std::out_of_range);
}

// T& operator[]( const Key& key );
TEST(map, element_access_7) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  ASSERT_EQ(std_map[1], map[1]);
  ASSERT_EQ(std_map[2], map[2]);
  ASSERT_EQ(std_map[3], map[3]);

  std_map[2] = 100;
  map[2] = 100;
  ASSERT_EQ(std_map[2], map[2]);
}
TEST(map, element_access_8) {
  std::map<char, int> std_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::map<char, int> map = {{'a', 1}, {'b', 2}, {'c', 3}};

  ASSERT_EQ(std_map[1], map[1]);
  ASSERT_EQ(std_map[2], map[2]);
  ASSERT_EQ(std_map[3], map[3]);

  std_map['a'] = 100;
  map['a'] = 100;
  ASSERT_EQ(std_map['a'], map['a']);
}

// T& operator[]( Key&& key );
TEST(map, element_access_9) {
}
