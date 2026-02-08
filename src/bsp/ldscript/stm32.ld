ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

_Min_Heap_Size = 0x200;
_Min_Stack_Size = 0x400;

MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
  ROM (rx)  : ORIGIN = 0x80000000, LENGTH = 64K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >ROM

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >ROM

  .rodata :
  {

  }

  /* Initialized data sections >RAM */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;     /* create a global symbol at data start */
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;     /* define a global symbol at data end */
    
  } >RAM AT> ROM

  /* Uninitialized data setcion >RAM */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    /* 1. start point definition */
    _sbss = .;
    __bss_start__ = _sbss;

    /* 2. load all bss section and common */
    *(.bss)
    *(.bss*)
    *(COMMON)

    /* 3. end point definition */
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  ._user_head_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    
    /* inspect a memory has enough spaces */
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM
}