/* 
 * File:   AVLTree.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef AVLTREE_H
#define	AVLTREE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "DataTypes.h"
#define INSERT_AUTHOR 0
#define INSERT_COAUTHOR 1
    
int max                                     (int x, int y);
int height                                  (SocialNetworkT *tree);
SocialNetworkT *insert_co_authors           (SocialNetworkT *T,char **coAuthors, 
                                                int pos, int total_authors);

SocialNetworkT *single_rotate_left          (SocialNetworkT *K2);
SocialNetworkT *single_rotate_right         (SocialNetworkT *K1);
SocialNetworkT *double_rotate_left          (SocialNetworkT *K3);
SocialNetworkT *double_rotate_right         (SocialNetworkT *K1 );
SocialNetworkT *new_author_node             (char **authors, int pos, 
                                                        int total_authors);

SocialNetworkT *new_co_authors_node         (char **authors, int pos);
SocialNetworkT *insert_avl                  (SocialNetworkT *T, char **authors, 
                                                int pos, int total_authors, 
                                                int flag);

int get_author_total_coAuthors_tree         (SocialNetworkT *T, char *author);
int total_articles_with_this_coAuthor       (SocialNetworkT *T, char *autor, 
                                                char *coauthor);

int get_total_different_Authors             (SocialNetworkT *tree);
int numOfDistinctinsert_co_authors          (SocialNetworkT *tree);
int get_number_of_relations                 (SocialNetworkT *tree);
int max_pair_author_coAuthor_aux            (SocialNetworkT *tree);
int max_pair_author_coAuthor                (SocialNetworkT *tree);
int get_final_height                        (SocialNetworkT *tree);
void get_coAuthors_with_N_weight            (SocialNetworkT *autor, 
                                                SocialNetworkT *coTree, int N, 
                                                PairsAuthorsS **listPairs);

int get_total_coAuthors                     (SocialNetworkT *coTree);
void get_pair_with_N_weight                 (SocialNetworkT *Tree,int N, 
                                                PairsAuthorsS **lp);
void with_most_coAuthors                    (SocialNetworkT *T, 
                                                RejectedS **top);
void prepare_tree_aux                       (SocialNetworkT *T);

#ifdef	__cplusplus
}
#endif

#endif	/* AVLTREE_H */

