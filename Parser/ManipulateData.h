/* 
 * File:   ManipulateData.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef MANIPULATEDATA_H
#define	MANIPULATEDATA_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "DataTypes.h"

char **new_array_strings                (int rows, int cols);  
Bool exist_word                         (char *title);
RejectedS *add_rejected                 (RejectedS *list,char *name, int num);
void init_statistics                            (StatisticsS *stats);
YearArtS **create_array_year_articles           (int size);
SocialNetworkT **create_hashTable_social_network();
ReportsS *create_reports                        ();
YearArtS *create_article_num_authors_array      ();
void extend_array_articlesNumAuthors_space      (ReportsS *reports, int pos, 
                                                    int numAuthors);

size_t size_of_hashTable                (ReportsS **reports);
YearArtS ** extend_left_buffer          (ReportsS *reports, short year);
YearArtS **extend_right_buffer          (ReportsS *reports, short year);

void add_year_articles_num_authors      (ReportsS *reports,   short year, 
                                              int numAuthors, 
                                              int numArticles);
void calculate_accumulate               (ReportsS *reports);
Bool total_articles_between_two_dates   (ReportsS *reports, 
                                            int dataI, int dataF, int *result);
void save_file_names                    (FilesNames *names, char *directory);

PairsAuthorsS *remove_pairs_repetitions_aux (   PairsAuthorsS *listPairs, 
                                                SocialNetworkT *A, 
                                                SocialNetworkT *CA);
PairsAuthorsS *remove_pairs_repetitions (PairsAuthorsS *L);
RejectedS *insert_top_list              (RejectedS *top, SocialNetworkT *T, 
                                            int count);

RejectedS *clear_top                    (RejectedS *T, int count);
PairsAuthorsS *insert_pair_authors      (SocialNetworkT *A, SocialNetworkT *CA,
                                            PairsAuthorsS *L);
void free_pairsAuthors_list             (PairsAuthorsS *list);
void free_rejected_list                 (RejectedS *list);
void free_hastTable                     (ReportsS *reports);
void free_tree_coAuthors                (SocialNetworkT *T);
void free_tree_social_network           (SocialNetworkT *redeSocial);
void free_array_tree_social_network     (SocialNetworkT **reports);
void free_file_list                     (FilesNames *files);
void free_Reports                       (ReportsS *reports);
void free_array_of_strings                 (char ***matrix, int size);











#ifdef	__cplusplus
}
#endif

#endif	/* MANIPULATEDATA_H */

