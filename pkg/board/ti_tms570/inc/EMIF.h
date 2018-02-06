#ifndef EMIF_CONFIG_H_
#define EMIF_CONFIG_H_

/*****************************************EMIF*****************************************************************************/
#define EMIF            0xFFFFE800 
#define NUM_EMIF_CS         4                     /*No of Chip Select*/
#define EMIF_CS0_ADDRMAP_START  0x60000000
#define EMIF_CS0_ADDRMAP_END    0x63FFFFFC
#define EMIF_CS1_ADDRMAP_START  0x64000000
#define EMIF_CS1_ADDRMAP_END    0x67FFFFFC
#define EMIF_CS2_ADDRMAP_START  0x68000000
#define EMIF_CS2_ADDRMAP_END    0x6BFFFFFC
#define EMIF_CS3_ADDRMAP_START  0x6C000000
#define EMIF_CS3_ADDRMAP_END    0x6FFFFFFC
/**************************************************************************************************************************/

extern void         EMIF_Init                   (void);

extern void         EMIF_ASYNC_MEM_CONFIG       ( unsigned int ASYNC_Mem_Config,
                                                  unsigned int ASYNC_MEM_READ_CONF,
                                                  unsigned int ASYNC_MEM_WRITE_CONF,
                                                  unsigned int ASYNC_MEM_TURN_ARND_CYC,
                                                  unsigned int Chip_Sel);

extern void         FILL_EMIF_MEMORY_32BIT      ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern void         FILL_EMIF_MEMORY_16BIT      ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern void         FILL_EMIF_MEMORY_8BIT       ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern unsigned int CHECK_EMIF_MEMORY_32BIT     ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern unsigned int CHECK_EMIF_MEMORY_16BIT     ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern unsigned int CHECK_EMIF_MEMORY_8BIT      ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern void         FILL_EMIF_MEMORY_32BIT_ADR  ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words);

extern unsigned int CHECK_EMIF_MEMORY_32BIT_ADR ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words);

extern void         FILL_EMIF_MEMORY_BACKWARD   ( unsigned int *Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern void      ENDLESS_EMIF_MEMORY_READ_16BIT ( unsigned int Start_Address );

extern unsigned int TEST_EMIF_MEMORY_32BIT      ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern unsigned int TEST_EMIF_MEMORY_16BIT      ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);
 
extern unsigned int TEST_EMIF_MEMORY_8BIT       ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words,
                                                  unsigned int Pattern);

extern unsigned int TEST_EMIF_MEMORY_ADR        ( unsigned int Start_Address, 
                                                  unsigned int No_Of_Words);

#endif /*EMIF_CONFIG_H_*/
