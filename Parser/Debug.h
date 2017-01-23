/* 
 * File:   Debug.h
 * Author: Bruno Medeiros.
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define IDS_SIZE 20000
    
    typedef struct Logs{
        char *name;
        int  *ids;
        struct Logs *next;
    }LogsS;
    
    

LogsS *add_logs                          (char *name, LogsS *list);
Bool validate_parser_revista_debug       (char *article,ReportsS **reports, 
                                              int numberOfPagesAllowed);
void read_logs                           (char *fileName, LogsS **list);
void compare_list                        (LogsS *list1,LogsS *list2);
void read_stats                          (char *file1, char *file2);
void debug_rejected                      ();


#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

