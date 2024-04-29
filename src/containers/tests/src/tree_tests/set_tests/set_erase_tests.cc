#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "../insert_erase_data.h"
#include "assert_iterators.h"
#include "assert_set.h"

// iterator erase( iterator pos );
TEST(set, erase_1_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      std_set.erase(std_set.find(val));
      set.erase(set.find(val));

      assert_set(std_set, set);
    }
  }
}
TEST(set, erase_1_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      std_set.erase(std_set.find(val));
      set.erase(set.find(val));

      assert_set(std_set, set);
    }
  }
}

// iterator erase( const_iterator pos );
TEST(set, erase_2_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      decltype(std_set)::const_iterator std_it = std_set.find(val);
      decltype(set)::const_iterator it = set.find(val);

      assert_iterators(std_set, set, std_it, it);

      std_set.erase(std_it);
      set.erase(it);

      assert_set(std_set, set);
    }
  }
}
TEST(set, erase_2_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      decltype(std_set)::const_iterator std_it = std_set.find(val);
      decltype(set)::const_iterator it = set.find(val);

      assert_iterators(std_set, set, std_it, it);

      std_set.erase(std_it);
      set.erase(it);

      assert_set(std_set, set);
    }
  }
}

// size_type erase( const Key& key );
TEST(set, erase_4_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      std_set.erase(val);
      set.erase(val);

      assert_set(std_set, set);
    }
  }
}

TEST(set, erase_4_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_set.insert(val);
      set.insert(val);

      assert_set(std_set, set);
    }

    for (auto val : erase_seq) {
      std_set.erase(val);
      set.erase(val);

      assert_set(std_set, set);
    }
  }
}