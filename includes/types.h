#ifndef __TYPES_H
#define __TYPES_H

typedef void v_t;

typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef unsigned long int Address;

typedef unsigned int size_t;


#define NULL (void*)0
#define CHAR sizeof(int8_t)
#define SHORT sizeof(int16_t)
#define INT sizeof(int32_t)
#define LONG sizeof(int64_t)


#endif
