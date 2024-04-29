#pragma once

#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(
    std::multiset<Key, Compare, Allocator>& std_multiset,
    s21::multiset<Key, Compare, Allocator>& multiset,
    typename std::multiset<Key, Compare, Allocator>::const_iterator
        std_multiset_it,
    typename s21::multiset<Key, Compare, Allocator>::const_iterator
        multiset_it) {
  if (std_multiset_it != std_multiset.end() && multiset_it != multiset.end()) {
    ASSERT_EQ(*std_multiset_it, *multiset_it);
  } else {
    ASSERT_TRUE(std_multiset_it == std_multiset.end() &&
                multiset_it == multiset.end());
  }
}

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(
    std::multiset<Key, Compare, Allocator>& std_multiset,
    s21::multiset<Key, Compare, Allocator>& multiset,
    typename std::multiset<Key, Compare, Allocator>::const_reverse_iterator
        std_multiset_it,
    typename s21::multiset<Key, Compare, Allocator>::const_reverse_iterator
        multiset_it) {
  if (std_multiset_it != std_multiset.rend() &&
      multiset_it != multiset.rend()) {
    ASSERT_EQ(*std_multiset_it, *multiset_it);
  } else {
    ASSERT_TRUE(std_multiset_it == std_multiset.rend() &&
                multiset_it == multiset.rend());
  }
}

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
void assert_iterators(std::multiset<Key, Compare, Allocator>& std_multiset,
                      s21::multiset<Key, Compare, Allocator>& multiset) {
  assert_iterators(std_multiset, multiset, std_multiset.begin(),
                   multiset.begin());
  assert_iterators(std_multiset, multiset, std_multiset.cbegin(),
                   multiset.cbegin());

  assert_iterators(std_multiset, multiset, std_multiset.end(), multiset.end());
  assert_iterators(std_multiset, multiset, std_multiset.cend(),
                   multiset.cend());

  assert_iterators(std_multiset, multiset, std_multiset.rbegin(),
                   multiset.rbegin());
  assert_iterators(std_multiset, multiset, std_multiset.crbegin(),
                   multiset.crbegin());

  assert_iterators(std_multiset, multiset, std_multiset.rend(),
                   multiset.rend());
  assert_iterators(std_multiset, multiset, std_multiset.crend(),
                   multiset.crend());
}