#include "color_image.h"
#include <stdlib.h>

extern void myprintf(const char *format, ...);

/*
 *	CRC32
 */
#define CRC32_START 0UL
extern unsigned crc32(unsigned crc,unsigned char *buf, unsigned len);
/*
 *	ADLER32
 */
extern unsigned adler32(unsigned adler,unsigned char* buf, unsigned len);

/*8 bytes PNG signature*/
static const unsigned char png_signature[PNG_SIGNATURE_SIZE] =
    {137, 80, 78, 71, 13, 10, 26, 10};
#pragma pack(1)
typedef unsigned char length_t[PNG_CHUNK_LENGTH_FIELD];
typedef unsigned char type_t[PNG_CHUNK_TYPE_FIELD];
typedef unsigned char crc32_t[PNG_CHUNK_CRC32_FIELD];
								
typedef struct
{
	length_t length;
	type_t type;
}png_chunk_lt;

typedef struct
{
	png_chunk_lt lt;
	unsigned char data[PNG_IHDR_DATA_FIELD];
	crc32_t crc32;
}png_ihdr;

typedef struct
{
	png_chunk_lt lt;
	crc32_t crc32;
}png_iend;

png_ihdr png_ihdr_chunk_array[CAMERA_RES_AVAIL];
png_chunk_lt png_idat_chunk_array[CAMERA_RES_AVAIL];
png_iend png_iend_chunk;
#pragma pack()

unsigned int png_width_avail[CAMERA_RES_AVAIL] = {160,320,640};
unsigned int png_height_avail[CAMERA_RES_AVAIL];
unsigned int png_size_avail[CAMERA_RES_AVAIL];

#define EXTERNAL_RAM __attribute__((section (".graph")))
unsigned char EXTERNAL_RAM png_img[PNG_SIGNATURE_SIZE+
					  PNG_IHDR_CHUNK_SIZE+
					  /* Scanlines need a byte more for each row */
					  PNG_IDAT_CHUNK_SIZE+PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(PNG_IMG_WIDTH,PNG_IMG_HEIGHT))+
					  (PNG_IMG_HEIGHT*PNG_IMG_WIDTH*RGB_A)+PNG_IMG_HEIGHT+
					  PNG_IEND_CHUNK_SIZE];
					  
unsigned char EXTERNAL_RAM camera_image[PNG_IMG_WIDTH*PNG_IMG_HEIGHT*YCRYCB];
						
static inline void color_image_32bit(unsigned char* buffer, unsigned value)
{
  memcpy(buffer,&value,4);
}

void color_image_rgb2png_init()
{
	unsigned int i,j,crc32_code;
	
	/* Png Signature */
	for(i=0;i<PNG_SIGNATURE_SIZE;i++) png_img[i] = png_signature[i];
	
	for(j=0;j<CAMERA_RES_AVAIL;j++){
		/* Png IHDR Chunk */
		/* length */
		color_image_32bit(png_ihdr_chunk_array[j].lt.length,PNG_IHDR_DATA_FIELD);
	
		/* type */
		png_ihdr_chunk_array[j].lt.type[0] = 'I';
		png_ihdr_chunk_array[j].lt.type[1] = 'H';
		png_ihdr_chunk_array[j].lt.type[2] = 'D';
		png_ihdr_chunk_array[j].lt.type[3] = 'R';

		/* data */
		/* width */
		color_image_32bit(png_ihdr_chunk_array[j].data,png_width_avail[j]);
		
		/* height */
	  	png_height_avail[j] = ((png_width_avail[j]/4)*3);
	  	color_image_32bit(&png_ihdr_chunk_array[j].data[4],png_height_avail[j]);
	  	
	 	png_ihdr_chunk_array[j].data[8]=PNG_IMG_BIT_DEPTH;		/*bit depth*/
		png_ihdr_chunk_array[j].data[9]=PNG_IMG_COLOR_TYPE;		/*color type*/	
		png_ihdr_chunk_array[j].data[10]=PNG_IMG_COMPRESSION;	/*compression method*/
	 	png_ihdr_chunk_array[j].data[11]=PNG_IMG_FILTER;		/*filter method*/
	 	png_ihdr_chunk_array[j].data[12]=PNG_IMG_INTERLACE;		/*interlace method*/
	 	
	 	crc32_code = crc32(	CRC32_START,
	 						&png_ihdr_chunk_array[j].lt.type[0],
	 						PNG_CHUNK_TYPE_FIELD+PNG_IHDR_DATA_FIELD);
		color_image_32bit(png_ihdr_chunk_array[j].crc32,crc32_code); 
		
		/* Png IDAT Chunk */
		/* length */
		color_image_32bit(	png_idat_chunk_array[j].length,
							PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(png_width_avail[j],png_height_avail[j]))+
							PNG_SCANLINES_SIZE(png_width_avail[j],png_height_avail[j]));
		
		/* type */
		png_idat_chunk_array[j].type[0] = 'I';
		png_idat_chunk_array[j].type[1] = 'D';
		png_idat_chunk_array[j].type[2] = 'A';
		png_idat_chunk_array[j].type[3] = 'T';
		
		png_size_avail[j] = PNG_SIGNATURE_SIZE+PNG_IHDR_CHUNK_SIZE+ 
							PNG_IDAT_CHUNK_SIZE+
							PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(png_width_avail[j],png_height_avail[j]))+
							PNG_SCANLINES_SIZE(png_width_avail[j],png_height_avail[j])+
							PNG_IEND_CHUNK_SIZE;
	}
	
   	/* Png IEND Chunk */
	/* length */
	color_image_32bit(png_iend_chunk.lt.length,0);
    
    /* type */
	png_iend_chunk.lt.type[0]='I';
	png_iend_chunk.lt.type[1]='E';
	png_iend_chunk.lt.type[2]='N';
	png_iend_chunk.lt.type[3]='D';
	
	crc32_code = crc32(	CRC32_START,
						&png_iend_chunk.lt.type[0],
						PNG_CHUNK_TYPE_FIELD+PNG_IEND_DATA_FIELD);
  	color_image_32bit(png_iend_chunk.crc32,crc32_code); /*crc32*/
}

static inline void color_image_zlibdata(unsigned int png_width,unsigned int png_height)
{
	unsigned int i,j,k;
	/* deflate data */
	unsigned BFINAL, BTYPE, LEN, NLEN;
	/*zlib data: 1 byte CMF (CM+CINFO), 1 byte FLG, deflate data, 4 byte ADLER32 checksum of the Decompressed data*/
	unsigned CMF = 120; /*0b01111000: CM 8, CINFO 7. With CINFO 7, any window size up to 32768 can be used.*/
	unsigned FLEVEL = 0;
	unsigned FDICT = 0;
	unsigned CMFFLG = 256 * CMF + FDICT * 32 + FLEVEL * 64;
	unsigned FCHECK = 31 - CMFFLG % 31;
	CMFFLG += FCHECK;
	unsigned char firstbyte,*deflate_block_ptr;
	
	/* zlib index */
	i = PNG_SIGNATURE_SIZE+PNG_IHDR_CHUNK_SIZE+
		PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD;
	
	/* zlib data */
	png_img[i++]=(unsigned char)(CMFFLG / 256);
  	png_img[i++]=(unsigned char)(CMFFLG % 256);
  	
  	/* deflate data */
  	for(k = 0 , j = 0; k < PNG_ZLIB_BLOCKNUM(png_width,png_height); k++)
  	{
  		deflate_block_ptr = &png_img[i+k*(PNG_ZLIB_BLOCKDIM+PNG_ZLIB_BLOCKDEF)];
  		
        BFINAL = (k == PNG_ZLIB_BLOCKNUM(png_width,png_height) - 1);
	    BTYPE = 0;
	    
	    firstbyte = (unsigned char)(BFINAL + ((BTYPE & 1) << 1) + ((BTYPE & 2) << 1));
    	*deflate_block_ptr=firstbyte;
    	deflate_block_ptr++;
    	
    	LEN = PNG_ZLIB_BLOCKDIM;
    	if(BFINAL) LEN =(PNG_SCANLINES_SIZE(png_width,png_height)) - 
    					((PNG_ZLIB_BLOCKNUM(png_width,png_height) - 1)*PNG_ZLIB_BLOCKDIM);
    	NLEN = PNG_ZLIB_BLOCKDIM - LEN;
    	
    	*deflate_block_ptr = (unsigned char)(LEN % 256);
    	deflate_block_ptr++;
    	*deflate_block_ptr = (unsigned char)(LEN / 256);
    	deflate_block_ptr++;
    	*deflate_block_ptr = (unsigned char)(NLEN % 256);
    	deflate_block_ptr++;
    	*deflate_block_ptr = (unsigned char)(NLEN / 256);
    }

}

static inline unsigned char color_image_rgb2png(unsigned int png_width,unsigned int png_height)
{
	unsigned int adler32_code,crc32_code,i,j,iend_chunk_index,chunk_array_index;
	
	for(chunk_array_index=0;chunk_array_index<CAMERA_RES_AVAIL;chunk_array_index++){
		if(png_width==png_width_avail[chunk_array_index]) break;
	}
	
	/* IHDR */
	memcpy(	&png_img[PNG_SIGNATURE_SIZE],
			&png_ihdr_chunk_array[chunk_array_index],
			PNG_IHDR_CHUNK_SIZE);
  	
  	/* IDAT */
  	memcpy(	&png_img[PNG_SIGNATURE_SIZE+PNG_IHDR_CHUNK_SIZE],
  			&png_idat_chunk_array[chunk_array_index],
  			PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD);
  			
  	color_image_zlibdata(png_width,png_height);
	
  	/* IEND */
	iend_chunk_index = 	PNG_SIGNATURE_SIZE+PNG_IHDR_CHUNK_SIZE+PNG_IDAT_CHUNK_SIZE+
					 	PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(png_width,png_height))+
					 	PNG_SCANLINES_SIZE(png_width,png_height);
					 	
	memcpy(&png_img[iend_chunk_index],&png_iend_chunk,PNG_IEND_CHUNK_SIZE);
	
	/*adler32*/
	adler32_code = 1L;
	for(i = 0 , j = PNG_ZLIB_BLOCKDIM; i < PNG_ZLIB_BLOCKNUM(png_width,png_height); i++)
	{
		
		if(i==PNG_ZLIB_BLOCKNUM(png_width,png_height)-1)
			j = (PNG_SCANLINES_SIZE(png_width,png_height)) - 
				((PNG_ZLIB_BLOCKNUM(png_width,png_height) - 1)*PNG_ZLIB_BLOCKDIM);
    	
		
		adler32_code = adler32(	adler32_code,
						  		&png_img[PNG_SIGNATURE_SIZE+
									 	PNG_IHDR_CHUNK_SIZE+
								 		PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD+
								 		PNG_ZLIB_HEADER+(PNG_ZLIB_BLOCKDEF*(i+1))+
								 		(i*PNG_ZLIB_BLOCKDIM)],j);
	}
	
	color_image_32bit(&png_img[PNG_SIGNATURE_SIZE+
							  PNG_IHDR_CHUNK_SIZE+
							  PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD+
							  PNG_ZLIB_HEADER+(PNG_ZLIB_BLOCKDEF*PNG_ZLIB_BLOCKNUM(png_width,png_height))+
							  PNG_SCANLINES_SIZE(png_width,png_height)]
					 ,adler32_code);
	
	/*crc32*/
	crc32_code = crc32(	CRC32_START,
						&png_img[PNG_SIGNATURE_SIZE+
						PNG_IHDR_CHUNK_SIZE+
						PNG_CHUNK_LENGTH_FIELD],
			  		  	PNG_CHUNK_TYPE_FIELD+
			  		  	PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(png_width,png_height))+
					 	PNG_SCANLINES_SIZE(png_width,png_height));
  
  	color_image_32bit(&png_img[PNG_SIGNATURE_SIZE+
							  PNG_IHDR_CHUNK_SIZE+
							  PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD+
							  PNG_ZLIB_DATA(PNG_ZLIB_BLOCKNUM(png_width,png_height)) +
					 		  PNG_SCANLINES_SIZE(png_width,png_height)]
					 ,crc32_code); /*crc32*/
					 
	return chunk_array_index;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* / YUV2RGB                                                                  / */
/* ////////////////////////////////////////////////////////////////////////// */

static inline UChar_t color_image_saturate(int col)
{
	if (col < 0)
		return 0;
	else if (col > 255)
		return 255;
	else
		return col;
}

static inline void check_new_block(UChar_t *rgb,unsigned int *main_index,unsigned char *rgb_index)
{
	if (!((*main_index+*rgb_index)%(PNG_ZLIB_BLOCKDIM+PNG_ZLIB_BLOCKDEF))){
		// Jump deflate block info
		*rgb_index+=PNG_ZLIB_BLOCKDEF;
		*main_index+=PNG_ZLIB_BLOCKDEF;
	}
}

static inline void color_image_yuv2rgb_pair(UChar_t *rgb, UChar_t y1,UChar_t y2,UChar_t cr, UChar_t cb,unsigned int *index)
{
	unsigned char rgb_index=0;
	int r, g, b;
	
	r = R * ((int)cr - 128); // red
	g = -1 * (G1 * ((int)cr - 128) + G2 * ((int)cb - 128)); // green
	b = B * ((int)cb - 128); // blue
	
	r /= FLOAT2INT;
	g /= FLOAT2INT;
	b /= FLOAT2INT;
		
	rgb[rgb_index++] = color_image_saturate(r+y1);
	check_new_block(rgb,index,&rgb_index);
	
	rgb[rgb_index++] = color_image_saturate(g+y1);
	check_new_block(rgb,index,&rgb_index);
	
	rgb[rgb_index++] = color_image_saturate(b+y1);
	check_new_block(rgb,index,&rgb_index);
	if(RGB_A == 4)
		rgb[rgb_index++] = 255; // alpha channel
		
	rgb[rgb_index++] = color_image_saturate(r+y2);
	check_new_block(rgb,index,&rgb_index);
	
	rgb[rgb_index++] = color_image_saturate(g+y2);
	check_new_block(rgb,index,&rgb_index);
	
	rgb[rgb_index++] = color_image_saturate(b+y2);
	check_new_block(rgb,index,&rgb_index);
	if(RGB_A == 4)
		rgb[rgb_index++] = 255; // alpha channel	
}


/** Convert an image from YUV 4:2:2 to rgb.
 *
 * The returned array contains r,g,b triples and must be freed with delete[].
 */
static inline void color_image_yuv2rgb(const UChar_t yuvimage[],unsigned int image_length,unsigned int image_width)
{
	unsigned int k,j;
	unsigned char *deflate_block_ptr;
	
	j  = PNG_SIGNATURE_SIZE+PNG_IHDR_CHUNK_SIZE+
		 PNG_CHUNK_LENGTH_FIELD+PNG_CHUNK_TYPE_FIELD+
		 PNG_ZLIB_HEADER;
	
	deflate_block_ptr = &png_img[j];
	
	for (k = 0, j = PNG_ZLIB_BLOCKDEF; k < image_length/2; k += 2 , j+=(RGB_A*2)) {
		UChar_t y1, y2, cr, cb;
		y1 = yuvimage[k*2];
		cb = yuvimage[k*2+1];
		y2 = yuvimage[(k+1)*2];
		cr = yuvimage[(k+1)*2+1];
		
		if (!(k%image_width)){
			// Scanlines byte extra
			deflate_block_ptr[j++]=PNG_FILTER_ALG;
		}
		
		color_image_yuv2rgb_pair(&deflate_block_ptr[j], y1,y2, cr, cb, &j);
	}
}
/* ////////////////////////////////////////////////////////////////////////// */
/* / YUV 2 PNG                                                                  / */
/* ////////////////////////////////////////////////////////////////////////// */

unsigned char color_image_yuv2png(const UChar_t yuvimage[],	unsigned image_length, unsigned image_width)
{
	color_image_yuv2rgb(yuvimage,image_length,image_width);
	return color_image_rgb2png(image_width,(image_length/2)/image_width);
}
