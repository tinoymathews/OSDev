#include "includes/stdio.h"
#include "includes/string.h"

void printf(char* format, void* arg, uint8_t datasize)
{
    int32_t i;
    int32_t j;
    char* str;
    char strdigit[12]       = {'\0'};
    char strbinarydigit[64] = {'\0'};
    int32_t digit;
    int32_t digitfollower;
    int8_t digitcount;
    char base_format;
    char hex_char;
    int8_t i8DataSizeInBits;
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    /* Check format string and arguement */
    if( ( '%' != format[0] ) || ( NULL == arg ) )
        return;

    /* Traverse the format string and find the base format */
    base_format = format[1];

    /* If the base format is not a string, then datasize matters, otherwise ignore datasize */
    if( 's' != base_format )
    {
        /* Consider the data size for the arguement and collect the digit*/
        switch( datasize )
        {
            case CHAR:
                digit = *((int8_t*)arg);
                break;
            case SHORT:
                digit = *((int16_t*)arg);
                break;
            case INT:
                digit = *((int32_t*)arg);
                break;
            case LONG:
                digit = *((int64_t*)arg);
                break;
            default:
                return;
        }
    }

    /* Check the format to be printed */
    switch( base_format )
    {
		case 's':
			str = (char*)arg;
			break;
		case 'd':
			digitcount			  = -1;
			digitfollower		  = digit;

			/* Reinitialize strdigit array to empty string */
			memset( strdigit, '\0', 12 );

			/* Get total number of digits in the number */
			while( digitfollower != 0 )
			{
				digitcount++;
				digitfollower = digitfollower/10;
			}

			/* Assign the number to the character array */
			while( digit != 0 )
			{
			/* Get the last digit, 48 is ascii for '0' */
				strdigit[digitcount] = 48 + ( digit % 10 );
				digit				 = digit / 10;
				digitcount--;
			}
			str = strdigit;
			break;
		case 'x':
			digitcount = 10;

			while( digitcount >= 2 )
			{
				switch( digit % 16 )
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						hex_char = 48 + ( digit % 16 );
						break;
					case 10:
						hex_char = 'A';
						break;
					case 11:
						hex_char = 'B';
						break;
					case 12:
						hex_char = 'C';
						break;
					case 13:
						hex_char = 'D';
						break;
					case 14:
						hex_char = 'E';
						break;
					case 15:
						hex_char = 'F';
						break;
				}
				strdigit[digitcount] = hex_char;
				digit = digit / 16;
				digitcount--;
			}
			strdigit[digitcount]   = 'x';
			strdigit[digitcount-1] = '0';
			break;
		case 'b':
		    /* Get the data size in bits */
		    switch( datasize )
		    {
                case CHAR:
                    i8DataSizeInBits = CHAR * 8;
                    break;
                case SHORT:
                    i8DataSizeInBits = SHORT * 8;
                    break;
                case INT:
                    i8DataSizeInBits = INT * 8;
                    break;
                case LONG:
                    i8DataSizeInBits = LONG * 8;
                    break;
                default:
                    return;
		    }

            /* Fill array to get the binary representation */
            while( i8DataSizeInBits >= 0 )
            {
                strbinarydigit[i8DataSizeInBits-1] = 48 + ( digit % 2 );
                digit = digit >> 1;
                i8DataSizeInBits--;
            }
            str = strbinarydigit;
			break;
		case 'o':
			break;
		case 'c':
			break;
		default:
			break;
	}

	/* Put it on the screen */
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

