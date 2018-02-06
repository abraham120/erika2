/* Jan Kleinsorge, 2010 */

#include "ee.h"
#include "cpu/tricore1/inc/ee_hal.h"
#include "mcu/tc179x/inc/ee_wdt.h"
#include "mcu/tc179x/inc/ee_tc179xdefs.h"

/* To access WDTCON0/WDTCON1 a password sequence must be applied.  We
 * need this access to clear the ENDINIT bit so modifications to
 * certain system registers become possible. EE_*/

void EE_wdt_lock() {
    EE_WDT_CON0 c0;
    EE_WDT_CON1 c1;

    c0 = EE_tc179x_wdt_con0;
    c1 = EE_tc179x_wdt_con1;
    c0.reg &= 0xffffff03;
    c0.reg |= 0xf0;
    c0.reg |= (c1.reg & 0xc);
    c0.reg ^= 0x2;
    EE_tc179x_wdt_con0 = c0;
    c0.reg &= 0xfffffff0;
    c0.reg |= 0x3;
    EE_tc179x_wdt_con0 = c0;
    c0 = EE_tc179x_wdt_con0; /* read back new value: synchronise LFI */
}


void EE_wdt_unlock() {
    EE_WDT_CON0 c0;
    EE_WDT_CON1 c1;

    c0 = EE_tc179x_wdt_con0;
    c1 = EE_tc179x_wdt_con1;
    c0.reg &= 0xffffff03;
    c0.reg |= 0xf0;
    c0.reg |= (c1.reg & 0xc);
    c0.reg ^= 0x2;    
    EE_tc179x_wdt_con0 = c0;
    c0.reg &= 0xfffffff0;
    c0.reg |= 0x2;
    EE_tc179x_wdt_con0 = c0;
    c0 = EE_tc179x_wdt_con0; /* read back new value: synchronise LFI */
}
