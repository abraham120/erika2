/** 
* @file uwl_mac_gts.c
* @brief IEEE 802.15.4 MAC Layer GTS Management
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @version 0.1
* @date 2009-06-22
*/
#include <mac/uwl_mac_internal.h>
#include <hal/uwl_radio.h>
#include <util/uwl_memory.h>
#include <util/uwl_debug.h>

/******************************************************************************/
/*                            MAC GTS Private Data                            */
/******************************************************************************/
LIST_DEFINE_STATIC(gts_list, struct uwl_gts_info_t, 
		   UWL_MAC_GTS_MAX_NUMBER, COMPILER_ATTRIBUTE_NONE);

/******************************************************************************/
/*                        MAC GTS Private Functions                           */
/******************************************************************************/
#ifdef UWL_GTS_MANIPULATION /* TODO: in future always enable THIS!!! */
static int8_t gts_db_add_entry(uwl_mac_dev_addr_short_t dev_addr, uint8_t len, 
			       uint8_t dir) 
{
	struct uwl_gts_info_t *entry;

	if (len > UWL_MAC_SUPERFRAME_LAST_SLOT || dir > 1) 
		return -UWL_MAC_ERR_INVALID_PARAM; /* invalid params values */
	/*TODO: check aMinCAPLength, calculate the minCAP in slot and use it
		instead of 1 
	*/
	if (list_is_full(&gts_list) || uwl_mac_gts_stat.first_cfp_tslot < len+1)
		return -UWL_MAC_ERR_GTS_CFP_TOO_LARGE;
	for (entry = (struct uwl_gts_info_t *) list_iter_front(&gts_list); 
	     entry != 0;
             entry = (struct uwl_gts_info_t *) list_iter_next(&gts_list)) 
		if (entry->dev_address == dev_addr && entry->direction == dir)
			return 0; /*TODO: check. already added, make sense? */
	uwl_mac_gts_stat.first_cfp_tslot -= len;
	entry = list_push_front(&gts_list); /* NOTE: already checked if full! */
	entry->starting_tslot = uwl_mac_gts_stat.first_cfp_tslot;
	entry->length = len;
	entry->direction = dir;
	entry->dev_address = dev_addr;
	entry->expiration = 0x00; /* TODO: un-hardcode!!! */
	//uwl_mac_gts_stat.descriptor_count++;
	return UWL_MAC_ERR_NONE;
}
#endif

COMPILER_INLINE void gts_db_delete_all(void) 
{
	list_clear(&gts_list);
	uwl_mac_gts_stat.first_cfp_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT + 1;
	uwl_mac_gts_stat.tx_start_tslot = 0;
	uwl_mac_gts_stat.tx_length = 0;
	uwl_mac_gts_stat.rx_start_tslot = 0;
	uwl_mac_gts_stat.rx_length = 0;
}

COMPILER_INLINE void set_gts_descriptor(uint8_t *des, 
					uwl_mac_dev_addr_short_t addr, 
					uint8_t tslot, uint8_t len)
{
	//memcpy(des, &addr, sizeof(uwl_mac_dev_addr_short_t));
	des[0] = addr & 0x00FF;
	des[1] = addr >> 8;
	des[2] = (len << 4) | (tslot & 0x0F);
}

/******************************************************************************/
/*                MAC GTS General Exportable Functions                        */
/******************************************************************************/
/* TODO: add more low-level manipulation functions! 
         (e.g allowing GTS allocation with 'holes') 
*/
int8_t uwl_mac_gts_db_clean(void) 
{
	#ifdef UWL_GTS_MANIPULATION
	gts_db_delete_all();
	return 1;
	#else
	return -UWL_MAC_ERR_GTS_MANIPULATION_DISABLED;
	#endif
}

int8_t uwl_mac_gts_db_add(uwl_mac_dev_addr_short_t dev_addr, 
			  uint8_t len, uint8_t dir) 
{
	#ifdef UWL_GTS_MANIPULATION
	return gts_db_add_entry(dev_addr, len, dir);
	#else
	return -UWL_MAC_ERR_GTS_MANIPULATION_DISABLED;
	#endif
}

/******************************************************************************/
/*                        MAC GTS General Functions                           */
/******************************************************************************/
int8_t uwl_mac_gts_init(void) 
{
	gts_db_delete_all();
	return 1;
}

uint8_t uwl_mac_gts_set_gts_fields(uint8_t *gf) 
{
	struct uwl_gts_info_t *entry;
	uint8_t *tmp;
	uint8_t i = 0;
	uint8_t s = UWL_MAC_MPDU_GTS_SPEC_SIZE;

	memset(uwl_gts_schedule, 0x00, 
	       sizeof(struct uwl_gts_info_t) * UWL_MAC_GTS_MAX_NUMBER);
	if (uwl_mac_pib.macGTSPermit == 0) {
		UWL_MAC_GTS_SPEC_SET_EMPTY(gf);
		return s;
	}
	UWL_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gf, list_get_size(&gts_list));
	UWL_MAC_GTS_SPEC_SET_PERMIT(gf, uwl_mac_pib.macGTSPermit);
	if (list_is_empty(&gts_list))
		return s;
	tmp = gf + s;
	s += UWL_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	for (entry = (struct uwl_gts_info_t *) list_iter_front(&gts_list); 
	     entry != 0;
             entry = (struct uwl_gts_info_t *) list_iter_next(&gts_list)) {
		UWL_MAC_GTS_DIRECTION_SET(tmp, i, entry->direction);
		set_gts_descriptor(gf + s, entry->dev_address,  
				   entry->starting_tslot, entry->length); 
		s += UWL_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
		memcpy(uwl_gts_schedule + i, entry, 
		       sizeof(struct uwl_gts_info_t));
		i++;
	}
	/* TODO: remove this! DEBUG TEST!!! ---------- >>>>> */
	/*
	static uint16_t aaa = 0x0005;
	//static char bbb = 1;
	if (gts_db_add_entry(aaa++, 1, UWL_MAC_GTS_DIRECTION_OUT) == -1) {
		gts_db_delete_all();
		gts_db_add_entry(0x0002, 1, UWL_MAC_GTS_DIRECTION_OUT);
		gts_db_add_entry(0x0003, 3, UWL_MAC_GTS_DIRECTION_OUT);
		gts_db_add_entry(0x0004, 2, UWL_MAC_GTS_DIRECTION_OUT);
		//if (bbb) {
		//	uwl_mac_pib.macBeaconOrder++;
		//	bbb = 0;
		//} else {
		//	uwl_mac_pib.macBeaconOrder--;
		//	bbb = 1;
		//}
	}
	*/
	/* <<<<<<<<<<<<-----------------  TODO REMOVE BLOCK!!! */
	return s;
}

uint8_t uwl_mac_gts_get_gts_fields(uint8_t *gf) 
{
	uint8_t *tmp;
	uint8_t cnt;
	uint8_t i = 0;
	uint8_t s = UWL_MAC_MPDU_GTS_SPEC_SIZE;

	uwl_mac_pib.macGTSPermit = UWL_MAC_GTS_SPEC_GET_PERMIT(gf);
	/* TODO: current policy is, no more GTS available when the
		 descriptor is not present any more.
		 Check w.r.t the std.
	*/
	uwl_mac_gts_stat.tx_length = 0;
	uwl_mac_gts_stat.rx_length = 0;
	if (uwl_mac_pib.macGTSPermit == 0) 
		return s;
	cnt = UWL_MAC_GTS_SPEC_GET_DESCRIPTOR_COUNT(gf);
	tmp = gf + s;
	if (cnt > 0)
		s += UWL_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	/* NOTE: if the GTS descriptor list is malformed (more than one GTS
		 in tx or more than one in rx) this shall take the last one! */
	for (i = 0; i < cnt; i++) {
		if (UWL_MAC_GTS_DES_GET_ADDRESS(gf + s) == 
		    uwl_mac_pib.macShortAddress) {
			if (UWL_MAC_GTS_DIRECTION_GET(tmp, i) == 
			    UWL_MAC_GTS_DIRECTION_OUT) {
				uwl_mac_gts_stat.tx_start_tslot =
					UWL_MAC_GTS_DES_GET_START_SLOT(gf + s);
				uwl_mac_gts_stat.tx_length =
					UWL_MAC_GTS_DES_GET_LENGTH(gf + s);
			} else {
				uwl_mac_gts_stat.rx_start_tslot =
					UWL_MAC_GTS_DES_GET_START_SLOT(gf + s);
				uwl_mac_gts_stat.rx_length =
					UWL_MAC_GTS_DES_GET_LENGTH(gf + s);
			}
		}
		s += UWL_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
	}
	return s;
}


