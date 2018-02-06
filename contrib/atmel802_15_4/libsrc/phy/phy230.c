/**
 * \file
 * \brief IEEE 802.15.4. PHY layer implementation for the AT86RF230
 *
 * This file contains the implementation of an interface between the MAC
 * sublayer and the physical radio channel.
 *
 * $Id: phy230.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

/* === Includes ============================================================ */
#ifndef DEF_H
#include "def.h"
#endif

#include <stdio.h>

#include "board.h"
#include "phy.h"
#include "mac.h"
#include "ee_confMac.h"

#if (RADIO_TYPE == AT86RF230 && APP_TYPE >= APP_L1) || defined(DOXYGEN)

/* === Defines ============================================================= */

/*
 * This is a tunable option.
 *
 * If AUTO_CRC_ON is set to a true value, the phyGenerateCRC PIB
 * attribute will be implemented using the AT86RF230's hardware CRC
 * generation.  If it is set to a false value, a software CRC will be
 * used instead.
 */
#define AUTO_CRC_ON 1

/* Time in symbols to wait for PLL from BUSY_TX to RX_ON */
#define PLL_BUSY_TX_RX_ON_TIMEOUT   (8)

/* Max. Number of tx recovery retries in case TX fails */
#define MAX_TX_RETRY                (10)

/* Internal return value for plme_set_request_internal(). */
#define PHY_WAIT_FOR_ED             (0x80)

/* RG_TRX_STATUS mask for CCA_DONE */
#define CCA_DONE_MASK               (0x80)

/* RG_TRX_STATUS mask for the CCA result */
#define CCA_STATUS_MASK             (0x40)

/* === Globals ============================================================= */

static uint8_t  phy230_state;
static uint8_t  phy230_deferred_state;
static uint8_t  pibCheckCRC;
static uint8_t  pibGenerateCRC;
static uint8_t  pibRSSI;
static uint8_t  phy230_new_channel;
static bool  phy230_ed_running;
static volatile bool phy230_fasttimer_expired;
 uint8_t phy_rx_buffer[aMaxPHYPacketSize + sizeof(pd_data_ind_t)];



/*
 * Translation table for the RF230 16 tx power levels into power
 * levels (dBm).
 */
FLASH_DECLARE(static int8_t tx_power_levels[RF230_NUM_TX_PWR_LEVELS]) =
{
    3, /* 3.2 */
    2, /* 2.8 */
    2, /* 2.3 */
    1, /* 1.8 */
    1, /* 1.3 */
    0, /* 0.7 */
    0, /* 0.0 */
    -1,
    -2,
    -3,
    -4,
    -5,
    -7,
    -9,
    -12,
    -17,
};


/* === Prototypes ========================================================== */

static inline uint8_t compute_lqi(uint8_t lqi);
static void fasttimer_handler(void);
static void wait_for_pll_lock(void);
static void wait_for_rx_on_from_busy_tx(void);
static void phy_t_ed(void);

/* === Implementation ====================================================== */

/*
 * Turn RF230 tx power level into dBm | tolerance for phyTransmitPower.
 */
static inline uint8_t tx_pwr_to_dbm(uint8_t lev)
{
    return (uint8_t)(PGM_READ_BYTE(&tx_power_levels[lev]) & PHY_TXPOWER_MASK) |
        RF230_TX_PWR_TOLERANCE;
}

/*
 * Compute the RF230 tx power level corresponding to the respective
 * phyTransmitPower value.
 */
static inline uint8_t dbm_to_tx_pwr_lev(int8_t dbm)
{
    uint8_t signbit;
    int8_t i, x;

    dbm &= PHY_TXPOWER_MASK;
    /* sign-extend the 6-bit value into int8_t */
    signbit = (PHY_TXPOWER_MASK + 1) >> 1;
    if ((uint8_t)dbm & signbit)
    {
        dbm |= (int8_t)(-1 & ~PHY_TXPOWER_MASK);
    }

    /* check upper/lower bounds */
    x = PGM_READ_BYTE(&tx_power_levels[0]);
    if (dbm > x)
    {
        return 0;
    }

    x = PGM_READ_BYTE(&tx_power_levels[RF230_NUM_TX_PWR_LEVELS - 1]);
    if (dbm < x)
    {
        return RF230_NUM_TX_PWR_LEVELS - 1;
    }

    /* now walk the table, and find best match */
    for (i = RF230_NUM_TX_PWR_LEVELS - 1; i >= 0; i--)
    {
        x = PGM_READ_BYTE(&tx_power_levels[i]);
        if (x >= dbm)
        {
            return (uint8_t)i;
        }
    }

    ASSERT("We should never get here." == 0);
    return 0;
}

/**
 * \brief This is the radio specific irq handler
 *
 * @param irqstatus
 */
void phy_irq_handler(uint8_t irqstatus, uint32_t tstamp)
{
    
    if (phy230_state == PHY_BUSY_TX)
    {
        if (irqstatus & TRX_IRQ_TRX_END)
        {
            phy_trx_end();
        }
        if (irqstatus & TRX_IRQ_RX_START)
        {
            phy_rx_start(tstamp);  // 1
        }
    }
    else
    {
        if (irqstatus & TRX_IRQ_RX_START)
        {
	     
	     phy_rx_start(tstamp);
	  
       }
        if (irqstatus & TRX_IRQ_TRX_END)
        {
             phy_trx_end();
        }
    }
}

/**
 * \brief This function does the initialization of the phy layer.
 *
 * This function initializes the physical layer process, variables and PIBs.
 */

void phy_init(void)
{
#if DEBUG > 0
    uint8_t part, version, id0, id1;
#endif

    phy230_fasttimer_expired = false;

    phy230_deferred_state = PHY_BUSY;

    bios_pinset(TRX_PIN_RESET, 0);
    bios_pinset(TRX_PIN_SLEEP, 0);

    delay_us(4);

    bios_pinset(TRX_PIN_RESET, 1);

    bios_bit_write(SR_CLKM_SHA_SEL, 0);

#if !RC_OSC_USED
    /*
     * When not using the on-chip RC oscillator, select the
     * appropriate CLKM from the AT86RF230 that matches our F_CPU
     * compilation setting.
     */
#   if F_CPU == 8000000UL
    bios_bit_write(SR_CLKM_CTRL, CLKM_8MHz);
#   elif F_CPU == 4000000UL
    bios_bit_write(SR_CLKM_CTRL, CLKM_4MHz);
#   elif F_CPU == 2000000UL
    bios_bit_write(SR_CLKM_CTRL, CLKM_2MHz);
#   elif F_CPU == 1000000UL
    /* 1 MHz is default clock from AT86RF230 */
#   else
#      error "Unsupported F_CPU for CLKM-based clocking"
#   endif
#endif

#if DEBUG > 0
    /* check for the RF230 */
    part    = bios_reg_read(RG_PART_NUM);
    version = bios_reg_read(RG_VERSION_NUM);
    id0     = bios_reg_read(RG_MAN_ID_0);
    id1     = bios_reg_read(RG_MAN_ID_1);
#endif

    PRINT("PART_NUM = %x, VERSION_NUM = %x, ID0 = %x, ID1 = %x",
          part, version, id0, id1);
    bios_bit_write(SR_TRX_CMD, CMD_TRX_OFF);

    /* set CLKM driver strength to 2mA */
    bios_bit_write(SR_PAD_IO_CLKM, 0);

    bios_reg_write(RG_IRQ_MASK, TRX_KNOWN_IRQS);

    board_irq_init();

    phy230_state = PHY_TRX_OFF;

    /* phy layer should only report frames with valid CRC */
    pibCheckCRC  = false;
    pibGenerateCRC = false;

    // Initialize random number generator with current time.
    srand(bios_gettime());

#if BOARD_TYPE == EMU230
    /*
     * The emulation only supports CCA mode 2 (in order to obtain a
     * clear channel).
     */
    bios_bit_write(SR_CCA_MODE, 2);
#endif /* BOARD_TYPE == EMU230 */

}


/*
 * Recovers from an unsuccessful attempt to transmit a correct frame.
 * In case the transeiver has not been able to transmit the current frame,
 * this routine switches the radio into RX_ON and gives the PLL time to
 * recover and lock again. Afterwards the transceiver is put back to TX_ON,
 * and the caller may initiate another transmission attempt.
 */
static void recover_failed_tx(void)
{
    uint8_t hw_rec_status;

    // switch to RX_ON for a moment
    phy230_state = PHY_RX_ON;
    bios_bit_write(SR_TRX_CMD, CMD_RX_ON);

    // give the PLL time to switch from BUSY_TX to RX_ON
    wait_for_rx_on_from_busy_tx();
    bios_bit_read(SR_TRX_STATUS, &hw_rec_status);

    if(hw_rec_status != RX_ON)
    {
        // we re in trouble now ...
        ASSERT("Setting Radio to RX_ON failed." == 0);
    }

    // switch back PLL_ON to continue TX
    bios_bit_write(SR_TRX_CMD, CMD_PLL_ON);
    phy230_state = PHY_TX_ON;

    do
    {
        bios_bit_read(SR_TRX_STATUS, &hw_rec_status);
    } while (hw_rec_status != PLL_ON);
}


/**
 * \brief Perform a PHY reset
 *
 * This performs all actions internal to the PHY that need to be taken
 * upon a MAC layer reset.
 */
void phy_reset_internal(void)
{
    /* Nothing needed for this hardware. */
}

/**
 * \brief The PD-DATA.request primitive requests the transfer of an MPDU (i.e., PSDU) from the MAC sublayer to the local PHY entity.
 *
 * The receipt of the PD-DATA.request primitive by the PHY entity will cause
 * the transmission of the supplied PSDU. Provided the transmitter is enabled
 * (TX_ON state), the PHY will first construct a PPDU, containing the supplied
 * PSDU, and then transmit the PPDU. When the PHY entity has completed the
 * transmission, it will issue the PD-DATA.confirm primitive with a status of
 * SUCCESS. If the PD-DATA.request primitive is received while the receiver is
 * enabled (RX_ON state) or if the transceiver is disabled (TRX_OFF state),
 * the PHY entity will issue the PD-DATA.confirm primitive with a status of
 * RX_ON or TRX_OFF, respectively.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */
void pd_data_request(uint8_t *m)
{
    pd_data_req_t *msg = (pd_data_req_t *)m;
    pd_data_conf_t cm;

    if (pd_data_request_internal(msg, &cm))
    {
        bios_pushback_event(&cm);
    }
}

/**
 * \brief Internal form of the PD-DATA.request primitive.
 *
 * \param(in) msg pointer to PD-DATA.request structure
 * \param(out) cm pointer to PD-DATA.confirm structure provided by caller
 * \return Boolean whether a PD-DATA.confirm should be queued
 */
bool pd_data_request_internal(pd_data_req_t *msg, pd_data_conf_t *cm)
{
    uint8_t hwstatus;
    cm->size    = sizeof(pd_data_conf_t) - sizeof(cm->size);
    cm->cmdcode = PD_DATA_CONFIRM;

    if ((msg->psduLength > aMaxPHYPacketSize) ||
        (phyGenerateCRC && (msg->psduLength < CRC_SIZE)))
    {
        cm->status = PHY_INVALID_PARAMETER;
        return true;
    }
    else
    {
#if !AUTO_CRC_ON
        if (pibGenerateCRC)
        {
            bios_gen_crc16(msg->data);
        }
#endif
        switch( phy230_state )
        {
            case PHY_BUSY_TX:
                cm->status = PHY_BUSY_TX;
                return true;

            case PHY_TX_ON:
                {
                    bool tx_done = false;

                    /* We try to initiate a TX.
                       TX fails if phy does not immediately change PHY state to TX_BUSY.
                       In this case we will perform a recovery sequence and retry TX.
                       We will give up after tx_retry attempts and report an error back. */
                    for (uint8_t tx_retry = 0; tx_retry < MAX_TX_RETRY; tx_retry++)
                    {
                        bios_frame_write(1, &(msg->data[1])); /* dummy write to clear the tx pointer */
                        bios_pinset(TRX_PIN_SLEEP, 1);
                        bios_pinset(TRX_PIN_SLEEP, 0);
                        bios_frame_write(msg->psduLength, &(msg->data[1]));

                        bios_bit_read(SR_TRX_STATUS, &hwstatus);
                        if(hwstatus != BUSY_TX)
                        {
                            // start of TX failed
                            // call subroutine to recover from this to retry transmission
                            recover_failed_tx();
                        }
                        else
                        {
                            // TX was successful
                            phy230_state = PHY_BUSY_TX;
                            tx_done = true;
                            break;
                        }
                    }

                    if (!tx_done)
                    {
                        // TX was unsuccessful
                        cm->status = PHY_INVALID_PARAMETER;
                        return true;
                    }
                }
                break;

            case PHY_TRX_OFF:
                cm->status = PHY_TRX_OFF;
                return true;

            case PHY_BUSY_RX:
            case PHY_RX_ON:
                cm->status = PHY_RX_ON;
                return true;

            default:
                ASSERT("pd_data_request in wrong PHY state" == 0);
                break;
        }
    }
    return false;
}


/**
 * \brief The PLME-CCA.request primitive requests that the PLME perform a CCA.
 *
 * If the receiver is enabled on receipt of the PLME-CCA.request primitive,
 * the PLME will cause the PHY to perform a CCA. When the PHY has completed
 * the CCA, the PLME will issue the PLME-CCA.confirm primitive with a status
 * of either BUSY or IDLE, depending on the result of the CCA. If the
 * PLME-CCA.request primitive is received while the transceiver is disabled
 * (TRX_OFF state) or if the transmitter is enabled (TX_ON state), the PLME
 * will issue the PLME-CCA.confirm primitive with a status of TRX_OFF or
 * TX_ON, respectively.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */

void plme_cca_request(uint8_t *m)
{
    plme_cca_conf_t cm;
    uint8_t hwstatus;

    cm.size    = sizeof(plme_cca_conf_t) - sizeof(cm.size);
    cm.cmdcode = PLME_CCA_CONFIRM;

    switch( phy230_state ){
        case PHY_BUSY_TX:
        case PHY_TX_ON:
            cm.status = PHY_TX_ON;
            bios_pushback_event(&cm);
            break;

        case PHY_TRX_OFF:
            cm.status = PHY_TRX_OFF;
            bios_pushback_event(&cm);
            break;

        case PHY_BUSY_RX:
        case PHY_RX_ON:
            /* Temporary switch to PLL_ON for potential bug fix */
            bios_reg_write(RG_TRX_STATE, CMD_PLL_ON);
            bios_reg_write(RG_TRX_STATE, CMD_RX_ON);

            phy230_fasttimer_expired = false;

            /* This actually starts the measurement. */
            bios_bit_write(SR_CCA_REQUEST, 1);

            bios_fasttimer(CCA_TIMEOUT, fasttimer_handler);

            while (!phy230_fasttimer_expired)
            {
                /* wait for timer to expire */
            }
            hwstatus = bios_reg_read(RG_TRX_STATUS);
            ASSERT((hwstatus & CCA_DONE_MASK) != 0);

            if ((hwstatus & CCA_STATUS_MASK) != 0)
            {
                hwstatus = PHY_IDLE;
            }
            else
            {
                hwstatus = PHY_BUSY;
            }

            cm.status = hwstatus;
            bios_pushback_event(&cm);
            break;

        default:
            ASSERT("unexpected plme_cca.request" == 0);
            break;
    }
}

/*
 * The fasttimer handler
 *
 * This function is called if the fasttimer has expired.
 */

static void fasttimer_handler(void)
{
    phy230_fasttimer_expired = true;
}


/**
 * \brief The PLME-ED.request primitive requests that the PLME perform an ED measurement.
 *
 * If the receiver is enabled on receipt of the PLME-ED.request primitive, the
 * PLME will cause the PHY to perform an ED measurement. When the PHY has
 * completed the ED measurement, the PLME will issue the PLME-ED.confirm
 * primitive with a status of SUCCESS. If the PLME-ED.request primitive is
 * received while the transceiver is disabled (TRX_OFF state) or if the
 * transmitter is enabled (TX_ON state), the PLME will issue the
 * PLME-ED.confirm primitive with a status of TRX_OFF or TX_ON, respectively.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */
void plme_ed_request(uint8_t *m)
{
    plme_ed_conf_t cm;
    uint8_t hw_status;

    cm.size    = sizeof(plme_ed_conf_t) - sizeof(cm.size);
    cm.cmdcode = PLME_ED_CONFIRM;

    switch( phy230_state ){
        case PHY_BUSY_TX:
        case PHY_TX_ON:
            cm.status = PHY_TX_ON;
            bios_pushback_event(&cm);
            break;

        case PHY_TRX_OFF:
            cm.status = PHY_TRX_OFF;
            bios_pushback_event(&cm);
            break;

        case PHY_BUSY_RX:
        case PHY_RX_ON:
            /*
             * The following is in accordance to the SWPM.
             */
            hw_status = bios_reg_read(RG_TRX_STATE);
            bios_reg_write(RG_TRX_STATE, CMD_PLL_ON);
            bios_reg_write(RG_TRX_STATE, hw_status);
            /* This actually starts the measurement. */
            bios_reg_write(RG_PHY_ED_LEVEL, 0);
            bios_fasttimer(ED_TIMEOUT, phy_t_ed);
            phy230_ed_running = true;
            break;

        default:
            ASSERT("unexpected plme_ed.request" == 0);
            break;
    }
}

/*
 * The ED timer handler
 *
 * This function is called if the ED timer has expired.
 */

static void phy_t_ed(void)
{
    plme_ed_conf_t cm;
    uint8_t psr_buf[sizeof(plme_set_req_t) + 1];
    plme_set_req_t *psr = (plme_set_req_t *)psr_buf;

    cm.size    = sizeof(plme_ed_conf_t) - sizeof(cm.size);
    cm.cmdcode = PLME_ED_CONFIRM;

    switch( phy230_state ){
        case PHY_BUSY_TX:
        case PHY_TX_ON:
        case PHY_TRX_OFF:
           break;

        case PHY_BUSY_RX:
        case PHY_RX_ON:
            cm.EnergyLevel = bios_reg_read(RG_PHY_ED_LEVEL);
            cm.status = PHY_SUCCESS;
            bios_pushback_event(&cm);
            break;

        default:
            ASSERT("unexpected ED timeout" == 0);
            break;
    }

    cli();
    phy230_ed_running = false;
    if (phy230_new_channel != 0)
    {
        sei();
        /* perform deferred channel switching */
        psr->PIBAttribute = phyCurrentChannel;
        psr->data[1] = phy230_new_channel;
        phy230_new_channel = 0;
        plme_set_request((uint8_t *)psr);
    }
    sei();
}


/*
 * Internal function to handle delay for PLL Lock from BUSY_TX to RX_ON
 *
 * This function is called if the phy needs to wait for a PLL Lock when switching
 * from BUSY_TX to RX_ON.
 */

static void wait_for_rx_on_from_busy_tx(void)
{
    phy230_fasttimer_expired = false;
    // Wait until the PLL is locked
    bios_fasttimer(PLL_BUSY_TX_RX_ON_TIMEOUT, fasttimer_handler);
    while(!phy230_fasttimer_expired)
    {
        // do nothing, wait for PLL Lock fast timer to expire
    }
}


/*
 * Internal function to handle delay for PLL Lock
 *
 * This function is called if the phy needs to wait for a PLL Lock when switching
 * the receiver on.
 */

static void wait_for_pll_lock(void)
{
    phy230_fasttimer_expired = false;
    // Wait until the PLL is locked
    bios_fasttimer(PLL_LOCK_TIMEOUT, fasttimer_handler);
    while(!phy230_fasttimer_expired)
    {
        // do nothing, wait for PLL Lock fast timer to expire
    }
}


/**
 * \brief The PLME-GET.request primitive requests information about a given PHY PIB attribute.
 *
 * On receipt of the PLME-GET.request primitive, the PLME will attempt to
 * retrieve the requested PHY PIB attribute from its database. If the
 * identifier of the PIB attribute is not found in the database, the PLME will
 * issue the PLME-GET.confirm primitive with a status of UNSUPPORTED_ATTRIBUTE.
 * If the requested PHY PIB attribute is successfully retrieved, the PLME will
 * issue the PLME-GET.confirm primitive with a status of SUCCESS.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */
void plme_get_request(uint8_t *m)
{
    plme_get_req_t *msg = (plme_get_req_t *)m;
    uint8_t temp[sizeof(plme_get_conf_t) + PHY_MAX_GETCONF_SIZE];
    plme_get_conf_t *cm = (plme_get_conf_t *) temp;

    (void)plme_get_request_internal(msg, cm);
    bios_pushback_event(cm);
}


/**
 * \brief Internal implementation of PLME-GET.request primitive
 *
 * This version returns the message in a parameter, without queuing it
 * up in the message queue.  To be used internally in the PHY and MAC
 * implementation.
 *
 * \param in msg The pointer to the message containing the parameters of this request.
 * \param out cm The pointer to the PLME-GET.conf message to fill in.
 * \return The result status of the operation.
 */
uint8_t plme_get_request_internal(plme_get_req_t *msg, plme_get_conf_t *cm)
{
    uint8_t         *PIBAttributeValue = cm->data;
    uint8_t         tmp;

    cm->cmdcode      = PLME_GET_CONFIRM;
    cm->PIBAttribute = msg->PIBAttribute;
    cm->status       = PHY_SUCCESS;

    switch (msg->PIBAttribute)
    {
        case phyCurrentChannel:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            bios_bit_read(SR_CHANNEL, &(PIBAttributeValue[1]));
            break;

        case phyChannelsSupported:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 4;
            PIBAttributeValue[0] = 4;
            PIBAttributeValue[1] = (RF230_SUPPORTED_CHANNELS >> 24) & 0xff;
            PIBAttributeValue[2] = (RF230_SUPPORTED_CHANNELS >> 16) & 0xff;
            PIBAttributeValue[3] = (RF230_SUPPORTED_CHANNELS >>  8) & 0xff;
            PIBAttributeValue[4] = (RF230_SUPPORTED_CHANNELS >>  0) & 0xff;
            break;

        case phyTransmitPower:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            bios_bit_read(SR_TX_PWR, &tmp);
            PIBAttributeValue[1] = tx_pwr_to_dbm(tmp);
            break;

        case phyCCAMode:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            bios_bit_read(SR_CCA_MODE, &(PIBAttributeValue[1]));
            break;

        case phyCheckCRC:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            PIBAttributeValue[1] = pibCheckCRC;
            break;

        case phyGenerateCRC:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            PIBAttributeValue[1] = pibGenerateCRC;
            break;

        case phyRSSI:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            PIBAttributeValue[1] = pibRSSI;
            break;

        case phyWakeupTime:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size) + 1;
            PIBAttributeValue[0] = 1;
            PIBAttributeValue[1] = RF230_WAKEUP_TIME;
            break;

        default:
            cm->size = sizeof(plme_get_conf_t) - sizeof(cm->size);
            PIBAttributeValue[0] = 0;
            cm->status = PHY_UNSUPPORTED_ATTRIBUTE;
            break;
    }
    /*
     * Ensure PHY_MAX_GETCONF_SIZE is not exceeded, so our callers can
     * allocate sufficient buffer space.
     */
    ASSERT(cm->size <= sizeof(plme_get_conf_t) - sizeof(cm->size) +
           PHY_MAX_GETCONF_SIZE);

    return cm->status;
}

/**
 * \brief The PLME-SET-TRX-STATE.request primitive requests that the PHY entity change the internal operating state of the transceiver.
 *
 * On receipt of the PLME-SET-TRX-STATE.request primitive, the PLME will cause
 * the PHY to change to the requested state. If the state change is accepted,
 * the PHY will issue the PLME-SET-TRX-STATE.confirm primitive with a status of
 * SUCCESS. If this primitive requests a state that the transceiver is already
 * configured, the PHY will issue the PLME-SET-TRX-STATE.confirm primitive with
 * a status indicating the current state, i.e., RX_ON, TRX_OFF, or TX_ON. If
 * this primitive is issued with RX_ON or TRX_OFF argument and the PHY is busy
 * transmitting a PPDU, the PHY will issue the PLME-SET-TRXSTATE. confirm
 * primitive with a status BUSY_TX and defer the state change till the end of
 * transmission. If this primitive is issued with TX_ON or TRX_OFF argument and
 * the PHY is in RX_ON state and has already received a valid SFD, the PHY will
 * issue the PLME-SET-TRX-STATE.confirm primitive with a status BUSY_RX and
 * defer the state change till the end of reception of the PPDU. If this
 * primitive is issued with FORCE_TRX_OFF, the PHY will cause the PHY to go the
 * TRX_OFF state irrespective of the state the PHY is in.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */
void plme_set_trx_state_request(uint8_t *m)
{
    plme_set_trx_state_req_t    *msg = (plme_set_trx_state_req_t *)m;
    plme_set_trx_state_conf_t   cm;

    plme_set_trx_state_request_internal(msg, &cm);
    bios_pushback_event(&cm);
}

/**
 * \brief Internal implementation of PLME-SET-TRX-STATE.request primitive
 *
 * This version returns the message in a parameter, without queuing it
 * up in the message queue.  To be used internally in the PHY and MAC
 * implementation.
 *
 * \param in msg The pointer to the message containing the parameters of this request.
 * \param out cm The pointer to the PLME-SET-TRX-STATE.conf message to fill in.
 */
void plme_set_trx_state_request_internal(plme_set_trx_state_req_t *msg, plme_set_trx_state_conf_t *cm)
{
    uint8_t                     hw_state;
    uint8_t                     new_state = msg->state;
    uint8_t                     phy230_orig_state = PHY_TRX_OFF;

    cm->size         = sizeof(plme_set_trx_state_conf_t) - sizeof(cm->size);
    cm->cmdcode      = PLME_SET_TRX_STATE_CONFIRM;
    cm->status       = PHY_SUCCESS;

    if (phy230_state == new_state)
    {
        cm->status = phy230_state;
    }
    else
    {
        phy230_orig_state = phy230_state;

        switch (new_state)
        {
            case PHY_RX_ON:
                {
                    phy230_state = PHY_RX_ON;
                    bios_bit_write(SR_TRX_CMD, CMD_RX_ON);
                    // Check whether we came from PHY_TRX_OFF and need to wait until the PLL has locked
                    if (phy230_orig_state == PHY_TRX_OFF)
                    {
                        wait_for_pll_lock();
                    }
                }
                break;

            case PHY_TX_ON:
                bios_bit_write(SR_TRX_CMD, CMD_PLL_ON);
                // Check whether we came from PHY_TRX_OFF and need to wait until the PLL has locked
                if (phy230_orig_state == PHY_TRX_OFF)
                {
                    wait_for_pll_lock();
                }
                phy230_state = PHY_TX_ON;
                break;

            case PHY_TRX_OFF:
                bios_bit_write(SR_TRX_CMD, CMD_TRX_OFF);
                phy230_state = PHY_TRX_OFF;
                break;

            case PHY_FORCE_TRX_OFF:
                bios_bit_write(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
                phy230_state = PHY_TRX_OFF;
                phy230_deferred_state = PHY_BUSY;
                break;

            default:
                ASSERT("unsupported state requested" == 0);
                break;
        }

        bios_bit_read(SR_TRX_STATUS, &hw_state);
        switch (hw_state)
        {
            case BUSY_TX:
                phy230_deferred_state = new_state;
                phy230_state = cm->status = PHY_BUSY_TX;
                break;

            case BUSY_RX:
                phy230_deferred_state = new_state;
                phy230_state = cm->status = PHY_BUSY_RX;
                break;
        }
    }
}

/**
 * \brief The PLME-SET.request primitive attempts to set the indicated PHY PIB attribute to the given value.
 *
 * On receipt of the PLME-SET.request primitive, the PLME will attempt to write
 * the given value to the indicated PHY PIB attribute in its database. If the
 * PIBAttribute parameter specifies an attribute that is not found in the
 * database (see Table 19), the PLME will issue the PLME-SET.confirm primitive
 * with a status of UNSUPPORTED_ATTRIBUTE. If the PIBAttibuteValue parameter
 * specifies a value that is out of the valid range for the given attribute,
 * the PLME will issue the PLME-SET.confirm primitive with a status of
 * INVALID_PARAMETER. If the requested PHY PIB attribute is successfully
 * written, the PLME will issue the PLME-SET.confirm primitive with a status
 * of SUCCESS.
 *
 * \param m The pointer to the message containing the parameters of this request.
 */
void plme_set_request(uint8_t *m)
{
    plme_set_req_t *msg = (plme_set_req_t *)m;
    plme_set_conf_t cm;
    uint8_t result;

    result = plme_set_request_internal(msg, &cm);

    if (result != PHY_WAIT_FOR_ED)
    {
        bios_pushback_event(&cm);
    }
}

/**
 * \brief Internal implementation of PLME-SET.request primitive
 *
 * This version returns the message in a parameter, without queuing it
 * up in the message queue.  To be used internally in the PHY and MAC
 * implementation.
 *
 * \param in msg The pointer to the message containing the parameters of this request.
 * \param out cm The pointer to the PLME-SET.conf message to fill in.
 * \return The status of the operation, or PHY_WAIT_FOR_ED (no status available yet).
 */
uint8_t plme_set_request_internal(plme_set_req_t *msg, plme_set_conf_t *cm)
{
    uint8_t         *PIBAttributeValue = msg->data;
    uint8_t         curchan;

    cm->size         = sizeof(plme_set_conf_t) - sizeof(cm->size);
    cm->cmdcode      = PLME_SET_CONFIRM;
    cm->PIBAttribute = msg->PIBAttribute;
    cm->status       = PHY_SUCCESS;

    switch (msg->PIBAttribute)
    {
        case phyCurrentChannel:
            if (RF230_SUPPORTED_CHANNELS & (((uint32_t) 1) << PIBAttributeValue[1]))
            {
                cli();
                if (phy230_ed_running)
                {
                    /* defer channel switching until the ED measurement completed */
                    phy230_new_channel = PIBAttributeValue[1];
                    sei();
                    return PHY_WAIT_FOR_ED;
                }
                sei();
                bios_bit_read(SR_CHANNEL, &curchan);
                if( curchan != PIBAttributeValue[1])
                {
                    bios_bit_write(SR_CHANNEL, PIBAttributeValue[1]);
                }
            }
            else
            {
                cm->status = PHY_INVALID_PARAMETER;
            }
            break;

        case phyTransmitPower:
            bios_bit_write(SR_TX_PWR, dbm_to_tx_pwr_lev(PIBAttributeValue[1]));
            break;

        case phyCCAMode:
            bios_bit_write(SR_CCA_MODE, PIBAttributeValue[1]);
            break;

        case phyCheckCRC:
            pibCheckCRC = PIBAttributeValue[1];
            break;

        case phyGenerateCRC:
            pibGenerateCRC = PIBAttributeValue[1];
            // Set the AUTO CRC mode.
#if AUTO_CRC_ON
            bios_bit_write(SR_TX_AUTO_CRC_ON, pibGenerateCRC);
#endif
            break;

        default:
            cm->status = PHY_UNSUPPORTED_ATTRIBUTE;
            break;
    }

    return cm->status;
}

/*
 * This function merges the RSSI (from phyRSSI) and LQI values into
 * the final ppduLinkQuality value.
 *
 * parameter lqi: input LQI
 * return value: ppduLinkQuality
 */
static inline uint8_t compute_lqi(uint8_t lqi)
{
    uint8_t rssi;
    uint16_t LinkQuality;

    /*
     * RSSI ranges from 0 through 27 (inclusive).  Two stations
     * physically located side by side yield an RSSI of 15...16
     * (i. e. ~ -40 dBm), so we can safely consider that the maximum
     * useful value.
     *
     * Rx LQI normally is close to 255 unless there is severe
     * interference on the channel (multipath propagation, other radio
     * interference).  For frames with an LQI below ~ 200, the packet
     * error rate drastically increases, so we consider 192 to be the
     * smallest useful value.
     *
     * The formula chosen includes some square of the LQI value so
     * frames with a low RSSI but full LQI will still get a reasonable
     * ppduLinkQuality as they are pretty fine to be used except the
     * distance between Tx and Rx is rather close to the usable range.
     */

    /* Normalize LQI to 0..63. */
    if (lqi < 192)
    {
        lqi = 0;
    }
    else
    {
        lqi -= 192;
    }

    /* Normalize RSSI to 0..15. */
    if (pibRSSI > 15)
    {
        rssi = 15;
    }
    else
    {
        rssi = pibRSSI;
    }

    /*
     * This is the square component.  It makes small RSSI values more
     * preferrable provided the LQI was still good.
     */
    rssi += (lqi & (uint8_t)0x30) >> 4;

    lqi /= 4;                   /* range 0..15 */

    LinkQuality = lqi * rssi;
    if (LinkQuality >= 256)
    {
        return 255;
    }
    else
    {
        return LinkQuality;
    }
}


/**
 * \brief This function services the RX_START interrupt of the AT86RF230.
 *
 * \param tst This is the timestamp for this interrupt.
 */
 



void phy_rx_start(uint32_t tst)
{   uint8_t con;
    uint8_t length;
    uint32_t waittime;
    uint8_t lqi;
    pd_data_ind_t *pdi = (pd_data_ind_t *) phy_rx_buffer;
   
    
#if F_CPU == 8000000UL
#  define WAIT_FUZZ 0  /* # symbols to subtract from computed value */
#  define WAIT_US   0 /* # microseconds to additionally delay for (sub-symbol delay) */
#else
#  error "Routines have not been timed yet for your F_CPU"
#endif /* F_CPU */

    /*
     * The RSSI value is transient, and only available while the frame
     * is being received.  Just fetch it here, and store it in a PIB
     * attribute for later retrieval.
     */
    bios_bit_read(SR_RSSI, &pibRSSI);

    if ((phy230_state != PHY_RX_ON) && (phy230_deferred_state == PHY_RX_ON))
    {
        phy230_state = PHY_BUSY_RX;
        phy230_deferred_state = PHY_BUSY;
    }

    pdi->cmdcode   = PD_DATA_INDICATION;
    pdi->timestamp = tst;

    switch( phy230_state )
    {
        case PHY_BUSY_RX:
        case PHY_RX_ON:
            phy230_state = PHY_BUSY_RX;
            /*
             * Delay the frame upload until we can be sure we won't
             * encounter a FIFO underrun.
             */
            if (!bios_queue_full())
            {
                length = bios_frame_length_read();
                /*
                * Calculate delay time needed.  Our SPI octet rate is
                * less than our radio octet rate, so we cannot start
                * uploading the frame immediately as soon as the preamble
                * has been detected, as this would cause the RX FIFO to
                * underrun.  We have to delay until it is really sure the
                * frame will have been received entirely by the time our
                * SPI frame read is finished.
                *
                * As the actualy amount to wait depends on the length of
                * the frame, we at first read the length octet back.
                *
                * WAIT_FUZZ and WAIT_US account for the fact that we've
                * already spent quite some computation time until we got
                * here.
                *
                * The while loop is written in a way so timer overruns do
                * not matter (unsigned int wrap around).
                */
                waittime = RADIO_RATE_SP((unsigned)length) - SPI_RATE_SP((unsigned)length);
                while (bios_sub_time(bios_gettime(), tst) < bios_add_time(waittime, WAIT_FUZZ))
                    /* wait */ ;
#if WAIT_US > 0
                delay_us(WAIT_US);
#endif /* WAIT_US > 0 */
   
		 

                if(pibCheckCRC)
                {
                    pdi->psduLength         = bios_frame_crc_read((unsigned char *) &(pdi->data));
		 		   
                }
                else
                {
                    pdi->psduLength         = bios_frame_read((unsigned char *) &(pdi->data));
                }

                lqi = pdi->data[pdi->psduLength];

                if (pdi->psduLength > 0)
                {
                    /* decrement length by 1, because of LQI value, which is appended to the frame data */
                    pdi->psduLength         = pdi->psduLength - 1;
                    pdi->data[0]            = pdi->psduLength;
                    pdi->size               = sizeof(pd_data_ind_t) - sizeof(pdi->size) + pdi->psduLength;
                }

                if (pdi->psduLength > aMaxPHYPacketSize)
                {
                    /* should not happen anyway */
                    pdi->psduLength = aMaxPHYPacketSize;
                }

                if (pdi->psduLength > 0)
                {
#if APP_TYPE >= APP_L2
                    /*
                    * Pre-parse the MPDU just received, and let
                    * the MAC quickly generate an ACK frame if
                    * needed.
                    * If the parser discards the MPDU (e.g. since
                    * the address does not match, don't generate
                    * the PD-DATA.indication below at all.
                    */
                    if (mac_parse_MPDU(pdi, 1))
#endif /* APP_TYPE >= APP_L2 */
                    {
                        /*
                        * Here, we've left the critical path wrt. ack
                        * timing, so now take a bit of time to combine
                        * the RSSI and LQI values from this transmission
                        * into a ppduLinkQuality indication.
                        */
                        pdi->ppduLinkQuality = compute_lqi(lqi);
			bios_pushback_event(pdi);
                    }
                }
            }
            break;

        default:
            break;
    }
    
    
    
 
}

/**
 *  \brief This function services the TRX_END interrupt of the AT86RF230.
 */
void phy_trx_end(void)
{
    pd_data_conf_t cmdc;

    switch( phy230_state )
    {
        case PHY_BUSY_TX:
            cmdc.size    = sizeof(pd_data_conf_t) - sizeof(cmdc.size);
            cmdc.cmdcode = PD_DATA_CONFIRM;
            cmdc.status  = PHY_SUCCESS;
            bios_pushback_event(&cmdc);

            phy230_state = PHY_TX_ON;
            break;

        case PHY_BUSY_RX:
            phy230_state = PHY_RX_ON;
            break;

        default:
            // Due to SW generated ACK, TRX_END could be ignored in all other cases
            break;
    }

    switch (phy230_deferred_state)
    {
        case PHY_TRX_OFF:
            bios_bit_write(SR_TRX_CMD, CMD_TRX_OFF);
            phy230_state = PHY_TRX_OFF;
            break;

        case PHY_RX_ON:
            /* This state transition is already done by HW, do the same for SW */
            phy230_state = PHY_RX_ON;
            break;

        case PHY_TX_ON:
            /* This state transition is already done by HW, do the same for SW */
            phy230_state = PHY_TX_ON;
            break;

        case PHY_FORCE_TRX_OFF:
            bios_bit_write(SR_TRX_CMD, CMD_FORCE_TRX_OFF);
            phy230_state = PHY_TRX_OFF;
            break;

        case PHY_BUSY:
            /* do not do anything */
            break;

        default:
            ASSERT("unsupported state requested" == 0);
            break;
    }
    phy230_deferred_state = PHY_BUSY;
}
#endif /* (RADIO_TYPE == AT86RF230 || defined(DOXYGEN)) && APP_TYPE >= APP_L1 */

/* EOF */
