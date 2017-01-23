/* 
 * File:   main.c
 * Author: Bruno M. <brunom@di.uminho.pt>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ReadDBLP.h"
#include "AuxFuncReadDBLP.h"
#include "DataTypes.h"
#include "ManipulateData.h"
#include "RedeSocial.h"

/** Read a line from a given file */
Bool read_line_from_file(FILE *fp, char **buffer, Bool *flag){
     
     size_t count = 0; 
     size_t size = STRING_SIZE;
     char ch;
     
     *buffer = malloc(size); /** allocate buffer. **/
    
     ch = getc(fp);

      /** Read char by char until a new line is reach or the end of file. */
     while((ch != '\n') && (ch != EOF))               
     {      
        if(count == size)    /** If the buffer reach its initial size */
        { 
           size *= 2;   /** Double the size */
           *buffer = realloc(*buffer, size); /** Expand buffer */
        }       
    
        (*buffer)[count++] = ch;   /** Save the symbol read */
         ch = getc(fp);             /** Take a new symbol from the file */
     }
     (*buffer)[count] = '\0';       /** Close the string read */
                                    /** Warning the external call of 
                                     * the file was */
     *flag = (count > 0);           /** Verify if the line read is not empty */
     
     return (ch !=  EOF);         /** check if there is more lines 
                                   * to be read it. */
} 


Bool validate_parser_magazine(char *article, ReportsS *reports, int pagesLimite)
{
    
    int id, num_autors,volume,num_revista,num_pag,year;
    char *ptrAutors;

    size_t strAuthorsSize;
    
    if(parser_int(&article,&id)) // Read ID   
    {
        ptrAutors = article;
        
        if(    // Read # of Authors
               parser_authors(&article,&num_autors,&strAuthorsSize) && 
                is_title_valid(&article)      &&  // Read the title
                parser_magazine_info(&article)    &&  // Read journal name
                parser_int(&article, &volume)   &&  // Read Volume
                parser_num_magazine(&article, &num_revista)) // Read Journal number
        {             
          // Read number of pages and year        
            if(parser_num_pages(&article,&num_pag) && 
                    num_pag >= pagesLimite     && 
                    parser_year(&article,&year))        
            {
               // Add number of authors/year                                             
               add_year_articles_num_authors (reports,year, num_autors, 1);       
               reports->statistics->articles++; // The article is set as valid                              
               
               add_authors(reports->redesocial, ptrAutors, num_autors);
               return TRUE; 
            }
        } 
      }
               
     // The article was rejected 
     reports->statistics->tmp_rejected++;                                          
     return FALSE;    
}


Bool validate_parser_conference(char *article, ReportsS *reports, 
          int pagesLimite){
    
     int id, num_autors,num_pag,year;
     char *ptrAutors;
     size_t strAuthorsSize;
     
     if(parser_int(&article,&id))  /** Read ID */
     {
       ptrAutors = article;
       if(      //Read # of Authors
                parser_authors(&article,&num_autors,&strAuthorsSize) && 
                is_title_valid(&article)         && // Read the title
                parser_conference_info(&article)    && // Read Conference name
                parser_int(&article, &year))          // Read Year
       {                  
           if(*article == ':')                                                  
           {
              article++;
              /** Read number of pages */ 
              if(parser_num_pages(&article,&num_pag) && num_pag >= pagesLimite)       
              {
                  /** Add number of authors/year  */
                 add_year_articles_num_authors (reports,year, num_autors, 1); 
                 /** The article is set as valid */
                 reports->statistics->articles++;                                  
                 add_authors(reports->redesocial, ptrAutors,num_autors);
                 return TRUE;
              }
          }
       }
     }
      /** The article was rejected */
     reports->statistics->tmp_rejected++;                                          
     return FALSE;    
}

/* This function will receive a pointer to an function in 
 * order to apply the correct parser*/
Bool read_bibliography(char *file, ReportsS *reports, int numberOfPagesAllowed,
        Bool (*parser) (char *,ReportsS *,  int)){
    
    FILE *fp = NULL;        // Declare point to file.
    char *buffer = NULL;    // Buffer to hold the read lines
    Bool moreLines = TRUE;  // Variable to check if the file 
                            // have more lines to read 
    Bool validLine = FALSE;  // Variable to check if 
                             // the line read is valid
    char dir_file[FILE_NAME_SIZE];
    
    strcpy(dir_file,reports->files->directory);
    strcat(dir_file,file);
    
    fp = fopen(dir_file, "r"); 
   
    
    if(fp)  // No error reading file
    {
       while(moreLines)  // While the file have lines to read
       {
           // Read a line
            moreLines = read_line_from_file(fp, &buffer, &validLine);                      
       
            if(validLine)
            { 
                // If the line is valid, lets check if the 
                //  article have a valid format
                parser(buffer,reports,numberOfPagesAllowed);
            }
            
            validLine = FALSE;      // Initialize control variable                                                  
            free(buffer);           // Free allocated buffer
       }  
       fclose(fp);
       return TRUE;   // File was read with success
    }     
     
    
    return FALSE;  // It was not possible to read the file
}

Bool read_list_conferences(ReportsS *reports){
    FILE *fp = NULL;    
    char buffer [STRING_SIZE];
    int numberOfPages, tmpTotal;
    
    fp = fopen(reports->files->list, "r");
  
    
    if(fp) // No error reading file
    {
        fscanf(fp, "%[ ]",buffer);  // Remove spaces  
        
        // Read the number of pages on the first line
        if(fscanf (fp, "%d", &numberOfPages))                                               
        {
            do{
                fscanf(fp, "%[ ]",buffer);          // Remove spaces                                                 
                if(fscanf(fp,"%[^\n]",buffer) > 0)  // Read Line                                        
                {
                    // Save the number of articles already find it
                    tmpTotal = reports->statistics->articles;                                
                    reports->statistics->tmp_rejected = 0;
          
                    // If the read file was a journal
                    if(*buffer == 'j' || *buffer == 'J')                                   
                    {
                        read_bibliography(buffer, reports, 
                                numberOfPages, validate_parser_magazine);
                      
                        reports->statistics->revista += 
                                reports->statistics->articles - tmpTotal;
                        
                        reports->rejectedArticles = 
                                add_rejected (reports->rejectedArticles, 
                                buffer,reports->statistics->tmp_rejected);
                        
                        reports->statistics->rejected += 
                                reports->statistics->tmp_rejected;
                    }
                    else if(*buffer == 'c' || *buffer == 'C')
                    {   
                            read_bibliography(buffer,reports, 
                                numberOfPages,validate_parser_conference);       
                               
                               reports->statistics->conferencia += 
                                      reports->statistics->articles - tmpTotal;
                                
                                reports->rejectedArticles = 
                                        add_rejected (reports->rejectedArticles, 
                                        buffer, 
                                        reports->statistics->tmp_rejected);
                                
                                reports->statistics->rejected += 
                                        reports->statistics->tmp_rejected; 
                    }             
                }
          } while(fgetc(fp) != EOF);
      
        reports->statistics->entries = 
                reports->statistics->rejected + reports->statistics->articles;
        }
    }
    
    fclose(fp);
    return TRUE; 
}
