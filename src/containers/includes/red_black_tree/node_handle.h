#pragma once

#include <optional>

namespace s21 {

template <typename ValueType, typename NodeAllocator>
class BaseNodeHandle {
 public:
  using allocator_type = NodeAllocator;
  using alloc_traits = std::allocator_traits<allocator_type>;
  using node_type_ptr = alloc_traits::pointer;

  allocator_type get_allocator() const noexcept {
    assert(!empty());
    return opt_alloc_.value();
  }

  explicit operator bool() const noexcept {
    return node_ != nullptr;
  }

  [[nodiscard]] bool empty() const noexcept {
    return node_ == nullptr;
  }

 protected:
  constexpr BaseNodeHandle() noexcept {
  }

  ~BaseNodeHandle() {
    if (!empty()) {
      reset();
    }
  }

  BaseNodeHandle(BaseNodeHandle&& nh) noexcept
      : node_(nh.node_) {
    if (node_) {
      move(std::move(nh));
    }
  }

  BaseNodeHandle& operator=(BaseNodeHandle&& nh) noexcept {
    if (empty()) {
      if (!nh.empty()) {
        move(std::move(nh));
      }
    } else if (nh.empty()) {
      reset();
    } else {
      alloc_traits::destroy(opt_alloc_.value(), node_);
      alloc_traits::deallocate(opt_alloc_.value(), node_, 1);

      opt_alloc_ = std::move(nh.opt_alloc_.value());
      node_ = nh.node_;
      nh.node_ = nullptr;
    }
    return *this;
  }

  BaseNodeHandle(node_type_ptr ptr, const allocator_type& alloc)
      : node_(ptr),
        opt_alloc_(alloc) {
    assert(ptr != nullptr);
  }

  void swap(BaseNodeHandle& nh) noexcept {
    if (empty()) {
      if (!nh.empty()) {
        move(std::move(nh));
      }
    } else if (nh.empty()) {
      nh.move(std::move(*this));
    } else {
      std::swap(node_, nh.node_);
      opt_alloc_.swap(nh.opt_alloc_);
    }
  }

 private:
  void move(BaseNodeHandle&& nh) noexcept {
    opt_alloc_ = std::move(nh.opt_alloc_.value());
    node_ = nh.node_;
    nh.node_ = nullptr;
  }

  void reset() noexcept {
    allocator_type alloc = std::move(opt_alloc_.value());
    alloc_traits::destroy(alloc, node_);
    alloc_traits::deallocate(alloc, node_, 1);
    node_ = nullptr;
  }

 protected:
  node_type_ptr node_ = nullptr;

 private:
  void swap_alloc(std::optional<allocator_type>& other_opt_alloc_) noexcept {
    if constexpr (alloc_traits::propagate_on_container_swap::value) {
      opt_alloc_.swap(other_opt_alloc_);
    } else if constexpr (!alloc_traits::is_always_equal::value) {
      assert(opt_alloc_.value() == other_opt_alloc_.value());
    }
  }

  void init_alloc(const allocator_type& alloc) {
    opt_alloc_ = alloc;
  }

  void set_alloc(allocator_type&& alloc) noexcept {
    if constexpr (alloc_traits::propagate_on_container_move_assignment::value) {
      opt_alloc_ = std::move(alloc);
    } else if constexpr (!alloc_traits::is_always_equal::value) {
      assert(opt_alloc_.has_value());
      if (opt_alloc_.has_value()) {
        assert(opt_alloc_.value() == alloc);
      }
    }
  }

  std::optional<allocator_type> opt_alloc_;

  template <class Key_, class Value_, class KeyOfValue_, class Compare_,
            class Allocator_, bool is_unique_>
  friend class Tree;
};

template <typename Key, typename Value, typename NodeAllocator>
class NodeHandle : public BaseNodeHandle<Value, NodeAllocator> {
 public:
  using value_type = Value;
  using key_type = Key;
  using mapped_type = value_type::second_type;

  using allocator_type = NodeAllocator;
  using alloc_traits = std::allocator_traits<allocator_type>;
  using node_type_ptr = alloc_traits::pointer;

  constexpr NodeHandle() noexcept = default;
  NodeHandle(NodeHandle&&) noexcept = default;
  ~NodeHandle() = default;

  NodeHandle& operator=(NodeHandle&&) noexcept = default;

  key_type& key() const noexcept {
    return *key_;
  }

  mapped_type& mapped() const noexcept {
    return *mapped_;
  }

  void swap(NodeHandle& other) noexcept {
    this->swap(other);
    std::swap(key_, other.key_);
    std::swap(mapped_, other.mapped_);
  }

 private:
  NodeHandle(node_type_ptr node, const allocator_type& alloc)
      : BaseNodeHandle<value_type, allocator_type>(node, alloc) {
    if (node) {
      auto& unconst_key = const_cast<key_type&>(node->data.first);
      key_ = &unconst_key;
      mapped_ = &node->data.second;
    }
  }

  key_type* key_ = nullptr;
  mapped_type* mapped_ = nullptr;

  template <typename Key_, typename T_, typename Compare_, typename Allocator_>
  friend class map;

  template <class Key_, class Value_, class KeyOfValue_, class Compare_,
            class Allocator_, bool is_unique_>
  friend class Tree;
};

template <typename Value, typename NodeAllocator>
class NodeHandle<Value, Value, NodeAllocator>
    : public BaseNodeHandle<Value, NodeAllocator> {
 public:
  using value_type = Value;

  using allocator_type = NodeAllocator;
  using alloc_traits = std::allocator_traits<allocator_type>;
  using node_type_ptr = alloc_traits::pointer;

  constexpr NodeHandle() noexcept = default;
  NodeHandle(NodeHandle&&) noexcept = default;
  ~NodeHandle() = default;

  NodeHandle& operator=(NodeHandle&&) noexcept = default;

  value_type& value() const noexcept {
    return this->node_->data;
  }

  void swap(NodeHandle& other) noexcept {
    this->swap(other);
  }

 private:
  NodeHandle(node_type_ptr node, const allocator_type& alloc)
      : BaseNodeHandle<value_type, allocator_type>(node, alloc) {
  }

  const value_type& key() const noexcept {
    return value();
  }

  template <typename Key_, typename Compare_, typename Allocator_>
  friend class set;

  template <typename Key_, typename Compare_, typename Allocator_>
  friend class multiset;

  template <class Key_, class Value_, class KeyOfValue_, class Compare_,
            class Allocator_, bool is_unique_>
  friend class Tree;
};

}  // namespace s21
