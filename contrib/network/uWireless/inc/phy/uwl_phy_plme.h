/**
* @file phy_plme.h
* @brief IEEE 802.15.4 PLME-SAP Interface
* @author Christian Nastasi
* @date 2009-03-19
*
* The file contains the declaration of the PLME service primitives
* of the IEEE 802.15.4 standard.
* The definition of the \b request funtions takes place in the phy subtree,
* while the \b confirm ones are defined in the mac subree.
* \todo Make a specific reference to the files that implement these primitives.
*/
#ifndef __uwl_phy_plme_h__
#define __uwl_phy_plme_h__

#include <phy/uwl_phy_types.h>

int8_t uwl_PLME_CCA_request(void);
int8_t uwl_PLME_CCA_confirm(enum uwl_phy_code_t status);

int8_t uwl_PLME_ED_request(void);
int8_t uwl_PLME_ED_confirm(enum uwl_phy_code_t status, uint8_t EnergyLevel);

int8_t uwl_PLME_GET_request(enum uwl_phy_pib_id_t PIBAttribute);
int8_t uwl_PLME_GET_confirm(enum uwl_phy_code_t status,
			    enum uwl_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue);

int8_t uwl_PLME_SET_TRX_STATE_request(enum uwl_phy_code_t state);
int8_t uwl_PLME_SET_TRX_STATE_confirm(enum uwl_phy_code_t status);

int8_t uwl_PLME_SET_request(enum uwl_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue);
int8_t uwl_PLME_SET_confirm(enum uwl_phy_code_t status,
			    enum uwl_phy_pib_id_t PIBAttribute);

#endif /* Header Protection */
