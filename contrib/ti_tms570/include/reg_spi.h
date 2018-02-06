/** @file reg_spi.h
*   @brief SPI Register Layer Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the SPI driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __REG_SPI_H__
#define __REG_SPI_H__

#include "sys_common.h"
#include "reg_gio.h"


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Spi Register Frame Definition */
/** @struct spiBase
*   @brief SPI Register Definition
*
*   This structure is used to access the SPI module egisters.
*/
/** @typedef spiBASE_t
*   @brief SPI Register Frame Type Definition
*
*   This type is used to access the SPI Registers.
*/
typedef volatile struct spiBase
{
    uint32  GCR0;                 /**< 0x0000: Global Control 0 */
    uint32  GCR1;                 /**< 0x0004: Global Control 1 */	
    uint32  INT0;                 /**< 0x0008: Interrupt Register */	
    uint32  LVL;                  /**< 0x000C: Interrupt Level */
    uint32  FLG;                  /**< 0x0010: Interrupt flags */	
    uint32  PCFUN;                /**< 0x0014: Function Pin Enable */
    uint32  PCDIR;                /**< 0x0018: Pin Direction */
    uint32  PCDIN;                /**< 0x001C: Pin Input Latch */
    uint32  PCDOUT;               /**< 0x0020: Pin Output Latch */
    uint32  PCSET;                /**< 0x0024: Output Pin Set */
    uint32  PCCLR;                /**< 0x0028: Output Pin Clr */
    uint32  PCPDR;                /**< 0x002C: Open Drain Output Enable */
    uint32  PCDIS;                /**< 0x0030: Pullup/Pulldown Disable */
    uint32  PCPSL;                /**< 0x0034: Pullup/Pulldown Selection */
    uint32  DAT0;                 /**< 0x0038: Transmit Data */
    uint32  DAT1;                 /**< 0x003C: Transmit Data with Format and Chip Select */
    uint32  BUF;                  /**< 0x0040: Receive Buffer */
    uint32  EMU;                  /**< 0x0044: Emulation Receive Buffer */
    uint32  DELAY;                /**< 0x0048: Delays */
    uint32  CSDEF;                /**< 0x004C: Default Chip Select */
    uint32  FMT0;                 /**< 0x0050: Data Format 0 */
    uint32  FMT1;                 /**< 0x0054: Data Format 1 */
    uint32  FMT2;                 /**< 0x0058: Data Format 2 */
    uint32  FMT3;                 /**< 0x005C: Data Format 3 */
    uint32  INTVECT0;             /**< 0x0060: Interrupt Vector 0 */
    uint32  INTVECT1;             /**< 0x0064: Interrupt Vector 1 */
    uint32  SRSEL;                /**< 0x0068: Slew Rate Select */
    uint32  PMCTRL;               /**< 0x006C: Parallel Mode Control */
    uint32  MIBSPIE;              /**< 0x0070: Multi-buffer Mode Enable  */
    uint32  TGITENST;             /**< 0x0074: TG Interrupt Enable Set */
    uint32  TGITENCR;             /**< 0x0078: TG Interrupt Enable Clear */
    uint32  TGITLVST;             /**< 0x007C: Transfer Group Interrupt Level Set */
    uint32  TGITLVCR;             /**< 0x0080: Transfer Group Interrupt Level Clear */
    uint32  TGINTFLG;             /**< 0x0084: Transfer Group Interrupt Flag */	
    uint32    rsvd1[2U];           /**< 0x0088: Reserved */
    uint32  TICKCNT;              /**< 0x0090: Tick Counter */
    uint32  LTGPEND;              /**< 0x0090: Last TG End Pointer */	
    uint32  TGCTRL[16U];          /**< 0x0098 - 0x00D4: Transfer Group Control */
    uint32  DMACTRL[8U];          /**< 0x00D8 - 0x00F4: DMA Control */
    uint32  DMACOUNT[8U];         /**< 0x00F8 - 0x0114: DMA Count */
    uint32  DMACNTLEN;            /**< 0x0118 - 0x0114: DMA Control length */
    uint32    rsvd2;              /**< 0x011C: Reserved */
    uint32  UERRCTRL;             /**< 0x0120: Multi-buffer RAM Uncorrectable Parity Error Control */	
    uint32  UERRSTAT;             /**< 0x0124: Multi-buffer RAM Uncorrectable Parity Error Status */	  
    uint32  UERRADDRRX;           /**< 0x0128: RXRAM Uncorrectable Parity Error Address */	
    uint32  UERRADDRTX;           /**< 0x012C: TXRAM Uncorrectable Parity Error Address */	
    uint32  RXOVRN_BUF_ADDR;      /**< 0x0130: RXRAM Overrun Buffer Address */
    uint32  IOLPKTSTCR;           /**< 0x0134: IO loopback */
} spiBASE_t;


/** @def spiREG1
*   @brief SPI1 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG1 ((spiBASE_t *)0xFFF7F400U)


/** @def spiPORT1
*   @brief SPI1 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI1
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT1 ((gioPORT_t *)0xFFF7F418U)


/** @def spiREG3
*   @brief SPI3 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG3 ((spiBASE_t *)0xFFF7F800U)


/** @def spiPORT3
*   @brief SPI3 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI3
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT3 ((gioPORT_t *)0xFFF7F818U)


/** @def spiREG5
*   @brief SPI5 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG5 ((spiBASE_t *)0xFFF7FC00U)


/** @def spiPORT5
*   @brief SPI5 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI5
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT5 ((gioPORT_t *)0xFFF7FC18U)


/** @struct spiRamBase
*   @brief SPI Buffer RAM Definition
*
*   This structure is used to access the SPI buffer memory.
*/
/** @typedef spiRAM_t
*   @brief SPI RAM Type Definition
*
*   This type is used to access the SPI RAM.
*/
typedef volatile struct spiRamBase
{
    struct 
    {
     uint16  control;  /**< tx buffer control */  
     uint16  data;     /**< tx buffer data    */
    } tx[128];
    struct
    {
	 uint16 flags;    /**< rx buffer flags */
     uint16 data;     /**< rx buffer data  */
    } rx[128];
} spiRAM_t;


/** @def spiRAM1
*   @brief SPI1 Buffer RAM Pointer
*
*   This pointer is used by the SPI driver to access the spi buffer memory.
*/
#define spiRAM1 ((spiRAM_t *)0xFF0E0000U)


/** @def spiRAM3
*   @brief SPI3 Buffer RAM Pointer
*
*   This pointer is used by the SPI driver to access the spi buffer memory.
*/
#define spiRAM3 ((spiRAM_t *)0xFF0C0000U)


/** @def spiRAM5
*   @brief SPI5 Buffer RAM Pointer
*
*   This pointer is used by the SPI driver to access the spi buffer memory.
*/
#define spiRAM5 ((spiRAM_t *)0xFF0A0000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
