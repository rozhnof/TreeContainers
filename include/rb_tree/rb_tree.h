#pragma once

#include <rb_tree/iterator.h>
#include <rb_tree/node.h>
#include <rb_tree/node_handle.h>

#include <concepts>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>

namespace vr {

template <typename KeyOfValue, typename Key, typename Value>
concept is_key_of_value = requires {
  requires(std::invocable<KeyOfValue, Value>);
};

template <typename Compare, typename Key>
concept is_compare = requires {
  requires(std::invocable<Compare, Key, Key>);
};

template <typename Allocator, typename Value>
concept is_allocator = requires(Allocator a) {
  requires std::same_as<typename Allocator::value_type, Value>;
  { a.allocate(std::declval<std::size_t>()) } -> std::same_as<Value*>;
  {
    a.deallocate(std::declval<Value*>(), std::declval<std::size_t>())
    } -> std::same_as<void>;
};

template <typename T, typename Key, typename Compare>
concept is_transparent = requires {
  typename Compare::is_transparent;
  requires(std::invocable<Compare, T, Key>);
};

template <typename Iter, typename Value>
concept is_correct_iterator = requires {
  requires std::input_iterator<Iter> &&
      (std::convertible_to<std::iter_value_t<Iter>, Value> ||
       std::constructible_from<Value, std::iter_value_t<Iter>>);
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator, bool is_unique>
requires is_key_of_value<KeyOfValue, Key, Value> && is_compare<Compare, Key> &&
    is_allocator<Allocator, Value>
class Tree {
 public:
  using key_type = Key;
  using value_type = Value;
  using key_of_value = KeyOfValue;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;

  using reference = value_type&;
  using const_reference = const value_type&;

  using node_type = Node<Value>;
  using base_node_type = BaseNode<Value>;

  using node_color = Color;
  using node_child_ptr = node_type::NodeMemberPtr;

  using node_allocator = typename std::allocator_traits<
      Allocator>::template rebind_alloc<node_type>;
  using node_allocator_traits = std::allocator_traits<node_allocator>;

  using iterator = Iterator<Value, false>;
  using const_iterator = Iterator<Value, true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  base_node_type fake_;
  size_type size_ = 0;

  [[no_unique_address]] key_compare comp_;
  [[no_unique_address]] key_of_value key_extractor_ = key_of_value();
  [[no_unique_address]] node_allocator node_alloc_;

  template <typename IteratorType, typename NodeType>
  struct node_insert_return {
    IteratorType position = IteratorType();
    bool inserted = false;
    NodeType node;
  };

  using node_handle_type = NodeHandle<key_type, value_type, node_allocator>;
  using insert_return_type = node_insert_return<
      std::conditional_t<std::is_same_v<key_type, value_type>, const_iterator,
                         iterator>,
      node_handle_type>;

  Tree()
      : Tree(Compare()) {
  }

  explicit Tree(const Compare& comp, const Allocator& alloc = Allocator())
      : fake_(nullptr, node_color::kRed),
        comp_(comp),
        node_alloc_(alloc) {
    clear_fake();
  }

  explicit Tree(const Allocator& alloc)
      : Tree(Compare(), alloc) {
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      Tree(InputIt first, InputIt last, const Compare& comp = Compare(),
           const Allocator& alloc = Allocator())
      : Tree(comp, alloc) {
    insert(first, last);
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>)
      Tree(InputIt first, InputIt last, const Allocator& alloc)
      : Tree(first, last, Compare(), alloc) {
  }

  Tree(std::initializer_list<Value> init, const Compare& comp = Compare(),
       const Allocator& alloc = Allocator())
      : Tree(init.begin(), init.end(), comp, alloc) {
  }

  Tree(std::initializer_list<Value> init, const Allocator& alloc)
      : Tree(init.begin(), init.end(), alloc) {
  }

  Tree(const Tree& other)
      : Tree(other,
             std::allocator_traits<allocator_type>::
                 select_on_container_copy_construction(other.get_allocator())) {
  }
  Tree(const Tree& other, const Allocator& alloc)
      : Tree(other.begin(), other.end(), alloc){};

  Tree(Tree&& other) noexcept {
    clear_fake();
    swap_fields(other);
    node_alloc_ = std::move(other.node_alloc_);
  }

  Tree(Tree&& other, const Allocator& alloc) noexcept {
    clear_fake();
    if (other.get_allocator() == alloc) {
      swap_fields(other);
      node_alloc_ = std::move(other.node_alloc_);
    } else {
      Tree temp(other, alloc);
      swap_fields(temp);
      swap_alloc(temp);
    }
  }

  Tree& operator=(const Tree& other) {
    if (this == &other) {
      return *this;
    }

    clear();

    if constexpr (std::allocator_traits<allocator_type>::
                      propagate_on_container_copy_assignment::value) {
      node_alloc_ = other.node_alloc_;
    }

    insert(other.begin(), other.end());

    return *this;
  }

  Tree& operator=(Tree&& other) noexcept(
      std::allocator_traits<allocator_type>::is_always_equal::value&&
          std::is_nothrow_move_assignable<key_compare>::value) {
    if (this == &other) {
      return *this;
    }

    clear();

    bool is_alloc_copied = false;
    if constexpr (std::allocator_traits<allocator_type>::
                      propagate_on_container_move_assignment::value) {
      auto old_alloc = node_alloc_;
      node_alloc_ = other.node_alloc_;

      if (old_alloc == node_alloc_) {
        fake_ = other.fake_;
        size_ = other.size_;
        get_root()->parent = get_fake();

        other.clear_fake();
        other.size_ = 0;

        is_alloc_copied = true;
      }
    }

    if (!is_alloc_copied) {
      insert(other.begin(), other.end());
      other.clear();
    }

    return *this;
  }

  Tree& operator=(std::initializer_list<value_type> init_list) {
    clear();

    insert(init_list.begin(), init_list.end());

    return *this;
  }

  allocator_type get_allocator() const noexcept {
    return node_alloc_;
  }

  ~Tree() {
    clear(get_root());
  }

  iterator begin() noexcept {
    return iterator(get_leftmost());
  }
  const_iterator begin() const noexcept {
    return const_iterator(get_leftmost());
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(get_leftmost());
  }

  iterator end() noexcept {
    return iterator(get_fake());
  }
  const_iterator end() const noexcept {
    return const_iterator(get_fake());
  }
  const_iterator cend() const noexcept {
    return const_iterator(get_fake());
  }

  reverse_iterator rbegin() noexcept {
    return std::make_reverse_iterator(end());
  }
  const_reverse_iterator rbegin() const noexcept {
    return std::make_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return std::make_reverse_iterator(cend());
  }

  reverse_iterator rend() noexcept {
    return std::make_reverse_iterator(begin());
  }
  const_reverse_iterator rend() const noexcept {
    return std::make_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return std::make_reverse_iterator(cbegin());
  }

  [[nodiscard]] bool empty() const noexcept {
    return size_ == 0;
  }
  size_type size() const noexcept {
    return size_;
  }
  size_type max_size() const noexcept {
    return node_allocator_traits::max_size(node_alloc_);
  }

  void clear() noexcept {
    clear(get_root());
    clear_fake();
    size_ = 0;
  }

  void clear_fake() noexcept {
    set_root(get_fake());
    set_leftmost(get_fake());
    set_rightmost(get_fake());
  }

  // TODO: think about insert through hint insert (excess checks for get
  // position)
  template <typename T>
  requires(std::convertible_to<T, value_type>) std::pair<iterator, bool> insert(
      T&& data) {
    return insert(end(), std::forward<T>(data));
  }

  template <typename T>
  requires(std::convertible_to<T, value_type>) std::pair<iterator, bool> insert(
      const_iterator pos, T&& data) {
    auto new_node =
        constructNode(nullptr, std::forward<T>(data), node_color::kRed);
    return insert(pos, new_node);
  }

  std::pair<iterator, bool> insert(const_iterator pos, node_type* new_node) {
    if (get_root() == get_fake()) {
      createRoot(new_node);
      ++size_;
      return {iterator(get_root()), true};
    }

    // TODO: change return value
    auto [parent, direction] =
        get_insert_hint_position(pos, key_extractor_(new_node->data));

    // TODO: ochen ploho (double search)
    if (parent == nullptr) {
      return {find(key_extractor_(new_node->data)), false};
    }

    if (auto node = parent->*direction; node != nullptr) {
      new_node->parent = parent;
      new_node->color = node_color::kRed;

      new_node->*direction = node;

      parent->*direction = new_node;
      node->parent = new_node;
    } else {
      new_node->parent = parent;
      new_node->color = node_color::kRed;

      if (parent == get_fake()) {
        changeRoot(new_node);
      } else {
        parent->*direction = new_node;
      }
    }

    if (get_leftmost()->left == new_node) {
      set_leftmost(new_node);
    } else if (get_rightmost()->right == new_node) {
      set_rightmost(new_node);
    }

    fixInsert(new_node);

    ++size_;
    return {iterator(new_node), true};
  }

  template <typename InputIt>
  requires(is_correct_iterator<InputIt, value_type>) void insert(InputIt first,
                                                                 InputIt last) {
    iterator first_inserted = end();
    iterator last_inserted = end();

    try {
      first_inserted = insert(*(first++)).first;
      for (; first != last; ++first) {
        last_inserted = insert(*first).first;
      }
    } catch (...) {
      erase(first_inserted, ++last_inserted);
      throw;
    }
  }

  void insert(std::initializer_list<value_type> ilist) {
    insert(ilist.begin(), ilist.end());
  }

  std::pair<node_type*, node_child_ptr> get_insert_position(
      const key_type& key) const {
    node_type* it = get_root();
    node_type* parent = get_fake();
    node_child_ptr child = &node_type::parent;

    while (it != nullptr) {
      if constexpr (is_unique) {
        if (!comp_(key, key_extractor_(it->data)) &&
            !comp_(key_extractor_(it->data), key)) {
          return {nullptr, nullptr};
        }
      }

      child = node_type::get_left_if(comp_(key, key_extractor_(it->data)));
      parent = it;
      it = it->*child;
    }
    return {parent, child};
  }

  std::pair<node_type*, node_child_ptr> get_insert_hint_position(
      const_iterator position, const key_type& key) {
    if (position.ptr_ == get_fake()) {
      if (size() > 0 && comp_(key_extractor_(get_rightmost()->data), key)) {
        return {get_rightmost(), &node_type::right};
      } else {
        return get_insert_position(key);
      }
    }

    iterator pos = position.unconst();
    iterator it = pos;

    if (comp_(key, key_extractor_(pos.ptr_->data))) {
      node_child_ptr direction = &node_type::left;
      node_child_ptr back_direction = base_node_type::get_sibling(direction);

      --it;

      if (pos.ptr_ == direction_most(direction)) {
        return {direction_most(direction), direction};
      } else if (comp_(key_extractor_(it.ptr_->data), key)) {
        if ((it.ptr_->*back_direction) == nullptr) {
          return {it.ptr_, back_direction};
        } else {
          return {pos.ptr_, direction};
        }
      } else {
        return get_insert_position(key);
      }
    } else if (comp_(key_extractor_(pos.ptr_->data), key)) {
      node_child_ptr direction = &node_type::right;
      node_child_ptr back_direction = base_node_type::get_sibling(direction);

      if (pos.ptr_ == direction_most(direction)) {
        return {direction_most(direction), direction};
      } else if (comp_(key, key_extractor_(it.ptr_->data))) {
        if ((pos.ptr_->*back_direction) == nullptr) {
          return {pos.ptr_, back_direction};
        } else {
          return {it.ptr_, direction};
        }
      } else {
        return get_insert_position(key);
      }
    } else {
      if constexpr (is_unique) {
        return {nullptr, nullptr};
      }
      return {pos.ptr_, &node_type::right};
    }
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Args...>)
      std::pair<iterator, bool> emplace(Args&&... args) {
    value_type data(std::forward<Args>(args)...);
    return insert(std::move(data));
  }

  template <typename... Args>
  requires(std::is_constructible_v<value_type, Args...>) iterator
      emplace_hint(const_iterator hint, Args&&... args) {
    value_type data(std::forward<Args>(args)...);
    return insert(hint, std::move(data)).first;
  }

  // TODO: think about whether its true
  template <typename T, typename... Args>
  std::pair<iterator, bool> try_emplace(T&& key, Args&&... args) requires(
      std::convertible_to<T, key_type>&&
          std::is_constructible_v<value_type, T, Args...>) {
    value_type data(std::piecewise_construct,
                    std::forward_as_tuple(std::forward<T>(key)),
                    std::forward_as_tuple(std::forward<Args>(args)...));
    return insert(std::move(data));
  }

  template <typename T, typename... Args>
  requires(std::convertible_to<T, key_type>&&
               std::is_constructible_v<value_type, T, Args...>) iterator
      try_emplace(const_iterator hint, T&& key, Args&&... args) {
    value_type data(std::piecewise_construct,
                    std::forward_as_tuple(std::forward<T>(key)),
                    std::forward_as_tuple(std::forward<Args>(args)...));
    return insert(hint, std::move(data)).first;
  }

  iterator erase(iterator pos) {
    iterator result = pos;
    ++result;

    node_type* extracted_node = extract_node(pos);
    destroyNode(extracted_node);

    return result;
  }

  iterator erase(const_iterator pos) {
    return erase(pos.unconst());
  }

  iterator erase(const_iterator first, const_iterator last) {
    while (first != last) {
      auto new_it = first++;
      erase(new_it);
    }
    return last.unconst();
  }

  size_type erase(const Key& key) {
    auto pos = find(key);

    if (pos != end()) {
      erase(pos++);
    } else {
      return 0;
    }

    if constexpr (!is_unique) {
      size_type counter = 1;

      while (!comp_(key, key_extractor_(*pos)) &&
             !comp_(key_extractor_(*pos), key)) {
        ++counter;
        erase(pos++);
      }

      return counter;
    }
    return 1;
  }

  void swap(Tree& other) noexcept(
      std::allocator_traits<allocator_type>::is_always_equal::value&&
          std::is_nothrow_swappable<key_compare>::value) {
    swap_fields(other);
    if constexpr (std::allocator_traits<
                      allocator_type>::propagate_on_container_swap::value) {
      swap_alloc(other);
    }
  }

  void swap_fields(Tree& other) {
    swap_fake_node(other);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  void swap_alloc(Tree& other) {
    std::swap(node_alloc_, other.node_alloc_);
  }

  void swap_fake_node(Tree& other) {
    std::swap(fake_.parent->parent, other.fake_.parent->parent);
    std::swap(fake_.parent, other.fake_.parent);
    std::swap(fake_.left, other.fake_.left);
    std::swap(fake_.right, other.fake_.right);
    std::swap(fake_.color, other.fake_.color);
  }

  node_handle_type extract(const_iterator position) {
    node_type* extracted_node;
    if (position != end()) {
      extracted_node = extract_node(position);
    }
    return node_handle_type(extracted_node, node_alloc_);
  }

  node_handle_type extract(const key_type& key) {
    auto it = find(key);
    return extract(it);
  }

  template <typename OtherKeyOfValue, typename OtherCompare, bool unique>
  void merge(Tree<Key, Value, OtherKeyOfValue, OtherCompare, Allocator, unique>&
                 source) {
    for (auto it = source.begin(); it != source.end(); ++it) {
      insert(*it);
    }
    source.clear();
  }

  template <typename OtherKeyOfValue, typename OtherCompare, bool unique>
  void merge(Tree<Key, Value, OtherKeyOfValue, OtherCompare, Allocator,
                  unique>&& source) {
    merge(source);
  }

  // Lookup
  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) size_type count(const T& key)
  const {
    size_type counter = 0;
    iterator it = find(key);

    while (it != end() && !comp_(key, key_extractor_(*it)) &&
           !comp_(key_extractor_(*it), key)) {
      ++it;
      ++counter;
    }

    return counter;
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) iterator find(const T& key)
  const {
    node_type* node = get_root();

    if (node == get_fake()) {
      return iterator(node);
    }

    while (node != nullptr && !(!comp_(key, key_extractor_(node->data)) &&
                                !comp_(key_extractor_(node->data), key))) {
      node_child_ptr child =
          node_type::get_left_if(comp_(key, key_extractor_(node->data)));
      node = node->*child;
    }

    if (node == nullptr) {
      node = get_fake();
    }

    return iterator(node);
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) bool contains(const T& key) const {
    return (find(key) != end());
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> || is_transparent<T, Key, Compare>)
      std::pair<const_iterator, const_iterator> equal_range(const T& key)
  const {
    auto first = lower_bound(key);
    auto last = upper_bound(key);
    return {first, last};
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> || is_transparent<T, Key, Compare>)
      std::pair<iterator, iterator> equal_range(const T& key) {
    auto first = lower_bound(key);
    auto last = upper_bound(key);
    return {first, last};
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) iterator lower_bound(const T& key) {
    node_type* node = get_root();
    node_type* parent = node;

    while (node != nullptr && !(!comp_(key, key_extractor_(node->data)) &&
                                !comp_(key_extractor_(node->data), key))) {
      node_child_ptr child =
          node_type::get_left_if(comp_(key, key_extractor_(node->data)));
      parent = node;
      node = node->*child;
    }

    iterator low_bound(node);

    if (node == nullptr) {
      low_bound.ptr_ = parent;
      if (comp_(key_extractor_(parent->data), key)) {
        ++low_bound;
      }
    }
    return low_bound;
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) const_iterator
      lower_bound(const T& key)
  const {
    node_type* node = get_root();
    node_type* parent = node;

    while (node != nullptr && !(!comp_(key, key_extractor_(node->data)) &&
                                !comp_(key_extractor_(node->data), key))) {
      node_child_ptr child =
          node_type::get_left_if(comp_(key, key_extractor_(node->data)));
      parent = node;
      node = node->*child;
    }

    const_iterator low_bound(node);

    if (node == nullptr) {
      low_bound.ptr_ = parent;
      if (comp_(key_extractor_(parent->data), key)) {
        ++low_bound;
      }
    }
    return low_bound;
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) const_iterator
      upper_bound(const T& key)
  const {
    const_iterator low_bound = lower_bound(key);

    if (low_bound != end()) {
      if (!comp_(key_extractor_(*low_bound), key) &&
          !comp_(key, key_extractor_(*low_bound))) {
        ++low_bound;
      }
    }
    return low_bound;
  }

  template <typename T>
  requires(std::convertible_to<T, key_type> ||
           is_transparent<T, Key, Compare>) iterator upper_bound(const T& key) {
    iterator low_bound = lower_bound(key);

    if (low_bound != end()) {
      if (!comp_(key_extractor_(*low_bound), key) &&
          !comp_(key, key_extractor_(*low_bound))) {
        ++low_bound;
      }
    }
    return low_bound;
  }

  // Observer
  key_compare key_comp() const {
    return comp_;
  }

  //   impl
  node_type* extract_node(const_iterator it) noexcept {
    node_type* node = it.ptr_;
    node_type* y;

    if (node->right != nullptr) {
      y = node->successor();
    } else if (node->left != nullptr) {
      y = node->predecessor();
    } else {
      y = node;
    }

    if (y != node) {
      swap_node(y, node);
    }

    base_node_type nil_base_node(y, node_color::kBlack);
    node_type* nil_node_ptr = static_cast<node_type*>(&nil_base_node);

    node_type* x;
    if (y->left != nullptr) {
      x = y->left;
    } else if (y->right != nullptr) {
      x = y->right;
    } else {
      x = nil_node_ptr;
    }

    x->parent = y->parent;
    if (y->parent == get_fake()) {
      changeRoot(x);
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }

    if (y->color == node_color::kBlack) {
      fixRemove(x);
    }

    if (get_root() == nil_node_ptr) {
      changeRoot(get_fake());
    } else if (nil_node_ptr->parent->left == nil_node_ptr) {
      nil_node_ptr->parent->left = nullptr;
    } else if (nil_node_ptr->parent->right == nil_node_ptr) {
      nil_node_ptr->parent->right = nullptr;
    }

    --size_;

    // TODO: make better
    if (size_ > 0) {
      set_leftmost(get_root()->minimum());
      set_rightmost(get_root()->maximum());
    } else {
      set_leftmost(get_fake());
      set_rightmost(get_fake());
    }
    return y;
  }

  void swap_node(node_type*& y, node_type*& node) noexcept {
    if (get_root() == node) {
      node->parent = y->parent;
      if (node->parent->left == y) {
        node->parent->left = node;
      } else {
        node->parent->right = node;
      }
      changeRoot(y);
    } else if (get_root() == y) {
      y->parent = node->parent;
      if (y->parent->left == node) {
        y->parent->left = y;
      } else {
        y->parent->right = y;
      }
      changeRoot(node);
    } else {
      std::swap(node->parent, y->parent);

      if (node->parent->left == y) {
        node->parent->left = node;
      } else {
        node->parent->right = node;
      }
      if (y->parent->left == node) {
        y->parent->left = y;
      } else {
        y->parent->right = y;
      }
    }

    std::swap(y->left, node->left);
    if (node->left != nullptr) {
      node->left->parent = node;
    }
    if (y->left != nullptr) {
      y->left->parent = y;
    }

    std::swap(y->right, node->right);
    if (node->right != nullptr) {
      node->right->parent = node;
    }
    if (y->right != nullptr) {
      y->right->parent = y;
    }

    std::swap(y->color, node->color);
    std::swap(y, node);
  }

  void fixRemove(node_type* node) noexcept {
    while (node != get_root() && node->color == node_color::kBlack) {
      node_type* w;

      node_child_ptr current_child =
          node_type::get_left_if(node == node->parent->left);
      node_child_ptr sibling_child = node_type::get_sibling(current_child);

      w = node->parent->*sibling_child;

      if (w->color == node_color::kRed) {
        w->color = node_color::kBlack;
        node->parent->color = node_color::kRed;
        rotate(node->parent, current_child);
        w = node->parent->*sibling_child;
      }

      if ((w->*current_child == nullptr ||
           (w->*current_child)->color == node_color::kBlack) &&
          (w->*sibling_child == nullptr ||
           (w->*sibling_child)->color == node_color::kBlack)) {
        w->color = node_color::kRed;
        node = node->parent;
      } else {
        if (w->*sibling_child == nullptr ||
            (w->*sibling_child)->color == node_color::kBlack) {
          if (w->*sibling_child != nullptr) {
            (w->*current_child)->color = node_color::kBlack;
          }
          w->color = node_color::kRed;
          rotate(w, sibling_child);
          w = node->parent->*sibling_child;
        }

        w->color = node->parent->color;
        node->parent->color = node_color::kBlack;
        (w->*sibling_child)->color = node_color::kBlack;
        rotate(node->parent, current_child);
        node = get_root();
      }
    }
    node->color = node_color::kBlack;
  }

  void clear(node_type* node) noexcept {
    if (node != get_fake() && node != nullptr) {
      clear(node->right);
      clear(node->left);
      destroyNode(node);
    } else if (node != nullptr) {
      clear_fake();
    }
  }

  // create
  void createRoot(node_type* new_root) noexcept {
    new_root->parent = static_cast<node_type*>(&fake_);
    new_root->color = node_color::kBlack;

    set_leftmost(new_root);
    set_rightmost(new_root);

    set_root(new_root);
  }

  void changeRoot(node_type* new_root) noexcept {
    new_root->parent = get_fake();
    set_root(new_root);
  }

  template <typename T>
  requires(std::convertible_to<T, value_type>) node_type* constructNode(
      node_type* parent, T&& data, node_color color) {
    node_type* node = node_allocator_traits::allocate(node_alloc_, 1);

    try {
      node_allocator_traits::construct(node_alloc_, node, parent, color,
                                       std::forward<T>(data));
    } catch (...) {
      destroyNode(node);
      throw;
    }

    return node;
  }

  void destroyNode(node_type* node) noexcept {
    node_allocator_traits::destroy(node_alloc_, node);
    node_allocator_traits::deallocate(node_alloc_, node, 1);
  }

  void fixInsert(node_type* node) noexcept {
    while (node != get_root() && node->parent->color == node_color::kRed) {
      node_child_ptr current_child =
          node_type::get_left_if(node->parent == node->parent->parent->left);
      node_child_ptr sibling_child = node_type::get_sibling(current_child);

      node_type* uncle = node->parent->parent->*sibling_child;

      if (uncle != nullptr && uncle->color == node_color::kRed) {
        uncle->color = node_color::kBlack;

        node->parent->color = node_color::kBlack;
        node->parent->parent->color = node_color::kRed;

        node = node->parent->parent;
      } else {
        if (node == node->parent->*sibling_child) {
          node = node->parent;
          rotate(node, current_child);
        }
        node->parent->color = node_color::kBlack;
        node->parent->parent->color = node_color::kRed;

        rotate(node->parent->parent, sibling_child);
      }
    }
    get_root()->color = node_color::kBlack;
  }

  void rotate(node_type* x, node_child_ptr current_child) noexcept {
    node_child_ptr sibling_child = node_type::get_sibling(current_child);
    node_type* y = x->*sibling_child;

    if (y == nullptr) {
      return;
    }

    x->*sibling_child = y->*current_child;
    if (y->*current_child != nullptr) {
      (y->*current_child)->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == get_root()->parent) {
      changeRoot(y);
    } else if (x == x->parent->*current_child) {
      x->parent->*current_child = y;
    } else {
      x->parent->*sibling_child = y;
    }

    y->*current_child = x;
    x->parent = y;
  }

  std::pair<node_type*, node_child_ptr> search(const key_type& key) const {
    node_type* it = get_root();
    node_type* parent = nullptr;
    node_child_ptr child;

    while (it != nullptr && !comp_(key, key_extractor_(it->data)) &&
           !comp_(key_extractor_(it->data), key)) {
      child = node_type::get_left_if(comp_(key, key_extractor_(it->data)));
      parent = it;
      it = it->*child;
    }
    return {parent, child};
  }

  auto* direction_most(node_child_ptr direction) const noexcept {
    if (direction == &node_type::left) {
      return get_leftmost();
    } else {
      return get_rightmost();
    }
  }

  void set_leftmost(node_type* node) noexcept {
    fake_.left = node;
  }
  void set_rightmost(node_type* node) noexcept {
    fake_.right = node;
  }
  void set_root(node_type* node) noexcept {
    fake_.parent = node;
  }

  node_type* get_leftmost() const noexcept {
    return fake_.left;
  }
  node_type* get_rightmost() const noexcept {
    return fake_.right;
  }
  node_type* get_root() const noexcept {
    return fake_.parent;
  }
  node_type* get_fake() const noexcept {
    return static_cast<node_type*>(const_cast<base_node_type*>(&fake_));
  }
};

}  // namespace vr
