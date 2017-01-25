#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_list_G.h"
#include "Data_node.h"

/**                     Generic linked list Functions                   */


/**
 * Function to print a generic list
 * @param list          : The list to be printed
 * @param printf_data   : The function pointer to print the data
 */
void print_linked_list(Linked_list_g *list, void (*printf_data) (void *))
{
    
    while(list){
        
        printf_data(list->data);
        list = list->next;
    }
}

/**
 * Inserts a node in the head of a given list
 * @param list  : The list where the node will be inserted
 * @param node  : The node to be inserted
 * @return 1 if the node was successfully inserted, 0 otherwise
 */
int insert_head_linked_list_g(Linked_list_g **list, void *node)
{
    Linked_list_g *new = malloc(sizeof(*new));
    
    if(new){
        new->data = node;
        new->next = *list;
        *list = new;        // Update the head of the list
        return 1;
    }
    else   // Memory problems
        return 0;
}

/**
 * Inserts a node in the end of a given list
 * @param list  : The list where the node will be inserted
 * @param node  : The node to be inserted
 * @return 1 if the node was successfully inserted, 0 otherwise
 */
int insert_end_linked_list_g(Linked_list_g **list, void *node)
{
    if(*list){
        
        Linked_list_g *current = *list;
        
        // Find the last node
        while(current->next){
            current = current->next;
        }
        current->next = malloc(sizeof(*current->next));
        
        if(current->next){
            current->next->data = node;
            current->next->next = NULL;
            return 1;
        }
        else // Memory Problems
            return 0; 
    }
    else
    {   // Empty list
        return insert_head_linked_list_g(list, node);
    }
}
/**
 * Inserts a node in a given list according to a compare function
 * @param head      : The list where the node will be inserted
 * @param node      : The node to be inserted
 * @param compare   : The compare function user to compare the nodes
 * @return 1 if the node was successfully inserted, 0 otherwise
 */
int insert_order_linked_list_g(Linked_list_g **head, void *node,
                                int (*compare) (void *, void *))
{
    Linked_list_g *list = *head;
    
    if(list && !compare(node, list->data))
    {
        Linked_list_g *current = list;
        
        // Find the correct position
        // while there is elements and the condition is not satisfied
        while(current->next && !compare(node, current->next->data)){
            current = current->next;
        }
        
        // Either there is no more elements or the condition is satisfied
        Linked_list_g *new = malloc(sizeof(*new));
        
        if(new)
        {
            Linked_list_g *tmp = current->next;
            current->next = new;
            new->next = tmp;
            new->data = node;
            return 1;
        }
        else    // Memory problems
            return 0;
    }
    else{   // Empty list or the element should be inserted into the head
        return insert_head_linked_list_g(head, node);
    }
} 


/**
 * This function delete a node of the list. It assumes that lists
 * can have duplicates
 * @param list              : The linked list
 * @param data              : The data to be removed
 * @param free_function     : The function that allows data deletions
 * @param equal_function    : The function that compares two elements. Will be 
 * used to identify the element to be removed   
 * @return The linked list without the data to be removed
 */

int delete_node(Linked_list_g **head, void *data ,
                            void (*free_function) (void *),
                            int  (*equal_function) (void *, void *))
{
    Linked_list_g *list = *head;
    
    if(!list)
    {
       return 0; // if null list 
    }   
    else
    {
        // Check if the elements to be removed are in the head
        while(list && equal_function(list->data, data))
        {
            Linked_list_g *to_delete = list; 
            list = list->next;
            
            free_function(to_delete->data);
            free(to_delete);
        }
        //Update the head if so needed
        *head = list; 
        
        Linked_list_g *current = list, *previous = NULL; 
       
        // Check if the elements to be removed are in the tail 
        while(current)
        {   // element found
            if(equal_function(current->data, data))
            {
                Linked_list_g *to_delete = current;   
                
                // cut the link to the element to be deleted
                previous->next = to_delete->next; 
                free_function(to_delete->data);
                free(to_delete);
                current = previous; // set the current to the previous
                // so it can be update in the next lines.
            } 
            previous = current;
            current = current->next;
        }
        return 1;
    }
}

/**
 * Frees the memory occupied by a list
 * @param list          : The list to be freed
 * @param free_data     : A pointer to a function use to free the node within 
 * the list
 * 
 */
void free_linked_list_g(Linked_list_g *list, void (*free_data) (void *))
{
    
    Linked_list_g *tmp;
    
    while(list)
    {
        tmp = list;         // save the pointer the current element
        list = list->next;  // update pointer
            
        free_data(tmp->data);   // Free data in the current node
        free(tmp);              // Free the current node
    }
   
}




