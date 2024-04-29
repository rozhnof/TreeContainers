#pragma once

#include <map.h>

#include <iostream>
#include <map>

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value>>>
void assert_map(std::map<Key, Value, Compare, Allocator>& std_map,
                s21::map<Key, Value, Compare, Allocator>& map) {
  ASSERT_EQ(std_map.size(), map.size());
  ASSERT_EQ(std_map.get_allocator(), map.get_allocator());

  auto std_it = std_map.begin();
  auto it = map.begin();

  for (; std_it != std_map.end(); ++std_it, ++it) {
    ASSERT_EQ(std_it->first, it->first);
    ASSERT_EQ(std_it->second, it->second);
  }
}
