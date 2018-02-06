/*********************************************************************
 *
 *                  SNMP Defs for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        SNMP.h
 * Dependencies:    StackTsk.h
 *                  UDP.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * Author               Date     Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     1/9/03   Original        (Rev 1.0)
 * Amit Shirbhate 		09/24/08 SNMPv2c Support added.	
 ********************************************************************/
 
#ifndef SNMP_H
#define SNMP_H


/****************************************************************************
  Section:
	Macros and Definitions 
  ***************************************************************************/

#define DATA_TYPE_TABLE_SIZE    (sizeof(dataTypeTable)/sizeof(dataTypeTable[0]))


//This is the file that contains SNMP BIB file.
//File name must contain all upper case letter and must match
//with what was included in MPFS image.
#if defined(STACK_USE_MPFS)
#define SNMP_BIB_FILE_NAME      "SNMP.BIB"
#else
#define SNMP_BIB_FILE_NAME		"snmp.bib"
#endif


//Change this to match your OID string length.
#define OID_MAX_LEN             (15)

#define SNMP_START_OF_VAR       (0)
#define SNMP_END_OF_VAR         (0xff)
#define SNMP_INDEX_INVALID      (0xff)


//Trap information.
//This table maintains list of intereseted receivers
//who should receive notifications when some interesting
//event occurs.
#define TRAP_TABLE_SIZE         (2)
#define TRAP_COMMUNITY_MAX_LEN       (8)


//This is the SNMP OID variable id.
//This id is assigned via MIB file.  Only dynamic and AgentID
//variables can contian ID.  MIB2BIB utility enforces this
//rules when BIB was generated.
typedef BYTE SNMP_ID;
typedef BYTE SNMP_INDEX;



/****************************************************************************
  Section:
	Data Structures and Enumerations
  ***************************************************************************/

typedef struct 
{
   BYTE Size;
   struct
   {
       BYTE communityLen;					//Community name length
       char community[TRAP_COMMUNITY_MAX_LEN];	//Community name array
       IP_ADDR IPAddress;					//IP address to which trap to be sent
       struct
       {
           unsigned int bEnabled : 1;		//Trap enabled flag	
       } Flags;
   } table[TRAP_TABLE_SIZE];				
} TRAP_INFO;

typedef union
{
    DWORD dword;				//double word value
    WORD  word;					//word value
    BYTE  byte;					//byte value
    BYTE  v[sizeof(DWORD)];		//byte array
} SNMP_VAL;

typedef enum
{
	READ_COMMUNITY=1,		//Read only community	
	WRITE_COMMUNITY=2,		//Read write community
	INVALID_COMMUNITY=3			//Community invalid
}COMMUNITY_TYPE;


//This is the list of SNMP action a remote NMS can perform.
//This inforamtion is passed to application via
//callback SNMPValidateCommunity().
//Application should validate the action for given community
//string.
typedef enum
{
    SNMP_GET            = 0xa0,	//Snmp GET identifier
    SNMP_GET_NEXT       = 0xa1, //Snmp GET_NEXT identifier
    SNMP_GET_RESPONSE   = 0xa2,	//Snmp GET_RESPONSE identifier
    SNMP_SET            = 0xa3,	//Snmp SET identifier
    SNMP_TRAP           = 0xa4,	//Snmp TRAP identifier
    SNMP_V2C_GET_BULK	= 0xa5,	//Snmp GET_BULK identifier
    SNMP_ACTION_UNKNOWN = 0		//Snmp requested action unknown
} SNMP_ACTION;

typedef enum
{
	COLD_START 			=0x0,
	WARM_START			=0x1,
	LINK_DOWN			=0x2,
	LINK_UP				=0x3,
	AUTH_FAILURE		=0x4,	
	EGP_NEBOR_LOSS		=0x5,
	ENTERPRISE_SPECIFIC	=0x6
	
} GENERIC_TRAP_NOTIFICATION_TYPE; 


typedef enum
{
	VENDOR_TRAP_DEFAULT 	=0x0,
	BUTTON_PUSH_EVENT		=0x1,
	POT_READING_MORE_512	=0x2
} VENDOR_SPECIFIC_TRAP_NOTIFICATION_TYPE;


/****************************************************************************
  Section:
	Global Variables
  ***************************************************************************/
extern BYTE gSendTrapFlag;//Global flag to send Trap
extern BYTE gGenericTrapNotification;//Global flag for Generic trap notification
extern BYTE gSpecificTrapNotification;//Global flag for vendor specific trap notification
extern BYTE gOIDCorrespondingSnmpMibID;//Gloabal var to store SNMP ID of var for OID received in SNMP request.


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/
void SNMPInit(void);
BOOL SNMPTask(void);
void SNMPSendTrap(void);
BYTE SNMPValidateCommunity(BYTE* community);
BOOL SNMPNotify(SNMP_ID var, SNMP_VAL val, SNMP_INDEX index);
BOOL SNMPSetVar(SNMP_ID var, SNMP_INDEX index,BYTE ref, SNMP_VAL val);
BOOL SNMPGetVar(SNMP_ID var, SNMP_INDEX index,BYTE* ref, SNMP_VAL* val);
BOOL SNMPIsNotifyReady(IP_ADDR* remoteHost);
void SNMPNotifyPrepare(IP_ADDR* remoteHost, char* community, BYTE communityLen, SNMP_ID agentIDVar, BYTE notificationCode, DWORD timestamp);
BOOL SNMPGetNextIndex(SNMP_ID var, SNMP_INDEX* index);
BOOL SNMPIsValidSetLen(SNMP_ID var, BYTE len);

#endif
