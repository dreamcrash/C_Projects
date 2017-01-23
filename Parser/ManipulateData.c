/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ManipulateData.h"
#include "AuxFuncReadDBLP.h"
#include "DataTypes.h"
#include "ReadDBLP.h"
#include "SaveDBLP.h"
#include "printStdio.h"


/*  Creates an Array of Strings */
char **new_array_strings(int total_words, int words_size){
    
    char **aux = malloc(total_words * sizeof(char*));
    
    if(aux)
    {
        int no_nulls = 1;
        for(int i = 0; i < total_words && no_nulls; i++)
        {
            aux[i] = malloc(words_size+1);
            if(!aux[i]) no_nulls = 0;
        }
        
        if(no_nulls) return aux;
    }
    
    // Memory Problems
    return NULL;
}


/** Verify in a given word is on the list */
Bool exist_word(char *title){
    
    return(
            strstr(title,"editorial")    || strstr(title,"preface") ||
            strstr(title,"errata")       || strstr(title,"obituary")||
            strstr(title,"in memory of") || strstr(title,"isbn")    
          );
}

/** Add an conference and the number of their rejected articles*/
RejectedS *add_rejected (RejectedS *list, char *name, int number){
    
        RejectedS *aux = NULL;
        
        if(!list)
        {
            aux = malloc(sizeof(RejectedS));
            if(aux)
            {
                aux->name = malloc(strlen(name) + 1);
                strcpy(aux->name,name);
                aux->total_rejections = number;
                aux->next = NULL;
                return aux;
            }
            else // Memory Problems
                return NULL;
        }
        else
            list->next = add_rejected(list->next,name,number);
        
        return list;
}

/** Initialize the statistics structure */
void init_statistics(StatisticsS *stats){
    
    stats->articles = 0;
    stats->conferencia = 0;
    stats->entries = 0;
    stats->rejected = 0;
    stats->revista = 0;
    stats->tmp_rejected = 0;
}


/** Create an array of years*/
YearArtS **create_array_year_articles(int size){
    
    YearArtS **arrayYearArticles = malloc(size * sizeof(YearArtS *));
    
    if(arrayYearArticles)
    {
        for(int i = 0; i < size; i++)
        {
            arrayYearArticles[i] = NULL; 
        }
        return arrayYearArticles;
    }
    else // Memory problems
        return NULL;
}

/* Create the HashTable of Social Net.*/
SocialNetworkT **create_hashTable_social_network(){
    
    SocialNetworkT **redeSocial = malloc(HASH_SIZE * sizeof(SocialNetworkT *));
    
    if(redeSocial)
    {
        for(int i = 0; i < HASH_SIZE; i++)
        {
            redeSocial[i] = NULL;
        }
        return redeSocial;
    }
    else // Memory problems
        return NULL;
}

/** Create and initializes the Report structure */
ReportsS *create_reports(){
    
    ReportsS *reports = malloc(sizeof(*reports));
    
    if(reports){
       
        // Set to default the max number of authors find it in on article
        reports->maxNumberAuthorsFinded = MAX_AUTHORS; 
        // Set to default the initial year
        reports->initialYear = INITIAL_YEAR;     
        // Set to default the final year     
        reports->finalYear   = FINAL_YEAR;    
        // Create the structure to hold the D.txt statistics
        reports->statistics = malloc(sizeof(StatisticsS)); 
        
        if(reports->statistics)
        {
            // Read the files names
            reports->files = malloc(sizeof(FilesNames));  
            if(reports->files)
            {
                reports->files->D_txt       = NULL;
                reports->files->E_txt       = NULL;
                reports->files->G_txt       = NULL;
                reports->files->data3       = NULL;
                reports->files->data4       = NULL;
                reports->files->directory   = NULL;
                reports->files->list        = NULL;
                reports->pairs = NULL;
                // Set to NULL the linked list of conferences/number 
                //  of rejected articles => E.txt 
                reports->rejectedArticles = NULL;                                
                reports->redesocial = create_hashTable_social_network();
                
                // Create the array of years
                reports->hashtable = 
                   create_array_year_articles(FINAL_YEAR - INITIAL_YEAR + 1); 

                // Initialize the statistics structure               
               init_statistics(reports->statistics);  
            }
            return reports;
        }
        
    }
    // Memory Problems
    return NULL;   
}

/** Create an array to hold the number of 
 * articles per authors (each array position means the number of authors) 
 */
YearArtS *create_article_num_authors_array(){
    
    YearArtS *article_num_autors = malloc(sizeof(YearArtS)); 
    
    if(article_num_autors)
    {
        article_num_autors->total_articles = 0;
        article_num_autors->artPerAutSize = MAX_AUTHORS;
        article_num_autors->artPerAut = malloc(sizeof(int) * MAX_AUTHORS);

        /** Initialize positions*/
        for(int i = 0; i < MAX_AUTHORS; i++)
            article_num_autors->artPerAut[i] = 0; 
        
        return article_num_autors;
    }
    else // Memory problems
        return NULL;
}

/** If there is need for more space 
 * (and article with an higher number of authors)
 */
void extend_array_articlesNumAuthors_space(ReportsS *reports, int pos, 
        int numAuthors){

    int additionalSpace = numAuthors + 3;
    
    YearArtS *year_article = reports->hashtable[pos];
 
    /** Extend space */
    year_article->artPerAut = realloc(year_article->artPerAut, 
                                        additionalSpace * sizeof(int));  
        
    /** Initialize just the new position */
    for(int i = year_article->artPerAutSize; i < additionalSpace; i++) 
        year_article->artPerAut[i] = 0;
           
    year_article->artPerAutSize = additionalSpace; /** Save the new size */
        
    /** Test if this was the biggest number of authors find it until now*/
    if (reports->maxNumberAuthorsFinded < additionalSpace) 
        reports->maxNumberAuthorsFinded = additionalSpace;
}


size_t size_of_hashTable(ReportsS **reports){
    
    ReportsS *ptr_reports = *reports;
    
    int totalYears = ptr_reports->finalYear - ptr_reports->initialYear + 1;
    size_t mySize = 0;
    
    for(int i = 0; i < totalYears; i++)
    {
        if(ptr_reports->hashtable[i])
        {
            mySize += sizeof(YearArtS);
            mySize += sizeof(int) *ptr_reports->hashtable[i]->artPerAutSize;
        }
        else    
            mySize += sizeof(YearArtS *);
    }
    return mySize;
}

YearArtS **extend_left_buffer(ReportsS *reports, short year){

    int newInitialYear = year - 20;
    int oldNumYears = reports->finalYear - reports->initialYear + 1;
    int newNumYears = reports->finalYear - newInitialYear + 1;
    int oldBeginPosition = newNumYears - oldNumYears;
    
    YearArtS **oldHashTable_ptr = reports->hashtable;
    
    YearArtS **newHashTable = malloc((newNumYears + 1) * sizeof(YearArtS *));
    
    if(newHashTable)
    {
        int j = 0;
        
        // Fill with NULL the new declared pointers
        for(; j < oldBeginPosition; j++)  
            newHashTable[j] = NULL;         

        // Set the new pointers to the old memory positions
        for(int i = 0; j < newNumYears; i++, j++)
            newHashTable[j] = reports->hashtable[i]; 
        
        
        // Update the new initial year
        reports->initialYear = newInitialYear;     
        
        // Free old hashtable
        free(oldHashTable_ptr);
        
        return newHashTable;
    }
    else // Memory problems
        return NULL;
}

YearArtS **extend_right_buffer(ReportsS *reports, short year){

    int newFinalYear = year + 20;
    int newNumYears = newFinalYear - reports->initialYear + 1;
    int oldFinalPos = reports->finalYear - reports->initialYear;
    int totalYears = oldFinalPos + newNumYears;
    
    YearArtS **newHashTable = realloc(reports->hashtable, 
            ((totalYears + 1) * sizeof(YearArtS *)));
    
    if(newHashTable)
    {
        /** Fill with NULL the new declared pointers */
       for(int j = oldFinalPos; j < newNumYears; j++)  
           newHashTable[j] = NULL;                

       reports->finalYear = newFinalYear;
       return newHashTable;
    }
    else // Memory problems
        return NULL;
}


/** Save the number of articles find for a given year 
 * and a given number of authors*/
void add_year_articles_num_authors(
        ReportsS *reports, short year, int numAuthors, int numArticles)
{
    
    int pos = year - reports->initialYear;
    
    // The year that to insert is inferior to the default year
    if(year < reports->initialYear)
    { 
        reports->hashtable = extend_left_buffer(reports, year);         
        pos = year - reports->initialYear;
    }
    
    // The year that to insert is superior to the default year
    if(year > reports->finalYear)
    {
       reports->hashtable = extend_right_buffer(reports,year);
    }
    
    
    // This entry was not yet added
    if(!(reports->hashtable[pos]))
    {
        reports->hashtable[pos] = create_article_num_authors_array();   
    }
    
    // Incremental the total of articles already find this year
    reports->hashtable[pos]->total_articles += numArticles;     
    
    // The array of articles/authors must be extended
    if(numAuthors >= reports->hashtable[pos]->artPerAutSize)
    {  
        extend_array_articlesNumAuthors_space(reports, pos, numAuthors);
    }
    
    reports->hashtable[pos]->artPerAut[numAuthors] += numArticles;
    
}


void calculate_accumulate(ReportsS *reports){
   
    int acumulado = 0;
    int numYear = reports->finalYear - reports->initialYear + 1; 
    
    for(int i = 0; i < numYear; i++)
    {
        if(reports->hashtable[i])    /** If there is data for this year */
        {
            reports->hashtable[i]->accumulated = 
                    acumulado + reports->hashtable[i]->total_articles;
            
            acumulado += reports->hashtable[i]->total_articles;
        }
    }
}


/** Calculates the number of articles find it for between two different dates*/
Bool total_articles_between_two_dates(ReportsS *reports, int dataI, int dataF, 
        int *results){
     
    int posI =   dataI - reports->initialYear;
    int posF =   dataF - reports->initialYear;
    
    if(posI >= 0 && posF >= 0 && posI <= posF)
    {
        /** Start in a valid year inside the given range */
        while(posI <= posF && reports->hashtable[posI] == NULL) 
            posI++;
        
         /** End in a valid year inside the given range */
        while(posF >= posI && reports->hashtable[posF] == NULL) 
            posF--;              
        
        if(posI >= 0 && posF >= 0 && posI <= posF)
        {
            *results =  reports->hashtable[posF]->accumulated - 
                        reports->hashtable[posI]->accumulated + 
                        reports->hashtable[posI]->total_articles;
            return TRUE;
        }
    }
    return FALSE;
}

/** Holds the directories were the reports should be save       */
void save_file_names(FilesNames *names, char *directory){
    
    names->list  = malloc(FILE_NAME_SIZE);
    names->D_txt = malloc(FILE_NAME_SIZE);
    names->E_txt = malloc(FILE_NAME_SIZE);
    names->G_txt = malloc(FILE_NAME_SIZE);
    names->data3 = malloc(FILE_NAME_SIZE);
    names->data4 = malloc(FILE_NAME_SIZE);
    names->directory = malloc(FILE_NAME_SIZE);
    strcpy(names->list,directory);
    strcat(names->list,LIST_NAME);
    strcpy(names->D_txt,directory);
    strcat(names->D_txt,REPORT_D);
    strcpy(names->E_txt,directory);
    strcat(names->E_txt,REPORT_E);
    strcpy(names->G_txt,directory);
    strcat(names->G_txt,REPORT_G);
    strcpy(names->data3,directory);
    strcat(names->data3,YEAR_TO_YEAR_NAME);
    strcpy(names->data4,directory);
    strcat(names->data4,YEAR);
    strcpy(names->directory,directory);
}


/* Function to add a Pair of Authors to a linked list of pars of authors*/
PairsAuthorsS *insert_pair_authors(     SocialNetworkT *A, 
                                        SocialNetworkT *CA, 
                                        PairsAuthorsS  *L){
    
    PairsAuthorsS *aux = malloc(sizeof(PairsAuthorsS));
    
    if(aux)
    {
        aux->author   = A;
        aux->coAuthor = CA;
        aux->next = L;
        return aux;
    }
    else // Memory problems
        return NULL;
}


PairsAuthorsS *remove_pairs_repetitions_aux(PairsAuthorsS *listPairs, 
        SocialNetworkT *A, SocialNetworkT *CA){
    
    PairsAuthorsS *aux = NULL;
    
    if(!listPairs) return NULL;
    else if(strcmp(listPairs->author->name,CA->name) == 0 && 
            strcmp(listPairs->coAuthor->name,A->name) == 0)
    {
        aux = listPairs->next;
        free(listPairs);
        return aux;
    }
    else listPairs->next = remove_pairs_repetitions_aux(listPairs->next,A,CA);
    
    return listPairs;
}


PairsAuthorsS *remove_pairs_repetitions(PairsAuthorsS *L){
    
    if(L)
    {
        L = remove_pairs_repetitions_aux(L,L->author,L->coAuthor);
        L->next = remove_pairs_repetitions(L->next);
    }
    return L;  
}

RejectedS *insert_top_list(RejectedS *top, SocialNetworkT *T, int count)
{
    /*  Where you read total_rejections, is in fact the total of coAuthors, 
     * I used this data type because I was to lazy to do another one 
     * specifically for this task
     */
    
    RejectedS *aux = NULL;
   
    /* Ordering from the biggest to the smallest */
    if(!top || T->total > top->total_rejections) 
    {
        aux = malloc(sizeof(RejectedS));
        
        if(aux)
        {
            aux->name = malloc(strlen(T->name) + 1);
            strcpy(aux->name,T->name);
            aux->total_rejections = T->total;

            aux->next = top;
            return aux;
        } 
        else // Memory problems
            return NULL;
    }
    else 
        top->next = insert_top_list(top->next,T, count+1);
    
    return top;
}

RejectedS *clear_top(RejectedS *T, int count){
    
    RejectedS *aux = NULL;
    if(!T) return T;
    
    if(count >= TOP)
    {
        if(T->next && T->total_rejections == T->next->total_rejections)
           T->next = clear_top(T->next,count+1);
        else
        {
            aux = T;
            free_rejected_list(T->next);
            T->next = NULL;
            return aux;
        }
    }
    else  
        T->next = clear_top(T->next,count+1);
    
    return T;
}



/** -------------------------- > Free Memory functions < --------- */

void free_pairsAuthors_list (PairsAuthorsS *list){
    
    if(list)
    {
        PairsAuthorsS *head = list;
        
        while(list)
        {
            list = list->next;
            free(head);
            head = list;
        }
    }
}

void free_rejected_list(RejectedS *list){
    
    if(list)
    {
        RejectedS *head = list;
        while(list)
        {
            list = list->next;
            free(head->name);
            free(head);
            head = list;
        }
    }
    
}

void free_hastTable(ReportsS *reports){
    
    int totalYears = reports->finalYear - reports->initialYear + 1;
    
    for(int i = 0; i < totalYears; i++)
    {
        if(reports->hashtable[i])
        {
            free(reports->hashtable[i]->artPerAut);
            free(reports->hashtable[i]);
        }
    }
    
    free(reports->hashtable);
}

void free_tree_coAuthors(SocialNetworkT *T){
    
    if(T)
    {
        free_tree_coAuthors(T->left);
        free_tree_coAuthors(T->right);
        free(T->name);
        free(T);
    }
}

void free_tree_social_network(SocialNetworkT *social_network){
    
    if(social_network)
    {
        free_tree_social_network    (social_network->left);
        free_tree_social_network    (social_network->right);
        free_tree_coAuthors         (social_network->co_authors);
        free                        (social_network->name);
        free                        (social_network);
    }
}

void free_array_tree_social_network(SocialNetworkT **social_network){
    
    for(int i = 0; i < HASH_SIZE; i++) 
        free_tree_social_network(social_network[i]);
    
    free(social_network);
}

void free_file_list(FilesNames *files){
    
    free(files->D_txt);
    free(files->E_txt);
    free(files->G_txt);
    free(files->data3);
    free(files->data4);
    free(files->directory);
    free(files->list);
    free(files);
}

void free_Reports(ReportsS *reports){
    
    free                            (reports->statistics);
    free_file_list                  (reports->files);
    free_pairsAuthors_list          (reports->pairs);
    free_rejected_list              (reports->rejectedArticles);
    free_array_tree_social_network  (reports->redesocial);
    free_hastTable                  (reports);
    free                            (reports);
}

void free_array_of_strings(char ***matrix, int size){
    
    for(int i = 0; i < size; i++) 
        free((*matrix)[i]);
    
    free(*matrix); 
    
    *matrix = NULL;
}

