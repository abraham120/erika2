#ifndef _DISPLAY_H
#define _DISPLAY_H

                            
/* DISPLAY RGB color definitions                                                 */
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */


extern void DISPLAY_Init           (void);
extern void DISPLAY_WindowMax      (void);
extern void DISPLAY_PutPixel       (unsigned int x, unsigned int y);
extern void DISPLAY_SetTextColor   (unsigned short color);
extern void DISPLAY_SetBackColor   (unsigned short color);
extern void DISPLAY_Clear          (unsigned short color);
extern void DISPLAY_DrawChar       (unsigned int x, unsigned int y, unsigned short *c);
extern void DISPLAY_DisplayChar    (unsigned int ln, unsigned int col, unsigned char  c);
extern void DISPLAY_DisplayString  (unsigned int ln, unsigned int col, char *s);
extern void DISPLAY_ClearLn        (unsigned int ln);
extern void DISPLAY_Bargraph       (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val);
extern void DISPLAY_Bitmap         (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char const *bitmap);
extern void DISPLAY_Bmp            (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char const *bmp);

#endif /* _DISPLAY_H */
