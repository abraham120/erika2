/**
 * @file
 *
 * @brief WPAN MAC API
 *
 * $Id: wpan_mac.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef WPAN_MAC_H
#define WPAN_MAC_H

#ifndef ALIGN8BIT
# define ALIGN8BIT
#endif

/* === Includes ============================================================ */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals =========================================================== */

/* === Types =============================================================== */

#if !defined(DOXYGEN_NO_MAC)

/**
 * Frame address information structure, used for @ref mcps_data_req() and @ref mcps_data_ind()
 * workaround for parameter stack size limitation, see @ref sec64bit)
 *
 * @ingroup apiMacTypes
 */
typedef struct
#if !defined(DOXYGEN)
wpan_mcpsdata_addr_tag
#endif
{
    /**
    * The source addressing mode for this primitive (see @ref secAddrMode).
    */
    uint8_t SrcAddrMode;
    /**
    * The 16 bit PAN identifier of the entity from which the MSDU is being transferred.
    */
    uint16_t SrcPANId;
    /**
    * The source address. If SrcAddrMode is set to WPAN_ADDRMODE_SHORT, the value
    * is interpreted a 16 bit address.
    */
    uint64_t SrcAddr;
    /**
    * The destination addressing mode for this primitive (see @ref secAddrMode).
    */
    uint8_t DstAddrMode;

    /**
    * The 16 bit PAN identifier of the entity to which the MSDU is being transferred.
    */
    uint16_t DstPANId;

    /**
    * The destination device address. If DstAddrMode is set to WPAN_ADDRMODE_SHORT, the value
    * is interpreted a 16 bit address.
    */
    uint64_t DstAddr;

} wpan_mcpsdata_addr_t;

/**
 * Frame address information structure, used for mcps_data_req() and mcps_data_ind()
 * (workaround for parameter stack size limitation, see @ref sec64bit)
 *
 * @ingroup apiMacTypes
 */
typedef struct
#if !defined(DOXYGEN)
wpan_commstatus_addr_tag
#endif
{
    /**
    * The 16 bit PAN identifier of the entity from which the MSDU is being transferred.
    */
    uint16_t PANId;
    /**
    * The source addressing mode for this primitive. This value can take one
    * of the following values: 0 = no address (addressing fields omitted). 0 x 01
    * = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit extended address.
    */
    uint8_t SrcAddrMode;
    /**
    * The source addressing mode for this primitive. This value can take one
    * of the following values: 0 = no address (addressing fields omitted). 0 x 01
    * = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit extended address.
    */
    uint64_t SrcAddr;
    /**
    * The destination addressing mode for this primitive. This value can take
    * one of the following values: 0 x 00 = no address (addressing fields
    * omitted). 0 x 01 = reserved. 0 x 02 = 16 bit short address. 0 x 03 = 64 bit
    * extended address.
    */
    uint8_t DstAddrMode;

    /**
    * The individual device address of the device for which the frame was
    * intended.
    */
    uint64_t DstAddr;

} wpan_commstatus_addr_t;


/**
 * This is the PANDescriptor type for long addresses.
 *
 * @ingroup apiMacTypes
 */
typedef struct
#if !defined(DOXYGEN)
wpan_pandescriptor_tag
#endif
{
    /** The coordinator addressing mode corresponding to the received beacon
    frame. (see @ref secAddrMode) */
    uint8_t     CoordAddrMode           ALIGN8BIT;
    /** The PAN identifier of the coordinator as specified in the received
        beacon frame. */
    uint16_t    CoordPANId              ALIGN8BIT;
    /** The address of the coordinator as specified in the received beacon frame. If
        CoordAddrMode is set to WPAN_ADDRMODE_SHORT, the value is interpreted a
        16 bit address. */
    uint64_t    CoordAddress            ALIGN8BIT;
    /** The current logical channel occupied by the network
       (see @ref secLogicalChannel).*/
    uint8_t     LogicalChannel          ALIGN8BIT;
    /** The superframe specification as specified in the received beacon frame
       (see @ref secSuperFrameSpec).*/
    uint16_t    SuperframeSpec          ALIGN8BIT;
    /** TRUE if the beacon is from a PAN coordinator that is accepting GTS
    requests (see @ref subsecGTS). */
    uint8_t     GTSPermit               ALIGN8BIT;
    /** The LQ at which the network beacon was received. Lower values represent
    lower LQ (see 6.7.8 in 802.15.4-2003). */
    uint8_t     LinkQuality             ALIGN8BIT;
    /** The time at which the beacon frame was received, in symbols (see @ref secSymbolTime).
        This value is equal to the timestamp taken when the beacon frame was
        received, as described in 7.5.4.1. The precision of this value is a
        minimum of 20 bits, with the lowest 4 bits being the least significant. */
    uint32_t    TimeStamp               ALIGN8BIT;
    /** An indication of whether the received beacon frame is using security.
        This value is set to TRUE if the security enable subfield was set to 1 or
       FALSE if the security enabled subfield was set to 0 @noteSec. */
    uint8_t     SecurityUse             ALIGN8BIT;
    /** The macSecurityMode parameter value from the ACL entry associated with
    the sender of the data frame. This value is set to 0 x 08 if the sender of
    the data frame was not found in the ACL @noteSec. */
    uint8_t     ACLEntry                ALIGN8BIT;
    /** TRUE if there was an error in the security processing of the frame or
    FALSE otherwise @noteSec. */
    uint8_t     SecurityFailure         ALIGN8BIT;
} wpan_pandescriptor_t;


#endif /* if !defined(DOXYGEN_NO_MAC) */


/* === Macros ============================================================== */

/* these Macros are just for the API */

/** Value for the address mode, where no address is given (see @ref secAddrMode).
 * @ingroup apiMacConst
 */
#define WPAN_ADDRMODE_NONE  (0x00)
/** Value for the address mode, where a 16 bit short address is given (see @ref secAddrMode).
 * @ingroup apiMacConst
 */
#define WPAN_ADDRMODE_SHORT (0x02)
/** Value for the address mode, where a 64 bit long address is given (see @ref secAddrMode).
 * @ingroup apiMacConst
 */
#define WPAN_ADDRMODE_LONG  (0x03)
/** Value for TxOptions parameter im mcps_data_request() (see @ref secTxOpt).
 * @ingroup apiMacConst
 */
#define WPAN_TXOPT_OFF       (0x00)
/** Value for TxOptions parameter im mcps_data_request() (see @ref secTxOpt).
 * @ingroup apiMacConst
 */
#define WPAN_TXOPT_ACK       (0x01)
/** Value for TxOptions parameter im mcps_data_request() (see @ref secTxOpt).
 * @ingroup apiMacConst
 */
#define WPAN_TXOPT_INIDIRECT (0x04)

/** Flag value for capability information field (see @ref secParmCap)
 * @ingroup apiMacConst
 */
#define WPAN_CAP_ALTPANCOORD   (0x01)
/** Flag value for capability information field (see @ref secParmCap)
 * @ingroup apiMacConst
 */
#define WPAN_CAP_FFD           (0x02)
/** Flag value for capability information field (see @ref secParmCap)
 * @ingroup apiMacConst
 */
#define WPAN_CAP_PWRSOURCE     (0x04)
/** Flag value for capability information field (see @ref secParmCap)
 * @ingroup apiMacConst
 */
#define WPAN_CAP_RXONWHENIDLE  (0x08)
/** Flag value for capability information field (see @ref secParmCap)
 * @ingroup apiMacConst
 */
#define WPAN_CAP_ALLOCADDRESS  (0x80)



/* === Prototypes ========================================================== */
#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------------------------------------*/

/**
 * @brief The stack initialization function.
 * This function initializes all resources, which are used from the library.
 * It has to be called before any other function of the library is called.
 *
 * @ingroup apiGrp
 */
void wpan_init(void);

/**
 * @brief The stack task function called by the application.
 * This function should be called as frequently as possible by the application
 * in order to provide a permanent execution of the protocol stack.
 *
 * @return Boolean true if an event was processed otherwise false.
 * @ingroup apiGrp
 */
bool wpan_task(void);

/**
 * @brief Start a user defined timer.
 *
 * @param tid
 *        A number which identifies the timer @rangeUint8 .
 * @param duration
 *        The duration in symbol periods when the timer expires (see @ref secSymbolTime).
 *
 * @ingroup apiGrp
 */
bool wpan_start_timer(const uint8_t tid, const uint32_t duration);

/**
 * @brief Stop a previously started user defined timer.
 *
 * @param tid
 *        A number which identifies the timer @rangeUint8
 * @ingroup apiGrp
 */
bool wpan_stop_timer(const uint8_t tid);

/**
 * @brief Callback function, which is called for each user defined timer that expires.
 * This function has to be implemented by the application in order to process a timer expiration
 * event.
 *
 * @param tid
 *          A number which identifies the timer @rangeUint8
 * @ingroup apiGrp */
void usr_timer_trigger(uint8_t tid);

/*--------------------------------------------------------------------*/

/*
 * These functions have to be called from the application
 * in order to initiate an action in the communication
 * stack at the MAC level
 */
/**
  * @ingroup apiMacReq
  * @{
  */

/**
 * Forms an MCPS DATA REQUEST message and puts it in the message queue.
 *
 * @param addrInfo      Pointer to a address information structure of the type
 *                      @ref wpan_mcpsdata_addr_t (see also @ref sec64bit).
 * @param msduHandle    The handle of the MSDU in the transaction queue @rangeUint8 .
 * @param TxOptions     Bitfield of the transmission options for the MSDU (@ref secTxOpt)
 * @param msdu          Pointer to the data to transmit.
 * @param msduLength    Length of the data to transmit.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mcps_data_request(const wpan_mcpsdata_addr_t *addrInfo,
    const uint8_t msduHandle, const uint8_t TxOptions, const uint8_t *msdu,
    const uint8_t msduLength);

/**
 * Forms an MCPS PURGE REQUEST message and puts it in the message queue.
 * @param msduHandle The handle of the MSDU to be purged from the transaction queue @rangeUint8.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mcps_purge_request(const uint8_t msduHandle);



/**
 * Forms an MLME ASSOCIATE REQUEST message and puts it in the message queue.
 * @param LogicalChannel    Channel to send the Associate Request message on (see @ref secLogicalChannel).
 * @param CoordAddrMode     Address mode of the coordinator (values: @ref WPAN_ADDRMODE_SHORT, @ref WPAN_ADDRMODE_LONG).
 * @param CoordPANId        PAN ID of the coordinator.
 * @param CoordAddress      Address of the coordinator.
 * @param CapabilityInformation Bitfield that describes the nodes capabilities.
 *                              (see @ref secParmCap)
 * @param SecurityEnable        Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_associate_request(const uint8_t LogicalChannel,
    const uint8_t CoordAddrMode, const uint16_t CoordPANId,
    const uint64_t CoordAddress, const uint8_t CapabilityInformation,
    const bool SecurityEnable);

/**
 * Forms an MLME ASSOCIATE RESPONSE message and puts it in the message queue.
 * @param DeviceAddress The address of the device requesting association.
 * @param assoc_ShortAddress The short device address allocated by the coordinator on successful association.
 * @param status The status of the association attempt (see @ref secAssocStat).
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_associate_response(const uint64_t DeviceAddress,
    const uint16_t assoc_ShortAddress, const uint8_t status,
    const bool SecurityEnable);

/**
 * Forms an MLME DISASSOCIATE REQUEST message and puts it in the message queue.
 * @param DeviceAddress The address of the device to send the disassociation notification.
 * @param DisassociateReason The reason for the disassociation (see @ref secDisass).
 *
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_disassociate_request(const uint64_t DeviceAddress,
    const uint8_t DisassociateReason, const bool SecurityEnable);

/**
 * Forms an MLME GET REQUEST message and puts it in the message queue.
 * @param PIBAttribute The PIB attribute to get (see @ref apiMacMib).
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_get_request(const uint8_t PIBAttribute);

/**
 * Forms an MLME GTS REQUEST message and puts it in the message queue.
 *
 * @note Because there is currently no GTS implementation (see @ref subsecGTS), this
 * request is not processed in the MAC. This includes the confirm message.
 *
 * @param GTSCharacteristics The characteristics of the GTS request.
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_gts_request(const uint8_t GTSCharacteristics,
    const bool SecurityEnable);

/**
 * Forms an MLME ORPHAN RESPONSE message and puts it in the message queue.
 * @param OrphanAddress The address of the orphaned device.
 * @param ShortAddress The short address allocated to the orphaned device if it is associated with this coordinator.
 * @param AssociatedMember Boolean true if the orphaned device is associated with this coordinator.
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_orphan_response(const uint64_t OrphanAddress,
    const uint16_t ShortAddress, const bool AssociatedMember,
    const bool SecurityEnable);

/**
 * Forms an MLME POLL REQUEST message and puts it in the message queue.
 * @param CoordAddrMode The addressing mode of the coordinator to which the poll is intended <br>
 *        (values: @ref WPAN_ADDRMODE_SHORT, @ref WPAN_ADDRMODE_LONG, see @ref secAddrMode).
 * @param CoordPANId The PAN identifier of the coordinator to which the poll is intended.
 * @param CoordAddress The address of the coordinator to which the poll is intended.
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_poll_request(const uint8_t CoordAddrMode,
    const uint16_t CoordPANId, const uint64_t CoordAddress,
    const bool SecurityEnable);

/**
 * Forms an MLME RESET REQUEST message and puts it in the message queue.
 * @param SetDefaultPib  If this parameter is true, all PIB values are reset to their default values
 *                        (see @ref apiMacMib).
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_reset_request(const bool SetDefaultPib);

/**
 * Forms an MLME SET REQUEST message and puts it in the message queue.
 * @param PIBAttribute The PIB attribute to be set (see @ref apiMacMib).
 * @param PIBAttributeValue A void pointer which points to the value to be stored in the PIB attribute.
 * @param PIBAttributeValueSize The size of PIBAttributeValue.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_set_request(const uint8_t PIBAttribute,
    const void *PIBAttributeValue, const size_t PIBAttributeValueSize);

/**
 * Forms an MLME RX ENABLE REQUEST message and puts it in the message queue.
 * @param DeferPermit Boolean true if the receiver enable can be deferred until during the next superframe if the requested time has already passed.
 * @param RxOnTime The number of symbols from the start of the superframe before the receiver is to be enabled (see @ref secSymbolTime).
 * @param RxOnDuration The number of symbols for which the receiver is to be enabled (see @ref secSymbolTime).
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_rx_enable_request(const bool DeferPermit,
    const uint32_t RxOnTime, const uint32_t RxOnDuration);

/**
 * Forms an MLME SCAN REQUEST message and puts it in the message queue.
 * @param ScanType The type of scan to perform (see @ref secScanTypes).
 * @param ScanChannels The channels to scan (see @ref secChannelMask).
 * @param ScanDuration The duration of each scan (see @ref secSymbolTime).
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_scan_request(const uint8_t ScanType,
    const uint32_t ScanChannels, const uint8_t ScanDuration);

/**
 * Forms an MLME START REQUEST message and puts it in the message queue.
 * @param PANId The PAN identifier to be used by the beacon.
 * @param LogicalChannel Channel to transmit on (see @ref secLogicalChannel).
 * @param BeaconOrder How often the beacon is to be transmitted (see @ref secBeaconOrder).
 * @param SuperframeOrder The length of the active portion of the superframe, including the beacon frame (see @ref secBeaconOrder).
 * @param PANCoordinator Boolean to become the PAN coordinator or not.
 * @param BatteryLifeExtension Boolean true will disable the receiver of the beaconing device for a period of time after the interframe spacing period of the beacon frame..
 * @param CoordRealignment Boolean to transmit a coordinator realignment command prior to changing the superframe configuration.
 * @param SecurityEnable Boolean to enable or disable security @noteSec.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_start_request(const uint16_t PANId,
    const uint8_t LogicalChannel, const uint8_t BeaconOrder,
    const uint8_t SuperframeOrder, const bool PANCoordinator,
    const bool BatteryLifeExtension, const bool CoordRealignment,
    const bool SecurityEnable);

/**
 * Forms an MLME SYNC REQUEST message and puts it in the message queue.
 * @param LogicalChannel Channel on which to attempt coordinator synchronization (see @ref secLogicalChannel).
 * @param TrackBeacon Boolean to synchronize with the next beacon and attempt to track all future beacons.
 * @return true = success, false = failed to add to message queue because of overflow.
 */
bool wpan_mlme_sync_request(const uint8_t LogicalChannel,
    const bool TrackBeacon);

/*@}*//* apiMacReq */

/**
  * @addtogroup apiMacCb
  * @{
  */

/**
 * @brief Callback function for a mcps_data_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mcps_data_conf_t coming from the stack.
 *
 * @param msduHandle
 *     The handle of the MSDU to be purged from the transaction queue @rangeUint8.
 * @param status
 *     The result code for the corresponding request (see 7.1.1.2.1 in 802.15.4).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mcps_data_conf(uint8_t msduHandle, uint8_t status);

/**
 * @brief Callback function for a mcps_data_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mcps_data_ind_t coming from the stack.
 *
 * @param pAddrInfo
 *     Pointer to a address information structure of the type @ref wpan_mcpsdata_addr_t (see @ref sec64bit).
 * @param mpduLinkQuality
 *     LQ value measured during reception of the MPDU. Lower values represent lower LQ (see 6.7.8 in 802.15.4-2003).
 * @param SecurityUse
 *     An indication of whether the received data frame is using security. This
 *     value is set to TRUE if the security enable subfield was set to 1 or FALSE
 *     if the security enabled subfield was set to 0 @noteSec.
 * @param ACLEntry
 *     The macSecurityMode parameter value from the ACL entry associated with
 *     the sender of the data frame. This value is set to 0 x 08 if the sender of
 *     the data frame was not found in the ACL @noteSec.
 * @param msduLength
 *     Size The number of octets contained in the MSDU being indicated by the MAC sublayer entity.
 *     The maximum length of a MSDU is defined by the constant aMaxPHYPacketSize.
 * @param msdu
 *     Pointer to array of uint8_t data, the length of the array is given by the parameter data_length.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mcps_data_ind(wpan_mcpsdata_addr_t *addrInfo, uint8_t mpduLinkQuality,
        uint8_t SecurityUse, uint8_t ACLEntry, uint8_t msduLength, uint8_t *msdu);

/**
 * @brief Callback function for a mcps_purge_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mcps_purge_conf_t coming from the stack.
 *
 * @param msduHandle
 *     The handle of the MSDU to be purged from the transaction queue @rangeUint8.
 * @param status
 *     The result code for the corresponding request.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mcps_purge_conf(uint8_t msduHandle, uint8_t status);

/**
 * @brief Callback function for a mlme_associate_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_associate_conf_t coming from the stack.
 *
 * @param AssocShortAddress
 *     The short device address allocated by the coordinator on successful
 *     association. This parameter is set to 0xffff if the association was
 *     unsuccessful.
 * @param status
 *     The result code for the corresponding request (see 7.1.1.5.1 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_associate_conf(uint16_t AssocShortAddress, uint8_t status);

/**
 * @brief Callback function for a mlme_associate_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_associate_ind_t coming from the stack.
 *
 * @param DeviceAddress
 *     IEEE 64-bit address of entity.
 * @param CapabilityInformation
 *     Operating capabilities of joined device (see @ref secParmCap).
 * @param SecurityUse
 *     An indication of whether the received data frame is using security. This
 *     value is set to TRUE if the security enable subfield was set to 1 or FALSE
 *     if the security enabled subfield was set to 0 @noteSec.
 * @param ACLEntry
 *     The macSecurityMode parameter value from the ACL entry associated with
 *     the sender of the data frame. This value is set to 0 x 08 if the sender of
 *     the data frame was not found in the ACL @noteSec.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_associate_ind(uint64_t DeviceAddress, uint8_t CapabilityInformation, uint8_t SecurityUse, uint8_t ACLEntry);

/**
 * @brief Callback function for a mlme_beacon_notify_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_beacon_notify_ind_t coming from the stack.
 *
 * @param BSN
 *     The beacon sequence number.
 * @param PANDescriptor
 *     Pointer of type @see pandescriptor_long_t to the PANDescriptor for the received beacon.
 * @param PendAddrSpec
 *     The beacon pending address specification (see @ref secPendAddrSpec).
 * @param data
 *     Pointer to array of uint8_t data, the length of the array is given by the parameter data_length.
 * @param data_length
 *     Number of bytes in the array, referenced by the parameter *data.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_beacon_notify_ind(uint8_t BSN, wpan_pandescriptor_t PANDescriptor, uint8_t PendAddrSpec, uint8_t *data, uint8_t data_length);

/**
 * @brief Callback function for a mlme_comm_status_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_comm_status_ind_t coming from the stack.
 *
 * @param pAddrInfo
 *      Pointer to address information structure of type @ref wpan_commstatus_addr_t (see also @ref sec64bit).
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.12.1.12 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_comm_status_ind(wpan_commstatus_addr_t *pAddrInfo, uint8_t status);

/**
 * @brief Callback function for a mlme_disassociate_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_disassociate_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.4.3.1 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_disassociate_conf(uint8_t status);

/**
 * @brief Callback function for a mlme_disassociate_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_disassociate_ind_t coming from the stack.
 *
 * @param DeviceAddress
 *     IEEE 64-bit address of entity.
 * @param DisassociateReason
 *     The reason for the disassociation (see @ref secDisass).
 * @param SecurityUse
 *     An indication of whether the received data frame is using security. This
 *     value is set to TRUE if the security enable subfield was set to 1 or FALSE
 *     if the security enabled subfield was set to 0 @noteSec.
 * @param ACLEntry
 *     The macSecurityMode parameter value from the ACL entry associated with
 *     the sender of the data frame. This value is set to 0 x 08 if the sender of
 *     the data frame was not found in the ACL @noteSec.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_disassociate_ind(uint64_t DeviceAddress, uint8_t DisassociateReason, uint8_t SecurityUse, uint8_t ACLEntry);

/**
 * @brief Callback function for a mlme_get_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_get_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request.
 * @param PIBAttribute
 *     The identifier of the PHY PIB attribute to get (see @ref apiMacMib).
 * @param PIBAttributeValue
 *     Pointer to array of uint8_t data, the length of the array is given by the parameter data_length.
 * @param PIBAttributeValueSize
 *     Number of bytes in the array, referenced by the parameter *PIBAttributeValueSize.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_get_conf(uint8_t status, uint8_t PIBAttribute, uint8_t *PIBAttributeValue, uint8_t PIBAttributeValueSize);

/**
 * @brief Callback function for a mlme_gts_conf message.
 *
 * @note Because there is currently no GTS implementation (see @ref subsecGTS), this
 * confirm is not emited from the MAC.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_gts_conf_t coming from the stack.
 * @param GTSCharacteristics
 *     The characteristics of the GTS request.
 * @param status
 *     The result code for the corresponding request.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_gts_conf(uint8_t GTSCharacteristics, uint8_t status);

/**
 * @brief Callback function for a mlme_gts_ind message.
 *
 * @note Because there is currently no GTS implementation (see @ref subsecGTS), this
 * indication is not emitted from the MAC.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_gts_ind_t coming from the stack.
 *
 * @param DevAddress
 *     The short address of the device that has been allocated or deallocated a
 *     GTS.
 * @param GTSCharacteristics
 *     The characteristics of the GTS request.
 * @param SecurityUse
 *     An indication of whether the received data frame is using security. This
 *     value is set to TRUE if the security enable subfield was set to 1 or FALSE
 *     if the security enabled subfield was set to 0.
 * @param ACLEntry
 *     The macSecurityMode parameter value from the ACL entry associated with
 *     the sender of the data frame. This value is set to 0 x 08 if the sender of
 *     the data frame was not found in the ACL @noteSec.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_gts_ind(uint16_t DevAddress, uint8_t GTSCharacteristics, uint8_t SecurityUse, uint8_t ACLEntry);

/**
 * @brief Callback function for a mlme_orphan_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_orphan_ind_t coming from the stack.
 *
 * @param OrphanAddress
 *     The address of the orphaned device.
 * @param SecurityUse
 *     An indication of whether the received data frame is using security. This
 *     value is set to TRUE if the security enable subfield was set to 1 or FALSE
 *     if the security enabled subfield was set to 0 @noteSec.
 * @param ACLEntry
 *     The macSecurityMode parameter value from the ACL entry associated with
 *     the sender of the data frame. This value is set to 0 x 08 if the sender of
 *     the data frame was not found in the ACL @noteSec.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_orphan_ind(uint64_t OrphanAddress, uint8_t SecurityUse, uint8_t ACLEntry);

/**
 * @brief Callback function for a mlme_poll_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_poll_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.16.2.16 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_poll_conf(uint8_t status);

/**
 * @brief Callback function for a mlme_reset_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_reset_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.9.2.1 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_reset_conf(uint8_t status);

/**
 * @brief Callback function for a mlme_rx_enable_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_rx_enable_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.10.2.10 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_rx_enable_conf(uint8_t status);

/**
 * @brief Callback function for a mlme_scan_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_scan_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request.
 * @param ScanType
 *     Indicates the type of scan performed (see @ref secScanTypes).
 * @param UnscannedChannels
 *     Indicates which channels given in the request were not scanned (1 = not
 *     scanned, 0 = scanned or not requested). This parameter is only valid for
 *     passive or active scans (see @ref secChannelMask).
 * @param ResultListSize
 *     The number of elements returned in the appropriate result
 *     lists. This value is 0 for the result of an orphan scan.
 * @param data
 *     Pointer to array of uint8_t data, the length of the array is given by the parameter data_length.
 * @param data_length
 *     Number of bytes in the array, referenced by the parameter *data.
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_scan_conf(uint8_t status, uint8_t ScanType, uint32_t UnscannedChannels, uint8_t ResultListSize, uint8_t *data, uint8_t data_length);

/**
 * @brief Callback function for a mlme_set_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_set_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.14.2.1 in 802.15.4-2003).
 * @param PIBAttribute
 *     The identifier of the PHY PIB attribute to get (see @ref apiMacMib).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_set_conf(uint8_t status, uint8_t PIBAttribute);

/**
 * @brief Callback function for a mlme_start_conf message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_start_conf_t coming from the stack.
 *
 * @param status
 *     The result code for the corresponding request (see 7.1.14.2.14 in 802.15.4-2003).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_start_conf(uint8_t status);

/**
 * @brief Callback function for a mlme_sync_loss_ind message.
 *
 * This function has to be implemented by the application in order to
 * process a message of the type mlme_sync_loss_ind_t coming from the stack.
 *
 * @param LossReason
 *     The reason that synchronization was lost (values: @ref MAC_BEACON_LOSS, @ref MAC_REALIGNMENT, @ref MAC_PAN_ID_CONFLICT).
 *
 * @return void
 *
 * @ingroup apiMacCb
 */
void usr_mlme_sync_loss_ind(uint8_t LossReason);

/*@}*//* apiMacCb */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WPAN_MAC_H */
/* EOF */
