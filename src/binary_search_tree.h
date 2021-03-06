#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
template <typename T>
struct Node {
  T data;
  Node* left;
  Node* right;
  Node() {
    left = right = nullptr;
    data = 0;
  }
  Node(const T& e) {
    data = e;
    left = right = nullptr;
  }
};
template <typename T>
class BinarySearchTree {
 protected:
  Node<T>* root_;  // pointer at the root of the tree
 public:
  BinarySearchTree() {  // tree's constructor used to create an empty tree
    root_ = nullptr;
  }
  // Returns true if the tree contains no elements
  bool IsEmpty() const { return root_ == nullptr; }

  void DeleteNode(
      Node<T>* pointer);  // assistant function used by the destructor

  ~BinarySearchTree() {  // the destructor used to delete the tree
    DeleteNode(root_);
  }

  void Insert(
      const std::string& word1,
      const std::string& word2);  // function to insert a new tuple of words

  bool Contains(const T& element) const;
};

#endif