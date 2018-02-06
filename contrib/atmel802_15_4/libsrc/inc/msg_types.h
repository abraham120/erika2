/**
 * \file msg_types.h
 * \brief This file defines all message structures.
 *
 * $Id: msg_types.h,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MSG_TYPES_H
#define MSG_TYPES_H

#ifndef ALIGN8BIT
# define ALIGN8BIT
#endif

/* === Includes ============================================================= */
#include "wpan_mac.h"
#include "msg_const.h"
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================ */

/* === Types ================================================================ */


/**
 * \brief octet string, the 0th element gives the length of data
 *
 * \code
 *   char *mystr = "hello world"
 *   octetstr_t data[20];
 *   data[0]=strlen(mystr);
 *   strcpy(&data[1], mystr, data[0]);
 * \endcode
 */
typedef uint8_t octetstr_t;

/* === CMDIF-SAP messages =================================================== */

/** \brief This is the CMDIF-ECHO.request message structure.
*/
typedef struct cmdif_echo_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_REQUEST */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to read to frame, data[0] gives the length */
} cmdif_echo_req_t;

/** \brief This is the CMDIF-ECHO.confirm message structure.
*/
typedef struct cmdif_echo_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_CONFIRM */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to read to frame, data[0] gives the length */
} cmdif_echo_conf_t;

/** \brief This is the CMDIF-ECHO.indication message structure.
*/
typedef struct echo_ind_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to read to frame, data[0] gives the length */
} echo_ind_t;


/** \brief This is the CMDIF-VERSION.request message structure.
*/
typedef struct cmdif_version_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
} cmdif_version_req_t;

/** \brief This is the CMDIF-VERSION.confirm message structure.
*/
typedef struct cmdif_version_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
    uint8_t     major       ALIGN8BIT; /**< major version number */
    uint8_t     minor       ALIGN8BIT; /**< minor version number */
    uint8_t     revision    ALIGN8BIT; /**< revision number */
    uint8_t     apptype     ALIGN8BIT; /**< application type number */
    uint8_t     boardtype   ALIGN8BIT; /**< board type number */
    uint64_t    macaddr     ALIGN8BIT; /**< MAC address (first 8 byte in EEPROM)*/
} cmdif_version_conf_t;


/** \brief This is the CMDIF-VALIDATION.request message structure.
*/
typedef struct cmdif_validation_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
    uint8_t     subcmd      ALIGN8BIT; /**< code for the validation sub command */
    octetstr_t  data[1]     ALIGN8BIT; /**< argument data of this message */
} cmdif_validation_req_t;

/** \brief This is the CMDIF-VALIDATION.confirm message structure.
*/
typedef struct cmdif_validation_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
    uint8_t     subcmd      ALIGN8BIT; /**< code for the validation sub command, which was processed */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the validation request. */
    octetstr_t  data[1]     ALIGN8BIT; /** < argument data of this message  */
} cmdif_validation_conf_t;

/** \brief This is the CMDIF-VALIDATION.indication message structure.
*/
typedef struct cmdif_validation_ind_tag
{
    uint8_t     size        ALIGN8BIT;    /**< The total length of this message. */
    enum msg_code cmdcode   ALIGN8BIT;   /**< This identifies the message as \ref CMDIF_ECHO_INDICATION */
    uint8_t     subind      ALIGN8BIT;   /**< code for the validation sub indication */
    octetstr_t  data[1]     ALIGN8BIT;   /** < argument data of this message  */
} cmdif_validation_ind_t;

/** \brief This is the CMDIF-REGRD.request message structure.
*/
typedef struct regrd_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_REGRD_REQUEST */
    uint8_t     address     ALIGN8BIT; /**< The address (offset) of the register in the transceiver that should be read. */
} regrd_req_t;

/** \brief This is the CMDIF-REGRD.confirm message structure.
*/
typedef struct regrd_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_REGRD_CONFIRM */
    uint32_t    value       ALIGN8BIT; /**< The value of the register in the Transceiver that was be read. */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to read a register. */
} regrd_conf_t;

/** \brief This is the CMDIF-REGWR.request message structure.
*/
typedef struct regwr_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_REGWR_REQUEST */
    uint8_t     address     ALIGN8BIT; /**< The address (offset) of the register in the transceiver that should be written. */
    uint16_t    value       ALIGN8BIT; /**< The value of the register in the Transceiver that should be written. */
} regwr_req_t;

/** \brief This is the CMDIF-REGWR.confirm message structure.
*/
typedef struct regwr_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_REGWR_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} regwr_conf_t;


/** \brief This is the CMDIF-BITRD.request message structure.
*/
typedef struct bitrd_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_BITRD_REQUEST */
    uint8_t     address     ALIGN8BIT; /**< address (offset) of the register in the transceiver that should be written. */
    uint16_t    mask        ALIGN8BIT; /**< mask value for bit register */
    uint8_t     pos         ALIGN8BIT; /**< position counted from MSB */

} bitrd_req_t;

/** \brief This is the CMDIF-BITRD.confirm message structure.
*/
typedef struct bitrd_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_BITRD_CONFIRM */
    uint16_t    value       ALIGN8BIT; /**< The value of the sub register */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} bitrd_conf_t;


/** \brief This is the CMDIF-BITWR.request message structure.
*/
typedef struct bitwr_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_BITWR_REQUEST */
    uint8_t     address     ALIGN8BIT; /**< address (offset) of the register in the transceiver that should be written. */
    uint16_t    mask        ALIGN8BIT; /**< mask value for bit register */
    uint8_t     pos         ALIGN8BIT; /**< position counted from MSB */
    uint16_t    value       ALIGN8BIT; /**< The value of the sub register */

} bitwr_req_t;

/** \brief This is the CMDIF-BITWR.confirm message structure.
*/
typedef struct bitwr_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_BITWR_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} bitwr_conf_t;

/** \brief This is the CMDIF-PINSET.request message structure.
*/
typedef struct pinset_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_PINSET_REQUEST */
    uint8_t     pinid       ALIGN8BIT; /**< The identifier of the pin in the transceiver that should be set. */
    uint8_t     value       ALIGN8BIT; /**< The value of the pin in the Transceiver that should be set. */
} pinset_req_t;

/** \brief This is the CMDIF-PINSET.confirm message structure.
*/
typedef struct pinset_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_PINSET_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} pinset_conf_t;

/** \brief This is the CMDIF-PINGET.request message structure.
*/
typedef struct pinget_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_PINGET_REQUEST */
    uint8_t     pinid       ALIGN8BIT; /**< The identifier of the pin in the transceiver that should be set. */
} pinget_req_t;

/** \brief This is the CMDIF-PINGET.confirm message structure.
*/
typedef struct pinget_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_PINGET_CONFIRM */
    uint8_t     value       ALIGN8BIT; /**< The value of the pin in the Transceiver that should be get. */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} pinget_conf_t;


/** \brief CMDIF-SRAMUP.request message structure
 */
typedef struct sramup_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SRAMUP_CONFIRM */
    uint16_t    address     ALIGN8BIT; /**< SRAM start address */
    uint8_t     length      ALIGN8BIT; /**< number of bytes to copy */
} sramup_req_t;


/** \brief CMDIF-SRAMUP.confirm message structure
 */
typedef struct sramup_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SRAMUP_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< result of the sram read request */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to read to SRAM, data[0] gives the length */
} sramup_conf_t;


/** \brief CMDIF-SRAMDN.request message structure
 */
typedef struct sramdn_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SRAMUP_REQUEST */
    uint16_t    address     ALIGN8BIT; /**< SRAM start address */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to write to SRAM, data[0] gives the length */
} sramdn_req_t;

/** \brief CMDIF-SRAMDWN.confirm message structure
 */
typedef struct sramdn_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SRAMUP_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} sramdn_conf_t;



/** \brief CMDIF-FRAMEUP.request message structure
 */
typedef struct frameup_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_FRAMEUP_REQUEST */
} frameup_req_t;


/** \brief CMDIF-FRAMEUP.confirm message structure
 */
typedef struct frameup_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_FRAMEUP_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< result of the frame read request */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to read to frame, data[0] gives the length */
} frameup_conf_t;


/** \brief CMDIF-FRAMEDWN.request message structure
 */
typedef struct framedn_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_FRAMEDWN_REQUEST */
    octetstr_t  data[1]     ALIGN8BIT; /** < bytes to write to frame, data[0] gives the length */
} framedn_req_t;

/** \brief CMDIF-FRAMEDWN.confirm message structure
 */
typedef struct framedn_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_FRAMEDWN_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} framedn_conf_t;

/** \brief CMDIF-SET_ROUTE.request message structure */
typedef struct cmdif_set_route_req_tag {
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SET_ROUTE_REQUEST */
    /** This value specifies the message type */
    uint8_t     mtype       ALIGN8BIT;
    /** 0 means no routing, and 1 means route this message type */
    uint8_t     state       ALIGN8BIT;
} cmdif_set_route_req_t;

/** \brief CMDIF-SET_ROUTE.confirm message structure */
typedef struct cmdif_set_route_conf_tag {
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_SET_ROUTE_CONFIRM */
    /** 0 on SUCCESS */
    uint8_t     status      ALIGN8BIT;
} cmdif_set_route_conf_t;

/** \brief CMDIF-GET_ROUTE.request message structure */
typedef struct cmdif_get_route_req_tag {
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_GET_ROUTE_REQUEST */
    /** If the value is 0, then this request speicifies the UART routing. If
    the value is 1, than it defines the internal routing. */
    uint8_t     direction   ALIGN8BIT;
    /** This value specifies the message type */
    uint8_t     mtype       ALIGN8BIT;
} cmdif_get_route_req_t;

/** \brief CMDIF-GET_ROUTE.confirm message structure */
typedef struct cmdif_get_route_conf_tag {
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_GET_ROUTE_CONFIRM */
    uint8_t     status      ALIGN8BIT;
} cmdif_get_route_conf_t;

/** \brief CMDIF-BOOTLOAD.confirm message structure */
typedef struct cmdif_bootload_req_tag {
    uint8_t     size        ALIGN8BIT; /**< The total length of this message.  */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_BOOTLOAD_REQUEST */
} cmdif_bootload_req_t;

/** \brief TIMER_EXPIRED.indication message structure */
typedef struct timer_expired_ind_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref TIMER_EXPIRED_INDICATION */
    uint8_t     tid         ALIGN8BIT; /**< The identifier of the timer that expired */
} timer_expired_ind_t;

/** \brief CMDIF_TMRSTART.indication message structure */
typedef struct timerstart_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_TMRSTART_REQUEST  */
    uint8_t     tid         ALIGN8BIT; /**< The identifier of the timer that is started */
    uint32_t    timeout     ALIGN8BIT; /**< The duration of the timer */
} timerstart_req_t;

/** \brief CMDIF_TMRSTART.confirm message structure */
typedef struct timerstart_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_TMRSTART_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} timerstart_conf_t;

/** \brief CMDIF_TMRSTOP.indication message structure */
typedef struct timerstop_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_TMRSTOP_REQUEST */
    uint8_t     tid         ALIGN8BIT; /**< The identifier of the timer that expired */
} timerstop_req_t;

/** \brief CMDIF_TMRSTOP.confirm message structure */
typedef struct timerstop_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref CMDIF_TMRSTOP_CONFIRM */
    uint8_t     cnfcode     ALIGN8BIT; /**< The result of the request to write a register. */
} timerstop_conf_t;


/** \brief TRX_INTERRUPT.indication message structure */
typedef struct trx_interrupt_ind_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref TRX_INTERRUPT_INDICATION */
    uint8_t     cause       ALIGN8BIT; /**< The cuase of that interrupt */
} trx_interrupt_ind_t;


/* === PD-SAP messages ====================================================== */

/** \brief This is the PD-DATA.request message structure.
*/
typedef struct pd_data_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PD_DATA_REQUEST */
    uint8_t     psduLength  ALIGN8BIT; /**< The number of octets contained in the PSDU to be transmitted by the PHY entity.*/
    octetstr_t  data[1]     ALIGN8BIT; /**< The first octet of the PSDU. */
} pd_data_req_t;

/** \brief This is the PD-DATA.confirm message structure.
*/
typedef struct pd_data_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PD_DATA_CONFIRM */
    uint8_t     status      ALIGN8BIT; /**< The result of the request to transmit a packet.*/
} pd_data_conf_t;


/** \brief This is the PD-DATA.indication message structure.
*/
typedef struct pd_data_ind_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PD_DATA_INDICATION */
    uint8_t     psduLength  ALIGN8BIT; /**< The number of octets contained in the PSDU by the PHY entity.*/
    uint8_t     ppduLinkQuality ALIGN8BIT; /**< Link quality (LQ) value measured during reception of the PPDU. */
    uint32_t    timestamp   ALIGN8BIT; /**< The system time at SFD interrupt. */
    octetstr_t  data[1]     ALIGN8BIT; /**< The first octet of the PSDU and ppduLinkQuality = psdu[psduLength] */
} pd_data_ind_t;


/* === PLME-SAP messages ==================================================== */

/** \brief This is the PLME-CCA.request message structure.
*/
typedef struct plme_cca_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_CCA_REQUEST */
} plme_cca_req_t;

/** \brief This is the PLME-CCA.confirm message structure.
*/
typedef struct plme_cca_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_CCA_CONFIRM */
    uint8_t     status      ALIGN8BIT; /**< The result of the request to perform a CCA. ( \ref TRX_OFF, \ref TX_ON, \ref BUSY, or \ref IDLE ) */
} plme_cca_conf_t;

/** \brief This is the PLME-ED.request message structure.
*/
typedef struct plme_ed_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_ED_REQUEST */
} plme_ed_req_t;

/** \brief This is the PLME-ED.confirm message structure.
*/
typedef struct plme_ed_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_ED_CONFIRM */
    uint8_t     status      ALIGN8BIT; /**< The result of the request to perform an ED measurement. ( \ref SUCCESS, \ref TRX_OFF, or \ref TX_ON ) */
    uint8_t     EnergyLevel ALIGN8BIT; /**< The ED level for the current channel. */
} plme_ed_conf_t;

/** \brief This is the PLME-GET.request message structure.
*/
typedef struct plme_get_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref PLME_GET_REQUEST */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the PHY PIB attribute to get. */
} plme_get_req_t;

/** \brief This is the PLME-GET.confirm message structure.
*/
typedef struct plme_get_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref PLME_GET_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request for PHY PIB attribute information.*/
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the PHY PIB attribute to get. */
    octetstr_t  data[1]      ALIGN8BIT; /**< The first byte of the value which is indicated by PHY PIB attribute to get. */
} plme_get_conf_t;

/** \brief This is the PLME-SET.request message structure.
*/
typedef struct plme_set_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref PLME_SET_REQUEST */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the PHY PIB attribute to set. */
    octetstr_t  data[1]      ALIGN8BIT; /**< The first byte of the value which is indicated by PHY PIB attribute to set. */
} plme_set_req_t;

/** \brief This is the PLME-SET.confirm message structure.
*/
typedef struct plme_set_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref PLME_SET_CONFIRM */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the PHY PIB attribute to set. */
    uint8_t     status       ALIGN8BIT; /**< The status of the attempt to set the request PIB attribute. */
} plme_set_conf_t;

/** \brief This is the PLME-SET-TRX-STATE.request message structure.
*/
typedef struct plme_set_trx_state_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_SET_TRX_STATE_REQUEST */
    uint8_t     state       ALIGN8BIT; /**< The new state in which to configure the transceiver. */
} plme_set_trx_state_req_t;

/** \brief This is the PLME-SET-TRX-STATE.confirm message structure.
*/
typedef struct plme_set_trx_state_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref PLME_SET_TRX_STATE_CONFIRM */
    uint8_t     status      ALIGN8BIT; /**< The result of the request to change the state of the transceiver. (\ref SUCCESS, \ref RX_ON, \ref TRX_OFF, \ref TX_ON, \ref BUSY_RX, or \ref BUSY_TX ) */
} plme_set_trx_state_conf_t;

/* === MCPS-SAP messages ==================================================== */

/** \brief This is the MCPS-DATA.request message structure.
*/
typedef struct mcps_data_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MCPS_DATA_REQUEST */
    /** The source addressing mode for this primitive and subsequent MPDU. This
    value can take one of the following values: 0 x 00 = no address (addressing
    fields omitted). 0 x 01 = reserved. 0 x 02 = 16 bit short address. 0 x 03 =
    64 bit extended address.*/
    uint8_t    SrcAddrMode ALIGN8BIT;
    /** The 16 bit PAN identifier of the entity from which the MSDU is being transferred. */
    uint16_t    SrcPANId    ALIGN8BIT;
    /** The individual device address of the entity from which the MSDU is being transferred. */
    uint64_t    SrcAddr     ALIGN8BIT;
    /** The destination addressing mode for this primitive and subsequent MPDU.
    This value can take one of the following values: 0 x 00 = no address
    (addressing fields omitted). 0 x 01 = reserved. 0 x 02 = 16 bit short
    address. 0 x 03 = 64 bit extended address. */
    uint8_t     DstAddrMode ALIGN8BIT;
    /** The 16 bit PAN identifier of the entity to which the MSDU is being transferred. */
    uint16_t    DstPANId    ALIGN8BIT;
    /** The individual device address of the entity to which the MSDU is being transferred. */
    uint64_t    DstAddr     ALIGN8BIT;
    /** The handle associated with the MSDU to be transmitted by the MAC sublayer entity. */
    uint8_t    msduHandle  ALIGN8BIT;
    /** The transmission options for this MSDU. These are a bitwise OR of one or
    more of the following: 0 x 01 = acknowledged transmission. 0 x 02 = GTS
    transmission. 0 x 04 = indirect transmission. 0 x 08 = security enabled
    transmission. */
    uint8_t     TxOptions   ALIGN8BIT;
    /** The number of octets contained in the MSDU to be transmitted by the MAC sublayer entity. */
    uint8_t     msduLength  ALIGN8BIT;
    /** The set of octets forming the MSDU to be transmitted by the MAC sublayer entity. */
    octetstr_t  data[1]     ALIGN8BIT;
} mcps_data_req_t;

/** \brief This is the MCPS-DATA.confirm message structure.
*/
typedef struct mcps_data_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MCPS_DATA_CONFIRM */
    /** The handle associated with the MSDU being confirmed. */
    uint8_t    msduHandle  ALIGN8BIT;
    /** The status of the last MSDU transmission. */
    uint8_t     status      ALIGN8BIT;
} mcps_data_conf_t;

/** \brief This is the MCPS-DATA.indication message structure.
*/
typedef struct mcps_data_ind_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MCPS_DATA_INDICATION */
    /** The source addressing mode for this primitive corresponding to the
    received MPDU. This value can take one of the following values: 0 x 00 = no
    address (addressing fields omitted). 0 x 01 = reserved. 0 x 02 = 16 bit
    short address. 0 x 03 = 64 bit extended address.*/
    uint8_t    SrcAddrMode ALIGN8BIT;
    /** The 16 bit PAN identifier of the entity from which the MSDU was received. */
    uint16_t    SrcPANId    ALIGN8BIT;
    /** The individual device address of the entity from which the MSDU was received. */
    uint64_t    SrcAddr     ALIGN8BIT;
    /** The destination addressing mode for this primitive corresponding to the
    received MPDU. This value can take one of the following values: 0 x 00 = no
    address (addressing fields omitted). 0 x 01 = reserved. 0 x 02 = 16 bit
    short device address. 0 x 03 = 64 bit extended device address. */
    uint8_t     DstAddrMode ALIGN8BIT;
    /** The 16 bit PAN identifier of the entity to which the MSDU is being transferred. */
    uint16_t    DstPANId    ALIGN8BIT;
    /** The individual device address of the entity to which the MSDU is being transferred.*/
    uint64_t    DstAddr     ALIGN8BIT;
    /** LQ value measured during reception of the MPDU. Lower values represent lower LQ (see 6.7.8). */
    uint8_t     mpduLinkQuality ALIGN8BIT;
    /** An indication of whether the received data frame is using security. This
    value is set to TRUE if the security enable subfield was set to 1 or FALSE
    if the security enabled subfield was set to 0. */
    uint8_t     SecurityUse ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0 x 08 if the sender of
    the data frame was not found in the ACL. */
    uint8_t     ACLEntry    ALIGN8BIT;
    /** Size The number of octets contained in the MSDU being indicated by the MAC sublayer entity. */
    uint8_t     msduLength  ALIGN8BIT;
    /** The set of octets forming the MSDU being indicated by the MAC sublayer entity. */
    octetstr_t  data[1]     ALIGN8BIT;
} mcps_data_ind_t;

/** \brief This is the MCPS-PURGE.request message structure.
*/
typedef struct mcps_purge_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MCPS_PURGE_REQUEST */
    /** The handle of the MSDU to be purged from the transaction queue. */
    uint8_t    msduHandle  ALIGN8BIT;
} mcps_purge_req_t;

/** \brief This is the MCPS-PURGE.confirm message structure.
*/
typedef struct mcps_purge_conf_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MCPS_PURGE_CONFIRM */
    /** The handle of the MSDU requested to be purge from the transaction queue. */
    uint8_t    msduHandle  ALIGN8BIT;
    /** The status of the request to be purged an MSDU from the transaction queue. */
    uint8_t     status      ALIGN8BIT;
} mcps_purge_conf_t;

/* === MLME-SAP messages ==================================================== */

/** \brief This is the MLME-ASSOCIATE.request message structure.
*/
typedef struct mlme_associate_req_tag
{
    uint8_t     size        ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode     ALIGN8BIT; /**< This identifies the message as \ref MLME_ASSOCIATE_REQUEST */
    /** The logical channel on which to attempt association. */
    uint8_t     LogicalChannel  ALIGN8BIT;
    /** The coordinator addressing mode for this primitive and subsequent MPDU.
    This value can take one of the following values: 2=16 bit short address.
    3=64 bit extended address. */
    uint8_t     CoordAddrMode   ALIGN8BIT;
    /** The identifier of the PAN with which to associate. */
    uint16_t    CoordPANId      ALIGN8BIT;
    /** The address of the coordinator with which to associate.*/
    uint64_t    CoordAddress    ALIGN8BIT;
    /** Specifies the operational capabilities of the associating device. */
    uint8_t     CapabilityInformation   ALIGN8BIT;
    /** TRUE if security is enabled for this transfer or FALSE otherwise. */
    uint8_t     SecurityEnable  ALIGN8BIT;
} mlme_associate_req_t;

/** \brief This is the MLME-ASSOCIATE.indication message structure.
*/
typedef struct mlme_associate_ind_tag
{
    /** The total length of this message. */
    uint8_t     size                    ALIGN8BIT;
    /** This identifies the message as \ref MLME_ASSOCIATE_INDICATION */
    enum msg_code cmdcode                 ALIGN8BIT;
    /** The address of the device requesting association. */
    uint64_t    DeviceAddress           ALIGN8BIT;
    /** The operational capabilities of the device requesting association. */
    uint8_t     CapabilityInformation   ALIGN8BIT;
    /** An indication of whether the received MAC command frame is using
    security. This value is set to TRUE if the security enable subfield was set
    to 1 or FALSE if the security enabled subfield was set to 0. */
    uint8_t     SecurityUse             ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0 x 08 if the sender of
    the data frame was not found in the ACL. */
    uint8_t     ACLEntry                ALIGN8BIT;
} mlme_associate_ind_t;

/** \brief This is the MLME-ASSOCIATE.response message structure. */
typedef struct mlme_associate_resp_tag
{
    /** The total length of this message. */
    uint8_t     size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_ASSOCIATE_RESPONSE */
    enum msg_code cmdcode             ALIGN8BIT;
    /** The address of the device requesting association. */
    uint64_t    DeviceAddress       ALIGN8BIT;
    /** The short device address allocated by the coordinator on successful
    association. This parameter is set to 0xffff if the association was
    unsuccessful. */
    uint16_t    AssocShortAddress   ALIGN8BIT;
    /** The status of the association attempt. */
    uint8_t     status              ALIGN8BIT;
    /** The status of the association attempt. */
    uint8_t     SecurityEnable      ALIGN8BIT;
} mlme_associate_resp_t;

/** \brief This is the MLME-ASSOCIATE.confirm message structure. */
typedef struct mlme_associate_conf_tag
{
    /** The total length of this message. */
    uint8_t     size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_ASSOCIATE_CONFIRM */
    enum msg_code cmdcode             ALIGN8BIT;
    /** The short device address allocated by the coordinator on successful
    association. This parameter will be equal to 0 x ffff if the association
    attempt was unsuccessful. */
    uint16_t    AssocShortAddress   ALIGN8BIT;
    /** The status of the association attempt. */
    uint8_t     status              ALIGN8BIT;
} mlme_associate_conf_t;

/** \brief This is the MLME-DISASSOCIATE.request message structure. */
typedef struct mlme_disassociate_req_tag
{
    /** The total length of this message. */
    uint8_t     size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_DISASSOCIATE_REQUEST */
    enum msg_code cmdcode             ALIGN8BIT;
    /** The address of the device to which to send the disassociation
    notification command. */
    uint64_t    DeviceAddress       ALIGN8BIT;
    /** The reason for the disassociation (see 7.3.1.3.2). */
    uint8_t     DisassociateReason  ALIGN8BIT;
    /** TRUE if security is enabled for this transfer or FALSE otherwise. */
    uint8_t     SecurityEnable      ALIGN8BIT;
} mlme_disassociate_req_t;

/** \brief This is the MLME-DISASSOCIATE.indication message structure. */
typedef struct mlme_disassociate_ind_tag
{
    /** The total length of this message. */
    uint8_t     size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_DISASSOCIATE_INDICATION */
    enum msg_code cmdcode             ALIGN8BIT;
    /** The address of the device requesting disassociation. */
    uint64_t    DeviceAddress       ALIGN8BIT;
    /** The reason for the disassociation (see 7.3.1.3.2). */
    uint8_t     DisassociateReason  ALIGN8BIT;
    /** An indication of whether the received MAC command frame is using
    security. This value is set to TRUE if the security enable subfield was set
    to 1 or FALSE if the security enabled subfield was set to 0. */
    uint8_t     SecurityUse         ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0x08 if the sender of the
    data frame was not found in the ACL. */
    uint8_t     ACLEntry            ALIGN8BIT;
} mlme_disassociate_ind_t;

/** \brief This is the MLME-DISASSOCIATE.confirm message structure. */
typedef struct mlme_disassociate_conf_tag
{
    /** The total length of this message. */
    uint8_t     size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_DISASSOCIATE_CONFIRM */
    enum msg_code cmdcode             ALIGN8BIT;
    /** The status of the disassociation attempt. */
    uint8_t     status              ALIGN8BIT;
} mlme_disassociate_conf_t;

/** \brief This is the MLME-BEACON-NOTIFY.indication message structure. */
typedef struct mlme_beacon_notify_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_BEACON_NOTIFY_INDICATION */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The beacon sequence number. */
    uint8_t         BSN                 ALIGN8BIT;
    /** The PANDescriptor for the received beacon. */
    wpan_pandescriptor_t PANDescriptor  ALIGN8BIT;
    /** The beacon pending address specification. */
    uint8_t         PendAddrSpec        ALIGN8BIT;
    /** AddrList - The list of addresses of the devices for which the beacon
    source has data. sduLength - The number of octets contained in the beacon
    payload of the beacon frame received by the MAC sublayer. sdu - The set of
    octets comprising the beacon payload to be transferred from the MAC sublayer
    entity to the next higher layer. */
    octetstr_t  data[1]                 ALIGN8BIT;
} mlme_beacon_notify_ind_t;

/** \brief This is the MLME-GTS.request message structure. */
typedef struct mlme_gts_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref  MLME_GTS_REQUEST */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The characteristics of the GTS request. */
    uint8_t         GTSCharacteristics  ALIGN8BIT;
    /** TRUE if security is enabled for this transfer or FALSE otherwise. */
    uint8_t         SecurityEnable      ALIGN8BIT;
} mlme_gts_req_t;

/** \brief This is the MLME-GTS.confirm message structure. */
typedef struct mlme_gts_conf_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref  MLME_GTS_CONFIRM */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The characteristics of the GTS request. */
    uint8_t         GTSCharacteristics  ALIGN8BIT;
    /** The status of the GTS request. */
    uint8_t         status              ALIGN8BIT;
} mlme_gts_conf_t;

/** \brief This is the MLME-GTS.indication message structure. */
typedef struct mlme_gts_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref  MLME_GTS_INDICATION */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The short address of the device that has been allocated or deallocated a
    GTS. */
    uint16_t        DevAddress          ALIGN8BIT;
    /** The characteristics of the GTS. */
    uint8_t         GTSCharacteristics  ALIGN8BIT;
    /** An indication of whether the received MAC command frame is using
    security. This value is set to TRUE if the security enable subfield was set
    to 1 or FALSE if the security enabled subfield was set to 0. */
    uint8_t         SecurityUse         ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0x08 if the sender of the
    data frame was not found in the ACL. */
    uint8_t         ACLEntry            ALIGN8BIT;
} mlme_gts_ind_t;

/** \brief This is the MLME-ORPHAN.indication message structure. */
typedef struct mlme_orphan_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref  MLME_ORPHAN_INDICATION */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The address of the orphaned device. */
    uint64_t        OrphanAddress       ALIGN8BIT;
    /** An indication of whether the received MAC command frame is using
    security. This value is set to TRUE if the security enable subfield was set
    to 1 or FALSE if the security enabled subfield was set to 0. */
    uint8_t         SecurityUse         ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0x08 if the sender of the
    data frame was not found in the ACL. */
    uint8_t         ACLEntry            ALIGN8BIT;
} mlme_orphan_ind_t;

/** \brief This is the MLME-ORPHAN.response message structure. */
typedef struct mlme_orphan_resp_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref  MLME_ORPHAN_RESPONSE */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The address of the orphaned device. */
    uint64_t        OrphanAddress       ALIGN8BIT;
    /** The short address allocated to the orphaned device if it is associated
    with this coordinator. The special short address 0 x fffe indicates that no
    short address was allocated, and the device will use its 64 bit extended
    address in all communications. If the device was not associated with this
    coordinator, this field will contain the value 0 x ffff and be ignored on
    receipt. */
    uint16_t        ShortAddress        ALIGN8BIT;
    /** TRUE if the orphaned device is associated with this coordinator or
    FALSE otherwise. */
    uint8_t         AssociatedMember    ALIGN8BIT;
    /** TRUE if security is enabled for this transfer or FALSE otherwise. */
    uint8_t         SecurityEnable      ALIGN8BIT;
} mlme_orphan_resp_t;

/** \brief This is the MLME-RESET.request message structure.
*/
typedef struct mlme_reset_req_tag
{
    uint8_t     size            ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode         ALIGN8BIT; /**< This identifies the message as \ref MLME_RESET_REQUEST */
    /** If TRUE, the MAC sublayer is reset and all MAC PIB attributes are set to
    their default values. If FALSE, the MAC sublayer is reset but all MAC PIB
    attributes retain their values prior to the generation of the
    MLME-RESET.request primitive. */
    uint8_t     SetDefaultPIB   ALIGN8BIT;
} mlme_reset_req_t;

/** \brief This is the MLME-RESET.confirm message structure.
*/
typedef struct mlme_reset_conf_tag
{
    uint8_t     size            ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode         ALIGN8BIT; /**< This identifies the message as \ref MLME_RESET_CONFIRM */
    /** The result of the reset operation. */
    uint8_t     status          ALIGN8BIT;
} mlme_reset_conf_t;

/** \brief This is the MLME-GET.request message structure.
*/
typedef struct mlme_get_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref MLME_GET_REQUEST */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the MAC PIB attribute to get. */
} mlme_get_req_t;

/** \brief This is the MLME-GET.confirm message structure.
*/
typedef struct mlme_get_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref MLME_GET_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request for PHY PIB attribute information.*/
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the MAC PIB attribute to get. */
    octetstr_t  data[1]      ALIGN8BIT; /**< The value of the indicated MAC PIB attribute that was read. */
} mlme_get_conf_t;

/** \brief This is the MLME-SET.request message structure.
*/
typedef struct mlme_set_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref MLME_SET_REQUEST */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the MAC PIB attribute to set. */
    octetstr_t  data[1]      ALIGN8BIT; /**< The value to write to the indicated MAC PIB attribute. */
} mlme_set_req_t;

/** \brief This is the MLME-SET.confirm message structure.
*/
typedef struct mlme_set_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode      ALIGN8BIT; /**< This identifies the message as \ref MLME_SET_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request to write the MAC PIB attribute. */
    uint8_t     PIBAttribute ALIGN8BIT; /**< The identifier of the MAC PIB attribute that was written. */
} mlme_set_conf_t;

/** \brief This is the MLME-RX-ENABLE.request message structure. */
typedef struct mlme_rx_enable_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_RX_ENABLE_REQUEST  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** TRUE if the receiver enable can be deferred until during the next
    superframe if the requested time has already passed. FALSE if the receiver
    enable is only to be attempted in the current superframe. This parameter is
    ignored for nonbeacon-enabled PANs. */
    uint8_t         DeferPermit         ALIGN8BIT;
    /** The number of symbols from the start of the superframe before the
    receiver is to be enabled. The precision of this value is a minimum of 20
    bits, with the lowest 4 bits being the least significant. This parameter is
    ignored for nonbeacon-enabled PANs. */
    uint32_t        RxOnTime            ALIGN8BIT;
    /** The number of symbols for which the receiver is to be enabled. */
    uint32_t        RxOnDuration        ALIGN8BIT;
} mlme_rx_enable_req_t;

/** \brief This is the MLME-RX-ENABLE.confirm message structure. */
typedef struct mlme_rx_enable_conf_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_RX_ENABLE_CONFIRM  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The result of the receiver enable request. */
    uint8_t     status          ALIGN8BIT;
} mlme_rx_enable_conf_t;

/** \brief This is the MLME-SCAN.request message structure. */
typedef struct mlme_scan_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_SCAN_REQUEST  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** Indicates the type of scan performed: 0 x 00 = ED scan (FFD only).
    0 x 01 = active scan (FFD only). 0 x 02 = passive scan. 0 x 03 = orphan
    scan. */
    uint8_t         ScanType            ALIGN8BIT;
    /** The 5 MSBs (b27, ... , b31) are reserved. The 27 LSBs (b0, b1, ... b26)
    indicate which channels are to be scanned (1 = scan, 0 = do not scan) for
    each of the 27 valid channels (see 6.1.2). */
    uint32_t        ScanChannels        ALIGN8BIT;
    /** A value used to calculate the length of time to spend scanning each
    channel for ED, active, and passive scans. This parameter is ignored for
    orphan scans. The time spent scanning each channel is
    [aBaseSuperframeDuration * (2n + 1)] symbols, where n is the value of the
    ScanDuration parameter. */
    uint8_t         ScanDuration        ALIGN8BIT;
} mlme_scan_req_t;

/** \brief This is the MLME-SCAN.confirm  message structure. */
typedef struct mlme_scan_conf_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_SCAN_CONFIRM  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The status of the scan request. */
    uint8_t         status              ALIGN8BIT;
    /** ScanType Integer 0 x 00 0 x 03 Indicates if the type of scan performed:
    0 x 00 = ED scan (FFD only). 0 x 01 = active scan (FFD only). 0 x 02 =
    passive scan. 0 x 03 = orphan scan. */
    uint8_t         ScanType            ALIGN8BIT;
    /** Indicates which channels given in the request were not scanned (1 = not
    scanned, 0 = scanned or not requested). This parameter is only valid for
    passive or active scans. */
    uint32_t        UnscannedChannels   ALIGN8BIT;
    /** The number of elements returned in the appropriate result
    lists. This value is 0 for the result of an orphan scan. */
    uint8_t         ResultListSize      ALIGN8BIT;
    /** ResultListSize -  The number of elements returned in the appropriate
    result lists. This value is 0 for the result of an orphan scan.
    EnergyDetectList - The number of elements returned in the appropriate result
    lists. This value is 0 for the result of an orphan scan.
    PANDescriptorList - The list of PAN descriptors, one for each beacon found
    during an active or passive scan. This parameter is null for ED and orphan
    scans.*/
    octetstr_t      data[1]             ALIGN8BIT;
} mlme_scan_conf_t;

/** \brief This is the MLME-COMM-STATUS.indication message structure. */
typedef struct mlme_comm_status_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_COMM_STATUS_INDICATION  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The 16 bit PAN identifier of the device from which the frame was
    received or to which the frame was being sent. */
    uint16_t        PANId               ALIGN8BIT;
    /** The source addressing mode for this primitive. This value can take one
    of the following values: 0 = no address (addressing fields omitted).
    0 x 01 = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit extended
    address. */
    uint8_t         SrcAddrMode         ALIGN8BIT;
    /** The source addressing mode for this primitive. This value can take one
    of the following values: 0 = no address (addressing fields omitted). 0 x 01
    = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit extended address.
    */
    uint64_t        SrcAddr             ALIGN8BIT;
    /** The destination addressing mode for this primitive. This value can take
    one of the following values: 0 x 00 = no address (addressing fields
    omitted). 0 x 01 = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit
    extended address. */
    uint8_t         DstAddrMode         ALIGN8BIT;
    /** The individual device address of the device for which the frame was
    intended. */
    uint64_t        DstAddr             ALIGN8BIT;
    /** The communications status. */
    uint8_t         status              ALIGN8BIT;
} mlme_comm_status_ind_t;

/** \brief This is the MLME-START.request message structure. */
typedef struct mlme_start_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_START_REQUEST  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The PAN identifier to be used by the beacon. */
    uint16_t        PANId               ALIGN8BIT;
    /** The logical channel on which to start transmitting beacons. */
    uint8_t         LogicalChannel      ALIGN8BIT;
    /** How often the beacon is to be transmitted. The beacon order, BO, and the
    beacon interval, BI, are related as follows: for 0 d BO d 14, BI =
    BaseSuperframeDuration * 2BO symbols. If BO = 15, the coordinator will not
    transmit a beacon, and the SuperframeOrder parameter value is ignored. */
    uint8_t         BeaconOrder         ALIGN8BIT;
    /** The length of the active portion of the superframe, including the beacon
    frame. The superframe order, SO, and the superframe duration, SD, are
    related as follows: for 0 d SO d BO d 14, SD = aBaseSuperframeDuration * 2SO
    symbols. If SO = 15, the superframe will not be active after the beacon. */
    uint8_t         SuperframeOrder     ALIGN8BIT;
    /** If this value is TRUE, the device will become the PAN coordinator of a
    new PAN. If this value is FALSE, the device will begin transmitting beacons
    on the PAN with which it is associated. */
    uint8_t         PANCoordinator      ALIGN8BIT;
    /** If this value is TRUE, the receiver of the beaconing device is disabled
    mac- BattLifeExtPeriods full backoff periods after the interframe spacing
    (IFS) period of the beacon frame. If this value is FALSE, the receiver of
    the beaconing device remains enabled for the entire CAP. */
    uint8_t         BatteryLifeExtension    ALIGN8BIT;
    /** TRUE if a coordinator realignment command is to be transmitted prior to
    changing the superframe configuration or FALSE otherwise. */
    uint8_t         CoordRealignment    ALIGN8BIT;
    /** TRUE if security is enabled for beacon transmissions or FALSE
    otherwise. */
    uint8_t         SecurityEnable      ALIGN8BIT;
} mlme_start_req_t;

/** \brief This is the MLME-START.confirm message structure. */
typedef struct mlme_start_conf_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_START_CONFIRM  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The result of the attempt to start using an updated superframe
    configuration. */
    uint8_t         status              ALIGN8BIT;
}  mlme_start_conf_t;

/** \brief This is the MLME-SYNC.request message structure. */
typedef struct mlme_sync_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_SYNC_REQUEST  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The logical channel on which to attempt coordinator synchronization. */
    uint8_t         LogicalChannel      ALIGN8BIT;
    /** TRUE if the MLME is to synchronize with the next beacon and attempt to
    track all future beacons. FALSE if the MLME is to synchronize with only the
    next beacon. */
    uint8_t         TrackBeacon         ALIGN8BIT;
} mlme_sync_req_t;

/** \brief This is the MLME-SYNC-LOSS.indication message structure. */
typedef struct mlme_sync_loss_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_SYNC_LOSS_INDICATION  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The reason that synchronization was lost. */
    uint8_t         LossReason          ALIGN8BIT;
} mlme_sync_loss_ind_t;

/** \brief This is the MLME-POLL.request message structure. */
typedef struct mlme_poll_req_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_POLL_REQUEST  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The addressing mode of the coordinator to which the poll is intended.
    This parameter can take one of the following values: 2 = 16 bit short
    address, 3 = 64 bit extended address. */
    uint8_t         CoordAddrMode       ALIGN8BIT;
    /** The PAN identifier of the coordinator to which the poll is intended. */
    uint16_t        CoordPANId          ALIGN8BIT;
    /** The address of the coordinator to which the poll is intended. */
    uint64_t        CoordAddress        ALIGN8BIT;
    /** TRUE if security is enabled for this transfer or FALSE otherwise. */
    uint8_t         SecurityEnable      ALIGN8BIT;
} mlme_poll_req_t;

/** \brief This is the MLME-POLL.confirm message structure. */
typedef struct mlme_poll_conf_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref MLME_POLL_CONFIRM  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** The status of the data request. */
    uint8_t         status              ALIGN8BIT;
} mlme_poll_conf_t;

/* === NLDE-SAP messages ==================================================== */

/** \brief This is the NLDE-DATA.request structure. */
typedef struct nlde_data_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLDE_DATA_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Destination address. */
    uint16_t    DstAddr         ALIGN8BIT;
    /** Length of NSDU. */
    uint8_t     NsduLength      ALIGN8BIT;
    /** Handle associated with the NSDU. */
    uint8_t     NsduHandle      ALIGN8BIT;
    /** Distance in hops the frame is allowed to travel. */
    uint8_t     Radius          ALIGN8BIT;
    /** Control route discovery. */
    uint8_t     DiscoverRoute   ALIGN8BIT;
    /** Apply NWK security. */
    uint8_t     SecurityEnable  ALIGN8BIT;
    /** The NSDU itself. */
    octetstr_t  data[1]         ALIGN8BIT;
} nlde_data_req_t;

/** \brief This is the NLDE-DATA.confirm structure. */
typedef struct nlde_data_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLDE_DATA_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Handle associated with the NSDU. */
    uint8_t     NsduHandle      ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlde_data_conf_t;

/** \brief This is the NLDE-DATA.indication structure. */
typedef struct nlde_data_ind_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLDE_DATA_INDICATION  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Source address of NSDU. */
    uint16_t    SrcAddr         ALIGN8BIT;
    /** Length of NSDU. */
    uint8_t     NsduLength      ALIGN8BIT;
    /** Link quality indication. */
    uint8_t     LinkQuality     ALIGN8BIT;
    /** The NSDU itself. */
    octetstr_t  data[1]         ALIGN8BIT;
} nlde_data_ind_t;

/* === NLME-SAP messages ==================================================== */

/** \brief This is the NLME-NETWORK-DISCOVERY.request structure. */
typedef struct nlme_network_discovery_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_NETWORK_DISCOVERY_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Bitmask of channels to scan for networks. */
    uint32_t    ScanChannels    ALIGN8BIT;
    /** Duration to scan for networks. */
    uint8_t     ScanDuration    ALIGN8BIT;
} nlme_network_discovery_req_t;

/** \brief This is the NLME-NETWORK-DISCOVERY.confirm structure. */
typedef struct nlme_network_discovery_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_NETWORK_DISCOVERY_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Number of networks discovered by the  search. */
    uint8_t     NetworkCount    ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
    /** List of network descriptors obtained. */
    octetstr_t  data[1]         ALIGN8BIT;
} nlme_network_discovery_conf_t;

/** \brief This is the NLME-NETWORK-FORMATION.request structure. */
typedef struct nlme_network_formation_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_NETWORK_FORMATION_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Bitmask of channels to scan for networks. */
    uint32_t    ScanChannels    ALIGN8BIT;
    /** Duration to scan for networks. */
    uint8_t     ScanDuration    ALIGN8BIT;
    /** Beacon order of the network. */
    uint8_t     BeaconOrder     ALIGN8BIT;
    /** Superframe order of the network. */
    uint8_t     SuperframeOrder ALIGN8BIT;
    /** Optional PAN identifier. */
    uint16_t    PANId           ALIGN8BIT;
    /** Whether to support battery life extension. */
    uint8_t     BatteryLifeExtension    ALIGN8BIT;
} nlme_network_formation_req_t;

/** \brief This is the NLME-NETWORK-FORMATION.confirm structure. */
typedef struct nlme_network_formation_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_NETWORK_FORMATION_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_network_formation_conf_t;

/** \brief This is the NLME-PERMIT-JOINING.request structure. */
typedef struct nlme_permit_joining_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_PERMIT_JOINING_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Lenth of time in seconds during with associations will be allowed. */
    uint8_t     PermitDuration  ALIGN8BIT;
} nlme_permit_joining_req_t;

/** \brief This is the NLME-PERMIT-JOINING.confirm structure. */
typedef struct nlme_permit_joining_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_PERMIT_JOINING_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_permit_joining_conf_t;

/** \brief This is the NLME-START-ROUTER.request structure. */
typedef struct nlme_start_router_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_START_ROUTER_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Beacon order of the network. */
    uint8_t     BeaconOrder     ALIGN8BIT;
    /** Superframe order of the network. */
    uint8_t     SuperframeOrder ALIGN8BIT;
    /** Whether to support battery life extension. */
    uint8_t     BatteryLifeExtension    ALIGN8BIT;
} nlme_start_router_req_t;

/** \brief This is the NLME-START-ROUTER.confirm structure. */
typedef struct nlme_start_router_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_START_ROUTER_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_start_router_conf_t;

/** \brief This is the NLME-JOIN.request structure. */
typedef struct nlme_join_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_JOIN_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** PAN identifier. */
    uint16_t    PANId           ALIGN8BIT;
    /** Whether to join as Zigbee router. */
    uint8_t     JoinAsRouter    ALIGN8BIT;
    /** Join directly, or re-join. */
    uint8_t     RejoinNetwork   ALIGN8BIT;
    /** Bitmask of channels to scan for networks. */
    uint32_t    ScanChannels    ALIGN8BIT;
    /** Duration to scan for networks. */
    uint8_t     ScanDuration    ALIGN8BIT;
    /** Is device mains-powered? */
    uint8_t     PowerSource     ALIGN8BIT;
    /** Whether to enable the Rx permanently. */
    uint8_t     RxOnWhenIdle    ALIGN8BIT;
    /** Whether to enable MAC security. */
    uint8_t     MACSecurity     ALIGN8BIT;
} nlme_join_req_t;

/** \brief This is the NLME-JOIN.indication structure. */
typedef struct nlme_join_ind_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_JOIN_INDICATION  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Network address of entity added to network. */
    uint16_t    ShortAddress    ALIGN8BIT;
    /** IEEE 64-bit address of entity. */
    uint64_t    ExtendedAddress ALIGN8BIT;
    /** Operating capabilities of joined device. */
    uint8_t     CapabilityInformation   ALIGN8BIT;
    /** Whether MAC security was used to associate. */
    uint8_t     SecureJoin      ALIGN8BIT;
} nlme_join_ind_t;

/** \brief This is the NLME-JOIN.confirm structure. */
typedef struct nlme_join_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_JOIN_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** PAN identifier from request this is the confirmation for. */
    uint16_t    PANId           ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_join_conf_t;

/** \brief This is the NLME-DIRECT-JOIN.request structure. */
typedef struct nlme_direct_join_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_DIRECT_JOIN_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** IEEE 64-bit address of entity. */
    uint64_t    DeviceAddress   ALIGN8BIT;
    /** Operating capabilities of device to join. */
    uint8_t     CapabilityInformation   ALIGN8BIT;
} nlme_direct_join_req_t;

/** \brief This is the NLME-DIRECT-JOIN.confirm structure. */
typedef struct nlme_direct_join_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_DIRECT_JOIN_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** IEEE 64-bit address of entity. */
    uint64_t    DeviceAddress   ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_direct_join_conf_t;

/** \brief This is the NLME-LEAVE.request structure. */
typedef struct nlme_leave_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_LEAVE_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** IEEE 64-bit address of entity to be removed from network. */
    uint64_t    DeviceAddress   ALIGN8BIT;
    /** Whether to ask device to remove its children. */
    uint8_t     RemoveChildren  ALIGN8BIT;
    /** Whether to enable MAC security for disassociation. */
    uint8_t     MACSecurity     ALIGN8BIT;
} nlme_leave_req_t;

/** \brief This is the NLME-LEAVE.indication structure. */
typedef struct nlme_leave_ind_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_LEAVE_INDICATION  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** IEEE 64-bit address of entity. */
    uint64_t    DeviceAddress   ALIGN8BIT;
} nlme_leave_ind_t;

/** \brief This is the NLME-LEAVE.confirm structure. */
typedef struct nlme_leave_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_LEAVE_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** IEEE 64-bit address of entity. */
    uint64_t    DeviceAddress   ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_leave_conf_t;

/** \brief This is the NLME-RESET.request structure. */
typedef struct nlme_reset_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_RESET_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
} nlme_reset_req_t;

/** \brief This is the NLME-RESET.confirm structure. */
typedef struct nlme_reset_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_RESET_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_reset_conf_t;

/** \brief This is the NLME-SYNC.request structure. */
typedef struct nlme_sync_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_SYNC_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** Whether synchronization should be maintained for further
     * beacons. */
    uint8_t     Track           ALIGN8BIT;
} nlme_sync_req_t;

/** \brief This is the NLME-SYNC.confirm structure. */
typedef struct nlme_sync_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_SYNC_confirm  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
} nlme_sync_conf_t;

/** \brief This is the NLME-GET.request structure. */
typedef struct nlme_get_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_GET_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The NIB attribute to read. */
    uint8_t     NIBAttribute    ALIGN8BIT;
} nlme_get_req_t;

/** \brief This is the NLME-GET.confirm structure. */
typedef struct nlme_get_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_GET_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
    /** The attribute that has been read. */
    uint8_t     NIBAttribute    ALIGN8BIT;
    /** The length of the attribute returned. */
    uint16_t    NIBAttributeLength ALIGN8BIT;
    /** The value of the attribute. */
    octetstr_t  data[1]         ALIGN8BIT;
} nlme_get_conf_t;

/** \brief This is the NLME-SET.request structure. */
typedef struct nlme_set_req_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_SET_REQUEST  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The attribute that to set. */
    uint8_t     NIBAttribute    ALIGN8BIT;
    /** The length of the attribute. */
    uint16_t    NIBAttributeLength ALIGN8BIT;
    /** The value of the attribute. */
    octetstr_t  data[1]         ALIGN8BIT;
} nlme_set_req_t;

/** \brief This is the NLME-SET.confirm structure. */
typedef struct nlme_set_conf_tag
{
    /** The total length of this message. */
    uint8_t     size            ALIGN8BIT;
    /** This identifies the message as \ref NLME_SET_CONFIRM  */
    uint8_t     cmdcode         ALIGN8BIT;
    /** The status of the request. */
    uint8_t     status          ALIGN8BIT;
    /** The attribute that has been set. */
    uint8_t     NIBAttribute    ALIGN8BIT;
} nlme_set_conf_t;

/** \brief This is the SNIFFER_FRAME.indication message structure. */
typedef struct sniffer_frame_ind_tag
{
    /** The total length of this message. */
    uint8_t         size                ALIGN8BIT;
    /** This identifies the message as \ref SNIFFER_FRAME_INDICATION  */
    uint8_t         cmdcode             ALIGN8BIT;
    /** Size The number of octets contained in the frame being indicated by the Script Sniffer. */
    uint8_t         frameType           ALIGN8BIT;
    /** The set of octets forming the frame being indicated by the Script Sniffer. */
    uint8_t         frameLength         ALIGN8BIT;
    /** The frame type. */
    octetstr_t      data[1]             ALIGN8BIT;

} sniffer_frame_ind_t;


/** \brief This is the SNIFFER_SET_CHANNEL.request message structure.
*/
typedef struct sniffer_set_channel_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_SET_CHANNEL_REQUEST */
    uint8_t     channel      ALIGN8BIT; /**< The channel of hte Script Sniffer to be set. */
} sniffer_set_channel_req_t;


/** \brief This is the SNIFFER_SET_CHANNEL.confirm message structure.
*/
typedef struct sniffer_set_channel_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_SET_CHANNEL_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request to set the sniffer channel. */
} sniffer_set_channel_conf_t;

/** \brief This is the SNIFFER_START.request message structure.
*/
typedef struct sniffer_start_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_START_REQUEST */
} sniffer_start_req_t;


/** \brief This is the SNIFFER_START.confirm message structure.
*/
typedef struct sniffer_start_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_START_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request to start the sniffer channel. */
} sniffer_start_conf_t;

/** \brief This is the SNIFFER_STOP.request message structure.
*/
typedef struct sniffer_stop_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_STOP_REQUEST */
} sniffer_stop_req_t;


/** \brief This is the SNIFFER_STOP.confirm message structure.
*/
typedef struct sniffer_stop_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_STOP_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request to start the sniffer channel. */
} sniffer_stop_conf_t;

/** \brief This is the SNIFFER_SET_FRMFILTER.request message structure.
*/
typedef struct sniffer_set_frmfilter_req_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_SET_FRMFILTER_REQUEST */
    uint8_t     frameType    ALIGN8BIT; /**< This specifies the frames to be accepted by the sniffer */
} sniffer_set_frmfilter_req_t;


/** \brief This is the SNIFFER_SET_FRMFILTER.confirm message structure.
*/
typedef struct sniffer_set_frmfilter_conf_tag
{
    uint8_t     size         ALIGN8BIT; /**< The total length of this message. */
    enum msg_code cmdcode    ALIGN8BIT; /**< This identifies the message as \ref SNIFFER_SET_FRMFILTER_CONFIRM */
    uint8_t     status       ALIGN8BIT; /**< The result of the request to start the sniffer channel. */
} sniffer_set_frmfilter_conf_t;
/* === Macros =============================================================== */

/* === Prototypes =========================================================== */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* MSG_TYPES_H */
/* EOF */
