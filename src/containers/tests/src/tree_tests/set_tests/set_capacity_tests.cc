#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "assert_set.h"

// [[nodiscard]] bool empty() const noexcept;
TEST(set, empty_1) {
  std::set<int> std_set;
  s21::set<int> set;
  EXPECT_EQ(std_set.empty(), set.empty());
}
TEST(set, empty_2) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(std_set.empty(), set.empty());
}
TEST(set, empty_and_clear) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.clear();
  set.clear();

  EXPECT_EQ(std_set.empty(), set.empty());
}
TEST(set, empty_and_erase) {
  std::set<int> std_set = {{1, 1}};
  s21::set<int> set = {{1, 1}};

  std_set.erase(1);
  set.erase(1);

  EXPECT_EQ(std_set.empty(), set.empty());
}
TEST(set, empty_erase_insert) {
  std::set<int> std_set = {{1, 1}};
  s21::set<int> set = {{1, 1}};

  std_set.erase(1);
  set.erase(1);

  EXPECT_EQ(std_set.empty(), set.empty());

  std_set.insert({2, 2});
  set.insert({2, 2});

  EXPECT_EQ(std_set.empty(), set.empty());

  std_set.erase(2);
  set.erase(2);

  EXPECT_EQ(std_set.empty(), set.empty());
}
TEST(set, empty_and_move) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  auto other_std_set = std::move(std_set);
  auto other_set = std::move(set);
  EXPECT_EQ(std_set.empty(), set.empty());
  EXPECT_EQ(other_std_set.empty(), other_set.empty());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, empty_and_merge_1) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.merge(std_set);
  other_set.merge(set);

  EXPECT_EQ(std_set.empty(), set.empty());
  EXPECT_EQ(other_std_set.empty(), other_set.empty());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, empty_and_merge_2) {
  std::set<int, std::less<int>> std_set = {1, 2, 3};
  s21::set<int, std::less<int>> set = {1, 2, 3};

  std::set<int, std::greater<int>> other_std_set;
  s21::set<int, std::greater<int>> other_set;

  other_std_set.merge(std_set);
  other_set.merge(set);

  EXPECT_EQ(std_set.empty(), set.empty());
  EXPECT_EQ(other_std_set.empty(), other_set.empty());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, empty_and_swap_1) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.swap(std_set);
  other_set.swap(set);

  EXPECT_EQ(std_set.empty(), set.empty());
  EXPECT_EQ(other_std_set.empty(), other_set.empty());
}
TEST(set, empty_and_swap_2) {
  std::set<int> std_set;
  s21::set<int> set;

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.swap(std_set);
  other_set.swap(set);

  EXPECT_EQ(std_set.empty(), set.empty());
  EXPECT_EQ(other_std_set.empty(), other_set.empty());
}

// size_type size() const noexcept;
TEST(set, size_1) {
  std::set<int> std_set;
  s21::set<int> set;
  EXPECT_EQ(std_set.size(), set.size());
}
TEST(set, size_2) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(std_set.size(), set.size());
}
TEST(set, size_and_clear) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std_set.clear();
  set.clear();

  EXPECT_EQ(std_set.size(), set.size());
}
TEST(set, size_and_erase) {
  std::set<int> std_set = {{1, 1}};
  s21::set<int> set = {{1, 1}};

  std_set.erase(1);
  set.erase(1);

  EXPECT_EQ(std_set.size(), set.size());
}
TEST(set, size_erase_insert) {
  std::set<int> std_set = {{1, 1}};
  s21::set<int> set = {{1, 1}};

  std_set.erase(1);
  set.erase(1);

  EXPECT_EQ(std_set.size(), set.size());

  std_set.insert({2, 2});
  set.insert({2, 2});

  EXPECT_EQ(std_set.size(), set.size());

  std_set.erase(2);
  set.erase(2);

  EXPECT_EQ(std_set.size(), set.size());
}
TEST(set, size_and_move) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  auto other_std_set = std::move(std_set);
  auto other_set = std::move(set);
  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(other_std_set.size(), other_set.size());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, size_and_merge_1) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.merge(std_set);
  other_set.merge(set);

  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(other_std_set.size(), other_set.size());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, size_and_merge_2) {
  std::set<int, std::less<int>> std_set = {1, 2, 3};
  s21::set<int, std::less<int>> set = {1, 2, 3};

  std::set<int, std::greater<int>> other_std_set;
  s21::set<int, std::greater<int>> other_set;

  other_std_set.merge(std_set);
  other_set.merge(set);

  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(other_std_set.size(), other_set.size());

  assert_set(std_set, set);
  assert_set(other_std_set, other_set);
}
TEST(set, size_and_swap_1) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.swap(std_set);
  other_set.swap(set);

  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(other_std_set.size(), other_set.size());
}
TEST(set, size_and_swap_2) {
  std::set<int> std_set;
  s21::set<int> set;

  std::set<int> other_std_set;
  s21::set<int> other_set;

  other_std_set.swap(std_set);
  other_set.swap(set);

  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(other_std_set.size(), other_set.size());
}
