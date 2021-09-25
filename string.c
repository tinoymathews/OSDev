#include "includes/string.h"

void *memcpy( void *dest, const void *src, size_t count )  
{  
	char *d;  
	const char *s;  
   
	/* Check whether source could be copied to destination with integrity */
	if ( ( ( int )dest > ( ( int )src+count ) ) || ( dest < src ) )  
        {  
	    d = (char*)dest;  
	    s = (char*)src;  
	    while (count--)  
        	*d++ = *s++;          
	}  
	else
	    return NULL;
     
	return dest; 
} 

void *memset( const void *str, int ch, size_t n )
{
	size_t t;
	char* string;

	/* NULL check */
	if( str == NULL )
		return NULL;

	/* Serial assignment of the character array */
	t      = 0;
	string = ( char* )str;
	while( t < n )
	{
		string[t] = ch;	
		t++;
	} 

	return ( void* )str;
}

size_t strlen( const char *str )
{
	size_t cCount = 0;

	/* Perform a null check of the incoming string */
	if( NULL == str	)
		return 0;

	/* Check null termination, which marks the completion of the string */
	while( '\0' != str[cCount] )
	{	
		cCount++;
	}
	
	return cCount;
}

char* strrev( char* str )
{
	size_t cIndex  = 0;
	size_t dIndex  = 0;
	char temp;

	/* Perform a null check of the incoming string */
	if( NULL == str )
		return (char*)NULL;
	
	/* Get the string length */
	dIndex = strlen(str);	
	
	/* Ping pong from both directions*/ 
	while( 	( dIndex > 0 ) && ( dIndex >= cIndex ) )
	{
		temp        = str[cIndex];
		str[cIndex] = str[dIndex];
		str[dIndex] = temp;

		dIndex--;
		cIndex++;
	}

	return str;
}
