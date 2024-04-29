#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "assert_multiset.h"

TEST(multiset, clear_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  std_multiset.clear();
  multiset.clear();

  assert_multiset(std_multiset, multiset);
}
TEST(multiset, clear_2) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (int i = 0; i < 10; ++i) {
    std_multiset.insert({i, i});
    multiset.insert({i, i});
  }

  std_multiset.clear();
  multiset.clear();

  assert_multiset(std_multiset, multiset);
}
TEST(multiset, clear_3) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (int i = 0; i < 10; ++i) {
    std_multiset.insert({i, i});
    multiset.insert({i, i});
  }

  auto std_multiset_copy = std_multiset;
  auto multiset_copy = multiset;

  std_multiset.clear();
  multiset.clear();

  assert_multiset(std_multiset_copy, multiset_copy);
}
TEST(multiset, clear_4) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (int i = 0; i < 10; ++i) {
    std_multiset.insert({i, i});
    multiset.insert({i, i});
  }

  auto std_multiset_move = std::move(std_multiset);
  auto multiset_move = std::move(multiset);

  std_multiset.clear();
  multiset.clear();

  assert_multiset(std_multiset_move, multiset_move);
}
TEST(multiset, clear_5) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (int i = 0; i < 10; ++i) {
    std_multiset.insert({i, i});
    multiset.insert({i, i});
  }

  std_multiset.clear();
  multiset.clear();

  std_multiset.clear();
  multiset.clear();

  assert_multiset(std_multiset, multiset);
}
TEST(multiset, swap_1) {
  std::multiset<int> std_multiset_1;
  s21::multiset<int> multiset_1;

  std::multiset<int> std_multiset_2;
  s21::multiset<int> multiset_2;

  std_multiset_1.swap(std_multiset_2);
  multiset_1.swap(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, swap_2) {
  std::multiset<int> std_multiset_1 = {1, 2, 3};
  s21::multiset<int> multiset_1 = {1, 2, 3};

  std::multiset<int> std_multiset_2;
  s21::multiset<int> multiset_2;

  std_multiset_1.swap(std_multiset_2);
  multiset_1.swap(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, swap_3) {
  std::multiset<int> std_multiset_1;
  s21::multiset<int> multiset_1;

  std::multiset<int> std_multiset_2 = {1, 2, 3};
  s21::multiset<int> multiset_2 = {1, 2, 3};

  std_multiset_1.swap(std_multiset_2);
  multiset_1.swap(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, swap_4) {
  std::multiset<int> std_multiset_1 = {5, 6, 7};
  s21::multiset<int> multiset_1 = {5, 6, 7};

  std::multiset<int> std_multiset_2 = {1, 2, 3};
  s21::multiset<int> multiset_2 = {1, 2, 3};

  std_multiset_1.swap(std_multiset_2);
  multiset_1.swap(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}

TEST(multiset, merge_1) {
  std::multiset<int> std_multiset_1;
  s21::multiset<int> multiset_1;

  std::multiset<int> std_multiset_2;
  s21::multiset<int> multiset_2;

  std_multiset_1.merge(std_multiset_2);
  multiset_1.merge(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, merge_2) {
  std::multiset<int> std_multiset_1 = {1, 2, 3};
  s21::multiset<int> multiset_1 = {1, 2, 3};

  std::multiset<int> std_multiset_2;
  s21::multiset<int> multiset_2;

  std_multiset_1.merge(std_multiset_2);
  multiset_1.merge(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, merge_3) {
  std::multiset<int> std_multiset_1;
  s21::multiset<int> multiset_1;

  std::multiset<int> std_multiset_2 = {1, 2, 3};
  s21::multiset<int> multiset_2 = {1, 2, 3};

  std_multiset_1.merge(std_multiset_2);
  multiset_1.merge(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}
TEST(multiset, merge_4) {
  std::multiset<int> std_multiset_1 = {5, 6, 7};
  s21::multiset<int> multiset_1 = {5, 6, 7};

  std::multiset<int> std_multiset_2 = {1, 2, 3};
  s21::multiset<int> multiset_2 = {1, 2, 3};

  std_multiset_1.merge(std_multiset_2);
  multiset_1.merge(multiset_2);

  assert_multiset(std_multiset_1, multiset_1);

  assert_multiset(std_multiset_2, multiset_2);
}