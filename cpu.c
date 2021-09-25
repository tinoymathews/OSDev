#include "includes/cpu.h"
#include "includes/string.h"

cpu_info stCpuInfo[INTEL_PROCESSOR_VARIANTS] = \
{\
	{"Later Intel 486 and Pentium", 0x01},\
	{"Pentium Pro, Pentium II and Celeron", 0x02},\
	{"Pentium III", 0x03},\
	{"Pentium 4", 0x02},\
	{"Xeon", 0x02},\
	{"Pentium M", 0x02},\
	{"Pentium 4 with HT", 0x05},\
	{"Pentium D(8xx)", 0x05},\
	{"Pentium D(9xx)", 0x06},\
	{"Core Duo", 0x0A},\
	{"Core 2 Duo", 0x0A},\
	{"Xeon 3000, 5100, 5200, 5300, 5400", 0x0A},\
	{"Core 2 Duo 8000 series", 0x0D},\
	{"Xeon 5200, 5400 series", 0x0A},\
	{"Atom", 0x0A},\
	{"Nehalem-based processors", 0x0B},\
	{"IvyBridge-based processors", 0x0D},\
	{"Skylake-based processors", 0x16},\
	{"System-On-Chip", 0x17}\
};

cpu_desc stCpuDesc[PROCESSOR_VARIANTS] = \
{\
	{"AMDisbetter!", "AMD K5 processor"},\
	{"AuthenticAMD", "AMD processor"},\
	{"CentaurHauls", "IDT WiChip/Centaur processor"},\
	{"CyrixInstead", "Cyrix/ST Microelectronics and IBM processor"},\
	{"GenuineIntel", "Intel processor"},\
	{"TransmetaCPU", "Transmeta processor"},\
	{"GenuineTMx86", "Genuine Transmeta processor"},\
	{"Geode by NSC", "National Semiconductor processor"},\
	{"NexGenDriven", "NexGen processor"},\
	{"RiseRiseRise", "Rise processor"},\
	{"SiS SiS SiS" , "SiS processor"},\
	{"UMC UMC UMC" , "UMC processor"},\
	{"VIA VIA VIA" , "VIA processor"},\
	{"Vortex86 SoC", "DM&P Vortex processor"},\
	{" Shanghai "  , "Zhaoxin processor"},\
	{"HygonGenuine", "Hygon processor"},\
	{"E2K MACHINE" , "MCST Elbrus processor"},\
	{"bhyve bhyve" , "bhyve VM"},\
	{" KVMKVMKVM"  , "KVM"},\
	{"TCGTCGTCGTCG", "QEMU VM"},\
	{"Microsoft Hv", "Microsoft Hyper-VM"},\
	{" Irpepyh  vr", "Parallels VM"},\
	{"VMWareVMWare", "VMWare"},\
	{"XenVMMXenVMM", "Xen HVM"},\
	{"ACRNACRNACRN", "Project ACRN"},\
	{"QNXQVMBSQG"  , "QNX Hypervisor"},\
};

void get_info( void )
{
	int32_t iNumber;

	/* 
	Static local variable initialization is only done once
	Lifetime of this variable is the entire run time
	Access scope is restricted within the function
	*/		
	char vendor[VENDOR_STRING_SIZE] = {'\0'};	
	char processor[PROCESSOR_STRING_SIZE] = {'\0'};

	/* Get the vendor */
	get_vendor( ( char* )vendor, ( char* )processor );

	printf( "%s", vendor, 0 );
	printf( "%s", processor, 0 );
	
	return;
}

void get_vendor( char* vendor_id, char* processor )
{
	int32_t idRes[3]   = {0};
        int32_t iProcessor = 0;
	uint8_t iCount     = 0;
	uint8_t iLen       = 0;

	/* Assign eax register to 0, this is parameter for the cpuid */	
	asm volatile( "mov $0x0, %eax\n\t" );
	/* Call cpuid */	
	asm volatile( "cpuid\n\t" );
	/* Copy contents of ebx into a[0] */
	asm volatile( "mov %%ebx, %0\n\t":"=r" ( idRes[0] ) );
	/* Copy contents of edx into a[1] */
	asm volatile( "mov %%edx, %0\n\t":"=r" ( idRes[1] ) );
	/* Copy contents of ecx into a[2] */
	asm volatile( "mov %%ecx, %0\n\t":"=r" ( idRes[2] ) );
	
	memcpy( ( void* )vendor_id, ( const void* )idRes, 3 * sizeof( int32_t ) );	

	/* Find processor type */	
	asm volatile( "mov %%eax, %0\n\t":"=r" ( iProcessor ) );

	while( iCount < INTEL_PROCESSOR_VARIANTS )
	{
		if( stCpuInfo[iCount].cpuid == iProcessor )
		{
			iLen = strlen( stCpuInfo[iCount].cpu );
			memcpy( ( void* )processor, ( const void* )stCpuInfo[iCount].cpu, iLen );		
			printf( "%s", "Discovered processor type", 0 );		
			break;
		}
		iCount++;
	}
	if( iCount == INTEL_PROCESSOR_VARIANTS )
		printf( "%s", "Unknown type", 0 );

	return;
}

void get_architecture( void )
{
	return;
}
