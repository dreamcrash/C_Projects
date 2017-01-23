#include <stdint.h> 
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "DataTypes.h"
#include <math.h>
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

/* SuperFastHash => By Paul Hsieh (C) 2004, 2005.  
 * Covered under the Paul Hsieh derivative 
   license. See: 
   http://www.azillionmonkeys.com/qed/weblicense.html for license details.
   http://www.azillionmonkeys.com/qed/hash.html */


// Other hash's => http://intercontineo.com/article/6539178876/


uint32_t SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

  int RSHash(char* str,   int len)
{
     int b    = 378551;
     int a    = 63689;
     int hash = 0;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


  int JSHash(char* str,   int len)
{
     int hash = 1315423911;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}
/* End Of JS Hash Function */


 /* End Of  P. J. Weinberger Hash Function */


  int ELFHash(char* str,   int len)
{
     int hash = 0;
     int x    = 0;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << 4) + (*str);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


  int BKDRHash(char* str,   int len)
{
     int seed = 131; /* 31 131 1313 13131 131313 etc.. */
     int hash = 0;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}
/* End Of BKDR Hash Function */


  int SDBMHash(char* str,   int len)
{
     int hash = 0;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


  int DJBHash(char* str,   int len)
{
     int hash = 5381;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}
/* End Of DJB Hash Function */


  int DEKHash(char* str,   int len)
{
     int hash = len;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }
   return hash;
}
/* End Of DEK Hash Function */


  int BPHash(char* str,   int len)
{
     int hash = 0;
     int i    = 0;
   for(i = 0; i < len; str++, i++)
   {
      hash = hash << 7 ^ (*str);
   }

   return hash;
}
/* End Of BP Hash Function */


  int FNVHash(char* str,   int len)
{
   const   int fnv_prime = 0x811C9DC5;
     int hash      = 0;
     int i         = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash *= fnv_prime;
      hash ^= (*str);
   }

   return hash;
}
/* End Of FNV Hash Function */


  int APHash(char* str,   int len)
{
     int hash = 0xAAAAAAAA;
     int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}
/* End Of AP Hash Function */



int getHash(char *data){
    return SuperFastHash(data,strlen(data)) % HASH_SIZE;
    
}
