/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"
#include "DataTypes.h"
#include "ManipulateData.h"


/**
 * Finds the max value between two values;
 * @param x : First value
 * @param y : Second value
 * @return  : The biggest value among the two passing as argument
 */
int max(int x, int y){
    return (x > y) ? x : y;
}

/**
 * Calculates the height of the AVL tree 
 * @param tree  : The AVL tree
 * @return      : The height of the AVL thee
 */
int height (SocialNetworkT *tree){
    return (!tree) ? -1 : tree->height;
}

/**
 * This function will take the coAuthors of an author and 
 * add them to the AVL
 * 
 * @param T             : The Social network
 * @param coAuthors     : The array of coAuthors names
 * @param pos           : The position of author
 * @param total_authors : The total number of authors
 * @return              : The Social network with the coAuthors added
 */
SocialNetworkT *insert_co_authors(SocialNetworkT *T, char **coAuthors, int pos, 
                                    int total_authors){
    
    for(int i = 0; i < total_authors; i++)
    {
        if(i != pos) // Making sure that we do not insert 
        {            // the actual author as its own coAuthor
            T = insert_avl(T, coAuthors, i, total_authors, INSERT_COAUTHOR);
        }
    }
    return T;
}

/* -------------------------- AVL ROTATION FUNCTIONS --------------- */ 

/* Authors Tree */

/**
 * Makes a single tree rotation to the left
 * @param K2    : The tree to be rotate
 * @return      : Returns the new root;
 */
SocialNetworkT *single_rotate_left(SocialNetworkT *K2 ){
    
    SocialNetworkT *K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;
 
    K2->height = max( height( K2->left ), height( K2->right ) ) + 1;
    K1->height = max( height( K1->left ), K2->height ) + 1;
 
    return K1;  /* New root */
}
 
/**
 * Makes a single tree rotation to the right
 * @param K1    : The tree to be rotate
 * @return      : Returns the new root;
 */
SocialNetworkT *single_rotate_right(SocialNetworkT  *K1) {
    
    SocialNetworkT *K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;
 
    K1->height = max( height( K1->left ), height( K1->right ) ) + 1;
    K2->height = max( height( K2->right ), K1->height ) + 1;
 
    return K2;  
}
 
/**
 * Makes a double tree rotation to the left (single right + single left)
 * @param K3    : The tree to be rotate
 * @return      : Returns the new root;
 */
SocialNetworkT *double_rotate_left(SocialNetworkT *K3){
    
    K3->left = single_rotate_right( K3->left );
 
    return single_rotate_left( K3 );
}
 
/**
 * Makes a double tree rotation to the right (single left + single right)
 * @param K1    : The tree to be rotate
 * @return      : Returns the new root;
 */
SocialNetworkT *double_rotate_right(SocialNetworkT *K1){
    
    K1->right = single_rotate_left(K1->right);
 
    return single_rotate_right( K1 );
}


/* ------------------------------------------------------------- */ 

/**
 * This function creates an Author Node
 * @param author            : The array of authors
 * @param pos               : The position of the author
 * @param total_authors     : The total number of authors
 * @return A node of SocialNetworkT for the author[pos]
 */
SocialNetworkT *new_author_node(char **authors, int pos, int total_authors)
{    
    SocialNetworkT *T = malloc(sizeof(SocialNetworkT));
    
    if(T)
    {
        T->name = malloc(strlen(authors[pos]) + 1);
        
        if(T->name)
        {
            strcpy(T->name,authors[pos]);
            T->left = T->right = NULL;
            T->height = 0;
            T->co_authors = NULL;
            T->co_authors = insert_co_authors(  T->co_authors, 
                                                authors, 
                                                pos,
                                                total_authors);
            return T;
        }
        else
        {// Memory Problems
            free(T);
            return NULL;
        }
    }
    else 
        // Memory Problems
        return NULL;
    
}

/* This function creates an CoAuthor Node */
SocialNetworkT *new_co_authors_node(char **authors, int pos){
      
    SocialNetworkT *T = malloc(sizeof(SocialNetworkT));
    
    if(T)
    {
        T->name = malloc(strlen(authors[pos]) + 1);
        
        if(T->name)
        {
            strcpy(T->name,authors[pos]);
            T->left = T->right = NULL;
            T->height = 0;
            T->total = 1;
            return T;
        }
        else{ // Memory Problems
            free(T);
            return NULL;
        } 
    }
    else // Memory Problems
        return NULL;
}

/* 
 * This function will insert an Author or CoAuthor 
 * (depending of the flag pass as argument on the AVL of Authors 
 * or CoAuthos (depending of the flag). 
    This function insert both Authors and CoAuthos for the sake of code reuse. 
 */

SocialNetworkT *insert_avl(SocialNetworkT *T, char **authors, int pos, 
                            int total_authors, int flag){
    
    
    /** If this author was never been add before*/
    if(!T)
    {
        T = (flag == INSERT_AUTHOR) ? 
            new_author_node(authors,pos,total_authors) : // Insert an Author
            new_co_authors_node(authors,pos); // Insert an CoAuthor 
                                        // to one Author's node
    } // If this author is already on the tree
    else if(strcmp(T->name,authors[pos]) == 0) 
    { 
        if(flag == INSERT_AUTHOR) //In the case that we are inserting an author
        {
           T->co_authors = insert_co_authors(T->co_authors, 
                                                authors, pos, total_authors);
        }
        else// Increment the Weight of this connection Author -Total-> CoAuthor
        {
           T->total++; 
        }
        return T;
    }
    else if(strcmp(T->name,authors[pos]) < 0) // Iterate over the left subTree
    {
        T->left = insert_avl(T->left,authors,pos,total_authors,flag);
        if((height(T->left) - height(T->right)) == 2) // Rotate the Tree
        {
            T = strcmp (T->left->name, authors[pos]) < 0 ? 
                                                    single_rotate_left(T) : 
                                                    double_rotate_left(T);
        }       
    }               
    else // Iterate over the right subTree
    {
        T->right = insert_avl(T->right, authors, pos, total_authors, flag);
        if ((height(T->right) - height(T->left)) == 2)//  Rotate the Tree
        {
            T = strcmp(T->right->name, authors[pos]) > 0 ? 
                                                    single_rotate_right(T) :
                                                    double_rotate_right(T);
        }
    }

    /* Updating the height of this node */
    T->height = max ( height(T->left), height(T->right)) + 1;
    return T;
}

/*
 * For a given author this function will return the total of 
 * coAuthors associated to this author
 */
int get_author_total_coAuthors_tree(SocialNetworkT *T, char *author){
         
    if(T)
    {
       
       if (strcmp(T->name,author) == 0)      
           return T->total;
       else if (strcmp(T->name,author) < 0)  
           return get_author_total_coAuthors_tree(T->left, author);
       else                                  
           return get_author_total_coAuthors_tree(T->right, author);
    }
    return -1;
}

/**
 * For a given pair of author and coAuthor will return the total of articles
 * which both have work
 * @param author        : The author name
 * @param coAuthor      : The coAuthor name
 * @param T             : The Social Network
 * @return              : the total of articles written by the two
 */
int total_articles_with_this_coAuthor(  SocialNetworkT *T, 
                                        char *author, char *coAuthor)
{
    if(T)
    {
       if (strcmp(T->name,author) == 0)
       {
           return get_author_total_coAuthors_tree(T->co_authors, coAuthor);
       }
       else if (strcmp(T->name, author) < 0)  
           return total_articles_with_this_coAuthor(T->left, author,coAuthor);
       else                                  
           return total_articles_with_this_coAuthor(T->right, author,coAuthor);
    }
    return -1;
}

/* Returns the number of different Authors for a give AVL*/
int get_total_different_Authors(SocialNetworkT *tree){
    
    return (!tree) ? 
       0 : 
       1 + get_total_different_Authors(tree->left) + 
                get_total_different_Authors(tree->right);
}

/* Returns the number of pairs Authors existed on a given Tree*/
int get_number_of_relations(SocialNetworkT *tree){
    
    return (!tree) ? 0 : get_total_different_Authors(tree->co_authors) + 
                            get_number_of_relations(tree->left) + 
                            get_number_of_relations(tree->right);
}

/* Returns the biggest number of articles 
 * wrote with a CoAuthor for a give Author */
int max_pair_author_coAuthor_aux(SocialNetworkT *tree){
    return (!tree) ? 0 : max(tree->total,
            max(max_pair_author_coAuthor_aux(tree->left),
            max_pair_author_coAuthor_aux(tree->right)));
}

/* Returns the biggest Pair for a given Authors Tree */
int max_pair_author_coAuthor(SocialNetworkT *tree){
    
    return (!tree) ? 0:
        max(max_pair_author_coAuthor_aux(tree->co_authors), 
            max(max_pair_author_coAuthor(tree->left), 
                    max_pair_author_coAuthor(tree->right)));
}

int get_final_height(SocialNetworkT *tree){
    
    return (!tree) ? 0 : 
        1 + max(get_final_height (tree->left), get_final_height (tree->right)); 
}

/* Add the an list the Pairs of Authors that had wrote N articles together */
void get_coAuthors_with_N_weight(   SocialNetworkT *autor, 
                                    SocialNetworkT *coTree, 
                                    int N, 
                                    PairsAuthorsS **listPairs){
    
    if(coTree)
    {
      if(coTree->total == N)
      {
          *listPairs = insert_pair_authors (autor,coTree,*listPairs);
      }
      get_coAuthors_with_N_weight(autor,coTree->left,N,listPairs);
      get_coAuthors_with_N_weight(autor,coTree->right,N,listPairs);  
    }
    
}

int get_total_coAuthors(SocialNetworkT *coTree){
    return (coTree) 
     ? 1 + get_total_coAuthors(coTree->left) + 
           get_total_coAuthors(coTree->right) 
      : 0;
}

/* Save on a list the Pairs of Authors that have wrote N articles together */
void get_pair_with_N_weight(SocialNetworkT *Tree,int N, PairsAuthorsS **lp){
    
    if(Tree)
    {
       get_coAuthors_with_N_weight(Tree, Tree->co_authors, N, lp);
       get_pair_with_N_weight     (Tree->left,N,lp);
       get_pair_with_N_weight     (Tree->right,N,lp);
    }
}

void with_most_coAuthors(SocialNetworkT *T, RejectedS **top){
    
    if(T)
    {
        (*top) = insert_top_list(*top, T, 1);
        (*top) = clear_top(*top,1);
        with_most_coAuthors(T->left,top);
        with_most_coAuthors(T->right,top);
    }
}

void prepare_tree_aux(SocialNetworkT *T){
    
    if(T)
    {
        T->total = get_total_coAuthors(T->co_authors);
        prepare_tree_aux(T->left);
        prepare_tree_aux(T->right);
    }
}
