/************************************************************************/
/*  Name        : Confidence Test for TMS570 board                   */
/*                                                                      */
/*  Module      : EMIF_Config.c                                         */
/*                                                                      */
/*  Description : Initialization of external memory interface for       */
/*                external RAM and graphic LCD                          */
/*                                                                      */
/************************************************************************/
/*  Revision History :                                                  */
/*                                                                      */
/*  21-April-2010   1.0 (Initial)                                       */
/************************************************************************/

/* Includes ----------------------------------------------------------- */

#include "board/ti_tms570/inc/ee_board.h"


/* Defines ------------------------------------------------------------ */
#define ASYNC_MEM_CONF SELECT_STROBE_MODE_DISABLE | EXTEND_WAIT_MODE_DISABLE | ASIZE_16BIT_DATA

#if 1
#define READ_STROBE_SETUP_TIME 		0xF	
#define READ_STROBE_DURATION_TIME 	0x3F		
#define READ_STROBE_HOLD_TIME 		0x7	
#define WRITE_STROBE_SETUP_TIME     0xF     
#define WRITE_STROBE_DURATION_TIME  0x3F        
#define WRITE_STROBE_HOLD_TIME      0x7
#else
#define READ_STROBE_SETUP_TIME      0x0 
#define READ_STROBE_DURATION_TIME   0x00        
#define READ_STROBE_HOLD_TIME       0x0 
#define WRITE_STROBE_SETUP_TIME     0x0     
#define WRITE_STROBE_DURATION_TIME  0x00        
#define WRITE_STROBE_HOLD_TIME      0x0
#endif

/* Globals  ----------------------------------------------------------- */
EMIF_ST    *EMIF_Ptr = (EMIF_ST *)   EMIF;



void EMIF_Init (void) 
{
  unsigned int i;
  unsigned int ASYNC_MEM_READ_CONF;			
  unsigned int ASYNC_MEM_WRITE_CONF;		
  unsigned int ASYNC_MEM_TURN_ARND_CYC;
    
/* --------------------------------------------------------------------- */
/*	Configure the EMIF MPU Region to be Strongly Ordered 				 */
/* --------------------------------------------------------------------- */
	// Now configured by HALcogen
  //ENABLE_EMIF_STRONGLY_ORDERED();

/* --------------------------------------------------------------------- */
/*	Configure the EMIF timing for the external RAM (CS0) and LCD (CS2)   */
/* --------------------------------------------------------------------- */

  ASYNC_MEM_READ_CONF  = (READ_STROBE_HOLD_TIME | 
                         (READ_STROBE_DURATION_TIME <<3) | 
                         (READ_STROBE_SETUP_TIME <<9));			
  ASYNC_MEM_WRITE_CONF = (WRITE_STROBE_HOLD_TIME | 
                         (WRITE_STROBE_DURATION_TIME <<3)| 
                         (WRITE_STROBE_SETUP_TIME <<9));			

  ASYNC_MEM_TURN_ARND_CYC = 4;

  for(i=0;i<NUM_EMIF_CS;i++)
  {
    EMIF_ASYNC_MEM_CONFIG( (unsigned int) ASYNC_MEM_CONF,
                           ASYNC_MEM_READ_CONF,
                           ASYNC_MEM_WRITE_CONF,
                           ASYNC_MEM_TURN_ARND_CYC,
                           (Chip_Select) i);
  }

 /*   //Flash_Wait_State = 4;
    //Configure_Flash((Flash_Mode)NON_PIPE_LINE,Flash_Wait_State);*/
}

void FILL_EMIF_MEMORY_8BIT(unsigned int Start_Address, 
					   	   unsigned int No_Of_Words,
					   	   unsigned int Pattern)
{
    unsigned char *Addr = (unsigned char *) Start_Address;
	while(No_Of_Words > 0)
	{
		*Addr++ = (Pattern & 0xFF000000)>>24;
		*Addr++ = (Pattern & 0x00FF0000)>>16;
		*Addr++ = (Pattern & 0x0000FF00)>>8;
		*Addr++ = (Pattern & 0x000000FF);
		No_Of_Words--;
	}

}

void FILL_EMIF_MEMORY_16BIT(unsigned int Start_Address, 
					   	    unsigned int No_Of_Words,
					   	    unsigned int Pattern)
{
    unsigned short *Addr = (unsigned short *) Start_Address;
	while(No_Of_Words > 0)
	{
		*Addr++ = (Pattern & 0xFFFF0000)>>16;
		*Addr++ = (Pattern & 0x0000FFFF);
		No_Of_Words--;
	}

}

void FILL_EMIF_MEMORY_32BIT(unsigned int Start_Address, 
					        unsigned int No_Of_Words,
					        unsigned int Pattern)
{
    unsigned int *Addr = (unsigned int *) Start_Address;
	while(No_Of_Words > 0)
	{
		*Addr++ = Pattern;
		No_Of_Words--;
	}

}

void FILL_EMIF_MEMORY_32BIT_ADR(unsigned int Start_Address, 
                                unsigned int No_Of_Words)
{
    unsigned int *Addr   = (unsigned int *) Start_Address;
    while(No_Of_Words > 0)
    {
        *Addr++ = Start_Address++;
        No_Of_Words--;
    }

}

void FILL_EMIF_MEMORY_BACKWARD(unsigned int *Start_Address, 
					   unsigned int No_Of_Words,
					   unsigned int Pattern)
{
	while(No_Of_Words > 0)
	{
		*Start_Address-- = Pattern;
		No_Of_Words--;
	}

}

unsigned int CHECK_EMIF_MEMORY_8BIT( unsigned int Start_Address, 
                                     unsigned int No_Of_Words,
                                     unsigned int Pattern)
{
    unsigned int ReadPattern;
    unsigned char *Addr = (unsigned char *) Start_Address;
  
	while(No_Of_Words > 0)
	{
        ReadPattern  = *Addr++ << 24;
		ReadPattern += *Addr++ << 16;
        ReadPattern += *Addr++ <<  8;
        ReadPattern += *Addr++;
		if (ReadPattern != Pattern)
		{
			return ((unsigned int)Addr);
		}
		No_Of_Words--;
	}
	return (0);
}

unsigned int CHECK_EMIF_MEMORY_16BIT( unsigned int Start_Address, 
                                      unsigned int No_Of_Words,
                                      unsigned int Pattern)
{
    unsigned int ReadPattern;
    unsigned short *Addr = (unsigned short *) Start_Address;
  
    while(No_Of_Words > 0)
    {
        ReadPattern  = *Addr++ << 16;
        ReadPattern += *Addr++;
        if (ReadPattern != Pattern)
        {
            return ((unsigned int)Addr);
        }
        No_Of_Words--;
    }
    return (0);
}

unsigned int CHECK_EMIF_MEMORY_32BIT( unsigned int Start_Address, 
                                      unsigned int No_Of_Words,
                                      unsigned int Pattern)
{
    unsigned int ReadPattern;
    unsigned int *Addr = (unsigned int *) Start_Address;
  
    while(No_Of_Words > 0)
    {
        ReadPattern = *Addr++;
        if (ReadPattern != Pattern)
        {
            return ((unsigned int)Addr);
        }
        No_Of_Words--;
    }
    return (0);
}

unsigned int CHECK_EMIF_MEMORY_32BIT_ADR( unsigned int Start_Address, 
                                          unsigned int No_Of_Words)
{
    unsigned int ReadPattern;
    unsigned int *Addr = (unsigned int *) Start_Address;
  
    while(No_Of_Words > 0)
    {
        ReadPattern = *Addr++;
        if (ReadPattern != Start_Address)
        {
            return (Start_Address);
        }
        No_Of_Words--;
        Start_Address++;
    }
    return (0);
}


void Ext_Async_Mem_Write(unsigned int* Ext_Mem_Address_Ptr,
						 unsigned int* Data_To_Write_Ptr,
						 unsigned int No_Of_32BitData)
{
	   while(No_Of_32BitData > 0)
	   {
			*Ext_Mem_Address_Ptr++ = *Data_To_Write_Ptr++;
		   No_Of_32BitData--;
	   }
}



unsigned int Calc_CheckSum(unsigned int *Data_To_Write_Ptr,unsigned int No_Of_32BitData)
{
	unsigned int CheckSum;
	CheckSum = 0;
    while(No_Of_32BitData > 0)
    {
		CheckSum = CheckSum + *Data_To_Write_Ptr++;
	   	No_Of_32BitData--;
	}
	return CheckSum;
}


void EMIF_ASYNC_MEM_CONFIG(	unsigned int ASYNC_Mem_Config,
							unsigned int ASYNC_MEM_READ_CONF,
							unsigned int ASYNC_MEM_WRITE_CONF,
							unsigned int ASYNC_MEM_TURN_ARND_CYC,
							unsigned int Chip_Sel)
{

    EMIF_Ptr->ASYNC_CR_UN[Chip_Sel].ASYNC_CR_UL = (ASYNC_Mem_Config |
    											  (ASYNC_MEM_TURN_ARND_CYC << 2) |
    											  (ASYNC_MEM_READ_CONF << 4) |
    											  (ASYNC_MEM_WRITE_CONF<< 17));
}

void ENDLESS_EMIF_MEMORY_READ_16BIT( unsigned int Start_Address)
{
  unsigned short volatile ReadPattern;
  unsigned short *Addr = (unsigned short *) Start_Address;
  
  while(1)
  {
    ReadPattern  = *Addr;
  }
}

unsigned int TEST_EMIF_MEMORY_32BIT( unsigned int Start_Address, 
                                     unsigned int No_Of_Words,
                                     unsigned int Pattern)
{
    unsigned int error;
  
//  Fill the EMIF Memory with data Patterns using 32 bit accesses
    FILL_EMIF_MEMORY_32BIT(Start_Address, No_Of_Words,Pattern);

//  check the EMIF Memory Patterns using 32 bit accesses
    error = CHECK_EMIF_MEMORY_32BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

//  Check the EMIF Memory Patterns using 16 bit accesses
    error = CHECK_EMIF_MEMORY_16BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

//  Check the EMIF Memory Patterns using 8 bit accesses
    error = CHECK_EMIF_MEMORY_8BIT (Start_Address, No_Of_Words,Pattern);
    return (error);
}

unsigned int TEST_EMIF_MEMORY_16BIT( unsigned int Start_Address, 
                                     unsigned int No_Of_Words,
                                     unsigned int Pattern)
{
    unsigned int error;
//  Fill the EMIF Memory with data Patterns using 16 bit accesses
    FILL_EMIF_MEMORY_16BIT(Start_Address, No_Of_Words,Pattern);

//  Check the EMIF Memory Patterns using 32 bit accesses
    error = CHECK_EMIF_MEMORY_32BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

//  Check the EMIF Memory Patterns using 16 bit accesses
    error = CHECK_EMIF_MEMORY_16BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

//  Check the EMIF Memory Patterns using 8 bit accesses
    error = CHECK_EMIF_MEMORY_8BIT (Start_Address, No_Of_Words,Pattern);
    return (error);
}
 
unsigned int TEST_EMIF_MEMORY_8BIT( unsigned int Start_Address, 
                                    unsigned int No_Of_Words,
                                    unsigned int Pattern)
{
    unsigned int error;
//  Fill the EMIF Memory with data Patterns using 8 bit accesses
    FILL_EMIF_MEMORY_8BIT(Start_Address, No_Of_Words,Pattern);

// Check the EMIF Memory Patterns using 32 bit accesses
    error = CHECK_EMIF_MEMORY_32BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

// Check the EMIF Memory Patterns using 16 bit accesses
    error = CHECK_EMIF_MEMORY_16BIT (Start_Address, No_Of_Words,Pattern);
    if (error) return (error);

// Check the EMIF Memory Patterns using 8 bit accesses
    error = CHECK_EMIF_MEMORY_8BIT (Start_Address, No_Of_Words,Pattern);
    return (error);
}

unsigned int TEST_EMIF_MEMORY_ADR ( unsigned int Start_Address, 
                                    unsigned int No_Of_Words)
{
    unsigned int error;
//  Fill the EMIF Memory with an incremented number using 32 bit accesses
    FILL_EMIF_MEMORY_32BIT_ADR(Start_Address, No_Of_Words);

// Check the EMIF Memory against an incremented number using 32 bit accesses
    error = CHECK_EMIF_MEMORY_32BIT_ADR (Start_Address, No_Of_Words);
    return (error);
}
