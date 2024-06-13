#pragma once

#include "node.h"

namespace vr {

template <typename Value, bool is_const>
struct Iterator {
 public:
  using iterator = Iterator<Value, false>;
  using const_iterator = Iterator<Value, true>;
  using iterator_type = Iterator<Value, is_const>;

  using value_type = Value;
  using node_type = Node<Value>;

  using reference =
      std::conditional_t<is_const, const value_type&, value_type&>;
  using pointer = std::conditional_t<is_const, const value_type*, value_type*>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;

  node_type* ptr_;

  explicit Iterator(node_type* ptr = nullptr)
      : ptr_(ptr) {
  }

  Iterator(const Iterator<Value, true>& other) requires(is_const)
      : ptr_(other.ptr_) {
  }
  Iterator(const Iterator<Value, false>& other)
      : ptr_(other.ptr_) {
  }

  iterator_type& operator=(const iterator_type& other) noexcept {
    this->ptr_ = other.ptr_;
    return *this;
  }

  reference operator*() const noexcept {
    return ptr_->data;
  }

  pointer operator->() const noexcept {
    return &ptr_->data;
  }

  bool operator==(const iterator_type& other) const noexcept {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const iterator_type& other) const noexcept {
    return ptr_ != other.ptr_;
  }

  iterator_type& operator++() {
    ptr_ = ptr_->successor();
    return *this;
  }

  iterator_type operator++(int) {
    iterator_type tmp(ptr_);
    ptr_ = ptr_->successor();
    return tmp;
  }

  iterator_type& operator--() {
    ptr_ = ptr_->predecessor();
    return *this;
  }

  iterator_type operator--(int) {
    iterator_type tmp(ptr_);
    ptr_ = ptr_->predecessor();
    return tmp;
  }

  Iterator<Value, false> unconst() const noexcept {
    return Iterator<Value, false>(ptr_);
  }
};

}  // namespace vr
