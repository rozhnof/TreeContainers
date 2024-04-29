#pragma once

namespace s21 {

enum Color { kRed = 0, kBlack = 1 };

template <typename Value>
struct Node;

template <typename Value>
struct BaseNode {
  using NodeType = Node<Value>;
  using NodeMemberPtr = NodeType* BaseNode::*;

  NodeType* left = nullptr;
  NodeType* right = nullptr;
  NodeType* parent = nullptr;
  Color color = Color::kBlack;

  BaseNode() noexcept {
  }
  BaseNode(NodeType* parent, Color color) noexcept
      : parent(parent),
        color(color) {
  }

  NodeType* successor() const noexcept {
    return get_by_direction(&NodeType::right);
  }

  NodeType* predecessor() const noexcept {
    return get_by_direction(&NodeType::left);
  }

  static NodeMemberPtr get_left_if(bool condition) noexcept {
    return (condition) ? &BaseNode::left : &BaseNode::right;
  }

  static NodeMemberPtr get_sibling(NodeMemberPtr node) noexcept {
    return get_left_if(node == &BaseNode::right);
  }

 protected:
  NodeType* get_by_direction(NodeMemberPtr direction) const noexcept {
    NodeType* node = const_cast<NodeType*>(static_cast<const NodeType*>(this));

    if (node->color == Color::kRed && node->parent->parent == node) {
      return node->right;
    } else if ((node->*direction) != nullptr) {
      return (node->*direction)->get_extremum(get_sibling(direction));
    }

    NodeType* y = node->parent;
    while (node == y->*direction &&
           !(y->color == Color::kRed && y->parent->parent == y)) {
      node = y;
      y = y->parent;
    }
    return y;
  }

  NodeType* get_extremum(NodeMemberPtr direction) const noexcept {
    NodeType* node = const_cast<NodeType*>(static_cast<const NodeType*>(this));
    while ((node->*direction) != nullptr) {
      node = node->*direction;
    }
    return node;
  }
};

template <typename Value>
struct Node : BaseNode<Value> {
  using NodeMemberPtr = BaseNode<Value>::NodeMemberPtr;

  Value data;

  template <typename... Args>
  requires(std::is_constructible_v<Value, Args...>)
      Node(Node* parent, Color color, Args&&... args)
      : BaseNode<Value>(parent, color),
        data(std::forward<Args>(args)...) {
  }

  Node* minimum() const noexcept {
    return BaseNode<Value>::get_extremum(&Node::left);
  }

  Node* maximum() const noexcept {
    return BaseNode<Value>::get_extremum(&Node::right);
  }
};

}  // namespace s21
