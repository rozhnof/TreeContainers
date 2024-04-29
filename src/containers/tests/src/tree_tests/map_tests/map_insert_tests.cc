#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "../insert_erase_data.h"
#include "assert_map.h"

// std::pair<iterator, bool> insert( const value_type& value );
TEST(map, insert_1_0) {
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;
    int i = 0;

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      auto [it_std, is_inserted_std] = std_map.insert(std_pair);
      auto [it_s21, is_inserted_s21] = map.insert(pair);

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_1_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      auto [it_std, is_inserted_std] = std_map.insert(std_pair);
      auto [it_s21, is_inserted_s21] = map.insert(pair);

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}

// template< class P >
// std::pair<iterator, bool> insert( P&& value );
TEST(map, insert_2_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (const auto& value : insert_seq) {
      auto [it_std, is_inserted_std] = std_map.insert(std::pair{value, i});
      auto [it_s21, is_inserted_s21] = map.insert(std::pair{value, i});

      ++i;

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_2_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto [it_std, is_inserted_std] = std_map.insert(std::pair{value, i});
      auto [it_s21, is_inserted_s21] = map.insert(std::pair{value, i});

      ++i;

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}

// std::pair<iterator, bool> insert( value_type&& value );
TEST(map, insert_3_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      auto [it_std, is_inserted_std] = std_map.insert(std::move(std_pair));
      auto [it_s21, is_inserted_s21] = map.insert(std::move(pair));

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_3_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      auto [it_std, is_inserted_std] = std_map.insert(std::move(std_pair));
      auto [it_s21, is_inserted_s21] = map.insert(std::move(pair));

      ASSERT_EQ(is_inserted_std, is_inserted_s21);
      ASSERT_EQ(*it_std, *it_s21);

      assert_map(std_map, map);
    }
  }
}

// iterator insert( const_iterator pos, const value_type& value );
TEST(map, insert_4_0) {
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      std_it = std_map.insert(std_map.end(), std_pair);
      it = map.insert(map.end(), pair);

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_4_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      std_it = std_map.insert(std_map.end(), std_pair);
      it = map.insert(map.end(), pair);

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}

// template< class P >
// iterator insert( const_iterator pos, P&& value );
TEST(map, insert_5_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      std_it = std_map.insert(std_map.end(), std::pair{value, i});
      it = map.insert(map.end(), std::pair{value, i});

      ++i;

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_5_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      std_it = std_map.insert(std_map.end(), std::pair{value, i});
      it = map.insert(map.end(), std::pair{value, i});

      ++i;

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}

// iterator insert( const_iterator pos, value_type&& value );
TEST(map, insert_6_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      std_it = std_map.insert(std_map.end(), std::move(std_pair));
      it = map.insert(map.end(), std::move(pair));

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}
TEST(map, insert_6_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_map.end();
    auto it = map.end();

    for (const auto& value : insert_seq) {
      auto std_pair = std::make_pair(value, i);
      auto pair = std::make_pair(value, i);

      ++i;

      std_it = std_map.insert(std_map.end(), std::move(std_pair));
      it = map.insert(map.end(), std::move(pair));

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}

// template< class InputIt >
// void insert( InputIt first, InputIt last );
TEST(map, insert_7_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::vector<std::pair<int, int>> ilist;

    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (const auto& val : insert_seq) {
      ilist.push_back({val, i});
    }

    ++i;

    std_map.insert(ilist.begin(), ilist.end());
    map.insert(ilist.begin(), ilist.end());

    assert_map(std_map, map);
  }
}
TEST(map, insert_7_1) {
  std::vector<std::pair<int, int>> ilist;

  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& val : insert_seq) {
      ilist.push_back({val, i});
    }

    ++i;

    std_map.insert(ilist.begin(), ilist.end());
    map.insert(ilist.begin(), ilist.end());

    assert_map(std_map, map);
  }
}

// void insert( std::initializer_list<value_type> ilist );
TEST(map, insert_8_0) {
  using ilist = std::initializer_list<std::pair<const int, int>>;

  ilist insert_seq_1 = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}};
  ilist insert_seq_2 = {{5, 0}, {3, 0}, {7, 0}, {4, 0},
                        {6, 0}, {2, 0}, {8, 0}, {1, 0}};
  ilist insert_seq_3 = {{3, 0}, {2, 0}, {5, 0}, {2, 0}, {7, 0},
                        {2, 0}, {4, 0}, {2, 0}, {6, 0}};
  ilist insert_seq_4 = {{7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}};
  ilist insert_seq_5 = {{1, 0}, {3, 0}, {2, 0}, {4, 0}, {3, 0},
                        {5, 0}, {4, 0}, {6, 0}, {5, 0}, {7, 0}};
  ilist insert_seq_6 = {{1, 0}, {2, 0}, {3, 0},  {4, 0}, {5, 0}, {6, 0}, {7, 0},
                        {8, 0}, {9, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0},
                        {5, 0}, {4, 0}, {3, 0},  {2, 0}, {1, 0}};
  ilist insert_seq_7 = {{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}};

  for (auto& insert_seq :
       {insert_seq_1, insert_seq_2, insert_seq_3, insert_seq_4, insert_seq_5,
        insert_seq_6, insert_seq_7}) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    std_map.insert(insert_seq);
    map.insert(insert_seq);

    assert_map(std_map, map);
  }
}
TEST(map, insert_8_1) {
  using ilist = std::initializer_list<std::pair<const int, int>>;

  ilist insert_seq_1 = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}};
  ilist insert_seq_2 = {{5, 0}, {3, 0}, {7, 0}, {4, 0},
                        {6, 0}, {2, 0}, {8, 0}, {1, 0}};
  ilist insert_seq_3 = {{3, 0}, {2, 0}, {5, 0}, {2, 0}, {7, 0},
                        {2, 0}, {4, 0}, {2, 0}, {6, 0}};
  ilist insert_seq_4 = {{7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}};
  ilist insert_seq_5 = {{1, 0}, {3, 0}, {2, 0}, {4, 0}, {3, 0},
                        {5, 0}, {4, 0}, {6, 0}, {5, 0}, {7, 0}};
  ilist insert_seq_6 = {{1, 0}, {2, 0}, {3, 0},  {4, 0}, {5, 0}, {6, 0}, {7, 0},
                        {8, 0}, {9, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0},
                        {5, 0}, {4, 0}, {3, 0},  {2, 0}, {1, 0}};
  ilist insert_seq_7 = {{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}};

  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& insert_seq :
       {insert_seq_1, insert_seq_2, insert_seq_3, insert_seq_4, insert_seq_5,
        insert_seq_6, insert_seq_7}) {
    std_map.insert(insert_seq);
    map.insert(insert_seq);

    assert_map(std_map, map);
  }
}

// insert_return_type insert( node_type&& nh );
TEST(map, insert_9_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (const auto& value : insert_seq) {
      std_map.insert({1, 0});
      map.insert({1, 0});

      auto std_nh = std::move(std_map.extract(1));
      auto nh = std::move(map.extract(1));

      std_nh.key() = value;
      std_nh.mapped() = i;

      nh.key() = value;
      nh.mapped() = i;

      auto std_irt = std_map.insert(std::move(std_nh));
      auto irt = map.insert(std::move(nh));

      ASSERT_EQ(std_irt.inserted, irt.inserted);
      ASSERT_EQ(*std_irt.position, *irt.position);
      ASSERT_EQ(std_irt.node.empty(), irt.node.empty());

      assert_map(std_map, map);
    }
  }
}

TEST(map, insert_9_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    for (const auto& value : insert_seq) {
      std_map.insert({1, 0});
      map.insert({1, 0});

      auto std_nh = std::move(std_map.extract(1));
      auto nh = std::move(map.extract(1));

      std_nh.key() = value;
      std_nh.mapped() = i;

      nh.key() = value;
      nh.mapped() = i;

      auto std_irt = std_map.insert(std::move(std_nh));
      auto irt = map.insert(std::move(nh));

      ASSERT_EQ(std_irt.inserted, irt.inserted);
      ASSERT_EQ(*std_irt.position, *irt.position);
      ASSERT_EQ(std_irt.node.empty(), irt.node.empty());

      assert_map(std_map, map);
    }
  }
}

// iterator insert( const_iterator pos, node_type&& nh );
TEST(map, insert_10_0) {
  int i = 0;
  for (const auto& insert_seq : insert_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    auto std_it = std_map.begin();
    auto it = map.begin();

    for (const auto& value : insert_seq) {
      std_map.insert({1, 0});
      map.insert({1, 0});

      auto std_nh = std::move(std_map.extract(1));
      auto nh = std::move(map.extract(1));

      std_nh.key() = value;
      std_nh.mapped() = i;

      nh.key() = value;
      nh.mapped() = i;

      std_it = std_map.insert(std_map.end(), std::move(std_nh));
      it = map.insert(map.end(), std::move(nh));

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);

      ++i;
    }
  }
}
TEST(map, insert_10_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;
  int i = 0;

  for (const auto& insert_seq : insert_sequences) {
    auto std_it = std_map.begin();
    auto it = map.begin();

    for (const auto& value : insert_seq) {
      std_map.insert({1, 0});
      map.insert({1, 0});

      auto std_nh = std::move(std_map.extract(1));
      auto nh = std::move(map.extract(1));

      std_nh.key() = value;
      std_nh.mapped() = i;

      nh.key() = value;
      nh.mapped() = i;

      std_it = std_map.insert(std_map.end(), std::move(std_nh));
      it = map.insert(map.end(), std::move(nh));

      ASSERT_EQ(*std_it, *it);

      assert_map(std_map, map);
    }
  }
}