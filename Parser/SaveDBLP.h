/* 
 * File:   SaveDBLP.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef SAVEDBLP_H
#define	SAVEDBLP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "DataTypes.h"
Bool save_file_percentage_articles_year (ReportsS *reports, int data, FILE *fp);
Bool save_file_statistics               (ReportsS *reports);
Bool save_file_rejected                 (ReportsS *reports);
void save_file_total_articles_per_author(ReportsS *reports, FILE *fp);
void save_file_per_year_total_authors   (ReportsS *reports, FILE *fp);
Bool save_file_total_articles_dates     (ReportsS *reports, FILE *fp);
Bool save_file_articles_authors         (ReportsS *reports, FILE *fp);
Bool save_report_G                      (ReportsS *reports);
void generated_reports                  (ReportsS *reports);
#ifdef	__cplusplus
}
#endif

#endif	/* SAVEDBLP_H */

