#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "assert_map.h"

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
TEST(map, count_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  ASSERT_EQ(std_map.count(1), map.count(1));

  std_map.insert({1, 1});
  map.insert({1, 1});

  ASSERT_EQ(std_map.count(1), map.count(1));

  std_map.insert({1, 1});
  map.insert({1, 1});

  ASSERT_EQ(std_map.count(1), map.count(1));
}

TEST(map, count_2) {
  std::map<A, int, Compare> std_map;
  s21::map<A, int, Compare> map;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_map.count(key), map.count(key));

  std_map.insert({key, 1});
  map.insert({key, 1});

  map.count(key);

  ASSERT_EQ(std_map.count(key), map.count(key));
  ASSERT_EQ(std_map.count(transparent_key), map.count(transparent_key));

  std_map.insert({key, 1});
  map.insert({key, 1});

  ASSERT_EQ(std_map.count(key), map.count(key));
  ASSERT_EQ(std_map.count(transparent_key), map.count(transparent_key));
}

// template< class K > size_type count( const K& x ) const;
TEST(map, count_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::map<A, int, Compare> std_map = {{key, 1}};
  const s21::map<A, int, Compare> map = {{key, 1}};

  ASSERT_EQ(std_map.count(key), map.count(key));
  ASSERT_EQ(std_map.count(transparent_key), map.count(transparent_key));
}

// iterator find( const Key& key );
TEST(map, find_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  ASSERT_EQ(std_map.find(1) == std_map.end(), map.find(1) == map.end());

  std_map.insert({1, 1});
  map.insert({1, 1});

  ASSERT_EQ(*std_map.find(1), *map.find(1));
}

// const_iterator find( const Key& key ) const;
TEST(map, find_2) {
  {
    const std::map<int, int> std_map;
    const s21::map<int, int> map;
    ASSERT_EQ(std_map.find(1) == std_map.end(), map.find(1) == map.end());
  }
  {
    const std::map<int, int> std_map = {{1, 1}};
    const s21::map<int, int> map = {{1, 1}};
    ASSERT_EQ(*std_map.find(1), *map.find(1));
  }
}

// template< class K > iterator find( const K& x );
TEST(map, find_3) {
  std::map<A, int, Compare> std_map;
  s21::map<A, int, Compare> map;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_map.find(key) == std_map.end(), map.find(key) == map.end());

  std_map.insert({key, 1});
  map.insert({key, 1});

  ASSERT_EQ(std_map.find(key) == std_map.end(), map.find(key) == map.end());
  ASSERT_EQ(std_map.find(transparent_key) == std_map.end(),
            map.find(transparent_key) == map.end());
}

// template< class K > const_iterator find( const K& x ) const;
TEST(map, find_4) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::map<A, int, Compare> std_map = {{key, 1}};
  const s21::map<A, int, Compare> map = {{key, 1}};

  ASSERT_EQ(std_map.find(key) == std_map.end(), map.find(key) == map.end());
  ASSERT_EQ(std_map.find(transparent_key) == std_map.end(),
            map.find(transparent_key) == map.end());
}

// bool contains( const Key& key ) const;
TEST(map, contains_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  ASSERT_EQ(std_map.contains(1), map.contains(1));

  std_map.insert({1, 1});
  map.insert({1, 1});

  ASSERT_EQ(std_map.contains(1), map.contains(1));
}
TEST(map, contains_2) {
  std::map<A, int, Compare> std_map;
  s21::map<A, int, Compare> map;

  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  ASSERT_EQ(std_map.contains(key), map.contains(key));

  std_map.insert({key, 1});
  map.insert({key, 1});

  ASSERT_EQ(std_map.contains(key), map.contains(key));
  ASSERT_EQ(std_map.contains(transparent_key), map.contains(transparent_key));
}

// template< class K > bool contains( const K& x ) const;
TEST(map, contains_3) {
  auto key = A(1, "1");
  auto transparent_key = std::string("1");

  const std::map<A, int, Compare> std_map = {{key, 1}};
  const s21::map<A, int, Compare> map = {{key, 1}};

  ASSERT_EQ(std_map.contains(key), map.contains(key));
  ASSERT_EQ(std_map.contains(transparent_key), map.contains(transparent_key));
}

// std::pair<iterator, iterator> equal_range( const Key& key );
TEST(map, equal_range_1) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto [std_range_first, std_range_last] = std_map.equal_range(2);
  auto [range_first, range_last] = map.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_map.find(2));
  ASSERT_TRUE(*range_first == *map.find(2));

  ASSERT_TRUE(*std_range_last == *std_map.find(3));
  ASSERT_TRUE(*range_last == *map.find(3));
}
TEST(map, equal_range_2) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto [std_range_first, std_range_last] = std_map.equal_range(3);
  auto [range_first, range_last] = map.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_map.find(3));
  ASSERT_TRUE(*range_first == *map.find(3));

  ASSERT_TRUE(std_range_last == std_map.end());
  ASSERT_TRUE(range_last == map.end());
}

// std::pair<const_iterator, const_iterator> equal_range( const Key& key )
// const;
TEST(map, equal_range_3) {
  const std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  const s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto [std_range_first, std_range_last] = std_map.equal_range(2);
  auto [range_first, range_last] = map.equal_range(2);

  ASSERT_TRUE(*std_range_first == *std_map.find(2));
  ASSERT_TRUE(*range_first == *map.find(2));

  ASSERT_TRUE(*std_range_last == *std_map.find(3));
  ASSERT_TRUE(*range_last == *map.find(3));
}
TEST(map, equal_range_4) {
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

  auto [std_range_first, std_range_last] = std_map.equal_range(3);
  auto [range_first, range_last] = map.equal_range(3);

  ASSERT_TRUE(*std_range_first == *std_map.find(3));
  ASSERT_TRUE(*range_first == *map.find(3));

  ASSERT_TRUE(std_range_last == std_map.end());
  ASSERT_TRUE(range_last == map.end());
}

// template< class K >
// std::pair<iterator, iterator> equal_range( const K& x );
TEST(map, equal_range_5) {
  std::map<A, int, Compare> std_map = {
      {A(1, "1"), 1}, {A(2, "2"), 2}, {A(3, "3"), 3}};
  s21::map<A, int, Compare> map = {
      {A(1, "1"), 1}, {A(2, "2"), 2}, {A(3, "3"), 3}};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_map.equal_range(key2);
  auto [range_first, range_last] = map.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_map.find(key2));
  ASSERT_TRUE(*range_first == *map.find(key2));

  ASSERT_TRUE(*std_range_last == *std_map.find(key3));
  ASSERT_TRUE(*range_last == *map.find(key3));
}

// template< class K >
// std::pair<const_iterator, const_iterator> equal_range( const K& x ) const;
TEST(map, equal_range_6) {
  const std::map<A, int, Compare> std_map = {
      {A(1, "1"), 1}, {A(2, "2"), 2}, {A(3, "3"), 3}};
  const s21::map<A, int, Compare> map = {
      {A(1, "1"), 1}, {A(2, "2"), 2}, {A(3, "3"), 3}};

  auto key2 = std::string("2");
  auto key3 = std::string("3");

  auto [std_range_first, std_range_last] = std_map.equal_range(key2);
  auto [range_first, range_last] = map.equal_range(key2);

  ASSERT_TRUE(*std_range_first == *std_map.find(key2));
  ASSERT_TRUE(*range_first == *map.find(key2));

  ASSERT_TRUE(*std_range_last == *std_map.find(key3));
  ASSERT_TRUE(*range_last == *map.find(key3));
}

// iterator lower_bound( const Key& key );
TEST(map, lower_bound_1) {
  std::map<int, int> std_map = {{10, 10}, {20, 20}, {30, 30}};
  s21::map<int, int> map = {{10, 10}, {20, 20}, {30, 30}};

  {
    auto std_it = std_map.lower_bound(10);
    auto it = map.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_map.find(10));
    ASSERT_TRUE(*it == *map.find(10));
  }
  {
    auto std_it = std_map.lower_bound(15);
    auto it = map.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.lower_bound(25);
    auto it = map.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_map.find(30));
    ASSERT_TRUE(*it == *map.find(30));
  }
  {
    auto std_it = std_map.lower_bound(35);
    auto it = map.lower_bound(35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// const_iterator lower_bound( const Key& key ) const;
TEST(map, lower_bound_2) {
  const std::map<int, int> std_map = {{10, 10}, {20, 20}, {30, 30}};
  const s21::map<int, int> map = {{10, 10}, {20, 20}, {30, 30}};

  {
    auto std_it = std_map.lower_bound(10);
    auto it = map.lower_bound(10);

    ASSERT_TRUE(*std_it == *std_map.find(10));
    ASSERT_TRUE(*it == *map.find(10));
  }
  {
    auto std_it = std_map.lower_bound(15);
    auto it = map.lower_bound(15);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.lower_bound(25);
    auto it = map.lower_bound(25);

    ASSERT_TRUE(*std_it == *std_map.find(30));
    ASSERT_TRUE(*it == *map.find(30));
  }
  {
    auto std_it = std_map.lower_bound(35);
    auto it = map.lower_bound(35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// template< class K >
// iterator lower_bound( const K& x );
TEST(map, lower_bound_3) {
  std::map<A, int, Compare> std_map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};
  s21::map<A, int, Compare> map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_map.lower_bound(key10);
    auto it = map.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_map.find(key10));
    ASSERT_TRUE(*it == *map.find(key10));
  }
  {
    auto std_it = std_map.lower_bound(key15);
    auto it = map.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.lower_bound(key25);
    auto it = map.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_map.find(key30));
    ASSERT_TRUE(*it == *map.find(key30));
  }
  {
    auto std_it = std_map.lower_bound(key35);
    auto it = map.lower_bound(key35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// template< class K >
// const_iterator lower_bound( const K& x ) const;
TEST(map, lower_bound_4) {
  const std::map<A, int, Compare> std_map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};
  const s21::map<A, int, Compare> map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_map.lower_bound(key10);
    auto it = map.lower_bound(key10);

    ASSERT_TRUE(*std_it == *std_map.find(key10));
    ASSERT_TRUE(*it == *map.find(key10));
  }
  {
    auto std_it = std_map.lower_bound(key15);
    auto it = map.lower_bound(key15);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.lower_bound(key25);
    auto it = map.lower_bound(key25);

    ASSERT_TRUE(*std_it == *std_map.find(key30));
    ASSERT_TRUE(*it == *map.find(key30));
  }
  {
    auto std_it = std_map.lower_bound(key35);
    auto it = map.lower_bound(key35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// iterator upper_bound( const Key& key );
TEST(map, upper_bound_1) {
  std::map<int, int> std_map = {{10, 10}, {20, 20}, {30, 30}};
  s21::map<int, int> map = {{10, 10}, {20, 20}, {30, 30}};

  {
    auto std_it = std_map.upper_bound(10);
    auto it = map.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.upper_bound(15);
    auto it = map.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.upper_bound(25);
    auto it = map.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_map.find(30));
    ASSERT_TRUE(*it == *map.find(30));
  }
  {
    auto std_it = std_map.upper_bound(35);
    auto it = map.upper_bound(35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// const_iterator upper_bound( const Key& key ) const;
TEST(map, upper_bound_2) {
  const std::map<int, int> std_map = {{10, 10}, {20, 20}, {30, 30}};
  const s21::map<int, int> map = {{10, 10}, {20, 20}, {30, 30}};

  {
    auto std_it = std_map.upper_bound(10);
    auto it = map.upper_bound(10);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.upper_bound(15);
    auto it = map.upper_bound(15);

    ASSERT_TRUE(*std_it == *std_map.find(20));
    ASSERT_TRUE(*it == *map.find(20));
  }
  {
    auto std_it = std_map.upper_bound(25);
    auto it = map.upper_bound(25);

    ASSERT_TRUE(*std_it == *std_map.find(30));
    ASSERT_TRUE(*it == *map.find(30));
  }
  {
    auto std_it = std_map.upper_bound(35);
    auto it = map.upper_bound(35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// template< class K >
// iterator upper_bound( const K& x );
TEST(map, upper_bound_3) {
  std::map<A, int, Compare> std_map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};
  s21::map<A, int, Compare> map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_map.upper_bound(key10);
    auto it = map.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.upper_bound(key15);
    auto it = map.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.upper_bound(key25);
    auto it = map.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_map.find(key30));
    ASSERT_TRUE(*it == *map.find(key30));
  }
  {
    auto std_it = std_map.upper_bound(key35);
    auto it = map.upper_bound(key35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}

// template< class K >
// const_iterator upper_bound( const K& x ) const;
TEST(map, upper_bound_4) {
  const std::map<A, int, Compare> std_map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};
  const s21::map<A, int, Compare> map = {
      {A(10, "10"), 10}, {A(20, "20"), 20}, {A(30, "30"), 30}};

  auto key10 = std::string("10");
  auto key15 = std::string("15");
  auto key20 = std::string("20");
  auto key25 = std::string("25");
  auto key30 = std::string("30");
  auto key35 = std::string("35");

  {
    auto std_it = std_map.upper_bound(key10);
    auto it = map.upper_bound(key10);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.upper_bound(key15);
    auto it = map.upper_bound(key15);

    ASSERT_TRUE(*std_it == *std_map.find(key20));
    ASSERT_TRUE(*it == *map.find(key20));
  }
  {
    auto std_it = std_map.upper_bound(key25);
    auto it = map.upper_bound(key25);

    ASSERT_TRUE(*std_it == *std_map.find(key30));
    ASSERT_TRUE(*it == *map.find(key30));
  }
  {
    auto std_it = std_map.upper_bound(key35);
    auto it = map.upper_bound(key35);

    ASSERT_TRUE(std_it == std_map.end());
    ASSERT_TRUE(it == map.end());
  }
}
