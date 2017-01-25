/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include "Linked_list_G.h"
#include "Data_node.h"


void test_linked_list(){
    
    Linked_list_g *list = NULL;
   
    
    insert_end_linked_list_g  (&list, new_node    (1, 31, "Bruno Medeiros"));
    insert_end_linked_list_g  (&list, new_node    (2, 30, "Old John"));
    insert_end_linked_list_g  (&list, new_node    (3, 30, "End Mate"));
    
    print_linked_list       (list, printf_node);
    free_linked_list_g      (list, free_node);
    
     Linked_list_g *list2 = NULL;
     Node *n1 = new_node (1, 27, "Bruno Medeiros");
     Node *n2 = new_node (2, 27, "Old John");
     Node *n3 = new_node (3, 27, "End Mate");
     Node *n4 = new_node (0, 27, "GOD Mate");
     Node *n5 = new_node (4, 27, "Carlos sa");
     
    printf("\n\n LIST 2 \n\n");
    insert_order_linked_list_g  (&list2, n1,is_age_x_smaller_than_y);
    insert_order_linked_list_g  (&list2, n2,is_age_x_smaller_than_y);
    insert_order_linked_list_g  (&list2, n3,is_age_x_smaller_than_y);
    insert_order_linked_list_g  (&list2, n4,is_age_x_smaller_than_y);
    insert_head_linked_list_g   (&list2, n5);
    
    print_linked_list       (list2, printf_node);
    printf("\n\n After DELETE \n\n\n");
    
    int age = 27;
    char *name = "Old John";
    
    delete_node(&list2, name, free_node, is_equal_names);
    delete_node(&list2, &age, free_node, is_equal_ages);
    
    print_linked_list       (list2, printf_node);
    free_linked_list_g      (list2, free_node);
}




int main(void) {
    test_linked_list();
    return 0;
}

