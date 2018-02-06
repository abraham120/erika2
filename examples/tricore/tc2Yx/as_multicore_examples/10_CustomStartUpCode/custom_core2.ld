/*
 * Name: ee_tc27x_gnu_memory_cpu0.x
 *
 * Description: TC27x memory description for cpu0 in multicore
 * environment
 */

/*
 * Global
 */

OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_START)

 __TRICORE_DERIVATE_MEMORY_MAP__ = 0x270;

/* Start-up Program Flash Memory */
__PMU_PFLASH_STARTUP_BEGIN = 0x80000000;
__PMU_PFLASH_STARTUP_SIZE  = 1k;

/* Absolute 18bit addressing data */
__PMU_PFLASH_ABS18_BEGIN  = 0x80003000;
__PMU_PFLASH_ABS18_SIZE   = 4k;

/*Program Flash Memory (PFLASH1)*/
__PMU_PFLASH_BEGIN = 0x80300000;
__PMU_PFLASH_SIZE  = 1M;

/*Data Flash Memory (DFLASH0)*/ 
__PMU_DFLASH0_BEGIN = 0xAF0C0000;
__PMU_DFLASH0_SIZE = 256k;

/*Data Flash Memory (DFLASH1)*/ 
__PMU_DFLASH1_BEGIN = 0xAF11C000;
__PMU_DFLASH1_SIZE = 16K;

/*Boot ROM (BROM)*/
__BROM_BEGIN = 0x8FFF8000;
__BROM_SIZE = 32K;

/*Scratch-Pad RAM (PSPR)*/ 
__PMI_PSPR_BEGIN = 0x50100000;
__PMI_PSPR_SIZE = 24K;

/*Local Data RAM (DSPR)*/ 
__DMI_DSPR_BEGIN = 0x50000000;
__DMI_DSPR_SIZE = 112K;

/*Data RAM (LMU)*/ 
__LMU_SRAM_BEGIN = 0x90006000;
__LMU_SRAM_SIZE = 8K;

  /* CSA list size */
__CSA_SIZE = DEFINED (__CSA_SIZE) ? __CSA_SIZE : 8k ;
  /* User stack Size */ 
__USTACK_SIZE = DEFINED (__USTACK_SIZE) ? __USTACK_SIZE : 2K;
  /* Interrupt Stack Size */
__ISTACK_SIZE = DEFINED (__ISTACK_SIZE) ? __ISTACK_SIZE : 0K;
  /* Heap size */
__HEAP_SIZE = DEFINED (__HEAP_SIZE) ? __HEAP_SIZE : 0;

MEMORY
{
  /* - 0x(8)A0000000--0x(8)A000001F ABM Header Start */
  /* - 0x(8)A0000020 Boot Address */
  /* - 0x(A)80000020--0x(A)80017FFF Code Application Pattern */

  /* - Program Flash Memory for startup (PFLASH0) */
  PMU_PFLASH_STARTUP (rx!p): org = 0x80000000, len = 1k

  /* - Program Flash Memory for 18 bit absolute adrressing (PFLASH0) */
  PMU_PFLASH_ABS18  (rx!p): org = 0x80003000, len = 4k
  /* - Program Flash Memory (PFLASH1) */
  PMU_PFLASH (rx!p):  org = 0x80300000, len = 1M
  /* - Data Flash Memory (DFLASH0) */ 
  PMU_DFLASH0 (r!xp):  org = 0xAF0C0000, len = 256k
  /* - Data Flash Memory (DFLASH1) */ 
  PMU_DFLASH1 (r!xp):  org = 0xAF11C000, len = 16K

  /* - Boot ROM (BROM) */ 
  BROM (rx!p):  org = 0x8FFF8000, len = 32K

  /* - Scratch-Pad RAM (PSPR) (0x2500 + 0x3B00 = 24k) */
  PMI_PSPR_STARTUP  (wx!p):  org = 0x50100000, len = 0x2500
  PMI_PSPR          (wx!p):  org = 0x50102500, len = 0x3B00
  /* - Local Data Scratch-Pad RAM (DSPR) */
  DMI_DSPR (w!xp): org = 0x50000000, len = 112K
  /* - Data RAM */ 
  LMU_SRAM (w!xp):  org = 0x90006000, len = 8K
}

SECTIONS
{
  /*
   * Startup code for TriCore
   */
  .startup :
  {
    BootModeIndex = .;
    PROVIDE(__startup_code_start = .);
    KEEP (*(.startup_code))
    KEEP (*(ee_start))
    . = ALIGN(8);
    PROVIDE(__startup_code_end = .);
  } > PMI_PSPR_STARTUP /* PMI_PSPR: Scratch-Pad RAM (PSPR) */

  /*
   * Allocate space for absolute addressable sections; this requires that
   * "int_dspr" starts at a TriCore segment (256M) and points to
   * some RAM area!  If these conditions are not met by your particular
   * hardware setup, you should either not use absolute data, or you
   * must move .zdata*,.zbss*,.bdata*,.bbss* input sections to some appropriate
   * memory area.
   */
 .zbss  (NOLOAD) :
  {
    ZBSS_BASE = . ;
    *(.zbss)
    *(.zbss.*)
    *(.gnu.linkonce.zb.*)
    *(.bbss)
    *(.bbss.*)
    . = ALIGN(8);
    ZBSS_END = . ;
  } > DMI_DSPR

  .zdata  :
  {
    ZDATA_BASE = . ;
    *(.zrodata)
    *(.zrodata.*)
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
    *(.bdata)
    *(.bdata.*)
    . = ALIGN(8);
    ZDATA_END = . ;
  } > DMI_DSPR

  /*
   * Allocate .text and other read-only sections.
   */

  /*
   * Code executed before calling main
   */
  .init :
  {
    *(.init)
    *(.fini)
    . = ALIGN(8);
  } > PMI_PSPR_STARTUP

  /*
   * Section for interrupt table
   */
  .inttab  :
  {
    PROVIDE(__inttab_start = .);
    KEEP (*(.inttab));
    KEEP (*(.*.inttab.*));
    PROVIDE(__inttab_end = .);
    . = ALIGN(8);
  } > PMI_PSPR_STARTUP /* PMI_PSPR: Scratch-Pad RAM (PSPR) */ 

  /*
   * Code sections
   */
  tc27x_start (0x50102000) :
  {
    KEEP(*(*.tc27x_start))
    . = ALIGN(8);
  }

  .text  :
  {
    PROVIDE(__text_start = .);
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    /*
     * .gnu.warning sections are handled specially by elf32.em.
     */
    *(.gnu.warning)
    . = ALIGN(8);
  } > PMI_PSPR /* PMI_PSPR: Scratch-Pad RAM (PSPR) */

  /*
   * Storage of write-protected data
   */

  /* Erika Constant Shared Data */
  ee_mcglobalc  :
  {
    KEEP(*(ee_mcglobalc))
    . = ALIGN(8);
  } > DMI_DSPR

  .rodata  :
  {
    PROVIDE(__rodata_start = .);

    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    *(.toc)
    /*  Clear and copy tables that tell the startup code
        which memory areas to clear and to copy, respectively, are not
        needed in Execution from RAM */
    . = ALIGN(8);
  } > DMI_DSPR /* DMI_DSPR: Scratch-Pad RAM (DSPR) */ 

  /* Erika RTOS Multicore constant global data (in RAM configuration, locator
     rule have to be explicit otherwise they will tied wrongly with a ROM
     memory) */
  ee_mcglobalc  :
  {
    *(ee_mcglobalc)
    . = ALIGN(8);
  } > DMI_DSPR /* DMI_DSPR: Scratch-Pad RAM (DSPR) */

  .sdata2  :
  {
    *(.sdata.rodata)
    *(.sdata.rodata.*)
    . = ALIGN(8);
  } > DMI_DSPR

  /*
   * C++ exception handling tables.  NOTE: gcc emits .eh_frame
   * sections when compiling C sources with debugging enabled (-g).
   * If you can be sure that your final application consists
   * exclusively of C objects (i.e., no C++ objects), you may use
   * the -R option of the "strip" and "objcopy" utilities to remove
   * the .eh_frame section from the executable.
   */
  .eh_frame  :
  {
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = . ;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = . ;
    *(.jcr)
    . = ALIGN(8);
  } > PMI_PSPR /* PMI_PSPR: Scratch-Pad RAM (PSPR) */

  /*
   * We're done now with the text part of the executable.  The
   * following sections are special in that their initial code or
   * data (if any) must also be stored in said text part of an
   * executable, but they "live" at completely different addresses
   * at runtime -- usually in RAM areas.  NOTE: This is not really
   * necessary if you use a special program loader (e.g., a debugger)
   * to load a complete executable consisting of code, data, BSS, etc.
   * into the RAM of some target hardware or a simulator, but it *is*
   * necessary if you want to burn your application into non-volatile
   * memories such as EPROM or FLASH.
   */

  .sdata  :
  {
    . = ALIGN(8) ;
    SDATA_BASE = . ;
    PROVIDE(__sdata_start = .);
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
  } > DMI_DSPR /* DMI_DSPR: Local Data RAM (DSPR) */

  /*
   * Initialised data
   */
  .data  :
  {
    PROVIDE(__data_start = .);
    . = ALIGN(8) ;
    DATA_BASE = . ;
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
    . = ALIGN(8) ;
    DATA_END = . ;
    PROVIDE(__data_end = .);
  } > DMI_DSPR

  /*
   * Not initialised data in section ’.sbss’, addressable by small data area pointer (%a0)
   */
  .sbss (NOLOAD) : FLAGS(aws)
  {
    PROVIDE(__sbss_start = .);
    *(.sbss)
    _CONFIG_BEGIN_ = .;
    *(.sbss.CONFIG)
    _CONFIG_END_ = .;
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    PROVIDE(__sbss_end = .);
    . = ALIGN(8);
  } > DMI_DSPR /* DMI_DSPR: Local Data RAM (DSPR) */

  /*
   * Not Initialised data.
   * Allocate space for BSS sections.
   */
  .bss (NOLOAD) :
  {
    BSS_BASE = .;
    PROVIDE(__bss_start = .);
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)

    PROVIDE(__bss_end = .);
    . = ALIGN(8);
  } > DMI_DSPR /* DMI_DSPR: Local Data RAM (DSPR) */

  /* Erika RTOS Multicore global data */
  ee_mcglobald  :
  {
    KEEP(*(ee_mcglobald))
    . = ALIGN(8);
  } > LMU_SRAM

  /*
   * Section for ustack
   */  
  .ustack :
  {
    . = ALIGN(8);
     __USTACK_BEGIN = . ;
    . += __USTACK_SIZE ;
    . = ALIGN(8);
     __USTACK = . ;
     __USTACK_END = . ;
  } > DMI_DSPR

  /*
   * Section for istack
   */  
  .istack :
  {
    . = ALIGN(8);
     __ISTACK_BEGIN = . ;
    . += __ISTACK_SIZE ;
    . = ALIGN(8);
     __ISTACK = . ;
     __ISTACK_END = . ;
  } > DMI_DSPR

  /*
   * Section for heap
   */  
  .heap :
  {
    . = ALIGN(8);
     __HEAP_BEGIN = . ;
     __HEAP = . ;
    . += __HEAP_SIZE ;
    . = ALIGN(8);
     __HEAP_END = . ;
  } > DMI_DSPR

  /*
   * Section for CSA
   */  
  .csa :
  {
    . = ALIGN(64);
     __CSA_BEGIN = . ;
     __CSA = . ;
    . += __CSA_SIZE ;
    . = ALIGN(64);
     __CSA_END = . ;
  } > DMI_DSPR

  /* Make sure CSA, stack and heap addresses are properly aligned.  */
  _. = ASSERT ((__CSA_BEGIN & 0x3f) == 0 , "illegal CSA start address") ;
  _. = ASSERT ((__CSA_SIZE & 0x3f) == 0 , "illegal CSA size") ;
  _. = ASSERT ((__ISTACK & 7) == 0 , "ISTACK not doubleword aligned") ;
  _. = ASSERT ((__USTACK & 7) == 0 , "USTACK not doubleword aligned") ;
  /* _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not doubleword aligned") ; */

  /* Define a default symbol for address 0.  */
  NULL = DEFINED (NULL) ? NULL : 0 ;
  /*
   * DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the
   * beginning of the section, so we begin them at 0.
   */
  /*
   * DWARF 1
   */
  .comment         0 : { *(.comment) }
  .debug           0 : { *(.debug) }
  .line            0 : { *(.line) }
  /*
   * GNU DWARF 1 extensions
   */
  .debug_srcinfo   0 : { *(.debug_srcinfo) }
  .debug_sfnames   0 : { *(.debug_sfnames) }
  /*
   * DWARF 1.1 and DWARF 2
   */
  .debug_aranges   0 : { *(.debug_aranges) }
  .debug_pubnames  0 : { *(.debug_pubnames) }
  /*
   * DWARF 2
   */
  .debug_info      0 : { *(.debug_info) }
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }
  .debug_ranges    0 : { *(.debug_ranges) }
  /*
   * SGI/MIPS DWARF 2 extensions
   */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /*
   * Optional sections that may only appear when relocating.
   */
  /*
   * Optional sections that may appear regardless of relocating.
   */
  .version_info    0 : { *(.version_info) }
  .boffs           0 : { KEEP (*(.boffs)) }
}

