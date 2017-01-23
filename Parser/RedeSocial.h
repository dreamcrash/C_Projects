/* 
 * File:   RedeSocial.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef REDESOCIAL_H
#define	REDESOCIAL_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "DataTypes.h"

void add_authors  (SocialNetworkT **rs, char *autors, int numberOfAuthors);    
int get_max_hashTableTree_final_height      (SocialNetworkT **rs);
int get_num_hashTable_distinct_authors      (SocialNetworkT **rs);
int get_total_number_relations              (SocialNetworkT **rs);
int get_biggest_number_article_between_pair (SocialNetworkT **rs);
int get_hastTable_total_colisions           (SocialNetworkT **rs);
int get_hashTable_total_coAuthors           (SocialNetworkT **rs, char *author);
int get_total_articles_between_two_authors  (SocialNetworkT **rs, char *author, 
                                                    char *coAuthor);
void collect_hashTable_biggest_pairs            (ReportsS *R);
void prints_top_10_authors_with_most_coAuthors  (SocialNetworkT **rs);
void prepare_tree                               (SocialNetworkT **rs);
void querys1                                    (SocialNetworkT **redesocial);
void querys2                                    (ReportsS *rede);
void social_network_questions                   (ReportsS *reports);



#ifdef	__cplusplus
}
#endif

#endif	/* REDESOCIAL_H */

