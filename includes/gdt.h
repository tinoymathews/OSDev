#ifndef __GDT_H_
#define __GDT_H_

#include "types.h"

#define GDT_TOTALSEGMENTS 3
#define GDT_NULL 0
#define GDT_CODE 1
#define GDT_DATA 2


/*
GDT structure
-------------------------------------------------
31---------------------1615---------------------0
|     Base 0:15          |       Limit 0:15     |
-------------------------------------------------
63         5655   5251  4847       4039        32
| Base 24:31 |Flags|Limit|AccessByte |Base 16:23|
|            |     |16:19|           |          |
-------------------------------------------------  
Access Byte:
----------------
|P|DPL |DT|Type|
----------------
P    - Segment is present?(1 = Yes)
DPL  - Which Ring(0 to 3)
DT   - Descriptor type
Type - Which type?

Flags|Limit:
-----------------
|G|D|0|A|Seg Len|
-----------------
G    	- Granularity(0 = 1 byte, 1 = 4 byte)
D    	- Operand Size(0 = 16 bit, 1 = 32 bit)
0    	- Always 0
A       - Availiable for system(Always set to 0)
Seg Len - Higher 4 bits of Segment length

*/
typedef struct GlobalDescriptorTable
{
	uint16_t u16Limit_Low;
	uint16_t u16Base_Low;
	uint8_t  u8Base_High1;
	uint8_t  u8Access_Type;
	uint8_t  u8FlagsLimit;
	uint8_t  u8Base_High2;

}__attribute__((packed)) GDT;

typedef struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed)) GDT_PTR;

/* Initializes a segment */
void init_Segment( int8_t i8Segment, uint32_t u32Base, uint32_t u32Limit, uint8_t u8Type, uint8_t u8Flags);

/* Gets the base address to a segment */
uint32_t get_SegmentBase( int8_t i8Segment );

/* Gets the size limit to a segment */
uint32_t get_SegmentLimit( int8_t i8Segment );

/* Gets the access type to a segment */
uint8_t get_SegmentAccessType( int8_t i8Segment );

/* Gets the flags to a segment */
uint8_t get_SegmentFlags( int8_t u8Segment );

/* Set up the segments with the processor */
void setup_gdt();

#endif
