#pragma once

#include <rb_tree/rb_tree.h>

namespace vr {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
requires is_compare<Compare, Key> && is_allocator<Allocator, Key>
class set;

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
requires is_compare<Compare, Key> && is_allocator<Allocator, Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
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
      return p;
    }
  };

  using tree_type = vr::Tree<key_type, value_type, key_of_value, key_compare,
                              allocator_type, false>;
  using iterator = tree_type::iterator;
  using const_iterator = tree_type::const_iterator;
  using reverse_iterator = tree_type::reverse_iterator;
  using const_reverse_iterator = tree_type::const_reverse_iterator;
  using node_type = tree_type::node_handle_type;
  using insert_return_type = tree_type::insert_return_type;

  tree_type tree;

  multiset()
      : tree() {
  }
  explicit multiset(const Compare& comp, const Allocator& alloc = Allocator())
      : tree(comp, alloc) {
  }
  explicit multiset(const Allocator& alloc)
      : tree(alloc) {
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      multiset(InputIt first, InputIt last, const Compare& comp = Compare(),
               const Allocator& alloc = Allocator())
      : tree(first, last, comp, alloc) {
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      multiset(InputIt first, InputIt last, const Allocator& alloc)
      : tree(first, last, alloc) {
  }

  multiset(std::initializer_list<value_type> init,
           const Compare& comp = Compare(),
           const Allocator& alloc = Allocator())
      : tree(init, comp, alloc) {
  }
  multiset(std::initializer_list<value_type> init, const Allocator& alloc)
      : tree(init, alloc) {
  }

  multiset(const multiset& other)
      : tree(other.tree) {
  }
  multiset(const multiset& other, const Allocator& alloc)
      : tree(other.tree, alloc){};

  multiset(multiset&& other) noexcept
      : tree(std::move(other.tree)) {
  }
  multiset(multiset&& other, const Allocator& alloc) noexcept
      : tree(std::move(other.tree), alloc) {
  }

  ~multiset() {
  }

  multiset& operator=(const multiset& other) {
    tree = other.tree;
    return *this;
  }
  multiset& operator=(multiset&& other) noexcept(
      std::allocator_traits<allocator_type>::is_always_equal::value&&
          std::is_nothrow_move_assignable<key_compare>::value) {
    tree = std::move(other.tree);
    return *this;
  }
  multiset& operator=(std::initializer_list<value_type> init_list) {
    tree = init_list;
    return *this;
  }

  allocator_type get_allocator() const noexcept {
    return tree.get_allocator();
  };

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

  iterator insert(const value_type& value) {
    return tree.insert(value).first;
  }

  iterator insert(value_type&& value) {
    return tree.insert(std::move(value)).first;
  }

  iterator insert(const_iterator pos, const value_type& value) {
    return tree.insert(pos, value).first;
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

  iterator insert(node_type&& nh) {
    if (nh.empty()) {
      return end();
    }

    // TODO: check allocator

    auto [it, is_inserted] = tree.insert(nh.value());

    if (is_inserted) {
      nh.node_ = nullptr;
    }

    return it;
  }

  iterator insert(const_iterator pos, node_type&& nh) {
    if (nh.empty()) {
      return end();
    }

    // TODO: check allocator

    auto [it, _] = tree.insert(pos, nh.value());

    return it;
  }

  // TODO: remove this
  template <typename... Args>
  requires(std::convertible_to<value_type, Args>&&...)
      std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree.insert_many(std::forward<Args>(args)...);
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

  void swap(multiset& other) noexcept(
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
  void merge(set<Key, OtherCompare, Allocator>& source) {
    tree.merge(source.tree);
  }

  template <typename OtherCompare>
  void merge(set<Key, OtherCompare, Allocator>&& source) {
    tree.merge(std::move(source.tree));
  }

  template <typename OtherCompare>
  void merge(multiset<Key, OtherCompare, Allocator>& source) {
    tree.merge(source.tree);
  }

  template <typename OtherCompare>
  void merge(multiset<Key, OtherCompare, Allocator>&& source) {
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

  bool contains(const Key& key) const {
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
