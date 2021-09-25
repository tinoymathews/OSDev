#include "includes/stdio.h"
#include "includes/cpu.h"
#include "includes/gdt.h"



void kernelMain(const void* multiboot_structure, uint32_t magicnumber)
{
    uint8_t u8Size;
    printf("%s", "Starting OS...", 0);

    /* Print out data sizes */
    printf( "%s", "Size of char : ", 0 );
    u8Size = sizeof( int8_t );
    printf( "%d", &u8Size, CHAR );

    printf( "%s", "Size of short : ", 0 );
    u8Size = sizeof( int16_t );
    printf( "%d", &u8Size, CHAR );

    printf( "%s", "Size of int : ", 0 );
    u8Size = sizeof( int32_t );
    printf( "%d", &u8Size, CHAR );

    /* Initialize Global Descriptor Table */
    setup_gdt();

    printf("%s", "Global decriptor table setup complete...", 0 );

    /* Get CPU information */
    get_info();

    /* The kernel should not stop, must keep running */
    while(1);
}
