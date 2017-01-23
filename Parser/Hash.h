/* 
 * File:   Hash.h
 * Author: Bruno M. <brunom@di.uminho.pt>
 */

#ifndef HASH_H
#define	HASH_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    

uint32_t SuperFastHash                  (const char * data, int len);
int getHash                             (char *data);
int RSHash                              (char* str,   int len);
int JSHash                              (char* str,   int len);
int ELFHash                             (char* str,   int len);
int BKDRHash                            (char* str,   int len);
int SDBMHash                            (char* str,   int len);
int DJBHash                             (char* str,   int len);
int DEKHash                             (char* str,   int len);
int BPHash                              (char* str,   int len);
int FNVHash                             (char* str,   int len);
int APHash                              (char* str,   int len);

#ifdef	__cplusplus
}
#endif

#endif	/* HASH_H */

