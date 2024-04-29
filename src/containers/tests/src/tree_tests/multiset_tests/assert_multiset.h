#pragma once

#include <multiset.h>

#include <iostream>
#include <set>

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
void assert_multiset(std::multiset<Key, Compare, Allocator>& std_multiset,
                     s21::multiset<Key, Compare, Allocator>& multiset) {
  ASSERT_EQ(std_multiset.size(), multiset.size());
  ASSERT_EQ(std_multiset.get_allocator(), multiset.get_allocator());

  auto std_it = std_multiset.begin();
  auto it = multiset.begin();

  for (; std_it != std_multiset.end(); ++std_it, ++it) {
    ASSERT_EQ(*std_it, *it);
  }
}
