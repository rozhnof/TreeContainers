#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "assert_iterators.h"
#include "assert_set.h"

TEST(set, iterators_1) {
  std::set<int> std_set;
  s21::set<int> set;
  assert_iterators(std_set, set);

  std_set.insert(10);
  set.insert(10);

  assert_iterators(std_set, set);
}
TEST(set, iterators_2) {
  std::set<int> std_set = {1};
  s21::set<int> set = {1};
  assert_iterators(std_set, set);
}
TEST(set, iterators_3) {
  std::set<int> std_set = {1, 2};
  s21::set<int> set = {1, 2};
  assert_iterators(std_set, set);
}
TEST(set, iterators_4) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};
  assert_iterators(std_set, set);
}
TEST(set, iterators_5) {
  std::set<int> std_set = {1};
  s21::set<int> set = {1};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);
}
TEST(set, iterators_6) {
  std::set<int> std_set = {1, 2};
  s21::set<int> set = {1, 2};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);
}
TEST(set, iterators_7) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);
}
TEST(set, iterators_8) {
  std::set<int> std_set = {1, 2};
  s21::set<int> set = {1, 2};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);

  std_set.erase(2);
  set.erase(2);

  assert_iterators(std_set, set);
}
TEST(set, iterators_9) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);

  std_set.erase(2);
  set.erase(2);

  assert_iterators(std_set, set);
}
TEST(set, iterators_10) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);

  std_set.erase(3);
  set.erase(3);

  assert_iterators(std_set, set);
}
TEST(set, iterators_11) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.erase(2);
  set.erase(2);

  assert_iterators(std_set, set);

  std_set.erase(3);
  set.erase(3);

  assert_iterators(std_set, set);
}
TEST(set, iterators_12) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.erase(1);
  set.erase(1);

  std_set.erase(2);
  set.erase(2);

  std_set.erase(3);
  set.erase(3);

  assert_iterators(std_set, set);
}
TEST(set, iterators_13) {
  std::set<int> std_set;
  s21::set<int> set;

  std_set.insert(1);
  set.insert(1);

  assert_iterators(std_set, set);

  std_set.erase(1);
  set.erase(1);

  assert_iterators(std_set, set);
}

TEST(set, iterators_14) {
  s21::set<int> set = {1, 2, 3};

  {
    auto it = set.find(2);

    auto prev = it;
    --prev;
    ASSERT_EQ(*set.find(1), *prev);

    auto next = it;
    ++next;
    ASSERT_EQ(*set.find(3), *next);

    set.erase(2);

    ASSERT_EQ(*(++prev), *next);
  }

  {
    auto prev = set.find(1);
    auto next = prev;
    ++next;

    auto it = set.insert(2);

    ASSERT_EQ(*(++prev), *it);
    ASSERT_EQ(*(--next), *it);
  }
}