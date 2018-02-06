/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

#include "BswCommon.h"

typedef struct {
    uint32 crc;                 ///< (bytes 0..3) CRC of the flash segment (the field itself (i.e. the first 4 bytes of the flash segment) is not included in the calculation of the CRC - see ComputeCrc_Skip4()).
    uint8 description[32];      ///< (bytes 4..35) Description of the release of the flash segment (ex. "Fixed bug in error DiagService"). Coding: ASCII coded, zero-termination is absent if the length is exactly 32.
    uint8 date[16];             ///< (bytes 36..51) Date of the release. This is a text field, and the syntax is not specified (ex. "18/01/2013 15:44"). Coding: ASCII coded, zero-termination is absent if the length is exactly 16.
    uint16 swVersion;           ///< (bytes 52..53) Version of the master flash segment. Display type: hex HH.HH. The counter starts from 00.01.
    uint16 segmentVersion;      ///< (bytes 54..55) Version of the flash segment. Display type: hex HH.HH. \n The counter re-starts from 00.01 each time 'swVersion' changes. \n For the master flash segment the only valid value is 00.01.
    uint8 segmentId;            ///< (byte 56) Identifier of the segment. Possible values 0=APPL_CP0, 1=CALIB_RAM, 2=CALIB_FLASH, 3=APPL_CP1.
    uint8 compressEncrypt;      ///< (byte 57) Bits 0..3 'compressionType', possible values: 0=no_compression; 1=compression. \n Bits 4..7 'encryptionType', possible values: 0=no encryption.
    uint16 minLoaderVers;       ///< (bytes 58..59) The version of the bootloader currently installed on the ECU must be at least 'minLoaderVers'. Display type: hex HH.HH.
    uint32 masterSegmId;        ///< (bytes 60..63) It's the CRC of the master flash segment. \n Used to link every flash segment with the related master flash segment. \n If the current flash segment is the master then the fields 'masterSegmId' must be 0.
    uint32 startAddr;           ///< (bytes 64..67) Start address in flash.
    uint32 maxEndAddr;          ///< (bytes 68..71) Maximum end address in flash for the segment (i.e. the minimum entity that can be erased by the flash driver). It's the first location after the end of the block.
    uint32 sizeInFlash;         ///< (bytes 72..75) Size of the binary image in flash (i.e. uncompressed). Must be maxEndAddr <= startAddr + sizeInFlash. Include the descriptor, if descriptorInFlash==1.
    uint32 compressedSize;      ///< (bytes 76..79) Size of the compressed file. Always includes the descriptor (because the descriptor is always present in the file). If no compression is used and descriptorInFlash==TRUE, then sizeInFlash=compressedSize.
    uint8 loaderConfig;         ///< (byte 80) Bit0(LSB)='descriptorInFlash', possible values: 0=descriptor_not_copied_in_flash, 1=descriptor_copied_in_flash. (descriptorInFlash==0 not to be implemented). \n Bit1='binaryPresent', if 0 the file doesn't contain the binary image.
    uint8 addrSpId;             ///< (byte 81) Address Space Identifier. Used to identify the target device. Possible values: 0=PPC, 1=DSP.
    uint16 padding2;            ///< (bytes 82..83) Padding
    uint16 hwId;                ///< (bytes 84..85) Used to link the 'release packet' to a compatible hardware. Display type: decimal. \n Possible values: 1=PHET. The bootloader checks the 'hwId' and inhibit the programming if the 'hwId' doesn't match.
    uint16 swId;                ///< (bytes 86..87) Used to identify the type of the sw. Display type: decimal. \n Possible values: 1=PHET.
    uint8 padding1[40];         ///< (bytes 88..127) Padding to reach the size of SEGM_DESCRIPTOR_SIZE=128 bytes.
} FlashSegmentDescriptorType;

/// Descriptor of the 'compressed sub-block'.
/// The descriptor is located at the start of the 'compressed sub-block'.
/// The descriptor is not used if compression is not used.
typedef struct {
    uint32 crc;                         ///< CRC of the 'compressed sub-block' (the field itself (i.e. the first 4 bytes of the 'compressed sub-block') is not included in the calculation of the CRC - see ComputeCrc_Skip4()).
    uint32 comprDataSize;               ///< Size of the binary part of the 'compressed data block'. Max allowed value COMPR_DATA_MAX_SIZE.
    uint32 dataBlockSize;               ///< Size of the uncompressed binary ('dataBlock'). The usual value is DATA_BLOCK_SIZE, except for the last 'data block' which size can be lesser.
    uint32 padding0;                    ///< Padding to reach 16 bytes.
} CompressedDataBlockDescriptorType;

#endif      // _DESCRIPTORS_H_
