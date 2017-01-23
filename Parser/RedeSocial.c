/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuxFuncReadDBLP.h"
#include "DataTypes.h"
#include "ManipulateData.h"
#include "AVLTree.h"
#include "Hash.h"
#include "printStdio.h"

    
/* This function will take the authors list (a string) of an accepted 
 * article and put them on the SocialNet */
void add_authors(SocialNetworkT **network, char *authors, int total_authors){
    
    /* Will be use to save each author in a different position of an array */
     char **coAuthors;  
     int i = 0, hash;
     
     /* Allocate space of the array of strings*/
      coAuthors = new_array_strings(total_authors,STRING_SIZE);
      bypass_symbol(&authors, ' ');    /** Clean any spaces in the end */ 
   
     /* Breaking the authors name into different strings*/
      while(i < total_authors && sscanf (authors,"%[^,|:]s", coAuthors[i]) > 0)       
      {
          /** updating the actual position on the string */
          authors += strlen(coAuthors[i++]) + 1;       
          bypass_symbol(&authors, ' ');    /** Clean any spaces in the end */ 
      }
      
     /* Add the list of authors into the social network */ 
     for(i = 0; i < total_authors; i++)
     {
       hash = getHash(coAuthors[i]);
       network[hash] = insert_avl(network[hash], 
                                    coAuthors, i,total_authors,INSERT_AUTHOR);
      
     }
     /* Free the memory occupied by the array of strings */
     free_array_of_strings(&coAuthors, total_authors);
 
}

/* This function finds the Tree on the hashtable with the biggest Height */
int get_max_hashTableTree_final_height(SocialNetworkT **rs){
    int biggest = 0;
    
    /* For each position of the hashtable we 
     * check the height of it AVL Tree */
    for(int i = 0; i < HASH_SIZE; i++) 
        biggest = max(biggest,get_final_height(rs[i]));
    
    return biggest;
}

/* This function will count the number of different Authors in the system */
int get_num_hashTable_distinct_authors(SocialNetworkT **rs){
    int count = 0;
    
    /* For each hashtable position it will count 
     * the number of element on the AVL Tree */
    for(int i = 0; i < HASH_SIZE; i++) 
        count += get_total_different_Authors(rs[i]);
    
    return count;
}

/* This functions counts the number of pairs authors 
 * that exists in the system */
int get_total_number_relations (SocialNetworkT **rs){
    int count = 0;
    
    for(int i = 0; i < HASH_SIZE; i++) 
        count += get_number_of_relations(rs[i]);
    
    return count;
}

/* This functions will return the biggest number 
 * of articles write between a pair of authors */
int get_biggest_number_article_between_pair(SocialNetworkT **rs){
    int biggest = 0;
    
    for(int i = 0; i < HASH_SIZE; i++) 
    {
        biggest =  max (biggest, max_pair_author_coAuthor(rs[i]));
    }
    
    return biggest;
}

/* This function returns the number of collisions on the hashtable */
int get_hastTable_total_colisions(SocialNetworkT **rs){
    int conta = 0;
    int total = get_num_hashTable_distinct_authors(rs);
    
    for(int i = 0; i < HASH_SIZE; i++)
    {
        if(rs[i]) conta++;
    }
    
    return total-conta;
}

/* Returns the number of CoAuthors for a given Author */
int get_hashTable_total_coAuthors(SocialNetworkT **rs,char *author){
    int hash = getHash(author);
    
    return (rs[hash]) ? get_author_total_coAuthors_tree(rs[hash], author) : 0;
}

/* Returns the number of articles wrote together by a pair of Authors */
int get_total_articles_between_two_authors(SocialNetworkT **rs, 
        char *author, char *coAuthor){
    
    int hash = getHash(author);
    return total_articles_with_this_coAuthor(rs[hash], author,coAuthor);
}


/**
 * Collects and save in R the biggest pairs of articles wrote
 * between two authors
 */
void collect_hashTable_biggest_pairs(ReportsS *R){
    
    
    int max = get_biggest_number_article_between_pair(R->redesocial);
    
    for(int i = 0; i < HASH_SIZE; i++){
        get_pair_with_N_weight(R->redesocial[i],max,&(R->pairs));
    }
    
}

/* Find and print the Top 'X' Authors with most coAuthors */
void prints_top_10_authors_with_most_coAuthors(SocialNetworkT **rs){
      
    RejectedS *top = NULL;
    
    for(int i = 0; i < HASH_SIZE; i++) 
        with_most_coAuthors(rs[i], &top);
    
    print_top_10_authors(top);
    free_rejected_list(top);
    top = NULL;
}

/* This function will put on the Authors Node 
 * the number of coAuthors that he/she have */
void prepare_tree(SocialNetworkT **rs){
      
    for(int i = 0; i < HASH_SIZE; i++) 
        prepare_tree_aux(rs[i]);
     
}

/* Set of Questions 1*/
void querys1(SocialNetworkT **social_network){
        
    int valor = get_biggest_number_article_between_pair(social_network);
    printf("Number of Collisions in the HashTable -> %d\n", 
            get_hastTable_total_colisions(social_network));
    
    printf("Height of the biggest tree -> %d\n", 
            get_max_hashTableTree_final_height(social_network));
    
    printf("The total number of authors in the network -> %d.\n",
            get_num_hashTable_distinct_authors(social_network));
    
    printf("Total of connections -> %d.\n",
            get_total_number_relations(social_network));
    
    printf("The highest number of authors that have wrote together -> %d\n",
            valor);
    
    printf("List of pars with + of %d Articles wrote together:\n",valor);
}

/* Set of Questions 2*/
void querys2(ReportsS *rede){
        
    char author [] = "Da Wang";
    char coAuthor[] = "Danilo Silva";
    
    //Josef Kittler e Maria Petrou: 8
    //Ali Tajer e Rui M. Castro: 2
    //Da Wang e Danilo Silva: 1
    
    
    //Fabio Roli: 25      
    //Jun Sato: 19
    //Li Meng: 3
    //Diogo Reis: 1
    
    
    int question1 = get_hashTable_total_coAuthors(rede->redesocial,author);
    int question2 = get_total_articles_between_two_authors(rede->redesocial,
            author,coAuthor);
    
    if(question1 >= 0) printf("1) The author %s have %d co-authors.\n",
            author,question1);
    else               printf("1) %s not found!\n",author);
    
    if(question2 >= 0)
    {
        printf("2) The authors %s and %s have %d articles together.\n",
                author,coAuthor,question2);
    }
    else               printf("2) %s not found!\n",author); 
    
    collect_hashTable_biggest_pairs(rede);
    rede->pairs = remove_pairs_repetitions(rede->pairs);
    print_pairs_authors(rede->pairs);
    free_pairsAuthors_list(rede->pairs);
    rede->pairs = NULL;
    prints_top_10_authors_with_most_coAuthors(rede->redesocial);
}

/* Making Questions to the social Network*/
void social_network_questions(ReportsS *rede){
    
      prepare_tree(rede->redesocial);
      querys1(rede->redesocial);
      querys2(rede);
}
