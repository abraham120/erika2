/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/******************************************************************************
* Copyright © 2004 Altera Corporation, San Jose, California, USA.             *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
*******************************************************************************
*                                                                             *
* Modified version from:
* Author - PRR                                                                *
*                                                                             *
* MAC_Address.c - This is the mechanism by which the driver finds out         *
* it's MAC address. It's board specific so we've made it part of your         *
* application                                                                 *
*                                                                             *
******************************************************************************/

#include "alt_types.h"
#include "io.h"
#include "lwip/netif.h"

/*
* read_mac_address
*
* Read the MAC address in a board specific way
*
*/
err_t read_mac_address(struct netif *netif)
{
  err_t ret_code = ERR_IF;
  alt_u32 signature;

  /*
  * Our board has the MAC address stored at 0x7f000 in flash
  */
#if defined(ALTERA_NIOS_DEV_BOARD_CYCLONE_1C20) ||\
    defined(ALTERA_NIOS_DEV_BOARD_STRATIX_1S10) ||\
    defined(ALTERA_NIOS_DEV_BOARD_STRATIX_1S10_ES) ||\
    defined(ALTERA_NIOS_DEV_BOARD_STRATIX_1S40)
  signature = IORD_32DIRECT(0x7f0000, 0);

  if (signature != 0x00005afe)
  {
    LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("No MAC Address in the flash\n"));
    fprintf(stderr, "Can't read the MAC address.\nYou need to modify the function read_mac_address to set a MAC address for your board\n");
  }
  else
  {
    /* Set MAC hardware address length */
    netif->hwaddr_len = 6;

    netif->hwaddr[0] = IORD_8DIRECT(0x7f0000, 4);
    netif->hwaddr[1] = IORD_8DIRECT(0x7f0000, 5);
    netif->hwaddr[2] = IORD_8DIRECT(0x7f0000, 6);
    netif->hwaddr[3] = IORD_8DIRECT(0x7f0000, 7);
    netif->hwaddr[4] = IORD_8DIRECT(0x7f0000, 8);
    netif->hwaddr[5] = IORD_8DIRECT(0x7f0000, 9);
    ret_code = ERR_OK;
  }
#else
  fprintf(stderr, "Not an Altera board.\nYou need to modify the function read_mac_address to set a MAC address for your board.\n");
#endif


  return ret_code;

}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
