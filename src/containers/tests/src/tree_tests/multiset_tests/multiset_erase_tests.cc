#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "../insert_erase_data.h"
#include "assert_iterators.h"
#include "assert_multiset.h"

// iterator erase( iterator pos );
TEST(multiset, erase_1_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    for (auto val : insert_seq) {
      std_multiset.insert(val);
      multiset.insert(val);

      assert_multiset(std_multiset, multiset);
    }

    for (auto val : erase_seq) {
      std_multiset.erase(std_multiset.find(val));
      multiset.erase(multiset.find(val));

      assert_multiset(std_multiset, multiset);
    }
  }
}
// iterator erase( const_iterator pos );
TEST(multiset, erase_2_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    for (auto val : insert_seq) {
      std_multiset.insert(val);
      multiset.insert(val);

      assert_multiset(std_multiset, multiset);
    }

    for (auto val : erase_seq) {
      decltype(std_multiset)::const_iterator std_it = std_multiset.find(val);
      decltype(multiset)::const_iterator it = multiset.find(val);

      assert_iterators(std_multiset, multiset, std_it, it);

      std_multiset.erase(std_it);
      multiset.erase(it);

      assert_multiset(std_multiset, multiset);
    }
  }
}