#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "assert_multiset.h"

// [[nodiscard]] bool empty() const noexcept;
TEST(multiset, empty_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;
  EXPECT_EQ(std_multiset.empty(), multiset.empty());
}
TEST(multiset, empty_2) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};
  EXPECT_EQ(std_multiset.empty(), multiset.empty());
}
TEST(multiset, empty_and_clear) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.clear();
  multiset.clear();

  EXPECT_EQ(std_multiset.empty(), multiset.empty());
}
TEST(multiset, empty_and_move) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  auto other_std_multiset = std::move(std_multiset);
  auto other_multiset = std::move(multiset);
  EXPECT_EQ(std_multiset.empty(), multiset.empty());
  EXPECT_EQ(other_std_multiset.empty(), other_multiset.empty());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, empty_and_merge_1) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.merge(std_multiset);
  other_multiset.merge(multiset);

  EXPECT_EQ(std_multiset.empty(), multiset.empty());
  EXPECT_EQ(other_std_multiset.empty(), other_multiset.empty());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, empty_and_merge_2) {
  std::multiset<int, std::less<int>> std_multiset = {1, 2, 3};
  s21::multiset<int, std::less<int>> multiset = {1, 2, 3};

  std::multiset<int, std::greater<int>> other_std_multiset;
  s21::multiset<int, std::greater<int>> other_multiset;

  other_std_multiset.merge(std_multiset);
  other_multiset.merge(multiset);

  EXPECT_EQ(std_multiset.empty(), multiset.empty());
  EXPECT_EQ(other_std_multiset.empty(), other_multiset.empty());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, empty_and_swap_1) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.swap(std_multiset);
  other_multiset.swap(multiset);

  EXPECT_EQ(std_multiset.empty(), multiset.empty());
  EXPECT_EQ(other_std_multiset.empty(), other_multiset.empty());
}
TEST(multiset, empty_and_swap_2) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.swap(std_multiset);
  other_multiset.swap(multiset);

  EXPECT_EQ(std_multiset.empty(), multiset.empty());
  EXPECT_EQ(other_std_multiset.empty(), other_multiset.empty());
}

// size_type size() const noexcept;
TEST(multiset, size_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;
  EXPECT_EQ(std_multiset.size(), multiset.size());
}
TEST(multiset, size_2) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};
  EXPECT_EQ(std_multiset.size(), multiset.size());
}
TEST(multiset, size_and_clear) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std_multiset.clear();
  multiset.clear();

  EXPECT_EQ(std_multiset.size(), multiset.size());
}

TEST(multiset, size_erase_insert) {
  std::multiset<int> std_multiset = {{1, 1}};
  s21::multiset<int> multiset = {{1, 1}};

  std_multiset.erase(1);
  multiset.erase(1);

  EXPECT_EQ(std_multiset.size(), multiset.size());

  std_multiset.insert({2, 2});
  multiset.insert({2, 2});

  EXPECT_EQ(std_multiset.size(), multiset.size());

  std_multiset.erase(2);
  multiset.erase(2);

  EXPECT_EQ(std_multiset.size(), multiset.size());
}
TEST(multiset, size_and_move) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  auto other_std_multiset = std::move(std_multiset);
  auto other_multiset = std::move(multiset);
  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(other_std_multiset.size(), other_multiset.size());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, size_and_merge_1) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.merge(std_multiset);
  other_multiset.merge(multiset);

  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(other_std_multiset.size(), other_multiset.size());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, size_and_merge_2) {
  std::multiset<int, std::less<int>> std_multiset = {1, 2, 3};
  s21::multiset<int, std::less<int>> multiset = {1, 2, 3};

  std::multiset<int, std::greater<int>> other_std_multiset;
  s21::multiset<int, std::greater<int>> other_multiset;

  other_std_multiset.merge(std_multiset);
  other_multiset.merge(multiset);

  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(other_std_multiset.size(), other_multiset.size());

  assert_multiset(std_multiset, multiset);
  assert_multiset(other_std_multiset, other_multiset);
}
TEST(multiset, size_and_swap_1) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.swap(std_multiset);
  other_multiset.swap(multiset);

  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(other_std_multiset.size(), other_multiset.size());
}
TEST(multiset, size_and_swap_2) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  std::multiset<int> other_std_multiset;
  s21::multiset<int> other_multiset;

  other_std_multiset.swap(std_multiset);
  other_multiset.swap(multiset);

  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(other_std_multiset.size(), other_multiset.size());
}
