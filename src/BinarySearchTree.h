//Συναρτήσεις και βιβλιοθήκες για μέτρηση χρόνου δεν ξέρω οπότε είτε τις μαθαίνω και τις προσθέτω κάποια στιγμή ή τις βάζεις εσύ 
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <cstring>
class BinarySearchTree
{
public://εδω δεν ημουν σιγουρος αν πρεπει να το βαλω private ή protected, το αφήνω σε σένα για να μπορείς να το συνδέσεις με τα δικά σου
//struct to save the two words of the pair as well as left,right pointers and pair counter
struct node {
    char *string1; 
    char *string2;
    unsigned int counter; 
    struct node *left;
    struct node *right;
};

public:
//function to insert new nodes
static void insert(char* word1,char* word2,struct node** leaf);

//function to search if a pair of words is part of the tree
static void search(char* word1,char* word2, struct node* leaf);

//function to empty the memory that the tree allocated 
static void tree_deletion(struct node** leaf);
};
#endif