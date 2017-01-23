#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "ReadDBLP.h"
#include "AuxFuncReadDBLP.h"
#include "DataTypes.h"
#include "Debug.h"
#include "ManipulateData.h"

/** Function for the logs*/
LogsS *add_logs(char *name, LogsS *list){
    
    LogsS *aux = malloc(sizeof(LogsS));
    
    if(aux)
    {
        aux->ids =  malloc(sizeof(int) * IDS_SIZE);
        if(aux->ids)
        {
            aux->name = malloc(STRING_SIZE+1);
            
            if(aux->name)
            {
                for(int i = 0; i < IDS_SIZE;i++)   
                    aux->ids[i] = 0;

                strcpy(aux->name,name);
                aux->next = list;
                return aux;
            }
            else{
                free(aux->ids);
                free(aux);
                return NULL; // Memory problems
            }
        }
        else{
            free(aux);
            return NULL; // Memory problems
        }
    }
    else    // Memory problems
        return NULL;
}

Bool validate_parser_revista_debug(char *article, ReportsS **reports,
          int numberOfPagesAllowed
)
{
     int id, num_autors,volume,num_revista,num_pag,year;
     char *begin;
     size_t strAuthorsSize;
     
     bypass_symbol(&article, ' '); /** Take out spaces */
     
     begin = article;
     
     if(parser_int(&article,&id))   /** Read ID */
     {
         bypass_symbol(&article, ' ');
         
         /** Read Number of Authors */
         if(parser_authors(&article,&num_autors,&strAuthorsSize))  
         {  
             bypass_symbol(&article, ' ');
             /** Read the title */
             if(is_title_valid(&article))                          
             {
                  /** Read magazine name */
                  if(parser_magazine_info(&article))                
                  {
                       bypass_symbol(&article, ' ');
                        /** Read Volume */
                       if(parser_int(&article, &volume))          
                       {
                            bypass_symbol(&article, ' ');
                             /** Read magazine number */
                            if(parser_num_magazine(&article, &num_revista)) 
                            {
                                bypass_symbol(&article, ' '); 
                                /** Read number of pages */
                                if(parser_num_pages(&article,&num_pag) 
                                        && num_pag >= numberOfPagesAllowed)     
                                {
                                   bypass_symbol(&article, ' ');
                                   if(parser_year(&article,&year))
                                   {
                                      return TRUE;

                                   }else printf("Year\n");
                                }else printf("Number of pages\n");
                            }else printf("Number\n");
                       }else printf("Volume\n");
                  }else printf("Magazine\n");
             } else printf("Title\n"); 
         }  else printf("Authors\n");  
     }else printf("ID\n");
     
     
     wprintf(L"<%d> -> %ls\n",(*reports)->statistics->tmp_rejected,begin);
     getchar();
     return FALSE;    
}

void read_logs (char *fileName, LogsS **list){
    FILE *fp = NULL;                                           
    char buffer [STRING_SIZE];
    
    fp = fopen(fileName, "r"); 
   
    if(!fp) return; 
    
      do
      {
          /** Read Line */
         if(fscanf(fp,"%s",buffer) > 0)                            
         {
             if(isdigit(buffer[0]))(*list)->ids[atoi(buffer)]++;
             else                  *list = add_logs(buffer, *list);
         }
      }while(fgetc(fp) != EOF);
        
    fclose(fp);
    return ; 
}

void compare_list(LogsS *list1, LogsS *list2){
    
    if (list1 && list2)
    {
        compare_list(list1->next,list2->next);
        printf("%s %s\n",list1->name, list2->name);

        for(int i = IDS_SIZE-1; i >= 0; i--)
        {
            if(list1->ids[i] != list2->ids[i] && list1->ids[i] <= 1 
                    && list2->ids[i] <= 1)
            {
                if(list1->ids[i] > 0) printf("%d JMF Reject\n",i);
                if(list2->ids[i] > 0) printf("%d Bru Reject\n",i);
            }
        }
        
    }
}

void read_stats (char *file1, char *file2){
    
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    char buffer1 [STRING_SIZE];
    char buffer2 [STRING_SIZE];
    int valor1,valor2,diff;
    float expression;
    
    fp1 = fopen(file1, "r");
    fp2 = fopen(file2, "r"); 
   
    if(!fp1 || !fp2) return; 
    
      do
      {
          /** Read Line */
         if(fscanf(fp1,"%s",buffer1) > 0 && fscanf(fp2,"%s",buffer2))   
         {
             if(isdigit(buffer1[0]) && isdigit(buffer2[0]))
             {
                 valor1 = atoi(buffer1);
                 valor2 = atoi(buffer2);
                 diff = abs((valor2 - valor1));
                 
                 expression = diff * 1.0 / (valor2 * 1.0);
                 printf("%.3f\n",expression);
             }
         }
      }while(fgetc(fp1) != EOF && fgetc(fp2) != EOF);
        
    fclose(fp1);
    fclose(fp2);
    return ; 
}

void debug_rejected(){
     LogsS *list1 = NULL;
     LogsS *list2 = NULL;
     read_logs ("a.txt", &list1);
     read_logs ("b.txt", &list2);
     compare_list(list1,list2);
}
