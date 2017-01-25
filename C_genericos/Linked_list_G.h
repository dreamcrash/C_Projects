/* 
 * File:   Linked_list_G.h
 * Author: Bruno Medeiros
 */

#ifndef LINKED_LIST_G_H
#define LINKED_LIST_G_H

#ifdef __cplusplus
extern "C" {
#endif
   
    
typedef struct LINKED_LIST{
    
    void *data;
    struct LINKED_LIST *next;
    
}Linked_list_g;    

void print_linked_list                      (Linked_list_g *list, 
                                                void (*printf_data) (void *));

int insert_head_linked_list_g              (Linked_list_g **head, void *node);
int insert_end_linked_list_g               (Linked_list_g **head, void *node);
int insert_order_linked_list_g             (Linked_list_g **head, void *node,
                                                int (*compare) (void *, void *));

int delete_node                            (Linked_list_g **list, void *data ,
                                                void (*free_f) (void *),
                                                int  (*eq_f) (void *, void *));

void free_linked_list_g                     (Linked_list_g *list, 
                                                void (*free_data) (void *));

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_G_H */

