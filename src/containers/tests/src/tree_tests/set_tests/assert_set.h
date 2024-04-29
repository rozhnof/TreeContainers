#pragma once

#include <set.h>

#include <iostream>
#include <set>

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
void assert_set(std::set<Key, Compare, Allocator>& std_set,
                s21::set<Key, Compare, Allocator>& set) {
  ASSERT_EQ(std_set.size(), set.size());
  ASSERT_EQ(std_set.get_allocator(), set.get_allocator());

  auto std_it = std_set.begin();
  auto it = set.begin();

  for (; std_it != std_set.end(); ++std_it, ++it) {
    ASSERT_EQ(*std_it, *it);
  }
}
