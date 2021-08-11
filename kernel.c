#include "includes/types.h"

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    for(int32_t i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}


void kernelMain(const void* multiboot_structure, uint32_t magicnumber)
{
    printf("Starting OS...");

    /* The kernel should not stop, must keep running */
    while(1);
}
