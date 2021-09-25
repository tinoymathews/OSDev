#ifndef __STRING_H_
#define __STRING_H_

#include "types.h"

void *memcpy( void *dest, const void *src, size_t count );
void *memset( const void *str, int ch, size_t n );
size_t strlen(const char *str);
char* strrev( char* str );

#endif
