#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "assert_set.h"

TEST(set, clear_1) {
  std::set<int> std_set;
  s21::set<int> set;

  std_set.clear();
  set.clear();

  assert_set(std_set, set);
}
TEST(set, clear_2) {
  std::set<int> std_set;
  s21::set<int> set;

  for (int i = 0; i < 10; ++i) {
    std_set.insert({i, i});
    set.insert({i, i});
  }

  std_set.clear();
  set.clear();

  assert_set(std_set, set);
}
TEST(set, clear_3) {
  std::set<int> std_set;
  s21::set<int> set;

  for (int i = 0; i < 10; ++i) {
    std_set.insert({i, i});
    set.insert({i, i});
  }

  auto std_set_copy = std_set;
  auto set_copy = set;

  std_set.clear();
  set.clear();

  assert_set(std_set_copy, set_copy);
}
TEST(set, clear_4) {
  std::set<int> std_set;
  s21::set<int> set;

  for (int i = 0; i < 10; ++i) {
    std_set.insert({i, i});
    set.insert({i, i});
  }

  auto std_set_move = std::move(std_set);
  auto set_move = std::move(set);

  std_set.clear();
  set.clear();

  assert_set(std_set_move, set_move);
}
TEST(set, clear_5) {
  std::set<int> std_set;
  s21::set<int> set;

  for (int i = 0; i < 10; ++i) {
    std_set.insert({i, i});
    set.insert({i, i});
  }

  std_set.clear();
  set.clear();

  std_set.clear();
  set.clear();

  assert_set(std_set, set);
}
TEST(set, swap_1) {
  std::set<int> std_set_1;
  s21::set<int> set_1;

  std::set<int> std_set_2;
  s21::set<int> set_2;

  std_set_1.swap(std_set_2);
  set_1.swap(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, swap_2) {
  std::set<int> std_set_1 = {1, 2, 3};
  s21::set<int> set_1 = {1, 2, 3};

  std::set<int> std_set_2;
  s21::set<int> set_2;

  std_set_1.swap(std_set_2);
  set_1.swap(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, swap_3) {
  std::set<int> std_set_1;
  s21::set<int> set_1;

  std::set<int> std_set_2 = {1, 2, 3};
  s21::set<int> set_2 = {1, 2, 3};

  std_set_1.swap(std_set_2);
  set_1.swap(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, swap_4) {
  std::set<int> std_set_1 = {5, 6, 7};
  s21::set<int> set_1 = {5, 6, 7};

  std::set<int> std_set_2 = {1, 2, 3};
  s21::set<int> set_2 = {1, 2, 3};

  std_set_1.swap(std_set_2);
  set_1.swap(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}

TEST(set, merge_1) {
  std::set<int> std_set_1;
  s21::set<int> set_1;

  std::set<int> std_set_2;
  s21::set<int> set_2;

  std_set_1.merge(std_set_2);
  set_1.merge(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, merge_2) {
  std::set<int> std_set_1 = {1, 2, 3};
  s21::set<int> set_1 = {1, 2, 3};

  std::set<int> std_set_2;
  s21::set<int> set_2;

  std_set_1.merge(std_set_2);
  set_1.merge(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, merge_3) {
  std::set<int> std_set_1;
  s21::set<int> set_1;

  std::set<int> std_set_2 = {1, 2, 3};
  s21::set<int> set_2 = {1, 2, 3};

  std_set_1.merge(std_set_2);
  set_1.merge(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}
TEST(set, merge_4) {
  std::set<int> std_set_1 = {5, 6, 7};
  s21::set<int> set_1 = {5, 6, 7};

  std::set<int> std_set_2 = {1, 2, 3};
  s21::set<int> set_2 = {1, 2, 3};

  std_set_1.merge(std_set_2);
  set_1.merge(set_2);

  assert_set(std_set_1, set_1);

  assert_set(std_set_2, set_2);
}