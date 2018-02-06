/* ------------------------------------------------------------------------- */
/* EMIF.h : EMIF Module Definitions				     	     				 */
/*                                                                           */
/* Copyright (c) Texas Instruments 1997, All right reserved.                 */
/*                                                                           */
/* History:                                                                  */
/*    Rev 1.0  07.07.07  Prathap Srinivasan   - prathap@ti.com               */
/*                                                                           */
/*                       Definition of EMIF Register set  	             	 */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ----------------- USEFUL Definitions ------------------------------------ */
/* ------------------------------------------------------------------------- */

#if defined(_TMS470_BIG) || defined(__big_endian__)
typedef unsigned char Chip_Select;

#define CS0		       0x00000000
#define CS1		       0x00000001
#define CS2		       0x00000002
#define CS3		       0x00000003
#define CS4		       0x00000004
#define CS5		       0x00000005
#define CS6		       0x00000006
#define CS7		       0x00000007

typedef unsigned int Flash_Mode;
#define PIPE_LINE      0x00000001
#define NON_PIPE_LINE  0x00000000

typedef unsigned int Async_Memory_Config;

#define SELECT_STROBE_MODE_ENABLE   0x80000000
#define EXTEND_WAIT_MODE_ENABLE     0x40000000
#define SELECT_STROBE_MODE_DISABLE	0x00000000
#define EXTEND_WAIT_MODE_DISABLE	0x00000000
#define ASIZE_8BIT_DATA       		0x00000000
#define ASIZE_16BIT_DATA      		0x00000001
#define ASIZE_32BIT_DATA      		0x00000002

/* ------------------------------------------------------------------------- */
/* --------------- Definitiopn of the EMIF Register Map -------------------- */
/* ------------------------------------------------------------------------- */


typedef volatile struct
{
    union                                      /* 0x00      */
    {
     unsigned int RCSR_UL; 
     struct
     {
     unsigned int BE_B1: 1;
     unsigned int FR_B1: 1;
     unsigned int MODULE_ID_B14: 14;
     unsigned int MAJOR_REVISION_B8: 8;
     unsigned int MINOR_REVISION_B8: 8;
     }RCSR_ST;
    }RCSR_UN;

    union                                      /* 0x04      */
    {
     unsigned int ASYNC_WCCR_UL; 
     struct
     {
     unsigned int WP3_B1: 1;
     unsigned int WP2_B1: 1;
     unsigned int WP1_B1: 1;
     unsigned int WP0_B1: 1;
     unsigned int : 4;
     unsigned int CS5_WAIT: 2;
     unsigned int CS4_WAIT: 2;
     unsigned int CS3_WAIT: 2;
     unsigned int CS2_WAIT: 2;
     unsigned int : 8;
     unsigned int MAX_EXT_WAIT_B8: 8;
	 }ASYNC_WCCR_ST;
    }ASYNC_WCCR_UN;

    union                                      /* 0x08      */
    {
     unsigned int SDRAM_CR_UL; 
     struct
     {
     unsigned int SR_B1: 1;
     unsigned int PD_B1: 1;
     unsigned int PDWR_B1: 1;
     unsigned int : 11;
     unsigned int DDR_DR_ST_B1: 1;
     unsigned int BIT_17_LOCK_B1: 1;
     unsigned int : 1;
     unsigned int NM_B1: 1;
     unsigned int DISABLE_DDR_DLL_B1: 1;
     unsigned int BIT_13_LOCK_B1: 1;
     unsigned int CL_B3: 3;
     unsigned int BIT_11_9_LOCK_B1: 1;                        
     unsigned int : 1;
     unsigned int IBANK_B3: 3;
     unsigned int EBANK_B1: 1;
     unsigned int PAGESIZE_B3: 3;
     }SDRAM_CR_ST;
    }SDRAM_CR_UN;


    union                                      /* 0x0C      */
    {
     unsigned int SDRAM_RCR_UL; 
     struct
     {
     unsigned int : 13;
     unsigned int DDR_REF_THRESH_B3: 3;                        
     unsigned int : 3;
     unsigned int REFRESH_RATE_B13: 13;
     }SDRAM_RCR_ST;
    }SDRAM_RCR_UN;

    union                                      /* 0x10,0X14,0X18,0X1C     */
    {
     unsigned int ASYNC_CR_UL; 
     struct
     {
     unsigned int SS_B1: 1;                        
     unsigned int EW_B1: 1;                        
     unsigned int W_SETUP_B4: 4;
     unsigned int W_STROBE_B6: 6;
     unsigned int W_HOLD_B3: 3;
     unsigned int R_SETUP_B4: 4;
     unsigned int R_STROBE_B6: 6;
     unsigned int R_HOLD_B3: 3;
     unsigned int TA_B2: 2;
     unsigned int ASIZE_B2: 2;
     }ASYNC_CR_ST;
    }ASYNC_CR_UN[4];

    union                                      /* 0x20     */
    {
     unsigned int SDRAM_TR_UL; 
     struct
     {
     unsigned int T_RFC_B5: 5;
     unsigned int T_RP_B3: 3;
     unsigned int : 1;
     unsigned int T_RCD_B4: 4;
     unsigned int : 1;
     unsigned int T_WR_B3: 3;
     unsigned int T_RAS_B4: 4;
     unsigned int T_RC_B4: 4;
     unsigned int : 1;
     unsigned int T_RRD_B3: 3;
     unsigned int : 4;
     }SDRAM_TR_ST;
    }SDRAM_TR_UN;

    union                                      /* 0x24     */
    {
     unsigned int DDR_SR_UL; 
     struct
     {
     unsigned int : 28;
     unsigned int PHY_DLL_READY_B1: 1;
     unsigned int : 2;
     unsigned int DDR_B1: 1;
     }DDR_SR_ST;
    }DDR_SR_UN;

    union                                      /* 0x28     */
    {
     unsigned int DDR_PHY_CR_UL; 
     struct
     {
     unsigned int DDR_PHY_CTRL_B32: 32;
     }DDR_PHY_CR_ST;
    }DDR_PHY_CR_UN;

    union                                      /* 0x2C     */
    {
     unsigned int DDR_PHY_SR_UL; 
     struct
     {
     unsigned int DDR_PHY_STAT_B32: 32;
     }DDR_PHY_SR_ST;
    }DDR_PHY_SR_UN;

    union                                      /* 0x30     */
    {
     unsigned int TOTAL_SDRAM_AR_UL; 
     struct
     {
     unsigned int TOTAL_ACCESSES_B32: 32;
     }TOTAL_SDRAM_AR_ST;
    }TOTAL_SDRAM_AR_UN;

    union                                      /* 0x34     */
    {
     unsigned int TOTAL_SDRAM_ACTR_UL; 
     struct
     {
     unsigned int TOTAL_ACTIVATE_B32: 32;
     }TOTAL_SDRAM_ACTR_ST;
    }TOTAL_SDRAM_ACTR_UN;

    unsigned int : 32;   			/* 0x38     */
    unsigned int : 32;   			/* 0x3C     */
    unsigned int : 32;   			/* 0x40     */
    unsigned int : 32;   			/* 0x44     */
    unsigned int : 32;   			/* 0x48     */
    unsigned int : 32;   			/* 0x4c     */
    unsigned int : 32;   			/* 0x50     */
    unsigned int : 32;   			/* 0x54     */
    unsigned int : 32;   			/* 0x58     */

    union                                      /* 0x5c     */
    {
     unsigned int ONENAND_FLASH_CTRL_UL; 
     struct
     {
     unsigned int : 21;
     unsigned int rd_latency_B3 : 3;
     unsigned int cs5_sync_rd_B1 : 1;
     unsigned int cs4_sync_rd_B1 : 1;
     unsigned int cs3_sync_rd_B1 : 1;
     unsigned int cs2_sync_rd_B1 : 1;
     unsigned int cs5_use_1nand_B1 : 1;
     unsigned int cs4_use_1nand_B1 : 1;
     unsigned int cs3_use_1nand_B1 : 1;
     unsigned int cs2_use_1nand_B1 : 1;
     }ONENAND_FLASH_CTRL_ST;
    }ONENAND_FLASH_CTRL_UN;

    union                                      /* 0x60     */
    {
     unsigned int NAND_FLASH_CTRL_UL; 
     struct
     {
     unsigned int : 20;
     unsigned int cs5_ecc_start_B1 : 1;
     unsigned int cs4_ecc_start_B1 : 1;
     unsigned int cs3_ecc_start_B1 : 1;
     unsigned int cs2_ecc_start_B1 : 1;
     unsigned int : 4;
     unsigned int cs5_use_nand_B1 : 1;
     unsigned int cs4_use_nand_B1 : 1;
     unsigned int cs3_use_nand_B1 : 1;
     unsigned int cs2_use_nand_B1 : 1;
     }NAND_FLASH_CTRL_ST;
    }NAND_FLASH_CTRL_UN;


    union                                      /* 0x64     */
    {
     unsigned int NAND_Flash_STATUS_UL; 
     struct
     {
     unsigned int : 4;
     unsigned int wait_state_B4 : 4;
     }NAND_Flash_STATUS_ST;
    }NAND_Flash_STATUS_UN;

    union                                      /* 0x68     */
    {
     unsigned int PAGE_MODE_CONTROL_UL; 
     struct
     {
     unsigned int cs5_pg_del_B6 : 6;
     unsigned int cs5_pg_size_B1 : 1;
     unsigned int cs5_pg_md_en_B1 : 1;
     unsigned int cs4_pg_del_B6 : 6;
     unsigned int cs4_pg_size_B1 : 1;
     unsigned int cs4_pg_md_en_B1 : 1;     
     unsigned int cs3_pg_del_B6 : 6;
     unsigned int cs3_pg_size_B1 : 1;
     unsigned int cs3_pg_md_en_B1 : 1;
     unsigned int cs2_pg_del_B6 : 6;
     unsigned int cs2_pg_size_B1 : 1;
     unsigned int cs2_pg_md_en_B1 : 1;
     }PAGE_MODE_CONTROL_ST;
    }PAGE_MODE_CONTROL_UN;

    unsigned int : 32;   			/* 0x6C     */
    unsigned int : 32;   			/* 0x70     */
    unsigned int : 32;   			/* 0x74     */
    unsigned int : 32;   			/* 0x78     */
    unsigned int : 32;   			/* 0x7C     */
    unsigned int : 32;   			/* 0x80     */
    unsigned int : 32;   			/* 0x84     */
    unsigned int : 32;   			/* 0x88     */
    unsigned int : 32;   			/* 0x8C     */
    unsigned int : 32;   			/* 0x90     */
    unsigned int : 32;   			/* 0x94     */
    unsigned int : 32;   			/* 0x98     */
    unsigned int : 32;   			/* 0x9C     */
    unsigned int : 32;   			/* 0xA0     */
    unsigned int : 32;   			/* 0xA4     */
    unsigned int : 32;   			/* 0xA8     */
    unsigned int : 32;   			/* 0xAC     */
    unsigned int : 32;   			/* 0xB0     */

}EMIF_ST;

/* ------------------------------------------------------------------------- */
/* ------------------------- e_EMIF_ST 	------------------------------------ */		
/* ------------------------------------------------------------------------- */
extern EMIF_ST e_EMIF_ST;

extern EMIF_ST* EMIF_Ptr;
/* ------------------------------------------------------------------------- */

#elif defined(_TMS470_LITTLE) || defined(__little_endian__)
typedef unsigned char Chip_Select;

#define CS0		       0x00000000
#define CS1		       0x00000001
#define CS2		       0x00000002
#define CS3		       0x00000003
#define CS4		       0x00000004
#define CS5		       0x00000005
#define CS6		       0x00000006
#define CS7		       0x00000007

typedef unsigned int Flash_Mode;
#define PIPE_LINE      0x00000001
#define NON_PIPE_LINE  0x00000000

typedef unsigned int Async_Memory_Config;

#define SELECT_STROBE_MODE_ENABLE   0x80000000
#define EXTEND_WAIT_MODE_ENABLE     0x40000000
#define SELECT_STROBE_MODE_DISABLE	0x00000000
#define EXTEND_WAIT_MODE_DISABLE	0x00000000
#define ASIZE_8BIT_DATA       		0x00000000
#define ASIZE_16BIT_DATA      		0x00000001
#define ASIZE_32BIT_DATA      		0x00000002

/* ------------------------------------------------------------------------- */
/* --------------- Definitiopn of the EMIF Register Map -------------------- */
/* ------------------------------------------------------------------------- */


typedef volatile struct
{
    union                                      /* 0x00      */
    {
     unsigned int RCSR_UL; 
     struct
     {
     unsigned int MINOR_REVISION_B8: 8;
     unsigned int MAJOR_REVISION_B8: 8;
     unsigned int MODULE_ID_B14: 14;
     unsigned int FR_B1: 1;
     unsigned int BE_B1: 1;
     }RCSR_ST;
    }RCSR_UN;

    union                                      /* 0x04      */
    {
     unsigned int ASYNC_WCCR_UL; 
     struct
     {
     unsigned int MAX_EXT_WAIT_B8: 8;
     unsigned int : 8;
     unsigned int CS2_WAIT: 2;
     unsigned int CS3_WAIT: 2;
     unsigned int CS4_WAIT: 2;
     unsigned int CS5_WAIT: 2;
     unsigned int : 4;
     unsigned int WP0_B1: 1;
     unsigned int WP1_B1: 1;
     unsigned int WP2_B1: 1;
     unsigned int WP3_B1: 1;
	 }ASYNC_WCCR_ST;
    }ASYNC_WCCR_UN;

    union                                      /* 0x08      */
    {
     unsigned int SDRAM_CR_UL; 
     struct
     {
     unsigned int PAGESIZE_B3: 3;
     unsigned int EBANK_B1: 1;
     unsigned int IBANK_B3: 3;
     unsigned int : 1;
     unsigned int BIT_11_9_LOCK_B1: 1;                        
     unsigned int CL_B3: 3;
     unsigned int BIT_13_LOCK_B1: 1;
     unsigned int DISABLE_DDR_DLL_B1: 1;
     unsigned int NM_B1: 1;
     unsigned int : 1;
     unsigned int BIT_17_LOCK_B1: 1;
     unsigned int DDR_DR_ST_B1: 1;
     unsigned int : 11;
     unsigned int PDWR_B1: 1;
     unsigned int PD_B1: 1;
     unsigned int SR_B1: 1;
     }SDRAM_CR_ST;
    }SDRAM_CR_UN;


    union                                      /* 0x0C      */
    {
     unsigned int SDRAM_RCR_UL; 
     struct
     {
     unsigned int REFRESH_RATE_B13: 13;
     unsigned int : 3;
     unsigned int DDR_REF_THRESH_B3: 3;                        
     unsigned int : 13;
     }SDRAM_RCR_ST;
    }SDRAM_RCR_UN;

    union                                      /* 0x10,0X14,0X18,0X1C     */
    {
     unsigned int ASYNC_CR_UL; 
     struct
     {
     unsigned int ASIZE_B2: 2;
     unsigned int TA_B2: 2;
     unsigned int R_HOLD_B3: 3;
     unsigned int R_STROBE_B6: 6;
     unsigned int R_SETUP_B4: 4;
     unsigned int W_HOLD_B3: 3;
     unsigned int W_STROBE_B6: 6;
     unsigned int W_SETUP_B4: 4;
     unsigned int EW_B1: 1;                        
     unsigned int SS_B1: 1;                        
     }ASYNC_CR_ST;
    }ASYNC_CR_UN[4];

    union                                      /* 0x20     */
    {
     unsigned int SDRAM_TR_UL; 
     struct
     {
     unsigned int : 4;
     unsigned int T_RRD_B3: 3;
     unsigned int : 1;
     unsigned int T_RC_B4: 4;
     unsigned int T_RAS_B4: 4;
     unsigned int T_WR_B3: 3;
     unsigned int : 1;
     unsigned int T_RCD_B4: 4;
     unsigned int : 1;
     unsigned int T_RP_B3: 3;
     unsigned int T_RFC_B5: 5;
     }SDRAM_TR_ST;
    }SDRAM_TR_UN;

    union                                      /* 0x24     */
    {
     unsigned int DDR_SR_UL; 
     struct
     {
     unsigned int DDR_B1: 1;
     unsigned int : 2;
     unsigned int PHY_DLL_READY_B1: 1;
     unsigned int : 28;
     }DDR_SR_ST;
    }DDR_SR_UN;

    union                                      /* 0x28     */
    {
     unsigned int DDR_PHY_CR_UL; 
     struct
     {
     unsigned int DDR_PHY_CTRL_B32: 32;
     }DDR_PHY_CR_ST;
    }DDR_PHY_CR_UN;

    union                                      /* 0x2C     */
    {
     unsigned int DDR_PHY_SR_UL; 
     struct
     {
     unsigned int DDR_PHY_STAT_B32: 32;
     }DDR_PHY_SR_ST;
    }DDR_PHY_SR_UN;

    union                                      /* 0x30     */
    {
     unsigned int TOTAL_SDRAM_AR_UL; 
     struct
     {
     unsigned int TOTAL_ACCESSES_B32: 32;
     }TOTAL_SDRAM_AR_ST;
    }TOTAL_SDRAM_AR_UN;

    union                                      /* 0x34     */
    {
     unsigned int TOTAL_SDRAM_ACTR_UL; 
     struct
     {
     unsigned int TOTAL_ACTIVATE_B32: 32;
     }TOTAL_SDRAM_ACTR_ST;
    }TOTAL_SDRAM_ACTR_UN;

    unsigned int : 32;   			/* 0x38     */
    unsigned int : 32;   			/* 0x3C     */
    unsigned int : 32;   			/* 0x40     */
    unsigned int : 32;   			/* 0x44     */
    unsigned int : 32;   			/* 0x48     */
    unsigned int : 32;   			/* 0x4c     */
    unsigned int : 32;   			/* 0x50     */
    unsigned int : 32;   			/* 0x54     */
    union                                      /* 0x5c     */
    {
     unsigned int ONENAND_FLASH_CTRL_UL; 
     struct
     {
     unsigned int : 21;
     unsigned int rd_latency_B3 : 3;
     unsigned int cs5_sync_rd_B1 : 1;
     unsigned int cs4_sync_rd_B1 : 1;
     unsigned int cs3_sync_rd_B1 : 1;
     unsigned int cs2_sync_rd_B1 : 1;
     unsigned int cs5_use_1nand_B1 : 1;
     unsigned int cs4_use_1nand_B1 : 1;
     unsigned int cs3_use_1nand_B1 : 1;
     unsigned int cs2_use_1nand_B1 : 1;
     }ONENAND_FLASH_CTRL_ST;
    }ONENAND_FLASH_CTRL_UN;

    union                                      /* 0x60     */
    {
     unsigned int NAND_FLASH_CTRL_UL; 
     struct
     {
     unsigned int : 20;
     unsigned int cs5_ecc_start_B1 : 1;
     unsigned int cs4_ecc_start_B1 : 1;
     unsigned int cs3_ecc_start_B1 : 1;
     unsigned int cs2_ecc_start_B1 : 1;
     unsigned int : 4;
     unsigned int cs5_use_nand_B1 : 1;
     unsigned int cs4_use_nand_B1 : 1;
     unsigned int cs3_use_nand_B1 : 1;
     unsigned int cs2_use_nand_B1 : 1;
     }NAND_FLASH_CTRL_ST;
    }NAND_FLASH_CTRL_UN;


    union                                      /* 0x64     */
    {
     unsigned int NAND_Flash_STATUS_UL; 
     struct
     {
     unsigned int : 4;
     unsigned int wait_state_B4 : 4;
     }NAND_Flash_STATUS_ST;
    }NAND_Flash_STATUS_UN;

    union                                      /* 0x68     */
    {
     unsigned int PAGE_MODE_CONTROL_UL; 
     struct
     {
     unsigned int cs5_pg_del_B6 : 6;
     unsigned int cs5_pg_size_B1 : 1;
     unsigned int cs5_pg_md_en_B1 : 1;
     unsigned int cs4_pg_del_B6 : 6;
     unsigned int cs4_pg_size_B1 : 1;
     unsigned int cs4_pg_md_en_B1 : 1;     
     unsigned int cs3_pg_del_B6 : 6;
     unsigned int cs3_pg_size_B1 : 1;
     unsigned int cs3_pg_md_en_B1 : 1;
     unsigned int cs2_pg_del_B6 : 6;
     unsigned int cs2_pg_size_B1 : 1;
     unsigned int cs2_pg_md_en_B1 : 1;
     }PAGE_MODE_CONTROL_ST;
    }PAGE_MODE_CONTROL_UN;

    unsigned int : 32;   			/* 0x6C     */
    unsigned int : 32;   			/* 0x70     */
    unsigned int : 32;   			/* 0x74     */
    unsigned int : 32;   			/* 0x78     */
    unsigned int : 32;   			/* 0x7C     */
    unsigned int : 32;   			/* 0x80     */
    unsigned int : 32;   			/* 0x84     */
    unsigned int : 32;   			/* 0x88     */
    unsigned int : 32;   			/* 0x8C     */
    unsigned int : 32;   			/* 0x90     */
    unsigned int : 32;   			/* 0x94     */
    unsigned int : 32;   			/* 0x98     */
    unsigned int : 32;   			/* 0x9C     */
    unsigned int : 32;   			/* 0xA0     */
    unsigned int : 32;   			/* 0xA4     */
    unsigned int : 32;   			/* 0xA8     */
    unsigned int : 32;   			/* 0xAC     */
    unsigned int : 32;   			/* 0xB0     */

}EMIF_ST;

/* ------------------------------------------------------------------------- */
/* ------------------------- e_EMIF_ST 	------------------------------------ */		
/* ------------------------------------------------------------------------- */
extern EMIF_ST e_EMIF_ST;

extern EMIF_ST* EMIF_Ptr;
/* ------------------------------------------------------------------------- */

#endif
