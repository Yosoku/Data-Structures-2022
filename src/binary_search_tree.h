#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

class BinarySearchTree {
protected:
  struct Node {//this struct will be used to store the tree's leaves
    std::string first_word;
    std::string second_word;
    Node *left;
    Node *right;
    unsigned int counter;//variable to count how many times the tuple of words has been found

  //every time a new node is created this function is called to initialize the node's data
    Node(const std::string &first_word, const std::string &second_word) {
      this->first_word = first_word;
      this->second_word = second_word;
      right = NULL;
      left = NULL;
      counter = 1;
    }
  };
  Node *root_; //pointer at the root of the tree
  Node *pointer_;// assistant pointer to cross the tree's nodes
public:
  BinarySearchTree() {//tree's constructor used to create an empty tree
    root_ = NULL;
    pointer_ = NULL;
  }

  void DeleteNode(Node *pointer);//assistant function used by the destructor

  ~BinarySearchTree(){//the destructor used to delete the tree
    DeleteNode(root_);
  }

  void Insert(const std::string& word1, const std::string& word2);//function to insert a new tuple of words
  
  bool Search(const std::string& word1, const std::string& word2);//function to search for a specific tuple of words
};

#endif