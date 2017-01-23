/* 
 * File:   ERROS.h
 * Author: Bruno Medeiros
 */

#ifndef ERROS_H
#define ERROS_H
#define ERRORHANDLE int
#define EXIT 0
#define SUCCESS 1
#define OUT_OF_LIMITS 2
#define WRONG_PARSER 3
#define MEMORY_PROBLEMS 4
#define KEEP_EXECUTION 5
#define COMMAND_NOT_FOUND 6


#ifdef __cplusplus
extern "C" {
#endif

void check_erros_msg        (ERRORHANDLE msg);
void check_success_msg      (ERRORHANDLE msg);

#ifdef __cplusplus
}
#endif

#endif /* ERROS_H */

