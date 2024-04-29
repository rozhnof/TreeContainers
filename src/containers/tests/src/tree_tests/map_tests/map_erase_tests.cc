#include <gtest/gtest.h>
#include <map.h>

#include <map>

#include "../insert_erase_data.h"
#include "assert_map.h"

// iterator erase( iterator pos );
TEST(map, erase_1_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      std_map.erase(std_map.find(val));
      map.erase(map.find(val));

      assert_map(std_map, map);
    }
  }
}
TEST(map, erase_1_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      std_map.erase(std_map.find(val));
      map.erase(map.find(val));

      assert_map(std_map, map);
    }
  }
}

// iterator erase( const_iterator pos );
TEST(map, erase_2_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      decltype(std_map)::const_iterator std_it = std_map.find(val);
      decltype(map)::const_iterator it = map.find(val);

      std_map.erase(std_it);
      map.erase(it);

      assert_map(std_map, map);
    }
  }
}
TEST(map, erase_2_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      decltype(std_map)::const_iterator std_it = std_map.find(val);
      decltype(map)::const_iterator it = map.find(val);

      std_map.erase(std_it);
      map.erase(it);

      assert_map(std_map, map);
    }
  }
}

// iterator erase( const_iterator first, const_iterator last );
TEST(map, erase_3_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    decltype(std_map)::iterator std_begin = std_map.begin();
    decltype(map)::iterator begin = map.begin();

    decltype(std_map)::iterator std_end = std_map.end();
    decltype(map)::iterator end = map.end();

    std_map.erase(std_begin, std_end);
    map.erase(begin, end);

    assert_map(std_map, map);
  }
}
TEST(map, erase_3_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    decltype(std_map)::iterator std_begin = std_map.begin();
    decltype(map)::iterator begin = map.begin();

    decltype(std_map)::iterator std_end = std_map.end();
    decltype(map)::iterator end = map.end();

    std_map.erase(std_begin, std_end);
    map.erase(begin, end);

    assert_map(std_map, map);
  }
}
TEST(map, erase_3_2) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    decltype(std_map)::const_iterator std_begin = std_map.begin();
    decltype(map)::const_iterator begin = map.begin();

    decltype(std_map)::const_iterator std_end = std_map.end();
    decltype(map)::const_iterator end = map.end();

    std_map.erase(std_begin, std_end);
    map.erase(begin, end);

    assert_map(std_map, map);
  }
}
TEST(map, erase_3_3) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    decltype(std_map)::const_iterator std_begin = std_map.begin();
    decltype(map)::const_iterator begin = map.begin();

    decltype(std_map)::const_iterator std_end = std_map.end();
    decltype(map)::const_iterator end = map.end();

    std_map.erase(std_begin, std_end);
    map.erase(begin, end);

    assert_map(std_map, map);
  }
}

// size_type erase( const Key& key );
TEST(map, erase_4_0) {
  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    std::map<int, int> std_map;
    s21::map<int, int> map;

    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      std_map.erase(val);
      map.erase(val);

      assert_map(std_map, map);
    }
  }
}

TEST(map, erase_4_1) {
  std::map<int, int> std_map;
  s21::map<int, int> map;

  for (auto& [insert_seq, erase_seq] : erase_sequences) {
    for (auto val : insert_seq) {
      std_map.insert({val, 0});
      map.insert({val, 0});

      assert_map(std_map, map);
    }

    for (auto val : erase_seq) {
      std_map.erase(val);
      map.erase(val);

      assert_map(std_map, map);
    }
  }
}