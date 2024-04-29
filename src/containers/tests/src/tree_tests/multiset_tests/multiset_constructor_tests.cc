#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "assert_multiset.h"

// multiset();
TEST(multiset, constructor_1_0) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  assert_multiset(std_multiset, multiset);
}

// explicit multiset(const Compare& comp, const Allocator& alloc = Allocator());
TEST(multiset, constructor_2_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset(comp, alloc);
  s21::multiset<int> multiset(comp, alloc);

  assert_multiset(std_multiset, multiset);
}

// explicit multiset(const Allocator& alloc);
TEST(multiset, constructor_3_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset(alloc);
  s21::multiset<int> multiset(alloc);

  assert_multiset(std_multiset, multiset);
}

// template<class InputIt>
// multiset(InputIt first, InputIt last,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(multiset, constructor_4_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std_multiset.begin(), std_multiset.end(),
                                       comp, alloc);
  s21::multiset<int> multiset_copy(multiset.begin(), multiset.end(), comp,
                                   alloc);

  assert_multiset(std_multiset, multiset);
}

// template<class InputIt>
// multiset(InputIt first, InputIt last, const Allocator& alloc)
TEST(multiset, constructor_5_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std_multiset.begin(), std_multiset.end(),
                                       alloc);
  s21::multiset<int> multiset_copy(multiset.begin(), multiset.end(), alloc);

  assert_multiset(std_multiset, multiset);
}

// multiset(const multiset& other);
TEST(multiset, constructor_6_0) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std_multiset);
  s21::multiset<int> multiset_copy(multiset);

  assert_multiset(std_multiset, multiset);
  assert_multiset(std_multiset_copy, multiset_copy);
}

// multiset(const multiset& other, const Allocator& alloc);
TEST(multiset, constructor_7_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std_multiset, alloc);
  s21::multiset<int> multiset_copy(multiset, alloc);

  assert_multiset(std_multiset, multiset);
  assert_multiset(std_multiset_copy, multiset_copy);
}

// multiset(multiset&& other);
TEST(multiset, constructor_8_0) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std::move(std_multiset));
  s21::multiset<int> multiset_copy(std::move(multiset));

  assert_multiset(std_multiset, multiset);
  assert_multiset(std_multiset_copy, multiset_copy);
}

// multiset(multiset&& other, const Allocator& alloc);
TEST(multiset, constructor_9_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  std::multiset<int> std_multiset_copy(std::move(std_multiset), alloc);
  s21::multiset<int> multiset_copy(std::move(multiset), alloc);

  assert_multiset(std_multiset, multiset);
  assert_multiset(std_multiset_copy, multiset_copy);
}

// multiset(std::initializer_list<value_type> init,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(multiset, constructor_10_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  {
    std::multiset<int> std_multiset({1, 2, 3});
    s21::multiset<int> multiset({1, 2, 3});
  }
  {
    std::multiset<int> std_multiset({1, 2, 3}, comp);
    s21::multiset<int> multiset({1, 2, 3}, comp);
  }
  {
    std::multiset<int> std_multiset({1, 2, 3}, comp, alloc);
    s21::multiset<int> multiset({1, 2, 3}, comp, alloc);
  }
}

// multiset(std::initializer_list<value_type> init, const Allocator& alloc )
TEST(multiset, constructor_11_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::multiset<int> std_multiset({1, 2, 3}, alloc);
  s21::multiset<int> multiset({1, 2, 3}, alloc);
}
