/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedeSocial.h"
#include "printStdio.h"
#include "DataTypes.h"

/**
 * Function to print the basic statics
 * @param stats : The states collected
 */
void print_statistics(StatisticsS *stats){
    printf("Basic Statistics\n");
    printf("%d Entries\n",stats->entries);
    printf("%d Rejected\n",stats->rejected);
    printf("%d Articles\n",stats->articles);
    printf("\t%d in Journal\n",stats->revista);
    printf("\t%d in conference\n",stats->conferencia);
}

void print_rejected(RejectedS *list){
    
    printf("Lista Rejeitadas\n");
    while(list)
    {
        
        printf("%s %d\n",list->name,list->total_rejections);
        list = list->next;
    }
    
}

void print_hash(ReportsS *reports){
        int year;
        int numYears = reports->finalYear - reports->initialYear + 1;
    
        for(int i = 0; i < numYears; i++)
        {
            if(reports->hashtable[i])
            {
                printf("Acumulated %d\n",reports->hashtable[i]->accumulated);
                printf("Total Articles %d\n",reports->hashtable[i]->total_articles);
                printf("\"ano\",\"#autores\",\"#artigos\n");
                year = reports->initialYear + i;
                    
                for(int j = 0; j < reports->hashtable[i]->artPerAutSize; j++)
                {
                    if(reports->hashtable[i]->artPerAut[j])
                    {
                        printf("\"%d\",\"%d\",\"%d\"\n",year, j,
                           reports->hashtable[i]->artPerAut[j]);
                    }
                }
            } 
        } 
}

void print_total_per_author(ReportsS *reports){

    int total = 0;
    int numYear = reports->finalYear - reports->initialYear + 1;
        
    printf("\"#autores\",\"#artigos\"\n");
    
    for(int i = 1; i < reports->maxNumberAuthorsFinded; i++)
    {
        for(int j = 0; j < numYear;j++)
        {
            if(reports->hashtable[j] && reports->hashtable[j]->artPerAutSize > i) 
                total += reports->hashtable[j]->artPerAut[i];
               
        }
        if(total > 0) printf("\"%d\",\"%d\"\n",i,total); 
           
         total = 0;
   }
}

void print_report(ReportsS *reports) {
    
     print_statistics(reports->statistics);
     print_rejected(reports->rejectedArticles);
     print_hash(reports);
     print_total_per_author(reports);
}

void print_social_network(SocialNetworkT *tree){
    
    if(tree)
    {
        printf("%s\n",tree->name);
        print_social_network(tree->left);
        print_social_network(tree->right);
    }
}

void print_pairs_authors(PairsAuthorsS *pairs){
     
    while(pairs)
    {
        printf("(%s,%s) => %d. \n",pairs->author->name, pairs->coAuthor->name, 
                pairs->coAuthor->total);
        pairs = pairs->next;
        
    }
}

void print_top_10_authors(RejectedS *list){
    
    int count = 0;
    int anterior = 0;
    int acumulado = 0;
    
    printf("The 10 top Authors with most number of CoAuthors.\n");
    while(list)
    {
        if(count < 10 && anterior != list->total_rejections)
        { 
            count = count + 1 + acumulado;
            acumulado = 0;
        }
        else acumulado++;
        printf("%d > %s %d\n",count,list->name,list->total_rejections);
        
        
        anterior = list->total_rejections;
        list = list->next;
    }
}
