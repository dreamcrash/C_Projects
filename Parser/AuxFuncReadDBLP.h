/* 
 * File:   AuxFuncReadDBLP.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 *
 */

#ifndef AUXFUNCREADDBLP_H
#define	AUXFUNCREADDBLP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "DataTypes.h"
    
char *str_toLower                 (char *title);
void bypass_symbol                (char **article, char symbol);
Bool parser_int                   (char **article, int *number);
Bool read_line_from_file             (FILE *fp, char **buffer, Bool *flag);
Bool parser_authors               (char **article, int *autors, size_t *size);
Bool is_title_valid               (char **article);
Bool parser_magazine_info         (char **article);
Bool parser_num_magazine          (char **article,   int *number);
Bool parser_num_pages             (char **article,   int *num_pag);
Bool parser_year                  (char **article,   int *year);
Bool parser_conference_info       (char **article);

#ifdef	__cplusplus
}
#endif

#endif	/* AUXFUNCREADDBLP_H */

