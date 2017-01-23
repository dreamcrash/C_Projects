/* 
 * File:   ReadDBLP.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef READDBLP_H
#define	READDBLP_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "DataTypes.h" 

Bool read_line_from_file        (FILE *fp, char **buffer, Bool *flag);
Bool validate_parser_magazine   (char *article,ReportsS *r,int numPagesAllowed);
Bool validate_parser_conference (char *article,ReportsS *r, int pagesLim);
Bool read_bibliography          (char *file, ReportsS *r, int pagesLim, 
                                    Bool (*parser) (char *,ReportsS *,  int));
Bool read_list_conferences      (ReportsS *reports);


#ifdef	__cplusplus
}
#endif

#endif	/* READDBLP_H */

