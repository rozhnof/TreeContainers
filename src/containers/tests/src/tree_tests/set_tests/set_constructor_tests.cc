#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "assert_set.h"

// set();
TEST(set, constructor_1_0) {
  std::set<int> std_set;
  s21::set<int> set;

  assert_set(std_set, set);
}

// explicit set(const Compare& comp, const Allocator& alloc = Allocator());
TEST(set, constructor_2_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set(comp, alloc);
  s21::set<int> set(comp, alloc);

  assert_set(std_set, set);
}

// explicit set(const Allocator& alloc);
TEST(set, constructor_3_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set(alloc);
  s21::set<int> set(alloc);

  assert_set(std_set, set);
}

// template<class InputIt>
// set(InputIt first, InputIt last,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(set, constructor_4_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std_set.begin(), std_set.end(), comp, alloc);
  s21::set<int> set_copy(set.begin(), set.end(), comp, alloc);

  assert_set(std_set, set);
}

// template<class InputIt>
// set(InputIt first, InputIt last, const Allocator& alloc)
TEST(set, constructor_5_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std_set.begin(), std_set.end(), alloc);
  s21::set<int> set_copy(set.begin(), set.end(), alloc);

  assert_set(std_set, set);
}

// set(const set& other);
TEST(set, constructor_6_0) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std_set);
  s21::set<int> set_copy(set);

  assert_set(std_set, set);
  assert_set(std_set_copy, set_copy);
}

// set(const set& other, const Allocator& alloc);
TEST(set, constructor_7_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std_set, alloc);
  s21::set<int> set_copy(set, alloc);

  assert_set(std_set, set);
  assert_set(std_set_copy, set_copy);
}

// set(set&& other);
TEST(set, constructor_8_0) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std::move(std_set));
  s21::set<int> set_copy(std::move(set));

  assert_set(std_set, set);
  assert_set(std_set_copy, set_copy);
}

// set(set&& other, const Allocator& alloc);
TEST(set, constructor_9_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  std::set<int> std_set_copy(std::move(std_set), alloc);
  s21::set<int> set_copy(std::move(set), alloc);

  assert_set(std_set, set);
  assert_set(std_set_copy, set_copy);
}

// set(std::initializer_list<value_type> init,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(set, constructor_10_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  {
    std::set<int> std_set({1, 2, 3});
    s21::set<int> set({1, 2, 3});
  }
  {
    std::set<int> std_set({1, 2, 3}, comp);
    s21::set<int> set({1, 2, 3}, comp);
  }
  {
    std::set<int> std_set({1, 2, 3}, comp, alloc);
    s21::set<int> set({1, 2, 3}, comp, alloc);
  }
}

// set(std::initializer_list<value_type> init, const Allocator& alloc )
TEST(set, constructor_11_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::set<int> std_set({1, 2, 3}, alloc);
  s21::set<int> set({1, 2, 3}, alloc);
}
