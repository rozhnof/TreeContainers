#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "assert_iterators.h"
#include "assert_multiset.h"

TEST(multiset, iterators_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;
  assert_iterators(std_multiset, multiset);

  std_multiset.insert(10);
  multiset.insert(10);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_2) {
  std::multiset<int> std_multiset = {1};
  s21::multiset<int> multiset = {1};
  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_3) {
  std::multiset<int> std_multiset = {1, 2};
  s21::multiset<int> multiset = {1, 2};
  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_4) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};
  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_6) {
  std::multiset<int> std_multiset = {1, 2};
  s21::multiset<int> multiset = {1, 2};

  std_multiset.erase(1);
  multiset.erase(1);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_7) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.erase(1);
  multiset.erase(1);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_8) {
  std::multiset<int> std_multiset = {1, 2};
  s21::multiset<int> multiset = {1, 2};

  std_multiset.erase(1);
  multiset.erase(1);

  assert_iterators(std_multiset, multiset);

  std_multiset.erase(2);
  multiset.erase(2);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_9) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.erase(1);
  multiset.erase(1);

  assert_iterators(std_multiset, multiset);

  std_multiset.erase(2);
  multiset.erase(2);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_10) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.erase(1);
  multiset.erase(1);

  assert_iterators(std_multiset, multiset);

  std_multiset.erase(3);
  multiset.erase(3);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_11) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.erase(2);
  multiset.erase(2);

  assert_iterators(std_multiset, multiset);

  std_multiset.erase(3);
  multiset.erase(3);

  assert_iterators(std_multiset, multiset);
}
TEST(multiset, iterators_12) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.erase(1);
  multiset.erase(1);

  std_multiset.erase(2);
  multiset.erase(2);

  std_multiset.erase(3);
  multiset.erase(3);

  assert_iterators(std_multiset, multiset);
}

TEST(multiset, iterators_14) {
  s21::multiset<int> multiset = {1, 2, 3};

  {
    auto it = multiset.find(2);

    auto prev = it;
    --prev;
    ASSERT_EQ(*multiset.find(1), *prev);

    auto next = it;
    ++next;
    ASSERT_EQ(*multiset.find(3), *next);

    multiset.erase(2);

    ASSERT_EQ(*(++prev), *next);
  }

  {
    auto prev = multiset.find(1);
    auto next = prev;
    ++next;

    auto it = multiset.insert(2);

    ASSERT_EQ(*(++prev), *it);
    ASSERT_EQ(*(--next), *it);
  }
}