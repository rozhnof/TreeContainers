#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "../insert_erase_data.h"
#include "assert_iterators.h"
#include "assert_set.h"

TEST(set, insert_1_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (const auto& value : insert_seq) {
      auto it_std = std_set.insert(value);
      auto it_s21 = set.insert(value);

      assert_set(std_set, set);
    }
  }
}
TEST(set, insert_1_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto it_std = std_set.insert(value);
      auto it_s21 = set.insert(value);

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_3_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      auto it_std = std_set.insert(std::move(val1));
      auto it_s21 = set.insert(std::move(val2));

      assert_set(std_set, set);
    }
  }
}
TEST(set, insert_3_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      auto it_std = std_set.insert(std::move(val1));
      auto it_s21 = set.insert(std::move(val2));

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_4_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    auto std_it = std_set.end();
    auto it = set.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_set.insert(std_set.end(), val1);
      it = set.insert(set.end(), val2);

      ASSERT_EQ(*std_it, *it);

      assert_set(std_set, set);
    }
  }
}
TEST(set, insert_4_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_set.end();
    auto it = set.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_set.insert(std_set.end(), val1);
      it = set.insert(set.end(), val2);

      ASSERT_EQ(*std_it, *it);

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_6_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    auto std_it = std_set.end();
    auto it = set.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_set.insert(std_set.end(), std::move(val1));
      it = set.insert(set.end(), std::move(val2));

      ASSERT_EQ(*std_it, *it);

      assert_set(std_set, set);
    }
  }
}
TEST(set, insert_6_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_set.end();
    auto it = set.end();

    for (const auto& value : insert_seq) {
      auto val1 = value;
      auto val2 = value;

      std_it = std_set.insert(std_set.end(), std::move(val1));
      it = set.insert(set.end(), std::move(val2));

      ASSERT_EQ(*std_it, *it);

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_7_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    std_set.insert(insert_seq.begin(), insert_seq.end());
    set.insert(insert_seq.begin(), insert_seq.end());

    assert_set(std_set, set);
  }
}
TEST(set, insert_7_1) {
  std::set<int> std_set;
  s21::set<int> set;

  for (const auto& insert_seq : insert_sequences) {
    std_set.insert(insert_seq.begin(), insert_seq.end());
    set.insert(insert_seq.begin(), insert_seq.end());

    assert_set(std_set, set);
  }
}

TEST(set, insert_9_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    for (const auto& value : insert_seq) {
      std_set.insert(1);
      set.insert(1);

      auto std_nh = std::move(std_set.extract(1));
      auto nh = std::move(set.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      auto std_it = std_set.insert(std::move(std_nh));
      auto it = set.insert(std::move(nh));

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_9_1) {
  std::set<int> std_set;
  s21::set<int> set;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      std_set.insert(1);
      set.insert(1);

      auto std_nh = std::move(std_set.extract(1));
      auto nh = std::move(set.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      auto std_it = std_set.insert(std::move(std_nh));
      auto it = set.insert(std::move(nh));

      assert_set(std_set, set);
    }
  }
}

TEST(set, insert_10_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::set<int> std_set;
    s21::set<int> set;

    auto std_it = std_set.begin();
    auto it = set.begin();

    for (const auto& value : insert_seq) {
      std_set.insert(1);
      set.insert(1);

      auto std_nh = std::move(std_set.extract(1));
      auto nh = std::move(set.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      std_it = std_set.insert(std_set.end(), std::move(std_nh));
      it = set.insert(set.end(), std::move(nh));

      assert_iterators(std_set, set, std_it, it);

      assert_set(std_set, set);

      ++i;
    }
  }
}
TEST(set, insert_10_1) {
  std::set<int> std_set;
  s21::set<int> set;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_set.begin();
    auto it = set.begin();

    for (const auto& value : insert_seq) {
      std_set.insert(1);
      set.insert(1);

      auto std_nh = std::move(std_set.extract(1));
      auto nh = std::move(set.extract(1));

      std_nh.value() = value;
      nh.value() = value;

      std_it = std_set.insert(std_set.end(), std::move(std_nh));
      it = set.insert(set.end(), std::move(nh));

      assert_iterators(std_set, set, std_it, it);

      assert_set(std_set, set);
    }
  }
}