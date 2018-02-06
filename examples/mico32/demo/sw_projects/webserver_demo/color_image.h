/*
Copyright (C) 2010 - Bernardo Dal Seno , Alessandro Paolinelli
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/**
 *\file color_image.h
 *\author Bernardo Dal Seno , Alessandro Paolinelli
 *\brief  Conversion YUV 2 RGB and PNG build ad-hoc for camera image
 */
 
#ifndef COLOR_IMAGE_H
#define COLOR_IMAGE_H

#include <string.h>

/*
 * CAMERA FEATURES 
 */

#define CAMERA_RES_AVAIL	3
#define CAMERA_RES_BASE		160
/*
 * YUV 2 RGB DEFINES
 */

#define RGB_A	3
#define YCRYCB	2

#define FLOAT2INT	65536
#define R  ((int)(1.371F * FLOAT2INT))
#define G1 ((int)(0.698F * FLOAT2INT))
#define G2 ((int)(0.336F * FLOAT2INT))
#define B  ((int)(1.732F * FLOAT2INT))

/*
 * RGB 2 PNG DEFINES
 */

#define PNG_SIGNATURE_SIZE		8
#define PNG_CHUNK_LENGTH_FIELD	4
#define PNG_CHUNK_TYPE_FIELD	4
#define PNG_CHUNK_CRC32_FIELD	4
#define PNG_CHUNK_COMMON_SIZE	(PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD+PNG_CHUNK_CRC32_FIELD)
#define PNG_IHDR_DATA_FIELD		13
#define PNG_IEND_DATA_FIELD		0

#define PNG_IHDR_CHUNK_SIZE		(PNG_CHUNK_COMMON_SIZE+PNG_IHDR_DATA_FIELD)
#define PNG_IDAT_CHUNK_SIZE		PNG_CHUNK_COMMON_SIZE
#define PNG_IEND_CHUNK_SIZE		(PNG_CHUNK_COMMON_SIZE+PNG_IEND_DATA_FIELD)

/* Max Width Avalilable */
#define PNG_IMG_WIDTH			640
#define PNG_IMG_WIDTH_DEFAULT	640
#define PNG_IMG_HEIGHT			((PNG_IMG_WIDTH/4)*3)
#define PNG_IMG_BIT_DEPTH		8
#define PNG_IMG_COLOR_TYPE		2
#define PNG_IMG_COMPRESSION		0		
#define PNG_IMG_FILTER			0
#define PNG_IMG_INTERLACE		0

#define PNG_FILTER_ALG			0	/* none */

#define PNG_ZLIB_HEADER			2
#define PNG_ZLIB_BLOCKDEF		5
#define PNG_ZLIB_BLOCKDIM		65535
#define PNG_ZLIB_TRAILER		4

#define PNG_SCANLINES_SIZE(w,h) ((unsigned int) (w*h*RGB_A)+h)
#define PNG_ZLIB_BLOCKNUM(w,h)  (((unsigned int)((w*h*RGB_A)+h)/(PNG_ZLIB_BLOCKDIM+1)) + 1) 
#define PNG_ZLIB_DATA(bn)		(PNG_ZLIB_HEADER+(PNG_ZLIB_BLOCKDEF*bn)+PNG_ZLIB_TRAILER)

typedef unsigned char UChar_t;

void color_image_rgb2png_init();
unsigned char color_image_yuv2png(const UChar_t yuvimage[],	unsigned image_length, unsigned image_width);

#endif