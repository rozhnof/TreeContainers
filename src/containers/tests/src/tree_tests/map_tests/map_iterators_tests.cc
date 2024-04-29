#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value>>>
void assert_iterators(
    std::map<Key, Value, Compare, Allocator>& std_map,
    s21::map<Key, Value, Compare, Allocator>& map,
    typename std::map<Key, Value, Compare, Allocator>::const_iterator
        std_map_it,
    typename s21::map<Key, Value, Compare, Allocator>::const_iterator map_it) {
  if (std_map_it != std_map.end() && map_it != map.end()) {
    ASSERT_EQ(*std_map_it, *map_it);
  } else {
    ASSERT_TRUE(std_map_it == std_map.end() && map_it == map.end());
  }
}

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value>>>
void assert_iterators(
    std::map<Key, Value, Compare, Allocator>& std_map,
    s21::map<Key, Value, Compare, Allocator>& map,
    typename std::map<Key, Value, Compare, Allocator>::const_reverse_iterator
        std_map_it,
    typename s21::map<Key, Value, Compare, Allocator>::const_reverse_iterator
        map_it) {
  if (std_map_it != std_map.rend() && map_it != map.rend()) {
    ASSERT_EQ(*std_map_it, *map_it);
  } else {
    ASSERT_TRUE(std_map_it == std_map.rend() && map_it == map.rend());
  }
}

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value>>>
void assert_iterators(std::map<Key, Value, Compare, Allocator>& std_map,
                      s21::map<Key, Value, Compare, Allocator>& map) {
  assert_iterators(std_map, map, std_map.begin(), map.begin());
  assert_iterators(std_map, map, std_map.cbegin(), map.cbegin());

  assert_iterators(std_map, map, std_map.end(), map.end());
  assert_iterators(std_map, map, std_map.cend(), map.cend());

  assert_iterators(std_map, map, std_map.rbegin(), map.rbegin());
  assert_iterators(std_map, map, std_map.crbegin(), map.crbegin());

  assert_iterators(std_map, map, std_map.rend(), map.rend());
  assert_iterators(std_map, map, std_map.crend(), map.crend());
}

TEST(map, iterators_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  assert_iterators(std_map, map);

  std_map.insert({10, 10});
  map.insert({10, 10});

  assert_iterators(std_map, map);
}
TEST(map, iterators_2) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};
  assert_iterators(std_map, map);
}
TEST(map, iterators_3) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}};
  s21::map<int, int> map = {{1, 1}, {2, 2}};
  assert_iterators(std_map, map);
}
TEST(map, iterators_4) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};
  assert_iterators(std_map, map);
}
TEST(map, iterators_5) {
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int> map = {{1, 1}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);
}
TEST(map, iterators_6) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}};
  s21::map<int, int> map = {{1, 1}, {2, 2}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);
}
TEST(map, iterators_7) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);
}
TEST(map, iterators_8) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}};
  s21::map<int, int> map = {{1, 1}, {2, 2}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);

  std_map.erase(2);
  map.erase(2);

  assert_iterators(std_map, map);
}
TEST(map, iterators_9) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);

  std_map.erase(2);
  map.erase(2);

  assert_iterators(std_map, map);
}
TEST(map, iterators_10) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);

  std_map.erase(3);
  map.erase(3);

  assert_iterators(std_map, map);
}
TEST(map, iterators_11) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.erase(2);
  map.erase(2);

  assert_iterators(std_map, map);

  std_map.erase(3);
  map.erase(3);

  assert_iterators(std_map, map);
}
TEST(map, iterators_12) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  std_map.erase(1);
  map.erase(1);

  std_map.erase(2);
  map.erase(2);

  std_map.erase(3);
  map.erase(3);

  assert_iterators(std_map, map);
}
TEST(map, iterators_13) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  std_map.insert({1, 1});
  map.insert({1, 1});

  assert_iterators(std_map, map);

  std_map.erase(1);
  map.erase(1);

  assert_iterators(std_map, map);
}

TEST(map, iterators_14) {
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  {
    auto it = map.find(2);

    auto prev = it;
    --prev;
    ASSERT_EQ(*map.find(1), *prev);

    auto next = it;
    ++next;
    ASSERT_EQ(*map.find(3), *next);

    map.erase(2);

    ASSERT_EQ(*(++prev), *next);
  }

  {
    auto prev = map.find(1);
    auto next = prev;
    ++next;

    auto [it, _] = map.insert({2, 2});

    ASSERT_EQ(*(++prev), *it);
    ASSERT_EQ(*(--next), *it);
  }
}