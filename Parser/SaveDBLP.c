/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printStdio.h"
#include "SaveDBLP.h"
#include "ManipulateData.h"
#include "DataTypes.h"
#include "RedeSocial.h"



/** Calculates the percentage of articles for a given number of */
Bool save_file_percentage_articles_year(ReportsS *reports, int year, FILE *fp){
    
    float percentagem;
    int pos =  year - reports->initialYear;
    
    if(pos >= 0 && reports->hashtable[pos])                                                  /** If there is a valid position with data */
    {   
        fprintf(fp,"\"ano\",\"#autores\",\"percentagem\"\n");                                   /** Print the title on file*/
        for(int i = 1; i < reports->hashtable[pos]->artPerAutSize; i++)                          /** For all the number of authors */
        {
            if(reports->hashtable[pos]->artPerAut[i] > 0)                                    /** That have articles */
            {
               percentagem = ((reports->hashtable[pos]->artPerAut[i] * 1.0) /                /** Lets calculate their percentage */
                             ((reports->hashtable[pos]->total_articles) * 1.0)) 
                                * 100.0;
                
             fprintf(fp,"\"%d\",\"%d\",\"%.2f\"\n",year,i,percentagem);                       /** Print the values on file */
            }
        }
        return TRUE;
    }
    return FALSE;
}

/** Save on file the Report D*/
Bool save_file_statistics(ReportsS *reports){
    
    FILE *fp;

    if((fp=fopen(reports->files->D_txt, "wb")))
    {
        fprintf(fp,"Estatistica basica\n------------------\n");
        fprintf(fp,"%d entradas\n",reports->statistics->entries);
        fprintf(fp,"%d rejeitadas\n",reports->statistics->rejected);
        fprintf(fp,"%d artigos\n",reports->statistics->articles);
        fprintf(fp,"  %d em revista\n",reports->statistics->revista);
        fprintf(fp,"  %d em conferencia\n",reports->statistics->conferencia);
        fclose(fp);
        
        return TRUE;
    }
    return FALSE;
}


/** Save on file the Report E*/
Bool save_file_rejected(ReportsS *reports){
    
   FILE *fp;
   RejectedS *list = reports->rejectedArticles;

    if((fp=fopen(reports->files->E_txt, "wb")))
    {
        fprintf(fp,"Lista Rejeitadas\n----------------\n");
        
        while(list)
        {
             fprintf(fp,"%s %d\n",list->name,list->total_rejections);
             list = list->next;
        }
        fclose(fp);
        return TRUE;
    }
   fclose(fp);
   return FALSE;
}

/** Save on file the total Number of articles per number of authors*/
void save_file_total_articles_per_author(ReportsS *reports, FILE *fp)
{
          int total = 0;
          int numYear = reports->finalYear - reports->initialYear + 1;
        
        fprintf(fp,"\"#autores\",\"#artigos\"\n");
    
        for(int i = 1; i < reports->maxNumberAuthorsFinded; i++)
        {
            for(int j = 0; j < numYear;j++)
            {
                if(reports->hashtable[j] && 
                        reports->hashtable[j]->artPerAutSize > i) 
                    total += reports->hashtable[j]->artPerAut[i];
               
            }
            if(total > 0) fprintf(fp,"\"%d\",\"%d\"\n",i,total); 
           
            total = 0;
        }
}

/** Save on file for each year the number of articles per number of authors*/
void save_file_per_year_total_authors(ReportsS *reports, FILE *fp){

    int ano;
    int numYear = reports->finalYear - reports->initialYear + 1;
    
    fprintf(fp,"\"ano\",\"#autores\",\"#artigos\"\n");
    
    for(int i = 0; i < numYear; i++)              
    {
        if(reports->hashtable[i]) // If the actual year have saved data
        {
            ano = reports->initialYear + i;  
                
            for(int j = 0; j < reports->hashtable[i]->artPerAutSize; j++)                                /** For all number of authors find */
            {
                // Print this data on file 
                if(reports->hashtable[i]->artPerAut[j])                                              /** If there is data for the actual number of authors */
                   fprintf(fp,"\"%d\",\"%d\",\"%d\"\n",ano, j,
                           reports->hashtable[i]->artPerAut[j]);   
                

            }
        }
   }
}

/** Save on file the number of articles find for a given temporal range */
Bool save_file_total_articles_dates(ReportsS *reports, FILE *file){
    
    FILE *fp = NULL;            // Declare point to file.
    char buffer[STRING_SIZE];   // Buffer to hold the read lines
    int dataI,dataF,result = 0;
    char symbol;
    
    fp = fopen(reports->files->data3, "r"); 
   
    if(fp) // No error reading file
    {
        // While the file have lines to read
       fprintf(file,"\"intervalo\",\"#artigos\"\n"); 
       do                                                                             
       {
           if(fscanf(fp,"%[^\n]",buffer) > 0)    // Read a line                                 
            {
               /** Reads string with the format xxxx-yyyy, 'x' & 'y' are digits. 
                * If the string do not follow this   
                * format a black hole will appear somewhere on the universe */   
                sscanf(buffer,"%d %c %d",&dataI,&symbol,&dataF);                      
                
                total_articles_between_two_dates(reports,dataI, dataF, &result);
                fprintf(file,"\"%d-%d\",\"%d\"\n",dataI,dataF,result);
            }
            
       } while(fgetc(fp) != EOF);         
       
       fclose(fp);
       return TRUE; /** File was read with success */
    }             
    return FALSE; /** It was not possible to read the file */
}
/** Save on file percentage of the number of Articles 
 * per number of authors for a given year*/

Bool save_file_articles_authors(ReportsS *reports, FILE *file){
    
    FILE *fp = NULL;                                                              
    char buffer[STRING_SIZE]; // Buffer to hold the read lines
    int year;
    
    fp = fopen(reports->files->data4, "r");                                       
   
    if(fp)    // No error reading file                                                              
    {    
       do                                                                  
       {    // While the file have lines to read      
            if(fscanf(fp,"%[^\n]",buffer) > 0)  // Read a line
            {
                sscanf(buffer,"%d",&year); 
                save_file_percentage_articles_year(reports, year,file);
            }
            
       } while(fgetc(fp) != EOF);         

       fclose(fp);
       return TRUE;    // File was read with success                                                         
    }
    fclose(fp);
    return FALSE;  // It was not possible to read the file                                                           
}

/** Save all the information necessary to the Report G*/
Bool save_report_G(ReportsS *reports){
    
   FILE *fp;

    if((fp=fopen(reports->files->G_txt, "wb")))
    {
        save_file_per_year_total_authors        (reports,fp); 
        save_file_total_articles_per_author     (reports,fp);
        save_file_total_articles_dates          (reports,fp);
        save_file_articles_authors              (reports,fp);
        fclose                                  (fp);
        return TRUE;
    }
    fclose                                      (fp);
    return FALSE;
}

/** Generate all the Reports needed*/
void generated_reports(ReportsS *reports){
    
      save_file_statistics      (reports);  // Generate D report
      save_file_rejected        (reports);  // Generate E report 
      calculate_accumulate      (reports);
      save_report_G             (reports);  // Generate G report
      social_network_questions  (reports);
}
