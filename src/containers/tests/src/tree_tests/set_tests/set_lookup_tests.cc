#include <gtest/gtest.h>
#include <set.h>

#include <set>

#include "assert_set.h"

struct A {
  int key = 0;
  std::string data;

  A() {
  }
  A(int key, const std::string data)
      : key(key),
        data(data) {
  }

  bool operator<(const A& other) const {
    return key < other.key;
  }

  bool operator==(const A& other) const {
    return key == other.key && data == other.data;
  }
};

struct Compare {
  using is_transparent = void;

  bool operator()(const A& lhs, const A& rhs) const {
    return lhs < rhs;
  }

  bool operator()(const std::string& lhs, const A& rhs) const {
    return lhs < rhs.data;
  }

  bool operator()(const A& lhs, const std::string& rhs) const {
    return lhs.data < rhs;
  }
};

// size_type count( const Key& key ) const;
TEST(set, count_1) {
  std::set<int> std_set;
  s21::set<int> set;

  ASSERT_EQ(std_set.count(1), set.count(1));

  std_set.insert(1);
  set.insert(1);

  ASSERT_EQ(std_set.count(1), set.count(1));

  std_set.insert(1);
  set.insert(1);

  ASSERT_EQ(std_set.count(1), set.count(1));
}

TEST(set, count_2) {
  std::set<A, Compare> std_set;
  s21::set<A, Compare> set;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_set.count(key), set.count(key));

  std_set.insert(key);
  set.insert(key);

  set.count(key);

  ASSERT_EQ(std_set.count(key), set.count(key));
  ASSERT_EQ(std_set.count(transparent_key), set.count(transparent_key));

  std_set.insert(key);
  set.insert(key);

  ASSERT_EQ(std_set.count(key), set.count(key));
  ASSERT_EQ(std_set.count(transparent_key), set.count(transparent_key));
}

// template< class K > size_type count( const K& x ) const;
TEST(set, count_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::set<A, Compare> std_set = {key};
  const s21::set<A, Compare> set = {key};

  ASSERT_EQ(std_set.count(key), set.count(key));
  ASSERT_EQ(std_set.count(transparent_key), set.count(transparent_key));
}

// iterator find( const Key& key );
TEST(set, find_1) {
  std::set<int> std_set;
  s21::set<int> set;

  ASSERT_EQ(std_set.find(1) == std_set.end(), set.find(1) == set.end());

  std_set.insert(1);
  set.insert(1);

  ASSERT_EQ(*std_set.find(1), *set.find(1));
}

// const_iterator find( const Key& key ) const;
TEST(set, find_2) {
  {
    const std::set<int> std_set;
    const s21::set<int> set;
    ASSERT_EQ(std_set.find(1) == std_set.end(), set.find(1) == set.end());
  }
  {
    const std::set<int> std_set = {{1, 1}};
    const s21::set<int> set = {{1, 1}};
    ASSERT_EQ(*std_set.find(1), *set.find(1));
  }
}

// template< class K > iterator find( const K& x );
TEST(set, find_3) {
  std::set<A, Compare> std_set;
  s21::set<A, Compare> set;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_set.find(key) == std_set.end(), set.find(key) == set.end());

  std_set.insert(key);
  set.insert(key);

  ASSERT_EQ(std_set.find(key) == std_set.end(), set.find(key) == set.end());
  ASSERT_EQ(std_set.find(transparent_key) == std_set.end(),
            set.find(transparent_key) == set.end());
}

// template< class K > const_iterator find( const K& x ) const;
TEST(set, find_4) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::set<A, Compare> std_set = {key};
  const s21::set<A, Compare> set = {key};

  ASSERT_EQ(std_set.find(key) == std_set.end(), set.find(key) == set.end());
  ASSERT_EQ(std_set.find(transparent_key) == std_set.end(),
            set.find(transparent_key) == set.end());
}

// bool contains( const Key& key ) const;
TEST(set, contains_1) {
  std::set<int> std_set;
  s21::set<int> set;

  ASSERT_EQ(std_set.contains(1), set.contains(1));

  std_set.insert(1);
  set.insert(1);

  ASSERT_EQ(std_set.contains(1), set.contains(1));
}
TEST(set, contains_2) {
  std::set<A, Compare> std_set;
  s21::set<A, Compare> set;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_set.contains(key), set.contains(key));

  std_set.insert(key);
  set.insert(key);

  ASSERT_EQ(std_set.contains(key), set.contains(key));
  ASSERT_EQ(std_set.contains(transparent_key), set.contains(transparent_key));
}

// template< class K > bool contains( const K& x ) const;
TEST(set, contains_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::set<A, Compare> std_set = {key};
  const s21::set<A, Compare> set = {key};

  ASSERT_EQ(std_set.contains(key), set.contains(key));
  ASSERT_EQ(std_set.contains(transparent_key), set.contains(transparent_key));
}

// std::pair<iterator, iterator> equal_range( const Key& key );
TEST(set, equal_range_1) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_set.equal_range(2);
  auto [range_first, range_last] = set.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_set.find(2));
  ASSERT_TRUE(*range_first == *set.find(2));

  ASSERT_TRUE(*std_range_last == *std_set.find(3));
  ASSERT_TRUE(*range_last == *set.find(3));
}
TEST(set, equal_range_2) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_set.equal_range(3);
  auto [range_first, range_last] = set.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_set.find(3));
  ASSERT_TRUE(*range_first == *set.find(3));

  ASSERT_TRUE(std_range_last == std_set.end());
  ASSERT_TRUE(range_last == set.end());
}

// std::pair<const_iterator, const_iterator> equal_range( const Key& key )
// const;
TEST(set, equal_range_3) {
  const std::set<int> std_set = {1, 2, 3};
  const s21::set<int> set = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_set.equal_range(2);
  auto [range_first, range_last] = set.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_set.find(2));
  ASSERT_TRUE(*range_first == *set.find(2));

  ASSERT_TRUE(*std_range_last == *std_set.find(3));
  ASSERT_TRUE(*range_last == *set.find(3));
}
TEST(set, equal_range_4) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> set = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_set.equal_range(3);
  auto [range_first, range_last] = set.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_set.find(3));
  ASSERT_TRUE(*range_first == *set.find(3));

  ASSERT_TRUE(std_range_last == std_set.end());
  ASSERT_TRUE(range_last == set.end());
}

// template< class K >
// std::pair<iterator, iterator> equal_range( const K& x );
TEST(set, equal_range_5) {
  std::set<A, Compare> std_set = {A(1, "1"), A(2, "2"), A(3, "3")};
  s21::set<A, Compare> set = {A(1, "1"), A(2, "2"), A(3, "3")};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_set.equal_range(key2);
  auto [range_first, range_last] = set.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_set.find(key2));
  ASSERT_TRUE(*range_first == *set.find(key2));

  ASSERT_TRUE(*std_range_last == *std_set.find(key3));
  ASSERT_TRUE(*range_last == *set.find(key3));
}

// template< class K >
// std::pair<const_iterator, const_iterator> equal_range( const K& x ) const;
TEST(set, equal_range_6) {
  const std::set<A, Compare> std_set = {A(1, "1"), A(2, "2"), A(3, "3")};
  const s21::set<A, Compare> set = {A(1, "1"), A(2, "2"), A(3, "3")};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_set.equal_range(key2);
  auto [range_first, range_last] = set.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_set.find(key2));
  ASSERT_TRUE(*range_first == *set.find(key2));

  ASSERT_TRUE(*std_range_last == *std_set.find(key3));
  ASSERT_TRUE(*range_last == *set.find(key3));
}

// iterator lower_bound( const Key& key );
TEST(set, lower_bound_1) {
  std::set<int> std_set = {10, 20, 30};
  s21::set<int> set = {10, 20, 30};

  {
    auto std_it = std_set.lower_bound(10);
    auto it = set.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_set.find(10));
    ASSERT_TRUE(*it == *set.find(10));
  }
  {
    auto std_it = std_set.lower_bound(15);
    auto it = set.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.lower_bound(25);
    auto it = set.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_set.find(30));
    ASSERT_TRUE(*it == *set.find(30));
  }
  {
    auto std_it = std_set.lower_bound(35);
    auto it = set.lower_bound(35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// const_iterator lower_bound( const Key& key ) const;
TEST(set, lower_bound_2) {
  const std::set<int> std_set = {10, 20, 30};
  const s21::set<int> set = {10, 20, 30};

  {
    auto std_it = std_set.lower_bound(10);
    auto it = set.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_set.find(10));
    ASSERT_TRUE(*it == *set.find(10));
  }
  {
    auto std_it = std_set.lower_bound(15);
    auto it = set.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.lower_bound(25);
    auto it = set.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_set.find(30));
    ASSERT_TRUE(*it == *set.find(30));
  }
  {
    auto std_it = std_set.lower_bound(35);
    auto it = set.lower_bound(35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// template< class K >
// iterator lower_bound( const K& x );
TEST(set, lower_bound_3) {
  std::set<A, Compare> std_set = {A(10, "10"), A(20, "20"), A(30, "30")};
  s21::set<A, Compare> set = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_set.lower_bound(key10);
    auto it = set.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_set.find(key10));
    ASSERT_TRUE(*it == *set.find(key10));
  }
  {
    auto std_it = std_set.lower_bound(key15);
    auto it = set.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.lower_bound(key25);
    auto it = set.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_set.find(key30));
    ASSERT_TRUE(*it == *set.find(key30));
  }
  {
    auto std_it = std_set.lower_bound(key35);
    auto it = set.lower_bound(key35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// template< class K >
// const_iterator lower_bound( const K& x ) const;
TEST(set, lower_bound_4) {
  const std::set<A, Compare> std_set = {A(10, "10"), A(20, "20"), A(30, "30")};
  const s21::set<A, Compare> set = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_set.lower_bound(key10);
    auto it = set.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_set.find(key10));
    ASSERT_TRUE(*it == *set.find(key10));
  }
  {
    auto std_it = std_set.lower_bound(key15);
    auto it = set.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.lower_bound(key25);
    auto it = set.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_set.find(key30));
    ASSERT_TRUE(*it == *set.find(key30));
  }
  {
    auto std_it = std_set.lower_bound(key35);
    auto it = set.lower_bound(key35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// iterator upper_bound( const Key& key );
TEST(set, upper_bound_1) {
  std::set<int> std_set = {10, 20, 30};
  s21::set<int> set = {10, 20, 30};

  {
    auto std_it = std_set.upper_bound(10);
    auto it = set.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.upper_bound(15);
    auto it = set.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.upper_bound(25);
    auto it = set.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_set.find(30));
    ASSERT_TRUE(*it == *set.find(30));
  }
  {
    auto std_it = std_set.upper_bound(35);
    auto it = set.upper_bound(35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// const_iterator upper_bound( const Key& key ) const;
TEST(set, upper_bound_2) {
  const std::set<int> std_set = {10, 20, 30};
  const s21::set<int> set = {10, 20, 30};

  {
    auto std_it = std_set.upper_bound(10);
    auto it = set.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.upper_bound(15);
    auto it = set.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_set.find(20));
    ASSERT_TRUE(*it == *set.find(20));
  }
  {
    auto std_it = std_set.upper_bound(25);
    auto it = set.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_set.find(30));
    ASSERT_TRUE(*it == *set.find(30));
  }
  {
    auto std_it = std_set.upper_bound(35);
    auto it = set.upper_bound(35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// template< class K >
// iterator upper_bound( const K& x );
TEST(set, upper_bound_3) {
  std::set<A, Compare> std_set = {A(10, "10"), A(20, "20"), A(30, "30")};
  s21::set<A, Compare> set = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_set.upper_bound(key10);
    auto it = set.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.upper_bound(key15);
    auto it = set.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.upper_bound(key25);
    auto it = set.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_set.find(key30));
    ASSERT_TRUE(*it == *set.find(key30));
  }
  {
    auto std_it = std_set.upper_bound(key35);
    auto it = set.upper_bound(key35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}

// template< class K >
// const_iterator upper_bound( const K& x ) const;
TEST(set, upper_bound_4) {
  const std::set<A, Compare> std_set = {A(10, "10"), A(20, "20"), A(30, "30")};
  const s21::set<A, Compare> set = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_set.upper_bound(key10);
    auto it = set.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.upper_bound(key15);
    auto it = set.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_set.find(key20));
    ASSERT_TRUE(*it == *set.find(key20));
  }
  {
    auto std_it = std_set.upper_bound(key25);
    auto it = set.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_set.find(key30));
    ASSERT_TRUE(*it == *set.find(key30));
  }
  {
    auto std_it = std_set.upper_bound(key35);
    auto it = set.upper_bound(key35);

    ASSERT_TRUE(std_it == std_set.end());
    ASSERT_TRUE(it == set.end());
  }
}
