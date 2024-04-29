#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

TEST(map, clear_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  std_map.clear();
  map.clear();

  assert_map(std_map, map);
}
TEST(map, clear_2) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (int i = 0; i < 10; ++i) {
    std_map.insert({i, i});
    map.insert({i, i});
  }

  std_map.clear();
  map.clear();

  assert_map(std_map, map);
}
TEST(map, clear_3) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (int i = 0; i < 10; ++i) {
    std_map.insert({i, i});
    map.insert({i, i});
  }

  auto std_map_copy = std_map;
  auto map_copy = map;

  std_map.clear();
  map.clear();

  assert_map(std_map_copy, map_copy);
}
TEST(map, clear_4) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (int i = 0; i < 10; ++i) {
    std_map.insert({i, i});
    map.insert({i, i});
  }

  auto std_map_move = std::move(std_map);
  auto map_move = std::move(map);

  std_map.clear();
  map.clear();

  assert_map(std_map_move, map_move);
}
TEST(map, clear_5) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (int i = 0; i < 10; ++i) {
    std_map.insert({i, i});
    map.insert({i, i});
  }

  std_map.clear();
  map.clear();

  std_map.clear();
  map.clear();

  assert_map(std_map, map);
}
TEST(map, swap_1) {
  std::map<int, int> std_map_1;
  s21::map<int, int> map_1;

  std::map<int, int> std_map_2;
  s21::map<int, int> map_2;

  std_map_1.swap(std_map_2);
  map_1.swap(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, swap_2) {
  std::map<int, int> std_map_1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_1 = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_2;
  s21::map<int, int> map_2;

  std_map_1.swap(std_map_2);
  map_1.swap(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, swap_3) {
  std::map<int, int> std_map_1;
  s21::map<int, int> map_1;

  std::map<int, int> std_map_2 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_2 = {{1, 1}, {2, 2}, {3, 3}};

  std_map_1.swap(std_map_2);
  map_1.swap(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, swap_4) {
  std::map<int, int> std_map_1 = {{5, 5}, {6, 6}, {7, 7}};
  s21::map<int, int> map_1 = {{5, 5}, {6, 6}, {7, 7}};

  std::map<int, int> std_map_2 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_2 = {{1, 1}, {2, 2}, {3, 3}};

  std_map_1.swap(std_map_2);
  map_1.swap(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}

TEST(map, merge_1) {
  std::map<int, int> std_map_1;
  s21::map<int, int> map_1;

  std::map<int, int> std_map_2;
  s21::map<int, int> map_2;

  std_map_1.merge(std_map_2);
  map_1.merge(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, merge_2) {
  std::map<int, int> std_map_1 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_1 = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_2;
  s21::map<int, int> map_2;

  std_map_1.merge(std_map_2);
  map_1.merge(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, merge_3) {
  std::map<int, int> std_map_1;
  s21::map<int, int> map_1;

  std::map<int, int> std_map_2 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_2 = {{1, 1}, {2, 2}, {3, 3}};

  std_map_1.merge(std_map_2);
  map_1.merge(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}
TEST(map, merge_4) {
  std::map<int, int> std_map_1 = {{5, 5}, {6, 6}, {7, 7}};
  s21::map<int, int> map_1 = {{5, 5}, {6, 6}, {7, 7}};

  std::map<int, int> std_map_2 = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map_2 = {{1, 1}, {2, 2}, {3, 3}};

  std_map_1.merge(std_map_2);
  map_1.merge(map_2);

  assert_map(std_map_1, map_1);

  assert_map(std_map_2, map_2);
}