/* 
 * File:   Data_node.h
 * Author: Bruno Medeiros
 */

#ifndef DATA_NODE_H
#define DATA_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NODE{
    
    int id;
    int age;
    char *name;
}Node;    
    
    
Node *new_node                              (int id, int age, char *name);
void printf_node                            (void *data);
void free_node                              (void *data);
int is_id_x_smaller_than_y                  (void *d1, void *d2);
int is_age_x_smaller_than_y                 (void *x, void *y);
int is_name_x_smaller_than_y                (void *x, void *y);
int is_equal_ids                            (void *x, void *y);
int is_equal_ages                           (void *x, void *y);
int is_equal_names                          (void *x, void *y);




#ifdef __cplusplus
}
#endif

#endif /* DATA_NODE_H */

