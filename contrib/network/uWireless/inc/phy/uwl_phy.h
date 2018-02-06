/**
* @file phy.h
* @brief IEEE 802.15.4 PHY Layer Public Interface
* @author Christian Nastasi
* @date 2009-03-22
*
* This file is the entry point for the IEEE 802.15.4 PHY primitives.
*/
#ifndef __uwl_phy_h__
#define __uwl_phy_h__

#include <phy/uwl_phy_const.h>	/* Include the PHY constants definition. */
#include <phy/uwl_phy_types.h>	/* Include the PHY types. */
#include <phy/uwl_phy_pd.h>	/* Include the PD-SAP definition. */
#include <phy/uwl_phy_plme.h>	/* Include the PLME-SAP definition. */

int8_t uwl_phy_init(void);

#endif /* Header Protection */
