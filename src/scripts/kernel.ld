/*
 *      This script tells LD how to set up our kernel image. 
 *      Firstly it tells LD that the start location of our binary should be the symbol 'start'. 
 *      It then tells LD that the .text section (that's where all your code goes) should be first,
 *      and should start at 0x100000 (1MB). 
 *      The .data (initialised static data) and the .bss (uninitialised static data) should be next, 
 *      and each should be page-aligned (ALIGN(4096)).
 *      Linux GCC also adds in an extra data section: .rodata. 
 *      This is for read-only initialised data, such as constants. 
 *      For simplicity we simply bundle this in with the .data section.
 */
ENTRY(start)
SECTIONS
{
	PROVIDE( kern_start = 0xC0100000);
	. = 0x100000; 
	.init.text : 
	{
		*(.init.text)
		. = ALIGN(4096);
	}
	.init.data : 
	{
		*(.init.data)
		. = ALIGN(4096);
	}

	. += 0xC0000000;
	.text : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss : AT(ADDR(.bss) - 0xC0000000)
	{
		*(.bss)
		. = ALIGN(4096);
	}
	.stab : AT(ADDR(.stab) - 0xC0000000)
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr : AT(ADDR(.stabstr) - 0xC0000000)
	{
		*(.stabstr)
	 	. = ALIGN(4096);
	}
	PROVIDE( kern_end = . );
	
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}

