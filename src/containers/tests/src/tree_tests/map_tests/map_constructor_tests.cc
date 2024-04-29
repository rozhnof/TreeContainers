#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

// map();
TEST(map, constructor_1_0) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  assert_map(std_map, map);
}

// explicit map(const Compare& comp, const Allocator& alloc = Allocator());
TEST(map, constructor_2_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map(comp, alloc);
  s21::map<int, int> map(comp, alloc);

  assert_map(std_map, map);
}

// explicit map(const Allocator& alloc);
TEST(map, constructor_3_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map(alloc);
  s21::map<int, int> map(alloc);

  assert_map(std_map, map);
}

// template<class InputIt>
// map(InputIt first, InputIt last,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(map, constructor_4_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std_map.begin(), std_map.end(), comp, alloc);
  s21::map<int, int> map_copy(map.begin(), map.end(), comp, alloc);

  assert_map(std_map, map);
}

// template<class InputIt>
// map(InputIt first, InputIt last, const Allocator& alloc)
TEST(map, constructor_5_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std_map.begin(), std_map.end(), alloc);
  s21::map<int, int> map_copy(map.begin(), map.end(), alloc);

  assert_map(std_map, map);
}

// map(const map& other);
TEST(map, constructor_6_0) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std_map);
  s21::map<int, int> map_copy(map);

  assert_map(std_map, map);
  assert_map(std_map_copy, map_copy);
}

// map(const map& other, const Allocator& alloc);
TEST(map, constructor_7_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std_map, alloc);
  s21::map<int, int> map_copy(map, alloc);

  assert_map(std_map, map);
  assert_map(std_map_copy, map_copy);
}

// map(map&& other);
TEST(map, constructor_8_0) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std::move(std_map));
  s21::map<int, int> map_copy(std::move(map));

  assert_map(std_map, map);
  assert_map(std_map_copy, map_copy);
}

// map(map&& other, const Allocator& alloc);
TEST(map, constructor_9_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std::map<int, int> std_map_copy(std::move(std_map), alloc);
  s21::map<int, int> map_copy(std::move(map), alloc);

  assert_map(std_map, map);
  assert_map(std_map_copy, map_copy);
}

// map(std::initializer_list<value_type> init,
//     const Compare& comp = Compare(),
//     const Allocator& alloc = Allocator());
TEST(map, constructor_10_0) {
  std::less<int> comp;
  std::allocator<std::pair<int, int>> alloc;

  {
    std::map<int, int> std_map({{1, 1}, {2, 2}, {3, 3}});
    s21::map<int, int> map({{1, 1}, {2, 2}, {3, 3}});
  }
  {
    std::map<int, int> std_map({{1, 1}, {2, 2}, {3, 3}}, comp);
    s21::map<int, int> map({{1, 1}, {2, 2}, {3, 3}}, comp);
  }
  {
    std::map<int, int> std_map({{1, 1}, {2, 2}, {3, 3}}, comp, alloc);
    s21::map<int, int> map({{1, 1}, {2, 2}, {3, 3}}, comp, alloc);
  }
}

// map(std::initializer_list<value_type> init, const Allocator& alloc )
TEST(map, constructor_11_0) {
  std::allocator<std::pair<int, int>> alloc;

  std::map<int, int> std_map({{1, 1}, {2, 2}, {3, 3}}, alloc);
  s21::map<int, int> map({{1, 1}, {2, 2}, {3, 3}}, alloc);
}
