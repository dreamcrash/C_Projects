/* 
 * File:   printStdio.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef PRINTSTDIO_H
#define	PRINTSTDIO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "DataTypes.h"
    
void print_statistics            (StatisticsS *stats);
void print_rejected              (RejectedS *list);
void print_hash                  (ReportsS *reports);
void print_total_per_author         (ReportsS *reports);
void print_report                (ReportsS *reports);
void print_social_network            (SocialNetworkT *tree);
void print_pairs_authors          (PairsAuthorsS *pairs);
void print_top_10_authors          (RejectedS *list);


#ifdef	__cplusplus
}
#endif

#endif	/* PRINTSTDIO_H */

