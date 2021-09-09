#include "includes/gdt.h"


GDT gdt_entry[GDT_TOTALSEGMENTS];
GDT_PTR gdt_ptr;

void init_Segment( int8_t i8Segment, uint32_t u32Base, uint32_t u32Limit, uint8_t u8Type, uint8_t u8Flags)
{
	/* Initialize the base address to the segment */		
	gdt_entry[i8Segment].u16Base_Low  = ( u32Base & 0xFFFF );   
	gdt_entry[i8Segment].u8Base_High1 = ( u32Base >> 16 ) & 0xFF;
	gdt_entry[i8Segment].u8Base_High2 = ( u32Base >> 24 ) & 0xFF;

	/* Initialize the size of the descriptor */
	gdt_entry[i8Segment].u16Limit_Low  = ( u32Limit & 0xFFFF );
	gdt_entry[i8Segment].u8FlagsLimit  = ( ( u32Limit >> 16 ) & 0x0F );
	gdt_entry[i8Segment].u8FlagsLimit |= ( u8Flags & 0xF );

	/* Initialize the access type */
	gdt_entry[i8Segment].u8Access_Type = u8Type;
}

uint32_t get_SegmentBase( int8_t i8Segment )
{
	uint32_t u32Base;
	uint32_t u32Base_High1;
	uint32_t u32Base_High2;

	/* Initialize all variables */
	u32Base 	= 0;
	u32Base_High1	= 0;
	u32Base_High2	= 0;
	
	/* Formulate the segment base address from the gdt entry structure */
	u32Base 	= gdt_entry[i8Segment].u16Base_Low;
	u32Base_High1 	= gdt_entry[i8Segment].u8Base_High1;
	u32Base_High2 	= gdt_entry[i8Segment].u8Base_High2;
	
	/* Shift the High 1 and by 16 bit places and High 2 by 24 bit places */
	u32Base_High1 = u32Base_High1 << 16;
	u32Base_High2 = u32Base_High2 << 24;

	/* Formulate the final base address */
	u32Base = u32Base_High2 | u32Base_High1 | u32Base;

	return u32Base;
}

uint32_t get_SegmentLimit( int8_t i8Segment )
{
	uint32_t u32Limit;
	uint32_t u32Limit_High;

	/* Initialize alö variables */
	u32Limit 	       = 0;
	u32Limit_High 	       = 0;
	
	/* Formulate the segment size limit from the gdt structure */
	u32Limit 	       = gdt_entry[i8Segment].u16Limit_Low;
	u32Limit_High 	       = gdt_entry[i8Segment].u8FlagsLimit;
	u32Limit_High          = u32Limit_High << 16;
	u32Limit               = u32Limit_High | u32Limit;
	
	return u32Limit;
}

uint8_t get_SegmentAccessType( int8_t i8Segment )
{
	return 	gdt_entry[i8Segment].u8Access_Type;
}

uint8_t get_SegmentFlags( int8_t i8Segment )
{
	uint8_t u8Flags = 0;

	/* Recover just the flags for the segment */
	u8Flags = gdt_entry[i8Segment].u8FlagsLimit;
	u8Flags = u8Flags >> 8;

	return u8Flags;
}

void setup_lgdt()
{
	uint16_t x = 0x10;

	asm volatile( "lgdt (%0)" :: "m"(gdt_ptr) );	
	asm volatile( "movl %%ax, %0" : "=r"(x) );	
	asm volatile( "movl %%ds, %0" : "=r"(x) );
	asm volatile( "movl %%es, %0" : "=r"(x) );                
	asm volatile( "movl %%fs, %0" : "=r"(x) );        
	asm volatile( "movl %%gs, %0" : "=r"(x) );        
	asm volatile( "movl %%ss, %0" : "=r"(x) );        

	return;
}

void setup_gdt()
{
	/* Set up GDT reference */	
	gdt_ptr.limit = ( sizeof( GDT ) * GDT_TOTALSEGMENTS ) - 1;
	gdt_ptr.base  = (Address)&gdt_entry;

	/* Set up the null descriptor */
	init_Segment( 0, 0, 0, 0, 0 );
	
	/* Set up the code segment */
	init_Segment( 1, 0, 0xFFFFFFFF, 0x9A, 0xCF );

	/* Set up the data segment */
	init_Segment( 2, 0, 0xFFFFFFFF, 0x92, 0xCF );

	/* Set up the gdt using the lgdt instruction */
	setup_lgdt();
}
