#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "../insert_erase_data.h"
#include "assert_iterators.h"
#include "assert_multiset.h"

TEST(multiset, insert_1_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    for (const auto& value : insert_seq) {
      auto it_std = std_multiset.insert(value);
      auto it_s21 = multiset.insert(value);

      ASSERT_EQ(*it_std, *it_s21);

      assert_multiset(std_multiset, multiset);
    }
  }
}
TEST(multiset, insert_1_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto it_std = std_multiset.insert(value);
      auto it_s21 = multiset.insert(value);

      ASSERT_EQ(*it_std, *it_s21);

      assert_multiset(std_multiset, multiset);
    }
  }
}

TEST(multiset, insert_3_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      auto it_std = std_multiset.insert(std::move(val1));
      auto it_s21 = multiset.insert(std::move(val2));

      ASSERT_EQ(*it_std, *it_s21);

      assert_multiset(std_multiset, multiset);
    }
  }
}
TEST(multiset, insert_3_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      auto it_std = std_multiset.insert(std::move(val1));
      auto it_s21 = multiset.insert(std::move(val2));

      ASSERT_EQ(*it_std, *it_s21);

      assert_multiset(std_multiset, multiset);
    }
  }
}

TEST(multiset, insert_4_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    auto std_it = std_multiset.end();
    auto it = multiset.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_multiset.insert(std_multiset.end(), val1);
      it = multiset.insert(multiset.end(), val2);

      ASSERT_EQ(*std_it, *it);

      assert_multiset(std_multiset, multiset);
    }
  }
}
TEST(multiset, insert_4_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_multiset.end();
    auto it = multiset.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_multiset.insert(std_multiset.end(), val1);
      it = multiset.insert(multiset.end(), val2);

      ASSERT_EQ(*std_it, *it);

      assert_multiset(std_multiset, multiset);
    }
  }
}

TEST(multiset, insert_6_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    auto std_it = std_multiset.end();
    auto it = multiset.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_multiset.insert(std_multiset.end(), std::move(val1));
      it = multiset.insert(multiset.end(), std::move(val2));

      ASSERT_EQ(*std_it, *it);

      assert_multiset(std_multiset, multiset);
    }
  }
}
TEST(multiset, insert_6_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_multiset.end();
    auto it = multiset.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_multiset.insert(std_multiset.end(), std::move(val1));
      it = multiset.insert(multiset.end(), std::move(val2));

      ASSERT_EQ(*std_it, *it);

      assert_multiset(std_multiset, multiset);
    }
  }
}

TEST(multiset, insert_7_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    std_multiset.insert(insert_seq.begin(), insert_seq.end());
    multiset.insert(insert_seq.begin(), insert_seq.end());

    assert_multiset(std_multiset, multiset);
  }
}
TEST(multiset, insert_7_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  for (const auto& insert_seq : insert_sequences) {
    std_multiset.insert(insert_seq.begin(), insert_seq.end());
    multiset.insert(insert_seq.begin(), insert_seq.end());

    assert_multiset(std_multiset, multiset);
  }
}

TEST(multiset, insert_9_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    for (const auto& value : insert_seq) {
      std_multiset.insert(1);
      multiset.insert(1);

      auto std_nh = std::move(std_multiset.extract(1));
      auto nh = std::move(multiset.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      auto std_it = std_multiset.insert(std::move(std_nh));
      auto it = multiset.insert(std::move(nh));

      assert_iterators(std_multiset, multiset, std_it, it);

      assert_multiset(std_multiset, multiset);
    }
  }
}

TEST(multiset, insert_10_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::multiset<int> std_multiset;
    s21::multiset<int> multiset;

    auto std_it = std_multiset.begin();
    auto it = multiset.begin();

    for (const auto& value : insert_seq) {
      std_multiset.insert(1);
      multiset.insert(1);

      auto std_nh = std::move(std_multiset.extract(1));
      auto nh = std::move(multiset.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      std_it = std_multiset.insert(std_multiset.end(), std::move(std_nh));
      it = multiset.insert(multiset.end(), std::move(nh));

      assert_iterators(std_multiset, multiset, std_it, it);

      assert_multiset(std_multiset, multiset);

      ++i;
    }
  }
}
