#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_node.h"

/**
 * Creating a new node
 * @param id    : The id of the user
 * @param age   : The age of the user
 * @param name  : The Name of the user
 * @return A new created node or null in case of memory allocation problems
 */
Node *new_node(int id, int age, char *name){
    
    Node *new = malloc(sizeof(*new));
    
    if(new)
    {
        new->id = id;
        new->age = age;
        new->name = malloc(sizeof(new->name) * (strlen(name) + 1));
        
        if(new->name){
            
            strcpy(new->name,name);
            
            return new;
        }// Memory problems
        else
        {
            free(new);
            return NULL;
        }
    }
    else    // Memory problems
        return NULL;
}

/**
 * Prints a given node
 * @param data : A pointer to the Node
 */
void printf_node(void *data)
{
    
    Node *n = (Node *) data;
    
    printf("ID      : %d\n", n->id);
    printf("Name    : %s\n", n->name);
    printf("Age     : %d\n\n", n->age);
}

/**
 * 
 * @param data : Node to be freed
 */
void free_node (void *data)
{
    Node *node = (Node *) data;
    free(node->name);
    free(node);
}


/** Compare functions */
int is_id_x_smaller_than_y (void *x, void *y){
    
    Node *n1 = (Node *) x;
    Node *n2 = (Node *) y;
    
    return n1->id < n2->id;
}

int is_age_x_smaller_than_y (void *x, void *y){
    
    Node *n1 = (Node *) x;
    Node *n2 = (Node *) y;
    
    return n1->age < n2->age;
}

int is_name_x_smaller_than_y (void *x, void *y){
    
    Node *n1 = (Node *) x;
    Node *n2 = (Node *) y;
    
    return strcmp(n1->name, n2->name) < 0;
}

int is_equal_ids(void *x, void *y){
    
    Node *n1 = (Node *) x;
    int *id2 =  (int *) y;
    
    return n1->id == *id2;
}

int is_equal_ages(void *x, void *y){
    
    Node *n1 = (Node *) x;
    int *age2 = (int *) y;
    return n1->age == *age2;
}

int is_equal_names(void *x, void *y){
    
    Node *n1 = (Node *) x;
    char *string2 = (char *) y;
    
    return strcmp(n1->name, string2) == 0;
}