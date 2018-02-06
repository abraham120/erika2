
#include "board/ti_tms570/inc/ee_board.h"


/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    17



#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/* Note: LCD is connected to CS2 */
#define LCD_BASE        (EMIF_CS2_ADDRMAP_START)
#define LCD_REG16  (*((volatile unsigned short *)(LCD_BASE  ))) 
#define LCD_DAT16  (*((volatile unsigned short *)(LCD_BASE+04)))
 
static volatile unsigned short TextColor = Black, BackColor = White;


/* Delay in while loop cycles                                                   */
static void delay (int cnt) {

  cnt <<= DELAY_2N;
  while (cnt--);
}



/* Write command to LCD controller                                              */
static __inline void wr_cmd (unsigned char c) {
  LCD_REG16 = c;
}



/* Write data to LCD controller                                                 */
static __inline void wr_dat (unsigned short c) {
  LCD_DAT16 = c;
}



/* Read data from LCD controller                                                */
static __inline unsigned short rd_dat (void) {
  return (LCD_DAT16);
}


/* Write to LCD register                                                        */
static __inline void wr_reg (unsigned char reg, unsigned short val) {
  wr_cmd(reg);
  wr_dat(val);
}



/* Read from LCD register                                                       */
static unsigned short rd_reg (unsigned char reg) {
  wr_cmd(reg);
  return (rd_dat());
}



/* Initialize the Graphic LCD controller                                        */
void DISPLAY_Init (void) { 
  static unsigned short DriverCode;

  DriverCode = rd_reg(0x00);

  /* Start Initial Sequence --------------------------------------------------*/
//wr_reg(0xE5, 0x8000);                 /* Set the internal vcore voltage     */
  wr_reg(0x00, 0x0001);                 /* Start internal OSC                 */
  wr_reg(0x01, 0x0000);                 /* Clear SS and SM bit for vertical   */
  wr_reg(0x02, 0x0700);                 /* Set 1 line inversion               */
  wr_reg(0x04, 0x0000);                 /* Resize register                    */
  wr_reg(0x08, 0x0207);                 /* 2 lines front, 7 back porch        */
  wr_reg(0x09, 0x0000);                 /* Set non-disp area refresh cyc ISC  */
  wr_reg(0x0A, 0x0000);                 /* FMARK function                     */
  wr_reg(0x0C, 0x0000);                 /* RGB interface setting              */
  wr_reg(0x0D, 0x0000);                 /* Frame marker Position              */
  wr_reg(0x0F, 0x0000);                 /* RGB interface polarity             */

  /* Power On sequence -------------------------------------------------------*/
  wr_reg(0x10, 0x0000);                 /* Reset Power Control 1              */
  wr_reg(0x11, 0x0000);                 /* Reset Power Control 2              */
  wr_reg(0x12, 0x0000);                 /* Reset Power Control 3              */
  wr_reg(0x13, 0x0000);                 /* Reset Power Control 4              */
  delay(20);                            /* Discharge cap power voltage (200ms)*/
  wr_reg(0x10, 0x12B0);                 /* SAP, BT[3:0], AP, DSTB, SLP, STB   */
  wr_reg(0x11, 0x0007);                 /* DC1[2:0], DC0[2:0], VC[2:0]        */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x12, 0x01BD);                 /* VREG1OUT voltage                   */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x13, 0x1400);                 /* VDV[4:0] for VCOM amplitude        */
  wr_reg(0x29, 0x000E);                 /* VCM[4:0] for VCOMH                 */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x20, 0x0000);                 /* GRAM horizontal Address            */
  wr_reg(0x21, 0x0000);                 /* GRAM Vertical Address              */

  /* Adjust the Gamma Curve --------------------------------------------------*/
  if (DriverCode == 0x5408) {           /* LCD with touch                     */
    wr_reg(0x30, 0x0B0D);
    wr_reg(0x31, 0x1923);
    wr_reg(0x32, 0x1C26);
    wr_reg(0x33, 0x261C);
    wr_reg(0x34, 0x2419);
    wr_reg(0x35, 0x0D0B);
    wr_reg(0x36, 0x1006);
    wr_reg(0x37, 0x0610);
    wr_reg(0x38, 0x0706);
    wr_reg(0x39, 0x0304);
    wr_reg(0x3A, 0x0E05);
    wr_reg(0x3B, 0x0E01);
    wr_reg(0x3C, 0x010E);
    wr_reg(0x3D, 0x050E);
    wr_reg(0x3E, 0x0403);
    wr_reg(0x3F, 0x0607);
  }
  if (DriverCode == 0xC990) {           /* LCD without touch                  */
    wr_reg(0x30, 0x0006);
    wr_reg(0x31, 0x0101);
    wr_reg(0x32, 0x0003);
    wr_reg(0x35, 0x0106);
    wr_reg(0x36, 0x0B02);
    wr_reg(0x37, 0x0302);
    wr_reg(0x38, 0x0707);
    wr_reg(0x39, 0x0007);
    wr_reg(0x3C, 0x0600);
    wr_reg(0x3D, 0x020B);
  }
  
  /* Set GRAM area -----------------------------------------------------------*/
  wr_reg(0x50, 0x0000);                 /* Horizontal GRAM Start Address      */
  wr_reg(0x51, (HEIGHT-1));             /* Horizontal GRAM End   Address      */
  wr_reg(0x52, 0x0000);                 /* Vertical   GRAM Start Address      */
  wr_reg(0x53, (WIDTH-1));              /* Vertical   GRAM End   Address      */
  if (DriverCode == 0x5408)             /* LCD with touch                     */
    wr_reg(0x60, 0xA700);               /* Gate Scan Line    A700 -> 2700 horizontal orientation */
  if (DriverCode == 0xC990)             /* LCD without touch                  */
    wr_reg(0x60, 0x2700);               /* Gate Scan Line                     */
  wr_reg(0x61, 0x0001);                 /* NDL,VLE, REV                       */
  wr_reg(0x6A, 0x0000);                 /* Set scrolling line                 */

  /* Partial Display Control -------------------------------------------------*/
  wr_reg(0x80, 0x0000);
  wr_reg(0x81, 0x0000);
  wr_reg(0x82, 0x0000);
  wr_reg(0x83, 0x0000);
  wr_reg(0x84, 0x0000);
  wr_reg(0x85, 0x0000);

  /* Panel Control -----------------------------------------------------------*/
  wr_reg(0x90, 0x0010);
  wr_reg(0x92, 0x0000);
  wr_reg(0x93, 0x0003);
  wr_reg(0x95, 0x0110);
  wr_reg(0x97, 0x0000);
  wr_reg(0x98, 0x0000);

  /* Set GRAM write direction and BGR = 1
     I/D=10 (Horizontal : increment, Vertical : increment)
     AM=1 (address is updated in vertical writing direction)                  */
  wr_reg(0x03, 0x1038);                 /* TRIREG=0 -> 65536 colors R5G6B5 bitmap format */

  wr_reg(0x07, 0x0137);                 /* display ON          */
}



/* Set draw window region to whole screen                                       */
void DISPLAY_WindowMax (void) {
  wr_reg(0x50, 0);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, HEIGHT-1);               /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, 0);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, WIDTH-1);                /* Vertical   GRAM End   Address (-1) */
}



/* Draw a pixel in foreground color                                             */
void DISPLAY_PutPixel (unsigned int x, unsigned int y) {
  wr_reg(0x20, y);
  wr_reg(0x21, x);
  wr_cmd(0x22);
  wr_dat(TextColor);
}



/* Set foreground color                                                         */
void DISPLAY_SetTextColor (unsigned short color) {
  TextColor = color;
}



/* Set background color                                                         */
void DISPLAY_SetBackColor (unsigned short color) {
  BackColor = color;
}



/* Clear display                                                                */
void DISPLAY_Clear (unsigned short color) {
  unsigned int   i;

  DISPLAY_WindowMax();

  wr_reg(0x20, 0);
  wr_reg(0x21, 0);
  wr_cmd(0x22);
  for(i = 0; i < (WIDTH*HEIGHT); i++)
    wr_dat(color);
}



/* Draw character on given position                                             */
void DISPLAY_DrawChar(unsigned int x, unsigned int y, unsigned short *c) {
  int i, j;
	
  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+CHAR_H-1);             /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+CHAR_W-1);             /* Vertical   GRAM End   Address (-1) */
  wr_reg(0x20, y);
  wr_reg(0x21, x);
  wr_cmd(0x22);              /* Prepare to write GRAM */
  for (j = 0; j < CHAR_H; j++) {
    for (i = 0; i < CHAR_W; i++) {
      if((*c & (1 << i)) == 0x00) {
        wr_dat(BackColor);
      } else {
        wr_dat(TextColor);
      }
    }
    c++;
  }
}



/* Disply character on given line                                               */
void DISPLAY_DisplayChar (unsigned int ln, unsigned int col, unsigned char c) {
  c -= 32;
  DISPLAY_DrawChar(col * CHAR_W, ln * CHAR_H, &Font[c * CHAR_H]);
}



/* Disply string on given line                                                  */
void DISPLAY_DisplayString (unsigned int ln, unsigned int col, char *s) {
  DISPLAY_WindowMax();
  while (*s) {
    DISPLAY_DisplayChar(ln, col++, *s++);
  }
}



/* Clear given line                                                             */
void DISPLAY_ClearLn (unsigned int ln) {
  DISPLAY_WindowMax();
  DISPLAY_DisplayString(ln, 0, "                    ");
}


/* Draw bargraph                                                                */
void DISPLAY_Bargraph (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val) {
  int i,j;

  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+CHAR_H-1);             /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

//  val = (val * w) >> 10;                /* Scale value = 0 - 1024             */
  wr_reg(0x20, y);
  wr_reg(0x21, x);
  wr_cmd(0x22);
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if(j >= val) {
        wr_dat(BackColor);
      } else {
        wr_dat(TextColor);
      }
    }
  }
}



/* Display graphical bitmap image at position x horizontally and y vertically   */
void DISPLAY_Bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char const *bitmap) {
  unsigned int   i;
  unsigned int   len = w*h;
  unsigned short *bitmap_ptr = (unsigned short *)bitmap;

  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  wr_reg(0x20, y);
  wr_reg(0x21, x);

  wr_cmd(0x22);
  for (i = 0; i < len; i++) {
    wr_dat(*bitmap_ptr++);
  }
}



/* Display graphical bmp file image at position x horizontally and y vertically */
void DISPLAY_Bmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char const *bmp) {
  unsigned int    i, j;
  unsigned short pixel;

  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  wr_cmd(0x22);
  bmp += (h-1)*w*2;
  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      pixel  = *bmp++;                  // BMP is stored in little endian format
      pixel |= (*bmp++) << 8;
      wr_dat(pixel);
    }
    bmp -= 2*2*w;
  }
}

/******************************************************************************/
