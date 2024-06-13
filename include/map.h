#pragma once

#include <rb_tree/rb_tree.h>

namespace vr {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
requires is_compare<Compare, Key> &&
    is_allocator<Allocator, std::pair<const Key, T>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  class value_compare {
   protected:
    Compare comp;
    explicit value_compare(const Compare& comp)
        : comp(comp) {
    }
    bool operator()(const value_type& lhs, const value_type& rhs) const {
      return comp(lhs.first, rhs.first);
    }
  };

  struct key_of_value {
    const key_type& operator()(const value_type& p) const {
      return p.first;
    }
  };

  using tree_type = vr::Tree<key_type, value_type, key_of_value, key_compare,
                              allocator_type, true>;
  using iterator = tree_type::iterator;
  using const_iterator = tree_type::const_iterator;
  using reverse_iterator = tree_type::reverse_iterator;
  using const_reverse_iterator = tree_type::const_reverse_iterator;
  using node_type = tree_type::node_handle_type;
  using insert_return_type = tree_type::insert_return_type;

  tree_type tree;

  map()
      : tree() {
  }
  explicit map(const Compare& comp, const Allocator& alloc = Allocator())
      : tree(comp, alloc) {
  }
  explicit map(const Allocator& alloc)
      : tree(alloc) {
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      map(InputIt first, InputIt last, const Compare& comp = Compare(),
          const Allocator& alloc = Allocator())
      : tree(first, last, comp, alloc) {
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      map(InputIt first, InputIt last, const Allocator& alloc)
      : tree(first, last, alloc) {
  }

  map(std::initializer_list<value_type> init, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : tree(init, comp, alloc) {
  }
  map(std::initializer_list<value_type> init, const Allocator& alloc)
      : tree(init, alloc) {
  }

  map(const map& other)
      : tree(other.tree) {
  }
  map(const map& other, const Allocator& alloc)
      : tree(other.tree, alloc){};

  map(map&& other) noexcept
      : tree(std::move(other.tree)) {
  }
  map(map&& other, const Allocator& alloc) noexcept
      : tree(std::move(other.tree), alloc) {
  }

  ~map() {
  }

  map& operator=(const map& other) {
    tree = other.tree;
    return *this;
  }
  map& operator=(map&& other) noexcept(
      std::allocator_traits<allocator_type>::is_always_equal::value&&
          std::is_nothrow_move_assignable<key_compare>::value) {
    tree = std::move(other.tree);
    return *this;
  }
  map& operator=(std::initializer_list<value_type> init_list) {
    tree = init_list;
    return *this;
  }

  allocator_type get_allocator() const noexcept {
    return tree.get_allocator();
  };

  T& at(const Key& key) {
    iterator it = find(key);

    if (it == tree.end()) {
      throw std::out_of_range("out of range");
    }

    return (*it).second;
  }

  const T& at(const Key& key) const {
    const_iterator it = find(key);

    if (it == tree.end()) {
      throw std::out_of_range("out of range");
    }

    return (*it).second;
  }

  T& operator[](const Key& key) {
    iterator it = find(key);

    if (it == tree.end()) {
      it = emplace(key, T()).first;
    }

    return (*it).second;
  }

  T& operator[](Key&& key) {
    iterator it = find(key);

    if (it == tree.end()) {
      it = emplace(std::move(key), T()).first;
    }

    return (*it).second;
  }

  iterator begin() noexcept {
    return tree.begin();
  }
  const_iterator begin() const noexcept {
    return tree.begin();
  }
  const_iterator cbegin() const noexcept {
    return tree.cbegin();
  }

  iterator end() noexcept {
    return tree.end();
  }
  const_iterator end() const noexcept {
    return tree.end();
  }
  const_iterator cend() const noexcept {
    return tree.cend();
  }

  reverse_iterator rbegin() noexcept {
    return tree.rbegin();
  }
  const_reverse_iterator rbegin() const noexcept {
    return tree.rbegin();
  }
  const_reverse_iterator crbegin() const noexcept {
    return tree.crbegin();
  }

  reverse_iterator rend() noexcept {
    return tree.rend();
  }
  const_reverse_iterator rend() const noexcept {
    return tree.rend();
  }
  const_reverse_iterator crend() const noexcept {
    return tree.crend();
  }

  [[nodiscard]] bool empty() const noexcept {
    return tree.empty();
  }
  size_type size() const noexcept {
    return tree.size();
  }
  size_type max_size() const noexcept {
    return tree.max_size();
  }

  void clear() noexcept {
    tree.clear();
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree.insert(value);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return emplace(key, obj);
  }

  template <class P>
  requires(std::convertible_to<value_type, P>) std::pair<iterator, bool> insert(
      P&& value) {
    return tree.insert(std::forward<P>(value));
  }

  std::pair<iterator, bool> insert(value_type&& value) {
    return tree.insert(std::move(value));
  }

  iterator insert(const_iterator pos, const value_type& value) {
    return tree.insert(pos, value);
  }

  template <typename P>
  requires(std::convertible_to<value_type, P>) iterator
      insert(const_iterator pos, P&& value) {
    return tree.insert(pos, std::forward<P>(value)).first;
  }

  iterator insert(const_iterator pos, value_type&& value) {
    return tree.insert(pos, std::move(value)).first;
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>) void insert(InputIt first,
                                                                 InputIt last) {
    tree.insert(first, last);
  }

  void insert(std::initializer_list<value_type> ilist) {
    tree.insert(ilist);
  }

  insert_return_type insert(node_type&& nh) {
    insert_return_type result;

    if (nh.empty()) {
      result.position = end();
      return result;
    }

    // TODO: check allocator

    auto [it, is_inserted] = tree.try_emplace(nh.key(), nh.mapped());
    result.position = it;
    result.inserted = is_inserted;

    if (is_inserted) {
      nh.node_ = nullptr;
    } else {
      result.node = std::move(nh);
    }

    return result;
  }

  iterator insert(const_iterator pos, node_type&& nh) {
    if (nh.empty()) {
      return end();
    }

    // TODO: check allocator

    auto it = tree.try_emplace(pos, nh.key(), nh.mapped());

    return it;
  }

  // TODO: remove this
  template <typename... Args>
  requires(std::convertible_to<value_type, Args>&&...)
      std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree.insert_many(std::forward<Args>(args)...);
  }

  template <typename M>
  std::pair<iterator, bool> insert_or_assign(const Key& key, M&& obj) {
    auto [it, is_inserted] = emplace(key, obj);

    if (!is_inserted) {
      it->second = std::forward<M>(obj);
    }

    return {it, is_inserted};
  }

  template <typename M>
  std::pair<iterator, bool> insert_or_assign(Key&& key, M&& obj) {
    auto [it, is_inserted] = emplace(std::move(key), obj);

    if (!is_inserted) {
      it->second = std::forward<M>(obj);
    }

    return {it, is_inserted};
  }

  template <typename K, typename M>
  std::pair<iterator, bool> insert_or_assign(K&& key, M&& obj) {
    auto [it, is_inserted] = emplace(std::forward<K>(key), obj);

    if (!is_inserted) {
      it->second = std::forward<M>(obj);
    }

    return {it, is_inserted};
  }

  template <typename M>
  iterator insert_or_assign(const_iterator hint, const Key& key, M&& obj) {
    auto it = emplace_hint(hint, key, obj);

    if (!it->second != obj) {
      it->second = std::forward<M>(obj);
    }

    return it;
  }

  template <typename M>
  iterator insert_or_assign(const_iterator hint, Key&& key, M&& obj) {
    auto it = emplace_hint(hint, std::move(key), obj);

    if (!it->second != obj) {
      it->second = std::forward<M>(obj);
    }

    return it;
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Args...>)
      std::pair<iterator, bool> emplace(Args&&... args) {
    return tree.emplace(std::forward<Args>(args)...);
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Args...>) iterator
      emplace_hint(const_iterator hint, Args&&... args) {
    return tree.emplace_hint(hint, std::forward<Args>(args)...);
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Key, Args...>)
      std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args) {
    return tree.try_emplace(k, std::forward<Args>(args)...);
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Key, Args...>)
      std::pair<iterator, bool> try_emplace(Key&& k, Args&&... args) {
    return tree.try_emplace(std::move(k), std::forward<Args>(args)...);
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Key, Args...>) iterator
      try_emplace(const_iterator hint, const Key& k, Args&&... args) {
    return tree.try_emplace(hint, k, std::forward<Args>(args)...);
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Key, Args...>) iterator
      try_emplace(const_iterator hint, Key&& k, Args&&... args) {
    return tree.try_emplace(hint, std::move(k), std::forward<Args>(args)...);
  }

  iterator erase(iterator pos) {
    return tree.erase(pos);
  }
  iterator erase(const_iterator pos) {
    return tree.erase(pos);
  }
  iterator erase(const_iterator first, const_iterator last) {
    return tree.erase(first, last);
  }
  size_type erase(const Key& key) {
    return tree.erase(key);
  }

  void swap(map& other) noexcept(
      std::allocator_traits<Allocator>::is_always_equal::value&&
          std::is_nothrow_swappable<Compare>::value) {
    tree.swap(other.tree);
  }

  node_type extract(const_iterator position) {
    return tree.extract(position);
  }
  node_type extract(const Key& k) {
    return tree.extract(k);
  }

  template <typename OtherCompare>
  void merge(map<Key, T, OtherCompare, Allocator>& source) {
    tree.merge(source.tree);
  }

  template <typename OtherCompare>
  void merge(map<Key, T, OtherCompare, Allocator>&& source) {
    tree.merge(std::move(source.tree));
  }

  size_type count(const Key& key) const {
    return tree.count(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) size_type count(const K& x)
  const {
    return tree.count(x);
  }

  iterator find(const Key& key) {
    return tree.find(key);
  }
  const_iterator find(const Key& key) const {
    return tree.find(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) iterator find(const K& x) {
    return tree.find(x);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) const_iterator find(const K& x)
  const {
    return tree.find(x);
  }

  bool contains(const T& key) const {
    return tree.contains(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) bool contains(const K& key) const {
    return tree.contains(key);
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return tree.equal_range(key);
  }
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return tree.equal_range(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>)
      std::pair<iterator, iterator> equal_range(const K& x) {
    return tree.equal_range(x);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>)
      std::pair<const_iterator, const_iterator> equal_range(const K& x)
  const {
    return tree.equal_range(x);
  }

  iterator lower_bound(const Key& key) {
    return tree.lower_bound(key);
  }
  const_iterator lower_bound(const Key& key) const {
    return tree.lower_bound(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) iterator lower_bound(const K& x) {
    return tree.lower_bound(x);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) const_iterator
      lower_bound(const K& x)
  const {
    return tree.lower_bound(x);
  }

  iterator upper_bound(const Key& key) {
    return tree.upper_bound(key);
  }
  const_iterator upper_bound(const Key& key) const {
    return tree.upper_bound(key);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) iterator upper_bound(const K& x) {
    return tree.upper_bound(x);
  }

  template <typename K>
  requires(is_transparent<K, Key, Compare>) const_iterator
      upper_bound(const K& x)
  const {
    return tree.upper_bound(x);
  }

  key_compare key_comp() const {
    return tree.key_comp();
  }
  value_compare value_comp() const {
    return value_compare();
  }
};

}  // namespace vr
