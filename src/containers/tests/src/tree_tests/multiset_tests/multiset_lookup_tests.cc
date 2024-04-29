#include <gtest/gtest.h>
#include <multiset.h>

#include <set>

#include "assert_multiset.h"

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
TEST(multiset, count_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  ASSERT_EQ(std_multiset.count(1), multiset.count(1));

  std_multiset.insert(1);
  multiset.insert(1);

  ASSERT_EQ(std_multiset.count(1), multiset.count(1));

  std_multiset.insert(1);
  multiset.insert(1);

  ASSERT_EQ(std_multiset.count(1), multiset.count(1));
}

TEST(multiset, count_2) {
  std::multiset<A, Compare> std_multiset;
  s21::multiset<A, Compare> multiset;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_multiset.count(key), multiset.count(key));

  std_multiset.insert(key);
  multiset.insert(key);

  multiset.count(key);

  ASSERT_EQ(std_multiset.count(key), multiset.count(key));
  ASSERT_EQ(std_multiset.count(transparent_key),
            multiset.count(transparent_key));

  std_multiset.insert(key);
  multiset.insert(key);

  ASSERT_EQ(std_multiset.count(key), multiset.count(key));
  ASSERT_EQ(std_multiset.count(transparent_key),
            multiset.count(transparent_key));
}

// template< class K > size_type count( const K& x ) const;
TEST(multiset, count_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::multiset<A, Compare> std_multiset = {key};
  const s21::multiset<A, Compare> multiset = {key};

  ASSERT_EQ(std_multiset.count(key), multiset.count(key));
  ASSERT_EQ(std_multiset.count(transparent_key),
            multiset.count(transparent_key));
}

// iterator find( const Key& key );
TEST(multiset, find_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  ASSERT_EQ(std_multiset.find(1) == std_multiset.end(),
            multiset.find(1) == multiset.end());

  std_multiset.insert(1);
  multiset.insert(1);

  ASSERT_EQ(*std_multiset.find(1), *multiset.find(1));
}

// const_iterator find( const Key& key ) const;
TEST(multiset, find_2) {
  {
    const std::multiset<int> std_multiset;
    const s21::multiset<int> multiset;
    ASSERT_EQ(std_multiset.find(1) == std_multiset.end(),
              multiset.find(1) == multiset.end());
  }
  {
    const std::multiset<int> std_multiset = {{1, 1}};
    const s21::multiset<int> multiset = {{1, 1}};
    ASSERT_EQ(*std_multiset.find(1), *multiset.find(1));
  }
}

// template< class K > iterator find( const K& x );
TEST(multiset, find_3) {
  std::multiset<A, Compare> std_multiset;
  s21::multiset<A, Compare> multiset;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_multiset.find(key) == std_multiset.end(),
            multiset.find(key) == multiset.end());

  std_multiset.insert(key);
  multiset.insert(key);

  ASSERT_EQ(std_multiset.find(key) == std_multiset.end(),
            multiset.find(key) == multiset.end());
  ASSERT_EQ(std_multiset.find(transparent_key) == std_multiset.end(),
            multiset.find(transparent_key) == multiset.end());
}

// template< class K > const_iterator find( const K& x ) const;
TEST(multiset, find_4) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::multiset<A, Compare> std_multiset = {key};
  const s21::multiset<A, Compare> multiset = {key};

  ASSERT_EQ(std_multiset.find(key) == std_multiset.end(),
            multiset.find(key) == multiset.end());
  ASSERT_EQ(std_multiset.find(transparent_key) == std_multiset.end(),
            multiset.find(transparent_key) == multiset.end());
}

// bool contains( const Key& key ) const;
TEST(multiset, contains_1) {
  std::multiset<int> std_multiset;
  s21::multiset<int> multiset;

  ASSERT_EQ(std_multiset.contains(1), multiset.contains(1));

  std_multiset.insert(1);
  multiset.insert(1);

  ASSERT_EQ(std_multiset.contains(1), multiset.contains(1));
}
TEST(multiset, contains_2) {
  std::multiset<A, Compare> std_multiset;
  s21::multiset<A, Compare> multiset;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_multiset.contains(key), multiset.contains(key));

  std_multiset.insert(key);
  multiset.insert(key);

  ASSERT_EQ(std_multiset.contains(key), multiset.contains(key));
  ASSERT_EQ(std_multiset.contains(transparent_key),
            multiset.contains(transparent_key));
}

// template< class K > bool contains( const K& x ) const;
TEST(multiset, contains_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::multiset<A, Compare> std_multiset = {key};
  const s21::multiset<A, Compare> multiset = {key};

  ASSERT_EQ(std_multiset.contains(key), multiset.contains(key));
  ASSERT_EQ(std_multiset.contains(transparent_key),
            multiset.contains(transparent_key));
}

// std::pair<iterator, iterator> equal_range( const Key& key );
TEST(multiset, equal_range_1) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_multiset.equal_range(2);
  auto [range_first, range_last] = multiset.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(2));
  ASSERT_TRUE(*range_first == *multiset.find(2));

  ASSERT_TRUE(*std_range_last == *std_multiset.find(3));
  ASSERT_TRUE(*range_last == *multiset.find(3));
}
TEST(multiset, equal_range_2) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_multiset.equal_range(3);
  auto [range_first, range_last] = multiset.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(3));
  ASSERT_TRUE(*range_first == *multiset.find(3));

  ASSERT_TRUE(std_range_last == std_multiset.end());
  ASSERT_TRUE(range_last == multiset.end());
}

// std::pair<const_iterator, const_iterator> equal_range( const Key& key )
// const;
TEST(multiset, equal_range_3) {
  const std::multiset<int> std_multiset = {1, 2, 3};
  const s21::multiset<int> multiset = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_multiset.equal_range(2);
  auto [range_first, range_last] = multiset.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(2));
  ASSERT_TRUE(*range_first == *multiset.find(2));

  ASSERT_TRUE(*std_range_last == *std_multiset.find(3));
  ASSERT_TRUE(*range_last == *multiset.find(3));
}
TEST(multiset, equal_range_4) {
  std::multiset<int> std_multiset = {1, 2, 3};
  s21::multiset<int> multiset = {1, 2, 3};

  auto [std_range_first, std_range_last] = std_multiset.equal_range(3);
  auto [range_first, range_last] = multiset.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(3));
  ASSERT_TRUE(*range_first == *multiset.find(3));

  ASSERT_TRUE(std_range_last == std_multiset.end());
  ASSERT_TRUE(range_last == multiset.end());
}

// template< class K >
// std::pair<iterator, iterator> equal_range( const K& x );
TEST(multiset, equal_range_5) {
  std::multiset<A, Compare> std_multiset = {A(1, "1"), A(2, "2"), A(3, "3")};
  s21::multiset<A, Compare> multiset = {A(1, "1"), A(2, "2"), A(3, "3")};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_multiset.equal_range(key2);
  auto [range_first, range_last] = multiset.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(key2));
  ASSERT_TRUE(*range_first == *multiset.find(key2));

  ASSERT_TRUE(*std_range_last == *std_multiset.find(key3));
  ASSERT_TRUE(*range_last == *multiset.find(key3));
}

// template< class K >
// std::pair<const_iterator, const_iterator> equal_range( const K& x ) const;
TEST(multiset, equal_range_6) {
  const std::multiset<A, Compare> std_multiset = {A(1, "1"), A(2, "2"),
                                                  A(3, "3")};
  const s21::multiset<A, Compare> multiset = {A(1, "1"), A(2, "2"), A(3, "3")};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_multiset.equal_range(key2);
  auto [range_first, range_last] = multiset.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_multiset.find(key2));
  ASSERT_TRUE(*range_first == *multiset.find(key2));

  ASSERT_TRUE(*std_range_last == *std_multiset.find(key3));
  ASSERT_TRUE(*range_last == *multiset.find(key3));
}

// iterator lower_bound( const Key& key );
TEST(multiset, lower_bound_1) {
  std::multiset<int> std_multiset = {10, 20, 30};
  s21::multiset<int> multiset = {10, 20, 30};

  {
    auto std_it = std_multiset.lower_bound(10);
    auto it = multiset.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_multiset.find(10));
    ASSERT_TRUE(*it == *multiset.find(10));
  }
  {
    auto std_it = std_multiset.lower_bound(15);
    auto it = multiset.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.lower_bound(25);
    auto it = multiset.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_multiset.find(30));
    ASSERT_TRUE(*it == *multiset.find(30));
  }
  {
    auto std_it = std_multiset.lower_bound(35);
    auto it = multiset.lower_bound(35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// const_iterator lower_bound( const Key& key ) const;
TEST(multiset, lower_bound_2) {
  const std::multiset<int> std_multiset = {10, 20, 30};
  const s21::multiset<int> multiset = {10, 20, 30};

  {
    auto std_it = std_multiset.lower_bound(10);
    auto it = multiset.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_multiset.find(10));
    ASSERT_TRUE(*it == *multiset.find(10));
  }
  {
    auto std_it = std_multiset.lower_bound(15);
    auto it = multiset.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.lower_bound(25);
    auto it = multiset.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_multiset.find(30));
    ASSERT_TRUE(*it == *multiset.find(30));
  }
  {
    auto std_it = std_multiset.lower_bound(35);
    auto it = multiset.lower_bound(35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// template< class K >
// iterator lower_bound( const K& x );
TEST(multiset, lower_bound_3) {
  std::multiset<A, Compare> std_multiset = {A(10, "10"), A(20, "20"),
                                            A(30, "30")};
  s21::multiset<A, Compare> multiset = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_multiset.lower_bound(key10);
    auto it = multiset.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_multiset.find(key10));
    ASSERT_TRUE(*it == *multiset.find(key10));
  }
  {
    auto std_it = std_multiset.lower_bound(key15);
    auto it = multiset.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.lower_bound(key25);
    auto it = multiset.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_multiset.find(key30));
    ASSERT_TRUE(*it == *multiset.find(key30));
  }
  {
    auto std_it = std_multiset.lower_bound(key35);
    auto it = multiset.lower_bound(key35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// template< class K >
// const_iterator lower_bound( const K& x ) const;
TEST(multiset, lower_bound_4) {
  const std::multiset<A, Compare> std_multiset = {A(10, "10"), A(20, "20"),
                                                  A(30, "30")};
  const s21::multiset<A, Compare> multiset = {A(10, "10"), A(20, "20"),
                                              A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_multiset.lower_bound(key10);
    auto it = multiset.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_multiset.find(key10));
    ASSERT_TRUE(*it == *multiset.find(key10));
  }
  {
    auto std_it = std_multiset.lower_bound(key15);
    auto it = multiset.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.lower_bound(key25);
    auto it = multiset.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_multiset.find(key30));
    ASSERT_TRUE(*it == *multiset.find(key30));
  }
  {
    auto std_it = std_multiset.lower_bound(key35);
    auto it = multiset.lower_bound(key35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// iterator upper_bound( const Key& key );
TEST(multiset, upper_bound_1) {
  std::multiset<int> std_multiset = {10, 20, 30};
  s21::multiset<int> multiset = {10, 20, 30};

  {
    auto std_it = std_multiset.upper_bound(10);
    auto it = multiset.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.upper_bound(15);
    auto it = multiset.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.upper_bound(25);
    auto it = multiset.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_multiset.find(30));
    ASSERT_TRUE(*it == *multiset.find(30));
  }
  {
    auto std_it = std_multiset.upper_bound(35);
    auto it = multiset.upper_bound(35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// const_iterator upper_bound( const Key& key ) const;
TEST(multiset, upper_bound_2) {
  const std::multiset<int> std_multiset = {10, 20, 30};
  const s21::multiset<int> multiset = {10, 20, 30};

  {
    auto std_it = std_multiset.upper_bound(10);
    auto it = multiset.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.upper_bound(15);
    auto it = multiset.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_multiset.find(20));
    ASSERT_TRUE(*it == *multiset.find(20));
  }
  {
    auto std_it = std_multiset.upper_bound(25);
    auto it = multiset.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_multiset.find(30));
    ASSERT_TRUE(*it == *multiset.find(30));
  }
  {
    auto std_it = std_multiset.upper_bound(35);
    auto it = multiset.upper_bound(35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// template< class K >
// iterator upper_bound( const K& x );
TEST(multiset, upper_bound_3) {
  std::multiset<A, Compare> std_multiset = {A(10, "10"), A(20, "20"),
                                            A(30, "30")};
  s21::multiset<A, Compare> multiset = {A(10, "10"), A(20, "20"), A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_multiset.upper_bound(key10);
    auto it = multiset.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.upper_bound(key15);
    auto it = multiset.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.upper_bound(key25);
    auto it = multiset.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_multiset.find(key30));
    ASSERT_TRUE(*it == *multiset.find(key30));
  }
  {
    auto std_it = std_multiset.upper_bound(key35);
    auto it = multiset.upper_bound(key35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}

// template< class K >
// const_iterator upper_bound( const K& x ) const;
TEST(multiset, upper_bound_4) {
  const std::multiset<A, Compare> std_multiset = {A(10, "10"), A(20, "20"),
                                                  A(30, "30")};
  const s21::multiset<A, Compare> multiset = {A(10, "10"), A(20, "20"),
                                              A(30, "30")};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_multiset.upper_bound(key10);
    auto it = multiset.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.upper_bound(key15);
    auto it = multiset.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_multiset.find(key20));
    ASSERT_TRUE(*it == *multiset.find(key20));
  }
  {
    auto std_it = std_multiset.upper_bound(key25);
    auto it = multiset.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_multiset.find(key30));
    ASSERT_TRUE(*it == *multiset.find(key30));
  }
  {
    auto std_it = std_multiset.upper_bound(key35);
    auto it = multiset.upper_bound(key35);

    ASSERT_TRUE(std_it == std_multiset.end());
    ASSERT_TRUE(it == multiset.end());
  }
}
