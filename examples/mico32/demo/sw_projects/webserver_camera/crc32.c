/* 
  crc32.c -- compute the CRC-32 of a data stream
  Copyright (C) 1995-2006, 2010 Mark Adler
    
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3  This notice may not be removed or altered from any source distribution.

  Jean-loup Gailly        Mark Adler
  jloup@gzip.org          madler@alumni.caltech.edu
 	
  Thanks to Rodney Brown <rbrown64@csc.com.au> for his contribution of faster
  CRC methods: exclusive-oring 32 bits of data at a time, and pre-computing
  tables for updating the shift register in one step with three exclusive-ors
  instead of four steps with four exclusive-ors.  This results in about a
  factor of two increase in speed on a Power PC G4 (PPC7455) using gcc -O3.
*/

/*
 * Copyright: 2010, Evidence Srl
 * Modified by: Alessandro Paolinelli
 * Description: customized zlib crc32 for our application.
 */
 
#define Z_NULL  0
#define local static
#define TBLS 1

local volatile int crc_table_empty = 1;
local unsigned crc_table[TBLS][256];
local void make_crc_table();

/*
  Generate tables for a byte-wise 32-bit CRC calculation on the polynomial:
  x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1.

  Polynomials over GF(2) are represented in binary, one bit per coefficient,
  with the lowest powers in the most significant bit.  Then adding polynomials
  is just exclusive-or, and multiplying a polynomial by x is a right shift by
  one.  If we call the above polynomial p, and represent a byte as the
  polynomial q, also with the lowest power in the most significant bit (so the
  byte 0xb1 is the polynomial x^7+x^3+x+1), then the CRC is (q*x^32) mod p,
  where a mod b means the remainder after dividing a by b.

  This calculation is done using the shift-register method of multiplying and
  taking the remainder.  The register is initialized to zero, and for each
  incoming bit, x^32 is added mod p to the register if the bit is a one (where
  x^32 mod p is p+x^32 = x^26+...+1), and the register is multiplied mod p by
  x (which is shifting right by one and adding x^32 mod p if the bit shifted
  out is a one).  We start with the highest power (least significant bit) of
  q and repeat for all eight bits of q.

  The first table is simply the CRC of all possible eight bit values.  This is
  all the information needed to generate CRCs on data a byte at a time for all
  combinations of CRC register values and incoming bytes.  The remaining tables
  allow for word-at-a-time CRC calculation for both big-endian and little-
  endian machines, where a word is four bytes.
*/
local void make_crc_table()
{
    unsigned long c;
    int n, k;
    unsigned long poly;                 /* polynomial exclusive-or pattern */
    /* terms of polynomial defining this crc (except x^32): */
    static const unsigned char p[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26};

    /* make exclusive-or pattern from polynomial (0xedb88320UL) */
    poly = 0UL;
    for (n = 0; n < sizeof(p)/sizeof(unsigned char); n++)
        poly |= 1UL << (31 - p[n]);

    /* generate a crc for every 8-bit value */
    for (n = 0; n < 256; n++) {
        c = (unsigned long)n;
        for (k = 0; k < 8; k++)
            c = c & 1 ? poly ^ (c >> 1) : c >> 1;
        crc_table[0][n] = c;
    }
    crc_table_empty = 0;
}

/* ========================================================================= */
#define DO1 crc = crc_table[0][((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8)
#define DO8 DO1; DO1; DO1; DO1; DO1; DO1; DO1; DO1

/* ========================================================================= */
unsigned crc32(unsigned crc,unsigned char *buf, unsigned len)
{
    if (buf == Z_NULL) return 0UL;

    if (crc_table_empty)
        make_crc_table();

    crc = crc ^ 0xffffffffUL;
    while (len >= 8) {
        DO8;
        len -= 8;
    }
    if (len) do {
        DO1;
    } while (--len);
    return crc ^ 0xffffffffUL;
}