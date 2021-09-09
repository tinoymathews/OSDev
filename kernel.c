#include "includes/types.h"
#include "includes/gdt.h"

static uint16_t* VideoMemory = (uint16_t*)0xb8000;

void printf(char* str)
{
    int32_t i;
    int32_t j;

    for(i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];    

    /* Fill the remaining characters to emulate the new line */
    j = i;
    while( i < 80 )
    {
	VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[j];
	i++;
    }
    
    /* Update the video memory to the next line */
    VideoMemory = VideoMemory + 80;
}


void kernelMain(const void* multiboot_structure, uint32_t magicnumber)
{
    printf("Starting OS...");

    /* Initialize Global Descriptor Table */
    setup_gdt();

    printf("Global decriptor table setup complete..." );

    /* The kernel should not stop, must keep running */
    while(1);
}
