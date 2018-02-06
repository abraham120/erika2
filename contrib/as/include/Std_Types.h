/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

/** @file	Std_Types.h
 *  @brief	AUTOSAR Standard Types Header File.
 *
 *  This file contains all the types that are used across several modules of the
 *  basic software and that are platform and compiler independend.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */


/*
 * STD014:	The standard types header files shall be protecetd against
 * 		multiple inclusion.
 */
#ifndef	STD_TYPES_H
#define	STD_TYPES_H

/*
 * STD001:	Std_Types.h shall include Platform_Types.h
 * 		Std_Types.h shall include Compiler.h
 * 		All other basic software modules shall inlcude Std_types.h
 */
#include "Platform_Types.h"
#include "Compiler.h"

/** @brief	Standard Return Type
 *
 *  <b>STD005:</b> This type can be used as standard API return type which is
 *  shared between the RTE and the BSW modules.
 *
 *  <b>STD011:</b> The <tt>Std_ReturnType</tt> shall normally be used with value
 *  <tt>E_OK</tt> or <tt>E_NOT_OK</tt>. If those  return values are not
 *  sufficient user specific values can be defined by using the 6 least specific
 *  bits.
 *
 *  Layout of the <tt>Std_ReturnType</tt> shall be as stated in the RTE
 *  specification. Bit 7 and Bit 8 are reserved and defined by the RTE
 *  specification.
 *
 */
typedef	uint8	Std_ReturnType;

#ifndef	STATUSTYPEDEFINED
#define	STATUSTYPEDEFINED	/**< OSEK compliance */
#define	E_OK		0x00	/**< OK		     */

/** @brief	OSEK compliance
 *
 *  <b>STD006:</b> Because <tt>E_OK</tt> is already defined within OSEKm the
 *  symbol <tt>E_OK</tt> has to be shared. To avoid name clashes and
 *  redefinition problems, the symbols have to be defined in the following way
 *  (approved within implementation):<br>
 *  <code>
 *    \#ifndef STATUSTYPEDEFINED<br>
 *    \#define STATUSTYPEDEFINED<br>
 *    \#define E_OK 0x00<br>
 *    typedef unsigned char StatusType;<br>
 *    \#endif<br>
 *    \#define E_NOT_OK 0x01
 *  </code>
 */
typedef	unsigned char	StatusType;	/* OSEK compliance */
#endif
#define	E_NOT_OK	0x01	/**< NOT OK	      */

/*
 * STD007:	The symbols STD_HIGH and STD_LOW shall be defined as follows:
 */
#define	STD_LOW		0x00	/**< Physical state 0V         */
#define	STD_HIGH	0x01	/**< Physical state 5V or 3.3V */

/*
 * STD010:	The symbols STD_ON and STD_OFF shall be defined as follows:
 */
#define	STD_OFF		0x00	/**< OFF */
#define	STD_ON		0x01	/**< ON  */

/*
 * STD013	The symbols STD_ACTIVE and STD_IDLE shall be defined as follows:
 */
#define	STD_IDLE	0x00	/**< Logical state idle   */
#define	STD_ACTIVE	0x01	/**< Logical state active */

/** @brief	Standar Version Informations Type
 *
 *  <b>STD015:</b> This type shall be used to request the version of a BSW
 *  module using the <tt>\<Module name\>_GetVersionInfo()</tt> function.
 */
typedef	struct
{
  uint16	vendorID;		/**< Vendor Identifier.		    */
  uint16	moduleID;		/**< Module Identifier.		    */
  uint8		sw_major_version;	/**< Software Version Major Number. */
  uint8		sw_minor_version;	/**< Software Version Minor Number. */
  uint8		sw_patch_version;	/**< Software Version Patch Number. */
} Std_VersionInfoType;

/*uint8		ar_major_version;*/	/* AUTOSAR Version Major Number. */
/*uint8		ar_minor_version;*/	/* AUTOSAR Version Minor Number. */
/*uint8		ar_patch_version;*/	/* AUTOSAR Version Patch Number. */


/** @brief	Standard Version Informations Retrieval Macro Function.
 *  @param	_vi	Standard Version Informations Type Pointer.
 *  @param	_module	<tt>\<Module name\></tt> Macro.
 *
 *  Macro Function used to implement <tt>\<Module name\>_GetVersionInfo()</tt>.
 */
#define	STD_GET_VERSION_INFO(_vi,_module) \
	if(_vi != NULL) \
	{\
		((_vi)->vendorID = _module ## _VENDOR_ID);\
		((_vi)->moduleID = _module ## _MODULE_ID);\
		((_vi)->sw_major_version = _module ## _SW_MAJOR_VERSION);\
		((_vi)->sw_minor_version = _module ## _SW_MINOR_VERSION);\
		((_vi)->sw_patch_version = _module ## _SW_PATCH_VERSION);\
	}
/*
		((_vi)->ar_major_version = _module ## _AR_MAJOR_VERSION);\
		((_vi)->ar_minor_version = _module ## _AR_MINOR_VERSION);\
		((_vi)->ar_patch_version = _module ## _AR_PATCH_VERSION);\
*/
#endif	/* STD_TYPES_H */
