#include "mcu/microchip_pic32/inc/ee_spi.h"
#include "cpu/pic32/inc/ee_utils.h"

#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
#define MCHP_SPICON_MASKS (EE_SPI_MASTER | EE_SPI_SDO_ON_CLOCK_TO_IDLE | \
			   EE_SPI_CLOCK_IDLE_HIGH | EE_SPI_SDI_ON_CLOCK_END)

#define IS_MASTER(flags)	((flags) & EE_SPI_MASTER)
#define IS_DMA_TX(flags) 	((flags) & EE_SPI_DMA_TX)
#define IS_DMA_RX(flags) 	((flags) & EE_SPI_DMA_RX)

//#define ADDR_VIRTUAL_TO_PHYSICAL(a) (((EE_UREG)(a)) & 0x1FFFFFFF)


/******************************************************************************/
/*			 Check SPI PORT 1 settings (with defaults) 	      */
/******************************************************************************/

#ifdef __32MX360F512L__

/* Check SPI PORT 1 settings (with defaults) */
#ifndef EE_SPI_PORT1_DCHCON
#define EE_SPI_PORT1_DCHCON(m)	DCH0CON		##m	
#endif
#define SPI1_DCHCON	EE_SPI_PORT1_DCHCON()
#define SPI1_DCHCONSET	EE_SPI_PORT1_DCHCON(SET)
#define SPI1_DCHCONCLR	EE_SPI_PORT1_DCHCON(CLR)
#define SPI1_DCHCONINV	EE_SPI_PORT1_DCHCON(INV)

#ifndef EE_SPI_PORT1_DCHECON
#define EE_SPI_PORT1_DCHECON(m)	DCH0ECON	##m	
#endif
#define SPI1_DCHECON	EE_SPI_PORT1_DCHECON()
#define SPI1_DCHECONSET	EE_SPI_PORT1_DCHECON(SET)
#define SPI1_DCHECONCLR	EE_SPI_PORT1_DCHECON(CLR)
#define SPI1_DCHECONINV	EE_SPI_PORT1_DCHECON(INV)

#ifndef EE_SPI_PORT1_DCHINT
#define EE_SPI_PORT1_DCHINT(m)	DCH0INT		##m	
#endif
#define SPI1_DCHINT	EE_SPI_PORT1_DCHINT()
#define SPI1_DCHINTSET	EE_SPI_PORT1_DCHINT(SET)
#define SPI1_DCHINTCLR	EE_SPI_PORT1_DCHINT(CLR)
#define SPI1_DCHINTINV	EE_SPI_PORT1_DCHINT(INV)

#ifndef EE_SPI_PORT1_DCHSSA
#define EE_SPI_PORT1_DCHSSA(m)	DCH0SSA		##m	
#endif
#define SPI1_DCHSSA	EE_SPI_PORT1_DCHSSA()

#ifndef EE_SPI_PORT1_DCHDSA
#define EE_SPI_PORT1_DCHDSA(m)	DCH0DSA		##m	
#endif
#define SPI1_DCHDSA	EE_SPI_PORT1_DCHDSA()

#ifndef EE_SPI_PORT1_DCHSSIZ
#define EE_SPI_PORT1_DCHSSIZ(m)	DCH0SSIZ	##m	
#endif
#define SPI1_DCHSSIZ	EE_SPI_PORT1_DCHSSIZ()

#ifndef EE_SPI_PORT1_DCHDSIZ
#define EE_SPI_PORT1_DCHDSIZ(m)	DCH0DSIZ	##m	
#endif
#define SPI1_DCHDSIZ	EE_SPI_PORT1_DCHDSIZ()

#ifndef EE_SPI_PORT1_DCHCSIZ
#define EE_SPI_PORT1_DCHCSIZ(m)	DCH0CSIZ	##m	
#endif
#define SPI1_DCHCSIZ	EE_SPI_PORT1_DCHCSIZ()

#ifndef EE_SPI_PORT1_DMA_IE_MASK
#define SPI1_DMAIE_MASK		_IEC1_DMA0IE_MASK
#else 	
#define SPI1_DMAIE_MASK 	EE_SPI_PORT1_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IF_MASK
#define SPI1_DMAIF_MASK		_IFS1_DMA0IF_MASK
#else 	
#define SPI1_DMAIF_MASK		EE_SPI_PORT1_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_MASK
#define SPI1_DMAIP_MASK		_IPC9_DMA0IP_MASK
#else 	
#define SPI1_DMAIP_MASK		EE_SPI_PORT1_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IS_MASK
#define SPI1_DMAIS_MASK		_IPC9_DMA0IS_MASK
#else 	
#define SPI1_DMAIS_MASK		EE_SPI_PORT1_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_POS
#define SPI1_DMAIP_POS		_IPC9_DMA0IP_POSITION
#else 	
#define SPI1_DMAIP_POS		EE_SPI_PORT1_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IS_POS
#define SPI1_DMAIS_POS		_IPC9_DMA0IS_POSITION
#else 	
#define SPI1_DMAIS_POS		EE_SPI_PORT1_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IRQ
#define SPI1_DMA_IRQ		_DMA0_VECTOR
#else 	
#define SPI1_DMA_IRQ		EE_SPI_PORT1_DMA_IRQ
#endif

/******************************************************************************/
/*			 Check SPI PORT 2 settings (with defaults) 	      */
/******************************************************************************/
#ifndef EE_SPI_PORT2_DCHCON
#define EE_SPI_PORT2_DCHCON(m)	DCH1CON		##m	
#endif
#define SPI2_DCHCON	EE_SPI_PORT2_DCHCON()
#define SPI2_DCHCONSET	EE_SPI_PORT2_DCHCON(SET)
#define SPI2_DCHCONCLR	EE_SPI_PORT2_DCHCON(CLR)
#define SPI2_DCHCONINV	EE_SPI_PORT2_DCHCON(INV)

#ifndef EE_SPI_PORT2_DCHECON
#define EE_SPI_PORT2_DCHECON(m)	DCH1ECON	##m	
#endif
#define SPI2_DCHECON	EE_SPI_PORT2_DCHECON()
#define SPI2_DCHECONSET	EE_SPI_PORT2_DCHECON(SET)
#define SPI2_DCHECONCLR	EE_SPI_PORT2_DCHECON(CLR)
#define SPI2_DCHECONINV	EE_SPI_PORT2_DCHECON(INV)

#ifndef EE_SPI_PORT2_DCHINT
#define EE_SPI_PORT2_DCHINT(m)	DCH1INT		##m	
#endif
#define SPI2_DCHINT	EE_SPI_PORT2_DCHINT()
#define SPI2_DCHINTSET	EE_SPI_PORT2_DCHINT(SET)
#define SPI2_DCHINTCLR	EE_SPI_PORT2_DCHINT(CLR)
#define SPI2_DCHINTINV	EE_SPI_PORT2_DCHINT(INV)

#ifndef EE_SPI_PORT2_DCHSSA
#define EE_SPI_PORT2_DCHSSA(m)	DCH1SSA		##m	
#endif
#define SPI2_DCHSSA	EE_SPI_PORT2_DCHSSA()

#ifndef EE_SPI_PORT2_DCHDSA
#define EE_SPI_PORT2_DCHDSA(m)	DCH1DSA		##m	
#endif
#define SPI2_DCHDSA	EE_SPI_PORT2_DCHDSA()

#ifndef EE_SPI_PORT2_DCHSSIZ
#define EE_SPI_PORT2_DCHSSIZ(m)	DCH1SSIZ	##m	
#endif
#define SPI2_DCHSSIZ	EE_SPI_PORT2_DCHSSIZ()

#ifndef EE_SPI_PORT2_DCHDSIZ
#define EE_SPI_PORT2_DCHDSIZ(m)	DCH1DSIZ	##m	
#endif
#define SPI2_DCHDSIZ	EE_SPI_PORT2_DCHDSIZ()

#ifndef EE_SPI_PORT2_DCHCSIZ
#define EE_SPI_PORT2_DCHCSIZ(m)	DCH1CSIZ	##m	
#endif
#define SPI2_DCHCSIZ	EE_SPI_PORT2_DCHCSIZ()

#ifndef EE_SPI_PORT2_DMA_IE_MASK
#define SPI2_DMAIE_MASK		_IEC1_DMA1IE_MASK
#else 	
#define SPI2_DMAIE_MASK 	EE_SPI_PORT2_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IF_MASK
#define SPI2_DMAIF_MASK		_IFS1_DMA1IF_MASK
#else 	
#define SPI2_DMAIF_MASK		EE_SPI_PORT2_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IP_MASK
#define SPI2_DMAIP_MASK		_IPC9_DMA1IP_MASK
#else 	
#define SPI2_DMAIP_MASK		EE_SPI_PORT2_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IS_MASK
#define SPI2_DMAIS_MASK		_IPC9_DMA1IS_MASK
#else 	
#define SPI2_DMAIS_MASK		EE_SPI_PORT2_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT2_DMA_IP_POS
#define SPI2_DMAIP_POS		_IPC9_DMA1IP_POSITION
#else 	
#define SPI2_DMAIP_POS		EE_SPI_PORT2_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT2_DMA_IS_POS
#define SPI2_DMAIS_POS		_IPC9_DMA1IS_POSITION
#else 	
#define SPI2_DMAIS_POS		EE_SPI_PORT2_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT2_DMA_IRQ
#define SPI2_DMA_IRQ		_DMA1_VECTOR
#else 	
#define SPI2_DMA_IRQ		EE_SPI_PORT2_DMA_IRQ
#endif


#else // !defined __32MX360F512L__

/* Check SPI PORT 1 settings (with defaults) */
#ifndef EE_SPI_PORT1_DCHCON
#define EE_SPI_PORT1_DCHCON(m)	DCH0CON		##m	
#endif
#define SPI1_DCHCON	EE_SPI_PORT1_DCHCON()
#define SPI1_DCHCONSET	EE_SPI_PORT1_DCHCON(SET)
#define SPI1_DCHCONCLR	EE_SPI_PORT1_DCHCON(CLR)
#define SPI1_DCHCONINV	EE_SPI_PORT1_DCHCON(INV)

#ifndef EE_SPI_PORT1_DCHECON
#define EE_SPI_PORT1_DCHECON(m)	DCH0ECON	##m	
#endif
#define SPI1_DCHECON	EE_SPI_PORT1_DCHECON()
#define SPI1_DCHECONSET	EE_SPI_PORT1_DCHECON(SET)
#define SPI1_DCHECONCLR	EE_SPI_PORT1_DCHECON(CLR)
#define SPI1_DCHECONINV	EE_SPI_PORT1_DCHECON(INV)

#ifndef EE_SPI_PORT1_DCHINT
#define EE_SPI_PORT1_DCHINT(m)	DCH0INT		##m	
#endif
#define SPI1_DCHINT	EE_SPI_PORT1_DCHINT()
#define SPI1_DCHINTSET	EE_SPI_PORT1_DCHINT(SET)
#define SPI1_DCHINTCLR	EE_SPI_PORT1_DCHINT(CLR)
#define SPI1_DCHINTINV	EE_SPI_PORT1_DCHINT(INV)

#ifndef EE_SPI_PORT1_DCHSSA
#define EE_SPI_PORT1_DCHSSA(m)	DCH0SSA		##m	
#endif
#define SPI1_DCHSSA	EE_SPI_PORT1_DCHSSA()

#ifndef EE_SPI_PORT1_DCHDSA
#define EE_SPI_PORT1_DCHDSA(m)	DCH0DSA		##m	
#endif
#define SPI1_DCHDSA	EE_SPI_PORT1_DCHDSA()

#ifndef EE_SPI_PORT1_DCHSSIZ
#define EE_SPI_PORT1_DCHSSIZ(m)	DCH0SSIZ	##m	
#endif
#define SPI1_DCHSSIZ	EE_SPI_PORT1_DCHSSIZ()

#ifndef EE_SPI_PORT1_DCHDSIZ
#define EE_SPI_PORT1_DCHDSIZ(m)	DCH0DSIZ	##m	
#endif
#define SPI1_DCHDSIZ	EE_SPI_PORT1_DCHDSIZ()

#ifndef EE_SPI_PORT1_DCHCSIZ
#define EE_SPI_PORT1_DCHCSIZ(m)	DCH0CSIZ	##m	
#endif
#define SPI1_DCHCSIZ	EE_SPI_PORT1_DCHCSIZ()

#ifndef EE_SPI_PORT1_DMA_IE_MASK
#define SPI1_DMAIE_MASK		_IEC1_DMA0IE_MASK
#else 	
#define SPI1_DMAIE_MASK 	EE_SPI_PORT1_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IF_MASK
#define SPI1_DMAIF_MASK		_IFS1_DMA0IF_MASK
#else 	
#define SPI1_DMAIF_MASK		EE_SPI_PORT1_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_MASK
#define SPI1_DMAIP_MASK		_IPC9_DMA0IP_MASK
#else 	
#define SPI1_DMAIP_MASK		EE_SPI_PORT1_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IS_MASK
#define SPI1_DMAIS_MASK		_IPC9_DMA0IS_MASK
#else 	
#define SPI1_DMAIS_MASK		EE_SPI_PORT1_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT1_DMA_IP_POS
#define SPI1_DMAIP_POS		_IPC9_DMA0IP_POSITION
#else 	
#define SPI1_DMAIP_POS		EE_SPI_PORT1_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IS_POS
#define SPI1_DMAIS_POS		_IPC9_DMA0IS_POSITION
#else 	
#define SPI1_DMAIS_POS		EE_SPI_PORT1_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT1_DMA_IRQ
#define SPI1_DMA_IRQ		_DMA0_VECTOR
#else 	
#define SPI1_DMA_IRQ		EE_SPI_PORT1_DMA_IRQ
#endif

/******************************************************************************/
/*			 Check SPI PORT 1A settings (with defaults) 	      */
/******************************************************************************/
#ifndef EE_SPI_PORT1A_DCHCON
#define EE_SPI_PORT1A_DCHCON(m)	DCH1CON		##m	
#endif
#define SPI1A_DCHCON		EE_SPI_PORT1A_DCHCON()
#define SPI1A_DCHCONSET		EE_SPI_PORT1A_DCHCON(SET)
#define SPI1A_DCHCONCLR		EE_SPI_PORT1A_DCHCON(CLR)
#define SPI1A_DCHCONINV		EE_SPI_PORT1A_DCHCON(INV)

#ifndef EE_SPI_PORT1A_DCHECON
#define EE_SPI_PORT1A_DCHECON(m)	DCH1ECON	##m	
#endif
#define SPI1A_DCHECON		EE_SPI_PORT1A_DCHECON()
#define SPI1A_DCHECONSET	EE_SPI_PORT1A_DCHECON(SET)
#define SPI1A_DCHECONCLR	EE_SPI_PORT1A_DCHECON(CLR)
#define SPI1A_DCHECONINV	EE_SPI_PORT1A_DCHECON(INV)

#ifndef EE_SPI_PORT1A_DCHINT
#define EE_SPI_PORT1A_DCHINT(m)	DCH1INT		##m	
#endif
#define SPI1A_DCHINT		EE_SPI_PORT1A_DCHINT()
#define SPI1A_DCHINTSET		EE_SPI_PORT1A_DCHINT(SET)
#define SPI1A_DCHINTCLR		EE_SPI_PORT1A_DCHINT(CLR)
#define SPI1A_DCHINTINV		EE_SPI_PORT1A_DCHINT(INV)

#ifndef EE_SPI_PORT1A_DCHSSA
#define EE_SPI_PORT1A_DCHSSA(m)		DCH1SSA		##m	
#endif
#define SPI1A_DCHSSA		EE_SPI_PORT1A_DCHSSA()

#ifndef EE_SPI_PORT1A_DCHDSA
#define EE_SPI_PORT1A_DCHDSA(m)		DCH1DSA		##m	
#endif
#define SPI1A_DCHDSA	EE_SPI_PORT1A_DCHDSA()

#ifndef EE_SPI_PORT1A_DCHSSIZ
#define EE_SPI_PORT1A_DCHSSIZ(m)	DCH1SSIZ	##m	
#endif
#define SPI1A_DCHSSIZ		EE_SPI_PORT1A_DCHSSIZ()

#ifndef EE_SPI_PORT1A_DCHDSIZ
#define EE_SPI_PORT1A_DCHDSIZ(m)	DCH1DSIZ	##m	
#endif
#define SPI1A_DCHDSIZ	EE_SPI_PORT1A_DCHDSIZ()

#ifndef EE_SPI_PORT1A_DCHCSIZ
#define EE_SPI_PORT1A_DCHCSIZ(m)	DCH1CSIZ	##m	
#endif
#define SPI1A_DCHCSIZ	EE_SPI_PORT1A_DCHCSIZ()

#ifndef EE_SPI_PORT1A_DMA_IE_MASK
#define SPI1A_DMAIE_MASK		_IEC1_DMA1IE_MASK
#else 	
#define SPI1A_DMAIE_MASK 	EE_SPI_PORT1A_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT1A_DMA_IF_MASK
#define SPI1A_DMAIF_MASK		_IFS1_DMA1IF_MASK
#else 	
#define SPI1A_DMAIF_MASK		EE_SPI_PORT1A_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT1A_DMA_IP_MASK
#define SPI1A_DMAIP_MASK		_IPC9_DMA1IP_MASK
#else 	
#define SPI1A_DMAIP_MASK		EE_SPI_PORT1A_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT1A_DMA_IS_MASK
#define SPI1A_DMAIS_MASK		_IPC9_DMA1IS_MASK
#else 	
#define SPI1A_DMAIS_MASK		EE_SPI_PORT1A_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT1A_DMA_IP_POS
#define SPI1A_DMAIP_POS		_IPC9_DMA1IP_POSITION
#else 	
#define SPI1A_DMAIP_POS		EE_SPI_PORT1A_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT1A_DMA_IS_POS
#define SPI1A_DMAIS_POS		_IPC9_DMA1IS_POSITION
#else 	
#define SPI1A_DMAIS_POS		EE_SPI_PORT1A_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT1A_DMA_IRQ
#define SPI1A_DMA_IRQ		_DMA1_VECTOR
#else 	
#define SPI1A_DMA_IRQ		EE_SPI_PORT1A_DMA_IRQ
#endif

/******************************************************************************/
/*			 Check SPI PORT 2A settings (with defaults) 	      */
/******************************************************************************/
#ifndef EE_SPI_PORT2A_DCHCON
#define EE_SPI_PORT2A_DCHCON(m)	DCH2CON		##m	
#endif
#define SPI2A_DCHCON	EE_SPI_PORT2A_DCHCON()
#define SPI2A_DCHCONSET	EE_SPI_PORT2A_DCHCON(SET)
#define SPI2A_DCHCONCLR	EE_SPI_PORT2A_DCHCON(CLR)
#define SPI2A_DCHCONINV	EE_SPI_PORT2A_DCHCON(INV)

#ifndef EE_SPI_PORT2A_DCHECON
#define EE_SPI_PORT2A_DCHECON(m)	DCH2ECON	##m	
#endif
#define SPI2A_DCHECON	EE_SPI_PORT2A_DCHECON()
#define SPI2A_DCHECONSET	EE_SPI_PORT2A_DCHECON(SET)
#define SPI2A_DCHECONCLR	EE_SPI_PORT2A_DCHECON(CLR)
#define SPI2A_DCHECONINV	EE_SPI_PORT2A_DCHECON(INV)

#ifndef EE_SPI_PORT2A_DCHINT
#define EE_SPI_PORT2A_DCHINT(m)	DCH2INT		##m	
#endif
#define SPI2A_DCHINT		EE_SPI_PORT2A_DCHINT()
#define SPI2A_DCHINTSET		EE_SPI_PORT2A_DCHINT(SET)
#define SPI2A_DCHINTCLR		EE_SPI_PORT2A_DCHINT(CLR)
#define SPI2A_DCHINTINV		EE_SPI_PORT2A_DCHINT(INV)

#ifndef EE_SPI_PORT2A_DCHSSA
#define EE_SPI_PORT2A_DCHSSA(m)		DCH2SSA		##m	
#endif
#define SPI2A_DCHSSA		EE_SPI_PORT2A_DCHSSA()

#ifndef EE_SPI_PORT2A_DCHDSA
#define EE_SPI_PORT2A_DCHDSA(m)		DCH2DSA		##m	
#endif
#define SPI2A_DCHDSA	EE_SPI_PORT2A_DCHDSA()

#ifndef EE_SPI_PORT2A_DCHSSIZ
#define EE_SPI_PORT2A_DCHSSIZ(m)	DCH2SSIZ	##m	
#endif
#define SPI2A_DCHSSIZ		EE_SPI_PORT2A_DCHSSIZ()

#ifndef EE_SPI_PORT2A_DCHDSIZ
#define EE_SPI_PORT2A_DCHDSIZ(m)	DCH2DSIZ	##m	
#endif
#define SPI2A_DCHDSIZ	EE_SPI_PORT2A_DCHDSIZ()

#ifndef EE_SPI_PORT2A_DCHCSIZ
#define EE_SPI_PORT2A_DCHCSIZ(m)	DCH2CSIZ	##m	
#endif
#define SPI2A_DCHCSIZ	EE_SPI_PORT2A_DCHCSIZ()

#ifndef EE_SPI_PORT2A_DMA_IE_MASK
#define SPI2A_DMAIE_MASK		_IEC1_DMA2IE_MASK
#else 	
#define SPI2A_DMAIE_MASK 	EE_SPI_PORT2A_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT2A_DMA_IF_MASK
#define SPI2A_DMAIF_MASK		_IFS1_DMA2IF_MASK
#else 	
#define SPI2A_DMAIF_MASK		EE_SPI_PORT2A_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT2A_DMA_IP_MASK
#define SPI2A_DMAIP_MASK		_IPC9_DMA2IP_MASK
#else 	
#define SPI2A_DMAIP_MASK		EE_SPI_PORT2A_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT2A_DMA_IS_MASK
#define SPI2A_DMAIS_MASK		_IPC9_DMA2IS_MASK
#else 	
#define SPI2A_DMAIS_MASK		EE_SPI_PORT2A_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT2A_DMA_IP_POS
#define SPI2A_DMAIP_POS		_IPC9_DMA2IP_POSITION
#else 	
#define SPI2A_DMAIP_POS		EE_SPI_PORT2A_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT2A_DMA_IS_POS
#define SPI2A_DMAIS_POS		_IPC9_DMA2IS_POSITION
#else 	
#define SPI2A_DMAIS_POS		EE_SPI_PORT2A_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT2A_DMA_IRQ
#define SPI2A_DMA_IRQ		_DMA2_VECTOR
#else 	
#define SPI2A_DMA_IRQ		EE_SPI_PORT2A_DMA_IRQ
#endif


/******************************************************************************/
/*			 Check SPI PORT 3A settings (with defaults) 	      */
/******************************************************************************/
#ifndef EE_SPI_PORT3A_DCHCON
#define EE_SPI_PORT3A_DCHCON(m)	DCH3CON		##m	
#endif
#define SPI3A_DCHCON	EE_SPI_PORT3A_DCHCON()
#define SPI3A_DCHCONSET	EE_SPI_PORT3A_DCHCON(SET)
#define SPI3A_DCHCONCLR	EE_SPI_PORT3A_DCHCON(CLR)
#define SPI3A_DCHCONINV	EE_SPI_PORT3A_DCHCON(INV)

#ifndef EE_SPI_PORT3A_DCHECON
#define EE_SPI_PORT3A_DCHECON(m)	DCH3ECON	##m	
#endif
#define SPI3A_DCHECON	EE_SPI_PORT3A_DCHECON()
#define SPI3A_DCHECONSET	EE_SPI_PORT3A_DCHECON(SET)
#define SPI3A_DCHECONCLR	EE_SPI_PORT3A_DCHECON(CLR)
#define SPI3A_DCHECONINV	EE_SPI_PORT3A_DCHECON(INV)

#ifndef EE_SPI_PORT3A_DCHINT
#define EE_SPI_PORT3A_DCHINT(m)	DCH3INT		##m	
#endif
#define SPI3A_DCHINT		EE_SPI_PORT3A_DCHINT()
#define SPI3A_DCHINTSET		EE_SPI_PORT3A_DCHINT(SET)
#define SPI3A_DCHINTCLR		EE_SPI_PORT3A_DCHINT(CLR)
#define SPI3A_DCHINTINV		EE_SPI_PORT3A_DCHINT(INV)

#ifndef EE_SPI_PORT3A_DCHSSA
#define EE_SPI_PORT3A_DCHSSA(m)		DCH3SSA		##m	
#endif
#define SPI3A_DCHSSA		EE_SPI_PORT3A_DCHSSA()

#ifndef EE_SPI_PORT3A_DCHDSA
#define EE_SPI_PORT3A_DCHDSA(m)		DCH3DSA		##m	
#endif
#define SPI3A_DCHDSA	EE_SPI_PORT3A_DCHDSA()

#ifndef EE_SPI_PORT3A_DCHSSIZ
#define EE_SPI_PORT3A_DCHSSIZ(m)	DCH3SSIZ	##m	
#endif
#define SPI3A_DCHSSIZ		EE_SPI_PORT3A_DCHSSIZ()

#ifndef EE_SPI_PORT3A_DCHDSIZ
#define EE_SPI_PORT3A_DCHDSIZ(m)	DCH3DSIZ	##m	
#endif
#define SPI3A_DCHDSIZ	EE_SPI_PORT3A_DCHDSIZ()

#ifndef EE_SPI_PORT3A_DCHCSIZ
#define EE_SPI_PORT3A_DCHCSIZ(m)	DCH3CSIZ	##m	
#endif
#define SPI3A_DCHCSIZ	EE_SPI_PORT3A_DCHCSIZ()

#ifndef EE_SPI_PORT3A_DMA_IE_MASK
#define SPI3A_DMAIE_MASK		_IEC1_DMA3IE_MASK
#else 	
#define SPI3A_DMAIE_MASK 	EE_SPI_PORT3A_DMA_IE_MASK
#endif

#ifndef EE_SPI_PORT3A_DMA_IF_MASK
#define SPI3A_DMAIF_MASK		_IFS1_DMA3IF_MASK
#else 	
#define SPI3A_DMAIF_MASK		EE_SPI_PORT3A_DMA_IF_MASK
#endif

#ifndef EE_SPI_PORT3A_DMA_IP_MASK
#define SPI3A_DMAIP_MASK		_IPC9_DMA3IP_MASK
#else 	
#define SPI3A_DMAIP_MASK		EE_SPI_PORT3A_DMA_IP_MASK
#endif

#ifndef EE_SPI_PORT3A_DMA_IS_MASK
#define SPI3A_DMAIS_MASK		_IPC9_DMA3IS_MASK
#else 	
#define SPI3A_DMAIS_MASK		EE_SPI_PORT3A_DMA_IS_MASK
#endif

#ifndef EE_SPI_PORT3A_DMA_IP_POS
#define SPI3A_DMAIP_POS		_IPC9_DMA3IP_POSITION
#else 	
#define SPI3A_DMAIP_POS		EE_SPI_PORT3A_DMA_IP_POS
#endif

#ifndef EE_SPI_PORT3A_DMA_IS_POS
#define SPI3A_DMAIS_POS		_IPC9_DMA3IS_POSITION
#else 	
#define SPI3A_DMAIS_POS		EE_SPI_PORT3A_DMA_IS_POS
#endif

#ifndef EE_SPI_PORT3A_DMA_IRQ
#define SPI3A_DMA_IRQ		_DMA3_VECTOR
#else 	
#define SPI3A_DMA_IRQ		EE_SPI_PORT3A_DMA_IRQ
#endif

#endif


/* NOTE: this work under the assumption that all the DMA channels have the same 
*  control registers specification. See pic32mx family reference manual.
*/
#define SPI_DCHCON_CHEN_MASK 	_DCH0CON_CHEN_MASK
#define SPI_DCHECON_CFORCE_MASK _DCH0ECON_CFORCE_MASK
#define SPI_DCHECON_SIRQEN_MASK _DCH0ECON_SIRQEN_MASK
#define SPI_DCHECON_CHSIRQ_POS 	_DCH0ECON_CHSIRQ_POSITION
#define SPI_DCHINT_CHBCIE_MASK 	_DCH0INT_CHBCIE_MASK
#define SPI_DCHINT_CHBCIF_MASK 	_DCH0INT_CHBCIF_MASK








/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/

#ifdef __32MX795F512L__

#ifdef __USE_SPI_PORT1A__
static EE_UINT16 port1a_flags;
static void (* volatile port1a_tx_callback)(void) = NULL;

#endif //__EE_SPI_PORT1A__


#ifdef __USE_SPI_PORT2A__
static EE_UINT16 port2a_flags;
static void (* volatile port2a_tx_callback)(void) = NULL;
#endif //__EE_SPI_PORT2A__

#ifdef __USE_SPI_PORT3A__
static EE_UINT16 port3a_flags;
static void (* volatile port3a_tx_callback)(void) = NULL;
#endif //__EE_SPI_PORT2A__

#ifdef __USE_SPI_PORT1__
static EE_UINT16 port1_flags;
static void (* volatile port1_tx_callback)(void) = NULL;
#endif //__EE_SPI_PORT1__



#else //not defined __32MX795F512L__

static EE_UINT16 port1_flags;
static EE_UINT16 port2_flags;
static void (* volatile port1_tx_callback)(void) = NULL;
static void (* volatile port2_tx_callback)(void) = NULL;

#endif


/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
__INLINE__ EE_UREG get_brg(EE_UINT32 baudrate) 
{
	EE_UINT32 pbc = EE_get_peripheral_clock();
	return (pbc/(2*baudrate) - 1); 
}


/******************************************************************************/
/*				Init Functions				      */
/******************************************************************************/

#ifdef __32MX795F512L__


/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu	*	      */
/*   	*********************************************************	      */
/******************************************************************************/

#ifdef __USE_SPI_PORT1A__
__INLINE__ EE_INT8 init_port1A(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC0CLR = _IEC0_SPI1AEIE_MASK | _IEC0_SPI1ATXIE_MASK | 
		  _IEC0_SPI1ARXIE_MASK;
	
	IFS0CLR = _IFS0_SPI1AEIF_MASK | _IFS0_SPI1ATXIF_MASK | 
		  _IFS0_SPI1ARXIF_MASK;

	SPI1ACON = 0;
	SPI1ASTATCLR = _SPI1ASTAT_SPIROV_MASK; 
	SPI1ABRG = get_brg(baudrate); 	

	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	port1a_flags = flags;

	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits

	
	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI1A_DMAIE_MASK;		
		IFS1CLR = SPI1A_DMAIF_MASK;		
		IPC9CLR = SPI1A_DMAIP_MASK | SPI1A_DMAIS_MASK;
		IPC9SET = ((5 << SPI1A_DMAIP_POS) & SPI1A_DMAIP_MASK) | 
			  ((2 << SPI1A_DMAIS_POS) & SPI1A_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI1A_DCHCON = 0; // TODO: check this, now priority = 0
		SPI1A_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI1A_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI1A_DCHINT = 0;
	}

	SPI1ACON = v | _SPI1ACON_ON_MASK;

	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT1A__


#ifdef __USE_SPI_PORT2A__
__INLINE__ EE_UINT8 init_port2A(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC1CLR = _IEC1_SPI2AEIE_MASK | _IEC1_SPI2ATXIE_MASK | 
		  _IEC1_SPI2ARXIE_MASK;
	IFS1CLR = _IFS1_SPI2AEIF_MASK | _IFS1_SPI2ATXIF_MASK | 
		  _IFS1_SPI2ARXIF_MASK;
	SPI2ACON = 0;
	SPI2ASTATCLR = _SPI2ASTAT_SPIROV_MASK; 
	SPI2ABRG = get_brg(baudrate); 	
	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	port2a_flags = flags;
	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
	
	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI2A_DMAIE_MASK;		
		IFS1CLR = SPI2A_DMAIF_MASK;		
		IPC9CLR = SPI2A_DMAIP_MASK | SPI2A_DMAIS_MASK;
		IPC9SET = ((5 << SPI2A_DMAIP_POS) & SPI2A_DMAIP_MASK) | 
			  ((2 << SPI2A_DMAIS_POS) & SPI2A_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI2A_DCHCON = 0; // TODO: check this, now priority = 0
		SPI2A_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI2A_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI2A_DCHINT = 0;
	}
	
	SPI2ACON = v | _SPI2ACON_ON_MASK;
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT2A__


#ifdef __USE_SPI_PORT3A__
__INLINE__ EE_UINT8 init_port3A(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC1CLR = _IEC1_SPI3AEIE_MASK | _IEC1_SPI3ATXIE_MASK | 
		  _IEC1_SPI3ARXIE_MASK;
	IFS1CLR = _IFS1_SPI3AEIF_MASK | _IFS1_SPI3ATXIF_MASK | 
		  _IFS1_SPI3ARXIF_MASK;
	
	SPI3ACON = 0;
	SPI3ASTATCLR = _SPI3ASTAT_SPIROV_MASK; 
	SPI3ABRG = get_brg(baudrate); 	
	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	
	port3a_flags = flags;
	
	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits

	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI3A_DMAIE_MASK;		
		IFS1CLR = SPI3A_DMAIF_MASK;		
		IPC9CLR = SPI3A_DMAIP_MASK | SPI3A_DMAIS_MASK;
		IPC9SET = ((5 << SPI3A_DMAIP_POS) & SPI3A_DMAIP_MASK) | 
			  ((2 << SPI3A_DMAIS_POS) & SPI3A_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI3A_DCHCON = 0; // TODO: check this, now priority = 0
		SPI3A_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI3A_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI3A_DCHINT = 0;
	}
	
	SPI3ACON = v | _SPI3ACON_ON_MASK;
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT3A__


#ifdef __USE_SPI_PORT1__
__INLINE__ EE_UINT8 init_port1(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC0CLR = _IEC0_SPI1EIE_MASK | _IEC0_SPI1TXIE_MASK | 
		  _IEC0_SPI1RXIE_MASK;
	IFS0CLR = _IFS0_SPI1EIF_MASK | _IFS0_SPI1TXIF_MASK | 
		  _IFS0_SPI1RXIF_MASK;
	
	SPI1CON = 0;
	SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
	SPI1BRG = get_brg(baudrate); 	
	
	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	
	port1_flags = flags;
	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
	
	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI1_DMAIE_MASK;		
		IFS1CLR = SPI1_DMAIF_MASK;		
		IPC9CLR = SPI1_DMAIP_MASK | SPI1_DMAIS_MASK;
		IPC9SET = ((5 << SPI1_DMAIP_POS) & SPI1_DMAIP_MASK) | 
			  ((2 << SPI1_DMAIS_POS) & SPI1_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI1_DCHCON = 0; // TODO: check this, now priority = 0
		SPI1_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI1_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI1_DCHINT = 0;
	}
	SPI1CON = v | _SPI1CON_ON_MASK;

	return EE_SPI_NO_ERRORS;
}
#endif // __USE_SPI_PORT1__


#else //not defined __32MX795F512L__


/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx360f512l mcu	*	      */
/*   	*********************************************************	      */
/******************************************************************************/

__INLINE__ EE_INT8 init_port1(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC0CLR = _IEC0_SPI1EIE_MASK | _IEC0_SPI1TXIE_MASK | 
		  _IEC0_SPI1RXIE_MASK;
	IFS0CLR = _IFS0_SPI1EIF_MASK | _IFS0_SPI1TXIF_MASK | 
		  _IFS0_SPI1RXIF_MASK;
	SPI1CON = 0;
	SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
	SPI1BRG = get_brg(baudrate); 	
	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	port1_flags = flags;
	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI1_DMAIE_MASK;		
		IFS1CLR = SPI1_DMAIF_MASK;		
		IPC9CLR = SPI1_DMAIP_MASK | SPI1_DMAIS_MASK;
		IPC9SET = ((5 << SPI1_DMAIP_POS) & SPI1_DMAIP_MASK) | 
			  ((2 << SPI1_DMAIS_POS) & SPI1_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI1_DCHCON = 0; // TODO: check this, now priority = 0
		SPI1_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI1_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI1_DCHINT = 0;
	}
	SPI1CON = v | _SPI1CON_ON_MASK;

	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_UINT8 init_port2(EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_UREG v; 

	IEC1CLR = _IEC1_SPI2EIE_MASK | _IEC1_SPI2TXIE_MASK | 
		  _IEC1_SPI2RXIE_MASK;
	IFS1CLR = _IFS1_SPI2EIF_MASK | _IFS1_SPI2TXIF_MASK | 
		  _IFS1_SPI2RXIF_MASK;
	SPI2CON = 0;
	SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
	SPI2BRG = get_brg(baudrate); 	
	/* Flag parsing */
	if (!IS_MASTER(flags))
		return -EE_SPI_ERR_UNIMPLEMENTED;
	if (IS_DMA_RX(flags)) 
		return -EE_SPI_ERR_UNIMPLEMENTED;
	port2_flags = flags;
	v = flags & MCHP_SPICON_MASKS;	// Select Microchip valid bits
	if (IS_DMA_TX(flags)) {
		IEC1CLR = SPI2_DMAIE_MASK;		
		IFS1CLR = SPI2_DMAIF_MASK;		
		IPC9CLR = SPI2_DMAIP_MASK | SPI2_DMAIS_MASK;
		IPC9SET = ((5 << SPI2_DMAIP_POS) & SPI2_DMAIP_MASK) | 
			  ((2 << SPI2_DMAIS_POS) & SPI2_DMAIS_MASK);
		DMACONSET = _DMACON_ON_MASK; 
		SPI2_DCHCON = 0; // TODO: check this, now priority = 0
		SPI2_DCHECON = SPI_DCHECON_SIRQEN_MASK | 
			       (_SPI2_TX_IRQ << SPI_DCHECON_CHSIRQ_POS);
		SPI2_DCHINT = 0;
	}
	SPI2CON = v | _SPI2CON_ON_MASK;

	return EE_SPI_NO_ERRORS;
}

#endif


/******************************************************************************/
/*				Write Functions				      */
/******************************************************************************/



#ifdef __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu	*	      */
/*   	*********************************************************	      */
/******************************************************************************/


#ifdef __USE_SPI_PORT1A__
#ifdef __USE_SPI_PORT1A_DMA__
__INLINE__ EE_INT8 write_dma_port1A(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI1A_DCHCON & SPIA_DCHCON_CHEN_MASK) || 
	   (SPI1ASTAT & _SPI1ASTAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS0CLR = _IFS0_SPI1ATXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI1A_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI1A_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI1A_DCHINT = 0;			// Clear IRQ sources
	SPI1A_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI1A_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI1ABUF);
	SPI1A_DCHSSIZ = len;
	SPI1A_DCHDSIZ = 1;
	SPI1A_DCHCSIZ = 1;
	SPI1A_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI1A_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI1A_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI1A_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}
#endif	//__USE_SPI_PORT1A_DMA__
#endif	//__USE_SPI_PORT1A__


#ifdef __USE_SPI_PORT2A__
#ifdef __USE_SPI_PORT2A_DMA__
__INLINE__ EE_INT8 write_dma_port2A(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI2A_DCHCON & SPI_DCHCON_CHEN_MASK) || 
	   (SPI2ASTAT & _SPI2ASTAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS1CLR = _IFS1_SPI2ATXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI2A_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI2A_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI2A_DCHINT = 0;			// Clear IRQ sources
	SPI2A_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI2A_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI2ABUF);
	SPI2A_DCHSSIZ = len;
	SPI2A_DCHDSIZ = 1;
	SPI2A_DCHCSIZ = 1;
	SPI2A_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI2A_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI2A_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI2A_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT2A_DMA__
#endif //__USE_SPI_PORT2A__


#ifdef __USE_SPI_PORT3A__
#ifdef __USE_SPI_PORT3A_DMA__
__INLINE__ EE_INT8 write_dma_port3A(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI3A_DCHCON & SPI_DCHCON_CHEN_MASK) || 
	   (SPI3ASTAT & _SPI3ASTAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS1CLR = _IFS1_SPI3ATXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI3A_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI3A_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI3A_DCHINT = 0;			// Clear IRQ sources
	SPI3A_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI3A_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI3ABUF);
	SPI3A_DCHSSIZ = len;
	SPI3A_DCHDSIZ = 1;
	SPI3A_DCHCSIZ = 1;
	SPI3A_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI3A_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI3A_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI3A_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT3A_DMA__
#endif //__USE_SPI_PORT3A__



#ifdef __USE_SPI_PORT1A__
#ifdef __USE_SPI_PORT1A_DMA__
__INLINE__ EE_INT8 write_dma_port1A(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI1_DCHCON & SPI_DCHCON_CHEN_MASK) || 
	   (SPI1STAT & _SPI1STAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS0CLR = _IFS0_SPI1TXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI1_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI1_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI1_DCHINT = 0;			// Clear IRQ sources
	SPI1_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI1_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI1BUF);
	SPI1_DCHSSIZ = len;
	SPI1_DCHDSIZ = 1;
	SPI1_DCHCSIZ = 1;
	SPI1_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI1_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI1_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI1_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}
#endif	//__USE_SPI_PORT1_DMA__
#endif	//__USE_SPI_PORT1__



#ifdef __USE_SPI_PORT1A__
__INLINE__ EE_INT8 write_polling_port1A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1ASTATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI1ASTATbits.SPITBE) ; 
   		SPI1ABUF = data[i];
   		while (!SPI1ASTATbits.SPIRBF) ;
		SPI1ASTATCLR = _SPI1ASTAT_SPIROV_MASK; 
		dummy = SPI1ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif // __USE_SPI_PORT1A__



#ifdef __USE_SPI_PORT2A__
__INLINE__ EE_INT8 write_polling_port2A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI2ASTATCLR = _SPI2ASTAT_SPIROV_MASK; 
   		while (!SPI2ASTATbits.SPITBE) ; 
   		SPI2BUF = data[i];
   		while (!SPI2ASTATbits.SPIRBF) ;
		SPI2ASTATCLR = _SPI2ASTAT_SPIROV_MASK; 
		dummy = SPI2ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif // __USE_SPI_PORT2A__



#ifdef __USE_SPI_PORT3A__
__INLINE__ EE_INT8 write_polling_port3A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI3ASTATCLR = _SPI3ASTAT_SPIROV_MASK; 
   		while (!SPI3ASTATbits.SPITBE) ; 
   		SPI3ABUF = data[i];
   		while (!SPI3ASTATbits.SPIRBF) ;
		SPI3ASTATCLR = _SPI3ASTAT_SPIROV_MASK; 
		dummy = SPI3ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif // __USE_SPI_PORT3A__



#ifdef __USE_SPI_PORT1__
__INLINE__ EE_INT8 write_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
   		while (!SPI1STATbits.SPITBE) ; 
   		SPI1BUF = data[i];
   		while (!SPI1STATbits.SPIRBF) ;
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		dummy = SPI1BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT1__

#else //not defined __32MX795F512L__

__INLINE__ EE_INT8 write_dma_port1(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI1_DCHCON & SPI_DCHCON_CHEN_MASK) || 
	   (SPI1STAT & _SPI1STAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS0CLR = _IFS0_SPI1TXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI1_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI1_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI1_DCHINT = 0;			// Clear IRQ sources
	SPI1_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI1_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI1BUF);
	SPI1_DCHSSIZ = len;
	SPI1_DCHDSIZ = 1;
	SPI1_DCHCSIZ = 1;
	SPI1_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI1_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI1_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI1_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_dma_port2(EE_UINT8 *data, EE_UINT32 len)
{
	/* TODO: limit someway the lenght? */
	if ((SPI2_DCHCON & SPI_DCHCON_CHEN_MASK) || 
	   (SPI2STAT & _SPI2STAT_SPIBUSY_MASK))
		return -EE_SPI_ERR_BUSY;
	IFS1CLR = _IFS1_SPI2TXIF_MASK;		// Clear SPITX IRQ flag 
	IEC1CLR = SPI2_DMAIE_MASK;		// Stop DMA channel IRQ
	IFS1CLR = SPI2_DMAIF_MASK;		// Clear DMA channel IRQ
	SPI2_DCHINT = 0;			// Clear IRQ sources
	SPI2_DCHSSA = EE_ADDR_VIRTUAL_TO_PHYSICAL(data);
	SPI2_DCHDSA = EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)&SPI2BUF);
	SPI2_DCHSSIZ = len;
	SPI2_DCHDSIZ = 1;
	SPI2_DCHCSIZ = 1;
	SPI2_DCHINTSET = SPI_DCHINT_CHBCIE_MASK;// IRQ Source is end-of-block
	IEC1SET = SPI2_DMAIE_MASK;		// Enable DMA channel IRQ
	SPI2_DCHCONSET = SPI_DCHCON_CHEN_MASK;	// Enable DMA Channel 
	SPI2_DCHECONSET = SPI_DCHECON_CFORCE_MASK; 	// Force Tx Start 

	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
   		while (!SPI1STATbits.SPITBE) ; 
   		SPI1BUF = data[i];
   		while (!SPI1STATbits.SPIRBF) ;
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		dummy = SPI1BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 write_polling_port2(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;
	register EE_UREG dummy;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI2STATbits.SPITBE) ; 
   		SPI2BUF = data[i];
   		while (!SPI2STATbits.SPIRBF) ;
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
		dummy = SPI2BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}

#endif

/******************************************************************************/
/*				Read Functions				      */
/******************************************************************************/


#ifdef __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu	*	      */
/*   	*********************************************************	      */
/******************************************************************************/

#ifdef __USE_SPI_PORT1A__
__INLINE__ EE_INT8 read_polling_port1A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1ASTATCLR = _SPI1ASTAT_SPIROV_MASK; 
   		while (!SPI1ASTATbits.SPITBE) ; 
   		SPI1ABUF = 0;
   		while (!SPI1ASTATbits.SPIRBF) ;
		SPI1ASTATCLR = _SPI1ASTAT_SPIROV_MASK; 
		data[i] = SPI1ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT1__



#ifdef __USE_SPI_PORT2A__
__INLINE__ EE_INT8 read_polling_port2A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI2ASTATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI2ASTATbits.SPITBE) ; 
   		SPI2ABUF = 0;
   		while (!SPI2ASTATbits.SPIRBF) ;
		SPI2STATCLR = _SPI2ASTAT_SPIROV_MASK; 
		data[i] = SPI2ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT2A__



#ifdef __USE_SPI_PORT3A__
__INLINE__ EE_INT8 read_polling_port3A(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI3ASTATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI3ASTATbits.SPITBE) ; 
   		SPI3ABUF = 0;
   		while (!SPI3ASTATbits.SPIRBF) ;
		SPI3ASTATCLR = _SPI3ASTAT_SPIROV_MASK; 
		data[i] = SPI3ABUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT3A__



#ifdef __USE_SPI_PORT1__
__INLINE__ EE_INT8 read_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
   		while (!SPI1STATbits.SPITBE) ; 
   		SPI1BUF = 0;
   		while (!SPI1STATbits.SPIRBF) ;
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		data[i] = SPI1BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}
#endif //__USE_SPI_PORT1__


#else //not defined __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx360f512l mcu	*	      */
/*   	*********************************************************	      */
/******************************************************************************/

__INLINE__ EE_INT8 read_polling_port1(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
   		while (!SPI1STATbits.SPITBE) ; 
   		SPI1BUF = 0;
   		while (!SPI1STATbits.SPIRBF) ;
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		data[i] = SPI1BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}

__INLINE__ EE_INT8 read_polling_port2(EE_UINT8 *data, EE_UINT32 len) 
{
	EE_UINT32 i;

	/* TODO: what if Slave mode?  */
	for (i = 0; i < len; i++) {
		/* TODO: use the SPIROV in IRQ mode */
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI2STATbits.SPITBE) ; 
   		SPI2BUF = 0;
   		while (!SPI2STATbits.SPIRBF) ;
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
		data[i] = SPI2BUF & 0x00FF;
	}
	return EE_SPI_NO_ERRORS;
}

#endif

/******************************************************************************/
/*                                SPI ISRs                                    */
/******************************************************************************/


#ifdef __32MX795F512L__


/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of ISRs for the pic32mx795f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/

#ifdef __USE_SPI_PORT1__
#ifdef __USE_SPI_PORT1_DMA__
ISR2(SPI1_DMA_IRQ) 
{
	
	register EE_UREG dummy;

	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI1_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI1_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI1_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI1STAT & _SPI1STAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI1BUF;			// Clean the SPIRBF bit
		if (port1_tx_callback)
			port1_tx_callback();
	}
	
}
#endif //__USE_SPI_PORT1_DMA__
#endif //__USE_SPI_PORT1__


#ifdef __USE_SPI_PORT1A__
#ifdef __USE_SPI_PORT1A_DMA__
ISR2(SPI1A_DMA_IRQ) 
{
	
	register EE_UREG dummy;

	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI1A_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI1A_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI1A_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI1ASTAT & _SPI1ASTAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI1ABUF;			// Clean the SPIRBF bit
		if (port1a_tx_callback)
			port1a_tx_callback();
	}

}
#endif //__USE_SPI_PORT1A_DMA__
#endif //__USE_SPI_PORT1A__


#ifdef __USE_SPI_PORT2A__
#ifdef __USE_SPI_PORT2A_DMA__
ISR2(SPI2A_DMA_IRQ) 
{
	
	register EE_UREG dummy;

	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI2A_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI2A_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI2A_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI2ASTAT & _SPI2ASTAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI2ABUF;			// Clean the SPIRBF bit
		if (port2a_tx_callback)
			port2a_tx_callback();
	}
	
}
#endif //__USE_SPI_PORT2A_DMA__
#endif //__USE_SPI_PORT2A__



#ifdef __USE_SPI_PORT3A__
#ifdef __USE_SPI_PORT3A_DMA__
ISR2(SPI3A_DMA_IRQ) 
{
		
	register EE_UREG dummy;
	
	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI3A_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI3A_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI3A_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI3ASTAT & _SPI3ASTAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI3ABUF;			// Clean the SPIRBF bit
		if (port3a_tx_callback)
			port3a_tx_callback();
	
	}
	
}
#endif //__USE_SPI_PORT3A_DMA__
#endif //__USE_SPI_PORT3A__


#else //not defined __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of ISRs for the pic32mx360f512l mcu 	*	      */
/*   	*********************************************************	      */
/******************************************************************************/

ISR2(SPI1_DMA_IRQ) 
{
	register EE_UREG dummy;

	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI1_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI1_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI1_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI1STAT & _SPI1STAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI1BUF;			// Clean the SPIRBF bit
		if (port1_tx_callback)
			port1_tx_callback();
	}
}

ISR2(SPI2_DMA_IRQ) 
{
	register EE_UREG dummy;

	// TODO: when DMA rx is done, rebuild this ISR!
	IFS1CLR = SPI2_DMAIF_MASK;			// Clear DMA channel IRQ
	if (SPI2_DCHINT & SPI_DCHINT_CHBCIF_MASK) {	// Check BlockEnd IRQ
		SPI2_DCHINTCLR = SPI_DCHINT_CHBCIF_MASK;// Clear IRQ source
		// TODO: check if this leads to deadlock
		while (SPI2STAT & _SPI2STAT_SPIBUSY_MASK) ; // Wait bus done
		dummy = SPI2BUF;			// Clean the SPIRBF bit
		if (port2_tx_callback)
			port2_tx_callback();
	}
}

#endif


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
EE_INT8 EE_spi_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags) 
{

#ifdef __32MX795F512L__
	
	switch (port) {

	#ifdef __USE_SPI_PORT1__
	case EE_SPI_PORT_1:
		init_port1(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT1__
	
	#ifdef __USE_SPI_PORT1A__
	case EE_SPI_PORT_1A:
		init_port1A(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT1A__	
	
	#ifdef __USE_SPI_PORT2A__
	case EE_SPI_PORT_2A:
		init_port2A(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT2A__
	
	#ifdef __USE_SPI_PORT3A__
	case EE_SPI_PORT_3A:
		init_port3A(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT3A__
	
	default:
		return -EE_SPI_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__
	
	if (port == EE_SPI_PORT_1) {
		init_port1(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		init_port2(baudrate, flags); 
		return EE_SPI_NO_ERRORS;
	}
	return -EE_SPI_ERR_BAD_PORT;
#endif
}

EE_INT8 EE_spi_close(EE_UINT8 port)
{

#ifdef __32MX795F512L__

	switch (port) {
	
	#ifdef __USE_SPI_PORT1__
	case EE_SPI_PORT_1:
		SPI1CONCLR= _SPI1CON_ON_MASK;
		port1_flags = 0;
		return EE_SPI_NO_ERRORS;
	break;
	#endif

	#ifdef __USE_SPI_PORT1A__
	case EE_SPI_PORT_1A:
		SPI1ACONCLR= _SPI1ACON_ON_MASK;
		port1a_flags = 0;
		return EE_SPI_NO_ERRORS;
	break;
	#endif

	#ifdef __USE_SPI_PORT2A__
	case EE_SPI_PORT_2A:
		SPI2ACONCLR= _SPI2ACON_ON_MASK;
		port2a_flags = 0;
		return EE_SPI_NO_ERRORS;
	break;
	#endif

	#ifdef __USE_SPI_PORT3A__
	case EE_SPI_PORT_3A:
		SPI3ACONCLR= _SPI3ACON_ON_MASK;
		port3a_flags = 0;
		return EE_SPI_NO_ERRORS;
	break;
	#endif

	default:
		return -EE_SPI_ERR_BAD_PORT;
	}	

#else //not defined __32MX795F512L__

	if (port == EE_SPI_PORT_1) {
		SPI1CONCLR= _SPI1CON_ON_MASK;
		port1_flags = 0;
		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		SPI2CONCLR= _SPI2CON_ON_MASK;
		port2_flags = 0;
		return EE_SPI_NO_ERRORS;
	}
	return -EE_SPI_ERR_BAD_PORT;

#endif
}




EE_INT8 EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{	

#ifdef __32MX795F512L__
	
	switch (port) {
	#ifdef __USE_SPI_PORT1__
	#ifdef __USE_SPI_PORT1_DMA__
	case EE_SPI_PORT_1:
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port1_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT1_DMA__
	#endif //__USE_SPI_PORT1__

	#ifdef __USE_SPI_PORT1A__
	#ifdef __USE_SPI_PORT1A_DMA__
	case EE_SPI_PORT_1A:
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port1a_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT1A_DMA__
	#endif //__USE_SPI_PORT1A__


	#ifdef __USE_SPI_PORT2A__
	#ifdef __USE_SPI_PORT2A_DMA__
	case EE_SPI_PORT_2A:
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port2a_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT2A_DMA__
	#endif //__USE_SPI_PORT2A__
	
	#ifdef __USE_SPI_PORT3A__
	#ifdef __USE_SPI_PORT3A_DMA__
	case EE_SPI_PORT_3A:
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port3a_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	break;
	#endif //__USE_SPI_PORT3A_DMA__
	#endif //__USE_SPI_PORT3A__

	default:
		return -EE_SPI_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__
	if (port == EE_SPI_PORT_1) {
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port1_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		switch (event) {
		case EE_SPI_EVT_TX_DONE :
			port2_tx_callback = f;
			break;
		case EE_SPI_EVT_RX_DONE :
		default :
			return -EE_SPI_ERR_BAD_ARGS;
		}
		return EE_SPI_NO_ERRORS;
	}
	return -EE_SPI_ERR_BAD_PORT;
	
#endif
}


EE_INT8 EE_spi_write(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{

#ifdef __32MX795F512L__	

	switch (port) {

	#ifdef __USE_SPI_PORT1__
	case EE_SPI_PORT_1:
		if(IS_DMA_TX(port1_flags))
			#ifdef __USE_SPI_PORT1_DMA__
			return write_dma_port1(data, len);
			#else
			return -EE_SPI_ERR_UNIMPLEMENTED;
			#endif
		return write_polling_port1(data, len);
	break;
	#endif //__USE_SPI_PORT1__
	
	#ifdef __USE_SPI_PORT1A__
	case EE_SPI_PORT_1A:
		if(IS_DMA_TX(port1a_flags)) 
			#ifdef __USE_SPI_PORT1A_DMA__
			return write_dma_port1A(data, len);
			#else
			return -EE_SPI_ERR_UNIMPLEMENTED;
			#endif
		return write_polling_port1A(data, len);
	break;
	#endif //__USE_SPI_PORT1A__

	#ifdef __USE_SPI_PORT2A__
	case EE_SPI_PORT_2A:
		if(IS_DMA_TX(port2a_flags))
			#ifdef __USE_SPI_PORT2A_DMA__ 
			return write_dma_port2A(data, len);
			#else
			return -EE_SPI_ERR_UNIMPLEMENTED;
			#endif			
		return write_polling_port2A(data, len);
	break;
	#endif //__USE_SPI_PORT2A__	
	
	#ifdef __USE_SPI_PORT3A__
	case EE_SPI_PORT_3A:
		if(IS_DMA_TX(port3a_flags)) 
			#ifdef __USE_SPI_PORT3A_DMA__ 
			return write_dma_port3A(data, len);
			#else
			return -EE_SPI_ERR_UNIMPLEMENTED;
			#endif
		return write_polling_port3A(data, len);
	break;
	#endif //__USE_SPI_PORT3A__
	default:
		return -EE_SPI_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__	

	if (port == EE_SPI_PORT_1) {
		if(IS_DMA_TX(port1_flags))
			return write_dma_port1(data, len);
		return write_polling_port1(data, len);
	} else if (port == EE_SPI_PORT_2) {
		if(IS_DMA_TX(port2_flags)) 
			return write_dma_port2(data, len);
		return write_polling_port2(data, len);
	}
	return -EE_SPI_ERR_BAD_PORT;

#endif
}


EE_INT8 EE_spi_read(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{

#ifdef __32MX795F512L__

	switch (port) {
	#ifdef __USE_SPI_PORT1__
	case EE_SPI_PORT_1:
		if(IS_DMA_RX(port1_flags)) 
			//	read write_dma_port1(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port1(data, len);
	break;
	#endif //__USE_SPI_PORT1__

	#ifdef __USE_SPI_PORT1A__
	case EE_SPI_PORT_1A:
		if(IS_DMA_RX(port1a_flags)) 
			//	read write_dma_port1A(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port1A(data, len);
	break;
	#endif //__USE_SPI_PORT1A__	
	
	#ifdef __USE_SPI_PORT2A__
	case EE_SPI_PORT_2A:
		if(IS_DMA_RX(port2a_flags)) 
			//	read write_dma_port2A(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port2A(data, len);
	break;
	#endif //__USE_SPI_PORT2A__

	#ifdef __USE_SPI_PORT3A__
	case EE_SPI_PORT_3A:
		if(IS_DMA_RX(port3a_flags)) 
			//	read write_dma_port3A(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port3A(data, len);
	break;
	#endif //__USE_SPI_PORT3A__

	default:
		return -EE_SPI_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__	
	if (port == EE_SPI_PORT_1) {
		if(IS_DMA_RX(port1_flags)) 
		//	read write_dma_port1(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port1(data, len);
	} else if (port == EE_SPI_PORT_2) {
		if(IS_DMA_RX(port2_flags)) 
		//	read write_dma_port2(data, len);
			return -EE_SPI_ERR_UNIMPLEMENTED;
		return read_polling_port2(data, len);
	}
	return -EE_SPI_ERR_BAD_PORT;

#endif
}
