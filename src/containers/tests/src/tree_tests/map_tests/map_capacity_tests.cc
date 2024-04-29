#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

// [[nodiscard]] bool empty() const noexcept;
TEST(map, empty_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  EXPECT_EQ(std_map.empty(), map.empty());
}
TEST(map, empty_2) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(std_map.empty(), map.empty());
}
TEST(map, empty_and_clear) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.clear();
  map.clear();

  EXPECT_EQ(std_map.empty(), map.empty());
}
TEST(map, empty_and_erase) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};

  std_map.erase(1);
  map.erase(1);

  EXPECT_EQ(std_map.empty(), map.empty());
}
TEST(map, empty_erase_insert) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};

  std_map.erase(1);
  map.erase(1);

  EXPECT_EQ(std_map.empty(), map.empty());

  std_map.insert({2, 2});
  map.insert({2, 2});

  EXPECT_EQ(std_map.empty(), map.empty());

  std_map.erase(2);
  map.erase(2);

  EXPECT_EQ(std_map.empty(), map.empty());
}
TEST(map, empty_and_move) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto other_std_map = std::move(std_map);
  auto other_map = std::move(map);
  EXPECT_EQ(std_map.empty(), map.empty());
  EXPECT_EQ(other_std_map.empty(), other_map.empty());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, empty_and_merge_1) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.merge(std_map);
  other_map.merge(map);

  EXPECT_EQ(std_map.empty(), map.empty());
  EXPECT_EQ(other_std_map.empty(), other_map.empty());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, empty_and_merge_2) {
  std::map<int, int, std::less<int>> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::less<int>> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int, std::greater<int>> other_std_map;
  s21::map<int, int, std::greater<int>> other_map;

  other_std_map.merge(std_map);
  other_map.merge(map);

  EXPECT_EQ(std_map.empty(), map.empty());
  EXPECT_EQ(other_std_map.empty(), other_map.empty());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, empty_and_swap_1) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.swap(std_map);
  other_map.swap(map);

  EXPECT_EQ(std_map.empty(), map.empty());
  EXPECT_EQ(other_std_map.empty(), other_map.empty());
}
TEST(map, empty_and_swap_2) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.swap(std_map);
  other_map.swap(map);

  EXPECT_EQ(std_map.empty(), map.empty());
  EXPECT_EQ(other_std_map.empty(), other_map.empty());
}

// size_type size() const noexcept;
TEST(map, size_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  EXPECT_EQ(std_map.size(), map.size());
}
TEST(map, size_2) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(std_map.size(), map.size());
}
TEST(map, size_and_clear) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.clear();
  map.clear();

  EXPECT_EQ(std_map.size(), map.size());
}
TEST(map, size_and_erase) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};

  std_map.erase(1);
  map.erase(1);

  EXPECT_EQ(std_map.size(), map.size());
}
TEST(map, size_erase_insert) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};

  std_map.erase(1);
  map.erase(1);

  EXPECT_EQ(std_map.size(), map.size());

  std_map.insert({2, 2});
  map.insert({2, 2});

  EXPECT_EQ(std_map.size(), map.size());

  std_map.erase(2);
  map.erase(2);

  EXPECT_EQ(std_map.size(), map.size());
}
TEST(map, size_and_move) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto other_std_map = std::move(std_map);
  auto other_map = std::move(map);
  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(other_std_map.size(), other_map.size());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, size_and_merge_1) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.merge(std_map);
  other_map.merge(map);

  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(other_std_map.size(), other_map.size());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, size_and_merge_2) {
  std::map<int, int, std::less<int>> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int, std::less<int>> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int, std::greater<int>> other_std_map;
  s21::map<int, int, std::greater<int>> other_map;

  other_std_map.merge(std_map);
  other_map.merge(map);

  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(other_std_map.size(), other_map.size());

  assert_map(std_map, map);
  assert_map(other_std_map, other_map);
}
TEST(map, size_and_swap_1) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.swap(std_map);
  other_map.swap(map);

  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(other_std_map.size(), other_map.size());
}
TEST(map, size_and_swap_2) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  std::map<int, int> other_std_map;
  s21::map<int, int> other_map;

  other_std_map.swap(std_map);
  other_map.swap(map);

  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(other_std_map.size(), other_map.size());
}
