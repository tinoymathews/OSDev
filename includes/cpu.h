#ifndef __CPU_H_
#define __CPU_H_

#include "types.h"
#include "stdio.h"

#define VENDOR_STRING_SIZE 32
#define PROCESSOR_STRING_SIZE 64
#define INTEL_PROCESSOR_VARIANTS 19
#define PROCESSOR_VARIANTS 30

typedef struct cpuinfo
{
	char *cpu;
	uint8_t cpuid;
}cpu_info;

typedef struct cpudescriptor
{
	char* cpustring;
	char* cpuoutstring;
}cpu_desc;

void get_info( void );
void get_vendor( char* vendor_id, char* processor );
void get_architecture( void );

#endif
