#include "binary_search_tree.h"
#include <iostream>
#include <string>

bool BinarySearchTree::Search(const std::string& word1, const std::string& word2) {
    Node *pointer = root_;
    int compare_word1;
    int compare_word2;
    while (pointer != NULL) {//checking if the tree is empty and using a loop to search all the nodes necessary
      compare_word1 = pointer->first_word.compare(word1);//comparing the first word of the tuple we want to find with the first word of the existing node we are crossing
      compare_word2 = pointer->second_word.compare(word2);//same for the second word of the tuple
      if (compare_word1 > 0) {//if the first word we wanna find, lexicographically, has a priority we go left
        pointer = pointer->left;
      } else if (compare_word1 < 0) {//if the first word we wanna find, lexicographically, does not have a priority we go right 
        pointer = pointer->right;
      } else {//if the first words are lexicographically equivalent, we compare the second words
        if (compare_word2 > 0) {//same procedure with first word
          pointer = pointer->left;
        } else if (compare_word2 < 0) {//same procedure with first word
          pointer = pointer->right;
        } else {
          return true;//if second words are lexicographically equivalent too, we have found the wanted tuple that we searched for in the tree
        }
      }
    }
    return false;
  }

void BinarySearchTree::Insert(const std::string& word1, const std::string& word2) {
    if (root_ == NULL) {//if tree is empty we insert the tuple at the root-node
      Node *new_node = new Node(word1, word2);
      root_ = new_node;
      pointer_ = root_;
    } else {
      while (pointer_ != NULL) {//if its not empty we compare the first words lexicographically to see if we will go left or right
        int compare_word1;
        int compare_word2;
        compare_word1 = pointer_->first_word.compare(word1);
        compare_word2 = pointer_->second_word.compare(word2);
        if (compare_word1 > 0) { //going left
          if (pointer_->left == NULL) {
            Node *new_node = new Node(word1, word2);
            pointer_->left = new_node;
            pointer_ = root_;
            break;
          } else {
            pointer_ = pointer_->left;
          }
        } else if (compare_word1 < 0) { //going right
          if (pointer_->right == NULL) {
            Node *new_node = new Node(word1, word2);
            pointer_->right = new_node;
            pointer_ = root_;
            break;
          } else {
            pointer_ = pointer_->right;
          }
        } else {//if first words lexicographically equivalent we compare second words and again go left or right
          if (compare_word2 > 0) {//going left
            if (pointer_->left == NULL) {
              Node *new_node = new Node(word1, word2);
              pointer_->left = new_node;
            } else {
              pointer_ = pointer_->left;
            }
          } else if (compare_word2 < 0) {//going right
            if (pointer_->right == NULL) {
              Node *new_node = new Node(word1, word2);
              pointer_->right = new_node;
            } else {
              pointer_ = pointer_->right;
            }
          } else {//if second words are equivalent too we increase the counter of the specific tuple of words by one
            pointer_->counter++;
          }
        }
      }
    }
  }

void BinarySearchTree::DeleteNode(Node *pointer){//the assistant function used by the destructor
  if (pointer!=NULL){//if tree not empty already
    if(pointer->left!=NULL)//recursive calls to get every node (basically crossing the tree in post-order)
      DeleteNode(pointer->left);
    if (pointer->right!=NULL)
      DeleteNode(pointer->right);
    delete pointer;//deleting every node since we have already used recursion
  }
}