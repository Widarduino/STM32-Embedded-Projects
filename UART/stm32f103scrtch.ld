ENTRY(Reset_Handler)
/* entry for the event of a reset */
MEMORY
{
	FLASH(rx) : ORIGIN =0x08000000, LENGTH = 64K
	SRAM(rwx) : ORIGIN =0x20000000, LENGTH = 20K
} 
/*define memory*/

_estack = ORIGIN(SRAM) + LENGTH(SRAM); 
/* end of RAM*/

SECTIONS
{
/*ALIGN just moves the pointer ahead*/
	.text : 
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector)) /* order is important for loading*/
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
		_etext = .; /*mark end of text*/
	 } >FLASH
	
	 _sidata = LOADADDR(.data); /*initialized data start*/

	 .data : 
	 {
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	 } >SRAM AT> FLASH
	 /* copies to SRAM after physically writing to FLASH */

	 .bss :
	 {
		 . = ALIGN(4);
		 _sbss = .;
		 *(.bss)
		 *(.bss*)
		 *(COMMON) /* good practice because old gcc uses common*/

		. = ALIGN(4);
		 _ebss = .;
	 }>SRAM

}
