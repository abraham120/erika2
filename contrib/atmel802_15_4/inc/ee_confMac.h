/* coordinator data*/
/* === Includes ============================================================ */
#ifndef _CONFMAC_
#define _CONFMAC_

#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "wpan_defines.h"
#include "ieee_const.h"
#include "wpan_mac.h"
#include "ee.h"
#ifdef	__ATMEGA128__
#include "mcu/atmel_atmega128/inc/ee_ic.h"
#endif	/* __ATMEGA128__ */

/* ==== Macros for Coordinator=============================================== */
#ifndef RF_CHANNEL
# define RF_CHANNEL (18)
# warning "RF channel undefined, using channel 18 as default"
#endif
#define PANCOORD_SHORT_ADD      (0xBABE)
#define BROADCAST_SHORT_ADD     (0xFFFF)
#define PANID                   (0xCAFE)

#define PANCOORD_SCAN_CHANNELS  ((uint32_t)0x00000000)
#define SCAN_DURATION            (3)
#define BEACON_ORDER            (15)    /*  NO Beacon */
#define SUPERFRAME_ORDER        (15)
#define EMPTY_LONG_ADDRESS      (~(uint64_t)0)

#define MAX_ENTRIES             (8)
#define NO_ENTRY                (0xFF)

/* macro stores the state value and sets the state led to 0 */
#ifdef PANCOORDINATOR

#define SET_STATE(x) do { c_status.state=(x); \
                          PORTE |= (_BV((uint8_t)(x)));} while(0)
#endif	
#ifdef DEVICE
#define SET_STATE(x) do { d_status.state=(x); \
                          PORTE |= (_BV((uint8_t)(x)));} while(0)
#endif			  
			  
/* ==== Macros for Device   =============================================== */

#define ALL_HIGH_BAND_CHANNELS ((uint32_t)0x07FFF800)
#define CHANNELMASK(a) (1UL<<(a))
			  
			  
/* === Typedefs ============================================================ */
typedef struct
{
    bool associated;
    uint64_t long_addr;
} association_entry_t;

typedef enum
{
    INIT_DONE_C,
    PEND_RESET_C,
    PEND_SET_SHORT_ADDR_C,
    PEND_INITIAL_SCAN_C,
    PEND_START_C,
    PEND_ASSOC_PERMIT_C,
    RUN_C,
} coord_state_t;

typedef enum
{
    INIT_DONE_D,
    PEND_RESET_D,
    PEND_SCAN_D,
    PEND_ASSOCIATE_D,
    PEND_SET_SHORT_ADDR_D,
    PEND_START_D,
    RUN_D,
} device_state_t;

typedef struct
{
    uint8_t handle;
    uint8_t led_value;
    coord_state_t state;
} coord_status_t;

typedef struct
{
    bool led;
    bool switch_pressed;
    uint16_t device_short_address;
    uint8_t  coord_address_mode;
    uint64_t coord_address;
    uint16_t pan_id;
    uint8_t logical_channel;
    uint8_t msdu_handle;
    device_state_t state;
} device_status_t;

typedef enum
{
    RX_FREE_COORD,
    RX_BUSY_COORD,
    RX_END_COORD
} rx_state;

typedef struct
{
    rx_state state;
} receiver_st;

/* === Static Variables ==================================================== */
//static coord_status_t c_status;
//coord_status_t c_status;
//device_status_t d_status;

uint8_t data_buffer[127];


/* === Prototypes for Coordinator============================================ */
/*
void application_init(void);
void mac_do_reset(void);
void mac_active_scan(void);
void mac_start_pan(void);
void mac_set_short_addr(uint16_t addr);
void mac_set_assoc_permit(uint8_t permit);
void mac_register_device(uint64_t DeviceAddress);
void mac_send_data(void);

static void association_table_init(void);
static uint8_t get_empty_association_slot(void);
uint8_t search_association_entry(uint64_t addr);

/* === Prototypes for Device============================================ */
/*
static void switch_task(void);
static void mac_scan(void);
static void mac_associate(void);

*/
#endif




