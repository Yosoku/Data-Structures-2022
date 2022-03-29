#include "binary_search_tree.h"

void BinarySearchTree::insert(char* word1,char* word2,struct node** leaf)
{
if(*leaf==NULL){
        *leaf =(node*)malloc(sizeof(node));
        (*leaf)->string1=(char*)malloc(strlen(word1)+1);     // memory allocation for string1
        strcpy((*leaf)->string1,word1);                      // copy first word to string1
        (*leaf)->string2=(char*)malloc(strlen(word2)+1);     // memory allocation for string2
        strcpy((*leaf)->string2,word2);                      // copy second word to string2
        (*leaf)->left =NULL;                                 //set left pointer to null
        (*leaf)->right=NULL;                                 //set right pointer to null
        (*leaf)->counter=1;                                  //set counter of pair to 1
    } else {
        //choose where to place a node if root already exists
        int search_string1;
        int search_string2;
        search_string1 = strcmp(word1,(*leaf)->string1);
        search_string2 = strcmp(word2,(*leaf)->string2);
        if(search_string1<0)
            insert( word1,word2,&(*leaf)->left);//recursive call of insert function to go left
        else if(search_string1>0)
            insert( word1,word2,&(*leaf)->right);//recursive call of insert function to go right
        else
        {
          if(search_string2<0)//compare second word of pair if first already exists in another pair
            insert( word1,word2,&(*leaf)->left);//go left
                                                
          else if(search_string2>0)//compare second word of pair if first already exists in another pair
            insert( word1,word2,&(*leaf)->right);//go right                                   
          else
            ((*leaf)->counter)++;//identical pair so increase counter of this pair by one
        }
    }
}

void BinarySearchTree::search(char* word1,char* word2, struct node* leaf)
{
    int search_string1;
    int search_string2;
    if(leaf!=NULL) {
        search_string1=strcmp(word1,leaf->string1);
        search_string2=strcmp(word2,leaf->string2);
        //search for first word of the pair
        if(search_string1<0)
            search(word1,word2,leaf->left);
        else if(search_string1>0)
            search(word1,word2,leaf->right);
        //if we found the first word in a pair we need to check the second word too
        //search for second word of the pair
        else
        {
          if(search_string2<0)
            search(word1,word2,leaf->left);
          else if(search_string2>0)
            search(word1,word2,leaf->right);
          else
          {
            //σε αυτό το else λείπει κώδικας ώστε να αποθηκεύονται σε αρχείο τα ζεύγη που βρέθηκαν στην αναζήτηση και ο μετρητής τους αλλά δεν ξέρω πως να το κάνω αυτό
          }
        }  
    }
    return;
}

void BinarySearchTree::tree_deletion(struct node** leaf)
{
    if(*leaf!=NULL) {
        //recursive calls to enter every node of the tree
        tree_deletion(&(*leaf)->left);
        tree_deletion(&(*leaf)->right);
        //gradually delete every node's words and then itself
        free((*leaf)->string1);         
        free((*leaf)->string2); 
        free((*leaf));
    }
}