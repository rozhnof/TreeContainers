#pragma once

#include <gtest/gtest.h>
#include <set.h>

#include <set>

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(
    std::set<Key, Compare, Allocator>& std_set,
    s21::set<Key, Compare, Allocator>& set,
    typename std::set<Key, Compare, Allocator>::const_iterator std_set_it,
    typename s21::set<Key, Compare, Allocator>::const_iterator set_it) {
  if (std_set_it != std_set.end() && set_it != set.end()) {
    ASSERT_EQ(*std_set_it, *set_it);
  } else {
    ASSERT_TRUE(std_set_it == std_set.end() && set_it == set.end());
  }
}

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(
    std::set<Key, Compare, Allocator>& std_set,
    s21::set<Key, Compare, Allocator>& set,
    typename std::set<Key, Compare, Allocator>::const_reverse_iterator
        std_set_it,
    typename s21::set<Key, Compare, Allocator>::const_reverse_iterator set_it) {
  if (std_set_it != std_set.rend() && set_it != set.rend()) {
    ASSERT_EQ(*std_set_it, *set_it);
  } else {
    ASSERT_TRUE(std_set_it == std_set.rend() && set_it == set.rend());
  }
}

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(std::set<Key, Compare, Allocator>& std_set,
                      s21::set<Key, Compare, Allocator>& set) {
  assert_iterators(std_set, set, std_set.begin(), set.begin());
  assert_iterators(std_set, set, std_set.cbegin(), set.cbegin());

  assert_iterators(std_set, set, std_set.end(), set.end());
  assert_iterators(std_set, set, std_set.cend(), set.cend());

  assert_iterators(std_set, set, std_set.rbegin(), set.rbegin());
  assert_iterators(std_set, set, std_set.crbegin(), set.crbegin());

  assert_iterators(std_set, set, std_set.rend(), set.rend());
  assert_iterators(std_set, set, std_set.crend(), set.crend());
}