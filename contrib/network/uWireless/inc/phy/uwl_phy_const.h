/**
* @file phy_const.h
* @brief IEEE 802.15.4 PHY Constants
* @author Christian Nastasi
* @date 2009-03-22
*/
#ifndef __uwl_phy_const_h__
#define __uwl_phy_const_h__

/**
*  @brief Number of Channel Pages
*
*  According to this value the \ref UWL_PHY_CHANNEL_SUPPORTED_INIT must be
*  properly defined as an array of \c UWL_PHY_CHANNEL_PAGES elements.
*/
#define UWL_PHY_CHANNEL_PAGES 1



#define UWL_PHY_CHANNEL_PAGE_FIRST 	0
#define UWL_PHY_CHANNEL_PAGE_LAST 	31

#define UWL_PHY_ERR_NONE		1 /* Returned as positive! */
#define UWL_PHY_ERR_INVALID_PARAM	2
#define UWL_PHY_ERR_HW_FAILURE		3
#define UWL_PHY_ERR_NOT_INITIALIZED	4
#define UWL_PHY_ERR_KAL_ERROR		5



/**
* @name IEEE 802.15.4 PHY Layer Constants
* @{ */
#define UWL_aMaxPHYPacketSize 	127
#define UWL_aTurnaroundTime 	12
/**  @} */

#endif /* Header Protection */
