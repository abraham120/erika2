/******************************************************************************/
/* DISCLAIMER                                                                 */
/* This software is supplied by Renesas Electronics Corporation and is only   */
/* intended for use with Renesas products. No other uses are authorized.This  */
/* software is owned by Renesas Electronics Corporation and is protected      */
/* under all applicable laws, including copyright laws.                       */
/* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES          */
/* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING  */
/* BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR */
/* PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY           */
/* DISCLAIMED.                                                                */
/* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS     */
/* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE       */
/* LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL      */
/* DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS    */
/* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.           */
/* Renesas reserves the right, without notice, to make changes to this        */
/* software and to discontinue the availability of this software.             */
/* By using this software, you agree to the additional terms and conditions   */
/* found by accessing the following link:                                     */
/* http://www.renesas.com/disclaimer                                          */
/*                                                                            */
/* Device     : RH/RH850G3K/R7F701057                                         */
/* File Name  : dr7f701057.dvf.h                                              */
/* Abstract   : Definition of I/O Register                                    */
/* History    : V1.10  [Device File version]                                  */
/* Options    : -ghs_pragma_io=on -anonymous=on -indent=4 -structure=on -type */
/*              def=on -def=on -autosar=on -modulearray=on -const=on -bitfiel */
/*              d=on -bitsfr=on -df=.\dr7f701057.dvf -o=..\output\update\inc_ */
/*              ghs\dr7f701057.dvf.h                                          */
/* Date       : 19.02.2015                                                    */
/* Version    : V1.04.00.04  [df2iodef.exe version]                           */
/* This is a typical example.                                                 */
/*                                                                            */
/******************************************************************************/
#ifndef __R7F701057IODEFINE_HEADER__
#define __R7F701057IODEFINE_HEADER__

#ifndef _IODEF_AUTOSAR_TYPEDEF_
#define _IODEF_AUTOSAR_TYPEDEF_
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
#endif

#ifndef _GHS_PRAGMA_IO_TYPEDEF_
#define _GHS_PRAGMA_IO_TYPEDEF_
#define PRAGMA(x) _Pragma(#x)
#define __READ volatile const
#define __WRITE volatile
#define __READ_WRITE volatile
#define __IOREG(reg, addr, attrib, type) PRAGMA(ghs io reg addr) \
extern attrib type reg;
#define __IOREGARRAY(reg, array, addr, attrib, type) PRAGMA(ghs io reg addr) \
extern attrib type reg[array];
#endif

typedef struct
{
    uint8 bit00:1;
    uint8 bit01:1;
    uint8 bit02:1;
    uint8 bit03:1;
    uint8 bit04:1;
    uint8 bit05:1;
    uint8 bit06:1;
    uint8 bit07:1;
} __bitf_T;

#define  L 0
#define  H 1
#define LL 0
#define LH 1
#define HL 2
#define HH 3

typedef struct 
{                                                          /* Bit Access       */
    uint8  AAS0:1;                                         /* AAS0             */
    uint8  AAS1:1;                                         /* AAS1             */
    uint8  AAS2:1;                                         /* AAS2             */
    uint8  GCA:1;                                          /* GCA              */
    uint8  :1;                                             /* Reserved Bits    */
    uint8  DID:1;                                          /* DID              */
    uint8  :2;                                             /* Reserved Bits    */
    uint8  :8;                                             /* Reserved Bits    */
    uint8  :8;                                             /* Reserved Bits    */
    uint8  :8;                                             /* Reserved Bits    */
} __type0;
typedef struct 
{                                                          /* Bit Access       */
    uint8  TMOF:1;                                         /* TMOF             */
    uint8  AL:1;                                           /* AL               */
    uint8  START:1;                                        /* START            */
    uint8  STOP:1;                                         /* STOP             */
    uint8  NACKF:1;                                        /* NACKF            */
    uint8  RDRF:1;                                         /* RDRF             */
    uint8  TEND:1;                                         /* TEND             */
    const uint8  TDRE:1;                                   /* TDRE             */
    uint8  :8;                                             /* Reserved Bits    */
    uint8  :8;                                             /* Reserved Bits    */
    uint8  :8;                                             /* Reserved Bits    */
} __type1;
typedef struct 
{                                                          /* Bit Access       */
    uint8  MBS:1;                                          /* MBS              */
    uint8  JOBE:1;                                         /* JOBE             */
    uint8  :3;                                             /* Reserved Bits    */
    uint8  RXE:1;                                          /* RXE              */
    uint8  TXE:1;                                          /* TXE              */
    uint8  PWR:1;                                          /* PWR              */
} __type2;
typedef struct 
{                                                          /* Bit Access       */
    uint8  :7;                                             /* Reserved Bits    */
    uint8  SVSDIS:1;                                       /* SVSDIS           */
} __type3;
typedef struct 
{                                                          /* Bit Access       */
    uint8  :5;                                             /* Reserved Bits    */
    uint8  RXE:1;                                          /* RXE              */
    uint8  TXE:1;                                          /* TXE              */
    uint8  PWR:1;                                          /* PWR              */
} __type4;
typedef struct 
{                                                          /* Bit Access       */
    uint8  SCE:1;                                          /* SCE              */
    uint8  :7;                                             /* Reserved Bits    */
} __type5;
typedef struct 
{                                                          /* Bit Access       */
    uint8  :4;                                             /* Reserved Bits    */
    uint8  SLSB:1;                                         /* SLSB             */
    uint8  AMPM:1;                                         /* AMPM             */
    const uint8  CEST:1;                                   /* CEST             */
    uint8  CE:1;                                           /* CE               */
} __type6;
typedef struct 
{                                                          /* Bit Access       */
    uint8  CT0:1;                                          /* CT0              */
    uint8  CT1:1;                                          /* CT1              */
    uint8  CT2:1;                                          /* CT2              */
    uint8  EN1S:1;                                         /* EN1S             */
    uint8  ENALM:1;                                        /* ENALM            */
    uint8  EN1HZ:1;                                        /* EN1HZ            */
    uint8  :2;                                             /* Reserved Bits    */
} __type7;
typedef struct 
{                                                          /* Bit Access       */
    uint8  WAIT:1;                                         /* WAIT             */
    const uint8  WST:1;                                    /* WST              */
    uint8  RSUB:1;                                         /* RSUB             */
    const uint8  RSST:1;                                   /* RSST             */
    const uint8  WSST:1;                                   /* WSST             */
    const uint8  WUST:1;                                   /* WUST             */
    uint8  :2;                                             /* Reserved Bits    */
} __type8;
typedef struct 
{                                                          /* Bit Access       */
    uint8  KRM0:1;                                         /* KRM0             */
    uint8  KRM1:1;                                         /* KRM1             */
    uint8  KRM2:1;                                         /* KRM2             */
    uint8  KRM3:1;                                         /* KRM3             */
    uint8  KRM4:1;                                         /* KRM4             */
    uint8  KRM5:1;                                         /* KRM5             */
    uint8  KRM6:1;                                         /* KRM6             */
    uint8  KRM7:1;                                         /* KRM7             */
} __type9;
typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
    uint8  UINT8[4];                                       /* 8-bit Access     */
} __type10;
typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
    uint8  UINT8[4];                                       /* 8-bit Access     */
    __type0;                                               /* Bit Access       */
} __type11;
typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
    uint8  UINT8[4];                                       /* 8-bit Access     */
    __type1;                                               /* Bit Access       */
} __type12;
typedef union
{                                                          /* IOR              */
    uint16 UINT16;                                         /* 16-bit Access    */
    uint8  UINT8[2];                                       /* 8-bit Access     */
    struct 
    {
        union
        {                                                  /* IOR              */
            uint8  UINT8;                                  /*  8-bit Access    */
        } LBRP0;
        union
        {                                                  /* IOR              */
            uint8  UINT8;                                  /*  8-bit Access    */
        } LBRP1;
    };
} __type13;
typedef union
{                                                          /* IOR              */
    uint16 UINT16;                                         /* 16-bit Access    */
    uint8  UINT8[2];                                       /* 8-bit Access     */
} __type14;
typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
} __type15;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type2;                                               /* Bit Access       */
} __type16;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type3;                                               /* Bit Access       */
} __type17;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type4;                                               /* Bit Access       */
} __type18;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type5;                                               /* Bit Access       */
} __type19;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type6;                                               /* Bit Access       */
} __type20;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type7;                                               /* Bit Access       */
} __type21;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type8;                                               /* Bit Access       */
} __type22;
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
    __type9;                                               /* Bit Access       */
} __type23;

typedef struct 
{                                                          /* Module           */
    uint32 ID0;                                            /* ID0              */
    uint32 ID1;                                            /* ID1              */
    uint32 ID2;                                            /* ID2              */
    uint32 ID3;                                            /* ID3              */
    const uint32 IDST;                                     /* IDST             */
} __type24;
typedef struct 
{                                                          /* Module           */
    const uint8  FPMON;                                    /* FPMON            */
    uint8  dummy0[15];                                     /* Reserved         */
    uint8  FASTAT;                                         /* FASTAT           */
    uint8  dummy1[3];                                      /* Reserved         */
    uint8  FAEINT;                                         /* FAEINT           */
    uint8  dummy2[11];                                     /* Reserved         */
    uint16 FAREASELC;                                      /* FAREASELC        */
    uint8  dummy3[14];                                     /* Reserved         */
    uint32 FSADDR;                                         /* FSADDR           */
    uint32 FEADDR;                                         /* FEADDR           */
    uint8  dummy4[28];                                     /* Reserved         */
    uint16 FCURAME;                                        /* FCURAME          */
    uint8  dummy5[42];                                     /* Reserved         */
    const uint32 FSTATR;                                   /* FSTATR           */
    uint16 FENTRYR;                                        /* FENTRYR          */
    uint8  dummy6[2];                                      /* Reserved         */
    uint16 FPROTR;                                         /* FPROTR           */
    uint8  dummy7[2];                                      /* Reserved         */
    uint16 FSUINITR;                                       /* FSUINITR         */
    uint8  dummy8[2];                                      /* Reserved         */
    const uint8  FLKSTAT;                                  /* FLKSTAT          */
    uint8  dummy9[3];                                      /* Reserved         */
    const uint32 FRFSTEADR;                                /* FRFSTEADR        */
    const uint8  FRTSTAT;                                  /* FRTSTAT          */
    uint8  dummy10[7];                                     /* Reserved         */
    const uint16 FCMDR;                                    /* FCMDR            */
    uint8  dummy11[30];                                    /* Reserved         */
    const uint16 FPESTAT;                                  /* FPESTAT          */
    uint8  dummy12[14];                                    /* Reserved         */
    uint8  FBCCNT;                                         /* FBCCNT           */
    uint8  dummy13[3];                                     /* Reserved         */
    const uint8  FBCSTAT;                                  /* FBCSTAT          */
    uint8  dummy14[3];                                     /* Reserved         */
    const uint32 FPSADDR;                                  /* FPSADDR          */
    uint8  dummy15[4];                                     /* Reserved         */
    uint16 FCPSR;                                          /* FCPSR            */
    uint8  dummy16[2];                                     /* Reserved         */
    uint16 FPCKAR;                                         /* FPCKAR           */
    uint8  dummy17[26];                                    /* Reserved         */
    const uint16 FECCEMON;                                 /* FECCEMON         */
    uint8  dummy18[2];                                     /* Reserved         */
    uint16 FECCTMD;                                        /* FECCTMD          */
    uint8  dummy19[2];                                     /* Reserved         */
    uint16 FDMYECC;                                        /* FDMYECC          */
} __type25;
typedef struct 
{                                                          /* Module           */
    uint8  BWCBUFEN;                                       /* BWCBUFEN         */
} __type26;
typedef struct 
{                                                          /* Module           */
    uint8  FCUFAREA;                                       /* FCUFAREA         */
} __type27;
typedef struct 
{                                                          /* Module           */
    __type10 CR1;                                          /* CR1              */
    __type10 CR2;                                          /* CR2              */
    __type10 MR1;                                          /* MR1              */
    __type10 MR2;                                          /* MR2              */
    __type10 MR3;                                          /* MR3              */
    __type10 FER;                                          /* FER              */
    __type10 SER;                                          /* SER              */
    __type10 IER;                                          /* IER              */
    __type11 SR1;                                          /* SR1              */
    __type12 SR2;                                          /* SR2              */
    __type10 SAR0;                                         /* SAR0             */
    __type10 SAR1;                                         /* SAR1             */
    __type10 SAR2;                                         /* SAR2             */
    __type10 BRL;                                          /* BRL              */
    __type10 BRH;                                          /* BRH              */
    __type10 DRT;                                          /* DRT              */
    const __type10 DRR;                                    /* DRR              */
} __type28;
typedef struct 
{                                                          /* Module           */
    uint32 PRDNAME1;                                       /* PRDNAME1         */
    uint32 PRDNAME2;                                       /* PRDNAME2         */
    uint32 PRDNAME3;                                       /* PRDNAME3         */
} __type29;
typedef struct 
{                                                          /* Module           */
    uint8  dummy20[1];                                     /* Reserved         */
    uint8  GLWBR;                                          /* GLWBR            */
    uint8  GLBRP0;                                         /* GLBRP0           */
    uint8  GLBRP1;                                         /* GLBRP1           */
    uint8  GLSTC;                                          /* GLSTC            */
} __type30;
typedef struct 
{                                                          /* Module           */
    uint8  L0MD;                                           /* L0MD             */
    uint8  L0BFC;                                          /* L0BFC            */
    uint8  L0SC;                                           /* L0SC             */
    uint8  L0WUP;                                          /* L0WUP            */
    uint8  L0IE;                                           /* L0IE             */
    uint8  L0EDE;                                          /* L0EDE            */
    uint8  L0CUC;                                          /* L0CUC            */
    uint8  dummy21[1];                                     /* Reserved         */
    uint8  L0TRC;                                          /* L0TRC            */
    const uint8  L0MST;                                    /* L0MST            */
    uint8  L0ST;                                           /* L0ST             */
    uint8  L0EST;                                          /* L0EST            */
    uint8  L0DFC;                                          /* L0DFC            */
    uint8  L0IDB;                                          /* L0IDB            */
    uint8  L0CBR;                                          /* L0CBR            */
    uint8  dummy22[1];                                     /* Reserved         */
    uint8  L0DBR1;                                         /* L0DBR1           */
    uint8  L0DBR2;                                         /* L0DBR2           */
    uint8  L0DBR3;                                         /* L0DBR3           */
    uint8  L0DBR4;                                         /* L0DBR4           */
    uint8  L0DBR5;                                         /* L0DBR5           */
    uint8  L0DBR6;                                         /* L0DBR6           */
    uint8  L0DBR7;                                         /* L0DBR7           */
    uint8  L0DBR8;                                         /* L0DBR8           */
} __type31;
typedef struct 
{                                                          /* Module           */
    uint8  L1MD;                                           /* L1MD             */
    uint8  L1BFC;                                          /* L1BFC            */
    uint8  L1SC;                                           /* L1SC             */
    uint8  L1WUP;                                          /* L1WUP            */
    uint8  L1IE;                                           /* L1IE             */
    uint8  L1EDE;                                          /* L1EDE            */
    uint8  L1CUC;                                          /* L1CUC            */
    uint8  dummy23[1];                                     /* Reserved         */
    uint8  L1TRC;                                          /* L1TRC            */
    const uint8  L1MST;                                    /* L1MST            */
    uint8  L1ST;                                           /* L1ST             */
    uint8  L1EST;                                          /* L1EST            */
    uint8  L1DFC;                                          /* L1DFC            */
    uint8  L1IDB;                                          /* L1IDB            */
    uint8  L1CBR;                                          /* L1CBR            */
    uint8  dummy24[1];                                     /* Reserved         */
    uint8  L1DBR1;                                         /* L1DBR1           */
    uint8  L1DBR2;                                         /* L1DBR2           */
    uint8  L1DBR3;                                         /* L1DBR3           */
    uint8  L1DBR4;                                         /* L1DBR4           */
    uint8  L1DBR5;                                         /* L1DBR5           */
    uint8  L1DBR6;                                         /* L1DBR6           */
    uint8  L1DBR7;                                         /* L1DBR7           */
    uint8  L1DBR8;                                         /* L1DBR8           */
} __type32;
typedef struct 
{                                                          /* Module           */
    uint8  L2MD;                                           /* L2MD             */
    uint8  L2BFC;                                          /* L2BFC            */
    uint8  L2SC;                                           /* L2SC             */
    uint8  L2WUP;                                          /* L2WUP            */
    uint8  L2IE;                                           /* L2IE             */
    uint8  L2EDE;                                          /* L2EDE            */
    uint8  L2CUC;                                          /* L2CUC            */
    uint8  dummy25[1];                                     /* Reserved         */
    uint8  L2TRC;                                          /* L2TRC            */
    const uint8  L2MST;                                    /* L2MST            */
    uint8  L2ST;                                           /* L2ST             */
    uint8  L2EST;                                          /* L2EST            */
    uint8  L2DFC;                                          /* L2DFC            */
    uint8  L2IDB;                                          /* L2IDB            */
    uint8  L2CBR;                                          /* L2CBR            */
    uint8  dummy26[1];                                     /* Reserved         */
    uint8  L2DBR1;                                         /* L2DBR1           */
    uint8  L2DBR2;                                         /* L2DBR2           */
    uint8  L2DBR3;                                         /* L2DBR3           */
    uint8  L2DBR4;                                         /* L2DBR4           */
    uint8  L2DBR5;                                         /* L2DBR5           */
    uint8  L2DBR6;                                         /* L2DBR6           */
    uint8  L2DBR7;                                         /* L2DBR7           */
    uint8  L2DBR8;                                         /* L2DBR8           */
} __type33;
typedef struct 
{                                                          /* Module           */
    uint8  L3MD;                                           /* L3MD             */
    uint8  L3BFC;                                          /* L3BFC            */
    uint8  L3SC;                                           /* L3SC             */
    uint8  L3WUP;                                          /* L3WUP            */
    uint8  L3IE;                                           /* L3IE             */
    uint8  L3EDE;                                          /* L3EDE            */
    uint8  L3CUC;                                          /* L3CUC            */
    uint8  dummy27[1];                                     /* Reserved         */
    uint8  L3TRC;                                          /* L3TRC            */
    const uint8  L3MST;                                    /* L3MST            */
    uint8  L3ST;                                           /* L3ST             */
    uint8  L3EST;                                          /* L3EST            */
    uint8  L3DFC;                                          /* L3DFC            */
    uint8  L3IDB;                                          /* L3IDB            */
    uint8  L3CBR;                                          /* L3CBR            */
    uint8  dummy28[1];                                     /* Reserved         */
    uint8  L3DBR1;                                         /* L3DBR1           */
    uint8  L3DBR2;                                         /* L3DBR2           */
    uint8  L3DBR3;                                         /* L3DBR3           */
    uint8  L3DBR4;                                         /* L3DBR4           */
    uint8  L3DBR5;                                         /* L3DBR5           */
    uint8  L3DBR6;                                         /* L3DBR6           */
    uint8  L3DBR7;                                         /* L3DBR7           */
    uint8  L3DBR8;                                         /* L3DBR8           */
} __type34;
typedef struct 
{                                                          /* Module           */
    uint8  dummy29[1];                                     /* Reserved         */
    uint8  LWBR;                                           /* LWBR             */
    __type13 LBRP01;                                       /* LBRP01           */
    uint8  LSTC;                                           /* LSTC             */
    uint8  dummy30[3];                                     /* Reserved         */
    uint8  LMD;                                            /* LMD              */
    uint8  LBFC;                                           /* LBFC             */
    uint8  LSC;                                            /* LSC              */
    uint8  LWUP;                                           /* LWUP             */
    uint8  LIE;                                            /* LIE              */
    uint8  LEDE;                                           /* LEDE             */
    uint8  LCUC;                                           /* LCUC             */
    uint8  dummy31[1];                                     /* Reserved         */
    uint8  LTRC;                                           /* LTRC             */
    const uint8  LMST;                                     /* LMST             */
    uint8  LST;                                            /* LST              */
    uint8  LEST;                                           /* LEST             */
    uint8  LDFC;                                           /* LDFC             */
    uint8  LIDB;                                           /* LIDB             */
    uint8  LCBR;                                           /* LCBR             */
    uint8  LUDB0;                                          /* LUDB0            */
    uint8  LDBR1;                                          /* LDBR1            */
    uint8  LDBR2;                                          /* LDBR2            */
    uint8  LDBR3;                                          /* LDBR3            */
    uint8  LDBR4;                                          /* LDBR4            */
    uint8  LDBR5;                                          /* LDBR5            */
    uint8  LDBR6;                                          /* LDBR6            */
    uint8  LDBR7;                                          /* LDBR7            */
    uint8  LDBR8;                                          /* LDBR8            */
    uint8  LUOER;                                          /* LUOER            */
    uint8  LUOR1;                                          /* LUOR1            */
    uint8  dummy32[2];                                     /* Reserved         */
    __type14 LUTDR;                                        /* LUTDR            */
    const __type14 LURDR;                                  /* LURDR            */
    __type14 LUWTDR;                                       /* LUWTDR           */
    uint8  dummy33[22];                                    /* Reserved         */
} __type35;
typedef struct 
{                                                          /* Module           */
    __type10 C0CFG;                                        /* C0CFG            */
    __type10 C0CTR;                                        /* C0CTR            */
    const __type10 C0STS;                                  /* C0STS            */
    __type10 C0ERFL;                                       /* C0ERFL           */
    __type10 C1CFG;                                        /* C1CFG            */
    __type10 C1CTR;                                        /* C1CTR            */
    const __type10 C1STS;                                  /* C1STS            */
    __type10 C1ERFL;                                       /* C1ERFL           */
    __type10 C2CFG;                                        /* C2CFG            */
    __type10 C2CTR;                                        /* C2CTR            */
    const __type10 C2STS;                                  /* C2STS            */
    __type10 C2ERFL;                                       /* C2ERFL           */
    __type10 C3CFG;                                        /* C3CFG            */
    __type10 C3CTR;                                        /* C3CTR            */
    const __type10 C3STS;                                  /* C3STS            */
    __type10 C3ERFL;                                       /* C3ERFL           */
    __type10 C4CFG;                                        /* C4CFG            */
    __type10 C4CTR;                                        /* C4CTR            */
    const __type10 C4STS;                                  /* C4STS            */
    __type10 C4ERFL;                                       /* C4ERFL           */
    __type10 C5CFG;                                        /* C5CFG            */
    __type10 C5CTR;                                        /* C5CTR            */
    const __type10 C5STS;                                  /* C5STS            */
    __type10 C5ERFL;                                       /* C5ERFL           */
    uint8  dummy34[36];                                    /* Reserved         */
    __type10 GCFG;                                         /* GCFG             */
    __type10 GCTR;                                         /* GCTR             */
    const __type10 GSTS;                                   /* GSTS             */
    __type10 GERFL;                                        /* GERFL            */
    const __type15 GTSC;                                   /* GTSC             */
    __type10 GAFLECTR;                                     /* GAFLECTR         */
    __type10 GAFLCFG0;                                     /* GAFLCFG0         */
    __type10 GAFLCFG1;                                     /* GAFLCFG1         */
    __type10 RMNB;                                         /* RMNB             */
    __type10 RMND0;                                        /* RMND0            */
    __type10 RMND1;                                        /* RMND1            */
    __type10 RMND2;                                        /* RMND2            */
    uint8  dummy35[4];                                     /* Reserved         */
    __type10 RFCC0;                                        /* RFCC0            */
    __type10 RFCC1;                                        /* RFCC1            */
    __type10 RFCC2;                                        /* RFCC2            */
    __type10 RFCC3;                                        /* RFCC3            */
    __type10 RFCC4;                                        /* RFCC4            */
    __type10 RFCC5;                                        /* RFCC5            */
    __type10 RFCC6;                                        /* RFCC6            */
    __type10 RFCC7;                                        /* RFCC7            */
    __type10 RFSTS0;                                       /* RFSTS0           */
    __type10 RFSTS1;                                       /* RFSTS1           */
    __type10 RFSTS2;                                       /* RFSTS2           */
    __type10 RFSTS3;                                       /* RFSTS3           */
    __type10 RFSTS4;                                       /* RFSTS4           */
    __type10 RFSTS5;                                       /* RFSTS5           */
    __type10 RFSTS6;                                       /* RFSTS6           */
    __type10 RFSTS7;                                       /* RFSTS7           */
    __type10 RFPCTR0;                                      /* RFPCTR0          */
    __type10 RFPCTR1;                                      /* RFPCTR1          */
    __type10 RFPCTR2;                                      /* RFPCTR2          */
    __type10 RFPCTR3;                                      /* RFPCTR3          */
    __type10 RFPCTR4;                                      /* RFPCTR4          */
    __type10 RFPCTR5;                                      /* RFPCTR5          */
    __type10 RFPCTR6;                                      /* RFPCTR6          */
    __type10 RFPCTR7;                                      /* RFPCTR7          */
    __type10 CFCC0;                                        /* CFCC0            */
    __type10 CFCC1;                                        /* CFCC1            */
    __type10 CFCC2;                                        /* CFCC2            */
    __type10 CFCC3;                                        /* CFCC3            */
    __type10 CFCC4;                                        /* CFCC4            */
    __type10 CFCC5;                                        /* CFCC5            */
    __type10 CFCC6;                                        /* CFCC6            */
    __type10 CFCC7;                                        /* CFCC7            */
    __type10 CFCC8;                                        /* CFCC8            */
    __type10 CFCC9;                                        /* CFCC9            */
    __type10 CFCC10;                                       /* CFCC10           */
    __type10 CFCC11;                                       /* CFCC11           */
    __type10 CFCC12;                                       /* CFCC12           */
    __type10 CFCC13;                                       /* CFCC13           */
    __type10 CFCC14;                                       /* CFCC14           */
    __type10 CFCC15;                                       /* CFCC15           */
    __type10 CFCC16;                                       /* CFCC16           */
    __type10 CFCC17;                                       /* CFCC17           */
    uint8  dummy36[24];                                    /* Reserved         */
    __type10 CFSTS0;                                       /* CFSTS0           */
    __type10 CFSTS1;                                       /* CFSTS1           */
    __type10 CFSTS2;                                       /* CFSTS2           */
    __type10 CFSTS3;                                       /* CFSTS3           */
    __type10 CFSTS4;                                       /* CFSTS4           */
    __type10 CFSTS5;                                       /* CFSTS5           */
    __type10 CFSTS6;                                       /* CFSTS6           */
    __type10 CFSTS7;                                       /* CFSTS7           */
    __type10 CFSTS8;                                       /* CFSTS8           */
    __type10 CFSTS9;                                       /* CFSTS9           */
    __type10 CFSTS10;                                      /* CFSTS10          */
    __type10 CFSTS11;                                      /* CFSTS11          */
    __type10 CFSTS12;                                      /* CFSTS12          */
    __type10 CFSTS13;                                      /* CFSTS13          */
    __type10 CFSTS14;                                      /* CFSTS14          */
    __type10 CFSTS15;                                      /* CFSTS15          */
    __type10 CFSTS16;                                      /* CFSTS16          */
    __type10 CFSTS17;                                      /* CFSTS17          */
    uint8  dummy37[24];                                    /* Reserved         */
    __type10 CFPCTR0;                                      /* CFPCTR0          */
    __type10 CFPCTR1;                                      /* CFPCTR1          */
    __type10 CFPCTR2;                                      /* CFPCTR2          */
    __type10 CFPCTR3;                                      /* CFPCTR3          */
    __type10 CFPCTR4;                                      /* CFPCTR4          */
    __type10 CFPCTR5;                                      /* CFPCTR5          */
    __type10 CFPCTR6;                                      /* CFPCTR6          */
    __type10 CFPCTR7;                                      /* CFPCTR7          */
    __type10 CFPCTR8;                                      /* CFPCTR8          */
    __type10 CFPCTR9;                                      /* CFPCTR9          */
    __type10 CFPCTR10;                                     /* CFPCTR10         */
    __type10 CFPCTR11;                                     /* CFPCTR11         */
    __type10 CFPCTR12;                                     /* CFPCTR12         */
    __type10 CFPCTR13;                                     /* CFPCTR13         */
    __type10 CFPCTR14;                                     /* CFPCTR14         */
    __type10 CFPCTR15;                                     /* CFPCTR15         */
    __type10 CFPCTR16;                                     /* CFPCTR16         */
    __type10 CFPCTR17;                                     /* CFPCTR17         */
    uint8  dummy38[24];                                    /* Reserved         */
    const __type10 FESTS;                                  /* FESTS            */
    const __type10 FFSTS;                                  /* FFSTS            */
    const __type10 FMSTS;                                  /* FMSTS            */
    const __type10 RFISTS;                                 /* RFISTS           */
    const __type10 CFRISTS;                                /* CFRISTS          */
    const __type10 CFTISTS;                                /* CFTISTS          */
    uint8  TMC0;                                           /* TMC0             */
    uint8  TMC1;                                           /* TMC1             */
    uint8  TMC2;                                           /* TMC2             */
    uint8  TMC3;                                           /* TMC3             */
    uint8  TMC4;                                           /* TMC4             */
    uint8  TMC5;                                           /* TMC5             */
    uint8  TMC6;                                           /* TMC6             */
    uint8  TMC7;                                           /* TMC7             */
    uint8  TMC8;                                           /* TMC8             */
    uint8  TMC9;                                           /* TMC9             */
    uint8  TMC10;                                          /* TMC10            */
    uint8  TMC11;                                          /* TMC11            */
    uint8  TMC12;                                          /* TMC12            */
    uint8  TMC13;                                          /* TMC13            */
    uint8  TMC14;                                          /* TMC14            */
    uint8  TMC15;                                          /* TMC15            */
    uint8  TMC16;                                          /* TMC16            */
    uint8  TMC17;                                          /* TMC17            */
    uint8  TMC18;                                          /* TMC18            */
    uint8  TMC19;                                          /* TMC19            */
    uint8  TMC20;                                          /* TMC20            */
    uint8  TMC21;                                          /* TMC21            */
    uint8  TMC22;                                          /* TMC22            */
    uint8  TMC23;                                          /* TMC23            */
    uint8  TMC24;                                          /* TMC24            */
    uint8  TMC25;                                          /* TMC25            */
    uint8  TMC26;                                          /* TMC26            */
    uint8  TMC27;                                          /* TMC27            */
    uint8  TMC28;                                          /* TMC28            */
    uint8  TMC29;                                          /* TMC29            */
    uint8  TMC30;                                          /* TMC30            */
    uint8  TMC31;                                          /* TMC31            */
    uint8  TMC32;                                          /* TMC32            */
    uint8  TMC33;                                          /* TMC33            */
    uint8  TMC34;                                          /* TMC34            */
    uint8  TMC35;                                          /* TMC35            */
    uint8  TMC36;                                          /* TMC36            */
    uint8  TMC37;                                          /* TMC37            */
    uint8  TMC38;                                          /* TMC38            */
    uint8  TMC39;                                          /* TMC39            */
    uint8  TMC40;                                          /* TMC40            */
    uint8  TMC41;                                          /* TMC41            */
    uint8  TMC42;                                          /* TMC42            */
    uint8  TMC43;                                          /* TMC43            */
    uint8  TMC44;                                          /* TMC44            */
    uint8  TMC45;                                          /* TMC45            */
    uint8  TMC46;                                          /* TMC46            */
    uint8  TMC47;                                          /* TMC47            */
    uint8  TMC48;                                          /* TMC48            */
    uint8  TMC49;                                          /* TMC49            */
    uint8  TMC50;                                          /* TMC50            */
    uint8  TMC51;                                          /* TMC51            */
    uint8  TMC52;                                          /* TMC52            */
    uint8  TMC53;                                          /* TMC53            */
    uint8  TMC54;                                          /* TMC54            */
    uint8  TMC55;                                          /* TMC55            */
    uint8  TMC56;                                          /* TMC56            */
    uint8  TMC57;                                          /* TMC57            */
    uint8  TMC58;                                          /* TMC58            */
    uint8  TMC59;                                          /* TMC59            */
    uint8  TMC60;                                          /* TMC60            */
    uint8  TMC61;                                          /* TMC61            */
    uint8  TMC62;                                          /* TMC62            */
    uint8  TMC63;                                          /* TMC63            */
    uint8  TMC64;                                          /* TMC64            */
    uint8  TMC65;                                          /* TMC65            */
    uint8  TMC66;                                          /* TMC66            */
    uint8  TMC67;                                          /* TMC67            */
    uint8  TMC68;                                          /* TMC68            */
    uint8  TMC69;                                          /* TMC69            */
    uint8  TMC70;                                          /* TMC70            */
    uint8  TMC71;                                          /* TMC71            */
    uint8  TMC72;                                          /* TMC72            */
    uint8  TMC73;                                          /* TMC73            */
    uint8  TMC74;                                          /* TMC74            */
    uint8  TMC75;                                          /* TMC75            */
    uint8  TMC76;                                          /* TMC76            */
    uint8  TMC77;                                          /* TMC77            */
    uint8  TMC78;                                          /* TMC78            */
    uint8  TMC79;                                          /* TMC79            */
    uint8  TMC80;                                          /* TMC80            */
    uint8  TMC81;                                          /* TMC81            */
    uint8  TMC82;                                          /* TMC82            */
    uint8  TMC83;                                          /* TMC83            */
    uint8  TMC84;                                          /* TMC84            */
    uint8  TMC85;                                          /* TMC85            */
    uint8  TMC86;                                          /* TMC86            */
    uint8  TMC87;                                          /* TMC87            */
    uint8  TMC88;                                          /* TMC88            */
    uint8  TMC89;                                          /* TMC89            */
    uint8  TMC90;                                          /* TMC90            */
    uint8  TMC91;                                          /* TMC91            */
    uint8  TMC92;                                          /* TMC92            */
    uint8  TMC93;                                          /* TMC93            */
    uint8  TMC94;                                          /* TMC94            */
    uint8  TMC95;                                          /* TMC95            */
    uint8  dummy39[32];                                    /* Reserved         */
    uint8  TMSTS0;                                         /* TMSTS0           */
    uint8  TMSTS1;                                         /* TMSTS1           */
    uint8  TMSTS2;                                         /* TMSTS2           */
    uint8  TMSTS3;                                         /* TMSTS3           */
    uint8  TMSTS4;                                         /* TMSTS4           */
    uint8  TMSTS5;                                         /* TMSTS5           */
    uint8  TMSTS6;                                         /* TMSTS6           */
    uint8  TMSTS7;                                         /* TMSTS7           */
    uint8  TMSTS8;                                         /* TMSTS8           */
    uint8  TMSTS9;                                         /* TMSTS9           */
    uint8  TMSTS10;                                        /* TMSTS10          */
    uint8  TMSTS11;                                        /* TMSTS11          */
    uint8  TMSTS12;                                        /* TMSTS12          */
    uint8  TMSTS13;                                        /* TMSTS13          */
    uint8  TMSTS14;                                        /* TMSTS14          */
    uint8  TMSTS15;                                        /* TMSTS15          */
    uint8  TMSTS16;                                        /* TMSTS16          */
    uint8  TMSTS17;                                        /* TMSTS17          */
    uint8  TMSTS18;                                        /* TMSTS18          */
    uint8  TMSTS19;                                        /* TMSTS19          */
    uint8  TMSTS20;                                        /* TMSTS20          */
    uint8  TMSTS21;                                        /* TMSTS21          */
    uint8  TMSTS22;                                        /* TMSTS22          */
    uint8  TMSTS23;                                        /* TMSTS23          */
    uint8  TMSTS24;                                        /* TMSTS24          */
    uint8  TMSTS25;                                        /* TMSTS25          */
    uint8  TMSTS26;                                        /* TMSTS26          */
    uint8  TMSTS27;                                        /* TMSTS27          */
    uint8  TMSTS28;                                        /* TMSTS28          */
    uint8  TMSTS29;                                        /* TMSTS29          */
    uint8  TMSTS30;                                        /* TMSTS30          */
    uint8  TMSTS31;                                        /* TMSTS31          */
    uint8  TMSTS32;                                        /* TMSTS32          */
    uint8  TMSTS33;                                        /* TMSTS33          */
    uint8  TMSTS34;                                        /* TMSTS34          */
    uint8  TMSTS35;                                        /* TMSTS35          */
    uint8  TMSTS36;                                        /* TMSTS36          */
    uint8  TMSTS37;                                        /* TMSTS37          */
    uint8  TMSTS38;                                        /* TMSTS38          */
    uint8  TMSTS39;                                        /* TMSTS39          */
    uint8  TMSTS40;                                        /* TMSTS40          */
    uint8  TMSTS41;                                        /* TMSTS41          */
    uint8  TMSTS42;                                        /* TMSTS42          */
    uint8  TMSTS43;                                        /* TMSTS43          */
    uint8  TMSTS44;                                        /* TMSTS44          */
    uint8  TMSTS45;                                        /* TMSTS45          */
    uint8  TMSTS46;                                        /* TMSTS46          */
    uint8  TMSTS47;                                        /* TMSTS47          */
    uint8  TMSTS48;                                        /* TMSTS48          */
    uint8  TMSTS49;                                        /* TMSTS49          */
    uint8  TMSTS50;                                        /* TMSTS50          */
    uint8  TMSTS51;                                        /* TMSTS51          */
    uint8  TMSTS52;                                        /* TMSTS52          */
    uint8  TMSTS53;                                        /* TMSTS53          */
    uint8  TMSTS54;                                        /* TMSTS54          */
    uint8  TMSTS55;                                        /* TMSTS55          */
    uint8  TMSTS56;                                        /* TMSTS56          */
    uint8  TMSTS57;                                        /* TMSTS57          */
    uint8  TMSTS58;                                        /* TMSTS58          */
    uint8  TMSTS59;                                        /* TMSTS59          */
    uint8  TMSTS60;                                        /* TMSTS60          */
    uint8  TMSTS61;                                        /* TMSTS61          */
    uint8  TMSTS62;                                        /* TMSTS62          */
    uint8  TMSTS63;                                        /* TMSTS63          */
    uint8  TMSTS64;                                        /* TMSTS64          */
    uint8  TMSTS65;                                        /* TMSTS65          */
    uint8  TMSTS66;                                        /* TMSTS66          */
    uint8  TMSTS67;                                        /* TMSTS67          */
    uint8  TMSTS68;                                        /* TMSTS68          */
    uint8  TMSTS69;                                        /* TMSTS69          */
    uint8  TMSTS70;                                        /* TMSTS70          */
    uint8  TMSTS71;                                        /* TMSTS71          */
    uint8  TMSTS72;                                        /* TMSTS72          */
    uint8  TMSTS73;                                        /* TMSTS73          */
    uint8  TMSTS74;                                        /* TMSTS74          */
    uint8  TMSTS75;                                        /* TMSTS75          */
    uint8  TMSTS76;                                        /* TMSTS76          */
    uint8  TMSTS77;                                        /* TMSTS77          */
    uint8  TMSTS78;                                        /* TMSTS78          */
    uint8  TMSTS79;                                        /* TMSTS79          */
    uint8  TMSTS80;                                        /* TMSTS80          */
    uint8  TMSTS81;                                        /* TMSTS81          */
    uint8  TMSTS82;                                        /* TMSTS82          */
    uint8  TMSTS83;                                        /* TMSTS83          */
    uint8  TMSTS84;                                        /* TMSTS84          */
    uint8  TMSTS85;                                        /* TMSTS85          */
    uint8  TMSTS86;                                        /* TMSTS86          */
    uint8  TMSTS87;                                        /* TMSTS87          */
    uint8  TMSTS88;                                        /* TMSTS88          */
    uint8  TMSTS89;                                        /* TMSTS89          */
    uint8  TMSTS90;                                        /* TMSTS90          */
    uint8  TMSTS91;                                        /* TMSTS91          */
    uint8  TMSTS92;                                        /* TMSTS92          */
    uint8  TMSTS93;                                        /* TMSTS93          */
    uint8  TMSTS94;                                        /* TMSTS94          */
    uint8  TMSTS95;                                        /* TMSTS95          */
    uint8  dummy40[32];                                    /* Reserved         */
    const __type10 TMTRSTS0;                               /* TMTRSTS0         */
    const __type10 TMTRSTS1;                               /* TMTRSTS1         */
    const __type10 TMTRSTS2;                               /* TMTRSTS2         */
    uint8  dummy41[4];                                     /* Reserved         */
    const __type10 TMTARSTS0;                              /* TMTARSTS0        */
    const __type10 TMTARSTS1;                              /* TMTARSTS1        */
    const __type10 TMTARSTS2;                              /* TMTARSTS2        */
    uint8  dummy42[4];                                     /* Reserved         */
    const __type10 TMTCSTS0;                               /* TMTCSTS0         */
    const __type10 TMTCSTS1;                               /* TMTCSTS1         */
    const __type10 TMTCSTS2;                               /* TMTCSTS2         */
    uint8  dummy43[4];                                     /* Reserved         */
    const __type10 TMTASTS0;                               /* TMTASTS0         */
    const __type10 TMTASTS1;                               /* TMTASTS1         */
    const __type10 TMTASTS2;                               /* TMTASTS2         */
    uint8  dummy44[4];                                     /* Reserved         */
    __type10 TMIEC0;                                       /* TMIEC0           */
    __type10 TMIEC1;                                       /* TMIEC1           */
    __type10 TMIEC2;                                       /* TMIEC2           */
    uint8  dummy45[4];                                     /* Reserved         */
    __type10 TXQCC0;                                       /* TXQCC0           */
    __type10 TXQCC1;                                       /* TXQCC1           */
    __type10 TXQCC2;                                       /* TXQCC2           */
    __type10 TXQCC3;                                       /* TXQCC3           */
    __type10 TXQCC4;                                       /* TXQCC4           */
    __type10 TXQCC5;                                       /* TXQCC5           */
    uint8  dummy46[8];                                     /* Reserved         */
    __type10 TXQSTS0;                                      /* TXQSTS0          */
    __type10 TXQSTS1;                                      /* TXQSTS1          */
    __type10 TXQSTS2;                                      /* TXQSTS2          */
    __type10 TXQSTS3;                                      /* TXQSTS3          */
    __type10 TXQSTS4;                                      /* TXQSTS4          */
    __type10 TXQSTS5;                                      /* TXQSTS5          */
    uint8  dummy47[8];                                     /* Reserved         */
    __type10 TXQPCTR0;                                     /* TXQPCTR0         */
    __type10 TXQPCTR1;                                     /* TXQPCTR1         */
    __type10 TXQPCTR2;                                     /* TXQPCTR2         */
    __type10 TXQPCTR3;                                     /* TXQPCTR3         */
    __type10 TXQPCTR4;                                     /* TXQPCTR4         */
    __type10 TXQPCTR5;                                     /* TXQPCTR5         */
    uint8  dummy48[8];                                     /* Reserved         */
    __type10 THLCC0;                                       /* THLCC0           */
    __type10 THLCC1;                                       /* THLCC1           */
    __type10 THLCC2;                                       /* THLCC2           */
    __type10 THLCC3;                                       /* THLCC3           */
    __type10 THLCC4;                                       /* THLCC4           */
    __type10 THLCC5;                                       /* THLCC5           */
    uint8  dummy49[8];                                     /* Reserved         */
    __type10 THLSTS0;                                      /* THLSTS0          */
    __type10 THLSTS1;                                      /* THLSTS1          */
    __type10 THLSTS2;                                      /* THLSTS2          */
    __type10 THLSTS3;                                      /* THLSTS3          */
    __type10 THLSTS4;                                      /* THLSTS4          */
    __type10 THLSTS5;                                      /* THLSTS5          */
    uint8  dummy50[8];                                     /* Reserved         */
    __type10 THLPCTR0;                                     /* THLPCTR0         */
    __type10 THLPCTR1;                                     /* THLPCTR1         */
    __type10 THLPCTR2;                                     /* THLPCTR2         */
    __type10 THLPCTR3;                                     /* THLPCTR3         */
    __type10 THLPCTR4;                                     /* THLPCTR4         */
    __type10 THLPCTR5;                                     /* THLPCTR5         */
    uint8  dummy51[8];                                     /* Reserved         */
    const __type10 GTINTSTS0;                              /* GTINTSTS0        */
    const __type10 GTINTSTS1;                              /* GTINTSTS1        */
    __type10 GTSTCFG;                                      /* GTSTCFG          */
    __type10 GTSTCTR;                                      /* GTSTCTR          */
    uint8  dummy52[12];                                    /* Reserved         */
    __type15 GLOCKK;                                       /* GLOCKK           */
    uint8  dummy53[128];                                   /* Reserved         */
    __type10 GAFLID0;                                      /* GAFLID0          */
    __type10 GAFLM0;                                       /* GAFLM0           */
    __type10 GAFLP00;                                      /* GAFLP00          */
    __type10 GAFLP10;                                      /* GAFLP10          */
    __type10 GAFLID1;                                      /* GAFLID1          */
    __type10 GAFLM1;                                       /* GAFLM1           */
    __type10 GAFLP01;                                      /* GAFLP01          */
    __type10 GAFLP11;                                      /* GAFLP11          */
    __type10 GAFLID2;                                      /* GAFLID2          */
    __type10 GAFLM2;                                       /* GAFLM2           */
    __type10 GAFLP02;                                      /* GAFLP02          */
    __type10 GAFLP12;                                      /* GAFLP12          */
    __type10 GAFLID3;                                      /* GAFLID3          */
    __type10 GAFLM3;                                       /* GAFLM3           */
    __type10 GAFLP03;                                      /* GAFLP03          */
    __type10 GAFLP13;                                      /* GAFLP13          */
    __type10 GAFLID4;                                      /* GAFLID4          */
    __type10 GAFLM4;                                       /* GAFLM4           */
    __type10 GAFLP04;                                      /* GAFLP04          */
    __type10 GAFLP14;                                      /* GAFLP14          */
    __type10 GAFLID5;                                      /* GAFLID5          */
    __type10 GAFLM5;                                       /* GAFLM5           */
    __type10 GAFLP05;                                      /* GAFLP05          */
    __type10 GAFLP15;                                      /* GAFLP15          */
    __type10 GAFLID6;                                      /* GAFLID6          */
    __type10 GAFLM6;                                       /* GAFLM6           */
    __type10 GAFLP06;                                      /* GAFLP06          */
    __type10 GAFLP16;                                      /* GAFLP16          */
    __type10 GAFLID7;                                      /* GAFLID7          */
    __type10 GAFLM7;                                       /* GAFLM7           */
    __type10 GAFLP07;                                      /* GAFLP07          */
    __type10 GAFLP17;                                      /* GAFLP17          */
    __type10 GAFLID8;                                      /* GAFLID8          */
    __type10 GAFLM8;                                       /* GAFLM8           */
    __type10 GAFLP08;                                      /* GAFLP08          */
    __type10 GAFLP18;                                      /* GAFLP18          */
    __type10 GAFLID9;                                      /* GAFLID9          */
    __type10 GAFLM9;                                       /* GAFLM9           */
    __type10 GAFLP09;                                      /* GAFLP09          */
    __type10 GAFLP19;                                      /* GAFLP19          */
    __type10 GAFLID10;                                     /* GAFLID10         */
    __type10 GAFLM10;                                      /* GAFLM10          */
    __type10 GAFLP010;                                     /* GAFLP010         */
    __type10 GAFLP110;                                     /* GAFLP110         */
    __type10 GAFLID11;                                     /* GAFLID11         */
    __type10 GAFLM11;                                      /* GAFLM11          */
    __type10 GAFLP011;                                     /* GAFLP011         */
    __type10 GAFLP111;                                     /* GAFLP111         */
    __type10 GAFLID12;                                     /* GAFLID12         */
    __type10 GAFLM12;                                      /* GAFLM12          */
    __type10 GAFLP012;                                     /* GAFLP012         */
    __type10 GAFLP112;                                     /* GAFLP112         */
    __type10 GAFLID13;                                     /* GAFLID13         */
    __type10 GAFLM13;                                      /* GAFLM13          */
    __type10 GAFLP013;                                     /* GAFLP013         */
    __type10 GAFLP113;                                     /* GAFLP113         */
    __type10 GAFLID14;                                     /* GAFLID14         */
    __type10 GAFLM14;                                      /* GAFLM14          */
    __type10 GAFLP014;                                     /* GAFLP014         */
    __type10 GAFLP114;                                     /* GAFLP114         */
    __type10 GAFLID15;                                     /* GAFLID15         */
    __type10 GAFLM15;                                      /* GAFLM15          */
    __type10 GAFLP015;                                     /* GAFLP015         */
    __type10 GAFLP115;                                     /* GAFLP115         */
    const __type10 RMID0;                                  /* RMID0            */
    const __type10 RMPTR0;                                 /* RMPTR0           */
    const __type10 RMDF00;                                 /* RMDF00           */
    const __type10 RMDF10;                                 /* RMDF10           */
    const __type10 RMID1;                                  /* RMID1            */
    const __type10 RMPTR1;                                 /* RMPTR1           */
    const __type10 RMDF01;                                 /* RMDF01           */
    const __type10 RMDF11;                                 /* RMDF11           */
    const __type10 RMID2;                                  /* RMID2            */
    const __type10 RMPTR2;                                 /* RMPTR2           */
    const __type10 RMDF02;                                 /* RMDF02           */
    const __type10 RMDF12;                                 /* RMDF12           */
    const __type10 RMID3;                                  /* RMID3            */
    const __type10 RMPTR3;                                 /* RMPTR3           */
    const __type10 RMDF03;                                 /* RMDF03           */
    const __type10 RMDF13;                                 /* RMDF13           */
    const __type10 RMID4;                                  /* RMID4            */
    const __type10 RMPTR4;                                 /* RMPTR4           */
    const __type10 RMDF04;                                 /* RMDF04           */
    const __type10 RMDF14;                                 /* RMDF14           */
    const __type10 RMID5;                                  /* RMID5            */
    const __type10 RMPTR5;                                 /* RMPTR5           */
    const __type10 RMDF05;                                 /* RMDF05           */
    const __type10 RMDF15;                                 /* RMDF15           */
    const __type10 RMID6;                                  /* RMID6            */
    const __type10 RMPTR6;                                 /* RMPTR6           */
    const __type10 RMDF06;                                 /* RMDF06           */
    const __type10 RMDF16;                                 /* RMDF16           */
    const __type10 RMID7;                                  /* RMID7            */
    const __type10 RMPTR7;                                 /* RMPTR7           */
    const __type10 RMDF07;                                 /* RMDF07           */
    const __type10 RMDF17;                                 /* RMDF17           */
    const __type10 RMID8;                                  /* RMID8            */
    const __type10 RMPTR8;                                 /* RMPTR8           */
    const __type10 RMDF08;                                 /* RMDF08           */
    const __type10 RMDF18;                                 /* RMDF18           */
    const __type10 RMID9;                                  /* RMID9            */
    const __type10 RMPTR9;                                 /* RMPTR9           */
    const __type10 RMDF09;                                 /* RMDF09           */
    const __type10 RMDF19;                                 /* RMDF19           */
    const __type10 RMID10;                                 /* RMID10           */
    const __type10 RMPTR10;                                /* RMPTR10          */
    const __type10 RMDF010;                                /* RMDF010          */
    const __type10 RMDF110;                                /* RMDF110          */
    const __type10 RMID11;                                 /* RMID11           */
    const __type10 RMPTR11;                                /* RMPTR11          */
    const __type10 RMDF011;                                /* RMDF011          */
    const __type10 RMDF111;                                /* RMDF111          */
    const __type10 RMID12;                                 /* RMID12           */
    const __type10 RMPTR12;                                /* RMPTR12          */
    const __type10 RMDF012;                                /* RMDF012          */
    const __type10 RMDF112;                                /* RMDF112          */
    const __type10 RMID13;                                 /* RMID13           */
    const __type10 RMPTR13;                                /* RMPTR13          */
    const __type10 RMDF013;                                /* RMDF013          */
    const __type10 RMDF113;                                /* RMDF113          */
    const __type10 RMID14;                                 /* RMID14           */
    const __type10 RMPTR14;                                /* RMPTR14          */
    const __type10 RMDF014;                                /* RMDF014          */
    const __type10 RMDF114;                                /* RMDF114          */
    const __type10 RMID15;                                 /* RMID15           */
    const __type10 RMPTR15;                                /* RMPTR15          */
    const __type10 RMDF015;                                /* RMDF015          */
    const __type10 RMDF115;                                /* RMDF115          */
    const __type10 RMID16;                                 /* RMID16           */
    const __type10 RMPTR16;                                /* RMPTR16          */
    const __type10 RMDF016;                                /* RMDF016          */
    const __type10 RMDF116;                                /* RMDF116          */
    const __type10 RMID17;                                 /* RMID17           */
    const __type10 RMPTR17;                                /* RMPTR17          */
    const __type10 RMDF017;                                /* RMDF017          */
    const __type10 RMDF117;                                /* RMDF117          */
    const __type10 RMID18;                                 /* RMID18           */
    const __type10 RMPTR18;                                /* RMPTR18          */
    const __type10 RMDF018;                                /* RMDF018          */
    const __type10 RMDF118;                                /* RMDF118          */
    const __type10 RMID19;                                 /* RMID19           */
    const __type10 RMPTR19;                                /* RMPTR19          */
    const __type10 RMDF019;                                /* RMDF019          */
    const __type10 RMDF119;                                /* RMDF119          */
    const __type10 RMID20;                                 /* RMID20           */
    const __type10 RMPTR20;                                /* RMPTR20          */
    const __type10 RMDF020;                                /* RMDF020          */
    const __type10 RMDF120;                                /* RMDF120          */
    const __type10 RMID21;                                 /* RMID21           */
    const __type10 RMPTR21;                                /* RMPTR21          */
    const __type10 RMDF021;                                /* RMDF021          */
    const __type10 RMDF121;                                /* RMDF121          */
    const __type10 RMID22;                                 /* RMID22           */
    const __type10 RMPTR22;                                /* RMPTR22          */
    const __type10 RMDF022;                                /* RMDF022          */
    const __type10 RMDF122;                                /* RMDF122          */
    const __type10 RMID23;                                 /* RMID23           */
    const __type10 RMPTR23;                                /* RMPTR23          */
    const __type10 RMDF023;                                /* RMDF023          */
    const __type10 RMDF123;                                /* RMDF123          */
    const __type10 RMID24;                                 /* RMID24           */
    const __type10 RMPTR24;                                /* RMPTR24          */
    const __type10 RMDF024;                                /* RMDF024          */
    const __type10 RMDF124;                                /* RMDF124          */
    const __type10 RMID25;                                 /* RMID25           */
    const __type10 RMPTR25;                                /* RMPTR25          */
    const __type10 RMDF025;                                /* RMDF025          */
    const __type10 RMDF125;                                /* RMDF125          */
    const __type10 RMID26;                                 /* RMID26           */
    const __type10 RMPTR26;                                /* RMPTR26          */
    const __type10 RMDF026;                                /* RMDF026          */
    const __type10 RMDF126;                                /* RMDF126          */
    const __type10 RMID27;                                 /* RMID27           */
    const __type10 RMPTR27;                                /* RMPTR27          */
    const __type10 RMDF027;                                /* RMDF027          */
    const __type10 RMDF127;                                /* RMDF127          */
    const __type10 RMID28;                                 /* RMID28           */
    const __type10 RMPTR28;                                /* RMPTR28          */
    const __type10 RMDF028;                                /* RMDF028          */
    const __type10 RMDF128;                                /* RMDF128          */
    const __type10 RMID29;                                 /* RMID29           */
    const __type10 RMPTR29;                                /* RMPTR29          */
    const __type10 RMDF029;                                /* RMDF029          */
    const __type10 RMDF129;                                /* RMDF129          */
    const __type10 RMID30;                                 /* RMID30           */
    const __type10 RMPTR30;                                /* RMPTR30          */
    const __type10 RMDF030;                                /* RMDF030          */
    const __type10 RMDF130;                                /* RMDF130          */
    const __type10 RMID31;                                 /* RMID31           */
    const __type10 RMPTR31;                                /* RMPTR31          */
    const __type10 RMDF031;                                /* RMDF031          */
    const __type10 RMDF131;                                /* RMDF131          */
    const __type10 RMID32;                                 /* RMID32           */
    const __type10 RMPTR32;                                /* RMPTR32          */
    const __type10 RMDF032;                                /* RMDF032          */
    const __type10 RMDF132;                                /* RMDF132          */
    const __type10 RMID33;                                 /* RMID33           */
    const __type10 RMPTR33;                                /* RMPTR33          */
    const __type10 RMDF033;                                /* RMDF033          */
    const __type10 RMDF133;                                /* RMDF133          */
    const __type10 RMID34;                                 /* RMID34           */
    const __type10 RMPTR34;                                /* RMPTR34          */
    const __type10 RMDF034;                                /* RMDF034          */
    const __type10 RMDF134;                                /* RMDF134          */
    const __type10 RMID35;                                 /* RMID35           */
    const __type10 RMPTR35;                                /* RMPTR35          */
    const __type10 RMDF035;                                /* RMDF035          */
    const __type10 RMDF135;                                /* RMDF135          */
    const __type10 RMID36;                                 /* RMID36           */
    const __type10 RMPTR36;                                /* RMPTR36          */
    const __type10 RMDF036;                                /* RMDF036          */
    const __type10 RMDF136;                                /* RMDF136          */
    const __type10 RMID37;                                 /* RMID37           */
    const __type10 RMPTR37;                                /* RMPTR37          */
    const __type10 RMDF037;                                /* RMDF037          */
    const __type10 RMDF137;                                /* RMDF137          */
    const __type10 RMID38;                                 /* RMID38           */
    const __type10 RMPTR38;                                /* RMPTR38          */
    const __type10 RMDF038;                                /* RMDF038          */
    const __type10 RMDF138;                                /* RMDF138          */
    const __type10 RMID39;                                 /* RMID39           */
    const __type10 RMPTR39;                                /* RMPTR39          */
    const __type10 RMDF039;                                /* RMDF039          */
    const __type10 RMDF139;                                /* RMDF139          */
    const __type10 RMID40;                                 /* RMID40           */
    const __type10 RMPTR40;                                /* RMPTR40          */
    const __type10 RMDF040;                                /* RMDF040          */
    const __type10 RMDF140;                                /* RMDF140          */
    const __type10 RMID41;                                 /* RMID41           */
    const __type10 RMPTR41;                                /* RMPTR41          */
    const __type10 RMDF041;                                /* RMDF041          */
    const __type10 RMDF141;                                /* RMDF141          */
    const __type10 RMID42;                                 /* RMID42           */
    const __type10 RMPTR42;                                /* RMPTR42          */
    const __type10 RMDF042;                                /* RMDF042          */
    const __type10 RMDF142;                                /* RMDF142          */
    const __type10 RMID43;                                 /* RMID43           */
    const __type10 RMPTR43;                                /* RMPTR43          */
    const __type10 RMDF043;                                /* RMDF043          */
    const __type10 RMDF143;                                /* RMDF143          */
    const __type10 RMID44;                                 /* RMID44           */
    const __type10 RMPTR44;                                /* RMPTR44          */
    const __type10 RMDF044;                                /* RMDF044          */
    const __type10 RMDF144;                                /* RMDF144          */
    const __type10 RMID45;                                 /* RMID45           */
    const __type10 RMPTR45;                                /* RMPTR45          */
    const __type10 RMDF045;                                /* RMDF045          */
    const __type10 RMDF145;                                /* RMDF145          */
    const __type10 RMID46;                                 /* RMID46           */
    const __type10 RMPTR46;                                /* RMPTR46          */
    const __type10 RMDF046;                                /* RMDF046          */
    const __type10 RMDF146;                                /* RMDF146          */
    const __type10 RMID47;                                 /* RMID47           */
    const __type10 RMPTR47;                                /* RMPTR47          */
    const __type10 RMDF047;                                /* RMDF047          */
    const __type10 RMDF147;                                /* RMDF147          */
    const __type10 RMID48;                                 /* RMID48           */
    const __type10 RMPTR48;                                /* RMPTR48          */
    const __type10 RMDF048;                                /* RMDF048          */
    const __type10 RMDF148;                                /* RMDF148          */
    const __type10 RMID49;                                 /* RMID49           */
    const __type10 RMPTR49;                                /* RMPTR49          */
    const __type10 RMDF049;                                /* RMDF049          */
    const __type10 RMDF149;                                /* RMDF149          */
    const __type10 RMID50;                                 /* RMID50           */
    const __type10 RMPTR50;                                /* RMPTR50          */
    const __type10 RMDF050;                                /* RMDF050          */
    const __type10 RMDF150;                                /* RMDF150          */
    const __type10 RMID51;                                 /* RMID51           */
    const __type10 RMPTR51;                                /* RMPTR51          */
    const __type10 RMDF051;                                /* RMDF051          */
    const __type10 RMDF151;                                /* RMDF151          */
    const __type10 RMID52;                                 /* RMID52           */
    const __type10 RMPTR52;                                /* RMPTR52          */
    const __type10 RMDF052;                                /* RMDF052          */
    const __type10 RMDF152;                                /* RMDF152          */
    const __type10 RMID53;                                 /* RMID53           */
    const __type10 RMPTR53;                                /* RMPTR53          */
    const __type10 RMDF053;                                /* RMDF053          */
    const __type10 RMDF153;                                /* RMDF153          */
    const __type10 RMID54;                                 /* RMID54           */
    const __type10 RMPTR54;                                /* RMPTR54          */
    const __type10 RMDF054;                                /* RMDF054          */
    const __type10 RMDF154;                                /* RMDF154          */
    const __type10 RMID55;                                 /* RMID55           */
    const __type10 RMPTR55;                                /* RMPTR55          */
    const __type10 RMDF055;                                /* RMDF055          */
    const __type10 RMDF155;                                /* RMDF155          */
    const __type10 RMID56;                                 /* RMID56           */
    const __type10 RMPTR56;                                /* RMPTR56          */
    const __type10 RMDF056;                                /* RMDF056          */
    const __type10 RMDF156;                                /* RMDF156          */
    const __type10 RMID57;                                 /* RMID57           */
    const __type10 RMPTR57;                                /* RMPTR57          */
    const __type10 RMDF057;                                /* RMDF057          */
    const __type10 RMDF157;                                /* RMDF157          */
    const __type10 RMID58;                                 /* RMID58           */
    const __type10 RMPTR58;                                /* RMPTR58          */
    const __type10 RMDF058;                                /* RMDF058          */
    const __type10 RMDF158;                                /* RMDF158          */
    const __type10 RMID59;                                 /* RMID59           */
    const __type10 RMPTR59;                                /* RMPTR59          */
    const __type10 RMDF059;                                /* RMDF059          */
    const __type10 RMDF159;                                /* RMDF159          */
    const __type10 RMID60;                                 /* RMID60           */
    const __type10 RMPTR60;                                /* RMPTR60          */
    const __type10 RMDF060;                                /* RMDF060          */
    const __type10 RMDF160;                                /* RMDF160          */
    const __type10 RMID61;                                 /* RMID61           */
    const __type10 RMPTR61;                                /* RMPTR61          */
    const __type10 RMDF061;                                /* RMDF061          */
    const __type10 RMDF161;                                /* RMDF161          */
    const __type10 RMID62;                                 /* RMID62           */
    const __type10 RMPTR62;                                /* RMPTR62          */
    const __type10 RMDF062;                                /* RMDF062          */
    const __type10 RMDF162;                                /* RMDF162          */
    const __type10 RMID63;                                 /* RMID63           */
    const __type10 RMPTR63;                                /* RMPTR63          */
    const __type10 RMDF063;                                /* RMDF063          */
    const __type10 RMDF163;                                /* RMDF163          */
    const __type10 RMID64;                                 /* RMID64           */
    const __type10 RMPTR64;                                /* RMPTR64          */
    const __type10 RMDF064;                                /* RMDF064          */
    const __type10 RMDF164;                                /* RMDF164          */
    const __type10 RMID65;                                 /* RMID65           */
    const __type10 RMPTR65;                                /* RMPTR65          */
    const __type10 RMDF065;                                /* RMDF065          */
    const __type10 RMDF165;                                /* RMDF165          */
    const __type10 RMID66;                                 /* RMID66           */
    const __type10 RMPTR66;                                /* RMPTR66          */
    const __type10 RMDF066;                                /* RMDF066          */
    const __type10 RMDF166;                                /* RMDF166          */
    const __type10 RMID67;                                 /* RMID67           */
    const __type10 RMPTR67;                                /* RMPTR67          */
    const __type10 RMDF067;                                /* RMDF067          */
    const __type10 RMDF167;                                /* RMDF167          */
    const __type10 RMID68;                                 /* RMID68           */
    const __type10 RMPTR68;                                /* RMPTR68          */
    const __type10 RMDF068;                                /* RMDF068          */
    const __type10 RMDF168;                                /* RMDF168          */
    const __type10 RMID69;                                 /* RMID69           */
    const __type10 RMPTR69;                                /* RMPTR69          */
    const __type10 RMDF069;                                /* RMDF069          */
    const __type10 RMDF169;                                /* RMDF169          */
    const __type10 RMID70;                                 /* RMID70           */
    const __type10 RMPTR70;                                /* RMPTR70          */
    const __type10 RMDF070;                                /* RMDF070          */
    const __type10 RMDF170;                                /* RMDF170          */
    const __type10 RMID71;                                 /* RMID71           */
    const __type10 RMPTR71;                                /* RMPTR71          */
    const __type10 RMDF071;                                /* RMDF071          */
    const __type10 RMDF171;                                /* RMDF171          */
    const __type10 RMID72;                                 /* RMID72           */
    const __type10 RMPTR72;                                /* RMPTR72          */
    const __type10 RMDF072;                                /* RMDF072          */
    const __type10 RMDF172;                                /* RMDF172          */
    const __type10 RMID73;                                 /* RMID73           */
    const __type10 RMPTR73;                                /* RMPTR73          */
    const __type10 RMDF073;                                /* RMDF073          */
    const __type10 RMDF173;                                /* RMDF173          */
    const __type10 RMID74;                                 /* RMID74           */
    const __type10 RMPTR74;                                /* RMPTR74          */
    const __type10 RMDF074;                                /* RMDF074          */
    const __type10 RMDF174;                                /* RMDF174          */
    const __type10 RMID75;                                 /* RMID75           */
    const __type10 RMPTR75;                                /* RMPTR75          */
    const __type10 RMDF075;                                /* RMDF075          */
    const __type10 RMDF175;                                /* RMDF175          */
    const __type10 RMID76;                                 /* RMID76           */
    const __type10 RMPTR76;                                /* RMPTR76          */
    const __type10 RMDF076;                                /* RMDF076          */
    const __type10 RMDF176;                                /* RMDF176          */
    const __type10 RMID77;                                 /* RMID77           */
    const __type10 RMPTR77;                                /* RMPTR77          */
    const __type10 RMDF077;                                /* RMDF077          */
    const __type10 RMDF177;                                /* RMDF177          */
    const __type10 RMID78;                                 /* RMID78           */
    const __type10 RMPTR78;                                /* RMPTR78          */
    const __type10 RMDF078;                                /* RMDF078          */
    const __type10 RMDF178;                                /* RMDF178          */
    const __type10 RMID79;                                 /* RMID79           */
    const __type10 RMPTR79;                                /* RMPTR79          */
    const __type10 RMDF079;                                /* RMDF079          */
    const __type10 RMDF179;                                /* RMDF179          */
    const __type10 RMID80;                                 /* RMID80           */
    const __type10 RMPTR80;                                /* RMPTR80          */
    const __type10 RMDF080;                                /* RMDF080          */
    const __type10 RMDF180;                                /* RMDF180          */
    const __type10 RMID81;                                 /* RMID81           */
    const __type10 RMPTR81;                                /* RMPTR81          */
    const __type10 RMDF081;                                /* RMDF081          */
    const __type10 RMDF181;                                /* RMDF181          */
    const __type10 RMID82;                                 /* RMID82           */
    const __type10 RMPTR82;                                /* RMPTR82          */
    const __type10 RMDF082;                                /* RMDF082          */
    const __type10 RMDF182;                                /* RMDF182          */
    const __type10 RMID83;                                 /* RMID83           */
    const __type10 RMPTR83;                                /* RMPTR83          */
    const __type10 RMDF083;                                /* RMDF083          */
    const __type10 RMDF183;                                /* RMDF183          */
    const __type10 RMID84;                                 /* RMID84           */
    const __type10 RMPTR84;                                /* RMPTR84          */
    const __type10 RMDF084;                                /* RMDF084          */
    const __type10 RMDF184;                                /* RMDF184          */
    const __type10 RMID85;                                 /* RMID85           */
    const __type10 RMPTR85;                                /* RMPTR85          */
    const __type10 RMDF085;                                /* RMDF085          */
    const __type10 RMDF185;                                /* RMDF185          */
    const __type10 RMID86;                                 /* RMID86           */
    const __type10 RMPTR86;                                /* RMPTR86          */
    const __type10 RMDF086;                                /* RMDF086          */
    const __type10 RMDF186;                                /* RMDF186          */
    const __type10 RMID87;                                 /* RMID87           */
    const __type10 RMPTR87;                                /* RMPTR87          */
    const __type10 RMDF087;                                /* RMDF087          */
    const __type10 RMDF187;                                /* RMDF187          */
    const __type10 RMID88;                                 /* RMID88           */
    const __type10 RMPTR88;                                /* RMPTR88          */
    const __type10 RMDF088;                                /* RMDF088          */
    const __type10 RMDF188;                                /* RMDF188          */
    const __type10 RMID89;                                 /* RMID89           */
    const __type10 RMPTR89;                                /* RMPTR89          */
    const __type10 RMDF089;                                /* RMDF089          */
    const __type10 RMDF189;                                /* RMDF189          */
    const __type10 RMID90;                                 /* RMID90           */
    const __type10 RMPTR90;                                /* RMPTR90          */
    const __type10 RMDF090;                                /* RMDF090          */
    const __type10 RMDF190;                                /* RMDF190          */
    const __type10 RMID91;                                 /* RMID91           */
    const __type10 RMPTR91;                                /* RMPTR91          */
    const __type10 RMDF091;                                /* RMDF091          */
    const __type10 RMDF191;                                /* RMDF191          */
    const __type10 RMID92;                                 /* RMID92           */
    const __type10 RMPTR92;                                /* RMPTR92          */
    const __type10 RMDF092;                                /* RMDF092          */
    const __type10 RMDF192;                                /* RMDF192          */
    const __type10 RMID93;                                 /* RMID93           */
    const __type10 RMPTR93;                                /* RMPTR93          */
    const __type10 RMDF093;                                /* RMDF093          */
    const __type10 RMDF193;                                /* RMDF193          */
    const __type10 RMID94;                                 /* RMID94           */
    const __type10 RMPTR94;                                /* RMPTR94          */
    const __type10 RMDF094;                                /* RMDF094          */
    const __type10 RMDF194;                                /* RMDF194          */
    const __type10 RMID95;                                 /* RMID95           */
    const __type10 RMPTR95;                                /* RMPTR95          */
    const __type10 RMDF095;                                /* RMDF095          */
    const __type10 RMDF195;                                /* RMDF195          */
    uint8  dummy54[512];                                   /* Reserved         */
    const __type10 RFID0;                                  /* RFID0            */
    const __type10 RFPTR0;                                 /* RFPTR0           */
    const __type10 RFDF00;                                 /* RFDF00           */
    const __type10 RFDF10;                                 /* RFDF10           */
    const __type10 RFID1;                                  /* RFID1            */
    const __type10 RFPTR1;                                 /* RFPTR1           */
    const __type10 RFDF01;                                 /* RFDF01           */
    const __type10 RFDF11;                                 /* RFDF11           */
    const __type10 RFID2;                                  /* RFID2            */
    const __type10 RFPTR2;                                 /* RFPTR2           */
    const __type10 RFDF02;                                 /* RFDF02           */
    const __type10 RFDF12;                                 /* RFDF12           */
    const __type10 RFID3;                                  /* RFID3            */
    const __type10 RFPTR3;                                 /* RFPTR3           */
    const __type10 RFDF03;                                 /* RFDF03           */
    const __type10 RFDF13;                                 /* RFDF13           */
    const __type10 RFID4;                                  /* RFID4            */
    const __type10 RFPTR4;                                 /* RFPTR4           */
    const __type10 RFDF04;                                 /* RFDF04           */
    const __type10 RFDF14;                                 /* RFDF14           */
    const __type10 RFID5;                                  /* RFID5            */
    const __type10 RFPTR5;                                 /* RFPTR5           */
    const __type10 RFDF05;                                 /* RFDF05           */
    const __type10 RFDF15;                                 /* RFDF15           */
    const __type10 RFID6;                                  /* RFID6            */
    const __type10 RFPTR6;                                 /* RFPTR6           */
    const __type10 RFDF06;                                 /* RFDF06           */
    const __type10 RFDF16;                                 /* RFDF16           */
    const __type10 RFID7;                                  /* RFID7            */
    const __type10 RFPTR7;                                 /* RFPTR7           */
    const __type10 RFDF07;                                 /* RFDF07           */
    const __type10 RFDF17;                                 /* RFDF17           */
    __type10 CFID0;                                        /* CFID0            */
    __type10 CFPTR0;                                       /* CFPTR0           */
    __type10 CFDF00;                                       /* CFDF00           */
    __type10 CFDF10;                                       /* CFDF10           */
    __type10 CFID1;                                        /* CFID1            */
    __type10 CFPTR1;                                       /* CFPTR1           */
    __type10 CFDF01;                                       /* CFDF01           */
    __type10 CFDF11;                                       /* CFDF11           */
    __type10 CFID2;                                        /* CFID2            */
    __type10 CFPTR2;                                       /* CFPTR2           */
    __type10 CFDF02;                                       /* CFDF02           */
    __type10 CFDF12;                                       /* CFDF12           */
    __type10 CFID3;                                        /* CFID3            */
    __type10 CFPTR3;                                       /* CFPTR3           */
    __type10 CFDF03;                                       /* CFDF03           */
    __type10 CFDF13;                                       /* CFDF13           */
    __type10 CFID4;                                        /* CFID4            */
    __type10 CFPTR4;                                       /* CFPTR4           */
    __type10 CFDF04;                                       /* CFDF04           */
    __type10 CFDF14;                                       /* CFDF14           */
    __type10 CFID5;                                        /* CFID5            */
    __type10 CFPTR5;                                       /* CFPTR5           */
    __type10 CFDF05;                                       /* CFDF05           */
    __type10 CFDF15;                                       /* CFDF15           */
    __type10 CFID6;                                        /* CFID6            */
    __type10 CFPTR6;                                       /* CFPTR6           */
    __type10 CFDF06;                                       /* CFDF06           */
    __type10 CFDF16;                                       /* CFDF16           */
    __type10 CFID7;                                        /* CFID7            */
    __type10 CFPTR7;                                       /* CFPTR7           */
    __type10 CFDF07;                                       /* CFDF07           */
    __type10 CFDF17;                                       /* CFDF17           */
    __type10 CFID8;                                        /* CFID8            */
    __type10 CFPTR8;                                       /* CFPTR8           */
    __type10 CFDF08;                                       /* CFDF08           */
    __type10 CFDF18;                                       /* CFDF18           */
    __type10 CFID9;                                        /* CFID9            */
    __type10 CFPTR9;                                       /* CFPTR9           */
    __type10 CFDF09;                                       /* CFDF09           */
    __type10 CFDF19;                                       /* CFDF19           */
    __type10 CFID10;                                       /* CFID10           */
    __type10 CFPTR10;                                      /* CFPTR10          */
    __type10 CFDF010;                                      /* CFDF010          */
    __type10 CFDF110;                                      /* CFDF110          */
    __type10 CFID11;                                       /* CFID11           */
    __type10 CFPTR11;                                      /* CFPTR11          */
    __type10 CFDF011;                                      /* CFDF011          */
    __type10 CFDF111;                                      /* CFDF111          */
    __type10 CFID12;                                       /* CFID12           */
    __type10 CFPTR12;                                      /* CFPTR12          */
    __type10 CFDF012;                                      /* CFDF012          */
    __type10 CFDF112;                                      /* CFDF112          */
    __type10 CFID13;                                       /* CFID13           */
    __type10 CFPTR13;                                      /* CFPTR13          */
    __type10 CFDF013;                                      /* CFDF013          */
    __type10 CFDF113;                                      /* CFDF113          */
    __type10 CFID14;                                       /* CFID14           */
    __type10 CFPTR14;                                      /* CFPTR14          */
    __type10 CFDF014;                                      /* CFDF014          */
    __type10 CFDF114;                                      /* CFDF114          */
    __type10 CFID15;                                       /* CFID15           */
    __type10 CFPTR15;                                      /* CFPTR15          */
    __type10 CFDF015;                                      /* CFDF015          */
    __type10 CFDF115;                                      /* CFDF115          */
    __type10 CFID16;                                       /* CFID16           */
    __type10 CFPTR16;                                      /* CFPTR16          */
    __type10 CFDF016;                                      /* CFDF016          */
    __type10 CFDF116;                                      /* CFDF116          */
    __type10 CFID17;                                       /* CFID17           */
    __type10 CFPTR17;                                      /* CFPTR17          */
    __type10 CFDF017;                                      /* CFDF017          */
    __type10 CFDF117;                                      /* CFDF117          */
    uint8  dummy55[96];                                    /* Reserved         */
    __type10 TMID0;                                        /* TMID0            */
    __type10 TMPTR0;                                       /* TMPTR0           */
    __type10 TMDF00;                                       /* TMDF00           */
    __type10 TMDF10;                                       /* TMDF10           */
    __type10 TMID1;                                        /* TMID1            */
    __type10 TMPTR1;                                       /* TMPTR1           */
    __type10 TMDF01;                                       /* TMDF01           */
    __type10 TMDF11;                                       /* TMDF11           */
    __type10 TMID2;                                        /* TMID2            */
    __type10 TMPTR2;                                       /* TMPTR2           */
    __type10 TMDF02;                                       /* TMDF02           */
    __type10 TMDF12;                                       /* TMDF12           */
    __type10 TMID3;                                        /* TMID3            */
    __type10 TMPTR3;                                       /* TMPTR3           */
    __type10 TMDF03;                                       /* TMDF03           */
    __type10 TMDF13;                                       /* TMDF13           */
    __type10 TMID4;                                        /* TMID4            */
    __type10 TMPTR4;                                       /* TMPTR4           */
    __type10 TMDF04;                                       /* TMDF04           */
    __type10 TMDF14;                                       /* TMDF14           */
    __type10 TMID5;                                        /* TMID5            */
    __type10 TMPTR5;                                       /* TMPTR5           */
    __type10 TMDF05;                                       /* TMDF05           */
    __type10 TMDF15;                                       /* TMDF15           */
    __type10 TMID6;                                        /* TMID6            */
    __type10 TMPTR6;                                       /* TMPTR6           */
    __type10 TMDF06;                                       /* TMDF06           */
    __type10 TMDF16;                                       /* TMDF16           */
    __type10 TMID7;                                        /* TMID7            */
    __type10 TMPTR7;                                       /* TMPTR7           */
    __type10 TMDF07;                                       /* TMDF07           */
    __type10 TMDF17;                                       /* TMDF17           */
    __type10 TMID8;                                        /* TMID8            */
    __type10 TMPTR8;                                       /* TMPTR8           */
    __type10 TMDF08;                                       /* TMDF08           */
    __type10 TMDF18;                                       /* TMDF18           */
    __type10 TMID9;                                        /* TMID9            */
    __type10 TMPTR9;                                       /* TMPTR9           */
    __type10 TMDF09;                                       /* TMDF09           */
    __type10 TMDF19;                                       /* TMDF19           */
    __type10 TMID10;                                       /* TMID10           */
    __type10 TMPTR10;                                      /* TMPTR10          */
    __type10 TMDF010;                                      /* TMDF010          */
    __type10 TMDF110;                                      /* TMDF110          */
    __type10 TMID11;                                       /* TMID11           */
    __type10 TMPTR11;                                      /* TMPTR11          */
    __type10 TMDF011;                                      /* TMDF011          */
    __type10 TMDF111;                                      /* TMDF111          */
    __type10 TMID12;                                       /* TMID12           */
    __type10 TMPTR12;                                      /* TMPTR12          */
    __type10 TMDF012;                                      /* TMDF012          */
    __type10 TMDF112;                                      /* TMDF112          */
    __type10 TMID13;                                       /* TMID13           */
    __type10 TMPTR13;                                      /* TMPTR13          */
    __type10 TMDF013;                                      /* TMDF013          */
    __type10 TMDF113;                                      /* TMDF113          */
    __type10 TMID14;                                       /* TMID14           */
    __type10 TMPTR14;                                      /* TMPTR14          */
    __type10 TMDF014;                                      /* TMDF014          */
    __type10 TMDF114;                                      /* TMDF114          */
    __type10 TMID15;                                       /* TMID15           */
    __type10 TMPTR15;                                      /* TMPTR15          */
    __type10 TMDF015;                                      /* TMDF015          */
    __type10 TMDF115;                                      /* TMDF115          */
    __type10 TMID16;                                       /* TMID16           */
    __type10 TMPTR16;                                      /* TMPTR16          */
    __type10 TMDF016;                                      /* TMDF016          */
    __type10 TMDF116;                                      /* TMDF116          */
    __type10 TMID17;                                       /* TMID17           */
    __type10 TMPTR17;                                      /* TMPTR17          */
    __type10 TMDF017;                                      /* TMDF017          */
    __type10 TMDF117;                                      /* TMDF117          */
    __type10 TMID18;                                       /* TMID18           */
    __type10 TMPTR18;                                      /* TMPTR18          */
    __type10 TMDF018;                                      /* TMDF018          */
    __type10 TMDF118;                                      /* TMDF118          */
    __type10 TMID19;                                       /* TMID19           */
    __type10 TMPTR19;                                      /* TMPTR19          */
    __type10 TMDF019;                                      /* TMDF019          */
    __type10 TMDF119;                                      /* TMDF119          */
    __type10 TMID20;                                       /* TMID20           */
    __type10 TMPTR20;                                      /* TMPTR20          */
    __type10 TMDF020;                                      /* TMDF020          */
    __type10 TMDF120;                                      /* TMDF120          */
    __type10 TMID21;                                       /* TMID21           */
    __type10 TMPTR21;                                      /* TMPTR21          */
    __type10 TMDF021;                                      /* TMDF021          */
    __type10 TMDF121;                                      /* TMDF121          */
    __type10 TMID22;                                       /* TMID22           */
    __type10 TMPTR22;                                      /* TMPTR22          */
    __type10 TMDF022;                                      /* TMDF022          */
    __type10 TMDF122;                                      /* TMDF122          */
    __type10 TMID23;                                       /* TMID23           */
    __type10 TMPTR23;                                      /* TMPTR23          */
    __type10 TMDF023;                                      /* TMDF023          */
    __type10 TMDF123;                                      /* TMDF123          */
    __type10 TMID24;                                       /* TMID24           */
    __type10 TMPTR24;                                      /* TMPTR24          */
    __type10 TMDF024;                                      /* TMDF024          */
    __type10 TMDF124;                                      /* TMDF124          */
    __type10 TMID25;                                       /* TMID25           */
    __type10 TMPTR25;                                      /* TMPTR25          */
    __type10 TMDF025;                                      /* TMDF025          */
    __type10 TMDF125;                                      /* TMDF125          */
    __type10 TMID26;                                       /* TMID26           */
    __type10 TMPTR26;                                      /* TMPTR26          */
    __type10 TMDF026;                                      /* TMDF026          */
    __type10 TMDF126;                                      /* TMDF126          */
    __type10 TMID27;                                       /* TMID27           */
    __type10 TMPTR27;                                      /* TMPTR27          */
    __type10 TMDF027;                                      /* TMDF027          */
    __type10 TMDF127;                                      /* TMDF127          */
    __type10 TMID28;                                       /* TMID28           */
    __type10 TMPTR28;                                      /* TMPTR28          */
    __type10 TMDF028;                                      /* TMDF028          */
    __type10 TMDF128;                                      /* TMDF128          */
    __type10 TMID29;                                       /* TMID29           */
    __type10 TMPTR29;                                      /* TMPTR29          */
    __type10 TMDF029;                                      /* TMDF029          */
    __type10 TMDF129;                                      /* TMDF129          */
    __type10 TMID30;                                       /* TMID30           */
    __type10 TMPTR30;                                      /* TMPTR30          */
    __type10 TMDF030;                                      /* TMDF030          */
    __type10 TMDF130;                                      /* TMDF130          */
    __type10 TMID31;                                       /* TMID31           */
    __type10 TMPTR31;                                      /* TMPTR31          */
    __type10 TMDF031;                                      /* TMDF031          */
    __type10 TMDF131;                                      /* TMDF131          */
    __type10 TMID32;                                       /* TMID32           */
    __type10 TMPTR32;                                      /* TMPTR32          */
    __type10 TMDF032;                                      /* TMDF032          */
    __type10 TMDF132;                                      /* TMDF132          */
    __type10 TMID33;                                       /* TMID33           */
    __type10 TMPTR33;                                      /* TMPTR33          */
    __type10 TMDF033;                                      /* TMDF033          */
    __type10 TMDF133;                                      /* TMDF133          */
    __type10 TMID34;                                       /* TMID34           */
    __type10 TMPTR34;                                      /* TMPTR34          */
    __type10 TMDF034;                                      /* TMDF034          */
    __type10 TMDF134;                                      /* TMDF134          */
    __type10 TMID35;                                       /* TMID35           */
    __type10 TMPTR35;                                      /* TMPTR35          */
    __type10 TMDF035;                                      /* TMDF035          */
    __type10 TMDF135;                                      /* TMDF135          */
    __type10 TMID36;                                       /* TMID36           */
    __type10 TMPTR36;                                      /* TMPTR36          */
    __type10 TMDF036;                                      /* TMDF036          */
    __type10 TMDF136;                                      /* TMDF136          */
    __type10 TMID37;                                       /* TMID37           */
    __type10 TMPTR37;                                      /* TMPTR37          */
    __type10 TMDF037;                                      /* TMDF037          */
    __type10 TMDF137;                                      /* TMDF137          */
    __type10 TMID38;                                       /* TMID38           */
    __type10 TMPTR38;                                      /* TMPTR38          */
    __type10 TMDF038;                                      /* TMDF038          */
    __type10 TMDF138;                                      /* TMDF138          */
    __type10 TMID39;                                       /* TMID39           */
    __type10 TMPTR39;                                      /* TMPTR39          */
    __type10 TMDF039;                                      /* TMDF039          */
    __type10 TMDF139;                                      /* TMDF139          */
    __type10 TMID40;                                       /* TMID40           */
    __type10 TMPTR40;                                      /* TMPTR40          */
    __type10 TMDF040;                                      /* TMDF040          */
    __type10 TMDF140;                                      /* TMDF140          */
    __type10 TMID41;                                       /* TMID41           */
    __type10 TMPTR41;                                      /* TMPTR41          */
    __type10 TMDF041;                                      /* TMDF041          */
    __type10 TMDF141;                                      /* TMDF141          */
    __type10 TMID42;                                       /* TMID42           */
    __type10 TMPTR42;                                      /* TMPTR42          */
    __type10 TMDF042;                                      /* TMDF042          */
    __type10 TMDF142;                                      /* TMDF142          */
    __type10 TMID43;                                       /* TMID43           */
    __type10 TMPTR43;                                      /* TMPTR43          */
    __type10 TMDF043;                                      /* TMDF043          */
    __type10 TMDF143;                                      /* TMDF143          */
    __type10 TMID44;                                       /* TMID44           */
    __type10 TMPTR44;                                      /* TMPTR44          */
    __type10 TMDF044;                                      /* TMDF044          */
    __type10 TMDF144;                                      /* TMDF144          */
    __type10 TMID45;                                       /* TMID45           */
    __type10 TMPTR45;                                      /* TMPTR45          */
    __type10 TMDF045;                                      /* TMDF045          */
    __type10 TMDF145;                                      /* TMDF145          */
    __type10 TMID46;                                       /* TMID46           */
    __type10 TMPTR46;                                      /* TMPTR46          */
    __type10 TMDF046;                                      /* TMDF046          */
    __type10 TMDF146;                                      /* TMDF146          */
    __type10 TMID47;                                       /* TMID47           */
    __type10 TMPTR47;                                      /* TMPTR47          */
    __type10 TMDF047;                                      /* TMDF047          */
    __type10 TMDF147;                                      /* TMDF147          */
    __type10 TMID48;                                       /* TMID48           */
    __type10 TMPTR48;                                      /* TMPTR48          */
    __type10 TMDF048;                                      /* TMDF048          */
    __type10 TMDF148;                                      /* TMDF148          */
    __type10 TMID49;                                       /* TMID49           */
    __type10 TMPTR49;                                      /* TMPTR49          */
    __type10 TMDF049;                                      /* TMDF049          */
    __type10 TMDF149;                                      /* TMDF149          */
    __type10 TMID50;                                       /* TMID50           */
    __type10 TMPTR50;                                      /* TMPTR50          */
    __type10 TMDF050;                                      /* TMDF050          */
    __type10 TMDF150;                                      /* TMDF150          */
    __type10 TMID51;                                       /* TMID51           */
    __type10 TMPTR51;                                      /* TMPTR51          */
    __type10 TMDF051;                                      /* TMDF051          */
    __type10 TMDF151;                                      /* TMDF151          */
    __type10 TMID52;                                       /* TMID52           */
    __type10 TMPTR52;                                      /* TMPTR52          */
    __type10 TMDF052;                                      /* TMDF052          */
    __type10 TMDF152;                                      /* TMDF152          */
    __type10 TMID53;                                       /* TMID53           */
    __type10 TMPTR53;                                      /* TMPTR53          */
    __type10 TMDF053;                                      /* TMDF053          */
    __type10 TMDF153;                                      /* TMDF153          */
    __type10 TMID54;                                       /* TMID54           */
    __type10 TMPTR54;                                      /* TMPTR54          */
    __type10 TMDF054;                                      /* TMDF054          */
    __type10 TMDF154;                                      /* TMDF154          */
    __type10 TMID55;                                       /* TMID55           */
    __type10 TMPTR55;                                      /* TMPTR55          */
    __type10 TMDF055;                                      /* TMDF055          */
    __type10 TMDF155;                                      /* TMDF155          */
    __type10 TMID56;                                       /* TMID56           */
    __type10 TMPTR56;                                      /* TMPTR56          */
    __type10 TMDF056;                                      /* TMDF056          */
    __type10 TMDF156;                                      /* TMDF156          */
    __type10 TMID57;                                       /* TMID57           */
    __type10 TMPTR57;                                      /* TMPTR57          */
    __type10 TMDF057;                                      /* TMDF057          */
    __type10 TMDF157;                                      /* TMDF157          */
    __type10 TMID58;                                       /* TMID58           */
    __type10 TMPTR58;                                      /* TMPTR58          */
    __type10 TMDF058;                                      /* TMDF058          */
    __type10 TMDF158;                                      /* TMDF158          */
    __type10 TMID59;                                       /* TMID59           */
    __type10 TMPTR59;                                      /* TMPTR59          */
    __type10 TMDF059;                                      /* TMDF059          */
    __type10 TMDF159;                                      /* TMDF159          */
    __type10 TMID60;                                       /* TMID60           */
    __type10 TMPTR60;                                      /* TMPTR60          */
    __type10 TMDF060;                                      /* TMDF060          */
    __type10 TMDF160;                                      /* TMDF160          */
    __type10 TMID61;                                       /* TMID61           */
    __type10 TMPTR61;                                      /* TMPTR61          */
    __type10 TMDF061;                                      /* TMDF061          */
    __type10 TMDF161;                                      /* TMDF161          */
    __type10 TMID62;                                       /* TMID62           */
    __type10 TMPTR62;                                      /* TMPTR62          */
    __type10 TMDF062;                                      /* TMDF062          */
    __type10 TMDF162;                                      /* TMDF162          */
    __type10 TMID63;                                       /* TMID63           */
    __type10 TMPTR63;                                      /* TMPTR63          */
    __type10 TMDF063;                                      /* TMDF063          */
    __type10 TMDF163;                                      /* TMDF163          */
    __type10 TMID64;                                       /* TMID64           */
    __type10 TMPTR64;                                      /* TMPTR64          */
    __type10 TMDF064;                                      /* TMDF064          */
    __type10 TMDF164;                                      /* TMDF164          */
    __type10 TMID65;                                       /* TMID65           */
    __type10 TMPTR65;                                      /* TMPTR65          */
    __type10 TMDF065;                                      /* TMDF065          */
    __type10 TMDF165;                                      /* TMDF165          */
    __type10 TMID66;                                       /* TMID66           */
    __type10 TMPTR66;                                      /* TMPTR66          */
    __type10 TMDF066;                                      /* TMDF066          */
    __type10 TMDF166;                                      /* TMDF166          */
    __type10 TMID67;                                       /* TMID67           */
    __type10 TMPTR67;                                      /* TMPTR67          */
    __type10 TMDF067;                                      /* TMDF067          */
    __type10 TMDF167;                                      /* TMDF167          */
    __type10 TMID68;                                       /* TMID68           */
    __type10 TMPTR68;                                      /* TMPTR68          */
    __type10 TMDF068;                                      /* TMDF068          */
    __type10 TMDF168;                                      /* TMDF168          */
    __type10 TMID69;                                       /* TMID69           */
    __type10 TMPTR69;                                      /* TMPTR69          */
    __type10 TMDF069;                                      /* TMDF069          */
    __type10 TMDF169;                                      /* TMDF169          */
    __type10 TMID70;                                       /* TMID70           */
    __type10 TMPTR70;                                      /* TMPTR70          */
    __type10 TMDF070;                                      /* TMDF070          */
    __type10 TMDF170;                                      /* TMDF170          */
    __type10 TMID71;                                       /* TMID71           */
    __type10 TMPTR71;                                      /* TMPTR71          */
    __type10 TMDF071;                                      /* TMDF071          */
    __type10 TMDF171;                                      /* TMDF171          */
    __type10 TMID72;                                       /* TMID72           */
    __type10 TMPTR72;                                      /* TMPTR72          */
    __type10 TMDF072;                                      /* TMDF072          */
    __type10 TMDF172;                                      /* TMDF172          */
    __type10 TMID73;                                       /* TMID73           */
    __type10 TMPTR73;                                      /* TMPTR73          */
    __type10 TMDF073;                                      /* TMDF073          */
    __type10 TMDF173;                                      /* TMDF173          */
    __type10 TMID74;                                       /* TMID74           */
    __type10 TMPTR74;                                      /* TMPTR74          */
    __type10 TMDF074;                                      /* TMDF074          */
    __type10 TMDF174;                                      /* TMDF174          */
    __type10 TMID75;                                       /* TMID75           */
    __type10 TMPTR75;                                      /* TMPTR75          */
    __type10 TMDF075;                                      /* TMDF075          */
    __type10 TMDF175;                                      /* TMDF175          */
    __type10 TMID76;                                       /* TMID76           */
    __type10 TMPTR76;                                      /* TMPTR76          */
    __type10 TMDF076;                                      /* TMDF076          */
    __type10 TMDF176;                                      /* TMDF176          */
    __type10 TMID77;                                       /* TMID77           */
    __type10 TMPTR77;                                      /* TMPTR77          */
    __type10 TMDF077;                                      /* TMDF077          */
    __type10 TMDF177;                                      /* TMDF177          */
    __type10 TMID78;                                       /* TMID78           */
    __type10 TMPTR78;                                      /* TMPTR78          */
    __type10 TMDF078;                                      /* TMDF078          */
    __type10 TMDF178;                                      /* TMDF178          */
    __type10 TMID79;                                       /* TMID79           */
    __type10 TMPTR79;                                      /* TMPTR79          */
    __type10 TMDF079;                                      /* TMDF079          */
    __type10 TMDF179;                                      /* TMDF179          */
    __type10 TMID80;                                       /* TMID80           */
    __type10 TMPTR80;                                      /* TMPTR80          */
    __type10 TMDF080;                                      /* TMDF080          */
    __type10 TMDF180;                                      /* TMDF180          */
    __type10 TMID81;                                       /* TMID81           */
    __type10 TMPTR81;                                      /* TMPTR81          */
    __type10 TMDF081;                                      /* TMDF081          */
    __type10 TMDF181;                                      /* TMDF181          */
    __type10 TMID82;                                       /* TMID82           */
    __type10 TMPTR82;                                      /* TMPTR82          */
    __type10 TMDF082;                                      /* TMDF082          */
    __type10 TMDF182;                                      /* TMDF182          */
    __type10 TMID83;                                       /* TMID83           */
    __type10 TMPTR83;                                      /* TMPTR83          */
    __type10 TMDF083;                                      /* TMDF083          */
    __type10 TMDF183;                                      /* TMDF183          */
    __type10 TMID84;                                       /* TMID84           */
    __type10 TMPTR84;                                      /* TMPTR84          */
    __type10 TMDF084;                                      /* TMDF084          */
    __type10 TMDF184;                                      /* TMDF184          */
    __type10 TMID85;                                       /* TMID85           */
    __type10 TMPTR85;                                      /* TMPTR85          */
    __type10 TMDF085;                                      /* TMDF085          */
    __type10 TMDF185;                                      /* TMDF185          */
    __type10 TMID86;                                       /* TMID86           */
    __type10 TMPTR86;                                      /* TMPTR86          */
    __type10 TMDF086;                                      /* TMDF086          */
    __type10 TMDF186;                                      /* TMDF186          */
    __type10 TMID87;                                       /* TMID87           */
    __type10 TMPTR87;                                      /* TMPTR87          */
    __type10 TMDF087;                                      /* TMDF087          */
    __type10 TMDF187;                                      /* TMDF187          */
    __type10 TMID88;                                       /* TMID88           */
    __type10 TMPTR88;                                      /* TMPTR88          */
    __type10 TMDF088;                                      /* TMDF088          */
    __type10 TMDF188;                                      /* TMDF188          */
    __type10 TMID89;                                       /* TMID89           */
    __type10 TMPTR89;                                      /* TMPTR89          */
    __type10 TMDF089;                                      /* TMDF089          */
    __type10 TMDF189;                                      /* TMDF189          */
    __type10 TMID90;                                       /* TMID90           */
    __type10 TMPTR90;                                      /* TMPTR90          */
    __type10 TMDF090;                                      /* TMDF090          */
    __type10 TMDF190;                                      /* TMDF190          */
    __type10 TMID91;                                       /* TMID91           */
    __type10 TMPTR91;                                      /* TMPTR91          */
    __type10 TMDF091;                                      /* TMDF091          */
    __type10 TMDF191;                                      /* TMDF191          */
    __type10 TMID92;                                       /* TMID92           */
    __type10 TMPTR92;                                      /* TMPTR92          */
    __type10 TMDF092;                                      /* TMDF092          */
    __type10 TMDF192;                                      /* TMDF192          */
    __type10 TMID93;                                       /* TMID93           */
    __type10 TMPTR93;                                      /* TMPTR93          */
    __type10 TMDF093;                                      /* TMDF093          */
    __type10 TMDF193;                                      /* TMDF193          */
    __type10 TMID94;                                       /* TMID94           */
    __type10 TMPTR94;                                      /* TMPTR94          */
    __type10 TMDF094;                                      /* TMDF094          */
    __type10 TMDF194;                                      /* TMDF194          */
    __type10 TMID95;                                       /* TMID95           */
    __type10 TMPTR95;                                      /* TMPTR95          */
    __type10 TMDF095;                                      /* TMDF095          */
    __type10 TMDF195;                                      /* TMDF195          */
    uint8  dummy56[512];                                   /* Reserved         */
    const __type10 THLACC0;                                /* THLACC0          */
    const __type10 THLACC1;                                /* THLACC1          */
    const __type10 THLACC2;                                /* THLACC2          */
    const __type10 THLACC3;                                /* THLACC3          */
    const __type10 THLACC4;                                /* THLACC4          */
    const __type10 THLACC5;                                /* THLACC5          */
    uint8  dummy57[232];                                   /* Reserved         */
    __type10 RPGACC0;                                      /* RPGACC0          */
    __type10 RPGACC1;                                      /* RPGACC1          */
    __type10 RPGACC2;                                      /* RPGACC2          */
    __type10 RPGACC3;                                      /* RPGACC3          */
    __type10 RPGACC4;                                      /* RPGACC4          */
    __type10 RPGACC5;                                      /* RPGACC5          */
    __type10 RPGACC6;                                      /* RPGACC6          */
    __type10 RPGACC7;                                      /* RPGACC7          */
    __type10 RPGACC8;                                      /* RPGACC8          */
    __type10 RPGACC9;                                      /* RPGACC9          */
    __type10 RPGACC10;                                     /* RPGACC10         */
    __type10 RPGACC11;                                     /* RPGACC11         */
    __type10 RPGACC12;                                     /* RPGACC12         */
    __type10 RPGACC13;                                     /* RPGACC13         */
    __type10 RPGACC14;                                     /* RPGACC14         */
    __type10 RPGACC15;                                     /* RPGACC15         */
    __type10 RPGACC16;                                     /* RPGACC16         */
    __type10 RPGACC17;                                     /* RPGACC17         */
    __type10 RPGACC18;                                     /* RPGACC18         */
    __type10 RPGACC19;                                     /* RPGACC19         */
    __type10 RPGACC20;                                     /* RPGACC20         */
    __type10 RPGACC21;                                     /* RPGACC21         */
    __type10 RPGACC22;                                     /* RPGACC22         */
    __type10 RPGACC23;                                     /* RPGACC23         */
    __type10 RPGACC24;                                     /* RPGACC24         */
    __type10 RPGACC25;                                     /* RPGACC25         */
    __type10 RPGACC26;                                     /* RPGACC26         */
    __type10 RPGACC27;                                     /* RPGACC27         */
    __type10 RPGACC28;                                     /* RPGACC28         */
    __type10 RPGACC29;                                     /* RPGACC29         */
    __type10 RPGACC30;                                     /* RPGACC30         */
    __type10 RPGACC31;                                     /* RPGACC31         */
    __type10 RPGACC32;                                     /* RPGACC32         */
    __type10 RPGACC33;                                     /* RPGACC33         */
    __type10 RPGACC34;                                     /* RPGACC34         */
    __type10 RPGACC35;                                     /* RPGACC35         */
    __type10 RPGACC36;                                     /* RPGACC36         */
    __type10 RPGACC37;                                     /* RPGACC37         */
    __type10 RPGACC38;                                     /* RPGACC38         */
    __type10 RPGACC39;                                     /* RPGACC39         */
    __type10 RPGACC40;                                     /* RPGACC40         */
    __type10 RPGACC41;                                     /* RPGACC41         */
    __type10 RPGACC42;                                     /* RPGACC42         */
    __type10 RPGACC43;                                     /* RPGACC43         */
    __type10 RPGACC44;                                     /* RPGACC44         */
    __type10 RPGACC45;                                     /* RPGACC45         */
    __type10 RPGACC46;                                     /* RPGACC46         */
    __type10 RPGACC47;                                     /* RPGACC47         */
    __type10 RPGACC48;                                     /* RPGACC48         */
    __type10 RPGACC49;                                     /* RPGACC49         */
    __type10 RPGACC50;                                     /* RPGACC50         */
    __type10 RPGACC51;                                     /* RPGACC51         */
    __type10 RPGACC52;                                     /* RPGACC52         */
    __type10 RPGACC53;                                     /* RPGACC53         */
    __type10 RPGACC54;                                     /* RPGACC54         */
    __type10 RPGACC55;                                     /* RPGACC55         */
    __type10 RPGACC56;                                     /* RPGACC56         */
    __type10 RPGACC57;                                     /* RPGACC57         */
    __type10 RPGACC58;                                     /* RPGACC58         */
    __type10 RPGACC59;                                     /* RPGACC59         */
    __type10 RPGACC60;                                     /* RPGACC60         */
    __type10 RPGACC61;                                     /* RPGACC61         */
    __type10 RPGACC62;                                     /* RPGACC62         */
    __type10 RPGACC63;                                     /* RPGACC63         */
} __type36;
typedef struct 
{                                                          /* Module           */
    __type16 CTL0;                                         /* CTL0             */
    uint8  dummy58[3];                                     /* Reserved         */
    const uint32 STR0;                                     /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy59[6];                                     /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy60[2];                                     /* Reserved         */
    __type17 EMU;                                          /* EMU              */
    uint8  dummy61[4071];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy62[2];                                     /* Reserved         */
    const uint32 RX0W;                                     /* RX0W             */
    const uint16 RX0H;                                     /* RX0H             */
    uint8  dummy63[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint8  dummy64[36];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy65[2];                                     /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint32 CFG4;                                           /* CFG4             */
    uint32 CFG5;                                           /* CFG5             */
    uint32 CFG6;                                           /* CFG6             */
    uint32 CFG7;                                           /* CFG7             */
    uint8  dummy66[4];                                     /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy67[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy68[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy69[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} __type37;
typedef struct 
{                                                          /* Module           */
    __type16 CTL0;                                         /* CTL0             */
    uint8  dummy70[3];                                     /* Reserved         */
    const uint32 STR0;                                     /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy71[6];                                     /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy72[2];                                     /* Reserved         */
    __type17 EMU;                                          /* EMU              */
    uint8  dummy73[4071];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy74[2];                                     /* Reserved         */
    const uint32 RX0W;                                     /* RX0W             */
    const uint16 RX0H;                                     /* RX0H             */
    uint8  dummy75[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint8  dummy76[36];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy77[2];                                     /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint32 CFG4;                                           /* CFG4             */
    uint32 CFG5;                                           /* CFG5             */
    uint8  dummy78[12];                                    /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy79[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy80[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy81[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} __type38;
typedef struct 
{                                                          /* Module           */
    __type16 CTL0;                                         /* CTL0             */
    uint8  dummy82[3];                                     /* Reserved         */
    const uint32 STR0;                                     /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy83[6];                                     /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy84[2];                                     /* Reserved         */
    __type17 EMU;                                          /* EMU              */
    uint8  dummy85[4071];                                  /* Reserved         */
    uint32 MCTL1;                                          /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy86[2];                                     /* Reserved         */
    const uint32 RX0W;                                     /* RX0W             */
    const uint16 RX0H;                                     /* RX0H             */
    uint8  dummy87[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint8  dummy88[36];                                    /* Reserved         */
    uint16 MCTL0;                                          /* MCTL0            */
    uint8  dummy89[2];                                     /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint32 CFG1;                                           /* CFG1             */
    uint32 CFG2;                                           /* CFG2             */
    uint32 CFG3;                                           /* CFG3             */
    uint8  dummy90[20];                                    /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy91[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy92[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy93[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} __type39;
typedef struct 
{                                                          /* Module           */
    __type18 CTL0;                                         /* CTL0             */
    uint8  dummy94[3];                                     /* Reserved         */
    const uint32 STR0;                                     /* STR0             */
    uint16 STCR0;                                          /* STCR0            */
    uint8  dummy95[6];                                     /* Reserved         */
    uint32 CTL1;                                           /* CTL1             */
    uint16 CTL2;                                           /* CTL2             */
    uint8  dummy96[2];                                     /* Reserved         */
    __type17 EMU;                                          /* EMU              */
    uint8  dummy97[4071];                                  /* Reserved         */
    __type19 BCTL0;                                        /* BCTL0            */
    uint8  dummy98[3];                                     /* Reserved         */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy99[2];                                     /* Reserved         */
    const uint16 RX0;                                      /* RX0              */
    uint8  dummy100[2];                                    /* Reserved         */
    uint32 CFG0;                                           /* CFG0             */
    uint8  dummy101[4076];                                 /* Reserved         */
} __type40;
typedef struct 
{                                                          /* Module           */
    uint8  SST;                                            /* SST              */
    uint8  dummy102[11];                                   /* Reserved         */
    uint16 SSER0;                                          /* SSER0            */
    uint8  dummy103[6];                                    /* Reserved         */
    uint16 SSER2;                                          /* SSER2            */
    uint8  dummy104[102];                                  /* Reserved         */
    uint8  HIZCEN0;                                        /* HIZCEN0          */
    uint8  dummy105[15];                                   /* Reserved         */
    uint16 ADTEN400;                                       /* ADTEN400         */
    uint8  dummy106[2];                                    /* Reserved         */
    uint16 ADTEN401;                                       /* ADTEN401         */
    uint8  dummy107[2];                                    /* Reserved         */
    uint16 ADTEN402;                                       /* ADTEN402         */
    uint8  dummy108[38];                                   /* Reserved         */
    uint32 REG200;                                         /* REG200           */
    uint32 REG201;                                         /* REG201           */
    uint32 REG202;                                         /* REG202           */
    uint32 REG203;                                         /* REG203           */
    uint8  dummy109[24];                                   /* Reserved         */
    uint32 REG30;                                          /* REG30            */
    uint32 REG31;                                          /* REG31            */
} __type41;
typedef struct 
{                                                          /* Module           */
    uint16 CDR0;                                           /* CDR0             */
    uint8  dummy110[2];                                    /* Reserved         */
    uint16 CDR1;                                           /* CDR1             */
    uint8  dummy111[2];                                    /* Reserved         */
    uint16 CDR2;                                           /* CDR2             */
    uint8  dummy112[2];                                    /* Reserved         */
    uint16 CDR3;                                           /* CDR3             */
    uint8  dummy113[2];                                    /* Reserved         */
    uint16 CDR4;                                           /* CDR4             */
    uint8  dummy114[2];                                    /* Reserved         */
    uint16 CDR5;                                           /* CDR5             */
    uint8  dummy115[2];                                    /* Reserved         */
    uint16 CDR6;                                           /* CDR6             */
    uint8  dummy116[2];                                    /* Reserved         */
    uint16 CDR7;                                           /* CDR7             */
    uint8  dummy117[2];                                    /* Reserved         */
    uint16 CDR8;                                           /* CDR8             */
    uint8  dummy118[2];                                    /* Reserved         */
    uint16 CDR9;                                           /* CDR9             */
    uint8  dummy119[2];                                    /* Reserved         */
    uint16 CDR10;                                          /* CDR10            */
    uint8  dummy120[2];                                    /* Reserved         */
    uint16 CDR11;                                          /* CDR11            */
    uint8  dummy121[2];                                    /* Reserved         */
    uint16 CDR12;                                          /* CDR12            */
    uint8  dummy122[2];                                    /* Reserved         */
    uint16 CDR13;                                          /* CDR13            */
    uint8  dummy123[2];                                    /* Reserved         */
    uint16 CDR14;                                          /* CDR14            */
    uint8  dummy124[2];                                    /* Reserved         */
    uint16 CDR15;                                          /* CDR15            */
    uint8  dummy125[2];                                    /* Reserved         */
    uint16 TOL;                                            /* TOL              */
    uint8  dummy126[2];                                    /* Reserved         */
    uint16 RDT;                                            /* RDT              */
    uint8  dummy127[2];                                    /* Reserved         */
    const uint16 RSF;                                      /* RSF              */
    uint8  dummy128[2];                                    /* Reserved         */
    uint16 TRO;                                            /* TRO              */
    uint8  dummy129[2];                                    /* Reserved         */
    uint16 TME;                                            /* TME              */
    uint8  dummy130[2];                                    /* Reserved         */
    uint16 TDL;                                            /* TDL              */
    uint8  dummy131[2];                                    /* Reserved         */
    uint16 TO;                                             /* TO               */
    uint8  dummy132[2];                                    /* Reserved         */
    uint16 TOE;                                            /* TOE              */
    uint8  dummy133[34];                                   /* Reserved         */
    const uint16 CNT0;                                     /* CNT0             */
    uint8  dummy134[2];                                    /* Reserved         */
    const uint16 CNT1;                                     /* CNT1             */
    uint8  dummy135[2];                                    /* Reserved         */
    const uint16 CNT2;                                     /* CNT2             */
    uint8  dummy136[2];                                    /* Reserved         */
    const uint16 CNT3;                                     /* CNT3             */
    uint8  dummy137[2];                                    /* Reserved         */
    const uint16 CNT4;                                     /* CNT4             */
    uint8  dummy138[2];                                    /* Reserved         */
    const uint16 CNT5;                                     /* CNT5             */
    uint8  dummy139[2];                                    /* Reserved         */
    const uint16 CNT6;                                     /* CNT6             */
    uint8  dummy140[2];                                    /* Reserved         */
    const uint16 CNT7;                                     /* CNT7             */
    uint8  dummy141[2];                                    /* Reserved         */
    const uint16 CNT8;                                     /* CNT8             */
    uint8  dummy142[2];                                    /* Reserved         */
    const uint16 CNT9;                                     /* CNT9             */
    uint8  dummy143[2];                                    /* Reserved         */
    const uint16 CNT10;                                    /* CNT10            */
    uint8  dummy144[2];                                    /* Reserved         */
    const uint16 CNT11;                                    /* CNT11            */
    uint8  dummy145[2];                                    /* Reserved         */
    const uint16 CNT12;                                    /* CNT12            */
    uint8  dummy146[2];                                    /* Reserved         */
    const uint16 CNT13;                                    /* CNT13            */
    uint8  dummy147[2];                                    /* Reserved         */
    const uint16 CNT14;                                    /* CNT14            */
    uint8  dummy148[2];                                    /* Reserved         */
    const uint16 CNT15;                                    /* CNT15            */
    uint8  dummy149[2];                                    /* Reserved         */
    uint8  CMUR0;                                          /* CMUR0            */
    uint8  dummy150[3];                                    /* Reserved         */
    uint8  CMUR1;                                          /* CMUR1            */
    uint8  dummy151[3];                                    /* Reserved         */
    uint8  CMUR2;                                          /* CMUR2            */
    uint8  dummy152[3];                                    /* Reserved         */
    uint8  CMUR3;                                          /* CMUR3            */
    uint8  dummy153[3];                                    /* Reserved         */
    uint8  CMUR4;                                          /* CMUR4            */
    uint8  dummy154[3];                                    /* Reserved         */
    uint8  CMUR5;                                          /* CMUR5            */
    uint8  dummy155[3];                                    /* Reserved         */
    uint8  CMUR6;                                          /* CMUR6            */
    uint8  dummy156[3];                                    /* Reserved         */
    uint8  CMUR7;                                          /* CMUR7            */
    uint8  dummy157[3];                                    /* Reserved         */
    uint8  CMUR8;                                          /* CMUR8            */
    uint8  dummy158[3];                                    /* Reserved         */
    uint8  CMUR9;                                          /* CMUR9            */
    uint8  dummy159[3];                                    /* Reserved         */
    uint8  CMUR10;                                         /* CMUR10           */
    uint8  dummy160[3];                                    /* Reserved         */
    uint8  CMUR11;                                         /* CMUR11           */
    uint8  dummy161[3];                                    /* Reserved         */
    uint8  CMUR12;                                         /* CMUR12           */
    uint8  dummy162[3];                                    /* Reserved         */
    uint8  CMUR13;                                         /* CMUR13           */
    uint8  dummy163[3];                                    /* Reserved         */
    uint8  CMUR14;                                         /* CMUR14           */
    uint8  dummy164[3];                                    /* Reserved         */
    uint8  CMUR15;                                         /* CMUR15           */
    uint8  dummy165[67];                                   /* Reserved         */
    const uint8  CSR0;                                     /* CSR0             */
    uint8  dummy166[3];                                    /* Reserved         */
    const uint8  CSR1;                                     /* CSR1             */
    uint8  dummy167[3];                                    /* Reserved         */
    const uint8  CSR2;                                     /* CSR2             */
    uint8  dummy168[3];                                    /* Reserved         */
    const uint8  CSR3;                                     /* CSR3             */
    uint8  dummy169[3];                                    /* Reserved         */
    const uint8  CSR4;                                     /* CSR4             */
    uint8  dummy170[3];                                    /* Reserved         */
    const uint8  CSR5;                                     /* CSR5             */
    uint8  dummy171[3];                                    /* Reserved         */
    const uint8  CSR6;                                     /* CSR6             */
    uint8  dummy172[3];                                    /* Reserved         */
    const uint8  CSR7;                                     /* CSR7             */
    uint8  dummy173[3];                                    /* Reserved         */
    const uint8  CSR8;                                     /* CSR8             */
    uint8  dummy174[3];                                    /* Reserved         */
    const uint8  CSR9;                                     /* CSR9             */
    uint8  dummy175[3];                                    /* Reserved         */
    const uint8  CSR10;                                    /* CSR10            */
    uint8  dummy176[3];                                    /* Reserved         */
    const uint8  CSR11;                                    /* CSR11            */
    uint8  dummy177[3];                                    /* Reserved         */
    const uint8  CSR12;                                    /* CSR12            */
    uint8  dummy178[3];                                    /* Reserved         */
    const uint8  CSR13;                                    /* CSR13            */
    uint8  dummy179[3];                                    /* Reserved         */
    const uint8  CSR14;                                    /* CSR14            */
    uint8  dummy180[3];                                    /* Reserved         */
    const uint8  CSR15;                                    /* CSR15            */
    uint8  dummy181[3];                                    /* Reserved         */
    uint8  CSC0;                                           /* CSC0             */
    uint8  dummy182[3];                                    /* Reserved         */
    uint8  CSC1;                                           /* CSC1             */
    uint8  dummy183[3];                                    /* Reserved         */
    uint8  CSC2;                                           /* CSC2             */
    uint8  dummy184[3];                                    /* Reserved         */
    uint8  CSC3;                                           /* CSC3             */
    uint8  dummy185[3];                                    /* Reserved         */
    uint8  CSC4;                                           /* CSC4             */
    uint8  dummy186[3];                                    /* Reserved         */
    uint8  CSC5;                                           /* CSC5             */
    uint8  dummy187[3];                                    /* Reserved         */
    uint8  CSC6;                                           /* CSC6             */
    uint8  dummy188[3];                                    /* Reserved         */
    uint8  CSC7;                                           /* CSC7             */
    uint8  dummy189[3];                                    /* Reserved         */
    uint8  CSC8;                                           /* CSC8             */
    uint8  dummy190[3];                                    /* Reserved         */
    uint8  CSC9;                                           /* CSC9             */
    uint8  dummy191[3];                                    /* Reserved         */
    uint8  CSC10;                                          /* CSC10            */
    uint8  dummy192[3];                                    /* Reserved         */
    uint8  CSC11;                                          /* CSC11            */
    uint8  dummy193[3];                                    /* Reserved         */
    uint8  CSC12;                                          /* CSC12            */
    uint8  dummy194[3];                                    /* Reserved         */
    uint8  CSC13;                                          /* CSC13            */
    uint8  dummy195[3];                                    /* Reserved         */
    uint8  CSC14;                                          /* CSC14            */
    uint8  dummy196[3];                                    /* Reserved         */
    uint8  CSC15;                                          /* CSC15            */
    uint8  dummy197[3];                                    /* Reserved         */
    const uint16 TE;                                       /* TE               */
    uint8  dummy198[2];                                    /* Reserved         */
    uint16 TS;                                             /* TS               */
    uint8  dummy199[2];                                    /* Reserved         */
    uint16 TT;                                             /* TT               */
    uint8  dummy200[54];                                   /* Reserved         */
    uint16 CMOR0;                                          /* CMOR0            */
    uint8  dummy201[2];                                    /* Reserved         */
    uint16 CMOR1;                                          /* CMOR1            */
    uint8  dummy202[2];                                    /* Reserved         */
    uint16 CMOR2;                                          /* CMOR2            */
    uint8  dummy203[2];                                    /* Reserved         */
    uint16 CMOR3;                                          /* CMOR3            */
    uint8  dummy204[2];                                    /* Reserved         */
    uint16 CMOR4;                                          /* CMOR4            */
    uint8  dummy205[2];                                    /* Reserved         */
    uint16 CMOR5;                                          /* CMOR5            */
    uint8  dummy206[2];                                    /* Reserved         */
    uint16 CMOR6;                                          /* CMOR6            */
    uint8  dummy207[2];                                    /* Reserved         */
    uint16 CMOR7;                                          /* CMOR7            */
    uint8  dummy208[2];                                    /* Reserved         */
    uint16 CMOR8;                                          /* CMOR8            */
    uint8  dummy209[2];                                    /* Reserved         */
    uint16 CMOR9;                                          /* CMOR9            */
    uint8  dummy210[2];                                    /* Reserved         */
    uint16 CMOR10;                                         /* CMOR10           */
    uint8  dummy211[2];                                    /* Reserved         */
    uint16 CMOR11;                                         /* CMOR11           */
    uint8  dummy212[2];                                    /* Reserved         */
    uint16 CMOR12;                                         /* CMOR12           */
    uint8  dummy213[2];                                    /* Reserved         */
    uint16 CMOR13;                                         /* CMOR13           */
    uint8  dummy214[2];                                    /* Reserved         */
    uint16 CMOR14;                                         /* CMOR14           */
    uint8  dummy215[2];                                    /* Reserved         */
    uint16 CMOR15;                                         /* CMOR15           */
    uint8  dummy216[2];                                    /* Reserved         */
    uint16 TPS;                                            /* TPS              */
    uint8  dummy217[2];                                    /* Reserved         */
    uint8  BRS;                                            /* BRS              */
    uint8  dummy218[3];                                    /* Reserved         */
    uint16 TOM;                                            /* TOM              */
    uint8  dummy219[2];                                    /* Reserved         */
    uint16 TOC;                                            /* TOC              */
    uint8  dummy220[2];                                    /* Reserved         */
    uint16 TDE;                                            /* TDE              */
    uint8  dummy221[2];                                    /* Reserved         */
    uint16 TDM;                                            /* TDM              */
    uint8  dummy222[2];                                    /* Reserved         */
    uint16 TRE;                                            /* TRE              */
    uint8  dummy223[2];                                    /* Reserved         */
    uint16 TRC;                                            /* TRC              */
    uint8  dummy224[2];                                    /* Reserved         */
    uint16 RDE;                                            /* RDE              */
    uint8  dummy225[2];                                    /* Reserved         */
    uint16 RDM;                                            /* RDM              */
    uint8  dummy226[2];                                    /* Reserved         */
    uint16 RDS;                                            /* RDS              */
    uint8  dummy227[2];                                    /* Reserved         */
    uint16 RDC;                                            /* RDC              */
    uint8  dummy228[34];                                   /* Reserved         */
    uint8  EMU;                                            /* EMU              */
} __type42;
typedef struct 
{                                                          /* Module           */
    uint16 CDR0;                                           /* CDR0             */
    uint8  dummy229[2];                                    /* Reserved         */
    uint16 CDR1;                                           /* CDR1             */
    uint8  dummy230[2];                                    /* Reserved         */
    uint16 CDR2;                                           /* CDR2             */
    uint8  dummy231[2];                                    /* Reserved         */
    uint16 CDR3;                                           /* CDR3             */
    uint8  dummy232[2];                                    /* Reserved         */
    uint16 CDR4;                                           /* CDR4             */
    uint8  dummy233[2];                                    /* Reserved         */
    uint16 CDR5;                                           /* CDR5             */
    uint8  dummy234[2];                                    /* Reserved         */
    uint16 CDR6;                                           /* CDR6             */
    uint8  dummy235[2];                                    /* Reserved         */
    uint16 CDR7;                                           /* CDR7             */
    uint8  dummy236[2];                                    /* Reserved         */
    uint16 CDR8;                                           /* CDR8             */
    uint8  dummy237[2];                                    /* Reserved         */
    uint16 CDR9;                                           /* CDR9             */
    uint8  dummy238[2];                                    /* Reserved         */
    uint16 CDR10;                                          /* CDR10            */
    uint8  dummy239[2];                                    /* Reserved         */
    uint16 CDR11;                                          /* CDR11            */
    uint8  dummy240[2];                                    /* Reserved         */
    uint16 CDR12;                                          /* CDR12            */
    uint8  dummy241[2];                                    /* Reserved         */
    uint16 CDR13;                                          /* CDR13            */
    uint8  dummy242[2];                                    /* Reserved         */
    uint16 CDR14;                                          /* CDR14            */
    uint8  dummy243[2];                                    /* Reserved         */
    uint16 CDR15;                                          /* CDR15            */
    uint8  dummy244[2];                                    /* Reserved         */
    uint16 TOL;                                            /* TOL              */
    uint8  dummy245[2];                                    /* Reserved         */
    uint16 RDT;                                            /* RDT              */
    uint8  dummy246[2];                                    /* Reserved         */
    const uint16 RSF;                                      /* RSF              */
    uint8  dummy247[10];                                   /* Reserved         */
    uint16 TDL;                                            /* TDL              */
    uint8  dummy248[2];                                    /* Reserved         */
    uint16 TO;                                             /* TO               */
    uint8  dummy249[2];                                    /* Reserved         */
    uint16 TOE;                                            /* TOE              */
    uint8  dummy250[34];                                   /* Reserved         */
    const uint16 CNT0;                                     /* CNT0             */
    uint8  dummy251[2];                                    /* Reserved         */
    const uint16 CNT1;                                     /* CNT1             */
    uint8  dummy252[2];                                    /* Reserved         */
    const uint16 CNT2;                                     /* CNT2             */
    uint8  dummy253[2];                                    /* Reserved         */
    const uint16 CNT3;                                     /* CNT3             */
    uint8  dummy254[2];                                    /* Reserved         */
    const uint16 CNT4;                                     /* CNT4             */
    uint8  dummy255[2];                                    /* Reserved         */
    const uint16 CNT5;                                     /* CNT5             */
    uint8  dummy256[2];                                    /* Reserved         */
    const uint16 CNT6;                                     /* CNT6             */
    uint8  dummy257[2];                                    /* Reserved         */
    const uint16 CNT7;                                     /* CNT7             */
    uint8  dummy258[2];                                    /* Reserved         */
    const uint16 CNT8;                                     /* CNT8             */
    uint8  dummy259[2];                                    /* Reserved         */
    const uint16 CNT9;                                     /* CNT9             */
    uint8  dummy260[2];                                    /* Reserved         */
    const uint16 CNT10;                                    /* CNT10            */
    uint8  dummy261[2];                                    /* Reserved         */
    const uint16 CNT11;                                    /* CNT11            */
    uint8  dummy262[2];                                    /* Reserved         */
    const uint16 CNT12;                                    /* CNT12            */
    uint8  dummy263[2];                                    /* Reserved         */
    const uint16 CNT13;                                    /* CNT13            */
    uint8  dummy264[2];                                    /* Reserved         */
    const uint16 CNT14;                                    /* CNT14            */
    uint8  dummy265[2];                                    /* Reserved         */
    const uint16 CNT15;                                    /* CNT15            */
    uint8  dummy266[2];                                    /* Reserved         */
    uint8  CMUR0;                                          /* CMUR0            */
    uint8  dummy267[3];                                    /* Reserved         */
    uint8  CMUR1;                                          /* CMUR1            */
    uint8  dummy268[3];                                    /* Reserved         */
    uint8  CMUR2;                                          /* CMUR2            */
    uint8  dummy269[3];                                    /* Reserved         */
    uint8  CMUR3;                                          /* CMUR3            */
    uint8  dummy270[3];                                    /* Reserved         */
    uint8  CMUR4;                                          /* CMUR4            */
    uint8  dummy271[3];                                    /* Reserved         */
    uint8  CMUR5;                                          /* CMUR5            */
    uint8  dummy272[3];                                    /* Reserved         */
    uint8  CMUR6;                                          /* CMUR6            */
    uint8  dummy273[3];                                    /* Reserved         */
    uint8  CMUR7;                                          /* CMUR7            */
    uint8  dummy274[3];                                    /* Reserved         */
    uint8  CMUR8;                                          /* CMUR8            */
    uint8  dummy275[3];                                    /* Reserved         */
    uint8  CMUR9;                                          /* CMUR9            */
    uint8  dummy276[3];                                    /* Reserved         */
    uint8  CMUR10;                                         /* CMUR10           */
    uint8  dummy277[3];                                    /* Reserved         */
    uint8  CMUR11;                                         /* CMUR11           */
    uint8  dummy278[3];                                    /* Reserved         */
    uint8  CMUR12;                                         /* CMUR12           */
    uint8  dummy279[3];                                    /* Reserved         */
    uint8  CMUR13;                                         /* CMUR13           */
    uint8  dummy280[3];                                    /* Reserved         */
    uint8  CMUR14;                                         /* CMUR14           */
    uint8  dummy281[3];                                    /* Reserved         */
    uint8  CMUR15;                                         /* CMUR15           */
    uint8  dummy282[67];                                   /* Reserved         */
    const uint8  CSR0;                                     /* CSR0             */
    uint8  dummy283[3];                                    /* Reserved         */
    const uint8  CSR1;                                     /* CSR1             */
    uint8  dummy284[3];                                    /* Reserved         */
    const uint8  CSR2;                                     /* CSR2             */
    uint8  dummy285[3];                                    /* Reserved         */
    const uint8  CSR3;                                     /* CSR3             */
    uint8  dummy286[3];                                    /* Reserved         */
    const uint8  CSR4;                                     /* CSR4             */
    uint8  dummy287[3];                                    /* Reserved         */
    const uint8  CSR5;                                     /* CSR5             */
    uint8  dummy288[3];                                    /* Reserved         */
    const uint8  CSR6;                                     /* CSR6             */
    uint8  dummy289[3];                                    /* Reserved         */
    const uint8  CSR7;                                     /* CSR7             */
    uint8  dummy290[3];                                    /* Reserved         */
    const uint8  CSR8;                                     /* CSR8             */
    uint8  dummy291[3];                                    /* Reserved         */
    const uint8  CSR9;                                     /* CSR9             */
    uint8  dummy292[3];                                    /* Reserved         */
    const uint8  CSR10;                                    /* CSR10            */
    uint8  dummy293[3];                                    /* Reserved         */
    const uint8  CSR11;                                    /* CSR11            */
    uint8  dummy294[3];                                    /* Reserved         */
    const uint8  CSR12;                                    /* CSR12            */
    uint8  dummy295[3];                                    /* Reserved         */
    const uint8  CSR13;                                    /* CSR13            */
    uint8  dummy296[3];                                    /* Reserved         */
    const uint8  CSR14;                                    /* CSR14            */
    uint8  dummy297[3];                                    /* Reserved         */
    const uint8  CSR15;                                    /* CSR15            */
    uint8  dummy298[3];                                    /* Reserved         */
    uint8  CSC0;                                           /* CSC0             */
    uint8  dummy299[3];                                    /* Reserved         */
    uint8  CSC1;                                           /* CSC1             */
    uint8  dummy300[3];                                    /* Reserved         */
    uint8  CSC2;                                           /* CSC2             */
    uint8  dummy301[3];                                    /* Reserved         */
    uint8  CSC3;                                           /* CSC3             */
    uint8  dummy302[3];                                    /* Reserved         */
    uint8  CSC4;                                           /* CSC4             */
    uint8  dummy303[3];                                    /* Reserved         */
    uint8  CSC5;                                           /* CSC5             */
    uint8  dummy304[3];                                    /* Reserved         */
    uint8  CSC6;                                           /* CSC6             */
    uint8  dummy305[3];                                    /* Reserved         */
    uint8  CSC7;                                           /* CSC7             */
    uint8  dummy306[3];                                    /* Reserved         */
    uint8  CSC8;                                           /* CSC8             */
    uint8  dummy307[3];                                    /* Reserved         */
    uint8  CSC9;                                           /* CSC9             */
    uint8  dummy308[3];                                    /* Reserved         */
    uint8  CSC10;                                          /* CSC10            */
    uint8  dummy309[3];                                    /* Reserved         */
    uint8  CSC11;                                          /* CSC11            */
    uint8  dummy310[3];                                    /* Reserved         */
    uint8  CSC12;                                          /* CSC12            */
    uint8  dummy311[3];                                    /* Reserved         */
    uint8  CSC13;                                          /* CSC13            */
    uint8  dummy312[3];                                    /* Reserved         */
    uint8  CSC14;                                          /* CSC14            */
    uint8  dummy313[3];                                    /* Reserved         */
    uint8  CSC15;                                          /* CSC15            */
    uint8  dummy314[3];                                    /* Reserved         */
    const uint16 TE;                                       /* TE               */
    uint8  dummy315[2];                                    /* Reserved         */
    uint16 TS;                                             /* TS               */
    uint8  dummy316[2];                                    /* Reserved         */
    uint16 TT;                                             /* TT               */
    uint8  dummy317[54];                                   /* Reserved         */
    uint16 CMOR0;                                          /* CMOR0            */
    uint8  dummy318[2];                                    /* Reserved         */
    uint16 CMOR1;                                          /* CMOR1            */
    uint8  dummy319[2];                                    /* Reserved         */
    uint16 CMOR2;                                          /* CMOR2            */
    uint8  dummy320[2];                                    /* Reserved         */
    uint16 CMOR3;                                          /* CMOR3            */
    uint8  dummy321[2];                                    /* Reserved         */
    uint16 CMOR4;                                          /* CMOR4            */
    uint8  dummy322[2];                                    /* Reserved         */
    uint16 CMOR5;                                          /* CMOR5            */
    uint8  dummy323[2];                                    /* Reserved         */
    uint16 CMOR6;                                          /* CMOR6            */
    uint8  dummy324[2];                                    /* Reserved         */
    uint16 CMOR7;                                          /* CMOR7            */
    uint8  dummy325[2];                                    /* Reserved         */
    uint16 CMOR8;                                          /* CMOR8            */
    uint8  dummy326[2];                                    /* Reserved         */
    uint16 CMOR9;                                          /* CMOR9            */
    uint8  dummy327[2];                                    /* Reserved         */
    uint16 CMOR10;                                         /* CMOR10           */
    uint8  dummy328[2];                                    /* Reserved         */
    uint16 CMOR11;                                         /* CMOR11           */
    uint8  dummy329[2];                                    /* Reserved         */
    uint16 CMOR12;                                         /* CMOR12           */
    uint8  dummy330[2];                                    /* Reserved         */
    uint16 CMOR13;                                         /* CMOR13           */
    uint8  dummy331[2];                                    /* Reserved         */
    uint16 CMOR14;                                         /* CMOR14           */
    uint8  dummy332[2];                                    /* Reserved         */
    uint16 CMOR15;                                         /* CMOR15           */
    uint8  dummy333[2];                                    /* Reserved         */
    uint16 TPS;                                            /* TPS              */
    uint8  dummy334[6];                                    /* Reserved         */
    uint16 TOM;                                            /* TOM              */
    uint8  dummy335[2];                                    /* Reserved         */
    uint16 TOC;                                            /* TOC              */
    uint8  dummy336[2];                                    /* Reserved         */
    uint16 TDE;                                            /* TDE              */
    uint8  dummy337[14];                                   /* Reserved         */
    uint16 RDE;                                            /* RDE              */
    uint8  dummy338[2];                                    /* Reserved         */
    uint16 RDM;                                            /* RDM              */
    uint8  dummy339[2];                                    /* Reserved         */
    uint16 RDS;                                            /* RDS              */
    uint8  dummy340[2];                                    /* Reserved         */
    uint16 RDC;                                            /* RDC              */
    uint8  dummy341[34];                                   /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy342[3439];                                 /* Reserved         */
} __type43;
typedef struct 
{                                                          /* Module           */
    uint32 CDR0;                                           /* CDR0             */
    uint32 CDR1;                                           /* CDR1             */
    uint32 CDR2;                                           /* CDR2             */
    uint32 CDR3;                                           /* CDR3             */
    const uint32 CNT0;                                     /* CNT0             */
    const uint32 CNT1;                                     /* CNT1             */
    const uint32 CNT2;                                     /* CNT2             */
    const uint32 CNT3;                                     /* CNT3             */
    uint8  CMUR0;                                          /* CMUR0            */
    uint8  dummy343[3];                                    /* Reserved         */
    uint8  CMUR1;                                          /* CMUR1            */
    uint8  dummy344[3];                                    /* Reserved         */
    uint8  CMUR2;                                          /* CMUR2            */
    uint8  dummy345[3];                                    /* Reserved         */
    uint8  CMUR3;                                          /* CMUR3            */
    uint8  dummy346[3];                                    /* Reserved         */
    const uint8  CSR0;                                     /* CSR0             */
    uint8  dummy347[3];                                    /* Reserved         */
    const uint8  CSR1;                                     /* CSR1             */
    uint8  dummy348[3];                                    /* Reserved         */
    const uint8  CSR2;                                     /* CSR2             */
    uint8  dummy349[3];                                    /* Reserved         */
    const uint8  CSR3;                                     /* CSR3             */
    uint8  dummy350[3];                                    /* Reserved         */
    uint8  CSC0;                                           /* CSC0             */
    uint8  dummy351[3];                                    /* Reserved         */
    uint8  CSC1;                                           /* CSC1             */
    uint8  dummy352[3];                                    /* Reserved         */
    uint8  CSC2;                                           /* CSC2             */
    uint8  dummy353[3];                                    /* Reserved         */
    uint8  CSC3;                                           /* CSC3             */
    uint8  dummy354[3];                                    /* Reserved         */
    const uint8  TE;                                       /* TE               */
    uint8  dummy355[3];                                    /* Reserved         */
    uint8  TS;                                             /* TS               */
    uint8  dummy356[3];                                    /* Reserved         */
    uint8  TT;                                             /* TT               */
    uint8  dummy357[3];                                    /* Reserved         */
    uint8  TO;                                             /* TO               */
    uint8  dummy358[3];                                    /* Reserved         */
    uint8  TOE;                                            /* TOE              */
    uint8  dummy359[3];                                    /* Reserved         */
    uint8  TOL;                                            /* TOL              */
    uint8  dummy360[3];                                    /* Reserved         */
    uint8  RDT;                                            /* RDT              */
    uint8  dummy361[3];                                    /* Reserved         */
    const uint8  RSF;                                      /* RSF              */
    uint8  dummy362[19];                                   /* Reserved         */
    uint16 CMOR0;                                          /* CMOR0            */
    uint8  dummy363[2];                                    /* Reserved         */
    uint16 CMOR1;                                          /* CMOR1            */
    uint8  dummy364[2];                                    /* Reserved         */
    uint16 CMOR2;                                          /* CMOR2            */
    uint8  dummy365[2];                                    /* Reserved         */
    uint16 CMOR3;                                          /* CMOR3            */
    uint8  dummy366[2];                                    /* Reserved         */
    uint16 TPS;                                            /* TPS              */
    uint8  dummy367[2];                                    /* Reserved         */
    uint8  BRS;                                            /* BRS              */
    uint8  dummy368[3];                                    /* Reserved         */
    uint8  TOM;                                            /* TOM              */
    uint8  dummy369[3];                                    /* Reserved         */
    uint8  TOC;                                            /* TOC              */
    uint8  dummy370[3];                                    /* Reserved         */
    uint8  RDE;                                            /* RDE              */
    uint8  dummy371[3];                                    /* Reserved         */
    uint8  RDM;                                            /* RDM              */
    uint8  dummy372[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy373[3927];                                 /* Reserved         */
} __type44;
typedef struct 
{                                                          /* Module           */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy374[3];                                    /* Reserved         */
    const uint8  STR;                                      /* STR              */
    uint8  dummy375[3];                                    /* Reserved         */
    uint8  STC;                                            /* STC              */
    uint8  dummy376[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy377[19];                                   /* Reserved         */
    const uint8  QUE0;                                     /* QUE0             */
    uint8  dummy378[3];                                    /* Reserved         */
    const uint8  QUE1;                                     /* QUE1             */
    uint8  dummy379[3];                                    /* Reserved         */
    const uint8  QUE2;                                     /* QUE2             */
    uint8  dummy380[3];                                    /* Reserved         */
    const uint8  QUE3;                                     /* QUE3             */
    uint8  dummy381[3];                                    /* Reserved         */
    const uint8  QUE4;                                     /* QUE4             */
    uint8  dummy382[3];                                    /* Reserved         */
    const uint8  QUE5;                                     /* QUE5             */
    uint8  dummy383[3];                                    /* Reserved         */
    const uint8  QUE6;                                     /* QUE6             */
    uint8  dummy384[3];                                    /* Reserved         */
    const uint8  QUE7;                                     /* QUE7             */
    uint8  dummy385[3];                                    /* Reserved         */
    uint32 PVCR00_01;                                      /* PVCR00_01        */
    uint32 PVCR02_03;                                      /* PVCR02_03        */
    uint32 PVCR04_05;                                      /* PVCR04_05        */
    uint32 PVCR06_07;                                      /* PVCR06_07        */
    uint32 PVCR08_09;                                      /* PVCR08_09        */
    uint32 PVCR10_11;                                      /* PVCR10_11        */
    uint32 PVCR12_13;                                      /* PVCR12_13        */
    uint32 PVCR14_15;                                      /* PVCR14_15        */
    uint32 PVCR16_17;                                      /* PVCR16_17        */
    uint32 PVCR18_19;                                      /* PVCR18_19        */
    uint32 PVCR20_21;                                      /* PVCR20_21        */
    uint32 PVCR22_23;                                      /* PVCR22_23        */
    uint32 PVCR24_25;                                      /* PVCR24_25        */
    uint32 PVCR26_27;                                      /* PVCR26_27        */
    uint32 PVCR28_29;                                      /* PVCR28_29        */
    uint32 PVCR30_31;                                      /* PVCR30_31        */
    uint32 PVCR32_33;                                      /* PVCR32_33        */
    uint32 PVCR34_35;                                      /* PVCR34_35        */
    uint32 PVCR36_37;                                      /* PVCR36_37        */
    uint32 PVCR38_39;                                      /* PVCR38_39        */
    uint32 PVCR40_41;                                      /* PVCR40_41        */
    uint32 PVCR42_43;                                      /* PVCR42_43        */
    uint32 PVCR44_45;                                      /* PVCR44_45        */
    uint32 PVCR46_47;                                      /* PVCR46_47        */
    uint32 PVCR48_49;                                      /* PVCR48_49        */
    uint32 PVCR50_51;                                      /* PVCR50_51        */
    uint32 PVCR52_53;                                      /* PVCR52_53        */
    uint32 PVCR54_55;                                      /* PVCR54_55        */
    uint32 PVCR56_57;                                      /* PVCR56_57        */
    uint32 PVCR58_59;                                      /* PVCR58_59        */
    uint32 PVCR60_61;                                      /* PVCR60_61        */
    uint32 PVCR62_63;                                      /* PVCR62_63        */
    uint32 PVCR64_65;                                      /* PVCR64_65        */
    uint32 PVCR66_67;                                      /* PVCR66_67        */
    uint32 PVCR68_69;                                      /* PVCR68_69        */
    uint32 PVCR70_71;                                      /* PVCR70_71        */
} __type45;
typedef struct 
{                                                          /* Module           */
    uint16 CSDR;                                           /* CSDR             */
    uint8  dummy386[2];                                    /* Reserved         */
    uint16 CRDR;                                           /* CRDR             */
    uint8  dummy387[2];                                    /* Reserved         */
    uint16 CTDR;                                           /* CTDR             */
    uint8  dummy388[2];                                    /* Reserved         */
    uint8  RDT;                                            /* RDT              */
    uint8  dummy389[3];                                    /* Reserved         */
    const uint8  RSF;                                      /* RSF              */
    uint8  dummy390[3];                                    /* Reserved         */
    const uint16 CNT;                                      /* CNT              */
    uint8  dummy391[10];                                   /* Reserved         */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy392[3];                                    /* Reserved         */
    const uint16 CSBR;                                     /* CSBR             */
    uint8  dummy393[2];                                    /* Reserved         */
    const uint16 CRBR;                                     /* CRBR             */
    uint8  dummy394[2];                                    /* Reserved         */
    const uint16 CTBR;                                     /* CTBR             */
    uint8  dummy395[18];                                   /* Reserved         */
} __type46;
typedef struct 
{                                                          /* Module           */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy396[2];                                    /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy397[2];                                    /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy398[2];                                    /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
    uint8  dummy399[2];                                    /* Reserved         */
    const uint8  TE;                                       /* TE               */
    uint8  dummy400[3];                                    /* Reserved         */
    uint8  TS;                                             /* TS               */
    uint8  dummy401[3];                                    /* Reserved         */
    uint8  TT;                                             /* TT               */
    uint8  dummy402[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
} __type47;
typedef struct 
{                                                          /* Module           */
    __type20 CTL0;                                         /* CTL0             */
    uint8  dummy403[3];                                    /* Reserved         */
    __type21 CTL1;                                         /* CTL1             */
    uint8  dummy404[3];                                    /* Reserved         */
    __type22 CTL2;                                         /* CTL2             */
    uint8  dummy405[3];                                    /* Reserved         */
    const uint32 SUBC;                                     /* SUBC             */
    const uint32 SRBU;                                     /* SRBU             */
    uint8  SEC;                                            /* SEC              */
    uint8  dummy406[3];                                    /* Reserved         */
    uint8  MIN;                                            /* MIN              */
    uint8  dummy407[3];                                    /* Reserved         */
    uint8  HOUR;                                           /* HOUR             */
    uint8  dummy408[3];                                    /* Reserved         */
    uint8  WEEK;                                           /* WEEK             */
    uint8  dummy409[3];                                    /* Reserved         */
    uint8  DAY;                                            /* DAY              */
    uint8  dummy410[3];                                    /* Reserved         */
    uint8  MONTH;                                          /* MONTH            */
    uint8  dummy411[3];                                    /* Reserved         */
    uint8  YEAR;                                           /* YEAR             */
    uint8  dummy412[3];                                    /* Reserved         */
    uint32 TIME;                                           /* TIME             */
    uint32 CAL;                                            /* CAL              */
    uint8  SUBU;                                           /* SUBU             */
    uint8  dummy413[3];                                    /* Reserved         */
    uint32 SCMP;                                           /* SCMP             */
    uint8  ALM;                                            /* ALM              */
    uint8  dummy414[3];                                    /* Reserved         */
    uint8  ALH;                                            /* ALH              */
    uint8  dummy415[3];                                    /* Reserved         */
    uint8  ALW;                                            /* ALW              */
    uint8  dummy416[3];                                    /* Reserved         */
    const uint8  SECC;                                     /* SECC             */
    uint8  dummy417[3];                                    /* Reserved         */
    const uint8  MINC;                                     /* MINC             */
    uint8  dummy418[3];                                    /* Reserved         */
    const uint8  HOURC;                                    /* HOURC            */
    uint8  dummy419[3];                                    /* Reserved         */
    const uint8  WEEKC;                                    /* WEEKC            */
    uint8  dummy420[3];                                    /* Reserved         */
    const uint8  DAYC;                                     /* DAYC             */
    uint8  dummy421[3];                                    /* Reserved         */
    const uint8  MONC;                                     /* MONC             */
    uint8  dummy422[3];                                    /* Reserved         */
    const uint8  YEARC;                                    /* YEARC            */
    uint8  dummy423[3];                                    /* Reserved         */
    const uint32 TIMEC;                                    /* TIMEC            */
    const uint32 CALC;                                     /* CALC             */
    uint8  dummy424[4];                                    /* Reserved         */
    __type17 EMU;                                          /* EMU              */
} __type48;
typedef struct 
{                                                          /* Module           */
    uint16 CCR0;                                           /* CCR0             */
    uint8  dummy425[2];                                    /* Reserved         */
    uint16 CCR1;                                           /* CCR1             */
    uint8  dummy426[2];                                    /* Reserved         */
    uint16 CNT;                                            /* CNT              */
    uint8  dummy427[2];                                    /* Reserved         */
    const uint8  FLG;                                      /* FLG              */
    uint8  dummy428[3];                                    /* Reserved         */
    uint8  FGC;                                            /* FGC              */
    uint8  dummy429[3];                                    /* Reserved         */
    const uint8  TE;                                       /* TE               */
    uint8  dummy430[3];                                    /* Reserved         */
    uint8  TS;                                             /* TS               */
    uint8  dummy431[3];                                    /* Reserved         */
    uint8  TT;                                             /* TT               */
    uint8  dummy432[3];                                    /* Reserved         */
    uint8  IOC0;                                           /* IOC0             */
    uint8  dummy433[31];                                   /* Reserved         */
    uint16 CTL;                                            /* CTL              */
    uint8  dummy434[2];                                    /* Reserved         */
    uint8  IOC1;                                           /* IOC1             */
    uint8  dummy435[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
} __type49;
typedef struct 
{                                                          /* Module           */
    const uint16 FLG;                                      /* FLG              */
    uint8  dummy436[2];                                    /* Reserved         */
    uint8  ACWE;                                           /* ACWE             */
    uint8  dummy437[3];                                    /* Reserved         */
    uint8  ACTS;                                           /* ACTS             */
    uint8  dummy438[3];                                    /* Reserved         */
    uint8  ACTT;                                           /* ACTT             */
    uint8  dummy439[7];                                    /* Reserved         */
    uint8  OPHS;                                           /* OPHS             */
    uint8  dummy440[3];                                    /* Reserved         */
    uint8  OPHT;                                           /* OPHT             */
    uint8  dummy441[7];                                    /* Reserved         */
    uint16 CTL0;                                           /* CTL0             */
    uint8  dummy442[2];                                    /* Reserved         */
    uint8  CTL1;                                           /* CTL1             */
    uint8  dummy443[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
} __type50;
typedef struct 
{                                                          /* Module           */
    uint32 CMP;                                            /* CMP              */
    const uint32 CNT;                                      /* CNT              */
    uint8  dummy444[8];                                    /* Reserved         */
    const uint8  TE;                                       /* TE               */
    uint8  dummy445[3];                                    /* Reserved         */
    uint8  TS;                                             /* TS               */
    uint8  dummy446[3];                                    /* Reserved         */
    uint8  TT;                                             /* TT               */
    uint8  dummy447[7];                                    /* Reserved         */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy448[3];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
} __type51;
typedef struct 
{                                                          /* Module           */
    uint8  WDTE;                                           /* WDTE             */
    uint8  dummy449[3];                                    /* Reserved         */
    uint8  EVAC;                                           /* EVAC             */
    uint8  dummy450[3];                                    /* Reserved         */
    const uint8  REF;                                      /* REF              */
    uint8  dummy451[3];                                    /* Reserved         */
    uint8  MD;                                             /* MD               */
    uint8  dummy452[4083];                                 /* Reserved         */
} __type52;
typedef struct 
{                                                          /* Module           */
    __type10 VCR00;                                        /* VCR00            */
    __type10 VCR01;                                        /* VCR01            */
    __type10 VCR02;                                        /* VCR02            */
    __type10 VCR03;                                        /* VCR03            */
    __type10 VCR04;                                        /* VCR04            */
    __type10 VCR05;                                        /* VCR05            */
    __type10 VCR06;                                        /* VCR06            */
    __type10 VCR07;                                        /* VCR07            */
    __type10 VCR08;                                        /* VCR08            */
    __type10 VCR09;                                        /* VCR09            */
    __type10 VCR10;                                        /* VCR10            */
    __type10 VCR11;                                        /* VCR11            */
    __type10 VCR12;                                        /* VCR12            */
    __type10 VCR13;                                        /* VCR13            */
    __type10 VCR14;                                        /* VCR14            */
    __type10 VCR15;                                        /* VCR15            */
    __type10 VCR16;                                        /* VCR16            */
    __type10 VCR17;                                        /* VCR17            */
    __type10 VCR18;                                        /* VCR18            */
    __type10 VCR19;                                        /* VCR19            */
    __type10 VCR20;                                        /* VCR20            */
    __type10 VCR21;                                        /* VCR21            */
    __type10 VCR22;                                        /* VCR22            */
    __type10 VCR23;                                        /* VCR23            */
    __type10 VCR24;                                        /* VCR24            */
    __type10 VCR25;                                        /* VCR25            */
    __type10 VCR26;                                        /* VCR26            */
    __type10 VCR27;                                        /* VCR27            */
    __type10 VCR28;                                        /* VCR28            */
    __type10 VCR29;                                        /* VCR29            */
    __type10 VCR30;                                        /* VCR30            */
    __type10 VCR31;                                        /* VCR31            */
    __type10 VCR32;                                        /* VCR32            */
    __type10 VCR33;                                        /* VCR33            */
    __type10 VCR34;                                        /* VCR34            */
    __type10 VCR35;                                        /* VCR35            */
    __type10 VCR36;                                        /* VCR36            */
    __type10 VCR37;                                        /* VCR37            */
    __type10 VCR38;                                        /* VCR38            */
    __type10 VCR39;                                        /* VCR39            */
    __type10 VCR40;                                        /* VCR40            */
    __type10 VCR41;                                        /* VCR41            */
    __type10 VCR42;                                        /* VCR42            */
    __type10 VCR43;                                        /* VCR43            */
    __type10 VCR44;                                        /* VCR44            */
    __type10 VCR45;                                        /* VCR45            */
    __type10 VCR46;                                        /* VCR46            */
    __type10 VCR47;                                        /* VCR47            */
    __type10 VCR48;                                        /* VCR48            */
    __type10 VCR49;                                        /* VCR49            */
    uint8  dummy453[44];                                   /* Reserved         */
    const __type10 PWDVCR;                                 /* PWDVCR           */
    uint8  dummy454[8];                                    /* Reserved         */
    const __type15 DR00;                                   /* DR00             */
    const __type15 DR02;                                   /* DR02             */
    const __type15 DR04;                                   /* DR04             */
    const __type15 DR06;                                   /* DR06             */
    const __type15 DR08;                                   /* DR08             */
    const __type15 DR10;                                   /* DR10             */
    const __type15 DR12;                                   /* DR12             */
    const __type15 DR14;                                   /* DR14             */
    const __type15 DR16;                                   /* DR16             */
    const __type15 DR18;                                   /* DR18             */
    const __type15 DR20;                                   /* DR20             */
    const __type15 DR22;                                   /* DR22             */
    const __type15 DR24;                                   /* DR24             */
    const __type15 DR26;                                   /* DR26             */
    const __type15 DR28;                                   /* DR28             */
    const __type15 DR30;                                   /* DR30             */
    const __type15 DR32;                                   /* DR32             */
    const __type15 DR34;                                   /* DR34             */
    const __type15 DR36;                                   /* DR36             */
    const __type15 DR38;                                   /* DR38             */
    const __type15 DR40;                                   /* DR40             */
    const __type15 DR42;                                   /* DR42             */
    const __type15 DR44;                                   /* DR44             */
    const __type15 DR46;                                   /* DR46             */
    const __type15 DR48;                                   /* DR48             */
    uint8  dummy455[20];                                   /* Reserved         */
    const __type15 PWDTSNDR;                               /* PWDTSNDR         */
    uint8  dummy456[132];                                  /* Reserved         */
    const uint32 DIR00;                                    /* DIR00            */
    const uint32 DIR01;                                    /* DIR01            */
    const uint32 DIR02;                                    /* DIR02            */
    const uint32 DIR03;                                    /* DIR03            */
    const uint32 DIR04;                                    /* DIR04            */
    const uint32 DIR05;                                    /* DIR05            */
    const uint32 DIR06;                                    /* DIR06            */
    const uint32 DIR07;                                    /* DIR07            */
    const uint32 DIR08;                                    /* DIR08            */
    const uint32 DIR09;                                    /* DIR09            */
    const uint32 DIR10;                                    /* DIR10            */
    const uint32 DIR11;                                    /* DIR11            */
    const uint32 DIR12;                                    /* DIR12            */
    const uint32 DIR13;                                    /* DIR13            */
    const uint32 DIR14;                                    /* DIR14            */
    const uint32 DIR15;                                    /* DIR15            */
    const uint32 DIR16;                                    /* DIR16            */
    const uint32 DIR17;                                    /* DIR17            */
    const uint32 DIR18;                                    /* DIR18            */
    const uint32 DIR19;                                    /* DIR19            */
    const uint32 DIR20;                                    /* DIR20            */
    const uint32 DIR21;                                    /* DIR21            */
    const uint32 DIR22;                                    /* DIR22            */
    const uint32 DIR23;                                    /* DIR23            */
    const uint32 DIR24;                                    /* DIR24            */
    const uint32 DIR25;                                    /* DIR25            */
    const uint32 DIR26;                                    /* DIR26            */
    const uint32 DIR27;                                    /* DIR27            */
    const uint32 DIR28;                                    /* DIR28            */
    const uint32 DIR29;                                    /* DIR29            */
    const uint32 DIR30;                                    /* DIR30            */
    const uint32 DIR31;                                    /* DIR31            */
    const uint32 DIR32;                                    /* DIR32            */
    const uint32 DIR33;                                    /* DIR33            */
    const uint32 DIR34;                                    /* DIR34            */
    const uint32 DIR35;                                    /* DIR35            */
    const uint32 DIR36;                                    /* DIR36            */
    const uint32 DIR37;                                    /* DIR37            */
    const uint32 DIR38;                                    /* DIR38            */
    const uint32 DIR39;                                    /* DIR39            */
    const uint32 DIR40;                                    /* DIR40            */
    const uint32 DIR41;                                    /* DIR41            */
    const uint32 DIR42;                                    /* DIR42            */
    const uint32 DIR43;                                    /* DIR43            */
    const uint32 DIR44;                                    /* DIR44            */
    const uint32 DIR45;                                    /* DIR45            */
    const uint32 DIR46;                                    /* DIR46            */
    const uint32 DIR47;                                    /* DIR47            */
    const uint32 DIR48;                                    /* DIR48            */
    const uint32 DIR49;                                    /* DIR49            */
    uint8  dummy457[44];                                   /* Reserved         */
    const uint32 PWDDIR;                                   /* PWDDIR           */
    uint8  dummy458[8];                                    /* Reserved         */
    __type10 ADHALTR;                                      /* ADHALTR          */
    __type10 ADCR;                                         /* ADCR             */
    const __type15 SGSTR;                                  /* SGSTR            */
    const __type10 MPXCURR;                                /* MPXCURR          */
    uint8  dummy459[4];                                    /* Reserved         */
    __type10 THSMPSTCR;                                    /* THSMPSTCR        */
    __type10 THCR;                                         /* THCR             */
    __type10 THAHLDSTCR;                                   /* THAHLDSTCR       */
    __type10 THBHLDSTCR;                                   /* THBHLDSTCR       */
    __type10 THACR;                                        /* THACR            */
    __type10 THBCR;                                        /* THBCR            */
    __type10 THER;                                         /* THER             */
    __type10 THGSR;                                        /* THGSR            */
    __type10 SFTCR;                                        /* SFTCR            */
    __type15 ULLMTBR0;                                     /* ULLMTBR0         */
    __type15 ULLMTBR1;                                     /* ULLMTBR1         */
    __type15 ULLMTBR2;                                     /* ULLMTBR2         */
    __type10 ECR;                                          /* ECR              */
    const __type10 ULER;                                   /* ULER             */
    const __type10 OWER;                                   /* OWER             */
    __type10 DGCTL0;                                       /* DGCTL0           */
    __type15 DGCTL1;                                       /* DGCTL1           */
    __type15 PDCTL1;                                       /* PDCTL1           */
    __type10 PDCTL2;                                       /* PDCTL2           */
    uint8  dummy460[32];                                   /* Reserved         */
    __type10 SMPCR;                                        /* SMPCR            */
    uint8  dummy461[4];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy462[183];                                  /* Reserved         */
    __type10 SGSTCR1;                                      /* SGSTCR1          */
    uint8  dummy463[4];                                    /* Reserved         */
    __type10 SGCR1;                                        /* SGCR1            */
    __type10 SGVCSP1;                                      /* SGVCSP1          */
    __type10 SGVCEP1;                                      /* SGVCEP1          */
    __type10 SGMCYCR1;                                     /* SGMCYCR1         */
    __type10 SGSEFCR1;                                     /* SGSEFCR1         */
    __type15 SGTSEL1;                                      /* SGTSEL1          */
    uint8  dummy464[32];                                   /* Reserved         */
    __type10 SGSTCR2;                                      /* SGSTCR2          */
    uint8  dummy465[4];                                    /* Reserved         */
    __type10 SGCR2;                                        /* SGCR2            */
    __type10 SGVCSP2;                                      /* SGVCSP2          */
    __type10 SGVCEP2;                                      /* SGVCEP2          */
    __type10 SGMCYCR2;                                     /* SGMCYCR2         */
    __type10 SGSEFCR2;                                     /* SGSEFCR2         */
    __type15 SGTSEL2;                                      /* SGTSEL2          */
    uint8  dummy466[32];                                   /* Reserved         */
    __type10 SGSTCR3;                                      /* SGSTCR3          */
    uint8  dummy467[4];                                    /* Reserved         */
    __type10 SGCR3;                                        /* SGCR3            */
    __type10 SGVCSP3;                                      /* SGVCSP3          */
    __type10 SGVCEP3;                                      /* SGVCEP3          */
    __type10 SGMCYCR3;                                     /* SGMCYCR3         */
    __type10 SGSEFCR3;                                     /* SGSEFCR3         */
    __type15 SGTSEL3;                                      /* SGTSEL3          */
    uint8  dummy468[40];                                   /* Reserved         */
    __type10 PWDSGCR;                                      /* PWDSGCR          */
    uint8  dummy469[12];                                   /* Reserved         */
    __type10 PWDSGSEFCR;                                   /* PWDSGSEFCR       */
} __type53;
typedef struct 
{                                                          /* Module           */
    __type10 VCR00;                                        /* VCR00            */
    __type10 VCR01;                                        /* VCR01            */
    __type10 VCR02;                                        /* VCR02            */
    __type10 VCR03;                                        /* VCR03            */
    __type10 VCR04;                                        /* VCR04            */
    __type10 VCR05;                                        /* VCR05            */
    __type10 VCR06;                                        /* VCR06            */
    __type10 VCR07;                                        /* VCR07            */
    __type10 VCR08;                                        /* VCR08            */
    __type10 VCR09;                                        /* VCR09            */
    __type10 VCR10;                                        /* VCR10            */
    __type10 VCR11;                                        /* VCR11            */
    __type10 VCR12;                                        /* VCR12            */
    __type10 VCR13;                                        /* VCR13            */
    __type10 VCR14;                                        /* VCR14            */
    __type10 VCR15;                                        /* VCR15            */
    __type10 VCR16;                                        /* VCR16            */
    __type10 VCR17;                                        /* VCR17            */
    __type10 VCR18;                                        /* VCR18            */
    __type10 VCR19;                                        /* VCR19            */
    __type10 VCR20;                                        /* VCR20            */
    __type10 VCR21;                                        /* VCR21            */
    __type10 VCR22;                                        /* VCR22            */
    __type10 VCR23;                                        /* VCR23            */
    uint8  dummy470[148];                                  /* Reserved         */
    const __type10 PWDVCR;                                 /* PWDVCR           */
    uint8  dummy471[8];                                    /* Reserved         */
    const __type15 DR00;                                   /* DR00             */
    const __type15 DR02;                                   /* DR02             */
    const __type15 DR04;                                   /* DR04             */
    const __type15 DR06;                                   /* DR06             */
    const __type15 DR08;                                   /* DR08             */
    const __type15 DR10;                                   /* DR10             */
    const __type15 DR12;                                   /* DR12             */
    const __type15 DR14;                                   /* DR14             */
    const __type15 DR16;                                   /* DR16             */
    const __type15 DR18;                                   /* DR18             */
    const __type15 DR20;                                   /* DR20             */
    const __type15 DR22;                                   /* DR22             */
    uint8  dummy472[72];                                   /* Reserved         */
    const __type15 PWDTSNDR;                               /* PWDTSNDR         */
    uint8  dummy473[132];                                  /* Reserved         */
    const uint32 DIR00;                                    /* DIR00            */
    const uint32 DIR01;                                    /* DIR01            */
    const uint32 DIR02;                                    /* DIR02            */
    const uint32 DIR03;                                    /* DIR03            */
    const uint32 DIR04;                                    /* DIR04            */
    const uint32 DIR05;                                    /* DIR05            */
    const uint32 DIR06;                                    /* DIR06            */
    const uint32 DIR07;                                    /* DIR07            */
    const uint32 DIR08;                                    /* DIR08            */
    const uint32 DIR09;                                    /* DIR09            */
    const uint32 DIR10;                                    /* DIR10            */
    const uint32 DIR11;                                    /* DIR11            */
    const uint32 DIR12;                                    /* DIR12            */
    const uint32 DIR13;                                    /* DIR13            */
    const uint32 DIR14;                                    /* DIR14            */
    const uint32 DIR15;                                    /* DIR15            */
    const uint32 DIR16;                                    /* DIR16            */
    const uint32 DIR17;                                    /* DIR17            */
    const uint32 DIR18;                                    /* DIR18            */
    const uint32 DIR19;                                    /* DIR19            */
    const uint32 DIR20;                                    /* DIR20            */
    const uint32 DIR21;                                    /* DIR21            */
    const uint32 DIR22;                                    /* DIR22            */
    const uint32 DIR23;                                    /* DIR23            */
    uint8  dummy474[148];                                  /* Reserved         */
    const uint32 PWDDIR;                                   /* PWDDIR           */
    uint8  dummy475[8];                                    /* Reserved         */
    __type10 ADHALTR;                                      /* ADHALTR          */
    __type10 ADCR;                                         /* ADCR             */
    const __type15 SGSTR;                                  /* SGSTR            */
    uint8  dummy476[40];                                   /* Reserved         */
    __type10 SFTCR;                                        /* SFTCR            */
    __type15 ULLMTBR0;                                     /* ULLMTBR0         */
    __type15 ULLMTBR1;                                     /* ULLMTBR1         */
    __type15 ULLMTBR2;                                     /* ULLMTBR2         */
    __type10 ECR;                                          /* ECR              */
    const __type10 ULER;                                   /* ULER             */
    const __type10 OWER;                                   /* OWER             */
    __type10 DGCTL0;                                       /* DGCTL0           */
    __type15 DGCTL1;                                       /* DGCTL1           */
    __type15 PDCTL1;                                       /* PDCTL1           */
    __type10 PDCTL2;                                       /* PDCTL2           */
    uint8  dummy477[32];                                   /* Reserved         */
    __type10 SMPCR;                                        /* SMPCR            */
    uint8  dummy478[4];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy479[183];                                  /* Reserved         */
    __type10 SGSTCR1;                                      /* SGSTCR1          */
    uint8  dummy480[4];                                    /* Reserved         */
    __type10 SGCR1;                                        /* SGCR1            */
    __type10 SGVCSP1;                                      /* SGVCSP1          */
    __type10 SGVCEP1;                                      /* SGVCEP1          */
    __type10 SGMCYCR1;                                     /* SGMCYCR1         */
    __type10 SGSEFCR1;                                     /* SGSEFCR1         */
    __type15 SGTSEL1;                                      /* SGTSEL1          */
    uint8  dummy481[32];                                   /* Reserved         */
    __type10 SGSTCR2;                                      /* SGSTCR2          */
    uint8  dummy482[4];                                    /* Reserved         */
    __type10 SGCR2;                                        /* SGCR2            */
    __type10 SGVCSP2;                                      /* SGVCSP2          */
    __type10 SGVCEP2;                                      /* SGVCEP2          */
    __type10 SGMCYCR2;                                     /* SGMCYCR2         */
    __type10 SGSEFCR2;                                     /* SGSEFCR2         */
    __type15 SGTSEL2;                                      /* SGTSEL2          */
    uint8  dummy483[32];                                   /* Reserved         */
    __type10 SGSTCR3;                                      /* SGSTCR3          */
    uint8  dummy484[4];                                    /* Reserved         */
    __type10 SGCR3;                                        /* SGCR3            */
    __type10 SGVCSP3;                                      /* SGVCSP3          */
    __type10 SGVCEP3;                                      /* SGVCEP3          */
    __type10 SGMCYCR3;                                     /* SGMCYCR3         */
    __type10 SGSEFCR3;                                     /* SGSEFCR3         */
    __type15 SGTSEL3;                                      /* SGTSEL3          */
    uint8  dummy485[40];                                   /* Reserved         */
    __type10 PWDSGCR;                                      /* PWDSGCR          */
    uint8  dummy486[12];                                   /* Reserved         */
    __type10 PWDSGSEFCR;                                   /* PWDSGSEFCR       */
} __type54;
typedef struct 
{                                                          /* Module           */
    uint32 CIN;                                            /* CIN              */
    uint32 COUT;                                           /* COUT             */
    uint8  dummy487[24];                                   /* Reserved         */
    uint8  CTL;                                            /* CTL              */
    uint8  dummy488[4063];                                 /* Reserved         */
} __type55;
typedef struct 
{                                                          /* Module           */
    __type23 KRM;                                          /* KRM              */
} __type56;
typedef struct 
{                                                          /* Module           */
    uint8  CTL0;                                           /* CTL0             */
    uint8  dummy489[7];                                    /* Reserved         */
    uint16 CMPL;                                           /* CMPL             */
    uint8  dummy490[2];                                    /* Reserved         */
    uint16 CMPH;                                           /* CMPH             */
    uint8  dummy491[2];                                    /* Reserved         */
    uint8  PCMD;                                           /* PCMD             */
    uint8  dummy492[3];                                    /* Reserved         */
    const uint8  PS;                                       /* PS               */
    uint8  dummy493[3];                                    /* Reserved         */
    uint8  EMU0;                                           /* EMU0             */
} __type57;
typedef struct 
{                                                          /* Module           */
    uint32 TEST;                                           /* TEST             */
    const uint32 TESTS;                                    /* TESTS            */
} __type58;


__IOREG(FLMDCNT, 0xFFA00000, __READ_WRITE, uint32);
__IOREG(FLMDPCMD, 0xFFA00004, __READ_WRITE, uint32);
__IOREG(FLMDPS, 0xFFA00008, __READ, uint32);
__IOREG(SELB_TAUJ0I, 0xFFBC0100, __READ_WRITE, uint8);
__IOREG(SELB_TAUD0I, 0xFFBC0200, __READ_WRITE, uint16);
__IOREG(SELB_INTC1, 0xFFBC0300, __READ_WRITE, uint16);
__IOREG(SELB_INTC2, 0xFFBC0304, __READ_WRITE, uint16);
__IOREG(SELB_READTEST, 0xFFBC0600, __READ_WRITE, uint8);
__IOREG(SLPWGA0, 0xFFBC1000, __READ_WRITE, uint32);
__IOREG(SLPWGA1, 0xFFBC1004, __READ_WRITE, uint32);
__IOREG(SLPWGA2, 0xFFBC1008, __READ_WRITE, uint32);
__IOREG(SCTLR, 0xFFBC2000, __READ_WRITE, uint32);
__IOREG(EVFR, 0xFFBC2004, __READ_WRITE, uint32);
__IOREG(DPSELR0, 0xFFBC2008, __READ_WRITE, uint32);
__IOREG(DPSELRM, 0xFFBC200C, __READ_WRITE, uint32);
__IOREG(DPSELRML, 0xFFBC200C, __READ_WRITE, uint16);
__IOREG(DPSELR1, 0xFFBC200C, __READ_WRITE, uint8);
__IOREG(DPSELR2, 0xFFBC200D, __READ_WRITE, uint8);
__IOREG(DPSELRMH, 0xFFBC200E, __READ_WRITE, uint16);
__IOREG(DPSELR3, 0xFFBC200E, __READ_WRITE, uint8);
__IOREG(DPSELR4, 0xFFBC200F, __READ_WRITE, uint8);
__IOREG(DPSELRH, 0xFFBC2010, __READ_WRITE, uint32);
__IOREG(DPSELRHL, 0xFFBC2010, __READ_WRITE, uint16);
__IOREG(DPSELR5, 0xFFBC2010, __READ_WRITE, uint8);
__IOREG(DPSELR6, 0xFFBC2011, __READ_WRITE, uint8);
__IOREG(DPSELRHH, 0xFFBC2012, __READ_WRITE, uint16);
__IOREG(DPSELR7, 0xFFBC2012, __READ_WRITE, uint8);
__IOREG(DPDSR0, 0xFFBC2014, __READ_WRITE, uint32);
__IOREG(DPDSRM, 0xFFBC2018, __READ_WRITE, uint32);
__IOREG(DPDSRML, 0xFFBC2018, __READ_WRITE, uint16);
__IOREG(DPDSR1, 0xFFBC2018, __READ_WRITE, uint8);
__IOREG(DPDSR2, 0xFFBC2019, __READ_WRITE, uint8);
__IOREG(DPDSRMH, 0xFFBC201A, __READ_WRITE, uint16);
__IOREG(DPDSR3, 0xFFBC201A, __READ_WRITE, uint8);
__IOREG(DPDSR4, 0xFFBC201B, __READ_WRITE, uint8);
__IOREG(DPDSRH, 0xFFBC201C, __READ_WRITE, uint32);
__IOREG(DPDSRHL, 0xFFBC201C, __READ_WRITE, uint16);
__IOREG(DPDSR5, 0xFFBC201C, __READ_WRITE, uint8);
__IOREG(DPDSR6, 0xFFBC201D, __READ_WRITE, uint8);
__IOREG(DPDSRHH, 0xFFBC201E, __READ_WRITE, uint16);
__IOREG(DPDSR7, 0xFFBC201E, __READ_WRITE, uint8);
__IOREG(DPDIMR0, 0xFFBC2020, __READ, uint32);
__IOREG(DPDIMR1, 0xFFBC2024, __READ, uint8);
__IOREG(DPDIMR2, 0xFFBC2028, __READ, uint8);
__IOREG(DPDIMR3, 0xFFBC202C, __READ, uint8);
__IOREG(DPDIMR4, 0xFFBC2030, __READ, uint8);
__IOREG(DPDIMR5, 0xFFBC2034, __READ, uint8);
__IOREG(DPDIMR6, 0xFFBC2038, __READ, uint8);
__IOREG(DPDIMR7, 0xFFBC203C, __READ, uint8);
__IOREG(CNTVAL, 0xFFBC2040, __READ_WRITE, uint16);
__IOREG(SOSTR, 0xFFBC2044, __READ, uint8);
__IOREG(P0, 0xFFC10000, __READ_WRITE, uint16);
__IOREG(P1, 0xFFC10004, __READ_WRITE, uint16);
__IOREG(P2, 0xFFC10008, __READ_WRITE, uint16);
__IOREG(P8, 0xFFC10020, __READ_WRITE, uint16);
__IOREG(P9, 0xFFC10024, __READ_WRITE, uint16);
__IOREG(P10, 0xFFC10028, __READ_WRITE, uint16);
__IOREG(P11, 0xFFC1002C, __READ_WRITE, uint16);
__IOREG(P12, 0xFFC10030, __READ_WRITE, uint16);
__IOREG(P18, 0xFFC10048, __READ_WRITE, uint16);
__IOREG(P20, 0xFFC10050, __READ_WRITE, uint16);
__IOREG(AP0, 0xFFC100C8, __READ_WRITE, uint16);
__IOREG(AP1, 0xFFC100CC, __READ_WRITE, uint16);
__IOREG(PSR0, 0xFFC10100, __READ_WRITE, uint32);
__IOREG(PSR1, 0xFFC10104, __READ_WRITE, uint32);
__IOREG(PSR2, 0xFFC10108, __READ_WRITE, uint32);
__IOREG(PSR8, 0xFFC10120, __READ_WRITE, uint32);
__IOREG(PSR9, 0xFFC10124, __READ_WRITE, uint32);
__IOREG(PSR10, 0xFFC10128, __READ_WRITE, uint32);
__IOREG(PSR11, 0xFFC1012C, __READ_WRITE, uint32);
__IOREG(PSR12, 0xFFC10130, __READ_WRITE, uint32);
__IOREG(PSR18, 0xFFC10148, __READ_WRITE, uint32);
__IOREG(PSR20, 0xFFC10150, __READ_WRITE, uint32);
__IOREG(APSR0, 0xFFC101C8, __READ_WRITE, uint32);
__IOREG(APSR1, 0xFFC101CC, __READ_WRITE, uint32);
__IOREG(PPR0, 0xFFC10200, __READ, uint16);
__IOREG(PPR1, 0xFFC10204, __READ, uint16);
__IOREG(PPR2, 0xFFC10208, __READ, uint16);
__IOREG(PPR8, 0xFFC10220, __READ, uint16);
__IOREG(PPR9, 0xFFC10224, __READ, uint16);
__IOREG(PPR10, 0xFFC10228, __READ, uint16);
__IOREG(PPR11, 0xFFC1022C, __READ, uint16);
__IOREG(PPR12, 0xFFC10230, __READ, uint16);
__IOREG(PPR18, 0xFFC10248, __READ, uint16);
__IOREG(PPR20, 0xFFC10250, __READ, uint16);
__IOREG(APPR0, 0xFFC102C8, __READ, uint16);
__IOREG(APPR1, 0xFFC102CC, __READ, uint16);
__IOREG(IPPR0, 0xFFC102F0, __READ, uint16);
__IOREG(PM0, 0xFFC10300, __READ_WRITE, uint16);
__IOREG(PM1, 0xFFC10304, __READ_WRITE, uint16);
__IOREG(PM2, 0xFFC10308, __READ_WRITE, uint16);
__IOREG(PM8, 0xFFC10320, __READ_WRITE, uint16);
__IOREG(PM9, 0xFFC10324, __READ_WRITE, uint16);
__IOREG(PM10, 0xFFC10328, __READ_WRITE, uint16);
__IOREG(PM11, 0xFFC1032C, __READ_WRITE, uint16);
__IOREG(PM12, 0xFFC10330, __READ_WRITE, uint16);
__IOREG(PM18, 0xFFC10348, __READ_WRITE, uint16);
__IOREG(PM20, 0xFFC10350, __READ_WRITE, uint16);
__IOREG(APM0, 0xFFC103C8, __READ_WRITE, uint16);
__IOREG(APM1, 0xFFC103CC, __READ_WRITE, uint16);
__IOREG(PMC0, 0xFFC10400, __READ_WRITE, uint16);
__IOREG(PMC1, 0xFFC10404, __READ_WRITE, uint16);
__IOREG(PMC2, 0xFFC10408, __READ_WRITE, uint16);
__IOREG(PMC8, 0xFFC10420, __READ_WRITE, uint16);
__IOREG(PMC9, 0xFFC10424, __READ_WRITE, uint16);
__IOREG(PMC10, 0xFFC10428, __READ_WRITE, uint16);
__IOREG(PMC11, 0xFFC1042C, __READ_WRITE, uint16);
__IOREG(PMC12, 0xFFC10430, __READ_WRITE, uint16);
__IOREG(PMC18, 0xFFC10448, __READ_WRITE, uint16);
__IOREG(PMC20, 0xFFC10450, __READ_WRITE, uint16);
__IOREG(PFC0, 0xFFC10500, __READ_WRITE, uint16);
__IOREG(PFC1, 0xFFC10504, __READ_WRITE, uint16);
__IOREG(PFC8, 0xFFC10520, __READ_WRITE, uint16);
__IOREG(PFC9, 0xFFC10524, __READ_WRITE, uint16);
__IOREG(PFC10, 0xFFC10528, __READ_WRITE, uint16);
__IOREG(PFC11, 0xFFC1052C, __READ_WRITE, uint16);
__IOREG(PFC12, 0xFFC10530, __READ_WRITE, uint16);
__IOREG(PFC18, 0xFFC10548, __READ_WRITE, uint16);
__IOREG(PFC20, 0xFFC10550, __READ_WRITE, uint16);
__IOREG(PFCE0, 0xFFC10600, __READ_WRITE, uint16);
__IOREG(PFCE8, 0xFFC10620, __READ_WRITE, uint16);
__IOREG(PFCE9, 0xFFC10624, __READ_WRITE, uint16);
__IOREG(PFCE10, 0xFFC10628, __READ_WRITE, uint16);
__IOREG(PFCE11, 0xFFC1062C, __READ_WRITE, uint16);
__IOREG(PFCE12, 0xFFC10630, __READ_WRITE, uint16);
__IOREG(PNOT0, 0xFFC10700, __READ_WRITE, uint16);
__IOREG(PNOT1, 0xFFC10704, __READ_WRITE, uint16);
__IOREG(PNOT2, 0xFFC10708, __READ_WRITE, uint16);
__IOREG(PNOT8, 0xFFC10720, __READ_WRITE, uint16);
__IOREG(PNOT9, 0xFFC10724, __READ_WRITE, uint16);
__IOREG(PNOT10, 0xFFC10728, __READ_WRITE, uint16);
__IOREG(PNOT11, 0xFFC1072C, __READ_WRITE, uint16);
__IOREG(PNOT12, 0xFFC10730, __READ_WRITE, uint16);
__IOREG(PNOT18, 0xFFC10748, __READ_WRITE, uint16);
__IOREG(PNOT20, 0xFFC10750, __READ_WRITE, uint16);
__IOREG(APNOT0, 0xFFC107C8, __READ_WRITE, uint16);
__IOREG(APNOT1, 0xFFC107CC, __READ_WRITE, uint16);
__IOREG(PMSR0, 0xFFC10800, __READ_WRITE, uint32);
__IOREG(PMSR1, 0xFFC10804, __READ_WRITE, uint32);
__IOREG(PMSR2, 0xFFC10808, __READ_WRITE, uint32);
__IOREG(PMSR8, 0xFFC10820, __READ_WRITE, uint32);
__IOREG(PMSR9, 0xFFC10824, __READ_WRITE, uint32);
__IOREG(PMSR10, 0xFFC10828, __READ_WRITE, uint32);
__IOREG(PMSR11, 0xFFC1082C, __READ_WRITE, uint32);
__IOREG(PMSR12, 0xFFC10830, __READ_WRITE, uint32);
__IOREG(PMSR18, 0xFFC10848, __READ_WRITE, uint32);
__IOREG(PMSR20, 0xFFC10850, __READ_WRITE, uint32);
__IOREG(APMSR0, 0xFFC108C8, __READ_WRITE, uint32);
__IOREG(APMSR1, 0xFFC108CC, __READ_WRITE, uint32);
__IOREG(PMCSR0, 0xFFC10900, __READ_WRITE, uint32);
__IOREG(PMCSR1, 0xFFC10904, __READ_WRITE, uint32);
__IOREG(PMCSR2, 0xFFC10908, __READ_WRITE, uint32);
__IOREG(PMCSR8, 0xFFC10920, __READ_WRITE, uint32);
__IOREG(PMCSR9, 0xFFC10924, __READ_WRITE, uint32);
__IOREG(PMCSR10, 0xFFC10928, __READ_WRITE, uint32);
__IOREG(PMCSR11, 0xFFC1092C, __READ_WRITE, uint32);
__IOREG(PMCSR12, 0xFFC10930, __READ_WRITE, uint32);
__IOREG(PMCSR18, 0xFFC10948, __READ_WRITE, uint32);
__IOREG(PMCSR20, 0xFFC10950, __READ_WRITE, uint32);
__IOREG(PFCAE0, 0xFFC10A00, __READ_WRITE, uint16);
__IOREG(PFCAE10, 0xFFC10A28, __READ_WRITE, uint16);
__IOREG(PFCAE11, 0xFFC10A2C, __READ_WRITE, uint16);
__IOREG(PIBC0, 0xFFC14000, __READ_WRITE, uint16);
__IOREG(PIBC1, 0xFFC14004, __READ_WRITE, uint16);
__IOREG(PIBC2, 0xFFC14008, __READ_WRITE, uint16);
__IOREG(PIBC8, 0xFFC14020, __READ_WRITE, uint16);
__IOREG(PIBC9, 0xFFC14024, __READ_WRITE, uint16);
__IOREG(PIBC10, 0xFFC14028, __READ_WRITE, uint16);
__IOREG(PIBC11, 0xFFC1402C, __READ_WRITE, uint16);
__IOREG(PIBC12, 0xFFC14030, __READ_WRITE, uint16);
__IOREG(PIBC18, 0xFFC14048, __READ_WRITE, uint16);
__IOREG(PIBC20, 0xFFC14050, __READ_WRITE, uint16);
__IOREG(APIBC0, 0xFFC140C8, __READ_WRITE, uint16);
__IOREG(APIBC1, 0xFFC140CC, __READ_WRITE, uint16);
__IOREG(IPIBC0, 0xFFC140F0, __READ_WRITE, uint16);
__IOREG(PBDC0, 0xFFC14100, __READ_WRITE, uint16);
__IOREG(PBDC1, 0xFFC14104, __READ_WRITE, uint16);
__IOREG(PBDC2, 0xFFC14108, __READ_WRITE, uint16);
__IOREG(PBDC8, 0xFFC14120, __READ_WRITE, uint16);
__IOREG(PBDC9, 0xFFC14124, __READ_WRITE, uint16);
__IOREG(PBDC10, 0xFFC14128, __READ_WRITE, uint16);
__IOREG(PBDC11, 0xFFC1412C, __READ_WRITE, uint16);
__IOREG(PBDC12, 0xFFC14130, __READ_WRITE, uint16);
__IOREG(PBDC18, 0xFFC14148, __READ_WRITE, uint16);
__IOREG(PBDC20, 0xFFC14150, __READ_WRITE, uint16);
__IOREG(APBDC0, 0xFFC141C8, __READ_WRITE, uint16);
__IOREG(APBDC1, 0xFFC141CC, __READ_WRITE, uint16);
__IOREG(PIPC0, 0xFFC14200, __READ_WRITE, uint16);
__IOREG(PIPC10, 0xFFC14228, __READ_WRITE, uint16);
__IOREG(PIPC11, 0xFFC1422C, __READ_WRITE, uint16);
__IOREG(PU0, 0xFFC14300, __READ_WRITE, uint16);
__IOREG(PU1, 0xFFC14304, __READ_WRITE, uint16);
__IOREG(PU2, 0xFFC14308, __READ_WRITE, uint16);
__IOREG(PU8, 0xFFC14320, __READ_WRITE, uint16);
__IOREG(PU9, 0xFFC14324, __READ_WRITE, uint16);
__IOREG(PU10, 0xFFC14328, __READ_WRITE, uint16);
__IOREG(PU11, 0xFFC1432C, __READ_WRITE, uint16);
__IOREG(PU12, 0xFFC14330, __READ_WRITE, uint16);
__IOREG(PU18, 0xFFC14348, __READ_WRITE, uint16);
__IOREG(PU20, 0xFFC14350, __READ_WRITE, uint16);
__IOREG(PD0, 0xFFC14400, __READ_WRITE, uint16);
__IOREG(PD8, 0xFFC14420, __READ_WRITE, uint16);
__IOREG(PD9, 0xFFC14424, __READ_WRITE, uint16);
__IOREG(PD10, 0xFFC14428, __READ_WRITE, uint16);
__IOREG(PD11, 0xFFC1442C, __READ_WRITE, uint16);
__IOREG(PODC0, 0xFFC14500, __READ_WRITE, uint32);
__IOREG(PODC1, 0xFFC14504, __READ_WRITE, uint32);
__IOREG(PODC2, 0xFFC14508, __READ_WRITE, uint32);
__IOREG(PODC8, 0xFFC14520, __READ_WRITE, uint32);
__IOREG(PODC9, 0xFFC14524, __READ_WRITE, uint32);
__IOREG(PODC10, 0xFFC14528, __READ_WRITE, uint32);
__IOREG(PODC11, 0xFFC1452C, __READ_WRITE, uint32);
__IOREG(PODC12, 0xFFC14530, __READ_WRITE, uint32);
__IOREG(PODC18, 0xFFC14548, __READ_WRITE, uint32);
__IOREG(PODC20, 0xFFC14550, __READ_WRITE, uint32);
__IOREG(PDSC0, 0xFFC14600, __READ_WRITE, uint32);
__IOREG(PDSC10, 0xFFC14628, __READ_WRITE, uint32);
__IOREG(PDSC11, 0xFFC1462C, __READ_WRITE, uint32);
__IOREG(PDSC12, 0xFFC14630, __READ_WRITE, uint32);
__IOREG(PIS0, 0xFFC14700, __READ_WRITE, uint16);
__IOREG(PIS1, 0xFFC14704, __READ_WRITE, uint16);
__IOREG(PIS2, 0xFFC14708, __READ_WRITE, uint16);
__IOREG(PIS10, 0xFFC14728, __READ_WRITE, uint16);
__IOREG(PIS11, 0xFFC1472C, __READ_WRITE, uint16);
__IOREG(PIS12, 0xFFC14730, __READ_WRITE, uint16);
__IOREG(PIS20, 0xFFC14750, __READ_WRITE, uint16);
__IOREG(PPROTS0, 0xFFC14B00, __READ, uint32);
__IOREG(PPROTS1, 0xFFC14B04, __READ, uint32);
__IOREG(PPROTS2, 0xFFC14B08, __READ, uint32);
__IOREG(PPROTS8, 0xFFC14B20, __READ, uint32);
__IOREG(PPROTS9, 0xFFC14B24, __READ, uint32);
__IOREG(PPROTS10, 0xFFC14B28, __READ, uint32);
__IOREG(PPROTS11, 0xFFC14B2C, __READ, uint32);
__IOREG(PPROTS12, 0xFFC14B30, __READ, uint32);
__IOREG(PPROTS18, 0xFFC14B48, __READ, uint32);
__IOREG(PPROTS20, 0xFFC14B50, __READ, uint32);
__IOREG(PPCMD0, 0xFFC14C00, __READ_WRITE, uint32);
__IOREG(PPCMD1, 0xFFC14C04, __READ_WRITE, uint32);
__IOREG(PPCMD2, 0xFFC14C08, __READ_WRITE, uint32);
__IOREG(PPCMD8, 0xFFC14C20, __READ_WRITE, uint32);
__IOREG(PPCMD9, 0xFFC14C24, __READ_WRITE, uint32);
__IOREG(PPCMD10, 0xFFC14C28, __READ_WRITE, uint32);
__IOREG(PPCMD11, 0xFFC14C2C, __READ_WRITE, uint32);
__IOREG(PPCMD12, 0xFFC14C30, __READ_WRITE, uint32);
__IOREG(PPCMD18, 0xFFC14C48, __READ_WRITE, uint32);
__IOREG(PPCMD20, 0xFFC14C50, __READ_WRITE, uint32);
__IOREG(JP0, 0xFFC20000, __READ_WRITE, uint8);
__IOREG(JPSR0, 0xFFC20010, __READ_WRITE, uint32);
__IOREG(JPPR0, 0xFFC20020, __READ, uint8);
__IOREG(JPM0, 0xFFC20030, __READ_WRITE, uint8);
__IOREG(JPMC0, 0xFFC20040, __READ_WRITE, uint8);
__IOREG(JPFC0, 0xFFC20050, __READ_WRITE, uint8);
__IOREG(JPNOT0, 0xFFC20070, __READ_WRITE, uint8);
__IOREG(JPMSR0, 0xFFC20080, __READ_WRITE, uint32);
__IOREG(JPMCSR0, 0xFFC20090, __READ_WRITE, uint32);
__IOREG(JPIBC0, 0xFFC20400, __READ_WRITE, uint8);
__IOREG(JPBDC0, 0xFFC20410, __READ_WRITE, uint8);
__IOREG(JPU0, 0xFFC20430, __READ_WRITE, uint8);
__IOREG(JPD0, 0xFFC20440, __READ_WRITE, uint8);
__IOREG(JPODC0, 0xFFC20450, __READ_WRITE, uint32);
__IOREG(JPISA0, 0xFFC204A0, __READ_WRITE, uint8);
__IOREG(JPPROTS0, 0xFFC204B0, __READ, uint32);
__IOREG(JPPCMD0, 0xFFC204C0, __READ_WRITE, uint32);
__IOREG(DNFATAUD0ICTL, 0xFFC30000, __READ_WRITE, uint8);
__IOREG(DNFATAUD0IEN, 0xFFC30004, __READ_WRITE, uint16);
__IOREG(DNFATAUD0IENH, 0xFFC30008, __READ_WRITE, uint8);
#define DNFATAUD0IENH0     (((volatile __bitf_T *)0xFFC30008)->bit00)
#define DNFATAUD0IENH1     (((volatile __bitf_T *)0xFFC30008)->bit01)
#define DNFATAUD0IENH2     (((volatile __bitf_T *)0xFFC30008)->bit02)
#define DNFATAUD0IENH3     (((volatile __bitf_T *)0xFFC30008)->bit03)
#define DNFATAUD0IENH4     (((volatile __bitf_T *)0xFFC30008)->bit04)
#define DNFATAUD0IENH5     (((volatile __bitf_T *)0xFFC30008)->bit05)
#define DNFATAUD0IENH6     (((volatile __bitf_T *)0xFFC30008)->bit06)
#define DNFATAUD0IENH7     (((volatile __bitf_T *)0xFFC30008)->bit07)
__IOREG(DNFATAUD0IENL, 0xFFC3000C, __READ_WRITE, uint8);
#define DNFATAUD0IENL0     (((volatile __bitf_T *)0xFFC3000C)->bit00)
#define DNFATAUD0IENL1     (((volatile __bitf_T *)0xFFC3000C)->bit01)
#define DNFATAUD0IENL2     (((volatile __bitf_T *)0xFFC3000C)->bit02)
#define DNFATAUD0IENL3     (((volatile __bitf_T *)0xFFC3000C)->bit03)
#define DNFATAUD0IENL4     (((volatile __bitf_T *)0xFFC3000C)->bit04)
#define DNFATAUD0IENL5     (((volatile __bitf_T *)0xFFC3000C)->bit05)
#define DNFATAUD0IENL6     (((volatile __bitf_T *)0xFFC3000C)->bit06)
#define DNFATAUD0IENL7     (((volatile __bitf_T *)0xFFC3000C)->bit07)
__IOREG(DNFATAUB0ICTL, 0xFFC30020, __READ_WRITE, uint8);
__IOREG(DNFATAUB0IEN, 0xFFC30024, __READ_WRITE, uint16);
__IOREG(DNFATAUB0IENH, 0xFFC30028, __READ_WRITE, uint8);
#define DNFATAUB0IENH0     (((volatile __bitf_T *)0xFFC30028)->bit00)
#define DNFATAUB0IENH1     (((volatile __bitf_T *)0xFFC30028)->bit01)
#define DNFATAUB0IENH2     (((volatile __bitf_T *)0xFFC30028)->bit02)
#define DNFATAUB0IENH3     (((volatile __bitf_T *)0xFFC30028)->bit03)
#define DNFATAUB0IENH4     (((volatile __bitf_T *)0xFFC30028)->bit04)
#define DNFATAUB0IENH5     (((volatile __bitf_T *)0xFFC30028)->bit05)
#define DNFATAUB0IENH6     (((volatile __bitf_T *)0xFFC30028)->bit06)
#define DNFATAUB0IENH7     (((volatile __bitf_T *)0xFFC30028)->bit07)
__IOREG(DNFATAUB0IENL, 0xFFC3002C, __READ_WRITE, uint8);
#define DNFATAUB0IENL0     (((volatile __bitf_T *)0xFFC3002C)->bit00)
#define DNFATAUB0IENL1     (((volatile __bitf_T *)0xFFC3002C)->bit01)
#define DNFATAUB0IENL2     (((volatile __bitf_T *)0xFFC3002C)->bit02)
#define DNFATAUB0IENL3     (((volatile __bitf_T *)0xFFC3002C)->bit03)
#define DNFATAUB0IENL4     (((volatile __bitf_T *)0xFFC3002C)->bit04)
#define DNFATAUB0IENL5     (((volatile __bitf_T *)0xFFC3002C)->bit05)
#define DNFATAUB0IENL6     (((volatile __bitf_T *)0xFFC3002C)->bit06)
#define DNFATAUB0IENL7     (((volatile __bitf_T *)0xFFC3002C)->bit07)
__IOREG(DNFATAUB1ICTL, 0xFFC30040, __READ_WRITE, uint8);
__IOREG(DNFATAUB1IEN, 0xFFC30044, __READ_WRITE, uint16);
__IOREG(DNFATAUB1IENH, 0xFFC30048, __READ_WRITE, uint8);
#define DNFATAUB1IENH0     (((volatile __bitf_T *)0xFFC30048)->bit00)
#define DNFATAUB1IENH1     (((volatile __bitf_T *)0xFFC30048)->bit01)
#define DNFATAUB1IENH2     (((volatile __bitf_T *)0xFFC30048)->bit02)
#define DNFATAUB1IENH3     (((volatile __bitf_T *)0xFFC30048)->bit03)
#define DNFATAUB1IENH4     (((volatile __bitf_T *)0xFFC30048)->bit04)
#define DNFATAUB1IENH5     (((volatile __bitf_T *)0xFFC30048)->bit05)
#define DNFATAUB1IENH6     (((volatile __bitf_T *)0xFFC30048)->bit06)
#define DNFATAUB1IENH7     (((volatile __bitf_T *)0xFFC30048)->bit07)
__IOREG(DNFATAUB1IENL, 0xFFC3004C, __READ_WRITE, uint8);
#define DNFATAUB1IENL0     (((volatile __bitf_T *)0xFFC3004C)->bit00)
#define DNFATAUB1IENL1     (((volatile __bitf_T *)0xFFC3004C)->bit01)
#define DNFATAUB1IENL2     (((volatile __bitf_T *)0xFFC3004C)->bit02)
#define DNFATAUB1IENL3     (((volatile __bitf_T *)0xFFC3004C)->bit03)
#define DNFATAUB1IENL4     (((volatile __bitf_T *)0xFFC3004C)->bit04)
#define DNFATAUB1IENL5     (((volatile __bitf_T *)0xFFC3004C)->bit05)
#define DNFATAUB1IENL6     (((volatile __bitf_T *)0xFFC3004C)->bit06)
#define DNFATAUB1IENL7     (((volatile __bitf_T *)0xFFC3004C)->bit07)
__IOREG(DNFAENCA0ICTL, 0xFFC30060, __READ_WRITE, uint8);
__IOREG(DNFAENCA0IEN, 0xFFC30064, __READ_WRITE, uint16);
__IOREG(DNFAENCA0IENL, 0xFFC3006C, __READ_WRITE, uint8);
#define DNFAENCA0IENL0     (((volatile __bitf_T *)0xFFC3006C)->bit00)
#define DNFAENCA0IENL1     (((volatile __bitf_T *)0xFFC3006C)->bit01)
#define DNFAENCA0IENL2     (((volatile __bitf_T *)0xFFC3006C)->bit02)
#define DNFAENCA0IENL3     (((volatile __bitf_T *)0xFFC3006C)->bit03)
#define DNFAENCA0IENL4     (((volatile __bitf_T *)0xFFC3006C)->bit04)
__IOREG(DNFAADCTL0CTL, 0xFFC300A0, __READ_WRITE, uint8);
__IOREG(DNFAADCTL0EN, 0xFFC300A4, __READ_WRITE, uint16);
__IOREG(DNFAADCTL0ENL, 0xFFC300AC, __READ_WRITE, uint8);
#define DNFAADCTL0ENL0     (((volatile __bitf_T *)0xFFC300AC)->bit00)
#define DNFAADCTL0ENL1     (((volatile __bitf_T *)0xFFC300AC)->bit01)
#define DNFAADCTL0ENL2     (((volatile __bitf_T *)0xFFC300AC)->bit02)
__IOREG(DNFAADCTL1CTL, 0xFFC300C0, __READ_WRITE, uint8);
__IOREG(DNFAADCTL1EN, 0xFFC300C4, __READ_WRITE, uint16);
__IOREG(DNFAADCTL1ENL, 0xFFC300CC, __READ_WRITE, uint8);
#define DNFAADCTL1ENL0     (((volatile __bitf_T *)0xFFC300CC)->bit00)
#define DNFAADCTL1ENL1     (((volatile __bitf_T *)0xFFC300CC)->bit01)
#define DNFAADCTL1ENL2     (((volatile __bitf_T *)0xFFC300CC)->bit02)
__IOREG(FCLA0CTL0_NMI, 0xFFC34000, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_INTPL, 0xFFC34020, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_INTPL, 0xFFC34024, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_INTPL, 0xFFC34028, __READ_WRITE, uint8);
__IOREG(FCLA0CTL3_INTPL, 0xFFC3402C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL4_INTPL, 0xFFC34030, __READ_WRITE, uint8);
__IOREG(FCLA0CTL5_INTPL, 0xFFC34034, __READ_WRITE, uint8);
__IOREG(FCLA0CTL6_INTPL, 0xFFC34038, __READ_WRITE, uint8);
__IOREG(FCLA0CTL7_INTPL, 0xFFC3403C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_INTPH, 0xFFC34040, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_INTPH, 0xFFC34044, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_INTPH, 0xFFC34048, __READ_WRITE, uint8);
__IOREG(FCLA0CTL3_INTPH, 0xFFC3404C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL4_INTPH, 0xFFC34050, __READ_WRITE, uint8);
__IOREG(FCLA0CTL5_INTPH, 0xFFC34054, __READ_WRITE, uint8);
__IOREG(FCLA0CTL6_INTPH, 0xFFC34058, __READ_WRITE, uint8);
__IOREG(FCLA0CTL7_INTPH, 0xFFC3405C, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_ADC0, 0xFFC34060, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_ADC0, 0xFFC34064, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_ADC0, 0xFFC34068, __READ_WRITE, uint8);
__IOREG(FCLA0CTL0_ADC1, 0xFFC34080, __READ_WRITE, uint8);
__IOREG(FCLA0CTL1_ADC1, 0xFFC34084, __READ_WRITE, uint8);
__IOREG(FCLA0CTL2_ADC1, 0xFFC34088, __READ_WRITE, uint8);
__IOREG(EEPRDCYCL, 0xFFC5A010, __READ_WRITE, uint8);
__IOREG(CFECCCTL, 0xFFC62000, __READ_WRITE, uint16);
__IOREG(CFFSTERSTR, 0xFFC62004, __READ, uint32);
__IOREG(CFFSTSTC, 0xFFC62024, __READ_WRITE, uint8);
__IOREG(CFOVFSTR, 0xFFC62028, __READ, uint8);
__IOREG(CFOVFSTC, 0xFFC6202C, __READ_WRITE, uint8);
__IOREG(CFERRINT, 0xFFC62030, __READ_WRITE, uint8);
__IOREG(CFFSTEADR, 0xFFC62034, __READ, uint32);
__IOREG(CFTSTCTL, 0xFFC62054, __READ_WRITE, uint16);
__IOREG(LRECCCTL, 0xFFC63000, __READ_WRITE, uint16);
__IOREG(LRFSTERSTR, 0xFFC63004, __READ, uint32);
__IOREG(LRSTCLR, 0xFFC63024, __READ_WRITE, uint8);
__IOREG(LROVFSTR, 0xFFC63028, __READ, uint8);
__IOREG(LROVFSTC, 0xFFC6302C, __READ_WRITE, uint8);
__IOREG(LRFSTEADR0, 0xFFC63030, __READ, uint32);
__IOREG(LRERRINT, 0xFFC630B0, __READ_WRITE, uint8);
__IOREG(LRTSTCTL, 0xFFC630B4, __READ_WRITE, uint16);
__IOREG(LRTDATBF0, 0xFFC630B8, __READ, uint32);
__IOREG(DFECCCTL, 0xFFC66000, __READ_WRITE, uint16);
__IOREG(DFERSTR, 0xFFC66004, __READ, uint32);
__IOREG(DFERSTC, 0xFFC66008, __READ_WRITE, uint8);
__IOREG(DFERRINT, 0xFFC66014, __READ_WRITE, uint8);
__IOREG(DFTSTCTL, 0xFFC6601C, __READ_WRITE, uint16);
__IOREG(ECCCSIH0CTL, 0xFFC70000, __READ_WRITE, uint16);
__IOREG(ECCCSIH0TMC, 0xFFC70004, __READ_WRITE, uint16);
__IOREG(ECCCSIH0TRC, 0xFFC70008, __READ_WRITE, uint32);
__IOREG(ECCCSIH0ERDB, 0xFFC70008, __READ_WRITE, uint8);
__IOREG(ECCCSIH0ECRD, 0xFFC70009, __READ_WRITE, uint8);
__IOREG(ECCCSIH0HORD, 0xFFC7000A, __READ_WRITE, uint8);
__IOREG(ECCCSIH0SYND, 0xFFC7000B, __READ_WRITE, uint8);
__IOREG(ECCCSIH0TED, 0xFFC7000C, __READ_WRITE, uint32);
__IOREG(ECCCSIH1CTL, 0xFFC70010, __READ_WRITE, uint16);
__IOREG(ECCCSIH1TMC, 0xFFC70014, __READ_WRITE, uint16);
__IOREG(ECCCSIH1TRC, 0xFFC70018, __READ_WRITE, uint32);
__IOREG(ECCCSIH1ERDB, 0xFFC70018, __READ_WRITE, uint8);
__IOREG(ECCCSIH1ECRD, 0xFFC70019, __READ_WRITE, uint8);
__IOREG(ECCCSIH1HORD, 0xFFC7001A, __READ_WRITE, uint8);
__IOREG(ECCCSIH1SYND, 0xFFC7001B, __READ_WRITE, uint8);
__IOREG(ECCCSIH1TED, 0xFFC7001C, __READ_WRITE, uint32);
__IOREG(ECCCSIH2CTL, 0xFFC70020, __READ_WRITE, uint16);
__IOREG(ECCCSIH2TMC, 0xFFC70024, __READ_WRITE, uint16);
__IOREG(ECCCSIH2TRC, 0xFFC70028, __READ_WRITE, uint32);
__IOREG(ECCCSIH2ERDB, 0xFFC70028, __READ_WRITE, uint8);
__IOREG(ECCCSIH2ECRD, 0xFFC70029, __READ_WRITE, uint8);
__IOREG(ECCCSIH2HORD, 0xFFC7002A, __READ_WRITE, uint8);
__IOREG(ECCCSIH2SYND, 0xFFC7002B, __READ_WRITE, uint8);
__IOREG(ECCCSIH2TED, 0xFFC7002C, __READ_WRITE, uint32);
__IOREG(ECCCSIH3CTL, 0xFFC70030, __READ_WRITE, uint16);
__IOREG(ECCCSIH3TMC, 0xFFC70034, __READ_WRITE, uint16);
__IOREG(ECCCSIH3TRC, 0xFFC70038, __READ_WRITE, uint32);
__IOREG(ECCCSIH3ERDB, 0xFFC70038, __READ_WRITE, uint8);
__IOREG(ECCCSIH3ECRD, 0xFFC70039, __READ_WRITE, uint8);
__IOREG(ECCCSIH3HORD, 0xFFC7003A, __READ_WRITE, uint8);
__IOREG(ECCCSIH3SYND, 0xFFC7003B, __READ_WRITE, uint8);
__IOREG(ECCCSIH3TED, 0xFFC7003C, __READ_WRITE, uint32);
__IOREG(ECCRCAN0CTL, 0xFFC71000, __READ_WRITE, uint16);
__IOREG(ECCRCAN0TMC, 0xFFC71004, __READ_WRITE, uint16);
__IOREG(ECCRCAN0TRC, 0xFFC71008, __READ_WRITE, uint32);
__IOREG(ECCRCAN0ERDB, 0xFFC71008, __READ_WRITE, uint8);
__IOREG(ECCRCAN0ECRD, 0xFFC71009, __READ_WRITE, uint8);
__IOREG(ECCRCAN0HORD, 0xFFC7100A, __READ_WRITE, uint8);
__IOREG(ECCRCAN0SYND, 0xFFC7100B, __READ_WRITE, uint8);
__IOREG(ECCRCAN0TED, 0xFFC7100C, __READ_WRITE, uint32);
__IOREG(CVMF, 0xFFF50000, __READ_WRITE, uint32);
__IOREG(CVMDE, 0xFFF50004, __READ, uint32);
__IOREG(CVMDIAG, 0xFFF50014, __READ_WRITE, uint32);
__IOREG(PROTCMDCVM, 0xFFF50100, __READ_WRITE, uint32);
__IOREG(PROTSCVM, 0xFFF50104, __READ, uint32);
__IOREG(PROTCMD0, 0xFFF80000, __READ_WRITE, uint32);
__IOREG(PROTS0, 0xFFF80004, __READ, uint32);
__IOREG(STBC0PSC, 0xFFF80100, __READ_WRITE, uint32);
__IOREG(STBC0STPT, 0xFFF80110, __READ_WRITE, uint32);
__IOREG(WDTNMIF, 0xFFF80200, __READ, uint32);
__IOREG(WDTNMIFC, 0xFFF80208, __READ_WRITE, uint32);
__IOREG(FEINTF, 0xFFF80300, __READ, uint32);
__IOREG(FEINTFMSK, 0xFFF80304, __READ_WRITE, uint32);
__IOREG(FEINTFC, 0xFFF80308, __READ_WRITE, uint32);
__IOREG(WUF0, 0xFFF80400, __READ, uint32);
__IOREG(WUFMSK0, 0xFFF80404, __READ_WRITE, uint32);
__IOREG(WUFC0, 0xFFF80408, __READ_WRITE, uint32);
__IOREG(WUF20, 0xFFF80520, __READ, uint32);
__IOREG(WUFMSK20, 0xFFF80524, __READ_WRITE, uint32);
__IOREG(WUFC20, 0xFFF80528, __READ_WRITE, uint32);
__IOREG(RESF, 0xFFF80760, __READ, uint32);
__IOREG(RESFC, 0xFFF80768, __READ_WRITE, uint32);
__IOREG(RESFR, 0xFFF80860, __READ, uint32);
__IOREG(RESFCR, 0xFFF80868, __READ_WRITE, uint32);
__IOREG(VLVF, 0xFFF80980, __READ, uint32);
__IOREG(VLVFC, 0xFFF80988, __READ_WRITE, uint32);
__IOREG(LVICNT, 0xFFF80A00, __READ_WRITE, uint32);
__IOREG(SWRESA, 0xFFF80A04, __READ_WRITE, uint32);
__IOREG(IOHOLD, 0xFFF80B00, __READ_WRITE, uint32);
__IOREG(ROSCE, 0xFFF81000, __READ_WRITE, uint32);
__IOREG(ROSCS, 0xFFF81004, __READ, uint32);
__IOREG(ROSCSTPM, 0xFFF81018, __READ_WRITE, uint32);
__IOREG(MOSCE, 0xFFF81100, __READ_WRITE, uint32);
__IOREG(MOSCS, 0xFFF81104, __READ, uint32);
__IOREG(MOSCC, 0xFFF81108, __READ_WRITE, uint32);
__IOREG(MOSCST, 0xFFF8110C, __READ_WRITE, uint32);
__IOREG(MOSCSTPM, 0xFFF81118, __READ_WRITE, uint32);
__IOREG(SOSCE, 0xFFF81200, __READ_WRITE, uint32);
__IOREG(SOSCS, 0xFFF81204, __READ, uint32);
__IOREG(SOSCST, 0xFFF8120C, __READ_WRITE, uint32);
__IOREG(CKSC_AWDTAD_CTL, 0xFFF82000, __READ_WRITE, uint32);
__IOREG(CKSC_AWDTAD_ACT, 0xFFF82008, __READ, uint32);
__IOREG(CKSC_AWDTAD_STPM, 0xFFF82018, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJS_CTL, 0xFFF82100, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJS_ACT, 0xFFF82108, __READ, uint32);
__IOREG(CKSC_ATAUJD_CTL, 0xFFF82200, __READ_WRITE, uint32);
__IOREG(CKSC_ATAUJD_ACT, 0xFFF82208, __READ, uint32);
__IOREG(CKSC_ATAUJD_STPM, 0xFFF82218, __READ_WRITE, uint32);
__IOREG(CKSC_ARTCAS_CTL, 0xFFF82300, __READ_WRITE, uint32);
__IOREG(CKSC_ARTCAS_ACT, 0xFFF82308, __READ, uint32);
__IOREG(CKSC_ARTCAD_CTL, 0xFFF82400, __READ_WRITE, uint32);
__IOREG(CKSC_ARTCAD_ACT, 0xFFF82408, __READ, uint32);
__IOREG(CKSC_ARTCAD_STPM, 0xFFF82418, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAS_CTL, 0xFFF82500, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAS_ACT, 0xFFF82508, __READ, uint32);
__IOREG(CKSC_AADCAD_CTL, 0xFFF82600, __READ_WRITE, uint32);
__IOREG(CKSC_AADCAD_ACT, 0xFFF82608, __READ, uint32);
__IOREG(CKSC_AADCAD_STPM, 0xFFF82618, __READ_WRITE, uint32);
__IOREG(CKSC_AFOUTS_CTL, 0xFFF82700, __READ_WRITE, uint32);
__IOREG(CKSC_AFOUTS_ACT, 0xFFF82708, __READ, uint32);
__IOREG(CKSC_AFOUTS_STPM, 0xFFF82718, __READ_WRITE, uint32);
__IOREG(FOUTDIV, 0xFFF82800, __READ_WRITE, uint32);
__IOREG(FOUTSTAT, 0xFFF82804, __READ, uint32);
__IOREG(PROTCMD1, 0xFFF88000, __READ_WRITE, uint32);
__IOREG(PROTS1, 0xFFF88004, __READ, uint32);
__IOREG(WUF_ISO0, 0xFFF88110, __READ, uint32);
__IOREG(WUFMSK_ISO0, 0xFFF88114, __READ_WRITE, uint32);
__IOREG(WUFC_ISO0, 0xFFF88118, __READ_WRITE, uint32);
__IOREG(PLLE, 0xFFF89000, __READ_WRITE, uint32);
__IOREG(PLLS, 0xFFF89004, __READ, uint32);
__IOREG(PLLC, 0xFFF89008, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKS_CTL, 0xFFF8A000, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKS_ACT, 0xFFF8A008, __READ, uint32);
__IOREG(CKSC_CPUCLKD_CTL, 0xFFF8A100, __READ_WRITE, uint32);
__IOREG(CKSC_CPUCLKD_ACT, 0xFFF8A108, __READ, uint32);
__IOREG(CKSC_IPERI1S_CTL, 0xFFF8A200, __READ_WRITE, uint32);
__IOREG(CKSC_IPERI1S_ACT, 0xFFF8A208, __READ, uint32);
__IOREG(CKSC_IPERI2S_CTL, 0xFFF8A300, __READ_WRITE, uint32);
__IOREG(CKSC_IPERI2S_ACT, 0xFFF8A308, __READ, uint32);
__IOREG(CKSC_ILINS_CTL, 0xFFF8A400, __READ_WRITE, uint32);
__IOREG(CKSC_ILINS_ACT, 0xFFF8A408, __READ, uint32);
__IOREG(CKSC_IADCAS_CTL, 0xFFF8A500, __READ_WRITE, uint32);
__IOREG(CKSC_IADCAS_ACT, 0xFFF8A508, __READ, uint32);
__IOREG(CKSC_IADCAD_CTL, 0xFFF8A600, __READ_WRITE, uint32);
__IOREG(CKSC_IADCAD_ACT, 0xFFF8A608, __READ, uint32);
__IOREG(CKSC_ILIND_CTL, 0xFFF8A800, __READ_WRITE, uint32);
__IOREG(CKSC_ILIND_ACT, 0xFFF8A808, __READ, uint32);
__IOREG(CKSC_ILIND_STPM, 0xFFF8A818, __READ_WRITE, uint32);
__IOREG(CKSC_ICANS_CTL, 0xFFF8A900, __READ_WRITE, uint32);
__IOREG(CKSC_ICANS_ACT, 0xFFF8A908, __READ, uint32);
__IOREG(CKSC_ICANS_STPM, 0xFFF8A918, __READ_WRITE, uint32);
__IOREG(CKSC_ICANOSCD_CTL, 0xFFF8AA00, __READ_WRITE, uint32);
__IOREG(CKSC_ICANOSCD_ACT, 0xFFF8AA08, __READ, uint32);
__IOREG(CKSC_ICANOSCD_STPM, 0xFFF8AA18, __READ_WRITE, uint32);
__IOREG(CKSC_ICSIS_CTL, 0xFFF8AB00, __READ_WRITE, uint32);
__IOREG(CKSC_ICSIS_ACT, 0xFFF8AB08, __READ, uint32);
__IOREG(PROTCMDCLMA, 0xFFF8C200, __READ_WRITE, uint32);
__IOREG(PROTSCLMA, 0xFFF8C204, __READ, uint32);
__IOREG(BSC, 0xFFFF8200, __READ_WRITE, uint16);
__IOREG(DEC, 0xFFFF8202, __READ_WRITE, uint16);
__IOREG(DWC, 0xFFFF8208, __READ_WRITE, uint16);
__IOREG(DHC, 0xFFFF820C, __READ_WRITE, uint16);
__IOREG(AWC, 0xFFFF8210, __READ_WRITE, uint16);
__IOREG(ICC, 0xFFFF8214, __READ_WRITE, uint16);
__IOREG(DTRC0, 0xFFFF8300, __READ_WRITE, uint8);
#define DTRC0ADS           (((volatile __bitf_T *)0xFFFF8300)->bit00)
#define DTRC0ERR           (((volatile __bitf_T *)0xFFFF8300)->bit07)
__IOREG(DMCM0, 0xFFFF8304, __READ_WRITE, uint16);
__IOREG(DSA0, 0xFFFF8314, __READ_WRITE, uint32);
__IOREG(DSA0L, 0xFFFF8314, __READ_WRITE, uint16);
__IOREG(DSA0H, 0xFFFF8316, __READ_WRITE, uint16);
__IOREG(DDA0, 0xFFFF8324, __READ_WRITE, uint32);
__IOREG(DDA0L, 0xFFFF8324, __READ_WRITE, uint16);
__IOREG(DDA0H, 0xFFFF8326, __READ_WRITE, uint16);
__IOREG(DTC0, 0xFFFF8332, __READ_WRITE, uint16);
__IOREG(DTCT0, 0xFFFF8338, __READ_WRITE, uint16);
__IOREG(DTS0, 0xFFFF833A, __READ_WRITE, uint8);
#define DTS0DTE            (((volatile __bitf_T *)0xFFFF833A)->bit00)
#define DTS0SR             (((volatile __bitf_T *)0xFFFF833A)->bit01)
#define DTS0DR             (((volatile __bitf_T *)0xFFFF833A)->bit02)
#define DTS0ER             (((volatile __bitf_T *)0xFFFF833A)->bit03)
#define DTS0DT             (((volatile __bitf_T *)0xFFFF833A)->bit06)
#define DTS0TC             (((volatile __bitf_T *)0xFFFF833A)->bit07)
__IOREG(DSA1, 0xFFFF8344, __READ_WRITE, uint32);
__IOREG(DSA1L, 0xFFFF8344, __READ_WRITE, uint16);
__IOREG(DSA1H, 0xFFFF8346, __READ_WRITE, uint16);
__IOREG(DDA1, 0xFFFF8354, __READ_WRITE, uint32);
__IOREG(DDA1L, 0xFFFF8354, __READ_WRITE, uint16);
__IOREG(DDA1H, 0xFFFF8356, __READ_WRITE, uint16);
__IOREG(DTC1, 0xFFFF8362, __READ_WRITE, uint16);
__IOREG(DTCT1, 0xFFFF8368, __READ_WRITE, uint16);
__IOREG(DTS1, 0xFFFF836A, __READ_WRITE, uint8);
#define DTS1DTE            (((volatile __bitf_T *)0xFFFF836A)->bit00)
#define DTS1SR             (((volatile __bitf_T *)0xFFFF836A)->bit01)
#define DTS1DR             (((volatile __bitf_T *)0xFFFF836A)->bit02)
#define DTS1ER             (((volatile __bitf_T *)0xFFFF836A)->bit03)
#define DTS1DT             (((volatile __bitf_T *)0xFFFF836A)->bit06)
#define DTS1TC             (((volatile __bitf_T *)0xFFFF836A)->bit07)
__IOREG(DSA2, 0xFFFF8374, __READ_WRITE, uint32);
__IOREG(DSA2L, 0xFFFF8374, __READ_WRITE, uint16);
__IOREG(DSA2H, 0xFFFF8376, __READ_WRITE, uint16);
__IOREG(DDA2, 0xFFFF8384, __READ_WRITE, uint32);
__IOREG(DDA2L, 0xFFFF8384, __READ_WRITE, uint16);
__IOREG(DDA2H, 0xFFFF8386, __READ_WRITE, uint16);
__IOREG(DTC2, 0xFFFF8392, __READ_WRITE, uint16);
__IOREG(DTCT2, 0xFFFF8398, __READ_WRITE, uint16);
__IOREG(DTS2, 0xFFFF839A, __READ_WRITE, uint8);
#define DTS2DTE            (((volatile __bitf_T *)0xFFFF839A)->bit00)
#define DTS2SR             (((volatile __bitf_T *)0xFFFF839A)->bit01)
#define DTS2DR             (((volatile __bitf_T *)0xFFFF839A)->bit02)
#define DTS2ER             (((volatile __bitf_T *)0xFFFF839A)->bit03)
#define DTS2DT             (((volatile __bitf_T *)0xFFFF839A)->bit06)
#define DTS2TC             (((volatile __bitf_T *)0xFFFF839A)->bit07)
__IOREG(DSA3, 0xFFFF83A4, __READ_WRITE, uint32);
__IOREG(DSA3L, 0xFFFF83A4, __READ_WRITE, uint16);
__IOREG(DSA3H, 0xFFFF83A6, __READ_WRITE, uint16);
__IOREG(DDA3, 0xFFFF83B4, __READ_WRITE, uint32);
__IOREG(DDA3L, 0xFFFF83B4, __READ_WRITE, uint16);
__IOREG(DDA3H, 0xFFFF83B6, __READ_WRITE, uint16);
__IOREG(DTC3, 0xFFFF83C2, __READ_WRITE, uint16);
__IOREG(DTCT3, 0xFFFF83C8, __READ_WRITE, uint16);
__IOREG(DTS3, 0xFFFF83CA, __READ_WRITE, uint8);
#define DTS3DTE            (((volatile __bitf_T *)0xFFFF83CA)->bit00)
#define DTS3SR             (((volatile __bitf_T *)0xFFFF83CA)->bit01)
#define DTS3DR             (((volatile __bitf_T *)0xFFFF83CA)->bit02)
#define DTS3ER             (((volatile __bitf_T *)0xFFFF83CA)->bit03)
#define DTS3DT             (((volatile __bitf_T *)0xFFFF83CA)->bit06)
#define DTS3TC             (((volatile __bitf_T *)0xFFFF83CA)->bit07)
__IOREG(DSA4, 0xFFFF83D4, __READ_WRITE, uint32);
__IOREG(DSA4L, 0xFFFF83D4, __READ_WRITE, uint16);
__IOREG(DSA4H, 0xFFFF83D6, __READ_WRITE, uint16);
__IOREG(DDA4, 0xFFFF83E4, __READ_WRITE, uint32);
__IOREG(DDA4L, 0xFFFF83E4, __READ_WRITE, uint16);
__IOREG(DDA4H, 0xFFFF83E6, __READ_WRITE, uint16);
__IOREG(DTC4, 0xFFFF83F2, __READ_WRITE, uint16);
__IOREG(DTCT4, 0xFFFF83F8, __READ_WRITE, uint16);
__IOREG(DTS4, 0xFFFF83FA, __READ_WRITE, uint8);
#define DTS4DTE            (((volatile __bitf_T *)0xFFFF83FA)->bit00)
#define DTS4SR             (((volatile __bitf_T *)0xFFFF83FA)->bit01)
#define DTS4DR             (((volatile __bitf_T *)0xFFFF83FA)->bit02)
#define DTS4ER             (((volatile __bitf_T *)0xFFFF83FA)->bit03)
#define DTS4DT             (((volatile __bitf_T *)0xFFFF83FA)->bit06)
#define DTS4TC             (((volatile __bitf_T *)0xFFFF83FA)->bit07)
__IOREG(DSA5, 0xFFFF8404, __READ_WRITE, uint32);
__IOREG(DSA5L, 0xFFFF8404, __READ_WRITE, uint16);
__IOREG(DSA5H, 0xFFFF8406, __READ_WRITE, uint16);
__IOREG(DDA5, 0xFFFF8414, __READ_WRITE, uint32);
__IOREG(DDA5L, 0xFFFF8414, __READ_WRITE, uint16);
__IOREG(DDA5H, 0xFFFF8416, __READ_WRITE, uint16);
__IOREG(DTC5, 0xFFFF8422, __READ_WRITE, uint16);
__IOREG(DTCT5, 0xFFFF8428, __READ_WRITE, uint16);
__IOREG(DTS5, 0xFFFF842A, __READ_WRITE, uint8);
#define DTS5DTE            (((volatile __bitf_T *)0xFFFF842A)->bit00)
#define DTS5SR             (((volatile __bitf_T *)0xFFFF842A)->bit01)
#define DTS5DR             (((volatile __bitf_T *)0xFFFF842A)->bit02)
#define DTS5ER             (((volatile __bitf_T *)0xFFFF842A)->bit03)
#define DTS5DT             (((volatile __bitf_T *)0xFFFF842A)->bit06)
#define DTS5TC             (((volatile __bitf_T *)0xFFFF842A)->bit07)
__IOREG(DSA6, 0xFFFF8434, __READ_WRITE, uint32);
__IOREG(DSA6L, 0xFFFF8434, __READ_WRITE, uint16);
__IOREG(DSA6H, 0xFFFF8436, __READ_WRITE, uint16);
__IOREG(DDA6, 0xFFFF8444, __READ_WRITE, uint32);
__IOREG(DDA6L, 0xFFFF8444, __READ_WRITE, uint16);
__IOREG(DDA6H, 0xFFFF8446, __READ_WRITE, uint16);
__IOREG(DTC6, 0xFFFF8452, __READ_WRITE, uint16);
__IOREG(DTCT6, 0xFFFF8458, __READ_WRITE, uint16);
__IOREG(DTS6, 0xFFFF845A, __READ_WRITE, uint8);
#define DTS6DTE            (((volatile __bitf_T *)0xFFFF845A)->bit00)
#define DTS6SR             (((volatile __bitf_T *)0xFFFF845A)->bit01)
#define DTS6DR             (((volatile __bitf_T *)0xFFFF845A)->bit02)
#define DTS6ER             (((volatile __bitf_T *)0xFFFF845A)->bit03)
#define DTS6DT             (((volatile __bitf_T *)0xFFFF845A)->bit06)
#define DTS6TC             (((volatile __bitf_T *)0xFFFF845A)->bit07)
__IOREG(DSA7, 0xFFFF8464, __READ_WRITE, uint32);
__IOREG(DSA7L, 0xFFFF8464, __READ_WRITE, uint16);
__IOREG(DSA7H, 0xFFFF8466, __READ_WRITE, uint16);
__IOREG(DDA7, 0xFFFF8474, __READ_WRITE, uint32);
__IOREG(DDA7L, 0xFFFF8474, __READ_WRITE, uint16);
__IOREG(DDA7H, 0xFFFF8476, __READ_WRITE, uint16);
__IOREG(DTC7, 0xFFFF8482, __READ_WRITE, uint16);
__IOREG(DTCT7, 0xFFFF8488, __READ_WRITE, uint16);
__IOREG(DTS7, 0xFFFF848A, __READ_WRITE, uint8);
#define DTS7DTE            (((volatile __bitf_T *)0xFFFF848A)->bit00)
#define DTS7SR             (((volatile __bitf_T *)0xFFFF848A)->bit01)
#define DTS7DR             (((volatile __bitf_T *)0xFFFF848A)->bit02)
#define DTS7ER             (((volatile __bitf_T *)0xFFFF848A)->bit03)
#define DTS7DT             (((volatile __bitf_T *)0xFFFF848A)->bit06)
#define DTS7TC             (((volatile __bitf_T *)0xFFFF848A)->bit07)
__IOREG(DSA8, 0xFFFF8514, __READ_WRITE, uint32);
__IOREG(DSA8L, 0xFFFF8514, __READ_WRITE, uint16);
__IOREG(DSA8H, 0xFFFF8516, __READ_WRITE, uint16);
__IOREG(DDA8, 0xFFFF8524, __READ_WRITE, uint32);
__IOREG(DDA8L, 0xFFFF8524, __READ_WRITE, uint16);
__IOREG(DDA8H, 0xFFFF8526, __READ_WRITE, uint16);
__IOREG(DTC8, 0xFFFF8532, __READ_WRITE, uint16);
__IOREG(DTCT8, 0xFFFF8538, __READ_WRITE, uint16);
__IOREG(DTS8, 0xFFFF853A, __READ_WRITE, uint8);
#define DTS8DTE            (((volatile __bitf_T *)0xFFFF853A)->bit00)
#define DTS8SR             (((volatile __bitf_T *)0xFFFF853A)->bit01)
#define DTS8DR             (((volatile __bitf_T *)0xFFFF853A)->bit02)
#define DTS8ER             (((volatile __bitf_T *)0xFFFF853A)->bit03)
#define DTS8DT             (((volatile __bitf_T *)0xFFFF853A)->bit06)
#define DTS8TC             (((volatile __bitf_T *)0xFFFF853A)->bit07)
__IOREG(DSA9, 0xFFFF8544, __READ_WRITE, uint32);
__IOREG(DSA9L, 0xFFFF8544, __READ_WRITE, uint16);
__IOREG(DSA9H, 0xFFFF8546, __READ_WRITE, uint16);
__IOREG(DDA9, 0xFFFF8554, __READ_WRITE, uint32);
__IOREG(DDA9L, 0xFFFF8554, __READ_WRITE, uint16);
__IOREG(DDA9H, 0xFFFF8556, __READ_WRITE, uint16);
__IOREG(DTC9, 0xFFFF8562, __READ_WRITE, uint16);
__IOREG(DTCT9, 0xFFFF8568, __READ_WRITE, uint16);
__IOREG(DTS9, 0xFFFF856A, __READ_WRITE, uint8);
#define DTS9DTE            (((volatile __bitf_T *)0xFFFF856A)->bit00)
#define DTS9SR             (((volatile __bitf_T *)0xFFFF856A)->bit01)
#define DTS9DR             (((volatile __bitf_T *)0xFFFF856A)->bit02)
#define DTS9ER             (((volatile __bitf_T *)0xFFFF856A)->bit03)
#define DTS9DT             (((volatile __bitf_T *)0xFFFF856A)->bit06)
#define DTS9TC             (((volatile __bitf_T *)0xFFFF856A)->bit07)
__IOREG(DSA10, 0xFFFF8574, __READ_WRITE, uint32);
__IOREG(DSA10L, 0xFFFF8574, __READ_WRITE, uint16);
__IOREG(DSA10H, 0xFFFF8576, __READ_WRITE, uint16);
__IOREG(DDA10, 0xFFFF8584, __READ_WRITE, uint32);
__IOREG(DDA10L, 0xFFFF8584, __READ_WRITE, uint16);
__IOREG(DDA10H, 0xFFFF8586, __READ_WRITE, uint16);
__IOREG(DTC10, 0xFFFF8592, __READ_WRITE, uint16);
__IOREG(DTCT10, 0xFFFF8598, __READ_WRITE, uint16);
__IOREG(DTS10, 0xFFFF859A, __READ_WRITE, uint8);
#define DTS10DTE           (((volatile __bitf_T *)0xFFFF859A)->bit00)
#define DTS10SR            (((volatile __bitf_T *)0xFFFF859A)->bit01)
#define DTS10DR            (((volatile __bitf_T *)0xFFFF859A)->bit02)
#define DTS10ER            (((volatile __bitf_T *)0xFFFF859A)->bit03)
#define DTS10DT            (((volatile __bitf_T *)0xFFFF859A)->bit06)
#define DTS10TC            (((volatile __bitf_T *)0xFFFF859A)->bit07)
__IOREG(DSA11, 0xFFFF85A4, __READ_WRITE, uint32);
__IOREG(DSA11L, 0xFFFF85A4, __READ_WRITE, uint16);
__IOREG(DSA11H, 0xFFFF85A6, __READ_WRITE, uint16);
__IOREG(DDA11, 0xFFFF85B4, __READ_WRITE, uint32);
__IOREG(DDA11L, 0xFFFF85B4, __READ_WRITE, uint16);
__IOREG(DDA11H, 0xFFFF85B6, __READ_WRITE, uint16);
__IOREG(DTC11, 0xFFFF85C2, __READ_WRITE, uint16);
__IOREG(DTCT11, 0xFFFF85C8, __READ_WRITE, uint16);
__IOREG(DTS11, 0xFFFF85CA, __READ_WRITE, uint8);
#define DTS11DTE           (((volatile __bitf_T *)0xFFFF85CA)->bit00)
#define DTS11SR            (((volatile __bitf_T *)0xFFFF85CA)->bit01)
#define DTS11DR            (((volatile __bitf_T *)0xFFFF85CA)->bit02)
#define DTS11ER            (((volatile __bitf_T *)0xFFFF85CA)->bit03)
#define DTS11DT            (((volatile __bitf_T *)0xFFFF85CA)->bit06)
#define DTS11TC            (((volatile __bitf_T *)0xFFFF85CA)->bit07)
__IOREG(DSA12, 0xFFFF85D4, __READ_WRITE, uint32);
__IOREG(DSA12L, 0xFFFF85D4, __READ_WRITE, uint16);
__IOREG(DSA12H, 0xFFFF85D6, __READ_WRITE, uint16);
__IOREG(DDA12, 0xFFFF85E4, __READ_WRITE, uint32);
__IOREG(DDA12L, 0xFFFF85E4, __READ_WRITE, uint16);
__IOREG(DDA12H, 0xFFFF85E6, __READ_WRITE, uint16);
__IOREG(DTC12, 0xFFFF85F2, __READ_WRITE, uint16);
__IOREG(DTCT12, 0xFFFF85F8, __READ_WRITE, uint16);
__IOREG(DTS12, 0xFFFF85FA, __READ_WRITE, uint8);
#define DTS12DTE           (((volatile __bitf_T *)0xFFFF85FA)->bit00)
#define DTS12SR            (((volatile __bitf_T *)0xFFFF85FA)->bit01)
#define DTS12DR            (((volatile __bitf_T *)0xFFFF85FA)->bit02)
#define DTS12ER            (((volatile __bitf_T *)0xFFFF85FA)->bit03)
#define DTS12DT            (((volatile __bitf_T *)0xFFFF85FA)->bit06)
#define DTS12TC            (((volatile __bitf_T *)0xFFFF85FA)->bit07)
__IOREG(DSA13, 0xFFFF8604, __READ_WRITE, uint32);
__IOREG(DSA13L, 0xFFFF8604, __READ_WRITE, uint16);
__IOREG(DSA13H, 0xFFFF8606, __READ_WRITE, uint16);
__IOREG(DDA13, 0xFFFF8614, __READ_WRITE, uint32);
__IOREG(DDA13L, 0xFFFF8614, __READ_WRITE, uint16);
__IOREG(DDA13H, 0xFFFF8616, __READ_WRITE, uint16);
__IOREG(DTC13, 0xFFFF8622, __READ_WRITE, uint16);
__IOREG(DTCT13, 0xFFFF8628, __READ_WRITE, uint16);
__IOREG(DTS13, 0xFFFF862A, __READ_WRITE, uint8);
#define DTS13DTE           (((volatile __bitf_T *)0xFFFF862A)->bit00)
#define DTS13SR            (((volatile __bitf_T *)0xFFFF862A)->bit01)
#define DTS13DR            (((volatile __bitf_T *)0xFFFF862A)->bit02)
#define DTS13ER            (((volatile __bitf_T *)0xFFFF862A)->bit03)
#define DTS13DT            (((volatile __bitf_T *)0xFFFF862A)->bit06)
#define DTS13TC            (((volatile __bitf_T *)0xFFFF862A)->bit07)
__IOREG(DSA14, 0xFFFF8634, __READ_WRITE, uint32);
__IOREG(DSA14L, 0xFFFF8634, __READ_WRITE, uint16);
__IOREG(DSA14H, 0xFFFF8636, __READ_WRITE, uint16);
__IOREG(DDA14, 0xFFFF8644, __READ_WRITE, uint32);
__IOREG(DDA14L, 0xFFFF8644, __READ_WRITE, uint16);
__IOREG(DDA14H, 0xFFFF8646, __READ_WRITE, uint16);
__IOREG(DTC14, 0xFFFF8652, __READ_WRITE, uint16);
__IOREG(DTCT14, 0xFFFF8658, __READ_WRITE, uint16);
__IOREG(DTS14, 0xFFFF865A, __READ_WRITE, uint8);
#define DTS14DTE           (((volatile __bitf_T *)0xFFFF865A)->bit00)
#define DTS14SR            (((volatile __bitf_T *)0xFFFF865A)->bit01)
#define DTS14DR            (((volatile __bitf_T *)0xFFFF865A)->bit02)
#define DTS14ER            (((volatile __bitf_T *)0xFFFF865A)->bit03)
#define DTS14DT            (((volatile __bitf_T *)0xFFFF865A)->bit06)
#define DTS14TC            (((volatile __bitf_T *)0xFFFF865A)->bit07)
__IOREG(DSA15, 0xFFFF8664, __READ_WRITE, uint32);
__IOREG(DSA15L, 0xFFFF8664, __READ_WRITE, uint16);
__IOREG(DSA15H, 0xFFFF8666, __READ_WRITE, uint16);
__IOREG(DDA15, 0xFFFF8674, __READ_WRITE, uint32);
__IOREG(DDA15L, 0xFFFF8674, __READ_WRITE, uint16);
__IOREG(DDA15H, 0xFFFF8676, __READ_WRITE, uint16);
__IOREG(DTC15, 0xFFFF8682, __READ_WRITE, uint16);
__IOREG(DTCT15, 0xFFFF8688, __READ_WRITE, uint16);
__IOREG(DTS15, 0xFFFF868A, __READ_WRITE, uint8);
#define DTS15DTE           (((volatile __bitf_T *)0xFFFF868A)->bit00)
#define DTS15SR            (((volatile __bitf_T *)0xFFFF868A)->bit01)
#define DTS15DR            (((volatile __bitf_T *)0xFFFF868A)->bit02)
#define DTS15ER            (((volatile __bitf_T *)0xFFFF868A)->bit03)
#define DTS15DT            (((volatile __bitf_T *)0xFFFF868A)->bit06)
#define DTS15TC            (((volatile __bitf_T *)0xFFFF868A)->bit07)
__IOREG(DTFR0, 0xFFFF8B00, __READ_WRITE, uint16);
__IOREG(DTFR1, 0xFFFF8B02, __READ_WRITE, uint16);
__IOREG(DTFR2, 0xFFFF8B04, __READ_WRITE, uint16);
__IOREG(DTFR3, 0xFFFF8B06, __READ_WRITE, uint16);
__IOREG(DTFR4, 0xFFFF8B08, __READ_WRITE, uint16);
__IOREG(DTFR5, 0xFFFF8B0A, __READ_WRITE, uint16);
__IOREG(DTFR6, 0xFFFF8B0C, __READ_WRITE, uint16);
__IOREG(DTFR7, 0xFFFF8B0E, __READ_WRITE, uint16);
__IOREG(DTFR8, 0xFFFF8B10, __READ_WRITE, uint16);
__IOREG(DTFR9, 0xFFFF8B12, __READ_WRITE, uint16);
__IOREG(DTFR10, 0xFFFF8B14, __READ_WRITE, uint16);
__IOREG(DTFR11, 0xFFFF8B16, __READ_WRITE, uint16);
__IOREG(DTFR12, 0xFFFF8B18, __READ_WRITE, uint16);
__IOREG(DTFR13, 0xFFFF8B1A, __READ_WRITE, uint16);
__IOREG(DTFR14, 0xFFFF8B1C, __READ_WRITE, uint16);
__IOREG(DTFR15, 0xFFFF8B1E, __READ_WRITE, uint16);
__IOREG(DRQCLR, 0xFFFF8B40, __READ_WRITE, uint16);
__IOREG(DRQSTR, 0xFFFF8B44, __READ, uint16);
__IOREG(SEG_CONT, 0xFFFF8C00, __READ_WRITE, uint16);
__IOREG(SEG_CONTL, 0xFFFF8C00, __READ_WRITE, uint8);
#define SEG_CONTROME       (((volatile __bitf_T *)0xFFFF8C00)->bit01)
#define SEG_CONTEXTE       (((volatile __bitf_T *)0xFFFF8C00)->bit02)
#define SEG_CONTRAME       (((volatile __bitf_T *)0xFFFF8C00)->bit04)
#define SEG_CONTRMWE       (((volatile __bitf_T *)0xFFFF8C00)->bit06)
#define SEG_CONTDMAE       (((volatile __bitf_T *)0xFFFF8C00)->bit07)
__IOREG(SEG_FLAG, 0xFFFF8C02, __READ_WRITE, uint16);
__IOREG(SEG_FLAGL, 0xFFFF8C02, __READ_WRITE, uint8);
#define SEG_FLAGROMF       (((volatile __bitf_T *)0xFFFF8C02)->bit01)
#define SEG_FLAGEXTF       (((volatile __bitf_T *)0xFFFF8C02)->bit02)
#define SEG_FLAGRAMF       (((volatile __bitf_T *)0xFFFF8C02)->bit04)
#define SEG_FLAGRMWF       (((volatile __bitf_T *)0xFFFF8C02)->bit06)
#define SEG_FLAGDMAF       (((volatile __bitf_T *)0xFFFF8C02)->bit07)
__IOREG(ICCSIH2IC_1, 0xFFFF9000, __READ_WRITE, uint16);
__IOREG(ICTAUD0I0, 0xFFFF9000, __READ_WRITE, uint16);
__IOREG(ICCSIH2ICL_1, 0xFFFF9000, __READ_WRITE, uint8);
__IOREG(ICTAUD0I0L, 0xFFFF9000, __READ_WRITE, uint8);
__IOREG(ICCSIH2ICH_1, 0xFFFF9001, __READ_WRITE, uint8);
__IOREG(ICTAUD0I0H, 0xFFFF9001, __READ_WRITE, uint8);
#define P0CSIH2IC_1        (((volatile __bitf_T *)0xFFFF9000)->bit00)
#define P0TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit00)
#define P1CSIH2IC_1        (((volatile __bitf_T *)0xFFFF9000)->bit01)
#define P1TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit01)
#define P2CSIH2IC_1        (((volatile __bitf_T *)0xFFFF9000)->bit02)
#define P2TAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit02)
#define TBCSIH2IC_1        (((volatile __bitf_T *)0xFFFF9000)->bit06)
#define TBTAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit06)
#define MKCSIH2IC_1        (((volatile __bitf_T *)0xFFFF9000)->bit07)
#define MKTAUD0I0          (((volatile __bitf_T *)0xFFFF9000)->bit07)
#define RFCSIH2IC_1        (((volatile __bitf_T *)0xFFFF9001)->bit04)
#define RFTAUD0I0          (((volatile __bitf_T *)0xFFFF9001)->bit04)
#define CTCSIH2IC_1        (((volatile __bitf_T *)0xFFFF9001)->bit07)
#define CTTAUD0I0          (((volatile __bitf_T *)0xFFFF9001)->bit07)
__IOREG(ICCSIH3IC_1, 0xFFFF9002, __READ_WRITE, uint16);
__IOREG(ICTAUD0I2, 0xFFFF9002, __READ_WRITE, uint16);
__IOREG(ICCSIH3ICL_1, 0xFFFF9002, __READ_WRITE, uint8);
__IOREG(ICTAUD0I2L, 0xFFFF9002, __READ_WRITE, uint8);
__IOREG(ICCSIH3ICH_1, 0xFFFF9003, __READ_WRITE, uint8);
__IOREG(ICTAUD0I2H, 0xFFFF9003, __READ_WRITE, uint8);
#define P0CSIH3IC_1        (((volatile __bitf_T *)0xFFFF9002)->bit00)
#define P0TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit00)
#define P1CSIH3IC_1        (((volatile __bitf_T *)0xFFFF9002)->bit01)
#define P1TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit01)
#define P2CSIH3IC_1        (((volatile __bitf_T *)0xFFFF9002)->bit02)
#define P2TAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit02)
#define TBCSIH3IC_1        (((volatile __bitf_T *)0xFFFF9002)->bit06)
#define TBTAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit06)
#define MKCSIH3IC_1        (((volatile __bitf_T *)0xFFFF9002)->bit07)
#define MKTAUD0I2          (((volatile __bitf_T *)0xFFFF9002)->bit07)
#define RFCSIH3IC_1        (((volatile __bitf_T *)0xFFFF9003)->bit04)
#define RFTAUD0I2          (((volatile __bitf_T *)0xFFFF9003)->bit04)
#define CTCSIH3IC_1        (((volatile __bitf_T *)0xFFFF9003)->bit07)
#define CTTAUD0I2          (((volatile __bitf_T *)0xFFFF9003)->bit07)
__IOREG(ICTAUD0I4, 0xFFFF9004, __READ_WRITE, uint16);
__IOREG(ICTAUD0I4L, 0xFFFF9004, __READ_WRITE, uint8);
__IOREG(ICTAUD0I4H, 0xFFFF9005, __READ_WRITE, uint8);
#define P0TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit00)
#define P1TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit01)
#define P2TAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit02)
#define TBTAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit06)
#define MKTAUD0I4          (((volatile __bitf_T *)0xFFFF9004)->bit07)
#define RFTAUD0I4          (((volatile __bitf_T *)0xFFFF9005)->bit04)
#define CTTAUD0I4          (((volatile __bitf_T *)0xFFFF9005)->bit07)
__IOREG(ICTAUD0I6, 0xFFFF9006, __READ_WRITE, uint16);
__IOREG(ICTAUD0I6L, 0xFFFF9006, __READ_WRITE, uint8);
__IOREG(ICTAUD0I6H, 0xFFFF9007, __READ_WRITE, uint8);
#define P0TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit00)
#define P1TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit01)
#define P2TAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit02)
#define TBTAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit06)
#define MKTAUD0I6          (((volatile __bitf_T *)0xFFFF9006)->bit07)
#define RFTAUD0I6          (((volatile __bitf_T *)0xFFFF9007)->bit04)
#define CTTAUD0I6          (((volatile __bitf_T *)0xFFFF9007)->bit07)
__IOREG(ICTAUD0I8, 0xFFFF9008, __READ_WRITE, uint16);
__IOREG(ICTAUD0I8L, 0xFFFF9008, __READ_WRITE, uint8);
__IOREG(ICTAUD0I8H, 0xFFFF9009, __READ_WRITE, uint8);
#define P0TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit00)
#define P1TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit01)
#define P2TAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit02)
#define TBTAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit06)
#define MKTAUD0I8          (((volatile __bitf_T *)0xFFFF9008)->bit07)
#define RFTAUD0I8          (((volatile __bitf_T *)0xFFFF9009)->bit04)
#define CTTAUD0I8          (((volatile __bitf_T *)0xFFFF9009)->bit07)
__IOREG(ICCSIH3IR_1, 0xFFFF900A, __READ_WRITE, uint16);
__IOREG(ICTAUD0I10, 0xFFFF900A, __READ_WRITE, uint16);
__IOREG(ICCSIH3IRL_1, 0xFFFF900A, __READ_WRITE, uint8);
__IOREG(ICTAUD0I10L, 0xFFFF900A, __READ_WRITE, uint8);
__IOREG(ICCSIH3IRH_1, 0xFFFF900B, __READ_WRITE, uint8);
__IOREG(ICTAUD0I10H, 0xFFFF900B, __READ_WRITE, uint8);
#define P0CSIH3IR_1        (((volatile __bitf_T *)0xFFFF900A)->bit00)
#define P0TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit00)
#define P1CSIH3IR_1        (((volatile __bitf_T *)0xFFFF900A)->bit01)
#define P1TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit01)
#define P2CSIH3IR_1        (((volatile __bitf_T *)0xFFFF900A)->bit02)
#define P2TAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit02)
#define TBCSIH3IR_1        (((volatile __bitf_T *)0xFFFF900A)->bit06)
#define TBTAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit06)
#define MKCSIH3IR_1        (((volatile __bitf_T *)0xFFFF900A)->bit07)
#define MKTAUD0I10         (((volatile __bitf_T *)0xFFFF900A)->bit07)
#define RFCSIH3IR_1        (((volatile __bitf_T *)0xFFFF900B)->bit04)
#define RFTAUD0I10         (((volatile __bitf_T *)0xFFFF900B)->bit04)
#define CTCSIH3IR_1        (((volatile __bitf_T *)0xFFFF900B)->bit07)
#define CTTAUD0I10         (((volatile __bitf_T *)0xFFFF900B)->bit07)
__IOREG(ICCSIH3IRE_1, 0xFFFF900C, __READ_WRITE, uint16);
__IOREG(ICTAUD0I12, 0xFFFF900C, __READ_WRITE, uint16);
__IOREG(ICCSIH3IREL_1, 0xFFFF900C, __READ_WRITE, uint8);
__IOREG(ICTAUD0I12L, 0xFFFF900C, __READ_WRITE, uint8);
__IOREG(ICCSIH3IREH_1, 0xFFFF900D, __READ_WRITE, uint8);
__IOREG(ICTAUD0I12H, 0xFFFF900D, __READ_WRITE, uint8);
#define P0CSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900C)->bit00)
#define P0TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit00)
#define P1CSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900C)->bit01)
#define P1TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit01)
#define P2CSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900C)->bit02)
#define P2TAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit02)
#define TBCSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900C)->bit06)
#define TBTAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit06)
#define MKCSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900C)->bit07)
#define MKTAUD0I12         (((volatile __bitf_T *)0xFFFF900C)->bit07)
#define RFCSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900D)->bit04)
#define RFTAUD0I12         (((volatile __bitf_T *)0xFFFF900D)->bit04)
#define CTCSIH3IRE_1       (((volatile __bitf_T *)0xFFFF900D)->bit07)
#define CTTAUD0I12         (((volatile __bitf_T *)0xFFFF900D)->bit07)
__IOREG(ICCSIH3IJC_1, 0xFFFF900E, __READ_WRITE, uint16);
__IOREG(ICTAUD0I14, 0xFFFF900E, __READ_WRITE, uint16);
__IOREG(ICCSIH3IJCL_1, 0xFFFF900E, __READ_WRITE, uint8);
__IOREG(ICTAUD0I14L, 0xFFFF900E, __READ_WRITE, uint8);
__IOREG(ICCSIH3IJCH_1, 0xFFFF900F, __READ_WRITE, uint8);
__IOREG(ICTAUD0I14H, 0xFFFF900F, __READ_WRITE, uint8);
#define P0CSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900E)->bit00)
#define P0TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit00)
#define P1CSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900E)->bit01)
#define P1TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit01)
#define P2CSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900E)->bit02)
#define P2TAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit02)
#define TBCSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900E)->bit06)
#define TBTAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit06)
#define MKCSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900E)->bit07)
#define MKTAUD0I14         (((volatile __bitf_T *)0xFFFF900E)->bit07)
#define RFCSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900F)->bit04)
#define RFTAUD0I14         (((volatile __bitf_T *)0xFFFF900F)->bit04)
#define CTCSIH3IJC_1       (((volatile __bitf_T *)0xFFFF900F)->bit07)
#define CTTAUD0I14         (((volatile __bitf_T *)0xFFFF900F)->bit07)
__IOREG(ICCSIH1IC_1, 0xFFFF9010, __READ_WRITE, uint16);
__IOREG(ICTAPA0IPEK0, 0xFFFF9010, __READ_WRITE, uint16);
__IOREG(ICCSIH1ICL_1, 0xFFFF9010, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0L, 0xFFFF9010, __READ_WRITE, uint8);
__IOREG(ICCSIH1ICH_1, 0xFFFF9011, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0H, 0xFFFF9011, __READ_WRITE, uint8);
#define P0CSIH1IC_1        (((volatile __bitf_T *)0xFFFF9010)->bit00)
#define P0TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit00)
#define P1CSIH1IC_1        (((volatile __bitf_T *)0xFFFF9010)->bit01)
#define P1TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit01)
#define P2CSIH1IC_1        (((volatile __bitf_T *)0xFFFF9010)->bit02)
#define P2TAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit02)
#define TBCSIH1IC_1        (((volatile __bitf_T *)0xFFFF9010)->bit06)
#define TBTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit06)
#define MKCSIH1IC_1        (((volatile __bitf_T *)0xFFFF9010)->bit07)
#define MKTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9010)->bit07)
#define RFCSIH1IC_1        (((volatile __bitf_T *)0xFFFF9011)->bit04)
#define RFTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9011)->bit04)
#define CTCSIH1IC_1        (((volatile __bitf_T *)0xFFFF9011)->bit07)
#define CTTAPA0IPEK0       (((volatile __bitf_T *)0xFFFF9011)->bit07)
__IOREG(ICCSIH1IR_1, 0xFFFF9012, __READ_WRITE, uint16);
__IOREG(ICTAPA0IVLY0, 0xFFFF9012, __READ_WRITE, uint16);
__IOREG(ICCSIH1IRL_1, 0xFFFF9012, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0L, 0xFFFF9012, __READ_WRITE, uint8);
__IOREG(ICCSIH1IRH_1, 0xFFFF9013, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0H, 0xFFFF9013, __READ_WRITE, uint8);
#define P0CSIH1IR_1        (((volatile __bitf_T *)0xFFFF9012)->bit00)
#define P0TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit00)
#define P1CSIH1IR_1        (((volatile __bitf_T *)0xFFFF9012)->bit01)
#define P1TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit01)
#define P2CSIH1IR_1        (((volatile __bitf_T *)0xFFFF9012)->bit02)
#define P2TAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit02)
#define TBCSIH1IR_1        (((volatile __bitf_T *)0xFFFF9012)->bit06)
#define TBTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit06)
#define MKCSIH1IR_1        (((volatile __bitf_T *)0xFFFF9012)->bit07)
#define MKTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9012)->bit07)
#define RFCSIH1IR_1        (((volatile __bitf_T *)0xFFFF9013)->bit04)
#define RFTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9013)->bit04)
#define CTCSIH1IR_1        (((volatile __bitf_T *)0xFFFF9013)->bit07)
#define CTTAPA0IVLY0       (((volatile __bitf_T *)0xFFFF9013)->bit07)
__IOREG(ICADCA0I0, 0xFFFF9014, __READ_WRITE, uint16);
__IOREG(ICADCA0I0L, 0xFFFF9014, __READ_WRITE, uint8);
__IOREG(ICADCA0I0H, 0xFFFF9015, __READ_WRITE, uint8);
#define P0ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit00)
#define P1ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit01)
#define P2ADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit02)
#define TBADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit06)
#define MKADCA0I0          (((volatile __bitf_T *)0xFFFF9014)->bit07)
#define RFADCA0I0          (((volatile __bitf_T *)0xFFFF9015)->bit04)
#define CTADCA0I0          (((volatile __bitf_T *)0xFFFF9015)->bit07)
__IOREG(ICADCA0I1, 0xFFFF9016, __READ_WRITE, uint16);
__IOREG(ICADCA0I1L, 0xFFFF9016, __READ_WRITE, uint8);
__IOREG(ICADCA0I1H, 0xFFFF9017, __READ_WRITE, uint8);
#define P0ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit00)
#define P1ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit01)
#define P2ADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit02)
#define TBADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit06)
#define MKADCA0I1          (((volatile __bitf_T *)0xFFFF9016)->bit07)
#define RFADCA0I1          (((volatile __bitf_T *)0xFFFF9017)->bit04)
#define CTADCA0I1          (((volatile __bitf_T *)0xFFFF9017)->bit07)
__IOREG(ICADCA0I2, 0xFFFF9018, __READ_WRITE, uint16);
__IOREG(ICADCA0I2L, 0xFFFF9018, __READ_WRITE, uint8);
__IOREG(ICADCA0I2H, 0xFFFF9019, __READ_WRITE, uint8);
#define P0ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit00)
#define P1ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit01)
#define P2ADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit02)
#define TBADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit06)
#define MKADCA0I2          (((volatile __bitf_T *)0xFFFF9018)->bit07)
#define RFADCA0I2          (((volatile __bitf_T *)0xFFFF9019)->bit04)
#define CTADCA0I2          (((volatile __bitf_T *)0xFFFF9019)->bit07)
__IOREG(ICDCUTDI, 0xFFFF901A, __READ_WRITE, uint16);
__IOREG(ICDCUTDIL, 0xFFFF901A, __READ_WRITE, uint8);
__IOREG(ICDCUTDIH, 0xFFFF901B, __READ_WRITE, uint8);
#define P0DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit00)
#define P1DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit01)
#define P2DCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit02)
#define TBDCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit06)
#define MKDCUTDI           (((volatile __bitf_T *)0xFFFF901A)->bit07)
#define RFDCUTDI           (((volatile __bitf_T *)0xFFFF901B)->bit04)
#define CTDCUTDI           (((volatile __bitf_T *)0xFFFF901B)->bit07)
__IOREG(ICRCANGERR, 0xFFFF901C, __READ_WRITE, uint16);
__IOREG(ICRCANGERRL, 0xFFFF901C, __READ_WRITE, uint8);
__IOREG(ICRCANGERRH, 0xFFFF901D, __READ_WRITE, uint8);
#define P0RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit00)
#define P1RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit01)
#define P2RCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit02)
#define TBRCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit06)
#define MKRCANGERR         (((volatile __bitf_T *)0xFFFF901C)->bit07)
#define RFRCANGERR         (((volatile __bitf_T *)0xFFFF901D)->bit04)
#define CTRCANGERR         (((volatile __bitf_T *)0xFFFF901D)->bit07)
__IOREG(ICRCANGRECC, 0xFFFF901E, __READ_WRITE, uint16);
__IOREG(ICRCANGRECCL, 0xFFFF901E, __READ_WRITE, uint8);
__IOREG(ICRCANGRECCH, 0xFFFF901F, __READ_WRITE, uint8);
#define P0RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit00)
#define P1RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit01)
#define P2RCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit02)
#define TBRCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit06)
#define MKRCANGRECC        (((volatile __bitf_T *)0xFFFF901E)->bit07)
#define RFRCANGRECC        (((volatile __bitf_T *)0xFFFF901F)->bit04)
#define CTRCANGRECC        (((volatile __bitf_T *)0xFFFF901F)->bit07)
__IOREG(ICRCAN0ERR, 0xFFFF9020, __READ_WRITE, uint16);
__IOREG(ICRCAN0ERRL, 0xFFFF9020, __READ_WRITE, uint8);
__IOREG(ICRCAN0ERRH, 0xFFFF9021, __READ_WRITE, uint8);
#define P0RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit00)
#define P1RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit01)
#define P2RCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit02)
#define TBRCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit06)
#define MKRCAN0ERR         (((volatile __bitf_T *)0xFFFF9020)->bit07)
#define RFRCAN0ERR         (((volatile __bitf_T *)0xFFFF9021)->bit04)
#define CTRCAN0ERR         (((volatile __bitf_T *)0xFFFF9021)->bit07)
__IOREG(ICRCAN0REC, 0xFFFF9022, __READ_WRITE, uint16);
__IOREG(ICRCAN0RECL, 0xFFFF9022, __READ_WRITE, uint8);
__IOREG(ICRCAN0RECH, 0xFFFF9023, __READ_WRITE, uint8);
#define P0RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit00)
#define P1RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit01)
#define P2RCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit02)
#define TBRCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit06)
#define MKRCAN0REC         (((volatile __bitf_T *)0xFFFF9022)->bit07)
#define RFRCAN0REC         (((volatile __bitf_T *)0xFFFF9023)->bit04)
#define CTRCAN0REC         (((volatile __bitf_T *)0xFFFF9023)->bit07)
__IOREG(ICRCAN0TRX, 0xFFFF9024, __READ_WRITE, uint16);
__IOREG(ICRCAN0TRXL, 0xFFFF9024, __READ_WRITE, uint8);
__IOREG(ICRCAN0TRXH, 0xFFFF9025, __READ_WRITE, uint8);
#define P0RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit00)
#define P1RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit01)
#define P2RCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit02)
#define TBRCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit06)
#define MKRCAN0TRX         (((volatile __bitf_T *)0xFFFF9024)->bit07)
#define RFRCAN0TRX         (((volatile __bitf_T *)0xFFFF9025)->bit04)
#define CTRCAN0TRX         (((volatile __bitf_T *)0xFFFF9025)->bit07)
__IOREG(ICCSIG0IC, 0xFFFF9026, __READ_WRITE, uint16);
__IOREG(ICCSIH1IRE_1, 0xFFFF9026, __READ_WRITE, uint16);
__IOREG(ICCSIG0ICL, 0xFFFF9026, __READ_WRITE, uint8);
__IOREG(ICCSIH1IREL_1, 0xFFFF9026, __READ_WRITE, uint8);
__IOREG(ICCSIG0ICH, 0xFFFF9027, __READ_WRITE, uint8);
__IOREG(ICCSIH1IREH_1, 0xFFFF9027, __READ_WRITE, uint8);
#define P0CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit00)
#define P0CSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9026)->bit00)
#define P1CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit01)
#define P1CSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9026)->bit01)
#define P2CSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit02)
#define P2CSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9026)->bit02)
#define TBCSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit06)
#define TBCSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9026)->bit06)
#define MKCSIG0IC          (((volatile __bitf_T *)0xFFFF9026)->bit07)
#define MKCSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9026)->bit07)
#define RFCSIG0IC          (((volatile __bitf_T *)0xFFFF9027)->bit04)
#define RFCSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9027)->bit04)
#define CTCSIG0IC          (((volatile __bitf_T *)0xFFFF9027)->bit07)
#define CTCSIH1IRE_1       (((volatile __bitf_T *)0xFFFF9027)->bit07)
__IOREG(ICCSIG0IR, 0xFFFF9028, __READ_WRITE, uint16);
__IOREG(ICCSIH1IJC_1, 0xFFFF9028, __READ_WRITE, uint16);
__IOREG(ICCSIG0IRL, 0xFFFF9028, __READ_WRITE, uint8);
__IOREG(ICCSIH1IJCL_1, 0xFFFF9028, __READ_WRITE, uint8);
__IOREG(ICCSIG0IRH, 0xFFFF9029, __READ_WRITE, uint8);
__IOREG(ICCSIH1IJCH_1, 0xFFFF9029, __READ_WRITE, uint8);
#define P0CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit00)
#define P0CSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9028)->bit00)
#define P1CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit01)
#define P1CSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9028)->bit01)
#define P2CSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit02)
#define P2CSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9028)->bit02)
#define TBCSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit06)
#define TBCSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9028)->bit06)
#define MKCSIG0IR          (((volatile __bitf_T *)0xFFFF9028)->bit07)
#define MKCSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9028)->bit07)
#define RFCSIG0IR          (((volatile __bitf_T *)0xFFFF9029)->bit04)
#define RFCSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9029)->bit04)
#define CTCSIG0IR          (((volatile __bitf_T *)0xFFFF9029)->bit07)
#define CTCSIH1IJC_1       (((volatile __bitf_T *)0xFFFF9029)->bit07)
__IOREG(ICCSIH0IC, 0xFFFF902A, __READ_WRITE, uint16);
__IOREG(ICCSIH0ICL, 0xFFFF902A, __READ_WRITE, uint8);
__IOREG(ICCSIH0ICH, 0xFFFF902B, __READ_WRITE, uint8);
#define P0CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit00)
#define P1CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit01)
#define P2CSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit02)
#define TBCSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit06)
#define MKCSIH0IC          (((volatile __bitf_T *)0xFFFF902A)->bit07)
#define RFCSIH0IC          (((volatile __bitf_T *)0xFFFF902B)->bit04)
#define CTCSIH0IC          (((volatile __bitf_T *)0xFFFF902B)->bit07)
__IOREG(ICCSIH0IR, 0xFFFF902C, __READ_WRITE, uint16);
__IOREG(ICCSIH0IRL, 0xFFFF902C, __READ_WRITE, uint8);
__IOREG(ICCSIH0IRH, 0xFFFF902D, __READ_WRITE, uint8);
#define P0CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit00)
#define P1CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit01)
#define P2CSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit02)
#define TBCSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit06)
#define MKCSIH0IR          (((volatile __bitf_T *)0xFFFF902C)->bit07)
#define RFCSIH0IR          (((volatile __bitf_T *)0xFFFF902D)->bit04)
#define CTCSIH0IR          (((volatile __bitf_T *)0xFFFF902D)->bit07)
__IOREG(ICCSIH0IRE, 0xFFFF902E, __READ_WRITE, uint16);
__IOREG(ICCSIH0IREL, 0xFFFF902E, __READ_WRITE, uint8);
__IOREG(ICCSIH0IREH, 0xFFFF902F, __READ_WRITE, uint8);
#define P0CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit00)
#define P1CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit01)
#define P2CSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit02)
#define TBCSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit06)
#define MKCSIH0IRE         (((volatile __bitf_T *)0xFFFF902E)->bit07)
#define RFCSIH0IRE         (((volatile __bitf_T *)0xFFFF902F)->bit04)
#define CTCSIH0IRE         (((volatile __bitf_T *)0xFFFF902F)->bit07)
__IOREG(ICCSIH0IJC, 0xFFFF9030, __READ_WRITE, uint16);
__IOREG(ICCSIH0IJCL, 0xFFFF9030, __READ_WRITE, uint8);
__IOREG(ICCSIH0IJCH, 0xFFFF9031, __READ_WRITE, uint8);
#define P0CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit00)
#define P1CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit01)
#define P2CSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit02)
#define TBCSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit06)
#define MKCSIH0IJC         (((volatile __bitf_T *)0xFFFF9030)->bit07)
#define RFCSIH0IJC         (((volatile __bitf_T *)0xFFFF9031)->bit04)
#define CTCSIH0IJC         (((volatile __bitf_T *)0xFFFF9031)->bit07)
__IOREG(ICRLIN30, 0xFFFF9032, __READ_WRITE, uint16);
__IOREG(ICRLIN30L, 0xFFFF9032, __READ_WRITE, uint8);
__IOREG(ICRLIN30H, 0xFFFF9033, __READ_WRITE, uint8);
#define P0RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit00)
#define P1RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit01)
#define P2RLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit02)
#define TBRLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit06)
#define MKRLIN30           (((volatile __bitf_T *)0xFFFF9032)->bit07)
#define RFRLIN30           (((volatile __bitf_T *)0xFFFF9033)->bit04)
#define CTRLIN30           (((volatile __bitf_T *)0xFFFF9033)->bit07)
__IOREG(ICRLIN30UR0, 0xFFFF9034, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR0L, 0xFFFF9034, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR0H, 0xFFFF9035, __READ_WRITE, uint8);
#define P0RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit00)
#define P1RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit01)
#define P2RLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit02)
#define TBRLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit06)
#define MKRLIN30UR0        (((volatile __bitf_T *)0xFFFF9034)->bit07)
#define RFRLIN30UR0        (((volatile __bitf_T *)0xFFFF9035)->bit04)
#define CTRLIN30UR0        (((volatile __bitf_T *)0xFFFF9035)->bit07)
__IOREG(ICRLIN30UR1, 0xFFFF9036, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR1L, 0xFFFF9036, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR1H, 0xFFFF9037, __READ_WRITE, uint8);
#define P0RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit00)
#define P1RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit01)
#define P2RLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit02)
#define TBRLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit06)
#define MKRLIN30UR1        (((volatile __bitf_T *)0xFFFF9036)->bit07)
#define RFRLIN30UR1        (((volatile __bitf_T *)0xFFFF9037)->bit04)
#define CTRLIN30UR1        (((volatile __bitf_T *)0xFFFF9037)->bit07)
__IOREG(ICRLIN30UR2, 0xFFFF9038, __READ_WRITE, uint16);
__IOREG(ICRLIN30UR2L, 0xFFFF9038, __READ_WRITE, uint8);
__IOREG(ICRLIN30UR2H, 0xFFFF9039, __READ_WRITE, uint8);
#define P0RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit00)
#define P1RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit01)
#define P2RLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit02)
#define TBRLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit06)
#define MKRLIN30UR2        (((volatile __bitf_T *)0xFFFF9038)->bit07)
#define RFRLIN30UR2        (((volatile __bitf_T *)0xFFFF9039)->bit04)
#define CTRLIN30UR2        (((volatile __bitf_T *)0xFFFF9039)->bit07)
__IOREG(ICCSIH2IR_1, 0xFFFF903A, __READ_WRITE, uint16);
__IOREG(ICP0, 0xFFFF903A, __READ_WRITE, uint16);
__IOREG(ICCSIH2IRL_1, 0xFFFF903A, __READ_WRITE, uint8);
__IOREG(ICP0L, 0xFFFF903A, __READ_WRITE, uint8);
__IOREG(ICCSIH2IRH_1, 0xFFFF903B, __READ_WRITE, uint8);
__IOREG(ICP0H, 0xFFFF903B, __READ_WRITE, uint8);
#define P0CSIH2IR_1        (((volatile __bitf_T *)0xFFFF903A)->bit00)
#define P0P0               (((volatile __bitf_T *)0xFFFF903A)->bit00)
#define P1CSIH2IR_1        (((volatile __bitf_T *)0xFFFF903A)->bit01)
#define P1P0               (((volatile __bitf_T *)0xFFFF903A)->bit01)
#define P2CSIH2IR_1        (((volatile __bitf_T *)0xFFFF903A)->bit02)
#define P2P0               (((volatile __bitf_T *)0xFFFF903A)->bit02)
#define TBCSIH2IR_1        (((volatile __bitf_T *)0xFFFF903A)->bit06)
#define TBP0               (((volatile __bitf_T *)0xFFFF903A)->bit06)
#define MKCSIH2IR_1        (((volatile __bitf_T *)0xFFFF903A)->bit07)
#define MKP0               (((volatile __bitf_T *)0xFFFF903A)->bit07)
#define RFCSIH2IR_1        (((volatile __bitf_T *)0xFFFF903B)->bit04)
#define RFP0               (((volatile __bitf_T *)0xFFFF903B)->bit04)
#define CTCSIH2IR_1        (((volatile __bitf_T *)0xFFFF903B)->bit07)
#define CTP0               (((volatile __bitf_T *)0xFFFF903B)->bit07)
__IOREG(ICCSIH2IRE_1, 0xFFFF903C, __READ_WRITE, uint16);
__IOREG(ICP1, 0xFFFF903C, __READ_WRITE, uint16);
__IOREG(ICCSIH2IREL_1, 0xFFFF903C, __READ_WRITE, uint8);
__IOREG(ICP1L, 0xFFFF903C, __READ_WRITE, uint8);
__IOREG(ICCSIH2IREH_1, 0xFFFF903D, __READ_WRITE, uint8);
__IOREG(ICP1H, 0xFFFF903D, __READ_WRITE, uint8);
#define P0CSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903C)->bit00)
#define P0P1               (((volatile __bitf_T *)0xFFFF903C)->bit00)
#define P1CSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903C)->bit01)
#define P1P1               (((volatile __bitf_T *)0xFFFF903C)->bit01)
#define P2CSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903C)->bit02)
#define P2P1               (((volatile __bitf_T *)0xFFFF903C)->bit02)
#define TBCSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903C)->bit06)
#define TBP1               (((volatile __bitf_T *)0xFFFF903C)->bit06)
#define MKCSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903C)->bit07)
#define MKP1               (((volatile __bitf_T *)0xFFFF903C)->bit07)
#define RFCSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903D)->bit04)
#define RFP1               (((volatile __bitf_T *)0xFFFF903D)->bit04)
#define CTCSIH2IRE_1       (((volatile __bitf_T *)0xFFFF903D)->bit07)
#define CTP1               (((volatile __bitf_T *)0xFFFF903D)->bit07)
__IOREG(ICCSIH2IJC_1, 0xFFFF903E, __READ_WRITE, uint16);
__IOREG(ICP2, 0xFFFF903E, __READ_WRITE, uint16);
__IOREG(ICCSIH2IJCL_1, 0xFFFF903E, __READ_WRITE, uint8);
__IOREG(ICP2L, 0xFFFF903E, __READ_WRITE, uint8);
__IOREG(ICCSIH2IJCH_1, 0xFFFF903F, __READ_WRITE, uint8);
__IOREG(ICP2H, 0xFFFF903F, __READ_WRITE, uint8);
#define P0CSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903E)->bit00)
#define P0P2               (((volatile __bitf_T *)0xFFFF903E)->bit00)
#define P1CSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903E)->bit01)
#define P1P2               (((volatile __bitf_T *)0xFFFF903E)->bit01)
#define P2CSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903E)->bit02)
#define P2P2               (((volatile __bitf_T *)0xFFFF903E)->bit02)
#define TBCSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903E)->bit06)
#define TBP2               (((volatile __bitf_T *)0xFFFF903E)->bit06)
#define MKCSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903E)->bit07)
#define MKP2               (((volatile __bitf_T *)0xFFFF903E)->bit07)
#define RFCSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903F)->bit04)
#define RFP2               (((volatile __bitf_T *)0xFFFF903F)->bit04)
#define CTCSIH2IJC_1       (((volatile __bitf_T *)0xFFFF903F)->bit07)
#define CTP2               (((volatile __bitf_T *)0xFFFF903F)->bit07)
__IOREG(FNC, 0xFFFF9078, __READ, uint16);
__IOREG(FNCH, 0xFFFF9079, __READ, uint8);
#define FNRF               (((const volatile __bitf_T *)0xFFFF9079)->bit04)
__IOREG(FIC, 0xFFFF907A, __READ, uint16);
__IOREG(FICH, 0xFFFF907B, __READ, uint8);
#define FIRF               (((const volatile __bitf_T *)0xFFFF907B)->bit04)
__IOREG(IMR0, 0xFFFF90F0, __READ_WRITE, uint32);
__IOREG(IMR0L, 0xFFFF90F0, __READ_WRITE, uint16);
__IOREG(IMR0LL, 0xFFFF90F0, __READ_WRITE, uint8);
__IOREG(IMR0LH, 0xFFFF90F1, __READ_WRITE, uint8);
__IOREG(IMR0H, 0xFFFF90F2, __READ_WRITE, uint16);
__IOREG(IMR0HL, 0xFFFF90F2, __READ_WRITE, uint8);
__IOREG(IMR0HH, 0xFFFF90F3, __READ_WRITE, uint8);
#define IMR0EIMK0          (((volatile __bitf_T *)0xFFFF90F0)->bit00)
#define IMR0EIMK1          (((volatile __bitf_T *)0xFFFF90F0)->bit01)
#define IMR0EIMK2          (((volatile __bitf_T *)0xFFFF90F0)->bit02)
#define IMR0EIMK3          (((volatile __bitf_T *)0xFFFF90F0)->bit03)
#define IMR0EIMK4          (((volatile __bitf_T *)0xFFFF90F0)->bit04)
#define IMR0EIMK5          (((volatile __bitf_T *)0xFFFF90F0)->bit05)
#define IMR0EIMK6          (((volatile __bitf_T *)0xFFFF90F0)->bit06)
#define IMR0EIMK7          (((volatile __bitf_T *)0xFFFF90F0)->bit07)
#define IMR0EIMK8          (((volatile __bitf_T *)0xFFFF90F1)->bit00)
#define IMR0EIMK9          (((volatile __bitf_T *)0xFFFF90F1)->bit01)
#define IMR0EIMK10         (((volatile __bitf_T *)0xFFFF90F1)->bit02)
#define IMR0EIMK11         (((volatile __bitf_T *)0xFFFF90F1)->bit03)
#define IMR0EIMK12         (((volatile __bitf_T *)0xFFFF90F1)->bit04)
#define IMR0EIMK13         (((volatile __bitf_T *)0xFFFF90F1)->bit05)
#define IMR0EIMK14         (((volatile __bitf_T *)0xFFFF90F1)->bit06)
#define IMR0EIMK15         (((volatile __bitf_T *)0xFFFF90F1)->bit07)
#define IMR0EIMK16         (((volatile __bitf_T *)0xFFFF90F2)->bit00)
#define IMR0EIMK17         (((volatile __bitf_T *)0xFFFF90F2)->bit01)
#define IMR0EIMK18         (((volatile __bitf_T *)0xFFFF90F2)->bit02)
#define IMR0EIMK19         (((volatile __bitf_T *)0xFFFF90F2)->bit03)
#define IMR0EIMK20         (((volatile __bitf_T *)0xFFFF90F2)->bit04)
#define IMR0EIMK21         (((volatile __bitf_T *)0xFFFF90F2)->bit05)
#define IMR0EIMK22         (((volatile __bitf_T *)0xFFFF90F2)->bit06)
#define IMR0EIMK23         (((volatile __bitf_T *)0xFFFF90F2)->bit07)
#define IMR0EIMK24         (((volatile __bitf_T *)0xFFFF90F3)->bit00)
#define IMR0EIMK25         (((volatile __bitf_T *)0xFFFF90F3)->bit01)
#define IMR0EIMK26         (((volatile __bitf_T *)0xFFFF90F3)->bit02)
#define IMR0EIMK27         (((volatile __bitf_T *)0xFFFF90F3)->bit03)
#define IMR0EIMK28         (((volatile __bitf_T *)0xFFFF90F3)->bit04)
#define IMR0EIMK29         (((volatile __bitf_T *)0xFFFF90F3)->bit05)
#define IMR0EIMK30         (((volatile __bitf_T *)0xFFFF90F3)->bit06)
#define IMR0EIMK31         (((volatile __bitf_T *)0xFFFF90F3)->bit07)
__IOREG(ICWDTA0, 0xFFFFA040, __READ_WRITE, uint16);
__IOREG(ICWDTA0L, 0xFFFFA040, __READ_WRITE, uint8);
__IOREG(ICWDTA0H, 0xFFFFA041, __READ_WRITE, uint8);
#define P0WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit00)
#define P1WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit01)
#define P2WDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit02)
#define TBWDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit06)
#define MKWDTA0            (((volatile __bitf_T *)0xFFFFA040)->bit07)
#define RFWDTA0            (((volatile __bitf_T *)0xFFFFA041)->bit04)
#define CTWDTA0            (((volatile __bitf_T *)0xFFFFA041)->bit07)
__IOREG(ICWDTA1, 0xFFFFA042, __READ_WRITE, uint16);
__IOREG(ICWDTA1L, 0xFFFFA042, __READ_WRITE, uint8);
__IOREG(ICWDTA1H, 0xFFFFA043, __READ_WRITE, uint8);
#define P0WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit00)
#define P1WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit01)
#define P2WDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit02)
#define TBWDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit06)
#define MKWDTA1            (((volatile __bitf_T *)0xFFFFA042)->bit07)
#define RFWDTA1            (((volatile __bitf_T *)0xFFFFA043)->bit04)
#define CTWDTA1            (((volatile __bitf_T *)0xFFFFA043)->bit07)
__IOREG(ICP3, 0xFFFFA044, __READ_WRITE, uint16);
__IOREG(ICP3L, 0xFFFFA044, __READ_WRITE, uint8);
__IOREG(ICP3H, 0xFFFFA045, __READ_WRITE, uint8);
#define P0P3               (((volatile __bitf_T *)0xFFFFA044)->bit00)
#define P1P3               (((volatile __bitf_T *)0xFFFFA044)->bit01)
#define P2P3               (((volatile __bitf_T *)0xFFFFA044)->bit02)
#define TBP3               (((volatile __bitf_T *)0xFFFFA044)->bit06)
#define MKP3               (((volatile __bitf_T *)0xFFFFA044)->bit07)
#define RFP3               (((volatile __bitf_T *)0xFFFFA045)->bit04)
#define CTP3               (((volatile __bitf_T *)0xFFFFA045)->bit07)
__IOREG(ICP4, 0xFFFFA046, __READ_WRITE, uint16);
__IOREG(ICP4L, 0xFFFFA046, __READ_WRITE, uint8);
__IOREG(ICP4H, 0xFFFFA047, __READ_WRITE, uint8);
#define P0P4               (((volatile __bitf_T *)0xFFFFA046)->bit00)
#define P1P4               (((volatile __bitf_T *)0xFFFFA046)->bit01)
#define P2P4               (((volatile __bitf_T *)0xFFFFA046)->bit02)
#define TBP4               (((volatile __bitf_T *)0xFFFFA046)->bit06)
#define MKP4               (((volatile __bitf_T *)0xFFFFA046)->bit07)
#define RFP4               (((volatile __bitf_T *)0xFFFFA047)->bit04)
#define CTP4               (((volatile __bitf_T *)0xFFFFA047)->bit07)
__IOREG(ICP5, 0xFFFFA048, __READ_WRITE, uint16);
__IOREG(ICP5L, 0xFFFFA048, __READ_WRITE, uint8);
__IOREG(ICP5H, 0xFFFFA049, __READ_WRITE, uint8);
#define P0P5               (((volatile __bitf_T *)0xFFFFA048)->bit00)
#define P1P5               (((volatile __bitf_T *)0xFFFFA048)->bit01)
#define P2P5               (((volatile __bitf_T *)0xFFFFA048)->bit02)
#define TBP5               (((volatile __bitf_T *)0xFFFFA048)->bit06)
#define MKP5               (((volatile __bitf_T *)0xFFFFA048)->bit07)
#define RFP5               (((volatile __bitf_T *)0xFFFFA049)->bit04)
#define CTP5               (((volatile __bitf_T *)0xFFFFA049)->bit07)
__IOREG(ICP10, 0xFFFFA04A, __READ_WRITE, uint16);
__IOREG(ICP10L, 0xFFFFA04A, __READ_WRITE, uint8);
__IOREG(ICP10H, 0xFFFFA04B, __READ_WRITE, uint8);
#define P0P10              (((volatile __bitf_T *)0xFFFFA04A)->bit00)
#define P1P10              (((volatile __bitf_T *)0xFFFFA04A)->bit01)
#define P2P10              (((volatile __bitf_T *)0xFFFFA04A)->bit02)
#define TBP10              (((volatile __bitf_T *)0xFFFFA04A)->bit06)
#define MKP10              (((volatile __bitf_T *)0xFFFFA04A)->bit07)
#define RFP10              (((volatile __bitf_T *)0xFFFFA04B)->bit04)
#define CTP10              (((volatile __bitf_T *)0xFFFFA04B)->bit07)
__IOREG(ICP11, 0xFFFFA04C, __READ_WRITE, uint16);
__IOREG(ICP11L, 0xFFFFA04C, __READ_WRITE, uint8);
__IOREG(ICP11H, 0xFFFFA04D, __READ_WRITE, uint8);
#define P0P11              (((volatile __bitf_T *)0xFFFFA04C)->bit00)
#define P1P11              (((volatile __bitf_T *)0xFFFFA04C)->bit01)
#define P2P11              (((volatile __bitf_T *)0xFFFFA04C)->bit02)
#define TBP11              (((volatile __bitf_T *)0xFFFFA04C)->bit06)
#define MKP11              (((volatile __bitf_T *)0xFFFFA04C)->bit07)
#define RFP11              (((volatile __bitf_T *)0xFFFFA04D)->bit04)
#define CTP11              (((volatile __bitf_T *)0xFFFFA04D)->bit07)
__IOREG(ICTAUD0I1, 0xFFFFA04E, __READ_WRITE, uint16);
__IOREG(ICTAUD0I1L, 0xFFFFA04E, __READ_WRITE, uint8);
__IOREG(ICTAUD0I1H, 0xFFFFA04F, __READ_WRITE, uint8);
#define P0TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit00)
#define P1TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit01)
#define P2TAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit02)
#define TBTAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit06)
#define MKTAUD0I1          (((volatile __bitf_T *)0xFFFFA04E)->bit07)
#define RFTAUD0I1          (((volatile __bitf_T *)0xFFFFA04F)->bit04)
#define CTTAUD0I1          (((volatile __bitf_T *)0xFFFFA04F)->bit07)
__IOREG(ICTAUD0I3, 0xFFFFA050, __READ_WRITE, uint16);
__IOREG(ICTAUD0I3L, 0xFFFFA050, __READ_WRITE, uint8);
__IOREG(ICTAUD0I3H, 0xFFFFA051, __READ_WRITE, uint8);
#define P0TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit00)
#define P1TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit01)
#define P2TAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit02)
#define TBTAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit06)
#define MKTAUD0I3          (((volatile __bitf_T *)0xFFFFA050)->bit07)
#define RFTAUD0I3          (((volatile __bitf_T *)0xFFFFA051)->bit04)
#define CTTAUD0I3          (((volatile __bitf_T *)0xFFFFA051)->bit07)
__IOREG(ICTAUD0I5, 0xFFFFA052, __READ_WRITE, uint16);
__IOREG(ICTAUD0I5L, 0xFFFFA052, __READ_WRITE, uint8);
__IOREG(ICTAUD0I5H, 0xFFFFA053, __READ_WRITE, uint8);
#define P0TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit00)
#define P1TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit01)
#define P2TAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit02)
#define TBTAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit06)
#define MKTAUD0I5          (((volatile __bitf_T *)0xFFFFA052)->bit07)
#define RFTAUD0I5          (((volatile __bitf_T *)0xFFFFA053)->bit04)
#define CTTAUD0I5          (((volatile __bitf_T *)0xFFFFA053)->bit07)
__IOREG(ICTAUD0I7, 0xFFFFA054, __READ_WRITE, uint16);
__IOREG(ICTAUD0I7L, 0xFFFFA054, __READ_WRITE, uint8);
__IOREG(ICTAUD0I7H, 0xFFFFA055, __READ_WRITE, uint8);
#define P0TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit00)
#define P1TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit01)
#define P2TAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit02)
#define TBTAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit06)
#define MKTAUD0I7          (((volatile __bitf_T *)0xFFFFA054)->bit07)
#define RFTAUD0I7          (((volatile __bitf_T *)0xFFFFA055)->bit04)
#define CTTAUD0I7          (((volatile __bitf_T *)0xFFFFA055)->bit07)
__IOREG(ICTAUD0I9, 0xFFFFA056, __READ_WRITE, uint16);
__IOREG(ICTAUD0I9L, 0xFFFFA056, __READ_WRITE, uint8);
__IOREG(ICTAUD0I9H, 0xFFFFA057, __READ_WRITE, uint8);
#define P0TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit00)
#define P1TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit01)
#define P2TAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit02)
#define TBTAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit06)
#define MKTAUD0I9          (((volatile __bitf_T *)0xFFFFA056)->bit07)
#define RFTAUD0I9          (((volatile __bitf_T *)0xFFFFA057)->bit04)
#define CTTAUD0I9          (((volatile __bitf_T *)0xFFFFA057)->bit07)
__IOREG(ICTAUD0I11, 0xFFFFA058, __READ_WRITE, uint16);
__IOREG(ICTAUD0I11L, 0xFFFFA058, __READ_WRITE, uint8);
__IOREG(ICTAUD0I11H, 0xFFFFA059, __READ_WRITE, uint8);
#define P0TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit00)
#define P1TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit01)
#define P2TAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit02)
#define TBTAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit06)
#define MKTAUD0I11         (((volatile __bitf_T *)0xFFFFA058)->bit07)
#define RFTAUD0I11         (((volatile __bitf_T *)0xFFFFA059)->bit04)
#define CTTAUD0I11         (((volatile __bitf_T *)0xFFFFA059)->bit07)
__IOREG(ICTAUD0I13, 0xFFFFA05A, __READ_WRITE, uint16);
__IOREG(ICTAUD0I13L, 0xFFFFA05A, __READ_WRITE, uint8);
__IOREG(ICTAUD0I13H, 0xFFFFA05B, __READ_WRITE, uint8);
#define P0TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit00)
#define P1TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit01)
#define P2TAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit02)
#define TBTAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit06)
#define MKTAUD0I13         (((volatile __bitf_T *)0xFFFFA05A)->bit07)
#define RFTAUD0I13         (((volatile __bitf_T *)0xFFFFA05B)->bit04)
#define CTTAUD0I13         (((volatile __bitf_T *)0xFFFFA05B)->bit07)
__IOREG(ICTAUD0I15, 0xFFFFA05C, __READ_WRITE, uint16);
__IOREG(ICTAUD0I15L, 0xFFFFA05C, __READ_WRITE, uint8);
__IOREG(ICTAUD0I15H, 0xFFFFA05D, __READ_WRITE, uint8);
#define P0TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit00)
#define P1TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit01)
#define P2TAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit02)
#define TBTAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit06)
#define MKTAUD0I15         (((volatile __bitf_T *)0xFFFFA05C)->bit07)
#define RFTAUD0I15         (((volatile __bitf_T *)0xFFFFA05D)->bit04)
#define CTTAUD0I15         (((volatile __bitf_T *)0xFFFFA05D)->bit07)
__IOREG(ICADCA0ERR, 0xFFFFA05E, __READ_WRITE, uint16);
__IOREG(ICADCA0ERRL, 0xFFFFA05E, __READ_WRITE, uint8);
__IOREG(ICADCA0ERRH, 0xFFFFA05F, __READ_WRITE, uint8);
#define P0ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit00)
#define P1ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit01)
#define P2ADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit02)
#define TBADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit06)
#define MKADCA0ERR         (((volatile __bitf_T *)0xFFFFA05E)->bit07)
#define RFADCA0ERR         (((volatile __bitf_T *)0xFFFFA05F)->bit04)
#define CTADCA0ERR         (((volatile __bitf_T *)0xFFFFA05F)->bit07)
__IOREG(ICCSIG0IRE, 0xFFFFA062, __READ_WRITE, uint16);
__IOREG(ICCSIG0IREL, 0xFFFFA062, __READ_WRITE, uint8);
__IOREG(ICCSIG0IREH, 0xFFFFA063, __READ_WRITE, uint8);
#define P0CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit00)
#define P1CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit01)
#define P2CSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit02)
#define TBCSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit06)
#define MKCSIG0IRE         (((volatile __bitf_T *)0xFFFFA062)->bit07)
#define RFCSIG0IRE         (((volatile __bitf_T *)0xFFFFA063)->bit04)
#define CTCSIG0IRE         (((volatile __bitf_T *)0xFFFFA063)->bit07)
__IOREG(ICRLIN20, 0xFFFFA064, __READ_WRITE, uint16);
__IOREG(ICRLIN20L, 0xFFFFA064, __READ_WRITE, uint8);
__IOREG(ICRLIN20H, 0xFFFFA065, __READ_WRITE, uint8);
#define P0RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit00)
#define P1RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit01)
#define P2RLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit02)
#define TBRLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit06)
#define MKRLIN20           (((volatile __bitf_T *)0xFFFFA064)->bit07)
#define RFRLIN20           (((volatile __bitf_T *)0xFFFFA065)->bit04)
#define CTRLIN20           (((volatile __bitf_T *)0xFFFFA065)->bit07)
__IOREG(ICRLIN21, 0xFFFFA066, __READ_WRITE, uint16);
__IOREG(ICRLIN21L, 0xFFFFA066, __READ_WRITE, uint8);
__IOREG(ICRLIN21H, 0xFFFFA067, __READ_WRITE, uint8);
#define P0RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit00)
#define P1RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit01)
#define P2RLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit02)
#define TBRLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit06)
#define MKRLIN21           (((volatile __bitf_T *)0xFFFFA066)->bit07)
#define RFRLIN21           (((volatile __bitf_T *)0xFFFFA067)->bit04)
#define CTRLIN21           (((volatile __bitf_T *)0xFFFFA067)->bit07)
__IOREG(ICDMA0, 0xFFFFA068, __READ_WRITE, uint16);
__IOREG(ICDMA0L, 0xFFFFA068, __READ_WRITE, uint8);
__IOREG(ICDMA0H, 0xFFFFA069, __READ_WRITE, uint8);
#define P0DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit00)
#define P1DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit01)
#define P2DMA0             (((volatile __bitf_T *)0xFFFFA068)->bit02)
#define TBDMA0             (((volatile __bitf_T *)0xFFFFA068)->bit06)
#define MKDMA0             (((volatile __bitf_T *)0xFFFFA068)->bit07)
#define RFDMA0             (((volatile __bitf_T *)0xFFFFA069)->bit04)
#define CTDMA0             (((volatile __bitf_T *)0xFFFFA069)->bit07)
__IOREG(ICDMA1, 0xFFFFA06A, __READ_WRITE, uint16);
__IOREG(ICDMA1L, 0xFFFFA06A, __READ_WRITE, uint8);
__IOREG(ICDMA1H, 0xFFFFA06B, __READ_WRITE, uint8);
#define P0DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit00)
#define P1DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit01)
#define P2DMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit02)
#define TBDMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit06)
#define MKDMA1             (((volatile __bitf_T *)0xFFFFA06A)->bit07)
#define RFDMA1             (((volatile __bitf_T *)0xFFFFA06B)->bit04)
#define CTDMA1             (((volatile __bitf_T *)0xFFFFA06B)->bit07)
__IOREG(ICDMA2, 0xFFFFA06C, __READ_WRITE, uint16);
__IOREG(ICDMA2L, 0xFFFFA06C, __READ_WRITE, uint8);
__IOREG(ICDMA2H, 0xFFFFA06D, __READ_WRITE, uint8);
#define P0DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit00)
#define P1DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit01)
#define P2DMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit02)
#define TBDMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit06)
#define MKDMA2             (((volatile __bitf_T *)0xFFFFA06C)->bit07)
#define RFDMA2             (((volatile __bitf_T *)0xFFFFA06D)->bit04)
#define CTDMA2             (((volatile __bitf_T *)0xFFFFA06D)->bit07)
__IOREG(ICDMA3, 0xFFFFA06E, __READ_WRITE, uint16);
__IOREG(ICDMA3L, 0xFFFFA06E, __READ_WRITE, uint8);
__IOREG(ICDMA3H, 0xFFFFA06F, __READ_WRITE, uint8);
#define P0DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit00)
#define P1DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit01)
#define P2DMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit02)
#define TBDMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit06)
#define MKDMA3             (((volatile __bitf_T *)0xFFFFA06E)->bit07)
#define RFDMA3             (((volatile __bitf_T *)0xFFFFA06F)->bit04)
#define CTDMA3             (((volatile __bitf_T *)0xFFFFA06F)->bit07)
__IOREG(ICDMA4, 0xFFFFA070, __READ_WRITE, uint16);
__IOREG(ICDMA4L, 0xFFFFA070, __READ_WRITE, uint8);
__IOREG(ICDMA4H, 0xFFFFA071, __READ_WRITE, uint8);
#define P0DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit00)
#define P1DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit01)
#define P2DMA4             (((volatile __bitf_T *)0xFFFFA070)->bit02)
#define TBDMA4             (((volatile __bitf_T *)0xFFFFA070)->bit06)
#define MKDMA4             (((volatile __bitf_T *)0xFFFFA070)->bit07)
#define RFDMA4             (((volatile __bitf_T *)0xFFFFA071)->bit04)
#define CTDMA4             (((volatile __bitf_T *)0xFFFFA071)->bit07)
__IOREG(ICDMA5, 0xFFFFA072, __READ_WRITE, uint16);
__IOREG(ICDMA5L, 0xFFFFA072, __READ_WRITE, uint8);
__IOREG(ICDMA5H, 0xFFFFA073, __READ_WRITE, uint8);
#define P0DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit00)
#define P1DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit01)
#define P2DMA5             (((volatile __bitf_T *)0xFFFFA072)->bit02)
#define TBDMA5             (((volatile __bitf_T *)0xFFFFA072)->bit06)
#define MKDMA5             (((volatile __bitf_T *)0xFFFFA072)->bit07)
#define RFDMA5             (((volatile __bitf_T *)0xFFFFA073)->bit04)
#define CTDMA5             (((volatile __bitf_T *)0xFFFFA073)->bit07)
__IOREG(ICDMA6, 0xFFFFA074, __READ_WRITE, uint16);
__IOREG(ICDMA6L, 0xFFFFA074, __READ_WRITE, uint8);
__IOREG(ICDMA6H, 0xFFFFA075, __READ_WRITE, uint8);
#define P0DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit00)
#define P1DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit01)
#define P2DMA6             (((volatile __bitf_T *)0xFFFFA074)->bit02)
#define TBDMA6             (((volatile __bitf_T *)0xFFFFA074)->bit06)
#define MKDMA6             (((volatile __bitf_T *)0xFFFFA074)->bit07)
#define RFDMA6             (((volatile __bitf_T *)0xFFFFA075)->bit04)
#define CTDMA6             (((volatile __bitf_T *)0xFFFFA075)->bit07)
__IOREG(ICDMA7, 0xFFFFA076, __READ_WRITE, uint16);
__IOREG(ICDMA7L, 0xFFFFA076, __READ_WRITE, uint8);
__IOREG(ICDMA7H, 0xFFFFA077, __READ_WRITE, uint8);
#define P0DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit00)
#define P1DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit01)
#define P2DMA7             (((volatile __bitf_T *)0xFFFFA076)->bit02)
#define TBDMA7             (((volatile __bitf_T *)0xFFFFA076)->bit06)
#define MKDMA7             (((volatile __bitf_T *)0xFFFFA076)->bit07)
#define RFDMA7             (((volatile __bitf_T *)0xFFFFA077)->bit04)
#define CTDMA7             (((volatile __bitf_T *)0xFFFFA077)->bit07)
__IOREG(ICDMA8, 0xFFFFA078, __READ_WRITE, uint16);
__IOREG(ICDMA8L, 0xFFFFA078, __READ_WRITE, uint8);
__IOREG(ICDMA8H, 0xFFFFA079, __READ_WRITE, uint8);
#define P0DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit00)
#define P1DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit01)
#define P2DMA8             (((volatile __bitf_T *)0xFFFFA078)->bit02)
#define TBDMA8             (((volatile __bitf_T *)0xFFFFA078)->bit06)
#define MKDMA8             (((volatile __bitf_T *)0xFFFFA078)->bit07)
#define RFDMA8             (((volatile __bitf_T *)0xFFFFA079)->bit04)
#define CTDMA8             (((volatile __bitf_T *)0xFFFFA079)->bit07)
__IOREG(ICDMA9, 0xFFFFA07A, __READ_WRITE, uint16);
__IOREG(ICDMA9L, 0xFFFFA07A, __READ_WRITE, uint8);
__IOREG(ICDMA9H, 0xFFFFA07B, __READ_WRITE, uint8);
#define P0DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit00)
#define P1DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit01)
#define P2DMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit02)
#define TBDMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit06)
#define MKDMA9             (((volatile __bitf_T *)0xFFFFA07A)->bit07)
#define RFDMA9             (((volatile __bitf_T *)0xFFFFA07B)->bit04)
#define CTDMA9             (((volatile __bitf_T *)0xFFFFA07B)->bit07)
__IOREG(ICDMA10, 0xFFFFA07C, __READ_WRITE, uint16);
__IOREG(ICDMA10L, 0xFFFFA07C, __READ_WRITE, uint8);
__IOREG(ICDMA10H, 0xFFFFA07D, __READ_WRITE, uint8);
#define P0DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit00)
#define P1DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit01)
#define P2DMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit02)
#define TBDMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit06)
#define MKDMA10            (((volatile __bitf_T *)0xFFFFA07C)->bit07)
#define RFDMA10            (((volatile __bitf_T *)0xFFFFA07D)->bit04)
#define CTDMA10            (((volatile __bitf_T *)0xFFFFA07D)->bit07)
__IOREG(ICDMA11, 0xFFFFA07E, __READ_WRITE, uint16);
__IOREG(ICDMA11L, 0xFFFFA07E, __READ_WRITE, uint8);
__IOREG(ICDMA11H, 0xFFFFA07F, __READ_WRITE, uint8);
#define P0DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit00)
#define P1DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit01)
#define P2DMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit02)
#define TBDMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit06)
#define MKDMA11            (((volatile __bitf_T *)0xFFFFA07E)->bit07)
#define RFDMA11            (((volatile __bitf_T *)0xFFFFA07F)->bit04)
#define CTDMA11            (((volatile __bitf_T *)0xFFFFA07F)->bit07)
__IOREG(ICDMA12, 0xFFFFA080, __READ_WRITE, uint16);
__IOREG(ICDMA12L, 0xFFFFA080, __READ_WRITE, uint8);
__IOREG(ICDMA12H, 0xFFFFA081, __READ_WRITE, uint8);
#define P0DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit00)
#define P1DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit01)
#define P2DMA12            (((volatile __bitf_T *)0xFFFFA080)->bit02)
#define TBDMA12            (((volatile __bitf_T *)0xFFFFA080)->bit06)
#define MKDMA12            (((volatile __bitf_T *)0xFFFFA080)->bit07)
#define RFDMA12            (((volatile __bitf_T *)0xFFFFA081)->bit04)
#define CTDMA12            (((volatile __bitf_T *)0xFFFFA081)->bit07)
__IOREG(ICDMA13, 0xFFFFA082, __READ_WRITE, uint16);
__IOREG(ICDMA13L, 0xFFFFA082, __READ_WRITE, uint8);
__IOREG(ICDMA13H, 0xFFFFA083, __READ_WRITE, uint8);
#define P0DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit00)
#define P1DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit01)
#define P2DMA13            (((volatile __bitf_T *)0xFFFFA082)->bit02)
#define TBDMA13            (((volatile __bitf_T *)0xFFFFA082)->bit06)
#define MKDMA13            (((volatile __bitf_T *)0xFFFFA082)->bit07)
#define RFDMA13            (((volatile __bitf_T *)0xFFFFA083)->bit04)
#define CTDMA13            (((volatile __bitf_T *)0xFFFFA083)->bit07)
__IOREG(ICDMA14, 0xFFFFA084, __READ_WRITE, uint16);
__IOREG(ICDMA14L, 0xFFFFA084, __READ_WRITE, uint8);
__IOREG(ICDMA14H, 0xFFFFA085, __READ_WRITE, uint8);
#define P0DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit00)
#define P1DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit01)
#define P2DMA14            (((volatile __bitf_T *)0xFFFFA084)->bit02)
#define TBDMA14            (((volatile __bitf_T *)0xFFFFA084)->bit06)
#define MKDMA14            (((volatile __bitf_T *)0xFFFFA084)->bit07)
#define RFDMA14            (((volatile __bitf_T *)0xFFFFA085)->bit04)
#define CTDMA14            (((volatile __bitf_T *)0xFFFFA085)->bit07)
__IOREG(ICDMA15, 0xFFFFA086, __READ_WRITE, uint16);
__IOREG(ICDMA15L, 0xFFFFA086, __READ_WRITE, uint8);
__IOREG(ICDMA15H, 0xFFFFA087, __READ_WRITE, uint8);
#define P0DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit00)
#define P1DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit01)
#define P2DMA15            (((volatile __bitf_T *)0xFFFFA086)->bit02)
#define TBDMA15            (((volatile __bitf_T *)0xFFFFA086)->bit06)
#define MKDMA15            (((volatile __bitf_T *)0xFFFFA086)->bit07)
#define RFDMA15            (((volatile __bitf_T *)0xFFFFA087)->bit04)
#define CTDMA15            (((volatile __bitf_T *)0xFFFFA087)->bit07)
__IOREG(ICRIIC0TI, 0xFFFFA088, __READ_WRITE, uint16);
__IOREG(ICRIIC0TIL, 0xFFFFA088, __READ_WRITE, uint8);
__IOREG(ICRIIC0TIH, 0xFFFFA089, __READ_WRITE, uint8);
#define P0RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit00)
#define P1RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit01)
#define P2RIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit02)
#define TBRIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit06)
#define MKRIIC0TI          (((volatile __bitf_T *)0xFFFFA088)->bit07)
#define RFRIIC0TI          (((volatile __bitf_T *)0xFFFFA089)->bit04)
#define CTRIIC0TI          (((volatile __bitf_T *)0xFFFFA089)->bit07)
__IOREG(ICRIIC0TEI, 0xFFFFA08A, __READ_WRITE, uint16);
__IOREG(ICRIIC0TEIL, 0xFFFFA08A, __READ_WRITE, uint8);
__IOREG(ICRIIC0TEIH, 0xFFFFA08B, __READ_WRITE, uint8);
#define P0RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit00)
#define P1RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit01)
#define P2RIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit02)
#define TBRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit06)
#define MKRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08A)->bit07)
#define RFRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08B)->bit04)
#define CTRIIC0TEI         (((volatile __bitf_T *)0xFFFFA08B)->bit07)
__IOREG(ICRIIC0RI, 0xFFFFA08C, __READ_WRITE, uint16);
__IOREG(ICRIIC0RIL, 0xFFFFA08C, __READ_WRITE, uint8);
__IOREG(ICRIIC0RIH, 0xFFFFA08D, __READ_WRITE, uint8);
#define P0RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit00)
#define P1RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit01)
#define P2RIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit02)
#define TBRIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit06)
#define MKRIIC0RI          (((volatile __bitf_T *)0xFFFFA08C)->bit07)
#define RFRIIC0RI          (((volatile __bitf_T *)0xFFFFA08D)->bit04)
#define CTRIIC0RI          (((volatile __bitf_T *)0xFFFFA08D)->bit07)
__IOREG(ICRIIC0EE, 0xFFFFA08E, __READ_WRITE, uint16);
__IOREG(ICRIIC0EEL, 0xFFFFA08E, __READ_WRITE, uint8);
__IOREG(ICRIIC0EEH, 0xFFFFA08F, __READ_WRITE, uint8);
#define P0RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit00)
#define P1RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit01)
#define P2RIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit02)
#define TBRIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit06)
#define MKRIIC0EE          (((volatile __bitf_T *)0xFFFFA08E)->bit07)
#define RFRIIC0EE          (((volatile __bitf_T *)0xFFFFA08F)->bit04)
#define CTRIIC0EE          (((volatile __bitf_T *)0xFFFFA08F)->bit07)
__IOREG(ICTAUJ0I0, 0xFFFFA090, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I0L, 0xFFFFA090, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I0H, 0xFFFFA091, __READ_WRITE, uint8);
#define P0TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit00)
#define P1TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit01)
#define P2TAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit02)
#define TBTAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit06)
#define MKTAUJ0I0          (((volatile __bitf_T *)0xFFFFA090)->bit07)
#define RFTAUJ0I0          (((volatile __bitf_T *)0xFFFFA091)->bit04)
#define CTTAUJ0I0          (((volatile __bitf_T *)0xFFFFA091)->bit07)
__IOREG(ICTAUJ0I1, 0xFFFFA092, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I1L, 0xFFFFA092, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I1H, 0xFFFFA093, __READ_WRITE, uint8);
#define P0TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit00)
#define P1TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit01)
#define P2TAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit02)
#define TBTAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit06)
#define MKTAUJ0I1          (((volatile __bitf_T *)0xFFFFA092)->bit07)
#define RFTAUJ0I1          (((volatile __bitf_T *)0xFFFFA093)->bit04)
#define CTTAUJ0I1          (((volatile __bitf_T *)0xFFFFA093)->bit07)
__IOREG(ICTAUJ0I2, 0xFFFFA094, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I2L, 0xFFFFA094, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I2H, 0xFFFFA095, __READ_WRITE, uint8);
#define P0TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit00)
#define P1TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit01)
#define P2TAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit02)
#define TBTAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit06)
#define MKTAUJ0I2          (((volatile __bitf_T *)0xFFFFA094)->bit07)
#define RFTAUJ0I2          (((volatile __bitf_T *)0xFFFFA095)->bit04)
#define CTTAUJ0I2          (((volatile __bitf_T *)0xFFFFA095)->bit07)
__IOREG(ICTAUJ0I3, 0xFFFFA096, __READ_WRITE, uint16);
__IOREG(ICTAUJ0I3L, 0xFFFFA096, __READ_WRITE, uint8);
__IOREG(ICTAUJ0I3H, 0xFFFFA097, __READ_WRITE, uint8);
#define P0TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit00)
#define P1TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit01)
#define P2TAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit02)
#define TBTAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit06)
#define MKTAUJ0I3          (((volatile __bitf_T *)0xFFFFA096)->bit07)
#define RFTAUJ0I3          (((volatile __bitf_T *)0xFFFFA097)->bit04)
#define CTTAUJ0I3          (((volatile __bitf_T *)0xFFFFA097)->bit07)
__IOREG(ICOSTM0, 0xFFFFA098, __READ_WRITE, uint16);
__IOREG(ICOSTM0L, 0xFFFFA098, __READ_WRITE, uint8);
__IOREG(ICOSTM0H, 0xFFFFA099, __READ_WRITE, uint8);
#define P0OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit00)
#define P1OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit01)
#define P2OSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit02)
#define TBOSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit06)
#define MKOSTM0            (((volatile __bitf_T *)0xFFFFA098)->bit07)
#define RFOSTM0            (((volatile __bitf_T *)0xFFFFA099)->bit04)
#define CTOSTM0            (((volatile __bitf_T *)0xFFFFA099)->bit07)
__IOREG(ICENCA0IOV, 0xFFFFA09A, __READ_WRITE, uint16);
__IOREG(ICPWGA4, 0xFFFFA09A, __READ_WRITE, uint16);
__IOREG(ICENCA0IOVL, 0xFFFFA09A, __READ_WRITE, uint8);
__IOREG(ICPWGA4L, 0xFFFFA09A, __READ_WRITE, uint8);
__IOREG(ICENCA0IOVH, 0xFFFFA09B, __READ_WRITE, uint8);
__IOREG(ICPWGA4H, 0xFFFFA09B, __READ_WRITE, uint8);
#define P0ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit00)
#define P0PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit00)
#define P1ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit01)
#define P1PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit01)
#define P2ENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit02)
#define P2PWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit02)
#define TBENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit06)
#define TBPWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit06)
#define MKENCA0IOV         (((volatile __bitf_T *)0xFFFFA09A)->bit07)
#define MKPWGA4            (((volatile __bitf_T *)0xFFFFA09A)->bit07)
#define RFENCA0IOV         (((volatile __bitf_T *)0xFFFFA09B)->bit04)
#define RFPWGA4            (((volatile __bitf_T *)0xFFFFA09B)->bit04)
#define CTENCA0IOV         (((volatile __bitf_T *)0xFFFFA09B)->bit07)
#define CTPWGA4            (((volatile __bitf_T *)0xFFFFA09B)->bit07)
__IOREG(ICENCA0IUD, 0xFFFFA09C, __READ_WRITE, uint16);
__IOREG(ICPWGA5, 0xFFFFA09C, __READ_WRITE, uint16);
__IOREG(ICENCA0IUDL, 0xFFFFA09C, __READ_WRITE, uint8);
__IOREG(ICPWGA5L, 0xFFFFA09C, __READ_WRITE, uint8);
__IOREG(ICENCA0IUDH, 0xFFFFA09D, __READ_WRITE, uint8);
__IOREG(ICPWGA5H, 0xFFFFA09D, __READ_WRITE, uint8);
#define P0ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit00)
#define P0PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit00)
#define P1ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit01)
#define P1PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit01)
#define P2ENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit02)
#define P2PWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit02)
#define TBENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit06)
#define TBPWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit06)
#define MKENCA0IUD         (((volatile __bitf_T *)0xFFFFA09C)->bit07)
#define MKPWGA5            (((volatile __bitf_T *)0xFFFFA09C)->bit07)
#define RFENCA0IUD         (((volatile __bitf_T *)0xFFFFA09D)->bit04)
#define RFPWGA5            (((volatile __bitf_T *)0xFFFFA09D)->bit04)
#define CTENCA0IUD         (((volatile __bitf_T *)0xFFFFA09D)->bit07)
#define CTPWGA5            (((volatile __bitf_T *)0xFFFFA09D)->bit07)
__IOREG(ICENCA0I0, 0xFFFFA09E, __READ_WRITE, uint16);
__IOREG(ICPWGA6, 0xFFFFA09E, __READ_WRITE, uint16);
__IOREG(ICENCA0I0L, 0xFFFFA09E, __READ_WRITE, uint8);
__IOREG(ICPWGA6L, 0xFFFFA09E, __READ_WRITE, uint8);
__IOREG(ICENCA0I0H, 0xFFFFA09F, __READ_WRITE, uint8);
__IOREG(ICPWGA6H, 0xFFFFA09F, __READ_WRITE, uint8);
#define P0ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit00)
#define P0PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit00)
#define P1ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit01)
#define P1PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit01)
#define P2ENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit02)
#define P2PWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit02)
#define TBENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit06)
#define TBPWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit06)
#define MKENCA0I0          (((volatile __bitf_T *)0xFFFFA09E)->bit07)
#define MKPWGA6            (((volatile __bitf_T *)0xFFFFA09E)->bit07)
#define RFENCA0I0          (((volatile __bitf_T *)0xFFFFA09F)->bit04)
#define RFPWGA6            (((volatile __bitf_T *)0xFFFFA09F)->bit04)
#define CTENCA0I0          (((volatile __bitf_T *)0xFFFFA09F)->bit07)
#define CTPWGA6            (((volatile __bitf_T *)0xFFFFA09F)->bit07)
__IOREG(ICENCA0I1, 0xFFFFA0A0, __READ_WRITE, uint16);
__IOREG(ICPWGA7, 0xFFFFA0A0, __READ_WRITE, uint16);
__IOREG(ICENCA0I1L, 0xFFFFA0A0, __READ_WRITE, uint8);
__IOREG(ICPWGA7L, 0xFFFFA0A0, __READ_WRITE, uint8);
__IOREG(ICENCA0I1H, 0xFFFFA0A1, __READ_WRITE, uint8);
__IOREG(ICPWGA7H, 0xFFFFA0A1, __READ_WRITE, uint8);
#define P0ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit00)
#define P0PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit00)
#define P1ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit01)
#define P1PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit01)
#define P2ENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit02)
#define P2PWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit02)
#define TBENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit06)
#define TBPWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit06)
#define MKENCA0I1          (((volatile __bitf_T *)0xFFFFA0A0)->bit07)
#define MKPWGA7            (((volatile __bitf_T *)0xFFFFA0A0)->bit07)
#define RFENCA0I1          (((volatile __bitf_T *)0xFFFFA0A1)->bit04)
#define RFPWGA7            (((volatile __bitf_T *)0xFFFFA0A1)->bit04)
#define CTENCA0I1          (((volatile __bitf_T *)0xFFFFA0A1)->bit07)
#define CTPWGA7            (((volatile __bitf_T *)0xFFFFA0A1)->bit07)
__IOREG(ICENCA0IEC, 0xFFFFA0A2, __READ_WRITE, uint16);
__IOREG(ICENCA0IECL, 0xFFFFA0A2, __READ_WRITE, uint8);
__IOREG(ICENCA0IECH, 0xFFFFA0A3, __READ_WRITE, uint8);
#define P0ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit00)
#define P1ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit01)
#define P2ENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit02)
#define TBENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit06)
#define MKENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A2)->bit07)
#define RFENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A3)->bit04)
#define CTENCA0IEC         (((volatile __bitf_T *)0xFFFFA0A3)->bit07)
__IOREG(ICKR0, 0xFFFFA0A4, __READ_WRITE, uint16);
__IOREG(ICKR0L, 0xFFFFA0A4, __READ_WRITE, uint8);
__IOREG(ICKR0H, 0xFFFFA0A5, __READ_WRITE, uint8);
#define P0KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit00)
#define P1KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit01)
#define P2KR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit02)
#define TBKR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit06)
#define MKKR0              (((volatile __bitf_T *)0xFFFFA0A4)->bit07)
#define RFKR0              (((volatile __bitf_T *)0xFFFFA0A5)->bit04)
#define CTKR0              (((volatile __bitf_T *)0xFFFFA0A5)->bit07)
__IOREG(ICQFULL, 0xFFFFA0A6, __READ_WRITE, uint16);
__IOREG(ICQFULLL, 0xFFFFA0A6, __READ_WRITE, uint8);
__IOREG(ICQFULLH, 0xFFFFA0A7, __READ_WRITE, uint8);
#define P0QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit00)
#define P1QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit01)
#define P2QFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit02)
#define TBQFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit06)
#define MKQFULL            (((volatile __bitf_T *)0xFFFFA0A6)->bit07)
#define RFQFULL            (((volatile __bitf_T *)0xFFFFA0A7)->bit04)
#define CTQFULL            (((volatile __bitf_T *)0xFFFFA0A7)->bit07)
__IOREG(ICPWGA0, 0xFFFFA0A8, __READ_WRITE, uint16);
__IOREG(ICPWGA0L, 0xFFFFA0A8, __READ_WRITE, uint8);
__IOREG(ICPWGA0H, 0xFFFFA0A9, __READ_WRITE, uint8);
#define P0PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit00)
#define P1PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit01)
#define P2PWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit02)
#define TBPWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit06)
#define MKPWGA0            (((volatile __bitf_T *)0xFFFFA0A8)->bit07)
#define RFPWGA0            (((volatile __bitf_T *)0xFFFFA0A9)->bit04)
#define CTPWGA0            (((volatile __bitf_T *)0xFFFFA0A9)->bit07)
__IOREG(ICPWGA1, 0xFFFFA0AA, __READ_WRITE, uint16);
__IOREG(ICPWGA1L, 0xFFFFA0AA, __READ_WRITE, uint8);
__IOREG(ICPWGA1H, 0xFFFFA0AB, __READ_WRITE, uint8);
#define P0PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit00)
#define P1PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit01)
#define P2PWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit02)
#define TBPWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit06)
#define MKPWGA1            (((volatile __bitf_T *)0xFFFFA0AA)->bit07)
#define RFPWGA1            (((volatile __bitf_T *)0xFFFFA0AB)->bit04)
#define CTPWGA1            (((volatile __bitf_T *)0xFFFFA0AB)->bit07)
__IOREG(ICPWGA2, 0xFFFFA0AC, __READ_WRITE, uint16);
__IOREG(ICPWGA2L, 0xFFFFA0AC, __READ_WRITE, uint8);
__IOREG(ICPWGA2H, 0xFFFFA0AD, __READ_WRITE, uint8);
#define P0PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit00)
#define P1PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit01)
#define P2PWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit02)
#define TBPWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit06)
#define MKPWGA2            (((volatile __bitf_T *)0xFFFFA0AC)->bit07)
#define RFPWGA2            (((volatile __bitf_T *)0xFFFFA0AD)->bit04)
#define CTPWGA2            (((volatile __bitf_T *)0xFFFFA0AD)->bit07)
__IOREG(ICPWGA3, 0xFFFFA0AE, __READ_WRITE, uint16);
__IOREG(ICPWGA3L, 0xFFFFA0AE, __READ_WRITE, uint8);
__IOREG(ICPWGA3H, 0xFFFFA0AF, __READ_WRITE, uint8);
#define P0PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit00)
#define P1PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit01)
#define P2PWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit02)
#define TBPWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit06)
#define MKPWGA3            (((volatile __bitf_T *)0xFFFFA0AE)->bit07)
#define RFPWGA3            (((volatile __bitf_T *)0xFFFFA0AF)->bit04)
#define CTPWGA3            (((volatile __bitf_T *)0xFFFFA0AF)->bit07)
__IOREG(ICPWGA8, 0xFFFFA0B0, __READ_WRITE, uint16);
__IOREG(ICPWGA8L, 0xFFFFA0B0, __READ_WRITE, uint8);
__IOREG(ICPWGA8H, 0xFFFFA0B1, __READ_WRITE, uint8);
#define P0PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit00)
#define P1PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit01)
#define P2PWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit02)
#define TBPWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit06)
#define MKPWGA8            (((volatile __bitf_T *)0xFFFFA0B0)->bit07)
#define RFPWGA8            (((volatile __bitf_T *)0xFFFFA0B1)->bit04)
#define CTPWGA8            (((volatile __bitf_T *)0xFFFFA0B1)->bit07)
__IOREG(ICPWGA9, 0xFFFFA0B2, __READ_WRITE, uint16);
__IOREG(ICPWGA9L, 0xFFFFA0B2, __READ_WRITE, uint8);
__IOREG(ICPWGA9H, 0xFFFFA0B3, __READ_WRITE, uint8);
#define P0PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit00)
#define P1PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit01)
#define P2PWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit02)
#define TBPWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit06)
#define MKPWGA9            (((volatile __bitf_T *)0xFFFFA0B2)->bit07)
#define RFPWGA9            (((volatile __bitf_T *)0xFFFFA0B3)->bit04)
#define CTPWGA9            (((volatile __bitf_T *)0xFFFFA0B3)->bit07)
__IOREG(ICPWGA10, 0xFFFFA0B4, __READ_WRITE, uint16);
__IOREG(ICPWGA10L, 0xFFFFA0B4, __READ_WRITE, uint8);
__IOREG(ICPWGA10H, 0xFFFFA0B5, __READ_WRITE, uint8);
#define P0PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit00)
#define P1PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit01)
#define P2PWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit02)
#define TBPWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit06)
#define MKPWGA10           (((volatile __bitf_T *)0xFFFFA0B4)->bit07)
#define RFPWGA10           (((volatile __bitf_T *)0xFFFFA0B5)->bit04)
#define CTPWGA10           (((volatile __bitf_T *)0xFFFFA0B5)->bit07)
__IOREG(ICPWGA11, 0xFFFFA0B6, __READ_WRITE, uint16);
__IOREG(ICPWGA11L, 0xFFFFA0B6, __READ_WRITE, uint8);
__IOREG(ICPWGA11H, 0xFFFFA0B7, __READ_WRITE, uint8);
#define P0PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit00)
#define P1PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit01)
#define P2PWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit02)
#define TBPWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit06)
#define MKPWGA11           (((volatile __bitf_T *)0xFFFFA0B6)->bit07)
#define RFPWGA11           (((volatile __bitf_T *)0xFFFFA0B7)->bit04)
#define CTPWGA11           (((volatile __bitf_T *)0xFFFFA0B7)->bit07)
__IOREG(ICPWGA12, 0xFFFFA0B8, __READ_WRITE, uint16);
__IOREG(ICPWGA12L, 0xFFFFA0B8, __READ_WRITE, uint8);
__IOREG(ICPWGA12H, 0xFFFFA0B9, __READ_WRITE, uint8);
#define P0PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit00)
#define P1PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit01)
#define P2PWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit02)
#define TBPWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit06)
#define MKPWGA12           (((volatile __bitf_T *)0xFFFFA0B8)->bit07)
#define RFPWGA12           (((volatile __bitf_T *)0xFFFFA0B9)->bit04)
#define CTPWGA12           (((volatile __bitf_T *)0xFFFFA0B9)->bit07)
__IOREG(ICPWGA13, 0xFFFFA0BA, __READ_WRITE, uint16);
__IOREG(ICPWGA13L, 0xFFFFA0BA, __READ_WRITE, uint8);
__IOREG(ICPWGA13H, 0xFFFFA0BB, __READ_WRITE, uint8);
#define P0PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit00)
#define P1PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit01)
#define P2PWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit02)
#define TBPWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit06)
#define MKPWGA13           (((volatile __bitf_T *)0xFFFFA0BA)->bit07)
#define RFPWGA13           (((volatile __bitf_T *)0xFFFFA0BB)->bit04)
#define CTPWGA13           (((volatile __bitf_T *)0xFFFFA0BB)->bit07)
__IOREG(ICPWGA14, 0xFFFFA0BC, __READ_WRITE, uint16);
__IOREG(ICPWGA14L, 0xFFFFA0BC, __READ_WRITE, uint8);
__IOREG(ICPWGA14H, 0xFFFFA0BD, __READ_WRITE, uint8);
#define P0PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit00)
#define P1PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit01)
#define P2PWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit02)
#define TBPWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit06)
#define MKPWGA14           (((volatile __bitf_T *)0xFFFFA0BC)->bit07)
#define RFPWGA14           (((volatile __bitf_T *)0xFFFFA0BD)->bit04)
#define CTPWGA14           (((volatile __bitf_T *)0xFFFFA0BD)->bit07)
__IOREG(ICPWGA15, 0xFFFFA0BE, __READ_WRITE, uint16);
__IOREG(ICPWGA15L, 0xFFFFA0BE, __READ_WRITE, uint8);
__IOREG(ICPWGA15H, 0xFFFFA0BF, __READ_WRITE, uint8);
#define P0PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit00)
#define P1PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit01)
#define P2PWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit02)
#define TBPWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit06)
#define MKPWGA15           (((volatile __bitf_T *)0xFFFFA0BE)->bit07)
#define RFPWGA15           (((volatile __bitf_T *)0xFFFFA0BF)->bit04)
#define CTPWGA15           (((volatile __bitf_T *)0xFFFFA0BF)->bit07)
__IOREG(ICFLERR, 0xFFFFA0CC, __READ_WRITE, uint16);
__IOREG(ICFLERRL, 0xFFFFA0CC, __READ_WRITE, uint8);
__IOREG(ICFLERRH, 0xFFFFA0CD, __READ_WRITE, uint8);
#define P0FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit00)
#define P1FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit01)
#define P2FLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit02)
#define TBFLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit06)
#define MKFLERR            (((volatile __bitf_T *)0xFFFFA0CC)->bit07)
#define RFFLERR            (((volatile __bitf_T *)0xFFFFA0CD)->bit04)
#define CTFLERR            (((volatile __bitf_T *)0xFFFFA0CD)->bit07)
__IOREG(ICFLENDNM, 0xFFFFA0CE, __READ_WRITE, uint16);
__IOREG(ICFLENDNML, 0xFFFFA0CE, __READ_WRITE, uint8);
__IOREG(ICFLENDNMH, 0xFFFFA0CF, __READ_WRITE, uint8);
#define P0FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit00)
#define P1FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit01)
#define P2FLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit02)
#define TBFLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit06)
#define MKFLENDNM          (((volatile __bitf_T *)0xFFFFA0CE)->bit07)
#define RFFLENDNM          (((volatile __bitf_T *)0xFFFFA0CF)->bit04)
#define CTFLENDNM          (((volatile __bitf_T *)0xFFFFA0CF)->bit07)
__IOREG(ICCWEND, 0xFFFFA0D0, __READ_WRITE, uint16);
__IOREG(ICCWENDL, 0xFFFFA0D0, __READ_WRITE, uint8);
__IOREG(ICCWENDH, 0xFFFFA0D1, __READ_WRITE, uint8);
#define P0CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit00)
#define P1CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit01)
#define P2CWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit02)
#define TBCWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit06)
#define MKCWEND            (((volatile __bitf_T *)0xFFFFA0D0)->bit07)
#define RFCWEND            (((volatile __bitf_T *)0xFFFFA0D1)->bit04)
#define CTCWEND            (((volatile __bitf_T *)0xFFFFA0D1)->bit07)
__IOREG(ICRCAN1ERR, 0xFFFFA0D2, __READ_WRITE, uint16);
__IOREG(ICRCAN1ERRL, 0xFFFFA0D2, __READ_WRITE, uint8);
__IOREG(ICRCAN1ERRH, 0xFFFFA0D3, __READ_WRITE, uint8);
#define P0RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit00)
#define P1RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit01)
#define P2RCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit02)
#define TBRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit06)
#define MKRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D2)->bit07)
#define RFRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D3)->bit04)
#define CTRCAN1ERR         (((volatile __bitf_T *)0xFFFFA0D3)->bit07)
__IOREG(ICRCAN1REC, 0xFFFFA0D4, __READ_WRITE, uint16);
__IOREG(ICRCAN1RECL, 0xFFFFA0D4, __READ_WRITE, uint8);
__IOREG(ICRCAN1RECH, 0xFFFFA0D5, __READ_WRITE, uint8);
#define P0RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit00)
#define P1RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit01)
#define P2RCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit02)
#define TBRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit06)
#define MKRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D4)->bit07)
#define RFRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D5)->bit04)
#define CTRCAN1REC         (((volatile __bitf_T *)0xFFFFA0D5)->bit07)
__IOREG(ICRCAN1TRX, 0xFFFFA0D6, __READ_WRITE, uint16);
__IOREG(ICRCAN1TRXL, 0xFFFFA0D6, __READ_WRITE, uint8);
__IOREG(ICRCAN1TRXH, 0xFFFFA0D7, __READ_WRITE, uint8);
#define P0RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit00)
#define P1RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit01)
#define P2RCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit02)
#define TBRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit06)
#define MKRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D6)->bit07)
#define RFRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D7)->bit04)
#define CTRCAN1TRX         (((volatile __bitf_T *)0xFFFFA0D7)->bit07)
__IOREG(ICCSIH1IC, 0xFFFFA0D8, __READ_WRITE, uint16);
__IOREG(ICTAPA0IPEK0_2, 0xFFFFA0D8, __READ_WRITE, uint16);
__IOREG(ICCSIH1ICL, 0xFFFFA0D8, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0L_2, 0xFFFFA0D8, __READ_WRITE, uint8);
__IOREG(ICCSIH1ICH, 0xFFFFA0D9, __READ_WRITE, uint8);
__IOREG(ICTAPA0IPEK0H_2, 0xFFFFA0D9, __READ_WRITE, uint8);
#define P0CSIH1IC          (((volatile __bitf_T *)0xFFFFA0D8)->bit00)
#define P0TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit00)
#define P1CSIH1IC          (((volatile __bitf_T *)0xFFFFA0D8)->bit01)
#define P1TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit01)
#define P2CSIH1IC          (((volatile __bitf_T *)0xFFFFA0D8)->bit02)
#define P2TAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit02)
#define TBCSIH1IC          (((volatile __bitf_T *)0xFFFFA0D8)->bit06)
#define TBTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit06)
#define MKCSIH1IC          (((volatile __bitf_T *)0xFFFFA0D8)->bit07)
#define MKTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D8)->bit07)
#define RFCSIH1IC          (((volatile __bitf_T *)0xFFFFA0D9)->bit04)
#define RFTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D9)->bit04)
#define CTCSIH1IC          (((volatile __bitf_T *)0xFFFFA0D9)->bit07)
#define CTTAPA0IPEK0_2     (((volatile __bitf_T *)0xFFFFA0D9)->bit07)
__IOREG(ICCSIH1IR, 0xFFFFA0DA, __READ_WRITE, uint16);
__IOREG(ICTAPA0IVLY0_2, 0xFFFFA0DA, __READ_WRITE, uint16);
__IOREG(ICCSIH1IRL, 0xFFFFA0DA, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0L_2, 0xFFFFA0DA, __READ_WRITE, uint8);
__IOREG(ICCSIH1IRH, 0xFFFFA0DB, __READ_WRITE, uint8);
__IOREG(ICTAPA0IVLY0H_2, 0xFFFFA0DB, __READ_WRITE, uint8);
#define P0CSIH1IR          (((volatile __bitf_T *)0xFFFFA0DA)->bit00)
#define P0TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit00)
#define P1CSIH1IR          (((volatile __bitf_T *)0xFFFFA0DA)->bit01)
#define P1TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit01)
#define P2CSIH1IR          (((volatile __bitf_T *)0xFFFFA0DA)->bit02)
#define P2TAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit02)
#define TBCSIH1IR          (((volatile __bitf_T *)0xFFFFA0DA)->bit06)
#define TBTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit06)
#define MKCSIH1IR          (((volatile __bitf_T *)0xFFFFA0DA)->bit07)
#define MKTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DA)->bit07)
#define RFCSIH1IR          (((volatile __bitf_T *)0xFFFFA0DB)->bit04)
#define RFTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DB)->bit04)
#define CTCSIH1IR          (((volatile __bitf_T *)0xFFFFA0DB)->bit07)
#define CTTAPA0IVLY0_2     (((volatile __bitf_T *)0xFFFFA0DB)->bit07)
__IOREG(ICCSIG0IC_2, 0xFFFFA0DC, __READ_WRITE, uint16);
__IOREG(ICCSIH1IRE, 0xFFFFA0DC, __READ_WRITE, uint16);
__IOREG(ICCSIG0ICL_2, 0xFFFFA0DC, __READ_WRITE, uint8);
__IOREG(ICCSIH1IREL, 0xFFFFA0DC, __READ_WRITE, uint8);
__IOREG(ICCSIG0ICH_2, 0xFFFFA0DD, __READ_WRITE, uint8);
__IOREG(ICCSIH1IREH, 0xFFFFA0DD, __READ_WRITE, uint8);
#define P0CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit00)
#define P0CSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DC)->bit00)
#define P1CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit01)
#define P1CSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DC)->bit01)
#define P2CSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit02)
#define P2CSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DC)->bit02)
#define TBCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit06)
#define TBCSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DC)->bit06)
#define MKCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DC)->bit07)
#define MKCSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DC)->bit07)
#define RFCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DD)->bit04)
#define RFCSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DD)->bit04)
#define CTCSIG0IC_2        (((volatile __bitf_T *)0xFFFFA0DD)->bit07)
#define CTCSIH1IRE         (((volatile __bitf_T *)0xFFFFA0DD)->bit07)
__IOREG(ICCSIG0IR_2, 0xFFFFA0DE, __READ_WRITE, uint16);
__IOREG(ICCSIH1IJC, 0xFFFFA0DE, __READ_WRITE, uint16);
__IOREG(ICCSIG0IRL_2, 0xFFFFA0DE, __READ_WRITE, uint8);
__IOREG(ICCSIH1IJCL, 0xFFFFA0DE, __READ_WRITE, uint8);
__IOREG(ICCSIG0IRH_2, 0xFFFFA0DF, __READ_WRITE, uint8);
__IOREG(ICCSIH1IJCH, 0xFFFFA0DF, __READ_WRITE, uint8);
#define P0CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit00)
#define P0CSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DE)->bit00)
#define P1CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit01)
#define P1CSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DE)->bit01)
#define P2CSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit02)
#define P2CSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DE)->bit02)
#define TBCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit06)
#define TBCSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DE)->bit06)
#define MKCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DE)->bit07)
#define MKCSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DE)->bit07)
#define RFCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DF)->bit04)
#define RFCSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DF)->bit04)
#define CTCSIG0IR_2        (((volatile __bitf_T *)0xFFFFA0DF)->bit07)
#define CTCSIH1IJC         (((volatile __bitf_T *)0xFFFFA0DF)->bit07)
__IOREG(ICRLIN31, 0xFFFFA0E0, __READ_WRITE, uint16);
__IOREG(ICRLIN31L, 0xFFFFA0E0, __READ_WRITE, uint8);
__IOREG(ICRLIN31H, 0xFFFFA0E1, __READ_WRITE, uint8);
#define P0RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit00)
#define P1RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit01)
#define P2RLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit02)
#define TBRLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit06)
#define MKRLIN31           (((volatile __bitf_T *)0xFFFFA0E0)->bit07)
#define RFRLIN31           (((volatile __bitf_T *)0xFFFFA0E1)->bit04)
#define CTRLIN31           (((volatile __bitf_T *)0xFFFFA0E1)->bit07)
__IOREG(ICRLIN31UR0, 0xFFFFA0E2, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR0L, 0xFFFFA0E2, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR0H, 0xFFFFA0E3, __READ_WRITE, uint8);
#define P0RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit00)
#define P1RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit01)
#define P2RLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit02)
#define TBRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit06)
#define MKRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E2)->bit07)
#define RFRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E3)->bit04)
#define CTRLIN31UR0        (((volatile __bitf_T *)0xFFFFA0E3)->bit07)
__IOREG(ICRLIN31UR1, 0xFFFFA0E4, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR1L, 0xFFFFA0E4, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR1H, 0xFFFFA0E5, __READ_WRITE, uint8);
#define P0RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit00)
#define P1RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit01)
#define P2RLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit02)
#define TBRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit06)
#define MKRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E4)->bit07)
#define RFRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E5)->bit04)
#define CTRLIN31UR1        (((volatile __bitf_T *)0xFFFFA0E5)->bit07)
__IOREG(ICRLIN31UR2, 0xFFFFA0E6, __READ_WRITE, uint16);
__IOREG(ICRLIN31UR2L, 0xFFFFA0E6, __READ_WRITE, uint8);
__IOREG(ICRLIN31UR2H, 0xFFFFA0E7, __READ_WRITE, uint8);
#define P0RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit00)
#define P1RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit01)
#define P2RLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit02)
#define TBRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit06)
#define MKRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E6)->bit07)
#define RFRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E7)->bit04)
#define CTRLIN31UR2        (((volatile __bitf_T *)0xFFFFA0E7)->bit07)
__IOREG(ICPWGA20, 0xFFFFA0E8, __READ_WRITE, uint16);
__IOREG(ICPWGA20L, 0xFFFFA0E8, __READ_WRITE, uint8);
__IOREG(ICPWGA20H, 0xFFFFA0E9, __READ_WRITE, uint8);
#define P0PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit00)
#define P1PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit01)
#define P2PWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit02)
#define TBPWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit06)
#define MKPWGA20           (((volatile __bitf_T *)0xFFFFA0E8)->bit07)
#define RFPWGA20           (((volatile __bitf_T *)0xFFFFA0E9)->bit04)
#define CTPWGA20           (((volatile __bitf_T *)0xFFFFA0E9)->bit07)
__IOREG(ICPWGA21, 0xFFFFA0EA, __READ_WRITE, uint16);
__IOREG(ICPWGA21L, 0xFFFFA0EA, __READ_WRITE, uint8);
__IOREG(ICPWGA21H, 0xFFFFA0EB, __READ_WRITE, uint8);
#define P0PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit00)
#define P1PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit01)
#define P2PWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit02)
#define TBPWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit06)
#define MKPWGA21           (((volatile __bitf_T *)0xFFFFA0EA)->bit07)
#define RFPWGA21           (((volatile __bitf_T *)0xFFFFA0EB)->bit04)
#define CTPWGA21           (((volatile __bitf_T *)0xFFFFA0EB)->bit07)
__IOREG(ICPWGA22, 0xFFFFA0EC, __READ_WRITE, uint16);
__IOREG(ICPWGA22L, 0xFFFFA0EC, __READ_WRITE, uint8);
__IOREG(ICPWGA22H, 0xFFFFA0ED, __READ_WRITE, uint8);
#define P0PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit00)
#define P1PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit01)
#define P2PWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit02)
#define TBPWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit06)
#define MKPWGA22           (((volatile __bitf_T *)0xFFFFA0EC)->bit07)
#define RFPWGA22           (((volatile __bitf_T *)0xFFFFA0ED)->bit04)
#define CTPWGA22           (((volatile __bitf_T *)0xFFFFA0ED)->bit07)
__IOREG(ICPWGA23, 0xFFFFA0EE, __READ_WRITE, uint16);
__IOREG(ICPWGA23L, 0xFFFFA0EE, __READ_WRITE, uint8);
__IOREG(ICPWGA23H, 0xFFFFA0EF, __READ_WRITE, uint8);
#define P0PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit00)
#define P1PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit01)
#define P2PWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit02)
#define TBPWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit06)
#define MKPWGA23           (((volatile __bitf_T *)0xFFFFA0EE)->bit07)
#define RFPWGA23           (((volatile __bitf_T *)0xFFFFA0EF)->bit04)
#define CTPWGA23           (((volatile __bitf_T *)0xFFFFA0EF)->bit07)
__IOREG(ICP6, 0xFFFFA0F0, __READ_WRITE, uint16);
__IOREG(ICP6L, 0xFFFFA0F0, __READ_WRITE, uint8);
__IOREG(ICP6H, 0xFFFFA0F1, __READ_WRITE, uint8);
#define P0P6               (((volatile __bitf_T *)0xFFFFA0F0)->bit00)
#define P1P6               (((volatile __bitf_T *)0xFFFFA0F0)->bit01)
#define P2P6               (((volatile __bitf_T *)0xFFFFA0F0)->bit02)
#define TBP6               (((volatile __bitf_T *)0xFFFFA0F0)->bit06)
#define MKP6               (((volatile __bitf_T *)0xFFFFA0F0)->bit07)
#define RFP6               (((volatile __bitf_T *)0xFFFFA0F1)->bit04)
#define CTP6               (((volatile __bitf_T *)0xFFFFA0F1)->bit07)
__IOREG(ICP7, 0xFFFFA0F2, __READ_WRITE, uint16);
__IOREG(ICP7L, 0xFFFFA0F2, __READ_WRITE, uint8);
__IOREG(ICP7H, 0xFFFFA0F3, __READ_WRITE, uint8);
#define P0P7               (((volatile __bitf_T *)0xFFFFA0F2)->bit00)
#define P1P7               (((volatile __bitf_T *)0xFFFFA0F2)->bit01)
#define P2P7               (((volatile __bitf_T *)0xFFFFA0F2)->bit02)
#define TBP7               (((volatile __bitf_T *)0xFFFFA0F2)->bit06)
#define MKP7               (((volatile __bitf_T *)0xFFFFA0F2)->bit07)
#define RFP7               (((volatile __bitf_T *)0xFFFFA0F3)->bit04)
#define CTP7               (((volatile __bitf_T *)0xFFFFA0F3)->bit07)
__IOREG(ICP8, 0xFFFFA0F4, __READ_WRITE, uint16);
__IOREG(ICP8L, 0xFFFFA0F4, __READ_WRITE, uint8);
__IOREG(ICP8H, 0xFFFFA0F5, __READ_WRITE, uint8);
#define P0P8               (((volatile __bitf_T *)0xFFFFA0F4)->bit00)
#define P1P8               (((volatile __bitf_T *)0xFFFFA0F4)->bit01)
#define P2P8               (((volatile __bitf_T *)0xFFFFA0F4)->bit02)
#define TBP8               (((volatile __bitf_T *)0xFFFFA0F4)->bit06)
#define MKP8               (((volatile __bitf_T *)0xFFFFA0F4)->bit07)
#define RFP8               (((volatile __bitf_T *)0xFFFFA0F5)->bit04)
#define CTP8               (((volatile __bitf_T *)0xFFFFA0F5)->bit07)
__IOREG(ICP12, 0xFFFFA0F6, __READ_WRITE, uint16);
__IOREG(ICP12L, 0xFFFFA0F6, __READ_WRITE, uint8);
__IOREG(ICP12H, 0xFFFFA0F7, __READ_WRITE, uint8);
#define P0P12              (((volatile __bitf_T *)0xFFFFA0F6)->bit00)
#define P1P12              (((volatile __bitf_T *)0xFFFFA0F6)->bit01)
#define P2P12              (((volatile __bitf_T *)0xFFFFA0F6)->bit02)
#define TBP12              (((volatile __bitf_T *)0xFFFFA0F6)->bit06)
#define MKP12              (((volatile __bitf_T *)0xFFFFA0F6)->bit07)
#define RFP12              (((volatile __bitf_T *)0xFFFFA0F7)->bit04)
#define CTP12              (((volatile __bitf_T *)0xFFFFA0F7)->bit07)
__IOREG(ICCSIH2IC, 0xFFFFA0F8, __READ_WRITE, uint16);
__IOREG(ICTAUD0I0_2, 0xFFFFA0F8, __READ_WRITE, uint16);
__IOREG(ICCSIH2ICL, 0xFFFFA0F8, __READ_WRITE, uint8);
__IOREG(ICTAUD0I0L_2, 0xFFFFA0F8, __READ_WRITE, uint8);
__IOREG(ICCSIH2ICH, 0xFFFFA0F9, __READ_WRITE, uint8);
__IOREG(ICTAUD0I0H_2, 0xFFFFA0F9, __READ_WRITE, uint8);
#define P0CSIH2IC          (((volatile __bitf_T *)0xFFFFA0F8)->bit00)
#define P0TAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F8)->bit00)
#define P1CSIH2IC          (((volatile __bitf_T *)0xFFFFA0F8)->bit01)
#define P1TAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F8)->bit01)
#define P2CSIH2IC          (((volatile __bitf_T *)0xFFFFA0F8)->bit02)
#define P2TAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F8)->bit02)
#define TBCSIH2IC          (((volatile __bitf_T *)0xFFFFA0F8)->bit06)
#define TBTAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F8)->bit06)
#define MKCSIH2IC          (((volatile __bitf_T *)0xFFFFA0F8)->bit07)
#define MKTAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F8)->bit07)
#define RFCSIH2IC          (((volatile __bitf_T *)0xFFFFA0F9)->bit04)
#define RFTAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F9)->bit04)
#define CTCSIH2IC          (((volatile __bitf_T *)0xFFFFA0F9)->bit07)
#define CTTAUD0I0_2        (((volatile __bitf_T *)0xFFFFA0F9)->bit07)
__IOREG(ICCSIH2IR, 0xFFFFA0FA, __READ_WRITE, uint16);
__IOREG(ICP0_2, 0xFFFFA0FA, __READ_WRITE, uint16);
__IOREG(ICCSIH2IRL, 0xFFFFA0FA, __READ_WRITE, uint8);
__IOREG(ICP0L_2, 0xFFFFA0FA, __READ_WRITE, uint8);
__IOREG(ICCSIH2IRH, 0xFFFFA0FB, __READ_WRITE, uint8);
__IOREG(ICP0H_2, 0xFFFFA0FB, __READ_WRITE, uint8);
#define P0CSIH2IR          (((volatile __bitf_T *)0xFFFFA0FA)->bit00)
#define P0P0_2             (((volatile __bitf_T *)0xFFFFA0FA)->bit00)
#define P1CSIH2IR          (((volatile __bitf_T *)0xFFFFA0FA)->bit01)
#define P1P0_2             (((volatile __bitf_T *)0xFFFFA0FA)->bit01)
#define P2CSIH2IR          (((volatile __bitf_T *)0xFFFFA0FA)->bit02)
#define P2P0_2             (((volatile __bitf_T *)0xFFFFA0FA)->bit02)
#define TBCSIH2IR          (((volatile __bitf_T *)0xFFFFA0FA)->bit06)
#define TBP0_2             (((volatile __bitf_T *)0xFFFFA0FA)->bit06)
#define MKCSIH2IR          (((volatile __bitf_T *)0xFFFFA0FA)->bit07)
#define MKP0_2             (((volatile __bitf_T *)0xFFFFA0FA)->bit07)
#define RFCSIH2IR          (((volatile __bitf_T *)0xFFFFA0FB)->bit04)
#define RFP0_2             (((volatile __bitf_T *)0xFFFFA0FB)->bit04)
#define CTCSIH2IR          (((volatile __bitf_T *)0xFFFFA0FB)->bit07)
#define CTP0_2             (((volatile __bitf_T *)0xFFFFA0FB)->bit07)
__IOREG(ICCSIH2IRE, 0xFFFFA0FC, __READ_WRITE, uint16);
__IOREG(ICP1_2, 0xFFFFA0FC, __READ_WRITE, uint16);
__IOREG(ICCSIH2IREL, 0xFFFFA0FC, __READ_WRITE, uint8);
__IOREG(ICP1L_2, 0xFFFFA0FC, __READ_WRITE, uint8);
__IOREG(ICCSIH2IREH, 0xFFFFA0FD, __READ_WRITE, uint8);
__IOREG(ICP1H_2, 0xFFFFA0FD, __READ_WRITE, uint8);
#define P0CSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FC)->bit00)
#define P0P1_2             (((volatile __bitf_T *)0xFFFFA0FC)->bit00)
#define P1CSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FC)->bit01)
#define P1P1_2             (((volatile __bitf_T *)0xFFFFA0FC)->bit01)
#define P2CSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FC)->bit02)
#define P2P1_2             (((volatile __bitf_T *)0xFFFFA0FC)->bit02)
#define TBCSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FC)->bit06)
#define TBP1_2             (((volatile __bitf_T *)0xFFFFA0FC)->bit06)
#define MKCSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FC)->bit07)
#define MKP1_2             (((volatile __bitf_T *)0xFFFFA0FC)->bit07)
#define RFCSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FD)->bit04)
#define RFP1_2             (((volatile __bitf_T *)0xFFFFA0FD)->bit04)
#define CTCSIH2IRE         (((volatile __bitf_T *)0xFFFFA0FD)->bit07)
#define CTP1_2             (((volatile __bitf_T *)0xFFFFA0FD)->bit07)
__IOREG(ICCSIH2IJC, 0xFFFFA0FE, __READ_WRITE, uint16);
__IOREG(ICP2_2, 0xFFFFA0FE, __READ_WRITE, uint16);
__IOREG(ICCSIH2IJCL, 0xFFFFA0FE, __READ_WRITE, uint8);
__IOREG(ICP2L_2, 0xFFFFA0FE, __READ_WRITE, uint8);
__IOREG(ICCSIH2IJCH, 0xFFFFA0FF, __READ_WRITE, uint8);
__IOREG(ICP2H_2, 0xFFFFA0FF, __READ_WRITE, uint8);
#define P0CSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FE)->bit00)
#define P0P2_2             (((volatile __bitf_T *)0xFFFFA0FE)->bit00)
#define P1CSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FE)->bit01)
#define P1P2_2             (((volatile __bitf_T *)0xFFFFA0FE)->bit01)
#define P2CSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FE)->bit02)
#define P2P2_2             (((volatile __bitf_T *)0xFFFFA0FE)->bit02)
#define TBCSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FE)->bit06)
#define TBP2_2             (((volatile __bitf_T *)0xFFFFA0FE)->bit06)
#define MKCSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FE)->bit07)
#define MKP2_2             (((volatile __bitf_T *)0xFFFFA0FE)->bit07)
#define RFCSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FF)->bit04)
#define RFP2_2             (((volatile __bitf_T *)0xFFFFA0FF)->bit04)
#define CTCSIH2IJC         (((volatile __bitf_T *)0xFFFFA0FF)->bit07)
#define CTP2_2             (((volatile __bitf_T *)0xFFFFA0FF)->bit07)
__IOREG(ICTAUB0I0, 0xFFFFA10C, __READ_WRITE, uint16);
__IOREG(ICTAUB0I0L, 0xFFFFA10C, __READ_WRITE, uint8);
__IOREG(ICTAUB0I0H, 0xFFFFA10D, __READ_WRITE, uint8);
#define P0TAUB0I0          (((volatile __bitf_T *)0xFFFFA10C)->bit00)
#define P1TAUB0I0          (((volatile __bitf_T *)0xFFFFA10C)->bit01)
#define P2TAUB0I0          (((volatile __bitf_T *)0xFFFFA10C)->bit02)
#define TBTAUB0I0          (((volatile __bitf_T *)0xFFFFA10C)->bit06)
#define MKTAUB0I0          (((volatile __bitf_T *)0xFFFFA10C)->bit07)
#define RFTAUB0I0          (((volatile __bitf_T *)0xFFFFA10D)->bit04)
#define CTTAUB0I0          (((volatile __bitf_T *)0xFFFFA10D)->bit07)
__IOREG(ICTAUB0I1, 0xFFFFA10E, __READ_WRITE, uint16);
__IOREG(ICTAUB0I1L, 0xFFFFA10E, __READ_WRITE, uint8);
__IOREG(ICTAUB0I1H, 0xFFFFA10F, __READ_WRITE, uint8);
#define P0TAUB0I1          (((volatile __bitf_T *)0xFFFFA10E)->bit00)
#define P1TAUB0I1          (((volatile __bitf_T *)0xFFFFA10E)->bit01)
#define P2TAUB0I1          (((volatile __bitf_T *)0xFFFFA10E)->bit02)
#define TBTAUB0I1          (((volatile __bitf_T *)0xFFFFA10E)->bit06)
#define MKTAUB0I1          (((volatile __bitf_T *)0xFFFFA10E)->bit07)
#define RFTAUB0I1          (((volatile __bitf_T *)0xFFFFA10F)->bit04)
#define CTTAUB0I1          (((volatile __bitf_T *)0xFFFFA10F)->bit07)
__IOREG(ICTAUB0I2, 0xFFFFA110, __READ_WRITE, uint16);
__IOREG(ICTAUB0I2L, 0xFFFFA110, __READ_WRITE, uint8);
__IOREG(ICTAUB0I2H, 0xFFFFA111, __READ_WRITE, uint8);
#define P0TAUB0I2          (((volatile __bitf_T *)0xFFFFA110)->bit00)
#define P1TAUB0I2          (((volatile __bitf_T *)0xFFFFA110)->bit01)
#define P2TAUB0I2          (((volatile __bitf_T *)0xFFFFA110)->bit02)
#define TBTAUB0I2          (((volatile __bitf_T *)0xFFFFA110)->bit06)
#define MKTAUB0I2          (((volatile __bitf_T *)0xFFFFA110)->bit07)
#define RFTAUB0I2          (((volatile __bitf_T *)0xFFFFA111)->bit04)
#define CTTAUB0I2          (((volatile __bitf_T *)0xFFFFA111)->bit07)
__IOREG(ICPWGA16, 0xFFFFA112, __READ_WRITE, uint16);
__IOREG(ICTAUB0I3, 0xFFFFA112, __READ_WRITE, uint16);
__IOREG(ICPWGA16L, 0xFFFFA112, __READ_WRITE, uint8);
__IOREG(ICTAUB0I3L, 0xFFFFA112, __READ_WRITE, uint8);
__IOREG(ICPWGA16H, 0xFFFFA113, __READ_WRITE, uint8);
__IOREG(ICTAUB0I3H, 0xFFFFA113, __READ_WRITE, uint8);
#define P0PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit00)
#define P0TAUB0I3          (((volatile __bitf_T *)0xFFFFA112)->bit00)
#define P1PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit01)
#define P1TAUB0I3          (((volatile __bitf_T *)0xFFFFA112)->bit01)
#define P2PWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit02)
#define P2TAUB0I3          (((volatile __bitf_T *)0xFFFFA112)->bit02)
#define TBPWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit06)
#define TBTAUB0I3          (((volatile __bitf_T *)0xFFFFA112)->bit06)
#define MKPWGA16           (((volatile __bitf_T *)0xFFFFA112)->bit07)
#define MKTAUB0I3          (((volatile __bitf_T *)0xFFFFA112)->bit07)
#define RFPWGA16           (((volatile __bitf_T *)0xFFFFA113)->bit04)
#define RFTAUB0I3          (((volatile __bitf_T *)0xFFFFA113)->bit04)
#define CTPWGA16           (((volatile __bitf_T *)0xFFFFA113)->bit07)
#define CTTAUB0I3          (((volatile __bitf_T *)0xFFFFA113)->bit07)
__IOREG(ICTAUB0I4, 0xFFFFA114, __READ_WRITE, uint16);
__IOREG(ICTAUB0I4L, 0xFFFFA114, __READ_WRITE, uint8);
__IOREG(ICTAUB0I4H, 0xFFFFA115, __READ_WRITE, uint8);
#define P0TAUB0I4          (((volatile __bitf_T *)0xFFFFA114)->bit00)
#define P1TAUB0I4          (((volatile __bitf_T *)0xFFFFA114)->bit01)
#define P2TAUB0I4          (((volatile __bitf_T *)0xFFFFA114)->bit02)
#define TBTAUB0I4          (((volatile __bitf_T *)0xFFFFA114)->bit06)
#define MKTAUB0I4          (((volatile __bitf_T *)0xFFFFA114)->bit07)
#define RFTAUB0I4          (((volatile __bitf_T *)0xFFFFA115)->bit04)
#define CTTAUB0I4          (((volatile __bitf_T *)0xFFFFA115)->bit07)
__IOREG(ICPWGA17, 0xFFFFA116, __READ_WRITE, uint16);
__IOREG(ICTAUB0I5, 0xFFFFA116, __READ_WRITE, uint16);
__IOREG(ICPWGA17L, 0xFFFFA116, __READ_WRITE, uint8);
__IOREG(ICTAUB0I5L, 0xFFFFA116, __READ_WRITE, uint8);
__IOREG(ICPWGA17H, 0xFFFFA117, __READ_WRITE, uint8);
__IOREG(ICTAUB0I5H, 0xFFFFA117, __READ_WRITE, uint8);
#define P0PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit00)
#define P0TAUB0I5          (((volatile __bitf_T *)0xFFFFA116)->bit00)
#define P1PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit01)
#define P1TAUB0I5          (((volatile __bitf_T *)0xFFFFA116)->bit01)
#define P2PWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit02)
#define P2TAUB0I5          (((volatile __bitf_T *)0xFFFFA116)->bit02)
#define TBPWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit06)
#define TBTAUB0I5          (((volatile __bitf_T *)0xFFFFA116)->bit06)
#define MKPWGA17           (((volatile __bitf_T *)0xFFFFA116)->bit07)
#define MKTAUB0I5          (((volatile __bitf_T *)0xFFFFA116)->bit07)
#define RFPWGA17           (((volatile __bitf_T *)0xFFFFA117)->bit04)
#define RFTAUB0I5          (((volatile __bitf_T *)0xFFFFA117)->bit04)
#define CTPWGA17           (((volatile __bitf_T *)0xFFFFA117)->bit07)
#define CTTAUB0I5          (((volatile __bitf_T *)0xFFFFA117)->bit07)
__IOREG(ICTAUB0I6, 0xFFFFA118, __READ_WRITE, uint16);
__IOREG(ICTAUB0I6L, 0xFFFFA118, __READ_WRITE, uint8);
__IOREG(ICTAUB0I6H, 0xFFFFA119, __READ_WRITE, uint8);
#define P0TAUB0I6          (((volatile __bitf_T *)0xFFFFA118)->bit00)
#define P1TAUB0I6          (((volatile __bitf_T *)0xFFFFA118)->bit01)
#define P2TAUB0I6          (((volatile __bitf_T *)0xFFFFA118)->bit02)
#define TBTAUB0I6          (((volatile __bitf_T *)0xFFFFA118)->bit06)
#define MKTAUB0I6          (((volatile __bitf_T *)0xFFFFA118)->bit07)
#define RFTAUB0I6          (((volatile __bitf_T *)0xFFFFA119)->bit04)
#define CTTAUB0I6          (((volatile __bitf_T *)0xFFFFA119)->bit07)
__IOREG(ICPWGA18, 0xFFFFA11A, __READ_WRITE, uint16);
__IOREG(ICTAUB0I7, 0xFFFFA11A, __READ_WRITE, uint16);
__IOREG(ICPWGA18L, 0xFFFFA11A, __READ_WRITE, uint8);
__IOREG(ICTAUB0I7L, 0xFFFFA11A, __READ_WRITE, uint8);
__IOREG(ICPWGA18H, 0xFFFFA11B, __READ_WRITE, uint8);
__IOREG(ICTAUB0I7H, 0xFFFFA11B, __READ_WRITE, uint8);
#define P0PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit00)
#define P0TAUB0I7          (((volatile __bitf_T *)0xFFFFA11A)->bit00)
#define P1PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit01)
#define P1TAUB0I7          (((volatile __bitf_T *)0xFFFFA11A)->bit01)
#define P2PWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit02)
#define P2TAUB0I7          (((volatile __bitf_T *)0xFFFFA11A)->bit02)
#define TBPWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit06)
#define TBTAUB0I7          (((volatile __bitf_T *)0xFFFFA11A)->bit06)
#define MKPWGA18           (((volatile __bitf_T *)0xFFFFA11A)->bit07)
#define MKTAUB0I7          (((volatile __bitf_T *)0xFFFFA11A)->bit07)
#define RFPWGA18           (((volatile __bitf_T *)0xFFFFA11B)->bit04)
#define RFTAUB0I7          (((volatile __bitf_T *)0xFFFFA11B)->bit04)
#define CTPWGA18           (((volatile __bitf_T *)0xFFFFA11B)->bit07)
#define CTTAUB0I7          (((volatile __bitf_T *)0xFFFFA11B)->bit07)
__IOREG(ICTAUB0I8, 0xFFFFA11C, __READ_WRITE, uint16);
__IOREG(ICTAUB0I8L, 0xFFFFA11C, __READ_WRITE, uint8);
__IOREG(ICTAUB0I8H, 0xFFFFA11D, __READ_WRITE, uint8);
#define P0TAUB0I8          (((volatile __bitf_T *)0xFFFFA11C)->bit00)
#define P1TAUB0I8          (((volatile __bitf_T *)0xFFFFA11C)->bit01)
#define P2TAUB0I8          (((volatile __bitf_T *)0xFFFFA11C)->bit02)
#define TBTAUB0I8          (((volatile __bitf_T *)0xFFFFA11C)->bit06)
#define MKTAUB0I8          (((volatile __bitf_T *)0xFFFFA11C)->bit07)
#define RFTAUB0I8          (((volatile __bitf_T *)0xFFFFA11D)->bit04)
#define CTTAUB0I8          (((volatile __bitf_T *)0xFFFFA11D)->bit07)
__IOREG(ICPWGA19, 0xFFFFA11E, __READ_WRITE, uint16);
__IOREG(ICTAUB0I9, 0xFFFFA11E, __READ_WRITE, uint16);
__IOREG(ICPWGA19L, 0xFFFFA11E, __READ_WRITE, uint8);
__IOREG(ICTAUB0I9L, 0xFFFFA11E, __READ_WRITE, uint8);
__IOREG(ICPWGA19H, 0xFFFFA11F, __READ_WRITE, uint8);
__IOREG(ICTAUB0I9H, 0xFFFFA11F, __READ_WRITE, uint8);
#define P0PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit00)
#define P0TAUB0I9          (((volatile __bitf_T *)0xFFFFA11E)->bit00)
#define P1PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit01)
#define P1TAUB0I9          (((volatile __bitf_T *)0xFFFFA11E)->bit01)
#define P2PWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit02)
#define P2TAUB0I9          (((volatile __bitf_T *)0xFFFFA11E)->bit02)
#define TBPWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit06)
#define TBTAUB0I9          (((volatile __bitf_T *)0xFFFFA11E)->bit06)
#define MKPWGA19           (((volatile __bitf_T *)0xFFFFA11E)->bit07)
#define MKTAUB0I9          (((volatile __bitf_T *)0xFFFFA11E)->bit07)
#define RFPWGA19           (((volatile __bitf_T *)0xFFFFA11F)->bit04)
#define RFTAUB0I9          (((volatile __bitf_T *)0xFFFFA11F)->bit04)
#define CTPWGA19           (((volatile __bitf_T *)0xFFFFA11F)->bit07)
#define CTTAUB0I9          (((volatile __bitf_T *)0xFFFFA11F)->bit07)
__IOREG(ICTAUB0I10, 0xFFFFA120, __READ_WRITE, uint16);
__IOREG(ICTAUB0I10L, 0xFFFFA120, __READ_WRITE, uint8);
__IOREG(ICTAUB0I10H, 0xFFFFA121, __READ_WRITE, uint8);
#define P0TAUB0I10         (((volatile __bitf_T *)0xFFFFA120)->bit00)
#define P1TAUB0I10         (((volatile __bitf_T *)0xFFFFA120)->bit01)
#define P2TAUB0I10         (((volatile __bitf_T *)0xFFFFA120)->bit02)
#define TBTAUB0I10         (((volatile __bitf_T *)0xFFFFA120)->bit06)
#define MKTAUB0I10         (((volatile __bitf_T *)0xFFFFA120)->bit07)
#define RFTAUB0I10         (((volatile __bitf_T *)0xFFFFA121)->bit04)
#define CTTAUB0I10         (((volatile __bitf_T *)0xFFFFA121)->bit07)
__IOREG(ICPWGA26, 0xFFFFA122, __READ_WRITE, uint16);
__IOREG(ICTAUB0I11, 0xFFFFA122, __READ_WRITE, uint16);
__IOREG(ICPWGA26L, 0xFFFFA122, __READ_WRITE, uint8);
__IOREG(ICTAUB0I11L, 0xFFFFA122, __READ_WRITE, uint8);
__IOREG(ICPWGA26H, 0xFFFFA123, __READ_WRITE, uint8);
__IOREG(ICTAUB0I11H, 0xFFFFA123, __READ_WRITE, uint8);
#define P0PWGA26           (((volatile __bitf_T *)0xFFFFA122)->bit00)
#define P0TAUB0I11         (((volatile __bitf_T *)0xFFFFA122)->bit00)
#define P1PWGA26           (((volatile __bitf_T *)0xFFFFA122)->bit01)
#define P1TAUB0I11         (((volatile __bitf_T *)0xFFFFA122)->bit01)
#define P2PWGA26           (((volatile __bitf_T *)0xFFFFA122)->bit02)
#define P2TAUB0I11         (((volatile __bitf_T *)0xFFFFA122)->bit02)
#define TBPWGA26           (((volatile __bitf_T *)0xFFFFA122)->bit06)
#define TBTAUB0I11         (((volatile __bitf_T *)0xFFFFA122)->bit06)
#define MKPWGA26           (((volatile __bitf_T *)0xFFFFA122)->bit07)
#define MKTAUB0I11         (((volatile __bitf_T *)0xFFFFA122)->bit07)
#define RFPWGA26           (((volatile __bitf_T *)0xFFFFA123)->bit04)
#define RFTAUB0I11         (((volatile __bitf_T *)0xFFFFA123)->bit04)
#define CTPWGA26           (((volatile __bitf_T *)0xFFFFA123)->bit07)
#define CTTAUB0I11         (((volatile __bitf_T *)0xFFFFA123)->bit07)
__IOREG(ICTAUB0I12, 0xFFFFA124, __READ_WRITE, uint16);
__IOREG(ICTAUB0I12L, 0xFFFFA124, __READ_WRITE, uint8);
__IOREG(ICTAUB0I12H, 0xFFFFA125, __READ_WRITE, uint8);
#define P0TAUB0I12         (((volatile __bitf_T *)0xFFFFA124)->bit00)
#define P1TAUB0I12         (((volatile __bitf_T *)0xFFFFA124)->bit01)
#define P2TAUB0I12         (((volatile __bitf_T *)0xFFFFA124)->bit02)
#define TBTAUB0I12         (((volatile __bitf_T *)0xFFFFA124)->bit06)
#define MKTAUB0I12         (((volatile __bitf_T *)0xFFFFA124)->bit07)
#define RFTAUB0I12         (((volatile __bitf_T *)0xFFFFA125)->bit04)
#define CTTAUB0I12         (((volatile __bitf_T *)0xFFFFA125)->bit07)
__IOREG(ICPWGA30, 0xFFFFA126, __READ_WRITE, uint16);
__IOREG(ICTAUB0I13, 0xFFFFA126, __READ_WRITE, uint16);
__IOREG(ICPWGA30L, 0xFFFFA126, __READ_WRITE, uint8);
__IOREG(ICTAUB0I13L, 0xFFFFA126, __READ_WRITE, uint8);
__IOREG(ICPWGA30H, 0xFFFFA127, __READ_WRITE, uint8);
__IOREG(ICTAUB0I13H, 0xFFFFA127, __READ_WRITE, uint8);
#define P0PWGA30           (((volatile __bitf_T *)0xFFFFA126)->bit00)
#define P0TAUB0I13         (((volatile __bitf_T *)0xFFFFA126)->bit00)
#define P1PWGA30           (((volatile __bitf_T *)0xFFFFA126)->bit01)
#define P1TAUB0I13         (((volatile __bitf_T *)0xFFFFA126)->bit01)
#define P2PWGA30           (((volatile __bitf_T *)0xFFFFA126)->bit02)
#define P2TAUB0I13         (((volatile __bitf_T *)0xFFFFA126)->bit02)
#define TBPWGA30           (((volatile __bitf_T *)0xFFFFA126)->bit06)
#define TBTAUB0I13         (((volatile __bitf_T *)0xFFFFA126)->bit06)
#define MKPWGA30           (((volatile __bitf_T *)0xFFFFA126)->bit07)
#define MKTAUB0I13         (((volatile __bitf_T *)0xFFFFA126)->bit07)
#define RFPWGA30           (((volatile __bitf_T *)0xFFFFA127)->bit04)
#define RFTAUB0I13         (((volatile __bitf_T *)0xFFFFA127)->bit04)
#define CTPWGA30           (((volatile __bitf_T *)0xFFFFA127)->bit07)
#define CTTAUB0I13         (((volatile __bitf_T *)0xFFFFA127)->bit07)
__IOREG(ICTAUB0I14, 0xFFFFA128, __READ_WRITE, uint16);
__IOREG(ICTAUB0I14L, 0xFFFFA128, __READ_WRITE, uint8);
__IOREG(ICTAUB0I14H, 0xFFFFA129, __READ_WRITE, uint8);
#define P0TAUB0I14         (((volatile __bitf_T *)0xFFFFA128)->bit00)
#define P1TAUB0I14         (((volatile __bitf_T *)0xFFFFA128)->bit01)
#define P2TAUB0I14         (((volatile __bitf_T *)0xFFFFA128)->bit02)
#define TBTAUB0I14         (((volatile __bitf_T *)0xFFFFA128)->bit06)
#define MKTAUB0I14         (((volatile __bitf_T *)0xFFFFA128)->bit07)
#define RFTAUB0I14         (((volatile __bitf_T *)0xFFFFA129)->bit04)
#define CTTAUB0I14         (((volatile __bitf_T *)0xFFFFA129)->bit07)
__IOREG(ICPWGA31, 0xFFFFA12A, __READ_WRITE, uint16);
__IOREG(ICTAUB0I15, 0xFFFFA12A, __READ_WRITE, uint16);
__IOREG(ICPWGA31L, 0xFFFFA12A, __READ_WRITE, uint8);
__IOREG(ICTAUB0I15L, 0xFFFFA12A, __READ_WRITE, uint8);
__IOREG(ICPWGA31H, 0xFFFFA12B, __READ_WRITE, uint8);
__IOREG(ICTAUB0I15H, 0xFFFFA12B, __READ_WRITE, uint8);
#define P0PWGA31           (((volatile __bitf_T *)0xFFFFA12A)->bit00)
#define P0TAUB0I15         (((volatile __bitf_T *)0xFFFFA12A)->bit00)
#define P1PWGA31           (((volatile __bitf_T *)0xFFFFA12A)->bit01)
#define P1TAUB0I15         (((volatile __bitf_T *)0xFFFFA12A)->bit01)
#define P2PWGA31           (((volatile __bitf_T *)0xFFFFA12A)->bit02)
#define P2TAUB0I15         (((volatile __bitf_T *)0xFFFFA12A)->bit02)
#define TBPWGA31           (((volatile __bitf_T *)0xFFFFA12A)->bit06)
#define TBTAUB0I15         (((volatile __bitf_T *)0xFFFFA12A)->bit06)
#define MKPWGA31           (((volatile __bitf_T *)0xFFFFA12A)->bit07)
#define MKTAUB0I15         (((volatile __bitf_T *)0xFFFFA12A)->bit07)
#define RFPWGA31           (((volatile __bitf_T *)0xFFFFA12B)->bit04)
#define RFTAUB0I15         (((volatile __bitf_T *)0xFFFFA12B)->bit04)
#define CTPWGA31           (((volatile __bitf_T *)0xFFFFA12B)->bit07)
#define CTTAUB0I15         (((volatile __bitf_T *)0xFFFFA12B)->bit07)
__IOREG(ICCSIH3IC, 0xFFFFA12C, __READ_WRITE, uint16);
__IOREG(ICTAUD0I2_2, 0xFFFFA12C, __READ_WRITE, uint16);
__IOREG(ICCSIH3ICL, 0xFFFFA12C, __READ_WRITE, uint8);
__IOREG(ICTAUD0I2L_2, 0xFFFFA12C, __READ_WRITE, uint8);
__IOREG(ICCSIH3ICH, 0xFFFFA12D, __READ_WRITE, uint8);
__IOREG(ICTAUD0I2H_2, 0xFFFFA12D, __READ_WRITE, uint8);
#define P0CSIH3IC          (((volatile __bitf_T *)0xFFFFA12C)->bit00)
#define P0TAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12C)->bit00)
#define P1CSIH3IC          (((volatile __bitf_T *)0xFFFFA12C)->bit01)
#define P1TAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12C)->bit01)
#define P2CSIH3IC          (((volatile __bitf_T *)0xFFFFA12C)->bit02)
#define P2TAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12C)->bit02)
#define TBCSIH3IC          (((volatile __bitf_T *)0xFFFFA12C)->bit06)
#define TBTAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12C)->bit06)
#define MKCSIH3IC          (((volatile __bitf_T *)0xFFFFA12C)->bit07)
#define MKTAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12C)->bit07)
#define RFCSIH3IC          (((volatile __bitf_T *)0xFFFFA12D)->bit04)
#define RFTAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12D)->bit04)
#define CTCSIH3IC          (((volatile __bitf_T *)0xFFFFA12D)->bit07)
#define CTTAUD0I2_2        (((volatile __bitf_T *)0xFFFFA12D)->bit07)
__IOREG(ICCSIH3IR, 0xFFFFA12E, __READ_WRITE, uint16);
__IOREG(ICTAUD0I10_2, 0xFFFFA12E, __READ_WRITE, uint16);
__IOREG(ICCSIH3IRL, 0xFFFFA12E, __READ_WRITE, uint8);
__IOREG(ICTAUD0I10L_2, 0xFFFFA12E, __READ_WRITE, uint8);
__IOREG(ICCSIH3IRH, 0xFFFFA12F, __READ_WRITE, uint8);
__IOREG(ICTAUD0I10H_2, 0xFFFFA12F, __READ_WRITE, uint8);
#define P0CSIH3IR          (((volatile __bitf_T *)0xFFFFA12E)->bit00)
#define P0TAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12E)->bit00)
#define P1CSIH3IR          (((volatile __bitf_T *)0xFFFFA12E)->bit01)
#define P1TAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12E)->bit01)
#define P2CSIH3IR          (((volatile __bitf_T *)0xFFFFA12E)->bit02)
#define P2TAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12E)->bit02)
#define TBCSIH3IR          (((volatile __bitf_T *)0xFFFFA12E)->bit06)
#define TBTAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12E)->bit06)
#define MKCSIH3IR          (((volatile __bitf_T *)0xFFFFA12E)->bit07)
#define MKTAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12E)->bit07)
#define RFCSIH3IR          (((volatile __bitf_T *)0xFFFFA12F)->bit04)
#define RFTAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12F)->bit04)
#define CTCSIH3IR          (((volatile __bitf_T *)0xFFFFA12F)->bit07)
#define CTTAUD0I10_2       (((volatile __bitf_T *)0xFFFFA12F)->bit07)
__IOREG(ICCSIH3IRE, 0xFFFFA130, __READ_WRITE, uint16);
__IOREG(ICTAUD0I12_2, 0xFFFFA130, __READ_WRITE, uint16);
__IOREG(ICCSIH3IREL, 0xFFFFA130, __READ_WRITE, uint8);
__IOREG(ICTAUD0I12L_2, 0xFFFFA130, __READ_WRITE, uint8);
__IOREG(ICCSIH3IREH, 0xFFFFA131, __READ_WRITE, uint8);
__IOREG(ICTAUD0I12H_2, 0xFFFFA131, __READ_WRITE, uint8);
#define P0CSIH3IRE         (((volatile __bitf_T *)0xFFFFA130)->bit00)
#define P0TAUD0I12_2       (((volatile __bitf_T *)0xFFFFA130)->bit00)
#define P1CSIH3IRE         (((volatile __bitf_T *)0xFFFFA130)->bit01)
#define P1TAUD0I12_2       (((volatile __bitf_T *)0xFFFFA130)->bit01)
#define P2CSIH3IRE         (((volatile __bitf_T *)0xFFFFA130)->bit02)
#define P2TAUD0I12_2       (((volatile __bitf_T *)0xFFFFA130)->bit02)
#define TBCSIH3IRE         (((volatile __bitf_T *)0xFFFFA130)->bit06)
#define TBTAUD0I12_2       (((volatile __bitf_T *)0xFFFFA130)->bit06)
#define MKCSIH3IRE         (((volatile __bitf_T *)0xFFFFA130)->bit07)
#define MKTAUD0I12_2       (((volatile __bitf_T *)0xFFFFA130)->bit07)
#define RFCSIH3IRE         (((volatile __bitf_T *)0xFFFFA131)->bit04)
#define RFTAUD0I12_2       (((volatile __bitf_T *)0xFFFFA131)->bit04)
#define CTCSIH3IRE         (((volatile __bitf_T *)0xFFFFA131)->bit07)
#define CTTAUD0I12_2       (((volatile __bitf_T *)0xFFFFA131)->bit07)
__IOREG(ICCSIH3IJC, 0xFFFFA132, __READ_WRITE, uint16);
__IOREG(ICTAUD0I14_2, 0xFFFFA132, __READ_WRITE, uint16);
__IOREG(ICCSIH3IJCL, 0xFFFFA132, __READ_WRITE, uint8);
__IOREG(ICTAUD0I14L_2, 0xFFFFA132, __READ_WRITE, uint8);
__IOREG(ICCSIH3IJCH, 0xFFFFA133, __READ_WRITE, uint8);
__IOREG(ICTAUD0I14H_2, 0xFFFFA133, __READ_WRITE, uint8);
#define P0CSIH3IJC         (((volatile __bitf_T *)0xFFFFA132)->bit00)
#define P0TAUD0I14_2       (((volatile __bitf_T *)0xFFFFA132)->bit00)
#define P1CSIH3IJC         (((volatile __bitf_T *)0xFFFFA132)->bit01)
#define P1TAUD0I14_2       (((volatile __bitf_T *)0xFFFFA132)->bit01)
#define P2CSIH3IJC         (((volatile __bitf_T *)0xFFFFA132)->bit02)
#define P2TAUD0I14_2       (((volatile __bitf_T *)0xFFFFA132)->bit02)
#define TBCSIH3IJC         (((volatile __bitf_T *)0xFFFFA132)->bit06)
#define TBTAUD0I14_2       (((volatile __bitf_T *)0xFFFFA132)->bit06)
#define MKCSIH3IJC         (((volatile __bitf_T *)0xFFFFA132)->bit07)
#define MKTAUD0I14_2       (((volatile __bitf_T *)0xFFFFA132)->bit07)
#define RFCSIH3IJC         (((volatile __bitf_T *)0xFFFFA133)->bit04)
#define RFTAUD0I14_2       (((volatile __bitf_T *)0xFFFFA133)->bit04)
#define CTCSIH3IJC         (((volatile __bitf_T *)0xFFFFA133)->bit07)
#define CTTAUD0I14_2       (((volatile __bitf_T *)0xFFFFA133)->bit07)
__IOREG(ICRLIN22, 0xFFFFA134, __READ_WRITE, uint16);
__IOREG(ICRLIN22L, 0xFFFFA134, __READ_WRITE, uint8);
__IOREG(ICRLIN22H, 0xFFFFA135, __READ_WRITE, uint8);
#define P0RLIN22           (((volatile __bitf_T *)0xFFFFA134)->bit00)
#define P1RLIN22           (((volatile __bitf_T *)0xFFFFA134)->bit01)
#define P2RLIN22           (((volatile __bitf_T *)0xFFFFA134)->bit02)
#define TBRLIN22           (((volatile __bitf_T *)0xFFFFA134)->bit06)
#define MKRLIN22           (((volatile __bitf_T *)0xFFFFA134)->bit07)
#define RFRLIN22           (((volatile __bitf_T *)0xFFFFA135)->bit04)
#define CTRLIN22           (((volatile __bitf_T *)0xFFFFA135)->bit07)
__IOREG(ICRLIN23, 0xFFFFA136, __READ_WRITE, uint16);
__IOREG(ICRLIN23L, 0xFFFFA136, __READ_WRITE, uint8);
__IOREG(ICRLIN23H, 0xFFFFA137, __READ_WRITE, uint8);
#define P0RLIN23           (((volatile __bitf_T *)0xFFFFA136)->bit00)
#define P1RLIN23           (((volatile __bitf_T *)0xFFFFA136)->bit01)
#define P2RLIN23           (((volatile __bitf_T *)0xFFFFA136)->bit02)
#define TBRLIN23           (((volatile __bitf_T *)0xFFFFA136)->bit06)
#define MKRLIN23           (((volatile __bitf_T *)0xFFFFA136)->bit07)
#define RFRLIN23           (((volatile __bitf_T *)0xFFFFA137)->bit04)
#define CTRLIN23           (((volatile __bitf_T *)0xFFFFA137)->bit07)
__IOREG(ICRLIN32, 0xFFFFA138, __READ_WRITE, uint16);
__IOREG(ICRLIN32L, 0xFFFFA138, __READ_WRITE, uint8);
__IOREG(ICRLIN32H, 0xFFFFA139, __READ_WRITE, uint8);
#define P0RLIN32           (((volatile __bitf_T *)0xFFFFA138)->bit00)
#define P1RLIN32           (((volatile __bitf_T *)0xFFFFA138)->bit01)
#define P2RLIN32           (((volatile __bitf_T *)0xFFFFA138)->bit02)
#define TBRLIN32           (((volatile __bitf_T *)0xFFFFA138)->bit06)
#define MKRLIN32           (((volatile __bitf_T *)0xFFFFA138)->bit07)
#define RFRLIN32           (((volatile __bitf_T *)0xFFFFA139)->bit04)
#define CTRLIN32           (((volatile __bitf_T *)0xFFFFA139)->bit07)
__IOREG(ICRLIN32UR0, 0xFFFFA13A, __READ_WRITE, uint16);
__IOREG(ICRLIN32UR0L, 0xFFFFA13A, __READ_WRITE, uint8);
__IOREG(ICRLIN32UR0H, 0xFFFFA13B, __READ_WRITE, uint8);
#define P0RLIN32UR0        (((volatile __bitf_T *)0xFFFFA13A)->bit00)
#define P1RLIN32UR0        (((volatile __bitf_T *)0xFFFFA13A)->bit01)
#define P2RLIN32UR0        (((volatile __bitf_T *)0xFFFFA13A)->bit02)
#define TBRLIN32UR0        (((volatile __bitf_T *)0xFFFFA13A)->bit06)
#define MKRLIN32UR0        (((volatile __bitf_T *)0xFFFFA13A)->bit07)
#define RFRLIN32UR0        (((volatile __bitf_T *)0xFFFFA13B)->bit04)
#define CTRLIN32UR0        (((volatile __bitf_T *)0xFFFFA13B)->bit07)
__IOREG(ICRLIN32UR1, 0xFFFFA13C, __READ_WRITE, uint16);
__IOREG(ICRLIN32UR1L, 0xFFFFA13C, __READ_WRITE, uint8);
__IOREG(ICRLIN32UR1H, 0xFFFFA13D, __READ_WRITE, uint8);
#define P0RLIN32UR1        (((volatile __bitf_T *)0xFFFFA13C)->bit00)
#define P1RLIN32UR1        (((volatile __bitf_T *)0xFFFFA13C)->bit01)
#define P2RLIN32UR1        (((volatile __bitf_T *)0xFFFFA13C)->bit02)
#define TBRLIN32UR1        (((volatile __bitf_T *)0xFFFFA13C)->bit06)
#define MKRLIN32UR1        (((volatile __bitf_T *)0xFFFFA13C)->bit07)
#define RFRLIN32UR1        (((volatile __bitf_T *)0xFFFFA13D)->bit04)
#define CTRLIN32UR1        (((volatile __bitf_T *)0xFFFFA13D)->bit07)
__IOREG(ICRLIN32UR2, 0xFFFFA13E, __READ_WRITE, uint16);
__IOREG(ICRLIN32UR2L, 0xFFFFA13E, __READ_WRITE, uint8);
__IOREG(ICRLIN32UR2H, 0xFFFFA13F, __READ_WRITE, uint8);
#define P0RLIN32UR2        (((volatile __bitf_T *)0xFFFFA13E)->bit00)
#define P1RLIN32UR2        (((volatile __bitf_T *)0xFFFFA13E)->bit01)
#define P2RLIN32UR2        (((volatile __bitf_T *)0xFFFFA13E)->bit02)
#define TBRLIN32UR2        (((volatile __bitf_T *)0xFFFFA13E)->bit06)
#define MKRLIN32UR2        (((volatile __bitf_T *)0xFFFFA13E)->bit07)
#define RFRLIN32UR2        (((volatile __bitf_T *)0xFFFFA13F)->bit04)
#define CTRLIN32UR2        (((volatile __bitf_T *)0xFFFFA13F)->bit07)
__IOREG(ICTAUJ1I0, 0xFFFFA140, __READ_WRITE, uint16);
__IOREG(ICTAUJ1I0L, 0xFFFFA140, __READ_WRITE, uint8);
__IOREG(ICTAUJ1I0H, 0xFFFFA141, __READ_WRITE, uint8);
#define P0TAUJ1I0          (((volatile __bitf_T *)0xFFFFA140)->bit00)
#define P1TAUJ1I0          (((volatile __bitf_T *)0xFFFFA140)->bit01)
#define P2TAUJ1I0          (((volatile __bitf_T *)0xFFFFA140)->bit02)
#define TBTAUJ1I0          (((volatile __bitf_T *)0xFFFFA140)->bit06)
#define MKTAUJ1I0          (((volatile __bitf_T *)0xFFFFA140)->bit07)
#define RFTAUJ1I0          (((volatile __bitf_T *)0xFFFFA141)->bit04)
#define CTTAUJ1I0          (((volatile __bitf_T *)0xFFFFA141)->bit07)
__IOREG(ICTAUJ1I1, 0xFFFFA142, __READ_WRITE, uint16);
__IOREG(ICTAUJ1I1L, 0xFFFFA142, __READ_WRITE, uint8);
__IOREG(ICTAUJ1I1H, 0xFFFFA143, __READ_WRITE, uint8);
#define P0TAUJ1I1          (((volatile __bitf_T *)0xFFFFA142)->bit00)
#define P1TAUJ1I1          (((volatile __bitf_T *)0xFFFFA142)->bit01)
#define P2TAUJ1I1          (((volatile __bitf_T *)0xFFFFA142)->bit02)
#define TBTAUJ1I1          (((volatile __bitf_T *)0xFFFFA142)->bit06)
#define MKTAUJ1I1          (((volatile __bitf_T *)0xFFFFA142)->bit07)
#define RFTAUJ1I1          (((volatile __bitf_T *)0xFFFFA143)->bit04)
#define CTTAUJ1I1          (((volatile __bitf_T *)0xFFFFA143)->bit07)
__IOREG(ICTAUJ1I2, 0xFFFFA144, __READ_WRITE, uint16);
__IOREG(ICTAUJ1I2L, 0xFFFFA144, __READ_WRITE, uint8);
__IOREG(ICTAUJ1I2H, 0xFFFFA145, __READ_WRITE, uint8);
#define P0TAUJ1I2          (((volatile __bitf_T *)0xFFFFA144)->bit00)
#define P1TAUJ1I2          (((volatile __bitf_T *)0xFFFFA144)->bit01)
#define P2TAUJ1I2          (((volatile __bitf_T *)0xFFFFA144)->bit02)
#define TBTAUJ1I2          (((volatile __bitf_T *)0xFFFFA144)->bit06)
#define MKTAUJ1I2          (((volatile __bitf_T *)0xFFFFA144)->bit07)
#define RFTAUJ1I2          (((volatile __bitf_T *)0xFFFFA145)->bit04)
#define CTTAUJ1I2          (((volatile __bitf_T *)0xFFFFA145)->bit07)
__IOREG(ICTAUJ1I3, 0xFFFFA146, __READ_WRITE, uint16);
__IOREG(ICTAUJ1I3L, 0xFFFFA146, __READ_WRITE, uint8);
__IOREG(ICTAUJ1I3H, 0xFFFFA147, __READ_WRITE, uint8);
#define P0TAUJ1I3          (((volatile __bitf_T *)0xFFFFA146)->bit00)
#define P1TAUJ1I3          (((volatile __bitf_T *)0xFFFFA146)->bit01)
#define P2TAUJ1I3          (((volatile __bitf_T *)0xFFFFA146)->bit02)
#define TBTAUJ1I3          (((volatile __bitf_T *)0xFFFFA146)->bit06)
#define MKTAUJ1I3          (((volatile __bitf_T *)0xFFFFA146)->bit07)
#define RFTAUJ1I3          (((volatile __bitf_T *)0xFFFFA147)->bit04)
#define CTTAUJ1I3          (((volatile __bitf_T *)0xFFFFA147)->bit07)
__IOREG(ICPWGA24, 0xFFFFA160, __READ_WRITE, uint16);
__IOREG(ICPWGA24L, 0xFFFFA160, __READ_WRITE, uint8);
__IOREG(ICPWGA24H, 0xFFFFA161, __READ_WRITE, uint8);
#define P0PWGA24           (((volatile __bitf_T *)0xFFFFA160)->bit00)
#define P1PWGA24           (((volatile __bitf_T *)0xFFFFA160)->bit01)
#define P2PWGA24           (((volatile __bitf_T *)0xFFFFA160)->bit02)
#define TBPWGA24           (((volatile __bitf_T *)0xFFFFA160)->bit06)
#define MKPWGA24           (((volatile __bitf_T *)0xFFFFA160)->bit07)
#define RFPWGA24           (((volatile __bitf_T *)0xFFFFA161)->bit04)
#define CTPWGA24           (((volatile __bitf_T *)0xFFFFA161)->bit07)
__IOREG(ICPWGA25, 0xFFFFA162, __READ_WRITE, uint16);
__IOREG(ICPWGA25L, 0xFFFFA162, __READ_WRITE, uint8);
__IOREG(ICPWGA25H, 0xFFFFA163, __READ_WRITE, uint8);
#define P0PWGA25           (((volatile __bitf_T *)0xFFFFA162)->bit00)
#define P1PWGA25           (((volatile __bitf_T *)0xFFFFA162)->bit01)
#define P2PWGA25           (((volatile __bitf_T *)0xFFFFA162)->bit02)
#define TBPWGA25           (((volatile __bitf_T *)0xFFFFA162)->bit06)
#define MKPWGA25           (((volatile __bitf_T *)0xFFFFA162)->bit07)
#define RFPWGA25           (((volatile __bitf_T *)0xFFFFA163)->bit04)
#define CTPWGA25           (((volatile __bitf_T *)0xFFFFA163)->bit07)
__IOREG(ICPWGA27, 0xFFFFA164, __READ_WRITE, uint16);
__IOREG(ICPWGA27L, 0xFFFFA164, __READ_WRITE, uint8);
__IOREG(ICPWGA27H, 0xFFFFA165, __READ_WRITE, uint8);
#define P0PWGA27           (((volatile __bitf_T *)0xFFFFA164)->bit00)
#define P1PWGA27           (((volatile __bitf_T *)0xFFFFA164)->bit01)
#define P2PWGA27           (((volatile __bitf_T *)0xFFFFA164)->bit02)
#define TBPWGA27           (((volatile __bitf_T *)0xFFFFA164)->bit06)
#define MKPWGA27           (((volatile __bitf_T *)0xFFFFA164)->bit07)
#define RFPWGA27           (((volatile __bitf_T *)0xFFFFA165)->bit04)
#define CTPWGA27           (((volatile __bitf_T *)0xFFFFA165)->bit07)
__IOREG(ICPWGA28, 0xFFFFA166, __READ_WRITE, uint16);
__IOREG(ICPWGA28L, 0xFFFFA166, __READ_WRITE, uint8);
__IOREG(ICPWGA28H, 0xFFFFA167, __READ_WRITE, uint8);
#define P0PWGA28           (((volatile __bitf_T *)0xFFFFA166)->bit00)
#define P1PWGA28           (((volatile __bitf_T *)0xFFFFA166)->bit01)
#define P2PWGA28           (((volatile __bitf_T *)0xFFFFA166)->bit02)
#define TBPWGA28           (((volatile __bitf_T *)0xFFFFA166)->bit06)
#define MKPWGA28           (((volatile __bitf_T *)0xFFFFA166)->bit07)
#define RFPWGA28           (((volatile __bitf_T *)0xFFFFA167)->bit04)
#define CTPWGA28           (((volatile __bitf_T *)0xFFFFA167)->bit07)
__IOREG(ICPWGA29, 0xFFFFA168, __READ_WRITE, uint16);
__IOREG(ICPWGA29L, 0xFFFFA168, __READ_WRITE, uint8);
__IOREG(ICPWGA29H, 0xFFFFA169, __READ_WRITE, uint8);
#define P0PWGA29           (((volatile __bitf_T *)0xFFFFA168)->bit00)
#define P1PWGA29           (((volatile __bitf_T *)0xFFFFA168)->bit01)
#define P2PWGA29           (((volatile __bitf_T *)0xFFFFA168)->bit02)
#define TBPWGA29           (((volatile __bitf_T *)0xFFFFA168)->bit06)
#define MKPWGA29           (((volatile __bitf_T *)0xFFFFA168)->bit07)
#define RFPWGA29           (((volatile __bitf_T *)0xFFFFA169)->bit04)
#define CTPWGA29           (((volatile __bitf_T *)0xFFFFA169)->bit07)
__IOREG(ICPWGA32, 0xFFFFA16A, __READ_WRITE, uint16);
__IOREG(ICPWGA32L, 0xFFFFA16A, __READ_WRITE, uint8);
__IOREG(ICPWGA32H, 0xFFFFA16B, __READ_WRITE, uint8);
#define P0PWGA32           (((volatile __bitf_T *)0xFFFFA16A)->bit00)
#define P1PWGA32           (((volatile __bitf_T *)0xFFFFA16A)->bit01)
#define P2PWGA32           (((volatile __bitf_T *)0xFFFFA16A)->bit02)
#define TBPWGA32           (((volatile __bitf_T *)0xFFFFA16A)->bit06)
#define MKPWGA32           (((volatile __bitf_T *)0xFFFFA16A)->bit07)
#define RFPWGA32           (((volatile __bitf_T *)0xFFFFA16B)->bit04)
#define CTPWGA32           (((volatile __bitf_T *)0xFFFFA16B)->bit07)
__IOREG(ICPWGA33, 0xFFFFA16C, __READ_WRITE, uint16);
__IOREG(ICPWGA33L, 0xFFFFA16C, __READ_WRITE, uint8);
__IOREG(ICPWGA33H, 0xFFFFA16D, __READ_WRITE, uint8);
#define P0PWGA33           (((volatile __bitf_T *)0xFFFFA16C)->bit00)
#define P1PWGA33           (((volatile __bitf_T *)0xFFFFA16C)->bit01)
#define P2PWGA33           (((volatile __bitf_T *)0xFFFFA16C)->bit02)
#define TBPWGA33           (((volatile __bitf_T *)0xFFFFA16C)->bit06)
#define MKPWGA33           (((volatile __bitf_T *)0xFFFFA16C)->bit07)
#define RFPWGA33           (((volatile __bitf_T *)0xFFFFA16D)->bit04)
#define CTPWGA33           (((volatile __bitf_T *)0xFFFFA16D)->bit07)
__IOREG(ICPWGA34, 0xFFFFA16E, __READ_WRITE, uint16);
__IOREG(ICPWGA34L, 0xFFFFA16E, __READ_WRITE, uint8);
__IOREG(ICPWGA34H, 0xFFFFA16F, __READ_WRITE, uint8);
#define P0PWGA34           (((volatile __bitf_T *)0xFFFFA16E)->bit00)
#define P1PWGA34           (((volatile __bitf_T *)0xFFFFA16E)->bit01)
#define P2PWGA34           (((volatile __bitf_T *)0xFFFFA16E)->bit02)
#define TBPWGA34           (((volatile __bitf_T *)0xFFFFA16E)->bit06)
#define MKPWGA34           (((volatile __bitf_T *)0xFFFFA16E)->bit07)
#define RFPWGA34           (((volatile __bitf_T *)0xFFFFA16F)->bit04)
#define CTPWGA34           (((volatile __bitf_T *)0xFFFFA16F)->bit07)
__IOREG(ICPWGA35, 0xFFFFA170, __READ_WRITE, uint16);
__IOREG(ICPWGA35L, 0xFFFFA170, __READ_WRITE, uint8);
__IOREG(ICPWGA35H, 0xFFFFA171, __READ_WRITE, uint8);
#define P0PWGA35           (((volatile __bitf_T *)0xFFFFA170)->bit00)
#define P1PWGA35           (((volatile __bitf_T *)0xFFFFA170)->bit01)
#define P2PWGA35           (((volatile __bitf_T *)0xFFFFA170)->bit02)
#define TBPWGA35           (((volatile __bitf_T *)0xFFFFA170)->bit06)
#define MKPWGA35           (((volatile __bitf_T *)0xFFFFA170)->bit07)
#define RFPWGA35           (((volatile __bitf_T *)0xFFFFA171)->bit04)
#define CTPWGA35           (((volatile __bitf_T *)0xFFFFA171)->bit07)
__IOREG(ICPWGA36, 0xFFFFA172, __READ_WRITE, uint16);
__IOREG(ICPWGA36L, 0xFFFFA172, __READ_WRITE, uint8);
__IOREG(ICPWGA36H, 0xFFFFA173, __READ_WRITE, uint8);
#define P0PWGA36           (((volatile __bitf_T *)0xFFFFA172)->bit00)
#define P1PWGA36           (((volatile __bitf_T *)0xFFFFA172)->bit01)
#define P2PWGA36           (((volatile __bitf_T *)0xFFFFA172)->bit02)
#define TBPWGA36           (((volatile __bitf_T *)0xFFFFA172)->bit06)
#define MKPWGA36           (((volatile __bitf_T *)0xFFFFA172)->bit07)
#define RFPWGA36           (((volatile __bitf_T *)0xFFFFA173)->bit04)
#define CTPWGA36           (((volatile __bitf_T *)0xFFFFA173)->bit07)
__IOREG(ICPWGA37, 0xFFFFA174, __READ_WRITE, uint16);
__IOREG(ICPWGA37L, 0xFFFFA174, __READ_WRITE, uint8);
__IOREG(ICPWGA37H, 0xFFFFA175, __READ_WRITE, uint8);
#define P0PWGA37           (((volatile __bitf_T *)0xFFFFA174)->bit00)
#define P1PWGA37           (((volatile __bitf_T *)0xFFFFA174)->bit01)
#define P2PWGA37           (((volatile __bitf_T *)0xFFFFA174)->bit02)
#define TBPWGA37           (((volatile __bitf_T *)0xFFFFA174)->bit06)
#define MKPWGA37           (((volatile __bitf_T *)0xFFFFA174)->bit07)
#define RFPWGA37           (((volatile __bitf_T *)0xFFFFA175)->bit04)
#define CTPWGA37           (((volatile __bitf_T *)0xFFFFA175)->bit07)
__IOREG(ICPWGA38, 0xFFFFA176, __READ_WRITE, uint16);
__IOREG(ICPWGA38L, 0xFFFFA176, __READ_WRITE, uint8);
__IOREG(ICPWGA38H, 0xFFFFA177, __READ_WRITE, uint8);
#define P0PWGA38           (((volatile __bitf_T *)0xFFFFA176)->bit00)
#define P1PWGA38           (((volatile __bitf_T *)0xFFFFA176)->bit01)
#define P2PWGA38           (((volatile __bitf_T *)0xFFFFA176)->bit02)
#define TBPWGA38           (((volatile __bitf_T *)0xFFFFA176)->bit06)
#define MKPWGA38           (((volatile __bitf_T *)0xFFFFA176)->bit07)
#define RFPWGA38           (((volatile __bitf_T *)0xFFFFA177)->bit04)
#define CTPWGA38           (((volatile __bitf_T *)0xFFFFA177)->bit07)
__IOREG(ICPWGA39, 0xFFFFA178, __READ_WRITE, uint16);
__IOREG(ICPWGA39L, 0xFFFFA178, __READ_WRITE, uint8);
__IOREG(ICPWGA39H, 0xFFFFA179, __READ_WRITE, uint8);
#define P0PWGA39           (((volatile __bitf_T *)0xFFFFA178)->bit00)
#define P1PWGA39           (((volatile __bitf_T *)0xFFFFA178)->bit01)
#define P2PWGA39           (((volatile __bitf_T *)0xFFFFA178)->bit02)
#define TBPWGA39           (((volatile __bitf_T *)0xFFFFA178)->bit06)
#define MKPWGA39           (((volatile __bitf_T *)0xFFFFA178)->bit07)
#define RFPWGA39           (((volatile __bitf_T *)0xFFFFA179)->bit04)
#define CTPWGA39           (((volatile __bitf_T *)0xFFFFA179)->bit07)
__IOREG(ICPWGA40, 0xFFFFA17A, __READ_WRITE, uint16);
__IOREG(ICPWGA40L, 0xFFFFA17A, __READ_WRITE, uint8);
__IOREG(ICPWGA40H, 0xFFFFA17B, __READ_WRITE, uint8);
#define P0PWGA40           (((volatile __bitf_T *)0xFFFFA17A)->bit00)
#define P1PWGA40           (((volatile __bitf_T *)0xFFFFA17A)->bit01)
#define P2PWGA40           (((volatile __bitf_T *)0xFFFFA17A)->bit02)
#define TBPWGA40           (((volatile __bitf_T *)0xFFFFA17A)->bit06)
#define MKPWGA40           (((volatile __bitf_T *)0xFFFFA17A)->bit07)
#define RFPWGA40           (((volatile __bitf_T *)0xFFFFA17B)->bit04)
#define CTPWGA40           (((volatile __bitf_T *)0xFFFFA17B)->bit07)
__IOREG(ICPWGA41, 0xFFFFA17C, __READ_WRITE, uint16);
__IOREG(ICPWGA41L, 0xFFFFA17C, __READ_WRITE, uint8);
__IOREG(ICPWGA41H, 0xFFFFA17D, __READ_WRITE, uint8);
#define P0PWGA41           (((volatile __bitf_T *)0xFFFFA17C)->bit00)
#define P1PWGA41           (((volatile __bitf_T *)0xFFFFA17C)->bit01)
#define P2PWGA41           (((volatile __bitf_T *)0xFFFFA17C)->bit02)
#define TBPWGA41           (((volatile __bitf_T *)0xFFFFA17C)->bit06)
#define MKPWGA41           (((volatile __bitf_T *)0xFFFFA17C)->bit07)
#define RFPWGA41           (((volatile __bitf_T *)0xFFFFA17D)->bit04)
#define CTPWGA41           (((volatile __bitf_T *)0xFFFFA17D)->bit07)
__IOREG(ICPWGA42, 0xFFFFA17E, __READ_WRITE, uint16);
__IOREG(ICPWGA42L, 0xFFFFA17E, __READ_WRITE, uint8);
__IOREG(ICPWGA42H, 0xFFFFA17F, __READ_WRITE, uint8);
#define P0PWGA42           (((volatile __bitf_T *)0xFFFFA17E)->bit00)
#define P1PWGA42           (((volatile __bitf_T *)0xFFFFA17E)->bit01)
#define P2PWGA42           (((volatile __bitf_T *)0xFFFFA17E)->bit02)
#define TBPWGA42           (((volatile __bitf_T *)0xFFFFA17E)->bit06)
#define MKPWGA42           (((volatile __bitf_T *)0xFFFFA17E)->bit07)
#define RFPWGA42           (((volatile __bitf_T *)0xFFFFA17F)->bit04)
#define CTPWGA42           (((volatile __bitf_T *)0xFFFFA17F)->bit07)
__IOREG(ICPWGA43, 0xFFFFA180, __READ_WRITE, uint16);
__IOREG(ICPWGA43L, 0xFFFFA180, __READ_WRITE, uint8);
__IOREG(ICPWGA43H, 0xFFFFA181, __READ_WRITE, uint8);
#define P0PWGA43           (((volatile __bitf_T *)0xFFFFA180)->bit00)
#define P1PWGA43           (((volatile __bitf_T *)0xFFFFA180)->bit01)
#define P2PWGA43           (((volatile __bitf_T *)0xFFFFA180)->bit02)
#define TBPWGA43           (((volatile __bitf_T *)0xFFFFA180)->bit06)
#define MKPWGA43           (((volatile __bitf_T *)0xFFFFA180)->bit07)
#define RFPWGA43           (((volatile __bitf_T *)0xFFFFA181)->bit04)
#define CTPWGA43           (((volatile __bitf_T *)0xFFFFA181)->bit07)
__IOREG(ICPWGA44, 0xFFFFA182, __READ_WRITE, uint16);
__IOREG(ICPWGA44L, 0xFFFFA182, __READ_WRITE, uint8);
__IOREG(ICPWGA44H, 0xFFFFA183, __READ_WRITE, uint8);
#define P0PWGA44           (((volatile __bitf_T *)0xFFFFA182)->bit00)
#define P1PWGA44           (((volatile __bitf_T *)0xFFFFA182)->bit01)
#define P2PWGA44           (((volatile __bitf_T *)0xFFFFA182)->bit02)
#define TBPWGA44           (((volatile __bitf_T *)0xFFFFA182)->bit06)
#define MKPWGA44           (((volatile __bitf_T *)0xFFFFA182)->bit07)
#define RFPWGA44           (((volatile __bitf_T *)0xFFFFA183)->bit04)
#define CTPWGA44           (((volatile __bitf_T *)0xFFFFA183)->bit07)
__IOREG(ICPWGA45, 0xFFFFA184, __READ_WRITE, uint16);
__IOREG(ICPWGA45L, 0xFFFFA184, __READ_WRITE, uint8);
__IOREG(ICPWGA45H, 0xFFFFA185, __READ_WRITE, uint8);
#define P0PWGA45           (((volatile __bitf_T *)0xFFFFA184)->bit00)
#define P1PWGA45           (((volatile __bitf_T *)0xFFFFA184)->bit01)
#define P2PWGA45           (((volatile __bitf_T *)0xFFFFA184)->bit02)
#define TBPWGA45           (((volatile __bitf_T *)0xFFFFA184)->bit06)
#define MKPWGA45           (((volatile __bitf_T *)0xFFFFA184)->bit07)
#define RFPWGA45           (((volatile __bitf_T *)0xFFFFA185)->bit04)
#define CTPWGA45           (((volatile __bitf_T *)0xFFFFA185)->bit07)
__IOREG(ICPWGA46, 0xFFFFA186, __READ_WRITE, uint16);
__IOREG(ICPWGA46L, 0xFFFFA186, __READ_WRITE, uint8);
__IOREG(ICPWGA46H, 0xFFFFA187, __READ_WRITE, uint8);
#define P0PWGA46           (((volatile __bitf_T *)0xFFFFA186)->bit00)
#define P1PWGA46           (((volatile __bitf_T *)0xFFFFA186)->bit01)
#define P2PWGA46           (((volatile __bitf_T *)0xFFFFA186)->bit02)
#define TBPWGA46           (((volatile __bitf_T *)0xFFFFA186)->bit06)
#define MKPWGA46           (((volatile __bitf_T *)0xFFFFA186)->bit07)
#define RFPWGA46           (((volatile __bitf_T *)0xFFFFA187)->bit04)
#define CTPWGA46           (((volatile __bitf_T *)0xFFFFA187)->bit07)
__IOREG(ICPWGA47, 0xFFFFA188, __READ_WRITE, uint16);
__IOREG(ICPWGA47L, 0xFFFFA188, __READ_WRITE, uint8);
__IOREG(ICPWGA47H, 0xFFFFA189, __READ_WRITE, uint8);
#define P0PWGA47           (((volatile __bitf_T *)0xFFFFA188)->bit00)
#define P1PWGA47           (((volatile __bitf_T *)0xFFFFA188)->bit01)
#define P2PWGA47           (((volatile __bitf_T *)0xFFFFA188)->bit02)
#define TBPWGA47           (((volatile __bitf_T *)0xFFFFA188)->bit06)
#define MKPWGA47           (((volatile __bitf_T *)0xFFFFA188)->bit07)
#define RFPWGA47           (((volatile __bitf_T *)0xFFFFA189)->bit04)
#define CTPWGA47           (((volatile __bitf_T *)0xFFFFA189)->bit07)
__IOREG(ICP9, 0xFFFFA18A, __READ_WRITE, uint16);
__IOREG(ICP9L, 0xFFFFA18A, __READ_WRITE, uint8);
__IOREG(ICP9H, 0xFFFFA18B, __READ_WRITE, uint8);
#define P0P9               (((volatile __bitf_T *)0xFFFFA18A)->bit00)
#define P1P9               (((volatile __bitf_T *)0xFFFFA18A)->bit01)
#define P2P9               (((volatile __bitf_T *)0xFFFFA18A)->bit02)
#define TBP9               (((volatile __bitf_T *)0xFFFFA18A)->bit06)
#define MKP9               (((volatile __bitf_T *)0xFFFFA18A)->bit07)
#define RFP9               (((volatile __bitf_T *)0xFFFFA18B)->bit04)
#define CTP9               (((volatile __bitf_T *)0xFFFFA18B)->bit07)
__IOREG(ICP13, 0xFFFFA18C, __READ_WRITE, uint16);
__IOREG(ICP13L, 0xFFFFA18C, __READ_WRITE, uint8);
__IOREG(ICP13H, 0xFFFFA18D, __READ_WRITE, uint8);
#define P0P13              (((volatile __bitf_T *)0xFFFFA18C)->bit00)
#define P1P13              (((volatile __bitf_T *)0xFFFFA18C)->bit01)
#define P2P13              (((volatile __bitf_T *)0xFFFFA18C)->bit02)
#define TBP13              (((volatile __bitf_T *)0xFFFFA18C)->bit06)
#define MKP13              (((volatile __bitf_T *)0xFFFFA18C)->bit07)
#define RFP13              (((volatile __bitf_T *)0xFFFFA18D)->bit04)
#define CTP13              (((volatile __bitf_T *)0xFFFFA18D)->bit07)
__IOREG(ICP14, 0xFFFFA18E, __READ_WRITE, uint16);
__IOREG(ICP14L, 0xFFFFA18E, __READ_WRITE, uint8);
__IOREG(ICP14H, 0xFFFFA18F, __READ_WRITE, uint8);
#define P0P14              (((volatile __bitf_T *)0xFFFFA18E)->bit00)
#define P1P14              (((volatile __bitf_T *)0xFFFFA18E)->bit01)
#define P2P14              (((volatile __bitf_T *)0xFFFFA18E)->bit02)
#define TBP14              (((volatile __bitf_T *)0xFFFFA18E)->bit06)
#define MKP14              (((volatile __bitf_T *)0xFFFFA18E)->bit07)
#define RFP14              (((volatile __bitf_T *)0xFFFFA18F)->bit04)
#define CTP14              (((volatile __bitf_T *)0xFFFFA18F)->bit07)
__IOREG(ICP15, 0xFFFFA190, __READ_WRITE, uint16);
__IOREG(ICP15L, 0xFFFFA190, __READ_WRITE, uint8);
__IOREG(ICP15H, 0xFFFFA191, __READ_WRITE, uint8);
#define P0P15              (((volatile __bitf_T *)0xFFFFA190)->bit00)
#define P1P15              (((volatile __bitf_T *)0xFFFFA190)->bit01)
#define P2P15              (((volatile __bitf_T *)0xFFFFA190)->bit02)
#define TBP15              (((volatile __bitf_T *)0xFFFFA190)->bit06)
#define MKP15              (((volatile __bitf_T *)0xFFFFA190)->bit07)
#define RFP15              (((volatile __bitf_T *)0xFFFFA191)->bit04)
#define CTP15              (((volatile __bitf_T *)0xFFFFA191)->bit07)
__IOREG(ICRTCA01S, 0xFFFFA192, __READ_WRITE, uint16);
__IOREG(ICRTCA01SL, 0xFFFFA192, __READ_WRITE, uint8);
__IOREG(ICRTCA01SH, 0xFFFFA193, __READ_WRITE, uint8);
#define P0RTCA01S          (((volatile __bitf_T *)0xFFFFA192)->bit00)
#define P1RTCA01S          (((volatile __bitf_T *)0xFFFFA192)->bit01)
#define P2RTCA01S          (((volatile __bitf_T *)0xFFFFA192)->bit02)
#define TBRTCA01S          (((volatile __bitf_T *)0xFFFFA192)->bit06)
#define MKRTCA01S          (((volatile __bitf_T *)0xFFFFA192)->bit07)
#define RFRTCA01S          (((volatile __bitf_T *)0xFFFFA193)->bit04)
#define CTRTCA01S          (((volatile __bitf_T *)0xFFFFA193)->bit07)
__IOREG(ICRTCA0AL, 0xFFFFA194, __READ_WRITE, uint16);
__IOREG(ICRTCA0ALL, 0xFFFFA194, __READ_WRITE, uint8);
__IOREG(ICRTCA0ALH, 0xFFFFA195, __READ_WRITE, uint8);
#define P0RTCA0AL          (((volatile __bitf_T *)0xFFFFA194)->bit00)
#define P1RTCA0AL          (((volatile __bitf_T *)0xFFFFA194)->bit01)
#define P2RTCA0AL          (((volatile __bitf_T *)0xFFFFA194)->bit02)
#define TBRTCA0AL          (((volatile __bitf_T *)0xFFFFA194)->bit06)
#define MKRTCA0AL          (((volatile __bitf_T *)0xFFFFA194)->bit07)
#define RFRTCA0AL          (((volatile __bitf_T *)0xFFFFA195)->bit04)
#define CTRTCA0AL          (((volatile __bitf_T *)0xFFFFA195)->bit07)
__IOREG(ICRTCA0R, 0xFFFFA196, __READ_WRITE, uint16);
__IOREG(ICRTCA0RL, 0xFFFFA196, __READ_WRITE, uint8);
__IOREG(ICRTCA0RH, 0xFFFFA197, __READ_WRITE, uint8);
#define P0RTCA0R           (((volatile __bitf_T *)0xFFFFA196)->bit00)
#define P1RTCA0R           (((volatile __bitf_T *)0xFFFFA196)->bit01)
#define P2RTCA0R           (((volatile __bitf_T *)0xFFFFA196)->bit02)
#define TBRTCA0R           (((volatile __bitf_T *)0xFFFFA196)->bit06)
#define MKRTCA0R           (((volatile __bitf_T *)0xFFFFA196)->bit07)
#define RFRTCA0R           (((volatile __bitf_T *)0xFFFFA197)->bit04)
#define CTRTCA0R           (((volatile __bitf_T *)0xFFFFA197)->bit07)
__IOREG(ICADCA1ERR, 0xFFFFA198, __READ_WRITE, uint16);
__IOREG(ICADCA1ERRL, 0xFFFFA198, __READ_WRITE, uint8);
__IOREG(ICADCA1ERRH, 0xFFFFA199, __READ_WRITE, uint8);
#define P0ADCA1ERR         (((volatile __bitf_T *)0xFFFFA198)->bit00)
#define P1ADCA1ERR         (((volatile __bitf_T *)0xFFFFA198)->bit01)
#define P2ADCA1ERR         (((volatile __bitf_T *)0xFFFFA198)->bit02)
#define TBADCA1ERR         (((volatile __bitf_T *)0xFFFFA198)->bit06)
#define MKADCA1ERR         (((volatile __bitf_T *)0xFFFFA198)->bit07)
#define RFADCA1ERR         (((volatile __bitf_T *)0xFFFFA199)->bit04)
#define CTADCA1ERR         (((volatile __bitf_T *)0xFFFFA199)->bit07)
__IOREG(ICADCA1I0, 0xFFFFA19A, __READ_WRITE, uint16);
__IOREG(ICADCA1I0L, 0xFFFFA19A, __READ_WRITE, uint8);
__IOREG(ICADCA1I0H, 0xFFFFA19B, __READ_WRITE, uint8);
#define P0ADCA1I0          (((volatile __bitf_T *)0xFFFFA19A)->bit00)
#define P1ADCA1I0          (((volatile __bitf_T *)0xFFFFA19A)->bit01)
#define P2ADCA1I0          (((volatile __bitf_T *)0xFFFFA19A)->bit02)
#define TBADCA1I0          (((volatile __bitf_T *)0xFFFFA19A)->bit06)
#define MKADCA1I0          (((volatile __bitf_T *)0xFFFFA19A)->bit07)
#define RFADCA1I0          (((volatile __bitf_T *)0xFFFFA19B)->bit04)
#define CTADCA1I0          (((volatile __bitf_T *)0xFFFFA19B)->bit07)
__IOREG(ICADCA1I1, 0xFFFFA19C, __READ_WRITE, uint16);
__IOREG(ICADCA1I1L, 0xFFFFA19C, __READ_WRITE, uint8);
__IOREG(ICADCA1I1H, 0xFFFFA19D, __READ_WRITE, uint8);
#define P0ADCA1I1          (((volatile __bitf_T *)0xFFFFA19C)->bit00)
#define P1ADCA1I1          (((volatile __bitf_T *)0xFFFFA19C)->bit01)
#define P2ADCA1I1          (((volatile __bitf_T *)0xFFFFA19C)->bit02)
#define TBADCA1I1          (((volatile __bitf_T *)0xFFFFA19C)->bit06)
#define MKADCA1I1          (((volatile __bitf_T *)0xFFFFA19C)->bit07)
#define RFADCA1I1          (((volatile __bitf_T *)0xFFFFA19D)->bit04)
#define CTADCA1I1          (((volatile __bitf_T *)0xFFFFA19D)->bit07)
__IOREG(ICADCA1I2, 0xFFFFA19E, __READ_WRITE, uint16);
__IOREG(ICADCA1I2L, 0xFFFFA19E, __READ_WRITE, uint8);
__IOREG(ICADCA1I2H, 0xFFFFA19F, __READ_WRITE, uint8);
#define P0ADCA1I2          (((volatile __bitf_T *)0xFFFFA19E)->bit00)
#define P1ADCA1I2          (((volatile __bitf_T *)0xFFFFA19E)->bit01)
#define P2ADCA1I2          (((volatile __bitf_T *)0xFFFFA19E)->bit02)
#define TBADCA1I2          (((volatile __bitf_T *)0xFFFFA19E)->bit06)
#define MKADCA1I2          (((volatile __bitf_T *)0xFFFFA19E)->bit07)
#define RFADCA1I2          (((volatile __bitf_T *)0xFFFFA19F)->bit04)
#define CTADCA1I2          (((volatile __bitf_T *)0xFFFFA19F)->bit07)
__IOREG(ICRCAN2ERR, 0xFFFFA1A2, __READ_WRITE, uint16);
__IOREG(ICRCAN2ERRL, 0xFFFFA1A2, __READ_WRITE, uint8);
__IOREG(ICRCAN2ERRH, 0xFFFFA1A3, __READ_WRITE, uint8);
#define P0RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit00)
#define P1RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit01)
#define P2RCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit02)
#define TBRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit06)
#define MKRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A2)->bit07)
#define RFRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A3)->bit04)
#define CTRCAN2ERR         (((volatile __bitf_T *)0xFFFFA1A3)->bit07)
__IOREG(ICRCAN2REC, 0xFFFFA1A4, __READ_WRITE, uint16);
__IOREG(ICRCAN2RECL, 0xFFFFA1A4, __READ_WRITE, uint8);
__IOREG(ICRCAN2RECH, 0xFFFFA1A5, __READ_WRITE, uint8);
#define P0RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit00)
#define P1RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit01)
#define P2RCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit02)
#define TBRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit06)
#define MKRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A4)->bit07)
#define RFRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A5)->bit04)
#define CTRCAN2REC         (((volatile __bitf_T *)0xFFFFA1A5)->bit07)
__IOREG(ICRCAN2TRX, 0xFFFFA1A6, __READ_WRITE, uint16);
__IOREG(ICRCAN2TRXL, 0xFFFFA1A6, __READ_WRITE, uint8);
__IOREG(ICRCAN2TRXH, 0xFFFFA1A7, __READ_WRITE, uint8);
#define P0RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit00)
#define P1RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit01)
#define P2RCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit02)
#define TBRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit06)
#define MKRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A6)->bit07)
#define RFRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A7)->bit04)
#define CTRCAN2TRX         (((volatile __bitf_T *)0xFFFFA1A7)->bit07)
__IOREG(ICRCAN3ERR, 0xFFFFA1A8, __READ_WRITE, uint16);
__IOREG(ICRCAN3ERRL, 0xFFFFA1A8, __READ_WRITE, uint8);
__IOREG(ICRCAN3ERRH, 0xFFFFA1A9, __READ_WRITE, uint8);
#define P0RCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A8)->bit00)
#define P1RCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A8)->bit01)
#define P2RCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A8)->bit02)
#define TBRCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A8)->bit06)
#define MKRCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A8)->bit07)
#define RFRCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A9)->bit04)
#define CTRCAN3ERR         (((volatile __bitf_T *)0xFFFFA1A9)->bit07)
__IOREG(ICRCAN3REC, 0xFFFFA1AA, __READ_WRITE, uint16);
__IOREG(ICRCAN3RECL, 0xFFFFA1AA, __READ_WRITE, uint8);
__IOREG(ICRCAN3RECH, 0xFFFFA1AB, __READ_WRITE, uint8);
#define P0RCAN3REC         (((volatile __bitf_T *)0xFFFFA1AA)->bit00)
#define P1RCAN3REC         (((volatile __bitf_T *)0xFFFFA1AA)->bit01)
#define P2RCAN3REC         (((volatile __bitf_T *)0xFFFFA1AA)->bit02)
#define TBRCAN3REC         (((volatile __bitf_T *)0xFFFFA1AA)->bit06)
#define MKRCAN3REC         (((volatile __bitf_T *)0xFFFFA1AA)->bit07)
#define RFRCAN3REC         (((volatile __bitf_T *)0xFFFFA1AB)->bit04)
#define CTRCAN3REC         (((volatile __bitf_T *)0xFFFFA1AB)->bit07)
__IOREG(ICRCAN3TRX, 0xFFFFA1AC, __READ_WRITE, uint16);
__IOREG(ICRCAN3TRXL, 0xFFFFA1AC, __READ_WRITE, uint8);
__IOREG(ICRCAN3TRXH, 0xFFFFA1AD, __READ_WRITE, uint8);
#define P0RCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AC)->bit00)
#define P1RCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AC)->bit01)
#define P2RCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AC)->bit02)
#define TBRCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AC)->bit06)
#define MKRCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AC)->bit07)
#define RFRCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AD)->bit04)
#define CTRCAN3TRX         (((volatile __bitf_T *)0xFFFFA1AD)->bit07)
__IOREG(ICCSIG1IC, 0xFFFFA1AE, __READ_WRITE, uint16);
__IOREG(ICCSIG1ICL, 0xFFFFA1AE, __READ_WRITE, uint8);
__IOREG(ICCSIG1ICH, 0xFFFFA1AF, __READ_WRITE, uint8);
#define P0CSIG1IC          (((volatile __bitf_T *)0xFFFFA1AE)->bit00)
#define P1CSIG1IC          (((volatile __bitf_T *)0xFFFFA1AE)->bit01)
#define P2CSIG1IC          (((volatile __bitf_T *)0xFFFFA1AE)->bit02)
#define TBCSIG1IC          (((volatile __bitf_T *)0xFFFFA1AE)->bit06)
#define MKCSIG1IC          (((volatile __bitf_T *)0xFFFFA1AE)->bit07)
#define RFCSIG1IC          (((volatile __bitf_T *)0xFFFFA1AF)->bit04)
#define CTCSIG1IC          (((volatile __bitf_T *)0xFFFFA1AF)->bit07)
__IOREG(ICCSIG1IR, 0xFFFFA1B0, __READ_WRITE, uint16);
__IOREG(ICCSIG1IRL, 0xFFFFA1B0, __READ_WRITE, uint8);
__IOREG(ICCSIG1IRH, 0xFFFFA1B1, __READ_WRITE, uint8);
#define P0CSIG1IR          (((volatile __bitf_T *)0xFFFFA1B0)->bit00)
#define P1CSIG1IR          (((volatile __bitf_T *)0xFFFFA1B0)->bit01)
#define P2CSIG1IR          (((volatile __bitf_T *)0xFFFFA1B0)->bit02)
#define TBCSIG1IR          (((volatile __bitf_T *)0xFFFFA1B0)->bit06)
#define MKCSIG1IR          (((volatile __bitf_T *)0xFFFFA1B0)->bit07)
#define RFCSIG1IR          (((volatile __bitf_T *)0xFFFFA1B1)->bit04)
#define CTCSIG1IR          (((volatile __bitf_T *)0xFFFFA1B1)->bit07)
__IOREG(ICCSIG1IRE, 0xFFFFA1B2, __READ_WRITE, uint16);
__IOREG(ICCSIG1IREL, 0xFFFFA1B2, __READ_WRITE, uint8);
__IOREG(ICCSIG1IREH, 0xFFFFA1B3, __READ_WRITE, uint8);
#define P0CSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B2)->bit00)
#define P1CSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B2)->bit01)
#define P2CSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B2)->bit02)
#define TBCSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B2)->bit06)
#define MKCSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B2)->bit07)
#define RFCSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B3)->bit04)
#define CTCSIG1IRE         (((volatile __bitf_T *)0xFFFFA1B3)->bit07)
__IOREG(ICRLIN24, 0xFFFFA1B4, __READ_WRITE, uint16);
__IOREG(ICRLIN24L, 0xFFFFA1B4, __READ_WRITE, uint8);
__IOREG(ICRLIN24H, 0xFFFFA1B5, __READ_WRITE, uint8);
#define P0RLIN24           (((volatile __bitf_T *)0xFFFFA1B4)->bit00)
#define P1RLIN24           (((volatile __bitf_T *)0xFFFFA1B4)->bit01)
#define P2RLIN24           (((volatile __bitf_T *)0xFFFFA1B4)->bit02)
#define TBRLIN24           (((volatile __bitf_T *)0xFFFFA1B4)->bit06)
#define MKRLIN24           (((volatile __bitf_T *)0xFFFFA1B4)->bit07)
#define RFRLIN24           (((volatile __bitf_T *)0xFFFFA1B5)->bit04)
#define CTRLIN24           (((volatile __bitf_T *)0xFFFFA1B5)->bit07)
__IOREG(ICRLIN25, 0xFFFFA1B6, __READ_WRITE, uint16);
__IOREG(ICRLIN25L, 0xFFFFA1B6, __READ_WRITE, uint8);
__IOREG(ICRLIN25H, 0xFFFFA1B7, __READ_WRITE, uint8);
#define P0RLIN25           (((volatile __bitf_T *)0xFFFFA1B6)->bit00)
#define P1RLIN25           (((volatile __bitf_T *)0xFFFFA1B6)->bit01)
#define P2RLIN25           (((volatile __bitf_T *)0xFFFFA1B6)->bit02)
#define TBRLIN25           (((volatile __bitf_T *)0xFFFFA1B6)->bit06)
#define MKRLIN25           (((volatile __bitf_T *)0xFFFFA1B6)->bit07)
#define RFRLIN25           (((volatile __bitf_T *)0xFFFFA1B7)->bit04)
#define CTRLIN25           (((volatile __bitf_T *)0xFFFFA1B7)->bit07)
__IOREG(ICRLIN33, 0xFFFFA1B8, __READ_WRITE, uint16);
__IOREG(ICRLIN33L, 0xFFFFA1B8, __READ_WRITE, uint8);
__IOREG(ICRLIN33H, 0xFFFFA1B9, __READ_WRITE, uint8);
#define P0RLIN33           (((volatile __bitf_T *)0xFFFFA1B8)->bit00)
#define P1RLIN33           (((volatile __bitf_T *)0xFFFFA1B8)->bit01)
#define P2RLIN33           (((volatile __bitf_T *)0xFFFFA1B8)->bit02)
#define TBRLIN33           (((volatile __bitf_T *)0xFFFFA1B8)->bit06)
#define MKRLIN33           (((volatile __bitf_T *)0xFFFFA1B8)->bit07)
#define RFRLIN33           (((volatile __bitf_T *)0xFFFFA1B9)->bit04)
#define CTRLIN33           (((volatile __bitf_T *)0xFFFFA1B9)->bit07)
__IOREG(ICRLIN33UR0, 0xFFFFA1BA, __READ_WRITE, uint16);
__IOREG(ICRLIN33UR0L, 0xFFFFA1BA, __READ_WRITE, uint8);
__IOREG(ICRLIN33UR0H, 0xFFFFA1BB, __READ_WRITE, uint8);
#define P0RLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BA)->bit00)
#define P1RLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BA)->bit01)
#define P2RLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BA)->bit02)
#define TBRLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BA)->bit06)
#define MKRLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BA)->bit07)
#define RFRLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BB)->bit04)
#define CTRLIN33UR0        (((volatile __bitf_T *)0xFFFFA1BB)->bit07)
__IOREG(ICRLIN33UR1, 0xFFFFA1BC, __READ_WRITE, uint16);
__IOREG(ICRLIN33UR1L, 0xFFFFA1BC, __READ_WRITE, uint8);
__IOREG(ICRLIN33UR1H, 0xFFFFA1BD, __READ_WRITE, uint8);
#define P0RLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BC)->bit00)
#define P1RLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BC)->bit01)
#define P2RLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BC)->bit02)
#define TBRLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BC)->bit06)
#define MKRLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BC)->bit07)
#define RFRLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BD)->bit04)
#define CTRLIN33UR1        (((volatile __bitf_T *)0xFFFFA1BD)->bit07)
__IOREG(ICRLIN33UR2, 0xFFFFA1BE, __READ_WRITE, uint16);
__IOREG(ICRLIN33UR2L, 0xFFFFA1BE, __READ_WRITE, uint8);
__IOREG(ICRLIN33UR2H, 0xFFFFA1BF, __READ_WRITE, uint8);
#define P0RLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BE)->bit00)
#define P1RLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BE)->bit01)
#define P2RLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BE)->bit02)
#define TBRLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BE)->bit06)
#define MKRLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BE)->bit07)
#define RFRLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BF)->bit04)
#define CTRLIN33UR2        (((volatile __bitf_T *)0xFFFFA1BF)->bit07)
__IOREG(ICRLIN34, 0xFFFFA1C0, __READ_WRITE, uint16);
__IOREG(ICRLIN34L, 0xFFFFA1C0, __READ_WRITE, uint8);
__IOREG(ICRLIN34H, 0xFFFFA1C1, __READ_WRITE, uint8);
#define P0RLIN34           (((volatile __bitf_T *)0xFFFFA1C0)->bit00)
#define P1RLIN34           (((volatile __bitf_T *)0xFFFFA1C0)->bit01)
#define P2RLIN34           (((volatile __bitf_T *)0xFFFFA1C0)->bit02)
#define TBRLIN34           (((volatile __bitf_T *)0xFFFFA1C0)->bit06)
#define MKRLIN34           (((volatile __bitf_T *)0xFFFFA1C0)->bit07)
#define RFRLIN34           (((volatile __bitf_T *)0xFFFFA1C1)->bit04)
#define CTRLIN34           (((volatile __bitf_T *)0xFFFFA1C1)->bit07)
__IOREG(ICRLIN34UR0, 0xFFFFA1C2, __READ_WRITE, uint16);
__IOREG(ICRLIN34UR0L, 0xFFFFA1C2, __READ_WRITE, uint8);
__IOREG(ICRLIN34UR0H, 0xFFFFA1C3, __READ_WRITE, uint8);
#define P0RLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C2)->bit00)
#define P1RLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C2)->bit01)
#define P2RLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C2)->bit02)
#define TBRLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C2)->bit06)
#define MKRLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C2)->bit07)
#define RFRLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C3)->bit04)
#define CTRLIN34UR0        (((volatile __bitf_T *)0xFFFFA1C3)->bit07)
__IOREG(ICRLIN34UR1, 0xFFFFA1C4, __READ_WRITE, uint16);
__IOREG(ICRLIN34UR1L, 0xFFFFA1C4, __READ_WRITE, uint8);
__IOREG(ICRLIN34UR1H, 0xFFFFA1C5, __READ_WRITE, uint8);
#define P0RLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C4)->bit00)
#define P1RLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C4)->bit01)
#define P2RLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C4)->bit02)
#define TBRLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C4)->bit06)
#define MKRLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C4)->bit07)
#define RFRLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C5)->bit04)
#define CTRLIN34UR1        (((volatile __bitf_T *)0xFFFFA1C5)->bit07)
__IOREG(ICRLIN34UR2, 0xFFFFA1C6, __READ_WRITE, uint16);
__IOREG(ICRLIN34UR2L, 0xFFFFA1C6, __READ_WRITE, uint8);
__IOREG(ICRLIN34UR2H, 0xFFFFA1C7, __READ_WRITE, uint8);
#define P0RLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C6)->bit00)
#define P1RLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C6)->bit01)
#define P2RLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C6)->bit02)
#define TBRLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C6)->bit06)
#define MKRLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C6)->bit07)
#define RFRLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C7)->bit04)
#define CTRLIN34UR2        (((volatile __bitf_T *)0xFFFFA1C7)->bit07)
__IOREG(ICRLIN35, 0xFFFFA1C8, __READ_WRITE, uint16);
__IOREG(ICRLIN35L, 0xFFFFA1C8, __READ_WRITE, uint8);
__IOREG(ICRLIN35H, 0xFFFFA1C9, __READ_WRITE, uint8);
#define P0RLIN35           (((volatile __bitf_T *)0xFFFFA1C8)->bit00)
#define P1RLIN35           (((volatile __bitf_T *)0xFFFFA1C8)->bit01)
#define P2RLIN35           (((volatile __bitf_T *)0xFFFFA1C8)->bit02)
#define TBRLIN35           (((volatile __bitf_T *)0xFFFFA1C8)->bit06)
#define MKRLIN35           (((volatile __bitf_T *)0xFFFFA1C8)->bit07)
#define RFRLIN35           (((volatile __bitf_T *)0xFFFFA1C9)->bit04)
#define CTRLIN35           (((volatile __bitf_T *)0xFFFFA1C9)->bit07)
__IOREG(ICRLIN35UR0, 0xFFFFA1CA, __READ_WRITE, uint16);
__IOREG(ICRLIN35UR0L, 0xFFFFA1CA, __READ_WRITE, uint8);
__IOREG(ICRLIN35UR0H, 0xFFFFA1CB, __READ_WRITE, uint8);
#define P0RLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CA)->bit00)
#define P1RLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CA)->bit01)
#define P2RLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CA)->bit02)
#define TBRLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CA)->bit06)
#define MKRLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CA)->bit07)
#define RFRLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CB)->bit04)
#define CTRLIN35UR0        (((volatile __bitf_T *)0xFFFFA1CB)->bit07)
__IOREG(ICRLIN35UR1, 0xFFFFA1CC, __READ_WRITE, uint16);
__IOREG(ICRLIN35UR1L, 0xFFFFA1CC, __READ_WRITE, uint8);
__IOREG(ICRLIN35UR1H, 0xFFFFA1CD, __READ_WRITE, uint8);
#define P0RLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CC)->bit00)
#define P1RLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CC)->bit01)
#define P2RLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CC)->bit02)
#define TBRLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CC)->bit06)
#define MKRLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CC)->bit07)
#define RFRLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CD)->bit04)
#define CTRLIN35UR1        (((volatile __bitf_T *)0xFFFFA1CD)->bit07)
__IOREG(ICRLIN35UR2, 0xFFFFA1CE, __READ_WRITE, uint16);
__IOREG(ICRLIN35UR2L, 0xFFFFA1CE, __READ_WRITE, uint8);
__IOREG(ICRLIN35UR2H, 0xFFFFA1CF, __READ_WRITE, uint8);
#define P0RLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CE)->bit00)
#define P1RLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CE)->bit01)
#define P2RLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CE)->bit02)
#define TBRLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CE)->bit06)
#define MKRLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CE)->bit07)
#define RFRLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CF)->bit04)
#define CTRLIN35UR2        (((volatile __bitf_T *)0xFFFFA1CF)->bit07)
__IOREG(ICPWGA48, 0xFFFFA1D0, __READ_WRITE, uint16);
__IOREG(ICPWGA48L, 0xFFFFA1D0, __READ_WRITE, uint8);
__IOREG(ICPWGA48H, 0xFFFFA1D1, __READ_WRITE, uint8);
#define P0PWGA48           (((volatile __bitf_T *)0xFFFFA1D0)->bit00)
#define P1PWGA48           (((volatile __bitf_T *)0xFFFFA1D0)->bit01)
#define P2PWGA48           (((volatile __bitf_T *)0xFFFFA1D0)->bit02)
#define TBPWGA48           (((volatile __bitf_T *)0xFFFFA1D0)->bit06)
#define MKPWGA48           (((volatile __bitf_T *)0xFFFFA1D0)->bit07)
#define RFPWGA48           (((volatile __bitf_T *)0xFFFFA1D1)->bit04)
#define CTPWGA48           (((volatile __bitf_T *)0xFFFFA1D1)->bit07)
__IOREG(ICPWGA49, 0xFFFFA1D2, __READ_WRITE, uint16);
__IOREG(ICPWGA49L, 0xFFFFA1D2, __READ_WRITE, uint8);
__IOREG(ICPWGA49H, 0xFFFFA1D3, __READ_WRITE, uint8);
#define P0PWGA49           (((volatile __bitf_T *)0xFFFFA1D2)->bit00)
#define P1PWGA49           (((volatile __bitf_T *)0xFFFFA1D2)->bit01)
#define P2PWGA49           (((volatile __bitf_T *)0xFFFFA1D2)->bit02)
#define TBPWGA49           (((volatile __bitf_T *)0xFFFFA1D2)->bit06)
#define MKPWGA49           (((volatile __bitf_T *)0xFFFFA1D2)->bit07)
#define RFPWGA49           (((volatile __bitf_T *)0xFFFFA1D3)->bit04)
#define CTPWGA49           (((volatile __bitf_T *)0xFFFFA1D3)->bit07)
__IOREG(ICPWGA50, 0xFFFFA1D4, __READ_WRITE, uint16);
__IOREG(ICPWGA50L, 0xFFFFA1D4, __READ_WRITE, uint8);
__IOREG(ICPWGA50H, 0xFFFFA1D5, __READ_WRITE, uint8);
#define P0PWGA50           (((volatile __bitf_T *)0xFFFFA1D4)->bit00)
#define P1PWGA50           (((volatile __bitf_T *)0xFFFFA1D4)->bit01)
#define P2PWGA50           (((volatile __bitf_T *)0xFFFFA1D4)->bit02)
#define TBPWGA50           (((volatile __bitf_T *)0xFFFFA1D4)->bit06)
#define MKPWGA50           (((volatile __bitf_T *)0xFFFFA1D4)->bit07)
#define RFPWGA50           (((volatile __bitf_T *)0xFFFFA1D5)->bit04)
#define CTPWGA50           (((volatile __bitf_T *)0xFFFFA1D5)->bit07)
__IOREG(ICPWGA51, 0xFFFFA1D6, __READ_WRITE, uint16);
__IOREG(ICPWGA51L, 0xFFFFA1D6, __READ_WRITE, uint8);
__IOREG(ICPWGA51H, 0xFFFFA1D7, __READ_WRITE, uint8);
#define P0PWGA51           (((volatile __bitf_T *)0xFFFFA1D6)->bit00)
#define P1PWGA51           (((volatile __bitf_T *)0xFFFFA1D6)->bit01)
#define P2PWGA51           (((volatile __bitf_T *)0xFFFFA1D6)->bit02)
#define TBPWGA51           (((volatile __bitf_T *)0xFFFFA1D6)->bit06)
#define MKPWGA51           (((volatile __bitf_T *)0xFFFFA1D6)->bit07)
#define RFPWGA51           (((volatile __bitf_T *)0xFFFFA1D7)->bit04)
#define CTPWGA51           (((volatile __bitf_T *)0xFFFFA1D7)->bit07)
__IOREG(ICPWGA52, 0xFFFFA1D8, __READ_WRITE, uint16);
__IOREG(ICPWGA52L, 0xFFFFA1D8, __READ_WRITE, uint8);
__IOREG(ICPWGA52H, 0xFFFFA1D9, __READ_WRITE, uint8);
#define P0PWGA52           (((volatile __bitf_T *)0xFFFFA1D8)->bit00)
#define P1PWGA52           (((volatile __bitf_T *)0xFFFFA1D8)->bit01)
#define P2PWGA52           (((volatile __bitf_T *)0xFFFFA1D8)->bit02)
#define TBPWGA52           (((volatile __bitf_T *)0xFFFFA1D8)->bit06)
#define MKPWGA52           (((volatile __bitf_T *)0xFFFFA1D8)->bit07)
#define RFPWGA52           (((volatile __bitf_T *)0xFFFFA1D9)->bit04)
#define CTPWGA52           (((volatile __bitf_T *)0xFFFFA1D9)->bit07)
__IOREG(ICPWGA53, 0xFFFFA1DA, __READ_WRITE, uint16);
__IOREG(ICPWGA53L, 0xFFFFA1DA, __READ_WRITE, uint8);
__IOREG(ICPWGA53H, 0xFFFFA1DB, __READ_WRITE, uint8);
#define P0PWGA53           (((volatile __bitf_T *)0xFFFFA1DA)->bit00)
#define P1PWGA53           (((volatile __bitf_T *)0xFFFFA1DA)->bit01)
#define P2PWGA53           (((volatile __bitf_T *)0xFFFFA1DA)->bit02)
#define TBPWGA53           (((volatile __bitf_T *)0xFFFFA1DA)->bit06)
#define MKPWGA53           (((volatile __bitf_T *)0xFFFFA1DA)->bit07)
#define RFPWGA53           (((volatile __bitf_T *)0xFFFFA1DB)->bit04)
#define CTPWGA53           (((volatile __bitf_T *)0xFFFFA1DB)->bit07)
__IOREG(ICPWGA54, 0xFFFFA1DC, __READ_WRITE, uint16);
__IOREG(ICPWGA54L, 0xFFFFA1DC, __READ_WRITE, uint8);
__IOREG(ICPWGA54H, 0xFFFFA1DD, __READ_WRITE, uint8);
#define P0PWGA54           (((volatile __bitf_T *)0xFFFFA1DC)->bit00)
#define P1PWGA54           (((volatile __bitf_T *)0xFFFFA1DC)->bit01)
#define P2PWGA54           (((volatile __bitf_T *)0xFFFFA1DC)->bit02)
#define TBPWGA54           (((volatile __bitf_T *)0xFFFFA1DC)->bit06)
#define MKPWGA54           (((volatile __bitf_T *)0xFFFFA1DC)->bit07)
#define RFPWGA54           (((volatile __bitf_T *)0xFFFFA1DD)->bit04)
#define CTPWGA54           (((volatile __bitf_T *)0xFFFFA1DD)->bit07)
__IOREG(ICPWGA55, 0xFFFFA1DE, __READ_WRITE, uint16);
__IOREG(ICPWGA55L, 0xFFFFA1DE, __READ_WRITE, uint8);
__IOREG(ICPWGA55H, 0xFFFFA1DF, __READ_WRITE, uint8);
#define P0PWGA55           (((volatile __bitf_T *)0xFFFFA1DE)->bit00)
#define P1PWGA55           (((volatile __bitf_T *)0xFFFFA1DE)->bit01)
#define P2PWGA55           (((volatile __bitf_T *)0xFFFFA1DE)->bit02)
#define TBPWGA55           (((volatile __bitf_T *)0xFFFFA1DE)->bit06)
#define MKPWGA55           (((volatile __bitf_T *)0xFFFFA1DE)->bit07)
#define RFPWGA55           (((volatile __bitf_T *)0xFFFFA1DF)->bit04)
#define CTPWGA55           (((volatile __bitf_T *)0xFFFFA1DF)->bit07)
__IOREG(ICPWGA56, 0xFFFFA1E0, __READ_WRITE, uint16);
__IOREG(ICPWGA56L, 0xFFFFA1E0, __READ_WRITE, uint8);
__IOREG(ICPWGA56H, 0xFFFFA1E1, __READ_WRITE, uint8);
#define P0PWGA56           (((volatile __bitf_T *)0xFFFFA1E0)->bit00)
#define P1PWGA56           (((volatile __bitf_T *)0xFFFFA1E0)->bit01)
#define P2PWGA56           (((volatile __bitf_T *)0xFFFFA1E0)->bit02)
#define TBPWGA56           (((volatile __bitf_T *)0xFFFFA1E0)->bit06)
#define MKPWGA56           (((volatile __bitf_T *)0xFFFFA1E0)->bit07)
#define RFPWGA56           (((volatile __bitf_T *)0xFFFFA1E1)->bit04)
#define CTPWGA56           (((volatile __bitf_T *)0xFFFFA1E1)->bit07)
__IOREG(ICPWGA57, 0xFFFFA1E2, __READ_WRITE, uint16);
__IOREG(ICPWGA57L, 0xFFFFA1E2, __READ_WRITE, uint8);
__IOREG(ICPWGA57H, 0xFFFFA1E3, __READ_WRITE, uint8);
#define P0PWGA57           (((volatile __bitf_T *)0xFFFFA1E2)->bit00)
#define P1PWGA57           (((volatile __bitf_T *)0xFFFFA1E2)->bit01)
#define P2PWGA57           (((volatile __bitf_T *)0xFFFFA1E2)->bit02)
#define TBPWGA57           (((volatile __bitf_T *)0xFFFFA1E2)->bit06)
#define MKPWGA57           (((volatile __bitf_T *)0xFFFFA1E2)->bit07)
#define RFPWGA57           (((volatile __bitf_T *)0xFFFFA1E3)->bit04)
#define CTPWGA57           (((volatile __bitf_T *)0xFFFFA1E3)->bit07)
__IOREG(ICPWGA58, 0xFFFFA1E4, __READ_WRITE, uint16);
__IOREG(ICPWGA58L, 0xFFFFA1E4, __READ_WRITE, uint8);
__IOREG(ICPWGA58H, 0xFFFFA1E5, __READ_WRITE, uint8);
#define P0PWGA58           (((volatile __bitf_T *)0xFFFFA1E4)->bit00)
#define P1PWGA58           (((volatile __bitf_T *)0xFFFFA1E4)->bit01)
#define P2PWGA58           (((volatile __bitf_T *)0xFFFFA1E4)->bit02)
#define TBPWGA58           (((volatile __bitf_T *)0xFFFFA1E4)->bit06)
#define MKPWGA58           (((volatile __bitf_T *)0xFFFFA1E4)->bit07)
#define RFPWGA58           (((volatile __bitf_T *)0xFFFFA1E5)->bit04)
#define CTPWGA58           (((volatile __bitf_T *)0xFFFFA1E5)->bit07)
__IOREG(ICPWGA59, 0xFFFFA1E6, __READ_WRITE, uint16);
__IOREG(ICPWGA59L, 0xFFFFA1E6, __READ_WRITE, uint8);
__IOREG(ICPWGA59H, 0xFFFFA1E7, __READ_WRITE, uint8);
#define P0PWGA59           (((volatile __bitf_T *)0xFFFFA1E6)->bit00)
#define P1PWGA59           (((volatile __bitf_T *)0xFFFFA1E6)->bit01)
#define P2PWGA59           (((volatile __bitf_T *)0xFFFFA1E6)->bit02)
#define TBPWGA59           (((volatile __bitf_T *)0xFFFFA1E6)->bit06)
#define MKPWGA59           (((volatile __bitf_T *)0xFFFFA1E6)->bit07)
#define RFPWGA59           (((volatile __bitf_T *)0xFFFFA1E7)->bit04)
#define CTPWGA59           (((volatile __bitf_T *)0xFFFFA1E7)->bit07)
__IOREG(ICPWGA60, 0xFFFFA1E8, __READ_WRITE, uint16);
__IOREG(ICPWGA60L, 0xFFFFA1E8, __READ_WRITE, uint8);
__IOREG(ICPWGA60H, 0xFFFFA1E9, __READ_WRITE, uint8);
#define P0PWGA60           (((volatile __bitf_T *)0xFFFFA1E8)->bit00)
#define P1PWGA60           (((volatile __bitf_T *)0xFFFFA1E8)->bit01)
#define P2PWGA60           (((volatile __bitf_T *)0xFFFFA1E8)->bit02)
#define TBPWGA60           (((volatile __bitf_T *)0xFFFFA1E8)->bit06)
#define MKPWGA60           (((volatile __bitf_T *)0xFFFFA1E8)->bit07)
#define RFPWGA60           (((volatile __bitf_T *)0xFFFFA1E9)->bit04)
#define CTPWGA60           (((volatile __bitf_T *)0xFFFFA1E9)->bit07)
__IOREG(ICPWGA61, 0xFFFFA1EA, __READ_WRITE, uint16);
__IOREG(ICPWGA61L, 0xFFFFA1EA, __READ_WRITE, uint8);
__IOREG(ICPWGA61H, 0xFFFFA1EB, __READ_WRITE, uint8);
#define P0PWGA61           (((volatile __bitf_T *)0xFFFFA1EA)->bit00)
#define P1PWGA61           (((volatile __bitf_T *)0xFFFFA1EA)->bit01)
#define P2PWGA61           (((volatile __bitf_T *)0xFFFFA1EA)->bit02)
#define TBPWGA61           (((volatile __bitf_T *)0xFFFFA1EA)->bit06)
#define MKPWGA61           (((volatile __bitf_T *)0xFFFFA1EA)->bit07)
#define RFPWGA61           (((volatile __bitf_T *)0xFFFFA1EB)->bit04)
#define CTPWGA61           (((volatile __bitf_T *)0xFFFFA1EB)->bit07)
__IOREG(ICPWGA62, 0xFFFFA1EC, __READ_WRITE, uint16);
__IOREG(ICPWGA62L, 0xFFFFA1EC, __READ_WRITE, uint8);
__IOREG(ICPWGA62H, 0xFFFFA1ED, __READ_WRITE, uint8);
#define P0PWGA62           (((volatile __bitf_T *)0xFFFFA1EC)->bit00)
#define P1PWGA62           (((volatile __bitf_T *)0xFFFFA1EC)->bit01)
#define P2PWGA62           (((volatile __bitf_T *)0xFFFFA1EC)->bit02)
#define TBPWGA62           (((volatile __bitf_T *)0xFFFFA1EC)->bit06)
#define MKPWGA62           (((volatile __bitf_T *)0xFFFFA1EC)->bit07)
#define RFPWGA62           (((volatile __bitf_T *)0xFFFFA1ED)->bit04)
#define CTPWGA62           (((volatile __bitf_T *)0xFFFFA1ED)->bit07)
__IOREG(ICPWGA63, 0xFFFFA1EE, __READ_WRITE, uint16);
__IOREG(ICPWGA63L, 0xFFFFA1EE, __READ_WRITE, uint8);
__IOREG(ICPWGA63H, 0xFFFFA1EF, __READ_WRITE, uint8);
#define P0PWGA63           (((volatile __bitf_T *)0xFFFFA1EE)->bit00)
#define P1PWGA63           (((volatile __bitf_T *)0xFFFFA1EE)->bit01)
#define P2PWGA63           (((volatile __bitf_T *)0xFFFFA1EE)->bit02)
#define TBPWGA63           (((volatile __bitf_T *)0xFFFFA1EE)->bit06)
#define MKPWGA63           (((volatile __bitf_T *)0xFFFFA1EE)->bit07)
#define RFPWGA63           (((volatile __bitf_T *)0xFFFFA1EF)->bit04)
#define CTPWGA63           (((volatile __bitf_T *)0xFFFFA1EF)->bit07)
__IOREG(ICTAUB1I0, 0xFFFFA1F0, __READ_WRITE, uint16);
__IOREG(ICTAUB1I0L, 0xFFFFA1F0, __READ_WRITE, uint8);
__IOREG(ICTAUB1I0H, 0xFFFFA1F1, __READ_WRITE, uint8);
#define P0TAUB1I0          (((volatile __bitf_T *)0xFFFFA1F0)->bit00)
#define P1TAUB1I0          (((volatile __bitf_T *)0xFFFFA1F0)->bit01)
#define P2TAUB1I0          (((volatile __bitf_T *)0xFFFFA1F0)->bit02)
#define TBTAUB1I0          (((volatile __bitf_T *)0xFFFFA1F0)->bit06)
#define MKTAUB1I0          (((volatile __bitf_T *)0xFFFFA1F0)->bit07)
#define RFTAUB1I0          (((volatile __bitf_T *)0xFFFFA1F1)->bit04)
#define CTTAUB1I0          (((volatile __bitf_T *)0xFFFFA1F1)->bit07)
__IOREG(ICTAUB1I1, 0xFFFFA1F2, __READ_WRITE, uint16);
__IOREG(ICTAUB1I1L, 0xFFFFA1F2, __READ_WRITE, uint8);
__IOREG(ICTAUB1I1H, 0xFFFFA1F3, __READ_WRITE, uint8);
#define P0TAUB1I1          (((volatile __bitf_T *)0xFFFFA1F2)->bit00)
#define P1TAUB1I1          (((volatile __bitf_T *)0xFFFFA1F2)->bit01)
#define P2TAUB1I1          (((volatile __bitf_T *)0xFFFFA1F2)->bit02)
#define TBTAUB1I1          (((volatile __bitf_T *)0xFFFFA1F2)->bit06)
#define MKTAUB1I1          (((volatile __bitf_T *)0xFFFFA1F2)->bit07)
#define RFTAUB1I1          (((volatile __bitf_T *)0xFFFFA1F3)->bit04)
#define CTTAUB1I1          (((volatile __bitf_T *)0xFFFFA1F3)->bit07)
__IOREG(ICTAUB1I2, 0xFFFFA1F4, __READ_WRITE, uint16);
__IOREG(ICTAUB1I2L, 0xFFFFA1F4, __READ_WRITE, uint8);
__IOREG(ICTAUB1I2H, 0xFFFFA1F5, __READ_WRITE, uint8);
#define P0TAUB1I2          (((volatile __bitf_T *)0xFFFFA1F4)->bit00)
#define P1TAUB1I2          (((volatile __bitf_T *)0xFFFFA1F4)->bit01)
#define P2TAUB1I2          (((volatile __bitf_T *)0xFFFFA1F4)->bit02)
#define TBTAUB1I2          (((volatile __bitf_T *)0xFFFFA1F4)->bit06)
#define MKTAUB1I2          (((volatile __bitf_T *)0xFFFFA1F4)->bit07)
#define RFTAUB1I2          (((volatile __bitf_T *)0xFFFFA1F5)->bit04)
#define CTTAUB1I2          (((volatile __bitf_T *)0xFFFFA1F5)->bit07)
__IOREG(ICTAUB1I3, 0xFFFFA1F6, __READ_WRITE, uint16);
__IOREG(ICTAUB1I3L, 0xFFFFA1F6, __READ_WRITE, uint8);
__IOREG(ICTAUB1I3H, 0xFFFFA1F7, __READ_WRITE, uint8);
#define P0TAUB1I3          (((volatile __bitf_T *)0xFFFFA1F6)->bit00)
#define P1TAUB1I3          (((volatile __bitf_T *)0xFFFFA1F6)->bit01)
#define P2TAUB1I3          (((volatile __bitf_T *)0xFFFFA1F6)->bit02)
#define TBTAUB1I3          (((volatile __bitf_T *)0xFFFFA1F6)->bit06)
#define MKTAUB1I3          (((volatile __bitf_T *)0xFFFFA1F6)->bit07)
#define RFTAUB1I3          (((volatile __bitf_T *)0xFFFFA1F7)->bit04)
#define CTTAUB1I3          (((volatile __bitf_T *)0xFFFFA1F7)->bit07)
__IOREG(ICTAUB1I4, 0xFFFFA1F8, __READ_WRITE, uint16);
__IOREG(ICTAUB1I4L, 0xFFFFA1F8, __READ_WRITE, uint8);
__IOREG(ICTAUB1I4H, 0xFFFFA1F9, __READ_WRITE, uint8);
#define P0TAUB1I4          (((volatile __bitf_T *)0xFFFFA1F8)->bit00)
#define P1TAUB1I4          (((volatile __bitf_T *)0xFFFFA1F8)->bit01)
#define P2TAUB1I4          (((volatile __bitf_T *)0xFFFFA1F8)->bit02)
#define TBTAUB1I4          (((volatile __bitf_T *)0xFFFFA1F8)->bit06)
#define MKTAUB1I4          (((volatile __bitf_T *)0xFFFFA1F8)->bit07)
#define RFTAUB1I4          (((volatile __bitf_T *)0xFFFFA1F9)->bit04)
#define CTTAUB1I4          (((volatile __bitf_T *)0xFFFFA1F9)->bit07)
__IOREG(ICTAUB1I5, 0xFFFFA1FA, __READ_WRITE, uint16);
__IOREG(ICTAUB1I5L, 0xFFFFA1FA, __READ_WRITE, uint8);
__IOREG(ICTAUB1I5H, 0xFFFFA1FB, __READ_WRITE, uint8);
#define P0TAUB1I5          (((volatile __bitf_T *)0xFFFFA1FA)->bit00)
#define P1TAUB1I5          (((volatile __bitf_T *)0xFFFFA1FA)->bit01)
#define P2TAUB1I5          (((volatile __bitf_T *)0xFFFFA1FA)->bit02)
#define TBTAUB1I5          (((volatile __bitf_T *)0xFFFFA1FA)->bit06)
#define MKTAUB1I5          (((volatile __bitf_T *)0xFFFFA1FA)->bit07)
#define RFTAUB1I5          (((volatile __bitf_T *)0xFFFFA1FB)->bit04)
#define CTTAUB1I5          (((volatile __bitf_T *)0xFFFFA1FB)->bit07)
__IOREG(ICTAUB1I6, 0xFFFFA1FC, __READ_WRITE, uint16);
__IOREG(ICTAUB1I6L, 0xFFFFA1FC, __READ_WRITE, uint8);
__IOREG(ICTAUB1I6H, 0xFFFFA1FD, __READ_WRITE, uint8);
#define P0TAUB1I6          (((volatile __bitf_T *)0xFFFFA1FC)->bit00)
#define P1TAUB1I6          (((volatile __bitf_T *)0xFFFFA1FC)->bit01)
#define P2TAUB1I6          (((volatile __bitf_T *)0xFFFFA1FC)->bit02)
#define TBTAUB1I6          (((volatile __bitf_T *)0xFFFFA1FC)->bit06)
#define MKTAUB1I6          (((volatile __bitf_T *)0xFFFFA1FC)->bit07)
#define RFTAUB1I6          (((volatile __bitf_T *)0xFFFFA1FD)->bit04)
#define CTTAUB1I6          (((volatile __bitf_T *)0xFFFFA1FD)->bit07)
__IOREG(ICTAUB1I7, 0xFFFFA1FE, __READ_WRITE, uint16);
__IOREG(ICTAUB1I7L, 0xFFFFA1FE, __READ_WRITE, uint8);
__IOREG(ICTAUB1I7H, 0xFFFFA1FF, __READ_WRITE, uint8);
#define P0TAUB1I7          (((volatile __bitf_T *)0xFFFFA1FE)->bit00)
#define P1TAUB1I7          (((volatile __bitf_T *)0xFFFFA1FE)->bit01)
#define P2TAUB1I7          (((volatile __bitf_T *)0xFFFFA1FE)->bit02)
#define TBTAUB1I7          (((volatile __bitf_T *)0xFFFFA1FE)->bit06)
#define MKTAUB1I7          (((volatile __bitf_T *)0xFFFFA1FE)->bit07)
#define RFTAUB1I7          (((volatile __bitf_T *)0xFFFFA1FF)->bit04)
#define CTTAUB1I7          (((volatile __bitf_T *)0xFFFFA1FF)->bit07)
__IOREG(ICTAUB1I8, 0xFFFFA200, __READ_WRITE, uint16);
__IOREG(ICTAUB1I8L, 0xFFFFA200, __READ_WRITE, uint8);
__IOREG(ICTAUB1I8H, 0xFFFFA201, __READ_WRITE, uint8);
#define P0TAUB1I8          (((volatile __bitf_T *)0xFFFFA200)->bit00)
#define P1TAUB1I8          (((volatile __bitf_T *)0xFFFFA200)->bit01)
#define P2TAUB1I8          (((volatile __bitf_T *)0xFFFFA200)->bit02)
#define TBTAUB1I8          (((volatile __bitf_T *)0xFFFFA200)->bit06)
#define MKTAUB1I8          (((volatile __bitf_T *)0xFFFFA200)->bit07)
#define RFTAUB1I8          (((volatile __bitf_T *)0xFFFFA201)->bit04)
#define CTTAUB1I8          (((volatile __bitf_T *)0xFFFFA201)->bit07)
__IOREG(ICTAUB1I9, 0xFFFFA202, __READ_WRITE, uint16);
__IOREG(ICTAUB1I9L, 0xFFFFA202, __READ_WRITE, uint8);
__IOREG(ICTAUB1I9H, 0xFFFFA203, __READ_WRITE, uint8);
#define P0TAUB1I9          (((volatile __bitf_T *)0xFFFFA202)->bit00)
#define P1TAUB1I9          (((volatile __bitf_T *)0xFFFFA202)->bit01)
#define P2TAUB1I9          (((volatile __bitf_T *)0xFFFFA202)->bit02)
#define TBTAUB1I9          (((volatile __bitf_T *)0xFFFFA202)->bit06)
#define MKTAUB1I9          (((volatile __bitf_T *)0xFFFFA202)->bit07)
#define RFTAUB1I9          (((volatile __bitf_T *)0xFFFFA203)->bit04)
#define CTTAUB1I9          (((volatile __bitf_T *)0xFFFFA203)->bit07)
__IOREG(ICTAUB1I10, 0xFFFFA204, __READ_WRITE, uint16);
__IOREG(ICTAUB1I10L, 0xFFFFA204, __READ_WRITE, uint8);
__IOREG(ICTAUB1I10H, 0xFFFFA205, __READ_WRITE, uint8);
#define P0TAUB1I10         (((volatile __bitf_T *)0xFFFFA204)->bit00)
#define P1TAUB1I10         (((volatile __bitf_T *)0xFFFFA204)->bit01)
#define P2TAUB1I10         (((volatile __bitf_T *)0xFFFFA204)->bit02)
#define TBTAUB1I10         (((volatile __bitf_T *)0xFFFFA204)->bit06)
#define MKTAUB1I10         (((volatile __bitf_T *)0xFFFFA204)->bit07)
#define RFTAUB1I10         (((volatile __bitf_T *)0xFFFFA205)->bit04)
#define CTTAUB1I10         (((volatile __bitf_T *)0xFFFFA205)->bit07)
__IOREG(ICTAUB1I11, 0xFFFFA206, __READ_WRITE, uint16);
__IOREG(ICTAUB1I11L, 0xFFFFA206, __READ_WRITE, uint8);
__IOREG(ICTAUB1I11H, 0xFFFFA207, __READ_WRITE, uint8);
#define P0TAUB1I11         (((volatile __bitf_T *)0xFFFFA206)->bit00)
#define P1TAUB1I11         (((volatile __bitf_T *)0xFFFFA206)->bit01)
#define P2TAUB1I11         (((volatile __bitf_T *)0xFFFFA206)->bit02)
#define TBTAUB1I11         (((volatile __bitf_T *)0xFFFFA206)->bit06)
#define MKTAUB1I11         (((volatile __bitf_T *)0xFFFFA206)->bit07)
#define RFTAUB1I11         (((volatile __bitf_T *)0xFFFFA207)->bit04)
#define CTTAUB1I11         (((volatile __bitf_T *)0xFFFFA207)->bit07)
__IOREG(ICTAUB1I12, 0xFFFFA208, __READ_WRITE, uint16);
__IOREG(ICTAUB1I12L, 0xFFFFA208, __READ_WRITE, uint8);
__IOREG(ICTAUB1I12H, 0xFFFFA209, __READ_WRITE, uint8);
#define P0TAUB1I12         (((volatile __bitf_T *)0xFFFFA208)->bit00)
#define P1TAUB1I12         (((volatile __bitf_T *)0xFFFFA208)->bit01)
#define P2TAUB1I12         (((volatile __bitf_T *)0xFFFFA208)->bit02)
#define TBTAUB1I12         (((volatile __bitf_T *)0xFFFFA208)->bit06)
#define MKTAUB1I12         (((volatile __bitf_T *)0xFFFFA208)->bit07)
#define RFTAUB1I12         (((volatile __bitf_T *)0xFFFFA209)->bit04)
#define CTTAUB1I12         (((volatile __bitf_T *)0xFFFFA209)->bit07)
__IOREG(ICTAUB1I13, 0xFFFFA20A, __READ_WRITE, uint16);
__IOREG(ICTAUB1I13L, 0xFFFFA20A, __READ_WRITE, uint8);
__IOREG(ICTAUB1I13H, 0xFFFFA20B, __READ_WRITE, uint8);
#define P0TAUB1I13         (((volatile __bitf_T *)0xFFFFA20A)->bit00)
#define P1TAUB1I13         (((volatile __bitf_T *)0xFFFFA20A)->bit01)
#define P2TAUB1I13         (((volatile __bitf_T *)0xFFFFA20A)->bit02)
#define TBTAUB1I13         (((volatile __bitf_T *)0xFFFFA20A)->bit06)
#define MKTAUB1I13         (((volatile __bitf_T *)0xFFFFA20A)->bit07)
#define RFTAUB1I13         (((volatile __bitf_T *)0xFFFFA20B)->bit04)
#define CTTAUB1I13         (((volatile __bitf_T *)0xFFFFA20B)->bit07)
__IOREG(ICTAUB1I14, 0xFFFFA20C, __READ_WRITE, uint16);
__IOREG(ICTAUB1I14L, 0xFFFFA20C, __READ_WRITE, uint8);
__IOREG(ICTAUB1I14H, 0xFFFFA20D, __READ_WRITE, uint8);
#define P0TAUB1I14         (((volatile __bitf_T *)0xFFFFA20C)->bit00)
#define P1TAUB1I14         (((volatile __bitf_T *)0xFFFFA20C)->bit01)
#define P2TAUB1I14         (((volatile __bitf_T *)0xFFFFA20C)->bit02)
#define TBTAUB1I14         (((volatile __bitf_T *)0xFFFFA20C)->bit06)
#define MKTAUB1I14         (((volatile __bitf_T *)0xFFFFA20C)->bit07)
#define RFTAUB1I14         (((volatile __bitf_T *)0xFFFFA20D)->bit04)
#define CTTAUB1I14         (((volatile __bitf_T *)0xFFFFA20D)->bit07)
__IOREG(ICTAUB1I15, 0xFFFFA20E, __READ_WRITE, uint16);
__IOREG(ICTAUB1I15L, 0xFFFFA20E, __READ_WRITE, uint8);
__IOREG(ICTAUB1I15H, 0xFFFFA20F, __READ_WRITE, uint8);
#define P0TAUB1I15         (((volatile __bitf_T *)0xFFFFA20E)->bit00)
#define P1TAUB1I15         (((volatile __bitf_T *)0xFFFFA20E)->bit01)
#define P2TAUB1I15         (((volatile __bitf_T *)0xFFFFA20E)->bit02)
#define TBTAUB1I15         (((volatile __bitf_T *)0xFFFFA20E)->bit06)
#define MKTAUB1I15         (((volatile __bitf_T *)0xFFFFA20E)->bit07)
#define RFTAUB1I15         (((volatile __bitf_T *)0xFFFFA20F)->bit04)
#define CTTAUB1I15         (((volatile __bitf_T *)0xFFFFA20F)->bit07)
__IOREG(ICRCAN4ERR, 0xFFFFA210, __READ_WRITE, uint16);
__IOREG(ICRCAN4ERRL, 0xFFFFA210, __READ_WRITE, uint8);
__IOREG(ICRCAN4ERRH, 0xFFFFA211, __READ_WRITE, uint8);
#define P0RCAN4ERR         (((volatile __bitf_T *)0xFFFFA210)->bit00)
#define P1RCAN4ERR         (((volatile __bitf_T *)0xFFFFA210)->bit01)
#define P2RCAN4ERR         (((volatile __bitf_T *)0xFFFFA210)->bit02)
#define TBRCAN4ERR         (((volatile __bitf_T *)0xFFFFA210)->bit06)
#define MKRCAN4ERR         (((volatile __bitf_T *)0xFFFFA210)->bit07)
#define RFRCAN4ERR         (((volatile __bitf_T *)0xFFFFA211)->bit04)
#define CTRCAN4ERR         (((volatile __bitf_T *)0xFFFFA211)->bit07)
__IOREG(ICRCAN4REC, 0xFFFFA212, __READ_WRITE, uint16);
__IOREG(ICRCAN4RECL, 0xFFFFA212, __READ_WRITE, uint8);
__IOREG(ICRCAN4RECH, 0xFFFFA213, __READ_WRITE, uint8);
#define P0RCAN4REC         (((volatile __bitf_T *)0xFFFFA212)->bit00)
#define P1RCAN4REC         (((volatile __bitf_T *)0xFFFFA212)->bit01)
#define P2RCAN4REC         (((volatile __bitf_T *)0xFFFFA212)->bit02)
#define TBRCAN4REC         (((volatile __bitf_T *)0xFFFFA212)->bit06)
#define MKRCAN4REC         (((volatile __bitf_T *)0xFFFFA212)->bit07)
#define RFRCAN4REC         (((volatile __bitf_T *)0xFFFFA213)->bit04)
#define CTRCAN4REC         (((volatile __bitf_T *)0xFFFFA213)->bit07)
__IOREG(ICRCAN4TRX, 0xFFFFA214, __READ_WRITE, uint16);
__IOREG(ICRCAN4TRXL, 0xFFFFA214, __READ_WRITE, uint8);
__IOREG(ICRCAN4TRXH, 0xFFFFA215, __READ_WRITE, uint8);
#define P0RCAN4TRX         (((volatile __bitf_T *)0xFFFFA214)->bit00)
#define P1RCAN4TRX         (((volatile __bitf_T *)0xFFFFA214)->bit01)
#define P2RCAN4TRX         (((volatile __bitf_T *)0xFFFFA214)->bit02)
#define TBRCAN4TRX         (((volatile __bitf_T *)0xFFFFA214)->bit06)
#define MKRCAN4TRX         (((volatile __bitf_T *)0xFFFFA214)->bit07)
#define RFRCAN4TRX         (((volatile __bitf_T *)0xFFFFA215)->bit04)
#define CTRCAN4TRX         (((volatile __bitf_T *)0xFFFFA215)->bit07)
__IOREG(ICRLIN26, 0xFFFFA216, __READ_WRITE, uint16);
__IOREG(ICRLIN26L, 0xFFFFA216, __READ_WRITE, uint8);
__IOREG(ICRLIN26H, 0xFFFFA217, __READ_WRITE, uint8);
#define P0RLIN26           (((volatile __bitf_T *)0xFFFFA216)->bit00)
#define P1RLIN26           (((volatile __bitf_T *)0xFFFFA216)->bit01)
#define P2RLIN26           (((volatile __bitf_T *)0xFFFFA216)->bit02)
#define TBRLIN26           (((volatile __bitf_T *)0xFFFFA216)->bit06)
#define MKRLIN26           (((volatile __bitf_T *)0xFFFFA216)->bit07)
#define RFRLIN26           (((volatile __bitf_T *)0xFFFFA217)->bit04)
#define CTRLIN26           (((volatile __bitf_T *)0xFFFFA217)->bit07)
__IOREG(ICRLIN27, 0xFFFFA218, __READ_WRITE, uint16);
__IOREG(ICRLIN27L, 0xFFFFA218, __READ_WRITE, uint8);
__IOREG(ICRLIN27H, 0xFFFFA219, __READ_WRITE, uint8);
#define P0RLIN27           (((volatile __bitf_T *)0xFFFFA218)->bit00)
#define P1RLIN27           (((volatile __bitf_T *)0xFFFFA218)->bit01)
#define P2RLIN27           (((volatile __bitf_T *)0xFFFFA218)->bit02)
#define TBRLIN27           (((volatile __bitf_T *)0xFFFFA218)->bit06)
#define MKRLIN27           (((volatile __bitf_T *)0xFFFFA218)->bit07)
#define RFRLIN27           (((volatile __bitf_T *)0xFFFFA219)->bit04)
#define CTRLIN27           (((volatile __bitf_T *)0xFFFFA219)->bit07)
__IOREG(ICPWGA64, 0xFFFFA21A, __READ_WRITE, uint16);
__IOREG(ICPWGA64L, 0xFFFFA21A, __READ_WRITE, uint8);
__IOREG(ICPWGA64H, 0xFFFFA21B, __READ_WRITE, uint8);
#define P0PWGA64           (((volatile __bitf_T *)0xFFFFA21A)->bit00)
#define P1PWGA64           (((volatile __bitf_T *)0xFFFFA21A)->bit01)
#define P2PWGA64           (((volatile __bitf_T *)0xFFFFA21A)->bit02)
#define TBPWGA64           (((volatile __bitf_T *)0xFFFFA21A)->bit06)
#define MKPWGA64           (((volatile __bitf_T *)0xFFFFA21A)->bit07)
#define RFPWGA64           (((volatile __bitf_T *)0xFFFFA21B)->bit04)
#define CTPWGA64           (((volatile __bitf_T *)0xFFFFA21B)->bit07)
__IOREG(ICPWGA65, 0xFFFFA21C, __READ_WRITE, uint16);
__IOREG(ICPWGA65L, 0xFFFFA21C, __READ_WRITE, uint8);
__IOREG(ICPWGA65H, 0xFFFFA21D, __READ_WRITE, uint8);
#define P0PWGA65           (((volatile __bitf_T *)0xFFFFA21C)->bit00)
#define P1PWGA65           (((volatile __bitf_T *)0xFFFFA21C)->bit01)
#define P2PWGA65           (((volatile __bitf_T *)0xFFFFA21C)->bit02)
#define TBPWGA65           (((volatile __bitf_T *)0xFFFFA21C)->bit06)
#define MKPWGA65           (((volatile __bitf_T *)0xFFFFA21C)->bit07)
#define RFPWGA65           (((volatile __bitf_T *)0xFFFFA21D)->bit04)
#define CTPWGA65           (((volatile __bitf_T *)0xFFFFA21D)->bit07)
__IOREG(ICPWGA66, 0xFFFFA21E, __READ_WRITE, uint16);
__IOREG(ICPWGA66L, 0xFFFFA21E, __READ_WRITE, uint8);
__IOREG(ICPWGA66H, 0xFFFFA21F, __READ_WRITE, uint8);
#define P0PWGA66           (((volatile __bitf_T *)0xFFFFA21E)->bit00)
#define P1PWGA66           (((volatile __bitf_T *)0xFFFFA21E)->bit01)
#define P2PWGA66           (((volatile __bitf_T *)0xFFFFA21E)->bit02)
#define TBPWGA66           (((volatile __bitf_T *)0xFFFFA21E)->bit06)
#define MKPWGA66           (((volatile __bitf_T *)0xFFFFA21E)->bit07)
#define RFPWGA66           (((volatile __bitf_T *)0xFFFFA21F)->bit04)
#define CTPWGA66           (((volatile __bitf_T *)0xFFFFA21F)->bit07)
__IOREG(ICPWGA67, 0xFFFFA220, __READ_WRITE, uint16);
__IOREG(ICPWGA67L, 0xFFFFA220, __READ_WRITE, uint8);
__IOREG(ICPWGA67H, 0xFFFFA221, __READ_WRITE, uint8);
#define P0PWGA67           (((volatile __bitf_T *)0xFFFFA220)->bit00)
#define P1PWGA67           (((volatile __bitf_T *)0xFFFFA220)->bit01)
#define P2PWGA67           (((volatile __bitf_T *)0xFFFFA220)->bit02)
#define TBPWGA67           (((volatile __bitf_T *)0xFFFFA220)->bit06)
#define MKPWGA67           (((volatile __bitf_T *)0xFFFFA220)->bit07)
#define RFPWGA67           (((volatile __bitf_T *)0xFFFFA221)->bit04)
#define CTPWGA67           (((volatile __bitf_T *)0xFFFFA221)->bit07)
__IOREG(ICPWGA68, 0xFFFFA222, __READ_WRITE, uint16);
__IOREG(ICPWGA68L, 0xFFFFA222, __READ_WRITE, uint8);
__IOREG(ICPWGA68H, 0xFFFFA223, __READ_WRITE, uint8);
#define P0PWGA68           (((volatile __bitf_T *)0xFFFFA222)->bit00)
#define P1PWGA68           (((volatile __bitf_T *)0xFFFFA222)->bit01)
#define P2PWGA68           (((volatile __bitf_T *)0xFFFFA222)->bit02)
#define TBPWGA68           (((volatile __bitf_T *)0xFFFFA222)->bit06)
#define MKPWGA68           (((volatile __bitf_T *)0xFFFFA222)->bit07)
#define RFPWGA68           (((volatile __bitf_T *)0xFFFFA223)->bit04)
#define CTPWGA68           (((volatile __bitf_T *)0xFFFFA223)->bit07)
__IOREG(ICPWGA69, 0xFFFFA224, __READ_WRITE, uint16);
__IOREG(ICPWGA69L, 0xFFFFA224, __READ_WRITE, uint8);
__IOREG(ICPWGA69H, 0xFFFFA225, __READ_WRITE, uint8);
#define P0PWGA69           (((volatile __bitf_T *)0xFFFFA224)->bit00)
#define P1PWGA69           (((volatile __bitf_T *)0xFFFFA224)->bit01)
#define P2PWGA69           (((volatile __bitf_T *)0xFFFFA224)->bit02)
#define TBPWGA69           (((volatile __bitf_T *)0xFFFFA224)->bit06)
#define MKPWGA69           (((volatile __bitf_T *)0xFFFFA224)->bit07)
#define RFPWGA69           (((volatile __bitf_T *)0xFFFFA225)->bit04)
#define CTPWGA69           (((volatile __bitf_T *)0xFFFFA225)->bit07)
__IOREG(ICPWGA70, 0xFFFFA226, __READ_WRITE, uint16);
__IOREG(ICPWGA70L, 0xFFFFA226, __READ_WRITE, uint8);
__IOREG(ICPWGA70H, 0xFFFFA227, __READ_WRITE, uint8);
#define P0PWGA70           (((volatile __bitf_T *)0xFFFFA226)->bit00)
#define P1PWGA70           (((volatile __bitf_T *)0xFFFFA226)->bit01)
#define P2PWGA70           (((volatile __bitf_T *)0xFFFFA226)->bit02)
#define TBPWGA70           (((volatile __bitf_T *)0xFFFFA226)->bit06)
#define MKPWGA70           (((volatile __bitf_T *)0xFFFFA226)->bit07)
#define RFPWGA70           (((volatile __bitf_T *)0xFFFFA227)->bit04)
#define CTPWGA70           (((volatile __bitf_T *)0xFFFFA227)->bit07)
__IOREG(ICPWGA71, 0xFFFFA228, __READ_WRITE, uint16);
__IOREG(ICPWGA71L, 0xFFFFA228, __READ_WRITE, uint8);
__IOREG(ICPWGA71H, 0xFFFFA229, __READ_WRITE, uint8);
#define P0PWGA71           (((volatile __bitf_T *)0xFFFFA228)->bit00)
#define P1PWGA71           (((volatile __bitf_T *)0xFFFFA228)->bit01)
#define P2PWGA71           (((volatile __bitf_T *)0xFFFFA228)->bit02)
#define TBPWGA71           (((volatile __bitf_T *)0xFFFFA228)->bit06)
#define MKPWGA71           (((volatile __bitf_T *)0xFFFFA228)->bit07)
#define RFPWGA71           (((volatile __bitf_T *)0xFFFFA229)->bit04)
#define CTPWGA71           (((volatile __bitf_T *)0xFFFFA229)->bit07)
__IOREG(ICRLIN28, 0xFFFFA22A, __READ_WRITE, uint16);
__IOREG(ICRLIN28L, 0xFFFFA22A, __READ_WRITE, uint8);
__IOREG(ICRLIN28H, 0xFFFFA22B, __READ_WRITE, uint8);
#define P0RLIN28           (((volatile __bitf_T *)0xFFFFA22A)->bit00)
#define P1RLIN28           (((volatile __bitf_T *)0xFFFFA22A)->bit01)
#define P2RLIN28           (((volatile __bitf_T *)0xFFFFA22A)->bit02)
#define TBRLIN28           (((volatile __bitf_T *)0xFFFFA22A)->bit06)
#define MKRLIN28           (((volatile __bitf_T *)0xFFFFA22A)->bit07)
#define RFRLIN28           (((volatile __bitf_T *)0xFFFFA22B)->bit04)
#define CTRLIN28           (((volatile __bitf_T *)0xFFFFA22B)->bit07)
__IOREG(ICRLIN29, 0xFFFFA22C, __READ_WRITE, uint16);
__IOREG(ICRLIN29L, 0xFFFFA22C, __READ_WRITE, uint8);
__IOREG(ICRLIN29H, 0xFFFFA22D, __READ_WRITE, uint8);
#define P0RLIN29           (((volatile __bitf_T *)0xFFFFA22C)->bit00)
#define P1RLIN29           (((volatile __bitf_T *)0xFFFFA22C)->bit01)
#define P2RLIN29           (((volatile __bitf_T *)0xFFFFA22C)->bit02)
#define TBRLIN29           (((volatile __bitf_T *)0xFFFFA22C)->bit06)
#define MKRLIN29           (((volatile __bitf_T *)0xFFFFA22C)->bit07)
#define RFRLIN29           (((volatile __bitf_T *)0xFFFFA22D)->bit04)
#define CTRLIN29           (((volatile __bitf_T *)0xFFFFA22D)->bit07)
__IOREG(ICRCAN5ERR, 0xFFFFA22E, __READ_WRITE, uint16);
__IOREG(ICRCAN5ERRL, 0xFFFFA22E, __READ_WRITE, uint8);
__IOREG(ICRCAN5ERRH, 0xFFFFA22F, __READ_WRITE, uint8);
#define P0RCAN5ERR         (((volatile __bitf_T *)0xFFFFA22E)->bit00)
#define P1RCAN5ERR         (((volatile __bitf_T *)0xFFFFA22E)->bit01)
#define P2RCAN5ERR         (((volatile __bitf_T *)0xFFFFA22E)->bit02)
#define TBRCAN5ERR         (((volatile __bitf_T *)0xFFFFA22E)->bit06)
#define MKRCAN5ERR         (((volatile __bitf_T *)0xFFFFA22E)->bit07)
#define RFRCAN5ERR         (((volatile __bitf_T *)0xFFFFA22F)->bit04)
#define CTRCAN5ERR         (((volatile __bitf_T *)0xFFFFA22F)->bit07)
__IOREG(ICRCAN5REC, 0xFFFFA230, __READ_WRITE, uint16);
__IOREG(ICRCAN5RECL, 0xFFFFA230, __READ_WRITE, uint8);
__IOREG(ICRCAN5RECH, 0xFFFFA231, __READ_WRITE, uint8);
#define P0RCAN5REC         (((volatile __bitf_T *)0xFFFFA230)->bit00)
#define P1RCAN5REC         (((volatile __bitf_T *)0xFFFFA230)->bit01)
#define P2RCAN5REC         (((volatile __bitf_T *)0xFFFFA230)->bit02)
#define TBRCAN5REC         (((volatile __bitf_T *)0xFFFFA230)->bit06)
#define MKRCAN5REC         (((volatile __bitf_T *)0xFFFFA230)->bit07)
#define RFRCAN5REC         (((volatile __bitf_T *)0xFFFFA231)->bit04)
#define CTRCAN5REC         (((volatile __bitf_T *)0xFFFFA231)->bit07)
__IOREG(ICRCAN5TRX, 0xFFFFA232, __READ_WRITE, uint16);
__IOREG(ICRCAN5TRXL, 0xFFFFA232, __READ_WRITE, uint8);
__IOREG(ICRCAN5TRXH, 0xFFFFA233, __READ_WRITE, uint8);
#define P0RCAN5TRX         (((volatile __bitf_T *)0xFFFFA232)->bit00)
#define P1RCAN5TRX         (((volatile __bitf_T *)0xFFFFA232)->bit01)
#define P2RCAN5TRX         (((volatile __bitf_T *)0xFFFFA232)->bit02)
#define TBRCAN5TRX         (((volatile __bitf_T *)0xFFFFA232)->bit06)
#define MKRCAN5TRX         (((volatile __bitf_T *)0xFFFFA232)->bit07)
#define RFRCAN5TRX         (((volatile __bitf_T *)0xFFFFA233)->bit04)
#define CTRCAN5TRX         (((volatile __bitf_T *)0xFFFFA233)->bit07)
__IOREG(IMR1, 0xFFFFA404, __READ_WRITE, uint32);
__IOREG(IMR1L, 0xFFFFA404, __READ_WRITE, uint16);
__IOREG(IMR1LL, 0xFFFFA404, __READ_WRITE, uint8);
__IOREG(IMR1LH, 0xFFFFA405, __READ_WRITE, uint8);
__IOREG(IMR1H, 0xFFFFA406, __READ_WRITE, uint16);
__IOREG(IMR1HL, 0xFFFFA406, __READ_WRITE, uint8);
__IOREG(IMR1HH, 0xFFFFA407, __READ_WRITE, uint8);
#define IMR1EIMK32         (((volatile __bitf_T *)0xFFFFA404)->bit00)
#define IMR1EIMK33         (((volatile __bitf_T *)0xFFFFA404)->bit01)
#define IMR1EIMK34         (((volatile __bitf_T *)0xFFFFA404)->bit02)
#define IMR1EIMK35         (((volatile __bitf_T *)0xFFFFA404)->bit03)
#define IMR1EIMK36         (((volatile __bitf_T *)0xFFFFA404)->bit04)
#define IMR1EIMK37         (((volatile __bitf_T *)0xFFFFA404)->bit05)
#define IMR1EIMK38         (((volatile __bitf_T *)0xFFFFA404)->bit06)
#define IMR1EIMK39         (((volatile __bitf_T *)0xFFFFA404)->bit07)
#define IMR1EIMK40         (((volatile __bitf_T *)0xFFFFA405)->bit00)
#define IMR1EIMK41         (((volatile __bitf_T *)0xFFFFA405)->bit01)
#define IMR1EIMK42         (((volatile __bitf_T *)0xFFFFA405)->bit02)
#define IMR1EIMK43         (((volatile __bitf_T *)0xFFFFA405)->bit03)
#define IMR1EIMK44         (((volatile __bitf_T *)0xFFFFA405)->bit04)
#define IMR1EIMK45         (((volatile __bitf_T *)0xFFFFA405)->bit05)
#define IMR1EIMK46         (((volatile __bitf_T *)0xFFFFA405)->bit06)
#define IMR1EIMK47         (((volatile __bitf_T *)0xFFFFA405)->bit07)
#define IMR1EIMK49         (((volatile __bitf_T *)0xFFFFA406)->bit01)
#define IMR1EIMK50         (((volatile __bitf_T *)0xFFFFA406)->bit02)
#define IMR1EIMK51         (((volatile __bitf_T *)0xFFFFA406)->bit03)
#define IMR1EIMK52         (((volatile __bitf_T *)0xFFFFA406)->bit04)
#define IMR1EIMK53         (((volatile __bitf_T *)0xFFFFA406)->bit05)
#define IMR1EIMK54         (((volatile __bitf_T *)0xFFFFA406)->bit06)
#define IMR1EIMK55         (((volatile __bitf_T *)0xFFFFA406)->bit07)
#define IMR1EIMK56         (((volatile __bitf_T *)0xFFFFA407)->bit00)
#define IMR1EIMK57         (((volatile __bitf_T *)0xFFFFA407)->bit01)
#define IMR1EIMK58         (((volatile __bitf_T *)0xFFFFA407)->bit02)
#define IMR1EIMK59         (((volatile __bitf_T *)0xFFFFA407)->bit03)
#define IMR1EIMK60         (((volatile __bitf_T *)0xFFFFA407)->bit04)
#define IMR1EIMK61         (((volatile __bitf_T *)0xFFFFA407)->bit05)
#define IMR1EIMK62         (((volatile __bitf_T *)0xFFFFA407)->bit06)
#define IMR1EIMK63         (((volatile __bitf_T *)0xFFFFA407)->bit07)
__IOREG(IMR2, 0xFFFFA408, __READ_WRITE, uint32);
__IOREG(IMR2L, 0xFFFFA408, __READ_WRITE, uint16);
__IOREG(IMR2LL, 0xFFFFA408, __READ_WRITE, uint8);
__IOREG(IMR2LH, 0xFFFFA409, __READ_WRITE, uint8);
__IOREG(IMR2H, 0xFFFFA40A, __READ_WRITE, uint16);
__IOREG(IMR2HL, 0xFFFFA40A, __READ_WRITE, uint8);
__IOREG(IMR2HH, 0xFFFFA40B, __READ_WRITE, uint8);
#define IMR2EIMK64         (((volatile __bitf_T *)0xFFFFA408)->bit00)
#define IMR2EIMK65         (((volatile __bitf_T *)0xFFFFA408)->bit01)
#define IMR2EIMK66         (((volatile __bitf_T *)0xFFFFA408)->bit02)
#define IMR2EIMK67         (((volatile __bitf_T *)0xFFFFA408)->bit03)
#define IMR2EIMK68         (((volatile __bitf_T *)0xFFFFA408)->bit04)
#define IMR2EIMK69         (((volatile __bitf_T *)0xFFFFA408)->bit05)
#define IMR2EIMK70         (((volatile __bitf_T *)0xFFFFA408)->bit06)
#define IMR2EIMK71         (((volatile __bitf_T *)0xFFFFA408)->bit07)
#define IMR2EIMK72         (((volatile __bitf_T *)0xFFFFA409)->bit00)
#define IMR2EIMK73         (((volatile __bitf_T *)0xFFFFA409)->bit01)
#define IMR2EIMK74         (((volatile __bitf_T *)0xFFFFA409)->bit02)
#define IMR2EIMK75         (((volatile __bitf_T *)0xFFFFA409)->bit03)
#define IMR2EIMK76         (((volatile __bitf_T *)0xFFFFA409)->bit04)
#define IMR2EIMK77         (((volatile __bitf_T *)0xFFFFA409)->bit05)
#define IMR2EIMK78         (((volatile __bitf_T *)0xFFFFA409)->bit06)
#define IMR2EIMK79         (((volatile __bitf_T *)0xFFFFA409)->bit07)
#define IMR2EIMK80         (((volatile __bitf_T *)0xFFFFA40A)->bit00)
#define IMR2EIMK81         (((volatile __bitf_T *)0xFFFFA40A)->bit01)
#define IMR2EIMK82         (((volatile __bitf_T *)0xFFFFA40A)->bit02)
#define IMR2EIMK83         (((volatile __bitf_T *)0xFFFFA40A)->bit03)
#define IMR2EIMK84         (((volatile __bitf_T *)0xFFFFA40A)->bit04)
#define IMR2EIMK85         (((volatile __bitf_T *)0xFFFFA40A)->bit05)
#define IMR2EIMK86         (((volatile __bitf_T *)0xFFFFA40A)->bit06)
#define IMR2EIMK87         (((volatile __bitf_T *)0xFFFFA40A)->bit07)
#define IMR2EIMK88         (((volatile __bitf_T *)0xFFFFA40B)->bit00)
#define IMR2EIMK89         (((volatile __bitf_T *)0xFFFFA40B)->bit01)
#define IMR2EIMK90         (((volatile __bitf_T *)0xFFFFA40B)->bit02)
#define IMR2EIMK91         (((volatile __bitf_T *)0xFFFFA40B)->bit03)
#define IMR2EIMK92         (((volatile __bitf_T *)0xFFFFA40B)->bit04)
#define IMR2EIMK93         (((volatile __bitf_T *)0xFFFFA40B)->bit05)
#define IMR2EIMK94         (((volatile __bitf_T *)0xFFFFA40B)->bit06)
#define IMR2EIMK95         (((volatile __bitf_T *)0xFFFFA40B)->bit07)
__IOREG(IMR3, 0xFFFFA40C, __READ_WRITE, uint32);
__IOREG(IMR3L, 0xFFFFA40C, __READ_WRITE, uint16);
__IOREG(IMR3LL, 0xFFFFA40C, __READ_WRITE, uint8);
__IOREG(IMR3LH, 0xFFFFA40D, __READ_WRITE, uint8);
__IOREG(IMR3H, 0xFFFFA40E, __READ_WRITE, uint16);
__IOREG(IMR3HL, 0xFFFFA40E, __READ_WRITE, uint8);
__IOREG(IMR3HH, 0xFFFFA40F, __READ_WRITE, uint8);
#define IMR3EIMK102        (((volatile __bitf_T *)0xFFFFA40C)->bit06)
#define IMR3EIMK103        (((volatile __bitf_T *)0xFFFFA40C)->bit07)
#define IMR3EIMK104        (((volatile __bitf_T *)0xFFFFA40D)->bit00)
#define IMR3EIMK105        (((volatile __bitf_T *)0xFFFFA40D)->bit01)
#define IMR3EIMK106        (((volatile __bitf_T *)0xFFFFA40D)->bit02)
#define IMR3EIMK107        (((volatile __bitf_T *)0xFFFFA40D)->bit03)
#define IMR3EIMK108        (((volatile __bitf_T *)0xFFFFA40D)->bit04)
#define IMR3EIMK109        (((volatile __bitf_T *)0xFFFFA40D)->bit05)
#define IMR3EIMK110        (((volatile __bitf_T *)0xFFFFA40D)->bit06)
#define IMR3EIMK111        (((volatile __bitf_T *)0xFFFFA40D)->bit07)
#define IMR3EIMK112        (((volatile __bitf_T *)0xFFFFA40E)->bit00)
#define IMR3EIMK113        (((volatile __bitf_T *)0xFFFFA40E)->bit01)
#define IMR3EIMK114        (((volatile __bitf_T *)0xFFFFA40E)->bit02)
#define IMR3EIMK115        (((volatile __bitf_T *)0xFFFFA40E)->bit03)
#define IMR3EIMK116        (((volatile __bitf_T *)0xFFFFA40E)->bit04)
#define IMR3EIMK117        (((volatile __bitf_T *)0xFFFFA40E)->bit05)
#define IMR3EIMK118        (((volatile __bitf_T *)0xFFFFA40E)->bit06)
#define IMR3EIMK119        (((volatile __bitf_T *)0xFFFFA40E)->bit07)
#define IMR3EIMK120        (((volatile __bitf_T *)0xFFFFA40F)->bit00)
#define IMR3EIMK121        (((volatile __bitf_T *)0xFFFFA40F)->bit01)
#define IMR3EIMK122        (((volatile __bitf_T *)0xFFFFA40F)->bit02)
#define IMR3EIMK123        (((volatile __bitf_T *)0xFFFFA40F)->bit03)
#define IMR3EIMK124        (((volatile __bitf_T *)0xFFFFA40F)->bit04)
#define IMR3EIMK125        (((volatile __bitf_T *)0xFFFFA40F)->bit05)
#define IMR3EIMK126        (((volatile __bitf_T *)0xFFFFA40F)->bit06)
#define IMR3EIMK127        (((volatile __bitf_T *)0xFFFFA40F)->bit07)
__IOREG(IMR4, 0xFFFFA410, __READ_WRITE, uint32);
__IOREG(IMR4L, 0xFFFFA410, __READ_WRITE, uint16);
__IOREG(IMR4LL, 0xFFFFA410, __READ_WRITE, uint8);
__IOREG(IMR4LH, 0xFFFFA411, __READ_WRITE, uint8);
__IOREG(IMR4H, 0xFFFFA412, __READ_WRITE, uint16);
__IOREG(IMR4HL, 0xFFFFA412, __READ_WRITE, uint8);
__IOREG(IMR4HH, 0xFFFFA413, __READ_WRITE, uint8);
#define IMR4EIMK134        (((volatile __bitf_T *)0xFFFFA410)->bit06)
#define IMR4EIMK135        (((volatile __bitf_T *)0xFFFFA410)->bit07)
#define IMR4EIMK136        (((volatile __bitf_T *)0xFFFFA411)->bit00)
#define IMR4EIMK137        (((volatile __bitf_T *)0xFFFFA411)->bit01)
#define IMR4EIMK138        (((volatile __bitf_T *)0xFFFFA411)->bit02)
#define IMR4EIMK139        (((volatile __bitf_T *)0xFFFFA411)->bit03)
#define IMR4EIMK140        (((volatile __bitf_T *)0xFFFFA411)->bit04)
#define IMR4EIMK141        (((volatile __bitf_T *)0xFFFFA411)->bit05)
#define IMR4EIMK142        (((volatile __bitf_T *)0xFFFFA411)->bit06)
#define IMR4EIMK143        (((volatile __bitf_T *)0xFFFFA411)->bit07)
#define IMR4EIMK144        (((volatile __bitf_T *)0xFFFFA412)->bit00)
#define IMR4EIMK145        (((volatile __bitf_T *)0xFFFFA412)->bit01)
#define IMR4EIMK146        (((volatile __bitf_T *)0xFFFFA412)->bit02)
#define IMR4EIMK147        (((volatile __bitf_T *)0xFFFFA412)->bit03)
#define IMR4EIMK148        (((volatile __bitf_T *)0xFFFFA412)->bit04)
#define IMR4EIMK149        (((volatile __bitf_T *)0xFFFFA412)->bit05)
#define IMR4EIMK150        (((volatile __bitf_T *)0xFFFFA412)->bit06)
#define IMR4EIMK151        (((volatile __bitf_T *)0xFFFFA412)->bit07)
#define IMR4EIMK152        (((volatile __bitf_T *)0xFFFFA413)->bit00)
#define IMR4EIMK153        (((volatile __bitf_T *)0xFFFFA413)->bit01)
#define IMR4EIMK154        (((volatile __bitf_T *)0xFFFFA413)->bit02)
#define IMR4EIMK155        (((volatile __bitf_T *)0xFFFFA413)->bit03)
#define IMR4EIMK156        (((volatile __bitf_T *)0xFFFFA413)->bit04)
#define IMR4EIMK157        (((volatile __bitf_T *)0xFFFFA413)->bit05)
#define IMR4EIMK158        (((volatile __bitf_T *)0xFFFFA413)->bit06)
#define IMR4EIMK159        (((volatile __bitf_T *)0xFFFFA413)->bit07)
__IOREG(IMR5, 0xFFFFA414, __READ_WRITE, uint32);
__IOREG(IMR5L, 0xFFFFA414, __READ_WRITE, uint16);
__IOREG(IMR5LL, 0xFFFFA414, __READ_WRITE, uint8);
__IOREG(IMR5H, 0xFFFFA416, __READ_WRITE, uint16);
__IOREG(IMR5HL, 0xFFFFA416, __READ_WRITE, uint8);
__IOREG(IMR5HH, 0xFFFFA417, __READ_WRITE, uint8);
#define IMR5EIMK160        (((volatile __bitf_T *)0xFFFFA414)->bit00)
#define IMR5EIMK161        (((volatile __bitf_T *)0xFFFFA414)->bit01)
#define IMR5EIMK162        (((volatile __bitf_T *)0xFFFFA414)->bit02)
#define IMR5EIMK163        (((volatile __bitf_T *)0xFFFFA414)->bit03)
#define IMR5EIMK176        (((volatile __bitf_T *)0xFFFFA416)->bit00)
#define IMR5EIMK177        (((volatile __bitf_T *)0xFFFFA416)->bit01)
#define IMR5EIMK178        (((volatile __bitf_T *)0xFFFFA416)->bit02)
#define IMR5EIMK179        (((volatile __bitf_T *)0xFFFFA416)->bit03)
#define IMR5EIMK180        (((volatile __bitf_T *)0xFFFFA416)->bit04)
#define IMR5EIMK181        (((volatile __bitf_T *)0xFFFFA416)->bit05)
#define IMR5EIMK182        (((volatile __bitf_T *)0xFFFFA416)->bit06)
#define IMR5EIMK183        (((volatile __bitf_T *)0xFFFFA416)->bit07)
#define IMR5EIMK184        (((volatile __bitf_T *)0xFFFFA417)->bit00)
#define IMR5EIMK185        (((volatile __bitf_T *)0xFFFFA417)->bit01)
#define IMR5EIMK186        (((volatile __bitf_T *)0xFFFFA417)->bit02)
#define IMR5EIMK187        (((volatile __bitf_T *)0xFFFFA417)->bit03)
#define IMR5EIMK188        (((volatile __bitf_T *)0xFFFFA417)->bit04)
#define IMR5EIMK189        (((volatile __bitf_T *)0xFFFFA417)->bit05)
#define IMR5EIMK190        (((volatile __bitf_T *)0xFFFFA417)->bit06)
#define IMR5EIMK191        (((volatile __bitf_T *)0xFFFFA417)->bit07)
__IOREG(IMR6, 0xFFFFA418, __READ_WRITE, uint32);
__IOREG(IMR6L, 0xFFFFA418, __READ_WRITE, uint16);
__IOREG(IMR6LL, 0xFFFFA418, __READ_WRITE, uint8);
__IOREG(IMR6LH, 0xFFFFA419, __READ_WRITE, uint8);
__IOREG(IMR6H, 0xFFFFA41A, __READ_WRITE, uint16);
__IOREG(IMR6HL, 0xFFFFA41A, __READ_WRITE, uint8);
__IOREG(IMR6HH, 0xFFFFA41B, __READ_WRITE, uint8);
#define IMR6EIMK192        (((volatile __bitf_T *)0xFFFFA418)->bit00)
#define IMR6EIMK193        (((volatile __bitf_T *)0xFFFFA418)->bit01)
#define IMR6EIMK194        (((volatile __bitf_T *)0xFFFFA418)->bit02)
#define IMR6EIMK195        (((volatile __bitf_T *)0xFFFFA418)->bit03)
#define IMR6EIMK196        (((volatile __bitf_T *)0xFFFFA418)->bit04)
#define IMR6EIMK197        (((volatile __bitf_T *)0xFFFFA418)->bit05)
#define IMR6EIMK198        (((volatile __bitf_T *)0xFFFFA418)->bit06)
#define IMR6EIMK199        (((volatile __bitf_T *)0xFFFFA418)->bit07)
#define IMR6EIMK200        (((volatile __bitf_T *)0xFFFFA419)->bit00)
#define IMR6EIMK201        (((volatile __bitf_T *)0xFFFFA419)->bit01)
#define IMR6EIMK202        (((volatile __bitf_T *)0xFFFFA419)->bit02)
#define IMR6EIMK203        (((volatile __bitf_T *)0xFFFFA419)->bit03)
#define IMR6EIMK204        (((volatile __bitf_T *)0xFFFFA419)->bit04)
#define IMR6EIMK205        (((volatile __bitf_T *)0xFFFFA419)->bit05)
#define IMR6EIMK206        (((volatile __bitf_T *)0xFFFFA419)->bit06)
#define IMR6EIMK207        (((volatile __bitf_T *)0xFFFFA419)->bit07)
#define IMR6EIMK209        (((volatile __bitf_T *)0xFFFFA41A)->bit01)
#define IMR6EIMK210        (((volatile __bitf_T *)0xFFFFA41A)->bit02)
#define IMR6EIMK211        (((volatile __bitf_T *)0xFFFFA41A)->bit03)
#define IMR6EIMK212        (((volatile __bitf_T *)0xFFFFA41A)->bit04)
#define IMR6EIMK213        (((volatile __bitf_T *)0xFFFFA41A)->bit05)
#define IMR6EIMK214        (((volatile __bitf_T *)0xFFFFA41A)->bit06)
#define IMR6EIMK215        (((volatile __bitf_T *)0xFFFFA41A)->bit07)
#define IMR6EIMK216        (((volatile __bitf_T *)0xFFFFA41B)->bit00)
#define IMR6EIMK217        (((volatile __bitf_T *)0xFFFFA41B)->bit01)
#define IMR6EIMK218        (((volatile __bitf_T *)0xFFFFA41B)->bit02)
#define IMR6EIMK219        (((volatile __bitf_T *)0xFFFFA41B)->bit03)
#define IMR6EIMK220        (((volatile __bitf_T *)0xFFFFA41B)->bit04)
#define IMR6EIMK221        (((volatile __bitf_T *)0xFFFFA41B)->bit05)
#define IMR6EIMK222        (((volatile __bitf_T *)0xFFFFA41B)->bit06)
#define IMR6EIMK223        (((volatile __bitf_T *)0xFFFFA41B)->bit07)
__IOREG(IMR7, 0xFFFFA41C, __READ_WRITE, uint32);
__IOREG(IMR7L, 0xFFFFA41C, __READ_WRITE, uint16);
__IOREG(IMR7LL, 0xFFFFA41C, __READ_WRITE, uint8);
__IOREG(IMR7LH, 0xFFFFA41D, __READ_WRITE, uint8);
__IOREG(IMR7H, 0xFFFFA41E, __READ_WRITE, uint16);
__IOREG(IMR7HL, 0xFFFFA41E, __READ_WRITE, uint8);
__IOREG(IMR7HH, 0xFFFFA41F, __READ_WRITE, uint8);
#define IMR7EIMK224        (((volatile __bitf_T *)0xFFFFA41C)->bit00)
#define IMR7EIMK225        (((volatile __bitf_T *)0xFFFFA41C)->bit01)
#define IMR7EIMK226        (((volatile __bitf_T *)0xFFFFA41C)->bit02)
#define IMR7EIMK227        (((volatile __bitf_T *)0xFFFFA41C)->bit03)
#define IMR7EIMK228        (((volatile __bitf_T *)0xFFFFA41C)->bit04)
#define IMR7EIMK229        (((volatile __bitf_T *)0xFFFFA41C)->bit05)
#define IMR7EIMK230        (((volatile __bitf_T *)0xFFFFA41C)->bit06)
#define IMR7EIMK231        (((volatile __bitf_T *)0xFFFFA41C)->bit07)
#define IMR7EIMK232        (((volatile __bitf_T *)0xFFFFA41D)->bit00)
#define IMR7EIMK233        (((volatile __bitf_T *)0xFFFFA41D)->bit01)
#define IMR7EIMK234        (((volatile __bitf_T *)0xFFFFA41D)->bit02)
#define IMR7EIMK235        (((volatile __bitf_T *)0xFFFFA41D)->bit03)
#define IMR7EIMK236        (((volatile __bitf_T *)0xFFFFA41D)->bit04)
#define IMR7EIMK237        (((volatile __bitf_T *)0xFFFFA41D)->bit05)
#define IMR7EIMK238        (((volatile __bitf_T *)0xFFFFA41D)->bit06)
#define IMR7EIMK239        (((volatile __bitf_T *)0xFFFFA41D)->bit07)
#define IMR7EIMK240        (((volatile __bitf_T *)0xFFFFA41E)->bit00)
#define IMR7EIMK241        (((volatile __bitf_T *)0xFFFFA41E)->bit01)
#define IMR7EIMK242        (((volatile __bitf_T *)0xFFFFA41E)->bit02)
#define IMR7EIMK243        (((volatile __bitf_T *)0xFFFFA41E)->bit03)
#define IMR7EIMK244        (((volatile __bitf_T *)0xFFFFA41E)->bit04)
#define IMR7EIMK245        (((volatile __bitf_T *)0xFFFFA41E)->bit05)
#define IMR7EIMK246        (((volatile __bitf_T *)0xFFFFA41E)->bit06)
#define IMR7EIMK247        (((volatile __bitf_T *)0xFFFFA41E)->bit07)
#define IMR7EIMK248        (((volatile __bitf_T *)0xFFFFA41F)->bit00)
#define IMR7EIMK249        (((volatile __bitf_T *)0xFFFFA41F)->bit01)
#define IMR7EIMK250        (((volatile __bitf_T *)0xFFFFA41F)->bit02)
#define IMR7EIMK251        (((volatile __bitf_T *)0xFFFFA41F)->bit03)
#define IMR7EIMK252        (((volatile __bitf_T *)0xFFFFA41F)->bit04)
#define IMR7EIMK253        (((volatile __bitf_T *)0xFFFFA41F)->bit05)
#define IMR7EIMK254        (((volatile __bitf_T *)0xFFFFA41F)->bit06)
#define IMR7EIMK255        (((volatile __bitf_T *)0xFFFFA41F)->bit07)
__IOREG(IMR8, 0xFFFFA420, __READ_WRITE, uint32);
__IOREG(IMR8L, 0xFFFFA420, __READ_WRITE, uint16);
__IOREG(IMR8LL, 0xFFFFA420, __READ_WRITE, uint8);
__IOREG(IMR8LH, 0xFFFFA421, __READ_WRITE, uint8);
__IOREG(IMR8H, 0xFFFFA422, __READ_WRITE, uint16);
__IOREG(IMR8HL, 0xFFFFA422, __READ_WRITE, uint8);
__IOREG(IMR8HH, 0xFFFFA423, __READ_WRITE, uint8);
#define IMR8EIMK256        (((volatile __bitf_T *)0xFFFFA420)->bit00)
#define IMR8EIMK257        (((volatile __bitf_T *)0xFFFFA420)->bit01)
#define IMR8EIMK258        (((volatile __bitf_T *)0xFFFFA420)->bit02)
#define IMR8EIMK259        (((volatile __bitf_T *)0xFFFFA420)->bit03)
#define IMR8EIMK260        (((volatile __bitf_T *)0xFFFFA420)->bit04)
#define IMR8EIMK261        (((volatile __bitf_T *)0xFFFFA420)->bit05)
#define IMR8EIMK262        (((volatile __bitf_T *)0xFFFFA420)->bit06)
#define IMR8EIMK263        (((volatile __bitf_T *)0xFFFFA420)->bit07)
#define IMR8EIMK264        (((volatile __bitf_T *)0xFFFFA421)->bit00)
#define IMR8EIMK265        (((volatile __bitf_T *)0xFFFFA421)->bit01)
#define IMR8EIMK266        (((volatile __bitf_T *)0xFFFFA421)->bit02)
#define IMR8EIMK267        (((volatile __bitf_T *)0xFFFFA421)->bit03)
#define IMR8EIMK268        (((volatile __bitf_T *)0xFFFFA421)->bit04)
#define IMR8EIMK269        (((volatile __bitf_T *)0xFFFFA421)->bit05)
#define IMR8EIMK270        (((volatile __bitf_T *)0xFFFFA421)->bit06)
#define IMR8EIMK271        (((volatile __bitf_T *)0xFFFFA421)->bit07)
#define IMR8EIMK272        (((volatile __bitf_T *)0xFFFFA422)->bit00)
#define IMR8EIMK273        (((volatile __bitf_T *)0xFFFFA422)->bit01)
#define IMR8EIMK274        (((volatile __bitf_T *)0xFFFFA422)->bit02)
#define IMR8EIMK275        (((volatile __bitf_T *)0xFFFFA422)->bit03)
#define IMR8EIMK276        (((volatile __bitf_T *)0xFFFFA422)->bit04)
#define IMR8EIMK277        (((volatile __bitf_T *)0xFFFFA422)->bit05)
#define IMR8EIMK278        (((volatile __bitf_T *)0xFFFFA422)->bit06)
#define IMR8EIMK279        (((volatile __bitf_T *)0xFFFFA422)->bit07)
#define IMR8EIMK280        (((volatile __bitf_T *)0xFFFFA423)->bit00)
#define IMR8EIMK281        (((volatile __bitf_T *)0xFFFFA423)->bit01)

__IOREG(SELF, 0xFFA08000, __READ_WRITE, __type24);                    /* SELF */
__IOREG(FACI, 0xFFA10000, __READ_WRITE, __type25);                    /* FACI */
__IOREG(PFSS, 0xFFBC0700, __READ_WRITE, __type26);                    /* PFSS */
__IOREG(CCIB, 0xFFC59008, __READ_WRITE, __type27);                    /* CCIB */
__IOREG(RIIC0, 0xFFCA0000, __READ_WRITE, __type28);                   /* RIIC0 */
__IOREG(SCDS, 0xFFCD00D0, __READ_WRITE, __type29);                    /* SCDS */
__IOREG(RLN240, 0xFFCE0000, __READ_WRITE, __type30);                  /* RLN240 */
__IOREG(RLN2400, 0xFFCE0008, __READ_WRITE, __type31);                 /* RLN2400 */
__IOREG(RLN2401, 0xFFCE0028, __READ_WRITE, __type32);                 /* RLN2401 */
__IOREG(RLN2402, 0xFFCE0048, __READ_WRITE, __type33);                 /* RLN2402 */
__IOREG(RLN2403, 0xFFCE0068, __READ_WRITE, __type34);                 /* RLN2403 */
__IOREG(RLN241, 0xFFCE0080, __READ_WRITE, __type30);                  /* RLN241 */
__IOREG(RLN2414, 0xFFCE0088, __READ_WRITE, __type31);                 /* RLN2414 */
__IOREG(RLN2415, 0xFFCE00A8, __READ_WRITE, __type32);                 /* RLN2415 */
__IOREG(RLN2416, 0xFFCE00C8, __READ_WRITE, __type33);                 /* RLN2416 */
__IOREG(RLN2417, 0xFFCE00E8, __READ_WRITE, __type34);                 /* RLN2417 */
__IOREG(RLN210, 0xFFCE0100, __READ_WRITE, __type30);                  /* RLN210 */
__IOREG(RLN2108, 0xFFCE0108, __READ_WRITE, __type31);                 /* RLN2108 */
__IOREG(RLN211, 0xFFCE0120, __READ_WRITE, __type30);                  /* RLN211 */
__IOREG(RLN2119, 0xFFCE0128, __READ_WRITE, __type31);                 /* RLN2119 */
__IOREG(RLN30, 0xFFCF0000, __READ_WRITE, __type35);                   /* RLN30 */
__IOREG(RLN31, 0xFFCF0040, __READ_WRITE, __type35);                   /* RLN31 */
__IOREG(RLN32, 0xFFCF0080, __READ_WRITE, __type35);                   /* RLN32 */
__IOREG(RLN33, 0xFFCF00C0, __READ_WRITE, __type35);                   /* RLN33 */
__IOREG(RLN34, 0xFFCF0100, __READ_WRITE, __type35);                   /* RLN34 */
__IOREG(RLN35, 0xFFCF0140, __READ_WRITE, __type35);                   /* RLN35 */
__IOREG(RSCAN0, 0xFFD00000, __READ_WRITE, __type36);                  /* RSCAN0 */
__IOREG(CSIH0, 0xFFD80000, __READ_WRITE, __type37);                   /* CSIH0 */
__IOREG(CSIH1, 0xFFD82000, __READ_WRITE, __type38);                   /* CSIH1 */
__IOREG(CSIH2, 0xFFD84000, __READ_WRITE, __type38);                   /* CSIH2 */
__IOREG(CSIH3, 0xFFD86000, __READ_WRITE, __type39);                   /* CSIH3 */
__IOREG(CSIG0, 0xFFDB0000, __READ_WRITE, __type40);                   /* CSIG0 */
__IOREG(CSIG1, 0xFFDB2000, __READ_WRITE, __type40);                   /* CSIG1 */
__IOREG(PIC0, 0xFFDD0004, __READ_WRITE, __type41);                    /* PIC0 */
__IOREG(TAUD0, 0xFFE20000, __READ_WRITE, __type42);                   /* TAUD0 */
__IOREG(TAUB0, 0xFFE30000, __READ_WRITE, __type43);                   /* TAUB0 */
__IOREG(TAUB1, 0xFFE31000, __READ_WRITE, __type43);                   /* TAUB1 */
__IOREG(TAUJ0, 0xFFE50000, __READ_WRITE, __type44);                   /* TAUJ0 */
__IOREG(TAUJ1, 0xFFE51000, __READ_WRITE, __type44);                   /* TAUJ1 */
__IOREG(PWSA0, 0xFFE70000, __READ_WRITE, __type45);                   /* PWSA0 */
__IOREG(PWGA0, 0xFFE71000, __READ_WRITE, __type46);                   /* PWGA0 */
__IOREG(PWGA1, 0xFFE71040, __READ_WRITE, __type46);                   /* PWGA1 */
__IOREG(PWGA2, 0xFFE71080, __READ_WRITE, __type46);                   /* PWGA2 */
__IOREG(PWGA3, 0xFFE710C0, __READ_WRITE, __type46);                   /* PWGA3 */
__IOREG(PWGA4, 0xFFE71100, __READ_WRITE, __type46);                   /* PWGA4 */
__IOREG(PWGA5, 0xFFE71140, __READ_WRITE, __type46);                   /* PWGA5 */
__IOREG(PWGA6, 0xFFE71180, __READ_WRITE, __type46);                   /* PWGA6 */
__IOREG(PWGA7, 0xFFE711C0, __READ_WRITE, __type46);                   /* PWGA7 */
__IOREG(PWGA8, 0xFFE71200, __READ_WRITE, __type46);                   /* PWGA8 */
__IOREG(PWGA9, 0xFFE71240, __READ_WRITE, __type46);                   /* PWGA9 */
__IOREG(PWGA10, 0xFFE71280, __READ_WRITE, __type46);                  /* PWGA10 */
__IOREG(PWGA11, 0xFFE712C0, __READ_WRITE, __type46);                  /* PWGA11 */
__IOREG(PWGA12, 0xFFE71300, __READ_WRITE, __type46);                  /* PWGA12 */
__IOREG(PWGA13, 0xFFE71340, __READ_WRITE, __type46);                  /* PWGA13 */
__IOREG(PWGA14, 0xFFE71380, __READ_WRITE, __type46);                  /* PWGA14 */
__IOREG(PWGA15, 0xFFE713C0, __READ_WRITE, __type46);                  /* PWGA15 */
__IOREG(PWGA16, 0xFFE71400, __READ_WRITE, __type46);                  /* PWGA16 */
__IOREG(PWGA17, 0xFFE71440, __READ_WRITE, __type46);                  /* PWGA17 */
__IOREG(PWGA18, 0xFFE71480, __READ_WRITE, __type46);                  /* PWGA18 */
__IOREG(PWGA19, 0xFFE714C0, __READ_WRITE, __type46);                  /* PWGA19 */
__IOREG(PWGA20, 0xFFE71500, __READ_WRITE, __type46);                  /* PWGA20 */
__IOREG(PWGA21, 0xFFE71540, __READ_WRITE, __type46);                  /* PWGA21 */
__IOREG(PWGA22, 0xFFE71580, __READ_WRITE, __type46);                  /* PWGA22 */
__IOREG(PWGA23, 0xFFE715C0, __READ_WRITE, __type46);                  /* PWGA23 */
__IOREG(PWGA24, 0xFFE71600, __READ_WRITE, __type46);                  /* PWGA24 */
__IOREG(PWGA25, 0xFFE71640, __READ_WRITE, __type46);                  /* PWGA25 */
__IOREG(PWGA26, 0xFFE71680, __READ_WRITE, __type46);                  /* PWGA26 */
__IOREG(PWGA27, 0xFFE716C0, __READ_WRITE, __type46);                  /* PWGA27 */
__IOREG(PWGA28, 0xFFE71700, __READ_WRITE, __type46);                  /* PWGA28 */
__IOREG(PWGA29, 0xFFE71740, __READ_WRITE, __type46);                  /* PWGA29 */
__IOREG(PWGA30, 0xFFE71780, __READ_WRITE, __type46);                  /* PWGA30 */
__IOREG(PWGA31, 0xFFE717C0, __READ_WRITE, __type46);                  /* PWGA31 */
__IOREG(PWGA32, 0xFFE71800, __READ_WRITE, __type46);                  /* PWGA32 */
__IOREG(PWGA33, 0xFFE71840, __READ_WRITE, __type46);                  /* PWGA33 */
__IOREG(PWGA34, 0xFFE71880, __READ_WRITE, __type46);                  /* PWGA34 */
__IOREG(PWGA35, 0xFFE718C0, __READ_WRITE, __type46);                  /* PWGA35 */
__IOREG(PWGA36, 0xFFE71900, __READ_WRITE, __type46);                  /* PWGA36 */
__IOREG(PWGA37, 0xFFE71940, __READ_WRITE, __type46);                  /* PWGA37 */
__IOREG(PWGA38, 0xFFE71980, __READ_WRITE, __type46);                  /* PWGA38 */
__IOREG(PWGA39, 0xFFE719C0, __READ_WRITE, __type46);                  /* PWGA39 */
__IOREG(PWGA40, 0xFFE71A00, __READ_WRITE, __type46);                  /* PWGA40 */
__IOREG(PWGA41, 0xFFE71A40, __READ_WRITE, __type46);                  /* PWGA41 */
__IOREG(PWGA42, 0xFFE71A80, __READ_WRITE, __type46);                  /* PWGA42 */
__IOREG(PWGA43, 0xFFE71AC0, __READ_WRITE, __type46);                  /* PWGA43 */
__IOREG(PWGA44, 0xFFE71B00, __READ_WRITE, __type46);                  /* PWGA44 */
__IOREG(PWGA45, 0xFFE71B40, __READ_WRITE, __type46);                  /* PWGA45 */
__IOREG(PWGA46, 0xFFE71B80, __READ_WRITE, __type46);                  /* PWGA46 */
__IOREG(PWGA47, 0xFFE71BC0, __READ_WRITE, __type46);                  /* PWGA47 */
__IOREG(PWGA48, 0xFFE71C00, __READ_WRITE, __type46);                  /* PWGA48 */
__IOREG(PWGA49, 0xFFE71C40, __READ_WRITE, __type46);                  /* PWGA49 */
__IOREG(PWGA50, 0xFFE71C80, __READ_WRITE, __type46);                  /* PWGA50 */
__IOREG(PWGA51, 0xFFE71CC0, __READ_WRITE, __type46);                  /* PWGA51 */
__IOREG(PWGA52, 0xFFE71D00, __READ_WRITE, __type46);                  /* PWGA52 */
__IOREG(PWGA53, 0xFFE71D40, __READ_WRITE, __type46);                  /* PWGA53 */
__IOREG(PWGA54, 0xFFE71D80, __READ_WRITE, __type46);                  /* PWGA54 */
__IOREG(PWGA55, 0xFFE71DC0, __READ_WRITE, __type46);                  /* PWGA55 */
__IOREG(PWGA56, 0xFFE71E00, __READ_WRITE, __type46);                  /* PWGA56 */
__IOREG(PWGA57, 0xFFE71E40, __READ_WRITE, __type46);                  /* PWGA57 */
__IOREG(PWGA58, 0xFFE71E80, __READ_WRITE, __type46);                  /* PWGA58 */
__IOREG(PWGA59, 0xFFE71EC0, __READ_WRITE, __type46);                  /* PWGA59 */
__IOREG(PWGA60, 0xFFE71F00, __READ_WRITE, __type46);                  /* PWGA60 */
__IOREG(PWGA61, 0xFFE71F40, __READ_WRITE, __type46);                  /* PWGA61 */
__IOREG(PWGA62, 0xFFE71F80, __READ_WRITE, __type46);                  /* PWGA62 */
__IOREG(PWGA63, 0xFFE71FC0, __READ_WRITE, __type46);                  /* PWGA63 */
__IOREG(PWGA64, 0xFFE72000, __READ_WRITE, __type46);                  /* PWGA64 */
__IOREG(PWGA65, 0xFFE72040, __READ_WRITE, __type46);                  /* PWGA65 */
__IOREG(PWGA66, 0xFFE72080, __READ_WRITE, __type46);                  /* PWGA66 */
__IOREG(PWGA67, 0xFFE720C0, __READ_WRITE, __type46);                  /* PWGA67 */
__IOREG(PWGA68, 0xFFE72100, __READ_WRITE, __type46);                  /* PWGA68 */
__IOREG(PWGA69, 0xFFE72140, __READ_WRITE, __type46);                  /* PWGA69 */
__IOREG(PWGA70, 0xFFE72180, __READ_WRITE, __type46);                  /* PWGA70 */
__IOREG(PWGA71, 0xFFE721C0, __READ_WRITE, __type46);                  /* PWGA71 */
__IOREG(PWBA0, 0xFFE72800, __READ_WRITE, __type47);                   /* PWBA0 */
__IOREG(RTCA0, 0xFFE78000, __READ_WRITE, __type48);                   /* RTCA0 */
__IOREG(ENCA0, 0xFFE80000, __READ_WRITE, __type49);                   /* ENCA0 */
__IOREG(TAPA0, 0xFFE90000, __READ_WRITE, __type50);                   /* TAPA0 */
__IOREG(OSTM0, 0xFFEC0000, __READ_WRITE, __type51);                   /* OSTM0 */
__IOREG(WDTA0, 0xFFED0000, __READ_WRITE, __type52);                   /* WDTA0 */
__IOREG(WDTA1, 0xFFED1000, __READ_WRITE, __type52);                   /* WDTA1 */
__IOREG(ADCA0, 0xFFF20000, __READ_WRITE, __type53);                   /* ADCA0 */
__IOREG(ADCA1, 0xFFF21000, __READ_WRITE, __type54);                   /* ADCA1 */
__IOREG(DCRA0, 0xFFF70000, __READ_WRITE, __type55);                   /* DCRA0 */
__IOREG(DCRA1, 0xFFF71000, __READ_WRITE, __type55);                   /* DCRA1 */
__IOREG(DCRA2, 0xFFF72000, __READ_WRITE, __type55);                   /* DCRA2 */
__IOREG(DCRA3, 0xFFF73000, __READ_WRITE, __type55);                   /* DCRA3 */
__IOREG(KR0, 0xFFF78000, __READ_WRITE, __type56);                     /* KR0 */
__IOREG(CLMA0, 0xFFF8C000, __READ_WRITE, __type57);                   /* CLMA0 */
__IOREG(CLMA, 0xFFF8C100, __READ_WRITE, __type58);                    /* CLMA */
__IOREG(CLMA1, 0xFFF8D000, __READ_WRITE, __type57);                   /* CLMA1 */
__IOREG(CLMA2, 0xFFF8E000, __READ_WRITE, __type57);                   /* CLMA2 */

__IOREGARRAY(CSIG, 2, 0xFFDB0000, __READ_WRITE, __type40);            /* CSIG[2] */
__IOREGARRAY(TAUB, 2, 0xFFE30000, __READ_WRITE, __type43);            /* TAUB[2] */
__IOREGARRAY(TAUJ, 2, 0xFFE50000, __READ_WRITE, __type44);            /* TAUJ[2] */
__IOREGARRAY(PWGA, 72, 0xFFE71000, __READ_WRITE, __type46);           /* PWGA[72] */
__IOREGARRAY(RLN3, 6, 0xFFCF0000, __READ_WRITE, __type35);            /* RLN3[6] */
__IOREGARRAY(WDTA, 2, 0xFFED0000, __READ_WRITE, __type52);            /* WDTA[2] */
__IOREGARRAY(DCRA, 4, 0xFFF70000, __READ_WRITE, __type55);            /* DCRA[4] */

#define SELFID0 SELF.ID0
#define SELFID1 SELF.ID1
#define SELFID2 SELF.ID2
#define SELFID3 SELF.ID3
#define SELFIDST SELF.IDST
#define FACIFPMON FACI.FPMON
#define FACIFASTAT FACI.FASTAT
#define FACIFAEINT FACI.FAEINT
#define FACIFAREASELC FACI.FAREASELC
#define FACIFSADDR FACI.FSADDR
#define FACIFEADDR FACI.FEADDR
#define FACIFCURAME FACI.FCURAME
#define FACIFSTATR FACI.FSTATR
#define FACIFENTRYR FACI.FENTRYR
#define FACIFPROTR FACI.FPROTR
#define FACIFSUINITR FACI.FSUINITR
#define FACIFLKSTAT FACI.FLKSTAT
#define FACIFRFSTEADR FACI.FRFSTEADR
#define FACIFRTSTAT FACI.FRTSTAT
#define FACIFCMDR FACI.FCMDR
#define FACIFPESTAT FACI.FPESTAT
#define FACIFBCCNT FACI.FBCCNT
#define FACIFBCSTAT FACI.FBCSTAT
#define FACIFPSADDR FACI.FPSADDR
#define FACIFCPSR FACI.FCPSR
#define FACIFPCKAR FACI.FPCKAR
#define FACIFECCEMON FACI.FECCEMON
#define FACIFECCTMD FACI.FECCTMD
#define FACIFDMYECC FACI.FDMYECC
#define PFSSBWCBUFEN PFSS.BWCBUFEN
#define CCIBFCUFAREA CCIB.FCUFAREA
#define RIIC0CR1 RIIC0.CR1.UINT32
#define RIIC0CR1L RIIC0.CR1.UINT16[L]
#define RIIC0CR1LL RIIC0.CR1.UINT8[LL]
#define RIIC0CR1LH RIIC0.CR1.UINT8[LH]
#define RIIC0CR1H RIIC0.CR1.UINT16[H]
#define RIIC0CR1HL RIIC0.CR1.UINT8[HL]
#define RIIC0CR1HH RIIC0.CR1.UINT8[HH]
#define RIIC0CR2 RIIC0.CR2.UINT32
#define RIIC0CR2L RIIC0.CR2.UINT16[L]
#define RIIC0CR2LL RIIC0.CR2.UINT8[LL]
#define RIIC0CR2LH RIIC0.CR2.UINT8[LH]
#define RIIC0CR2H RIIC0.CR2.UINT16[H]
#define RIIC0CR2HL RIIC0.CR2.UINT8[HL]
#define RIIC0CR2HH RIIC0.CR2.UINT8[HH]
#define RIIC0MR1 RIIC0.MR1.UINT32
#define RIIC0MR1L RIIC0.MR1.UINT16[L]
#define RIIC0MR1LL RIIC0.MR1.UINT8[LL]
#define RIIC0MR1LH RIIC0.MR1.UINT8[LH]
#define RIIC0MR1H RIIC0.MR1.UINT16[H]
#define RIIC0MR1HL RIIC0.MR1.UINT8[HL]
#define RIIC0MR1HH RIIC0.MR1.UINT8[HH]
#define RIIC0MR2 RIIC0.MR2.UINT32
#define RIIC0MR2L RIIC0.MR2.UINT16[L]
#define RIIC0MR2LL RIIC0.MR2.UINT8[LL]
#define RIIC0MR2LH RIIC0.MR2.UINT8[LH]
#define RIIC0MR2H RIIC0.MR2.UINT16[H]
#define RIIC0MR2HL RIIC0.MR2.UINT8[HL]
#define RIIC0MR2HH RIIC0.MR2.UINT8[HH]
#define RIIC0MR3 RIIC0.MR3.UINT32
#define RIIC0MR3L RIIC0.MR3.UINT16[L]
#define RIIC0MR3LL RIIC0.MR3.UINT8[LL]
#define RIIC0MR3LH RIIC0.MR3.UINT8[LH]
#define RIIC0MR3H RIIC0.MR3.UINT16[H]
#define RIIC0MR3HL RIIC0.MR3.UINT8[HL]
#define RIIC0MR3HH RIIC0.MR3.UINT8[HH]
#define RIIC0FER RIIC0.FER.UINT32
#define RIIC0FERL RIIC0.FER.UINT16[L]
#define RIIC0FERLL RIIC0.FER.UINT8[LL]
#define RIIC0FERLH RIIC0.FER.UINT8[LH]
#define RIIC0FERH RIIC0.FER.UINT16[H]
#define RIIC0FERHL RIIC0.FER.UINT8[HL]
#define RIIC0FERHH RIIC0.FER.UINT8[HH]
#define RIIC0SER RIIC0.SER.UINT32
#define RIIC0SERL RIIC0.SER.UINT16[L]
#define RIIC0SERLL RIIC0.SER.UINT8[LL]
#define RIIC0SERLH RIIC0.SER.UINT8[LH]
#define RIIC0SERH RIIC0.SER.UINT16[H]
#define RIIC0SERHL RIIC0.SER.UINT8[HL]
#define RIIC0SERHH RIIC0.SER.UINT8[HH]
#define RIIC0IER RIIC0.IER.UINT32
#define RIIC0IERL RIIC0.IER.UINT16[L]
#define RIIC0IERLL RIIC0.IER.UINT8[LL]
#define RIIC0IERLH RIIC0.IER.UINT8[LH]
#define RIIC0IERH RIIC0.IER.UINT16[H]
#define RIIC0IERHL RIIC0.IER.UINT8[HL]
#define RIIC0IERHH RIIC0.IER.UINT8[HH]
#define RIIC0SR1 RIIC0.SR1.UINT32
#define RIIC0SR1L RIIC0.SR1.UINT16[L]
#define RIIC0SR1LL RIIC0.SR1.UINT8[LL]
#define RIIC0SR1LH RIIC0.SR1.UINT8[LH]
#define RIIC0SR1H RIIC0.SR1.UINT16[H]
#define RIIC0SR1HL RIIC0.SR1.UINT8[HL]
#define RIIC0SR1HH RIIC0.SR1.UINT8[HH]
#define RIIC0AAS0 RIIC0.SR1.AAS0
#define RIIC0AAS1 RIIC0.SR1.AAS1
#define RIIC0AAS2 RIIC0.SR1.AAS2
#define RIIC0GCA RIIC0.SR1.GCA
#define RIIC0DID RIIC0.SR1.DID
#define RIIC0SR2 RIIC0.SR2.UINT32
#define RIIC0SR2L RIIC0.SR2.UINT16[L]
#define RIIC0SR2LL RIIC0.SR2.UINT8[LL]
#define RIIC0SR2LH RIIC0.SR2.UINT8[LH]
#define RIIC0SR2H RIIC0.SR2.UINT16[H]
#define RIIC0SR2HL RIIC0.SR2.UINT8[HL]
#define RIIC0SR2HH RIIC0.SR2.UINT8[HH]
#define RIIC0TMOF RIIC0.SR2.TMOF
#define RIIC0AL RIIC0.SR2.AL
#define RIIC0START RIIC0.SR2.START
#define RIIC0STOP RIIC0.SR2.STOP
#define RIIC0NACKF RIIC0.SR2.NACKF
#define RIIC0RDRF RIIC0.SR2.RDRF
#define RIIC0TEND RIIC0.SR2.TEND
#define RIIC0TDRE RIIC0.SR2.TDRE
#define RIIC0SAR0 RIIC0.SAR0.UINT32
#define RIIC0SAR0L RIIC0.SAR0.UINT16[L]
#define RIIC0SAR0LL RIIC0.SAR0.UINT8[LL]
#define RIIC0SAR0LH RIIC0.SAR0.UINT8[LH]
#define RIIC0SAR0H RIIC0.SAR0.UINT16[H]
#define RIIC0SAR0HL RIIC0.SAR0.UINT8[HL]
#define RIIC0SAR0HH RIIC0.SAR0.UINT8[HH]
#define RIIC0SAR1 RIIC0.SAR1.UINT32
#define RIIC0SAR1L RIIC0.SAR1.UINT16[L]
#define RIIC0SAR1LL RIIC0.SAR1.UINT8[LL]
#define RIIC0SAR1LH RIIC0.SAR1.UINT8[LH]
#define RIIC0SAR1H RIIC0.SAR1.UINT16[H]
#define RIIC0SAR1HL RIIC0.SAR1.UINT8[HL]
#define RIIC0SAR1HH RIIC0.SAR1.UINT8[HH]
#define RIIC0SAR2 RIIC0.SAR2.UINT32
#define RIIC0SAR2L RIIC0.SAR2.UINT16[L]
#define RIIC0SAR2LL RIIC0.SAR2.UINT8[LL]
#define RIIC0SAR2LH RIIC0.SAR2.UINT8[LH]
#define RIIC0SAR2H RIIC0.SAR2.UINT16[H]
#define RIIC0SAR2HL RIIC0.SAR2.UINT8[HL]
#define RIIC0SAR2HH RIIC0.SAR2.UINT8[HH]
#define RIIC0BRL RIIC0.BRL.UINT32
#define RIIC0BRLL RIIC0.BRL.UINT16[L]
#define RIIC0BRLLL RIIC0.BRL.UINT8[LL]
#define RIIC0BRLLH RIIC0.BRL.UINT8[LH]
#define RIIC0BRLH RIIC0.BRL.UINT16[H]
#define RIIC0BRLHL RIIC0.BRL.UINT8[HL]
#define RIIC0BRLHH RIIC0.BRL.UINT8[HH]
#define RIIC0BRH RIIC0.BRH.UINT32
#define RIIC0BRHL RIIC0.BRH.UINT16[L]
#define RIIC0BRHLL RIIC0.BRH.UINT8[LL]
#define RIIC0BRHLH RIIC0.BRH.UINT8[LH]
#define RIIC0BRHH RIIC0.BRH.UINT16[H]
#define RIIC0BRHHL RIIC0.BRH.UINT8[HL]
#define RIIC0BRHHH RIIC0.BRH.UINT8[HH]
#define RIIC0DRT RIIC0.DRT.UINT32
#define RIIC0DRTL RIIC0.DRT.UINT16[L]
#define RIIC0DRTLL RIIC0.DRT.UINT8[LL]
#define RIIC0DRTLH RIIC0.DRT.UINT8[LH]
#define RIIC0DRTH RIIC0.DRT.UINT16[H]
#define RIIC0DRTHL RIIC0.DRT.UINT8[HL]
#define RIIC0DRTHH RIIC0.DRT.UINT8[HH]
#define RIIC0DRR RIIC0.DRR.UINT32
#define RIIC0DRRL RIIC0.DRR.UINT16[L]
#define RIIC0DRRLL RIIC0.DRR.UINT8[LL]
#define RIIC0DRRLH RIIC0.DRR.UINT8[LH]
#define RIIC0DRRH RIIC0.DRR.UINT16[H]
#define RIIC0DRRHL RIIC0.DRR.UINT8[HL]
#define RIIC0DRRHH RIIC0.DRR.UINT8[HH]
#define SCDSPRDNAME1 SCDS.PRDNAME1
#define SCDSPRDNAME2 SCDS.PRDNAME2
#define SCDSPRDNAME3 SCDS.PRDNAME3
#define RLN240GLWBR RLN240.GLWBR
#define RLN240GLBRP0 RLN240.GLBRP0
#define RLN240GLBRP1 RLN240.GLBRP1
#define RLN240GLSTC RLN240.GLSTC
#define RLN2400L0MD RLN2400.L0MD
#define RLN2400L0BFC RLN2400.L0BFC
#define RLN2400L0SC RLN2400.L0SC
#define RLN2400L0WUP RLN2400.L0WUP
#define RLN2400L0IE RLN2400.L0IE
#define RLN2400L0EDE RLN2400.L0EDE
#define RLN2400L0CUC RLN2400.L0CUC
#define RLN2400L0TRC RLN2400.L0TRC
#define RLN2400L0MST RLN2400.L0MST
#define RLN2400L0ST RLN2400.L0ST
#define RLN2400L0EST RLN2400.L0EST
#define RLN2400L0DFC RLN2400.L0DFC
#define RLN2400L0IDB RLN2400.L0IDB
#define RLN2400L0CBR RLN2400.L0CBR
#define RLN2400L0DBR1 RLN2400.L0DBR1
#define RLN2400L0DBR2 RLN2400.L0DBR2
#define RLN2400L0DBR3 RLN2400.L0DBR3
#define RLN2400L0DBR4 RLN2400.L0DBR4
#define RLN2400L0DBR5 RLN2400.L0DBR5
#define RLN2400L0DBR6 RLN2400.L0DBR6
#define RLN2400L0DBR7 RLN2400.L0DBR7
#define RLN2400L0DBR8 RLN2400.L0DBR8
#define RLN2401L1MD RLN2401.L1MD
#define RLN2401L1BFC RLN2401.L1BFC
#define RLN2401L1SC RLN2401.L1SC
#define RLN2401L1WUP RLN2401.L1WUP
#define RLN2401L1IE RLN2401.L1IE
#define RLN2401L1EDE RLN2401.L1EDE
#define RLN2401L1CUC RLN2401.L1CUC
#define RLN2401L1TRC RLN2401.L1TRC
#define RLN2401L1MST RLN2401.L1MST
#define RLN2401L1ST RLN2401.L1ST
#define RLN2401L1EST RLN2401.L1EST
#define RLN2401L1DFC RLN2401.L1DFC
#define RLN2401L1IDB RLN2401.L1IDB
#define RLN2401L1CBR RLN2401.L1CBR
#define RLN2401L1DBR1 RLN2401.L1DBR1
#define RLN2401L1DBR2 RLN2401.L1DBR2
#define RLN2401L1DBR3 RLN2401.L1DBR3
#define RLN2401L1DBR4 RLN2401.L1DBR4
#define RLN2401L1DBR5 RLN2401.L1DBR5
#define RLN2401L1DBR6 RLN2401.L1DBR6
#define RLN2401L1DBR7 RLN2401.L1DBR7
#define RLN2401L1DBR8 RLN2401.L1DBR8
#define RLN2402L2MD RLN2402.L2MD
#define RLN2402L2BFC RLN2402.L2BFC
#define RLN2402L2SC RLN2402.L2SC
#define RLN2402L2WUP RLN2402.L2WUP
#define RLN2402L2IE RLN2402.L2IE
#define RLN2402L2EDE RLN2402.L2EDE
#define RLN2402L2CUC RLN2402.L2CUC
#define RLN2402L2TRC RLN2402.L2TRC
#define RLN2402L2MST RLN2402.L2MST
#define RLN2402L2ST RLN2402.L2ST
#define RLN2402L2EST RLN2402.L2EST
#define RLN2402L2DFC RLN2402.L2DFC
#define RLN2402L2IDB RLN2402.L2IDB
#define RLN2402L2CBR RLN2402.L2CBR
#define RLN2402L2DBR1 RLN2402.L2DBR1
#define RLN2402L2DBR2 RLN2402.L2DBR2
#define RLN2402L2DBR3 RLN2402.L2DBR3
#define RLN2402L2DBR4 RLN2402.L2DBR4
#define RLN2402L2DBR5 RLN2402.L2DBR5
#define RLN2402L2DBR6 RLN2402.L2DBR6
#define RLN2402L2DBR7 RLN2402.L2DBR7
#define RLN2402L2DBR8 RLN2402.L2DBR8
#define RLN2403L3MD RLN2403.L3MD
#define RLN2403L3BFC RLN2403.L3BFC
#define RLN2403L3SC RLN2403.L3SC
#define RLN2403L3WUP RLN2403.L3WUP
#define RLN2403L3IE RLN2403.L3IE
#define RLN2403L3EDE RLN2403.L3EDE
#define RLN2403L3CUC RLN2403.L3CUC
#define RLN2403L3TRC RLN2403.L3TRC
#define RLN2403L3MST RLN2403.L3MST
#define RLN2403L3ST RLN2403.L3ST
#define RLN2403L3EST RLN2403.L3EST
#define RLN2403L3DFC RLN2403.L3DFC
#define RLN2403L3IDB RLN2403.L3IDB
#define RLN2403L3CBR RLN2403.L3CBR
#define RLN2403L3DBR1 RLN2403.L3DBR1
#define RLN2403L3DBR2 RLN2403.L3DBR2
#define RLN2403L3DBR3 RLN2403.L3DBR3
#define RLN2403L3DBR4 RLN2403.L3DBR4
#define RLN2403L3DBR5 RLN2403.L3DBR5
#define RLN2403L3DBR6 RLN2403.L3DBR6
#define RLN2403L3DBR7 RLN2403.L3DBR7
#define RLN2403L3DBR8 RLN2403.L3DBR8
#define RLN241GLWBR RLN241.GLWBR
#define RLN241GLBRP0 RLN241.GLBRP0
#define RLN241GLBRP1 RLN241.GLBRP1
#define RLN241GLSTC RLN241.GLSTC
#define RLN2414L0MD RLN2414.L0MD
#define RLN2414L0BFC RLN2414.L0BFC
#define RLN2414L0SC RLN2414.L0SC
#define RLN2414L0WUP RLN2414.L0WUP
#define RLN2414L0IE RLN2414.L0IE
#define RLN2414L0EDE RLN2414.L0EDE
#define RLN2414L0CUC RLN2414.L0CUC
#define RLN2414L0TRC RLN2414.L0TRC
#define RLN2414L0MST RLN2414.L0MST
#define RLN2414L0ST RLN2414.L0ST
#define RLN2414L0EST RLN2414.L0EST
#define RLN2414L0DFC RLN2414.L0DFC
#define RLN2414L0IDB RLN2414.L0IDB
#define RLN2414L0CBR RLN2414.L0CBR
#define RLN2414L0DBR1 RLN2414.L0DBR1
#define RLN2414L0DBR2 RLN2414.L0DBR2
#define RLN2414L0DBR3 RLN2414.L0DBR3
#define RLN2414L0DBR4 RLN2414.L0DBR4
#define RLN2414L0DBR5 RLN2414.L0DBR5
#define RLN2414L0DBR6 RLN2414.L0DBR6
#define RLN2414L0DBR7 RLN2414.L0DBR7
#define RLN2414L0DBR8 RLN2414.L0DBR8
#define RLN2415L1MD RLN2415.L1MD
#define RLN2415L1BFC RLN2415.L1BFC
#define RLN2415L1SC RLN2415.L1SC
#define RLN2415L1WUP RLN2415.L1WUP
#define RLN2415L1IE RLN2415.L1IE
#define RLN2415L1EDE RLN2415.L1EDE
#define RLN2415L1CUC RLN2415.L1CUC
#define RLN2415L1TRC RLN2415.L1TRC
#define RLN2415L1MST RLN2415.L1MST
#define RLN2415L1ST RLN2415.L1ST
#define RLN2415L1EST RLN2415.L1EST
#define RLN2415L1DFC RLN2415.L1DFC
#define RLN2415L1IDB RLN2415.L1IDB
#define RLN2415L1CBR RLN2415.L1CBR
#define RLN2415L1DBR1 RLN2415.L1DBR1
#define RLN2415L1DBR2 RLN2415.L1DBR2
#define RLN2415L1DBR3 RLN2415.L1DBR3
#define RLN2415L1DBR4 RLN2415.L1DBR4
#define RLN2415L1DBR5 RLN2415.L1DBR5
#define RLN2415L1DBR6 RLN2415.L1DBR6
#define RLN2415L1DBR7 RLN2415.L1DBR7
#define RLN2415L1DBR8 RLN2415.L1DBR8
#define RLN2416L2MD RLN2416.L2MD
#define RLN2416L2BFC RLN2416.L2BFC
#define RLN2416L2SC RLN2416.L2SC
#define RLN2416L2WUP RLN2416.L2WUP
#define RLN2416L2IE RLN2416.L2IE
#define RLN2416L2EDE RLN2416.L2EDE
#define RLN2416L2CUC RLN2416.L2CUC
#define RLN2416L2TRC RLN2416.L2TRC
#define RLN2416L2MST RLN2416.L2MST
#define RLN2416L2ST RLN2416.L2ST
#define RLN2416L2EST RLN2416.L2EST
#define RLN2416L2DFC RLN2416.L2DFC
#define RLN2416L2IDB RLN2416.L2IDB
#define RLN2416L2CBR RLN2416.L2CBR
#define RLN2416L2DBR1 RLN2416.L2DBR1
#define RLN2416L2DBR2 RLN2416.L2DBR2
#define RLN2416L2DBR3 RLN2416.L2DBR3
#define RLN2416L2DBR4 RLN2416.L2DBR4
#define RLN2416L2DBR5 RLN2416.L2DBR5
#define RLN2416L2DBR6 RLN2416.L2DBR6
#define RLN2416L2DBR7 RLN2416.L2DBR7
#define RLN2416L2DBR8 RLN2416.L2DBR8
#define RLN2417L3MD RLN2417.L3MD
#define RLN2417L3BFC RLN2417.L3BFC
#define RLN2417L3SC RLN2417.L3SC
#define RLN2417L3WUP RLN2417.L3WUP
#define RLN2417L3IE RLN2417.L3IE
#define RLN2417L3EDE RLN2417.L3EDE
#define RLN2417L3CUC RLN2417.L3CUC
#define RLN2417L3TRC RLN2417.L3TRC
#define RLN2417L3MST RLN2417.L3MST
#define RLN2417L3ST RLN2417.L3ST
#define RLN2417L3EST RLN2417.L3EST
#define RLN2417L3DFC RLN2417.L3DFC
#define RLN2417L3IDB RLN2417.L3IDB
#define RLN2417L3CBR RLN2417.L3CBR
#define RLN2417L3DBR1 RLN2417.L3DBR1
#define RLN2417L3DBR2 RLN2417.L3DBR2
#define RLN2417L3DBR3 RLN2417.L3DBR3
#define RLN2417L3DBR4 RLN2417.L3DBR4
#define RLN2417L3DBR5 RLN2417.L3DBR5
#define RLN2417L3DBR6 RLN2417.L3DBR6
#define RLN2417L3DBR7 RLN2417.L3DBR7
#define RLN2417L3DBR8 RLN2417.L3DBR8
#define RLN210GLWBR RLN210.GLWBR
#define RLN210GLBRP0 RLN210.GLBRP0
#define RLN210GLBRP1 RLN210.GLBRP1
#define RLN210GLSTC RLN210.GLSTC
#define RLN2108L0MD RLN2108.L0MD
#define RLN2108L0BFC RLN2108.L0BFC
#define RLN2108L0SC RLN2108.L0SC
#define RLN2108L0WUP RLN2108.L0WUP
#define RLN2108L0IE RLN2108.L0IE
#define RLN2108L0EDE RLN2108.L0EDE
#define RLN2108L0CUC RLN2108.L0CUC
#define RLN2108L0TRC RLN2108.L0TRC
#define RLN2108L0MST RLN2108.L0MST
#define RLN2108L0ST RLN2108.L0ST
#define RLN2108L0EST RLN2108.L0EST
#define RLN2108L0DFC RLN2108.L0DFC
#define RLN2108L0IDB RLN2108.L0IDB
#define RLN2108L0CBR RLN2108.L0CBR
#define RLN2108L0DBR1 RLN2108.L0DBR1
#define RLN2108L0DBR2 RLN2108.L0DBR2
#define RLN2108L0DBR3 RLN2108.L0DBR3
#define RLN2108L0DBR4 RLN2108.L0DBR4
#define RLN2108L0DBR5 RLN2108.L0DBR5
#define RLN2108L0DBR6 RLN2108.L0DBR6
#define RLN2108L0DBR7 RLN2108.L0DBR7
#define RLN2108L0DBR8 RLN2108.L0DBR8
#define RLN211GLWBR RLN211.GLWBR
#define RLN211GLBRP0 RLN211.GLBRP0
#define RLN211GLBRP1 RLN211.GLBRP1
#define RLN211GLSTC RLN211.GLSTC
#define RLN2119L0MD RLN2119.L0MD
#define RLN2119L0BFC RLN2119.L0BFC
#define RLN2119L0SC RLN2119.L0SC
#define RLN2119L0WUP RLN2119.L0WUP
#define RLN2119L0IE RLN2119.L0IE
#define RLN2119L0EDE RLN2119.L0EDE
#define RLN2119L0CUC RLN2119.L0CUC
#define RLN2119L0TRC RLN2119.L0TRC
#define RLN2119L0MST RLN2119.L0MST
#define RLN2119L0ST RLN2119.L0ST
#define RLN2119L0EST RLN2119.L0EST
#define RLN2119L0DFC RLN2119.L0DFC
#define RLN2119L0IDB RLN2119.L0IDB
#define RLN2119L0CBR RLN2119.L0CBR
#define RLN2119L0DBR1 RLN2119.L0DBR1
#define RLN2119L0DBR2 RLN2119.L0DBR2
#define RLN2119L0DBR3 RLN2119.L0DBR3
#define RLN2119L0DBR4 RLN2119.L0DBR4
#define RLN2119L0DBR5 RLN2119.L0DBR5
#define RLN2119L0DBR6 RLN2119.L0DBR6
#define RLN2119L0DBR7 RLN2119.L0DBR7
#define RLN2119L0DBR8 RLN2119.L0DBR8
#define RLN30LWBR RLN30.LWBR
#define RLN30LBRP01 RLN30.LBRP01.UINT16
#define RLN30LBRP0 RLN30.LBRP01.UINT8[L]
#define RLN30LBRP1 RLN30.LBRP01.UINT8[H]
#define RLN30LSTC RLN30.LSTC
#define RLN30LMD RLN30.LMD
#define RLN30LBFC RLN30.LBFC
#define RLN30LSC RLN30.LSC
#define RLN30LWUP RLN30.LWUP
#define RLN30LIE RLN30.LIE
#define RLN30LEDE RLN30.LEDE
#define RLN30LCUC RLN30.LCUC
#define RLN30LTRC RLN30.LTRC
#define RLN30LMST RLN30.LMST
#define RLN30LST RLN30.LST
#define RLN30LEST RLN30.LEST
#define RLN30LDFC RLN30.LDFC
#define RLN30LIDB RLN30.LIDB
#define RLN30LCBR RLN30.LCBR
#define RLN30LUDB0 RLN30.LUDB0
#define RLN30LDBR1 RLN30.LDBR1
#define RLN30LDBR2 RLN30.LDBR2
#define RLN30LDBR3 RLN30.LDBR3
#define RLN30LDBR4 RLN30.LDBR4
#define RLN30LDBR5 RLN30.LDBR5
#define RLN30LDBR6 RLN30.LDBR6
#define RLN30LDBR7 RLN30.LDBR7
#define RLN30LDBR8 RLN30.LDBR8
#define RLN30LUOER RLN30.LUOER
#define RLN30LUOR1 RLN30.LUOR1
#define RLN30LUTDR RLN30.LUTDR.UINT16
#define RLN30LUTDRL RLN30.LUTDR.UINT8[L]
#define RLN30LUTDRH RLN30.LUTDR.UINT8[H]
#define RLN30LURDR RLN30.LURDR.UINT16
#define RLN30LURDRL RLN30.LURDR.UINT8[L]
#define RLN30LURDRH RLN30.LURDR.UINT8[H]
#define RLN30LUWTDR RLN30.LUWTDR.UINT16
#define RLN30LUWTDRL RLN30.LUWTDR.UINT8[L]
#define RLN30LUWTDRH RLN30.LUWTDR.UINT8[H]
#define RLN31LWBR RLN31.LWBR
#define RLN31LBRP01 RLN31.LBRP01.UINT16
#define RLN31LBRP0 RLN31.LBRP01.UINT8[L]
#define RLN31LBRP1 RLN31.LBRP01.UINT8[H]
#define RLN31LSTC RLN31.LSTC
#define RLN31LMD RLN31.LMD
#define RLN31LBFC RLN31.LBFC
#define RLN31LSC RLN31.LSC
#define RLN31LWUP RLN31.LWUP
#define RLN31LIE RLN31.LIE
#define RLN31LEDE RLN31.LEDE
#define RLN31LCUC RLN31.LCUC
#define RLN31LTRC RLN31.LTRC
#define RLN31LMST RLN31.LMST
#define RLN31LST RLN31.LST
#define RLN31LEST RLN31.LEST
#define RLN31LDFC RLN31.LDFC
#define RLN31LIDB RLN31.LIDB
#define RLN31LCBR RLN31.LCBR
#define RLN31LUDB0 RLN31.LUDB0
#define RLN31LDBR1 RLN31.LDBR1
#define RLN31LDBR2 RLN31.LDBR2
#define RLN31LDBR3 RLN31.LDBR3
#define RLN31LDBR4 RLN31.LDBR4
#define RLN31LDBR5 RLN31.LDBR5
#define RLN31LDBR6 RLN31.LDBR6
#define RLN31LDBR7 RLN31.LDBR7
#define RLN31LDBR8 RLN31.LDBR8
#define RLN31LUOER RLN31.LUOER
#define RLN31LUOR1 RLN31.LUOR1
#define RLN31LUTDR RLN31.LUTDR.UINT16
#define RLN31LUTDRL RLN31.LUTDR.UINT8[L]
#define RLN31LUTDRH RLN31.LUTDR.UINT8[H]
#define RLN31LURDR RLN31.LURDR.UINT16
#define RLN31LURDRL RLN31.LURDR.UINT8[L]
#define RLN31LURDRH RLN31.LURDR.UINT8[H]
#define RLN31LUWTDR RLN31.LUWTDR.UINT16
#define RLN31LUWTDRL RLN31.LUWTDR.UINT8[L]
#define RLN31LUWTDRH RLN31.LUWTDR.UINT8[H]
#define RLN32LWBR RLN32.LWBR
#define RLN32LBRP01 RLN32.LBRP01.UINT16
#define RLN32LBRP0 RLN32.LBRP01.UINT8[L]
#define RLN32LBRP1 RLN32.LBRP01.UINT8[H]
#define RLN32LSTC RLN32.LSTC
#define RLN32LMD RLN32.LMD
#define RLN32LBFC RLN32.LBFC
#define RLN32LSC RLN32.LSC
#define RLN32LWUP RLN32.LWUP
#define RLN32LIE RLN32.LIE
#define RLN32LEDE RLN32.LEDE
#define RLN32LCUC RLN32.LCUC
#define RLN32LTRC RLN32.LTRC
#define RLN32LMST RLN32.LMST
#define RLN32LST RLN32.LST
#define RLN32LEST RLN32.LEST
#define RLN32LDFC RLN32.LDFC
#define RLN32LIDB RLN32.LIDB
#define RLN32LCBR RLN32.LCBR
#define RLN32LUDB0 RLN32.LUDB0
#define RLN32LDBR1 RLN32.LDBR1
#define RLN32LDBR2 RLN32.LDBR2
#define RLN32LDBR3 RLN32.LDBR3
#define RLN32LDBR4 RLN32.LDBR4
#define RLN32LDBR5 RLN32.LDBR5
#define RLN32LDBR6 RLN32.LDBR6
#define RLN32LDBR7 RLN32.LDBR7
#define RLN32LDBR8 RLN32.LDBR8
#define RLN32LUOER RLN32.LUOER
#define RLN32LUOR1 RLN32.LUOR1
#define RLN32LUTDR RLN32.LUTDR.UINT16
#define RLN32LUTDRL RLN32.LUTDR.UINT8[L]
#define RLN32LUTDRH RLN32.LUTDR.UINT8[H]
#define RLN32LURDR RLN32.LURDR.UINT16
#define RLN32LURDRL RLN32.LURDR.UINT8[L]
#define RLN32LURDRH RLN32.LURDR.UINT8[H]
#define RLN32LUWTDR RLN32.LUWTDR.UINT16
#define RLN32LUWTDRL RLN32.LUWTDR.UINT8[L]
#define RLN32LUWTDRH RLN32.LUWTDR.UINT8[H]
#define RLN33LWBR RLN33.LWBR
#define RLN33LBRP01 RLN33.LBRP01.UINT16
#define RLN33LBRP0 RLN33.LBRP01.UINT8[L]
#define RLN33LBRP1 RLN33.LBRP01.UINT8[H]
#define RLN33LSTC RLN33.LSTC
#define RLN33LMD RLN33.LMD
#define RLN33LBFC RLN33.LBFC
#define RLN33LSC RLN33.LSC
#define RLN33LWUP RLN33.LWUP
#define RLN33LIE RLN33.LIE
#define RLN33LEDE RLN33.LEDE
#define RLN33LCUC RLN33.LCUC
#define RLN33LTRC RLN33.LTRC
#define RLN33LMST RLN33.LMST
#define RLN33LST RLN33.LST
#define RLN33LEST RLN33.LEST
#define RLN33LDFC RLN33.LDFC
#define RLN33LIDB RLN33.LIDB
#define RLN33LCBR RLN33.LCBR
#define RLN33LUDB0 RLN33.LUDB0
#define RLN33LDBR1 RLN33.LDBR1
#define RLN33LDBR2 RLN33.LDBR2
#define RLN33LDBR3 RLN33.LDBR3
#define RLN33LDBR4 RLN33.LDBR4
#define RLN33LDBR5 RLN33.LDBR5
#define RLN33LDBR6 RLN33.LDBR6
#define RLN33LDBR7 RLN33.LDBR7
#define RLN33LDBR8 RLN33.LDBR8
#define RLN33LUOER RLN33.LUOER
#define RLN33LUOR1 RLN33.LUOR1
#define RLN33LUTDR RLN33.LUTDR.UINT16
#define RLN33LUTDRL RLN33.LUTDR.UINT8[L]
#define RLN33LUTDRH RLN33.LUTDR.UINT8[H]
#define RLN33LURDR RLN33.LURDR.UINT16
#define RLN33LURDRL RLN33.LURDR.UINT8[L]
#define RLN33LURDRH RLN33.LURDR.UINT8[H]
#define RLN33LUWTDR RLN33.LUWTDR.UINT16
#define RLN33LUWTDRL RLN33.LUWTDR.UINT8[L]
#define RLN33LUWTDRH RLN33.LUWTDR.UINT8[H]
#define RLN34LWBR RLN34.LWBR
#define RLN34LBRP01 RLN34.LBRP01.UINT16
#define RLN34LBRP0 RLN34.LBRP01.UINT8[L]
#define RLN34LBRP1 RLN34.LBRP01.UINT8[H]
#define RLN34LSTC RLN34.LSTC
#define RLN34LMD RLN34.LMD
#define RLN34LBFC RLN34.LBFC
#define RLN34LSC RLN34.LSC
#define RLN34LWUP RLN34.LWUP
#define RLN34LIE RLN34.LIE
#define RLN34LEDE RLN34.LEDE
#define RLN34LCUC RLN34.LCUC
#define RLN34LTRC RLN34.LTRC
#define RLN34LMST RLN34.LMST
#define RLN34LST RLN34.LST
#define RLN34LEST RLN34.LEST
#define RLN34LDFC RLN34.LDFC
#define RLN34LIDB RLN34.LIDB
#define RLN34LCBR RLN34.LCBR
#define RLN34LUDB0 RLN34.LUDB0
#define RLN34LDBR1 RLN34.LDBR1
#define RLN34LDBR2 RLN34.LDBR2
#define RLN34LDBR3 RLN34.LDBR3
#define RLN34LDBR4 RLN34.LDBR4
#define RLN34LDBR5 RLN34.LDBR5
#define RLN34LDBR6 RLN34.LDBR6
#define RLN34LDBR7 RLN34.LDBR7
#define RLN34LDBR8 RLN34.LDBR8
#define RLN34LUOER RLN34.LUOER
#define RLN34LUOR1 RLN34.LUOR1
#define RLN34LUTDR RLN34.LUTDR.UINT16
#define RLN34LUTDRL RLN34.LUTDR.UINT8[L]
#define RLN34LUTDRH RLN34.LUTDR.UINT8[H]
#define RLN34LURDR RLN34.LURDR.UINT16
#define RLN34LURDRL RLN34.LURDR.UINT8[L]
#define RLN34LURDRH RLN34.LURDR.UINT8[H]
#define RLN34LUWTDR RLN34.LUWTDR.UINT16
#define RLN34LUWTDRL RLN34.LUWTDR.UINT8[L]
#define RLN34LUWTDRH RLN34.LUWTDR.UINT8[H]
#define RLN35LWBR RLN35.LWBR
#define RLN35LBRP01 RLN35.LBRP01.UINT16
#define RLN35LBRP0 RLN35.LBRP01.UINT8[L]
#define RLN35LBRP1 RLN35.LBRP01.UINT8[H]
#define RLN35LSTC RLN35.LSTC
#define RLN35LMD RLN35.LMD
#define RLN35LBFC RLN35.LBFC
#define RLN35LSC RLN35.LSC
#define RLN35LWUP RLN35.LWUP
#define RLN35LIE RLN35.LIE
#define RLN35LEDE RLN35.LEDE
#define RLN35LCUC RLN35.LCUC
#define RLN35LTRC RLN35.LTRC
#define RLN35LMST RLN35.LMST
#define RLN35LST RLN35.LST
#define RLN35LEST RLN35.LEST
#define RLN35LDFC RLN35.LDFC
#define RLN35LIDB RLN35.LIDB
#define RLN35LCBR RLN35.LCBR
#define RLN35LUDB0 RLN35.LUDB0
#define RLN35LDBR1 RLN35.LDBR1
#define RLN35LDBR2 RLN35.LDBR2
#define RLN35LDBR3 RLN35.LDBR3
#define RLN35LDBR4 RLN35.LDBR4
#define RLN35LDBR5 RLN35.LDBR5
#define RLN35LDBR6 RLN35.LDBR6
#define RLN35LDBR7 RLN35.LDBR7
#define RLN35LDBR8 RLN35.LDBR8
#define RLN35LUOER RLN35.LUOER
#define RLN35LUOR1 RLN35.LUOR1
#define RLN35LUTDR RLN35.LUTDR.UINT16
#define RLN35LUTDRL RLN35.LUTDR.UINT8[L]
#define RLN35LUTDRH RLN35.LUTDR.UINT8[H]
#define RLN35LURDR RLN35.LURDR.UINT16
#define RLN35LURDRL RLN35.LURDR.UINT8[L]
#define RLN35LURDRH RLN35.LURDR.UINT8[H]
#define RLN35LUWTDR RLN35.LUWTDR.UINT16
#define RLN35LUWTDRL RLN35.LUWTDR.UINT8[L]
#define RLN35LUWTDRH RLN35.LUWTDR.UINT8[H]
#define RSCAN0C0CFG RSCAN0.C0CFG.UINT32
#define RSCAN0C0CFGL RSCAN0.C0CFG.UINT16[L]
#define RSCAN0C0CFGLL RSCAN0.C0CFG.UINT8[LL]
#define RSCAN0C0CFGLH RSCAN0.C0CFG.UINT8[LH]
#define RSCAN0C0CFGH RSCAN0.C0CFG.UINT16[H]
#define RSCAN0C0CFGHL RSCAN0.C0CFG.UINT8[HL]
#define RSCAN0C0CFGHH RSCAN0.C0CFG.UINT8[HH]
#define RSCAN0C0CTR RSCAN0.C0CTR.UINT32
#define RSCAN0C0CTRL RSCAN0.C0CTR.UINT16[L]
#define RSCAN0C0CTRLL RSCAN0.C0CTR.UINT8[LL]
#define RSCAN0C0CTRLH RSCAN0.C0CTR.UINT8[LH]
#define RSCAN0C0CTRH RSCAN0.C0CTR.UINT16[H]
#define RSCAN0C0CTRHL RSCAN0.C0CTR.UINT8[HL]
#define RSCAN0C0CTRHH RSCAN0.C0CTR.UINT8[HH]
#define RSCAN0C0STS RSCAN0.C0STS.UINT32
#define RSCAN0C0STSL RSCAN0.C0STS.UINT16[L]
#define RSCAN0C0STSLL RSCAN0.C0STS.UINT8[LL]
#define RSCAN0C0STSH RSCAN0.C0STS.UINT16[H]
#define RSCAN0C0STSHL RSCAN0.C0STS.UINT8[HL]
#define RSCAN0C0STSHH RSCAN0.C0STS.UINT8[HH]
#define RSCAN0C0ERFL RSCAN0.C0ERFL.UINT32
#define RSCAN0C0ERFLL RSCAN0.C0ERFL.UINT16[L]
#define RSCAN0C0ERFLLL RSCAN0.C0ERFL.UINT8[LL]
#define RSCAN0C0ERFLLH RSCAN0.C0ERFL.UINT8[LH]
#define RSCAN0C0ERFLH RSCAN0.C0ERFL.UINT16[H]
#define RSCAN0C0ERFLHL RSCAN0.C0ERFL.UINT8[HL]
#define RSCAN0C0ERFLHH RSCAN0.C0ERFL.UINT8[HH]
#define RSCAN0C1CFG RSCAN0.C1CFG.UINT32
#define RSCAN0C1CFGL RSCAN0.C1CFG.UINT16[L]
#define RSCAN0C1CFGLL RSCAN0.C1CFG.UINT8[LL]
#define RSCAN0C1CFGLH RSCAN0.C1CFG.UINT8[LH]
#define RSCAN0C1CFGH RSCAN0.C1CFG.UINT16[H]
#define RSCAN0C1CFGHL RSCAN0.C1CFG.UINT8[HL]
#define RSCAN0C1CFGHH RSCAN0.C1CFG.UINT8[HH]
#define RSCAN0C1CTR RSCAN0.C1CTR.UINT32
#define RSCAN0C1CTRL RSCAN0.C1CTR.UINT16[L]
#define RSCAN0C1CTRLL RSCAN0.C1CTR.UINT8[LL]
#define RSCAN0C1CTRLH RSCAN0.C1CTR.UINT8[LH]
#define RSCAN0C1CTRH RSCAN0.C1CTR.UINT16[H]
#define RSCAN0C1CTRHL RSCAN0.C1CTR.UINT8[HL]
#define RSCAN0C1CTRHH RSCAN0.C1CTR.UINT8[HH]
#define RSCAN0C1STS RSCAN0.C1STS.UINT32
#define RSCAN0C1STSL RSCAN0.C1STS.UINT16[L]
#define RSCAN0C1STSLL RSCAN0.C1STS.UINT8[LL]
#define RSCAN0C1STSH RSCAN0.C1STS.UINT16[H]
#define RSCAN0C1STSHL RSCAN0.C1STS.UINT8[HL]
#define RSCAN0C1STSHH RSCAN0.C1STS.UINT8[HH]
#define RSCAN0C1ERFL RSCAN0.C1ERFL.UINT32
#define RSCAN0C1ERFLL RSCAN0.C1ERFL.UINT16[L]
#define RSCAN0C1ERFLLL RSCAN0.C1ERFL.UINT8[LL]
#define RSCAN0C1ERFLLH RSCAN0.C1ERFL.UINT8[LH]
#define RSCAN0C1ERFLH RSCAN0.C1ERFL.UINT16[H]
#define RSCAN0C1ERFLHL RSCAN0.C1ERFL.UINT8[HL]
#define RSCAN0C1ERFLHH RSCAN0.C1ERFL.UINT8[HH]
#define RSCAN0C2CFG RSCAN0.C2CFG.UINT32
#define RSCAN0C2CFGL RSCAN0.C2CFG.UINT16[L]
#define RSCAN0C2CFGLL RSCAN0.C2CFG.UINT8[LL]
#define RSCAN0C2CFGLH RSCAN0.C2CFG.UINT8[LH]
#define RSCAN0C2CFGH RSCAN0.C2CFG.UINT16[H]
#define RSCAN0C2CFGHL RSCAN0.C2CFG.UINT8[HL]
#define RSCAN0C2CFGHH RSCAN0.C2CFG.UINT8[HH]
#define RSCAN0C2CTR RSCAN0.C2CTR.UINT32
#define RSCAN0C2CTRL RSCAN0.C2CTR.UINT16[L]
#define RSCAN0C2CTRLL RSCAN0.C2CTR.UINT8[LL]
#define RSCAN0C2CTRLH RSCAN0.C2CTR.UINT8[LH]
#define RSCAN0C2CTRH RSCAN0.C2CTR.UINT16[H]
#define RSCAN0C2CTRHL RSCAN0.C2CTR.UINT8[HL]
#define RSCAN0C2CTRHH RSCAN0.C2CTR.UINT8[HH]
#define RSCAN0C2STS RSCAN0.C2STS.UINT32
#define RSCAN0C2STSL RSCAN0.C2STS.UINT16[L]
#define RSCAN0C2STSLL RSCAN0.C2STS.UINT8[LL]
#define RSCAN0C2STSH RSCAN0.C2STS.UINT16[H]
#define RSCAN0C2STSHL RSCAN0.C2STS.UINT8[HL]
#define RSCAN0C2STSHH RSCAN0.C2STS.UINT8[HH]
#define RSCAN0C2ERFL RSCAN0.C2ERFL.UINT32
#define RSCAN0C2ERFLL RSCAN0.C2ERFL.UINT16[L]
#define RSCAN0C2ERFLLL RSCAN0.C2ERFL.UINT8[LL]
#define RSCAN0C2ERFLLH RSCAN0.C2ERFL.UINT8[LH]
#define RSCAN0C2ERFLH RSCAN0.C2ERFL.UINT16[H]
#define RSCAN0C2ERFLHL RSCAN0.C2ERFL.UINT8[HL]
#define RSCAN0C2ERFLHH RSCAN0.C2ERFL.UINT8[HH]
#define RSCAN0C3CFG RSCAN0.C3CFG.UINT32
#define RSCAN0C3CFGL RSCAN0.C3CFG.UINT16[L]
#define RSCAN0C3CFGLL RSCAN0.C3CFG.UINT8[LL]
#define RSCAN0C3CFGLH RSCAN0.C3CFG.UINT8[LH]
#define RSCAN0C3CFGH RSCAN0.C3CFG.UINT16[H]
#define RSCAN0C3CFGHL RSCAN0.C3CFG.UINT8[HL]
#define RSCAN0C3CFGHH RSCAN0.C3CFG.UINT8[HH]
#define RSCAN0C3CTR RSCAN0.C3CTR.UINT32
#define RSCAN0C3CTRL RSCAN0.C3CTR.UINT16[L]
#define RSCAN0C3CTRLL RSCAN0.C3CTR.UINT8[LL]
#define RSCAN0C3CTRLH RSCAN0.C3CTR.UINT8[LH]
#define RSCAN0C3CTRH RSCAN0.C3CTR.UINT16[H]
#define RSCAN0C3CTRHL RSCAN0.C3CTR.UINT8[HL]
#define RSCAN0C3CTRHH RSCAN0.C3CTR.UINT8[HH]
#define RSCAN0C3STS RSCAN0.C3STS.UINT32
#define RSCAN0C3STSL RSCAN0.C3STS.UINT16[L]
#define RSCAN0C3STSLL RSCAN0.C3STS.UINT8[LL]
#define RSCAN0C3STSH RSCAN0.C3STS.UINT16[H]
#define RSCAN0C3STSHL RSCAN0.C3STS.UINT8[HL]
#define RSCAN0C3STSHH RSCAN0.C3STS.UINT8[HH]
#define RSCAN0C3ERFL RSCAN0.C3ERFL.UINT32
#define RSCAN0C3ERFLL RSCAN0.C3ERFL.UINT16[L]
#define RSCAN0C3ERFLLL RSCAN0.C3ERFL.UINT8[LL]
#define RSCAN0C3ERFLLH RSCAN0.C3ERFL.UINT8[LH]
#define RSCAN0C3ERFLH RSCAN0.C3ERFL.UINT16[H]
#define RSCAN0C3ERFLHL RSCAN0.C3ERFL.UINT8[HL]
#define RSCAN0C3ERFLHH RSCAN0.C3ERFL.UINT8[HH]
#define RSCAN0C4CFG RSCAN0.C4CFG.UINT32
#define RSCAN0C4CFGL RSCAN0.C4CFG.UINT16[L]
#define RSCAN0C4CFGLL RSCAN0.C4CFG.UINT8[LL]
#define RSCAN0C4CFGLH RSCAN0.C4CFG.UINT8[LH]
#define RSCAN0C4CFGH RSCAN0.C4CFG.UINT16[H]
#define RSCAN0C4CFGHL RSCAN0.C4CFG.UINT8[HL]
#define RSCAN0C4CFGHH RSCAN0.C4CFG.UINT8[HH]
#define RSCAN0C4CTR RSCAN0.C4CTR.UINT32
#define RSCAN0C4CTRL RSCAN0.C4CTR.UINT16[L]
#define RSCAN0C4CTRLL RSCAN0.C4CTR.UINT8[LL]
#define RSCAN0C4CTRLH RSCAN0.C4CTR.UINT8[LH]
#define RSCAN0C4CTRH RSCAN0.C4CTR.UINT16[H]
#define RSCAN0C4CTRHL RSCAN0.C4CTR.UINT8[HL]
#define RSCAN0C4CTRHH RSCAN0.C4CTR.UINT8[HH]
#define RSCAN0C4STS RSCAN0.C4STS.UINT32
#define RSCAN0C4STSL RSCAN0.C4STS.UINT16[L]
#define RSCAN0C4STSLL RSCAN0.C4STS.UINT8[LL]
#define RSCAN0C4STSH RSCAN0.C4STS.UINT16[H]
#define RSCAN0C4STSHL RSCAN0.C4STS.UINT8[HL]
#define RSCAN0C4STSHH RSCAN0.C4STS.UINT8[HH]
#define RSCAN0C4ERFL RSCAN0.C4ERFL.UINT32
#define RSCAN0C4ERFLL RSCAN0.C4ERFL.UINT16[L]
#define RSCAN0C4ERFLLL RSCAN0.C4ERFL.UINT8[LL]
#define RSCAN0C4ERFLLH RSCAN0.C4ERFL.UINT8[LH]
#define RSCAN0C4ERFLH RSCAN0.C4ERFL.UINT16[H]
#define RSCAN0C4ERFLHL RSCAN0.C4ERFL.UINT8[HL]
#define RSCAN0C4ERFLHH RSCAN0.C4ERFL.UINT8[HH]
#define RSCAN0C5CFG RSCAN0.C5CFG.UINT32
#define RSCAN0C5CFGL RSCAN0.C5CFG.UINT16[L]
#define RSCAN0C5CFGLL RSCAN0.C5CFG.UINT8[LL]
#define RSCAN0C5CFGLH RSCAN0.C5CFG.UINT8[LH]
#define RSCAN0C5CFGH RSCAN0.C5CFG.UINT16[H]
#define RSCAN0C5CFGHL RSCAN0.C5CFG.UINT8[HL]
#define RSCAN0C5CFGHH RSCAN0.C5CFG.UINT8[HH]
#define RSCAN0C5CTR RSCAN0.C5CTR.UINT32
#define RSCAN0C5CTRL RSCAN0.C5CTR.UINT16[L]
#define RSCAN0C5CTRLL RSCAN0.C5CTR.UINT8[LL]
#define RSCAN0C5CTRLH RSCAN0.C5CTR.UINT8[LH]
#define RSCAN0C5CTRH RSCAN0.C5CTR.UINT16[H]
#define RSCAN0C5CTRHL RSCAN0.C5CTR.UINT8[HL]
#define RSCAN0C5CTRHH RSCAN0.C5CTR.UINT8[HH]
#define RSCAN0C5STS RSCAN0.C5STS.UINT32
#define RSCAN0C5STSL RSCAN0.C5STS.UINT16[L]
#define RSCAN0C5STSLL RSCAN0.C5STS.UINT8[LL]
#define RSCAN0C5STSH RSCAN0.C5STS.UINT16[H]
#define RSCAN0C5STSHL RSCAN0.C5STS.UINT8[HL]
#define RSCAN0C5STSHH RSCAN0.C5STS.UINT8[HH]
#define RSCAN0C5ERFL RSCAN0.C5ERFL.UINT32
#define RSCAN0C5ERFLL RSCAN0.C5ERFL.UINT16[L]
#define RSCAN0C5ERFLLL RSCAN0.C5ERFL.UINT8[LL]
#define RSCAN0C5ERFLLH RSCAN0.C5ERFL.UINT8[LH]
#define RSCAN0C5ERFLH RSCAN0.C5ERFL.UINT16[H]
#define RSCAN0C5ERFLHL RSCAN0.C5ERFL.UINT8[HL]
#define RSCAN0C5ERFLHH RSCAN0.C5ERFL.UINT8[HH]
#define RSCAN0GCFG RSCAN0.GCFG.UINT32
#define RSCAN0GCFGL RSCAN0.GCFG.UINT16[L]
#define RSCAN0GCFGLL RSCAN0.GCFG.UINT8[LL]
#define RSCAN0GCFGLH RSCAN0.GCFG.UINT8[LH]
#define RSCAN0GCFGH RSCAN0.GCFG.UINT16[H]
#define RSCAN0GCFGHL RSCAN0.GCFG.UINT8[HL]
#define RSCAN0GCFGHH RSCAN0.GCFG.UINT8[HH]
#define RSCAN0GCTR RSCAN0.GCTR.UINT32
#define RSCAN0GCTRL RSCAN0.GCTR.UINT16[L]
#define RSCAN0GCTRLL RSCAN0.GCTR.UINT8[LL]
#define RSCAN0GCTRLH RSCAN0.GCTR.UINT8[LH]
#define RSCAN0GCTRH RSCAN0.GCTR.UINT16[H]
#define RSCAN0GCTRHL RSCAN0.GCTR.UINT8[HL]
#define RSCAN0GSTS RSCAN0.GSTS.UINT32
#define RSCAN0GSTSL RSCAN0.GSTS.UINT16[L]
#define RSCAN0GSTSLL RSCAN0.GSTS.UINT8[LL]
#define RSCAN0GERFL RSCAN0.GERFL.UINT32
#define RSCAN0GERFLL RSCAN0.GERFL.UINT16[L]
#define RSCAN0GERFLLL RSCAN0.GERFL.UINT8[LL]
#define RSCAN0GTSC RSCAN0.GTSC.UINT32
#define RSCAN0GTSCL RSCAN0.GTSC.UINT16[L]
#define RSCAN0GAFLECTR RSCAN0.GAFLECTR.UINT32
#define RSCAN0GAFLECTRL RSCAN0.GAFLECTR.UINT16[L]
#define RSCAN0GAFLECTRLL RSCAN0.GAFLECTR.UINT8[LL]
#define RSCAN0GAFLECTRLH RSCAN0.GAFLECTR.UINT8[LH]
#define RSCAN0GAFLCFG0 RSCAN0.GAFLCFG0.UINT32
#define RSCAN0GAFLCFG0L RSCAN0.GAFLCFG0.UINT16[L]
#define RSCAN0GAFLCFG0LL RSCAN0.GAFLCFG0.UINT8[LL]
#define RSCAN0GAFLCFG0LH RSCAN0.GAFLCFG0.UINT8[LH]
#define RSCAN0GAFLCFG0H RSCAN0.GAFLCFG0.UINT16[H]
#define RSCAN0GAFLCFG0HL RSCAN0.GAFLCFG0.UINT8[HL]
#define RSCAN0GAFLCFG0HH RSCAN0.GAFLCFG0.UINT8[HH]
#define RSCAN0GAFLCFG1 RSCAN0.GAFLCFG1.UINT32
#define RSCAN0GAFLCFG1H RSCAN0.GAFLCFG1.UINT16[H]
#define RSCAN0GAFLCFG1HL RSCAN0.GAFLCFG1.UINT8[HL]
#define RSCAN0GAFLCFG1HH RSCAN0.GAFLCFG1.UINT8[HH]
#define RSCAN0RMNB RSCAN0.RMNB.UINT32
#define RSCAN0RMNBL RSCAN0.RMNB.UINT16[L]
#define RSCAN0RMNBLL RSCAN0.RMNB.UINT8[LL]
#define RSCAN0RMND0 RSCAN0.RMND0.UINT32
#define RSCAN0RMND0L RSCAN0.RMND0.UINT16[L]
#define RSCAN0RMND0LL RSCAN0.RMND0.UINT8[LL]
#define RSCAN0RMND0LH RSCAN0.RMND0.UINT8[LH]
#define RSCAN0RMND0H RSCAN0.RMND0.UINT16[H]
#define RSCAN0RMND0HL RSCAN0.RMND0.UINT8[HL]
#define RSCAN0RMND0HH RSCAN0.RMND0.UINT8[HH]
#define RSCAN0RMND1 RSCAN0.RMND1.UINT32
#define RSCAN0RMND1L RSCAN0.RMND1.UINT16[L]
#define RSCAN0RMND1LL RSCAN0.RMND1.UINT8[LL]
#define RSCAN0RMND1LH RSCAN0.RMND1.UINT8[LH]
#define RSCAN0RMND1H RSCAN0.RMND1.UINT16[H]
#define RSCAN0RMND1HL RSCAN0.RMND1.UINT8[HL]
#define RSCAN0RMND1HH RSCAN0.RMND1.UINT8[HH]
#define RSCAN0RMND2 RSCAN0.RMND2.UINT32
#define RSCAN0RMND2L RSCAN0.RMND2.UINT16[L]
#define RSCAN0RMND2LL RSCAN0.RMND2.UINT8[LL]
#define RSCAN0RMND2LH RSCAN0.RMND2.UINT8[LH]
#define RSCAN0RMND2H RSCAN0.RMND2.UINT16[H]
#define RSCAN0RMND2HL RSCAN0.RMND2.UINT8[HL]
#define RSCAN0RMND2HH RSCAN0.RMND2.UINT8[HH]
#define RSCAN0RFCC0 RSCAN0.RFCC0.UINT32
#define RSCAN0RFCC0L RSCAN0.RFCC0.UINT16[L]
#define RSCAN0RFCC0LL RSCAN0.RFCC0.UINT8[LL]
#define RSCAN0RFCC0LH RSCAN0.RFCC0.UINT8[LH]
#define RSCAN0RFCC1 RSCAN0.RFCC1.UINT32
#define RSCAN0RFCC1L RSCAN0.RFCC1.UINT16[L]
#define RSCAN0RFCC1LL RSCAN0.RFCC1.UINT8[LL]
#define RSCAN0RFCC1LH RSCAN0.RFCC1.UINT8[LH]
#define RSCAN0RFCC2 RSCAN0.RFCC2.UINT32
#define RSCAN0RFCC2L RSCAN0.RFCC2.UINT16[L]
#define RSCAN0RFCC2LL RSCAN0.RFCC2.UINT8[LL]
#define RSCAN0RFCC2LH RSCAN0.RFCC2.UINT8[LH]
#define RSCAN0RFCC3 RSCAN0.RFCC3.UINT32
#define RSCAN0RFCC3L RSCAN0.RFCC3.UINT16[L]
#define RSCAN0RFCC3LL RSCAN0.RFCC3.UINT8[LL]
#define RSCAN0RFCC3LH RSCAN0.RFCC3.UINT8[LH]
#define RSCAN0RFCC4 RSCAN0.RFCC4.UINT32
#define RSCAN0RFCC4L RSCAN0.RFCC4.UINT16[L]
#define RSCAN0RFCC4LL RSCAN0.RFCC4.UINT8[LL]
#define RSCAN0RFCC4LH RSCAN0.RFCC4.UINT8[LH]
#define RSCAN0RFCC5 RSCAN0.RFCC5.UINT32
#define RSCAN0RFCC5L RSCAN0.RFCC5.UINT16[L]
#define RSCAN0RFCC5LL RSCAN0.RFCC5.UINT8[LL]
#define RSCAN0RFCC5LH RSCAN0.RFCC5.UINT8[LH]
#define RSCAN0RFCC6 RSCAN0.RFCC6.UINT32
#define RSCAN0RFCC6L RSCAN0.RFCC6.UINT16[L]
#define RSCAN0RFCC6LL RSCAN0.RFCC6.UINT8[LL]
#define RSCAN0RFCC6LH RSCAN0.RFCC6.UINT8[LH]
#define RSCAN0RFCC7 RSCAN0.RFCC7.UINT32
#define RSCAN0RFCC7L RSCAN0.RFCC7.UINT16[L]
#define RSCAN0RFCC7LL RSCAN0.RFCC7.UINT8[LL]
#define RSCAN0RFCC7LH RSCAN0.RFCC7.UINT8[LH]
#define RSCAN0RFSTS0 RSCAN0.RFSTS0.UINT32
#define RSCAN0RFSTS0L RSCAN0.RFSTS0.UINT16[L]
#define RSCAN0RFSTS0LL RSCAN0.RFSTS0.UINT8[LL]
#define RSCAN0RFSTS0LH RSCAN0.RFSTS0.UINT8[LH]
#define RSCAN0RFSTS1 RSCAN0.RFSTS1.UINT32
#define RSCAN0RFSTS1L RSCAN0.RFSTS1.UINT16[L]
#define RSCAN0RFSTS1LL RSCAN0.RFSTS1.UINT8[LL]
#define RSCAN0RFSTS1LH RSCAN0.RFSTS1.UINT8[LH]
#define RSCAN0RFSTS2 RSCAN0.RFSTS2.UINT32
#define RSCAN0RFSTS2L RSCAN0.RFSTS2.UINT16[L]
#define RSCAN0RFSTS2LL RSCAN0.RFSTS2.UINT8[LL]
#define RSCAN0RFSTS2LH RSCAN0.RFSTS2.UINT8[LH]
#define RSCAN0RFSTS3 RSCAN0.RFSTS3.UINT32
#define RSCAN0RFSTS3L RSCAN0.RFSTS3.UINT16[L]
#define RSCAN0RFSTS3LL RSCAN0.RFSTS3.UINT8[LL]
#define RSCAN0RFSTS3LH RSCAN0.RFSTS3.UINT8[LH]
#define RSCAN0RFSTS4 RSCAN0.RFSTS4.UINT32
#define RSCAN0RFSTS4L RSCAN0.RFSTS4.UINT16[L]
#define RSCAN0RFSTS4LL RSCAN0.RFSTS4.UINT8[LL]
#define RSCAN0RFSTS4LH RSCAN0.RFSTS4.UINT8[LH]
#define RSCAN0RFSTS5 RSCAN0.RFSTS5.UINT32
#define RSCAN0RFSTS5L RSCAN0.RFSTS5.UINT16[L]
#define RSCAN0RFSTS5LL RSCAN0.RFSTS5.UINT8[LL]
#define RSCAN0RFSTS5LH RSCAN0.RFSTS5.UINT8[LH]
#define RSCAN0RFSTS6 RSCAN0.RFSTS6.UINT32
#define RSCAN0RFSTS6L RSCAN0.RFSTS6.UINT16[L]
#define RSCAN0RFSTS6LL RSCAN0.RFSTS6.UINT8[LL]
#define RSCAN0RFSTS6LH RSCAN0.RFSTS6.UINT8[LH]
#define RSCAN0RFSTS7 RSCAN0.RFSTS7.UINT32
#define RSCAN0RFSTS7L RSCAN0.RFSTS7.UINT16[L]
#define RSCAN0RFSTS7LL RSCAN0.RFSTS7.UINT8[LL]
#define RSCAN0RFSTS7LH RSCAN0.RFSTS7.UINT8[LH]
#define RSCAN0RFPCTR0 RSCAN0.RFPCTR0.UINT32
#define RSCAN0RFPCTR0L RSCAN0.RFPCTR0.UINT16[L]
#define RSCAN0RFPCTR0LL RSCAN0.RFPCTR0.UINT8[LL]
#define RSCAN0RFPCTR1 RSCAN0.RFPCTR1.UINT32
#define RSCAN0RFPCTR1L RSCAN0.RFPCTR1.UINT16[L]
#define RSCAN0RFPCTR1LL RSCAN0.RFPCTR1.UINT8[LL]
#define RSCAN0RFPCTR2 RSCAN0.RFPCTR2.UINT32
#define RSCAN0RFPCTR2L RSCAN0.RFPCTR2.UINT16[L]
#define RSCAN0RFPCTR2LL RSCAN0.RFPCTR2.UINT8[LL]
#define RSCAN0RFPCTR3 RSCAN0.RFPCTR3.UINT32
#define RSCAN0RFPCTR3L RSCAN0.RFPCTR3.UINT16[L]
#define RSCAN0RFPCTR3LL RSCAN0.RFPCTR3.UINT8[LL]
#define RSCAN0RFPCTR4 RSCAN0.RFPCTR4.UINT32
#define RSCAN0RFPCTR4L RSCAN0.RFPCTR4.UINT16[L]
#define RSCAN0RFPCTR4LL RSCAN0.RFPCTR4.UINT8[LL]
#define RSCAN0RFPCTR5 RSCAN0.RFPCTR5.UINT32
#define RSCAN0RFPCTR5L RSCAN0.RFPCTR5.UINT16[L]
#define RSCAN0RFPCTR5LL RSCAN0.RFPCTR5.UINT8[LL]
#define RSCAN0RFPCTR6 RSCAN0.RFPCTR6.UINT32
#define RSCAN0RFPCTR6L RSCAN0.RFPCTR6.UINT16[L]
#define RSCAN0RFPCTR6LL RSCAN0.RFPCTR6.UINT8[LL]
#define RSCAN0RFPCTR7 RSCAN0.RFPCTR7.UINT32
#define RSCAN0RFPCTR7L RSCAN0.RFPCTR7.UINT16[L]
#define RSCAN0RFPCTR7LL RSCAN0.RFPCTR7.UINT8[LL]
#define RSCAN0CFCC0 RSCAN0.CFCC0.UINT32
#define RSCAN0CFCC0L RSCAN0.CFCC0.UINT16[L]
#define RSCAN0CFCC0LL RSCAN0.CFCC0.UINT8[LL]
#define RSCAN0CFCC0LH RSCAN0.CFCC0.UINT8[LH]
#define RSCAN0CFCC0H RSCAN0.CFCC0.UINT16[H]
#define RSCAN0CFCC0HL RSCAN0.CFCC0.UINT8[HL]
#define RSCAN0CFCC0HH RSCAN0.CFCC0.UINT8[HH]
#define RSCAN0CFCC1 RSCAN0.CFCC1.UINT32
#define RSCAN0CFCC1L RSCAN0.CFCC1.UINT16[L]
#define RSCAN0CFCC1LL RSCAN0.CFCC1.UINT8[LL]
#define RSCAN0CFCC1LH RSCAN0.CFCC1.UINT8[LH]
#define RSCAN0CFCC1H RSCAN0.CFCC1.UINT16[H]
#define RSCAN0CFCC1HL RSCAN0.CFCC1.UINT8[HL]
#define RSCAN0CFCC1HH RSCAN0.CFCC1.UINT8[HH]
#define RSCAN0CFCC2 RSCAN0.CFCC2.UINT32
#define RSCAN0CFCC2L RSCAN0.CFCC2.UINT16[L]
#define RSCAN0CFCC2LL RSCAN0.CFCC2.UINT8[LL]
#define RSCAN0CFCC2LH RSCAN0.CFCC2.UINT8[LH]
#define RSCAN0CFCC2H RSCAN0.CFCC2.UINT16[H]
#define RSCAN0CFCC2HL RSCAN0.CFCC2.UINT8[HL]
#define RSCAN0CFCC2HH RSCAN0.CFCC2.UINT8[HH]
#define RSCAN0CFCC3 RSCAN0.CFCC3.UINT32
#define RSCAN0CFCC3L RSCAN0.CFCC3.UINT16[L]
#define RSCAN0CFCC3LL RSCAN0.CFCC3.UINT8[LL]
#define RSCAN0CFCC3LH RSCAN0.CFCC3.UINT8[LH]
#define RSCAN0CFCC3H RSCAN0.CFCC3.UINT16[H]
#define RSCAN0CFCC3HL RSCAN0.CFCC3.UINT8[HL]
#define RSCAN0CFCC3HH RSCAN0.CFCC3.UINT8[HH]
#define RSCAN0CFCC4 RSCAN0.CFCC4.UINT32
#define RSCAN0CFCC4L RSCAN0.CFCC4.UINT16[L]
#define RSCAN0CFCC4LL RSCAN0.CFCC4.UINT8[LL]
#define RSCAN0CFCC4LH RSCAN0.CFCC4.UINT8[LH]
#define RSCAN0CFCC4H RSCAN0.CFCC4.UINT16[H]
#define RSCAN0CFCC4HL RSCAN0.CFCC4.UINT8[HL]
#define RSCAN0CFCC4HH RSCAN0.CFCC4.UINT8[HH]
#define RSCAN0CFCC5 RSCAN0.CFCC5.UINT32
#define RSCAN0CFCC5L RSCAN0.CFCC5.UINT16[L]
#define RSCAN0CFCC5LL RSCAN0.CFCC5.UINT8[LL]
#define RSCAN0CFCC5LH RSCAN0.CFCC5.UINT8[LH]
#define RSCAN0CFCC5H RSCAN0.CFCC5.UINT16[H]
#define RSCAN0CFCC5HL RSCAN0.CFCC5.UINT8[HL]
#define RSCAN0CFCC5HH RSCAN0.CFCC5.UINT8[HH]
#define RSCAN0CFCC6 RSCAN0.CFCC6.UINT32
#define RSCAN0CFCC6L RSCAN0.CFCC6.UINT16[L]
#define RSCAN0CFCC6LL RSCAN0.CFCC6.UINT8[LL]
#define RSCAN0CFCC6LH RSCAN0.CFCC6.UINT8[LH]
#define RSCAN0CFCC6H RSCAN0.CFCC6.UINT16[H]
#define RSCAN0CFCC6HL RSCAN0.CFCC6.UINT8[HL]
#define RSCAN0CFCC6HH RSCAN0.CFCC6.UINT8[HH]
#define RSCAN0CFCC7 RSCAN0.CFCC7.UINT32
#define RSCAN0CFCC7L RSCAN0.CFCC7.UINT16[L]
#define RSCAN0CFCC7LL RSCAN0.CFCC7.UINT8[LL]
#define RSCAN0CFCC7LH RSCAN0.CFCC7.UINT8[LH]
#define RSCAN0CFCC7H RSCAN0.CFCC7.UINT16[H]
#define RSCAN0CFCC7HL RSCAN0.CFCC7.UINT8[HL]
#define RSCAN0CFCC7HH RSCAN0.CFCC7.UINT8[HH]
#define RSCAN0CFCC8 RSCAN0.CFCC8.UINT32
#define RSCAN0CFCC8L RSCAN0.CFCC8.UINT16[L]
#define RSCAN0CFCC8LL RSCAN0.CFCC8.UINT8[LL]
#define RSCAN0CFCC8LH RSCAN0.CFCC8.UINT8[LH]
#define RSCAN0CFCC8H RSCAN0.CFCC8.UINT16[H]
#define RSCAN0CFCC8HL RSCAN0.CFCC8.UINT8[HL]
#define RSCAN0CFCC8HH RSCAN0.CFCC8.UINT8[HH]
#define RSCAN0CFCC9 RSCAN0.CFCC9.UINT32
#define RSCAN0CFCC9L RSCAN0.CFCC9.UINT16[L]
#define RSCAN0CFCC9LL RSCAN0.CFCC9.UINT8[LL]
#define RSCAN0CFCC9LH RSCAN0.CFCC9.UINT8[LH]
#define RSCAN0CFCC9H RSCAN0.CFCC9.UINT16[H]
#define RSCAN0CFCC9HL RSCAN0.CFCC9.UINT8[HL]
#define RSCAN0CFCC9HH RSCAN0.CFCC9.UINT8[HH]
#define RSCAN0CFCC10 RSCAN0.CFCC10.UINT32
#define RSCAN0CFCC10L RSCAN0.CFCC10.UINT16[L]
#define RSCAN0CFCC10LL RSCAN0.CFCC10.UINT8[LL]
#define RSCAN0CFCC10LH RSCAN0.CFCC10.UINT8[LH]
#define RSCAN0CFCC10H RSCAN0.CFCC10.UINT16[H]
#define RSCAN0CFCC10HL RSCAN0.CFCC10.UINT8[HL]
#define RSCAN0CFCC10HH RSCAN0.CFCC10.UINT8[HH]
#define RSCAN0CFCC11 RSCAN0.CFCC11.UINT32
#define RSCAN0CFCC11L RSCAN0.CFCC11.UINT16[L]
#define RSCAN0CFCC11LL RSCAN0.CFCC11.UINT8[LL]
#define RSCAN0CFCC11LH RSCAN0.CFCC11.UINT8[LH]
#define RSCAN0CFCC11H RSCAN0.CFCC11.UINT16[H]
#define RSCAN0CFCC11HL RSCAN0.CFCC11.UINT8[HL]
#define RSCAN0CFCC11HH RSCAN0.CFCC11.UINT8[HH]
#define RSCAN0CFCC12 RSCAN0.CFCC12.UINT32
#define RSCAN0CFCC12L RSCAN0.CFCC12.UINT16[L]
#define RSCAN0CFCC12LL RSCAN0.CFCC12.UINT8[LL]
#define RSCAN0CFCC12LH RSCAN0.CFCC12.UINT8[LH]
#define RSCAN0CFCC12H RSCAN0.CFCC12.UINT16[H]
#define RSCAN0CFCC12HL RSCAN0.CFCC12.UINT8[HL]
#define RSCAN0CFCC12HH RSCAN0.CFCC12.UINT8[HH]
#define RSCAN0CFCC13 RSCAN0.CFCC13.UINT32
#define RSCAN0CFCC13L RSCAN0.CFCC13.UINT16[L]
#define RSCAN0CFCC13LL RSCAN0.CFCC13.UINT8[LL]
#define RSCAN0CFCC13LH RSCAN0.CFCC13.UINT8[LH]
#define RSCAN0CFCC13H RSCAN0.CFCC13.UINT16[H]
#define RSCAN0CFCC13HL RSCAN0.CFCC13.UINT8[HL]
#define RSCAN0CFCC13HH RSCAN0.CFCC13.UINT8[HH]
#define RSCAN0CFCC14 RSCAN0.CFCC14.UINT32
#define RSCAN0CFCC14L RSCAN0.CFCC14.UINT16[L]
#define RSCAN0CFCC14LL RSCAN0.CFCC14.UINT8[LL]
#define RSCAN0CFCC14LH RSCAN0.CFCC14.UINT8[LH]
#define RSCAN0CFCC14H RSCAN0.CFCC14.UINT16[H]
#define RSCAN0CFCC14HL RSCAN0.CFCC14.UINT8[HL]
#define RSCAN0CFCC14HH RSCAN0.CFCC14.UINT8[HH]
#define RSCAN0CFCC15 RSCAN0.CFCC15.UINT32
#define RSCAN0CFCC15L RSCAN0.CFCC15.UINT16[L]
#define RSCAN0CFCC15LL RSCAN0.CFCC15.UINT8[LL]
#define RSCAN0CFCC15LH RSCAN0.CFCC15.UINT8[LH]
#define RSCAN0CFCC15H RSCAN0.CFCC15.UINT16[H]
#define RSCAN0CFCC15HL RSCAN0.CFCC15.UINT8[HL]
#define RSCAN0CFCC15HH RSCAN0.CFCC15.UINT8[HH]
#define RSCAN0CFCC16 RSCAN0.CFCC16.UINT32
#define RSCAN0CFCC16L RSCAN0.CFCC16.UINT16[L]
#define RSCAN0CFCC16LL RSCAN0.CFCC16.UINT8[LL]
#define RSCAN0CFCC16LH RSCAN0.CFCC16.UINT8[LH]
#define RSCAN0CFCC16H RSCAN0.CFCC16.UINT16[H]
#define RSCAN0CFCC16HL RSCAN0.CFCC16.UINT8[HL]
#define RSCAN0CFCC16HH RSCAN0.CFCC16.UINT8[HH]
#define RSCAN0CFCC17 RSCAN0.CFCC17.UINT32
#define RSCAN0CFCC17L RSCAN0.CFCC17.UINT16[L]
#define RSCAN0CFCC17LL RSCAN0.CFCC17.UINT8[LL]
#define RSCAN0CFCC17LH RSCAN0.CFCC17.UINT8[LH]
#define RSCAN0CFCC17H RSCAN0.CFCC17.UINT16[H]
#define RSCAN0CFCC17HL RSCAN0.CFCC17.UINT8[HL]
#define RSCAN0CFCC17HH RSCAN0.CFCC17.UINT8[HH]
#define RSCAN0CFSTS0 RSCAN0.CFSTS0.UINT32
#define RSCAN0CFSTS0L RSCAN0.CFSTS0.UINT16[L]
#define RSCAN0CFSTS0LL RSCAN0.CFSTS0.UINT8[LL]
#define RSCAN0CFSTS0LH RSCAN0.CFSTS0.UINT8[LH]
#define RSCAN0CFSTS1 RSCAN0.CFSTS1.UINT32
#define RSCAN0CFSTS1L RSCAN0.CFSTS1.UINT16[L]
#define RSCAN0CFSTS1LL RSCAN0.CFSTS1.UINT8[LL]
#define RSCAN0CFSTS1LH RSCAN0.CFSTS1.UINT8[LH]
#define RSCAN0CFSTS2 RSCAN0.CFSTS2.UINT32
#define RSCAN0CFSTS2L RSCAN0.CFSTS2.UINT16[L]
#define RSCAN0CFSTS2LL RSCAN0.CFSTS2.UINT8[LL]
#define RSCAN0CFSTS2LH RSCAN0.CFSTS2.UINT8[LH]
#define RSCAN0CFSTS3 RSCAN0.CFSTS3.UINT32
#define RSCAN0CFSTS3L RSCAN0.CFSTS3.UINT16[L]
#define RSCAN0CFSTS3LL RSCAN0.CFSTS3.UINT8[LL]
#define RSCAN0CFSTS3LH RSCAN0.CFSTS3.UINT8[LH]
#define RSCAN0CFSTS4 RSCAN0.CFSTS4.UINT32
#define RSCAN0CFSTS4L RSCAN0.CFSTS4.UINT16[L]
#define RSCAN0CFSTS4LL RSCAN0.CFSTS4.UINT8[LL]
#define RSCAN0CFSTS4LH RSCAN0.CFSTS4.UINT8[LH]
#define RSCAN0CFSTS5 RSCAN0.CFSTS5.UINT32
#define RSCAN0CFSTS5L RSCAN0.CFSTS5.UINT16[L]
#define RSCAN0CFSTS5LL RSCAN0.CFSTS5.UINT8[LL]
#define RSCAN0CFSTS5LH RSCAN0.CFSTS5.UINT8[LH]
#define RSCAN0CFSTS6 RSCAN0.CFSTS6.UINT32
#define RSCAN0CFSTS6L RSCAN0.CFSTS6.UINT16[L]
#define RSCAN0CFSTS6LL RSCAN0.CFSTS6.UINT8[LL]
#define RSCAN0CFSTS6LH RSCAN0.CFSTS6.UINT8[LH]
#define RSCAN0CFSTS7 RSCAN0.CFSTS7.UINT32
#define RSCAN0CFSTS7L RSCAN0.CFSTS7.UINT16[L]
#define RSCAN0CFSTS7LL RSCAN0.CFSTS7.UINT8[LL]
#define RSCAN0CFSTS7LH RSCAN0.CFSTS7.UINT8[LH]
#define RSCAN0CFSTS8 RSCAN0.CFSTS8.UINT32
#define RSCAN0CFSTS8L RSCAN0.CFSTS8.UINT16[L]
#define RSCAN0CFSTS8LL RSCAN0.CFSTS8.UINT8[LL]
#define RSCAN0CFSTS8LH RSCAN0.CFSTS8.UINT8[LH]
#define RSCAN0CFSTS9 RSCAN0.CFSTS9.UINT32
#define RSCAN0CFSTS9L RSCAN0.CFSTS9.UINT16[L]
#define RSCAN0CFSTS9LL RSCAN0.CFSTS9.UINT8[LL]
#define RSCAN0CFSTS9LH RSCAN0.CFSTS9.UINT8[LH]
#define RSCAN0CFSTS10 RSCAN0.CFSTS10.UINT32
#define RSCAN0CFSTS10L RSCAN0.CFSTS10.UINT16[L]
#define RSCAN0CFSTS10LL RSCAN0.CFSTS10.UINT8[LL]
#define RSCAN0CFSTS10LH RSCAN0.CFSTS10.UINT8[LH]
#define RSCAN0CFSTS11 RSCAN0.CFSTS11.UINT32
#define RSCAN0CFSTS11L RSCAN0.CFSTS11.UINT16[L]
#define RSCAN0CFSTS11LL RSCAN0.CFSTS11.UINT8[LL]
#define RSCAN0CFSTS11LH RSCAN0.CFSTS11.UINT8[LH]
#define RSCAN0CFSTS12 RSCAN0.CFSTS12.UINT32
#define RSCAN0CFSTS12L RSCAN0.CFSTS12.UINT16[L]
#define RSCAN0CFSTS12LL RSCAN0.CFSTS12.UINT8[LL]
#define RSCAN0CFSTS12LH RSCAN0.CFSTS12.UINT8[LH]
#define RSCAN0CFSTS13 RSCAN0.CFSTS13.UINT32
#define RSCAN0CFSTS13L RSCAN0.CFSTS13.UINT16[L]
#define RSCAN0CFSTS13LL RSCAN0.CFSTS13.UINT8[LL]
#define RSCAN0CFSTS13LH RSCAN0.CFSTS13.UINT8[LH]
#define RSCAN0CFSTS14 RSCAN0.CFSTS14.UINT32
#define RSCAN0CFSTS14L RSCAN0.CFSTS14.UINT16[L]
#define RSCAN0CFSTS14LL RSCAN0.CFSTS14.UINT8[LL]
#define RSCAN0CFSTS14LH RSCAN0.CFSTS14.UINT8[LH]
#define RSCAN0CFSTS15 RSCAN0.CFSTS15.UINT32
#define RSCAN0CFSTS15L RSCAN0.CFSTS15.UINT16[L]
#define RSCAN0CFSTS15LL RSCAN0.CFSTS15.UINT8[LL]
#define RSCAN0CFSTS15LH RSCAN0.CFSTS15.UINT8[LH]
#define RSCAN0CFSTS16 RSCAN0.CFSTS16.UINT32
#define RSCAN0CFSTS16L RSCAN0.CFSTS16.UINT16[L]
#define RSCAN0CFSTS16LL RSCAN0.CFSTS16.UINT8[LL]
#define RSCAN0CFSTS16LH RSCAN0.CFSTS16.UINT8[LH]
#define RSCAN0CFSTS17 RSCAN0.CFSTS17.UINT32
#define RSCAN0CFSTS17L RSCAN0.CFSTS17.UINT16[L]
#define RSCAN0CFSTS17LL RSCAN0.CFSTS17.UINT8[LL]
#define RSCAN0CFSTS17LH RSCAN0.CFSTS17.UINT8[LH]
#define RSCAN0CFPCTR0 RSCAN0.CFPCTR0.UINT32
#define RSCAN0CFPCTR0L RSCAN0.CFPCTR0.UINT16[L]
#define RSCAN0CFPCTR0LL RSCAN0.CFPCTR0.UINT8[LL]
#define RSCAN0CFPCTR1 RSCAN0.CFPCTR1.UINT32
#define RSCAN0CFPCTR1L RSCAN0.CFPCTR1.UINT16[L]
#define RSCAN0CFPCTR1LL RSCAN0.CFPCTR1.UINT8[LL]
#define RSCAN0CFPCTR2 RSCAN0.CFPCTR2.UINT32
#define RSCAN0CFPCTR2L RSCAN0.CFPCTR2.UINT16[L]
#define RSCAN0CFPCTR2LL RSCAN0.CFPCTR2.UINT8[LL]
#define RSCAN0CFPCTR3 RSCAN0.CFPCTR3.UINT32
#define RSCAN0CFPCTR3L RSCAN0.CFPCTR3.UINT16[L]
#define RSCAN0CFPCTR3LL RSCAN0.CFPCTR3.UINT8[LL]
#define RSCAN0CFPCTR4 RSCAN0.CFPCTR4.UINT32
#define RSCAN0CFPCTR4L RSCAN0.CFPCTR4.UINT16[L]
#define RSCAN0CFPCTR4LL RSCAN0.CFPCTR4.UINT8[LL]
#define RSCAN0CFPCTR5 RSCAN0.CFPCTR5.UINT32
#define RSCAN0CFPCTR5L RSCAN0.CFPCTR5.UINT16[L]
#define RSCAN0CFPCTR5LL RSCAN0.CFPCTR5.UINT8[LL]
#define RSCAN0CFPCTR6 RSCAN0.CFPCTR6.UINT32
#define RSCAN0CFPCTR6L RSCAN0.CFPCTR6.UINT16[L]
#define RSCAN0CFPCTR6LL RSCAN0.CFPCTR6.UINT8[LL]
#define RSCAN0CFPCTR7 RSCAN0.CFPCTR7.UINT32
#define RSCAN0CFPCTR7L RSCAN0.CFPCTR7.UINT16[L]
#define RSCAN0CFPCTR7LL RSCAN0.CFPCTR7.UINT8[LL]
#define RSCAN0CFPCTR8 RSCAN0.CFPCTR8.UINT32
#define RSCAN0CFPCTR8L RSCAN0.CFPCTR8.UINT16[L]
#define RSCAN0CFPCTR8LL RSCAN0.CFPCTR8.UINT8[LL]
#define RSCAN0CFPCTR9 RSCAN0.CFPCTR9.UINT32
#define RSCAN0CFPCTR9L RSCAN0.CFPCTR9.UINT16[L]
#define RSCAN0CFPCTR9LL RSCAN0.CFPCTR9.UINT8[LL]
#define RSCAN0CFPCTR10 RSCAN0.CFPCTR10.UINT32
#define RSCAN0CFPCTR10L RSCAN0.CFPCTR10.UINT16[L]
#define RSCAN0CFPCTR10LL RSCAN0.CFPCTR10.UINT8[LL]
#define RSCAN0CFPCTR11 RSCAN0.CFPCTR11.UINT32
#define RSCAN0CFPCTR11L RSCAN0.CFPCTR11.UINT16[L]
#define RSCAN0CFPCTR11LL RSCAN0.CFPCTR11.UINT8[LL]
#define RSCAN0CFPCTR12 RSCAN0.CFPCTR12.UINT32
#define RSCAN0CFPCTR12L RSCAN0.CFPCTR12.UINT16[L]
#define RSCAN0CFPCTR12LL RSCAN0.CFPCTR12.UINT8[LL]
#define RSCAN0CFPCTR13 RSCAN0.CFPCTR13.UINT32
#define RSCAN0CFPCTR13L RSCAN0.CFPCTR13.UINT16[L]
#define RSCAN0CFPCTR13LL RSCAN0.CFPCTR13.UINT8[LL]
#define RSCAN0CFPCTR14 RSCAN0.CFPCTR14.UINT32
#define RSCAN0CFPCTR14L RSCAN0.CFPCTR14.UINT16[L]
#define RSCAN0CFPCTR14LL RSCAN0.CFPCTR14.UINT8[LL]
#define RSCAN0CFPCTR15 RSCAN0.CFPCTR15.UINT32
#define RSCAN0CFPCTR15L RSCAN0.CFPCTR15.UINT16[L]
#define RSCAN0CFPCTR15LL RSCAN0.CFPCTR15.UINT8[LL]
#define RSCAN0CFPCTR16 RSCAN0.CFPCTR16.UINT32
#define RSCAN0CFPCTR16L RSCAN0.CFPCTR16.UINT16[L]
#define RSCAN0CFPCTR16LL RSCAN0.CFPCTR16.UINT8[LL]
#define RSCAN0CFPCTR17 RSCAN0.CFPCTR17.UINT32
#define RSCAN0CFPCTR17L RSCAN0.CFPCTR17.UINT16[L]
#define RSCAN0CFPCTR17LL RSCAN0.CFPCTR17.UINT8[LL]
#define RSCAN0FESTS RSCAN0.FESTS.UINT32
#define RSCAN0FESTSL RSCAN0.FESTS.UINT16[L]
#define RSCAN0FESTSLL RSCAN0.FESTS.UINT8[LL]
#define RSCAN0FESTSLH RSCAN0.FESTS.UINT8[LH]
#define RSCAN0FESTSH RSCAN0.FESTS.UINT16[H]
#define RSCAN0FESTSHL RSCAN0.FESTS.UINT8[HL]
#define RSCAN0FESTSHH RSCAN0.FESTS.UINT8[HH]
#define RSCAN0FFSTS RSCAN0.FFSTS.UINT32
#define RSCAN0FFSTSL RSCAN0.FFSTS.UINT16[L]
#define RSCAN0FFSTSLL RSCAN0.FFSTS.UINT8[LL]
#define RSCAN0FFSTSLH RSCAN0.FFSTS.UINT8[LH]
#define RSCAN0FFSTSH RSCAN0.FFSTS.UINT16[H]
#define RSCAN0FFSTSHL RSCAN0.FFSTS.UINT8[HL]
#define RSCAN0FFSTSHH RSCAN0.FFSTS.UINT8[HH]
#define RSCAN0FMSTS RSCAN0.FMSTS.UINT32
#define RSCAN0FMSTSL RSCAN0.FMSTS.UINT16[L]
#define RSCAN0FMSTSLL RSCAN0.FMSTS.UINT8[LL]
#define RSCAN0FMSTSLH RSCAN0.FMSTS.UINT8[LH]
#define RSCAN0FMSTSH RSCAN0.FMSTS.UINT16[H]
#define RSCAN0FMSTSHL RSCAN0.FMSTS.UINT8[HL]
#define RSCAN0FMSTSHH RSCAN0.FMSTS.UINT8[HH]
#define RSCAN0RFISTS RSCAN0.RFISTS.UINT32
#define RSCAN0RFISTSL RSCAN0.RFISTS.UINT16[L]
#define RSCAN0RFISTSLL RSCAN0.RFISTS.UINT8[LL]
#define RSCAN0CFRISTS RSCAN0.CFRISTS.UINT32
#define RSCAN0CFRISTSL RSCAN0.CFRISTS.UINT16[L]
#define RSCAN0CFRISTSLL RSCAN0.CFRISTS.UINT8[LL]
#define RSCAN0CFRISTSLH RSCAN0.CFRISTS.UINT8[LH]
#define RSCAN0CFRISTSH RSCAN0.CFRISTS.UINT16[H]
#define RSCAN0CFRISTSHL RSCAN0.CFRISTS.UINT8[HL]
#define RSCAN0CFTISTS RSCAN0.CFTISTS.UINT32
#define RSCAN0CFTISTSL RSCAN0.CFTISTS.UINT16[L]
#define RSCAN0CFTISTSLL RSCAN0.CFTISTS.UINT8[LL]
#define RSCAN0CFTISTSLH RSCAN0.CFTISTS.UINT8[LH]
#define RSCAN0CFTISTSH RSCAN0.CFTISTS.UINT16[H]
#define RSCAN0CFTISTSHL RSCAN0.CFTISTS.UINT8[HL]
#define RSCAN0TMC0 RSCAN0.TMC0
#define RSCAN0TMC1 RSCAN0.TMC1
#define RSCAN0TMC2 RSCAN0.TMC2
#define RSCAN0TMC3 RSCAN0.TMC3
#define RSCAN0TMC4 RSCAN0.TMC4
#define RSCAN0TMC5 RSCAN0.TMC5
#define RSCAN0TMC6 RSCAN0.TMC6
#define RSCAN0TMC7 RSCAN0.TMC7
#define RSCAN0TMC8 RSCAN0.TMC8
#define RSCAN0TMC9 RSCAN0.TMC9
#define RSCAN0TMC10 RSCAN0.TMC10
#define RSCAN0TMC11 RSCAN0.TMC11
#define RSCAN0TMC12 RSCAN0.TMC12
#define RSCAN0TMC13 RSCAN0.TMC13
#define RSCAN0TMC14 RSCAN0.TMC14
#define RSCAN0TMC15 RSCAN0.TMC15
#define RSCAN0TMC16 RSCAN0.TMC16
#define RSCAN0TMC17 RSCAN0.TMC17
#define RSCAN0TMC18 RSCAN0.TMC18
#define RSCAN0TMC19 RSCAN0.TMC19
#define RSCAN0TMC20 RSCAN0.TMC20
#define RSCAN0TMC21 RSCAN0.TMC21
#define RSCAN0TMC22 RSCAN0.TMC22
#define RSCAN0TMC23 RSCAN0.TMC23
#define RSCAN0TMC24 RSCAN0.TMC24
#define RSCAN0TMC25 RSCAN0.TMC25
#define RSCAN0TMC26 RSCAN0.TMC26
#define RSCAN0TMC27 RSCAN0.TMC27
#define RSCAN0TMC28 RSCAN0.TMC28
#define RSCAN0TMC29 RSCAN0.TMC29
#define RSCAN0TMC30 RSCAN0.TMC30
#define RSCAN0TMC31 RSCAN0.TMC31
#define RSCAN0TMC32 RSCAN0.TMC32
#define RSCAN0TMC33 RSCAN0.TMC33
#define RSCAN0TMC34 RSCAN0.TMC34
#define RSCAN0TMC35 RSCAN0.TMC35
#define RSCAN0TMC36 RSCAN0.TMC36
#define RSCAN0TMC37 RSCAN0.TMC37
#define RSCAN0TMC38 RSCAN0.TMC38
#define RSCAN0TMC39 RSCAN0.TMC39
#define RSCAN0TMC40 RSCAN0.TMC40
#define RSCAN0TMC41 RSCAN0.TMC41
#define RSCAN0TMC42 RSCAN0.TMC42
#define RSCAN0TMC43 RSCAN0.TMC43
#define RSCAN0TMC44 RSCAN0.TMC44
#define RSCAN0TMC45 RSCAN0.TMC45
#define RSCAN0TMC46 RSCAN0.TMC46
#define RSCAN0TMC47 RSCAN0.TMC47
#define RSCAN0TMC48 RSCAN0.TMC48
#define RSCAN0TMC49 RSCAN0.TMC49
#define RSCAN0TMC50 RSCAN0.TMC50
#define RSCAN0TMC51 RSCAN0.TMC51
#define RSCAN0TMC52 RSCAN0.TMC52
#define RSCAN0TMC53 RSCAN0.TMC53
#define RSCAN0TMC54 RSCAN0.TMC54
#define RSCAN0TMC55 RSCAN0.TMC55
#define RSCAN0TMC56 RSCAN0.TMC56
#define RSCAN0TMC57 RSCAN0.TMC57
#define RSCAN0TMC58 RSCAN0.TMC58
#define RSCAN0TMC59 RSCAN0.TMC59
#define RSCAN0TMC60 RSCAN0.TMC60
#define RSCAN0TMC61 RSCAN0.TMC61
#define RSCAN0TMC62 RSCAN0.TMC62
#define RSCAN0TMC63 RSCAN0.TMC63
#define RSCAN0TMC64 RSCAN0.TMC64
#define RSCAN0TMC65 RSCAN0.TMC65
#define RSCAN0TMC66 RSCAN0.TMC66
#define RSCAN0TMC67 RSCAN0.TMC67
#define RSCAN0TMC68 RSCAN0.TMC68
#define RSCAN0TMC69 RSCAN0.TMC69
#define RSCAN0TMC70 RSCAN0.TMC70
#define RSCAN0TMC71 RSCAN0.TMC71
#define RSCAN0TMC72 RSCAN0.TMC72
#define RSCAN0TMC73 RSCAN0.TMC73
#define RSCAN0TMC74 RSCAN0.TMC74
#define RSCAN0TMC75 RSCAN0.TMC75
#define RSCAN0TMC76 RSCAN0.TMC76
#define RSCAN0TMC77 RSCAN0.TMC77
#define RSCAN0TMC78 RSCAN0.TMC78
#define RSCAN0TMC79 RSCAN0.TMC79
#define RSCAN0TMC80 RSCAN0.TMC80
#define RSCAN0TMC81 RSCAN0.TMC81
#define RSCAN0TMC82 RSCAN0.TMC82
#define RSCAN0TMC83 RSCAN0.TMC83
#define RSCAN0TMC84 RSCAN0.TMC84
#define RSCAN0TMC85 RSCAN0.TMC85
#define RSCAN0TMC86 RSCAN0.TMC86
#define RSCAN0TMC87 RSCAN0.TMC87
#define RSCAN0TMC88 RSCAN0.TMC88
#define RSCAN0TMC89 RSCAN0.TMC89
#define RSCAN0TMC90 RSCAN0.TMC90
#define RSCAN0TMC91 RSCAN0.TMC91
#define RSCAN0TMC92 RSCAN0.TMC92
#define RSCAN0TMC93 RSCAN0.TMC93
#define RSCAN0TMC94 RSCAN0.TMC94
#define RSCAN0TMC95 RSCAN0.TMC95
#define RSCAN0TMSTS0 RSCAN0.TMSTS0
#define RSCAN0TMSTS1 RSCAN0.TMSTS1
#define RSCAN0TMSTS2 RSCAN0.TMSTS2
#define RSCAN0TMSTS3 RSCAN0.TMSTS3
#define RSCAN0TMSTS4 RSCAN0.TMSTS4
#define RSCAN0TMSTS5 RSCAN0.TMSTS5
#define RSCAN0TMSTS6 RSCAN0.TMSTS6
#define RSCAN0TMSTS7 RSCAN0.TMSTS7
#define RSCAN0TMSTS8 RSCAN0.TMSTS8
#define RSCAN0TMSTS9 RSCAN0.TMSTS9
#define RSCAN0TMSTS10 RSCAN0.TMSTS10
#define RSCAN0TMSTS11 RSCAN0.TMSTS11
#define RSCAN0TMSTS12 RSCAN0.TMSTS12
#define RSCAN0TMSTS13 RSCAN0.TMSTS13
#define RSCAN0TMSTS14 RSCAN0.TMSTS14
#define RSCAN0TMSTS15 RSCAN0.TMSTS15
#define RSCAN0TMSTS16 RSCAN0.TMSTS16
#define RSCAN0TMSTS17 RSCAN0.TMSTS17
#define RSCAN0TMSTS18 RSCAN0.TMSTS18
#define RSCAN0TMSTS19 RSCAN0.TMSTS19
#define RSCAN0TMSTS20 RSCAN0.TMSTS20
#define RSCAN0TMSTS21 RSCAN0.TMSTS21
#define RSCAN0TMSTS22 RSCAN0.TMSTS22
#define RSCAN0TMSTS23 RSCAN0.TMSTS23
#define RSCAN0TMSTS24 RSCAN0.TMSTS24
#define RSCAN0TMSTS25 RSCAN0.TMSTS25
#define RSCAN0TMSTS26 RSCAN0.TMSTS26
#define RSCAN0TMSTS27 RSCAN0.TMSTS27
#define RSCAN0TMSTS28 RSCAN0.TMSTS28
#define RSCAN0TMSTS29 RSCAN0.TMSTS29
#define RSCAN0TMSTS30 RSCAN0.TMSTS30
#define RSCAN0TMSTS31 RSCAN0.TMSTS31
#define RSCAN0TMSTS32 RSCAN0.TMSTS32
#define RSCAN0TMSTS33 RSCAN0.TMSTS33
#define RSCAN0TMSTS34 RSCAN0.TMSTS34
#define RSCAN0TMSTS35 RSCAN0.TMSTS35
#define RSCAN0TMSTS36 RSCAN0.TMSTS36
#define RSCAN0TMSTS37 RSCAN0.TMSTS37
#define RSCAN0TMSTS38 RSCAN0.TMSTS38
#define RSCAN0TMSTS39 RSCAN0.TMSTS39
#define RSCAN0TMSTS40 RSCAN0.TMSTS40
#define RSCAN0TMSTS41 RSCAN0.TMSTS41
#define RSCAN0TMSTS42 RSCAN0.TMSTS42
#define RSCAN0TMSTS43 RSCAN0.TMSTS43
#define RSCAN0TMSTS44 RSCAN0.TMSTS44
#define RSCAN0TMSTS45 RSCAN0.TMSTS45
#define RSCAN0TMSTS46 RSCAN0.TMSTS46
#define RSCAN0TMSTS47 RSCAN0.TMSTS47
#define RSCAN0TMSTS48 RSCAN0.TMSTS48
#define RSCAN0TMSTS49 RSCAN0.TMSTS49
#define RSCAN0TMSTS50 RSCAN0.TMSTS50
#define RSCAN0TMSTS51 RSCAN0.TMSTS51
#define RSCAN0TMSTS52 RSCAN0.TMSTS52
#define RSCAN0TMSTS53 RSCAN0.TMSTS53
#define RSCAN0TMSTS54 RSCAN0.TMSTS54
#define RSCAN0TMSTS55 RSCAN0.TMSTS55
#define RSCAN0TMSTS56 RSCAN0.TMSTS56
#define RSCAN0TMSTS57 RSCAN0.TMSTS57
#define RSCAN0TMSTS58 RSCAN0.TMSTS58
#define RSCAN0TMSTS59 RSCAN0.TMSTS59
#define RSCAN0TMSTS60 RSCAN0.TMSTS60
#define RSCAN0TMSTS61 RSCAN0.TMSTS61
#define RSCAN0TMSTS62 RSCAN0.TMSTS62
#define RSCAN0TMSTS63 RSCAN0.TMSTS63
#define RSCAN0TMSTS64 RSCAN0.TMSTS64
#define RSCAN0TMSTS65 RSCAN0.TMSTS65
#define RSCAN0TMSTS66 RSCAN0.TMSTS66
#define RSCAN0TMSTS67 RSCAN0.TMSTS67
#define RSCAN0TMSTS68 RSCAN0.TMSTS68
#define RSCAN0TMSTS69 RSCAN0.TMSTS69
#define RSCAN0TMSTS70 RSCAN0.TMSTS70
#define RSCAN0TMSTS71 RSCAN0.TMSTS71
#define RSCAN0TMSTS72 RSCAN0.TMSTS72
#define RSCAN0TMSTS73 RSCAN0.TMSTS73
#define RSCAN0TMSTS74 RSCAN0.TMSTS74
#define RSCAN0TMSTS75 RSCAN0.TMSTS75
#define RSCAN0TMSTS76 RSCAN0.TMSTS76
#define RSCAN0TMSTS77 RSCAN0.TMSTS77
#define RSCAN0TMSTS78 RSCAN0.TMSTS78
#define RSCAN0TMSTS79 RSCAN0.TMSTS79
#define RSCAN0TMSTS80 RSCAN0.TMSTS80
#define RSCAN0TMSTS81 RSCAN0.TMSTS81
#define RSCAN0TMSTS82 RSCAN0.TMSTS82
#define RSCAN0TMSTS83 RSCAN0.TMSTS83
#define RSCAN0TMSTS84 RSCAN0.TMSTS84
#define RSCAN0TMSTS85 RSCAN0.TMSTS85
#define RSCAN0TMSTS86 RSCAN0.TMSTS86
#define RSCAN0TMSTS87 RSCAN0.TMSTS87
#define RSCAN0TMSTS88 RSCAN0.TMSTS88
#define RSCAN0TMSTS89 RSCAN0.TMSTS89
#define RSCAN0TMSTS90 RSCAN0.TMSTS90
#define RSCAN0TMSTS91 RSCAN0.TMSTS91
#define RSCAN0TMSTS92 RSCAN0.TMSTS92
#define RSCAN0TMSTS93 RSCAN0.TMSTS93
#define RSCAN0TMSTS94 RSCAN0.TMSTS94
#define RSCAN0TMSTS95 RSCAN0.TMSTS95
#define RSCAN0TMTRSTS0 RSCAN0.TMTRSTS0.UINT32
#define RSCAN0TMTRSTS0L RSCAN0.TMTRSTS0.UINT16[L]
#define RSCAN0TMTRSTS0LL RSCAN0.TMTRSTS0.UINT8[LL]
#define RSCAN0TMTRSTS0LH RSCAN0.TMTRSTS0.UINT8[LH]
#define RSCAN0TMTRSTS0H RSCAN0.TMTRSTS0.UINT16[H]
#define RSCAN0TMTRSTS0HL RSCAN0.TMTRSTS0.UINT8[HL]
#define RSCAN0TMTRSTS0HH RSCAN0.TMTRSTS0.UINT8[HH]
#define RSCAN0TMTRSTS1 RSCAN0.TMTRSTS1.UINT32
#define RSCAN0TMTRSTS1L RSCAN0.TMTRSTS1.UINT16[L]
#define RSCAN0TMTRSTS1LL RSCAN0.TMTRSTS1.UINT8[LL]
#define RSCAN0TMTRSTS1LH RSCAN0.TMTRSTS1.UINT8[LH]
#define RSCAN0TMTRSTS1H RSCAN0.TMTRSTS1.UINT16[H]
#define RSCAN0TMTRSTS1HL RSCAN0.TMTRSTS1.UINT8[HL]
#define RSCAN0TMTRSTS1HH RSCAN0.TMTRSTS1.UINT8[HH]
#define RSCAN0TMTRSTS2 RSCAN0.TMTRSTS2.UINT32
#define RSCAN0TMTRSTS2L RSCAN0.TMTRSTS2.UINT16[L]
#define RSCAN0TMTRSTS2LL RSCAN0.TMTRSTS2.UINT8[LL]
#define RSCAN0TMTRSTS2LH RSCAN0.TMTRSTS2.UINT8[LH]
#define RSCAN0TMTRSTS2H RSCAN0.TMTRSTS2.UINT16[H]
#define RSCAN0TMTRSTS2HL RSCAN0.TMTRSTS2.UINT8[HL]
#define RSCAN0TMTRSTS2HH RSCAN0.TMTRSTS2.UINT8[HH]
#define RSCAN0TMTARSTS0 RSCAN0.TMTARSTS0.UINT32
#define RSCAN0TMTARSTS0L RSCAN0.TMTARSTS0.UINT16[L]
#define RSCAN0TMTARSTS0LL RSCAN0.TMTARSTS0.UINT8[LL]
#define RSCAN0TMTARSTS0LH RSCAN0.TMTARSTS0.UINT8[LH]
#define RSCAN0TMTARSTS0H RSCAN0.TMTARSTS0.UINT16[H]
#define RSCAN0TMTARSTS0HL RSCAN0.TMTARSTS0.UINT8[HL]
#define RSCAN0TMTARSTS0HH RSCAN0.TMTARSTS0.UINT8[HH]
#define RSCAN0TMTARSTS1 RSCAN0.TMTARSTS1.UINT32
#define RSCAN0TMTARSTS1L RSCAN0.TMTARSTS1.UINT16[L]
#define RSCAN0TMTARSTS1LL RSCAN0.TMTARSTS1.UINT8[LL]
#define RSCAN0TMTARSTS1LH RSCAN0.TMTARSTS1.UINT8[LH]
#define RSCAN0TMTARSTS1H RSCAN0.TMTARSTS1.UINT16[H]
#define RSCAN0TMTARSTS1HL RSCAN0.TMTARSTS1.UINT8[HL]
#define RSCAN0TMTARSTS1HH RSCAN0.TMTARSTS1.UINT8[HH]
#define RSCAN0TMTARSTS2 RSCAN0.TMTARSTS2.UINT32
#define RSCAN0TMTARSTS2L RSCAN0.TMTARSTS2.UINT16[L]
#define RSCAN0TMTARSTS2LL RSCAN0.TMTARSTS2.UINT8[LL]
#define RSCAN0TMTARSTS2LH RSCAN0.TMTARSTS2.UINT8[LH]
#define RSCAN0TMTARSTS2H RSCAN0.TMTARSTS2.UINT16[H]
#define RSCAN0TMTARSTS2HL RSCAN0.TMTARSTS2.UINT8[HL]
#define RSCAN0TMTARSTS2HH RSCAN0.TMTARSTS2.UINT8[HH]
#define RSCAN0TMTCSTS0 RSCAN0.TMTCSTS0.UINT32
#define RSCAN0TMTCSTS0L RSCAN0.TMTCSTS0.UINT16[L]
#define RSCAN0TMTCSTS0LL RSCAN0.TMTCSTS0.UINT8[LL]
#define RSCAN0TMTCSTS0LH RSCAN0.TMTCSTS0.UINT8[LH]
#define RSCAN0TMTCSTS0H RSCAN0.TMTCSTS0.UINT16[H]
#define RSCAN0TMTCSTS0HL RSCAN0.TMTCSTS0.UINT8[HL]
#define RSCAN0TMTCSTS0HH RSCAN0.TMTCSTS0.UINT8[HH]
#define RSCAN0TMTCSTS1 RSCAN0.TMTCSTS1.UINT32
#define RSCAN0TMTCSTS1L RSCAN0.TMTCSTS1.UINT16[L]
#define RSCAN0TMTCSTS1LL RSCAN0.TMTCSTS1.UINT8[LL]
#define RSCAN0TMTCSTS1LH RSCAN0.TMTCSTS1.UINT8[LH]
#define RSCAN0TMTCSTS1H RSCAN0.TMTCSTS1.UINT16[H]
#define RSCAN0TMTCSTS1HL RSCAN0.TMTCSTS1.UINT8[HL]
#define RSCAN0TMTCSTS1HH RSCAN0.TMTCSTS1.UINT8[HH]
#define RSCAN0TMTCSTS2 RSCAN0.TMTCSTS2.UINT32
#define RSCAN0TMTCSTS2L RSCAN0.TMTCSTS2.UINT16[L]
#define RSCAN0TMTCSTS2LL RSCAN0.TMTCSTS2.UINT8[LL]
#define RSCAN0TMTCSTS2LH RSCAN0.TMTCSTS2.UINT8[LH]
#define RSCAN0TMTCSTS2H RSCAN0.TMTCSTS2.UINT16[H]
#define RSCAN0TMTCSTS2HL RSCAN0.TMTCSTS2.UINT8[HL]
#define RSCAN0TMTCSTS2HH RSCAN0.TMTCSTS2.UINT8[HH]
#define RSCAN0TMTASTS0 RSCAN0.TMTASTS0.UINT32
#define RSCAN0TMTASTS0L RSCAN0.TMTASTS0.UINT16[L]
#define RSCAN0TMTASTS0LL RSCAN0.TMTASTS0.UINT8[LL]
#define RSCAN0TMTASTS0LH RSCAN0.TMTASTS0.UINT8[LH]
#define RSCAN0TMTASTS0H RSCAN0.TMTASTS0.UINT16[H]
#define RSCAN0TMTASTS0HL RSCAN0.TMTASTS0.UINT8[HL]
#define RSCAN0TMTASTS0HH RSCAN0.TMTASTS0.UINT8[HH]
#define RSCAN0TMTASTS1 RSCAN0.TMTASTS1.UINT32
#define RSCAN0TMTASTS1L RSCAN0.TMTASTS1.UINT16[L]
#define RSCAN0TMTASTS1LL RSCAN0.TMTASTS1.UINT8[LL]
#define RSCAN0TMTASTS1LH RSCAN0.TMTASTS1.UINT8[LH]
#define RSCAN0TMTASTS1H RSCAN0.TMTASTS1.UINT16[H]
#define RSCAN0TMTASTS1HL RSCAN0.TMTASTS1.UINT8[HL]
#define RSCAN0TMTASTS1HH RSCAN0.TMTASTS1.UINT8[HH]
#define RSCAN0TMTASTS2 RSCAN0.TMTASTS2.UINT32
#define RSCAN0TMTASTS2L RSCAN0.TMTASTS2.UINT16[L]
#define RSCAN0TMTASTS2LL RSCAN0.TMTASTS2.UINT8[LL]
#define RSCAN0TMTASTS2LH RSCAN0.TMTASTS2.UINT8[LH]
#define RSCAN0TMTASTS2H RSCAN0.TMTASTS2.UINT16[H]
#define RSCAN0TMTASTS2HL RSCAN0.TMTASTS2.UINT8[HL]
#define RSCAN0TMTASTS2HH RSCAN0.TMTASTS2.UINT8[HH]
#define RSCAN0TMIEC0 RSCAN0.TMIEC0.UINT32
#define RSCAN0TMIEC0L RSCAN0.TMIEC0.UINT16[L]
#define RSCAN0TMIEC0LL RSCAN0.TMIEC0.UINT8[LL]
#define RSCAN0TMIEC0LH RSCAN0.TMIEC0.UINT8[LH]
#define RSCAN0TMIEC0H RSCAN0.TMIEC0.UINT16[H]
#define RSCAN0TMIEC0HL RSCAN0.TMIEC0.UINT8[HL]
#define RSCAN0TMIEC0HH RSCAN0.TMIEC0.UINT8[HH]
#define RSCAN0TMIEC1 RSCAN0.TMIEC1.UINT32
#define RSCAN0TMIEC1L RSCAN0.TMIEC1.UINT16[L]
#define RSCAN0TMIEC1LL RSCAN0.TMIEC1.UINT8[LL]
#define RSCAN0TMIEC1LH RSCAN0.TMIEC1.UINT8[LH]
#define RSCAN0TMIEC1H RSCAN0.TMIEC1.UINT16[H]
#define RSCAN0TMIEC1HL RSCAN0.TMIEC1.UINT8[HL]
#define RSCAN0TMIEC1HH RSCAN0.TMIEC1.UINT8[HH]
#define RSCAN0TMIEC2 RSCAN0.TMIEC2.UINT32
#define RSCAN0TMIEC2L RSCAN0.TMIEC2.UINT16[L]
#define RSCAN0TMIEC2LL RSCAN0.TMIEC2.UINT8[LL]
#define RSCAN0TMIEC2LH RSCAN0.TMIEC2.UINT8[LH]
#define RSCAN0TMIEC2H RSCAN0.TMIEC2.UINT16[H]
#define RSCAN0TMIEC2HL RSCAN0.TMIEC2.UINT8[HL]
#define RSCAN0TMIEC2HH RSCAN0.TMIEC2.UINT8[HH]
#define RSCAN0TXQCC0 RSCAN0.TXQCC0.UINT32
#define RSCAN0TXQCC0L RSCAN0.TXQCC0.UINT16[L]
#define RSCAN0TXQCC0LL RSCAN0.TXQCC0.UINT8[LL]
#define RSCAN0TXQCC0LH RSCAN0.TXQCC0.UINT8[LH]
#define RSCAN0TXQCC1 RSCAN0.TXQCC1.UINT32
#define RSCAN0TXQCC1L RSCAN0.TXQCC1.UINT16[L]
#define RSCAN0TXQCC1LL RSCAN0.TXQCC1.UINT8[LL]
#define RSCAN0TXQCC1LH RSCAN0.TXQCC1.UINT8[LH]
#define RSCAN0TXQCC2 RSCAN0.TXQCC2.UINT32
#define RSCAN0TXQCC2L RSCAN0.TXQCC2.UINT16[L]
#define RSCAN0TXQCC2LL RSCAN0.TXQCC2.UINT8[LL]
#define RSCAN0TXQCC2LH RSCAN0.TXQCC2.UINT8[LH]
#define RSCAN0TXQCC3 RSCAN0.TXQCC3.UINT32
#define RSCAN0TXQCC3L RSCAN0.TXQCC3.UINT16[L]
#define RSCAN0TXQCC3LL RSCAN0.TXQCC3.UINT8[LL]
#define RSCAN0TXQCC3LH RSCAN0.TXQCC3.UINT8[LH]
#define RSCAN0TXQCC4 RSCAN0.TXQCC4.UINT32
#define RSCAN0TXQCC4L RSCAN0.TXQCC4.UINT16[L]
#define RSCAN0TXQCC4LL RSCAN0.TXQCC4.UINT8[LL]
#define RSCAN0TXQCC4LH RSCAN0.TXQCC4.UINT8[LH]
#define RSCAN0TXQCC5 RSCAN0.TXQCC5.UINT32
#define RSCAN0TXQCC5L RSCAN0.TXQCC5.UINT16[L]
#define RSCAN0TXQCC5LL RSCAN0.TXQCC5.UINT8[LL]
#define RSCAN0TXQCC5LH RSCAN0.TXQCC5.UINT8[LH]
#define RSCAN0TXQSTS0 RSCAN0.TXQSTS0.UINT32
#define RSCAN0TXQSTS0L RSCAN0.TXQSTS0.UINT16[L]
#define RSCAN0TXQSTS0LL RSCAN0.TXQSTS0.UINT8[LL]
#define RSCAN0TXQSTS1 RSCAN0.TXQSTS1.UINT32
#define RSCAN0TXQSTS1L RSCAN0.TXQSTS1.UINT16[L]
#define RSCAN0TXQSTS1LL RSCAN0.TXQSTS1.UINT8[LL]
#define RSCAN0TXQSTS2 RSCAN0.TXQSTS2.UINT32
#define RSCAN0TXQSTS2L RSCAN0.TXQSTS2.UINT16[L]
#define RSCAN0TXQSTS2LL RSCAN0.TXQSTS2.UINT8[LL]
#define RSCAN0TXQSTS3 RSCAN0.TXQSTS3.UINT32
#define RSCAN0TXQSTS3L RSCAN0.TXQSTS3.UINT16[L]
#define RSCAN0TXQSTS3LL RSCAN0.TXQSTS3.UINT8[LL]
#define RSCAN0TXQSTS4 RSCAN0.TXQSTS4.UINT32
#define RSCAN0TXQSTS4L RSCAN0.TXQSTS4.UINT16[L]
#define RSCAN0TXQSTS4LL RSCAN0.TXQSTS4.UINT8[LL]
#define RSCAN0TXQSTS5 RSCAN0.TXQSTS5.UINT32
#define RSCAN0TXQSTS5L RSCAN0.TXQSTS5.UINT16[L]
#define RSCAN0TXQSTS5LL RSCAN0.TXQSTS5.UINT8[LL]
#define RSCAN0TXQPCTR0 RSCAN0.TXQPCTR0.UINT32
#define RSCAN0TXQPCTR0L RSCAN0.TXQPCTR0.UINT16[L]
#define RSCAN0TXQPCTR0LL RSCAN0.TXQPCTR0.UINT8[LL]
#define RSCAN0TXQPCTR1 RSCAN0.TXQPCTR1.UINT32
#define RSCAN0TXQPCTR1L RSCAN0.TXQPCTR1.UINT16[L]
#define RSCAN0TXQPCTR1LL RSCAN0.TXQPCTR1.UINT8[LL]
#define RSCAN0TXQPCTR2 RSCAN0.TXQPCTR2.UINT32
#define RSCAN0TXQPCTR2L RSCAN0.TXQPCTR2.UINT16[L]
#define RSCAN0TXQPCTR2LL RSCAN0.TXQPCTR2.UINT8[LL]
#define RSCAN0TXQPCTR3 RSCAN0.TXQPCTR3.UINT32
#define RSCAN0TXQPCTR3L RSCAN0.TXQPCTR3.UINT16[L]
#define RSCAN0TXQPCTR3LL RSCAN0.TXQPCTR3.UINT8[LL]
#define RSCAN0TXQPCTR4 RSCAN0.TXQPCTR4.UINT32
#define RSCAN0TXQPCTR4L RSCAN0.TXQPCTR4.UINT16[L]
#define RSCAN0TXQPCTR4LL RSCAN0.TXQPCTR4.UINT8[LL]
#define RSCAN0TXQPCTR5 RSCAN0.TXQPCTR5.UINT32
#define RSCAN0TXQPCTR5L RSCAN0.TXQPCTR5.UINT16[L]
#define RSCAN0TXQPCTR5LL RSCAN0.TXQPCTR5.UINT8[LL]
#define RSCAN0THLCC0 RSCAN0.THLCC0.UINT32
#define RSCAN0THLCC0L RSCAN0.THLCC0.UINT16[L]
#define RSCAN0THLCC0LL RSCAN0.THLCC0.UINT8[LL]
#define RSCAN0THLCC0LH RSCAN0.THLCC0.UINT8[LH]
#define RSCAN0THLCC1 RSCAN0.THLCC1.UINT32
#define RSCAN0THLCC1L RSCAN0.THLCC1.UINT16[L]
#define RSCAN0THLCC1LL RSCAN0.THLCC1.UINT8[LL]
#define RSCAN0THLCC1LH RSCAN0.THLCC1.UINT8[LH]
#define RSCAN0THLCC2 RSCAN0.THLCC2.UINT32
#define RSCAN0THLCC2L RSCAN0.THLCC2.UINT16[L]
#define RSCAN0THLCC2LL RSCAN0.THLCC2.UINT8[LL]
#define RSCAN0THLCC2LH RSCAN0.THLCC2.UINT8[LH]
#define RSCAN0THLCC3 RSCAN0.THLCC3.UINT32
#define RSCAN0THLCC3L RSCAN0.THLCC3.UINT16[L]
#define RSCAN0THLCC3LL RSCAN0.THLCC3.UINT8[LL]
#define RSCAN0THLCC3LH RSCAN0.THLCC3.UINT8[LH]
#define RSCAN0THLCC4 RSCAN0.THLCC4.UINT32
#define RSCAN0THLCC4L RSCAN0.THLCC4.UINT16[L]
#define RSCAN0THLCC4LL RSCAN0.THLCC4.UINT8[LL]
#define RSCAN0THLCC4LH RSCAN0.THLCC4.UINT8[LH]
#define RSCAN0THLCC5 RSCAN0.THLCC5.UINT32
#define RSCAN0THLCC5L RSCAN0.THLCC5.UINT16[L]
#define RSCAN0THLCC5LL RSCAN0.THLCC5.UINT8[LL]
#define RSCAN0THLCC5LH RSCAN0.THLCC5.UINT8[LH]
#define RSCAN0THLSTS0 RSCAN0.THLSTS0.UINT32
#define RSCAN0THLSTS0L RSCAN0.THLSTS0.UINT16[L]
#define RSCAN0THLSTS0LL RSCAN0.THLSTS0.UINT8[LL]
#define RSCAN0THLSTS0LH RSCAN0.THLSTS0.UINT8[LH]
#define RSCAN0THLSTS1 RSCAN0.THLSTS1.UINT32
#define RSCAN0THLSTS1L RSCAN0.THLSTS1.UINT16[L]
#define RSCAN0THLSTS1LL RSCAN0.THLSTS1.UINT8[LL]
#define RSCAN0THLSTS1LH RSCAN0.THLSTS1.UINT8[LH]
#define RSCAN0THLSTS2 RSCAN0.THLSTS2.UINT32
#define RSCAN0THLSTS2L RSCAN0.THLSTS2.UINT16[L]
#define RSCAN0THLSTS2LL RSCAN0.THLSTS2.UINT8[LL]
#define RSCAN0THLSTS2LH RSCAN0.THLSTS2.UINT8[LH]
#define RSCAN0THLSTS3 RSCAN0.THLSTS3.UINT32
#define RSCAN0THLSTS3L RSCAN0.THLSTS3.UINT16[L]
#define RSCAN0THLSTS3LL RSCAN0.THLSTS3.UINT8[LL]
#define RSCAN0THLSTS3LH RSCAN0.THLSTS3.UINT8[LH]
#define RSCAN0THLSTS4 RSCAN0.THLSTS4.UINT32
#define RSCAN0THLSTS4L RSCAN0.THLSTS4.UINT16[L]
#define RSCAN0THLSTS4LL RSCAN0.THLSTS4.UINT8[LL]
#define RSCAN0THLSTS4LH RSCAN0.THLSTS4.UINT8[LH]
#define RSCAN0THLSTS5 RSCAN0.THLSTS5.UINT32
#define RSCAN0THLSTS5L RSCAN0.THLSTS5.UINT16[L]
#define RSCAN0THLSTS5LL RSCAN0.THLSTS5.UINT8[LL]
#define RSCAN0THLSTS5LH RSCAN0.THLSTS5.UINT8[LH]
#define RSCAN0THLPCTR0 RSCAN0.THLPCTR0.UINT32
#define RSCAN0THLPCTR0L RSCAN0.THLPCTR0.UINT16[L]
#define RSCAN0THLPCTR0LL RSCAN0.THLPCTR0.UINT8[LL]
#define RSCAN0THLPCTR1 RSCAN0.THLPCTR1.UINT32
#define RSCAN0THLPCTR1L RSCAN0.THLPCTR1.UINT16[L]
#define RSCAN0THLPCTR1LL RSCAN0.THLPCTR1.UINT8[LL]
#define RSCAN0THLPCTR2 RSCAN0.THLPCTR2.UINT32
#define RSCAN0THLPCTR2L RSCAN0.THLPCTR2.UINT16[L]
#define RSCAN0THLPCTR2LL RSCAN0.THLPCTR2.UINT8[LL]
#define RSCAN0THLPCTR3 RSCAN0.THLPCTR3.UINT32
#define RSCAN0THLPCTR3L RSCAN0.THLPCTR3.UINT16[L]
#define RSCAN0THLPCTR3LL RSCAN0.THLPCTR3.UINT8[LL]
#define RSCAN0THLPCTR4 RSCAN0.THLPCTR4.UINT32
#define RSCAN0THLPCTR4L RSCAN0.THLPCTR4.UINT16[L]
#define RSCAN0THLPCTR4LL RSCAN0.THLPCTR4.UINT8[LL]
#define RSCAN0THLPCTR5 RSCAN0.THLPCTR5.UINT32
#define RSCAN0THLPCTR5L RSCAN0.THLPCTR5.UINT16[L]
#define RSCAN0THLPCTR5LL RSCAN0.THLPCTR5.UINT8[LL]
#define RSCAN0GTINTSTS0 RSCAN0.GTINTSTS0.UINT32
#define RSCAN0GTINTSTS0L RSCAN0.GTINTSTS0.UINT16[L]
#define RSCAN0GTINTSTS0LL RSCAN0.GTINTSTS0.UINT8[LL]
#define RSCAN0GTINTSTS0LH RSCAN0.GTINTSTS0.UINT8[LH]
#define RSCAN0GTINTSTS0H RSCAN0.GTINTSTS0.UINT16[H]
#define RSCAN0GTINTSTS0HL RSCAN0.GTINTSTS0.UINT8[HL]
#define RSCAN0GTINTSTS0HH RSCAN0.GTINTSTS0.UINT8[HH]
#define RSCAN0GTINTSTS1 RSCAN0.GTINTSTS1.UINT32
#define RSCAN0GTINTSTS1L RSCAN0.GTINTSTS1.UINT16[L]
#define RSCAN0GTINTSTS1LL RSCAN0.GTINTSTS1.UINT8[LL]
#define RSCAN0GTINTSTS1LH RSCAN0.GTINTSTS1.UINT8[LH]
#define RSCAN0GTSTCFG RSCAN0.GTSTCFG.UINT32
#define RSCAN0GTSTCFGL RSCAN0.GTSTCFG.UINT16[L]
#define RSCAN0GTSTCFGLL RSCAN0.GTSTCFG.UINT8[LL]
#define RSCAN0GTSTCFGH RSCAN0.GTSTCFG.UINT16[H]
#define RSCAN0GTSTCFGHL RSCAN0.GTSTCFG.UINT8[HL]
#define RSCAN0GTSTCTR RSCAN0.GTSTCTR.UINT32
#define RSCAN0GTSTCTRL RSCAN0.GTSTCTR.UINT16[L]
#define RSCAN0GTSTCTRLL RSCAN0.GTSTCTR.UINT8[LL]
#define RSCAN0GLOCKK RSCAN0.GLOCKK.UINT32
#define RSCAN0GLOCKKL RSCAN0.GLOCKK.UINT16[L]
#define RSCAN0GAFLID0 RSCAN0.GAFLID0.UINT32
#define RSCAN0GAFLID0L RSCAN0.GAFLID0.UINT16[L]
#define RSCAN0GAFLID0LL RSCAN0.GAFLID0.UINT8[LL]
#define RSCAN0GAFLID0LH RSCAN0.GAFLID0.UINT8[LH]
#define RSCAN0GAFLID0H RSCAN0.GAFLID0.UINT16[H]
#define RSCAN0GAFLID0HL RSCAN0.GAFLID0.UINT8[HL]
#define RSCAN0GAFLID0HH RSCAN0.GAFLID0.UINT8[HH]
#define RSCAN0GAFLM0 RSCAN0.GAFLM0.UINT32
#define RSCAN0GAFLM0L RSCAN0.GAFLM0.UINT16[L]
#define RSCAN0GAFLM0LL RSCAN0.GAFLM0.UINT8[LL]
#define RSCAN0GAFLM0LH RSCAN0.GAFLM0.UINT8[LH]
#define RSCAN0GAFLM0H RSCAN0.GAFLM0.UINT16[H]
#define RSCAN0GAFLM0HL RSCAN0.GAFLM0.UINT8[HL]
#define RSCAN0GAFLM0HH RSCAN0.GAFLM0.UINT8[HH]
#define RSCAN0GAFLP00 RSCAN0.GAFLP00.UINT32
#define RSCAN0GAFLP00L RSCAN0.GAFLP00.UINT16[L]
#define RSCAN0GAFLP00LH RSCAN0.GAFLP00.UINT8[LH]
#define RSCAN0GAFLP00H RSCAN0.GAFLP00.UINT16[H]
#define RSCAN0GAFLP00HL RSCAN0.GAFLP00.UINT8[HL]
#define RSCAN0GAFLP00HH RSCAN0.GAFLP00.UINT8[HH]
#define RSCAN0GAFLP10 RSCAN0.GAFLP10.UINT32
#define RSCAN0GAFLP10L RSCAN0.GAFLP10.UINT16[L]
#define RSCAN0GAFLP10LL RSCAN0.GAFLP10.UINT8[LL]
#define RSCAN0GAFLP10LH RSCAN0.GAFLP10.UINT8[LH]
#define RSCAN0GAFLP10H RSCAN0.GAFLP10.UINT16[H]
#define RSCAN0GAFLP10HL RSCAN0.GAFLP10.UINT8[HL]
#define RSCAN0GAFLP10HH RSCAN0.GAFLP10.UINT8[HH]
#define RSCAN0GAFLID1 RSCAN0.GAFLID1.UINT32
#define RSCAN0GAFLID1L RSCAN0.GAFLID1.UINT16[L]
#define RSCAN0GAFLID1LL RSCAN0.GAFLID1.UINT8[LL]
#define RSCAN0GAFLID1LH RSCAN0.GAFLID1.UINT8[LH]
#define RSCAN0GAFLID1H RSCAN0.GAFLID1.UINT16[H]
#define RSCAN0GAFLID1HL RSCAN0.GAFLID1.UINT8[HL]
#define RSCAN0GAFLID1HH RSCAN0.GAFLID1.UINT8[HH]
#define RSCAN0GAFLM1 RSCAN0.GAFLM1.UINT32
#define RSCAN0GAFLM1L RSCAN0.GAFLM1.UINT16[L]
#define RSCAN0GAFLM1LL RSCAN0.GAFLM1.UINT8[LL]
#define RSCAN0GAFLM1LH RSCAN0.GAFLM1.UINT8[LH]
#define RSCAN0GAFLM1H RSCAN0.GAFLM1.UINT16[H]
#define RSCAN0GAFLM1HL RSCAN0.GAFLM1.UINT8[HL]
#define RSCAN0GAFLM1HH RSCAN0.GAFLM1.UINT8[HH]
#define RSCAN0GAFLP01 RSCAN0.GAFLP01.UINT32
#define RSCAN0GAFLP01L RSCAN0.GAFLP01.UINT16[L]
#define RSCAN0GAFLP01LH RSCAN0.GAFLP01.UINT8[LH]
#define RSCAN0GAFLP01H RSCAN0.GAFLP01.UINT16[H]
#define RSCAN0GAFLP01HL RSCAN0.GAFLP01.UINT8[HL]
#define RSCAN0GAFLP01HH RSCAN0.GAFLP01.UINT8[HH]
#define RSCAN0GAFLP11 RSCAN0.GAFLP11.UINT32
#define RSCAN0GAFLP11L RSCAN0.GAFLP11.UINT16[L]
#define RSCAN0GAFLP11LL RSCAN0.GAFLP11.UINT8[LL]
#define RSCAN0GAFLP11LH RSCAN0.GAFLP11.UINT8[LH]
#define RSCAN0GAFLP11H RSCAN0.GAFLP11.UINT16[H]
#define RSCAN0GAFLP11HL RSCAN0.GAFLP11.UINT8[HL]
#define RSCAN0GAFLP11HH RSCAN0.GAFLP11.UINT8[HH]
#define RSCAN0GAFLID2 RSCAN0.GAFLID2.UINT32
#define RSCAN0GAFLID2L RSCAN0.GAFLID2.UINT16[L]
#define RSCAN0GAFLID2LL RSCAN0.GAFLID2.UINT8[LL]
#define RSCAN0GAFLID2LH RSCAN0.GAFLID2.UINT8[LH]
#define RSCAN0GAFLID2H RSCAN0.GAFLID2.UINT16[H]
#define RSCAN0GAFLID2HL RSCAN0.GAFLID2.UINT8[HL]
#define RSCAN0GAFLID2HH RSCAN0.GAFLID2.UINT8[HH]
#define RSCAN0GAFLM2 RSCAN0.GAFLM2.UINT32
#define RSCAN0GAFLM2L RSCAN0.GAFLM2.UINT16[L]
#define RSCAN0GAFLM2LL RSCAN0.GAFLM2.UINT8[LL]
#define RSCAN0GAFLM2LH RSCAN0.GAFLM2.UINT8[LH]
#define RSCAN0GAFLM2H RSCAN0.GAFLM2.UINT16[H]
#define RSCAN0GAFLM2HL RSCAN0.GAFLM2.UINT8[HL]
#define RSCAN0GAFLM2HH RSCAN0.GAFLM2.UINT8[HH]
#define RSCAN0GAFLP02 RSCAN0.GAFLP02.UINT32
#define RSCAN0GAFLP02L RSCAN0.GAFLP02.UINT16[L]
#define RSCAN0GAFLP02LH RSCAN0.GAFLP02.UINT8[LH]
#define RSCAN0GAFLP02H RSCAN0.GAFLP02.UINT16[H]
#define RSCAN0GAFLP02HL RSCAN0.GAFLP02.UINT8[HL]
#define RSCAN0GAFLP02HH RSCAN0.GAFLP02.UINT8[HH]
#define RSCAN0GAFLP12 RSCAN0.GAFLP12.UINT32
#define RSCAN0GAFLP12L RSCAN0.GAFLP12.UINT16[L]
#define RSCAN0GAFLP12LL RSCAN0.GAFLP12.UINT8[LL]
#define RSCAN0GAFLP12LH RSCAN0.GAFLP12.UINT8[LH]
#define RSCAN0GAFLP12H RSCAN0.GAFLP12.UINT16[H]
#define RSCAN0GAFLP12HL RSCAN0.GAFLP12.UINT8[HL]
#define RSCAN0GAFLP12HH RSCAN0.GAFLP12.UINT8[HH]
#define RSCAN0GAFLID3 RSCAN0.GAFLID3.UINT32
#define RSCAN0GAFLID3L RSCAN0.GAFLID3.UINT16[L]
#define RSCAN0GAFLID3LL RSCAN0.GAFLID3.UINT8[LL]
#define RSCAN0GAFLID3LH RSCAN0.GAFLID3.UINT8[LH]
#define RSCAN0GAFLID3H RSCAN0.GAFLID3.UINT16[H]
#define RSCAN0GAFLID3HL RSCAN0.GAFLID3.UINT8[HL]
#define RSCAN0GAFLID3HH RSCAN0.GAFLID3.UINT8[HH]
#define RSCAN0GAFLM3 RSCAN0.GAFLM3.UINT32
#define RSCAN0GAFLM3L RSCAN0.GAFLM3.UINT16[L]
#define RSCAN0GAFLM3LL RSCAN0.GAFLM3.UINT8[LL]
#define RSCAN0GAFLM3LH RSCAN0.GAFLM3.UINT8[LH]
#define RSCAN0GAFLM3H RSCAN0.GAFLM3.UINT16[H]
#define RSCAN0GAFLM3HL RSCAN0.GAFLM3.UINT8[HL]
#define RSCAN0GAFLM3HH RSCAN0.GAFLM3.UINT8[HH]
#define RSCAN0GAFLP03 RSCAN0.GAFLP03.UINT32
#define RSCAN0GAFLP03L RSCAN0.GAFLP03.UINT16[L]
#define RSCAN0GAFLP03LH RSCAN0.GAFLP03.UINT8[LH]
#define RSCAN0GAFLP03H RSCAN0.GAFLP03.UINT16[H]
#define RSCAN0GAFLP03HL RSCAN0.GAFLP03.UINT8[HL]
#define RSCAN0GAFLP03HH RSCAN0.GAFLP03.UINT8[HH]
#define RSCAN0GAFLP13 RSCAN0.GAFLP13.UINT32
#define RSCAN0GAFLP13L RSCAN0.GAFLP13.UINT16[L]
#define RSCAN0GAFLP13LL RSCAN0.GAFLP13.UINT8[LL]
#define RSCAN0GAFLP13LH RSCAN0.GAFLP13.UINT8[LH]
#define RSCAN0GAFLP13H RSCAN0.GAFLP13.UINT16[H]
#define RSCAN0GAFLP13HL RSCAN0.GAFLP13.UINT8[HL]
#define RSCAN0GAFLP13HH RSCAN0.GAFLP13.UINT8[HH]
#define RSCAN0GAFLID4 RSCAN0.GAFLID4.UINT32
#define RSCAN0GAFLID4L RSCAN0.GAFLID4.UINT16[L]
#define RSCAN0GAFLID4LL RSCAN0.GAFLID4.UINT8[LL]
#define RSCAN0GAFLID4LH RSCAN0.GAFLID4.UINT8[LH]
#define RSCAN0GAFLID4H RSCAN0.GAFLID4.UINT16[H]
#define RSCAN0GAFLID4HL RSCAN0.GAFLID4.UINT8[HL]
#define RSCAN0GAFLID4HH RSCAN0.GAFLID4.UINT8[HH]
#define RSCAN0GAFLM4 RSCAN0.GAFLM4.UINT32
#define RSCAN0GAFLM4L RSCAN0.GAFLM4.UINT16[L]
#define RSCAN0GAFLM4LL RSCAN0.GAFLM4.UINT8[LL]
#define RSCAN0GAFLM4LH RSCAN0.GAFLM4.UINT8[LH]
#define RSCAN0GAFLM4H RSCAN0.GAFLM4.UINT16[H]
#define RSCAN0GAFLM4HL RSCAN0.GAFLM4.UINT8[HL]
#define RSCAN0GAFLM4HH RSCAN0.GAFLM4.UINT8[HH]
#define RSCAN0GAFLP04 RSCAN0.GAFLP04.UINT32
#define RSCAN0GAFLP04L RSCAN0.GAFLP04.UINT16[L]
#define RSCAN0GAFLP04LH RSCAN0.GAFLP04.UINT8[LH]
#define RSCAN0GAFLP04H RSCAN0.GAFLP04.UINT16[H]
#define RSCAN0GAFLP04HL RSCAN0.GAFLP04.UINT8[HL]
#define RSCAN0GAFLP04HH RSCAN0.GAFLP04.UINT8[HH]
#define RSCAN0GAFLP14 RSCAN0.GAFLP14.UINT32
#define RSCAN0GAFLP14L RSCAN0.GAFLP14.UINT16[L]
#define RSCAN0GAFLP14LL RSCAN0.GAFLP14.UINT8[LL]
#define RSCAN0GAFLP14LH RSCAN0.GAFLP14.UINT8[LH]
#define RSCAN0GAFLP14H RSCAN0.GAFLP14.UINT16[H]
#define RSCAN0GAFLP14HL RSCAN0.GAFLP14.UINT8[HL]
#define RSCAN0GAFLP14HH RSCAN0.GAFLP14.UINT8[HH]
#define RSCAN0GAFLID5 RSCAN0.GAFLID5.UINT32
#define RSCAN0GAFLID5L RSCAN0.GAFLID5.UINT16[L]
#define RSCAN0GAFLID5LL RSCAN0.GAFLID5.UINT8[LL]
#define RSCAN0GAFLID5LH RSCAN0.GAFLID5.UINT8[LH]
#define RSCAN0GAFLID5H RSCAN0.GAFLID5.UINT16[H]
#define RSCAN0GAFLID5HL RSCAN0.GAFLID5.UINT8[HL]
#define RSCAN0GAFLID5HH RSCAN0.GAFLID5.UINT8[HH]
#define RSCAN0GAFLM5 RSCAN0.GAFLM5.UINT32
#define RSCAN0GAFLM5L RSCAN0.GAFLM5.UINT16[L]
#define RSCAN0GAFLM5LL RSCAN0.GAFLM5.UINT8[LL]
#define RSCAN0GAFLM5LH RSCAN0.GAFLM5.UINT8[LH]
#define RSCAN0GAFLM5H RSCAN0.GAFLM5.UINT16[H]
#define RSCAN0GAFLM5HL RSCAN0.GAFLM5.UINT8[HL]
#define RSCAN0GAFLM5HH RSCAN0.GAFLM5.UINT8[HH]
#define RSCAN0GAFLP05 RSCAN0.GAFLP05.UINT32
#define RSCAN0GAFLP05L RSCAN0.GAFLP05.UINT16[L]
#define RSCAN0GAFLP05LH RSCAN0.GAFLP05.UINT8[LH]
#define RSCAN0GAFLP05H RSCAN0.GAFLP05.UINT16[H]
#define RSCAN0GAFLP05HL RSCAN0.GAFLP05.UINT8[HL]
#define RSCAN0GAFLP05HH RSCAN0.GAFLP05.UINT8[HH]
#define RSCAN0GAFLP15 RSCAN0.GAFLP15.UINT32
#define RSCAN0GAFLP15L RSCAN0.GAFLP15.UINT16[L]
#define RSCAN0GAFLP15LL RSCAN0.GAFLP15.UINT8[LL]
#define RSCAN0GAFLP15LH RSCAN0.GAFLP15.UINT8[LH]
#define RSCAN0GAFLP15H RSCAN0.GAFLP15.UINT16[H]
#define RSCAN0GAFLP15HL RSCAN0.GAFLP15.UINT8[HL]
#define RSCAN0GAFLP15HH RSCAN0.GAFLP15.UINT8[HH]
#define RSCAN0GAFLID6 RSCAN0.GAFLID6.UINT32
#define RSCAN0GAFLID6L RSCAN0.GAFLID6.UINT16[L]
#define RSCAN0GAFLID6LL RSCAN0.GAFLID6.UINT8[LL]
#define RSCAN0GAFLID6LH RSCAN0.GAFLID6.UINT8[LH]
#define RSCAN0GAFLID6H RSCAN0.GAFLID6.UINT16[H]
#define RSCAN0GAFLID6HL RSCAN0.GAFLID6.UINT8[HL]
#define RSCAN0GAFLID6HH RSCAN0.GAFLID6.UINT8[HH]
#define RSCAN0GAFLM6 RSCAN0.GAFLM6.UINT32
#define RSCAN0GAFLM6L RSCAN0.GAFLM6.UINT16[L]
#define RSCAN0GAFLM6LL RSCAN0.GAFLM6.UINT8[LL]
#define RSCAN0GAFLM6LH RSCAN0.GAFLM6.UINT8[LH]
#define RSCAN0GAFLM6H RSCAN0.GAFLM6.UINT16[H]
#define RSCAN0GAFLM6HL RSCAN0.GAFLM6.UINT8[HL]
#define RSCAN0GAFLM6HH RSCAN0.GAFLM6.UINT8[HH]
#define RSCAN0GAFLP06 RSCAN0.GAFLP06.UINT32
#define RSCAN0GAFLP06L RSCAN0.GAFLP06.UINT16[L]
#define RSCAN0GAFLP06LH RSCAN0.GAFLP06.UINT8[LH]
#define RSCAN0GAFLP06H RSCAN0.GAFLP06.UINT16[H]
#define RSCAN0GAFLP06HL RSCAN0.GAFLP06.UINT8[HL]
#define RSCAN0GAFLP06HH RSCAN0.GAFLP06.UINT8[HH]
#define RSCAN0GAFLP16 RSCAN0.GAFLP16.UINT32
#define RSCAN0GAFLP16L RSCAN0.GAFLP16.UINT16[L]
#define RSCAN0GAFLP16LL RSCAN0.GAFLP16.UINT8[LL]
#define RSCAN0GAFLP16LH RSCAN0.GAFLP16.UINT8[LH]
#define RSCAN0GAFLP16H RSCAN0.GAFLP16.UINT16[H]
#define RSCAN0GAFLP16HL RSCAN0.GAFLP16.UINT8[HL]
#define RSCAN0GAFLP16HH RSCAN0.GAFLP16.UINT8[HH]
#define RSCAN0GAFLID7 RSCAN0.GAFLID7.UINT32
#define RSCAN0GAFLID7L RSCAN0.GAFLID7.UINT16[L]
#define RSCAN0GAFLID7LL RSCAN0.GAFLID7.UINT8[LL]
#define RSCAN0GAFLID7LH RSCAN0.GAFLID7.UINT8[LH]
#define RSCAN0GAFLID7H RSCAN0.GAFLID7.UINT16[H]
#define RSCAN0GAFLID7HL RSCAN0.GAFLID7.UINT8[HL]
#define RSCAN0GAFLID7HH RSCAN0.GAFLID7.UINT8[HH]
#define RSCAN0GAFLM7 RSCAN0.GAFLM7.UINT32
#define RSCAN0GAFLM7L RSCAN0.GAFLM7.UINT16[L]
#define RSCAN0GAFLM7LL RSCAN0.GAFLM7.UINT8[LL]
#define RSCAN0GAFLM7LH RSCAN0.GAFLM7.UINT8[LH]
#define RSCAN0GAFLM7H RSCAN0.GAFLM7.UINT16[H]
#define RSCAN0GAFLM7HL RSCAN0.GAFLM7.UINT8[HL]
#define RSCAN0GAFLM7HH RSCAN0.GAFLM7.UINT8[HH]
#define RSCAN0GAFLP07 RSCAN0.GAFLP07.UINT32
#define RSCAN0GAFLP07L RSCAN0.GAFLP07.UINT16[L]
#define RSCAN0GAFLP07LH RSCAN0.GAFLP07.UINT8[LH]
#define RSCAN0GAFLP07H RSCAN0.GAFLP07.UINT16[H]
#define RSCAN0GAFLP07HL RSCAN0.GAFLP07.UINT8[HL]
#define RSCAN0GAFLP07HH RSCAN0.GAFLP07.UINT8[HH]
#define RSCAN0GAFLP17 RSCAN0.GAFLP17.UINT32
#define RSCAN0GAFLP17L RSCAN0.GAFLP17.UINT16[L]
#define RSCAN0GAFLP17LL RSCAN0.GAFLP17.UINT8[LL]
#define RSCAN0GAFLP17LH RSCAN0.GAFLP17.UINT8[LH]
#define RSCAN0GAFLP17H RSCAN0.GAFLP17.UINT16[H]
#define RSCAN0GAFLP17HL RSCAN0.GAFLP17.UINT8[HL]
#define RSCAN0GAFLP17HH RSCAN0.GAFLP17.UINT8[HH]
#define RSCAN0GAFLID8 RSCAN0.GAFLID8.UINT32
#define RSCAN0GAFLID8L RSCAN0.GAFLID8.UINT16[L]
#define RSCAN0GAFLID8LL RSCAN0.GAFLID8.UINT8[LL]
#define RSCAN0GAFLID8LH RSCAN0.GAFLID8.UINT8[LH]
#define RSCAN0GAFLID8H RSCAN0.GAFLID8.UINT16[H]
#define RSCAN0GAFLID8HL RSCAN0.GAFLID8.UINT8[HL]
#define RSCAN0GAFLID8HH RSCAN0.GAFLID8.UINT8[HH]
#define RSCAN0GAFLM8 RSCAN0.GAFLM8.UINT32
#define RSCAN0GAFLM8L RSCAN0.GAFLM8.UINT16[L]
#define RSCAN0GAFLM8LL RSCAN0.GAFLM8.UINT8[LL]
#define RSCAN0GAFLM8LH RSCAN0.GAFLM8.UINT8[LH]
#define RSCAN0GAFLM8H RSCAN0.GAFLM8.UINT16[H]
#define RSCAN0GAFLM8HL RSCAN0.GAFLM8.UINT8[HL]
#define RSCAN0GAFLM8HH RSCAN0.GAFLM8.UINT8[HH]
#define RSCAN0GAFLP08 RSCAN0.GAFLP08.UINT32
#define RSCAN0GAFLP08L RSCAN0.GAFLP08.UINT16[L]
#define RSCAN0GAFLP08LH RSCAN0.GAFLP08.UINT8[LH]
#define RSCAN0GAFLP08H RSCAN0.GAFLP08.UINT16[H]
#define RSCAN0GAFLP08HL RSCAN0.GAFLP08.UINT8[HL]
#define RSCAN0GAFLP08HH RSCAN0.GAFLP08.UINT8[HH]
#define RSCAN0GAFLP18 RSCAN0.GAFLP18.UINT32
#define RSCAN0GAFLP18L RSCAN0.GAFLP18.UINT16[L]
#define RSCAN0GAFLP18LL RSCAN0.GAFLP18.UINT8[LL]
#define RSCAN0GAFLP18LH RSCAN0.GAFLP18.UINT8[LH]
#define RSCAN0GAFLP18H RSCAN0.GAFLP18.UINT16[H]
#define RSCAN0GAFLP18HL RSCAN0.GAFLP18.UINT8[HL]
#define RSCAN0GAFLP18HH RSCAN0.GAFLP18.UINT8[HH]
#define RSCAN0GAFLID9 RSCAN0.GAFLID9.UINT32
#define RSCAN0GAFLID9L RSCAN0.GAFLID9.UINT16[L]
#define RSCAN0GAFLID9LL RSCAN0.GAFLID9.UINT8[LL]
#define RSCAN0GAFLID9LH RSCAN0.GAFLID9.UINT8[LH]
#define RSCAN0GAFLID9H RSCAN0.GAFLID9.UINT16[H]
#define RSCAN0GAFLID9HL RSCAN0.GAFLID9.UINT8[HL]
#define RSCAN0GAFLID9HH RSCAN0.GAFLID9.UINT8[HH]
#define RSCAN0GAFLM9 RSCAN0.GAFLM9.UINT32
#define RSCAN0GAFLM9L RSCAN0.GAFLM9.UINT16[L]
#define RSCAN0GAFLM9LL RSCAN0.GAFLM9.UINT8[LL]
#define RSCAN0GAFLM9LH RSCAN0.GAFLM9.UINT8[LH]
#define RSCAN0GAFLM9H RSCAN0.GAFLM9.UINT16[H]
#define RSCAN0GAFLM9HL RSCAN0.GAFLM9.UINT8[HL]
#define RSCAN0GAFLM9HH RSCAN0.GAFLM9.UINT8[HH]
#define RSCAN0GAFLP09 RSCAN0.GAFLP09.UINT32
#define RSCAN0GAFLP09L RSCAN0.GAFLP09.UINT16[L]
#define RSCAN0GAFLP09LH RSCAN0.GAFLP09.UINT8[LH]
#define RSCAN0GAFLP09H RSCAN0.GAFLP09.UINT16[H]
#define RSCAN0GAFLP09HL RSCAN0.GAFLP09.UINT8[HL]
#define RSCAN0GAFLP09HH RSCAN0.GAFLP09.UINT8[HH]
#define RSCAN0GAFLP19 RSCAN0.GAFLP19.UINT32
#define RSCAN0GAFLP19L RSCAN0.GAFLP19.UINT16[L]
#define RSCAN0GAFLP19LL RSCAN0.GAFLP19.UINT8[LL]
#define RSCAN0GAFLP19LH RSCAN0.GAFLP19.UINT8[LH]
#define RSCAN0GAFLP19H RSCAN0.GAFLP19.UINT16[H]
#define RSCAN0GAFLP19HL RSCAN0.GAFLP19.UINT8[HL]
#define RSCAN0GAFLP19HH RSCAN0.GAFLP19.UINT8[HH]
#define RSCAN0GAFLID10 RSCAN0.GAFLID10.UINT32
#define RSCAN0GAFLID10L RSCAN0.GAFLID10.UINT16[L]
#define RSCAN0GAFLID10LL RSCAN0.GAFLID10.UINT8[LL]
#define RSCAN0GAFLID10LH RSCAN0.GAFLID10.UINT8[LH]
#define RSCAN0GAFLID10H RSCAN0.GAFLID10.UINT16[H]
#define RSCAN0GAFLID10HL RSCAN0.GAFLID10.UINT8[HL]
#define RSCAN0GAFLID10HH RSCAN0.GAFLID10.UINT8[HH]
#define RSCAN0GAFLM10 RSCAN0.GAFLM10.UINT32
#define RSCAN0GAFLM10L RSCAN0.GAFLM10.UINT16[L]
#define RSCAN0GAFLM10LL RSCAN0.GAFLM10.UINT8[LL]
#define RSCAN0GAFLM10LH RSCAN0.GAFLM10.UINT8[LH]
#define RSCAN0GAFLM10H RSCAN0.GAFLM10.UINT16[H]
#define RSCAN0GAFLM10HL RSCAN0.GAFLM10.UINT8[HL]
#define RSCAN0GAFLM10HH RSCAN0.GAFLM10.UINT8[HH]
#define RSCAN0GAFLP010 RSCAN0.GAFLP010.UINT32
#define RSCAN0GAFLP010L RSCAN0.GAFLP010.UINT16[L]
#define RSCAN0GAFLP010LH RSCAN0.GAFLP010.UINT8[LH]
#define RSCAN0GAFLP010H RSCAN0.GAFLP010.UINT16[H]
#define RSCAN0GAFLP010HL RSCAN0.GAFLP010.UINT8[HL]
#define RSCAN0GAFLP010HH RSCAN0.GAFLP010.UINT8[HH]
#define RSCAN0GAFLP110 RSCAN0.GAFLP110.UINT32
#define RSCAN0GAFLP110L RSCAN0.GAFLP110.UINT16[L]
#define RSCAN0GAFLP110LL RSCAN0.GAFLP110.UINT8[LL]
#define RSCAN0GAFLP110LH RSCAN0.GAFLP110.UINT8[LH]
#define RSCAN0GAFLP110H RSCAN0.GAFLP110.UINT16[H]
#define RSCAN0GAFLP110HL RSCAN0.GAFLP110.UINT8[HL]
#define RSCAN0GAFLP110HH RSCAN0.GAFLP110.UINT8[HH]
#define RSCAN0GAFLID11 RSCAN0.GAFLID11.UINT32
#define RSCAN0GAFLID11L RSCAN0.GAFLID11.UINT16[L]
#define RSCAN0GAFLID11LL RSCAN0.GAFLID11.UINT8[LL]
#define RSCAN0GAFLID11LH RSCAN0.GAFLID11.UINT8[LH]
#define RSCAN0GAFLID11H RSCAN0.GAFLID11.UINT16[H]
#define RSCAN0GAFLID11HL RSCAN0.GAFLID11.UINT8[HL]
#define RSCAN0GAFLID11HH RSCAN0.GAFLID11.UINT8[HH]
#define RSCAN0GAFLM11 RSCAN0.GAFLM11.UINT32
#define RSCAN0GAFLM11L RSCAN0.GAFLM11.UINT16[L]
#define RSCAN0GAFLM11LL RSCAN0.GAFLM11.UINT8[LL]
#define RSCAN0GAFLM11LH RSCAN0.GAFLM11.UINT8[LH]
#define RSCAN0GAFLM11H RSCAN0.GAFLM11.UINT16[H]
#define RSCAN0GAFLM11HL RSCAN0.GAFLM11.UINT8[HL]
#define RSCAN0GAFLM11HH RSCAN0.GAFLM11.UINT8[HH]
#define RSCAN0GAFLP011 RSCAN0.GAFLP011.UINT32
#define RSCAN0GAFLP011L RSCAN0.GAFLP011.UINT16[L]
#define RSCAN0GAFLP011LH RSCAN0.GAFLP011.UINT8[LH]
#define RSCAN0GAFLP011H RSCAN0.GAFLP011.UINT16[H]
#define RSCAN0GAFLP011HL RSCAN0.GAFLP011.UINT8[HL]
#define RSCAN0GAFLP011HH RSCAN0.GAFLP011.UINT8[HH]
#define RSCAN0GAFLP111 RSCAN0.GAFLP111.UINT32
#define RSCAN0GAFLP111L RSCAN0.GAFLP111.UINT16[L]
#define RSCAN0GAFLP111LL RSCAN0.GAFLP111.UINT8[LL]
#define RSCAN0GAFLP111LH RSCAN0.GAFLP111.UINT8[LH]
#define RSCAN0GAFLP111H RSCAN0.GAFLP111.UINT16[H]
#define RSCAN0GAFLP111HL RSCAN0.GAFLP111.UINT8[HL]
#define RSCAN0GAFLP111HH RSCAN0.GAFLP111.UINT8[HH]
#define RSCAN0GAFLID12 RSCAN0.GAFLID12.UINT32
#define RSCAN0GAFLID12L RSCAN0.GAFLID12.UINT16[L]
#define RSCAN0GAFLID12LL RSCAN0.GAFLID12.UINT8[LL]
#define RSCAN0GAFLID12LH RSCAN0.GAFLID12.UINT8[LH]
#define RSCAN0GAFLID12H RSCAN0.GAFLID12.UINT16[H]
#define RSCAN0GAFLID12HL RSCAN0.GAFLID12.UINT8[HL]
#define RSCAN0GAFLID12HH RSCAN0.GAFLID12.UINT8[HH]
#define RSCAN0GAFLM12 RSCAN0.GAFLM12.UINT32
#define RSCAN0GAFLM12L RSCAN0.GAFLM12.UINT16[L]
#define RSCAN0GAFLM12LL RSCAN0.GAFLM12.UINT8[LL]
#define RSCAN0GAFLM12LH RSCAN0.GAFLM12.UINT8[LH]
#define RSCAN0GAFLM12H RSCAN0.GAFLM12.UINT16[H]
#define RSCAN0GAFLM12HL RSCAN0.GAFLM12.UINT8[HL]
#define RSCAN0GAFLM12HH RSCAN0.GAFLM12.UINT8[HH]
#define RSCAN0GAFLP012 RSCAN0.GAFLP012.UINT32
#define RSCAN0GAFLP012L RSCAN0.GAFLP012.UINT16[L]
#define RSCAN0GAFLP012LH RSCAN0.GAFLP012.UINT8[LH]
#define RSCAN0GAFLP012H RSCAN0.GAFLP012.UINT16[H]
#define RSCAN0GAFLP012HL RSCAN0.GAFLP012.UINT8[HL]
#define RSCAN0GAFLP012HH RSCAN0.GAFLP012.UINT8[HH]
#define RSCAN0GAFLP112 RSCAN0.GAFLP112.UINT32
#define RSCAN0GAFLP112L RSCAN0.GAFLP112.UINT16[L]
#define RSCAN0GAFLP112LL RSCAN0.GAFLP112.UINT8[LL]
#define RSCAN0GAFLP112LH RSCAN0.GAFLP112.UINT8[LH]
#define RSCAN0GAFLP112H RSCAN0.GAFLP112.UINT16[H]
#define RSCAN0GAFLP112HL RSCAN0.GAFLP112.UINT8[HL]
#define RSCAN0GAFLP112HH RSCAN0.GAFLP112.UINT8[HH]
#define RSCAN0GAFLID13 RSCAN0.GAFLID13.UINT32
#define RSCAN0GAFLID13L RSCAN0.GAFLID13.UINT16[L]
#define RSCAN0GAFLID13LL RSCAN0.GAFLID13.UINT8[LL]
#define RSCAN0GAFLID13LH RSCAN0.GAFLID13.UINT8[LH]
#define RSCAN0GAFLID13H RSCAN0.GAFLID13.UINT16[H]
#define RSCAN0GAFLID13HL RSCAN0.GAFLID13.UINT8[HL]
#define RSCAN0GAFLID13HH RSCAN0.GAFLID13.UINT8[HH]
#define RSCAN0GAFLM13 RSCAN0.GAFLM13.UINT32
#define RSCAN0GAFLM13L RSCAN0.GAFLM13.UINT16[L]
#define RSCAN0GAFLM13LL RSCAN0.GAFLM13.UINT8[LL]
#define RSCAN0GAFLM13LH RSCAN0.GAFLM13.UINT8[LH]
#define RSCAN0GAFLM13H RSCAN0.GAFLM13.UINT16[H]
#define RSCAN0GAFLM13HL RSCAN0.GAFLM13.UINT8[HL]
#define RSCAN0GAFLM13HH RSCAN0.GAFLM13.UINT8[HH]
#define RSCAN0GAFLP013 RSCAN0.GAFLP013.UINT32
#define RSCAN0GAFLP013L RSCAN0.GAFLP013.UINT16[L]
#define RSCAN0GAFLP013LH RSCAN0.GAFLP013.UINT8[LH]
#define RSCAN0GAFLP013H RSCAN0.GAFLP013.UINT16[H]
#define RSCAN0GAFLP013HL RSCAN0.GAFLP013.UINT8[HL]
#define RSCAN0GAFLP013HH RSCAN0.GAFLP013.UINT8[HH]
#define RSCAN0GAFLP113 RSCAN0.GAFLP113.UINT32
#define RSCAN0GAFLP113L RSCAN0.GAFLP113.UINT16[L]
#define RSCAN0GAFLP113LL RSCAN0.GAFLP113.UINT8[LL]
#define RSCAN0GAFLP113LH RSCAN0.GAFLP113.UINT8[LH]
#define RSCAN0GAFLP113H RSCAN0.GAFLP113.UINT16[H]
#define RSCAN0GAFLP113HL RSCAN0.GAFLP113.UINT8[HL]
#define RSCAN0GAFLP113HH RSCAN0.GAFLP113.UINT8[HH]
#define RSCAN0GAFLID14 RSCAN0.GAFLID14.UINT32
#define RSCAN0GAFLID14L RSCAN0.GAFLID14.UINT16[L]
#define RSCAN0GAFLID14LL RSCAN0.GAFLID14.UINT8[LL]
#define RSCAN0GAFLID14LH RSCAN0.GAFLID14.UINT8[LH]
#define RSCAN0GAFLID14H RSCAN0.GAFLID14.UINT16[H]
#define RSCAN0GAFLID14HL RSCAN0.GAFLID14.UINT8[HL]
#define RSCAN0GAFLID14HH RSCAN0.GAFLID14.UINT8[HH]
#define RSCAN0GAFLM14 RSCAN0.GAFLM14.UINT32
#define RSCAN0GAFLM14L RSCAN0.GAFLM14.UINT16[L]
#define RSCAN0GAFLM14LL RSCAN0.GAFLM14.UINT8[LL]
#define RSCAN0GAFLM14LH RSCAN0.GAFLM14.UINT8[LH]
#define RSCAN0GAFLM14H RSCAN0.GAFLM14.UINT16[H]
#define RSCAN0GAFLM14HL RSCAN0.GAFLM14.UINT8[HL]
#define RSCAN0GAFLM14HH RSCAN0.GAFLM14.UINT8[HH]
#define RSCAN0GAFLP014 RSCAN0.GAFLP014.UINT32
#define RSCAN0GAFLP014L RSCAN0.GAFLP014.UINT16[L]
#define RSCAN0GAFLP014LH RSCAN0.GAFLP014.UINT8[LH]
#define RSCAN0GAFLP014H RSCAN0.GAFLP014.UINT16[H]
#define RSCAN0GAFLP014HL RSCAN0.GAFLP014.UINT8[HL]
#define RSCAN0GAFLP014HH RSCAN0.GAFLP014.UINT8[HH]
#define RSCAN0GAFLP114 RSCAN0.GAFLP114.UINT32
#define RSCAN0GAFLP114L RSCAN0.GAFLP114.UINT16[L]
#define RSCAN0GAFLP114LL RSCAN0.GAFLP114.UINT8[LL]
#define RSCAN0GAFLP114LH RSCAN0.GAFLP114.UINT8[LH]
#define RSCAN0GAFLP114H RSCAN0.GAFLP114.UINT16[H]
#define RSCAN0GAFLP114HL RSCAN0.GAFLP114.UINT8[HL]
#define RSCAN0GAFLP114HH RSCAN0.GAFLP114.UINT8[HH]
#define RSCAN0GAFLID15 RSCAN0.GAFLID15.UINT32
#define RSCAN0GAFLID15L RSCAN0.GAFLID15.UINT16[L]
#define RSCAN0GAFLID15LL RSCAN0.GAFLID15.UINT8[LL]
#define RSCAN0GAFLID15LH RSCAN0.GAFLID15.UINT8[LH]
#define RSCAN0GAFLID15H RSCAN0.GAFLID15.UINT16[H]
#define RSCAN0GAFLID15HL RSCAN0.GAFLID15.UINT8[HL]
#define RSCAN0GAFLID15HH RSCAN0.GAFLID15.UINT8[HH]
#define RSCAN0GAFLM15 RSCAN0.GAFLM15.UINT32
#define RSCAN0GAFLM15L RSCAN0.GAFLM15.UINT16[L]
#define RSCAN0GAFLM15LL RSCAN0.GAFLM15.UINT8[LL]
#define RSCAN0GAFLM15LH RSCAN0.GAFLM15.UINT8[LH]
#define RSCAN0GAFLM15H RSCAN0.GAFLM15.UINT16[H]
#define RSCAN0GAFLM15HL RSCAN0.GAFLM15.UINT8[HL]
#define RSCAN0GAFLM15HH RSCAN0.GAFLM15.UINT8[HH]
#define RSCAN0GAFLP015 RSCAN0.GAFLP015.UINT32
#define RSCAN0GAFLP015L RSCAN0.GAFLP015.UINT16[L]
#define RSCAN0GAFLP015LH RSCAN0.GAFLP015.UINT8[LH]
#define RSCAN0GAFLP015H RSCAN0.GAFLP015.UINT16[H]
#define RSCAN0GAFLP015HL RSCAN0.GAFLP015.UINT8[HL]
#define RSCAN0GAFLP015HH RSCAN0.GAFLP015.UINT8[HH]
#define RSCAN0GAFLP115 RSCAN0.GAFLP115.UINT32
#define RSCAN0GAFLP115L RSCAN0.GAFLP115.UINT16[L]
#define RSCAN0GAFLP115LL RSCAN0.GAFLP115.UINT8[LL]
#define RSCAN0GAFLP115LH RSCAN0.GAFLP115.UINT8[LH]
#define RSCAN0GAFLP115H RSCAN0.GAFLP115.UINT16[H]
#define RSCAN0GAFLP115HL RSCAN0.GAFLP115.UINT8[HL]
#define RSCAN0GAFLP115HH RSCAN0.GAFLP115.UINT8[HH]
#define RSCAN0RMID0 RSCAN0.RMID0.UINT32
#define RSCAN0RMID0L RSCAN0.RMID0.UINT16[L]
#define RSCAN0RMID0LL RSCAN0.RMID0.UINT8[LL]
#define RSCAN0RMID0LH RSCAN0.RMID0.UINT8[LH]
#define RSCAN0RMID0H RSCAN0.RMID0.UINT16[H]
#define RSCAN0RMID0HL RSCAN0.RMID0.UINT8[HL]
#define RSCAN0RMID0HH RSCAN0.RMID0.UINT8[HH]
#define RSCAN0RMPTR0 RSCAN0.RMPTR0.UINT32
#define RSCAN0RMPTR0L RSCAN0.RMPTR0.UINT16[L]
#define RSCAN0RMPTR0LL RSCAN0.RMPTR0.UINT8[LL]
#define RSCAN0RMPTR0LH RSCAN0.RMPTR0.UINT8[LH]
#define RSCAN0RMPTR0H RSCAN0.RMPTR0.UINT16[H]
#define RSCAN0RMPTR0HL RSCAN0.RMPTR0.UINT8[HL]
#define RSCAN0RMPTR0HH RSCAN0.RMPTR0.UINT8[HH]
#define RSCAN0RMDF00 RSCAN0.RMDF00.UINT32
#define RSCAN0RMDF00L RSCAN0.RMDF00.UINT16[L]
#define RSCAN0RMDF00LL RSCAN0.RMDF00.UINT8[LL]
#define RSCAN0RMDF00LH RSCAN0.RMDF00.UINT8[LH]
#define RSCAN0RMDF00H RSCAN0.RMDF00.UINT16[H]
#define RSCAN0RMDF00HL RSCAN0.RMDF00.UINT8[HL]
#define RSCAN0RMDF00HH RSCAN0.RMDF00.UINT8[HH]
#define RSCAN0RMDF10 RSCAN0.RMDF10.UINT32
#define RSCAN0RMDF10L RSCAN0.RMDF10.UINT16[L]
#define RSCAN0RMDF10LL RSCAN0.RMDF10.UINT8[LL]
#define RSCAN0RMDF10LH RSCAN0.RMDF10.UINT8[LH]
#define RSCAN0RMDF10H RSCAN0.RMDF10.UINT16[H]
#define RSCAN0RMDF10HL RSCAN0.RMDF10.UINT8[HL]
#define RSCAN0RMDF10HH RSCAN0.RMDF10.UINT8[HH]
#define RSCAN0RMID1 RSCAN0.RMID1.UINT32
#define RSCAN0RMID1L RSCAN0.RMID1.UINT16[L]
#define RSCAN0RMID1LL RSCAN0.RMID1.UINT8[LL]
#define RSCAN0RMID1LH RSCAN0.RMID1.UINT8[LH]
#define RSCAN0RMID1H RSCAN0.RMID1.UINT16[H]
#define RSCAN0RMID1HL RSCAN0.RMID1.UINT8[HL]
#define RSCAN0RMID1HH RSCAN0.RMID1.UINT8[HH]
#define RSCAN0RMPTR1 RSCAN0.RMPTR1.UINT32
#define RSCAN0RMPTR1L RSCAN0.RMPTR1.UINT16[L]
#define RSCAN0RMPTR1LL RSCAN0.RMPTR1.UINT8[LL]
#define RSCAN0RMPTR1LH RSCAN0.RMPTR1.UINT8[LH]
#define RSCAN0RMPTR1H RSCAN0.RMPTR1.UINT16[H]
#define RSCAN0RMPTR1HL RSCAN0.RMPTR1.UINT8[HL]
#define RSCAN0RMPTR1HH RSCAN0.RMPTR1.UINT8[HH]
#define RSCAN0RMDF01 RSCAN0.RMDF01.UINT32
#define RSCAN0RMDF01L RSCAN0.RMDF01.UINT16[L]
#define RSCAN0RMDF01LL RSCAN0.RMDF01.UINT8[LL]
#define RSCAN0RMDF01LH RSCAN0.RMDF01.UINT8[LH]
#define RSCAN0RMDF01H RSCAN0.RMDF01.UINT16[H]
#define RSCAN0RMDF01HL RSCAN0.RMDF01.UINT8[HL]
#define RSCAN0RMDF01HH RSCAN0.RMDF01.UINT8[HH]
#define RSCAN0RMDF11 RSCAN0.RMDF11.UINT32
#define RSCAN0RMDF11L RSCAN0.RMDF11.UINT16[L]
#define RSCAN0RMDF11LL RSCAN0.RMDF11.UINT8[LL]
#define RSCAN0RMDF11LH RSCAN0.RMDF11.UINT8[LH]
#define RSCAN0RMDF11H RSCAN0.RMDF11.UINT16[H]
#define RSCAN0RMDF11HL RSCAN0.RMDF11.UINT8[HL]
#define RSCAN0RMDF11HH RSCAN0.RMDF11.UINT8[HH]
#define RSCAN0RMID2 RSCAN0.RMID2.UINT32
#define RSCAN0RMID2L RSCAN0.RMID2.UINT16[L]
#define RSCAN0RMID2LL RSCAN0.RMID2.UINT8[LL]
#define RSCAN0RMID2LH RSCAN0.RMID2.UINT8[LH]
#define RSCAN0RMID2H RSCAN0.RMID2.UINT16[H]
#define RSCAN0RMID2HL RSCAN0.RMID2.UINT8[HL]
#define RSCAN0RMID2HH RSCAN0.RMID2.UINT8[HH]
#define RSCAN0RMPTR2 RSCAN0.RMPTR2.UINT32
#define RSCAN0RMPTR2L RSCAN0.RMPTR2.UINT16[L]
#define RSCAN0RMPTR2LL RSCAN0.RMPTR2.UINT8[LL]
#define RSCAN0RMPTR2LH RSCAN0.RMPTR2.UINT8[LH]
#define RSCAN0RMPTR2H RSCAN0.RMPTR2.UINT16[H]
#define RSCAN0RMPTR2HL RSCAN0.RMPTR2.UINT8[HL]
#define RSCAN0RMPTR2HH RSCAN0.RMPTR2.UINT8[HH]
#define RSCAN0RMDF02 RSCAN0.RMDF02.UINT32
#define RSCAN0RMDF02L RSCAN0.RMDF02.UINT16[L]
#define RSCAN0RMDF02LL RSCAN0.RMDF02.UINT8[LL]
#define RSCAN0RMDF02LH RSCAN0.RMDF02.UINT8[LH]
#define RSCAN0RMDF02H RSCAN0.RMDF02.UINT16[H]
#define RSCAN0RMDF02HL RSCAN0.RMDF02.UINT8[HL]
#define RSCAN0RMDF02HH RSCAN0.RMDF02.UINT8[HH]
#define RSCAN0RMDF12 RSCAN0.RMDF12.UINT32
#define RSCAN0RMDF12L RSCAN0.RMDF12.UINT16[L]
#define RSCAN0RMDF12LL RSCAN0.RMDF12.UINT8[LL]
#define RSCAN0RMDF12LH RSCAN0.RMDF12.UINT8[LH]
#define RSCAN0RMDF12H RSCAN0.RMDF12.UINT16[H]
#define RSCAN0RMDF12HL RSCAN0.RMDF12.UINT8[HL]
#define RSCAN0RMDF12HH RSCAN0.RMDF12.UINT8[HH]
#define RSCAN0RMID3 RSCAN0.RMID3.UINT32
#define RSCAN0RMID3L RSCAN0.RMID3.UINT16[L]
#define RSCAN0RMID3LL RSCAN0.RMID3.UINT8[LL]
#define RSCAN0RMID3LH RSCAN0.RMID3.UINT8[LH]
#define RSCAN0RMID3H RSCAN0.RMID3.UINT16[H]
#define RSCAN0RMID3HL RSCAN0.RMID3.UINT8[HL]
#define RSCAN0RMID3HH RSCAN0.RMID3.UINT8[HH]
#define RSCAN0RMPTR3 RSCAN0.RMPTR3.UINT32
#define RSCAN0RMPTR3L RSCAN0.RMPTR3.UINT16[L]
#define RSCAN0RMPTR3LL RSCAN0.RMPTR3.UINT8[LL]
#define RSCAN0RMPTR3LH RSCAN0.RMPTR3.UINT8[LH]
#define RSCAN0RMPTR3H RSCAN0.RMPTR3.UINT16[H]
#define RSCAN0RMPTR3HL RSCAN0.RMPTR3.UINT8[HL]
#define RSCAN0RMPTR3HH RSCAN0.RMPTR3.UINT8[HH]
#define RSCAN0RMDF03 RSCAN0.RMDF03.UINT32
#define RSCAN0RMDF03L RSCAN0.RMDF03.UINT16[L]
#define RSCAN0RMDF03LL RSCAN0.RMDF03.UINT8[LL]
#define RSCAN0RMDF03LH RSCAN0.RMDF03.UINT8[LH]
#define RSCAN0RMDF03H RSCAN0.RMDF03.UINT16[H]
#define RSCAN0RMDF03HL RSCAN0.RMDF03.UINT8[HL]
#define RSCAN0RMDF03HH RSCAN0.RMDF03.UINT8[HH]
#define RSCAN0RMDF13 RSCAN0.RMDF13.UINT32
#define RSCAN0RMDF13L RSCAN0.RMDF13.UINT16[L]
#define RSCAN0RMDF13LL RSCAN0.RMDF13.UINT8[LL]
#define RSCAN0RMDF13LH RSCAN0.RMDF13.UINT8[LH]
#define RSCAN0RMDF13H RSCAN0.RMDF13.UINT16[H]
#define RSCAN0RMDF13HL RSCAN0.RMDF13.UINT8[HL]
#define RSCAN0RMDF13HH RSCAN0.RMDF13.UINT8[HH]
#define RSCAN0RMID4 RSCAN0.RMID4.UINT32
#define RSCAN0RMID4L RSCAN0.RMID4.UINT16[L]
#define RSCAN0RMID4LL RSCAN0.RMID4.UINT8[LL]
#define RSCAN0RMID4LH RSCAN0.RMID4.UINT8[LH]
#define RSCAN0RMID4H RSCAN0.RMID4.UINT16[H]
#define RSCAN0RMID4HL RSCAN0.RMID4.UINT8[HL]
#define RSCAN0RMID4HH RSCAN0.RMID4.UINT8[HH]
#define RSCAN0RMPTR4 RSCAN0.RMPTR4.UINT32
#define RSCAN0RMPTR4L RSCAN0.RMPTR4.UINT16[L]
#define RSCAN0RMPTR4LL RSCAN0.RMPTR4.UINT8[LL]
#define RSCAN0RMPTR4LH RSCAN0.RMPTR4.UINT8[LH]
#define RSCAN0RMPTR4H RSCAN0.RMPTR4.UINT16[H]
#define RSCAN0RMPTR4HL RSCAN0.RMPTR4.UINT8[HL]
#define RSCAN0RMPTR4HH RSCAN0.RMPTR4.UINT8[HH]
#define RSCAN0RMDF04 RSCAN0.RMDF04.UINT32
#define RSCAN0RMDF04L RSCAN0.RMDF04.UINT16[L]
#define RSCAN0RMDF04LL RSCAN0.RMDF04.UINT8[LL]
#define RSCAN0RMDF04LH RSCAN0.RMDF04.UINT8[LH]
#define RSCAN0RMDF04H RSCAN0.RMDF04.UINT16[H]
#define RSCAN0RMDF04HL RSCAN0.RMDF04.UINT8[HL]
#define RSCAN0RMDF04HH RSCAN0.RMDF04.UINT8[HH]
#define RSCAN0RMDF14 RSCAN0.RMDF14.UINT32
#define RSCAN0RMDF14L RSCAN0.RMDF14.UINT16[L]
#define RSCAN0RMDF14LL RSCAN0.RMDF14.UINT8[LL]
#define RSCAN0RMDF14LH RSCAN0.RMDF14.UINT8[LH]
#define RSCAN0RMDF14H RSCAN0.RMDF14.UINT16[H]
#define RSCAN0RMDF14HL RSCAN0.RMDF14.UINT8[HL]
#define RSCAN0RMDF14HH RSCAN0.RMDF14.UINT8[HH]
#define RSCAN0RMID5 RSCAN0.RMID5.UINT32
#define RSCAN0RMID5L RSCAN0.RMID5.UINT16[L]
#define RSCAN0RMID5LL RSCAN0.RMID5.UINT8[LL]
#define RSCAN0RMID5LH RSCAN0.RMID5.UINT8[LH]
#define RSCAN0RMID5H RSCAN0.RMID5.UINT16[H]
#define RSCAN0RMID5HL RSCAN0.RMID5.UINT8[HL]
#define RSCAN0RMID5HH RSCAN0.RMID5.UINT8[HH]
#define RSCAN0RMPTR5 RSCAN0.RMPTR5.UINT32
#define RSCAN0RMPTR5L RSCAN0.RMPTR5.UINT16[L]
#define RSCAN0RMPTR5LL RSCAN0.RMPTR5.UINT8[LL]
#define RSCAN0RMPTR5LH RSCAN0.RMPTR5.UINT8[LH]
#define RSCAN0RMPTR5H RSCAN0.RMPTR5.UINT16[H]
#define RSCAN0RMPTR5HL RSCAN0.RMPTR5.UINT8[HL]
#define RSCAN0RMPTR5HH RSCAN0.RMPTR5.UINT8[HH]
#define RSCAN0RMDF05 RSCAN0.RMDF05.UINT32
#define RSCAN0RMDF05L RSCAN0.RMDF05.UINT16[L]
#define RSCAN0RMDF05LL RSCAN0.RMDF05.UINT8[LL]
#define RSCAN0RMDF05LH RSCAN0.RMDF05.UINT8[LH]
#define RSCAN0RMDF05H RSCAN0.RMDF05.UINT16[H]
#define RSCAN0RMDF05HL RSCAN0.RMDF05.UINT8[HL]
#define RSCAN0RMDF05HH RSCAN0.RMDF05.UINT8[HH]
#define RSCAN0RMDF15 RSCAN0.RMDF15.UINT32
#define RSCAN0RMDF15L RSCAN0.RMDF15.UINT16[L]
#define RSCAN0RMDF15LL RSCAN0.RMDF15.UINT8[LL]
#define RSCAN0RMDF15LH RSCAN0.RMDF15.UINT8[LH]
#define RSCAN0RMDF15H RSCAN0.RMDF15.UINT16[H]
#define RSCAN0RMDF15HL RSCAN0.RMDF15.UINT8[HL]
#define RSCAN0RMDF15HH RSCAN0.RMDF15.UINT8[HH]
#define RSCAN0RMID6 RSCAN0.RMID6.UINT32
#define RSCAN0RMID6L RSCAN0.RMID6.UINT16[L]
#define RSCAN0RMID6LL RSCAN0.RMID6.UINT8[LL]
#define RSCAN0RMID6LH RSCAN0.RMID6.UINT8[LH]
#define RSCAN0RMID6H RSCAN0.RMID6.UINT16[H]
#define RSCAN0RMID6HL RSCAN0.RMID6.UINT8[HL]
#define RSCAN0RMID6HH RSCAN0.RMID6.UINT8[HH]
#define RSCAN0RMPTR6 RSCAN0.RMPTR6.UINT32
#define RSCAN0RMPTR6L RSCAN0.RMPTR6.UINT16[L]
#define RSCAN0RMPTR6LL RSCAN0.RMPTR6.UINT8[LL]
#define RSCAN0RMPTR6LH RSCAN0.RMPTR6.UINT8[LH]
#define RSCAN0RMPTR6H RSCAN0.RMPTR6.UINT16[H]
#define RSCAN0RMPTR6HL RSCAN0.RMPTR6.UINT8[HL]
#define RSCAN0RMPTR6HH RSCAN0.RMPTR6.UINT8[HH]
#define RSCAN0RMDF06 RSCAN0.RMDF06.UINT32
#define RSCAN0RMDF06L RSCAN0.RMDF06.UINT16[L]
#define RSCAN0RMDF06LL RSCAN0.RMDF06.UINT8[LL]
#define RSCAN0RMDF06LH RSCAN0.RMDF06.UINT8[LH]
#define RSCAN0RMDF06H RSCAN0.RMDF06.UINT16[H]
#define RSCAN0RMDF06HL RSCAN0.RMDF06.UINT8[HL]
#define RSCAN0RMDF06HH RSCAN0.RMDF06.UINT8[HH]
#define RSCAN0RMDF16 RSCAN0.RMDF16.UINT32
#define RSCAN0RMDF16L RSCAN0.RMDF16.UINT16[L]
#define RSCAN0RMDF16LL RSCAN0.RMDF16.UINT8[LL]
#define RSCAN0RMDF16LH RSCAN0.RMDF16.UINT8[LH]
#define RSCAN0RMDF16H RSCAN0.RMDF16.UINT16[H]
#define RSCAN0RMDF16HL RSCAN0.RMDF16.UINT8[HL]
#define RSCAN0RMDF16HH RSCAN0.RMDF16.UINT8[HH]
#define RSCAN0RMID7 RSCAN0.RMID7.UINT32
#define RSCAN0RMID7L RSCAN0.RMID7.UINT16[L]
#define RSCAN0RMID7LL RSCAN0.RMID7.UINT8[LL]
#define RSCAN0RMID7LH RSCAN0.RMID7.UINT8[LH]
#define RSCAN0RMID7H RSCAN0.RMID7.UINT16[H]
#define RSCAN0RMID7HL RSCAN0.RMID7.UINT8[HL]
#define RSCAN0RMID7HH RSCAN0.RMID7.UINT8[HH]
#define RSCAN0RMPTR7 RSCAN0.RMPTR7.UINT32
#define RSCAN0RMPTR7L RSCAN0.RMPTR7.UINT16[L]
#define RSCAN0RMPTR7LL RSCAN0.RMPTR7.UINT8[LL]
#define RSCAN0RMPTR7LH RSCAN0.RMPTR7.UINT8[LH]
#define RSCAN0RMPTR7H RSCAN0.RMPTR7.UINT16[H]
#define RSCAN0RMPTR7HL RSCAN0.RMPTR7.UINT8[HL]
#define RSCAN0RMPTR7HH RSCAN0.RMPTR7.UINT8[HH]
#define RSCAN0RMDF07 RSCAN0.RMDF07.UINT32
#define RSCAN0RMDF07L RSCAN0.RMDF07.UINT16[L]
#define RSCAN0RMDF07LL RSCAN0.RMDF07.UINT8[LL]
#define RSCAN0RMDF07LH RSCAN0.RMDF07.UINT8[LH]
#define RSCAN0RMDF07H RSCAN0.RMDF07.UINT16[H]
#define RSCAN0RMDF07HL RSCAN0.RMDF07.UINT8[HL]
#define RSCAN0RMDF07HH RSCAN0.RMDF07.UINT8[HH]
#define RSCAN0RMDF17 RSCAN0.RMDF17.UINT32
#define RSCAN0RMDF17L RSCAN0.RMDF17.UINT16[L]
#define RSCAN0RMDF17LL RSCAN0.RMDF17.UINT8[LL]
#define RSCAN0RMDF17LH RSCAN0.RMDF17.UINT8[LH]
#define RSCAN0RMDF17H RSCAN0.RMDF17.UINT16[H]
#define RSCAN0RMDF17HL RSCAN0.RMDF17.UINT8[HL]
#define RSCAN0RMDF17HH RSCAN0.RMDF17.UINT8[HH]
#define RSCAN0RMID8 RSCAN0.RMID8.UINT32
#define RSCAN0RMID8L RSCAN0.RMID8.UINT16[L]
#define RSCAN0RMID8LL RSCAN0.RMID8.UINT8[LL]
#define RSCAN0RMID8LH RSCAN0.RMID8.UINT8[LH]
#define RSCAN0RMID8H RSCAN0.RMID8.UINT16[H]
#define RSCAN0RMID8HL RSCAN0.RMID8.UINT8[HL]
#define RSCAN0RMID8HH RSCAN0.RMID8.UINT8[HH]
#define RSCAN0RMPTR8 RSCAN0.RMPTR8.UINT32
#define RSCAN0RMPTR8L RSCAN0.RMPTR8.UINT16[L]
#define RSCAN0RMPTR8LL RSCAN0.RMPTR8.UINT8[LL]
#define RSCAN0RMPTR8LH RSCAN0.RMPTR8.UINT8[LH]
#define RSCAN0RMPTR8H RSCAN0.RMPTR8.UINT16[H]
#define RSCAN0RMPTR8HL RSCAN0.RMPTR8.UINT8[HL]
#define RSCAN0RMPTR8HH RSCAN0.RMPTR8.UINT8[HH]
#define RSCAN0RMDF08 RSCAN0.RMDF08.UINT32
#define RSCAN0RMDF08L RSCAN0.RMDF08.UINT16[L]
#define RSCAN0RMDF08LL RSCAN0.RMDF08.UINT8[LL]
#define RSCAN0RMDF08LH RSCAN0.RMDF08.UINT8[LH]
#define RSCAN0RMDF08H RSCAN0.RMDF08.UINT16[H]
#define RSCAN0RMDF08HL RSCAN0.RMDF08.UINT8[HL]
#define RSCAN0RMDF08HH RSCAN0.RMDF08.UINT8[HH]
#define RSCAN0RMDF18 RSCAN0.RMDF18.UINT32
#define RSCAN0RMDF18L RSCAN0.RMDF18.UINT16[L]
#define RSCAN0RMDF18LL RSCAN0.RMDF18.UINT8[LL]
#define RSCAN0RMDF18LH RSCAN0.RMDF18.UINT8[LH]
#define RSCAN0RMDF18H RSCAN0.RMDF18.UINT16[H]
#define RSCAN0RMDF18HL RSCAN0.RMDF18.UINT8[HL]
#define RSCAN0RMDF18HH RSCAN0.RMDF18.UINT8[HH]
#define RSCAN0RMID9 RSCAN0.RMID9.UINT32
#define RSCAN0RMID9L RSCAN0.RMID9.UINT16[L]
#define RSCAN0RMID9LL RSCAN0.RMID9.UINT8[LL]
#define RSCAN0RMID9LH RSCAN0.RMID9.UINT8[LH]
#define RSCAN0RMID9H RSCAN0.RMID9.UINT16[H]
#define RSCAN0RMID9HL RSCAN0.RMID9.UINT8[HL]
#define RSCAN0RMID9HH RSCAN0.RMID9.UINT8[HH]
#define RSCAN0RMPTR9 RSCAN0.RMPTR9.UINT32
#define RSCAN0RMPTR9L RSCAN0.RMPTR9.UINT16[L]
#define RSCAN0RMPTR9LL RSCAN0.RMPTR9.UINT8[LL]
#define RSCAN0RMPTR9LH RSCAN0.RMPTR9.UINT8[LH]
#define RSCAN0RMPTR9H RSCAN0.RMPTR9.UINT16[H]
#define RSCAN0RMPTR9HL RSCAN0.RMPTR9.UINT8[HL]
#define RSCAN0RMPTR9HH RSCAN0.RMPTR9.UINT8[HH]
#define RSCAN0RMDF09 RSCAN0.RMDF09.UINT32
#define RSCAN0RMDF09L RSCAN0.RMDF09.UINT16[L]
#define RSCAN0RMDF09LL RSCAN0.RMDF09.UINT8[LL]
#define RSCAN0RMDF09LH RSCAN0.RMDF09.UINT8[LH]
#define RSCAN0RMDF09H RSCAN0.RMDF09.UINT16[H]
#define RSCAN0RMDF09HL RSCAN0.RMDF09.UINT8[HL]
#define RSCAN0RMDF09HH RSCAN0.RMDF09.UINT8[HH]
#define RSCAN0RMDF19 RSCAN0.RMDF19.UINT32
#define RSCAN0RMDF19L RSCAN0.RMDF19.UINT16[L]
#define RSCAN0RMDF19LL RSCAN0.RMDF19.UINT8[LL]
#define RSCAN0RMDF19LH RSCAN0.RMDF19.UINT8[LH]
#define RSCAN0RMDF19H RSCAN0.RMDF19.UINT16[H]
#define RSCAN0RMDF19HL RSCAN0.RMDF19.UINT8[HL]
#define RSCAN0RMDF19HH RSCAN0.RMDF19.UINT8[HH]
#define RSCAN0RMID10 RSCAN0.RMID10.UINT32
#define RSCAN0RMID10L RSCAN0.RMID10.UINT16[L]
#define RSCAN0RMID10LL RSCAN0.RMID10.UINT8[LL]
#define RSCAN0RMID10LH RSCAN0.RMID10.UINT8[LH]
#define RSCAN0RMID10H RSCAN0.RMID10.UINT16[H]
#define RSCAN0RMID10HL RSCAN0.RMID10.UINT8[HL]
#define RSCAN0RMID10HH RSCAN0.RMID10.UINT8[HH]
#define RSCAN0RMPTR10 RSCAN0.RMPTR10.UINT32
#define RSCAN0RMPTR10L RSCAN0.RMPTR10.UINT16[L]
#define RSCAN0RMPTR10LL RSCAN0.RMPTR10.UINT8[LL]
#define RSCAN0RMPTR10LH RSCAN0.RMPTR10.UINT8[LH]
#define RSCAN0RMPTR10H RSCAN0.RMPTR10.UINT16[H]
#define RSCAN0RMPTR10HL RSCAN0.RMPTR10.UINT8[HL]
#define RSCAN0RMPTR10HH RSCAN0.RMPTR10.UINT8[HH]
#define RSCAN0RMDF010 RSCAN0.RMDF010.UINT32
#define RSCAN0RMDF010L RSCAN0.RMDF010.UINT16[L]
#define RSCAN0RMDF010LL RSCAN0.RMDF010.UINT8[LL]
#define RSCAN0RMDF010LH RSCAN0.RMDF010.UINT8[LH]
#define RSCAN0RMDF010H RSCAN0.RMDF010.UINT16[H]
#define RSCAN0RMDF010HL RSCAN0.RMDF010.UINT8[HL]
#define RSCAN0RMDF010HH RSCAN0.RMDF010.UINT8[HH]
#define RSCAN0RMDF110 RSCAN0.RMDF110.UINT32
#define RSCAN0RMDF110L RSCAN0.RMDF110.UINT16[L]
#define RSCAN0RMDF110LL RSCAN0.RMDF110.UINT8[LL]
#define RSCAN0RMDF110LH RSCAN0.RMDF110.UINT8[LH]
#define RSCAN0RMDF110H RSCAN0.RMDF110.UINT16[H]
#define RSCAN0RMDF110HL RSCAN0.RMDF110.UINT8[HL]
#define RSCAN0RMDF110HH RSCAN0.RMDF110.UINT8[HH]
#define RSCAN0RMID11 RSCAN0.RMID11.UINT32
#define RSCAN0RMID11L RSCAN0.RMID11.UINT16[L]
#define RSCAN0RMID11LL RSCAN0.RMID11.UINT8[LL]
#define RSCAN0RMID11LH RSCAN0.RMID11.UINT8[LH]
#define RSCAN0RMID11H RSCAN0.RMID11.UINT16[H]
#define RSCAN0RMID11HL RSCAN0.RMID11.UINT8[HL]
#define RSCAN0RMID11HH RSCAN0.RMID11.UINT8[HH]
#define RSCAN0RMPTR11 RSCAN0.RMPTR11.UINT32
#define RSCAN0RMPTR11L RSCAN0.RMPTR11.UINT16[L]
#define RSCAN0RMPTR11LL RSCAN0.RMPTR11.UINT8[LL]
#define RSCAN0RMPTR11LH RSCAN0.RMPTR11.UINT8[LH]
#define RSCAN0RMPTR11H RSCAN0.RMPTR11.UINT16[H]
#define RSCAN0RMPTR11HL RSCAN0.RMPTR11.UINT8[HL]
#define RSCAN0RMPTR11HH RSCAN0.RMPTR11.UINT8[HH]
#define RSCAN0RMDF011 RSCAN0.RMDF011.UINT32
#define RSCAN0RMDF011L RSCAN0.RMDF011.UINT16[L]
#define RSCAN0RMDF011LL RSCAN0.RMDF011.UINT8[LL]
#define RSCAN0RMDF011LH RSCAN0.RMDF011.UINT8[LH]
#define RSCAN0RMDF011H RSCAN0.RMDF011.UINT16[H]
#define RSCAN0RMDF011HL RSCAN0.RMDF011.UINT8[HL]
#define RSCAN0RMDF011HH RSCAN0.RMDF011.UINT8[HH]
#define RSCAN0RMDF111 RSCAN0.RMDF111.UINT32
#define RSCAN0RMDF111L RSCAN0.RMDF111.UINT16[L]
#define RSCAN0RMDF111LL RSCAN0.RMDF111.UINT8[LL]
#define RSCAN0RMDF111LH RSCAN0.RMDF111.UINT8[LH]
#define RSCAN0RMDF111H RSCAN0.RMDF111.UINT16[H]
#define RSCAN0RMDF111HL RSCAN0.RMDF111.UINT8[HL]
#define RSCAN0RMDF111HH RSCAN0.RMDF111.UINT8[HH]
#define RSCAN0RMID12 RSCAN0.RMID12.UINT32
#define RSCAN0RMID12L RSCAN0.RMID12.UINT16[L]
#define RSCAN0RMID12LL RSCAN0.RMID12.UINT8[LL]
#define RSCAN0RMID12LH RSCAN0.RMID12.UINT8[LH]
#define RSCAN0RMID12H RSCAN0.RMID12.UINT16[H]
#define RSCAN0RMID12HL RSCAN0.RMID12.UINT8[HL]
#define RSCAN0RMID12HH RSCAN0.RMID12.UINT8[HH]
#define RSCAN0RMPTR12 RSCAN0.RMPTR12.UINT32
#define RSCAN0RMPTR12L RSCAN0.RMPTR12.UINT16[L]
#define RSCAN0RMPTR12LL RSCAN0.RMPTR12.UINT8[LL]
#define RSCAN0RMPTR12LH RSCAN0.RMPTR12.UINT8[LH]
#define RSCAN0RMPTR12H RSCAN0.RMPTR12.UINT16[H]
#define RSCAN0RMPTR12HL RSCAN0.RMPTR12.UINT8[HL]
#define RSCAN0RMPTR12HH RSCAN0.RMPTR12.UINT8[HH]
#define RSCAN0RMDF012 RSCAN0.RMDF012.UINT32
#define RSCAN0RMDF012L RSCAN0.RMDF012.UINT16[L]
#define RSCAN0RMDF012LL RSCAN0.RMDF012.UINT8[LL]
#define RSCAN0RMDF012LH RSCAN0.RMDF012.UINT8[LH]
#define RSCAN0RMDF012H RSCAN0.RMDF012.UINT16[H]
#define RSCAN0RMDF012HL RSCAN0.RMDF012.UINT8[HL]
#define RSCAN0RMDF012HH RSCAN0.RMDF012.UINT8[HH]
#define RSCAN0RMDF112 RSCAN0.RMDF112.UINT32
#define RSCAN0RMDF112L RSCAN0.RMDF112.UINT16[L]
#define RSCAN0RMDF112LL RSCAN0.RMDF112.UINT8[LL]
#define RSCAN0RMDF112LH RSCAN0.RMDF112.UINT8[LH]
#define RSCAN0RMDF112H RSCAN0.RMDF112.UINT16[H]
#define RSCAN0RMDF112HL RSCAN0.RMDF112.UINT8[HL]
#define RSCAN0RMDF112HH RSCAN0.RMDF112.UINT8[HH]
#define RSCAN0RMID13 RSCAN0.RMID13.UINT32
#define RSCAN0RMID13L RSCAN0.RMID13.UINT16[L]
#define RSCAN0RMID13LL RSCAN0.RMID13.UINT8[LL]
#define RSCAN0RMID13LH RSCAN0.RMID13.UINT8[LH]
#define RSCAN0RMID13H RSCAN0.RMID13.UINT16[H]
#define RSCAN0RMID13HL RSCAN0.RMID13.UINT8[HL]
#define RSCAN0RMID13HH RSCAN0.RMID13.UINT8[HH]
#define RSCAN0RMPTR13 RSCAN0.RMPTR13.UINT32
#define RSCAN0RMPTR13L RSCAN0.RMPTR13.UINT16[L]
#define RSCAN0RMPTR13LL RSCAN0.RMPTR13.UINT8[LL]
#define RSCAN0RMPTR13LH RSCAN0.RMPTR13.UINT8[LH]
#define RSCAN0RMPTR13H RSCAN0.RMPTR13.UINT16[H]
#define RSCAN0RMPTR13HL RSCAN0.RMPTR13.UINT8[HL]
#define RSCAN0RMPTR13HH RSCAN0.RMPTR13.UINT8[HH]
#define RSCAN0RMDF013 RSCAN0.RMDF013.UINT32
#define RSCAN0RMDF013L RSCAN0.RMDF013.UINT16[L]
#define RSCAN0RMDF013LL RSCAN0.RMDF013.UINT8[LL]
#define RSCAN0RMDF013LH RSCAN0.RMDF013.UINT8[LH]
#define RSCAN0RMDF013H RSCAN0.RMDF013.UINT16[H]
#define RSCAN0RMDF013HL RSCAN0.RMDF013.UINT8[HL]
#define RSCAN0RMDF013HH RSCAN0.RMDF013.UINT8[HH]
#define RSCAN0RMDF113 RSCAN0.RMDF113.UINT32
#define RSCAN0RMDF113L RSCAN0.RMDF113.UINT16[L]
#define RSCAN0RMDF113LL RSCAN0.RMDF113.UINT8[LL]
#define RSCAN0RMDF113LH RSCAN0.RMDF113.UINT8[LH]
#define RSCAN0RMDF113H RSCAN0.RMDF113.UINT16[H]
#define RSCAN0RMDF113HL RSCAN0.RMDF113.UINT8[HL]
#define RSCAN0RMDF113HH RSCAN0.RMDF113.UINT8[HH]
#define RSCAN0RMID14 RSCAN0.RMID14.UINT32
#define RSCAN0RMID14L RSCAN0.RMID14.UINT16[L]
#define RSCAN0RMID14LL RSCAN0.RMID14.UINT8[LL]
#define RSCAN0RMID14LH RSCAN0.RMID14.UINT8[LH]
#define RSCAN0RMID14H RSCAN0.RMID14.UINT16[H]
#define RSCAN0RMID14HL RSCAN0.RMID14.UINT8[HL]
#define RSCAN0RMID14HH RSCAN0.RMID14.UINT8[HH]
#define RSCAN0RMPTR14 RSCAN0.RMPTR14.UINT32
#define RSCAN0RMPTR14L RSCAN0.RMPTR14.UINT16[L]
#define RSCAN0RMPTR14LL RSCAN0.RMPTR14.UINT8[LL]
#define RSCAN0RMPTR14LH RSCAN0.RMPTR14.UINT8[LH]
#define RSCAN0RMPTR14H RSCAN0.RMPTR14.UINT16[H]
#define RSCAN0RMPTR14HL RSCAN0.RMPTR14.UINT8[HL]
#define RSCAN0RMPTR14HH RSCAN0.RMPTR14.UINT8[HH]
#define RSCAN0RMDF014 RSCAN0.RMDF014.UINT32
#define RSCAN0RMDF014L RSCAN0.RMDF014.UINT16[L]
#define RSCAN0RMDF014LL RSCAN0.RMDF014.UINT8[LL]
#define RSCAN0RMDF014LH RSCAN0.RMDF014.UINT8[LH]
#define RSCAN0RMDF014H RSCAN0.RMDF014.UINT16[H]
#define RSCAN0RMDF014HL RSCAN0.RMDF014.UINT8[HL]
#define RSCAN0RMDF014HH RSCAN0.RMDF014.UINT8[HH]
#define RSCAN0RMDF114 RSCAN0.RMDF114.UINT32
#define RSCAN0RMDF114L RSCAN0.RMDF114.UINT16[L]
#define RSCAN0RMDF114LL RSCAN0.RMDF114.UINT8[LL]
#define RSCAN0RMDF114LH RSCAN0.RMDF114.UINT8[LH]
#define RSCAN0RMDF114H RSCAN0.RMDF114.UINT16[H]
#define RSCAN0RMDF114HL RSCAN0.RMDF114.UINT8[HL]
#define RSCAN0RMDF114HH RSCAN0.RMDF114.UINT8[HH]
#define RSCAN0RMID15 RSCAN0.RMID15.UINT32
#define RSCAN0RMID15L RSCAN0.RMID15.UINT16[L]
#define RSCAN0RMID15LL RSCAN0.RMID15.UINT8[LL]
#define RSCAN0RMID15LH RSCAN0.RMID15.UINT8[LH]
#define RSCAN0RMID15H RSCAN0.RMID15.UINT16[H]
#define RSCAN0RMID15HL RSCAN0.RMID15.UINT8[HL]
#define RSCAN0RMID15HH RSCAN0.RMID15.UINT8[HH]
#define RSCAN0RMPTR15 RSCAN0.RMPTR15.UINT32
#define RSCAN0RMPTR15L RSCAN0.RMPTR15.UINT16[L]
#define RSCAN0RMPTR15LL RSCAN0.RMPTR15.UINT8[LL]
#define RSCAN0RMPTR15LH RSCAN0.RMPTR15.UINT8[LH]
#define RSCAN0RMPTR15H RSCAN0.RMPTR15.UINT16[H]
#define RSCAN0RMPTR15HL RSCAN0.RMPTR15.UINT8[HL]
#define RSCAN0RMPTR15HH RSCAN0.RMPTR15.UINT8[HH]
#define RSCAN0RMDF015 RSCAN0.RMDF015.UINT32
#define RSCAN0RMDF015L RSCAN0.RMDF015.UINT16[L]
#define RSCAN0RMDF015LL RSCAN0.RMDF015.UINT8[LL]
#define RSCAN0RMDF015LH RSCAN0.RMDF015.UINT8[LH]
#define RSCAN0RMDF015H RSCAN0.RMDF015.UINT16[H]
#define RSCAN0RMDF015HL RSCAN0.RMDF015.UINT8[HL]
#define RSCAN0RMDF015HH RSCAN0.RMDF015.UINT8[HH]
#define RSCAN0RMDF115 RSCAN0.RMDF115.UINT32
#define RSCAN0RMDF115L RSCAN0.RMDF115.UINT16[L]
#define RSCAN0RMDF115LL RSCAN0.RMDF115.UINT8[LL]
#define RSCAN0RMDF115LH RSCAN0.RMDF115.UINT8[LH]
#define RSCAN0RMDF115H RSCAN0.RMDF115.UINT16[H]
#define RSCAN0RMDF115HL RSCAN0.RMDF115.UINT8[HL]
#define RSCAN0RMDF115HH RSCAN0.RMDF115.UINT8[HH]
#define RSCAN0RMID16 RSCAN0.RMID16.UINT32
#define RSCAN0RMID16L RSCAN0.RMID16.UINT16[L]
#define RSCAN0RMID16LL RSCAN0.RMID16.UINT8[LL]
#define RSCAN0RMID16LH RSCAN0.RMID16.UINT8[LH]
#define RSCAN0RMID16H RSCAN0.RMID16.UINT16[H]
#define RSCAN0RMID16HL RSCAN0.RMID16.UINT8[HL]
#define RSCAN0RMID16HH RSCAN0.RMID16.UINT8[HH]
#define RSCAN0RMPTR16 RSCAN0.RMPTR16.UINT32
#define RSCAN0RMPTR16L RSCAN0.RMPTR16.UINT16[L]
#define RSCAN0RMPTR16LL RSCAN0.RMPTR16.UINT8[LL]
#define RSCAN0RMPTR16LH RSCAN0.RMPTR16.UINT8[LH]
#define RSCAN0RMPTR16H RSCAN0.RMPTR16.UINT16[H]
#define RSCAN0RMPTR16HL RSCAN0.RMPTR16.UINT8[HL]
#define RSCAN0RMPTR16HH RSCAN0.RMPTR16.UINT8[HH]
#define RSCAN0RMDF016 RSCAN0.RMDF016.UINT32
#define RSCAN0RMDF016L RSCAN0.RMDF016.UINT16[L]
#define RSCAN0RMDF016LL RSCAN0.RMDF016.UINT8[LL]
#define RSCAN0RMDF016LH RSCAN0.RMDF016.UINT8[LH]
#define RSCAN0RMDF016H RSCAN0.RMDF016.UINT16[H]
#define RSCAN0RMDF016HL RSCAN0.RMDF016.UINT8[HL]
#define RSCAN0RMDF016HH RSCAN0.RMDF016.UINT8[HH]
#define RSCAN0RMDF116 RSCAN0.RMDF116.UINT32
#define RSCAN0RMDF116L RSCAN0.RMDF116.UINT16[L]
#define RSCAN0RMDF116LL RSCAN0.RMDF116.UINT8[LL]
#define RSCAN0RMDF116LH RSCAN0.RMDF116.UINT8[LH]
#define RSCAN0RMDF116H RSCAN0.RMDF116.UINT16[H]
#define RSCAN0RMDF116HL RSCAN0.RMDF116.UINT8[HL]
#define RSCAN0RMDF116HH RSCAN0.RMDF116.UINT8[HH]
#define RSCAN0RMID17 RSCAN0.RMID17.UINT32
#define RSCAN0RMID17L RSCAN0.RMID17.UINT16[L]
#define RSCAN0RMID17LL RSCAN0.RMID17.UINT8[LL]
#define RSCAN0RMID17LH RSCAN0.RMID17.UINT8[LH]
#define RSCAN0RMID17H RSCAN0.RMID17.UINT16[H]
#define RSCAN0RMID17HL RSCAN0.RMID17.UINT8[HL]
#define RSCAN0RMID17HH RSCAN0.RMID17.UINT8[HH]
#define RSCAN0RMPTR17 RSCAN0.RMPTR17.UINT32
#define RSCAN0RMPTR17L RSCAN0.RMPTR17.UINT16[L]
#define RSCAN0RMPTR17LL RSCAN0.RMPTR17.UINT8[LL]
#define RSCAN0RMPTR17LH RSCAN0.RMPTR17.UINT8[LH]
#define RSCAN0RMPTR17H RSCAN0.RMPTR17.UINT16[H]
#define RSCAN0RMPTR17HL RSCAN0.RMPTR17.UINT8[HL]
#define RSCAN0RMPTR17HH RSCAN0.RMPTR17.UINT8[HH]
#define RSCAN0RMDF017 RSCAN0.RMDF017.UINT32
#define RSCAN0RMDF017L RSCAN0.RMDF017.UINT16[L]
#define RSCAN0RMDF017LL RSCAN0.RMDF017.UINT8[LL]
#define RSCAN0RMDF017LH RSCAN0.RMDF017.UINT8[LH]
#define RSCAN0RMDF017H RSCAN0.RMDF017.UINT16[H]
#define RSCAN0RMDF017HL RSCAN0.RMDF017.UINT8[HL]
#define RSCAN0RMDF017HH RSCAN0.RMDF017.UINT8[HH]
#define RSCAN0RMDF117 RSCAN0.RMDF117.UINT32
#define RSCAN0RMDF117L RSCAN0.RMDF117.UINT16[L]
#define RSCAN0RMDF117LL RSCAN0.RMDF117.UINT8[LL]
#define RSCAN0RMDF117LH RSCAN0.RMDF117.UINT8[LH]
#define RSCAN0RMDF117H RSCAN0.RMDF117.UINT16[H]
#define RSCAN0RMDF117HL RSCAN0.RMDF117.UINT8[HL]
#define RSCAN0RMDF117HH RSCAN0.RMDF117.UINT8[HH]
#define RSCAN0RMID18 RSCAN0.RMID18.UINT32
#define RSCAN0RMID18L RSCAN0.RMID18.UINT16[L]
#define RSCAN0RMID18LL RSCAN0.RMID18.UINT8[LL]
#define RSCAN0RMID18LH RSCAN0.RMID18.UINT8[LH]
#define RSCAN0RMID18H RSCAN0.RMID18.UINT16[H]
#define RSCAN0RMID18HL RSCAN0.RMID18.UINT8[HL]
#define RSCAN0RMID18HH RSCAN0.RMID18.UINT8[HH]
#define RSCAN0RMPTR18 RSCAN0.RMPTR18.UINT32
#define RSCAN0RMPTR18L RSCAN0.RMPTR18.UINT16[L]
#define RSCAN0RMPTR18LL RSCAN0.RMPTR18.UINT8[LL]
#define RSCAN0RMPTR18LH RSCAN0.RMPTR18.UINT8[LH]
#define RSCAN0RMPTR18H RSCAN0.RMPTR18.UINT16[H]
#define RSCAN0RMPTR18HL RSCAN0.RMPTR18.UINT8[HL]
#define RSCAN0RMPTR18HH RSCAN0.RMPTR18.UINT8[HH]
#define RSCAN0RMDF018 RSCAN0.RMDF018.UINT32
#define RSCAN0RMDF018L RSCAN0.RMDF018.UINT16[L]
#define RSCAN0RMDF018LL RSCAN0.RMDF018.UINT8[LL]
#define RSCAN0RMDF018LH RSCAN0.RMDF018.UINT8[LH]
#define RSCAN0RMDF018H RSCAN0.RMDF018.UINT16[H]
#define RSCAN0RMDF018HL RSCAN0.RMDF018.UINT8[HL]
#define RSCAN0RMDF018HH RSCAN0.RMDF018.UINT8[HH]
#define RSCAN0RMDF118 RSCAN0.RMDF118.UINT32
#define RSCAN0RMDF118L RSCAN0.RMDF118.UINT16[L]
#define RSCAN0RMDF118LL RSCAN0.RMDF118.UINT8[LL]
#define RSCAN0RMDF118LH RSCAN0.RMDF118.UINT8[LH]
#define RSCAN0RMDF118H RSCAN0.RMDF118.UINT16[H]
#define RSCAN0RMDF118HL RSCAN0.RMDF118.UINT8[HL]
#define RSCAN0RMDF118HH RSCAN0.RMDF118.UINT8[HH]
#define RSCAN0RMID19 RSCAN0.RMID19.UINT32
#define RSCAN0RMID19L RSCAN0.RMID19.UINT16[L]
#define RSCAN0RMID19LL RSCAN0.RMID19.UINT8[LL]
#define RSCAN0RMID19LH RSCAN0.RMID19.UINT8[LH]
#define RSCAN0RMID19H RSCAN0.RMID19.UINT16[H]
#define RSCAN0RMID19HL RSCAN0.RMID19.UINT8[HL]
#define RSCAN0RMID19HH RSCAN0.RMID19.UINT8[HH]
#define RSCAN0RMPTR19 RSCAN0.RMPTR19.UINT32
#define RSCAN0RMPTR19L RSCAN0.RMPTR19.UINT16[L]
#define RSCAN0RMPTR19LL RSCAN0.RMPTR19.UINT8[LL]
#define RSCAN0RMPTR19LH RSCAN0.RMPTR19.UINT8[LH]
#define RSCAN0RMPTR19H RSCAN0.RMPTR19.UINT16[H]
#define RSCAN0RMPTR19HL RSCAN0.RMPTR19.UINT8[HL]
#define RSCAN0RMPTR19HH RSCAN0.RMPTR19.UINT8[HH]
#define RSCAN0RMDF019 RSCAN0.RMDF019.UINT32
#define RSCAN0RMDF019L RSCAN0.RMDF019.UINT16[L]
#define RSCAN0RMDF019LL RSCAN0.RMDF019.UINT8[LL]
#define RSCAN0RMDF019LH RSCAN0.RMDF019.UINT8[LH]
#define RSCAN0RMDF019H RSCAN0.RMDF019.UINT16[H]
#define RSCAN0RMDF019HL RSCAN0.RMDF019.UINT8[HL]
#define RSCAN0RMDF019HH RSCAN0.RMDF019.UINT8[HH]
#define RSCAN0RMDF119 RSCAN0.RMDF119.UINT32
#define RSCAN0RMDF119L RSCAN0.RMDF119.UINT16[L]
#define RSCAN0RMDF119LL RSCAN0.RMDF119.UINT8[LL]
#define RSCAN0RMDF119LH RSCAN0.RMDF119.UINT8[LH]
#define RSCAN0RMDF119H RSCAN0.RMDF119.UINT16[H]
#define RSCAN0RMDF119HL RSCAN0.RMDF119.UINT8[HL]
#define RSCAN0RMDF119HH RSCAN0.RMDF119.UINT8[HH]
#define RSCAN0RMID20 RSCAN0.RMID20.UINT32
#define RSCAN0RMID20L RSCAN0.RMID20.UINT16[L]
#define RSCAN0RMID20LL RSCAN0.RMID20.UINT8[LL]
#define RSCAN0RMID20LH RSCAN0.RMID20.UINT8[LH]
#define RSCAN0RMID20H RSCAN0.RMID20.UINT16[H]
#define RSCAN0RMID20HL RSCAN0.RMID20.UINT8[HL]
#define RSCAN0RMID20HH RSCAN0.RMID20.UINT8[HH]
#define RSCAN0RMPTR20 RSCAN0.RMPTR20.UINT32
#define RSCAN0RMPTR20L RSCAN0.RMPTR20.UINT16[L]
#define RSCAN0RMPTR20LL RSCAN0.RMPTR20.UINT8[LL]
#define RSCAN0RMPTR20LH RSCAN0.RMPTR20.UINT8[LH]
#define RSCAN0RMPTR20H RSCAN0.RMPTR20.UINT16[H]
#define RSCAN0RMPTR20HL RSCAN0.RMPTR20.UINT8[HL]
#define RSCAN0RMPTR20HH RSCAN0.RMPTR20.UINT8[HH]
#define RSCAN0RMDF020 RSCAN0.RMDF020.UINT32
#define RSCAN0RMDF020L RSCAN0.RMDF020.UINT16[L]
#define RSCAN0RMDF020LL RSCAN0.RMDF020.UINT8[LL]
#define RSCAN0RMDF020LH RSCAN0.RMDF020.UINT8[LH]
#define RSCAN0RMDF020H RSCAN0.RMDF020.UINT16[H]
#define RSCAN0RMDF020HL RSCAN0.RMDF020.UINT8[HL]
#define RSCAN0RMDF020HH RSCAN0.RMDF020.UINT8[HH]
#define RSCAN0RMDF120 RSCAN0.RMDF120.UINT32
#define RSCAN0RMDF120L RSCAN0.RMDF120.UINT16[L]
#define RSCAN0RMDF120LL RSCAN0.RMDF120.UINT8[LL]
#define RSCAN0RMDF120LH RSCAN0.RMDF120.UINT8[LH]
#define RSCAN0RMDF120H RSCAN0.RMDF120.UINT16[H]
#define RSCAN0RMDF120HL RSCAN0.RMDF120.UINT8[HL]
#define RSCAN0RMDF120HH RSCAN0.RMDF120.UINT8[HH]
#define RSCAN0RMID21 RSCAN0.RMID21.UINT32
#define RSCAN0RMID21L RSCAN0.RMID21.UINT16[L]
#define RSCAN0RMID21LL RSCAN0.RMID21.UINT8[LL]
#define RSCAN0RMID21LH RSCAN0.RMID21.UINT8[LH]
#define RSCAN0RMID21H RSCAN0.RMID21.UINT16[H]
#define RSCAN0RMID21HL RSCAN0.RMID21.UINT8[HL]
#define RSCAN0RMID21HH RSCAN0.RMID21.UINT8[HH]
#define RSCAN0RMPTR21 RSCAN0.RMPTR21.UINT32
#define RSCAN0RMPTR21L RSCAN0.RMPTR21.UINT16[L]
#define RSCAN0RMPTR21LL RSCAN0.RMPTR21.UINT8[LL]
#define RSCAN0RMPTR21LH RSCAN0.RMPTR21.UINT8[LH]
#define RSCAN0RMPTR21H RSCAN0.RMPTR21.UINT16[H]
#define RSCAN0RMPTR21HL RSCAN0.RMPTR21.UINT8[HL]
#define RSCAN0RMPTR21HH RSCAN0.RMPTR21.UINT8[HH]
#define RSCAN0RMDF021 RSCAN0.RMDF021.UINT32
#define RSCAN0RMDF021L RSCAN0.RMDF021.UINT16[L]
#define RSCAN0RMDF021LL RSCAN0.RMDF021.UINT8[LL]
#define RSCAN0RMDF021LH RSCAN0.RMDF021.UINT8[LH]
#define RSCAN0RMDF021H RSCAN0.RMDF021.UINT16[H]
#define RSCAN0RMDF021HL RSCAN0.RMDF021.UINT8[HL]
#define RSCAN0RMDF021HH RSCAN0.RMDF021.UINT8[HH]
#define RSCAN0RMDF121 RSCAN0.RMDF121.UINT32
#define RSCAN0RMDF121L RSCAN0.RMDF121.UINT16[L]
#define RSCAN0RMDF121LL RSCAN0.RMDF121.UINT8[LL]
#define RSCAN0RMDF121LH RSCAN0.RMDF121.UINT8[LH]
#define RSCAN0RMDF121H RSCAN0.RMDF121.UINT16[H]
#define RSCAN0RMDF121HL RSCAN0.RMDF121.UINT8[HL]
#define RSCAN0RMDF121HH RSCAN0.RMDF121.UINT8[HH]
#define RSCAN0RMID22 RSCAN0.RMID22.UINT32
#define RSCAN0RMID22L RSCAN0.RMID22.UINT16[L]
#define RSCAN0RMID22LL RSCAN0.RMID22.UINT8[LL]
#define RSCAN0RMID22LH RSCAN0.RMID22.UINT8[LH]
#define RSCAN0RMID22H RSCAN0.RMID22.UINT16[H]
#define RSCAN0RMID22HL RSCAN0.RMID22.UINT8[HL]
#define RSCAN0RMID22HH RSCAN0.RMID22.UINT8[HH]
#define RSCAN0RMPTR22 RSCAN0.RMPTR22.UINT32
#define RSCAN0RMPTR22L RSCAN0.RMPTR22.UINT16[L]
#define RSCAN0RMPTR22LL RSCAN0.RMPTR22.UINT8[LL]
#define RSCAN0RMPTR22LH RSCAN0.RMPTR22.UINT8[LH]
#define RSCAN0RMPTR22H RSCAN0.RMPTR22.UINT16[H]
#define RSCAN0RMPTR22HL RSCAN0.RMPTR22.UINT8[HL]
#define RSCAN0RMPTR22HH RSCAN0.RMPTR22.UINT8[HH]
#define RSCAN0RMDF022 RSCAN0.RMDF022.UINT32
#define RSCAN0RMDF022L RSCAN0.RMDF022.UINT16[L]
#define RSCAN0RMDF022LL RSCAN0.RMDF022.UINT8[LL]
#define RSCAN0RMDF022LH RSCAN0.RMDF022.UINT8[LH]
#define RSCAN0RMDF022H RSCAN0.RMDF022.UINT16[H]
#define RSCAN0RMDF022HL RSCAN0.RMDF022.UINT8[HL]
#define RSCAN0RMDF022HH RSCAN0.RMDF022.UINT8[HH]
#define RSCAN0RMDF122 RSCAN0.RMDF122.UINT32
#define RSCAN0RMDF122L RSCAN0.RMDF122.UINT16[L]
#define RSCAN0RMDF122LL RSCAN0.RMDF122.UINT8[LL]
#define RSCAN0RMDF122LH RSCAN0.RMDF122.UINT8[LH]
#define RSCAN0RMDF122H RSCAN0.RMDF122.UINT16[H]
#define RSCAN0RMDF122HL RSCAN0.RMDF122.UINT8[HL]
#define RSCAN0RMDF122HH RSCAN0.RMDF122.UINT8[HH]
#define RSCAN0RMID23 RSCAN0.RMID23.UINT32
#define RSCAN0RMID23L RSCAN0.RMID23.UINT16[L]
#define RSCAN0RMID23LL RSCAN0.RMID23.UINT8[LL]
#define RSCAN0RMID23LH RSCAN0.RMID23.UINT8[LH]
#define RSCAN0RMID23H RSCAN0.RMID23.UINT16[H]
#define RSCAN0RMID23HL RSCAN0.RMID23.UINT8[HL]
#define RSCAN0RMID23HH RSCAN0.RMID23.UINT8[HH]
#define RSCAN0RMPTR23 RSCAN0.RMPTR23.UINT32
#define RSCAN0RMPTR23L RSCAN0.RMPTR23.UINT16[L]
#define RSCAN0RMPTR23LL RSCAN0.RMPTR23.UINT8[LL]
#define RSCAN0RMPTR23LH RSCAN0.RMPTR23.UINT8[LH]
#define RSCAN0RMPTR23H RSCAN0.RMPTR23.UINT16[H]
#define RSCAN0RMPTR23HL RSCAN0.RMPTR23.UINT8[HL]
#define RSCAN0RMPTR23HH RSCAN0.RMPTR23.UINT8[HH]
#define RSCAN0RMDF023 RSCAN0.RMDF023.UINT32
#define RSCAN0RMDF023L RSCAN0.RMDF023.UINT16[L]
#define RSCAN0RMDF023LL RSCAN0.RMDF023.UINT8[LL]
#define RSCAN0RMDF023LH RSCAN0.RMDF023.UINT8[LH]
#define RSCAN0RMDF023H RSCAN0.RMDF023.UINT16[H]
#define RSCAN0RMDF023HL RSCAN0.RMDF023.UINT8[HL]
#define RSCAN0RMDF023HH RSCAN0.RMDF023.UINT8[HH]
#define RSCAN0RMDF123 RSCAN0.RMDF123.UINT32
#define RSCAN0RMDF123L RSCAN0.RMDF123.UINT16[L]
#define RSCAN0RMDF123LL RSCAN0.RMDF123.UINT8[LL]
#define RSCAN0RMDF123LH RSCAN0.RMDF123.UINT8[LH]
#define RSCAN0RMDF123H RSCAN0.RMDF123.UINT16[H]
#define RSCAN0RMDF123HL RSCAN0.RMDF123.UINT8[HL]
#define RSCAN0RMDF123HH RSCAN0.RMDF123.UINT8[HH]
#define RSCAN0RMID24 RSCAN0.RMID24.UINT32
#define RSCAN0RMID24L RSCAN0.RMID24.UINT16[L]
#define RSCAN0RMID24LL RSCAN0.RMID24.UINT8[LL]
#define RSCAN0RMID24LH RSCAN0.RMID24.UINT8[LH]
#define RSCAN0RMID24H RSCAN0.RMID24.UINT16[H]
#define RSCAN0RMID24HL RSCAN0.RMID24.UINT8[HL]
#define RSCAN0RMID24HH RSCAN0.RMID24.UINT8[HH]
#define RSCAN0RMPTR24 RSCAN0.RMPTR24.UINT32
#define RSCAN0RMPTR24L RSCAN0.RMPTR24.UINT16[L]
#define RSCAN0RMPTR24LL RSCAN0.RMPTR24.UINT8[LL]
#define RSCAN0RMPTR24LH RSCAN0.RMPTR24.UINT8[LH]
#define RSCAN0RMPTR24H RSCAN0.RMPTR24.UINT16[H]
#define RSCAN0RMPTR24HL RSCAN0.RMPTR24.UINT8[HL]
#define RSCAN0RMPTR24HH RSCAN0.RMPTR24.UINT8[HH]
#define RSCAN0RMDF024 RSCAN0.RMDF024.UINT32
#define RSCAN0RMDF024L RSCAN0.RMDF024.UINT16[L]
#define RSCAN0RMDF024LL RSCAN0.RMDF024.UINT8[LL]
#define RSCAN0RMDF024LH RSCAN0.RMDF024.UINT8[LH]
#define RSCAN0RMDF024H RSCAN0.RMDF024.UINT16[H]
#define RSCAN0RMDF024HL RSCAN0.RMDF024.UINT8[HL]
#define RSCAN0RMDF024HH RSCAN0.RMDF024.UINT8[HH]
#define RSCAN0RMDF124 RSCAN0.RMDF124.UINT32
#define RSCAN0RMDF124L RSCAN0.RMDF124.UINT16[L]
#define RSCAN0RMDF124LL RSCAN0.RMDF124.UINT8[LL]
#define RSCAN0RMDF124LH RSCAN0.RMDF124.UINT8[LH]
#define RSCAN0RMDF124H RSCAN0.RMDF124.UINT16[H]
#define RSCAN0RMDF124HL RSCAN0.RMDF124.UINT8[HL]
#define RSCAN0RMDF124HH RSCAN0.RMDF124.UINT8[HH]
#define RSCAN0RMID25 RSCAN0.RMID25.UINT32
#define RSCAN0RMID25L RSCAN0.RMID25.UINT16[L]
#define RSCAN0RMID25LL RSCAN0.RMID25.UINT8[LL]
#define RSCAN0RMID25LH RSCAN0.RMID25.UINT8[LH]
#define RSCAN0RMID25H RSCAN0.RMID25.UINT16[H]
#define RSCAN0RMID25HL RSCAN0.RMID25.UINT8[HL]
#define RSCAN0RMID25HH RSCAN0.RMID25.UINT8[HH]
#define RSCAN0RMPTR25 RSCAN0.RMPTR25.UINT32
#define RSCAN0RMPTR25L RSCAN0.RMPTR25.UINT16[L]
#define RSCAN0RMPTR25LL RSCAN0.RMPTR25.UINT8[LL]
#define RSCAN0RMPTR25LH RSCAN0.RMPTR25.UINT8[LH]
#define RSCAN0RMPTR25H RSCAN0.RMPTR25.UINT16[H]
#define RSCAN0RMPTR25HL RSCAN0.RMPTR25.UINT8[HL]
#define RSCAN0RMPTR25HH RSCAN0.RMPTR25.UINT8[HH]
#define RSCAN0RMDF025 RSCAN0.RMDF025.UINT32
#define RSCAN0RMDF025L RSCAN0.RMDF025.UINT16[L]
#define RSCAN0RMDF025LL RSCAN0.RMDF025.UINT8[LL]
#define RSCAN0RMDF025LH RSCAN0.RMDF025.UINT8[LH]
#define RSCAN0RMDF025H RSCAN0.RMDF025.UINT16[H]
#define RSCAN0RMDF025HL RSCAN0.RMDF025.UINT8[HL]
#define RSCAN0RMDF025HH RSCAN0.RMDF025.UINT8[HH]
#define RSCAN0RMDF125 RSCAN0.RMDF125.UINT32
#define RSCAN0RMDF125L RSCAN0.RMDF125.UINT16[L]
#define RSCAN0RMDF125LL RSCAN0.RMDF125.UINT8[LL]
#define RSCAN0RMDF125LH RSCAN0.RMDF125.UINT8[LH]
#define RSCAN0RMDF125H RSCAN0.RMDF125.UINT16[H]
#define RSCAN0RMDF125HL RSCAN0.RMDF125.UINT8[HL]
#define RSCAN0RMDF125HH RSCAN0.RMDF125.UINT8[HH]
#define RSCAN0RMID26 RSCAN0.RMID26.UINT32
#define RSCAN0RMID26L RSCAN0.RMID26.UINT16[L]
#define RSCAN0RMID26LL RSCAN0.RMID26.UINT8[LL]
#define RSCAN0RMID26LH RSCAN0.RMID26.UINT8[LH]
#define RSCAN0RMID26H RSCAN0.RMID26.UINT16[H]
#define RSCAN0RMID26HL RSCAN0.RMID26.UINT8[HL]
#define RSCAN0RMID26HH RSCAN0.RMID26.UINT8[HH]
#define RSCAN0RMPTR26 RSCAN0.RMPTR26.UINT32
#define RSCAN0RMPTR26L RSCAN0.RMPTR26.UINT16[L]
#define RSCAN0RMPTR26LL RSCAN0.RMPTR26.UINT8[LL]
#define RSCAN0RMPTR26LH RSCAN0.RMPTR26.UINT8[LH]
#define RSCAN0RMPTR26H RSCAN0.RMPTR26.UINT16[H]
#define RSCAN0RMPTR26HL RSCAN0.RMPTR26.UINT8[HL]
#define RSCAN0RMPTR26HH RSCAN0.RMPTR26.UINT8[HH]
#define RSCAN0RMDF026 RSCAN0.RMDF026.UINT32
#define RSCAN0RMDF026L RSCAN0.RMDF026.UINT16[L]
#define RSCAN0RMDF026LL RSCAN0.RMDF026.UINT8[LL]
#define RSCAN0RMDF026LH RSCAN0.RMDF026.UINT8[LH]
#define RSCAN0RMDF026H RSCAN0.RMDF026.UINT16[H]
#define RSCAN0RMDF026HL RSCAN0.RMDF026.UINT8[HL]
#define RSCAN0RMDF026HH RSCAN0.RMDF026.UINT8[HH]
#define RSCAN0RMDF126 RSCAN0.RMDF126.UINT32
#define RSCAN0RMDF126L RSCAN0.RMDF126.UINT16[L]
#define RSCAN0RMDF126LL RSCAN0.RMDF126.UINT8[LL]
#define RSCAN0RMDF126LH RSCAN0.RMDF126.UINT8[LH]
#define RSCAN0RMDF126H RSCAN0.RMDF126.UINT16[H]
#define RSCAN0RMDF126HL RSCAN0.RMDF126.UINT8[HL]
#define RSCAN0RMDF126HH RSCAN0.RMDF126.UINT8[HH]
#define RSCAN0RMID27 RSCAN0.RMID27.UINT32
#define RSCAN0RMID27L RSCAN0.RMID27.UINT16[L]
#define RSCAN0RMID27LL RSCAN0.RMID27.UINT8[LL]
#define RSCAN0RMID27LH RSCAN0.RMID27.UINT8[LH]
#define RSCAN0RMID27H RSCAN0.RMID27.UINT16[H]
#define RSCAN0RMID27HL RSCAN0.RMID27.UINT8[HL]
#define RSCAN0RMID27HH RSCAN0.RMID27.UINT8[HH]
#define RSCAN0RMPTR27 RSCAN0.RMPTR27.UINT32
#define RSCAN0RMPTR27L RSCAN0.RMPTR27.UINT16[L]
#define RSCAN0RMPTR27LL RSCAN0.RMPTR27.UINT8[LL]
#define RSCAN0RMPTR27LH RSCAN0.RMPTR27.UINT8[LH]
#define RSCAN0RMPTR27H RSCAN0.RMPTR27.UINT16[H]
#define RSCAN0RMPTR27HL RSCAN0.RMPTR27.UINT8[HL]
#define RSCAN0RMPTR27HH RSCAN0.RMPTR27.UINT8[HH]
#define RSCAN0RMDF027 RSCAN0.RMDF027.UINT32
#define RSCAN0RMDF027L RSCAN0.RMDF027.UINT16[L]
#define RSCAN0RMDF027LL RSCAN0.RMDF027.UINT8[LL]
#define RSCAN0RMDF027LH RSCAN0.RMDF027.UINT8[LH]
#define RSCAN0RMDF027H RSCAN0.RMDF027.UINT16[H]
#define RSCAN0RMDF027HL RSCAN0.RMDF027.UINT8[HL]
#define RSCAN0RMDF027HH RSCAN0.RMDF027.UINT8[HH]
#define RSCAN0RMDF127 RSCAN0.RMDF127.UINT32
#define RSCAN0RMDF127L RSCAN0.RMDF127.UINT16[L]
#define RSCAN0RMDF127LL RSCAN0.RMDF127.UINT8[LL]
#define RSCAN0RMDF127LH RSCAN0.RMDF127.UINT8[LH]
#define RSCAN0RMDF127H RSCAN0.RMDF127.UINT16[H]
#define RSCAN0RMDF127HL RSCAN0.RMDF127.UINT8[HL]
#define RSCAN0RMDF127HH RSCAN0.RMDF127.UINT8[HH]
#define RSCAN0RMID28 RSCAN0.RMID28.UINT32
#define RSCAN0RMID28L RSCAN0.RMID28.UINT16[L]
#define RSCAN0RMID28LL RSCAN0.RMID28.UINT8[LL]
#define RSCAN0RMID28LH RSCAN0.RMID28.UINT8[LH]
#define RSCAN0RMID28H RSCAN0.RMID28.UINT16[H]
#define RSCAN0RMID28HL RSCAN0.RMID28.UINT8[HL]
#define RSCAN0RMID28HH RSCAN0.RMID28.UINT8[HH]
#define RSCAN0RMPTR28 RSCAN0.RMPTR28.UINT32
#define RSCAN0RMPTR28L RSCAN0.RMPTR28.UINT16[L]
#define RSCAN0RMPTR28LL RSCAN0.RMPTR28.UINT8[LL]
#define RSCAN0RMPTR28LH RSCAN0.RMPTR28.UINT8[LH]
#define RSCAN0RMPTR28H RSCAN0.RMPTR28.UINT16[H]
#define RSCAN0RMPTR28HL RSCAN0.RMPTR28.UINT8[HL]
#define RSCAN0RMPTR28HH RSCAN0.RMPTR28.UINT8[HH]
#define RSCAN0RMDF028 RSCAN0.RMDF028.UINT32
#define RSCAN0RMDF028L RSCAN0.RMDF028.UINT16[L]
#define RSCAN0RMDF028LL RSCAN0.RMDF028.UINT8[LL]
#define RSCAN0RMDF028LH RSCAN0.RMDF028.UINT8[LH]
#define RSCAN0RMDF028H RSCAN0.RMDF028.UINT16[H]
#define RSCAN0RMDF028HL RSCAN0.RMDF028.UINT8[HL]
#define RSCAN0RMDF028HH RSCAN0.RMDF028.UINT8[HH]
#define RSCAN0RMDF128 RSCAN0.RMDF128.UINT32
#define RSCAN0RMDF128L RSCAN0.RMDF128.UINT16[L]
#define RSCAN0RMDF128LL RSCAN0.RMDF128.UINT8[LL]
#define RSCAN0RMDF128LH RSCAN0.RMDF128.UINT8[LH]
#define RSCAN0RMDF128H RSCAN0.RMDF128.UINT16[H]
#define RSCAN0RMDF128HL RSCAN0.RMDF128.UINT8[HL]
#define RSCAN0RMDF128HH RSCAN0.RMDF128.UINT8[HH]
#define RSCAN0RMID29 RSCAN0.RMID29.UINT32
#define RSCAN0RMID29L RSCAN0.RMID29.UINT16[L]
#define RSCAN0RMID29LL RSCAN0.RMID29.UINT8[LL]
#define RSCAN0RMID29LH RSCAN0.RMID29.UINT8[LH]
#define RSCAN0RMID29H RSCAN0.RMID29.UINT16[H]
#define RSCAN0RMID29HL RSCAN0.RMID29.UINT8[HL]
#define RSCAN0RMID29HH RSCAN0.RMID29.UINT8[HH]
#define RSCAN0RMPTR29 RSCAN0.RMPTR29.UINT32
#define RSCAN0RMPTR29L RSCAN0.RMPTR29.UINT16[L]
#define RSCAN0RMPTR29LL RSCAN0.RMPTR29.UINT8[LL]
#define RSCAN0RMPTR29LH RSCAN0.RMPTR29.UINT8[LH]
#define RSCAN0RMPTR29H RSCAN0.RMPTR29.UINT16[H]
#define RSCAN0RMPTR29HL RSCAN0.RMPTR29.UINT8[HL]
#define RSCAN0RMPTR29HH RSCAN0.RMPTR29.UINT8[HH]
#define RSCAN0RMDF029 RSCAN0.RMDF029.UINT32
#define RSCAN0RMDF029L RSCAN0.RMDF029.UINT16[L]
#define RSCAN0RMDF029LL RSCAN0.RMDF029.UINT8[LL]
#define RSCAN0RMDF029LH RSCAN0.RMDF029.UINT8[LH]
#define RSCAN0RMDF029H RSCAN0.RMDF029.UINT16[H]
#define RSCAN0RMDF029HL RSCAN0.RMDF029.UINT8[HL]
#define RSCAN0RMDF029HH RSCAN0.RMDF029.UINT8[HH]
#define RSCAN0RMDF129 RSCAN0.RMDF129.UINT32
#define RSCAN0RMDF129L RSCAN0.RMDF129.UINT16[L]
#define RSCAN0RMDF129LL RSCAN0.RMDF129.UINT8[LL]
#define RSCAN0RMDF129LH RSCAN0.RMDF129.UINT8[LH]
#define RSCAN0RMDF129H RSCAN0.RMDF129.UINT16[H]
#define RSCAN0RMDF129HL RSCAN0.RMDF129.UINT8[HL]
#define RSCAN0RMDF129HH RSCAN0.RMDF129.UINT8[HH]
#define RSCAN0RMID30 RSCAN0.RMID30.UINT32
#define RSCAN0RMID30L RSCAN0.RMID30.UINT16[L]
#define RSCAN0RMID30LL RSCAN0.RMID30.UINT8[LL]
#define RSCAN0RMID30LH RSCAN0.RMID30.UINT8[LH]
#define RSCAN0RMID30H RSCAN0.RMID30.UINT16[H]
#define RSCAN0RMID30HL RSCAN0.RMID30.UINT8[HL]
#define RSCAN0RMID30HH RSCAN0.RMID30.UINT8[HH]
#define RSCAN0RMPTR30 RSCAN0.RMPTR30.UINT32
#define RSCAN0RMPTR30L RSCAN0.RMPTR30.UINT16[L]
#define RSCAN0RMPTR30LL RSCAN0.RMPTR30.UINT8[LL]
#define RSCAN0RMPTR30LH RSCAN0.RMPTR30.UINT8[LH]
#define RSCAN0RMPTR30H RSCAN0.RMPTR30.UINT16[H]
#define RSCAN0RMPTR30HL RSCAN0.RMPTR30.UINT8[HL]
#define RSCAN0RMPTR30HH RSCAN0.RMPTR30.UINT8[HH]
#define RSCAN0RMDF030 RSCAN0.RMDF030.UINT32
#define RSCAN0RMDF030L RSCAN0.RMDF030.UINT16[L]
#define RSCAN0RMDF030LL RSCAN0.RMDF030.UINT8[LL]
#define RSCAN0RMDF030LH RSCAN0.RMDF030.UINT8[LH]
#define RSCAN0RMDF030H RSCAN0.RMDF030.UINT16[H]
#define RSCAN0RMDF030HL RSCAN0.RMDF030.UINT8[HL]
#define RSCAN0RMDF030HH RSCAN0.RMDF030.UINT8[HH]
#define RSCAN0RMDF130 RSCAN0.RMDF130.UINT32
#define RSCAN0RMDF130L RSCAN0.RMDF130.UINT16[L]
#define RSCAN0RMDF130LL RSCAN0.RMDF130.UINT8[LL]
#define RSCAN0RMDF130LH RSCAN0.RMDF130.UINT8[LH]
#define RSCAN0RMDF130H RSCAN0.RMDF130.UINT16[H]
#define RSCAN0RMDF130HL RSCAN0.RMDF130.UINT8[HL]
#define RSCAN0RMDF130HH RSCAN0.RMDF130.UINT8[HH]
#define RSCAN0RMID31 RSCAN0.RMID31.UINT32
#define RSCAN0RMID31L RSCAN0.RMID31.UINT16[L]
#define RSCAN0RMID31LL RSCAN0.RMID31.UINT8[LL]
#define RSCAN0RMID31LH RSCAN0.RMID31.UINT8[LH]
#define RSCAN0RMID31H RSCAN0.RMID31.UINT16[H]
#define RSCAN0RMID31HL RSCAN0.RMID31.UINT8[HL]
#define RSCAN0RMID31HH RSCAN0.RMID31.UINT8[HH]
#define RSCAN0RMPTR31 RSCAN0.RMPTR31.UINT32
#define RSCAN0RMPTR31L RSCAN0.RMPTR31.UINT16[L]
#define RSCAN0RMPTR31LL RSCAN0.RMPTR31.UINT8[LL]
#define RSCAN0RMPTR31LH RSCAN0.RMPTR31.UINT8[LH]
#define RSCAN0RMPTR31H RSCAN0.RMPTR31.UINT16[H]
#define RSCAN0RMPTR31HL RSCAN0.RMPTR31.UINT8[HL]
#define RSCAN0RMPTR31HH RSCAN0.RMPTR31.UINT8[HH]
#define RSCAN0RMDF031 RSCAN0.RMDF031.UINT32
#define RSCAN0RMDF031L RSCAN0.RMDF031.UINT16[L]
#define RSCAN0RMDF031LL RSCAN0.RMDF031.UINT8[LL]
#define RSCAN0RMDF031LH RSCAN0.RMDF031.UINT8[LH]
#define RSCAN0RMDF031H RSCAN0.RMDF031.UINT16[H]
#define RSCAN0RMDF031HL RSCAN0.RMDF031.UINT8[HL]
#define RSCAN0RMDF031HH RSCAN0.RMDF031.UINT8[HH]
#define RSCAN0RMDF131 RSCAN0.RMDF131.UINT32
#define RSCAN0RMDF131L RSCAN0.RMDF131.UINT16[L]
#define RSCAN0RMDF131LL RSCAN0.RMDF131.UINT8[LL]
#define RSCAN0RMDF131LH RSCAN0.RMDF131.UINT8[LH]
#define RSCAN0RMDF131H RSCAN0.RMDF131.UINT16[H]
#define RSCAN0RMDF131HL RSCAN0.RMDF131.UINT8[HL]
#define RSCAN0RMDF131HH RSCAN0.RMDF131.UINT8[HH]
#define RSCAN0RMID32 RSCAN0.RMID32.UINT32
#define RSCAN0RMID32L RSCAN0.RMID32.UINT16[L]
#define RSCAN0RMID32LL RSCAN0.RMID32.UINT8[LL]
#define RSCAN0RMID32LH RSCAN0.RMID32.UINT8[LH]
#define RSCAN0RMID32H RSCAN0.RMID32.UINT16[H]
#define RSCAN0RMID32HL RSCAN0.RMID32.UINT8[HL]
#define RSCAN0RMID32HH RSCAN0.RMID32.UINT8[HH]
#define RSCAN0RMPTR32 RSCAN0.RMPTR32.UINT32
#define RSCAN0RMPTR32L RSCAN0.RMPTR32.UINT16[L]
#define RSCAN0RMPTR32LL RSCAN0.RMPTR32.UINT8[LL]
#define RSCAN0RMPTR32LH RSCAN0.RMPTR32.UINT8[LH]
#define RSCAN0RMPTR32H RSCAN0.RMPTR32.UINT16[H]
#define RSCAN0RMPTR32HL RSCAN0.RMPTR32.UINT8[HL]
#define RSCAN0RMPTR32HH RSCAN0.RMPTR32.UINT8[HH]
#define RSCAN0RMDF032 RSCAN0.RMDF032.UINT32
#define RSCAN0RMDF032L RSCAN0.RMDF032.UINT16[L]
#define RSCAN0RMDF032LL RSCAN0.RMDF032.UINT8[LL]
#define RSCAN0RMDF032LH RSCAN0.RMDF032.UINT8[LH]
#define RSCAN0RMDF032H RSCAN0.RMDF032.UINT16[H]
#define RSCAN0RMDF032HL RSCAN0.RMDF032.UINT8[HL]
#define RSCAN0RMDF032HH RSCAN0.RMDF032.UINT8[HH]
#define RSCAN0RMDF132 RSCAN0.RMDF132.UINT32
#define RSCAN0RMDF132L RSCAN0.RMDF132.UINT16[L]
#define RSCAN0RMDF132LL RSCAN0.RMDF132.UINT8[LL]
#define RSCAN0RMDF132LH RSCAN0.RMDF132.UINT8[LH]
#define RSCAN0RMDF132H RSCAN0.RMDF132.UINT16[H]
#define RSCAN0RMDF132HL RSCAN0.RMDF132.UINT8[HL]
#define RSCAN0RMDF132HH RSCAN0.RMDF132.UINT8[HH]
#define RSCAN0RMID33 RSCAN0.RMID33.UINT32
#define RSCAN0RMID33L RSCAN0.RMID33.UINT16[L]
#define RSCAN0RMID33LL RSCAN0.RMID33.UINT8[LL]
#define RSCAN0RMID33LH RSCAN0.RMID33.UINT8[LH]
#define RSCAN0RMID33H RSCAN0.RMID33.UINT16[H]
#define RSCAN0RMID33HL RSCAN0.RMID33.UINT8[HL]
#define RSCAN0RMID33HH RSCAN0.RMID33.UINT8[HH]
#define RSCAN0RMPTR33 RSCAN0.RMPTR33.UINT32
#define RSCAN0RMPTR33L RSCAN0.RMPTR33.UINT16[L]
#define RSCAN0RMPTR33LL RSCAN0.RMPTR33.UINT8[LL]
#define RSCAN0RMPTR33LH RSCAN0.RMPTR33.UINT8[LH]
#define RSCAN0RMPTR33H RSCAN0.RMPTR33.UINT16[H]
#define RSCAN0RMPTR33HL RSCAN0.RMPTR33.UINT8[HL]
#define RSCAN0RMPTR33HH RSCAN0.RMPTR33.UINT8[HH]
#define RSCAN0RMDF033 RSCAN0.RMDF033.UINT32
#define RSCAN0RMDF033L RSCAN0.RMDF033.UINT16[L]
#define RSCAN0RMDF033LL RSCAN0.RMDF033.UINT8[LL]
#define RSCAN0RMDF033LH RSCAN0.RMDF033.UINT8[LH]
#define RSCAN0RMDF033H RSCAN0.RMDF033.UINT16[H]
#define RSCAN0RMDF033HL RSCAN0.RMDF033.UINT8[HL]
#define RSCAN0RMDF033HH RSCAN0.RMDF033.UINT8[HH]
#define RSCAN0RMDF133 RSCAN0.RMDF133.UINT32
#define RSCAN0RMDF133L RSCAN0.RMDF133.UINT16[L]
#define RSCAN0RMDF133LL RSCAN0.RMDF133.UINT8[LL]
#define RSCAN0RMDF133LH RSCAN0.RMDF133.UINT8[LH]
#define RSCAN0RMDF133H RSCAN0.RMDF133.UINT16[H]
#define RSCAN0RMDF133HL RSCAN0.RMDF133.UINT8[HL]
#define RSCAN0RMDF133HH RSCAN0.RMDF133.UINT8[HH]
#define RSCAN0RMID34 RSCAN0.RMID34.UINT32
#define RSCAN0RMID34L RSCAN0.RMID34.UINT16[L]
#define RSCAN0RMID34LL RSCAN0.RMID34.UINT8[LL]
#define RSCAN0RMID34LH RSCAN0.RMID34.UINT8[LH]
#define RSCAN0RMID34H RSCAN0.RMID34.UINT16[H]
#define RSCAN0RMID34HL RSCAN0.RMID34.UINT8[HL]
#define RSCAN0RMID34HH RSCAN0.RMID34.UINT8[HH]
#define RSCAN0RMPTR34 RSCAN0.RMPTR34.UINT32
#define RSCAN0RMPTR34L RSCAN0.RMPTR34.UINT16[L]
#define RSCAN0RMPTR34LL RSCAN0.RMPTR34.UINT8[LL]
#define RSCAN0RMPTR34LH RSCAN0.RMPTR34.UINT8[LH]
#define RSCAN0RMPTR34H RSCAN0.RMPTR34.UINT16[H]
#define RSCAN0RMPTR34HL RSCAN0.RMPTR34.UINT8[HL]
#define RSCAN0RMPTR34HH RSCAN0.RMPTR34.UINT8[HH]
#define RSCAN0RMDF034 RSCAN0.RMDF034.UINT32
#define RSCAN0RMDF034L RSCAN0.RMDF034.UINT16[L]
#define RSCAN0RMDF034LL RSCAN0.RMDF034.UINT8[LL]
#define RSCAN0RMDF034LH RSCAN0.RMDF034.UINT8[LH]
#define RSCAN0RMDF034H RSCAN0.RMDF034.UINT16[H]
#define RSCAN0RMDF034HL RSCAN0.RMDF034.UINT8[HL]
#define RSCAN0RMDF034HH RSCAN0.RMDF034.UINT8[HH]
#define RSCAN0RMDF134 RSCAN0.RMDF134.UINT32
#define RSCAN0RMDF134L RSCAN0.RMDF134.UINT16[L]
#define RSCAN0RMDF134LL RSCAN0.RMDF134.UINT8[LL]
#define RSCAN0RMDF134LH RSCAN0.RMDF134.UINT8[LH]
#define RSCAN0RMDF134H RSCAN0.RMDF134.UINT16[H]
#define RSCAN0RMDF134HL RSCAN0.RMDF134.UINT8[HL]
#define RSCAN0RMDF134HH RSCAN0.RMDF134.UINT8[HH]
#define RSCAN0RMID35 RSCAN0.RMID35.UINT32
#define RSCAN0RMID35L RSCAN0.RMID35.UINT16[L]
#define RSCAN0RMID35LL RSCAN0.RMID35.UINT8[LL]
#define RSCAN0RMID35LH RSCAN0.RMID35.UINT8[LH]
#define RSCAN0RMID35H RSCAN0.RMID35.UINT16[H]
#define RSCAN0RMID35HL RSCAN0.RMID35.UINT8[HL]
#define RSCAN0RMID35HH RSCAN0.RMID35.UINT8[HH]
#define RSCAN0RMPTR35 RSCAN0.RMPTR35.UINT32
#define RSCAN0RMPTR35L RSCAN0.RMPTR35.UINT16[L]
#define RSCAN0RMPTR35LL RSCAN0.RMPTR35.UINT8[LL]
#define RSCAN0RMPTR35LH RSCAN0.RMPTR35.UINT8[LH]
#define RSCAN0RMPTR35H RSCAN0.RMPTR35.UINT16[H]
#define RSCAN0RMPTR35HL RSCAN0.RMPTR35.UINT8[HL]
#define RSCAN0RMPTR35HH RSCAN0.RMPTR35.UINT8[HH]
#define RSCAN0RMDF035 RSCAN0.RMDF035.UINT32
#define RSCAN0RMDF035L RSCAN0.RMDF035.UINT16[L]
#define RSCAN0RMDF035LL RSCAN0.RMDF035.UINT8[LL]
#define RSCAN0RMDF035LH RSCAN0.RMDF035.UINT8[LH]
#define RSCAN0RMDF035H RSCAN0.RMDF035.UINT16[H]
#define RSCAN0RMDF035HL RSCAN0.RMDF035.UINT8[HL]
#define RSCAN0RMDF035HH RSCAN0.RMDF035.UINT8[HH]
#define RSCAN0RMDF135 RSCAN0.RMDF135.UINT32
#define RSCAN0RMDF135L RSCAN0.RMDF135.UINT16[L]
#define RSCAN0RMDF135LL RSCAN0.RMDF135.UINT8[LL]
#define RSCAN0RMDF135LH RSCAN0.RMDF135.UINT8[LH]
#define RSCAN0RMDF135H RSCAN0.RMDF135.UINT16[H]
#define RSCAN0RMDF135HL RSCAN0.RMDF135.UINT8[HL]
#define RSCAN0RMDF135HH RSCAN0.RMDF135.UINT8[HH]
#define RSCAN0RMID36 RSCAN0.RMID36.UINT32
#define RSCAN0RMID36L RSCAN0.RMID36.UINT16[L]
#define RSCAN0RMID36LL RSCAN0.RMID36.UINT8[LL]
#define RSCAN0RMID36LH RSCAN0.RMID36.UINT8[LH]
#define RSCAN0RMID36H RSCAN0.RMID36.UINT16[H]
#define RSCAN0RMID36HL RSCAN0.RMID36.UINT8[HL]
#define RSCAN0RMID36HH RSCAN0.RMID36.UINT8[HH]
#define RSCAN0RMPTR36 RSCAN0.RMPTR36.UINT32
#define RSCAN0RMPTR36L RSCAN0.RMPTR36.UINT16[L]
#define RSCAN0RMPTR36LL RSCAN0.RMPTR36.UINT8[LL]
#define RSCAN0RMPTR36LH RSCAN0.RMPTR36.UINT8[LH]
#define RSCAN0RMPTR36H RSCAN0.RMPTR36.UINT16[H]
#define RSCAN0RMPTR36HL RSCAN0.RMPTR36.UINT8[HL]
#define RSCAN0RMPTR36HH RSCAN0.RMPTR36.UINT8[HH]
#define RSCAN0RMDF036 RSCAN0.RMDF036.UINT32
#define RSCAN0RMDF036L RSCAN0.RMDF036.UINT16[L]
#define RSCAN0RMDF036LL RSCAN0.RMDF036.UINT8[LL]
#define RSCAN0RMDF036LH RSCAN0.RMDF036.UINT8[LH]
#define RSCAN0RMDF036H RSCAN0.RMDF036.UINT16[H]
#define RSCAN0RMDF036HL RSCAN0.RMDF036.UINT8[HL]
#define RSCAN0RMDF036HH RSCAN0.RMDF036.UINT8[HH]
#define RSCAN0RMDF136 RSCAN0.RMDF136.UINT32
#define RSCAN0RMDF136L RSCAN0.RMDF136.UINT16[L]
#define RSCAN0RMDF136LL RSCAN0.RMDF136.UINT8[LL]
#define RSCAN0RMDF136LH RSCAN0.RMDF136.UINT8[LH]
#define RSCAN0RMDF136H RSCAN0.RMDF136.UINT16[H]
#define RSCAN0RMDF136HL RSCAN0.RMDF136.UINT8[HL]
#define RSCAN0RMDF136HH RSCAN0.RMDF136.UINT8[HH]
#define RSCAN0RMID37 RSCAN0.RMID37.UINT32
#define RSCAN0RMID37L RSCAN0.RMID37.UINT16[L]
#define RSCAN0RMID37LL RSCAN0.RMID37.UINT8[LL]
#define RSCAN0RMID37LH RSCAN0.RMID37.UINT8[LH]
#define RSCAN0RMID37H RSCAN0.RMID37.UINT16[H]
#define RSCAN0RMID37HL RSCAN0.RMID37.UINT8[HL]
#define RSCAN0RMID37HH RSCAN0.RMID37.UINT8[HH]
#define RSCAN0RMPTR37 RSCAN0.RMPTR37.UINT32
#define RSCAN0RMPTR37L RSCAN0.RMPTR37.UINT16[L]
#define RSCAN0RMPTR37LL RSCAN0.RMPTR37.UINT8[LL]
#define RSCAN0RMPTR37LH RSCAN0.RMPTR37.UINT8[LH]
#define RSCAN0RMPTR37H RSCAN0.RMPTR37.UINT16[H]
#define RSCAN0RMPTR37HL RSCAN0.RMPTR37.UINT8[HL]
#define RSCAN0RMPTR37HH RSCAN0.RMPTR37.UINT8[HH]
#define RSCAN0RMDF037 RSCAN0.RMDF037.UINT32
#define RSCAN0RMDF037L RSCAN0.RMDF037.UINT16[L]
#define RSCAN0RMDF037LL RSCAN0.RMDF037.UINT8[LL]
#define RSCAN0RMDF037LH RSCAN0.RMDF037.UINT8[LH]
#define RSCAN0RMDF037H RSCAN0.RMDF037.UINT16[H]
#define RSCAN0RMDF037HL RSCAN0.RMDF037.UINT8[HL]
#define RSCAN0RMDF037HH RSCAN0.RMDF037.UINT8[HH]
#define RSCAN0RMDF137 RSCAN0.RMDF137.UINT32
#define RSCAN0RMDF137L RSCAN0.RMDF137.UINT16[L]
#define RSCAN0RMDF137LL RSCAN0.RMDF137.UINT8[LL]
#define RSCAN0RMDF137LH RSCAN0.RMDF137.UINT8[LH]
#define RSCAN0RMDF137H RSCAN0.RMDF137.UINT16[H]
#define RSCAN0RMDF137HL RSCAN0.RMDF137.UINT8[HL]
#define RSCAN0RMDF137HH RSCAN0.RMDF137.UINT8[HH]
#define RSCAN0RMID38 RSCAN0.RMID38.UINT32
#define RSCAN0RMID38L RSCAN0.RMID38.UINT16[L]
#define RSCAN0RMID38LL RSCAN0.RMID38.UINT8[LL]
#define RSCAN0RMID38LH RSCAN0.RMID38.UINT8[LH]
#define RSCAN0RMID38H RSCAN0.RMID38.UINT16[H]
#define RSCAN0RMID38HL RSCAN0.RMID38.UINT8[HL]
#define RSCAN0RMID38HH RSCAN0.RMID38.UINT8[HH]
#define RSCAN0RMPTR38 RSCAN0.RMPTR38.UINT32
#define RSCAN0RMPTR38L RSCAN0.RMPTR38.UINT16[L]
#define RSCAN0RMPTR38LL RSCAN0.RMPTR38.UINT8[LL]
#define RSCAN0RMPTR38LH RSCAN0.RMPTR38.UINT8[LH]
#define RSCAN0RMPTR38H RSCAN0.RMPTR38.UINT16[H]
#define RSCAN0RMPTR38HL RSCAN0.RMPTR38.UINT8[HL]
#define RSCAN0RMPTR38HH RSCAN0.RMPTR38.UINT8[HH]
#define RSCAN0RMDF038 RSCAN0.RMDF038.UINT32
#define RSCAN0RMDF038L RSCAN0.RMDF038.UINT16[L]
#define RSCAN0RMDF038LL RSCAN0.RMDF038.UINT8[LL]
#define RSCAN0RMDF038LH RSCAN0.RMDF038.UINT8[LH]
#define RSCAN0RMDF038H RSCAN0.RMDF038.UINT16[H]
#define RSCAN0RMDF038HL RSCAN0.RMDF038.UINT8[HL]
#define RSCAN0RMDF038HH RSCAN0.RMDF038.UINT8[HH]
#define RSCAN0RMDF138 RSCAN0.RMDF138.UINT32
#define RSCAN0RMDF138L RSCAN0.RMDF138.UINT16[L]
#define RSCAN0RMDF138LL RSCAN0.RMDF138.UINT8[LL]
#define RSCAN0RMDF138LH RSCAN0.RMDF138.UINT8[LH]
#define RSCAN0RMDF138H RSCAN0.RMDF138.UINT16[H]
#define RSCAN0RMDF138HL RSCAN0.RMDF138.UINT8[HL]
#define RSCAN0RMDF138HH RSCAN0.RMDF138.UINT8[HH]
#define RSCAN0RMID39 RSCAN0.RMID39.UINT32
#define RSCAN0RMID39L RSCAN0.RMID39.UINT16[L]
#define RSCAN0RMID39LL RSCAN0.RMID39.UINT8[LL]
#define RSCAN0RMID39LH RSCAN0.RMID39.UINT8[LH]
#define RSCAN0RMID39H RSCAN0.RMID39.UINT16[H]
#define RSCAN0RMID39HL RSCAN0.RMID39.UINT8[HL]
#define RSCAN0RMID39HH RSCAN0.RMID39.UINT8[HH]
#define RSCAN0RMPTR39 RSCAN0.RMPTR39.UINT32
#define RSCAN0RMPTR39L RSCAN0.RMPTR39.UINT16[L]
#define RSCAN0RMPTR39LL RSCAN0.RMPTR39.UINT8[LL]
#define RSCAN0RMPTR39LH RSCAN0.RMPTR39.UINT8[LH]
#define RSCAN0RMPTR39H RSCAN0.RMPTR39.UINT16[H]
#define RSCAN0RMPTR39HL RSCAN0.RMPTR39.UINT8[HL]
#define RSCAN0RMPTR39HH RSCAN0.RMPTR39.UINT8[HH]
#define RSCAN0RMDF039 RSCAN0.RMDF039.UINT32
#define RSCAN0RMDF039L RSCAN0.RMDF039.UINT16[L]
#define RSCAN0RMDF039LL RSCAN0.RMDF039.UINT8[LL]
#define RSCAN0RMDF039LH RSCAN0.RMDF039.UINT8[LH]
#define RSCAN0RMDF039H RSCAN0.RMDF039.UINT16[H]
#define RSCAN0RMDF039HL RSCAN0.RMDF039.UINT8[HL]
#define RSCAN0RMDF039HH RSCAN0.RMDF039.UINT8[HH]
#define RSCAN0RMDF139 RSCAN0.RMDF139.UINT32
#define RSCAN0RMDF139L RSCAN0.RMDF139.UINT16[L]
#define RSCAN0RMDF139LL RSCAN0.RMDF139.UINT8[LL]
#define RSCAN0RMDF139LH RSCAN0.RMDF139.UINT8[LH]
#define RSCAN0RMDF139H RSCAN0.RMDF139.UINT16[H]
#define RSCAN0RMDF139HL RSCAN0.RMDF139.UINT8[HL]
#define RSCAN0RMDF139HH RSCAN0.RMDF139.UINT8[HH]
#define RSCAN0RMID40 RSCAN0.RMID40.UINT32
#define RSCAN0RMID40L RSCAN0.RMID40.UINT16[L]
#define RSCAN0RMID40LL RSCAN0.RMID40.UINT8[LL]
#define RSCAN0RMID40LH RSCAN0.RMID40.UINT8[LH]
#define RSCAN0RMID40H RSCAN0.RMID40.UINT16[H]
#define RSCAN0RMID40HL RSCAN0.RMID40.UINT8[HL]
#define RSCAN0RMID40HH RSCAN0.RMID40.UINT8[HH]
#define RSCAN0RMPTR40 RSCAN0.RMPTR40.UINT32
#define RSCAN0RMPTR40L RSCAN0.RMPTR40.UINT16[L]
#define RSCAN0RMPTR40LL RSCAN0.RMPTR40.UINT8[LL]
#define RSCAN0RMPTR40LH RSCAN0.RMPTR40.UINT8[LH]
#define RSCAN0RMPTR40H RSCAN0.RMPTR40.UINT16[H]
#define RSCAN0RMPTR40HL RSCAN0.RMPTR40.UINT8[HL]
#define RSCAN0RMPTR40HH RSCAN0.RMPTR40.UINT8[HH]
#define RSCAN0RMDF040 RSCAN0.RMDF040.UINT32
#define RSCAN0RMDF040L RSCAN0.RMDF040.UINT16[L]
#define RSCAN0RMDF040LL RSCAN0.RMDF040.UINT8[LL]
#define RSCAN0RMDF040LH RSCAN0.RMDF040.UINT8[LH]
#define RSCAN0RMDF040H RSCAN0.RMDF040.UINT16[H]
#define RSCAN0RMDF040HL RSCAN0.RMDF040.UINT8[HL]
#define RSCAN0RMDF040HH RSCAN0.RMDF040.UINT8[HH]
#define RSCAN0RMDF140 RSCAN0.RMDF140.UINT32
#define RSCAN0RMDF140L RSCAN0.RMDF140.UINT16[L]
#define RSCAN0RMDF140LL RSCAN0.RMDF140.UINT8[LL]
#define RSCAN0RMDF140LH RSCAN0.RMDF140.UINT8[LH]
#define RSCAN0RMDF140H RSCAN0.RMDF140.UINT16[H]
#define RSCAN0RMDF140HL RSCAN0.RMDF140.UINT8[HL]
#define RSCAN0RMDF140HH RSCAN0.RMDF140.UINT8[HH]
#define RSCAN0RMID41 RSCAN0.RMID41.UINT32
#define RSCAN0RMID41L RSCAN0.RMID41.UINT16[L]
#define RSCAN0RMID41LL RSCAN0.RMID41.UINT8[LL]
#define RSCAN0RMID41LH RSCAN0.RMID41.UINT8[LH]
#define RSCAN0RMID41H RSCAN0.RMID41.UINT16[H]
#define RSCAN0RMID41HL RSCAN0.RMID41.UINT8[HL]
#define RSCAN0RMID41HH RSCAN0.RMID41.UINT8[HH]
#define RSCAN0RMPTR41 RSCAN0.RMPTR41.UINT32
#define RSCAN0RMPTR41L RSCAN0.RMPTR41.UINT16[L]
#define RSCAN0RMPTR41LL RSCAN0.RMPTR41.UINT8[LL]
#define RSCAN0RMPTR41LH RSCAN0.RMPTR41.UINT8[LH]
#define RSCAN0RMPTR41H RSCAN0.RMPTR41.UINT16[H]
#define RSCAN0RMPTR41HL RSCAN0.RMPTR41.UINT8[HL]
#define RSCAN0RMPTR41HH RSCAN0.RMPTR41.UINT8[HH]
#define RSCAN0RMDF041 RSCAN0.RMDF041.UINT32
#define RSCAN0RMDF041L RSCAN0.RMDF041.UINT16[L]
#define RSCAN0RMDF041LL RSCAN0.RMDF041.UINT8[LL]
#define RSCAN0RMDF041LH RSCAN0.RMDF041.UINT8[LH]
#define RSCAN0RMDF041H RSCAN0.RMDF041.UINT16[H]
#define RSCAN0RMDF041HL RSCAN0.RMDF041.UINT8[HL]
#define RSCAN0RMDF041HH RSCAN0.RMDF041.UINT8[HH]
#define RSCAN0RMDF141 RSCAN0.RMDF141.UINT32
#define RSCAN0RMDF141L RSCAN0.RMDF141.UINT16[L]
#define RSCAN0RMDF141LL RSCAN0.RMDF141.UINT8[LL]
#define RSCAN0RMDF141LH RSCAN0.RMDF141.UINT8[LH]
#define RSCAN0RMDF141H RSCAN0.RMDF141.UINT16[H]
#define RSCAN0RMDF141HL RSCAN0.RMDF141.UINT8[HL]
#define RSCAN0RMDF141HH RSCAN0.RMDF141.UINT8[HH]
#define RSCAN0RMID42 RSCAN0.RMID42.UINT32
#define RSCAN0RMID42L RSCAN0.RMID42.UINT16[L]
#define RSCAN0RMID42LL RSCAN0.RMID42.UINT8[LL]
#define RSCAN0RMID42LH RSCAN0.RMID42.UINT8[LH]
#define RSCAN0RMID42H RSCAN0.RMID42.UINT16[H]
#define RSCAN0RMID42HL RSCAN0.RMID42.UINT8[HL]
#define RSCAN0RMID42HH RSCAN0.RMID42.UINT8[HH]
#define RSCAN0RMPTR42 RSCAN0.RMPTR42.UINT32
#define RSCAN0RMPTR42L RSCAN0.RMPTR42.UINT16[L]
#define RSCAN0RMPTR42LL RSCAN0.RMPTR42.UINT8[LL]
#define RSCAN0RMPTR42LH RSCAN0.RMPTR42.UINT8[LH]
#define RSCAN0RMPTR42H RSCAN0.RMPTR42.UINT16[H]
#define RSCAN0RMPTR42HL RSCAN0.RMPTR42.UINT8[HL]
#define RSCAN0RMPTR42HH RSCAN0.RMPTR42.UINT8[HH]
#define RSCAN0RMDF042 RSCAN0.RMDF042.UINT32
#define RSCAN0RMDF042L RSCAN0.RMDF042.UINT16[L]
#define RSCAN0RMDF042LL RSCAN0.RMDF042.UINT8[LL]
#define RSCAN0RMDF042LH RSCAN0.RMDF042.UINT8[LH]
#define RSCAN0RMDF042H RSCAN0.RMDF042.UINT16[H]
#define RSCAN0RMDF042HL RSCAN0.RMDF042.UINT8[HL]
#define RSCAN0RMDF042HH RSCAN0.RMDF042.UINT8[HH]
#define RSCAN0RMDF142 RSCAN0.RMDF142.UINT32
#define RSCAN0RMDF142L RSCAN0.RMDF142.UINT16[L]
#define RSCAN0RMDF142LL RSCAN0.RMDF142.UINT8[LL]
#define RSCAN0RMDF142LH RSCAN0.RMDF142.UINT8[LH]
#define RSCAN0RMDF142H RSCAN0.RMDF142.UINT16[H]
#define RSCAN0RMDF142HL RSCAN0.RMDF142.UINT8[HL]
#define RSCAN0RMDF142HH RSCAN0.RMDF142.UINT8[HH]
#define RSCAN0RMID43 RSCAN0.RMID43.UINT32
#define RSCAN0RMID43L RSCAN0.RMID43.UINT16[L]
#define RSCAN0RMID43LL RSCAN0.RMID43.UINT8[LL]
#define RSCAN0RMID43LH RSCAN0.RMID43.UINT8[LH]
#define RSCAN0RMID43H RSCAN0.RMID43.UINT16[H]
#define RSCAN0RMID43HL RSCAN0.RMID43.UINT8[HL]
#define RSCAN0RMID43HH RSCAN0.RMID43.UINT8[HH]
#define RSCAN0RMPTR43 RSCAN0.RMPTR43.UINT32
#define RSCAN0RMPTR43L RSCAN0.RMPTR43.UINT16[L]
#define RSCAN0RMPTR43LL RSCAN0.RMPTR43.UINT8[LL]
#define RSCAN0RMPTR43LH RSCAN0.RMPTR43.UINT8[LH]
#define RSCAN0RMPTR43H RSCAN0.RMPTR43.UINT16[H]
#define RSCAN0RMPTR43HL RSCAN0.RMPTR43.UINT8[HL]
#define RSCAN0RMPTR43HH RSCAN0.RMPTR43.UINT8[HH]
#define RSCAN0RMDF043 RSCAN0.RMDF043.UINT32
#define RSCAN0RMDF043L RSCAN0.RMDF043.UINT16[L]
#define RSCAN0RMDF043LL RSCAN0.RMDF043.UINT8[LL]
#define RSCAN0RMDF043LH RSCAN0.RMDF043.UINT8[LH]
#define RSCAN0RMDF043H RSCAN0.RMDF043.UINT16[H]
#define RSCAN0RMDF043HL RSCAN0.RMDF043.UINT8[HL]
#define RSCAN0RMDF043HH RSCAN0.RMDF043.UINT8[HH]
#define RSCAN0RMDF143 RSCAN0.RMDF143.UINT32
#define RSCAN0RMDF143L RSCAN0.RMDF143.UINT16[L]
#define RSCAN0RMDF143LL RSCAN0.RMDF143.UINT8[LL]
#define RSCAN0RMDF143LH RSCAN0.RMDF143.UINT8[LH]
#define RSCAN0RMDF143H RSCAN0.RMDF143.UINT16[H]
#define RSCAN0RMDF143HL RSCAN0.RMDF143.UINT8[HL]
#define RSCAN0RMDF143HH RSCAN0.RMDF143.UINT8[HH]
#define RSCAN0RMID44 RSCAN0.RMID44.UINT32
#define RSCAN0RMID44L RSCAN0.RMID44.UINT16[L]
#define RSCAN0RMID44LL RSCAN0.RMID44.UINT8[LL]
#define RSCAN0RMID44LH RSCAN0.RMID44.UINT8[LH]
#define RSCAN0RMID44H RSCAN0.RMID44.UINT16[H]
#define RSCAN0RMID44HL RSCAN0.RMID44.UINT8[HL]
#define RSCAN0RMID44HH RSCAN0.RMID44.UINT8[HH]
#define RSCAN0RMPTR44 RSCAN0.RMPTR44.UINT32
#define RSCAN0RMPTR44L RSCAN0.RMPTR44.UINT16[L]
#define RSCAN0RMPTR44LL RSCAN0.RMPTR44.UINT8[LL]
#define RSCAN0RMPTR44LH RSCAN0.RMPTR44.UINT8[LH]
#define RSCAN0RMPTR44H RSCAN0.RMPTR44.UINT16[H]
#define RSCAN0RMPTR44HL RSCAN0.RMPTR44.UINT8[HL]
#define RSCAN0RMPTR44HH RSCAN0.RMPTR44.UINT8[HH]
#define RSCAN0RMDF044 RSCAN0.RMDF044.UINT32
#define RSCAN0RMDF044L RSCAN0.RMDF044.UINT16[L]
#define RSCAN0RMDF044LL RSCAN0.RMDF044.UINT8[LL]
#define RSCAN0RMDF044LH RSCAN0.RMDF044.UINT8[LH]
#define RSCAN0RMDF044H RSCAN0.RMDF044.UINT16[H]
#define RSCAN0RMDF044HL RSCAN0.RMDF044.UINT8[HL]
#define RSCAN0RMDF044HH RSCAN0.RMDF044.UINT8[HH]
#define RSCAN0RMDF144 RSCAN0.RMDF144.UINT32
#define RSCAN0RMDF144L RSCAN0.RMDF144.UINT16[L]
#define RSCAN0RMDF144LL RSCAN0.RMDF144.UINT8[LL]
#define RSCAN0RMDF144LH RSCAN0.RMDF144.UINT8[LH]
#define RSCAN0RMDF144H RSCAN0.RMDF144.UINT16[H]
#define RSCAN0RMDF144HL RSCAN0.RMDF144.UINT8[HL]
#define RSCAN0RMDF144HH RSCAN0.RMDF144.UINT8[HH]
#define RSCAN0RMID45 RSCAN0.RMID45.UINT32
#define RSCAN0RMID45L RSCAN0.RMID45.UINT16[L]
#define RSCAN0RMID45LL RSCAN0.RMID45.UINT8[LL]
#define RSCAN0RMID45LH RSCAN0.RMID45.UINT8[LH]
#define RSCAN0RMID45H RSCAN0.RMID45.UINT16[H]
#define RSCAN0RMID45HL RSCAN0.RMID45.UINT8[HL]
#define RSCAN0RMID45HH RSCAN0.RMID45.UINT8[HH]
#define RSCAN0RMPTR45 RSCAN0.RMPTR45.UINT32
#define RSCAN0RMPTR45L RSCAN0.RMPTR45.UINT16[L]
#define RSCAN0RMPTR45LL RSCAN0.RMPTR45.UINT8[LL]
#define RSCAN0RMPTR45LH RSCAN0.RMPTR45.UINT8[LH]
#define RSCAN0RMPTR45H RSCAN0.RMPTR45.UINT16[H]
#define RSCAN0RMPTR45HL RSCAN0.RMPTR45.UINT8[HL]
#define RSCAN0RMPTR45HH RSCAN0.RMPTR45.UINT8[HH]
#define RSCAN0RMDF045 RSCAN0.RMDF045.UINT32
#define RSCAN0RMDF045L RSCAN0.RMDF045.UINT16[L]
#define RSCAN0RMDF045LL RSCAN0.RMDF045.UINT8[LL]
#define RSCAN0RMDF045LH RSCAN0.RMDF045.UINT8[LH]
#define RSCAN0RMDF045H RSCAN0.RMDF045.UINT16[H]
#define RSCAN0RMDF045HL RSCAN0.RMDF045.UINT8[HL]
#define RSCAN0RMDF045HH RSCAN0.RMDF045.UINT8[HH]
#define RSCAN0RMDF145 RSCAN0.RMDF145.UINT32
#define RSCAN0RMDF145L RSCAN0.RMDF145.UINT16[L]
#define RSCAN0RMDF145LL RSCAN0.RMDF145.UINT8[LL]
#define RSCAN0RMDF145LH RSCAN0.RMDF145.UINT8[LH]
#define RSCAN0RMDF145H RSCAN0.RMDF145.UINT16[H]
#define RSCAN0RMDF145HL RSCAN0.RMDF145.UINT8[HL]
#define RSCAN0RMDF145HH RSCAN0.RMDF145.UINT8[HH]
#define RSCAN0RMID46 RSCAN0.RMID46.UINT32
#define RSCAN0RMID46L RSCAN0.RMID46.UINT16[L]
#define RSCAN0RMID46LL RSCAN0.RMID46.UINT8[LL]
#define RSCAN0RMID46LH RSCAN0.RMID46.UINT8[LH]
#define RSCAN0RMID46H RSCAN0.RMID46.UINT16[H]
#define RSCAN0RMID46HL RSCAN0.RMID46.UINT8[HL]
#define RSCAN0RMID46HH RSCAN0.RMID46.UINT8[HH]
#define RSCAN0RMPTR46 RSCAN0.RMPTR46.UINT32
#define RSCAN0RMPTR46L RSCAN0.RMPTR46.UINT16[L]
#define RSCAN0RMPTR46LL RSCAN0.RMPTR46.UINT8[LL]
#define RSCAN0RMPTR46LH RSCAN0.RMPTR46.UINT8[LH]
#define RSCAN0RMPTR46H RSCAN0.RMPTR46.UINT16[H]
#define RSCAN0RMPTR46HL RSCAN0.RMPTR46.UINT8[HL]
#define RSCAN0RMPTR46HH RSCAN0.RMPTR46.UINT8[HH]
#define RSCAN0RMDF046 RSCAN0.RMDF046.UINT32
#define RSCAN0RMDF046L RSCAN0.RMDF046.UINT16[L]
#define RSCAN0RMDF046LL RSCAN0.RMDF046.UINT8[LL]
#define RSCAN0RMDF046LH RSCAN0.RMDF046.UINT8[LH]
#define RSCAN0RMDF046H RSCAN0.RMDF046.UINT16[H]
#define RSCAN0RMDF046HL RSCAN0.RMDF046.UINT8[HL]
#define RSCAN0RMDF046HH RSCAN0.RMDF046.UINT8[HH]
#define RSCAN0RMDF146 RSCAN0.RMDF146.UINT32
#define RSCAN0RMDF146L RSCAN0.RMDF146.UINT16[L]
#define RSCAN0RMDF146LL RSCAN0.RMDF146.UINT8[LL]
#define RSCAN0RMDF146LH RSCAN0.RMDF146.UINT8[LH]
#define RSCAN0RMDF146H RSCAN0.RMDF146.UINT16[H]
#define RSCAN0RMDF146HL RSCAN0.RMDF146.UINT8[HL]
#define RSCAN0RMDF146HH RSCAN0.RMDF146.UINT8[HH]
#define RSCAN0RMID47 RSCAN0.RMID47.UINT32
#define RSCAN0RMID47L RSCAN0.RMID47.UINT16[L]
#define RSCAN0RMID47LL RSCAN0.RMID47.UINT8[LL]
#define RSCAN0RMID47LH RSCAN0.RMID47.UINT8[LH]
#define RSCAN0RMID47H RSCAN0.RMID47.UINT16[H]
#define RSCAN0RMID47HL RSCAN0.RMID47.UINT8[HL]
#define RSCAN0RMID47HH RSCAN0.RMID47.UINT8[HH]
#define RSCAN0RMPTR47 RSCAN0.RMPTR47.UINT32
#define RSCAN0RMPTR47L RSCAN0.RMPTR47.UINT16[L]
#define RSCAN0RMPTR47LL RSCAN0.RMPTR47.UINT8[LL]
#define RSCAN0RMPTR47LH RSCAN0.RMPTR47.UINT8[LH]
#define RSCAN0RMPTR47H RSCAN0.RMPTR47.UINT16[H]
#define RSCAN0RMPTR47HL RSCAN0.RMPTR47.UINT8[HL]
#define RSCAN0RMPTR47HH RSCAN0.RMPTR47.UINT8[HH]
#define RSCAN0RMDF047 RSCAN0.RMDF047.UINT32
#define RSCAN0RMDF047L RSCAN0.RMDF047.UINT16[L]
#define RSCAN0RMDF047LL RSCAN0.RMDF047.UINT8[LL]
#define RSCAN0RMDF047LH RSCAN0.RMDF047.UINT8[LH]
#define RSCAN0RMDF047H RSCAN0.RMDF047.UINT16[H]
#define RSCAN0RMDF047HL RSCAN0.RMDF047.UINT8[HL]
#define RSCAN0RMDF047HH RSCAN0.RMDF047.UINT8[HH]
#define RSCAN0RMDF147 RSCAN0.RMDF147.UINT32
#define RSCAN0RMDF147L RSCAN0.RMDF147.UINT16[L]
#define RSCAN0RMDF147LL RSCAN0.RMDF147.UINT8[LL]
#define RSCAN0RMDF147LH RSCAN0.RMDF147.UINT8[LH]
#define RSCAN0RMDF147H RSCAN0.RMDF147.UINT16[H]
#define RSCAN0RMDF147HL RSCAN0.RMDF147.UINT8[HL]
#define RSCAN0RMDF147HH RSCAN0.RMDF147.UINT8[HH]
#define RSCAN0RMID48 RSCAN0.RMID48.UINT32
#define RSCAN0RMID48L RSCAN0.RMID48.UINT16[L]
#define RSCAN0RMID48LL RSCAN0.RMID48.UINT8[LL]
#define RSCAN0RMID48LH RSCAN0.RMID48.UINT8[LH]
#define RSCAN0RMID48H RSCAN0.RMID48.UINT16[H]
#define RSCAN0RMID48HL RSCAN0.RMID48.UINT8[HL]
#define RSCAN0RMID48HH RSCAN0.RMID48.UINT8[HH]
#define RSCAN0RMPTR48 RSCAN0.RMPTR48.UINT32
#define RSCAN0RMPTR48L RSCAN0.RMPTR48.UINT16[L]
#define RSCAN0RMPTR48LL RSCAN0.RMPTR48.UINT8[LL]
#define RSCAN0RMPTR48LH RSCAN0.RMPTR48.UINT8[LH]
#define RSCAN0RMPTR48H RSCAN0.RMPTR48.UINT16[H]
#define RSCAN0RMPTR48HL RSCAN0.RMPTR48.UINT8[HL]
#define RSCAN0RMPTR48HH RSCAN0.RMPTR48.UINT8[HH]
#define RSCAN0RMDF048 RSCAN0.RMDF048.UINT32
#define RSCAN0RMDF048L RSCAN0.RMDF048.UINT16[L]
#define RSCAN0RMDF048LL RSCAN0.RMDF048.UINT8[LL]
#define RSCAN0RMDF048LH RSCAN0.RMDF048.UINT8[LH]
#define RSCAN0RMDF048H RSCAN0.RMDF048.UINT16[H]
#define RSCAN0RMDF048HL RSCAN0.RMDF048.UINT8[HL]
#define RSCAN0RMDF048HH RSCAN0.RMDF048.UINT8[HH]
#define RSCAN0RMDF148 RSCAN0.RMDF148.UINT32
#define RSCAN0RMDF148L RSCAN0.RMDF148.UINT16[L]
#define RSCAN0RMDF148LL RSCAN0.RMDF148.UINT8[LL]
#define RSCAN0RMDF148LH RSCAN0.RMDF148.UINT8[LH]
#define RSCAN0RMDF148H RSCAN0.RMDF148.UINT16[H]
#define RSCAN0RMDF148HL RSCAN0.RMDF148.UINT8[HL]
#define RSCAN0RMDF148HH RSCAN0.RMDF148.UINT8[HH]
#define RSCAN0RMID49 RSCAN0.RMID49.UINT32
#define RSCAN0RMID49L RSCAN0.RMID49.UINT16[L]
#define RSCAN0RMID49LL RSCAN0.RMID49.UINT8[LL]
#define RSCAN0RMID49LH RSCAN0.RMID49.UINT8[LH]
#define RSCAN0RMID49H RSCAN0.RMID49.UINT16[H]
#define RSCAN0RMID49HL RSCAN0.RMID49.UINT8[HL]
#define RSCAN0RMID49HH RSCAN0.RMID49.UINT8[HH]
#define RSCAN0RMPTR49 RSCAN0.RMPTR49.UINT32
#define RSCAN0RMPTR49L RSCAN0.RMPTR49.UINT16[L]
#define RSCAN0RMPTR49LL RSCAN0.RMPTR49.UINT8[LL]
#define RSCAN0RMPTR49LH RSCAN0.RMPTR49.UINT8[LH]
#define RSCAN0RMPTR49H RSCAN0.RMPTR49.UINT16[H]
#define RSCAN0RMPTR49HL RSCAN0.RMPTR49.UINT8[HL]
#define RSCAN0RMPTR49HH RSCAN0.RMPTR49.UINT8[HH]
#define RSCAN0RMDF049 RSCAN0.RMDF049.UINT32
#define RSCAN0RMDF049L RSCAN0.RMDF049.UINT16[L]
#define RSCAN0RMDF049LL RSCAN0.RMDF049.UINT8[LL]
#define RSCAN0RMDF049LH RSCAN0.RMDF049.UINT8[LH]
#define RSCAN0RMDF049H RSCAN0.RMDF049.UINT16[H]
#define RSCAN0RMDF049HL RSCAN0.RMDF049.UINT8[HL]
#define RSCAN0RMDF049HH RSCAN0.RMDF049.UINT8[HH]
#define RSCAN0RMDF149 RSCAN0.RMDF149.UINT32
#define RSCAN0RMDF149L RSCAN0.RMDF149.UINT16[L]
#define RSCAN0RMDF149LL RSCAN0.RMDF149.UINT8[LL]
#define RSCAN0RMDF149LH RSCAN0.RMDF149.UINT8[LH]
#define RSCAN0RMDF149H RSCAN0.RMDF149.UINT16[H]
#define RSCAN0RMDF149HL RSCAN0.RMDF149.UINT8[HL]
#define RSCAN0RMDF149HH RSCAN0.RMDF149.UINT8[HH]
#define RSCAN0RMID50 RSCAN0.RMID50.UINT32
#define RSCAN0RMID50L RSCAN0.RMID50.UINT16[L]
#define RSCAN0RMID50LL RSCAN0.RMID50.UINT8[LL]
#define RSCAN0RMID50LH RSCAN0.RMID50.UINT8[LH]
#define RSCAN0RMID50H RSCAN0.RMID50.UINT16[H]
#define RSCAN0RMID50HL RSCAN0.RMID50.UINT8[HL]
#define RSCAN0RMID50HH RSCAN0.RMID50.UINT8[HH]
#define RSCAN0RMPTR50 RSCAN0.RMPTR50.UINT32
#define RSCAN0RMPTR50L RSCAN0.RMPTR50.UINT16[L]
#define RSCAN0RMPTR50LL RSCAN0.RMPTR50.UINT8[LL]
#define RSCAN0RMPTR50LH RSCAN0.RMPTR50.UINT8[LH]
#define RSCAN0RMPTR50H RSCAN0.RMPTR50.UINT16[H]
#define RSCAN0RMPTR50HL RSCAN0.RMPTR50.UINT8[HL]
#define RSCAN0RMPTR50HH RSCAN0.RMPTR50.UINT8[HH]
#define RSCAN0RMDF050 RSCAN0.RMDF050.UINT32
#define RSCAN0RMDF050L RSCAN0.RMDF050.UINT16[L]
#define RSCAN0RMDF050LL RSCAN0.RMDF050.UINT8[LL]
#define RSCAN0RMDF050LH RSCAN0.RMDF050.UINT8[LH]
#define RSCAN0RMDF050H RSCAN0.RMDF050.UINT16[H]
#define RSCAN0RMDF050HL RSCAN0.RMDF050.UINT8[HL]
#define RSCAN0RMDF050HH RSCAN0.RMDF050.UINT8[HH]
#define RSCAN0RMDF150 RSCAN0.RMDF150.UINT32
#define RSCAN0RMDF150L RSCAN0.RMDF150.UINT16[L]
#define RSCAN0RMDF150LL RSCAN0.RMDF150.UINT8[LL]
#define RSCAN0RMDF150LH RSCAN0.RMDF150.UINT8[LH]
#define RSCAN0RMDF150H RSCAN0.RMDF150.UINT16[H]
#define RSCAN0RMDF150HL RSCAN0.RMDF150.UINT8[HL]
#define RSCAN0RMDF150HH RSCAN0.RMDF150.UINT8[HH]
#define RSCAN0RMID51 RSCAN0.RMID51.UINT32
#define RSCAN0RMID51L RSCAN0.RMID51.UINT16[L]
#define RSCAN0RMID51LL RSCAN0.RMID51.UINT8[LL]
#define RSCAN0RMID51LH RSCAN0.RMID51.UINT8[LH]
#define RSCAN0RMID51H RSCAN0.RMID51.UINT16[H]
#define RSCAN0RMID51HL RSCAN0.RMID51.UINT8[HL]
#define RSCAN0RMID51HH RSCAN0.RMID51.UINT8[HH]
#define RSCAN0RMPTR51 RSCAN0.RMPTR51.UINT32
#define RSCAN0RMPTR51L RSCAN0.RMPTR51.UINT16[L]
#define RSCAN0RMPTR51LL RSCAN0.RMPTR51.UINT8[LL]
#define RSCAN0RMPTR51LH RSCAN0.RMPTR51.UINT8[LH]
#define RSCAN0RMPTR51H RSCAN0.RMPTR51.UINT16[H]
#define RSCAN0RMPTR51HL RSCAN0.RMPTR51.UINT8[HL]
#define RSCAN0RMPTR51HH RSCAN0.RMPTR51.UINT8[HH]
#define RSCAN0RMDF051 RSCAN0.RMDF051.UINT32
#define RSCAN0RMDF051L RSCAN0.RMDF051.UINT16[L]
#define RSCAN0RMDF051LL RSCAN0.RMDF051.UINT8[LL]
#define RSCAN0RMDF051LH RSCAN0.RMDF051.UINT8[LH]
#define RSCAN0RMDF051H RSCAN0.RMDF051.UINT16[H]
#define RSCAN0RMDF051HL RSCAN0.RMDF051.UINT8[HL]
#define RSCAN0RMDF051HH RSCAN0.RMDF051.UINT8[HH]
#define RSCAN0RMDF151 RSCAN0.RMDF151.UINT32
#define RSCAN0RMDF151L RSCAN0.RMDF151.UINT16[L]
#define RSCAN0RMDF151LL RSCAN0.RMDF151.UINT8[LL]
#define RSCAN0RMDF151LH RSCAN0.RMDF151.UINT8[LH]
#define RSCAN0RMDF151H RSCAN0.RMDF151.UINT16[H]
#define RSCAN0RMDF151HL RSCAN0.RMDF151.UINT8[HL]
#define RSCAN0RMDF151HH RSCAN0.RMDF151.UINT8[HH]
#define RSCAN0RMID52 RSCAN0.RMID52.UINT32
#define RSCAN0RMID52L RSCAN0.RMID52.UINT16[L]
#define RSCAN0RMID52LL RSCAN0.RMID52.UINT8[LL]
#define RSCAN0RMID52LH RSCAN0.RMID52.UINT8[LH]
#define RSCAN0RMID52H RSCAN0.RMID52.UINT16[H]
#define RSCAN0RMID52HL RSCAN0.RMID52.UINT8[HL]
#define RSCAN0RMID52HH RSCAN0.RMID52.UINT8[HH]
#define RSCAN0RMPTR52 RSCAN0.RMPTR52.UINT32
#define RSCAN0RMPTR52L RSCAN0.RMPTR52.UINT16[L]
#define RSCAN0RMPTR52LL RSCAN0.RMPTR52.UINT8[LL]
#define RSCAN0RMPTR52LH RSCAN0.RMPTR52.UINT8[LH]
#define RSCAN0RMPTR52H RSCAN0.RMPTR52.UINT16[H]
#define RSCAN0RMPTR52HL RSCAN0.RMPTR52.UINT8[HL]
#define RSCAN0RMPTR52HH RSCAN0.RMPTR52.UINT8[HH]
#define RSCAN0RMDF052 RSCAN0.RMDF052.UINT32
#define RSCAN0RMDF052L RSCAN0.RMDF052.UINT16[L]
#define RSCAN0RMDF052LL RSCAN0.RMDF052.UINT8[LL]
#define RSCAN0RMDF052LH RSCAN0.RMDF052.UINT8[LH]
#define RSCAN0RMDF052H RSCAN0.RMDF052.UINT16[H]
#define RSCAN0RMDF052HL RSCAN0.RMDF052.UINT8[HL]
#define RSCAN0RMDF052HH RSCAN0.RMDF052.UINT8[HH]
#define RSCAN0RMDF152 RSCAN0.RMDF152.UINT32
#define RSCAN0RMDF152L RSCAN0.RMDF152.UINT16[L]
#define RSCAN0RMDF152LL RSCAN0.RMDF152.UINT8[LL]
#define RSCAN0RMDF152LH RSCAN0.RMDF152.UINT8[LH]
#define RSCAN0RMDF152H RSCAN0.RMDF152.UINT16[H]
#define RSCAN0RMDF152HL RSCAN0.RMDF152.UINT8[HL]
#define RSCAN0RMDF152HH RSCAN0.RMDF152.UINT8[HH]
#define RSCAN0RMID53 RSCAN0.RMID53.UINT32
#define RSCAN0RMID53L RSCAN0.RMID53.UINT16[L]
#define RSCAN0RMID53LL RSCAN0.RMID53.UINT8[LL]
#define RSCAN0RMID53LH RSCAN0.RMID53.UINT8[LH]
#define RSCAN0RMID53H RSCAN0.RMID53.UINT16[H]
#define RSCAN0RMID53HL RSCAN0.RMID53.UINT8[HL]
#define RSCAN0RMID53HH RSCAN0.RMID53.UINT8[HH]
#define RSCAN0RMPTR53 RSCAN0.RMPTR53.UINT32
#define RSCAN0RMPTR53L RSCAN0.RMPTR53.UINT16[L]
#define RSCAN0RMPTR53LL RSCAN0.RMPTR53.UINT8[LL]
#define RSCAN0RMPTR53LH RSCAN0.RMPTR53.UINT8[LH]
#define RSCAN0RMPTR53H RSCAN0.RMPTR53.UINT16[H]
#define RSCAN0RMPTR53HL RSCAN0.RMPTR53.UINT8[HL]
#define RSCAN0RMPTR53HH RSCAN0.RMPTR53.UINT8[HH]
#define RSCAN0RMDF053 RSCAN0.RMDF053.UINT32
#define RSCAN0RMDF053L RSCAN0.RMDF053.UINT16[L]
#define RSCAN0RMDF053LL RSCAN0.RMDF053.UINT8[LL]
#define RSCAN0RMDF053LH RSCAN0.RMDF053.UINT8[LH]
#define RSCAN0RMDF053H RSCAN0.RMDF053.UINT16[H]
#define RSCAN0RMDF053HL RSCAN0.RMDF053.UINT8[HL]
#define RSCAN0RMDF053HH RSCAN0.RMDF053.UINT8[HH]
#define RSCAN0RMDF153 RSCAN0.RMDF153.UINT32
#define RSCAN0RMDF153L RSCAN0.RMDF153.UINT16[L]
#define RSCAN0RMDF153LL RSCAN0.RMDF153.UINT8[LL]
#define RSCAN0RMDF153LH RSCAN0.RMDF153.UINT8[LH]
#define RSCAN0RMDF153H RSCAN0.RMDF153.UINT16[H]
#define RSCAN0RMDF153HL RSCAN0.RMDF153.UINT8[HL]
#define RSCAN0RMDF153HH RSCAN0.RMDF153.UINT8[HH]
#define RSCAN0RMID54 RSCAN0.RMID54.UINT32
#define RSCAN0RMID54L RSCAN0.RMID54.UINT16[L]
#define RSCAN0RMID54LL RSCAN0.RMID54.UINT8[LL]
#define RSCAN0RMID54LH RSCAN0.RMID54.UINT8[LH]
#define RSCAN0RMID54H RSCAN0.RMID54.UINT16[H]
#define RSCAN0RMID54HL RSCAN0.RMID54.UINT8[HL]
#define RSCAN0RMID54HH RSCAN0.RMID54.UINT8[HH]
#define RSCAN0RMPTR54 RSCAN0.RMPTR54.UINT32
#define RSCAN0RMPTR54L RSCAN0.RMPTR54.UINT16[L]
#define RSCAN0RMPTR54LL RSCAN0.RMPTR54.UINT8[LL]
#define RSCAN0RMPTR54LH RSCAN0.RMPTR54.UINT8[LH]
#define RSCAN0RMPTR54H RSCAN0.RMPTR54.UINT16[H]
#define RSCAN0RMPTR54HL RSCAN0.RMPTR54.UINT8[HL]
#define RSCAN0RMPTR54HH RSCAN0.RMPTR54.UINT8[HH]
#define RSCAN0RMDF054 RSCAN0.RMDF054.UINT32
#define RSCAN0RMDF054L RSCAN0.RMDF054.UINT16[L]
#define RSCAN0RMDF054LL RSCAN0.RMDF054.UINT8[LL]
#define RSCAN0RMDF054LH RSCAN0.RMDF054.UINT8[LH]
#define RSCAN0RMDF054H RSCAN0.RMDF054.UINT16[H]
#define RSCAN0RMDF054HL RSCAN0.RMDF054.UINT8[HL]
#define RSCAN0RMDF054HH RSCAN0.RMDF054.UINT8[HH]
#define RSCAN0RMDF154 RSCAN0.RMDF154.UINT32
#define RSCAN0RMDF154L RSCAN0.RMDF154.UINT16[L]
#define RSCAN0RMDF154LL RSCAN0.RMDF154.UINT8[LL]
#define RSCAN0RMDF154LH RSCAN0.RMDF154.UINT8[LH]
#define RSCAN0RMDF154H RSCAN0.RMDF154.UINT16[H]
#define RSCAN0RMDF154HL RSCAN0.RMDF154.UINT8[HL]
#define RSCAN0RMDF154HH RSCAN0.RMDF154.UINT8[HH]
#define RSCAN0RMID55 RSCAN0.RMID55.UINT32
#define RSCAN0RMID55L RSCAN0.RMID55.UINT16[L]
#define RSCAN0RMID55LL RSCAN0.RMID55.UINT8[LL]
#define RSCAN0RMID55LH RSCAN0.RMID55.UINT8[LH]
#define RSCAN0RMID55H RSCAN0.RMID55.UINT16[H]
#define RSCAN0RMID55HL RSCAN0.RMID55.UINT8[HL]
#define RSCAN0RMID55HH RSCAN0.RMID55.UINT8[HH]
#define RSCAN0RMPTR55 RSCAN0.RMPTR55.UINT32
#define RSCAN0RMPTR55L RSCAN0.RMPTR55.UINT16[L]
#define RSCAN0RMPTR55LL RSCAN0.RMPTR55.UINT8[LL]
#define RSCAN0RMPTR55LH RSCAN0.RMPTR55.UINT8[LH]
#define RSCAN0RMPTR55H RSCAN0.RMPTR55.UINT16[H]
#define RSCAN0RMPTR55HL RSCAN0.RMPTR55.UINT8[HL]
#define RSCAN0RMPTR55HH RSCAN0.RMPTR55.UINT8[HH]
#define RSCAN0RMDF055 RSCAN0.RMDF055.UINT32
#define RSCAN0RMDF055L RSCAN0.RMDF055.UINT16[L]
#define RSCAN0RMDF055LL RSCAN0.RMDF055.UINT8[LL]
#define RSCAN0RMDF055LH RSCAN0.RMDF055.UINT8[LH]
#define RSCAN0RMDF055H RSCAN0.RMDF055.UINT16[H]
#define RSCAN0RMDF055HL RSCAN0.RMDF055.UINT8[HL]
#define RSCAN0RMDF055HH RSCAN0.RMDF055.UINT8[HH]
#define RSCAN0RMDF155 RSCAN0.RMDF155.UINT32
#define RSCAN0RMDF155L RSCAN0.RMDF155.UINT16[L]
#define RSCAN0RMDF155LL RSCAN0.RMDF155.UINT8[LL]
#define RSCAN0RMDF155LH RSCAN0.RMDF155.UINT8[LH]
#define RSCAN0RMDF155H RSCAN0.RMDF155.UINT16[H]
#define RSCAN0RMDF155HL RSCAN0.RMDF155.UINT8[HL]
#define RSCAN0RMDF155HH RSCAN0.RMDF155.UINT8[HH]
#define RSCAN0RMID56 RSCAN0.RMID56.UINT32
#define RSCAN0RMID56L RSCAN0.RMID56.UINT16[L]
#define RSCAN0RMID56LL RSCAN0.RMID56.UINT8[LL]
#define RSCAN0RMID56LH RSCAN0.RMID56.UINT8[LH]
#define RSCAN0RMID56H RSCAN0.RMID56.UINT16[H]
#define RSCAN0RMID56HL RSCAN0.RMID56.UINT8[HL]
#define RSCAN0RMID56HH RSCAN0.RMID56.UINT8[HH]
#define RSCAN0RMPTR56 RSCAN0.RMPTR56.UINT32
#define RSCAN0RMPTR56L RSCAN0.RMPTR56.UINT16[L]
#define RSCAN0RMPTR56LL RSCAN0.RMPTR56.UINT8[LL]
#define RSCAN0RMPTR56LH RSCAN0.RMPTR56.UINT8[LH]
#define RSCAN0RMPTR56H RSCAN0.RMPTR56.UINT16[H]
#define RSCAN0RMPTR56HL RSCAN0.RMPTR56.UINT8[HL]
#define RSCAN0RMPTR56HH RSCAN0.RMPTR56.UINT8[HH]
#define RSCAN0RMDF056 RSCAN0.RMDF056.UINT32
#define RSCAN0RMDF056L RSCAN0.RMDF056.UINT16[L]
#define RSCAN0RMDF056LL RSCAN0.RMDF056.UINT8[LL]
#define RSCAN0RMDF056LH RSCAN0.RMDF056.UINT8[LH]
#define RSCAN0RMDF056H RSCAN0.RMDF056.UINT16[H]
#define RSCAN0RMDF056HL RSCAN0.RMDF056.UINT8[HL]
#define RSCAN0RMDF056HH RSCAN0.RMDF056.UINT8[HH]
#define RSCAN0RMDF156 RSCAN0.RMDF156.UINT32
#define RSCAN0RMDF156L RSCAN0.RMDF156.UINT16[L]
#define RSCAN0RMDF156LL RSCAN0.RMDF156.UINT8[LL]
#define RSCAN0RMDF156LH RSCAN0.RMDF156.UINT8[LH]
#define RSCAN0RMDF156H RSCAN0.RMDF156.UINT16[H]
#define RSCAN0RMDF156HL RSCAN0.RMDF156.UINT8[HL]
#define RSCAN0RMDF156HH RSCAN0.RMDF156.UINT8[HH]
#define RSCAN0RMID57 RSCAN0.RMID57.UINT32
#define RSCAN0RMID57L RSCAN0.RMID57.UINT16[L]
#define RSCAN0RMID57LL RSCAN0.RMID57.UINT8[LL]
#define RSCAN0RMID57LH RSCAN0.RMID57.UINT8[LH]
#define RSCAN0RMID57H RSCAN0.RMID57.UINT16[H]
#define RSCAN0RMID57HL RSCAN0.RMID57.UINT8[HL]
#define RSCAN0RMID57HH RSCAN0.RMID57.UINT8[HH]
#define RSCAN0RMPTR57 RSCAN0.RMPTR57.UINT32
#define RSCAN0RMPTR57L RSCAN0.RMPTR57.UINT16[L]
#define RSCAN0RMPTR57LL RSCAN0.RMPTR57.UINT8[LL]
#define RSCAN0RMPTR57LH RSCAN0.RMPTR57.UINT8[LH]
#define RSCAN0RMPTR57H RSCAN0.RMPTR57.UINT16[H]
#define RSCAN0RMPTR57HL RSCAN0.RMPTR57.UINT8[HL]
#define RSCAN0RMPTR57HH RSCAN0.RMPTR57.UINT8[HH]
#define RSCAN0RMDF057 RSCAN0.RMDF057.UINT32
#define RSCAN0RMDF057L RSCAN0.RMDF057.UINT16[L]
#define RSCAN0RMDF057LL RSCAN0.RMDF057.UINT8[LL]
#define RSCAN0RMDF057LH RSCAN0.RMDF057.UINT8[LH]
#define RSCAN0RMDF057H RSCAN0.RMDF057.UINT16[H]
#define RSCAN0RMDF057HL RSCAN0.RMDF057.UINT8[HL]
#define RSCAN0RMDF057HH RSCAN0.RMDF057.UINT8[HH]
#define RSCAN0RMDF157 RSCAN0.RMDF157.UINT32
#define RSCAN0RMDF157L RSCAN0.RMDF157.UINT16[L]
#define RSCAN0RMDF157LL RSCAN0.RMDF157.UINT8[LL]
#define RSCAN0RMDF157LH RSCAN0.RMDF157.UINT8[LH]
#define RSCAN0RMDF157H RSCAN0.RMDF157.UINT16[H]
#define RSCAN0RMDF157HL RSCAN0.RMDF157.UINT8[HL]
#define RSCAN0RMDF157HH RSCAN0.RMDF157.UINT8[HH]
#define RSCAN0RMID58 RSCAN0.RMID58.UINT32
#define RSCAN0RMID58L RSCAN0.RMID58.UINT16[L]
#define RSCAN0RMID58LL RSCAN0.RMID58.UINT8[LL]
#define RSCAN0RMID58LH RSCAN0.RMID58.UINT8[LH]
#define RSCAN0RMID58H RSCAN0.RMID58.UINT16[H]
#define RSCAN0RMID58HL RSCAN0.RMID58.UINT8[HL]
#define RSCAN0RMID58HH RSCAN0.RMID58.UINT8[HH]
#define RSCAN0RMPTR58 RSCAN0.RMPTR58.UINT32
#define RSCAN0RMPTR58L RSCAN0.RMPTR58.UINT16[L]
#define RSCAN0RMPTR58LL RSCAN0.RMPTR58.UINT8[LL]
#define RSCAN0RMPTR58LH RSCAN0.RMPTR58.UINT8[LH]
#define RSCAN0RMPTR58H RSCAN0.RMPTR58.UINT16[H]
#define RSCAN0RMPTR58HL RSCAN0.RMPTR58.UINT8[HL]
#define RSCAN0RMPTR58HH RSCAN0.RMPTR58.UINT8[HH]
#define RSCAN0RMDF058 RSCAN0.RMDF058.UINT32
#define RSCAN0RMDF058L RSCAN0.RMDF058.UINT16[L]
#define RSCAN0RMDF058LL RSCAN0.RMDF058.UINT8[LL]
#define RSCAN0RMDF058LH RSCAN0.RMDF058.UINT8[LH]
#define RSCAN0RMDF058H RSCAN0.RMDF058.UINT16[H]
#define RSCAN0RMDF058HL RSCAN0.RMDF058.UINT8[HL]
#define RSCAN0RMDF058HH RSCAN0.RMDF058.UINT8[HH]
#define RSCAN0RMDF158 RSCAN0.RMDF158.UINT32
#define RSCAN0RMDF158L RSCAN0.RMDF158.UINT16[L]
#define RSCAN0RMDF158LL RSCAN0.RMDF158.UINT8[LL]
#define RSCAN0RMDF158LH RSCAN0.RMDF158.UINT8[LH]
#define RSCAN0RMDF158H RSCAN0.RMDF158.UINT16[H]
#define RSCAN0RMDF158HL RSCAN0.RMDF158.UINT8[HL]
#define RSCAN0RMDF158HH RSCAN0.RMDF158.UINT8[HH]
#define RSCAN0RMID59 RSCAN0.RMID59.UINT32
#define RSCAN0RMID59L RSCAN0.RMID59.UINT16[L]
#define RSCAN0RMID59LL RSCAN0.RMID59.UINT8[LL]
#define RSCAN0RMID59LH RSCAN0.RMID59.UINT8[LH]
#define RSCAN0RMID59H RSCAN0.RMID59.UINT16[H]
#define RSCAN0RMID59HL RSCAN0.RMID59.UINT8[HL]
#define RSCAN0RMID59HH RSCAN0.RMID59.UINT8[HH]
#define RSCAN0RMPTR59 RSCAN0.RMPTR59.UINT32
#define RSCAN0RMPTR59L RSCAN0.RMPTR59.UINT16[L]
#define RSCAN0RMPTR59LL RSCAN0.RMPTR59.UINT8[LL]
#define RSCAN0RMPTR59LH RSCAN0.RMPTR59.UINT8[LH]
#define RSCAN0RMPTR59H RSCAN0.RMPTR59.UINT16[H]
#define RSCAN0RMPTR59HL RSCAN0.RMPTR59.UINT8[HL]
#define RSCAN0RMPTR59HH RSCAN0.RMPTR59.UINT8[HH]
#define RSCAN0RMDF059 RSCAN0.RMDF059.UINT32
#define RSCAN0RMDF059L RSCAN0.RMDF059.UINT16[L]
#define RSCAN0RMDF059LL RSCAN0.RMDF059.UINT8[LL]
#define RSCAN0RMDF059LH RSCAN0.RMDF059.UINT8[LH]
#define RSCAN0RMDF059H RSCAN0.RMDF059.UINT16[H]
#define RSCAN0RMDF059HL RSCAN0.RMDF059.UINT8[HL]
#define RSCAN0RMDF059HH RSCAN0.RMDF059.UINT8[HH]
#define RSCAN0RMDF159 RSCAN0.RMDF159.UINT32
#define RSCAN0RMDF159L RSCAN0.RMDF159.UINT16[L]
#define RSCAN0RMDF159LL RSCAN0.RMDF159.UINT8[LL]
#define RSCAN0RMDF159LH RSCAN0.RMDF159.UINT8[LH]
#define RSCAN0RMDF159H RSCAN0.RMDF159.UINT16[H]
#define RSCAN0RMDF159HL RSCAN0.RMDF159.UINT8[HL]
#define RSCAN0RMDF159HH RSCAN0.RMDF159.UINT8[HH]
#define RSCAN0RMID60 RSCAN0.RMID60.UINT32
#define RSCAN0RMID60L RSCAN0.RMID60.UINT16[L]
#define RSCAN0RMID60LL RSCAN0.RMID60.UINT8[LL]
#define RSCAN0RMID60LH RSCAN0.RMID60.UINT8[LH]
#define RSCAN0RMID60H RSCAN0.RMID60.UINT16[H]
#define RSCAN0RMID60HL RSCAN0.RMID60.UINT8[HL]
#define RSCAN0RMID60HH RSCAN0.RMID60.UINT8[HH]
#define RSCAN0RMPTR60 RSCAN0.RMPTR60.UINT32
#define RSCAN0RMPTR60L RSCAN0.RMPTR60.UINT16[L]
#define RSCAN0RMPTR60LL RSCAN0.RMPTR60.UINT8[LL]
#define RSCAN0RMPTR60LH RSCAN0.RMPTR60.UINT8[LH]
#define RSCAN0RMPTR60H RSCAN0.RMPTR60.UINT16[H]
#define RSCAN0RMPTR60HL RSCAN0.RMPTR60.UINT8[HL]
#define RSCAN0RMPTR60HH RSCAN0.RMPTR60.UINT8[HH]
#define RSCAN0RMDF060 RSCAN0.RMDF060.UINT32
#define RSCAN0RMDF060L RSCAN0.RMDF060.UINT16[L]
#define RSCAN0RMDF060LL RSCAN0.RMDF060.UINT8[LL]
#define RSCAN0RMDF060LH RSCAN0.RMDF060.UINT8[LH]
#define RSCAN0RMDF060H RSCAN0.RMDF060.UINT16[H]
#define RSCAN0RMDF060HL RSCAN0.RMDF060.UINT8[HL]
#define RSCAN0RMDF060HH RSCAN0.RMDF060.UINT8[HH]
#define RSCAN0RMDF160 RSCAN0.RMDF160.UINT32
#define RSCAN0RMDF160L RSCAN0.RMDF160.UINT16[L]
#define RSCAN0RMDF160LL RSCAN0.RMDF160.UINT8[LL]
#define RSCAN0RMDF160LH RSCAN0.RMDF160.UINT8[LH]
#define RSCAN0RMDF160H RSCAN0.RMDF160.UINT16[H]
#define RSCAN0RMDF160HL RSCAN0.RMDF160.UINT8[HL]
#define RSCAN0RMDF160HH RSCAN0.RMDF160.UINT8[HH]
#define RSCAN0RMID61 RSCAN0.RMID61.UINT32
#define RSCAN0RMID61L RSCAN0.RMID61.UINT16[L]
#define RSCAN0RMID61LL RSCAN0.RMID61.UINT8[LL]
#define RSCAN0RMID61LH RSCAN0.RMID61.UINT8[LH]
#define RSCAN0RMID61H RSCAN0.RMID61.UINT16[H]
#define RSCAN0RMID61HL RSCAN0.RMID61.UINT8[HL]
#define RSCAN0RMID61HH RSCAN0.RMID61.UINT8[HH]
#define RSCAN0RMPTR61 RSCAN0.RMPTR61.UINT32
#define RSCAN0RMPTR61L RSCAN0.RMPTR61.UINT16[L]
#define RSCAN0RMPTR61LL RSCAN0.RMPTR61.UINT8[LL]
#define RSCAN0RMPTR61LH RSCAN0.RMPTR61.UINT8[LH]
#define RSCAN0RMPTR61H RSCAN0.RMPTR61.UINT16[H]
#define RSCAN0RMPTR61HL RSCAN0.RMPTR61.UINT8[HL]
#define RSCAN0RMPTR61HH RSCAN0.RMPTR61.UINT8[HH]
#define RSCAN0RMDF061 RSCAN0.RMDF061.UINT32
#define RSCAN0RMDF061L RSCAN0.RMDF061.UINT16[L]
#define RSCAN0RMDF061LL RSCAN0.RMDF061.UINT8[LL]
#define RSCAN0RMDF061LH RSCAN0.RMDF061.UINT8[LH]
#define RSCAN0RMDF061H RSCAN0.RMDF061.UINT16[H]
#define RSCAN0RMDF061HL RSCAN0.RMDF061.UINT8[HL]
#define RSCAN0RMDF061HH RSCAN0.RMDF061.UINT8[HH]
#define RSCAN0RMDF161 RSCAN0.RMDF161.UINT32
#define RSCAN0RMDF161L RSCAN0.RMDF161.UINT16[L]
#define RSCAN0RMDF161LL RSCAN0.RMDF161.UINT8[LL]
#define RSCAN0RMDF161LH RSCAN0.RMDF161.UINT8[LH]
#define RSCAN0RMDF161H RSCAN0.RMDF161.UINT16[H]
#define RSCAN0RMDF161HL RSCAN0.RMDF161.UINT8[HL]
#define RSCAN0RMDF161HH RSCAN0.RMDF161.UINT8[HH]
#define RSCAN0RMID62 RSCAN0.RMID62.UINT32
#define RSCAN0RMID62L RSCAN0.RMID62.UINT16[L]
#define RSCAN0RMID62LL RSCAN0.RMID62.UINT8[LL]
#define RSCAN0RMID62LH RSCAN0.RMID62.UINT8[LH]
#define RSCAN0RMID62H RSCAN0.RMID62.UINT16[H]
#define RSCAN0RMID62HL RSCAN0.RMID62.UINT8[HL]
#define RSCAN0RMID62HH RSCAN0.RMID62.UINT8[HH]
#define RSCAN0RMPTR62 RSCAN0.RMPTR62.UINT32
#define RSCAN0RMPTR62L RSCAN0.RMPTR62.UINT16[L]
#define RSCAN0RMPTR62LL RSCAN0.RMPTR62.UINT8[LL]
#define RSCAN0RMPTR62LH RSCAN0.RMPTR62.UINT8[LH]
#define RSCAN0RMPTR62H RSCAN0.RMPTR62.UINT16[H]
#define RSCAN0RMPTR62HL RSCAN0.RMPTR62.UINT8[HL]
#define RSCAN0RMPTR62HH RSCAN0.RMPTR62.UINT8[HH]
#define RSCAN0RMDF062 RSCAN0.RMDF062.UINT32
#define RSCAN0RMDF062L RSCAN0.RMDF062.UINT16[L]
#define RSCAN0RMDF062LL RSCAN0.RMDF062.UINT8[LL]
#define RSCAN0RMDF062LH RSCAN0.RMDF062.UINT8[LH]
#define RSCAN0RMDF062H RSCAN0.RMDF062.UINT16[H]
#define RSCAN0RMDF062HL RSCAN0.RMDF062.UINT8[HL]
#define RSCAN0RMDF062HH RSCAN0.RMDF062.UINT8[HH]
#define RSCAN0RMDF162 RSCAN0.RMDF162.UINT32
#define RSCAN0RMDF162L RSCAN0.RMDF162.UINT16[L]
#define RSCAN0RMDF162LL RSCAN0.RMDF162.UINT8[LL]
#define RSCAN0RMDF162LH RSCAN0.RMDF162.UINT8[LH]
#define RSCAN0RMDF162H RSCAN0.RMDF162.UINT16[H]
#define RSCAN0RMDF162HL RSCAN0.RMDF162.UINT8[HL]
#define RSCAN0RMDF162HH RSCAN0.RMDF162.UINT8[HH]
#define RSCAN0RMID63 RSCAN0.RMID63.UINT32
#define RSCAN0RMID63L RSCAN0.RMID63.UINT16[L]
#define RSCAN0RMID63LL RSCAN0.RMID63.UINT8[LL]
#define RSCAN0RMID63LH RSCAN0.RMID63.UINT8[LH]
#define RSCAN0RMID63H RSCAN0.RMID63.UINT16[H]
#define RSCAN0RMID63HL RSCAN0.RMID63.UINT8[HL]
#define RSCAN0RMID63HH RSCAN0.RMID63.UINT8[HH]
#define RSCAN0RMPTR63 RSCAN0.RMPTR63.UINT32
#define RSCAN0RMPTR63L RSCAN0.RMPTR63.UINT16[L]
#define RSCAN0RMPTR63LL RSCAN0.RMPTR63.UINT8[LL]
#define RSCAN0RMPTR63LH RSCAN0.RMPTR63.UINT8[LH]
#define RSCAN0RMPTR63H RSCAN0.RMPTR63.UINT16[H]
#define RSCAN0RMPTR63HL RSCAN0.RMPTR63.UINT8[HL]
#define RSCAN0RMPTR63HH RSCAN0.RMPTR63.UINT8[HH]
#define RSCAN0RMDF063 RSCAN0.RMDF063.UINT32
#define RSCAN0RMDF063L RSCAN0.RMDF063.UINT16[L]
#define RSCAN0RMDF063LL RSCAN0.RMDF063.UINT8[LL]
#define RSCAN0RMDF063LH RSCAN0.RMDF063.UINT8[LH]
#define RSCAN0RMDF063H RSCAN0.RMDF063.UINT16[H]
#define RSCAN0RMDF063HL RSCAN0.RMDF063.UINT8[HL]
#define RSCAN0RMDF063HH RSCAN0.RMDF063.UINT8[HH]
#define RSCAN0RMDF163 RSCAN0.RMDF163.UINT32
#define RSCAN0RMDF163L RSCAN0.RMDF163.UINT16[L]
#define RSCAN0RMDF163LL RSCAN0.RMDF163.UINT8[LL]
#define RSCAN0RMDF163LH RSCAN0.RMDF163.UINT8[LH]
#define RSCAN0RMDF163H RSCAN0.RMDF163.UINT16[H]
#define RSCAN0RMDF163HL RSCAN0.RMDF163.UINT8[HL]
#define RSCAN0RMDF163HH RSCAN0.RMDF163.UINT8[HH]
#define RSCAN0RMID64 RSCAN0.RMID64.UINT32
#define RSCAN0RMID64L RSCAN0.RMID64.UINT16[L]
#define RSCAN0RMID64LL RSCAN0.RMID64.UINT8[LL]
#define RSCAN0RMID64LH RSCAN0.RMID64.UINT8[LH]
#define RSCAN0RMID64H RSCAN0.RMID64.UINT16[H]
#define RSCAN0RMID64HL RSCAN0.RMID64.UINT8[HL]
#define RSCAN0RMID64HH RSCAN0.RMID64.UINT8[HH]
#define RSCAN0RMPTR64 RSCAN0.RMPTR64.UINT32
#define RSCAN0RMPTR64L RSCAN0.RMPTR64.UINT16[L]
#define RSCAN0RMPTR64LL RSCAN0.RMPTR64.UINT8[LL]
#define RSCAN0RMPTR64LH RSCAN0.RMPTR64.UINT8[LH]
#define RSCAN0RMPTR64H RSCAN0.RMPTR64.UINT16[H]
#define RSCAN0RMPTR64HL RSCAN0.RMPTR64.UINT8[HL]
#define RSCAN0RMPTR64HH RSCAN0.RMPTR64.UINT8[HH]
#define RSCAN0RMDF064 RSCAN0.RMDF064.UINT32
#define RSCAN0RMDF064L RSCAN0.RMDF064.UINT16[L]
#define RSCAN0RMDF064LL RSCAN0.RMDF064.UINT8[LL]
#define RSCAN0RMDF064LH RSCAN0.RMDF064.UINT8[LH]
#define RSCAN0RMDF064H RSCAN0.RMDF064.UINT16[H]
#define RSCAN0RMDF064HL RSCAN0.RMDF064.UINT8[HL]
#define RSCAN0RMDF064HH RSCAN0.RMDF064.UINT8[HH]
#define RSCAN0RMDF164 RSCAN0.RMDF164.UINT32
#define RSCAN0RMDF164L RSCAN0.RMDF164.UINT16[L]
#define RSCAN0RMDF164LL RSCAN0.RMDF164.UINT8[LL]
#define RSCAN0RMDF164LH RSCAN0.RMDF164.UINT8[LH]
#define RSCAN0RMDF164H RSCAN0.RMDF164.UINT16[H]
#define RSCAN0RMDF164HL RSCAN0.RMDF164.UINT8[HL]
#define RSCAN0RMDF164HH RSCAN0.RMDF164.UINT8[HH]
#define RSCAN0RMID65 RSCAN0.RMID65.UINT32
#define RSCAN0RMID65L RSCAN0.RMID65.UINT16[L]
#define RSCAN0RMID65LL RSCAN0.RMID65.UINT8[LL]
#define RSCAN0RMID65LH RSCAN0.RMID65.UINT8[LH]
#define RSCAN0RMID65H RSCAN0.RMID65.UINT16[H]
#define RSCAN0RMID65HL RSCAN0.RMID65.UINT8[HL]
#define RSCAN0RMID65HH RSCAN0.RMID65.UINT8[HH]
#define RSCAN0RMPTR65 RSCAN0.RMPTR65.UINT32
#define RSCAN0RMPTR65L RSCAN0.RMPTR65.UINT16[L]
#define RSCAN0RMPTR65LL RSCAN0.RMPTR65.UINT8[LL]
#define RSCAN0RMPTR65LH RSCAN0.RMPTR65.UINT8[LH]
#define RSCAN0RMPTR65H RSCAN0.RMPTR65.UINT16[H]
#define RSCAN0RMPTR65HL RSCAN0.RMPTR65.UINT8[HL]
#define RSCAN0RMPTR65HH RSCAN0.RMPTR65.UINT8[HH]
#define RSCAN0RMDF065 RSCAN0.RMDF065.UINT32
#define RSCAN0RMDF065L RSCAN0.RMDF065.UINT16[L]
#define RSCAN0RMDF065LL RSCAN0.RMDF065.UINT8[LL]
#define RSCAN0RMDF065LH RSCAN0.RMDF065.UINT8[LH]
#define RSCAN0RMDF065H RSCAN0.RMDF065.UINT16[H]
#define RSCAN0RMDF065HL RSCAN0.RMDF065.UINT8[HL]
#define RSCAN0RMDF065HH RSCAN0.RMDF065.UINT8[HH]
#define RSCAN0RMDF165 RSCAN0.RMDF165.UINT32
#define RSCAN0RMDF165L RSCAN0.RMDF165.UINT16[L]
#define RSCAN0RMDF165LL RSCAN0.RMDF165.UINT8[LL]
#define RSCAN0RMDF165LH RSCAN0.RMDF165.UINT8[LH]
#define RSCAN0RMDF165H RSCAN0.RMDF165.UINT16[H]
#define RSCAN0RMDF165HL RSCAN0.RMDF165.UINT8[HL]
#define RSCAN0RMDF165HH RSCAN0.RMDF165.UINT8[HH]
#define RSCAN0RMID66 RSCAN0.RMID66.UINT32
#define RSCAN0RMID66L RSCAN0.RMID66.UINT16[L]
#define RSCAN0RMID66LL RSCAN0.RMID66.UINT8[LL]
#define RSCAN0RMID66LH RSCAN0.RMID66.UINT8[LH]
#define RSCAN0RMID66H RSCAN0.RMID66.UINT16[H]
#define RSCAN0RMID66HL RSCAN0.RMID66.UINT8[HL]
#define RSCAN0RMID66HH RSCAN0.RMID66.UINT8[HH]
#define RSCAN0RMPTR66 RSCAN0.RMPTR66.UINT32
#define RSCAN0RMPTR66L RSCAN0.RMPTR66.UINT16[L]
#define RSCAN0RMPTR66LL RSCAN0.RMPTR66.UINT8[LL]
#define RSCAN0RMPTR66LH RSCAN0.RMPTR66.UINT8[LH]
#define RSCAN0RMPTR66H RSCAN0.RMPTR66.UINT16[H]
#define RSCAN0RMPTR66HL RSCAN0.RMPTR66.UINT8[HL]
#define RSCAN0RMPTR66HH RSCAN0.RMPTR66.UINT8[HH]
#define RSCAN0RMDF066 RSCAN0.RMDF066.UINT32
#define RSCAN0RMDF066L RSCAN0.RMDF066.UINT16[L]
#define RSCAN0RMDF066LL RSCAN0.RMDF066.UINT8[LL]
#define RSCAN0RMDF066LH RSCAN0.RMDF066.UINT8[LH]
#define RSCAN0RMDF066H RSCAN0.RMDF066.UINT16[H]
#define RSCAN0RMDF066HL RSCAN0.RMDF066.UINT8[HL]
#define RSCAN0RMDF066HH RSCAN0.RMDF066.UINT8[HH]
#define RSCAN0RMDF166 RSCAN0.RMDF166.UINT32
#define RSCAN0RMDF166L RSCAN0.RMDF166.UINT16[L]
#define RSCAN0RMDF166LL RSCAN0.RMDF166.UINT8[LL]
#define RSCAN0RMDF166LH RSCAN0.RMDF166.UINT8[LH]
#define RSCAN0RMDF166H RSCAN0.RMDF166.UINT16[H]
#define RSCAN0RMDF166HL RSCAN0.RMDF166.UINT8[HL]
#define RSCAN0RMDF166HH RSCAN0.RMDF166.UINT8[HH]
#define RSCAN0RMID67 RSCAN0.RMID67.UINT32
#define RSCAN0RMID67L RSCAN0.RMID67.UINT16[L]
#define RSCAN0RMID67LL RSCAN0.RMID67.UINT8[LL]
#define RSCAN0RMID67LH RSCAN0.RMID67.UINT8[LH]
#define RSCAN0RMID67H RSCAN0.RMID67.UINT16[H]
#define RSCAN0RMID67HL RSCAN0.RMID67.UINT8[HL]
#define RSCAN0RMID67HH RSCAN0.RMID67.UINT8[HH]
#define RSCAN0RMPTR67 RSCAN0.RMPTR67.UINT32
#define RSCAN0RMPTR67L RSCAN0.RMPTR67.UINT16[L]
#define RSCAN0RMPTR67LL RSCAN0.RMPTR67.UINT8[LL]
#define RSCAN0RMPTR67LH RSCAN0.RMPTR67.UINT8[LH]
#define RSCAN0RMPTR67H RSCAN0.RMPTR67.UINT16[H]
#define RSCAN0RMPTR67HL RSCAN0.RMPTR67.UINT8[HL]
#define RSCAN0RMPTR67HH RSCAN0.RMPTR67.UINT8[HH]
#define RSCAN0RMDF067 RSCAN0.RMDF067.UINT32
#define RSCAN0RMDF067L RSCAN0.RMDF067.UINT16[L]
#define RSCAN0RMDF067LL RSCAN0.RMDF067.UINT8[LL]
#define RSCAN0RMDF067LH RSCAN0.RMDF067.UINT8[LH]
#define RSCAN0RMDF067H RSCAN0.RMDF067.UINT16[H]
#define RSCAN0RMDF067HL RSCAN0.RMDF067.UINT8[HL]
#define RSCAN0RMDF067HH RSCAN0.RMDF067.UINT8[HH]
#define RSCAN0RMDF167 RSCAN0.RMDF167.UINT32
#define RSCAN0RMDF167L RSCAN0.RMDF167.UINT16[L]
#define RSCAN0RMDF167LL RSCAN0.RMDF167.UINT8[LL]
#define RSCAN0RMDF167LH RSCAN0.RMDF167.UINT8[LH]
#define RSCAN0RMDF167H RSCAN0.RMDF167.UINT16[H]
#define RSCAN0RMDF167HL RSCAN0.RMDF167.UINT8[HL]
#define RSCAN0RMDF167HH RSCAN0.RMDF167.UINT8[HH]
#define RSCAN0RMID68 RSCAN0.RMID68.UINT32
#define RSCAN0RMID68L RSCAN0.RMID68.UINT16[L]
#define RSCAN0RMID68LL RSCAN0.RMID68.UINT8[LL]
#define RSCAN0RMID68LH RSCAN0.RMID68.UINT8[LH]
#define RSCAN0RMID68H RSCAN0.RMID68.UINT16[H]
#define RSCAN0RMID68HL RSCAN0.RMID68.UINT8[HL]
#define RSCAN0RMID68HH RSCAN0.RMID68.UINT8[HH]
#define RSCAN0RMPTR68 RSCAN0.RMPTR68.UINT32
#define RSCAN0RMPTR68L RSCAN0.RMPTR68.UINT16[L]
#define RSCAN0RMPTR68LL RSCAN0.RMPTR68.UINT8[LL]
#define RSCAN0RMPTR68LH RSCAN0.RMPTR68.UINT8[LH]
#define RSCAN0RMPTR68H RSCAN0.RMPTR68.UINT16[H]
#define RSCAN0RMPTR68HL RSCAN0.RMPTR68.UINT8[HL]
#define RSCAN0RMPTR68HH RSCAN0.RMPTR68.UINT8[HH]
#define RSCAN0RMDF068 RSCAN0.RMDF068.UINT32
#define RSCAN0RMDF068L RSCAN0.RMDF068.UINT16[L]
#define RSCAN0RMDF068LL RSCAN0.RMDF068.UINT8[LL]
#define RSCAN0RMDF068LH RSCAN0.RMDF068.UINT8[LH]
#define RSCAN0RMDF068H RSCAN0.RMDF068.UINT16[H]
#define RSCAN0RMDF068HL RSCAN0.RMDF068.UINT8[HL]
#define RSCAN0RMDF068HH RSCAN0.RMDF068.UINT8[HH]
#define RSCAN0RMDF168 RSCAN0.RMDF168.UINT32
#define RSCAN0RMDF168L RSCAN0.RMDF168.UINT16[L]
#define RSCAN0RMDF168LL RSCAN0.RMDF168.UINT8[LL]
#define RSCAN0RMDF168LH RSCAN0.RMDF168.UINT8[LH]
#define RSCAN0RMDF168H RSCAN0.RMDF168.UINT16[H]
#define RSCAN0RMDF168HL RSCAN0.RMDF168.UINT8[HL]
#define RSCAN0RMDF168HH RSCAN0.RMDF168.UINT8[HH]
#define RSCAN0RMID69 RSCAN0.RMID69.UINT32
#define RSCAN0RMID69L RSCAN0.RMID69.UINT16[L]
#define RSCAN0RMID69LL RSCAN0.RMID69.UINT8[LL]
#define RSCAN0RMID69LH RSCAN0.RMID69.UINT8[LH]
#define RSCAN0RMID69H RSCAN0.RMID69.UINT16[H]
#define RSCAN0RMID69HL RSCAN0.RMID69.UINT8[HL]
#define RSCAN0RMID69HH RSCAN0.RMID69.UINT8[HH]
#define RSCAN0RMPTR69 RSCAN0.RMPTR69.UINT32
#define RSCAN0RMPTR69L RSCAN0.RMPTR69.UINT16[L]
#define RSCAN0RMPTR69LL RSCAN0.RMPTR69.UINT8[LL]
#define RSCAN0RMPTR69LH RSCAN0.RMPTR69.UINT8[LH]
#define RSCAN0RMPTR69H RSCAN0.RMPTR69.UINT16[H]
#define RSCAN0RMPTR69HL RSCAN0.RMPTR69.UINT8[HL]
#define RSCAN0RMPTR69HH RSCAN0.RMPTR69.UINT8[HH]
#define RSCAN0RMDF069 RSCAN0.RMDF069.UINT32
#define RSCAN0RMDF069L RSCAN0.RMDF069.UINT16[L]
#define RSCAN0RMDF069LL RSCAN0.RMDF069.UINT8[LL]
#define RSCAN0RMDF069LH RSCAN0.RMDF069.UINT8[LH]
#define RSCAN0RMDF069H RSCAN0.RMDF069.UINT16[H]
#define RSCAN0RMDF069HL RSCAN0.RMDF069.UINT8[HL]
#define RSCAN0RMDF069HH RSCAN0.RMDF069.UINT8[HH]
#define RSCAN0RMDF169 RSCAN0.RMDF169.UINT32
#define RSCAN0RMDF169L RSCAN0.RMDF169.UINT16[L]
#define RSCAN0RMDF169LL RSCAN0.RMDF169.UINT8[LL]
#define RSCAN0RMDF169LH RSCAN0.RMDF169.UINT8[LH]
#define RSCAN0RMDF169H RSCAN0.RMDF169.UINT16[H]
#define RSCAN0RMDF169HL RSCAN0.RMDF169.UINT8[HL]
#define RSCAN0RMDF169HH RSCAN0.RMDF169.UINT8[HH]
#define RSCAN0RMID70 RSCAN0.RMID70.UINT32
#define RSCAN0RMID70L RSCAN0.RMID70.UINT16[L]
#define RSCAN0RMID70LL RSCAN0.RMID70.UINT8[LL]
#define RSCAN0RMID70LH RSCAN0.RMID70.UINT8[LH]
#define RSCAN0RMID70H RSCAN0.RMID70.UINT16[H]
#define RSCAN0RMID70HL RSCAN0.RMID70.UINT8[HL]
#define RSCAN0RMID70HH RSCAN0.RMID70.UINT8[HH]
#define RSCAN0RMPTR70 RSCAN0.RMPTR70.UINT32
#define RSCAN0RMPTR70L RSCAN0.RMPTR70.UINT16[L]
#define RSCAN0RMPTR70LL RSCAN0.RMPTR70.UINT8[LL]
#define RSCAN0RMPTR70LH RSCAN0.RMPTR70.UINT8[LH]
#define RSCAN0RMPTR70H RSCAN0.RMPTR70.UINT16[H]
#define RSCAN0RMPTR70HL RSCAN0.RMPTR70.UINT8[HL]
#define RSCAN0RMPTR70HH RSCAN0.RMPTR70.UINT8[HH]
#define RSCAN0RMDF070 RSCAN0.RMDF070.UINT32
#define RSCAN0RMDF070L RSCAN0.RMDF070.UINT16[L]
#define RSCAN0RMDF070LL RSCAN0.RMDF070.UINT8[LL]
#define RSCAN0RMDF070LH RSCAN0.RMDF070.UINT8[LH]
#define RSCAN0RMDF070H RSCAN0.RMDF070.UINT16[H]
#define RSCAN0RMDF070HL RSCAN0.RMDF070.UINT8[HL]
#define RSCAN0RMDF070HH RSCAN0.RMDF070.UINT8[HH]
#define RSCAN0RMDF170 RSCAN0.RMDF170.UINT32
#define RSCAN0RMDF170L RSCAN0.RMDF170.UINT16[L]
#define RSCAN0RMDF170LL RSCAN0.RMDF170.UINT8[LL]
#define RSCAN0RMDF170LH RSCAN0.RMDF170.UINT8[LH]
#define RSCAN0RMDF170H RSCAN0.RMDF170.UINT16[H]
#define RSCAN0RMDF170HL RSCAN0.RMDF170.UINT8[HL]
#define RSCAN0RMDF170HH RSCAN0.RMDF170.UINT8[HH]
#define RSCAN0RMID71 RSCAN0.RMID71.UINT32
#define RSCAN0RMID71L RSCAN0.RMID71.UINT16[L]
#define RSCAN0RMID71LL RSCAN0.RMID71.UINT8[LL]
#define RSCAN0RMID71LH RSCAN0.RMID71.UINT8[LH]
#define RSCAN0RMID71H RSCAN0.RMID71.UINT16[H]
#define RSCAN0RMID71HL RSCAN0.RMID71.UINT8[HL]
#define RSCAN0RMID71HH RSCAN0.RMID71.UINT8[HH]
#define RSCAN0RMPTR71 RSCAN0.RMPTR71.UINT32
#define RSCAN0RMPTR71L RSCAN0.RMPTR71.UINT16[L]
#define RSCAN0RMPTR71LL RSCAN0.RMPTR71.UINT8[LL]
#define RSCAN0RMPTR71LH RSCAN0.RMPTR71.UINT8[LH]
#define RSCAN0RMPTR71H RSCAN0.RMPTR71.UINT16[H]
#define RSCAN0RMPTR71HL RSCAN0.RMPTR71.UINT8[HL]
#define RSCAN0RMPTR71HH RSCAN0.RMPTR71.UINT8[HH]
#define RSCAN0RMDF071 RSCAN0.RMDF071.UINT32
#define RSCAN0RMDF071L RSCAN0.RMDF071.UINT16[L]
#define RSCAN0RMDF071LL RSCAN0.RMDF071.UINT8[LL]
#define RSCAN0RMDF071LH RSCAN0.RMDF071.UINT8[LH]
#define RSCAN0RMDF071H RSCAN0.RMDF071.UINT16[H]
#define RSCAN0RMDF071HL RSCAN0.RMDF071.UINT8[HL]
#define RSCAN0RMDF071HH RSCAN0.RMDF071.UINT8[HH]
#define RSCAN0RMDF171 RSCAN0.RMDF171.UINT32
#define RSCAN0RMDF171L RSCAN0.RMDF171.UINT16[L]
#define RSCAN0RMDF171LL RSCAN0.RMDF171.UINT8[LL]
#define RSCAN0RMDF171LH RSCAN0.RMDF171.UINT8[LH]
#define RSCAN0RMDF171H RSCAN0.RMDF171.UINT16[H]
#define RSCAN0RMDF171HL RSCAN0.RMDF171.UINT8[HL]
#define RSCAN0RMDF171HH RSCAN0.RMDF171.UINT8[HH]
#define RSCAN0RMID72 RSCAN0.RMID72.UINT32
#define RSCAN0RMID72L RSCAN0.RMID72.UINT16[L]
#define RSCAN0RMID72LL RSCAN0.RMID72.UINT8[LL]
#define RSCAN0RMID72LH RSCAN0.RMID72.UINT8[LH]
#define RSCAN0RMID72H RSCAN0.RMID72.UINT16[H]
#define RSCAN0RMID72HL RSCAN0.RMID72.UINT8[HL]
#define RSCAN0RMID72HH RSCAN0.RMID72.UINT8[HH]
#define RSCAN0RMPTR72 RSCAN0.RMPTR72.UINT32
#define RSCAN0RMPTR72L RSCAN0.RMPTR72.UINT16[L]
#define RSCAN0RMPTR72LL RSCAN0.RMPTR72.UINT8[LL]
#define RSCAN0RMPTR72LH RSCAN0.RMPTR72.UINT8[LH]
#define RSCAN0RMPTR72H RSCAN0.RMPTR72.UINT16[H]
#define RSCAN0RMPTR72HL RSCAN0.RMPTR72.UINT8[HL]
#define RSCAN0RMPTR72HH RSCAN0.RMPTR72.UINT8[HH]
#define RSCAN0RMDF072 RSCAN0.RMDF072.UINT32
#define RSCAN0RMDF072L RSCAN0.RMDF072.UINT16[L]
#define RSCAN0RMDF072LL RSCAN0.RMDF072.UINT8[LL]
#define RSCAN0RMDF072LH RSCAN0.RMDF072.UINT8[LH]
#define RSCAN0RMDF072H RSCAN0.RMDF072.UINT16[H]
#define RSCAN0RMDF072HL RSCAN0.RMDF072.UINT8[HL]
#define RSCAN0RMDF072HH RSCAN0.RMDF072.UINT8[HH]
#define RSCAN0RMDF172 RSCAN0.RMDF172.UINT32
#define RSCAN0RMDF172L RSCAN0.RMDF172.UINT16[L]
#define RSCAN0RMDF172LL RSCAN0.RMDF172.UINT8[LL]
#define RSCAN0RMDF172LH RSCAN0.RMDF172.UINT8[LH]
#define RSCAN0RMDF172H RSCAN0.RMDF172.UINT16[H]
#define RSCAN0RMDF172HL RSCAN0.RMDF172.UINT8[HL]
#define RSCAN0RMDF172HH RSCAN0.RMDF172.UINT8[HH]
#define RSCAN0RMID73 RSCAN0.RMID73.UINT32
#define RSCAN0RMID73L RSCAN0.RMID73.UINT16[L]
#define RSCAN0RMID73LL RSCAN0.RMID73.UINT8[LL]
#define RSCAN0RMID73LH RSCAN0.RMID73.UINT8[LH]
#define RSCAN0RMID73H RSCAN0.RMID73.UINT16[H]
#define RSCAN0RMID73HL RSCAN0.RMID73.UINT8[HL]
#define RSCAN0RMID73HH RSCAN0.RMID73.UINT8[HH]
#define RSCAN0RMPTR73 RSCAN0.RMPTR73.UINT32
#define RSCAN0RMPTR73L RSCAN0.RMPTR73.UINT16[L]
#define RSCAN0RMPTR73LL RSCAN0.RMPTR73.UINT8[LL]
#define RSCAN0RMPTR73LH RSCAN0.RMPTR73.UINT8[LH]
#define RSCAN0RMPTR73H RSCAN0.RMPTR73.UINT16[H]
#define RSCAN0RMPTR73HL RSCAN0.RMPTR73.UINT8[HL]
#define RSCAN0RMPTR73HH RSCAN0.RMPTR73.UINT8[HH]
#define RSCAN0RMDF073 RSCAN0.RMDF073.UINT32
#define RSCAN0RMDF073L RSCAN0.RMDF073.UINT16[L]
#define RSCAN0RMDF073LL RSCAN0.RMDF073.UINT8[LL]
#define RSCAN0RMDF073LH RSCAN0.RMDF073.UINT8[LH]
#define RSCAN0RMDF073H RSCAN0.RMDF073.UINT16[H]
#define RSCAN0RMDF073HL RSCAN0.RMDF073.UINT8[HL]
#define RSCAN0RMDF073HH RSCAN0.RMDF073.UINT8[HH]
#define RSCAN0RMDF173 RSCAN0.RMDF173.UINT32
#define RSCAN0RMDF173L RSCAN0.RMDF173.UINT16[L]
#define RSCAN0RMDF173LL RSCAN0.RMDF173.UINT8[LL]
#define RSCAN0RMDF173LH RSCAN0.RMDF173.UINT8[LH]
#define RSCAN0RMDF173H RSCAN0.RMDF173.UINT16[H]
#define RSCAN0RMDF173HL RSCAN0.RMDF173.UINT8[HL]
#define RSCAN0RMDF173HH RSCAN0.RMDF173.UINT8[HH]
#define RSCAN0RMID74 RSCAN0.RMID74.UINT32
#define RSCAN0RMID74L RSCAN0.RMID74.UINT16[L]
#define RSCAN0RMID74LL RSCAN0.RMID74.UINT8[LL]
#define RSCAN0RMID74LH RSCAN0.RMID74.UINT8[LH]
#define RSCAN0RMID74H RSCAN0.RMID74.UINT16[H]
#define RSCAN0RMID74HL RSCAN0.RMID74.UINT8[HL]
#define RSCAN0RMID74HH RSCAN0.RMID74.UINT8[HH]
#define RSCAN0RMPTR74 RSCAN0.RMPTR74.UINT32
#define RSCAN0RMPTR74L RSCAN0.RMPTR74.UINT16[L]
#define RSCAN0RMPTR74LL RSCAN0.RMPTR74.UINT8[LL]
#define RSCAN0RMPTR74LH RSCAN0.RMPTR74.UINT8[LH]
#define RSCAN0RMPTR74H RSCAN0.RMPTR74.UINT16[H]
#define RSCAN0RMPTR74HL RSCAN0.RMPTR74.UINT8[HL]
#define RSCAN0RMPTR74HH RSCAN0.RMPTR74.UINT8[HH]
#define RSCAN0RMDF074 RSCAN0.RMDF074.UINT32
#define RSCAN0RMDF074L RSCAN0.RMDF074.UINT16[L]
#define RSCAN0RMDF074LL RSCAN0.RMDF074.UINT8[LL]
#define RSCAN0RMDF074LH RSCAN0.RMDF074.UINT8[LH]
#define RSCAN0RMDF074H RSCAN0.RMDF074.UINT16[H]
#define RSCAN0RMDF074HL RSCAN0.RMDF074.UINT8[HL]
#define RSCAN0RMDF074HH RSCAN0.RMDF074.UINT8[HH]
#define RSCAN0RMDF174 RSCAN0.RMDF174.UINT32
#define RSCAN0RMDF174L RSCAN0.RMDF174.UINT16[L]
#define RSCAN0RMDF174LL RSCAN0.RMDF174.UINT8[LL]
#define RSCAN0RMDF174LH RSCAN0.RMDF174.UINT8[LH]
#define RSCAN0RMDF174H RSCAN0.RMDF174.UINT16[H]
#define RSCAN0RMDF174HL RSCAN0.RMDF174.UINT8[HL]
#define RSCAN0RMDF174HH RSCAN0.RMDF174.UINT8[HH]
#define RSCAN0RMID75 RSCAN0.RMID75.UINT32
#define RSCAN0RMID75L RSCAN0.RMID75.UINT16[L]
#define RSCAN0RMID75LL RSCAN0.RMID75.UINT8[LL]
#define RSCAN0RMID75LH RSCAN0.RMID75.UINT8[LH]
#define RSCAN0RMID75H RSCAN0.RMID75.UINT16[H]
#define RSCAN0RMID75HL RSCAN0.RMID75.UINT8[HL]
#define RSCAN0RMID75HH RSCAN0.RMID75.UINT8[HH]
#define RSCAN0RMPTR75 RSCAN0.RMPTR75.UINT32
#define RSCAN0RMPTR75L RSCAN0.RMPTR75.UINT16[L]
#define RSCAN0RMPTR75LL RSCAN0.RMPTR75.UINT8[LL]
#define RSCAN0RMPTR75LH RSCAN0.RMPTR75.UINT8[LH]
#define RSCAN0RMPTR75H RSCAN0.RMPTR75.UINT16[H]
#define RSCAN0RMPTR75HL RSCAN0.RMPTR75.UINT8[HL]
#define RSCAN0RMPTR75HH RSCAN0.RMPTR75.UINT8[HH]
#define RSCAN0RMDF075 RSCAN0.RMDF075.UINT32
#define RSCAN0RMDF075L RSCAN0.RMDF075.UINT16[L]
#define RSCAN0RMDF075LL RSCAN0.RMDF075.UINT8[LL]
#define RSCAN0RMDF075LH RSCAN0.RMDF075.UINT8[LH]
#define RSCAN0RMDF075H RSCAN0.RMDF075.UINT16[H]
#define RSCAN0RMDF075HL RSCAN0.RMDF075.UINT8[HL]
#define RSCAN0RMDF075HH RSCAN0.RMDF075.UINT8[HH]
#define RSCAN0RMDF175 RSCAN0.RMDF175.UINT32
#define RSCAN0RMDF175L RSCAN0.RMDF175.UINT16[L]
#define RSCAN0RMDF175LL RSCAN0.RMDF175.UINT8[LL]
#define RSCAN0RMDF175LH RSCAN0.RMDF175.UINT8[LH]
#define RSCAN0RMDF175H RSCAN0.RMDF175.UINT16[H]
#define RSCAN0RMDF175HL RSCAN0.RMDF175.UINT8[HL]
#define RSCAN0RMDF175HH RSCAN0.RMDF175.UINT8[HH]
#define RSCAN0RMID76 RSCAN0.RMID76.UINT32
#define RSCAN0RMID76L RSCAN0.RMID76.UINT16[L]
#define RSCAN0RMID76LL RSCAN0.RMID76.UINT8[LL]
#define RSCAN0RMID76LH RSCAN0.RMID76.UINT8[LH]
#define RSCAN0RMID76H RSCAN0.RMID76.UINT16[H]
#define RSCAN0RMID76HL RSCAN0.RMID76.UINT8[HL]
#define RSCAN0RMID76HH RSCAN0.RMID76.UINT8[HH]
#define RSCAN0RMPTR76 RSCAN0.RMPTR76.UINT32
#define RSCAN0RMPTR76L RSCAN0.RMPTR76.UINT16[L]
#define RSCAN0RMPTR76LL RSCAN0.RMPTR76.UINT8[LL]
#define RSCAN0RMPTR76LH RSCAN0.RMPTR76.UINT8[LH]
#define RSCAN0RMPTR76H RSCAN0.RMPTR76.UINT16[H]
#define RSCAN0RMPTR76HL RSCAN0.RMPTR76.UINT8[HL]
#define RSCAN0RMPTR76HH RSCAN0.RMPTR76.UINT8[HH]
#define RSCAN0RMDF076 RSCAN0.RMDF076.UINT32
#define RSCAN0RMDF076L RSCAN0.RMDF076.UINT16[L]
#define RSCAN0RMDF076LL RSCAN0.RMDF076.UINT8[LL]
#define RSCAN0RMDF076LH RSCAN0.RMDF076.UINT8[LH]
#define RSCAN0RMDF076H RSCAN0.RMDF076.UINT16[H]
#define RSCAN0RMDF076HL RSCAN0.RMDF076.UINT8[HL]
#define RSCAN0RMDF076HH RSCAN0.RMDF076.UINT8[HH]
#define RSCAN0RMDF176 RSCAN0.RMDF176.UINT32
#define RSCAN0RMDF176L RSCAN0.RMDF176.UINT16[L]
#define RSCAN0RMDF176LL RSCAN0.RMDF176.UINT8[LL]
#define RSCAN0RMDF176LH RSCAN0.RMDF176.UINT8[LH]
#define RSCAN0RMDF176H RSCAN0.RMDF176.UINT16[H]
#define RSCAN0RMDF176HL RSCAN0.RMDF176.UINT8[HL]
#define RSCAN0RMDF176HH RSCAN0.RMDF176.UINT8[HH]
#define RSCAN0RMID77 RSCAN0.RMID77.UINT32
#define RSCAN0RMID77L RSCAN0.RMID77.UINT16[L]
#define RSCAN0RMID77LL RSCAN0.RMID77.UINT8[LL]
#define RSCAN0RMID77LH RSCAN0.RMID77.UINT8[LH]
#define RSCAN0RMID77H RSCAN0.RMID77.UINT16[H]
#define RSCAN0RMID77HL RSCAN0.RMID77.UINT8[HL]
#define RSCAN0RMID77HH RSCAN0.RMID77.UINT8[HH]
#define RSCAN0RMPTR77 RSCAN0.RMPTR77.UINT32
#define RSCAN0RMPTR77L RSCAN0.RMPTR77.UINT16[L]
#define RSCAN0RMPTR77LL RSCAN0.RMPTR77.UINT8[LL]
#define RSCAN0RMPTR77LH RSCAN0.RMPTR77.UINT8[LH]
#define RSCAN0RMPTR77H RSCAN0.RMPTR77.UINT16[H]
#define RSCAN0RMPTR77HL RSCAN0.RMPTR77.UINT8[HL]
#define RSCAN0RMPTR77HH RSCAN0.RMPTR77.UINT8[HH]
#define RSCAN0RMDF077 RSCAN0.RMDF077.UINT32
#define RSCAN0RMDF077L RSCAN0.RMDF077.UINT16[L]
#define RSCAN0RMDF077LL RSCAN0.RMDF077.UINT8[LL]
#define RSCAN0RMDF077LH RSCAN0.RMDF077.UINT8[LH]
#define RSCAN0RMDF077H RSCAN0.RMDF077.UINT16[H]
#define RSCAN0RMDF077HL RSCAN0.RMDF077.UINT8[HL]
#define RSCAN0RMDF077HH RSCAN0.RMDF077.UINT8[HH]
#define RSCAN0RMDF177 RSCAN0.RMDF177.UINT32
#define RSCAN0RMDF177L RSCAN0.RMDF177.UINT16[L]
#define RSCAN0RMDF177LL RSCAN0.RMDF177.UINT8[LL]
#define RSCAN0RMDF177LH RSCAN0.RMDF177.UINT8[LH]
#define RSCAN0RMDF177H RSCAN0.RMDF177.UINT16[H]
#define RSCAN0RMDF177HL RSCAN0.RMDF177.UINT8[HL]
#define RSCAN0RMDF177HH RSCAN0.RMDF177.UINT8[HH]
#define RSCAN0RMID78 RSCAN0.RMID78.UINT32
#define RSCAN0RMID78L RSCAN0.RMID78.UINT16[L]
#define RSCAN0RMID78LL RSCAN0.RMID78.UINT8[LL]
#define RSCAN0RMID78LH RSCAN0.RMID78.UINT8[LH]
#define RSCAN0RMID78H RSCAN0.RMID78.UINT16[H]
#define RSCAN0RMID78HL RSCAN0.RMID78.UINT8[HL]
#define RSCAN0RMID78HH RSCAN0.RMID78.UINT8[HH]
#define RSCAN0RMPTR78 RSCAN0.RMPTR78.UINT32
#define RSCAN0RMPTR78L RSCAN0.RMPTR78.UINT16[L]
#define RSCAN0RMPTR78LL RSCAN0.RMPTR78.UINT8[LL]
#define RSCAN0RMPTR78LH RSCAN0.RMPTR78.UINT8[LH]
#define RSCAN0RMPTR78H RSCAN0.RMPTR78.UINT16[H]
#define RSCAN0RMPTR78HL RSCAN0.RMPTR78.UINT8[HL]
#define RSCAN0RMPTR78HH RSCAN0.RMPTR78.UINT8[HH]
#define RSCAN0RMDF078 RSCAN0.RMDF078.UINT32
#define RSCAN0RMDF078L RSCAN0.RMDF078.UINT16[L]
#define RSCAN0RMDF078LL RSCAN0.RMDF078.UINT8[LL]
#define RSCAN0RMDF078LH RSCAN0.RMDF078.UINT8[LH]
#define RSCAN0RMDF078H RSCAN0.RMDF078.UINT16[H]
#define RSCAN0RMDF078HL RSCAN0.RMDF078.UINT8[HL]
#define RSCAN0RMDF078HH RSCAN0.RMDF078.UINT8[HH]
#define RSCAN0RMDF178 RSCAN0.RMDF178.UINT32
#define RSCAN0RMDF178L RSCAN0.RMDF178.UINT16[L]
#define RSCAN0RMDF178LL RSCAN0.RMDF178.UINT8[LL]
#define RSCAN0RMDF178LH RSCAN0.RMDF178.UINT8[LH]
#define RSCAN0RMDF178H RSCAN0.RMDF178.UINT16[H]
#define RSCAN0RMDF178HL RSCAN0.RMDF178.UINT8[HL]
#define RSCAN0RMDF178HH RSCAN0.RMDF178.UINT8[HH]
#define RSCAN0RMID79 RSCAN0.RMID79.UINT32
#define RSCAN0RMID79L RSCAN0.RMID79.UINT16[L]
#define RSCAN0RMID79LL RSCAN0.RMID79.UINT8[LL]
#define RSCAN0RMID79LH RSCAN0.RMID79.UINT8[LH]
#define RSCAN0RMID79H RSCAN0.RMID79.UINT16[H]
#define RSCAN0RMID79HL RSCAN0.RMID79.UINT8[HL]
#define RSCAN0RMID79HH RSCAN0.RMID79.UINT8[HH]
#define RSCAN0RMPTR79 RSCAN0.RMPTR79.UINT32
#define RSCAN0RMPTR79L RSCAN0.RMPTR79.UINT16[L]
#define RSCAN0RMPTR79LL RSCAN0.RMPTR79.UINT8[LL]
#define RSCAN0RMPTR79LH RSCAN0.RMPTR79.UINT8[LH]
#define RSCAN0RMPTR79H RSCAN0.RMPTR79.UINT16[H]
#define RSCAN0RMPTR79HL RSCAN0.RMPTR79.UINT8[HL]
#define RSCAN0RMPTR79HH RSCAN0.RMPTR79.UINT8[HH]
#define RSCAN0RMDF079 RSCAN0.RMDF079.UINT32
#define RSCAN0RMDF079L RSCAN0.RMDF079.UINT16[L]
#define RSCAN0RMDF079LL RSCAN0.RMDF079.UINT8[LL]
#define RSCAN0RMDF079LH RSCAN0.RMDF079.UINT8[LH]
#define RSCAN0RMDF079H RSCAN0.RMDF079.UINT16[H]
#define RSCAN0RMDF079HL RSCAN0.RMDF079.UINT8[HL]
#define RSCAN0RMDF079HH RSCAN0.RMDF079.UINT8[HH]
#define RSCAN0RMDF179 RSCAN0.RMDF179.UINT32
#define RSCAN0RMDF179L RSCAN0.RMDF179.UINT16[L]
#define RSCAN0RMDF179LL RSCAN0.RMDF179.UINT8[LL]
#define RSCAN0RMDF179LH RSCAN0.RMDF179.UINT8[LH]
#define RSCAN0RMDF179H RSCAN0.RMDF179.UINT16[H]
#define RSCAN0RMDF179HL RSCAN0.RMDF179.UINT8[HL]
#define RSCAN0RMDF179HH RSCAN0.RMDF179.UINT8[HH]
#define RSCAN0RMID80 RSCAN0.RMID80.UINT32
#define RSCAN0RMID80L RSCAN0.RMID80.UINT16[L]
#define RSCAN0RMID80LL RSCAN0.RMID80.UINT8[LL]
#define RSCAN0RMID80LH RSCAN0.RMID80.UINT8[LH]
#define RSCAN0RMID80H RSCAN0.RMID80.UINT16[H]
#define RSCAN0RMID80HL RSCAN0.RMID80.UINT8[HL]
#define RSCAN0RMID80HH RSCAN0.RMID80.UINT8[HH]
#define RSCAN0RMPTR80 RSCAN0.RMPTR80.UINT32
#define RSCAN0RMPTR80L RSCAN0.RMPTR80.UINT16[L]
#define RSCAN0RMPTR80LL RSCAN0.RMPTR80.UINT8[LL]
#define RSCAN0RMPTR80LH RSCAN0.RMPTR80.UINT8[LH]
#define RSCAN0RMPTR80H RSCAN0.RMPTR80.UINT16[H]
#define RSCAN0RMPTR80HL RSCAN0.RMPTR80.UINT8[HL]
#define RSCAN0RMPTR80HH RSCAN0.RMPTR80.UINT8[HH]
#define RSCAN0RMDF080 RSCAN0.RMDF080.UINT32
#define RSCAN0RMDF080L RSCAN0.RMDF080.UINT16[L]
#define RSCAN0RMDF080LL RSCAN0.RMDF080.UINT8[LL]
#define RSCAN0RMDF080LH RSCAN0.RMDF080.UINT8[LH]
#define RSCAN0RMDF080H RSCAN0.RMDF080.UINT16[H]
#define RSCAN0RMDF080HL RSCAN0.RMDF080.UINT8[HL]
#define RSCAN0RMDF080HH RSCAN0.RMDF080.UINT8[HH]
#define RSCAN0RMDF180 RSCAN0.RMDF180.UINT32
#define RSCAN0RMDF180L RSCAN0.RMDF180.UINT16[L]
#define RSCAN0RMDF180LL RSCAN0.RMDF180.UINT8[LL]
#define RSCAN0RMDF180LH RSCAN0.RMDF180.UINT8[LH]
#define RSCAN0RMDF180H RSCAN0.RMDF180.UINT16[H]
#define RSCAN0RMDF180HL RSCAN0.RMDF180.UINT8[HL]
#define RSCAN0RMDF180HH RSCAN0.RMDF180.UINT8[HH]
#define RSCAN0RMID81 RSCAN0.RMID81.UINT32
#define RSCAN0RMID81L RSCAN0.RMID81.UINT16[L]
#define RSCAN0RMID81LL RSCAN0.RMID81.UINT8[LL]
#define RSCAN0RMID81LH RSCAN0.RMID81.UINT8[LH]
#define RSCAN0RMID81H RSCAN0.RMID81.UINT16[H]
#define RSCAN0RMID81HL RSCAN0.RMID81.UINT8[HL]
#define RSCAN0RMID81HH RSCAN0.RMID81.UINT8[HH]
#define RSCAN0RMPTR81 RSCAN0.RMPTR81.UINT32
#define RSCAN0RMPTR81L RSCAN0.RMPTR81.UINT16[L]
#define RSCAN0RMPTR81LL RSCAN0.RMPTR81.UINT8[LL]
#define RSCAN0RMPTR81LH RSCAN0.RMPTR81.UINT8[LH]
#define RSCAN0RMPTR81H RSCAN0.RMPTR81.UINT16[H]
#define RSCAN0RMPTR81HL RSCAN0.RMPTR81.UINT8[HL]
#define RSCAN0RMPTR81HH RSCAN0.RMPTR81.UINT8[HH]
#define RSCAN0RMDF081 RSCAN0.RMDF081.UINT32
#define RSCAN0RMDF081L RSCAN0.RMDF081.UINT16[L]
#define RSCAN0RMDF081LL RSCAN0.RMDF081.UINT8[LL]
#define RSCAN0RMDF081LH RSCAN0.RMDF081.UINT8[LH]
#define RSCAN0RMDF081H RSCAN0.RMDF081.UINT16[H]
#define RSCAN0RMDF081HL RSCAN0.RMDF081.UINT8[HL]
#define RSCAN0RMDF081HH RSCAN0.RMDF081.UINT8[HH]
#define RSCAN0RMDF181 RSCAN0.RMDF181.UINT32
#define RSCAN0RMDF181L RSCAN0.RMDF181.UINT16[L]
#define RSCAN0RMDF181LL RSCAN0.RMDF181.UINT8[LL]
#define RSCAN0RMDF181LH RSCAN0.RMDF181.UINT8[LH]
#define RSCAN0RMDF181H RSCAN0.RMDF181.UINT16[H]
#define RSCAN0RMDF181HL RSCAN0.RMDF181.UINT8[HL]
#define RSCAN0RMDF181HH RSCAN0.RMDF181.UINT8[HH]
#define RSCAN0RMID82 RSCAN0.RMID82.UINT32
#define RSCAN0RMID82L RSCAN0.RMID82.UINT16[L]
#define RSCAN0RMID82LL RSCAN0.RMID82.UINT8[LL]
#define RSCAN0RMID82LH RSCAN0.RMID82.UINT8[LH]
#define RSCAN0RMID82H RSCAN0.RMID82.UINT16[H]
#define RSCAN0RMID82HL RSCAN0.RMID82.UINT8[HL]
#define RSCAN0RMID82HH RSCAN0.RMID82.UINT8[HH]
#define RSCAN0RMPTR82 RSCAN0.RMPTR82.UINT32
#define RSCAN0RMPTR82L RSCAN0.RMPTR82.UINT16[L]
#define RSCAN0RMPTR82LL RSCAN0.RMPTR82.UINT8[LL]
#define RSCAN0RMPTR82LH RSCAN0.RMPTR82.UINT8[LH]
#define RSCAN0RMPTR82H RSCAN0.RMPTR82.UINT16[H]
#define RSCAN0RMPTR82HL RSCAN0.RMPTR82.UINT8[HL]
#define RSCAN0RMPTR82HH RSCAN0.RMPTR82.UINT8[HH]
#define RSCAN0RMDF082 RSCAN0.RMDF082.UINT32
#define RSCAN0RMDF082L RSCAN0.RMDF082.UINT16[L]
#define RSCAN0RMDF082LL RSCAN0.RMDF082.UINT8[LL]
#define RSCAN0RMDF082LH RSCAN0.RMDF082.UINT8[LH]
#define RSCAN0RMDF082H RSCAN0.RMDF082.UINT16[H]
#define RSCAN0RMDF082HL RSCAN0.RMDF082.UINT8[HL]
#define RSCAN0RMDF082HH RSCAN0.RMDF082.UINT8[HH]
#define RSCAN0RMDF182 RSCAN0.RMDF182.UINT32
#define RSCAN0RMDF182L RSCAN0.RMDF182.UINT16[L]
#define RSCAN0RMDF182LL RSCAN0.RMDF182.UINT8[LL]
#define RSCAN0RMDF182LH RSCAN0.RMDF182.UINT8[LH]
#define RSCAN0RMDF182H RSCAN0.RMDF182.UINT16[H]
#define RSCAN0RMDF182HL RSCAN0.RMDF182.UINT8[HL]
#define RSCAN0RMDF182HH RSCAN0.RMDF182.UINT8[HH]
#define RSCAN0RMID83 RSCAN0.RMID83.UINT32
#define RSCAN0RMID83L RSCAN0.RMID83.UINT16[L]
#define RSCAN0RMID83LL RSCAN0.RMID83.UINT8[LL]
#define RSCAN0RMID83LH RSCAN0.RMID83.UINT8[LH]
#define RSCAN0RMID83H RSCAN0.RMID83.UINT16[H]
#define RSCAN0RMID83HL RSCAN0.RMID83.UINT8[HL]
#define RSCAN0RMID83HH RSCAN0.RMID83.UINT8[HH]
#define RSCAN0RMPTR83 RSCAN0.RMPTR83.UINT32
#define RSCAN0RMPTR83L RSCAN0.RMPTR83.UINT16[L]
#define RSCAN0RMPTR83LL RSCAN0.RMPTR83.UINT8[LL]
#define RSCAN0RMPTR83LH RSCAN0.RMPTR83.UINT8[LH]
#define RSCAN0RMPTR83H RSCAN0.RMPTR83.UINT16[H]
#define RSCAN0RMPTR83HL RSCAN0.RMPTR83.UINT8[HL]
#define RSCAN0RMPTR83HH RSCAN0.RMPTR83.UINT8[HH]
#define RSCAN0RMDF083 RSCAN0.RMDF083.UINT32
#define RSCAN0RMDF083L RSCAN0.RMDF083.UINT16[L]
#define RSCAN0RMDF083LL RSCAN0.RMDF083.UINT8[LL]
#define RSCAN0RMDF083LH RSCAN0.RMDF083.UINT8[LH]
#define RSCAN0RMDF083H RSCAN0.RMDF083.UINT16[H]
#define RSCAN0RMDF083HL RSCAN0.RMDF083.UINT8[HL]
#define RSCAN0RMDF083HH RSCAN0.RMDF083.UINT8[HH]
#define RSCAN0RMDF183 RSCAN0.RMDF183.UINT32
#define RSCAN0RMDF183L RSCAN0.RMDF183.UINT16[L]
#define RSCAN0RMDF183LL RSCAN0.RMDF183.UINT8[LL]
#define RSCAN0RMDF183LH RSCAN0.RMDF183.UINT8[LH]
#define RSCAN0RMDF183H RSCAN0.RMDF183.UINT16[H]
#define RSCAN0RMDF183HL RSCAN0.RMDF183.UINT8[HL]
#define RSCAN0RMDF183HH RSCAN0.RMDF183.UINT8[HH]
#define RSCAN0RMID84 RSCAN0.RMID84.UINT32
#define RSCAN0RMID84L RSCAN0.RMID84.UINT16[L]
#define RSCAN0RMID84LL RSCAN0.RMID84.UINT8[LL]
#define RSCAN0RMID84LH RSCAN0.RMID84.UINT8[LH]
#define RSCAN0RMID84H RSCAN0.RMID84.UINT16[H]
#define RSCAN0RMID84HL RSCAN0.RMID84.UINT8[HL]
#define RSCAN0RMID84HH RSCAN0.RMID84.UINT8[HH]
#define RSCAN0RMPTR84 RSCAN0.RMPTR84.UINT32
#define RSCAN0RMPTR84L RSCAN0.RMPTR84.UINT16[L]
#define RSCAN0RMPTR84LL RSCAN0.RMPTR84.UINT8[LL]
#define RSCAN0RMPTR84LH RSCAN0.RMPTR84.UINT8[LH]
#define RSCAN0RMPTR84H RSCAN0.RMPTR84.UINT16[H]
#define RSCAN0RMPTR84HL RSCAN0.RMPTR84.UINT8[HL]
#define RSCAN0RMPTR84HH RSCAN0.RMPTR84.UINT8[HH]
#define RSCAN0RMDF084 RSCAN0.RMDF084.UINT32
#define RSCAN0RMDF084L RSCAN0.RMDF084.UINT16[L]
#define RSCAN0RMDF084LL RSCAN0.RMDF084.UINT8[LL]
#define RSCAN0RMDF084LH RSCAN0.RMDF084.UINT8[LH]
#define RSCAN0RMDF084H RSCAN0.RMDF084.UINT16[H]
#define RSCAN0RMDF084HL RSCAN0.RMDF084.UINT8[HL]
#define RSCAN0RMDF084HH RSCAN0.RMDF084.UINT8[HH]
#define RSCAN0RMDF184 RSCAN0.RMDF184.UINT32
#define RSCAN0RMDF184L RSCAN0.RMDF184.UINT16[L]
#define RSCAN0RMDF184LL RSCAN0.RMDF184.UINT8[LL]
#define RSCAN0RMDF184LH RSCAN0.RMDF184.UINT8[LH]
#define RSCAN0RMDF184H RSCAN0.RMDF184.UINT16[H]
#define RSCAN0RMDF184HL RSCAN0.RMDF184.UINT8[HL]
#define RSCAN0RMDF184HH RSCAN0.RMDF184.UINT8[HH]
#define RSCAN0RMID85 RSCAN0.RMID85.UINT32
#define RSCAN0RMID85L RSCAN0.RMID85.UINT16[L]
#define RSCAN0RMID85LL RSCAN0.RMID85.UINT8[LL]
#define RSCAN0RMID85LH RSCAN0.RMID85.UINT8[LH]
#define RSCAN0RMID85H RSCAN0.RMID85.UINT16[H]
#define RSCAN0RMID85HL RSCAN0.RMID85.UINT8[HL]
#define RSCAN0RMID85HH RSCAN0.RMID85.UINT8[HH]
#define RSCAN0RMPTR85 RSCAN0.RMPTR85.UINT32
#define RSCAN0RMPTR85L RSCAN0.RMPTR85.UINT16[L]
#define RSCAN0RMPTR85LL RSCAN0.RMPTR85.UINT8[LL]
#define RSCAN0RMPTR85LH RSCAN0.RMPTR85.UINT8[LH]
#define RSCAN0RMPTR85H RSCAN0.RMPTR85.UINT16[H]
#define RSCAN0RMPTR85HL RSCAN0.RMPTR85.UINT8[HL]
#define RSCAN0RMPTR85HH RSCAN0.RMPTR85.UINT8[HH]
#define RSCAN0RMDF085 RSCAN0.RMDF085.UINT32
#define RSCAN0RMDF085L RSCAN0.RMDF085.UINT16[L]
#define RSCAN0RMDF085LL RSCAN0.RMDF085.UINT8[LL]
#define RSCAN0RMDF085LH RSCAN0.RMDF085.UINT8[LH]
#define RSCAN0RMDF085H RSCAN0.RMDF085.UINT16[H]
#define RSCAN0RMDF085HL RSCAN0.RMDF085.UINT8[HL]
#define RSCAN0RMDF085HH RSCAN0.RMDF085.UINT8[HH]
#define RSCAN0RMDF185 RSCAN0.RMDF185.UINT32
#define RSCAN0RMDF185L RSCAN0.RMDF185.UINT16[L]
#define RSCAN0RMDF185LL RSCAN0.RMDF185.UINT8[LL]
#define RSCAN0RMDF185LH RSCAN0.RMDF185.UINT8[LH]
#define RSCAN0RMDF185H RSCAN0.RMDF185.UINT16[H]
#define RSCAN0RMDF185HL RSCAN0.RMDF185.UINT8[HL]
#define RSCAN0RMDF185HH RSCAN0.RMDF185.UINT8[HH]
#define RSCAN0RMID86 RSCAN0.RMID86.UINT32
#define RSCAN0RMID86L RSCAN0.RMID86.UINT16[L]
#define RSCAN0RMID86LL RSCAN0.RMID86.UINT8[LL]
#define RSCAN0RMID86LH RSCAN0.RMID86.UINT8[LH]
#define RSCAN0RMID86H RSCAN0.RMID86.UINT16[H]
#define RSCAN0RMID86HL RSCAN0.RMID86.UINT8[HL]
#define RSCAN0RMID86HH RSCAN0.RMID86.UINT8[HH]
#define RSCAN0RMPTR86 RSCAN0.RMPTR86.UINT32
#define RSCAN0RMPTR86L RSCAN0.RMPTR86.UINT16[L]
#define RSCAN0RMPTR86LL RSCAN0.RMPTR86.UINT8[LL]
#define RSCAN0RMPTR86LH RSCAN0.RMPTR86.UINT8[LH]
#define RSCAN0RMPTR86H RSCAN0.RMPTR86.UINT16[H]
#define RSCAN0RMPTR86HL RSCAN0.RMPTR86.UINT8[HL]
#define RSCAN0RMPTR86HH RSCAN0.RMPTR86.UINT8[HH]
#define RSCAN0RMDF086 RSCAN0.RMDF086.UINT32
#define RSCAN0RMDF086L RSCAN0.RMDF086.UINT16[L]
#define RSCAN0RMDF086LL RSCAN0.RMDF086.UINT8[LL]
#define RSCAN0RMDF086LH RSCAN0.RMDF086.UINT8[LH]
#define RSCAN0RMDF086H RSCAN0.RMDF086.UINT16[H]
#define RSCAN0RMDF086HL RSCAN0.RMDF086.UINT8[HL]
#define RSCAN0RMDF086HH RSCAN0.RMDF086.UINT8[HH]
#define RSCAN0RMDF186 RSCAN0.RMDF186.UINT32
#define RSCAN0RMDF186L RSCAN0.RMDF186.UINT16[L]
#define RSCAN0RMDF186LL RSCAN0.RMDF186.UINT8[LL]
#define RSCAN0RMDF186LH RSCAN0.RMDF186.UINT8[LH]
#define RSCAN0RMDF186H RSCAN0.RMDF186.UINT16[H]
#define RSCAN0RMDF186HL RSCAN0.RMDF186.UINT8[HL]
#define RSCAN0RMDF186HH RSCAN0.RMDF186.UINT8[HH]
#define RSCAN0RMID87 RSCAN0.RMID87.UINT32
#define RSCAN0RMID87L RSCAN0.RMID87.UINT16[L]
#define RSCAN0RMID87LL RSCAN0.RMID87.UINT8[LL]
#define RSCAN0RMID87LH RSCAN0.RMID87.UINT8[LH]
#define RSCAN0RMID87H RSCAN0.RMID87.UINT16[H]
#define RSCAN0RMID87HL RSCAN0.RMID87.UINT8[HL]
#define RSCAN0RMID87HH RSCAN0.RMID87.UINT8[HH]
#define RSCAN0RMPTR87 RSCAN0.RMPTR87.UINT32
#define RSCAN0RMPTR87L RSCAN0.RMPTR87.UINT16[L]
#define RSCAN0RMPTR87LL RSCAN0.RMPTR87.UINT8[LL]
#define RSCAN0RMPTR87LH RSCAN0.RMPTR87.UINT8[LH]
#define RSCAN0RMPTR87H RSCAN0.RMPTR87.UINT16[H]
#define RSCAN0RMPTR87HL RSCAN0.RMPTR87.UINT8[HL]
#define RSCAN0RMPTR87HH RSCAN0.RMPTR87.UINT8[HH]
#define RSCAN0RMDF087 RSCAN0.RMDF087.UINT32
#define RSCAN0RMDF087L RSCAN0.RMDF087.UINT16[L]
#define RSCAN0RMDF087LL RSCAN0.RMDF087.UINT8[LL]
#define RSCAN0RMDF087LH RSCAN0.RMDF087.UINT8[LH]
#define RSCAN0RMDF087H RSCAN0.RMDF087.UINT16[H]
#define RSCAN0RMDF087HL RSCAN0.RMDF087.UINT8[HL]
#define RSCAN0RMDF087HH RSCAN0.RMDF087.UINT8[HH]
#define RSCAN0RMDF187 RSCAN0.RMDF187.UINT32
#define RSCAN0RMDF187L RSCAN0.RMDF187.UINT16[L]
#define RSCAN0RMDF187LL RSCAN0.RMDF187.UINT8[LL]
#define RSCAN0RMDF187LH RSCAN0.RMDF187.UINT8[LH]
#define RSCAN0RMDF187H RSCAN0.RMDF187.UINT16[H]
#define RSCAN0RMDF187HL RSCAN0.RMDF187.UINT8[HL]
#define RSCAN0RMDF187HH RSCAN0.RMDF187.UINT8[HH]
#define RSCAN0RMID88 RSCAN0.RMID88.UINT32
#define RSCAN0RMID88L RSCAN0.RMID88.UINT16[L]
#define RSCAN0RMID88LL RSCAN0.RMID88.UINT8[LL]
#define RSCAN0RMID88LH RSCAN0.RMID88.UINT8[LH]
#define RSCAN0RMID88H RSCAN0.RMID88.UINT16[H]
#define RSCAN0RMID88HL RSCAN0.RMID88.UINT8[HL]
#define RSCAN0RMID88HH RSCAN0.RMID88.UINT8[HH]
#define RSCAN0RMPTR88 RSCAN0.RMPTR88.UINT32
#define RSCAN0RMPTR88L RSCAN0.RMPTR88.UINT16[L]
#define RSCAN0RMPTR88LL RSCAN0.RMPTR88.UINT8[LL]
#define RSCAN0RMPTR88LH RSCAN0.RMPTR88.UINT8[LH]
#define RSCAN0RMPTR88H RSCAN0.RMPTR88.UINT16[H]
#define RSCAN0RMPTR88HL RSCAN0.RMPTR88.UINT8[HL]
#define RSCAN0RMPTR88HH RSCAN0.RMPTR88.UINT8[HH]
#define RSCAN0RMDF088 RSCAN0.RMDF088.UINT32
#define RSCAN0RMDF088L RSCAN0.RMDF088.UINT16[L]
#define RSCAN0RMDF088LL RSCAN0.RMDF088.UINT8[LL]
#define RSCAN0RMDF088LH RSCAN0.RMDF088.UINT8[LH]
#define RSCAN0RMDF088H RSCAN0.RMDF088.UINT16[H]
#define RSCAN0RMDF088HL RSCAN0.RMDF088.UINT8[HL]
#define RSCAN0RMDF088HH RSCAN0.RMDF088.UINT8[HH]
#define RSCAN0RMDF188 RSCAN0.RMDF188.UINT32
#define RSCAN0RMDF188L RSCAN0.RMDF188.UINT16[L]
#define RSCAN0RMDF188LL RSCAN0.RMDF188.UINT8[LL]
#define RSCAN0RMDF188LH RSCAN0.RMDF188.UINT8[LH]
#define RSCAN0RMDF188H RSCAN0.RMDF188.UINT16[H]
#define RSCAN0RMDF188HL RSCAN0.RMDF188.UINT8[HL]
#define RSCAN0RMDF188HH RSCAN0.RMDF188.UINT8[HH]
#define RSCAN0RMID89 RSCAN0.RMID89.UINT32
#define RSCAN0RMID89L RSCAN0.RMID89.UINT16[L]
#define RSCAN0RMID89LL RSCAN0.RMID89.UINT8[LL]
#define RSCAN0RMID89LH RSCAN0.RMID89.UINT8[LH]
#define RSCAN0RMID89H RSCAN0.RMID89.UINT16[H]
#define RSCAN0RMID89HL RSCAN0.RMID89.UINT8[HL]
#define RSCAN0RMID89HH RSCAN0.RMID89.UINT8[HH]
#define RSCAN0RMPTR89 RSCAN0.RMPTR89.UINT32
#define RSCAN0RMPTR89L RSCAN0.RMPTR89.UINT16[L]
#define RSCAN0RMPTR89LL RSCAN0.RMPTR89.UINT8[LL]
#define RSCAN0RMPTR89LH RSCAN0.RMPTR89.UINT8[LH]
#define RSCAN0RMPTR89H RSCAN0.RMPTR89.UINT16[H]
#define RSCAN0RMPTR89HL RSCAN0.RMPTR89.UINT8[HL]
#define RSCAN0RMPTR89HH RSCAN0.RMPTR89.UINT8[HH]
#define RSCAN0RMDF089 RSCAN0.RMDF089.UINT32
#define RSCAN0RMDF089L RSCAN0.RMDF089.UINT16[L]
#define RSCAN0RMDF089LL RSCAN0.RMDF089.UINT8[LL]
#define RSCAN0RMDF089LH RSCAN0.RMDF089.UINT8[LH]
#define RSCAN0RMDF089H RSCAN0.RMDF089.UINT16[H]
#define RSCAN0RMDF089HL RSCAN0.RMDF089.UINT8[HL]
#define RSCAN0RMDF089HH RSCAN0.RMDF089.UINT8[HH]
#define RSCAN0RMDF189 RSCAN0.RMDF189.UINT32
#define RSCAN0RMDF189L RSCAN0.RMDF189.UINT16[L]
#define RSCAN0RMDF189LL RSCAN0.RMDF189.UINT8[LL]
#define RSCAN0RMDF189LH RSCAN0.RMDF189.UINT8[LH]
#define RSCAN0RMDF189H RSCAN0.RMDF189.UINT16[H]
#define RSCAN0RMDF189HL RSCAN0.RMDF189.UINT8[HL]
#define RSCAN0RMDF189HH RSCAN0.RMDF189.UINT8[HH]
#define RSCAN0RMID90 RSCAN0.RMID90.UINT32
#define RSCAN0RMID90L RSCAN0.RMID90.UINT16[L]
#define RSCAN0RMID90LL RSCAN0.RMID90.UINT8[LL]
#define RSCAN0RMID90LH RSCAN0.RMID90.UINT8[LH]
#define RSCAN0RMID90H RSCAN0.RMID90.UINT16[H]
#define RSCAN0RMID90HL RSCAN0.RMID90.UINT8[HL]
#define RSCAN0RMID90HH RSCAN0.RMID90.UINT8[HH]
#define RSCAN0RMPTR90 RSCAN0.RMPTR90.UINT32
#define RSCAN0RMPTR90L RSCAN0.RMPTR90.UINT16[L]
#define RSCAN0RMPTR90LL RSCAN0.RMPTR90.UINT8[LL]
#define RSCAN0RMPTR90LH RSCAN0.RMPTR90.UINT8[LH]
#define RSCAN0RMPTR90H RSCAN0.RMPTR90.UINT16[H]
#define RSCAN0RMPTR90HL RSCAN0.RMPTR90.UINT8[HL]
#define RSCAN0RMPTR90HH RSCAN0.RMPTR90.UINT8[HH]
#define RSCAN0RMDF090 RSCAN0.RMDF090.UINT32
#define RSCAN0RMDF090L RSCAN0.RMDF090.UINT16[L]
#define RSCAN0RMDF090LL RSCAN0.RMDF090.UINT8[LL]
#define RSCAN0RMDF090LH RSCAN0.RMDF090.UINT8[LH]
#define RSCAN0RMDF090H RSCAN0.RMDF090.UINT16[H]
#define RSCAN0RMDF090HL RSCAN0.RMDF090.UINT8[HL]
#define RSCAN0RMDF090HH RSCAN0.RMDF090.UINT8[HH]
#define RSCAN0RMDF190 RSCAN0.RMDF190.UINT32
#define RSCAN0RMDF190L RSCAN0.RMDF190.UINT16[L]
#define RSCAN0RMDF190LL RSCAN0.RMDF190.UINT8[LL]
#define RSCAN0RMDF190LH RSCAN0.RMDF190.UINT8[LH]
#define RSCAN0RMDF190H RSCAN0.RMDF190.UINT16[H]
#define RSCAN0RMDF190HL RSCAN0.RMDF190.UINT8[HL]
#define RSCAN0RMDF190HH RSCAN0.RMDF190.UINT8[HH]
#define RSCAN0RMID91 RSCAN0.RMID91.UINT32
#define RSCAN0RMID91L RSCAN0.RMID91.UINT16[L]
#define RSCAN0RMID91LL RSCAN0.RMID91.UINT8[LL]
#define RSCAN0RMID91LH RSCAN0.RMID91.UINT8[LH]
#define RSCAN0RMID91H RSCAN0.RMID91.UINT16[H]
#define RSCAN0RMID91HL RSCAN0.RMID91.UINT8[HL]
#define RSCAN0RMID91HH RSCAN0.RMID91.UINT8[HH]
#define RSCAN0RMPTR91 RSCAN0.RMPTR91.UINT32
#define RSCAN0RMPTR91L RSCAN0.RMPTR91.UINT16[L]
#define RSCAN0RMPTR91LL RSCAN0.RMPTR91.UINT8[LL]
#define RSCAN0RMPTR91LH RSCAN0.RMPTR91.UINT8[LH]
#define RSCAN0RMPTR91H RSCAN0.RMPTR91.UINT16[H]
#define RSCAN0RMPTR91HL RSCAN0.RMPTR91.UINT8[HL]
#define RSCAN0RMPTR91HH RSCAN0.RMPTR91.UINT8[HH]
#define RSCAN0RMDF091 RSCAN0.RMDF091.UINT32
#define RSCAN0RMDF091L RSCAN0.RMDF091.UINT16[L]
#define RSCAN0RMDF091LL RSCAN0.RMDF091.UINT8[LL]
#define RSCAN0RMDF091LH RSCAN0.RMDF091.UINT8[LH]
#define RSCAN0RMDF091H RSCAN0.RMDF091.UINT16[H]
#define RSCAN0RMDF091HL RSCAN0.RMDF091.UINT8[HL]
#define RSCAN0RMDF091HH RSCAN0.RMDF091.UINT8[HH]
#define RSCAN0RMDF191 RSCAN0.RMDF191.UINT32
#define RSCAN0RMDF191L RSCAN0.RMDF191.UINT16[L]
#define RSCAN0RMDF191LL RSCAN0.RMDF191.UINT8[LL]
#define RSCAN0RMDF191LH RSCAN0.RMDF191.UINT8[LH]
#define RSCAN0RMDF191H RSCAN0.RMDF191.UINT16[H]
#define RSCAN0RMDF191HL RSCAN0.RMDF191.UINT8[HL]
#define RSCAN0RMDF191HH RSCAN0.RMDF191.UINT8[HH]
#define RSCAN0RMID92 RSCAN0.RMID92.UINT32
#define RSCAN0RMID92L RSCAN0.RMID92.UINT16[L]
#define RSCAN0RMID92LL RSCAN0.RMID92.UINT8[LL]
#define RSCAN0RMID92LH RSCAN0.RMID92.UINT8[LH]
#define RSCAN0RMID92H RSCAN0.RMID92.UINT16[H]
#define RSCAN0RMID92HL RSCAN0.RMID92.UINT8[HL]
#define RSCAN0RMID92HH RSCAN0.RMID92.UINT8[HH]
#define RSCAN0RMPTR92 RSCAN0.RMPTR92.UINT32
#define RSCAN0RMPTR92L RSCAN0.RMPTR92.UINT16[L]
#define RSCAN0RMPTR92LL RSCAN0.RMPTR92.UINT8[LL]
#define RSCAN0RMPTR92LH RSCAN0.RMPTR92.UINT8[LH]
#define RSCAN0RMPTR92H RSCAN0.RMPTR92.UINT16[H]
#define RSCAN0RMPTR92HL RSCAN0.RMPTR92.UINT8[HL]
#define RSCAN0RMPTR92HH RSCAN0.RMPTR92.UINT8[HH]
#define RSCAN0RMDF092 RSCAN0.RMDF092.UINT32
#define RSCAN0RMDF092L RSCAN0.RMDF092.UINT16[L]
#define RSCAN0RMDF092LL RSCAN0.RMDF092.UINT8[LL]
#define RSCAN0RMDF092LH RSCAN0.RMDF092.UINT8[LH]
#define RSCAN0RMDF092H RSCAN0.RMDF092.UINT16[H]
#define RSCAN0RMDF092HL RSCAN0.RMDF092.UINT8[HL]
#define RSCAN0RMDF092HH RSCAN0.RMDF092.UINT8[HH]
#define RSCAN0RMDF192 RSCAN0.RMDF192.UINT32
#define RSCAN0RMDF192L RSCAN0.RMDF192.UINT16[L]
#define RSCAN0RMDF192LL RSCAN0.RMDF192.UINT8[LL]
#define RSCAN0RMDF192LH RSCAN0.RMDF192.UINT8[LH]
#define RSCAN0RMDF192H RSCAN0.RMDF192.UINT16[H]
#define RSCAN0RMDF192HL RSCAN0.RMDF192.UINT8[HL]
#define RSCAN0RMDF192HH RSCAN0.RMDF192.UINT8[HH]
#define RSCAN0RMID93 RSCAN0.RMID93.UINT32
#define RSCAN0RMID93L RSCAN0.RMID93.UINT16[L]
#define RSCAN0RMID93LL RSCAN0.RMID93.UINT8[LL]
#define RSCAN0RMID93LH RSCAN0.RMID93.UINT8[LH]
#define RSCAN0RMID93H RSCAN0.RMID93.UINT16[H]
#define RSCAN0RMID93HL RSCAN0.RMID93.UINT8[HL]
#define RSCAN0RMID93HH RSCAN0.RMID93.UINT8[HH]
#define RSCAN0RMPTR93 RSCAN0.RMPTR93.UINT32
#define RSCAN0RMPTR93L RSCAN0.RMPTR93.UINT16[L]
#define RSCAN0RMPTR93LL RSCAN0.RMPTR93.UINT8[LL]
#define RSCAN0RMPTR93LH RSCAN0.RMPTR93.UINT8[LH]
#define RSCAN0RMPTR93H RSCAN0.RMPTR93.UINT16[H]
#define RSCAN0RMPTR93HL RSCAN0.RMPTR93.UINT8[HL]
#define RSCAN0RMPTR93HH RSCAN0.RMPTR93.UINT8[HH]
#define RSCAN0RMDF093 RSCAN0.RMDF093.UINT32
#define RSCAN0RMDF093L RSCAN0.RMDF093.UINT16[L]
#define RSCAN0RMDF093LL RSCAN0.RMDF093.UINT8[LL]
#define RSCAN0RMDF093LH RSCAN0.RMDF093.UINT8[LH]
#define RSCAN0RMDF093H RSCAN0.RMDF093.UINT16[H]
#define RSCAN0RMDF093HL RSCAN0.RMDF093.UINT8[HL]
#define RSCAN0RMDF093HH RSCAN0.RMDF093.UINT8[HH]
#define RSCAN0RMDF193 RSCAN0.RMDF193.UINT32
#define RSCAN0RMDF193L RSCAN0.RMDF193.UINT16[L]
#define RSCAN0RMDF193LL RSCAN0.RMDF193.UINT8[LL]
#define RSCAN0RMDF193LH RSCAN0.RMDF193.UINT8[LH]
#define RSCAN0RMDF193H RSCAN0.RMDF193.UINT16[H]
#define RSCAN0RMDF193HL RSCAN0.RMDF193.UINT8[HL]
#define RSCAN0RMDF193HH RSCAN0.RMDF193.UINT8[HH]
#define RSCAN0RMID94 RSCAN0.RMID94.UINT32
#define RSCAN0RMID94L RSCAN0.RMID94.UINT16[L]
#define RSCAN0RMID94LL RSCAN0.RMID94.UINT8[LL]
#define RSCAN0RMID94LH RSCAN0.RMID94.UINT8[LH]
#define RSCAN0RMID94H RSCAN0.RMID94.UINT16[H]
#define RSCAN0RMID94HL RSCAN0.RMID94.UINT8[HL]
#define RSCAN0RMID94HH RSCAN0.RMID94.UINT8[HH]
#define RSCAN0RMPTR94 RSCAN0.RMPTR94.UINT32
#define RSCAN0RMPTR94L RSCAN0.RMPTR94.UINT16[L]
#define RSCAN0RMPTR94LL RSCAN0.RMPTR94.UINT8[LL]
#define RSCAN0RMPTR94LH RSCAN0.RMPTR94.UINT8[LH]
#define RSCAN0RMPTR94H RSCAN0.RMPTR94.UINT16[H]
#define RSCAN0RMPTR94HL RSCAN0.RMPTR94.UINT8[HL]
#define RSCAN0RMPTR94HH RSCAN0.RMPTR94.UINT8[HH]
#define RSCAN0RMDF094 RSCAN0.RMDF094.UINT32
#define RSCAN0RMDF094L RSCAN0.RMDF094.UINT16[L]
#define RSCAN0RMDF094LL RSCAN0.RMDF094.UINT8[LL]
#define RSCAN0RMDF094LH RSCAN0.RMDF094.UINT8[LH]
#define RSCAN0RMDF094H RSCAN0.RMDF094.UINT16[H]
#define RSCAN0RMDF094HL RSCAN0.RMDF094.UINT8[HL]
#define RSCAN0RMDF094HH RSCAN0.RMDF094.UINT8[HH]
#define RSCAN0RMDF194 RSCAN0.RMDF194.UINT32
#define RSCAN0RMDF194L RSCAN0.RMDF194.UINT16[L]
#define RSCAN0RMDF194LL RSCAN0.RMDF194.UINT8[LL]
#define RSCAN0RMDF194LH RSCAN0.RMDF194.UINT8[LH]
#define RSCAN0RMDF194H RSCAN0.RMDF194.UINT16[H]
#define RSCAN0RMDF194HL RSCAN0.RMDF194.UINT8[HL]
#define RSCAN0RMDF194HH RSCAN0.RMDF194.UINT8[HH]
#define RSCAN0RMID95 RSCAN0.RMID95.UINT32
#define RSCAN0RMID95L RSCAN0.RMID95.UINT16[L]
#define RSCAN0RMID95LL RSCAN0.RMID95.UINT8[LL]
#define RSCAN0RMID95LH RSCAN0.RMID95.UINT8[LH]
#define RSCAN0RMID95H RSCAN0.RMID95.UINT16[H]
#define RSCAN0RMID95HL RSCAN0.RMID95.UINT8[HL]
#define RSCAN0RMID95HH RSCAN0.RMID95.UINT8[HH]
#define RSCAN0RMPTR95 RSCAN0.RMPTR95.UINT32
#define RSCAN0RMPTR95L RSCAN0.RMPTR95.UINT16[L]
#define RSCAN0RMPTR95LL RSCAN0.RMPTR95.UINT8[LL]
#define RSCAN0RMPTR95LH RSCAN0.RMPTR95.UINT8[LH]
#define RSCAN0RMPTR95H RSCAN0.RMPTR95.UINT16[H]
#define RSCAN0RMPTR95HL RSCAN0.RMPTR95.UINT8[HL]
#define RSCAN0RMPTR95HH RSCAN0.RMPTR95.UINT8[HH]
#define RSCAN0RMDF095 RSCAN0.RMDF095.UINT32
#define RSCAN0RMDF095L RSCAN0.RMDF095.UINT16[L]
#define RSCAN0RMDF095LL RSCAN0.RMDF095.UINT8[LL]
#define RSCAN0RMDF095LH RSCAN0.RMDF095.UINT8[LH]
#define RSCAN0RMDF095H RSCAN0.RMDF095.UINT16[H]
#define RSCAN0RMDF095HL RSCAN0.RMDF095.UINT8[HL]
#define RSCAN0RMDF095HH RSCAN0.RMDF095.UINT8[HH]
#define RSCAN0RMDF195 RSCAN0.RMDF195.UINT32
#define RSCAN0RMDF195L RSCAN0.RMDF195.UINT16[L]
#define RSCAN0RMDF195LL RSCAN0.RMDF195.UINT8[LL]
#define RSCAN0RMDF195LH RSCAN0.RMDF195.UINT8[LH]
#define RSCAN0RMDF195H RSCAN0.RMDF195.UINT16[H]
#define RSCAN0RMDF195HL RSCAN0.RMDF195.UINT8[HL]
#define RSCAN0RMDF195HH RSCAN0.RMDF195.UINT8[HH]
#define RSCAN0RFID0 RSCAN0.RFID0.UINT32
#define RSCAN0RFID0L RSCAN0.RFID0.UINT16[L]
#define RSCAN0RFID0LL RSCAN0.RFID0.UINT8[LL]
#define RSCAN0RFID0LH RSCAN0.RFID0.UINT8[LH]
#define RSCAN0RFID0H RSCAN0.RFID0.UINT16[H]
#define RSCAN0RFID0HL RSCAN0.RFID0.UINT8[HL]
#define RSCAN0RFID0HH RSCAN0.RFID0.UINT8[HH]
#define RSCAN0RFPTR0 RSCAN0.RFPTR0.UINT32
#define RSCAN0RFPTR0L RSCAN0.RFPTR0.UINT16[L]
#define RSCAN0RFPTR0LL RSCAN0.RFPTR0.UINT8[LL]
#define RSCAN0RFPTR0LH RSCAN0.RFPTR0.UINT8[LH]
#define RSCAN0RFPTR0H RSCAN0.RFPTR0.UINT16[H]
#define RSCAN0RFPTR0HL RSCAN0.RFPTR0.UINT8[HL]
#define RSCAN0RFPTR0HH RSCAN0.RFPTR0.UINT8[HH]
#define RSCAN0RFDF00 RSCAN0.RFDF00.UINT32
#define RSCAN0RFDF00L RSCAN0.RFDF00.UINT16[L]
#define RSCAN0RFDF00LL RSCAN0.RFDF00.UINT8[LL]
#define RSCAN0RFDF00LH RSCAN0.RFDF00.UINT8[LH]
#define RSCAN0RFDF00H RSCAN0.RFDF00.UINT16[H]
#define RSCAN0RFDF00HL RSCAN0.RFDF00.UINT8[HL]
#define RSCAN0RFDF00HH RSCAN0.RFDF00.UINT8[HH]
#define RSCAN0RFDF10 RSCAN0.RFDF10.UINT32
#define RSCAN0RFDF10L RSCAN0.RFDF10.UINT16[L]
#define RSCAN0RFDF10LL RSCAN0.RFDF10.UINT8[LL]
#define RSCAN0RFDF10LH RSCAN0.RFDF10.UINT8[LH]
#define RSCAN0RFDF10H RSCAN0.RFDF10.UINT16[H]
#define RSCAN0RFDF10HL RSCAN0.RFDF10.UINT8[HL]
#define RSCAN0RFDF10HH RSCAN0.RFDF10.UINT8[HH]
#define RSCAN0RFID1 RSCAN0.RFID1.UINT32
#define RSCAN0RFID1L RSCAN0.RFID1.UINT16[L]
#define RSCAN0RFID1LL RSCAN0.RFID1.UINT8[LL]
#define RSCAN0RFID1LH RSCAN0.RFID1.UINT8[LH]
#define RSCAN0RFID1H RSCAN0.RFID1.UINT16[H]
#define RSCAN0RFID1HL RSCAN0.RFID1.UINT8[HL]
#define RSCAN0RFID1HH RSCAN0.RFID1.UINT8[HH]
#define RSCAN0RFPTR1 RSCAN0.RFPTR1.UINT32
#define RSCAN0RFPTR1L RSCAN0.RFPTR1.UINT16[L]
#define RSCAN0RFPTR1LL RSCAN0.RFPTR1.UINT8[LL]
#define RSCAN0RFPTR1LH RSCAN0.RFPTR1.UINT8[LH]
#define RSCAN0RFPTR1H RSCAN0.RFPTR1.UINT16[H]
#define RSCAN0RFPTR1HL RSCAN0.RFPTR1.UINT8[HL]
#define RSCAN0RFPTR1HH RSCAN0.RFPTR1.UINT8[HH]
#define RSCAN0RFDF01 RSCAN0.RFDF01.UINT32
#define RSCAN0RFDF01L RSCAN0.RFDF01.UINT16[L]
#define RSCAN0RFDF01LL RSCAN0.RFDF01.UINT8[LL]
#define RSCAN0RFDF01LH RSCAN0.RFDF01.UINT8[LH]
#define RSCAN0RFDF01H RSCAN0.RFDF01.UINT16[H]
#define RSCAN0RFDF01HL RSCAN0.RFDF01.UINT8[HL]
#define RSCAN0RFDF01HH RSCAN0.RFDF01.UINT8[HH]
#define RSCAN0RFDF11 RSCAN0.RFDF11.UINT32
#define RSCAN0RFDF11L RSCAN0.RFDF11.UINT16[L]
#define RSCAN0RFDF11LL RSCAN0.RFDF11.UINT8[LL]
#define RSCAN0RFDF11LH RSCAN0.RFDF11.UINT8[LH]
#define RSCAN0RFDF11H RSCAN0.RFDF11.UINT16[H]
#define RSCAN0RFDF11HL RSCAN0.RFDF11.UINT8[HL]
#define RSCAN0RFDF11HH RSCAN0.RFDF11.UINT8[HH]
#define RSCAN0RFID2 RSCAN0.RFID2.UINT32
#define RSCAN0RFID2L RSCAN0.RFID2.UINT16[L]
#define RSCAN0RFID2LL RSCAN0.RFID2.UINT8[LL]
#define RSCAN0RFID2LH RSCAN0.RFID2.UINT8[LH]
#define RSCAN0RFID2H RSCAN0.RFID2.UINT16[H]
#define RSCAN0RFID2HL RSCAN0.RFID2.UINT8[HL]
#define RSCAN0RFID2HH RSCAN0.RFID2.UINT8[HH]
#define RSCAN0RFPTR2 RSCAN0.RFPTR2.UINT32
#define RSCAN0RFPTR2L RSCAN0.RFPTR2.UINT16[L]
#define RSCAN0RFPTR2LL RSCAN0.RFPTR2.UINT8[LL]
#define RSCAN0RFPTR2LH RSCAN0.RFPTR2.UINT8[LH]
#define RSCAN0RFPTR2H RSCAN0.RFPTR2.UINT16[H]
#define RSCAN0RFPTR2HL RSCAN0.RFPTR2.UINT8[HL]
#define RSCAN0RFPTR2HH RSCAN0.RFPTR2.UINT8[HH]
#define RSCAN0RFDF02 RSCAN0.RFDF02.UINT32
#define RSCAN0RFDF02L RSCAN0.RFDF02.UINT16[L]
#define RSCAN0RFDF02LL RSCAN0.RFDF02.UINT8[LL]
#define RSCAN0RFDF02LH RSCAN0.RFDF02.UINT8[LH]
#define RSCAN0RFDF02H RSCAN0.RFDF02.UINT16[H]
#define RSCAN0RFDF02HL RSCAN0.RFDF02.UINT8[HL]
#define RSCAN0RFDF02HH RSCAN0.RFDF02.UINT8[HH]
#define RSCAN0RFDF12 RSCAN0.RFDF12.UINT32
#define RSCAN0RFDF12L RSCAN0.RFDF12.UINT16[L]
#define RSCAN0RFDF12LL RSCAN0.RFDF12.UINT8[LL]
#define RSCAN0RFDF12LH RSCAN0.RFDF12.UINT8[LH]
#define RSCAN0RFDF12H RSCAN0.RFDF12.UINT16[H]
#define RSCAN0RFDF12HL RSCAN0.RFDF12.UINT8[HL]
#define RSCAN0RFDF12HH RSCAN0.RFDF12.UINT8[HH]
#define RSCAN0RFID3 RSCAN0.RFID3.UINT32
#define RSCAN0RFID3L RSCAN0.RFID3.UINT16[L]
#define RSCAN0RFID3LL RSCAN0.RFID3.UINT8[LL]
#define RSCAN0RFID3LH RSCAN0.RFID3.UINT8[LH]
#define RSCAN0RFID3H RSCAN0.RFID3.UINT16[H]
#define RSCAN0RFID3HL RSCAN0.RFID3.UINT8[HL]
#define RSCAN0RFID3HH RSCAN0.RFID3.UINT8[HH]
#define RSCAN0RFPTR3 RSCAN0.RFPTR3.UINT32
#define RSCAN0RFPTR3L RSCAN0.RFPTR3.UINT16[L]
#define RSCAN0RFPTR3LL RSCAN0.RFPTR3.UINT8[LL]
#define RSCAN0RFPTR3LH RSCAN0.RFPTR3.UINT8[LH]
#define RSCAN0RFPTR3H RSCAN0.RFPTR3.UINT16[H]
#define RSCAN0RFPTR3HL RSCAN0.RFPTR3.UINT8[HL]
#define RSCAN0RFPTR3HH RSCAN0.RFPTR3.UINT8[HH]
#define RSCAN0RFDF03 RSCAN0.RFDF03.UINT32
#define RSCAN0RFDF03L RSCAN0.RFDF03.UINT16[L]
#define RSCAN0RFDF03LL RSCAN0.RFDF03.UINT8[LL]
#define RSCAN0RFDF03LH RSCAN0.RFDF03.UINT8[LH]
#define RSCAN0RFDF03H RSCAN0.RFDF03.UINT16[H]
#define RSCAN0RFDF03HL RSCAN0.RFDF03.UINT8[HL]
#define RSCAN0RFDF03HH RSCAN0.RFDF03.UINT8[HH]
#define RSCAN0RFDF13 RSCAN0.RFDF13.UINT32
#define RSCAN0RFDF13L RSCAN0.RFDF13.UINT16[L]
#define RSCAN0RFDF13LL RSCAN0.RFDF13.UINT8[LL]
#define RSCAN0RFDF13LH RSCAN0.RFDF13.UINT8[LH]
#define RSCAN0RFDF13H RSCAN0.RFDF13.UINT16[H]
#define RSCAN0RFDF13HL RSCAN0.RFDF13.UINT8[HL]
#define RSCAN0RFDF13HH RSCAN0.RFDF13.UINT8[HH]
#define RSCAN0RFID4 RSCAN0.RFID4.UINT32
#define RSCAN0RFID4L RSCAN0.RFID4.UINT16[L]
#define RSCAN0RFID4LL RSCAN0.RFID4.UINT8[LL]
#define RSCAN0RFID4LH RSCAN0.RFID4.UINT8[LH]
#define RSCAN0RFID4H RSCAN0.RFID4.UINT16[H]
#define RSCAN0RFID4HL RSCAN0.RFID4.UINT8[HL]
#define RSCAN0RFID4HH RSCAN0.RFID4.UINT8[HH]
#define RSCAN0RFPTR4 RSCAN0.RFPTR4.UINT32
#define RSCAN0RFPTR4L RSCAN0.RFPTR4.UINT16[L]
#define RSCAN0RFPTR4LL RSCAN0.RFPTR4.UINT8[LL]
#define RSCAN0RFPTR4LH RSCAN0.RFPTR4.UINT8[LH]
#define RSCAN0RFPTR4H RSCAN0.RFPTR4.UINT16[H]
#define RSCAN0RFPTR4HL RSCAN0.RFPTR4.UINT8[HL]
#define RSCAN0RFPTR4HH RSCAN0.RFPTR4.UINT8[HH]
#define RSCAN0RFDF04 RSCAN0.RFDF04.UINT32
#define RSCAN0RFDF04L RSCAN0.RFDF04.UINT16[L]
#define RSCAN0RFDF04LL RSCAN0.RFDF04.UINT8[LL]
#define RSCAN0RFDF04LH RSCAN0.RFDF04.UINT8[LH]
#define RSCAN0RFDF04H RSCAN0.RFDF04.UINT16[H]
#define RSCAN0RFDF04HL RSCAN0.RFDF04.UINT8[HL]
#define RSCAN0RFDF04HH RSCAN0.RFDF04.UINT8[HH]
#define RSCAN0RFDF14 RSCAN0.RFDF14.UINT32
#define RSCAN0RFDF14L RSCAN0.RFDF14.UINT16[L]
#define RSCAN0RFDF14LL RSCAN0.RFDF14.UINT8[LL]
#define RSCAN0RFDF14LH RSCAN0.RFDF14.UINT8[LH]
#define RSCAN0RFDF14H RSCAN0.RFDF14.UINT16[H]
#define RSCAN0RFDF14HL RSCAN0.RFDF14.UINT8[HL]
#define RSCAN0RFDF14HH RSCAN0.RFDF14.UINT8[HH]
#define RSCAN0RFID5 RSCAN0.RFID5.UINT32
#define RSCAN0RFID5L RSCAN0.RFID5.UINT16[L]
#define RSCAN0RFID5LL RSCAN0.RFID5.UINT8[LL]
#define RSCAN0RFID5LH RSCAN0.RFID5.UINT8[LH]
#define RSCAN0RFID5H RSCAN0.RFID5.UINT16[H]
#define RSCAN0RFID5HL RSCAN0.RFID5.UINT8[HL]
#define RSCAN0RFID5HH RSCAN0.RFID5.UINT8[HH]
#define RSCAN0RFPTR5 RSCAN0.RFPTR5.UINT32
#define RSCAN0RFPTR5L RSCAN0.RFPTR5.UINT16[L]
#define RSCAN0RFPTR5LL RSCAN0.RFPTR5.UINT8[LL]
#define RSCAN0RFPTR5LH RSCAN0.RFPTR5.UINT8[LH]
#define RSCAN0RFPTR5H RSCAN0.RFPTR5.UINT16[H]
#define RSCAN0RFPTR5HL RSCAN0.RFPTR5.UINT8[HL]
#define RSCAN0RFPTR5HH RSCAN0.RFPTR5.UINT8[HH]
#define RSCAN0RFDF05 RSCAN0.RFDF05.UINT32
#define RSCAN0RFDF05L RSCAN0.RFDF05.UINT16[L]
#define RSCAN0RFDF05LL RSCAN0.RFDF05.UINT8[LL]
#define RSCAN0RFDF05LH RSCAN0.RFDF05.UINT8[LH]
#define RSCAN0RFDF05H RSCAN0.RFDF05.UINT16[H]
#define RSCAN0RFDF05HL RSCAN0.RFDF05.UINT8[HL]
#define RSCAN0RFDF05HH RSCAN0.RFDF05.UINT8[HH]
#define RSCAN0RFDF15 RSCAN0.RFDF15.UINT32
#define RSCAN0RFDF15L RSCAN0.RFDF15.UINT16[L]
#define RSCAN0RFDF15LL RSCAN0.RFDF15.UINT8[LL]
#define RSCAN0RFDF15LH RSCAN0.RFDF15.UINT8[LH]
#define RSCAN0RFDF15H RSCAN0.RFDF15.UINT16[H]
#define RSCAN0RFDF15HL RSCAN0.RFDF15.UINT8[HL]
#define RSCAN0RFDF15HH RSCAN0.RFDF15.UINT8[HH]
#define RSCAN0RFID6 RSCAN0.RFID6.UINT32
#define RSCAN0RFID6L RSCAN0.RFID6.UINT16[L]
#define RSCAN0RFID6LL RSCAN0.RFID6.UINT8[LL]
#define RSCAN0RFID6LH RSCAN0.RFID6.UINT8[LH]
#define RSCAN0RFID6H RSCAN0.RFID6.UINT16[H]
#define RSCAN0RFID6HL RSCAN0.RFID6.UINT8[HL]
#define RSCAN0RFID6HH RSCAN0.RFID6.UINT8[HH]
#define RSCAN0RFPTR6 RSCAN0.RFPTR6.UINT32
#define RSCAN0RFPTR6L RSCAN0.RFPTR6.UINT16[L]
#define RSCAN0RFPTR6LL RSCAN0.RFPTR6.UINT8[LL]
#define RSCAN0RFPTR6LH RSCAN0.RFPTR6.UINT8[LH]
#define RSCAN0RFPTR6H RSCAN0.RFPTR6.UINT16[H]
#define RSCAN0RFPTR6HL RSCAN0.RFPTR6.UINT8[HL]
#define RSCAN0RFPTR6HH RSCAN0.RFPTR6.UINT8[HH]
#define RSCAN0RFDF06 RSCAN0.RFDF06.UINT32
#define RSCAN0RFDF06L RSCAN0.RFDF06.UINT16[L]
#define RSCAN0RFDF06LL RSCAN0.RFDF06.UINT8[LL]
#define RSCAN0RFDF06LH RSCAN0.RFDF06.UINT8[LH]
#define RSCAN0RFDF06H RSCAN0.RFDF06.UINT16[H]
#define RSCAN0RFDF06HL RSCAN0.RFDF06.UINT8[HL]
#define RSCAN0RFDF06HH RSCAN0.RFDF06.UINT8[HH]
#define RSCAN0RFDF16 RSCAN0.RFDF16.UINT32
#define RSCAN0RFDF16L RSCAN0.RFDF16.UINT16[L]
#define RSCAN0RFDF16LL RSCAN0.RFDF16.UINT8[LL]
#define RSCAN0RFDF16LH RSCAN0.RFDF16.UINT8[LH]
#define RSCAN0RFDF16H RSCAN0.RFDF16.UINT16[H]
#define RSCAN0RFDF16HL RSCAN0.RFDF16.UINT8[HL]
#define RSCAN0RFDF16HH RSCAN0.RFDF16.UINT8[HH]
#define RSCAN0RFID7 RSCAN0.RFID7.UINT32
#define RSCAN0RFID7L RSCAN0.RFID7.UINT16[L]
#define RSCAN0RFID7LL RSCAN0.RFID7.UINT8[LL]
#define RSCAN0RFID7LH RSCAN0.RFID7.UINT8[LH]
#define RSCAN0RFID7H RSCAN0.RFID7.UINT16[H]
#define RSCAN0RFID7HL RSCAN0.RFID7.UINT8[HL]
#define RSCAN0RFID7HH RSCAN0.RFID7.UINT8[HH]
#define RSCAN0RFPTR7 RSCAN0.RFPTR7.UINT32
#define RSCAN0RFPTR7L RSCAN0.RFPTR7.UINT16[L]
#define RSCAN0RFPTR7LL RSCAN0.RFPTR7.UINT8[LL]
#define RSCAN0RFPTR7LH RSCAN0.RFPTR7.UINT8[LH]
#define RSCAN0RFPTR7H RSCAN0.RFPTR7.UINT16[H]
#define RSCAN0RFPTR7HL RSCAN0.RFPTR7.UINT8[HL]
#define RSCAN0RFPTR7HH RSCAN0.RFPTR7.UINT8[HH]
#define RSCAN0RFDF07 RSCAN0.RFDF07.UINT32
#define RSCAN0RFDF07L RSCAN0.RFDF07.UINT16[L]
#define RSCAN0RFDF07LL RSCAN0.RFDF07.UINT8[LL]
#define RSCAN0RFDF07LH RSCAN0.RFDF07.UINT8[LH]
#define RSCAN0RFDF07H RSCAN0.RFDF07.UINT16[H]
#define RSCAN0RFDF07HL RSCAN0.RFDF07.UINT8[HL]
#define RSCAN0RFDF07HH RSCAN0.RFDF07.UINT8[HH]
#define RSCAN0RFDF17 RSCAN0.RFDF17.UINT32
#define RSCAN0RFDF17L RSCAN0.RFDF17.UINT16[L]
#define RSCAN0RFDF17LL RSCAN0.RFDF17.UINT8[LL]
#define RSCAN0RFDF17LH RSCAN0.RFDF17.UINT8[LH]
#define RSCAN0RFDF17H RSCAN0.RFDF17.UINT16[H]
#define RSCAN0RFDF17HL RSCAN0.RFDF17.UINT8[HL]
#define RSCAN0RFDF17HH RSCAN0.RFDF17.UINT8[HH]
#define RSCAN0CFID0 RSCAN0.CFID0.UINT32
#define RSCAN0CFID0L RSCAN0.CFID0.UINT16[L]
#define RSCAN0CFID0LL RSCAN0.CFID0.UINT8[LL]
#define RSCAN0CFID0LH RSCAN0.CFID0.UINT8[LH]
#define RSCAN0CFID0H RSCAN0.CFID0.UINT16[H]
#define RSCAN0CFID0HL RSCAN0.CFID0.UINT8[HL]
#define RSCAN0CFID0HH RSCAN0.CFID0.UINT8[HH]
#define RSCAN0CFPTR0 RSCAN0.CFPTR0.UINT32
#define RSCAN0CFPTR0L RSCAN0.CFPTR0.UINT16[L]
#define RSCAN0CFPTR0LL RSCAN0.CFPTR0.UINT8[LL]
#define RSCAN0CFPTR0LH RSCAN0.CFPTR0.UINT8[LH]
#define RSCAN0CFPTR0H RSCAN0.CFPTR0.UINT16[H]
#define RSCAN0CFPTR0HL RSCAN0.CFPTR0.UINT8[HL]
#define RSCAN0CFPTR0HH RSCAN0.CFPTR0.UINT8[HH]
#define RSCAN0CFDF00 RSCAN0.CFDF00.UINT32
#define RSCAN0CFDF00L RSCAN0.CFDF00.UINT16[L]
#define RSCAN0CFDF00LL RSCAN0.CFDF00.UINT8[LL]
#define RSCAN0CFDF00LH RSCAN0.CFDF00.UINT8[LH]
#define RSCAN0CFDF00H RSCAN0.CFDF00.UINT16[H]
#define RSCAN0CFDF00HL RSCAN0.CFDF00.UINT8[HL]
#define RSCAN0CFDF00HH RSCAN0.CFDF00.UINT8[HH]
#define RSCAN0CFDF10 RSCAN0.CFDF10.UINT32
#define RSCAN0CFDF10L RSCAN0.CFDF10.UINT16[L]
#define RSCAN0CFDF10LL RSCAN0.CFDF10.UINT8[LL]
#define RSCAN0CFDF10LH RSCAN0.CFDF10.UINT8[LH]
#define RSCAN0CFDF10H RSCAN0.CFDF10.UINT16[H]
#define RSCAN0CFDF10HL RSCAN0.CFDF10.UINT8[HL]
#define RSCAN0CFDF10HH RSCAN0.CFDF10.UINT8[HH]
#define RSCAN0CFID1 RSCAN0.CFID1.UINT32
#define RSCAN0CFID1L RSCAN0.CFID1.UINT16[L]
#define RSCAN0CFID1LL RSCAN0.CFID1.UINT8[LL]
#define RSCAN0CFID1LH RSCAN0.CFID1.UINT8[LH]
#define RSCAN0CFID1H RSCAN0.CFID1.UINT16[H]
#define RSCAN0CFID1HL RSCAN0.CFID1.UINT8[HL]
#define RSCAN0CFID1HH RSCAN0.CFID1.UINT8[HH]
#define RSCAN0CFPTR1 RSCAN0.CFPTR1.UINT32
#define RSCAN0CFPTR1L RSCAN0.CFPTR1.UINT16[L]
#define RSCAN0CFPTR1LL RSCAN0.CFPTR1.UINT8[LL]
#define RSCAN0CFPTR1LH RSCAN0.CFPTR1.UINT8[LH]
#define RSCAN0CFPTR1H RSCAN0.CFPTR1.UINT16[H]
#define RSCAN0CFPTR1HL RSCAN0.CFPTR1.UINT8[HL]
#define RSCAN0CFPTR1HH RSCAN0.CFPTR1.UINT8[HH]
#define RSCAN0CFDF01 RSCAN0.CFDF01.UINT32
#define RSCAN0CFDF01L RSCAN0.CFDF01.UINT16[L]
#define RSCAN0CFDF01LL RSCAN0.CFDF01.UINT8[LL]
#define RSCAN0CFDF01LH RSCAN0.CFDF01.UINT8[LH]
#define RSCAN0CFDF01H RSCAN0.CFDF01.UINT16[H]
#define RSCAN0CFDF01HL RSCAN0.CFDF01.UINT8[HL]
#define RSCAN0CFDF01HH RSCAN0.CFDF01.UINT8[HH]
#define RSCAN0CFDF11 RSCAN0.CFDF11.UINT32
#define RSCAN0CFDF11L RSCAN0.CFDF11.UINT16[L]
#define RSCAN0CFDF11LL RSCAN0.CFDF11.UINT8[LL]
#define RSCAN0CFDF11LH RSCAN0.CFDF11.UINT8[LH]
#define RSCAN0CFDF11H RSCAN0.CFDF11.UINT16[H]
#define RSCAN0CFDF11HL RSCAN0.CFDF11.UINT8[HL]
#define RSCAN0CFDF11HH RSCAN0.CFDF11.UINT8[HH]
#define RSCAN0CFID2 RSCAN0.CFID2.UINT32
#define RSCAN0CFID2L RSCAN0.CFID2.UINT16[L]
#define RSCAN0CFID2LL RSCAN0.CFID2.UINT8[LL]
#define RSCAN0CFID2LH RSCAN0.CFID2.UINT8[LH]
#define RSCAN0CFID2H RSCAN0.CFID2.UINT16[H]
#define RSCAN0CFID2HL RSCAN0.CFID2.UINT8[HL]
#define RSCAN0CFID2HH RSCAN0.CFID2.UINT8[HH]
#define RSCAN0CFPTR2 RSCAN0.CFPTR2.UINT32
#define RSCAN0CFPTR2L RSCAN0.CFPTR2.UINT16[L]
#define RSCAN0CFPTR2LL RSCAN0.CFPTR2.UINT8[LL]
#define RSCAN0CFPTR2LH RSCAN0.CFPTR2.UINT8[LH]
#define RSCAN0CFPTR2H RSCAN0.CFPTR2.UINT16[H]
#define RSCAN0CFPTR2HL RSCAN0.CFPTR2.UINT8[HL]
#define RSCAN0CFPTR2HH RSCAN0.CFPTR2.UINT8[HH]
#define RSCAN0CFDF02 RSCAN0.CFDF02.UINT32
#define RSCAN0CFDF02L RSCAN0.CFDF02.UINT16[L]
#define RSCAN0CFDF02LL RSCAN0.CFDF02.UINT8[LL]
#define RSCAN0CFDF02LH RSCAN0.CFDF02.UINT8[LH]
#define RSCAN0CFDF02H RSCAN0.CFDF02.UINT16[H]
#define RSCAN0CFDF02HL RSCAN0.CFDF02.UINT8[HL]
#define RSCAN0CFDF02HH RSCAN0.CFDF02.UINT8[HH]
#define RSCAN0CFDF12 RSCAN0.CFDF12.UINT32
#define RSCAN0CFDF12L RSCAN0.CFDF12.UINT16[L]
#define RSCAN0CFDF12LL RSCAN0.CFDF12.UINT8[LL]
#define RSCAN0CFDF12LH RSCAN0.CFDF12.UINT8[LH]
#define RSCAN0CFDF12H RSCAN0.CFDF12.UINT16[H]
#define RSCAN0CFDF12HL RSCAN0.CFDF12.UINT8[HL]
#define RSCAN0CFDF12HH RSCAN0.CFDF12.UINT8[HH]
#define RSCAN0CFID3 RSCAN0.CFID3.UINT32
#define RSCAN0CFID3L RSCAN0.CFID3.UINT16[L]
#define RSCAN0CFID3LL RSCAN0.CFID3.UINT8[LL]
#define RSCAN0CFID3LH RSCAN0.CFID3.UINT8[LH]
#define RSCAN0CFID3H RSCAN0.CFID3.UINT16[H]
#define RSCAN0CFID3HL RSCAN0.CFID3.UINT8[HL]
#define RSCAN0CFID3HH RSCAN0.CFID3.UINT8[HH]
#define RSCAN0CFPTR3 RSCAN0.CFPTR3.UINT32
#define RSCAN0CFPTR3L RSCAN0.CFPTR3.UINT16[L]
#define RSCAN0CFPTR3LL RSCAN0.CFPTR3.UINT8[LL]
#define RSCAN0CFPTR3LH RSCAN0.CFPTR3.UINT8[LH]
#define RSCAN0CFPTR3H RSCAN0.CFPTR3.UINT16[H]
#define RSCAN0CFPTR3HL RSCAN0.CFPTR3.UINT8[HL]
#define RSCAN0CFPTR3HH RSCAN0.CFPTR3.UINT8[HH]
#define RSCAN0CFDF03 RSCAN0.CFDF03.UINT32
#define RSCAN0CFDF03L RSCAN0.CFDF03.UINT16[L]
#define RSCAN0CFDF03LL RSCAN0.CFDF03.UINT8[LL]
#define RSCAN0CFDF03LH RSCAN0.CFDF03.UINT8[LH]
#define RSCAN0CFDF03H RSCAN0.CFDF03.UINT16[H]
#define RSCAN0CFDF03HL RSCAN0.CFDF03.UINT8[HL]
#define RSCAN0CFDF03HH RSCAN0.CFDF03.UINT8[HH]
#define RSCAN0CFDF13 RSCAN0.CFDF13.UINT32
#define RSCAN0CFDF13L RSCAN0.CFDF13.UINT16[L]
#define RSCAN0CFDF13LL RSCAN0.CFDF13.UINT8[LL]
#define RSCAN0CFDF13LH RSCAN0.CFDF13.UINT8[LH]
#define RSCAN0CFDF13H RSCAN0.CFDF13.UINT16[H]
#define RSCAN0CFDF13HL RSCAN0.CFDF13.UINT8[HL]
#define RSCAN0CFDF13HH RSCAN0.CFDF13.UINT8[HH]
#define RSCAN0CFID4 RSCAN0.CFID4.UINT32
#define RSCAN0CFID4L RSCAN0.CFID4.UINT16[L]
#define RSCAN0CFID4LL RSCAN0.CFID4.UINT8[LL]
#define RSCAN0CFID4LH RSCAN0.CFID4.UINT8[LH]
#define RSCAN0CFID4H RSCAN0.CFID4.UINT16[H]
#define RSCAN0CFID4HL RSCAN0.CFID4.UINT8[HL]
#define RSCAN0CFID4HH RSCAN0.CFID4.UINT8[HH]
#define RSCAN0CFPTR4 RSCAN0.CFPTR4.UINT32
#define RSCAN0CFPTR4L RSCAN0.CFPTR4.UINT16[L]
#define RSCAN0CFPTR4LL RSCAN0.CFPTR4.UINT8[LL]
#define RSCAN0CFPTR4LH RSCAN0.CFPTR4.UINT8[LH]
#define RSCAN0CFPTR4H RSCAN0.CFPTR4.UINT16[H]
#define RSCAN0CFPTR4HL RSCAN0.CFPTR4.UINT8[HL]
#define RSCAN0CFPTR4HH RSCAN0.CFPTR4.UINT8[HH]
#define RSCAN0CFDF04 RSCAN0.CFDF04.UINT32
#define RSCAN0CFDF04L RSCAN0.CFDF04.UINT16[L]
#define RSCAN0CFDF04LL RSCAN0.CFDF04.UINT8[LL]
#define RSCAN0CFDF04LH RSCAN0.CFDF04.UINT8[LH]
#define RSCAN0CFDF04H RSCAN0.CFDF04.UINT16[H]
#define RSCAN0CFDF04HL RSCAN0.CFDF04.UINT8[HL]
#define RSCAN0CFDF04HH RSCAN0.CFDF04.UINT8[HH]
#define RSCAN0CFDF14 RSCAN0.CFDF14.UINT32
#define RSCAN0CFDF14L RSCAN0.CFDF14.UINT16[L]
#define RSCAN0CFDF14LL RSCAN0.CFDF14.UINT8[LL]
#define RSCAN0CFDF14LH RSCAN0.CFDF14.UINT8[LH]
#define RSCAN0CFDF14H RSCAN0.CFDF14.UINT16[H]
#define RSCAN0CFDF14HL RSCAN0.CFDF14.UINT8[HL]
#define RSCAN0CFDF14HH RSCAN0.CFDF14.UINT8[HH]
#define RSCAN0CFID5 RSCAN0.CFID5.UINT32
#define RSCAN0CFID5L RSCAN0.CFID5.UINT16[L]
#define RSCAN0CFID5LL RSCAN0.CFID5.UINT8[LL]
#define RSCAN0CFID5LH RSCAN0.CFID5.UINT8[LH]
#define RSCAN0CFID5H RSCAN0.CFID5.UINT16[H]
#define RSCAN0CFID5HL RSCAN0.CFID5.UINT8[HL]
#define RSCAN0CFID5HH RSCAN0.CFID5.UINT8[HH]
#define RSCAN0CFPTR5 RSCAN0.CFPTR5.UINT32
#define RSCAN0CFPTR5L RSCAN0.CFPTR5.UINT16[L]
#define RSCAN0CFPTR5LL RSCAN0.CFPTR5.UINT8[LL]
#define RSCAN0CFPTR5LH RSCAN0.CFPTR5.UINT8[LH]
#define RSCAN0CFPTR5H RSCAN0.CFPTR5.UINT16[H]
#define RSCAN0CFPTR5HL RSCAN0.CFPTR5.UINT8[HL]
#define RSCAN0CFPTR5HH RSCAN0.CFPTR5.UINT8[HH]
#define RSCAN0CFDF05 RSCAN0.CFDF05.UINT32
#define RSCAN0CFDF05L RSCAN0.CFDF05.UINT16[L]
#define RSCAN0CFDF05LL RSCAN0.CFDF05.UINT8[LL]
#define RSCAN0CFDF05LH RSCAN0.CFDF05.UINT8[LH]
#define RSCAN0CFDF05H RSCAN0.CFDF05.UINT16[H]
#define RSCAN0CFDF05HL RSCAN0.CFDF05.UINT8[HL]
#define RSCAN0CFDF05HH RSCAN0.CFDF05.UINT8[HH]
#define RSCAN0CFDF15 RSCAN0.CFDF15.UINT32
#define RSCAN0CFDF15L RSCAN0.CFDF15.UINT16[L]
#define RSCAN0CFDF15LL RSCAN0.CFDF15.UINT8[LL]
#define RSCAN0CFDF15LH RSCAN0.CFDF15.UINT8[LH]
#define RSCAN0CFDF15H RSCAN0.CFDF15.UINT16[H]
#define RSCAN0CFDF15HL RSCAN0.CFDF15.UINT8[HL]
#define RSCAN0CFDF15HH RSCAN0.CFDF15.UINT8[HH]
#define RSCAN0CFID6 RSCAN0.CFID6.UINT32
#define RSCAN0CFID6L RSCAN0.CFID6.UINT16[L]
#define RSCAN0CFID6LL RSCAN0.CFID6.UINT8[LL]
#define RSCAN0CFID6LH RSCAN0.CFID6.UINT8[LH]
#define RSCAN0CFID6H RSCAN0.CFID6.UINT16[H]
#define RSCAN0CFID6HL RSCAN0.CFID6.UINT8[HL]
#define RSCAN0CFID6HH RSCAN0.CFID6.UINT8[HH]
#define RSCAN0CFPTR6 RSCAN0.CFPTR6.UINT32
#define RSCAN0CFPTR6L RSCAN0.CFPTR6.UINT16[L]
#define RSCAN0CFPTR6LL RSCAN0.CFPTR6.UINT8[LL]
#define RSCAN0CFPTR6LH RSCAN0.CFPTR6.UINT8[LH]
#define RSCAN0CFPTR6H RSCAN0.CFPTR6.UINT16[H]
#define RSCAN0CFPTR6HL RSCAN0.CFPTR6.UINT8[HL]
#define RSCAN0CFPTR6HH RSCAN0.CFPTR6.UINT8[HH]
#define RSCAN0CFDF06 RSCAN0.CFDF06.UINT32
#define RSCAN0CFDF06L RSCAN0.CFDF06.UINT16[L]
#define RSCAN0CFDF06LL RSCAN0.CFDF06.UINT8[LL]
#define RSCAN0CFDF06LH RSCAN0.CFDF06.UINT8[LH]
#define RSCAN0CFDF06H RSCAN0.CFDF06.UINT16[H]
#define RSCAN0CFDF06HL RSCAN0.CFDF06.UINT8[HL]
#define RSCAN0CFDF06HH RSCAN0.CFDF06.UINT8[HH]
#define RSCAN0CFDF16 RSCAN0.CFDF16.UINT32
#define RSCAN0CFDF16L RSCAN0.CFDF16.UINT16[L]
#define RSCAN0CFDF16LL RSCAN0.CFDF16.UINT8[LL]
#define RSCAN0CFDF16LH RSCAN0.CFDF16.UINT8[LH]
#define RSCAN0CFDF16H RSCAN0.CFDF16.UINT16[H]
#define RSCAN0CFDF16HL RSCAN0.CFDF16.UINT8[HL]
#define RSCAN0CFDF16HH RSCAN0.CFDF16.UINT8[HH]
#define RSCAN0CFID7 RSCAN0.CFID7.UINT32
#define RSCAN0CFID7L RSCAN0.CFID7.UINT16[L]
#define RSCAN0CFID7LL RSCAN0.CFID7.UINT8[LL]
#define RSCAN0CFID7LH RSCAN0.CFID7.UINT8[LH]
#define RSCAN0CFID7H RSCAN0.CFID7.UINT16[H]
#define RSCAN0CFID7HL RSCAN0.CFID7.UINT8[HL]
#define RSCAN0CFID7HH RSCAN0.CFID7.UINT8[HH]
#define RSCAN0CFPTR7 RSCAN0.CFPTR7.UINT32
#define RSCAN0CFPTR7L RSCAN0.CFPTR7.UINT16[L]
#define RSCAN0CFPTR7LL RSCAN0.CFPTR7.UINT8[LL]
#define RSCAN0CFPTR7LH RSCAN0.CFPTR7.UINT8[LH]
#define RSCAN0CFPTR7H RSCAN0.CFPTR7.UINT16[H]
#define RSCAN0CFPTR7HL RSCAN0.CFPTR7.UINT8[HL]
#define RSCAN0CFPTR7HH RSCAN0.CFPTR7.UINT8[HH]
#define RSCAN0CFDF07 RSCAN0.CFDF07.UINT32
#define RSCAN0CFDF07L RSCAN0.CFDF07.UINT16[L]
#define RSCAN0CFDF07LL RSCAN0.CFDF07.UINT8[LL]
#define RSCAN0CFDF07LH RSCAN0.CFDF07.UINT8[LH]
#define RSCAN0CFDF07H RSCAN0.CFDF07.UINT16[H]
#define RSCAN0CFDF07HL RSCAN0.CFDF07.UINT8[HL]
#define RSCAN0CFDF07HH RSCAN0.CFDF07.UINT8[HH]
#define RSCAN0CFDF17 RSCAN0.CFDF17.UINT32
#define RSCAN0CFDF17L RSCAN0.CFDF17.UINT16[L]
#define RSCAN0CFDF17LL RSCAN0.CFDF17.UINT8[LL]
#define RSCAN0CFDF17LH RSCAN0.CFDF17.UINT8[LH]
#define RSCAN0CFDF17H RSCAN0.CFDF17.UINT16[H]
#define RSCAN0CFDF17HL RSCAN0.CFDF17.UINT8[HL]
#define RSCAN0CFDF17HH RSCAN0.CFDF17.UINT8[HH]
#define RSCAN0CFID8 RSCAN0.CFID8.UINT32
#define RSCAN0CFID8L RSCAN0.CFID8.UINT16[L]
#define RSCAN0CFID8LL RSCAN0.CFID8.UINT8[LL]
#define RSCAN0CFID8LH RSCAN0.CFID8.UINT8[LH]
#define RSCAN0CFID8H RSCAN0.CFID8.UINT16[H]
#define RSCAN0CFID8HL RSCAN0.CFID8.UINT8[HL]
#define RSCAN0CFID8HH RSCAN0.CFID8.UINT8[HH]
#define RSCAN0CFPTR8 RSCAN0.CFPTR8.UINT32
#define RSCAN0CFPTR8L RSCAN0.CFPTR8.UINT16[L]
#define RSCAN0CFPTR8LL RSCAN0.CFPTR8.UINT8[LL]
#define RSCAN0CFPTR8LH RSCAN0.CFPTR8.UINT8[LH]
#define RSCAN0CFPTR8H RSCAN0.CFPTR8.UINT16[H]
#define RSCAN0CFPTR8HL RSCAN0.CFPTR8.UINT8[HL]
#define RSCAN0CFPTR8HH RSCAN0.CFPTR8.UINT8[HH]
#define RSCAN0CFDF08 RSCAN0.CFDF08.UINT32
#define RSCAN0CFDF08L RSCAN0.CFDF08.UINT16[L]
#define RSCAN0CFDF08LL RSCAN0.CFDF08.UINT8[LL]
#define RSCAN0CFDF08LH RSCAN0.CFDF08.UINT8[LH]
#define RSCAN0CFDF08H RSCAN0.CFDF08.UINT16[H]
#define RSCAN0CFDF08HL RSCAN0.CFDF08.UINT8[HL]
#define RSCAN0CFDF08HH RSCAN0.CFDF08.UINT8[HH]
#define RSCAN0CFDF18 RSCAN0.CFDF18.UINT32
#define RSCAN0CFDF18L RSCAN0.CFDF18.UINT16[L]
#define RSCAN0CFDF18LL RSCAN0.CFDF18.UINT8[LL]
#define RSCAN0CFDF18LH RSCAN0.CFDF18.UINT8[LH]
#define RSCAN0CFDF18H RSCAN0.CFDF18.UINT16[H]
#define RSCAN0CFDF18HL RSCAN0.CFDF18.UINT8[HL]
#define RSCAN0CFDF18HH RSCAN0.CFDF18.UINT8[HH]
#define RSCAN0CFID9 RSCAN0.CFID9.UINT32
#define RSCAN0CFID9L RSCAN0.CFID9.UINT16[L]
#define RSCAN0CFID9LL RSCAN0.CFID9.UINT8[LL]
#define RSCAN0CFID9LH RSCAN0.CFID9.UINT8[LH]
#define RSCAN0CFID9H RSCAN0.CFID9.UINT16[H]
#define RSCAN0CFID9HL RSCAN0.CFID9.UINT8[HL]
#define RSCAN0CFID9HH RSCAN0.CFID9.UINT8[HH]
#define RSCAN0CFPTR9 RSCAN0.CFPTR9.UINT32
#define RSCAN0CFPTR9L RSCAN0.CFPTR9.UINT16[L]
#define RSCAN0CFPTR9LL RSCAN0.CFPTR9.UINT8[LL]
#define RSCAN0CFPTR9LH RSCAN0.CFPTR9.UINT8[LH]
#define RSCAN0CFPTR9H RSCAN0.CFPTR9.UINT16[H]
#define RSCAN0CFPTR9HL RSCAN0.CFPTR9.UINT8[HL]
#define RSCAN0CFPTR9HH RSCAN0.CFPTR9.UINT8[HH]
#define RSCAN0CFDF09 RSCAN0.CFDF09.UINT32
#define RSCAN0CFDF09L RSCAN0.CFDF09.UINT16[L]
#define RSCAN0CFDF09LL RSCAN0.CFDF09.UINT8[LL]
#define RSCAN0CFDF09LH RSCAN0.CFDF09.UINT8[LH]
#define RSCAN0CFDF09H RSCAN0.CFDF09.UINT16[H]
#define RSCAN0CFDF09HL RSCAN0.CFDF09.UINT8[HL]
#define RSCAN0CFDF09HH RSCAN0.CFDF09.UINT8[HH]
#define RSCAN0CFDF19 RSCAN0.CFDF19.UINT32
#define RSCAN0CFDF19L RSCAN0.CFDF19.UINT16[L]
#define RSCAN0CFDF19LL RSCAN0.CFDF19.UINT8[LL]
#define RSCAN0CFDF19LH RSCAN0.CFDF19.UINT8[LH]
#define RSCAN0CFDF19H RSCAN0.CFDF19.UINT16[H]
#define RSCAN0CFDF19HL RSCAN0.CFDF19.UINT8[HL]
#define RSCAN0CFDF19HH RSCAN0.CFDF19.UINT8[HH]
#define RSCAN0CFID10 RSCAN0.CFID10.UINT32
#define RSCAN0CFID10L RSCAN0.CFID10.UINT16[L]
#define RSCAN0CFID10LL RSCAN0.CFID10.UINT8[LL]
#define RSCAN0CFID10LH RSCAN0.CFID10.UINT8[LH]
#define RSCAN0CFID10H RSCAN0.CFID10.UINT16[H]
#define RSCAN0CFID10HL RSCAN0.CFID10.UINT8[HL]
#define RSCAN0CFID10HH RSCAN0.CFID10.UINT8[HH]
#define RSCAN0CFPTR10 RSCAN0.CFPTR10.UINT32
#define RSCAN0CFPTR10L RSCAN0.CFPTR10.UINT16[L]
#define RSCAN0CFPTR10LL RSCAN0.CFPTR10.UINT8[LL]
#define RSCAN0CFPTR10LH RSCAN0.CFPTR10.UINT8[LH]
#define RSCAN0CFPTR10H RSCAN0.CFPTR10.UINT16[H]
#define RSCAN0CFPTR10HL RSCAN0.CFPTR10.UINT8[HL]
#define RSCAN0CFPTR10HH RSCAN0.CFPTR10.UINT8[HH]
#define RSCAN0CFDF010 RSCAN0.CFDF010.UINT32
#define RSCAN0CFDF010L RSCAN0.CFDF010.UINT16[L]
#define RSCAN0CFDF010LL RSCAN0.CFDF010.UINT8[LL]
#define RSCAN0CFDF010LH RSCAN0.CFDF010.UINT8[LH]
#define RSCAN0CFDF010H RSCAN0.CFDF010.UINT16[H]
#define RSCAN0CFDF010HL RSCAN0.CFDF010.UINT8[HL]
#define RSCAN0CFDF010HH RSCAN0.CFDF010.UINT8[HH]
#define RSCAN0CFDF110 RSCAN0.CFDF110.UINT32
#define RSCAN0CFDF110L RSCAN0.CFDF110.UINT16[L]
#define RSCAN0CFDF110LL RSCAN0.CFDF110.UINT8[LL]
#define RSCAN0CFDF110LH RSCAN0.CFDF110.UINT8[LH]
#define RSCAN0CFDF110H RSCAN0.CFDF110.UINT16[H]
#define RSCAN0CFDF110HL RSCAN0.CFDF110.UINT8[HL]
#define RSCAN0CFDF110HH RSCAN0.CFDF110.UINT8[HH]
#define RSCAN0CFID11 RSCAN0.CFID11.UINT32
#define RSCAN0CFID11L RSCAN0.CFID11.UINT16[L]
#define RSCAN0CFID11LL RSCAN0.CFID11.UINT8[LL]
#define RSCAN0CFID11LH RSCAN0.CFID11.UINT8[LH]
#define RSCAN0CFID11H RSCAN0.CFID11.UINT16[H]
#define RSCAN0CFID11HL RSCAN0.CFID11.UINT8[HL]
#define RSCAN0CFID11HH RSCAN0.CFID11.UINT8[HH]
#define RSCAN0CFPTR11 RSCAN0.CFPTR11.UINT32
#define RSCAN0CFPTR11L RSCAN0.CFPTR11.UINT16[L]
#define RSCAN0CFPTR11LL RSCAN0.CFPTR11.UINT8[LL]
#define RSCAN0CFPTR11LH RSCAN0.CFPTR11.UINT8[LH]
#define RSCAN0CFPTR11H RSCAN0.CFPTR11.UINT16[H]
#define RSCAN0CFPTR11HL RSCAN0.CFPTR11.UINT8[HL]
#define RSCAN0CFPTR11HH RSCAN0.CFPTR11.UINT8[HH]
#define RSCAN0CFDF011 RSCAN0.CFDF011.UINT32
#define RSCAN0CFDF011L RSCAN0.CFDF011.UINT16[L]
#define RSCAN0CFDF011LL RSCAN0.CFDF011.UINT8[LL]
#define RSCAN0CFDF011LH RSCAN0.CFDF011.UINT8[LH]
#define RSCAN0CFDF011H RSCAN0.CFDF011.UINT16[H]
#define RSCAN0CFDF011HL RSCAN0.CFDF011.UINT8[HL]
#define RSCAN0CFDF011HH RSCAN0.CFDF011.UINT8[HH]
#define RSCAN0CFDF111 RSCAN0.CFDF111.UINT32
#define RSCAN0CFDF111L RSCAN0.CFDF111.UINT16[L]
#define RSCAN0CFDF111LL RSCAN0.CFDF111.UINT8[LL]
#define RSCAN0CFDF111LH RSCAN0.CFDF111.UINT8[LH]
#define RSCAN0CFDF111H RSCAN0.CFDF111.UINT16[H]
#define RSCAN0CFDF111HL RSCAN0.CFDF111.UINT8[HL]
#define RSCAN0CFDF111HH RSCAN0.CFDF111.UINT8[HH]
#define RSCAN0CFID12 RSCAN0.CFID12.UINT32
#define RSCAN0CFID12L RSCAN0.CFID12.UINT16[L]
#define RSCAN0CFID12LL RSCAN0.CFID12.UINT8[LL]
#define RSCAN0CFID12LH RSCAN0.CFID12.UINT8[LH]
#define RSCAN0CFID12H RSCAN0.CFID12.UINT16[H]
#define RSCAN0CFID12HL RSCAN0.CFID12.UINT8[HL]
#define RSCAN0CFID12HH RSCAN0.CFID12.UINT8[HH]
#define RSCAN0CFPTR12 RSCAN0.CFPTR12.UINT32
#define RSCAN0CFPTR12L RSCAN0.CFPTR12.UINT16[L]
#define RSCAN0CFPTR12LL RSCAN0.CFPTR12.UINT8[LL]
#define RSCAN0CFPTR12LH RSCAN0.CFPTR12.UINT8[LH]
#define RSCAN0CFPTR12H RSCAN0.CFPTR12.UINT16[H]
#define RSCAN0CFPTR12HL RSCAN0.CFPTR12.UINT8[HL]
#define RSCAN0CFPTR12HH RSCAN0.CFPTR12.UINT8[HH]
#define RSCAN0CFDF012 RSCAN0.CFDF012.UINT32
#define RSCAN0CFDF012L RSCAN0.CFDF012.UINT16[L]
#define RSCAN0CFDF012LL RSCAN0.CFDF012.UINT8[LL]
#define RSCAN0CFDF012LH RSCAN0.CFDF012.UINT8[LH]
#define RSCAN0CFDF012H RSCAN0.CFDF012.UINT16[H]
#define RSCAN0CFDF012HL RSCAN0.CFDF012.UINT8[HL]
#define RSCAN0CFDF012HH RSCAN0.CFDF012.UINT8[HH]
#define RSCAN0CFDF112 RSCAN0.CFDF112.UINT32
#define RSCAN0CFDF112L RSCAN0.CFDF112.UINT16[L]
#define RSCAN0CFDF112LL RSCAN0.CFDF112.UINT8[LL]
#define RSCAN0CFDF112LH RSCAN0.CFDF112.UINT8[LH]
#define RSCAN0CFDF112H RSCAN0.CFDF112.UINT16[H]
#define RSCAN0CFDF112HL RSCAN0.CFDF112.UINT8[HL]
#define RSCAN0CFDF112HH RSCAN0.CFDF112.UINT8[HH]
#define RSCAN0CFID13 RSCAN0.CFID13.UINT32
#define RSCAN0CFID13L RSCAN0.CFID13.UINT16[L]
#define RSCAN0CFID13LL RSCAN0.CFID13.UINT8[LL]
#define RSCAN0CFID13LH RSCAN0.CFID13.UINT8[LH]
#define RSCAN0CFID13H RSCAN0.CFID13.UINT16[H]
#define RSCAN0CFID13HL RSCAN0.CFID13.UINT8[HL]
#define RSCAN0CFID13HH RSCAN0.CFID13.UINT8[HH]
#define RSCAN0CFPTR13 RSCAN0.CFPTR13.UINT32
#define RSCAN0CFPTR13L RSCAN0.CFPTR13.UINT16[L]
#define RSCAN0CFPTR13LL RSCAN0.CFPTR13.UINT8[LL]
#define RSCAN0CFPTR13LH RSCAN0.CFPTR13.UINT8[LH]
#define RSCAN0CFPTR13H RSCAN0.CFPTR13.UINT16[H]
#define RSCAN0CFPTR13HL RSCAN0.CFPTR13.UINT8[HL]
#define RSCAN0CFPTR13HH RSCAN0.CFPTR13.UINT8[HH]
#define RSCAN0CFDF013 RSCAN0.CFDF013.UINT32
#define RSCAN0CFDF013L RSCAN0.CFDF013.UINT16[L]
#define RSCAN0CFDF013LL RSCAN0.CFDF013.UINT8[LL]
#define RSCAN0CFDF013LH RSCAN0.CFDF013.UINT8[LH]
#define RSCAN0CFDF013H RSCAN0.CFDF013.UINT16[H]
#define RSCAN0CFDF013HL RSCAN0.CFDF013.UINT8[HL]
#define RSCAN0CFDF013HH RSCAN0.CFDF013.UINT8[HH]
#define RSCAN0CFDF113 RSCAN0.CFDF113.UINT32
#define RSCAN0CFDF113L RSCAN0.CFDF113.UINT16[L]
#define RSCAN0CFDF113LL RSCAN0.CFDF113.UINT8[LL]
#define RSCAN0CFDF113LH RSCAN0.CFDF113.UINT8[LH]
#define RSCAN0CFDF113H RSCAN0.CFDF113.UINT16[H]
#define RSCAN0CFDF113HL RSCAN0.CFDF113.UINT8[HL]
#define RSCAN0CFDF113HH RSCAN0.CFDF113.UINT8[HH]
#define RSCAN0CFID14 RSCAN0.CFID14.UINT32
#define RSCAN0CFID14L RSCAN0.CFID14.UINT16[L]
#define RSCAN0CFID14LL RSCAN0.CFID14.UINT8[LL]
#define RSCAN0CFID14LH RSCAN0.CFID14.UINT8[LH]
#define RSCAN0CFID14H RSCAN0.CFID14.UINT16[H]
#define RSCAN0CFID14HL RSCAN0.CFID14.UINT8[HL]
#define RSCAN0CFID14HH RSCAN0.CFID14.UINT8[HH]
#define RSCAN0CFPTR14 RSCAN0.CFPTR14.UINT32
#define RSCAN0CFPTR14L RSCAN0.CFPTR14.UINT16[L]
#define RSCAN0CFPTR14LL RSCAN0.CFPTR14.UINT8[LL]
#define RSCAN0CFPTR14LH RSCAN0.CFPTR14.UINT8[LH]
#define RSCAN0CFPTR14H RSCAN0.CFPTR14.UINT16[H]
#define RSCAN0CFPTR14HL RSCAN0.CFPTR14.UINT8[HL]
#define RSCAN0CFPTR14HH RSCAN0.CFPTR14.UINT8[HH]
#define RSCAN0CFDF014 RSCAN0.CFDF014.UINT32
#define RSCAN0CFDF014L RSCAN0.CFDF014.UINT16[L]
#define RSCAN0CFDF014LL RSCAN0.CFDF014.UINT8[LL]
#define RSCAN0CFDF014LH RSCAN0.CFDF014.UINT8[LH]
#define RSCAN0CFDF014H RSCAN0.CFDF014.UINT16[H]
#define RSCAN0CFDF014HL RSCAN0.CFDF014.UINT8[HL]
#define RSCAN0CFDF014HH RSCAN0.CFDF014.UINT8[HH]
#define RSCAN0CFDF114 RSCAN0.CFDF114.UINT32
#define RSCAN0CFDF114L RSCAN0.CFDF114.UINT16[L]
#define RSCAN0CFDF114LL RSCAN0.CFDF114.UINT8[LL]
#define RSCAN0CFDF114LH RSCAN0.CFDF114.UINT8[LH]
#define RSCAN0CFDF114H RSCAN0.CFDF114.UINT16[H]
#define RSCAN0CFDF114HL RSCAN0.CFDF114.UINT8[HL]
#define RSCAN0CFDF114HH RSCAN0.CFDF114.UINT8[HH]
#define RSCAN0CFID15 RSCAN0.CFID15.UINT32
#define RSCAN0CFID15L RSCAN0.CFID15.UINT16[L]
#define RSCAN0CFID15LL RSCAN0.CFID15.UINT8[LL]
#define RSCAN0CFID15LH RSCAN0.CFID15.UINT8[LH]
#define RSCAN0CFID15H RSCAN0.CFID15.UINT16[H]
#define RSCAN0CFID15HL RSCAN0.CFID15.UINT8[HL]
#define RSCAN0CFID15HH RSCAN0.CFID15.UINT8[HH]
#define RSCAN0CFPTR15 RSCAN0.CFPTR15.UINT32
#define RSCAN0CFPTR15L RSCAN0.CFPTR15.UINT16[L]
#define RSCAN0CFPTR15LL RSCAN0.CFPTR15.UINT8[LL]
#define RSCAN0CFPTR15LH RSCAN0.CFPTR15.UINT8[LH]
#define RSCAN0CFPTR15H RSCAN0.CFPTR15.UINT16[H]
#define RSCAN0CFPTR15HL RSCAN0.CFPTR15.UINT8[HL]
#define RSCAN0CFPTR15HH RSCAN0.CFPTR15.UINT8[HH]
#define RSCAN0CFDF015 RSCAN0.CFDF015.UINT32
#define RSCAN0CFDF015L RSCAN0.CFDF015.UINT16[L]
#define RSCAN0CFDF015LL RSCAN0.CFDF015.UINT8[LL]
#define RSCAN0CFDF015LH RSCAN0.CFDF015.UINT8[LH]
#define RSCAN0CFDF015H RSCAN0.CFDF015.UINT16[H]
#define RSCAN0CFDF015HL RSCAN0.CFDF015.UINT8[HL]
#define RSCAN0CFDF015HH RSCAN0.CFDF015.UINT8[HH]
#define RSCAN0CFDF115 RSCAN0.CFDF115.UINT32
#define RSCAN0CFDF115L RSCAN0.CFDF115.UINT16[L]
#define RSCAN0CFDF115LL RSCAN0.CFDF115.UINT8[LL]
#define RSCAN0CFDF115LH RSCAN0.CFDF115.UINT8[LH]
#define RSCAN0CFDF115H RSCAN0.CFDF115.UINT16[H]
#define RSCAN0CFDF115HL RSCAN0.CFDF115.UINT8[HL]
#define RSCAN0CFDF115HH RSCAN0.CFDF115.UINT8[HH]
#define RSCAN0CFID16 RSCAN0.CFID16.UINT32
#define RSCAN0CFID16L RSCAN0.CFID16.UINT16[L]
#define RSCAN0CFID16LL RSCAN0.CFID16.UINT8[LL]
#define RSCAN0CFID16LH RSCAN0.CFID16.UINT8[LH]
#define RSCAN0CFID16H RSCAN0.CFID16.UINT16[H]
#define RSCAN0CFID16HL RSCAN0.CFID16.UINT8[HL]
#define RSCAN0CFID16HH RSCAN0.CFID16.UINT8[HH]
#define RSCAN0CFPTR16 RSCAN0.CFPTR16.UINT32
#define RSCAN0CFPTR16L RSCAN0.CFPTR16.UINT16[L]
#define RSCAN0CFPTR16LL RSCAN0.CFPTR16.UINT8[LL]
#define RSCAN0CFPTR16LH RSCAN0.CFPTR16.UINT8[LH]
#define RSCAN0CFPTR16H RSCAN0.CFPTR16.UINT16[H]
#define RSCAN0CFPTR16HL RSCAN0.CFPTR16.UINT8[HL]
#define RSCAN0CFPTR16HH RSCAN0.CFPTR16.UINT8[HH]
#define RSCAN0CFDF016 RSCAN0.CFDF016.UINT32
#define RSCAN0CFDF016L RSCAN0.CFDF016.UINT16[L]
#define RSCAN0CFDF016LL RSCAN0.CFDF016.UINT8[LL]
#define RSCAN0CFDF016LH RSCAN0.CFDF016.UINT8[LH]
#define RSCAN0CFDF016H RSCAN0.CFDF016.UINT16[H]
#define RSCAN0CFDF016HL RSCAN0.CFDF016.UINT8[HL]
#define RSCAN0CFDF016HH RSCAN0.CFDF016.UINT8[HH]
#define RSCAN0CFDF116 RSCAN0.CFDF116.UINT32
#define RSCAN0CFDF116L RSCAN0.CFDF116.UINT16[L]
#define RSCAN0CFDF116LL RSCAN0.CFDF116.UINT8[LL]
#define RSCAN0CFDF116LH RSCAN0.CFDF116.UINT8[LH]
#define RSCAN0CFDF116H RSCAN0.CFDF116.UINT16[H]
#define RSCAN0CFDF116HL RSCAN0.CFDF116.UINT8[HL]
#define RSCAN0CFDF116HH RSCAN0.CFDF116.UINT8[HH]
#define RSCAN0CFID17 RSCAN0.CFID17.UINT32
#define RSCAN0CFID17L RSCAN0.CFID17.UINT16[L]
#define RSCAN0CFID17LL RSCAN0.CFID17.UINT8[LL]
#define RSCAN0CFID17LH RSCAN0.CFID17.UINT8[LH]
#define RSCAN0CFID17H RSCAN0.CFID17.UINT16[H]
#define RSCAN0CFID17HL RSCAN0.CFID17.UINT8[HL]
#define RSCAN0CFID17HH RSCAN0.CFID17.UINT8[HH]
#define RSCAN0CFPTR17 RSCAN0.CFPTR17.UINT32
#define RSCAN0CFPTR17L RSCAN0.CFPTR17.UINT16[L]
#define RSCAN0CFPTR17LL RSCAN0.CFPTR17.UINT8[LL]
#define RSCAN0CFPTR17LH RSCAN0.CFPTR17.UINT8[LH]
#define RSCAN0CFPTR17H RSCAN0.CFPTR17.UINT16[H]
#define RSCAN0CFPTR17HL RSCAN0.CFPTR17.UINT8[HL]
#define RSCAN0CFPTR17HH RSCAN0.CFPTR17.UINT8[HH]
#define RSCAN0CFDF017 RSCAN0.CFDF017.UINT32
#define RSCAN0CFDF017L RSCAN0.CFDF017.UINT16[L]
#define RSCAN0CFDF017LL RSCAN0.CFDF017.UINT8[LL]
#define RSCAN0CFDF017LH RSCAN0.CFDF017.UINT8[LH]
#define RSCAN0CFDF017H RSCAN0.CFDF017.UINT16[H]
#define RSCAN0CFDF017HL RSCAN0.CFDF017.UINT8[HL]
#define RSCAN0CFDF017HH RSCAN0.CFDF017.UINT8[HH]
#define RSCAN0CFDF117 RSCAN0.CFDF117.UINT32
#define RSCAN0CFDF117L RSCAN0.CFDF117.UINT16[L]
#define RSCAN0CFDF117LL RSCAN0.CFDF117.UINT8[LL]
#define RSCAN0CFDF117LH RSCAN0.CFDF117.UINT8[LH]
#define RSCAN0CFDF117H RSCAN0.CFDF117.UINT16[H]
#define RSCAN0CFDF117HL RSCAN0.CFDF117.UINT8[HL]
#define RSCAN0CFDF117HH RSCAN0.CFDF117.UINT8[HH]
#define RSCAN0TMID0 RSCAN0.TMID0.UINT32
#define RSCAN0TMID0L RSCAN0.TMID0.UINT16[L]
#define RSCAN0TMID0LL RSCAN0.TMID0.UINT8[LL]
#define RSCAN0TMID0LH RSCAN0.TMID0.UINT8[LH]
#define RSCAN0TMID0H RSCAN0.TMID0.UINT16[H]
#define RSCAN0TMID0HL RSCAN0.TMID0.UINT8[HL]
#define RSCAN0TMID0HH RSCAN0.TMID0.UINT8[HH]
#define RSCAN0TMPTR0 RSCAN0.TMPTR0.UINT32
#define RSCAN0TMPTR0H RSCAN0.TMPTR0.UINT16[H]
#define RSCAN0TMPTR0HL RSCAN0.TMPTR0.UINT8[HL]
#define RSCAN0TMPTR0HH RSCAN0.TMPTR0.UINT8[HH]
#define RSCAN0TMDF00 RSCAN0.TMDF00.UINT32
#define RSCAN0TMDF00L RSCAN0.TMDF00.UINT16[L]
#define RSCAN0TMDF00LL RSCAN0.TMDF00.UINT8[LL]
#define RSCAN0TMDF00LH RSCAN0.TMDF00.UINT8[LH]
#define RSCAN0TMDF00H RSCAN0.TMDF00.UINT16[H]
#define RSCAN0TMDF00HL RSCAN0.TMDF00.UINT8[HL]
#define RSCAN0TMDF00HH RSCAN0.TMDF00.UINT8[HH]
#define RSCAN0TMDF10 RSCAN0.TMDF10.UINT32
#define RSCAN0TMDF10L RSCAN0.TMDF10.UINT16[L]
#define RSCAN0TMDF10LL RSCAN0.TMDF10.UINT8[LL]
#define RSCAN0TMDF10LH RSCAN0.TMDF10.UINT8[LH]
#define RSCAN0TMDF10H RSCAN0.TMDF10.UINT16[H]
#define RSCAN0TMDF10HL RSCAN0.TMDF10.UINT8[HL]
#define RSCAN0TMDF10HH RSCAN0.TMDF10.UINT8[HH]
#define RSCAN0TMID1 RSCAN0.TMID1.UINT32
#define RSCAN0TMID1L RSCAN0.TMID1.UINT16[L]
#define RSCAN0TMID1LL RSCAN0.TMID1.UINT8[LL]
#define RSCAN0TMID1LH RSCAN0.TMID1.UINT8[LH]
#define RSCAN0TMID1H RSCAN0.TMID1.UINT16[H]
#define RSCAN0TMID1HL RSCAN0.TMID1.UINT8[HL]
#define RSCAN0TMID1HH RSCAN0.TMID1.UINT8[HH]
#define RSCAN0TMPTR1 RSCAN0.TMPTR1.UINT32
#define RSCAN0TMPTR1H RSCAN0.TMPTR1.UINT16[H]
#define RSCAN0TMPTR1HL RSCAN0.TMPTR1.UINT8[HL]
#define RSCAN0TMPTR1HH RSCAN0.TMPTR1.UINT8[HH]
#define RSCAN0TMDF01 RSCAN0.TMDF01.UINT32
#define RSCAN0TMDF01L RSCAN0.TMDF01.UINT16[L]
#define RSCAN0TMDF01LL RSCAN0.TMDF01.UINT8[LL]
#define RSCAN0TMDF01LH RSCAN0.TMDF01.UINT8[LH]
#define RSCAN0TMDF01H RSCAN0.TMDF01.UINT16[H]
#define RSCAN0TMDF01HL RSCAN0.TMDF01.UINT8[HL]
#define RSCAN0TMDF01HH RSCAN0.TMDF01.UINT8[HH]
#define RSCAN0TMDF11 RSCAN0.TMDF11.UINT32
#define RSCAN0TMDF11L RSCAN0.TMDF11.UINT16[L]
#define RSCAN0TMDF11LL RSCAN0.TMDF11.UINT8[LL]
#define RSCAN0TMDF11LH RSCAN0.TMDF11.UINT8[LH]
#define RSCAN0TMDF11H RSCAN0.TMDF11.UINT16[H]
#define RSCAN0TMDF11HL RSCAN0.TMDF11.UINT8[HL]
#define RSCAN0TMDF11HH RSCAN0.TMDF11.UINT8[HH]
#define RSCAN0TMID2 RSCAN0.TMID2.UINT32
#define RSCAN0TMID2L RSCAN0.TMID2.UINT16[L]
#define RSCAN0TMID2LL RSCAN0.TMID2.UINT8[LL]
#define RSCAN0TMID2LH RSCAN0.TMID2.UINT8[LH]
#define RSCAN0TMID2H RSCAN0.TMID2.UINT16[H]
#define RSCAN0TMID2HL RSCAN0.TMID2.UINT8[HL]
#define RSCAN0TMID2HH RSCAN0.TMID2.UINT8[HH]
#define RSCAN0TMPTR2 RSCAN0.TMPTR2.UINT32
#define RSCAN0TMPTR2H RSCAN0.TMPTR2.UINT16[H]
#define RSCAN0TMPTR2HL RSCAN0.TMPTR2.UINT8[HL]
#define RSCAN0TMPTR2HH RSCAN0.TMPTR2.UINT8[HH]
#define RSCAN0TMDF02 RSCAN0.TMDF02.UINT32
#define RSCAN0TMDF02L RSCAN0.TMDF02.UINT16[L]
#define RSCAN0TMDF02LL RSCAN0.TMDF02.UINT8[LL]
#define RSCAN0TMDF02LH RSCAN0.TMDF02.UINT8[LH]
#define RSCAN0TMDF02H RSCAN0.TMDF02.UINT16[H]
#define RSCAN0TMDF02HL RSCAN0.TMDF02.UINT8[HL]
#define RSCAN0TMDF02HH RSCAN0.TMDF02.UINT8[HH]
#define RSCAN0TMDF12 RSCAN0.TMDF12.UINT32
#define RSCAN0TMDF12L RSCAN0.TMDF12.UINT16[L]
#define RSCAN0TMDF12LL RSCAN0.TMDF12.UINT8[LL]
#define RSCAN0TMDF12LH RSCAN0.TMDF12.UINT8[LH]
#define RSCAN0TMDF12H RSCAN0.TMDF12.UINT16[H]
#define RSCAN0TMDF12HL RSCAN0.TMDF12.UINT8[HL]
#define RSCAN0TMDF12HH RSCAN0.TMDF12.UINT8[HH]
#define RSCAN0TMID3 RSCAN0.TMID3.UINT32
#define RSCAN0TMID3L RSCAN0.TMID3.UINT16[L]
#define RSCAN0TMID3LL RSCAN0.TMID3.UINT8[LL]
#define RSCAN0TMID3LH RSCAN0.TMID3.UINT8[LH]
#define RSCAN0TMID3H RSCAN0.TMID3.UINT16[H]
#define RSCAN0TMID3HL RSCAN0.TMID3.UINT8[HL]
#define RSCAN0TMID3HH RSCAN0.TMID3.UINT8[HH]
#define RSCAN0TMPTR3 RSCAN0.TMPTR3.UINT32
#define RSCAN0TMPTR3H RSCAN0.TMPTR3.UINT16[H]
#define RSCAN0TMPTR3HL RSCAN0.TMPTR3.UINT8[HL]
#define RSCAN0TMPTR3HH RSCAN0.TMPTR3.UINT8[HH]
#define RSCAN0TMDF03 RSCAN0.TMDF03.UINT32
#define RSCAN0TMDF03L RSCAN0.TMDF03.UINT16[L]
#define RSCAN0TMDF03LL RSCAN0.TMDF03.UINT8[LL]
#define RSCAN0TMDF03LH RSCAN0.TMDF03.UINT8[LH]
#define RSCAN0TMDF03H RSCAN0.TMDF03.UINT16[H]
#define RSCAN0TMDF03HL RSCAN0.TMDF03.UINT8[HL]
#define RSCAN0TMDF03HH RSCAN0.TMDF03.UINT8[HH]
#define RSCAN0TMDF13 RSCAN0.TMDF13.UINT32
#define RSCAN0TMDF13L RSCAN0.TMDF13.UINT16[L]
#define RSCAN0TMDF13LL RSCAN0.TMDF13.UINT8[LL]
#define RSCAN0TMDF13LH RSCAN0.TMDF13.UINT8[LH]
#define RSCAN0TMDF13H RSCAN0.TMDF13.UINT16[H]
#define RSCAN0TMDF13HL RSCAN0.TMDF13.UINT8[HL]
#define RSCAN0TMDF13HH RSCAN0.TMDF13.UINT8[HH]
#define RSCAN0TMID4 RSCAN0.TMID4.UINT32
#define RSCAN0TMID4L RSCAN0.TMID4.UINT16[L]
#define RSCAN0TMID4LL RSCAN0.TMID4.UINT8[LL]
#define RSCAN0TMID4LH RSCAN0.TMID4.UINT8[LH]
#define RSCAN0TMID4H RSCAN0.TMID4.UINT16[H]
#define RSCAN0TMID4HL RSCAN0.TMID4.UINT8[HL]
#define RSCAN0TMID4HH RSCAN0.TMID4.UINT8[HH]
#define RSCAN0TMPTR4 RSCAN0.TMPTR4.UINT32
#define RSCAN0TMPTR4H RSCAN0.TMPTR4.UINT16[H]
#define RSCAN0TMPTR4HL RSCAN0.TMPTR4.UINT8[HL]
#define RSCAN0TMPTR4HH RSCAN0.TMPTR4.UINT8[HH]
#define RSCAN0TMDF04 RSCAN0.TMDF04.UINT32
#define RSCAN0TMDF04L RSCAN0.TMDF04.UINT16[L]
#define RSCAN0TMDF04LL RSCAN0.TMDF04.UINT8[LL]
#define RSCAN0TMDF04LH RSCAN0.TMDF04.UINT8[LH]
#define RSCAN0TMDF04H RSCAN0.TMDF04.UINT16[H]
#define RSCAN0TMDF04HL RSCAN0.TMDF04.UINT8[HL]
#define RSCAN0TMDF04HH RSCAN0.TMDF04.UINT8[HH]
#define RSCAN0TMDF14 RSCAN0.TMDF14.UINT32
#define RSCAN0TMDF14L RSCAN0.TMDF14.UINT16[L]
#define RSCAN0TMDF14LL RSCAN0.TMDF14.UINT8[LL]
#define RSCAN0TMDF14LH RSCAN0.TMDF14.UINT8[LH]
#define RSCAN0TMDF14H RSCAN0.TMDF14.UINT16[H]
#define RSCAN0TMDF14HL RSCAN0.TMDF14.UINT8[HL]
#define RSCAN0TMDF14HH RSCAN0.TMDF14.UINT8[HH]
#define RSCAN0TMID5 RSCAN0.TMID5.UINT32
#define RSCAN0TMID5L RSCAN0.TMID5.UINT16[L]
#define RSCAN0TMID5LL RSCAN0.TMID5.UINT8[LL]
#define RSCAN0TMID5LH RSCAN0.TMID5.UINT8[LH]
#define RSCAN0TMID5H RSCAN0.TMID5.UINT16[H]
#define RSCAN0TMID5HL RSCAN0.TMID5.UINT8[HL]
#define RSCAN0TMID5HH RSCAN0.TMID5.UINT8[HH]
#define RSCAN0TMPTR5 RSCAN0.TMPTR5.UINT32
#define RSCAN0TMPTR5H RSCAN0.TMPTR5.UINT16[H]
#define RSCAN0TMPTR5HL RSCAN0.TMPTR5.UINT8[HL]
#define RSCAN0TMPTR5HH RSCAN0.TMPTR5.UINT8[HH]
#define RSCAN0TMDF05 RSCAN0.TMDF05.UINT32
#define RSCAN0TMDF05L RSCAN0.TMDF05.UINT16[L]
#define RSCAN0TMDF05LL RSCAN0.TMDF05.UINT8[LL]
#define RSCAN0TMDF05LH RSCAN0.TMDF05.UINT8[LH]
#define RSCAN0TMDF05H RSCAN0.TMDF05.UINT16[H]
#define RSCAN0TMDF05HL RSCAN0.TMDF05.UINT8[HL]
#define RSCAN0TMDF05HH RSCAN0.TMDF05.UINT8[HH]
#define RSCAN0TMDF15 RSCAN0.TMDF15.UINT32
#define RSCAN0TMDF15L RSCAN0.TMDF15.UINT16[L]
#define RSCAN0TMDF15LL RSCAN0.TMDF15.UINT8[LL]
#define RSCAN0TMDF15LH RSCAN0.TMDF15.UINT8[LH]
#define RSCAN0TMDF15H RSCAN0.TMDF15.UINT16[H]
#define RSCAN0TMDF15HL RSCAN0.TMDF15.UINT8[HL]
#define RSCAN0TMDF15HH RSCAN0.TMDF15.UINT8[HH]
#define RSCAN0TMID6 RSCAN0.TMID6.UINT32
#define RSCAN0TMID6L RSCAN0.TMID6.UINT16[L]
#define RSCAN0TMID6LL RSCAN0.TMID6.UINT8[LL]
#define RSCAN0TMID6LH RSCAN0.TMID6.UINT8[LH]
#define RSCAN0TMID6H RSCAN0.TMID6.UINT16[H]
#define RSCAN0TMID6HL RSCAN0.TMID6.UINT8[HL]
#define RSCAN0TMID6HH RSCAN0.TMID6.UINT8[HH]
#define RSCAN0TMPTR6 RSCAN0.TMPTR6.UINT32
#define RSCAN0TMPTR6H RSCAN0.TMPTR6.UINT16[H]
#define RSCAN0TMPTR6HL RSCAN0.TMPTR6.UINT8[HL]
#define RSCAN0TMPTR6HH RSCAN0.TMPTR6.UINT8[HH]
#define RSCAN0TMDF06 RSCAN0.TMDF06.UINT32
#define RSCAN0TMDF06L RSCAN0.TMDF06.UINT16[L]
#define RSCAN0TMDF06LL RSCAN0.TMDF06.UINT8[LL]
#define RSCAN0TMDF06LH RSCAN0.TMDF06.UINT8[LH]
#define RSCAN0TMDF06H RSCAN0.TMDF06.UINT16[H]
#define RSCAN0TMDF06HL RSCAN0.TMDF06.UINT8[HL]
#define RSCAN0TMDF06HH RSCAN0.TMDF06.UINT8[HH]
#define RSCAN0TMDF16 RSCAN0.TMDF16.UINT32
#define RSCAN0TMDF16L RSCAN0.TMDF16.UINT16[L]
#define RSCAN0TMDF16LL RSCAN0.TMDF16.UINT8[LL]
#define RSCAN0TMDF16LH RSCAN0.TMDF16.UINT8[LH]
#define RSCAN0TMDF16H RSCAN0.TMDF16.UINT16[H]
#define RSCAN0TMDF16HL RSCAN0.TMDF16.UINT8[HL]
#define RSCAN0TMDF16HH RSCAN0.TMDF16.UINT8[HH]
#define RSCAN0TMID7 RSCAN0.TMID7.UINT32
#define RSCAN0TMID7L RSCAN0.TMID7.UINT16[L]
#define RSCAN0TMID7LL RSCAN0.TMID7.UINT8[LL]
#define RSCAN0TMID7LH RSCAN0.TMID7.UINT8[LH]
#define RSCAN0TMID7H RSCAN0.TMID7.UINT16[H]
#define RSCAN0TMID7HL RSCAN0.TMID7.UINT8[HL]
#define RSCAN0TMID7HH RSCAN0.TMID7.UINT8[HH]
#define RSCAN0TMPTR7 RSCAN0.TMPTR7.UINT32
#define RSCAN0TMPTR7H RSCAN0.TMPTR7.UINT16[H]
#define RSCAN0TMPTR7HL RSCAN0.TMPTR7.UINT8[HL]
#define RSCAN0TMPTR7HH RSCAN0.TMPTR7.UINT8[HH]
#define RSCAN0TMDF07 RSCAN0.TMDF07.UINT32
#define RSCAN0TMDF07L RSCAN0.TMDF07.UINT16[L]
#define RSCAN0TMDF07LL RSCAN0.TMDF07.UINT8[LL]
#define RSCAN0TMDF07LH RSCAN0.TMDF07.UINT8[LH]
#define RSCAN0TMDF07H RSCAN0.TMDF07.UINT16[H]
#define RSCAN0TMDF07HL RSCAN0.TMDF07.UINT8[HL]
#define RSCAN0TMDF07HH RSCAN0.TMDF07.UINT8[HH]
#define RSCAN0TMDF17 RSCAN0.TMDF17.UINT32
#define RSCAN0TMDF17L RSCAN0.TMDF17.UINT16[L]
#define RSCAN0TMDF17LL RSCAN0.TMDF17.UINT8[LL]
#define RSCAN0TMDF17LH RSCAN0.TMDF17.UINT8[LH]
#define RSCAN0TMDF17H RSCAN0.TMDF17.UINT16[H]
#define RSCAN0TMDF17HL RSCAN0.TMDF17.UINT8[HL]
#define RSCAN0TMDF17HH RSCAN0.TMDF17.UINT8[HH]
#define RSCAN0TMID8 RSCAN0.TMID8.UINT32
#define RSCAN0TMID8L RSCAN0.TMID8.UINT16[L]
#define RSCAN0TMID8LL RSCAN0.TMID8.UINT8[LL]
#define RSCAN0TMID8LH RSCAN0.TMID8.UINT8[LH]
#define RSCAN0TMID8H RSCAN0.TMID8.UINT16[H]
#define RSCAN0TMID8HL RSCAN0.TMID8.UINT8[HL]
#define RSCAN0TMID8HH RSCAN0.TMID8.UINT8[HH]
#define RSCAN0TMPTR8 RSCAN0.TMPTR8.UINT32
#define RSCAN0TMPTR8H RSCAN0.TMPTR8.UINT16[H]
#define RSCAN0TMPTR8HL RSCAN0.TMPTR8.UINT8[HL]
#define RSCAN0TMPTR8HH RSCAN0.TMPTR8.UINT8[HH]
#define RSCAN0TMDF08 RSCAN0.TMDF08.UINT32
#define RSCAN0TMDF08L RSCAN0.TMDF08.UINT16[L]
#define RSCAN0TMDF08LL RSCAN0.TMDF08.UINT8[LL]
#define RSCAN0TMDF08LH RSCAN0.TMDF08.UINT8[LH]
#define RSCAN0TMDF08H RSCAN0.TMDF08.UINT16[H]
#define RSCAN0TMDF08HL RSCAN0.TMDF08.UINT8[HL]
#define RSCAN0TMDF08HH RSCAN0.TMDF08.UINT8[HH]
#define RSCAN0TMDF18 RSCAN0.TMDF18.UINT32
#define RSCAN0TMDF18L RSCAN0.TMDF18.UINT16[L]
#define RSCAN0TMDF18LL RSCAN0.TMDF18.UINT8[LL]
#define RSCAN0TMDF18LH RSCAN0.TMDF18.UINT8[LH]
#define RSCAN0TMDF18H RSCAN0.TMDF18.UINT16[H]
#define RSCAN0TMDF18HL RSCAN0.TMDF18.UINT8[HL]
#define RSCAN0TMDF18HH RSCAN0.TMDF18.UINT8[HH]
#define RSCAN0TMID9 RSCAN0.TMID9.UINT32
#define RSCAN0TMID9L RSCAN0.TMID9.UINT16[L]
#define RSCAN0TMID9LL RSCAN0.TMID9.UINT8[LL]
#define RSCAN0TMID9LH RSCAN0.TMID9.UINT8[LH]
#define RSCAN0TMID9H RSCAN0.TMID9.UINT16[H]
#define RSCAN0TMID9HL RSCAN0.TMID9.UINT8[HL]
#define RSCAN0TMID9HH RSCAN0.TMID9.UINT8[HH]
#define RSCAN0TMPTR9 RSCAN0.TMPTR9.UINT32
#define RSCAN0TMPTR9H RSCAN0.TMPTR9.UINT16[H]
#define RSCAN0TMPTR9HL RSCAN0.TMPTR9.UINT8[HL]
#define RSCAN0TMPTR9HH RSCAN0.TMPTR9.UINT8[HH]
#define RSCAN0TMDF09 RSCAN0.TMDF09.UINT32
#define RSCAN0TMDF09L RSCAN0.TMDF09.UINT16[L]
#define RSCAN0TMDF09LL RSCAN0.TMDF09.UINT8[LL]
#define RSCAN0TMDF09LH RSCAN0.TMDF09.UINT8[LH]
#define RSCAN0TMDF09H RSCAN0.TMDF09.UINT16[H]
#define RSCAN0TMDF09HL RSCAN0.TMDF09.UINT8[HL]
#define RSCAN0TMDF09HH RSCAN0.TMDF09.UINT8[HH]
#define RSCAN0TMDF19 RSCAN0.TMDF19.UINT32
#define RSCAN0TMDF19L RSCAN0.TMDF19.UINT16[L]
#define RSCAN0TMDF19LL RSCAN0.TMDF19.UINT8[LL]
#define RSCAN0TMDF19LH RSCAN0.TMDF19.UINT8[LH]
#define RSCAN0TMDF19H RSCAN0.TMDF19.UINT16[H]
#define RSCAN0TMDF19HL RSCAN0.TMDF19.UINT8[HL]
#define RSCAN0TMDF19HH RSCAN0.TMDF19.UINT8[HH]
#define RSCAN0TMID10 RSCAN0.TMID10.UINT32
#define RSCAN0TMID10L RSCAN0.TMID10.UINT16[L]
#define RSCAN0TMID10LL RSCAN0.TMID10.UINT8[LL]
#define RSCAN0TMID10LH RSCAN0.TMID10.UINT8[LH]
#define RSCAN0TMID10H RSCAN0.TMID10.UINT16[H]
#define RSCAN0TMID10HL RSCAN0.TMID10.UINT8[HL]
#define RSCAN0TMID10HH RSCAN0.TMID10.UINT8[HH]
#define RSCAN0TMPTR10 RSCAN0.TMPTR10.UINT32
#define RSCAN0TMPTR10H RSCAN0.TMPTR10.UINT16[H]
#define RSCAN0TMPTR10HL RSCAN0.TMPTR10.UINT8[HL]
#define RSCAN0TMPTR10HH RSCAN0.TMPTR10.UINT8[HH]
#define RSCAN0TMDF010 RSCAN0.TMDF010.UINT32
#define RSCAN0TMDF010L RSCAN0.TMDF010.UINT16[L]
#define RSCAN0TMDF010LL RSCAN0.TMDF010.UINT8[LL]
#define RSCAN0TMDF010LH RSCAN0.TMDF010.UINT8[LH]
#define RSCAN0TMDF010H RSCAN0.TMDF010.UINT16[H]
#define RSCAN0TMDF010HL RSCAN0.TMDF010.UINT8[HL]
#define RSCAN0TMDF010HH RSCAN0.TMDF010.UINT8[HH]
#define RSCAN0TMDF110 RSCAN0.TMDF110.UINT32
#define RSCAN0TMDF110L RSCAN0.TMDF110.UINT16[L]
#define RSCAN0TMDF110LL RSCAN0.TMDF110.UINT8[LL]
#define RSCAN0TMDF110LH RSCAN0.TMDF110.UINT8[LH]
#define RSCAN0TMDF110H RSCAN0.TMDF110.UINT16[H]
#define RSCAN0TMDF110HL RSCAN0.TMDF110.UINT8[HL]
#define RSCAN0TMDF110HH RSCAN0.TMDF110.UINT8[HH]
#define RSCAN0TMID11 RSCAN0.TMID11.UINT32
#define RSCAN0TMID11L RSCAN0.TMID11.UINT16[L]
#define RSCAN0TMID11LL RSCAN0.TMID11.UINT8[LL]
#define RSCAN0TMID11LH RSCAN0.TMID11.UINT8[LH]
#define RSCAN0TMID11H RSCAN0.TMID11.UINT16[H]
#define RSCAN0TMID11HL RSCAN0.TMID11.UINT8[HL]
#define RSCAN0TMID11HH RSCAN0.TMID11.UINT8[HH]
#define RSCAN0TMPTR11 RSCAN0.TMPTR11.UINT32
#define RSCAN0TMPTR11H RSCAN0.TMPTR11.UINT16[H]
#define RSCAN0TMPTR11HL RSCAN0.TMPTR11.UINT8[HL]
#define RSCAN0TMPTR11HH RSCAN0.TMPTR11.UINT8[HH]
#define RSCAN0TMDF011 RSCAN0.TMDF011.UINT32
#define RSCAN0TMDF011L RSCAN0.TMDF011.UINT16[L]
#define RSCAN0TMDF011LL RSCAN0.TMDF011.UINT8[LL]
#define RSCAN0TMDF011LH RSCAN0.TMDF011.UINT8[LH]
#define RSCAN0TMDF011H RSCAN0.TMDF011.UINT16[H]
#define RSCAN0TMDF011HL RSCAN0.TMDF011.UINT8[HL]
#define RSCAN0TMDF011HH RSCAN0.TMDF011.UINT8[HH]
#define RSCAN0TMDF111 RSCAN0.TMDF111.UINT32
#define RSCAN0TMDF111L RSCAN0.TMDF111.UINT16[L]
#define RSCAN0TMDF111LL RSCAN0.TMDF111.UINT8[LL]
#define RSCAN0TMDF111LH RSCAN0.TMDF111.UINT8[LH]
#define RSCAN0TMDF111H RSCAN0.TMDF111.UINT16[H]
#define RSCAN0TMDF111HL RSCAN0.TMDF111.UINT8[HL]
#define RSCAN0TMDF111HH RSCAN0.TMDF111.UINT8[HH]
#define RSCAN0TMID12 RSCAN0.TMID12.UINT32
#define RSCAN0TMID12L RSCAN0.TMID12.UINT16[L]
#define RSCAN0TMID12LL RSCAN0.TMID12.UINT8[LL]
#define RSCAN0TMID12LH RSCAN0.TMID12.UINT8[LH]
#define RSCAN0TMID12H RSCAN0.TMID12.UINT16[H]
#define RSCAN0TMID12HL RSCAN0.TMID12.UINT8[HL]
#define RSCAN0TMID12HH RSCAN0.TMID12.UINT8[HH]
#define RSCAN0TMPTR12 RSCAN0.TMPTR12.UINT32
#define RSCAN0TMPTR12H RSCAN0.TMPTR12.UINT16[H]
#define RSCAN0TMPTR12HL RSCAN0.TMPTR12.UINT8[HL]
#define RSCAN0TMPTR12HH RSCAN0.TMPTR12.UINT8[HH]
#define RSCAN0TMDF012 RSCAN0.TMDF012.UINT32
#define RSCAN0TMDF012L RSCAN0.TMDF012.UINT16[L]
#define RSCAN0TMDF012LL RSCAN0.TMDF012.UINT8[LL]
#define RSCAN0TMDF012LH RSCAN0.TMDF012.UINT8[LH]
#define RSCAN0TMDF012H RSCAN0.TMDF012.UINT16[H]
#define RSCAN0TMDF012HL RSCAN0.TMDF012.UINT8[HL]
#define RSCAN0TMDF012HH RSCAN0.TMDF012.UINT8[HH]
#define RSCAN0TMDF112 RSCAN0.TMDF112.UINT32
#define RSCAN0TMDF112L RSCAN0.TMDF112.UINT16[L]
#define RSCAN0TMDF112LL RSCAN0.TMDF112.UINT8[LL]
#define RSCAN0TMDF112LH RSCAN0.TMDF112.UINT8[LH]
#define RSCAN0TMDF112H RSCAN0.TMDF112.UINT16[H]
#define RSCAN0TMDF112HL RSCAN0.TMDF112.UINT8[HL]
#define RSCAN0TMDF112HH RSCAN0.TMDF112.UINT8[HH]
#define RSCAN0TMID13 RSCAN0.TMID13.UINT32
#define RSCAN0TMID13L RSCAN0.TMID13.UINT16[L]
#define RSCAN0TMID13LL RSCAN0.TMID13.UINT8[LL]
#define RSCAN0TMID13LH RSCAN0.TMID13.UINT8[LH]
#define RSCAN0TMID13H RSCAN0.TMID13.UINT16[H]
#define RSCAN0TMID13HL RSCAN0.TMID13.UINT8[HL]
#define RSCAN0TMID13HH RSCAN0.TMID13.UINT8[HH]
#define RSCAN0TMPTR13 RSCAN0.TMPTR13.UINT32
#define RSCAN0TMPTR13H RSCAN0.TMPTR13.UINT16[H]
#define RSCAN0TMPTR13HL RSCAN0.TMPTR13.UINT8[HL]
#define RSCAN0TMPTR13HH RSCAN0.TMPTR13.UINT8[HH]
#define RSCAN0TMDF013 RSCAN0.TMDF013.UINT32
#define RSCAN0TMDF013L RSCAN0.TMDF013.UINT16[L]
#define RSCAN0TMDF013LL RSCAN0.TMDF013.UINT8[LL]
#define RSCAN0TMDF013LH RSCAN0.TMDF013.UINT8[LH]
#define RSCAN0TMDF013H RSCAN0.TMDF013.UINT16[H]
#define RSCAN0TMDF013HL RSCAN0.TMDF013.UINT8[HL]
#define RSCAN0TMDF013HH RSCAN0.TMDF013.UINT8[HH]
#define RSCAN0TMDF113 RSCAN0.TMDF113.UINT32
#define RSCAN0TMDF113L RSCAN0.TMDF113.UINT16[L]
#define RSCAN0TMDF113LL RSCAN0.TMDF113.UINT8[LL]
#define RSCAN0TMDF113LH RSCAN0.TMDF113.UINT8[LH]
#define RSCAN0TMDF113H RSCAN0.TMDF113.UINT16[H]
#define RSCAN0TMDF113HL RSCAN0.TMDF113.UINT8[HL]
#define RSCAN0TMDF113HH RSCAN0.TMDF113.UINT8[HH]
#define RSCAN0TMID14 RSCAN0.TMID14.UINT32
#define RSCAN0TMID14L RSCAN0.TMID14.UINT16[L]
#define RSCAN0TMID14LL RSCAN0.TMID14.UINT8[LL]
#define RSCAN0TMID14LH RSCAN0.TMID14.UINT8[LH]
#define RSCAN0TMID14H RSCAN0.TMID14.UINT16[H]
#define RSCAN0TMID14HL RSCAN0.TMID14.UINT8[HL]
#define RSCAN0TMID14HH RSCAN0.TMID14.UINT8[HH]
#define RSCAN0TMPTR14 RSCAN0.TMPTR14.UINT32
#define RSCAN0TMPTR14H RSCAN0.TMPTR14.UINT16[H]
#define RSCAN0TMPTR14HL RSCAN0.TMPTR14.UINT8[HL]
#define RSCAN0TMPTR14HH RSCAN0.TMPTR14.UINT8[HH]
#define RSCAN0TMDF014 RSCAN0.TMDF014.UINT32
#define RSCAN0TMDF014L RSCAN0.TMDF014.UINT16[L]
#define RSCAN0TMDF014LL RSCAN0.TMDF014.UINT8[LL]
#define RSCAN0TMDF014LH RSCAN0.TMDF014.UINT8[LH]
#define RSCAN0TMDF014H RSCAN0.TMDF014.UINT16[H]
#define RSCAN0TMDF014HL RSCAN0.TMDF014.UINT8[HL]
#define RSCAN0TMDF014HH RSCAN0.TMDF014.UINT8[HH]
#define RSCAN0TMDF114 RSCAN0.TMDF114.UINT32
#define RSCAN0TMDF114L RSCAN0.TMDF114.UINT16[L]
#define RSCAN0TMDF114LL RSCAN0.TMDF114.UINT8[LL]
#define RSCAN0TMDF114LH RSCAN0.TMDF114.UINT8[LH]
#define RSCAN0TMDF114H RSCAN0.TMDF114.UINT16[H]
#define RSCAN0TMDF114HL RSCAN0.TMDF114.UINT8[HL]
#define RSCAN0TMDF114HH RSCAN0.TMDF114.UINT8[HH]
#define RSCAN0TMID15 RSCAN0.TMID15.UINT32
#define RSCAN0TMID15L RSCAN0.TMID15.UINT16[L]
#define RSCAN0TMID15LL RSCAN0.TMID15.UINT8[LL]
#define RSCAN0TMID15LH RSCAN0.TMID15.UINT8[LH]
#define RSCAN0TMID15H RSCAN0.TMID15.UINT16[H]
#define RSCAN0TMID15HL RSCAN0.TMID15.UINT8[HL]
#define RSCAN0TMID15HH RSCAN0.TMID15.UINT8[HH]
#define RSCAN0TMPTR15 RSCAN0.TMPTR15.UINT32
#define RSCAN0TMPTR15H RSCAN0.TMPTR15.UINT16[H]
#define RSCAN0TMPTR15HL RSCAN0.TMPTR15.UINT8[HL]
#define RSCAN0TMPTR15HH RSCAN0.TMPTR15.UINT8[HH]
#define RSCAN0TMDF015 RSCAN0.TMDF015.UINT32
#define RSCAN0TMDF015L RSCAN0.TMDF015.UINT16[L]
#define RSCAN0TMDF015LL RSCAN0.TMDF015.UINT8[LL]
#define RSCAN0TMDF015LH RSCAN0.TMDF015.UINT8[LH]
#define RSCAN0TMDF015H RSCAN0.TMDF015.UINT16[H]
#define RSCAN0TMDF015HL RSCAN0.TMDF015.UINT8[HL]
#define RSCAN0TMDF015HH RSCAN0.TMDF015.UINT8[HH]
#define RSCAN0TMDF115 RSCAN0.TMDF115.UINT32
#define RSCAN0TMDF115L RSCAN0.TMDF115.UINT16[L]
#define RSCAN0TMDF115LL RSCAN0.TMDF115.UINT8[LL]
#define RSCAN0TMDF115LH RSCAN0.TMDF115.UINT8[LH]
#define RSCAN0TMDF115H RSCAN0.TMDF115.UINT16[H]
#define RSCAN0TMDF115HL RSCAN0.TMDF115.UINT8[HL]
#define RSCAN0TMDF115HH RSCAN0.TMDF115.UINT8[HH]
#define RSCAN0TMID16 RSCAN0.TMID16.UINT32
#define RSCAN0TMID16L RSCAN0.TMID16.UINT16[L]
#define RSCAN0TMID16LL RSCAN0.TMID16.UINT8[LL]
#define RSCAN0TMID16LH RSCAN0.TMID16.UINT8[LH]
#define RSCAN0TMID16H RSCAN0.TMID16.UINT16[H]
#define RSCAN0TMID16HL RSCAN0.TMID16.UINT8[HL]
#define RSCAN0TMID16HH RSCAN0.TMID16.UINT8[HH]
#define RSCAN0TMPTR16 RSCAN0.TMPTR16.UINT32
#define RSCAN0TMPTR16H RSCAN0.TMPTR16.UINT16[H]
#define RSCAN0TMPTR16HL RSCAN0.TMPTR16.UINT8[HL]
#define RSCAN0TMPTR16HH RSCAN0.TMPTR16.UINT8[HH]
#define RSCAN0TMDF016 RSCAN0.TMDF016.UINT32
#define RSCAN0TMDF016L RSCAN0.TMDF016.UINT16[L]
#define RSCAN0TMDF016LL RSCAN0.TMDF016.UINT8[LL]
#define RSCAN0TMDF016LH RSCAN0.TMDF016.UINT8[LH]
#define RSCAN0TMDF016H RSCAN0.TMDF016.UINT16[H]
#define RSCAN0TMDF016HL RSCAN0.TMDF016.UINT8[HL]
#define RSCAN0TMDF016HH RSCAN0.TMDF016.UINT8[HH]
#define RSCAN0TMDF116 RSCAN0.TMDF116.UINT32
#define RSCAN0TMDF116L RSCAN0.TMDF116.UINT16[L]
#define RSCAN0TMDF116LL RSCAN0.TMDF116.UINT8[LL]
#define RSCAN0TMDF116LH RSCAN0.TMDF116.UINT8[LH]
#define RSCAN0TMDF116H RSCAN0.TMDF116.UINT16[H]
#define RSCAN0TMDF116HL RSCAN0.TMDF116.UINT8[HL]
#define RSCAN0TMDF116HH RSCAN0.TMDF116.UINT8[HH]
#define RSCAN0TMID17 RSCAN0.TMID17.UINT32
#define RSCAN0TMID17L RSCAN0.TMID17.UINT16[L]
#define RSCAN0TMID17LL RSCAN0.TMID17.UINT8[LL]
#define RSCAN0TMID17LH RSCAN0.TMID17.UINT8[LH]
#define RSCAN0TMID17H RSCAN0.TMID17.UINT16[H]
#define RSCAN0TMID17HL RSCAN0.TMID17.UINT8[HL]
#define RSCAN0TMID17HH RSCAN0.TMID17.UINT8[HH]
#define RSCAN0TMPTR17 RSCAN0.TMPTR17.UINT32
#define RSCAN0TMPTR17H RSCAN0.TMPTR17.UINT16[H]
#define RSCAN0TMPTR17HL RSCAN0.TMPTR17.UINT8[HL]
#define RSCAN0TMPTR17HH RSCAN0.TMPTR17.UINT8[HH]
#define RSCAN0TMDF017 RSCAN0.TMDF017.UINT32
#define RSCAN0TMDF017L RSCAN0.TMDF017.UINT16[L]
#define RSCAN0TMDF017LL RSCAN0.TMDF017.UINT8[LL]
#define RSCAN0TMDF017LH RSCAN0.TMDF017.UINT8[LH]
#define RSCAN0TMDF017H RSCAN0.TMDF017.UINT16[H]
#define RSCAN0TMDF017HL RSCAN0.TMDF017.UINT8[HL]
#define RSCAN0TMDF017HH RSCAN0.TMDF017.UINT8[HH]
#define RSCAN0TMDF117 RSCAN0.TMDF117.UINT32
#define RSCAN0TMDF117L RSCAN0.TMDF117.UINT16[L]
#define RSCAN0TMDF117LL RSCAN0.TMDF117.UINT8[LL]
#define RSCAN0TMDF117LH RSCAN0.TMDF117.UINT8[LH]
#define RSCAN0TMDF117H RSCAN0.TMDF117.UINT16[H]
#define RSCAN0TMDF117HL RSCAN0.TMDF117.UINT8[HL]
#define RSCAN0TMDF117HH RSCAN0.TMDF117.UINT8[HH]
#define RSCAN0TMID18 RSCAN0.TMID18.UINT32
#define RSCAN0TMID18L RSCAN0.TMID18.UINT16[L]
#define RSCAN0TMID18LL RSCAN0.TMID18.UINT8[LL]
#define RSCAN0TMID18LH RSCAN0.TMID18.UINT8[LH]
#define RSCAN0TMID18H RSCAN0.TMID18.UINT16[H]
#define RSCAN0TMID18HL RSCAN0.TMID18.UINT8[HL]
#define RSCAN0TMID18HH RSCAN0.TMID18.UINT8[HH]
#define RSCAN0TMPTR18 RSCAN0.TMPTR18.UINT32
#define RSCAN0TMPTR18H RSCAN0.TMPTR18.UINT16[H]
#define RSCAN0TMPTR18HL RSCAN0.TMPTR18.UINT8[HL]
#define RSCAN0TMPTR18HH RSCAN0.TMPTR18.UINT8[HH]
#define RSCAN0TMDF018 RSCAN0.TMDF018.UINT32
#define RSCAN0TMDF018L RSCAN0.TMDF018.UINT16[L]
#define RSCAN0TMDF018LL RSCAN0.TMDF018.UINT8[LL]
#define RSCAN0TMDF018LH RSCAN0.TMDF018.UINT8[LH]
#define RSCAN0TMDF018H RSCAN0.TMDF018.UINT16[H]
#define RSCAN0TMDF018HL RSCAN0.TMDF018.UINT8[HL]
#define RSCAN0TMDF018HH RSCAN0.TMDF018.UINT8[HH]
#define RSCAN0TMDF118 RSCAN0.TMDF118.UINT32
#define RSCAN0TMDF118L RSCAN0.TMDF118.UINT16[L]
#define RSCAN0TMDF118LL RSCAN0.TMDF118.UINT8[LL]
#define RSCAN0TMDF118LH RSCAN0.TMDF118.UINT8[LH]
#define RSCAN0TMDF118H RSCAN0.TMDF118.UINT16[H]
#define RSCAN0TMDF118HL RSCAN0.TMDF118.UINT8[HL]
#define RSCAN0TMDF118HH RSCAN0.TMDF118.UINT8[HH]
#define RSCAN0TMID19 RSCAN0.TMID19.UINT32
#define RSCAN0TMID19L RSCAN0.TMID19.UINT16[L]
#define RSCAN0TMID19LL RSCAN0.TMID19.UINT8[LL]
#define RSCAN0TMID19LH RSCAN0.TMID19.UINT8[LH]
#define RSCAN0TMID19H RSCAN0.TMID19.UINT16[H]
#define RSCAN0TMID19HL RSCAN0.TMID19.UINT8[HL]
#define RSCAN0TMID19HH RSCAN0.TMID19.UINT8[HH]
#define RSCAN0TMPTR19 RSCAN0.TMPTR19.UINT32
#define RSCAN0TMPTR19H RSCAN0.TMPTR19.UINT16[H]
#define RSCAN0TMPTR19HL RSCAN0.TMPTR19.UINT8[HL]
#define RSCAN0TMPTR19HH RSCAN0.TMPTR19.UINT8[HH]
#define RSCAN0TMDF019 RSCAN0.TMDF019.UINT32
#define RSCAN0TMDF019L RSCAN0.TMDF019.UINT16[L]
#define RSCAN0TMDF019LL RSCAN0.TMDF019.UINT8[LL]
#define RSCAN0TMDF019LH RSCAN0.TMDF019.UINT8[LH]
#define RSCAN0TMDF019H RSCAN0.TMDF019.UINT16[H]
#define RSCAN0TMDF019HL RSCAN0.TMDF019.UINT8[HL]
#define RSCAN0TMDF019HH RSCAN0.TMDF019.UINT8[HH]
#define RSCAN0TMDF119 RSCAN0.TMDF119.UINT32
#define RSCAN0TMDF119L RSCAN0.TMDF119.UINT16[L]
#define RSCAN0TMDF119LL RSCAN0.TMDF119.UINT8[LL]
#define RSCAN0TMDF119LH RSCAN0.TMDF119.UINT8[LH]
#define RSCAN0TMDF119H RSCAN0.TMDF119.UINT16[H]
#define RSCAN0TMDF119HL RSCAN0.TMDF119.UINT8[HL]
#define RSCAN0TMDF119HH RSCAN0.TMDF119.UINT8[HH]
#define RSCAN0TMID20 RSCAN0.TMID20.UINT32
#define RSCAN0TMID20L RSCAN0.TMID20.UINT16[L]
#define RSCAN0TMID20LL RSCAN0.TMID20.UINT8[LL]
#define RSCAN0TMID20LH RSCAN0.TMID20.UINT8[LH]
#define RSCAN0TMID20H RSCAN0.TMID20.UINT16[H]
#define RSCAN0TMID20HL RSCAN0.TMID20.UINT8[HL]
#define RSCAN0TMID20HH RSCAN0.TMID20.UINT8[HH]
#define RSCAN0TMPTR20 RSCAN0.TMPTR20.UINT32
#define RSCAN0TMPTR20H RSCAN0.TMPTR20.UINT16[H]
#define RSCAN0TMPTR20HL RSCAN0.TMPTR20.UINT8[HL]
#define RSCAN0TMPTR20HH RSCAN0.TMPTR20.UINT8[HH]
#define RSCAN0TMDF020 RSCAN0.TMDF020.UINT32
#define RSCAN0TMDF020L RSCAN0.TMDF020.UINT16[L]
#define RSCAN0TMDF020LL RSCAN0.TMDF020.UINT8[LL]
#define RSCAN0TMDF020LH RSCAN0.TMDF020.UINT8[LH]
#define RSCAN0TMDF020H RSCAN0.TMDF020.UINT16[H]
#define RSCAN0TMDF020HL RSCAN0.TMDF020.UINT8[HL]
#define RSCAN0TMDF020HH RSCAN0.TMDF020.UINT8[HH]
#define RSCAN0TMDF120 RSCAN0.TMDF120.UINT32
#define RSCAN0TMDF120L RSCAN0.TMDF120.UINT16[L]
#define RSCAN0TMDF120LL RSCAN0.TMDF120.UINT8[LL]
#define RSCAN0TMDF120LH RSCAN0.TMDF120.UINT8[LH]
#define RSCAN0TMDF120H RSCAN0.TMDF120.UINT16[H]
#define RSCAN0TMDF120HL RSCAN0.TMDF120.UINT8[HL]
#define RSCAN0TMDF120HH RSCAN0.TMDF120.UINT8[HH]
#define RSCAN0TMID21 RSCAN0.TMID21.UINT32
#define RSCAN0TMID21L RSCAN0.TMID21.UINT16[L]
#define RSCAN0TMID21LL RSCAN0.TMID21.UINT8[LL]
#define RSCAN0TMID21LH RSCAN0.TMID21.UINT8[LH]
#define RSCAN0TMID21H RSCAN0.TMID21.UINT16[H]
#define RSCAN0TMID21HL RSCAN0.TMID21.UINT8[HL]
#define RSCAN0TMID21HH RSCAN0.TMID21.UINT8[HH]
#define RSCAN0TMPTR21 RSCAN0.TMPTR21.UINT32
#define RSCAN0TMPTR21H RSCAN0.TMPTR21.UINT16[H]
#define RSCAN0TMPTR21HL RSCAN0.TMPTR21.UINT8[HL]
#define RSCAN0TMPTR21HH RSCAN0.TMPTR21.UINT8[HH]
#define RSCAN0TMDF021 RSCAN0.TMDF021.UINT32
#define RSCAN0TMDF021L RSCAN0.TMDF021.UINT16[L]
#define RSCAN0TMDF021LL RSCAN0.TMDF021.UINT8[LL]
#define RSCAN0TMDF021LH RSCAN0.TMDF021.UINT8[LH]
#define RSCAN0TMDF021H RSCAN0.TMDF021.UINT16[H]
#define RSCAN0TMDF021HL RSCAN0.TMDF021.UINT8[HL]
#define RSCAN0TMDF021HH RSCAN0.TMDF021.UINT8[HH]
#define RSCAN0TMDF121 RSCAN0.TMDF121.UINT32
#define RSCAN0TMDF121L RSCAN0.TMDF121.UINT16[L]
#define RSCAN0TMDF121LL RSCAN0.TMDF121.UINT8[LL]
#define RSCAN0TMDF121LH RSCAN0.TMDF121.UINT8[LH]
#define RSCAN0TMDF121H RSCAN0.TMDF121.UINT16[H]
#define RSCAN0TMDF121HL RSCAN0.TMDF121.UINT8[HL]
#define RSCAN0TMDF121HH RSCAN0.TMDF121.UINT8[HH]
#define RSCAN0TMID22 RSCAN0.TMID22.UINT32
#define RSCAN0TMID22L RSCAN0.TMID22.UINT16[L]
#define RSCAN0TMID22LL RSCAN0.TMID22.UINT8[LL]
#define RSCAN0TMID22LH RSCAN0.TMID22.UINT8[LH]
#define RSCAN0TMID22H RSCAN0.TMID22.UINT16[H]
#define RSCAN0TMID22HL RSCAN0.TMID22.UINT8[HL]
#define RSCAN0TMID22HH RSCAN0.TMID22.UINT8[HH]
#define RSCAN0TMPTR22 RSCAN0.TMPTR22.UINT32
#define RSCAN0TMPTR22H RSCAN0.TMPTR22.UINT16[H]
#define RSCAN0TMPTR22HL RSCAN0.TMPTR22.UINT8[HL]
#define RSCAN0TMPTR22HH RSCAN0.TMPTR22.UINT8[HH]
#define RSCAN0TMDF022 RSCAN0.TMDF022.UINT32
#define RSCAN0TMDF022L RSCAN0.TMDF022.UINT16[L]
#define RSCAN0TMDF022LL RSCAN0.TMDF022.UINT8[LL]
#define RSCAN0TMDF022LH RSCAN0.TMDF022.UINT8[LH]
#define RSCAN0TMDF022H RSCAN0.TMDF022.UINT16[H]
#define RSCAN0TMDF022HL RSCAN0.TMDF022.UINT8[HL]
#define RSCAN0TMDF022HH RSCAN0.TMDF022.UINT8[HH]
#define RSCAN0TMDF122 RSCAN0.TMDF122.UINT32
#define RSCAN0TMDF122L RSCAN0.TMDF122.UINT16[L]
#define RSCAN0TMDF122LL RSCAN0.TMDF122.UINT8[LL]
#define RSCAN0TMDF122LH RSCAN0.TMDF122.UINT8[LH]
#define RSCAN0TMDF122H RSCAN0.TMDF122.UINT16[H]
#define RSCAN0TMDF122HL RSCAN0.TMDF122.UINT8[HL]
#define RSCAN0TMDF122HH RSCAN0.TMDF122.UINT8[HH]
#define RSCAN0TMID23 RSCAN0.TMID23.UINT32
#define RSCAN0TMID23L RSCAN0.TMID23.UINT16[L]
#define RSCAN0TMID23LL RSCAN0.TMID23.UINT8[LL]
#define RSCAN0TMID23LH RSCAN0.TMID23.UINT8[LH]
#define RSCAN0TMID23H RSCAN0.TMID23.UINT16[H]
#define RSCAN0TMID23HL RSCAN0.TMID23.UINT8[HL]
#define RSCAN0TMID23HH RSCAN0.TMID23.UINT8[HH]
#define RSCAN0TMPTR23 RSCAN0.TMPTR23.UINT32
#define RSCAN0TMPTR23H RSCAN0.TMPTR23.UINT16[H]
#define RSCAN0TMPTR23HL RSCAN0.TMPTR23.UINT8[HL]
#define RSCAN0TMPTR23HH RSCAN0.TMPTR23.UINT8[HH]
#define RSCAN0TMDF023 RSCAN0.TMDF023.UINT32
#define RSCAN0TMDF023L RSCAN0.TMDF023.UINT16[L]
#define RSCAN0TMDF023LL RSCAN0.TMDF023.UINT8[LL]
#define RSCAN0TMDF023LH RSCAN0.TMDF023.UINT8[LH]
#define RSCAN0TMDF023H RSCAN0.TMDF023.UINT16[H]
#define RSCAN0TMDF023HL RSCAN0.TMDF023.UINT8[HL]
#define RSCAN0TMDF023HH RSCAN0.TMDF023.UINT8[HH]
#define RSCAN0TMDF123 RSCAN0.TMDF123.UINT32
#define RSCAN0TMDF123L RSCAN0.TMDF123.UINT16[L]
#define RSCAN0TMDF123LL RSCAN0.TMDF123.UINT8[LL]
#define RSCAN0TMDF123LH RSCAN0.TMDF123.UINT8[LH]
#define RSCAN0TMDF123H RSCAN0.TMDF123.UINT16[H]
#define RSCAN0TMDF123HL RSCAN0.TMDF123.UINT8[HL]
#define RSCAN0TMDF123HH RSCAN0.TMDF123.UINT8[HH]
#define RSCAN0TMID24 RSCAN0.TMID24.UINT32
#define RSCAN0TMID24L RSCAN0.TMID24.UINT16[L]
#define RSCAN0TMID24LL RSCAN0.TMID24.UINT8[LL]
#define RSCAN0TMID24LH RSCAN0.TMID24.UINT8[LH]
#define RSCAN0TMID24H RSCAN0.TMID24.UINT16[H]
#define RSCAN0TMID24HL RSCAN0.TMID24.UINT8[HL]
#define RSCAN0TMID24HH RSCAN0.TMID24.UINT8[HH]
#define RSCAN0TMPTR24 RSCAN0.TMPTR24.UINT32
#define RSCAN0TMPTR24H RSCAN0.TMPTR24.UINT16[H]
#define RSCAN0TMPTR24HL RSCAN0.TMPTR24.UINT8[HL]
#define RSCAN0TMPTR24HH RSCAN0.TMPTR24.UINT8[HH]
#define RSCAN0TMDF024 RSCAN0.TMDF024.UINT32
#define RSCAN0TMDF024L RSCAN0.TMDF024.UINT16[L]
#define RSCAN0TMDF024LL RSCAN0.TMDF024.UINT8[LL]
#define RSCAN0TMDF024LH RSCAN0.TMDF024.UINT8[LH]
#define RSCAN0TMDF024H RSCAN0.TMDF024.UINT16[H]
#define RSCAN0TMDF024HL RSCAN0.TMDF024.UINT8[HL]
#define RSCAN0TMDF024HH RSCAN0.TMDF024.UINT8[HH]
#define RSCAN0TMDF124 RSCAN0.TMDF124.UINT32
#define RSCAN0TMDF124L RSCAN0.TMDF124.UINT16[L]
#define RSCAN0TMDF124LL RSCAN0.TMDF124.UINT8[LL]
#define RSCAN0TMDF124LH RSCAN0.TMDF124.UINT8[LH]
#define RSCAN0TMDF124H RSCAN0.TMDF124.UINT16[H]
#define RSCAN0TMDF124HL RSCAN0.TMDF124.UINT8[HL]
#define RSCAN0TMDF124HH RSCAN0.TMDF124.UINT8[HH]
#define RSCAN0TMID25 RSCAN0.TMID25.UINT32
#define RSCAN0TMID25L RSCAN0.TMID25.UINT16[L]
#define RSCAN0TMID25LL RSCAN0.TMID25.UINT8[LL]
#define RSCAN0TMID25LH RSCAN0.TMID25.UINT8[LH]
#define RSCAN0TMID25H RSCAN0.TMID25.UINT16[H]
#define RSCAN0TMID25HL RSCAN0.TMID25.UINT8[HL]
#define RSCAN0TMID25HH RSCAN0.TMID25.UINT8[HH]
#define RSCAN0TMPTR25 RSCAN0.TMPTR25.UINT32
#define RSCAN0TMPTR25H RSCAN0.TMPTR25.UINT16[H]
#define RSCAN0TMPTR25HL RSCAN0.TMPTR25.UINT8[HL]
#define RSCAN0TMPTR25HH RSCAN0.TMPTR25.UINT8[HH]
#define RSCAN0TMDF025 RSCAN0.TMDF025.UINT32
#define RSCAN0TMDF025L RSCAN0.TMDF025.UINT16[L]
#define RSCAN0TMDF025LL RSCAN0.TMDF025.UINT8[LL]
#define RSCAN0TMDF025LH RSCAN0.TMDF025.UINT8[LH]
#define RSCAN0TMDF025H RSCAN0.TMDF025.UINT16[H]
#define RSCAN0TMDF025HL RSCAN0.TMDF025.UINT8[HL]
#define RSCAN0TMDF025HH RSCAN0.TMDF025.UINT8[HH]
#define RSCAN0TMDF125 RSCAN0.TMDF125.UINT32
#define RSCAN0TMDF125L RSCAN0.TMDF125.UINT16[L]
#define RSCAN0TMDF125LL RSCAN0.TMDF125.UINT8[LL]
#define RSCAN0TMDF125LH RSCAN0.TMDF125.UINT8[LH]
#define RSCAN0TMDF125H RSCAN0.TMDF125.UINT16[H]
#define RSCAN0TMDF125HL RSCAN0.TMDF125.UINT8[HL]
#define RSCAN0TMDF125HH RSCAN0.TMDF125.UINT8[HH]
#define RSCAN0TMID26 RSCAN0.TMID26.UINT32
#define RSCAN0TMID26L RSCAN0.TMID26.UINT16[L]
#define RSCAN0TMID26LL RSCAN0.TMID26.UINT8[LL]
#define RSCAN0TMID26LH RSCAN0.TMID26.UINT8[LH]
#define RSCAN0TMID26H RSCAN0.TMID26.UINT16[H]
#define RSCAN0TMID26HL RSCAN0.TMID26.UINT8[HL]
#define RSCAN0TMID26HH RSCAN0.TMID26.UINT8[HH]
#define RSCAN0TMPTR26 RSCAN0.TMPTR26.UINT32
#define RSCAN0TMPTR26H RSCAN0.TMPTR26.UINT16[H]
#define RSCAN0TMPTR26HL RSCAN0.TMPTR26.UINT8[HL]
#define RSCAN0TMPTR26HH RSCAN0.TMPTR26.UINT8[HH]
#define RSCAN0TMDF026 RSCAN0.TMDF026.UINT32
#define RSCAN0TMDF026L RSCAN0.TMDF026.UINT16[L]
#define RSCAN0TMDF026LL RSCAN0.TMDF026.UINT8[LL]
#define RSCAN0TMDF026LH RSCAN0.TMDF026.UINT8[LH]
#define RSCAN0TMDF026H RSCAN0.TMDF026.UINT16[H]
#define RSCAN0TMDF026HL RSCAN0.TMDF026.UINT8[HL]
#define RSCAN0TMDF026HH RSCAN0.TMDF026.UINT8[HH]
#define RSCAN0TMDF126 RSCAN0.TMDF126.UINT32
#define RSCAN0TMDF126L RSCAN0.TMDF126.UINT16[L]
#define RSCAN0TMDF126LL RSCAN0.TMDF126.UINT8[LL]
#define RSCAN0TMDF126LH RSCAN0.TMDF126.UINT8[LH]
#define RSCAN0TMDF126H RSCAN0.TMDF126.UINT16[H]
#define RSCAN0TMDF126HL RSCAN0.TMDF126.UINT8[HL]
#define RSCAN0TMDF126HH RSCAN0.TMDF126.UINT8[HH]
#define RSCAN0TMID27 RSCAN0.TMID27.UINT32
#define RSCAN0TMID27L RSCAN0.TMID27.UINT16[L]
#define RSCAN0TMID27LL RSCAN0.TMID27.UINT8[LL]
#define RSCAN0TMID27LH RSCAN0.TMID27.UINT8[LH]
#define RSCAN0TMID27H RSCAN0.TMID27.UINT16[H]
#define RSCAN0TMID27HL RSCAN0.TMID27.UINT8[HL]
#define RSCAN0TMID27HH RSCAN0.TMID27.UINT8[HH]
#define RSCAN0TMPTR27 RSCAN0.TMPTR27.UINT32
#define RSCAN0TMPTR27H RSCAN0.TMPTR27.UINT16[H]
#define RSCAN0TMPTR27HL RSCAN0.TMPTR27.UINT8[HL]
#define RSCAN0TMPTR27HH RSCAN0.TMPTR27.UINT8[HH]
#define RSCAN0TMDF027 RSCAN0.TMDF027.UINT32
#define RSCAN0TMDF027L RSCAN0.TMDF027.UINT16[L]
#define RSCAN0TMDF027LL RSCAN0.TMDF027.UINT8[LL]
#define RSCAN0TMDF027LH RSCAN0.TMDF027.UINT8[LH]
#define RSCAN0TMDF027H RSCAN0.TMDF027.UINT16[H]
#define RSCAN0TMDF027HL RSCAN0.TMDF027.UINT8[HL]
#define RSCAN0TMDF027HH RSCAN0.TMDF027.UINT8[HH]
#define RSCAN0TMDF127 RSCAN0.TMDF127.UINT32
#define RSCAN0TMDF127L RSCAN0.TMDF127.UINT16[L]
#define RSCAN0TMDF127LL RSCAN0.TMDF127.UINT8[LL]
#define RSCAN0TMDF127LH RSCAN0.TMDF127.UINT8[LH]
#define RSCAN0TMDF127H RSCAN0.TMDF127.UINT16[H]
#define RSCAN0TMDF127HL RSCAN0.TMDF127.UINT8[HL]
#define RSCAN0TMDF127HH RSCAN0.TMDF127.UINT8[HH]
#define RSCAN0TMID28 RSCAN0.TMID28.UINT32
#define RSCAN0TMID28L RSCAN0.TMID28.UINT16[L]
#define RSCAN0TMID28LL RSCAN0.TMID28.UINT8[LL]
#define RSCAN0TMID28LH RSCAN0.TMID28.UINT8[LH]
#define RSCAN0TMID28H RSCAN0.TMID28.UINT16[H]
#define RSCAN0TMID28HL RSCAN0.TMID28.UINT8[HL]
#define RSCAN0TMID28HH RSCAN0.TMID28.UINT8[HH]
#define RSCAN0TMPTR28 RSCAN0.TMPTR28.UINT32
#define RSCAN0TMPTR28H RSCAN0.TMPTR28.UINT16[H]
#define RSCAN0TMPTR28HL RSCAN0.TMPTR28.UINT8[HL]
#define RSCAN0TMPTR28HH RSCAN0.TMPTR28.UINT8[HH]
#define RSCAN0TMDF028 RSCAN0.TMDF028.UINT32
#define RSCAN0TMDF028L RSCAN0.TMDF028.UINT16[L]
#define RSCAN0TMDF028LL RSCAN0.TMDF028.UINT8[LL]
#define RSCAN0TMDF028LH RSCAN0.TMDF028.UINT8[LH]
#define RSCAN0TMDF028H RSCAN0.TMDF028.UINT16[H]
#define RSCAN0TMDF028HL RSCAN0.TMDF028.UINT8[HL]
#define RSCAN0TMDF028HH RSCAN0.TMDF028.UINT8[HH]
#define RSCAN0TMDF128 RSCAN0.TMDF128.UINT32
#define RSCAN0TMDF128L RSCAN0.TMDF128.UINT16[L]
#define RSCAN0TMDF128LL RSCAN0.TMDF128.UINT8[LL]
#define RSCAN0TMDF128LH RSCAN0.TMDF128.UINT8[LH]
#define RSCAN0TMDF128H RSCAN0.TMDF128.UINT16[H]
#define RSCAN0TMDF128HL RSCAN0.TMDF128.UINT8[HL]
#define RSCAN0TMDF128HH RSCAN0.TMDF128.UINT8[HH]
#define RSCAN0TMID29 RSCAN0.TMID29.UINT32
#define RSCAN0TMID29L RSCAN0.TMID29.UINT16[L]
#define RSCAN0TMID29LL RSCAN0.TMID29.UINT8[LL]
#define RSCAN0TMID29LH RSCAN0.TMID29.UINT8[LH]
#define RSCAN0TMID29H RSCAN0.TMID29.UINT16[H]
#define RSCAN0TMID29HL RSCAN0.TMID29.UINT8[HL]
#define RSCAN0TMID29HH RSCAN0.TMID29.UINT8[HH]
#define RSCAN0TMPTR29 RSCAN0.TMPTR29.UINT32
#define RSCAN0TMPTR29H RSCAN0.TMPTR29.UINT16[H]
#define RSCAN0TMPTR29HL RSCAN0.TMPTR29.UINT8[HL]
#define RSCAN0TMPTR29HH RSCAN0.TMPTR29.UINT8[HH]
#define RSCAN0TMDF029 RSCAN0.TMDF029.UINT32
#define RSCAN0TMDF029L RSCAN0.TMDF029.UINT16[L]
#define RSCAN0TMDF029LL RSCAN0.TMDF029.UINT8[LL]
#define RSCAN0TMDF029LH RSCAN0.TMDF029.UINT8[LH]
#define RSCAN0TMDF029H RSCAN0.TMDF029.UINT16[H]
#define RSCAN0TMDF029HL RSCAN0.TMDF029.UINT8[HL]
#define RSCAN0TMDF029HH RSCAN0.TMDF029.UINT8[HH]
#define RSCAN0TMDF129 RSCAN0.TMDF129.UINT32
#define RSCAN0TMDF129L RSCAN0.TMDF129.UINT16[L]
#define RSCAN0TMDF129LL RSCAN0.TMDF129.UINT8[LL]
#define RSCAN0TMDF129LH RSCAN0.TMDF129.UINT8[LH]
#define RSCAN0TMDF129H RSCAN0.TMDF129.UINT16[H]
#define RSCAN0TMDF129HL RSCAN0.TMDF129.UINT8[HL]
#define RSCAN0TMDF129HH RSCAN0.TMDF129.UINT8[HH]
#define RSCAN0TMID30 RSCAN0.TMID30.UINT32
#define RSCAN0TMID30L RSCAN0.TMID30.UINT16[L]
#define RSCAN0TMID30LL RSCAN0.TMID30.UINT8[LL]
#define RSCAN0TMID30LH RSCAN0.TMID30.UINT8[LH]
#define RSCAN0TMID30H RSCAN0.TMID30.UINT16[H]
#define RSCAN0TMID30HL RSCAN0.TMID30.UINT8[HL]
#define RSCAN0TMID30HH RSCAN0.TMID30.UINT8[HH]
#define RSCAN0TMPTR30 RSCAN0.TMPTR30.UINT32
#define RSCAN0TMPTR30H RSCAN0.TMPTR30.UINT16[H]
#define RSCAN0TMPTR30HL RSCAN0.TMPTR30.UINT8[HL]
#define RSCAN0TMPTR30HH RSCAN0.TMPTR30.UINT8[HH]
#define RSCAN0TMDF030 RSCAN0.TMDF030.UINT32
#define RSCAN0TMDF030L RSCAN0.TMDF030.UINT16[L]
#define RSCAN0TMDF030LL RSCAN0.TMDF030.UINT8[LL]
#define RSCAN0TMDF030LH RSCAN0.TMDF030.UINT8[LH]
#define RSCAN0TMDF030H RSCAN0.TMDF030.UINT16[H]
#define RSCAN0TMDF030HL RSCAN0.TMDF030.UINT8[HL]
#define RSCAN0TMDF030HH RSCAN0.TMDF030.UINT8[HH]
#define RSCAN0TMDF130 RSCAN0.TMDF130.UINT32
#define RSCAN0TMDF130L RSCAN0.TMDF130.UINT16[L]
#define RSCAN0TMDF130LL RSCAN0.TMDF130.UINT8[LL]
#define RSCAN0TMDF130LH RSCAN0.TMDF130.UINT8[LH]
#define RSCAN0TMDF130H RSCAN0.TMDF130.UINT16[H]
#define RSCAN0TMDF130HL RSCAN0.TMDF130.UINT8[HL]
#define RSCAN0TMDF130HH RSCAN0.TMDF130.UINT8[HH]
#define RSCAN0TMID31 RSCAN0.TMID31.UINT32
#define RSCAN0TMID31L RSCAN0.TMID31.UINT16[L]
#define RSCAN0TMID31LL RSCAN0.TMID31.UINT8[LL]
#define RSCAN0TMID31LH RSCAN0.TMID31.UINT8[LH]
#define RSCAN0TMID31H RSCAN0.TMID31.UINT16[H]
#define RSCAN0TMID31HL RSCAN0.TMID31.UINT8[HL]
#define RSCAN0TMID31HH RSCAN0.TMID31.UINT8[HH]
#define RSCAN0TMPTR31 RSCAN0.TMPTR31.UINT32
#define RSCAN0TMPTR31H RSCAN0.TMPTR31.UINT16[H]
#define RSCAN0TMPTR31HL RSCAN0.TMPTR31.UINT8[HL]
#define RSCAN0TMPTR31HH RSCAN0.TMPTR31.UINT8[HH]
#define RSCAN0TMDF031 RSCAN0.TMDF031.UINT32
#define RSCAN0TMDF031L RSCAN0.TMDF031.UINT16[L]
#define RSCAN0TMDF031LL RSCAN0.TMDF031.UINT8[LL]
#define RSCAN0TMDF031LH RSCAN0.TMDF031.UINT8[LH]
#define RSCAN0TMDF031H RSCAN0.TMDF031.UINT16[H]
#define RSCAN0TMDF031HL RSCAN0.TMDF031.UINT8[HL]
#define RSCAN0TMDF031HH RSCAN0.TMDF031.UINT8[HH]
#define RSCAN0TMDF131 RSCAN0.TMDF131.UINT32
#define RSCAN0TMDF131L RSCAN0.TMDF131.UINT16[L]
#define RSCAN0TMDF131LL RSCAN0.TMDF131.UINT8[LL]
#define RSCAN0TMDF131LH RSCAN0.TMDF131.UINT8[LH]
#define RSCAN0TMDF131H RSCAN0.TMDF131.UINT16[H]
#define RSCAN0TMDF131HL RSCAN0.TMDF131.UINT8[HL]
#define RSCAN0TMDF131HH RSCAN0.TMDF131.UINT8[HH]
#define RSCAN0TMID32 RSCAN0.TMID32.UINT32
#define RSCAN0TMID32L RSCAN0.TMID32.UINT16[L]
#define RSCAN0TMID32LL RSCAN0.TMID32.UINT8[LL]
#define RSCAN0TMID32LH RSCAN0.TMID32.UINT8[LH]
#define RSCAN0TMID32H RSCAN0.TMID32.UINT16[H]
#define RSCAN0TMID32HL RSCAN0.TMID32.UINT8[HL]
#define RSCAN0TMID32HH RSCAN0.TMID32.UINT8[HH]
#define RSCAN0TMPTR32 RSCAN0.TMPTR32.UINT32
#define RSCAN0TMPTR32H RSCAN0.TMPTR32.UINT16[H]
#define RSCAN0TMPTR32HL RSCAN0.TMPTR32.UINT8[HL]
#define RSCAN0TMPTR32HH RSCAN0.TMPTR32.UINT8[HH]
#define RSCAN0TMDF032 RSCAN0.TMDF032.UINT32
#define RSCAN0TMDF032L RSCAN0.TMDF032.UINT16[L]
#define RSCAN0TMDF032LL RSCAN0.TMDF032.UINT8[LL]
#define RSCAN0TMDF032LH RSCAN0.TMDF032.UINT8[LH]
#define RSCAN0TMDF032H RSCAN0.TMDF032.UINT16[H]
#define RSCAN0TMDF032HL RSCAN0.TMDF032.UINT8[HL]
#define RSCAN0TMDF032HH RSCAN0.TMDF032.UINT8[HH]
#define RSCAN0TMDF132 RSCAN0.TMDF132.UINT32
#define RSCAN0TMDF132L RSCAN0.TMDF132.UINT16[L]
#define RSCAN0TMDF132LL RSCAN0.TMDF132.UINT8[LL]
#define RSCAN0TMDF132LH RSCAN0.TMDF132.UINT8[LH]
#define RSCAN0TMDF132H RSCAN0.TMDF132.UINT16[H]
#define RSCAN0TMDF132HL RSCAN0.TMDF132.UINT8[HL]
#define RSCAN0TMDF132HH RSCAN0.TMDF132.UINT8[HH]
#define RSCAN0TMID33 RSCAN0.TMID33.UINT32
#define RSCAN0TMID33L RSCAN0.TMID33.UINT16[L]
#define RSCAN0TMID33LL RSCAN0.TMID33.UINT8[LL]
#define RSCAN0TMID33LH RSCAN0.TMID33.UINT8[LH]
#define RSCAN0TMID33H RSCAN0.TMID33.UINT16[H]
#define RSCAN0TMID33HL RSCAN0.TMID33.UINT8[HL]
#define RSCAN0TMID33HH RSCAN0.TMID33.UINT8[HH]
#define RSCAN0TMPTR33 RSCAN0.TMPTR33.UINT32
#define RSCAN0TMPTR33H RSCAN0.TMPTR33.UINT16[H]
#define RSCAN0TMPTR33HL RSCAN0.TMPTR33.UINT8[HL]
#define RSCAN0TMPTR33HH RSCAN0.TMPTR33.UINT8[HH]
#define RSCAN0TMDF033 RSCAN0.TMDF033.UINT32
#define RSCAN0TMDF033L RSCAN0.TMDF033.UINT16[L]
#define RSCAN0TMDF033LL RSCAN0.TMDF033.UINT8[LL]
#define RSCAN0TMDF033LH RSCAN0.TMDF033.UINT8[LH]
#define RSCAN0TMDF033H RSCAN0.TMDF033.UINT16[H]
#define RSCAN0TMDF033HL RSCAN0.TMDF033.UINT8[HL]
#define RSCAN0TMDF033HH RSCAN0.TMDF033.UINT8[HH]
#define RSCAN0TMDF133 RSCAN0.TMDF133.UINT32
#define RSCAN0TMDF133L RSCAN0.TMDF133.UINT16[L]
#define RSCAN0TMDF133LL RSCAN0.TMDF133.UINT8[LL]
#define RSCAN0TMDF133LH RSCAN0.TMDF133.UINT8[LH]
#define RSCAN0TMDF133H RSCAN0.TMDF133.UINT16[H]
#define RSCAN0TMDF133HL RSCAN0.TMDF133.UINT8[HL]
#define RSCAN0TMDF133HH RSCAN0.TMDF133.UINT8[HH]
#define RSCAN0TMID34 RSCAN0.TMID34.UINT32
#define RSCAN0TMID34L RSCAN0.TMID34.UINT16[L]
#define RSCAN0TMID34LL RSCAN0.TMID34.UINT8[LL]
#define RSCAN0TMID34LH RSCAN0.TMID34.UINT8[LH]
#define RSCAN0TMID34H RSCAN0.TMID34.UINT16[H]
#define RSCAN0TMID34HL RSCAN0.TMID34.UINT8[HL]
#define RSCAN0TMID34HH RSCAN0.TMID34.UINT8[HH]
#define RSCAN0TMPTR34 RSCAN0.TMPTR34.UINT32
#define RSCAN0TMPTR34H RSCAN0.TMPTR34.UINT16[H]
#define RSCAN0TMPTR34HL RSCAN0.TMPTR34.UINT8[HL]
#define RSCAN0TMPTR34HH RSCAN0.TMPTR34.UINT8[HH]
#define RSCAN0TMDF034 RSCAN0.TMDF034.UINT32
#define RSCAN0TMDF034L RSCAN0.TMDF034.UINT16[L]
#define RSCAN0TMDF034LL RSCAN0.TMDF034.UINT8[LL]
#define RSCAN0TMDF034LH RSCAN0.TMDF034.UINT8[LH]
#define RSCAN0TMDF034H RSCAN0.TMDF034.UINT16[H]
#define RSCAN0TMDF034HL RSCAN0.TMDF034.UINT8[HL]
#define RSCAN0TMDF034HH RSCAN0.TMDF034.UINT8[HH]
#define RSCAN0TMDF134 RSCAN0.TMDF134.UINT32
#define RSCAN0TMDF134L RSCAN0.TMDF134.UINT16[L]
#define RSCAN0TMDF134LL RSCAN0.TMDF134.UINT8[LL]
#define RSCAN0TMDF134LH RSCAN0.TMDF134.UINT8[LH]
#define RSCAN0TMDF134H RSCAN0.TMDF134.UINT16[H]
#define RSCAN0TMDF134HL RSCAN0.TMDF134.UINT8[HL]
#define RSCAN0TMDF134HH RSCAN0.TMDF134.UINT8[HH]
#define RSCAN0TMID35 RSCAN0.TMID35.UINT32
#define RSCAN0TMID35L RSCAN0.TMID35.UINT16[L]
#define RSCAN0TMID35LL RSCAN0.TMID35.UINT8[LL]
#define RSCAN0TMID35LH RSCAN0.TMID35.UINT8[LH]
#define RSCAN0TMID35H RSCAN0.TMID35.UINT16[H]
#define RSCAN0TMID35HL RSCAN0.TMID35.UINT8[HL]
#define RSCAN0TMID35HH RSCAN0.TMID35.UINT8[HH]
#define RSCAN0TMPTR35 RSCAN0.TMPTR35.UINT32
#define RSCAN0TMPTR35H RSCAN0.TMPTR35.UINT16[H]
#define RSCAN0TMPTR35HL RSCAN0.TMPTR35.UINT8[HL]
#define RSCAN0TMPTR35HH RSCAN0.TMPTR35.UINT8[HH]
#define RSCAN0TMDF035 RSCAN0.TMDF035.UINT32
#define RSCAN0TMDF035L RSCAN0.TMDF035.UINT16[L]
#define RSCAN0TMDF035LL RSCAN0.TMDF035.UINT8[LL]
#define RSCAN0TMDF035LH RSCAN0.TMDF035.UINT8[LH]
#define RSCAN0TMDF035H RSCAN0.TMDF035.UINT16[H]
#define RSCAN0TMDF035HL RSCAN0.TMDF035.UINT8[HL]
#define RSCAN0TMDF035HH RSCAN0.TMDF035.UINT8[HH]
#define RSCAN0TMDF135 RSCAN0.TMDF135.UINT32
#define RSCAN0TMDF135L RSCAN0.TMDF135.UINT16[L]
#define RSCAN0TMDF135LL RSCAN0.TMDF135.UINT8[LL]
#define RSCAN0TMDF135LH RSCAN0.TMDF135.UINT8[LH]
#define RSCAN0TMDF135H RSCAN0.TMDF135.UINT16[H]
#define RSCAN0TMDF135HL RSCAN0.TMDF135.UINT8[HL]
#define RSCAN0TMDF135HH RSCAN0.TMDF135.UINT8[HH]
#define RSCAN0TMID36 RSCAN0.TMID36.UINT32
#define RSCAN0TMID36L RSCAN0.TMID36.UINT16[L]
#define RSCAN0TMID36LL RSCAN0.TMID36.UINT8[LL]
#define RSCAN0TMID36LH RSCAN0.TMID36.UINT8[LH]
#define RSCAN0TMID36H RSCAN0.TMID36.UINT16[H]
#define RSCAN0TMID36HL RSCAN0.TMID36.UINT8[HL]
#define RSCAN0TMID36HH RSCAN0.TMID36.UINT8[HH]
#define RSCAN0TMPTR36 RSCAN0.TMPTR36.UINT32
#define RSCAN0TMPTR36H RSCAN0.TMPTR36.UINT16[H]
#define RSCAN0TMPTR36HL RSCAN0.TMPTR36.UINT8[HL]
#define RSCAN0TMPTR36HH RSCAN0.TMPTR36.UINT8[HH]
#define RSCAN0TMDF036 RSCAN0.TMDF036.UINT32
#define RSCAN0TMDF036L RSCAN0.TMDF036.UINT16[L]
#define RSCAN0TMDF036LL RSCAN0.TMDF036.UINT8[LL]
#define RSCAN0TMDF036LH RSCAN0.TMDF036.UINT8[LH]
#define RSCAN0TMDF036H RSCAN0.TMDF036.UINT16[H]
#define RSCAN0TMDF036HL RSCAN0.TMDF036.UINT8[HL]
#define RSCAN0TMDF036HH RSCAN0.TMDF036.UINT8[HH]
#define RSCAN0TMDF136 RSCAN0.TMDF136.UINT32
#define RSCAN0TMDF136L RSCAN0.TMDF136.UINT16[L]
#define RSCAN0TMDF136LL RSCAN0.TMDF136.UINT8[LL]
#define RSCAN0TMDF136LH RSCAN0.TMDF136.UINT8[LH]
#define RSCAN0TMDF136H RSCAN0.TMDF136.UINT16[H]
#define RSCAN0TMDF136HL RSCAN0.TMDF136.UINT8[HL]
#define RSCAN0TMDF136HH RSCAN0.TMDF136.UINT8[HH]
#define RSCAN0TMID37 RSCAN0.TMID37.UINT32
#define RSCAN0TMID37L RSCAN0.TMID37.UINT16[L]
#define RSCAN0TMID37LL RSCAN0.TMID37.UINT8[LL]
#define RSCAN0TMID37LH RSCAN0.TMID37.UINT8[LH]
#define RSCAN0TMID37H RSCAN0.TMID37.UINT16[H]
#define RSCAN0TMID37HL RSCAN0.TMID37.UINT8[HL]
#define RSCAN0TMID37HH RSCAN0.TMID37.UINT8[HH]
#define RSCAN0TMPTR37 RSCAN0.TMPTR37.UINT32
#define RSCAN0TMPTR37H RSCAN0.TMPTR37.UINT16[H]
#define RSCAN0TMPTR37HL RSCAN0.TMPTR37.UINT8[HL]
#define RSCAN0TMPTR37HH RSCAN0.TMPTR37.UINT8[HH]
#define RSCAN0TMDF037 RSCAN0.TMDF037.UINT32
#define RSCAN0TMDF037L RSCAN0.TMDF037.UINT16[L]
#define RSCAN0TMDF037LL RSCAN0.TMDF037.UINT8[LL]
#define RSCAN0TMDF037LH RSCAN0.TMDF037.UINT8[LH]
#define RSCAN0TMDF037H RSCAN0.TMDF037.UINT16[H]
#define RSCAN0TMDF037HL RSCAN0.TMDF037.UINT8[HL]
#define RSCAN0TMDF037HH RSCAN0.TMDF037.UINT8[HH]
#define RSCAN0TMDF137 RSCAN0.TMDF137.UINT32
#define RSCAN0TMDF137L RSCAN0.TMDF137.UINT16[L]
#define RSCAN0TMDF137LL RSCAN0.TMDF137.UINT8[LL]
#define RSCAN0TMDF137LH RSCAN0.TMDF137.UINT8[LH]
#define RSCAN0TMDF137H RSCAN0.TMDF137.UINT16[H]
#define RSCAN0TMDF137HL RSCAN0.TMDF137.UINT8[HL]
#define RSCAN0TMDF137HH RSCAN0.TMDF137.UINT8[HH]
#define RSCAN0TMID38 RSCAN0.TMID38.UINT32
#define RSCAN0TMID38L RSCAN0.TMID38.UINT16[L]
#define RSCAN0TMID38LL RSCAN0.TMID38.UINT8[LL]
#define RSCAN0TMID38LH RSCAN0.TMID38.UINT8[LH]
#define RSCAN0TMID38H RSCAN0.TMID38.UINT16[H]
#define RSCAN0TMID38HL RSCAN0.TMID38.UINT8[HL]
#define RSCAN0TMID38HH RSCAN0.TMID38.UINT8[HH]
#define RSCAN0TMPTR38 RSCAN0.TMPTR38.UINT32
#define RSCAN0TMPTR38H RSCAN0.TMPTR38.UINT16[H]
#define RSCAN0TMPTR38HL RSCAN0.TMPTR38.UINT8[HL]
#define RSCAN0TMPTR38HH RSCAN0.TMPTR38.UINT8[HH]
#define RSCAN0TMDF038 RSCAN0.TMDF038.UINT32
#define RSCAN0TMDF038L RSCAN0.TMDF038.UINT16[L]
#define RSCAN0TMDF038LL RSCAN0.TMDF038.UINT8[LL]
#define RSCAN0TMDF038LH RSCAN0.TMDF038.UINT8[LH]
#define RSCAN0TMDF038H RSCAN0.TMDF038.UINT16[H]
#define RSCAN0TMDF038HL RSCAN0.TMDF038.UINT8[HL]
#define RSCAN0TMDF038HH RSCAN0.TMDF038.UINT8[HH]
#define RSCAN0TMDF138 RSCAN0.TMDF138.UINT32
#define RSCAN0TMDF138L RSCAN0.TMDF138.UINT16[L]
#define RSCAN0TMDF138LL RSCAN0.TMDF138.UINT8[LL]
#define RSCAN0TMDF138LH RSCAN0.TMDF138.UINT8[LH]
#define RSCAN0TMDF138H RSCAN0.TMDF138.UINT16[H]
#define RSCAN0TMDF138HL RSCAN0.TMDF138.UINT8[HL]
#define RSCAN0TMDF138HH RSCAN0.TMDF138.UINT8[HH]
#define RSCAN0TMID39 RSCAN0.TMID39.UINT32
#define RSCAN0TMID39L RSCAN0.TMID39.UINT16[L]
#define RSCAN0TMID39LL RSCAN0.TMID39.UINT8[LL]
#define RSCAN0TMID39LH RSCAN0.TMID39.UINT8[LH]
#define RSCAN0TMID39H RSCAN0.TMID39.UINT16[H]
#define RSCAN0TMID39HL RSCAN0.TMID39.UINT8[HL]
#define RSCAN0TMID39HH RSCAN0.TMID39.UINT8[HH]
#define RSCAN0TMPTR39 RSCAN0.TMPTR39.UINT32
#define RSCAN0TMPTR39H RSCAN0.TMPTR39.UINT16[H]
#define RSCAN0TMPTR39HL RSCAN0.TMPTR39.UINT8[HL]
#define RSCAN0TMPTR39HH RSCAN0.TMPTR39.UINT8[HH]
#define RSCAN0TMDF039 RSCAN0.TMDF039.UINT32
#define RSCAN0TMDF039L RSCAN0.TMDF039.UINT16[L]
#define RSCAN0TMDF039LL RSCAN0.TMDF039.UINT8[LL]
#define RSCAN0TMDF039LH RSCAN0.TMDF039.UINT8[LH]
#define RSCAN0TMDF039H RSCAN0.TMDF039.UINT16[H]
#define RSCAN0TMDF039HL RSCAN0.TMDF039.UINT8[HL]
#define RSCAN0TMDF039HH RSCAN0.TMDF039.UINT8[HH]
#define RSCAN0TMDF139 RSCAN0.TMDF139.UINT32
#define RSCAN0TMDF139L RSCAN0.TMDF139.UINT16[L]
#define RSCAN0TMDF139LL RSCAN0.TMDF139.UINT8[LL]
#define RSCAN0TMDF139LH RSCAN0.TMDF139.UINT8[LH]
#define RSCAN0TMDF139H RSCAN0.TMDF139.UINT16[H]
#define RSCAN0TMDF139HL RSCAN0.TMDF139.UINT8[HL]
#define RSCAN0TMDF139HH RSCAN0.TMDF139.UINT8[HH]
#define RSCAN0TMID40 RSCAN0.TMID40.UINT32
#define RSCAN0TMID40L RSCAN0.TMID40.UINT16[L]
#define RSCAN0TMID40LL RSCAN0.TMID40.UINT8[LL]
#define RSCAN0TMID40LH RSCAN0.TMID40.UINT8[LH]
#define RSCAN0TMID40H RSCAN0.TMID40.UINT16[H]
#define RSCAN0TMID40HL RSCAN0.TMID40.UINT8[HL]
#define RSCAN0TMID40HH RSCAN0.TMID40.UINT8[HH]
#define RSCAN0TMPTR40 RSCAN0.TMPTR40.UINT32
#define RSCAN0TMPTR40H RSCAN0.TMPTR40.UINT16[H]
#define RSCAN0TMPTR40HL RSCAN0.TMPTR40.UINT8[HL]
#define RSCAN0TMPTR40HH RSCAN0.TMPTR40.UINT8[HH]
#define RSCAN0TMDF040 RSCAN0.TMDF040.UINT32
#define RSCAN0TMDF040L RSCAN0.TMDF040.UINT16[L]
#define RSCAN0TMDF040LL RSCAN0.TMDF040.UINT8[LL]
#define RSCAN0TMDF040LH RSCAN0.TMDF040.UINT8[LH]
#define RSCAN0TMDF040H RSCAN0.TMDF040.UINT16[H]
#define RSCAN0TMDF040HL RSCAN0.TMDF040.UINT8[HL]
#define RSCAN0TMDF040HH RSCAN0.TMDF040.UINT8[HH]
#define RSCAN0TMDF140 RSCAN0.TMDF140.UINT32
#define RSCAN0TMDF140L RSCAN0.TMDF140.UINT16[L]
#define RSCAN0TMDF140LL RSCAN0.TMDF140.UINT8[LL]
#define RSCAN0TMDF140LH RSCAN0.TMDF140.UINT8[LH]
#define RSCAN0TMDF140H RSCAN0.TMDF140.UINT16[H]
#define RSCAN0TMDF140HL RSCAN0.TMDF140.UINT8[HL]
#define RSCAN0TMDF140HH RSCAN0.TMDF140.UINT8[HH]
#define RSCAN0TMID41 RSCAN0.TMID41.UINT32
#define RSCAN0TMID41L RSCAN0.TMID41.UINT16[L]
#define RSCAN0TMID41LL RSCAN0.TMID41.UINT8[LL]
#define RSCAN0TMID41LH RSCAN0.TMID41.UINT8[LH]
#define RSCAN0TMID41H RSCAN0.TMID41.UINT16[H]
#define RSCAN0TMID41HL RSCAN0.TMID41.UINT8[HL]
#define RSCAN0TMID41HH RSCAN0.TMID41.UINT8[HH]
#define RSCAN0TMPTR41 RSCAN0.TMPTR41.UINT32
#define RSCAN0TMPTR41H RSCAN0.TMPTR41.UINT16[H]
#define RSCAN0TMPTR41HL RSCAN0.TMPTR41.UINT8[HL]
#define RSCAN0TMPTR41HH RSCAN0.TMPTR41.UINT8[HH]
#define RSCAN0TMDF041 RSCAN0.TMDF041.UINT32
#define RSCAN0TMDF041L RSCAN0.TMDF041.UINT16[L]
#define RSCAN0TMDF041LL RSCAN0.TMDF041.UINT8[LL]
#define RSCAN0TMDF041LH RSCAN0.TMDF041.UINT8[LH]
#define RSCAN0TMDF041H RSCAN0.TMDF041.UINT16[H]
#define RSCAN0TMDF041HL RSCAN0.TMDF041.UINT8[HL]
#define RSCAN0TMDF041HH RSCAN0.TMDF041.UINT8[HH]
#define RSCAN0TMDF141 RSCAN0.TMDF141.UINT32
#define RSCAN0TMDF141L RSCAN0.TMDF141.UINT16[L]
#define RSCAN0TMDF141LL RSCAN0.TMDF141.UINT8[LL]
#define RSCAN0TMDF141LH RSCAN0.TMDF141.UINT8[LH]
#define RSCAN0TMDF141H RSCAN0.TMDF141.UINT16[H]
#define RSCAN0TMDF141HL RSCAN0.TMDF141.UINT8[HL]
#define RSCAN0TMDF141HH RSCAN0.TMDF141.UINT8[HH]
#define RSCAN0TMID42 RSCAN0.TMID42.UINT32
#define RSCAN0TMID42L RSCAN0.TMID42.UINT16[L]
#define RSCAN0TMID42LL RSCAN0.TMID42.UINT8[LL]
#define RSCAN0TMID42LH RSCAN0.TMID42.UINT8[LH]
#define RSCAN0TMID42H RSCAN0.TMID42.UINT16[H]
#define RSCAN0TMID42HL RSCAN0.TMID42.UINT8[HL]
#define RSCAN0TMID42HH RSCAN0.TMID42.UINT8[HH]
#define RSCAN0TMPTR42 RSCAN0.TMPTR42.UINT32
#define RSCAN0TMPTR42H RSCAN0.TMPTR42.UINT16[H]
#define RSCAN0TMPTR42HL RSCAN0.TMPTR42.UINT8[HL]
#define RSCAN0TMPTR42HH RSCAN0.TMPTR42.UINT8[HH]
#define RSCAN0TMDF042 RSCAN0.TMDF042.UINT32
#define RSCAN0TMDF042L RSCAN0.TMDF042.UINT16[L]
#define RSCAN0TMDF042LL RSCAN0.TMDF042.UINT8[LL]
#define RSCAN0TMDF042LH RSCAN0.TMDF042.UINT8[LH]
#define RSCAN0TMDF042H RSCAN0.TMDF042.UINT16[H]
#define RSCAN0TMDF042HL RSCAN0.TMDF042.UINT8[HL]
#define RSCAN0TMDF042HH RSCAN0.TMDF042.UINT8[HH]
#define RSCAN0TMDF142 RSCAN0.TMDF142.UINT32
#define RSCAN0TMDF142L RSCAN0.TMDF142.UINT16[L]
#define RSCAN0TMDF142LL RSCAN0.TMDF142.UINT8[LL]
#define RSCAN0TMDF142LH RSCAN0.TMDF142.UINT8[LH]
#define RSCAN0TMDF142H RSCAN0.TMDF142.UINT16[H]
#define RSCAN0TMDF142HL RSCAN0.TMDF142.UINT8[HL]
#define RSCAN0TMDF142HH RSCAN0.TMDF142.UINT8[HH]
#define RSCAN0TMID43 RSCAN0.TMID43.UINT32
#define RSCAN0TMID43L RSCAN0.TMID43.UINT16[L]
#define RSCAN0TMID43LL RSCAN0.TMID43.UINT8[LL]
#define RSCAN0TMID43LH RSCAN0.TMID43.UINT8[LH]
#define RSCAN0TMID43H RSCAN0.TMID43.UINT16[H]
#define RSCAN0TMID43HL RSCAN0.TMID43.UINT8[HL]
#define RSCAN0TMID43HH RSCAN0.TMID43.UINT8[HH]
#define RSCAN0TMPTR43 RSCAN0.TMPTR43.UINT32
#define RSCAN0TMPTR43H RSCAN0.TMPTR43.UINT16[H]
#define RSCAN0TMPTR43HL RSCAN0.TMPTR43.UINT8[HL]
#define RSCAN0TMPTR43HH RSCAN0.TMPTR43.UINT8[HH]
#define RSCAN0TMDF043 RSCAN0.TMDF043.UINT32
#define RSCAN0TMDF043L RSCAN0.TMDF043.UINT16[L]
#define RSCAN0TMDF043LL RSCAN0.TMDF043.UINT8[LL]
#define RSCAN0TMDF043LH RSCAN0.TMDF043.UINT8[LH]
#define RSCAN0TMDF043H RSCAN0.TMDF043.UINT16[H]
#define RSCAN0TMDF043HL RSCAN0.TMDF043.UINT8[HL]
#define RSCAN0TMDF043HH RSCAN0.TMDF043.UINT8[HH]
#define RSCAN0TMDF143 RSCAN0.TMDF143.UINT32
#define RSCAN0TMDF143L RSCAN0.TMDF143.UINT16[L]
#define RSCAN0TMDF143LL RSCAN0.TMDF143.UINT8[LL]
#define RSCAN0TMDF143LH RSCAN0.TMDF143.UINT8[LH]
#define RSCAN0TMDF143H RSCAN0.TMDF143.UINT16[H]
#define RSCAN0TMDF143HL RSCAN0.TMDF143.UINT8[HL]
#define RSCAN0TMDF143HH RSCAN0.TMDF143.UINT8[HH]
#define RSCAN0TMID44 RSCAN0.TMID44.UINT32
#define RSCAN0TMID44L RSCAN0.TMID44.UINT16[L]
#define RSCAN0TMID44LL RSCAN0.TMID44.UINT8[LL]
#define RSCAN0TMID44LH RSCAN0.TMID44.UINT8[LH]
#define RSCAN0TMID44H RSCAN0.TMID44.UINT16[H]
#define RSCAN0TMID44HL RSCAN0.TMID44.UINT8[HL]
#define RSCAN0TMID44HH RSCAN0.TMID44.UINT8[HH]
#define RSCAN0TMPTR44 RSCAN0.TMPTR44.UINT32
#define RSCAN0TMPTR44H RSCAN0.TMPTR44.UINT16[H]
#define RSCAN0TMPTR44HL RSCAN0.TMPTR44.UINT8[HL]
#define RSCAN0TMPTR44HH RSCAN0.TMPTR44.UINT8[HH]
#define RSCAN0TMDF044 RSCAN0.TMDF044.UINT32
#define RSCAN0TMDF044L RSCAN0.TMDF044.UINT16[L]
#define RSCAN0TMDF044LL RSCAN0.TMDF044.UINT8[LL]
#define RSCAN0TMDF044LH RSCAN0.TMDF044.UINT8[LH]
#define RSCAN0TMDF044H RSCAN0.TMDF044.UINT16[H]
#define RSCAN0TMDF044HL RSCAN0.TMDF044.UINT8[HL]
#define RSCAN0TMDF044HH RSCAN0.TMDF044.UINT8[HH]
#define RSCAN0TMDF144 RSCAN0.TMDF144.UINT32
#define RSCAN0TMDF144L RSCAN0.TMDF144.UINT16[L]
#define RSCAN0TMDF144LL RSCAN0.TMDF144.UINT8[LL]
#define RSCAN0TMDF144LH RSCAN0.TMDF144.UINT8[LH]
#define RSCAN0TMDF144H RSCAN0.TMDF144.UINT16[H]
#define RSCAN0TMDF144HL RSCAN0.TMDF144.UINT8[HL]
#define RSCAN0TMDF144HH RSCAN0.TMDF144.UINT8[HH]
#define RSCAN0TMID45 RSCAN0.TMID45.UINT32
#define RSCAN0TMID45L RSCAN0.TMID45.UINT16[L]
#define RSCAN0TMID45LL RSCAN0.TMID45.UINT8[LL]
#define RSCAN0TMID45LH RSCAN0.TMID45.UINT8[LH]
#define RSCAN0TMID45H RSCAN0.TMID45.UINT16[H]
#define RSCAN0TMID45HL RSCAN0.TMID45.UINT8[HL]
#define RSCAN0TMID45HH RSCAN0.TMID45.UINT8[HH]
#define RSCAN0TMPTR45 RSCAN0.TMPTR45.UINT32
#define RSCAN0TMPTR45H RSCAN0.TMPTR45.UINT16[H]
#define RSCAN0TMPTR45HL RSCAN0.TMPTR45.UINT8[HL]
#define RSCAN0TMPTR45HH RSCAN0.TMPTR45.UINT8[HH]
#define RSCAN0TMDF045 RSCAN0.TMDF045.UINT32
#define RSCAN0TMDF045L RSCAN0.TMDF045.UINT16[L]
#define RSCAN0TMDF045LL RSCAN0.TMDF045.UINT8[LL]
#define RSCAN0TMDF045LH RSCAN0.TMDF045.UINT8[LH]
#define RSCAN0TMDF045H RSCAN0.TMDF045.UINT16[H]
#define RSCAN0TMDF045HL RSCAN0.TMDF045.UINT8[HL]
#define RSCAN0TMDF045HH RSCAN0.TMDF045.UINT8[HH]
#define RSCAN0TMDF145 RSCAN0.TMDF145.UINT32
#define RSCAN0TMDF145L RSCAN0.TMDF145.UINT16[L]
#define RSCAN0TMDF145LL RSCAN0.TMDF145.UINT8[LL]
#define RSCAN0TMDF145LH RSCAN0.TMDF145.UINT8[LH]
#define RSCAN0TMDF145H RSCAN0.TMDF145.UINT16[H]
#define RSCAN0TMDF145HL RSCAN0.TMDF145.UINT8[HL]
#define RSCAN0TMDF145HH RSCAN0.TMDF145.UINT8[HH]
#define RSCAN0TMID46 RSCAN0.TMID46.UINT32
#define RSCAN0TMID46L RSCAN0.TMID46.UINT16[L]
#define RSCAN0TMID46LL RSCAN0.TMID46.UINT8[LL]
#define RSCAN0TMID46LH RSCAN0.TMID46.UINT8[LH]
#define RSCAN0TMID46H RSCAN0.TMID46.UINT16[H]
#define RSCAN0TMID46HL RSCAN0.TMID46.UINT8[HL]
#define RSCAN0TMID46HH RSCAN0.TMID46.UINT8[HH]
#define RSCAN0TMPTR46 RSCAN0.TMPTR46.UINT32
#define RSCAN0TMPTR46H RSCAN0.TMPTR46.UINT16[H]
#define RSCAN0TMPTR46HL RSCAN0.TMPTR46.UINT8[HL]
#define RSCAN0TMPTR46HH RSCAN0.TMPTR46.UINT8[HH]
#define RSCAN0TMDF046 RSCAN0.TMDF046.UINT32
#define RSCAN0TMDF046L RSCAN0.TMDF046.UINT16[L]
#define RSCAN0TMDF046LL RSCAN0.TMDF046.UINT8[LL]
#define RSCAN0TMDF046LH RSCAN0.TMDF046.UINT8[LH]
#define RSCAN0TMDF046H RSCAN0.TMDF046.UINT16[H]
#define RSCAN0TMDF046HL RSCAN0.TMDF046.UINT8[HL]
#define RSCAN0TMDF046HH RSCAN0.TMDF046.UINT8[HH]
#define RSCAN0TMDF146 RSCAN0.TMDF146.UINT32
#define RSCAN0TMDF146L RSCAN0.TMDF146.UINT16[L]
#define RSCAN0TMDF146LL RSCAN0.TMDF146.UINT8[LL]
#define RSCAN0TMDF146LH RSCAN0.TMDF146.UINT8[LH]
#define RSCAN0TMDF146H RSCAN0.TMDF146.UINT16[H]
#define RSCAN0TMDF146HL RSCAN0.TMDF146.UINT8[HL]
#define RSCAN0TMDF146HH RSCAN0.TMDF146.UINT8[HH]
#define RSCAN0TMID47 RSCAN0.TMID47.UINT32
#define RSCAN0TMID47L RSCAN0.TMID47.UINT16[L]
#define RSCAN0TMID47LL RSCAN0.TMID47.UINT8[LL]
#define RSCAN0TMID47LH RSCAN0.TMID47.UINT8[LH]
#define RSCAN0TMID47H RSCAN0.TMID47.UINT16[H]
#define RSCAN0TMID47HL RSCAN0.TMID47.UINT8[HL]
#define RSCAN0TMID47HH RSCAN0.TMID47.UINT8[HH]
#define RSCAN0TMPTR47 RSCAN0.TMPTR47.UINT32
#define RSCAN0TMPTR47H RSCAN0.TMPTR47.UINT16[H]
#define RSCAN0TMPTR47HL RSCAN0.TMPTR47.UINT8[HL]
#define RSCAN0TMPTR47HH RSCAN0.TMPTR47.UINT8[HH]
#define RSCAN0TMDF047 RSCAN0.TMDF047.UINT32
#define RSCAN0TMDF047L RSCAN0.TMDF047.UINT16[L]
#define RSCAN0TMDF047LL RSCAN0.TMDF047.UINT8[LL]
#define RSCAN0TMDF047LH RSCAN0.TMDF047.UINT8[LH]
#define RSCAN0TMDF047H RSCAN0.TMDF047.UINT16[H]
#define RSCAN0TMDF047HL RSCAN0.TMDF047.UINT8[HL]
#define RSCAN0TMDF047HH RSCAN0.TMDF047.UINT8[HH]
#define RSCAN0TMDF147 RSCAN0.TMDF147.UINT32
#define RSCAN0TMDF147L RSCAN0.TMDF147.UINT16[L]
#define RSCAN0TMDF147LL RSCAN0.TMDF147.UINT8[LL]
#define RSCAN0TMDF147LH RSCAN0.TMDF147.UINT8[LH]
#define RSCAN0TMDF147H RSCAN0.TMDF147.UINT16[H]
#define RSCAN0TMDF147HL RSCAN0.TMDF147.UINT8[HL]
#define RSCAN0TMDF147HH RSCAN0.TMDF147.UINT8[HH]
#define RSCAN0TMID48 RSCAN0.TMID48.UINT32
#define RSCAN0TMID48L RSCAN0.TMID48.UINT16[L]
#define RSCAN0TMID48LL RSCAN0.TMID48.UINT8[LL]
#define RSCAN0TMID48LH RSCAN0.TMID48.UINT8[LH]
#define RSCAN0TMID48H RSCAN0.TMID48.UINT16[H]
#define RSCAN0TMID48HL RSCAN0.TMID48.UINT8[HL]
#define RSCAN0TMID48HH RSCAN0.TMID48.UINT8[HH]
#define RSCAN0TMPTR48 RSCAN0.TMPTR48.UINT32
#define RSCAN0TMPTR48H RSCAN0.TMPTR48.UINT16[H]
#define RSCAN0TMPTR48HL RSCAN0.TMPTR48.UINT8[HL]
#define RSCAN0TMPTR48HH RSCAN0.TMPTR48.UINT8[HH]
#define RSCAN0TMDF048 RSCAN0.TMDF048.UINT32
#define RSCAN0TMDF048L RSCAN0.TMDF048.UINT16[L]
#define RSCAN0TMDF048LL RSCAN0.TMDF048.UINT8[LL]
#define RSCAN0TMDF048LH RSCAN0.TMDF048.UINT8[LH]
#define RSCAN0TMDF048H RSCAN0.TMDF048.UINT16[H]
#define RSCAN0TMDF048HL RSCAN0.TMDF048.UINT8[HL]
#define RSCAN0TMDF048HH RSCAN0.TMDF048.UINT8[HH]
#define RSCAN0TMDF148 RSCAN0.TMDF148.UINT32
#define RSCAN0TMDF148L RSCAN0.TMDF148.UINT16[L]
#define RSCAN0TMDF148LL RSCAN0.TMDF148.UINT8[LL]
#define RSCAN0TMDF148LH RSCAN0.TMDF148.UINT8[LH]
#define RSCAN0TMDF148H RSCAN0.TMDF148.UINT16[H]
#define RSCAN0TMDF148HL RSCAN0.TMDF148.UINT8[HL]
#define RSCAN0TMDF148HH RSCAN0.TMDF148.UINT8[HH]
#define RSCAN0TMID49 RSCAN0.TMID49.UINT32
#define RSCAN0TMID49L RSCAN0.TMID49.UINT16[L]
#define RSCAN0TMID49LL RSCAN0.TMID49.UINT8[LL]
#define RSCAN0TMID49LH RSCAN0.TMID49.UINT8[LH]
#define RSCAN0TMID49H RSCAN0.TMID49.UINT16[H]
#define RSCAN0TMID49HL RSCAN0.TMID49.UINT8[HL]
#define RSCAN0TMID49HH RSCAN0.TMID49.UINT8[HH]
#define RSCAN0TMPTR49 RSCAN0.TMPTR49.UINT32
#define RSCAN0TMPTR49H RSCAN0.TMPTR49.UINT16[H]
#define RSCAN0TMPTR49HL RSCAN0.TMPTR49.UINT8[HL]
#define RSCAN0TMPTR49HH RSCAN0.TMPTR49.UINT8[HH]
#define RSCAN0TMDF049 RSCAN0.TMDF049.UINT32
#define RSCAN0TMDF049L RSCAN0.TMDF049.UINT16[L]
#define RSCAN0TMDF049LL RSCAN0.TMDF049.UINT8[LL]
#define RSCAN0TMDF049LH RSCAN0.TMDF049.UINT8[LH]
#define RSCAN0TMDF049H RSCAN0.TMDF049.UINT16[H]
#define RSCAN0TMDF049HL RSCAN0.TMDF049.UINT8[HL]
#define RSCAN0TMDF049HH RSCAN0.TMDF049.UINT8[HH]
#define RSCAN0TMDF149 RSCAN0.TMDF149.UINT32
#define RSCAN0TMDF149L RSCAN0.TMDF149.UINT16[L]
#define RSCAN0TMDF149LL RSCAN0.TMDF149.UINT8[LL]
#define RSCAN0TMDF149LH RSCAN0.TMDF149.UINT8[LH]
#define RSCAN0TMDF149H RSCAN0.TMDF149.UINT16[H]
#define RSCAN0TMDF149HL RSCAN0.TMDF149.UINT8[HL]
#define RSCAN0TMDF149HH RSCAN0.TMDF149.UINT8[HH]
#define RSCAN0TMID50 RSCAN0.TMID50.UINT32
#define RSCAN0TMID50L RSCAN0.TMID50.UINT16[L]
#define RSCAN0TMID50LL RSCAN0.TMID50.UINT8[LL]
#define RSCAN0TMID50LH RSCAN0.TMID50.UINT8[LH]
#define RSCAN0TMID50H RSCAN0.TMID50.UINT16[H]
#define RSCAN0TMID50HL RSCAN0.TMID50.UINT8[HL]
#define RSCAN0TMID50HH RSCAN0.TMID50.UINT8[HH]
#define RSCAN0TMPTR50 RSCAN0.TMPTR50.UINT32
#define RSCAN0TMPTR50H RSCAN0.TMPTR50.UINT16[H]
#define RSCAN0TMPTR50HL RSCAN0.TMPTR50.UINT8[HL]
#define RSCAN0TMPTR50HH RSCAN0.TMPTR50.UINT8[HH]
#define RSCAN0TMDF050 RSCAN0.TMDF050.UINT32
#define RSCAN0TMDF050L RSCAN0.TMDF050.UINT16[L]
#define RSCAN0TMDF050LL RSCAN0.TMDF050.UINT8[LL]
#define RSCAN0TMDF050LH RSCAN0.TMDF050.UINT8[LH]
#define RSCAN0TMDF050H RSCAN0.TMDF050.UINT16[H]
#define RSCAN0TMDF050HL RSCAN0.TMDF050.UINT8[HL]
#define RSCAN0TMDF050HH RSCAN0.TMDF050.UINT8[HH]
#define RSCAN0TMDF150 RSCAN0.TMDF150.UINT32
#define RSCAN0TMDF150L RSCAN0.TMDF150.UINT16[L]
#define RSCAN0TMDF150LL RSCAN0.TMDF150.UINT8[LL]
#define RSCAN0TMDF150LH RSCAN0.TMDF150.UINT8[LH]
#define RSCAN0TMDF150H RSCAN0.TMDF150.UINT16[H]
#define RSCAN0TMDF150HL RSCAN0.TMDF150.UINT8[HL]
#define RSCAN0TMDF150HH RSCAN0.TMDF150.UINT8[HH]
#define RSCAN0TMID51 RSCAN0.TMID51.UINT32
#define RSCAN0TMID51L RSCAN0.TMID51.UINT16[L]
#define RSCAN0TMID51LL RSCAN0.TMID51.UINT8[LL]
#define RSCAN0TMID51LH RSCAN0.TMID51.UINT8[LH]
#define RSCAN0TMID51H RSCAN0.TMID51.UINT16[H]
#define RSCAN0TMID51HL RSCAN0.TMID51.UINT8[HL]
#define RSCAN0TMID51HH RSCAN0.TMID51.UINT8[HH]
#define RSCAN0TMPTR51 RSCAN0.TMPTR51.UINT32
#define RSCAN0TMPTR51H RSCAN0.TMPTR51.UINT16[H]
#define RSCAN0TMPTR51HL RSCAN0.TMPTR51.UINT8[HL]
#define RSCAN0TMPTR51HH RSCAN0.TMPTR51.UINT8[HH]
#define RSCAN0TMDF051 RSCAN0.TMDF051.UINT32
#define RSCAN0TMDF051L RSCAN0.TMDF051.UINT16[L]
#define RSCAN0TMDF051LL RSCAN0.TMDF051.UINT8[LL]
#define RSCAN0TMDF051LH RSCAN0.TMDF051.UINT8[LH]
#define RSCAN0TMDF051H RSCAN0.TMDF051.UINT16[H]
#define RSCAN0TMDF051HL RSCAN0.TMDF051.UINT8[HL]
#define RSCAN0TMDF051HH RSCAN0.TMDF051.UINT8[HH]
#define RSCAN0TMDF151 RSCAN0.TMDF151.UINT32
#define RSCAN0TMDF151L RSCAN0.TMDF151.UINT16[L]
#define RSCAN0TMDF151LL RSCAN0.TMDF151.UINT8[LL]
#define RSCAN0TMDF151LH RSCAN0.TMDF151.UINT8[LH]
#define RSCAN0TMDF151H RSCAN0.TMDF151.UINT16[H]
#define RSCAN0TMDF151HL RSCAN0.TMDF151.UINT8[HL]
#define RSCAN0TMDF151HH RSCAN0.TMDF151.UINT8[HH]
#define RSCAN0TMID52 RSCAN0.TMID52.UINT32
#define RSCAN0TMID52L RSCAN0.TMID52.UINT16[L]
#define RSCAN0TMID52LL RSCAN0.TMID52.UINT8[LL]
#define RSCAN0TMID52LH RSCAN0.TMID52.UINT8[LH]
#define RSCAN0TMID52H RSCAN0.TMID52.UINT16[H]
#define RSCAN0TMID52HL RSCAN0.TMID52.UINT8[HL]
#define RSCAN0TMID52HH RSCAN0.TMID52.UINT8[HH]
#define RSCAN0TMPTR52 RSCAN0.TMPTR52.UINT32
#define RSCAN0TMPTR52H RSCAN0.TMPTR52.UINT16[H]
#define RSCAN0TMPTR52HL RSCAN0.TMPTR52.UINT8[HL]
#define RSCAN0TMPTR52HH RSCAN0.TMPTR52.UINT8[HH]
#define RSCAN0TMDF052 RSCAN0.TMDF052.UINT32
#define RSCAN0TMDF052L RSCAN0.TMDF052.UINT16[L]
#define RSCAN0TMDF052LL RSCAN0.TMDF052.UINT8[LL]
#define RSCAN0TMDF052LH RSCAN0.TMDF052.UINT8[LH]
#define RSCAN0TMDF052H RSCAN0.TMDF052.UINT16[H]
#define RSCAN0TMDF052HL RSCAN0.TMDF052.UINT8[HL]
#define RSCAN0TMDF052HH RSCAN0.TMDF052.UINT8[HH]
#define RSCAN0TMDF152 RSCAN0.TMDF152.UINT32
#define RSCAN0TMDF152L RSCAN0.TMDF152.UINT16[L]
#define RSCAN0TMDF152LL RSCAN0.TMDF152.UINT8[LL]
#define RSCAN0TMDF152LH RSCAN0.TMDF152.UINT8[LH]
#define RSCAN0TMDF152H RSCAN0.TMDF152.UINT16[H]
#define RSCAN0TMDF152HL RSCAN0.TMDF152.UINT8[HL]
#define RSCAN0TMDF152HH RSCAN0.TMDF152.UINT8[HH]
#define RSCAN0TMID53 RSCAN0.TMID53.UINT32
#define RSCAN0TMID53L RSCAN0.TMID53.UINT16[L]
#define RSCAN0TMID53LL RSCAN0.TMID53.UINT8[LL]
#define RSCAN0TMID53LH RSCAN0.TMID53.UINT8[LH]
#define RSCAN0TMID53H RSCAN0.TMID53.UINT16[H]
#define RSCAN0TMID53HL RSCAN0.TMID53.UINT8[HL]
#define RSCAN0TMID53HH RSCAN0.TMID53.UINT8[HH]
#define RSCAN0TMPTR53 RSCAN0.TMPTR53.UINT32
#define RSCAN0TMPTR53H RSCAN0.TMPTR53.UINT16[H]
#define RSCAN0TMPTR53HL RSCAN0.TMPTR53.UINT8[HL]
#define RSCAN0TMPTR53HH RSCAN0.TMPTR53.UINT8[HH]
#define RSCAN0TMDF053 RSCAN0.TMDF053.UINT32
#define RSCAN0TMDF053L RSCAN0.TMDF053.UINT16[L]
#define RSCAN0TMDF053LL RSCAN0.TMDF053.UINT8[LL]
#define RSCAN0TMDF053LH RSCAN0.TMDF053.UINT8[LH]
#define RSCAN0TMDF053H RSCAN0.TMDF053.UINT16[H]
#define RSCAN0TMDF053HL RSCAN0.TMDF053.UINT8[HL]
#define RSCAN0TMDF053HH RSCAN0.TMDF053.UINT8[HH]
#define RSCAN0TMDF153 RSCAN0.TMDF153.UINT32
#define RSCAN0TMDF153L RSCAN0.TMDF153.UINT16[L]
#define RSCAN0TMDF153LL RSCAN0.TMDF153.UINT8[LL]
#define RSCAN0TMDF153LH RSCAN0.TMDF153.UINT8[LH]
#define RSCAN0TMDF153H RSCAN0.TMDF153.UINT16[H]
#define RSCAN0TMDF153HL RSCAN0.TMDF153.UINT8[HL]
#define RSCAN0TMDF153HH RSCAN0.TMDF153.UINT8[HH]
#define RSCAN0TMID54 RSCAN0.TMID54.UINT32
#define RSCAN0TMID54L RSCAN0.TMID54.UINT16[L]
#define RSCAN0TMID54LL RSCAN0.TMID54.UINT8[LL]
#define RSCAN0TMID54LH RSCAN0.TMID54.UINT8[LH]
#define RSCAN0TMID54H RSCAN0.TMID54.UINT16[H]
#define RSCAN0TMID54HL RSCAN0.TMID54.UINT8[HL]
#define RSCAN0TMID54HH RSCAN0.TMID54.UINT8[HH]
#define RSCAN0TMPTR54 RSCAN0.TMPTR54.UINT32
#define RSCAN0TMPTR54H RSCAN0.TMPTR54.UINT16[H]
#define RSCAN0TMPTR54HL RSCAN0.TMPTR54.UINT8[HL]
#define RSCAN0TMPTR54HH RSCAN0.TMPTR54.UINT8[HH]
#define RSCAN0TMDF054 RSCAN0.TMDF054.UINT32
#define RSCAN0TMDF054L RSCAN0.TMDF054.UINT16[L]
#define RSCAN0TMDF054LL RSCAN0.TMDF054.UINT8[LL]
#define RSCAN0TMDF054LH RSCAN0.TMDF054.UINT8[LH]
#define RSCAN0TMDF054H RSCAN0.TMDF054.UINT16[H]
#define RSCAN0TMDF054HL RSCAN0.TMDF054.UINT8[HL]
#define RSCAN0TMDF054HH RSCAN0.TMDF054.UINT8[HH]
#define RSCAN0TMDF154 RSCAN0.TMDF154.UINT32
#define RSCAN0TMDF154L RSCAN0.TMDF154.UINT16[L]
#define RSCAN0TMDF154LL RSCAN0.TMDF154.UINT8[LL]
#define RSCAN0TMDF154LH RSCAN0.TMDF154.UINT8[LH]
#define RSCAN0TMDF154H RSCAN0.TMDF154.UINT16[H]
#define RSCAN0TMDF154HL RSCAN0.TMDF154.UINT8[HL]
#define RSCAN0TMDF154HH RSCAN0.TMDF154.UINT8[HH]
#define RSCAN0TMID55 RSCAN0.TMID55.UINT32
#define RSCAN0TMID55L RSCAN0.TMID55.UINT16[L]
#define RSCAN0TMID55LL RSCAN0.TMID55.UINT8[LL]
#define RSCAN0TMID55LH RSCAN0.TMID55.UINT8[LH]
#define RSCAN0TMID55H RSCAN0.TMID55.UINT16[H]
#define RSCAN0TMID55HL RSCAN0.TMID55.UINT8[HL]
#define RSCAN0TMID55HH RSCAN0.TMID55.UINT8[HH]
#define RSCAN0TMPTR55 RSCAN0.TMPTR55.UINT32
#define RSCAN0TMPTR55H RSCAN0.TMPTR55.UINT16[H]
#define RSCAN0TMPTR55HL RSCAN0.TMPTR55.UINT8[HL]
#define RSCAN0TMPTR55HH RSCAN0.TMPTR55.UINT8[HH]
#define RSCAN0TMDF055 RSCAN0.TMDF055.UINT32
#define RSCAN0TMDF055L RSCAN0.TMDF055.UINT16[L]
#define RSCAN0TMDF055LL RSCAN0.TMDF055.UINT8[LL]
#define RSCAN0TMDF055LH RSCAN0.TMDF055.UINT8[LH]
#define RSCAN0TMDF055H RSCAN0.TMDF055.UINT16[H]
#define RSCAN0TMDF055HL RSCAN0.TMDF055.UINT8[HL]
#define RSCAN0TMDF055HH RSCAN0.TMDF055.UINT8[HH]
#define RSCAN0TMDF155 RSCAN0.TMDF155.UINT32
#define RSCAN0TMDF155L RSCAN0.TMDF155.UINT16[L]
#define RSCAN0TMDF155LL RSCAN0.TMDF155.UINT8[LL]
#define RSCAN0TMDF155LH RSCAN0.TMDF155.UINT8[LH]
#define RSCAN0TMDF155H RSCAN0.TMDF155.UINT16[H]
#define RSCAN0TMDF155HL RSCAN0.TMDF155.UINT8[HL]
#define RSCAN0TMDF155HH RSCAN0.TMDF155.UINT8[HH]
#define RSCAN0TMID56 RSCAN0.TMID56.UINT32
#define RSCAN0TMID56L RSCAN0.TMID56.UINT16[L]
#define RSCAN0TMID56LL RSCAN0.TMID56.UINT8[LL]
#define RSCAN0TMID56LH RSCAN0.TMID56.UINT8[LH]
#define RSCAN0TMID56H RSCAN0.TMID56.UINT16[H]
#define RSCAN0TMID56HL RSCAN0.TMID56.UINT8[HL]
#define RSCAN0TMID56HH RSCAN0.TMID56.UINT8[HH]
#define RSCAN0TMPTR56 RSCAN0.TMPTR56.UINT32
#define RSCAN0TMPTR56H RSCAN0.TMPTR56.UINT16[H]
#define RSCAN0TMPTR56HL RSCAN0.TMPTR56.UINT8[HL]
#define RSCAN0TMPTR56HH RSCAN0.TMPTR56.UINT8[HH]
#define RSCAN0TMDF056 RSCAN0.TMDF056.UINT32
#define RSCAN0TMDF056L RSCAN0.TMDF056.UINT16[L]
#define RSCAN0TMDF056LL RSCAN0.TMDF056.UINT8[LL]
#define RSCAN0TMDF056LH RSCAN0.TMDF056.UINT8[LH]
#define RSCAN0TMDF056H RSCAN0.TMDF056.UINT16[H]
#define RSCAN0TMDF056HL RSCAN0.TMDF056.UINT8[HL]
#define RSCAN0TMDF056HH RSCAN0.TMDF056.UINT8[HH]
#define RSCAN0TMDF156 RSCAN0.TMDF156.UINT32
#define RSCAN0TMDF156L RSCAN0.TMDF156.UINT16[L]
#define RSCAN0TMDF156LL RSCAN0.TMDF156.UINT8[LL]
#define RSCAN0TMDF156LH RSCAN0.TMDF156.UINT8[LH]
#define RSCAN0TMDF156H RSCAN0.TMDF156.UINT16[H]
#define RSCAN0TMDF156HL RSCAN0.TMDF156.UINT8[HL]
#define RSCAN0TMDF156HH RSCAN0.TMDF156.UINT8[HH]
#define RSCAN0TMID57 RSCAN0.TMID57.UINT32
#define RSCAN0TMID57L RSCAN0.TMID57.UINT16[L]
#define RSCAN0TMID57LL RSCAN0.TMID57.UINT8[LL]
#define RSCAN0TMID57LH RSCAN0.TMID57.UINT8[LH]
#define RSCAN0TMID57H RSCAN0.TMID57.UINT16[H]
#define RSCAN0TMID57HL RSCAN0.TMID57.UINT8[HL]
#define RSCAN0TMID57HH RSCAN0.TMID57.UINT8[HH]
#define RSCAN0TMPTR57 RSCAN0.TMPTR57.UINT32
#define RSCAN0TMPTR57H RSCAN0.TMPTR57.UINT16[H]
#define RSCAN0TMPTR57HL RSCAN0.TMPTR57.UINT8[HL]
#define RSCAN0TMPTR57HH RSCAN0.TMPTR57.UINT8[HH]
#define RSCAN0TMDF057 RSCAN0.TMDF057.UINT32
#define RSCAN0TMDF057L RSCAN0.TMDF057.UINT16[L]
#define RSCAN0TMDF057LL RSCAN0.TMDF057.UINT8[LL]
#define RSCAN0TMDF057LH RSCAN0.TMDF057.UINT8[LH]
#define RSCAN0TMDF057H RSCAN0.TMDF057.UINT16[H]
#define RSCAN0TMDF057HL RSCAN0.TMDF057.UINT8[HL]
#define RSCAN0TMDF057HH RSCAN0.TMDF057.UINT8[HH]
#define RSCAN0TMDF157 RSCAN0.TMDF157.UINT32
#define RSCAN0TMDF157L RSCAN0.TMDF157.UINT16[L]
#define RSCAN0TMDF157LL RSCAN0.TMDF157.UINT8[LL]
#define RSCAN0TMDF157LH RSCAN0.TMDF157.UINT8[LH]
#define RSCAN0TMDF157H RSCAN0.TMDF157.UINT16[H]
#define RSCAN0TMDF157HL RSCAN0.TMDF157.UINT8[HL]
#define RSCAN0TMDF157HH RSCAN0.TMDF157.UINT8[HH]
#define RSCAN0TMID58 RSCAN0.TMID58.UINT32
#define RSCAN0TMID58L RSCAN0.TMID58.UINT16[L]
#define RSCAN0TMID58LL RSCAN0.TMID58.UINT8[LL]
#define RSCAN0TMID58LH RSCAN0.TMID58.UINT8[LH]
#define RSCAN0TMID58H RSCAN0.TMID58.UINT16[H]
#define RSCAN0TMID58HL RSCAN0.TMID58.UINT8[HL]
#define RSCAN0TMID58HH RSCAN0.TMID58.UINT8[HH]
#define RSCAN0TMPTR58 RSCAN0.TMPTR58.UINT32
#define RSCAN0TMPTR58H RSCAN0.TMPTR58.UINT16[H]
#define RSCAN0TMPTR58HL RSCAN0.TMPTR58.UINT8[HL]
#define RSCAN0TMPTR58HH RSCAN0.TMPTR58.UINT8[HH]
#define RSCAN0TMDF058 RSCAN0.TMDF058.UINT32
#define RSCAN0TMDF058L RSCAN0.TMDF058.UINT16[L]
#define RSCAN0TMDF058LL RSCAN0.TMDF058.UINT8[LL]
#define RSCAN0TMDF058LH RSCAN0.TMDF058.UINT8[LH]
#define RSCAN0TMDF058H RSCAN0.TMDF058.UINT16[H]
#define RSCAN0TMDF058HL RSCAN0.TMDF058.UINT8[HL]
#define RSCAN0TMDF058HH RSCAN0.TMDF058.UINT8[HH]
#define RSCAN0TMDF158 RSCAN0.TMDF158.UINT32
#define RSCAN0TMDF158L RSCAN0.TMDF158.UINT16[L]
#define RSCAN0TMDF158LL RSCAN0.TMDF158.UINT8[LL]
#define RSCAN0TMDF158LH RSCAN0.TMDF158.UINT8[LH]
#define RSCAN0TMDF158H RSCAN0.TMDF158.UINT16[H]
#define RSCAN0TMDF158HL RSCAN0.TMDF158.UINT8[HL]
#define RSCAN0TMDF158HH RSCAN0.TMDF158.UINT8[HH]
#define RSCAN0TMID59 RSCAN0.TMID59.UINT32
#define RSCAN0TMID59L RSCAN0.TMID59.UINT16[L]
#define RSCAN0TMID59LL RSCAN0.TMID59.UINT8[LL]
#define RSCAN0TMID59LH RSCAN0.TMID59.UINT8[LH]
#define RSCAN0TMID59H RSCAN0.TMID59.UINT16[H]
#define RSCAN0TMID59HL RSCAN0.TMID59.UINT8[HL]
#define RSCAN0TMID59HH RSCAN0.TMID59.UINT8[HH]
#define RSCAN0TMPTR59 RSCAN0.TMPTR59.UINT32
#define RSCAN0TMPTR59H RSCAN0.TMPTR59.UINT16[H]
#define RSCAN0TMPTR59HL RSCAN0.TMPTR59.UINT8[HL]
#define RSCAN0TMPTR59HH RSCAN0.TMPTR59.UINT8[HH]
#define RSCAN0TMDF059 RSCAN0.TMDF059.UINT32
#define RSCAN0TMDF059L RSCAN0.TMDF059.UINT16[L]
#define RSCAN0TMDF059LL RSCAN0.TMDF059.UINT8[LL]
#define RSCAN0TMDF059LH RSCAN0.TMDF059.UINT8[LH]
#define RSCAN0TMDF059H RSCAN0.TMDF059.UINT16[H]
#define RSCAN0TMDF059HL RSCAN0.TMDF059.UINT8[HL]
#define RSCAN0TMDF059HH RSCAN0.TMDF059.UINT8[HH]
#define RSCAN0TMDF159 RSCAN0.TMDF159.UINT32
#define RSCAN0TMDF159L RSCAN0.TMDF159.UINT16[L]
#define RSCAN0TMDF159LL RSCAN0.TMDF159.UINT8[LL]
#define RSCAN0TMDF159LH RSCAN0.TMDF159.UINT8[LH]
#define RSCAN0TMDF159H RSCAN0.TMDF159.UINT16[H]
#define RSCAN0TMDF159HL RSCAN0.TMDF159.UINT8[HL]
#define RSCAN0TMDF159HH RSCAN0.TMDF159.UINT8[HH]
#define RSCAN0TMID60 RSCAN0.TMID60.UINT32
#define RSCAN0TMID60L RSCAN0.TMID60.UINT16[L]
#define RSCAN0TMID60LL RSCAN0.TMID60.UINT8[LL]
#define RSCAN0TMID60LH RSCAN0.TMID60.UINT8[LH]
#define RSCAN0TMID60H RSCAN0.TMID60.UINT16[H]
#define RSCAN0TMID60HL RSCAN0.TMID60.UINT8[HL]
#define RSCAN0TMID60HH RSCAN0.TMID60.UINT8[HH]
#define RSCAN0TMPTR60 RSCAN0.TMPTR60.UINT32
#define RSCAN0TMPTR60H RSCAN0.TMPTR60.UINT16[H]
#define RSCAN0TMPTR60HL RSCAN0.TMPTR60.UINT8[HL]
#define RSCAN0TMPTR60HH RSCAN0.TMPTR60.UINT8[HH]
#define RSCAN0TMDF060 RSCAN0.TMDF060.UINT32
#define RSCAN0TMDF060L RSCAN0.TMDF060.UINT16[L]
#define RSCAN0TMDF060LL RSCAN0.TMDF060.UINT8[LL]
#define RSCAN0TMDF060LH RSCAN0.TMDF060.UINT8[LH]
#define RSCAN0TMDF060H RSCAN0.TMDF060.UINT16[H]
#define RSCAN0TMDF060HL RSCAN0.TMDF060.UINT8[HL]
#define RSCAN0TMDF060HH RSCAN0.TMDF060.UINT8[HH]
#define RSCAN0TMDF160 RSCAN0.TMDF160.UINT32
#define RSCAN0TMDF160L RSCAN0.TMDF160.UINT16[L]
#define RSCAN0TMDF160LL RSCAN0.TMDF160.UINT8[LL]
#define RSCAN0TMDF160LH RSCAN0.TMDF160.UINT8[LH]
#define RSCAN0TMDF160H RSCAN0.TMDF160.UINT16[H]
#define RSCAN0TMDF160HL RSCAN0.TMDF160.UINT8[HL]
#define RSCAN0TMDF160HH RSCAN0.TMDF160.UINT8[HH]
#define RSCAN0TMID61 RSCAN0.TMID61.UINT32
#define RSCAN0TMID61L RSCAN0.TMID61.UINT16[L]
#define RSCAN0TMID61LL RSCAN0.TMID61.UINT8[LL]
#define RSCAN0TMID61LH RSCAN0.TMID61.UINT8[LH]
#define RSCAN0TMID61H RSCAN0.TMID61.UINT16[H]
#define RSCAN0TMID61HL RSCAN0.TMID61.UINT8[HL]
#define RSCAN0TMID61HH RSCAN0.TMID61.UINT8[HH]
#define RSCAN0TMPTR61 RSCAN0.TMPTR61.UINT32
#define RSCAN0TMPTR61H RSCAN0.TMPTR61.UINT16[H]
#define RSCAN0TMPTR61HL RSCAN0.TMPTR61.UINT8[HL]
#define RSCAN0TMPTR61HH RSCAN0.TMPTR61.UINT8[HH]
#define RSCAN0TMDF061 RSCAN0.TMDF061.UINT32
#define RSCAN0TMDF061L RSCAN0.TMDF061.UINT16[L]
#define RSCAN0TMDF061LL RSCAN0.TMDF061.UINT8[LL]
#define RSCAN0TMDF061LH RSCAN0.TMDF061.UINT8[LH]
#define RSCAN0TMDF061H RSCAN0.TMDF061.UINT16[H]
#define RSCAN0TMDF061HL RSCAN0.TMDF061.UINT8[HL]
#define RSCAN0TMDF061HH RSCAN0.TMDF061.UINT8[HH]
#define RSCAN0TMDF161 RSCAN0.TMDF161.UINT32
#define RSCAN0TMDF161L RSCAN0.TMDF161.UINT16[L]
#define RSCAN0TMDF161LL RSCAN0.TMDF161.UINT8[LL]
#define RSCAN0TMDF161LH RSCAN0.TMDF161.UINT8[LH]
#define RSCAN0TMDF161H RSCAN0.TMDF161.UINT16[H]
#define RSCAN0TMDF161HL RSCAN0.TMDF161.UINT8[HL]
#define RSCAN0TMDF161HH RSCAN0.TMDF161.UINT8[HH]
#define RSCAN0TMID62 RSCAN0.TMID62.UINT32
#define RSCAN0TMID62L RSCAN0.TMID62.UINT16[L]
#define RSCAN0TMID62LL RSCAN0.TMID62.UINT8[LL]
#define RSCAN0TMID62LH RSCAN0.TMID62.UINT8[LH]
#define RSCAN0TMID62H RSCAN0.TMID62.UINT16[H]
#define RSCAN0TMID62HL RSCAN0.TMID62.UINT8[HL]
#define RSCAN0TMID62HH RSCAN0.TMID62.UINT8[HH]
#define RSCAN0TMPTR62 RSCAN0.TMPTR62.UINT32
#define RSCAN0TMPTR62H RSCAN0.TMPTR62.UINT16[H]
#define RSCAN0TMPTR62HL RSCAN0.TMPTR62.UINT8[HL]
#define RSCAN0TMPTR62HH RSCAN0.TMPTR62.UINT8[HH]
#define RSCAN0TMDF062 RSCAN0.TMDF062.UINT32
#define RSCAN0TMDF062L RSCAN0.TMDF062.UINT16[L]
#define RSCAN0TMDF062LL RSCAN0.TMDF062.UINT8[LL]
#define RSCAN0TMDF062LH RSCAN0.TMDF062.UINT8[LH]
#define RSCAN0TMDF062H RSCAN0.TMDF062.UINT16[H]
#define RSCAN0TMDF062HL RSCAN0.TMDF062.UINT8[HL]
#define RSCAN0TMDF062HH RSCAN0.TMDF062.UINT8[HH]
#define RSCAN0TMDF162 RSCAN0.TMDF162.UINT32
#define RSCAN0TMDF162L RSCAN0.TMDF162.UINT16[L]
#define RSCAN0TMDF162LL RSCAN0.TMDF162.UINT8[LL]
#define RSCAN0TMDF162LH RSCAN0.TMDF162.UINT8[LH]
#define RSCAN0TMDF162H RSCAN0.TMDF162.UINT16[H]
#define RSCAN0TMDF162HL RSCAN0.TMDF162.UINT8[HL]
#define RSCAN0TMDF162HH RSCAN0.TMDF162.UINT8[HH]
#define RSCAN0TMID63 RSCAN0.TMID63.UINT32
#define RSCAN0TMID63L RSCAN0.TMID63.UINT16[L]
#define RSCAN0TMID63LL RSCAN0.TMID63.UINT8[LL]
#define RSCAN0TMID63LH RSCAN0.TMID63.UINT8[LH]
#define RSCAN0TMID63H RSCAN0.TMID63.UINT16[H]
#define RSCAN0TMID63HL RSCAN0.TMID63.UINT8[HL]
#define RSCAN0TMID63HH RSCAN0.TMID63.UINT8[HH]
#define RSCAN0TMPTR63 RSCAN0.TMPTR63.UINT32
#define RSCAN0TMPTR63H RSCAN0.TMPTR63.UINT16[H]
#define RSCAN0TMPTR63HL RSCAN0.TMPTR63.UINT8[HL]
#define RSCAN0TMPTR63HH RSCAN0.TMPTR63.UINT8[HH]
#define RSCAN0TMDF063 RSCAN0.TMDF063.UINT32
#define RSCAN0TMDF063L RSCAN0.TMDF063.UINT16[L]
#define RSCAN0TMDF063LL RSCAN0.TMDF063.UINT8[LL]
#define RSCAN0TMDF063LH RSCAN0.TMDF063.UINT8[LH]
#define RSCAN0TMDF063H RSCAN0.TMDF063.UINT16[H]
#define RSCAN0TMDF063HL RSCAN0.TMDF063.UINT8[HL]
#define RSCAN0TMDF063HH RSCAN0.TMDF063.UINT8[HH]
#define RSCAN0TMDF163 RSCAN0.TMDF163.UINT32
#define RSCAN0TMDF163L RSCAN0.TMDF163.UINT16[L]
#define RSCAN0TMDF163LL RSCAN0.TMDF163.UINT8[LL]
#define RSCAN0TMDF163LH RSCAN0.TMDF163.UINT8[LH]
#define RSCAN0TMDF163H RSCAN0.TMDF163.UINT16[H]
#define RSCAN0TMDF163HL RSCAN0.TMDF163.UINT8[HL]
#define RSCAN0TMDF163HH RSCAN0.TMDF163.UINT8[HH]
#define RSCAN0TMID64 RSCAN0.TMID64.UINT32
#define RSCAN0TMID64L RSCAN0.TMID64.UINT16[L]
#define RSCAN0TMID64LL RSCAN0.TMID64.UINT8[LL]
#define RSCAN0TMID64LH RSCAN0.TMID64.UINT8[LH]
#define RSCAN0TMID64H RSCAN0.TMID64.UINT16[H]
#define RSCAN0TMID64HL RSCAN0.TMID64.UINT8[HL]
#define RSCAN0TMID64HH RSCAN0.TMID64.UINT8[HH]
#define RSCAN0TMPTR64 RSCAN0.TMPTR64.UINT32
#define RSCAN0TMPTR64H RSCAN0.TMPTR64.UINT16[H]
#define RSCAN0TMPTR64HL RSCAN0.TMPTR64.UINT8[HL]
#define RSCAN0TMPTR64HH RSCAN0.TMPTR64.UINT8[HH]
#define RSCAN0TMDF064 RSCAN0.TMDF064.UINT32
#define RSCAN0TMDF064L RSCAN0.TMDF064.UINT16[L]
#define RSCAN0TMDF064LL RSCAN0.TMDF064.UINT8[LL]
#define RSCAN0TMDF064LH RSCAN0.TMDF064.UINT8[LH]
#define RSCAN0TMDF064H RSCAN0.TMDF064.UINT16[H]
#define RSCAN0TMDF064HL RSCAN0.TMDF064.UINT8[HL]
#define RSCAN0TMDF064HH RSCAN0.TMDF064.UINT8[HH]
#define RSCAN0TMDF164 RSCAN0.TMDF164.UINT32
#define RSCAN0TMDF164L RSCAN0.TMDF164.UINT16[L]
#define RSCAN0TMDF164LL RSCAN0.TMDF164.UINT8[LL]
#define RSCAN0TMDF164LH RSCAN0.TMDF164.UINT8[LH]
#define RSCAN0TMDF164H RSCAN0.TMDF164.UINT16[H]
#define RSCAN0TMDF164HL RSCAN0.TMDF164.UINT8[HL]
#define RSCAN0TMDF164HH RSCAN0.TMDF164.UINT8[HH]
#define RSCAN0TMID65 RSCAN0.TMID65.UINT32
#define RSCAN0TMID65L RSCAN0.TMID65.UINT16[L]
#define RSCAN0TMID65LL RSCAN0.TMID65.UINT8[LL]
#define RSCAN0TMID65LH RSCAN0.TMID65.UINT8[LH]
#define RSCAN0TMID65H RSCAN0.TMID65.UINT16[H]
#define RSCAN0TMID65HL RSCAN0.TMID65.UINT8[HL]
#define RSCAN0TMID65HH RSCAN0.TMID65.UINT8[HH]
#define RSCAN0TMPTR65 RSCAN0.TMPTR65.UINT32
#define RSCAN0TMPTR65H RSCAN0.TMPTR65.UINT16[H]
#define RSCAN0TMPTR65HL RSCAN0.TMPTR65.UINT8[HL]
#define RSCAN0TMPTR65HH RSCAN0.TMPTR65.UINT8[HH]
#define RSCAN0TMDF065 RSCAN0.TMDF065.UINT32
#define RSCAN0TMDF065L RSCAN0.TMDF065.UINT16[L]
#define RSCAN0TMDF065LL RSCAN0.TMDF065.UINT8[LL]
#define RSCAN0TMDF065LH RSCAN0.TMDF065.UINT8[LH]
#define RSCAN0TMDF065H RSCAN0.TMDF065.UINT16[H]
#define RSCAN0TMDF065HL RSCAN0.TMDF065.UINT8[HL]
#define RSCAN0TMDF065HH RSCAN0.TMDF065.UINT8[HH]
#define RSCAN0TMDF165 RSCAN0.TMDF165.UINT32
#define RSCAN0TMDF165L RSCAN0.TMDF165.UINT16[L]
#define RSCAN0TMDF165LL RSCAN0.TMDF165.UINT8[LL]
#define RSCAN0TMDF165LH RSCAN0.TMDF165.UINT8[LH]
#define RSCAN0TMDF165H RSCAN0.TMDF165.UINT16[H]
#define RSCAN0TMDF165HL RSCAN0.TMDF165.UINT8[HL]
#define RSCAN0TMDF165HH RSCAN0.TMDF165.UINT8[HH]
#define RSCAN0TMID66 RSCAN0.TMID66.UINT32
#define RSCAN0TMID66L RSCAN0.TMID66.UINT16[L]
#define RSCAN0TMID66LL RSCAN0.TMID66.UINT8[LL]
#define RSCAN0TMID66LH RSCAN0.TMID66.UINT8[LH]
#define RSCAN0TMID66H RSCAN0.TMID66.UINT16[H]
#define RSCAN0TMID66HL RSCAN0.TMID66.UINT8[HL]
#define RSCAN0TMID66HH RSCAN0.TMID66.UINT8[HH]
#define RSCAN0TMPTR66 RSCAN0.TMPTR66.UINT32
#define RSCAN0TMPTR66H RSCAN0.TMPTR66.UINT16[H]
#define RSCAN0TMPTR66HL RSCAN0.TMPTR66.UINT8[HL]
#define RSCAN0TMPTR66HH RSCAN0.TMPTR66.UINT8[HH]
#define RSCAN0TMDF066 RSCAN0.TMDF066.UINT32
#define RSCAN0TMDF066L RSCAN0.TMDF066.UINT16[L]
#define RSCAN0TMDF066LL RSCAN0.TMDF066.UINT8[LL]
#define RSCAN0TMDF066LH RSCAN0.TMDF066.UINT8[LH]
#define RSCAN0TMDF066H RSCAN0.TMDF066.UINT16[H]
#define RSCAN0TMDF066HL RSCAN0.TMDF066.UINT8[HL]
#define RSCAN0TMDF066HH RSCAN0.TMDF066.UINT8[HH]
#define RSCAN0TMDF166 RSCAN0.TMDF166.UINT32
#define RSCAN0TMDF166L RSCAN0.TMDF166.UINT16[L]
#define RSCAN0TMDF166LL RSCAN0.TMDF166.UINT8[LL]
#define RSCAN0TMDF166LH RSCAN0.TMDF166.UINT8[LH]
#define RSCAN0TMDF166H RSCAN0.TMDF166.UINT16[H]
#define RSCAN0TMDF166HL RSCAN0.TMDF166.UINT8[HL]
#define RSCAN0TMDF166HH RSCAN0.TMDF166.UINT8[HH]
#define RSCAN0TMID67 RSCAN0.TMID67.UINT32
#define RSCAN0TMID67L RSCAN0.TMID67.UINT16[L]
#define RSCAN0TMID67LL RSCAN0.TMID67.UINT8[LL]
#define RSCAN0TMID67LH RSCAN0.TMID67.UINT8[LH]
#define RSCAN0TMID67H RSCAN0.TMID67.UINT16[H]
#define RSCAN0TMID67HL RSCAN0.TMID67.UINT8[HL]
#define RSCAN0TMID67HH RSCAN0.TMID67.UINT8[HH]
#define RSCAN0TMPTR67 RSCAN0.TMPTR67.UINT32
#define RSCAN0TMPTR67H RSCAN0.TMPTR67.UINT16[H]
#define RSCAN0TMPTR67HL RSCAN0.TMPTR67.UINT8[HL]
#define RSCAN0TMPTR67HH RSCAN0.TMPTR67.UINT8[HH]
#define RSCAN0TMDF067 RSCAN0.TMDF067.UINT32
#define RSCAN0TMDF067L RSCAN0.TMDF067.UINT16[L]
#define RSCAN0TMDF067LL RSCAN0.TMDF067.UINT8[LL]
#define RSCAN0TMDF067LH RSCAN0.TMDF067.UINT8[LH]
#define RSCAN0TMDF067H RSCAN0.TMDF067.UINT16[H]
#define RSCAN0TMDF067HL RSCAN0.TMDF067.UINT8[HL]
#define RSCAN0TMDF067HH RSCAN0.TMDF067.UINT8[HH]
#define RSCAN0TMDF167 RSCAN0.TMDF167.UINT32
#define RSCAN0TMDF167L RSCAN0.TMDF167.UINT16[L]
#define RSCAN0TMDF167LL RSCAN0.TMDF167.UINT8[LL]
#define RSCAN0TMDF167LH RSCAN0.TMDF167.UINT8[LH]
#define RSCAN0TMDF167H RSCAN0.TMDF167.UINT16[H]
#define RSCAN0TMDF167HL RSCAN0.TMDF167.UINT8[HL]
#define RSCAN0TMDF167HH RSCAN0.TMDF167.UINT8[HH]
#define RSCAN0TMID68 RSCAN0.TMID68.UINT32
#define RSCAN0TMID68L RSCAN0.TMID68.UINT16[L]
#define RSCAN0TMID68LL RSCAN0.TMID68.UINT8[LL]
#define RSCAN0TMID68LH RSCAN0.TMID68.UINT8[LH]
#define RSCAN0TMID68H RSCAN0.TMID68.UINT16[H]
#define RSCAN0TMID68HL RSCAN0.TMID68.UINT8[HL]
#define RSCAN0TMID68HH RSCAN0.TMID68.UINT8[HH]
#define RSCAN0TMPTR68 RSCAN0.TMPTR68.UINT32
#define RSCAN0TMPTR68H RSCAN0.TMPTR68.UINT16[H]
#define RSCAN0TMPTR68HL RSCAN0.TMPTR68.UINT8[HL]
#define RSCAN0TMPTR68HH RSCAN0.TMPTR68.UINT8[HH]
#define RSCAN0TMDF068 RSCAN0.TMDF068.UINT32
#define RSCAN0TMDF068L RSCAN0.TMDF068.UINT16[L]
#define RSCAN0TMDF068LL RSCAN0.TMDF068.UINT8[LL]
#define RSCAN0TMDF068LH RSCAN0.TMDF068.UINT8[LH]
#define RSCAN0TMDF068H RSCAN0.TMDF068.UINT16[H]
#define RSCAN0TMDF068HL RSCAN0.TMDF068.UINT8[HL]
#define RSCAN0TMDF068HH RSCAN0.TMDF068.UINT8[HH]
#define RSCAN0TMDF168 RSCAN0.TMDF168.UINT32
#define RSCAN0TMDF168L RSCAN0.TMDF168.UINT16[L]
#define RSCAN0TMDF168LL RSCAN0.TMDF168.UINT8[LL]
#define RSCAN0TMDF168LH RSCAN0.TMDF168.UINT8[LH]
#define RSCAN0TMDF168H RSCAN0.TMDF168.UINT16[H]
#define RSCAN0TMDF168HL RSCAN0.TMDF168.UINT8[HL]
#define RSCAN0TMDF168HH RSCAN0.TMDF168.UINT8[HH]
#define RSCAN0TMID69 RSCAN0.TMID69.UINT32
#define RSCAN0TMID69L RSCAN0.TMID69.UINT16[L]
#define RSCAN0TMID69LL RSCAN0.TMID69.UINT8[LL]
#define RSCAN0TMID69LH RSCAN0.TMID69.UINT8[LH]
#define RSCAN0TMID69H RSCAN0.TMID69.UINT16[H]
#define RSCAN0TMID69HL RSCAN0.TMID69.UINT8[HL]
#define RSCAN0TMID69HH RSCAN0.TMID69.UINT8[HH]
#define RSCAN0TMPTR69 RSCAN0.TMPTR69.UINT32
#define RSCAN0TMPTR69H RSCAN0.TMPTR69.UINT16[H]
#define RSCAN0TMPTR69HL RSCAN0.TMPTR69.UINT8[HL]
#define RSCAN0TMPTR69HH RSCAN0.TMPTR69.UINT8[HH]
#define RSCAN0TMDF069 RSCAN0.TMDF069.UINT32
#define RSCAN0TMDF069L RSCAN0.TMDF069.UINT16[L]
#define RSCAN0TMDF069LL RSCAN0.TMDF069.UINT8[LL]
#define RSCAN0TMDF069LH RSCAN0.TMDF069.UINT8[LH]
#define RSCAN0TMDF069H RSCAN0.TMDF069.UINT16[H]
#define RSCAN0TMDF069HL RSCAN0.TMDF069.UINT8[HL]
#define RSCAN0TMDF069HH RSCAN0.TMDF069.UINT8[HH]
#define RSCAN0TMDF169 RSCAN0.TMDF169.UINT32
#define RSCAN0TMDF169L RSCAN0.TMDF169.UINT16[L]
#define RSCAN0TMDF169LL RSCAN0.TMDF169.UINT8[LL]
#define RSCAN0TMDF169LH RSCAN0.TMDF169.UINT8[LH]
#define RSCAN0TMDF169H RSCAN0.TMDF169.UINT16[H]
#define RSCAN0TMDF169HL RSCAN0.TMDF169.UINT8[HL]
#define RSCAN0TMDF169HH RSCAN0.TMDF169.UINT8[HH]
#define RSCAN0TMID70 RSCAN0.TMID70.UINT32
#define RSCAN0TMID70L RSCAN0.TMID70.UINT16[L]
#define RSCAN0TMID70LL RSCAN0.TMID70.UINT8[LL]
#define RSCAN0TMID70LH RSCAN0.TMID70.UINT8[LH]
#define RSCAN0TMID70H RSCAN0.TMID70.UINT16[H]
#define RSCAN0TMID70HL RSCAN0.TMID70.UINT8[HL]
#define RSCAN0TMID70HH RSCAN0.TMID70.UINT8[HH]
#define RSCAN0TMPTR70 RSCAN0.TMPTR70.UINT32
#define RSCAN0TMPTR70H RSCAN0.TMPTR70.UINT16[H]
#define RSCAN0TMPTR70HL RSCAN0.TMPTR70.UINT8[HL]
#define RSCAN0TMPTR70HH RSCAN0.TMPTR70.UINT8[HH]
#define RSCAN0TMDF070 RSCAN0.TMDF070.UINT32
#define RSCAN0TMDF070L RSCAN0.TMDF070.UINT16[L]
#define RSCAN0TMDF070LL RSCAN0.TMDF070.UINT8[LL]
#define RSCAN0TMDF070LH RSCAN0.TMDF070.UINT8[LH]
#define RSCAN0TMDF070H RSCAN0.TMDF070.UINT16[H]
#define RSCAN0TMDF070HL RSCAN0.TMDF070.UINT8[HL]
#define RSCAN0TMDF070HH RSCAN0.TMDF070.UINT8[HH]
#define RSCAN0TMDF170 RSCAN0.TMDF170.UINT32
#define RSCAN0TMDF170L RSCAN0.TMDF170.UINT16[L]
#define RSCAN0TMDF170LL RSCAN0.TMDF170.UINT8[LL]
#define RSCAN0TMDF170LH RSCAN0.TMDF170.UINT8[LH]
#define RSCAN0TMDF170H RSCAN0.TMDF170.UINT16[H]
#define RSCAN0TMDF170HL RSCAN0.TMDF170.UINT8[HL]
#define RSCAN0TMDF170HH RSCAN0.TMDF170.UINT8[HH]
#define RSCAN0TMID71 RSCAN0.TMID71.UINT32
#define RSCAN0TMID71L RSCAN0.TMID71.UINT16[L]
#define RSCAN0TMID71LL RSCAN0.TMID71.UINT8[LL]
#define RSCAN0TMID71LH RSCAN0.TMID71.UINT8[LH]
#define RSCAN0TMID71H RSCAN0.TMID71.UINT16[H]
#define RSCAN0TMID71HL RSCAN0.TMID71.UINT8[HL]
#define RSCAN0TMID71HH RSCAN0.TMID71.UINT8[HH]
#define RSCAN0TMPTR71 RSCAN0.TMPTR71.UINT32
#define RSCAN0TMPTR71H RSCAN0.TMPTR71.UINT16[H]
#define RSCAN0TMPTR71HL RSCAN0.TMPTR71.UINT8[HL]
#define RSCAN0TMPTR71HH RSCAN0.TMPTR71.UINT8[HH]
#define RSCAN0TMDF071 RSCAN0.TMDF071.UINT32
#define RSCAN0TMDF071L RSCAN0.TMDF071.UINT16[L]
#define RSCAN0TMDF071LL RSCAN0.TMDF071.UINT8[LL]
#define RSCAN0TMDF071LH RSCAN0.TMDF071.UINT8[LH]
#define RSCAN0TMDF071H RSCAN0.TMDF071.UINT16[H]
#define RSCAN0TMDF071HL RSCAN0.TMDF071.UINT8[HL]
#define RSCAN0TMDF071HH RSCAN0.TMDF071.UINT8[HH]
#define RSCAN0TMDF171 RSCAN0.TMDF171.UINT32
#define RSCAN0TMDF171L RSCAN0.TMDF171.UINT16[L]
#define RSCAN0TMDF171LL RSCAN0.TMDF171.UINT8[LL]
#define RSCAN0TMDF171LH RSCAN0.TMDF171.UINT8[LH]
#define RSCAN0TMDF171H RSCAN0.TMDF171.UINT16[H]
#define RSCAN0TMDF171HL RSCAN0.TMDF171.UINT8[HL]
#define RSCAN0TMDF171HH RSCAN0.TMDF171.UINT8[HH]
#define RSCAN0TMID72 RSCAN0.TMID72.UINT32
#define RSCAN0TMID72L RSCAN0.TMID72.UINT16[L]
#define RSCAN0TMID72LL RSCAN0.TMID72.UINT8[LL]
#define RSCAN0TMID72LH RSCAN0.TMID72.UINT8[LH]
#define RSCAN0TMID72H RSCAN0.TMID72.UINT16[H]
#define RSCAN0TMID72HL RSCAN0.TMID72.UINT8[HL]
#define RSCAN0TMID72HH RSCAN0.TMID72.UINT8[HH]
#define RSCAN0TMPTR72 RSCAN0.TMPTR72.UINT32
#define RSCAN0TMPTR72H RSCAN0.TMPTR72.UINT16[H]
#define RSCAN0TMPTR72HL RSCAN0.TMPTR72.UINT8[HL]
#define RSCAN0TMPTR72HH RSCAN0.TMPTR72.UINT8[HH]
#define RSCAN0TMDF072 RSCAN0.TMDF072.UINT32
#define RSCAN0TMDF072L RSCAN0.TMDF072.UINT16[L]
#define RSCAN0TMDF072LL RSCAN0.TMDF072.UINT8[LL]
#define RSCAN0TMDF072LH RSCAN0.TMDF072.UINT8[LH]
#define RSCAN0TMDF072H RSCAN0.TMDF072.UINT16[H]
#define RSCAN0TMDF072HL RSCAN0.TMDF072.UINT8[HL]
#define RSCAN0TMDF072HH RSCAN0.TMDF072.UINT8[HH]
#define RSCAN0TMDF172 RSCAN0.TMDF172.UINT32
#define RSCAN0TMDF172L RSCAN0.TMDF172.UINT16[L]
#define RSCAN0TMDF172LL RSCAN0.TMDF172.UINT8[LL]
#define RSCAN0TMDF172LH RSCAN0.TMDF172.UINT8[LH]
#define RSCAN0TMDF172H RSCAN0.TMDF172.UINT16[H]
#define RSCAN0TMDF172HL RSCAN0.TMDF172.UINT8[HL]
#define RSCAN0TMDF172HH RSCAN0.TMDF172.UINT8[HH]
#define RSCAN0TMID73 RSCAN0.TMID73.UINT32
#define RSCAN0TMID73L RSCAN0.TMID73.UINT16[L]
#define RSCAN0TMID73LL RSCAN0.TMID73.UINT8[LL]
#define RSCAN0TMID73LH RSCAN0.TMID73.UINT8[LH]
#define RSCAN0TMID73H RSCAN0.TMID73.UINT16[H]
#define RSCAN0TMID73HL RSCAN0.TMID73.UINT8[HL]
#define RSCAN0TMID73HH RSCAN0.TMID73.UINT8[HH]
#define RSCAN0TMPTR73 RSCAN0.TMPTR73.UINT32
#define RSCAN0TMPTR73H RSCAN0.TMPTR73.UINT16[H]
#define RSCAN0TMPTR73HL RSCAN0.TMPTR73.UINT8[HL]
#define RSCAN0TMPTR73HH RSCAN0.TMPTR73.UINT8[HH]
#define RSCAN0TMDF073 RSCAN0.TMDF073.UINT32
#define RSCAN0TMDF073L RSCAN0.TMDF073.UINT16[L]
#define RSCAN0TMDF073LL RSCAN0.TMDF073.UINT8[LL]
#define RSCAN0TMDF073LH RSCAN0.TMDF073.UINT8[LH]
#define RSCAN0TMDF073H RSCAN0.TMDF073.UINT16[H]
#define RSCAN0TMDF073HL RSCAN0.TMDF073.UINT8[HL]
#define RSCAN0TMDF073HH RSCAN0.TMDF073.UINT8[HH]
#define RSCAN0TMDF173 RSCAN0.TMDF173.UINT32
#define RSCAN0TMDF173L RSCAN0.TMDF173.UINT16[L]
#define RSCAN0TMDF173LL RSCAN0.TMDF173.UINT8[LL]
#define RSCAN0TMDF173LH RSCAN0.TMDF173.UINT8[LH]
#define RSCAN0TMDF173H RSCAN0.TMDF173.UINT16[H]
#define RSCAN0TMDF173HL RSCAN0.TMDF173.UINT8[HL]
#define RSCAN0TMDF173HH RSCAN0.TMDF173.UINT8[HH]
#define RSCAN0TMID74 RSCAN0.TMID74.UINT32
#define RSCAN0TMID74L RSCAN0.TMID74.UINT16[L]
#define RSCAN0TMID74LL RSCAN0.TMID74.UINT8[LL]
#define RSCAN0TMID74LH RSCAN0.TMID74.UINT8[LH]
#define RSCAN0TMID74H RSCAN0.TMID74.UINT16[H]
#define RSCAN0TMID74HL RSCAN0.TMID74.UINT8[HL]
#define RSCAN0TMID74HH RSCAN0.TMID74.UINT8[HH]
#define RSCAN0TMPTR74 RSCAN0.TMPTR74.UINT32
#define RSCAN0TMPTR74H RSCAN0.TMPTR74.UINT16[H]
#define RSCAN0TMPTR74HL RSCAN0.TMPTR74.UINT8[HL]
#define RSCAN0TMPTR74HH RSCAN0.TMPTR74.UINT8[HH]
#define RSCAN0TMDF074 RSCAN0.TMDF074.UINT32
#define RSCAN0TMDF074L RSCAN0.TMDF074.UINT16[L]
#define RSCAN0TMDF074LL RSCAN0.TMDF074.UINT8[LL]
#define RSCAN0TMDF074LH RSCAN0.TMDF074.UINT8[LH]
#define RSCAN0TMDF074H RSCAN0.TMDF074.UINT16[H]
#define RSCAN0TMDF074HL RSCAN0.TMDF074.UINT8[HL]
#define RSCAN0TMDF074HH RSCAN0.TMDF074.UINT8[HH]
#define RSCAN0TMDF174 RSCAN0.TMDF174.UINT32
#define RSCAN0TMDF174L RSCAN0.TMDF174.UINT16[L]
#define RSCAN0TMDF174LL RSCAN0.TMDF174.UINT8[LL]
#define RSCAN0TMDF174LH RSCAN0.TMDF174.UINT8[LH]
#define RSCAN0TMDF174H RSCAN0.TMDF174.UINT16[H]
#define RSCAN0TMDF174HL RSCAN0.TMDF174.UINT8[HL]
#define RSCAN0TMDF174HH RSCAN0.TMDF174.UINT8[HH]
#define RSCAN0TMID75 RSCAN0.TMID75.UINT32
#define RSCAN0TMID75L RSCAN0.TMID75.UINT16[L]
#define RSCAN0TMID75LL RSCAN0.TMID75.UINT8[LL]
#define RSCAN0TMID75LH RSCAN0.TMID75.UINT8[LH]
#define RSCAN0TMID75H RSCAN0.TMID75.UINT16[H]
#define RSCAN0TMID75HL RSCAN0.TMID75.UINT8[HL]
#define RSCAN0TMID75HH RSCAN0.TMID75.UINT8[HH]
#define RSCAN0TMPTR75 RSCAN0.TMPTR75.UINT32
#define RSCAN0TMPTR75H RSCAN0.TMPTR75.UINT16[H]
#define RSCAN0TMPTR75HL RSCAN0.TMPTR75.UINT8[HL]
#define RSCAN0TMPTR75HH RSCAN0.TMPTR75.UINT8[HH]
#define RSCAN0TMDF075 RSCAN0.TMDF075.UINT32
#define RSCAN0TMDF075L RSCAN0.TMDF075.UINT16[L]
#define RSCAN0TMDF075LL RSCAN0.TMDF075.UINT8[LL]
#define RSCAN0TMDF075LH RSCAN0.TMDF075.UINT8[LH]
#define RSCAN0TMDF075H RSCAN0.TMDF075.UINT16[H]
#define RSCAN0TMDF075HL RSCAN0.TMDF075.UINT8[HL]
#define RSCAN0TMDF075HH RSCAN0.TMDF075.UINT8[HH]
#define RSCAN0TMDF175 RSCAN0.TMDF175.UINT32
#define RSCAN0TMDF175L RSCAN0.TMDF175.UINT16[L]
#define RSCAN0TMDF175LL RSCAN0.TMDF175.UINT8[LL]
#define RSCAN0TMDF175LH RSCAN0.TMDF175.UINT8[LH]
#define RSCAN0TMDF175H RSCAN0.TMDF175.UINT16[H]
#define RSCAN0TMDF175HL RSCAN0.TMDF175.UINT8[HL]
#define RSCAN0TMDF175HH RSCAN0.TMDF175.UINT8[HH]
#define RSCAN0TMID76 RSCAN0.TMID76.UINT32
#define RSCAN0TMID76L RSCAN0.TMID76.UINT16[L]
#define RSCAN0TMID76LL RSCAN0.TMID76.UINT8[LL]
#define RSCAN0TMID76LH RSCAN0.TMID76.UINT8[LH]
#define RSCAN0TMID76H RSCAN0.TMID76.UINT16[H]
#define RSCAN0TMID76HL RSCAN0.TMID76.UINT8[HL]
#define RSCAN0TMID76HH RSCAN0.TMID76.UINT8[HH]
#define RSCAN0TMPTR76 RSCAN0.TMPTR76.UINT32
#define RSCAN0TMPTR76H RSCAN0.TMPTR76.UINT16[H]
#define RSCAN0TMPTR76HL RSCAN0.TMPTR76.UINT8[HL]
#define RSCAN0TMPTR76HH RSCAN0.TMPTR76.UINT8[HH]
#define RSCAN0TMDF076 RSCAN0.TMDF076.UINT32
#define RSCAN0TMDF076L RSCAN0.TMDF076.UINT16[L]
#define RSCAN0TMDF076LL RSCAN0.TMDF076.UINT8[LL]
#define RSCAN0TMDF076LH RSCAN0.TMDF076.UINT8[LH]
#define RSCAN0TMDF076H RSCAN0.TMDF076.UINT16[H]
#define RSCAN0TMDF076HL RSCAN0.TMDF076.UINT8[HL]
#define RSCAN0TMDF076HH RSCAN0.TMDF076.UINT8[HH]
#define RSCAN0TMDF176 RSCAN0.TMDF176.UINT32
#define RSCAN0TMDF176L RSCAN0.TMDF176.UINT16[L]
#define RSCAN0TMDF176LL RSCAN0.TMDF176.UINT8[LL]
#define RSCAN0TMDF176LH RSCAN0.TMDF176.UINT8[LH]
#define RSCAN0TMDF176H RSCAN0.TMDF176.UINT16[H]
#define RSCAN0TMDF176HL RSCAN0.TMDF176.UINT8[HL]
#define RSCAN0TMDF176HH RSCAN0.TMDF176.UINT8[HH]
#define RSCAN0TMID77 RSCAN0.TMID77.UINT32
#define RSCAN0TMID77L RSCAN0.TMID77.UINT16[L]
#define RSCAN0TMID77LL RSCAN0.TMID77.UINT8[LL]
#define RSCAN0TMID77LH RSCAN0.TMID77.UINT8[LH]
#define RSCAN0TMID77H RSCAN0.TMID77.UINT16[H]
#define RSCAN0TMID77HL RSCAN0.TMID77.UINT8[HL]
#define RSCAN0TMID77HH RSCAN0.TMID77.UINT8[HH]
#define RSCAN0TMPTR77 RSCAN0.TMPTR77.UINT32
#define RSCAN0TMPTR77H RSCAN0.TMPTR77.UINT16[H]
#define RSCAN0TMPTR77HL RSCAN0.TMPTR77.UINT8[HL]
#define RSCAN0TMPTR77HH RSCAN0.TMPTR77.UINT8[HH]
#define RSCAN0TMDF077 RSCAN0.TMDF077.UINT32
#define RSCAN0TMDF077L RSCAN0.TMDF077.UINT16[L]
#define RSCAN0TMDF077LL RSCAN0.TMDF077.UINT8[LL]
#define RSCAN0TMDF077LH RSCAN0.TMDF077.UINT8[LH]
#define RSCAN0TMDF077H RSCAN0.TMDF077.UINT16[H]
#define RSCAN0TMDF077HL RSCAN0.TMDF077.UINT8[HL]
#define RSCAN0TMDF077HH RSCAN0.TMDF077.UINT8[HH]
#define RSCAN0TMDF177 RSCAN0.TMDF177.UINT32
#define RSCAN0TMDF177L RSCAN0.TMDF177.UINT16[L]
#define RSCAN0TMDF177LL RSCAN0.TMDF177.UINT8[LL]
#define RSCAN0TMDF177LH RSCAN0.TMDF177.UINT8[LH]
#define RSCAN0TMDF177H RSCAN0.TMDF177.UINT16[H]
#define RSCAN0TMDF177HL RSCAN0.TMDF177.UINT8[HL]
#define RSCAN0TMDF177HH RSCAN0.TMDF177.UINT8[HH]
#define RSCAN0TMID78 RSCAN0.TMID78.UINT32
#define RSCAN0TMID78L RSCAN0.TMID78.UINT16[L]
#define RSCAN0TMID78LL RSCAN0.TMID78.UINT8[LL]
#define RSCAN0TMID78LH RSCAN0.TMID78.UINT8[LH]
#define RSCAN0TMID78H RSCAN0.TMID78.UINT16[H]
#define RSCAN0TMID78HL RSCAN0.TMID78.UINT8[HL]
#define RSCAN0TMID78HH RSCAN0.TMID78.UINT8[HH]
#define RSCAN0TMPTR78 RSCAN0.TMPTR78.UINT32
#define RSCAN0TMPTR78H RSCAN0.TMPTR78.UINT16[H]
#define RSCAN0TMPTR78HL RSCAN0.TMPTR78.UINT8[HL]
#define RSCAN0TMPTR78HH RSCAN0.TMPTR78.UINT8[HH]
#define RSCAN0TMDF078 RSCAN0.TMDF078.UINT32
#define RSCAN0TMDF078L RSCAN0.TMDF078.UINT16[L]
#define RSCAN0TMDF078LL RSCAN0.TMDF078.UINT8[LL]
#define RSCAN0TMDF078LH RSCAN0.TMDF078.UINT8[LH]
#define RSCAN0TMDF078H RSCAN0.TMDF078.UINT16[H]
#define RSCAN0TMDF078HL RSCAN0.TMDF078.UINT8[HL]
#define RSCAN0TMDF078HH RSCAN0.TMDF078.UINT8[HH]
#define RSCAN0TMDF178 RSCAN0.TMDF178.UINT32
#define RSCAN0TMDF178L RSCAN0.TMDF178.UINT16[L]
#define RSCAN0TMDF178LL RSCAN0.TMDF178.UINT8[LL]
#define RSCAN0TMDF178LH RSCAN0.TMDF178.UINT8[LH]
#define RSCAN0TMDF178H RSCAN0.TMDF178.UINT16[H]
#define RSCAN0TMDF178HL RSCAN0.TMDF178.UINT8[HL]
#define RSCAN0TMDF178HH RSCAN0.TMDF178.UINT8[HH]
#define RSCAN0TMID79 RSCAN0.TMID79.UINT32
#define RSCAN0TMID79L RSCAN0.TMID79.UINT16[L]
#define RSCAN0TMID79LL RSCAN0.TMID79.UINT8[LL]
#define RSCAN0TMID79LH RSCAN0.TMID79.UINT8[LH]
#define RSCAN0TMID79H RSCAN0.TMID79.UINT16[H]
#define RSCAN0TMID79HL RSCAN0.TMID79.UINT8[HL]
#define RSCAN0TMID79HH RSCAN0.TMID79.UINT8[HH]
#define RSCAN0TMPTR79 RSCAN0.TMPTR79.UINT32
#define RSCAN0TMPTR79H RSCAN0.TMPTR79.UINT16[H]
#define RSCAN0TMPTR79HL RSCAN0.TMPTR79.UINT8[HL]
#define RSCAN0TMPTR79HH RSCAN0.TMPTR79.UINT8[HH]
#define RSCAN0TMDF079 RSCAN0.TMDF079.UINT32
#define RSCAN0TMDF079L RSCAN0.TMDF079.UINT16[L]
#define RSCAN0TMDF079LL RSCAN0.TMDF079.UINT8[LL]
#define RSCAN0TMDF079LH RSCAN0.TMDF079.UINT8[LH]
#define RSCAN0TMDF079H RSCAN0.TMDF079.UINT16[H]
#define RSCAN0TMDF079HL RSCAN0.TMDF079.UINT8[HL]
#define RSCAN0TMDF079HH RSCAN0.TMDF079.UINT8[HH]
#define RSCAN0TMDF179 RSCAN0.TMDF179.UINT32
#define RSCAN0TMDF179L RSCAN0.TMDF179.UINT16[L]
#define RSCAN0TMDF179LL RSCAN0.TMDF179.UINT8[LL]
#define RSCAN0TMDF179LH RSCAN0.TMDF179.UINT8[LH]
#define RSCAN0TMDF179H RSCAN0.TMDF179.UINT16[H]
#define RSCAN0TMDF179HL RSCAN0.TMDF179.UINT8[HL]
#define RSCAN0TMDF179HH RSCAN0.TMDF179.UINT8[HH]
#define RSCAN0TMID80 RSCAN0.TMID80.UINT32
#define RSCAN0TMID80L RSCAN0.TMID80.UINT16[L]
#define RSCAN0TMID80LL RSCAN0.TMID80.UINT8[LL]
#define RSCAN0TMID80LH RSCAN0.TMID80.UINT8[LH]
#define RSCAN0TMID80H RSCAN0.TMID80.UINT16[H]
#define RSCAN0TMID80HL RSCAN0.TMID80.UINT8[HL]
#define RSCAN0TMID80HH RSCAN0.TMID80.UINT8[HH]
#define RSCAN0TMPTR80 RSCAN0.TMPTR80.UINT32
#define RSCAN0TMPTR80H RSCAN0.TMPTR80.UINT16[H]
#define RSCAN0TMPTR80HL RSCAN0.TMPTR80.UINT8[HL]
#define RSCAN0TMPTR80HH RSCAN0.TMPTR80.UINT8[HH]
#define RSCAN0TMDF080 RSCAN0.TMDF080.UINT32
#define RSCAN0TMDF080L RSCAN0.TMDF080.UINT16[L]
#define RSCAN0TMDF080LL RSCAN0.TMDF080.UINT8[LL]
#define RSCAN0TMDF080LH RSCAN0.TMDF080.UINT8[LH]
#define RSCAN0TMDF080H RSCAN0.TMDF080.UINT16[H]
#define RSCAN0TMDF080HL RSCAN0.TMDF080.UINT8[HL]
#define RSCAN0TMDF080HH RSCAN0.TMDF080.UINT8[HH]
#define RSCAN0TMDF180 RSCAN0.TMDF180.UINT32
#define RSCAN0TMDF180L RSCAN0.TMDF180.UINT16[L]
#define RSCAN0TMDF180LL RSCAN0.TMDF180.UINT8[LL]
#define RSCAN0TMDF180LH RSCAN0.TMDF180.UINT8[LH]
#define RSCAN0TMDF180H RSCAN0.TMDF180.UINT16[H]
#define RSCAN0TMDF180HL RSCAN0.TMDF180.UINT8[HL]
#define RSCAN0TMDF180HH RSCAN0.TMDF180.UINT8[HH]
#define RSCAN0TMID81 RSCAN0.TMID81.UINT32
#define RSCAN0TMID81L RSCAN0.TMID81.UINT16[L]
#define RSCAN0TMID81LL RSCAN0.TMID81.UINT8[LL]
#define RSCAN0TMID81LH RSCAN0.TMID81.UINT8[LH]
#define RSCAN0TMID81H RSCAN0.TMID81.UINT16[H]
#define RSCAN0TMID81HL RSCAN0.TMID81.UINT8[HL]
#define RSCAN0TMID81HH RSCAN0.TMID81.UINT8[HH]
#define RSCAN0TMPTR81 RSCAN0.TMPTR81.UINT32
#define RSCAN0TMPTR81H RSCAN0.TMPTR81.UINT16[H]
#define RSCAN0TMPTR81HL RSCAN0.TMPTR81.UINT8[HL]
#define RSCAN0TMPTR81HH RSCAN0.TMPTR81.UINT8[HH]
#define RSCAN0TMDF081 RSCAN0.TMDF081.UINT32
#define RSCAN0TMDF081L RSCAN0.TMDF081.UINT16[L]
#define RSCAN0TMDF081LL RSCAN0.TMDF081.UINT8[LL]
#define RSCAN0TMDF081LH RSCAN0.TMDF081.UINT8[LH]
#define RSCAN0TMDF081H RSCAN0.TMDF081.UINT16[H]
#define RSCAN0TMDF081HL RSCAN0.TMDF081.UINT8[HL]
#define RSCAN0TMDF081HH RSCAN0.TMDF081.UINT8[HH]
#define RSCAN0TMDF181 RSCAN0.TMDF181.UINT32
#define RSCAN0TMDF181L RSCAN0.TMDF181.UINT16[L]
#define RSCAN0TMDF181LL RSCAN0.TMDF181.UINT8[LL]
#define RSCAN0TMDF181LH RSCAN0.TMDF181.UINT8[LH]
#define RSCAN0TMDF181H RSCAN0.TMDF181.UINT16[H]
#define RSCAN0TMDF181HL RSCAN0.TMDF181.UINT8[HL]
#define RSCAN0TMDF181HH RSCAN0.TMDF181.UINT8[HH]
#define RSCAN0TMID82 RSCAN0.TMID82.UINT32
#define RSCAN0TMID82L RSCAN0.TMID82.UINT16[L]
#define RSCAN0TMID82LL RSCAN0.TMID82.UINT8[LL]
#define RSCAN0TMID82LH RSCAN0.TMID82.UINT8[LH]
#define RSCAN0TMID82H RSCAN0.TMID82.UINT16[H]
#define RSCAN0TMID82HL RSCAN0.TMID82.UINT8[HL]
#define RSCAN0TMID82HH RSCAN0.TMID82.UINT8[HH]
#define RSCAN0TMPTR82 RSCAN0.TMPTR82.UINT32
#define RSCAN0TMPTR82H RSCAN0.TMPTR82.UINT16[H]
#define RSCAN0TMPTR82HL RSCAN0.TMPTR82.UINT8[HL]
#define RSCAN0TMPTR82HH RSCAN0.TMPTR82.UINT8[HH]
#define RSCAN0TMDF082 RSCAN0.TMDF082.UINT32
#define RSCAN0TMDF082L RSCAN0.TMDF082.UINT16[L]
#define RSCAN0TMDF082LL RSCAN0.TMDF082.UINT8[LL]
#define RSCAN0TMDF082LH RSCAN0.TMDF082.UINT8[LH]
#define RSCAN0TMDF082H RSCAN0.TMDF082.UINT16[H]
#define RSCAN0TMDF082HL RSCAN0.TMDF082.UINT8[HL]
#define RSCAN0TMDF082HH RSCAN0.TMDF082.UINT8[HH]
#define RSCAN0TMDF182 RSCAN0.TMDF182.UINT32
#define RSCAN0TMDF182L RSCAN0.TMDF182.UINT16[L]
#define RSCAN0TMDF182LL RSCAN0.TMDF182.UINT8[LL]
#define RSCAN0TMDF182LH RSCAN0.TMDF182.UINT8[LH]
#define RSCAN0TMDF182H RSCAN0.TMDF182.UINT16[H]
#define RSCAN0TMDF182HL RSCAN0.TMDF182.UINT8[HL]
#define RSCAN0TMDF182HH RSCAN0.TMDF182.UINT8[HH]
#define RSCAN0TMID83 RSCAN0.TMID83.UINT32
#define RSCAN0TMID83L RSCAN0.TMID83.UINT16[L]
#define RSCAN0TMID83LL RSCAN0.TMID83.UINT8[LL]
#define RSCAN0TMID83LH RSCAN0.TMID83.UINT8[LH]
#define RSCAN0TMID83H RSCAN0.TMID83.UINT16[H]
#define RSCAN0TMID83HL RSCAN0.TMID83.UINT8[HL]
#define RSCAN0TMID83HH RSCAN0.TMID83.UINT8[HH]
#define RSCAN0TMPTR83 RSCAN0.TMPTR83.UINT32
#define RSCAN0TMPTR83H RSCAN0.TMPTR83.UINT16[H]
#define RSCAN0TMPTR83HL RSCAN0.TMPTR83.UINT8[HL]
#define RSCAN0TMPTR83HH RSCAN0.TMPTR83.UINT8[HH]
#define RSCAN0TMDF083 RSCAN0.TMDF083.UINT32
#define RSCAN0TMDF083L RSCAN0.TMDF083.UINT16[L]
#define RSCAN0TMDF083LL RSCAN0.TMDF083.UINT8[LL]
#define RSCAN0TMDF083LH RSCAN0.TMDF083.UINT8[LH]
#define RSCAN0TMDF083H RSCAN0.TMDF083.UINT16[H]
#define RSCAN0TMDF083HL RSCAN0.TMDF083.UINT8[HL]
#define RSCAN0TMDF083HH RSCAN0.TMDF083.UINT8[HH]
#define RSCAN0TMDF183 RSCAN0.TMDF183.UINT32
#define RSCAN0TMDF183L RSCAN0.TMDF183.UINT16[L]
#define RSCAN0TMDF183LL RSCAN0.TMDF183.UINT8[LL]
#define RSCAN0TMDF183LH RSCAN0.TMDF183.UINT8[LH]
#define RSCAN0TMDF183H RSCAN0.TMDF183.UINT16[H]
#define RSCAN0TMDF183HL RSCAN0.TMDF183.UINT8[HL]
#define RSCAN0TMDF183HH RSCAN0.TMDF183.UINT8[HH]
#define RSCAN0TMID84 RSCAN0.TMID84.UINT32
#define RSCAN0TMID84L RSCAN0.TMID84.UINT16[L]
#define RSCAN0TMID84LL RSCAN0.TMID84.UINT8[LL]
#define RSCAN0TMID84LH RSCAN0.TMID84.UINT8[LH]
#define RSCAN0TMID84H RSCAN0.TMID84.UINT16[H]
#define RSCAN0TMID84HL RSCAN0.TMID84.UINT8[HL]
#define RSCAN0TMID84HH RSCAN0.TMID84.UINT8[HH]
#define RSCAN0TMPTR84 RSCAN0.TMPTR84.UINT32
#define RSCAN0TMPTR84H RSCAN0.TMPTR84.UINT16[H]
#define RSCAN0TMPTR84HL RSCAN0.TMPTR84.UINT8[HL]
#define RSCAN0TMPTR84HH RSCAN0.TMPTR84.UINT8[HH]
#define RSCAN0TMDF084 RSCAN0.TMDF084.UINT32
#define RSCAN0TMDF084L RSCAN0.TMDF084.UINT16[L]
#define RSCAN0TMDF084LL RSCAN0.TMDF084.UINT8[LL]
#define RSCAN0TMDF084LH RSCAN0.TMDF084.UINT8[LH]
#define RSCAN0TMDF084H RSCAN0.TMDF084.UINT16[H]
#define RSCAN0TMDF084HL RSCAN0.TMDF084.UINT8[HL]
#define RSCAN0TMDF084HH RSCAN0.TMDF084.UINT8[HH]
#define RSCAN0TMDF184 RSCAN0.TMDF184.UINT32
#define RSCAN0TMDF184L RSCAN0.TMDF184.UINT16[L]
#define RSCAN0TMDF184LL RSCAN0.TMDF184.UINT8[LL]
#define RSCAN0TMDF184LH RSCAN0.TMDF184.UINT8[LH]
#define RSCAN0TMDF184H RSCAN0.TMDF184.UINT16[H]
#define RSCAN0TMDF184HL RSCAN0.TMDF184.UINT8[HL]
#define RSCAN0TMDF184HH RSCAN0.TMDF184.UINT8[HH]
#define RSCAN0TMID85 RSCAN0.TMID85.UINT32
#define RSCAN0TMID85L RSCAN0.TMID85.UINT16[L]
#define RSCAN0TMID85LL RSCAN0.TMID85.UINT8[LL]
#define RSCAN0TMID85LH RSCAN0.TMID85.UINT8[LH]
#define RSCAN0TMID85H RSCAN0.TMID85.UINT16[H]
#define RSCAN0TMID85HL RSCAN0.TMID85.UINT8[HL]
#define RSCAN0TMID85HH RSCAN0.TMID85.UINT8[HH]
#define RSCAN0TMPTR85 RSCAN0.TMPTR85.UINT32
#define RSCAN0TMPTR85H RSCAN0.TMPTR85.UINT16[H]
#define RSCAN0TMPTR85HL RSCAN0.TMPTR85.UINT8[HL]
#define RSCAN0TMPTR85HH RSCAN0.TMPTR85.UINT8[HH]
#define RSCAN0TMDF085 RSCAN0.TMDF085.UINT32
#define RSCAN0TMDF085L RSCAN0.TMDF085.UINT16[L]
#define RSCAN0TMDF085LL RSCAN0.TMDF085.UINT8[LL]
#define RSCAN0TMDF085LH RSCAN0.TMDF085.UINT8[LH]
#define RSCAN0TMDF085H RSCAN0.TMDF085.UINT16[H]
#define RSCAN0TMDF085HL RSCAN0.TMDF085.UINT8[HL]
#define RSCAN0TMDF085HH RSCAN0.TMDF085.UINT8[HH]
#define RSCAN0TMDF185 RSCAN0.TMDF185.UINT32
#define RSCAN0TMDF185L RSCAN0.TMDF185.UINT16[L]
#define RSCAN0TMDF185LL RSCAN0.TMDF185.UINT8[LL]
#define RSCAN0TMDF185LH RSCAN0.TMDF185.UINT8[LH]
#define RSCAN0TMDF185H RSCAN0.TMDF185.UINT16[H]
#define RSCAN0TMDF185HL RSCAN0.TMDF185.UINT8[HL]
#define RSCAN0TMDF185HH RSCAN0.TMDF185.UINT8[HH]
#define RSCAN0TMID86 RSCAN0.TMID86.UINT32
#define RSCAN0TMID86L RSCAN0.TMID86.UINT16[L]
#define RSCAN0TMID86LL RSCAN0.TMID86.UINT8[LL]
#define RSCAN0TMID86LH RSCAN0.TMID86.UINT8[LH]
#define RSCAN0TMID86H RSCAN0.TMID86.UINT16[H]
#define RSCAN0TMID86HL RSCAN0.TMID86.UINT8[HL]
#define RSCAN0TMID86HH RSCAN0.TMID86.UINT8[HH]
#define RSCAN0TMPTR86 RSCAN0.TMPTR86.UINT32
#define RSCAN0TMPTR86H RSCAN0.TMPTR86.UINT16[H]
#define RSCAN0TMPTR86HL RSCAN0.TMPTR86.UINT8[HL]
#define RSCAN0TMPTR86HH RSCAN0.TMPTR86.UINT8[HH]
#define RSCAN0TMDF086 RSCAN0.TMDF086.UINT32
#define RSCAN0TMDF086L RSCAN0.TMDF086.UINT16[L]
#define RSCAN0TMDF086LL RSCAN0.TMDF086.UINT8[LL]
#define RSCAN0TMDF086LH RSCAN0.TMDF086.UINT8[LH]
#define RSCAN0TMDF086H RSCAN0.TMDF086.UINT16[H]
#define RSCAN0TMDF086HL RSCAN0.TMDF086.UINT8[HL]
#define RSCAN0TMDF086HH RSCAN0.TMDF086.UINT8[HH]
#define RSCAN0TMDF186 RSCAN0.TMDF186.UINT32
#define RSCAN0TMDF186L RSCAN0.TMDF186.UINT16[L]
#define RSCAN0TMDF186LL RSCAN0.TMDF186.UINT8[LL]
#define RSCAN0TMDF186LH RSCAN0.TMDF186.UINT8[LH]
#define RSCAN0TMDF186H RSCAN0.TMDF186.UINT16[H]
#define RSCAN0TMDF186HL RSCAN0.TMDF186.UINT8[HL]
#define RSCAN0TMDF186HH RSCAN0.TMDF186.UINT8[HH]
#define RSCAN0TMID87 RSCAN0.TMID87.UINT32
#define RSCAN0TMID87L RSCAN0.TMID87.UINT16[L]
#define RSCAN0TMID87LL RSCAN0.TMID87.UINT8[LL]
#define RSCAN0TMID87LH RSCAN0.TMID87.UINT8[LH]
#define RSCAN0TMID87H RSCAN0.TMID87.UINT16[H]
#define RSCAN0TMID87HL RSCAN0.TMID87.UINT8[HL]
#define RSCAN0TMID87HH RSCAN0.TMID87.UINT8[HH]
#define RSCAN0TMPTR87 RSCAN0.TMPTR87.UINT32
#define RSCAN0TMPTR87H RSCAN0.TMPTR87.UINT16[H]
#define RSCAN0TMPTR87HL RSCAN0.TMPTR87.UINT8[HL]
#define RSCAN0TMPTR87HH RSCAN0.TMPTR87.UINT8[HH]
#define RSCAN0TMDF087 RSCAN0.TMDF087.UINT32
#define RSCAN0TMDF087L RSCAN0.TMDF087.UINT16[L]
#define RSCAN0TMDF087LL RSCAN0.TMDF087.UINT8[LL]
#define RSCAN0TMDF087LH RSCAN0.TMDF087.UINT8[LH]
#define RSCAN0TMDF087H RSCAN0.TMDF087.UINT16[H]
#define RSCAN0TMDF087HL RSCAN0.TMDF087.UINT8[HL]
#define RSCAN0TMDF087HH RSCAN0.TMDF087.UINT8[HH]
#define RSCAN0TMDF187 RSCAN0.TMDF187.UINT32
#define RSCAN0TMDF187L RSCAN0.TMDF187.UINT16[L]
#define RSCAN0TMDF187LL RSCAN0.TMDF187.UINT8[LL]
#define RSCAN0TMDF187LH RSCAN0.TMDF187.UINT8[LH]
#define RSCAN0TMDF187H RSCAN0.TMDF187.UINT16[H]
#define RSCAN0TMDF187HL RSCAN0.TMDF187.UINT8[HL]
#define RSCAN0TMDF187HH RSCAN0.TMDF187.UINT8[HH]
#define RSCAN0TMID88 RSCAN0.TMID88.UINT32
#define RSCAN0TMID88L RSCAN0.TMID88.UINT16[L]
#define RSCAN0TMID88LL RSCAN0.TMID88.UINT8[LL]
#define RSCAN0TMID88LH RSCAN0.TMID88.UINT8[LH]
#define RSCAN0TMID88H RSCAN0.TMID88.UINT16[H]
#define RSCAN0TMID88HL RSCAN0.TMID88.UINT8[HL]
#define RSCAN0TMID88HH RSCAN0.TMID88.UINT8[HH]
#define RSCAN0TMPTR88 RSCAN0.TMPTR88.UINT32
#define RSCAN0TMPTR88H RSCAN0.TMPTR88.UINT16[H]
#define RSCAN0TMPTR88HL RSCAN0.TMPTR88.UINT8[HL]
#define RSCAN0TMPTR88HH RSCAN0.TMPTR88.UINT8[HH]
#define RSCAN0TMDF088 RSCAN0.TMDF088.UINT32
#define RSCAN0TMDF088L RSCAN0.TMDF088.UINT16[L]
#define RSCAN0TMDF088LL RSCAN0.TMDF088.UINT8[LL]
#define RSCAN0TMDF088LH RSCAN0.TMDF088.UINT8[LH]
#define RSCAN0TMDF088H RSCAN0.TMDF088.UINT16[H]
#define RSCAN0TMDF088HL RSCAN0.TMDF088.UINT8[HL]
#define RSCAN0TMDF088HH RSCAN0.TMDF088.UINT8[HH]
#define RSCAN0TMDF188 RSCAN0.TMDF188.UINT32
#define RSCAN0TMDF188L RSCAN0.TMDF188.UINT16[L]
#define RSCAN0TMDF188LL RSCAN0.TMDF188.UINT8[LL]
#define RSCAN0TMDF188LH RSCAN0.TMDF188.UINT8[LH]
#define RSCAN0TMDF188H RSCAN0.TMDF188.UINT16[H]
#define RSCAN0TMDF188HL RSCAN0.TMDF188.UINT8[HL]
#define RSCAN0TMDF188HH RSCAN0.TMDF188.UINT8[HH]
#define RSCAN0TMID89 RSCAN0.TMID89.UINT32
#define RSCAN0TMID89L RSCAN0.TMID89.UINT16[L]
#define RSCAN0TMID89LL RSCAN0.TMID89.UINT8[LL]
#define RSCAN0TMID89LH RSCAN0.TMID89.UINT8[LH]
#define RSCAN0TMID89H RSCAN0.TMID89.UINT16[H]
#define RSCAN0TMID89HL RSCAN0.TMID89.UINT8[HL]
#define RSCAN0TMID89HH RSCAN0.TMID89.UINT8[HH]
#define RSCAN0TMPTR89 RSCAN0.TMPTR89.UINT32
#define RSCAN0TMPTR89H RSCAN0.TMPTR89.UINT16[H]
#define RSCAN0TMPTR89HL RSCAN0.TMPTR89.UINT8[HL]
#define RSCAN0TMPTR89HH RSCAN0.TMPTR89.UINT8[HH]
#define RSCAN0TMDF089 RSCAN0.TMDF089.UINT32
#define RSCAN0TMDF089L RSCAN0.TMDF089.UINT16[L]
#define RSCAN0TMDF089LL RSCAN0.TMDF089.UINT8[LL]
#define RSCAN0TMDF089LH RSCAN0.TMDF089.UINT8[LH]
#define RSCAN0TMDF089H RSCAN0.TMDF089.UINT16[H]
#define RSCAN0TMDF089HL RSCAN0.TMDF089.UINT8[HL]
#define RSCAN0TMDF089HH RSCAN0.TMDF089.UINT8[HH]
#define RSCAN0TMDF189 RSCAN0.TMDF189.UINT32
#define RSCAN0TMDF189L RSCAN0.TMDF189.UINT16[L]
#define RSCAN0TMDF189LL RSCAN0.TMDF189.UINT8[LL]
#define RSCAN0TMDF189LH RSCAN0.TMDF189.UINT8[LH]
#define RSCAN0TMDF189H RSCAN0.TMDF189.UINT16[H]
#define RSCAN0TMDF189HL RSCAN0.TMDF189.UINT8[HL]
#define RSCAN0TMDF189HH RSCAN0.TMDF189.UINT8[HH]
#define RSCAN0TMID90 RSCAN0.TMID90.UINT32
#define RSCAN0TMID90L RSCAN0.TMID90.UINT16[L]
#define RSCAN0TMID90LL RSCAN0.TMID90.UINT8[LL]
#define RSCAN0TMID90LH RSCAN0.TMID90.UINT8[LH]
#define RSCAN0TMID90H RSCAN0.TMID90.UINT16[H]
#define RSCAN0TMID90HL RSCAN0.TMID90.UINT8[HL]
#define RSCAN0TMID90HH RSCAN0.TMID90.UINT8[HH]
#define RSCAN0TMPTR90 RSCAN0.TMPTR90.UINT32
#define RSCAN0TMPTR90H RSCAN0.TMPTR90.UINT16[H]
#define RSCAN0TMPTR90HL RSCAN0.TMPTR90.UINT8[HL]
#define RSCAN0TMPTR90HH RSCAN0.TMPTR90.UINT8[HH]
#define RSCAN0TMDF090 RSCAN0.TMDF090.UINT32
#define RSCAN0TMDF090L RSCAN0.TMDF090.UINT16[L]
#define RSCAN0TMDF090LL RSCAN0.TMDF090.UINT8[LL]
#define RSCAN0TMDF090LH RSCAN0.TMDF090.UINT8[LH]
#define RSCAN0TMDF090H RSCAN0.TMDF090.UINT16[H]
#define RSCAN0TMDF090HL RSCAN0.TMDF090.UINT8[HL]
#define RSCAN0TMDF090HH RSCAN0.TMDF090.UINT8[HH]
#define RSCAN0TMDF190 RSCAN0.TMDF190.UINT32
#define RSCAN0TMDF190L RSCAN0.TMDF190.UINT16[L]
#define RSCAN0TMDF190LL RSCAN0.TMDF190.UINT8[LL]
#define RSCAN0TMDF190LH RSCAN0.TMDF190.UINT8[LH]
#define RSCAN0TMDF190H RSCAN0.TMDF190.UINT16[H]
#define RSCAN0TMDF190HL RSCAN0.TMDF190.UINT8[HL]
#define RSCAN0TMDF190HH RSCAN0.TMDF190.UINT8[HH]
#define RSCAN0TMID91 RSCAN0.TMID91.UINT32
#define RSCAN0TMID91L RSCAN0.TMID91.UINT16[L]
#define RSCAN0TMID91LL RSCAN0.TMID91.UINT8[LL]
#define RSCAN0TMID91LH RSCAN0.TMID91.UINT8[LH]
#define RSCAN0TMID91H RSCAN0.TMID91.UINT16[H]
#define RSCAN0TMID91HL RSCAN0.TMID91.UINT8[HL]
#define RSCAN0TMID91HH RSCAN0.TMID91.UINT8[HH]
#define RSCAN0TMPTR91 RSCAN0.TMPTR91.UINT32
#define RSCAN0TMPTR91H RSCAN0.TMPTR91.UINT16[H]
#define RSCAN0TMPTR91HL RSCAN0.TMPTR91.UINT8[HL]
#define RSCAN0TMPTR91HH RSCAN0.TMPTR91.UINT8[HH]
#define RSCAN0TMDF091 RSCAN0.TMDF091.UINT32
#define RSCAN0TMDF091L RSCAN0.TMDF091.UINT16[L]
#define RSCAN0TMDF091LL RSCAN0.TMDF091.UINT8[LL]
#define RSCAN0TMDF091LH RSCAN0.TMDF091.UINT8[LH]
#define RSCAN0TMDF091H RSCAN0.TMDF091.UINT16[H]
#define RSCAN0TMDF091HL RSCAN0.TMDF091.UINT8[HL]
#define RSCAN0TMDF091HH RSCAN0.TMDF091.UINT8[HH]
#define RSCAN0TMDF191 RSCAN0.TMDF191.UINT32
#define RSCAN0TMDF191L RSCAN0.TMDF191.UINT16[L]
#define RSCAN0TMDF191LL RSCAN0.TMDF191.UINT8[LL]
#define RSCAN0TMDF191LH RSCAN0.TMDF191.UINT8[LH]
#define RSCAN0TMDF191H RSCAN0.TMDF191.UINT16[H]
#define RSCAN0TMDF191HL RSCAN0.TMDF191.UINT8[HL]
#define RSCAN0TMDF191HH RSCAN0.TMDF191.UINT8[HH]
#define RSCAN0TMID92 RSCAN0.TMID92.UINT32
#define RSCAN0TMID92L RSCAN0.TMID92.UINT16[L]
#define RSCAN0TMID92LL RSCAN0.TMID92.UINT8[LL]
#define RSCAN0TMID92LH RSCAN0.TMID92.UINT8[LH]
#define RSCAN0TMID92H RSCAN0.TMID92.UINT16[H]
#define RSCAN0TMID92HL RSCAN0.TMID92.UINT8[HL]
#define RSCAN0TMID92HH RSCAN0.TMID92.UINT8[HH]
#define RSCAN0TMPTR92 RSCAN0.TMPTR92.UINT32
#define RSCAN0TMPTR92H RSCAN0.TMPTR92.UINT16[H]
#define RSCAN0TMPTR92HL RSCAN0.TMPTR92.UINT8[HL]
#define RSCAN0TMPTR92HH RSCAN0.TMPTR92.UINT8[HH]
#define RSCAN0TMDF092 RSCAN0.TMDF092.UINT32
#define RSCAN0TMDF092L RSCAN0.TMDF092.UINT16[L]
#define RSCAN0TMDF092LL RSCAN0.TMDF092.UINT8[LL]
#define RSCAN0TMDF092LH RSCAN0.TMDF092.UINT8[LH]
#define RSCAN0TMDF092H RSCAN0.TMDF092.UINT16[H]
#define RSCAN0TMDF092HL RSCAN0.TMDF092.UINT8[HL]
#define RSCAN0TMDF092HH RSCAN0.TMDF092.UINT8[HH]
#define RSCAN0TMDF192 RSCAN0.TMDF192.UINT32
#define RSCAN0TMDF192L RSCAN0.TMDF192.UINT16[L]
#define RSCAN0TMDF192LL RSCAN0.TMDF192.UINT8[LL]
#define RSCAN0TMDF192LH RSCAN0.TMDF192.UINT8[LH]
#define RSCAN0TMDF192H RSCAN0.TMDF192.UINT16[H]
#define RSCAN0TMDF192HL RSCAN0.TMDF192.UINT8[HL]
#define RSCAN0TMDF192HH RSCAN0.TMDF192.UINT8[HH]
#define RSCAN0TMID93 RSCAN0.TMID93.UINT32
#define RSCAN0TMID93L RSCAN0.TMID93.UINT16[L]
#define RSCAN0TMID93LL RSCAN0.TMID93.UINT8[LL]
#define RSCAN0TMID93LH RSCAN0.TMID93.UINT8[LH]
#define RSCAN0TMID93H RSCAN0.TMID93.UINT16[H]
#define RSCAN0TMID93HL RSCAN0.TMID93.UINT8[HL]
#define RSCAN0TMID93HH RSCAN0.TMID93.UINT8[HH]
#define RSCAN0TMPTR93 RSCAN0.TMPTR93.UINT32
#define RSCAN0TMPTR93H RSCAN0.TMPTR93.UINT16[H]
#define RSCAN0TMPTR93HL RSCAN0.TMPTR93.UINT8[HL]
#define RSCAN0TMPTR93HH RSCAN0.TMPTR93.UINT8[HH]
#define RSCAN0TMDF093 RSCAN0.TMDF093.UINT32
#define RSCAN0TMDF093L RSCAN0.TMDF093.UINT16[L]
#define RSCAN0TMDF093LL RSCAN0.TMDF093.UINT8[LL]
#define RSCAN0TMDF093LH RSCAN0.TMDF093.UINT8[LH]
#define RSCAN0TMDF093H RSCAN0.TMDF093.UINT16[H]
#define RSCAN0TMDF093HL RSCAN0.TMDF093.UINT8[HL]
#define RSCAN0TMDF093HH RSCAN0.TMDF093.UINT8[HH]
#define RSCAN0TMDF193 RSCAN0.TMDF193.UINT32
#define RSCAN0TMDF193L RSCAN0.TMDF193.UINT16[L]
#define RSCAN0TMDF193LL RSCAN0.TMDF193.UINT8[LL]
#define RSCAN0TMDF193LH RSCAN0.TMDF193.UINT8[LH]
#define RSCAN0TMDF193H RSCAN0.TMDF193.UINT16[H]
#define RSCAN0TMDF193HL RSCAN0.TMDF193.UINT8[HL]
#define RSCAN0TMDF193HH RSCAN0.TMDF193.UINT8[HH]
#define RSCAN0TMID94 RSCAN0.TMID94.UINT32
#define RSCAN0TMID94L RSCAN0.TMID94.UINT16[L]
#define RSCAN0TMID94LL RSCAN0.TMID94.UINT8[LL]
#define RSCAN0TMID94LH RSCAN0.TMID94.UINT8[LH]
#define RSCAN0TMID94H RSCAN0.TMID94.UINT16[H]
#define RSCAN0TMID94HL RSCAN0.TMID94.UINT8[HL]
#define RSCAN0TMID94HH RSCAN0.TMID94.UINT8[HH]
#define RSCAN0TMPTR94 RSCAN0.TMPTR94.UINT32
#define RSCAN0TMPTR94H RSCAN0.TMPTR94.UINT16[H]
#define RSCAN0TMPTR94HL RSCAN0.TMPTR94.UINT8[HL]
#define RSCAN0TMPTR94HH RSCAN0.TMPTR94.UINT8[HH]
#define RSCAN0TMDF094 RSCAN0.TMDF094.UINT32
#define RSCAN0TMDF094L RSCAN0.TMDF094.UINT16[L]
#define RSCAN0TMDF094LL RSCAN0.TMDF094.UINT8[LL]
#define RSCAN0TMDF094LH RSCAN0.TMDF094.UINT8[LH]
#define RSCAN0TMDF094H RSCAN0.TMDF094.UINT16[H]
#define RSCAN0TMDF094HL RSCAN0.TMDF094.UINT8[HL]
#define RSCAN0TMDF094HH RSCAN0.TMDF094.UINT8[HH]
#define RSCAN0TMDF194 RSCAN0.TMDF194.UINT32
#define RSCAN0TMDF194L RSCAN0.TMDF194.UINT16[L]
#define RSCAN0TMDF194LL RSCAN0.TMDF194.UINT8[LL]
#define RSCAN0TMDF194LH RSCAN0.TMDF194.UINT8[LH]
#define RSCAN0TMDF194H RSCAN0.TMDF194.UINT16[H]
#define RSCAN0TMDF194HL RSCAN0.TMDF194.UINT8[HL]
#define RSCAN0TMDF194HH RSCAN0.TMDF194.UINT8[HH]
#define RSCAN0TMID95 RSCAN0.TMID95.UINT32
#define RSCAN0TMID95L RSCAN0.TMID95.UINT16[L]
#define RSCAN0TMID95LL RSCAN0.TMID95.UINT8[LL]
#define RSCAN0TMID95LH RSCAN0.TMID95.UINT8[LH]
#define RSCAN0TMID95H RSCAN0.TMID95.UINT16[H]
#define RSCAN0TMID95HL RSCAN0.TMID95.UINT8[HL]
#define RSCAN0TMID95HH RSCAN0.TMID95.UINT8[HH]
#define RSCAN0TMPTR95 RSCAN0.TMPTR95.UINT32
#define RSCAN0TMPTR95H RSCAN0.TMPTR95.UINT16[H]
#define RSCAN0TMPTR95HL RSCAN0.TMPTR95.UINT8[HL]
#define RSCAN0TMPTR95HH RSCAN0.TMPTR95.UINT8[HH]
#define RSCAN0TMDF095 RSCAN0.TMDF095.UINT32
#define RSCAN0TMDF095L RSCAN0.TMDF095.UINT16[L]
#define RSCAN0TMDF095LL RSCAN0.TMDF095.UINT8[LL]
#define RSCAN0TMDF095LH RSCAN0.TMDF095.UINT8[LH]
#define RSCAN0TMDF095H RSCAN0.TMDF095.UINT16[H]
#define RSCAN0TMDF095HL RSCAN0.TMDF095.UINT8[HL]
#define RSCAN0TMDF095HH RSCAN0.TMDF095.UINT8[HH]
#define RSCAN0TMDF195 RSCAN0.TMDF195.UINT32
#define RSCAN0TMDF195L RSCAN0.TMDF195.UINT16[L]
#define RSCAN0TMDF195LL RSCAN0.TMDF195.UINT8[LL]
#define RSCAN0TMDF195LH RSCAN0.TMDF195.UINT8[LH]
#define RSCAN0TMDF195H RSCAN0.TMDF195.UINT16[H]
#define RSCAN0TMDF195HL RSCAN0.TMDF195.UINT8[HL]
#define RSCAN0TMDF195HH RSCAN0.TMDF195.UINT8[HH]
#define RSCAN0THLACC0 RSCAN0.THLACC0.UINT32
#define RSCAN0THLACC0L RSCAN0.THLACC0.UINT16[L]
#define RSCAN0THLACC0LL RSCAN0.THLACC0.UINT8[LL]
#define RSCAN0THLACC0LH RSCAN0.THLACC0.UINT8[LH]
#define RSCAN0THLACC1 RSCAN0.THLACC1.UINT32
#define RSCAN0THLACC1L RSCAN0.THLACC1.UINT16[L]
#define RSCAN0THLACC1LL RSCAN0.THLACC1.UINT8[LL]
#define RSCAN0THLACC1LH RSCAN0.THLACC1.UINT8[LH]
#define RSCAN0THLACC2 RSCAN0.THLACC2.UINT32
#define RSCAN0THLACC2L RSCAN0.THLACC2.UINT16[L]
#define RSCAN0THLACC2LL RSCAN0.THLACC2.UINT8[LL]
#define RSCAN0THLACC2LH RSCAN0.THLACC2.UINT8[LH]
#define RSCAN0THLACC3 RSCAN0.THLACC3.UINT32
#define RSCAN0THLACC3L RSCAN0.THLACC3.UINT16[L]
#define RSCAN0THLACC3LL RSCAN0.THLACC3.UINT8[LL]
#define RSCAN0THLACC3LH RSCAN0.THLACC3.UINT8[LH]
#define RSCAN0THLACC4 RSCAN0.THLACC4.UINT32
#define RSCAN0THLACC4L RSCAN0.THLACC4.UINT16[L]
#define RSCAN0THLACC4LL RSCAN0.THLACC4.UINT8[LL]
#define RSCAN0THLACC4LH RSCAN0.THLACC4.UINT8[LH]
#define RSCAN0THLACC5 RSCAN0.THLACC5.UINT32
#define RSCAN0THLACC5L RSCAN0.THLACC5.UINT16[L]
#define RSCAN0THLACC5LL RSCAN0.THLACC5.UINT8[LL]
#define RSCAN0THLACC5LH RSCAN0.THLACC5.UINT8[LH]
#define RSCAN0RPGACC0 RSCAN0.RPGACC0.UINT32
#define RSCAN0RPGACC0L RSCAN0.RPGACC0.UINT16[L]
#define RSCAN0RPGACC0LL RSCAN0.RPGACC0.UINT8[LL]
#define RSCAN0RPGACC0LH RSCAN0.RPGACC0.UINT8[LH]
#define RSCAN0RPGACC0H RSCAN0.RPGACC0.UINT16[H]
#define RSCAN0RPGACC0HL RSCAN0.RPGACC0.UINT8[HL]
#define RSCAN0RPGACC0HH RSCAN0.RPGACC0.UINT8[HH]
#define RSCAN0RPGACC1 RSCAN0.RPGACC1.UINT32
#define RSCAN0RPGACC1L RSCAN0.RPGACC1.UINT16[L]
#define RSCAN0RPGACC1LL RSCAN0.RPGACC1.UINT8[LL]
#define RSCAN0RPGACC1LH RSCAN0.RPGACC1.UINT8[LH]
#define RSCAN0RPGACC1H RSCAN0.RPGACC1.UINT16[H]
#define RSCAN0RPGACC1HL RSCAN0.RPGACC1.UINT8[HL]
#define RSCAN0RPGACC1HH RSCAN0.RPGACC1.UINT8[HH]
#define RSCAN0RPGACC2 RSCAN0.RPGACC2.UINT32
#define RSCAN0RPGACC2L RSCAN0.RPGACC2.UINT16[L]
#define RSCAN0RPGACC2LL RSCAN0.RPGACC2.UINT8[LL]
#define RSCAN0RPGACC2LH RSCAN0.RPGACC2.UINT8[LH]
#define RSCAN0RPGACC2H RSCAN0.RPGACC2.UINT16[H]
#define RSCAN0RPGACC2HL RSCAN0.RPGACC2.UINT8[HL]
#define RSCAN0RPGACC2HH RSCAN0.RPGACC2.UINT8[HH]
#define RSCAN0RPGACC3 RSCAN0.RPGACC3.UINT32
#define RSCAN0RPGACC3L RSCAN0.RPGACC3.UINT16[L]
#define RSCAN0RPGACC3LL RSCAN0.RPGACC3.UINT8[LL]
#define RSCAN0RPGACC3LH RSCAN0.RPGACC3.UINT8[LH]
#define RSCAN0RPGACC3H RSCAN0.RPGACC3.UINT16[H]
#define RSCAN0RPGACC3HL RSCAN0.RPGACC3.UINT8[HL]
#define RSCAN0RPGACC3HH RSCAN0.RPGACC3.UINT8[HH]
#define RSCAN0RPGACC4 RSCAN0.RPGACC4.UINT32
#define RSCAN0RPGACC4L RSCAN0.RPGACC4.UINT16[L]
#define RSCAN0RPGACC4LL RSCAN0.RPGACC4.UINT8[LL]
#define RSCAN0RPGACC4LH RSCAN0.RPGACC4.UINT8[LH]
#define RSCAN0RPGACC4H RSCAN0.RPGACC4.UINT16[H]
#define RSCAN0RPGACC4HL RSCAN0.RPGACC4.UINT8[HL]
#define RSCAN0RPGACC4HH RSCAN0.RPGACC4.UINT8[HH]
#define RSCAN0RPGACC5 RSCAN0.RPGACC5.UINT32
#define RSCAN0RPGACC5L RSCAN0.RPGACC5.UINT16[L]
#define RSCAN0RPGACC5LL RSCAN0.RPGACC5.UINT8[LL]
#define RSCAN0RPGACC5LH RSCAN0.RPGACC5.UINT8[LH]
#define RSCAN0RPGACC5H RSCAN0.RPGACC5.UINT16[H]
#define RSCAN0RPGACC5HL RSCAN0.RPGACC5.UINT8[HL]
#define RSCAN0RPGACC5HH RSCAN0.RPGACC5.UINT8[HH]
#define RSCAN0RPGACC6 RSCAN0.RPGACC6.UINT32
#define RSCAN0RPGACC6L RSCAN0.RPGACC6.UINT16[L]
#define RSCAN0RPGACC6LL RSCAN0.RPGACC6.UINT8[LL]
#define RSCAN0RPGACC6LH RSCAN0.RPGACC6.UINT8[LH]
#define RSCAN0RPGACC6H RSCAN0.RPGACC6.UINT16[H]
#define RSCAN0RPGACC6HL RSCAN0.RPGACC6.UINT8[HL]
#define RSCAN0RPGACC6HH RSCAN0.RPGACC6.UINT8[HH]
#define RSCAN0RPGACC7 RSCAN0.RPGACC7.UINT32
#define RSCAN0RPGACC7L RSCAN0.RPGACC7.UINT16[L]
#define RSCAN0RPGACC7LL RSCAN0.RPGACC7.UINT8[LL]
#define RSCAN0RPGACC7LH RSCAN0.RPGACC7.UINT8[LH]
#define RSCAN0RPGACC7H RSCAN0.RPGACC7.UINT16[H]
#define RSCAN0RPGACC7HL RSCAN0.RPGACC7.UINT8[HL]
#define RSCAN0RPGACC7HH RSCAN0.RPGACC7.UINT8[HH]
#define RSCAN0RPGACC8 RSCAN0.RPGACC8.UINT32
#define RSCAN0RPGACC8L RSCAN0.RPGACC8.UINT16[L]
#define RSCAN0RPGACC8LL RSCAN0.RPGACC8.UINT8[LL]
#define RSCAN0RPGACC8LH RSCAN0.RPGACC8.UINT8[LH]
#define RSCAN0RPGACC8H RSCAN0.RPGACC8.UINT16[H]
#define RSCAN0RPGACC8HL RSCAN0.RPGACC8.UINT8[HL]
#define RSCAN0RPGACC8HH RSCAN0.RPGACC8.UINT8[HH]
#define RSCAN0RPGACC9 RSCAN0.RPGACC9.UINT32
#define RSCAN0RPGACC9L RSCAN0.RPGACC9.UINT16[L]
#define RSCAN0RPGACC9LL RSCAN0.RPGACC9.UINT8[LL]
#define RSCAN0RPGACC9LH RSCAN0.RPGACC9.UINT8[LH]
#define RSCAN0RPGACC9H RSCAN0.RPGACC9.UINT16[H]
#define RSCAN0RPGACC9HL RSCAN0.RPGACC9.UINT8[HL]
#define RSCAN0RPGACC9HH RSCAN0.RPGACC9.UINT8[HH]
#define RSCAN0RPGACC10 RSCAN0.RPGACC10.UINT32
#define RSCAN0RPGACC10L RSCAN0.RPGACC10.UINT16[L]
#define RSCAN0RPGACC10LL RSCAN0.RPGACC10.UINT8[LL]
#define RSCAN0RPGACC10LH RSCAN0.RPGACC10.UINT8[LH]
#define RSCAN0RPGACC10H RSCAN0.RPGACC10.UINT16[H]
#define RSCAN0RPGACC10HL RSCAN0.RPGACC10.UINT8[HL]
#define RSCAN0RPGACC10HH RSCAN0.RPGACC10.UINT8[HH]
#define RSCAN0RPGACC11 RSCAN0.RPGACC11.UINT32
#define RSCAN0RPGACC11L RSCAN0.RPGACC11.UINT16[L]
#define RSCAN0RPGACC11LL RSCAN0.RPGACC11.UINT8[LL]
#define RSCAN0RPGACC11LH RSCAN0.RPGACC11.UINT8[LH]
#define RSCAN0RPGACC11H RSCAN0.RPGACC11.UINT16[H]
#define RSCAN0RPGACC11HL RSCAN0.RPGACC11.UINT8[HL]
#define RSCAN0RPGACC11HH RSCAN0.RPGACC11.UINT8[HH]
#define RSCAN0RPGACC12 RSCAN0.RPGACC12.UINT32
#define RSCAN0RPGACC12L RSCAN0.RPGACC12.UINT16[L]
#define RSCAN0RPGACC12LL RSCAN0.RPGACC12.UINT8[LL]
#define RSCAN0RPGACC12LH RSCAN0.RPGACC12.UINT8[LH]
#define RSCAN0RPGACC12H RSCAN0.RPGACC12.UINT16[H]
#define RSCAN0RPGACC12HL RSCAN0.RPGACC12.UINT8[HL]
#define RSCAN0RPGACC12HH RSCAN0.RPGACC12.UINT8[HH]
#define RSCAN0RPGACC13 RSCAN0.RPGACC13.UINT32
#define RSCAN0RPGACC13L RSCAN0.RPGACC13.UINT16[L]
#define RSCAN0RPGACC13LL RSCAN0.RPGACC13.UINT8[LL]
#define RSCAN0RPGACC13LH RSCAN0.RPGACC13.UINT8[LH]
#define RSCAN0RPGACC13H RSCAN0.RPGACC13.UINT16[H]
#define RSCAN0RPGACC13HL RSCAN0.RPGACC13.UINT8[HL]
#define RSCAN0RPGACC13HH RSCAN0.RPGACC13.UINT8[HH]
#define RSCAN0RPGACC14 RSCAN0.RPGACC14.UINT32
#define RSCAN0RPGACC14L RSCAN0.RPGACC14.UINT16[L]
#define RSCAN0RPGACC14LL RSCAN0.RPGACC14.UINT8[LL]
#define RSCAN0RPGACC14LH RSCAN0.RPGACC14.UINT8[LH]
#define RSCAN0RPGACC14H RSCAN0.RPGACC14.UINT16[H]
#define RSCAN0RPGACC14HL RSCAN0.RPGACC14.UINT8[HL]
#define RSCAN0RPGACC14HH RSCAN0.RPGACC14.UINT8[HH]
#define RSCAN0RPGACC15 RSCAN0.RPGACC15.UINT32
#define RSCAN0RPGACC15L RSCAN0.RPGACC15.UINT16[L]
#define RSCAN0RPGACC15LL RSCAN0.RPGACC15.UINT8[LL]
#define RSCAN0RPGACC15LH RSCAN0.RPGACC15.UINT8[LH]
#define RSCAN0RPGACC15H RSCAN0.RPGACC15.UINT16[H]
#define RSCAN0RPGACC15HL RSCAN0.RPGACC15.UINT8[HL]
#define RSCAN0RPGACC15HH RSCAN0.RPGACC15.UINT8[HH]
#define RSCAN0RPGACC16 RSCAN0.RPGACC16.UINT32
#define RSCAN0RPGACC16L RSCAN0.RPGACC16.UINT16[L]
#define RSCAN0RPGACC16LL RSCAN0.RPGACC16.UINT8[LL]
#define RSCAN0RPGACC16LH RSCAN0.RPGACC16.UINT8[LH]
#define RSCAN0RPGACC16H RSCAN0.RPGACC16.UINT16[H]
#define RSCAN0RPGACC16HL RSCAN0.RPGACC16.UINT8[HL]
#define RSCAN0RPGACC16HH RSCAN0.RPGACC16.UINT8[HH]
#define RSCAN0RPGACC17 RSCAN0.RPGACC17.UINT32
#define RSCAN0RPGACC17L RSCAN0.RPGACC17.UINT16[L]
#define RSCAN0RPGACC17LL RSCAN0.RPGACC17.UINT8[LL]
#define RSCAN0RPGACC17LH RSCAN0.RPGACC17.UINT8[LH]
#define RSCAN0RPGACC17H RSCAN0.RPGACC17.UINT16[H]
#define RSCAN0RPGACC17HL RSCAN0.RPGACC17.UINT8[HL]
#define RSCAN0RPGACC17HH RSCAN0.RPGACC17.UINT8[HH]
#define RSCAN0RPGACC18 RSCAN0.RPGACC18.UINT32
#define RSCAN0RPGACC18L RSCAN0.RPGACC18.UINT16[L]
#define RSCAN0RPGACC18LL RSCAN0.RPGACC18.UINT8[LL]
#define RSCAN0RPGACC18LH RSCAN0.RPGACC18.UINT8[LH]
#define RSCAN0RPGACC18H RSCAN0.RPGACC18.UINT16[H]
#define RSCAN0RPGACC18HL RSCAN0.RPGACC18.UINT8[HL]
#define RSCAN0RPGACC18HH RSCAN0.RPGACC18.UINT8[HH]
#define RSCAN0RPGACC19 RSCAN0.RPGACC19.UINT32
#define RSCAN0RPGACC19L RSCAN0.RPGACC19.UINT16[L]
#define RSCAN0RPGACC19LL RSCAN0.RPGACC19.UINT8[LL]
#define RSCAN0RPGACC19LH RSCAN0.RPGACC19.UINT8[LH]
#define RSCAN0RPGACC19H RSCAN0.RPGACC19.UINT16[H]
#define RSCAN0RPGACC19HL RSCAN0.RPGACC19.UINT8[HL]
#define RSCAN0RPGACC19HH RSCAN0.RPGACC19.UINT8[HH]
#define RSCAN0RPGACC20 RSCAN0.RPGACC20.UINT32
#define RSCAN0RPGACC20L RSCAN0.RPGACC20.UINT16[L]
#define RSCAN0RPGACC20LL RSCAN0.RPGACC20.UINT8[LL]
#define RSCAN0RPGACC20LH RSCAN0.RPGACC20.UINT8[LH]
#define RSCAN0RPGACC20H RSCAN0.RPGACC20.UINT16[H]
#define RSCAN0RPGACC20HL RSCAN0.RPGACC20.UINT8[HL]
#define RSCAN0RPGACC20HH RSCAN0.RPGACC20.UINT8[HH]
#define RSCAN0RPGACC21 RSCAN0.RPGACC21.UINT32
#define RSCAN0RPGACC21L RSCAN0.RPGACC21.UINT16[L]
#define RSCAN0RPGACC21LL RSCAN0.RPGACC21.UINT8[LL]
#define RSCAN0RPGACC21LH RSCAN0.RPGACC21.UINT8[LH]
#define RSCAN0RPGACC21H RSCAN0.RPGACC21.UINT16[H]
#define RSCAN0RPGACC21HL RSCAN0.RPGACC21.UINT8[HL]
#define RSCAN0RPGACC21HH RSCAN0.RPGACC21.UINT8[HH]
#define RSCAN0RPGACC22 RSCAN0.RPGACC22.UINT32
#define RSCAN0RPGACC22L RSCAN0.RPGACC22.UINT16[L]
#define RSCAN0RPGACC22LL RSCAN0.RPGACC22.UINT8[LL]
#define RSCAN0RPGACC22LH RSCAN0.RPGACC22.UINT8[LH]
#define RSCAN0RPGACC22H RSCAN0.RPGACC22.UINT16[H]
#define RSCAN0RPGACC22HL RSCAN0.RPGACC22.UINT8[HL]
#define RSCAN0RPGACC22HH RSCAN0.RPGACC22.UINT8[HH]
#define RSCAN0RPGACC23 RSCAN0.RPGACC23.UINT32
#define RSCAN0RPGACC23L RSCAN0.RPGACC23.UINT16[L]
#define RSCAN0RPGACC23LL RSCAN0.RPGACC23.UINT8[LL]
#define RSCAN0RPGACC23LH RSCAN0.RPGACC23.UINT8[LH]
#define RSCAN0RPGACC23H RSCAN0.RPGACC23.UINT16[H]
#define RSCAN0RPGACC23HL RSCAN0.RPGACC23.UINT8[HL]
#define RSCAN0RPGACC23HH RSCAN0.RPGACC23.UINT8[HH]
#define RSCAN0RPGACC24 RSCAN0.RPGACC24.UINT32
#define RSCAN0RPGACC24L RSCAN0.RPGACC24.UINT16[L]
#define RSCAN0RPGACC24LL RSCAN0.RPGACC24.UINT8[LL]
#define RSCAN0RPGACC24LH RSCAN0.RPGACC24.UINT8[LH]
#define RSCAN0RPGACC24H RSCAN0.RPGACC24.UINT16[H]
#define RSCAN0RPGACC24HL RSCAN0.RPGACC24.UINT8[HL]
#define RSCAN0RPGACC24HH RSCAN0.RPGACC24.UINT8[HH]
#define RSCAN0RPGACC25 RSCAN0.RPGACC25.UINT32
#define RSCAN0RPGACC25L RSCAN0.RPGACC25.UINT16[L]
#define RSCAN0RPGACC25LL RSCAN0.RPGACC25.UINT8[LL]
#define RSCAN0RPGACC25LH RSCAN0.RPGACC25.UINT8[LH]
#define RSCAN0RPGACC25H RSCAN0.RPGACC25.UINT16[H]
#define RSCAN0RPGACC25HL RSCAN0.RPGACC25.UINT8[HL]
#define RSCAN0RPGACC25HH RSCAN0.RPGACC25.UINT8[HH]
#define RSCAN0RPGACC26 RSCAN0.RPGACC26.UINT32
#define RSCAN0RPGACC26L RSCAN0.RPGACC26.UINT16[L]
#define RSCAN0RPGACC26LL RSCAN0.RPGACC26.UINT8[LL]
#define RSCAN0RPGACC26LH RSCAN0.RPGACC26.UINT8[LH]
#define RSCAN0RPGACC26H RSCAN0.RPGACC26.UINT16[H]
#define RSCAN0RPGACC26HL RSCAN0.RPGACC26.UINT8[HL]
#define RSCAN0RPGACC26HH RSCAN0.RPGACC26.UINT8[HH]
#define RSCAN0RPGACC27 RSCAN0.RPGACC27.UINT32
#define RSCAN0RPGACC27L RSCAN0.RPGACC27.UINT16[L]
#define RSCAN0RPGACC27LL RSCAN0.RPGACC27.UINT8[LL]
#define RSCAN0RPGACC27LH RSCAN0.RPGACC27.UINT8[LH]
#define RSCAN0RPGACC27H RSCAN0.RPGACC27.UINT16[H]
#define RSCAN0RPGACC27HL RSCAN0.RPGACC27.UINT8[HL]
#define RSCAN0RPGACC27HH RSCAN0.RPGACC27.UINT8[HH]
#define RSCAN0RPGACC28 RSCAN0.RPGACC28.UINT32
#define RSCAN0RPGACC28L RSCAN0.RPGACC28.UINT16[L]
#define RSCAN0RPGACC28LL RSCAN0.RPGACC28.UINT8[LL]
#define RSCAN0RPGACC28LH RSCAN0.RPGACC28.UINT8[LH]
#define RSCAN0RPGACC28H RSCAN0.RPGACC28.UINT16[H]
#define RSCAN0RPGACC28HL RSCAN0.RPGACC28.UINT8[HL]
#define RSCAN0RPGACC28HH RSCAN0.RPGACC28.UINT8[HH]
#define RSCAN0RPGACC29 RSCAN0.RPGACC29.UINT32
#define RSCAN0RPGACC29L RSCAN0.RPGACC29.UINT16[L]
#define RSCAN0RPGACC29LL RSCAN0.RPGACC29.UINT8[LL]
#define RSCAN0RPGACC29LH RSCAN0.RPGACC29.UINT8[LH]
#define RSCAN0RPGACC29H RSCAN0.RPGACC29.UINT16[H]
#define RSCAN0RPGACC29HL RSCAN0.RPGACC29.UINT8[HL]
#define RSCAN0RPGACC29HH RSCAN0.RPGACC29.UINT8[HH]
#define RSCAN0RPGACC30 RSCAN0.RPGACC30.UINT32
#define RSCAN0RPGACC30L RSCAN0.RPGACC30.UINT16[L]
#define RSCAN0RPGACC30LL RSCAN0.RPGACC30.UINT8[LL]
#define RSCAN0RPGACC30LH RSCAN0.RPGACC30.UINT8[LH]
#define RSCAN0RPGACC30H RSCAN0.RPGACC30.UINT16[H]
#define RSCAN0RPGACC30HL RSCAN0.RPGACC30.UINT8[HL]
#define RSCAN0RPGACC30HH RSCAN0.RPGACC30.UINT8[HH]
#define RSCAN0RPGACC31 RSCAN0.RPGACC31.UINT32
#define RSCAN0RPGACC31L RSCAN0.RPGACC31.UINT16[L]
#define RSCAN0RPGACC31LL RSCAN0.RPGACC31.UINT8[LL]
#define RSCAN0RPGACC31LH RSCAN0.RPGACC31.UINT8[LH]
#define RSCAN0RPGACC31H RSCAN0.RPGACC31.UINT16[H]
#define RSCAN0RPGACC31HL RSCAN0.RPGACC31.UINT8[HL]
#define RSCAN0RPGACC31HH RSCAN0.RPGACC31.UINT8[HH]
#define RSCAN0RPGACC32 RSCAN0.RPGACC32.UINT32
#define RSCAN0RPGACC32L RSCAN0.RPGACC32.UINT16[L]
#define RSCAN0RPGACC32LL RSCAN0.RPGACC32.UINT8[LL]
#define RSCAN0RPGACC32LH RSCAN0.RPGACC32.UINT8[LH]
#define RSCAN0RPGACC32H RSCAN0.RPGACC32.UINT16[H]
#define RSCAN0RPGACC32HL RSCAN0.RPGACC32.UINT8[HL]
#define RSCAN0RPGACC32HH RSCAN0.RPGACC32.UINT8[HH]
#define RSCAN0RPGACC33 RSCAN0.RPGACC33.UINT32
#define RSCAN0RPGACC33L RSCAN0.RPGACC33.UINT16[L]
#define RSCAN0RPGACC33LL RSCAN0.RPGACC33.UINT8[LL]
#define RSCAN0RPGACC33LH RSCAN0.RPGACC33.UINT8[LH]
#define RSCAN0RPGACC33H RSCAN0.RPGACC33.UINT16[H]
#define RSCAN0RPGACC33HL RSCAN0.RPGACC33.UINT8[HL]
#define RSCAN0RPGACC33HH RSCAN0.RPGACC33.UINT8[HH]
#define RSCAN0RPGACC34 RSCAN0.RPGACC34.UINT32
#define RSCAN0RPGACC34L RSCAN0.RPGACC34.UINT16[L]
#define RSCAN0RPGACC34LL RSCAN0.RPGACC34.UINT8[LL]
#define RSCAN0RPGACC34LH RSCAN0.RPGACC34.UINT8[LH]
#define RSCAN0RPGACC34H RSCAN0.RPGACC34.UINT16[H]
#define RSCAN0RPGACC34HL RSCAN0.RPGACC34.UINT8[HL]
#define RSCAN0RPGACC34HH RSCAN0.RPGACC34.UINT8[HH]
#define RSCAN0RPGACC35 RSCAN0.RPGACC35.UINT32
#define RSCAN0RPGACC35L RSCAN0.RPGACC35.UINT16[L]
#define RSCAN0RPGACC35LL RSCAN0.RPGACC35.UINT8[LL]
#define RSCAN0RPGACC35LH RSCAN0.RPGACC35.UINT8[LH]
#define RSCAN0RPGACC35H RSCAN0.RPGACC35.UINT16[H]
#define RSCAN0RPGACC35HL RSCAN0.RPGACC35.UINT8[HL]
#define RSCAN0RPGACC35HH RSCAN0.RPGACC35.UINT8[HH]
#define RSCAN0RPGACC36 RSCAN0.RPGACC36.UINT32
#define RSCAN0RPGACC36L RSCAN0.RPGACC36.UINT16[L]
#define RSCAN0RPGACC36LL RSCAN0.RPGACC36.UINT8[LL]
#define RSCAN0RPGACC36LH RSCAN0.RPGACC36.UINT8[LH]
#define RSCAN0RPGACC36H RSCAN0.RPGACC36.UINT16[H]
#define RSCAN0RPGACC36HL RSCAN0.RPGACC36.UINT8[HL]
#define RSCAN0RPGACC36HH RSCAN0.RPGACC36.UINT8[HH]
#define RSCAN0RPGACC37 RSCAN0.RPGACC37.UINT32
#define RSCAN0RPGACC37L RSCAN0.RPGACC37.UINT16[L]
#define RSCAN0RPGACC37LL RSCAN0.RPGACC37.UINT8[LL]
#define RSCAN0RPGACC37LH RSCAN0.RPGACC37.UINT8[LH]
#define RSCAN0RPGACC37H RSCAN0.RPGACC37.UINT16[H]
#define RSCAN0RPGACC37HL RSCAN0.RPGACC37.UINT8[HL]
#define RSCAN0RPGACC37HH RSCAN0.RPGACC37.UINT8[HH]
#define RSCAN0RPGACC38 RSCAN0.RPGACC38.UINT32
#define RSCAN0RPGACC38L RSCAN0.RPGACC38.UINT16[L]
#define RSCAN0RPGACC38LL RSCAN0.RPGACC38.UINT8[LL]
#define RSCAN0RPGACC38LH RSCAN0.RPGACC38.UINT8[LH]
#define RSCAN0RPGACC38H RSCAN0.RPGACC38.UINT16[H]
#define RSCAN0RPGACC38HL RSCAN0.RPGACC38.UINT8[HL]
#define RSCAN0RPGACC38HH RSCAN0.RPGACC38.UINT8[HH]
#define RSCAN0RPGACC39 RSCAN0.RPGACC39.UINT32
#define RSCAN0RPGACC39L RSCAN0.RPGACC39.UINT16[L]
#define RSCAN0RPGACC39LL RSCAN0.RPGACC39.UINT8[LL]
#define RSCAN0RPGACC39LH RSCAN0.RPGACC39.UINT8[LH]
#define RSCAN0RPGACC39H RSCAN0.RPGACC39.UINT16[H]
#define RSCAN0RPGACC39HL RSCAN0.RPGACC39.UINT8[HL]
#define RSCAN0RPGACC39HH RSCAN0.RPGACC39.UINT8[HH]
#define RSCAN0RPGACC40 RSCAN0.RPGACC40.UINT32
#define RSCAN0RPGACC40L RSCAN0.RPGACC40.UINT16[L]
#define RSCAN0RPGACC40LL RSCAN0.RPGACC40.UINT8[LL]
#define RSCAN0RPGACC40LH RSCAN0.RPGACC40.UINT8[LH]
#define RSCAN0RPGACC40H RSCAN0.RPGACC40.UINT16[H]
#define RSCAN0RPGACC40HL RSCAN0.RPGACC40.UINT8[HL]
#define RSCAN0RPGACC40HH RSCAN0.RPGACC40.UINT8[HH]
#define RSCAN0RPGACC41 RSCAN0.RPGACC41.UINT32
#define RSCAN0RPGACC41L RSCAN0.RPGACC41.UINT16[L]
#define RSCAN0RPGACC41LL RSCAN0.RPGACC41.UINT8[LL]
#define RSCAN0RPGACC41LH RSCAN0.RPGACC41.UINT8[LH]
#define RSCAN0RPGACC41H RSCAN0.RPGACC41.UINT16[H]
#define RSCAN0RPGACC41HL RSCAN0.RPGACC41.UINT8[HL]
#define RSCAN0RPGACC41HH RSCAN0.RPGACC41.UINT8[HH]
#define RSCAN0RPGACC42 RSCAN0.RPGACC42.UINT32
#define RSCAN0RPGACC42L RSCAN0.RPGACC42.UINT16[L]
#define RSCAN0RPGACC42LL RSCAN0.RPGACC42.UINT8[LL]
#define RSCAN0RPGACC42LH RSCAN0.RPGACC42.UINT8[LH]
#define RSCAN0RPGACC42H RSCAN0.RPGACC42.UINT16[H]
#define RSCAN0RPGACC42HL RSCAN0.RPGACC42.UINT8[HL]
#define RSCAN0RPGACC42HH RSCAN0.RPGACC42.UINT8[HH]
#define RSCAN0RPGACC43 RSCAN0.RPGACC43.UINT32
#define RSCAN0RPGACC43L RSCAN0.RPGACC43.UINT16[L]
#define RSCAN0RPGACC43LL RSCAN0.RPGACC43.UINT8[LL]
#define RSCAN0RPGACC43LH RSCAN0.RPGACC43.UINT8[LH]
#define RSCAN0RPGACC43H RSCAN0.RPGACC43.UINT16[H]
#define RSCAN0RPGACC43HL RSCAN0.RPGACC43.UINT8[HL]
#define RSCAN0RPGACC43HH RSCAN0.RPGACC43.UINT8[HH]
#define RSCAN0RPGACC44 RSCAN0.RPGACC44.UINT32
#define RSCAN0RPGACC44L RSCAN0.RPGACC44.UINT16[L]
#define RSCAN0RPGACC44LL RSCAN0.RPGACC44.UINT8[LL]
#define RSCAN0RPGACC44LH RSCAN0.RPGACC44.UINT8[LH]
#define RSCAN0RPGACC44H RSCAN0.RPGACC44.UINT16[H]
#define RSCAN0RPGACC44HL RSCAN0.RPGACC44.UINT8[HL]
#define RSCAN0RPGACC44HH RSCAN0.RPGACC44.UINT8[HH]
#define RSCAN0RPGACC45 RSCAN0.RPGACC45.UINT32
#define RSCAN0RPGACC45L RSCAN0.RPGACC45.UINT16[L]
#define RSCAN0RPGACC45LL RSCAN0.RPGACC45.UINT8[LL]
#define RSCAN0RPGACC45LH RSCAN0.RPGACC45.UINT8[LH]
#define RSCAN0RPGACC45H RSCAN0.RPGACC45.UINT16[H]
#define RSCAN0RPGACC45HL RSCAN0.RPGACC45.UINT8[HL]
#define RSCAN0RPGACC45HH RSCAN0.RPGACC45.UINT8[HH]
#define RSCAN0RPGACC46 RSCAN0.RPGACC46.UINT32
#define RSCAN0RPGACC46L RSCAN0.RPGACC46.UINT16[L]
#define RSCAN0RPGACC46LL RSCAN0.RPGACC46.UINT8[LL]
#define RSCAN0RPGACC46LH RSCAN0.RPGACC46.UINT8[LH]
#define RSCAN0RPGACC46H RSCAN0.RPGACC46.UINT16[H]
#define RSCAN0RPGACC46HL RSCAN0.RPGACC46.UINT8[HL]
#define RSCAN0RPGACC46HH RSCAN0.RPGACC46.UINT8[HH]
#define RSCAN0RPGACC47 RSCAN0.RPGACC47.UINT32
#define RSCAN0RPGACC47L RSCAN0.RPGACC47.UINT16[L]
#define RSCAN0RPGACC47LL RSCAN0.RPGACC47.UINT8[LL]
#define RSCAN0RPGACC47LH RSCAN0.RPGACC47.UINT8[LH]
#define RSCAN0RPGACC47H RSCAN0.RPGACC47.UINT16[H]
#define RSCAN0RPGACC47HL RSCAN0.RPGACC47.UINT8[HL]
#define RSCAN0RPGACC47HH RSCAN0.RPGACC47.UINT8[HH]
#define RSCAN0RPGACC48 RSCAN0.RPGACC48.UINT32
#define RSCAN0RPGACC48L RSCAN0.RPGACC48.UINT16[L]
#define RSCAN0RPGACC48LL RSCAN0.RPGACC48.UINT8[LL]
#define RSCAN0RPGACC48LH RSCAN0.RPGACC48.UINT8[LH]
#define RSCAN0RPGACC48H RSCAN0.RPGACC48.UINT16[H]
#define RSCAN0RPGACC48HL RSCAN0.RPGACC48.UINT8[HL]
#define RSCAN0RPGACC48HH RSCAN0.RPGACC48.UINT8[HH]
#define RSCAN0RPGACC49 RSCAN0.RPGACC49.UINT32
#define RSCAN0RPGACC49L RSCAN0.RPGACC49.UINT16[L]
#define RSCAN0RPGACC49LL RSCAN0.RPGACC49.UINT8[LL]
#define RSCAN0RPGACC49LH RSCAN0.RPGACC49.UINT8[LH]
#define RSCAN0RPGACC49H RSCAN0.RPGACC49.UINT16[H]
#define RSCAN0RPGACC49HL RSCAN0.RPGACC49.UINT8[HL]
#define RSCAN0RPGACC49HH RSCAN0.RPGACC49.UINT8[HH]
#define RSCAN0RPGACC50 RSCAN0.RPGACC50.UINT32
#define RSCAN0RPGACC50L RSCAN0.RPGACC50.UINT16[L]
#define RSCAN0RPGACC50LL RSCAN0.RPGACC50.UINT8[LL]
#define RSCAN0RPGACC50LH RSCAN0.RPGACC50.UINT8[LH]
#define RSCAN0RPGACC50H RSCAN0.RPGACC50.UINT16[H]
#define RSCAN0RPGACC50HL RSCAN0.RPGACC50.UINT8[HL]
#define RSCAN0RPGACC50HH RSCAN0.RPGACC50.UINT8[HH]
#define RSCAN0RPGACC51 RSCAN0.RPGACC51.UINT32
#define RSCAN0RPGACC51L RSCAN0.RPGACC51.UINT16[L]
#define RSCAN0RPGACC51LL RSCAN0.RPGACC51.UINT8[LL]
#define RSCAN0RPGACC51LH RSCAN0.RPGACC51.UINT8[LH]
#define RSCAN0RPGACC51H RSCAN0.RPGACC51.UINT16[H]
#define RSCAN0RPGACC51HL RSCAN0.RPGACC51.UINT8[HL]
#define RSCAN0RPGACC51HH RSCAN0.RPGACC51.UINT8[HH]
#define RSCAN0RPGACC52 RSCAN0.RPGACC52.UINT32
#define RSCAN0RPGACC52L RSCAN0.RPGACC52.UINT16[L]
#define RSCAN0RPGACC52LL RSCAN0.RPGACC52.UINT8[LL]
#define RSCAN0RPGACC52LH RSCAN0.RPGACC52.UINT8[LH]
#define RSCAN0RPGACC52H RSCAN0.RPGACC52.UINT16[H]
#define RSCAN0RPGACC52HL RSCAN0.RPGACC52.UINT8[HL]
#define RSCAN0RPGACC52HH RSCAN0.RPGACC52.UINT8[HH]
#define RSCAN0RPGACC53 RSCAN0.RPGACC53.UINT32
#define RSCAN0RPGACC53L RSCAN0.RPGACC53.UINT16[L]
#define RSCAN0RPGACC53LL RSCAN0.RPGACC53.UINT8[LL]
#define RSCAN0RPGACC53LH RSCAN0.RPGACC53.UINT8[LH]
#define RSCAN0RPGACC53H RSCAN0.RPGACC53.UINT16[H]
#define RSCAN0RPGACC53HL RSCAN0.RPGACC53.UINT8[HL]
#define RSCAN0RPGACC53HH RSCAN0.RPGACC53.UINT8[HH]
#define RSCAN0RPGACC54 RSCAN0.RPGACC54.UINT32
#define RSCAN0RPGACC54L RSCAN0.RPGACC54.UINT16[L]
#define RSCAN0RPGACC54LL RSCAN0.RPGACC54.UINT8[LL]
#define RSCAN0RPGACC54LH RSCAN0.RPGACC54.UINT8[LH]
#define RSCAN0RPGACC54H RSCAN0.RPGACC54.UINT16[H]
#define RSCAN0RPGACC54HL RSCAN0.RPGACC54.UINT8[HL]
#define RSCAN0RPGACC54HH RSCAN0.RPGACC54.UINT8[HH]
#define RSCAN0RPGACC55 RSCAN0.RPGACC55.UINT32
#define RSCAN0RPGACC55L RSCAN0.RPGACC55.UINT16[L]
#define RSCAN0RPGACC55LL RSCAN0.RPGACC55.UINT8[LL]
#define RSCAN0RPGACC55LH RSCAN0.RPGACC55.UINT8[LH]
#define RSCAN0RPGACC55H RSCAN0.RPGACC55.UINT16[H]
#define RSCAN0RPGACC55HL RSCAN0.RPGACC55.UINT8[HL]
#define RSCAN0RPGACC55HH RSCAN0.RPGACC55.UINT8[HH]
#define RSCAN0RPGACC56 RSCAN0.RPGACC56.UINT32
#define RSCAN0RPGACC56L RSCAN0.RPGACC56.UINT16[L]
#define RSCAN0RPGACC56LL RSCAN0.RPGACC56.UINT8[LL]
#define RSCAN0RPGACC56LH RSCAN0.RPGACC56.UINT8[LH]
#define RSCAN0RPGACC56H RSCAN0.RPGACC56.UINT16[H]
#define RSCAN0RPGACC56HL RSCAN0.RPGACC56.UINT8[HL]
#define RSCAN0RPGACC56HH RSCAN0.RPGACC56.UINT8[HH]
#define RSCAN0RPGACC57 RSCAN0.RPGACC57.UINT32
#define RSCAN0RPGACC57L RSCAN0.RPGACC57.UINT16[L]
#define RSCAN0RPGACC57LL RSCAN0.RPGACC57.UINT8[LL]
#define RSCAN0RPGACC57LH RSCAN0.RPGACC57.UINT8[LH]
#define RSCAN0RPGACC57H RSCAN0.RPGACC57.UINT16[H]
#define RSCAN0RPGACC57HL RSCAN0.RPGACC57.UINT8[HL]
#define RSCAN0RPGACC57HH RSCAN0.RPGACC57.UINT8[HH]
#define RSCAN0RPGACC58 RSCAN0.RPGACC58.UINT32
#define RSCAN0RPGACC58L RSCAN0.RPGACC58.UINT16[L]
#define RSCAN0RPGACC58LL RSCAN0.RPGACC58.UINT8[LL]
#define RSCAN0RPGACC58LH RSCAN0.RPGACC58.UINT8[LH]
#define RSCAN0RPGACC58H RSCAN0.RPGACC58.UINT16[H]
#define RSCAN0RPGACC58HL RSCAN0.RPGACC58.UINT8[HL]
#define RSCAN0RPGACC58HH RSCAN0.RPGACC58.UINT8[HH]
#define RSCAN0RPGACC59 RSCAN0.RPGACC59.UINT32
#define RSCAN0RPGACC59L RSCAN0.RPGACC59.UINT16[L]
#define RSCAN0RPGACC59LL RSCAN0.RPGACC59.UINT8[LL]
#define RSCAN0RPGACC59LH RSCAN0.RPGACC59.UINT8[LH]
#define RSCAN0RPGACC59H RSCAN0.RPGACC59.UINT16[H]
#define RSCAN0RPGACC59HL RSCAN0.RPGACC59.UINT8[HL]
#define RSCAN0RPGACC59HH RSCAN0.RPGACC59.UINT8[HH]
#define RSCAN0RPGACC60 RSCAN0.RPGACC60.UINT32
#define RSCAN0RPGACC60L RSCAN0.RPGACC60.UINT16[L]
#define RSCAN0RPGACC60LL RSCAN0.RPGACC60.UINT8[LL]
#define RSCAN0RPGACC60LH RSCAN0.RPGACC60.UINT8[LH]
#define RSCAN0RPGACC60H RSCAN0.RPGACC60.UINT16[H]
#define RSCAN0RPGACC60HL RSCAN0.RPGACC60.UINT8[HL]
#define RSCAN0RPGACC60HH RSCAN0.RPGACC60.UINT8[HH]
#define RSCAN0RPGACC61 RSCAN0.RPGACC61.UINT32
#define RSCAN0RPGACC61L RSCAN0.RPGACC61.UINT16[L]
#define RSCAN0RPGACC61LL RSCAN0.RPGACC61.UINT8[LL]
#define RSCAN0RPGACC61LH RSCAN0.RPGACC61.UINT8[LH]
#define RSCAN0RPGACC61H RSCAN0.RPGACC61.UINT16[H]
#define RSCAN0RPGACC61HL RSCAN0.RPGACC61.UINT8[HL]
#define RSCAN0RPGACC61HH RSCAN0.RPGACC61.UINT8[HH]
#define RSCAN0RPGACC62 RSCAN0.RPGACC62.UINT32
#define RSCAN0RPGACC62L RSCAN0.RPGACC62.UINT16[L]
#define RSCAN0RPGACC62LL RSCAN0.RPGACC62.UINT8[LL]
#define RSCAN0RPGACC62LH RSCAN0.RPGACC62.UINT8[LH]
#define RSCAN0RPGACC62H RSCAN0.RPGACC62.UINT16[H]
#define RSCAN0RPGACC62HL RSCAN0.RPGACC62.UINT8[HL]
#define RSCAN0RPGACC62HH RSCAN0.RPGACC62.UINT8[HH]
#define RSCAN0RPGACC63 RSCAN0.RPGACC63.UINT32
#define RSCAN0RPGACC63L RSCAN0.RPGACC63.UINT16[L]
#define RSCAN0RPGACC63LL RSCAN0.RPGACC63.UINT8[LL]
#define RSCAN0RPGACC63LH RSCAN0.RPGACC63.UINT8[LH]
#define RSCAN0RPGACC63H RSCAN0.RPGACC63.UINT16[H]
#define RSCAN0RPGACC63HL RSCAN0.RPGACC63.UINT8[HL]
#define RSCAN0RPGACC63HH RSCAN0.RPGACC63.UINT8[HH]
#define CSIH0CTL0 CSIH0.CTL0.UINT8
#define CSIH0MBS CSIH0.CTL0.MBS
#define CSIH0JOBE CSIH0.CTL0.JOBE
#define CSIH0RXE CSIH0.CTL0.RXE
#define CSIH0TXE CSIH0.CTL0.TXE
#define CSIH0PWR CSIH0.CTL0.PWR
#define CSIH0STR0 CSIH0.STR0
#define CSIH0STCR0 CSIH0.STCR0
#define CSIH0CTL1 CSIH0.CTL1
#define CSIH0CTL2 CSIH0.CTL2
#define CSIH0EMU CSIH0.EMU.UINT8
#define CSIH0SVSDIS CSIH0.EMU.SVSDIS
#define CSIH0MCTL1 CSIH0.MCTL1
#define CSIH0MCTL2 CSIH0.MCTL2
#define CSIH0TX0W CSIH0.TX0W
#define CSIH0TX0H CSIH0.TX0H
#define CSIH0RX0W CSIH0.RX0W
#define CSIH0RX0H CSIH0.RX0H
#define CSIH0MRWP0 CSIH0.MRWP0
#define CSIH0MCTL0 CSIH0.MCTL0
#define CSIH0CFG0 CSIH0.CFG0
#define CSIH0CFG1 CSIH0.CFG1
#define CSIH0CFG2 CSIH0.CFG2
#define CSIH0CFG3 CSIH0.CFG3
#define CSIH0CFG4 CSIH0.CFG4
#define CSIH0CFG5 CSIH0.CFG5
#define CSIH0CFG6 CSIH0.CFG6
#define CSIH0CFG7 CSIH0.CFG7
#define CSIH0BRS0 CSIH0.BRS0
#define CSIH0BRS1 CSIH0.BRS1
#define CSIH0BRS2 CSIH0.BRS2
#define CSIH0BRS3 CSIH0.BRS3
#define CSIH1CTL0 CSIH1.CTL0.UINT8
#define CSIH1MBS CSIH1.CTL0.MBS
#define CSIH1JOBE CSIH1.CTL0.JOBE
#define CSIH1RXE CSIH1.CTL0.RXE
#define CSIH1TXE CSIH1.CTL0.TXE
#define CSIH1PWR CSIH1.CTL0.PWR
#define CSIH1STR0 CSIH1.STR0
#define CSIH1STCR0 CSIH1.STCR0
#define CSIH1CTL1 CSIH1.CTL1
#define CSIH1CTL2 CSIH1.CTL2
#define CSIH1EMU CSIH1.EMU.UINT8
#define CSIH1SVSDIS CSIH1.EMU.SVSDIS
#define CSIH1MCTL1 CSIH1.MCTL1
#define CSIH1MCTL2 CSIH1.MCTL2
#define CSIH1TX0W CSIH1.TX0W
#define CSIH1TX0H CSIH1.TX0H
#define CSIH1RX0W CSIH1.RX0W
#define CSIH1RX0H CSIH1.RX0H
#define CSIH1MRWP0 CSIH1.MRWP0
#define CSIH1MCTL0 CSIH1.MCTL0
#define CSIH1CFG0 CSIH1.CFG0
#define CSIH1CFG1 CSIH1.CFG1
#define CSIH1CFG2 CSIH1.CFG2
#define CSIH1CFG3 CSIH1.CFG3
#define CSIH1CFG4 CSIH1.CFG4
#define CSIH1CFG5 CSIH1.CFG5
#define CSIH1BRS0 CSIH1.BRS0
#define CSIH1BRS1 CSIH1.BRS1
#define CSIH1BRS2 CSIH1.BRS2
#define CSIH1BRS3 CSIH1.BRS3
#define CSIH2CTL0 CSIH2.CTL0.UINT8
#define CSIH2MBS CSIH2.CTL0.MBS
#define CSIH2JOBE CSIH2.CTL0.JOBE
#define CSIH2RXE CSIH2.CTL0.RXE
#define CSIH2TXE CSIH2.CTL0.TXE
#define CSIH2PWR CSIH2.CTL0.PWR
#define CSIH2STR0 CSIH2.STR0
#define CSIH2STCR0 CSIH2.STCR0
#define CSIH2CTL1 CSIH2.CTL1
#define CSIH2CTL2 CSIH2.CTL2
#define CSIH2EMU CSIH2.EMU.UINT8
#define CSIH2SVSDIS CSIH2.EMU.SVSDIS
#define CSIH2MCTL1 CSIH2.MCTL1
#define CSIH2MCTL2 CSIH2.MCTL2
#define CSIH2TX0W CSIH2.TX0W
#define CSIH2TX0H CSIH2.TX0H
#define CSIH2RX0W CSIH2.RX0W
#define CSIH2RX0H CSIH2.RX0H
#define CSIH2MRWP0 CSIH2.MRWP0
#define CSIH2MCTL0 CSIH2.MCTL0
#define CSIH2CFG0 CSIH2.CFG0
#define CSIH2CFG1 CSIH2.CFG1
#define CSIH2CFG2 CSIH2.CFG2
#define CSIH2CFG3 CSIH2.CFG3
#define CSIH2CFG4 CSIH2.CFG4
#define CSIH2CFG5 CSIH2.CFG5
#define CSIH2BRS0 CSIH2.BRS0
#define CSIH2BRS1 CSIH2.BRS1
#define CSIH2BRS2 CSIH2.BRS2
#define CSIH2BRS3 CSIH2.BRS3
#define CSIH3CTL0 CSIH3.CTL0.UINT8
#define CSIH3MBS CSIH3.CTL0.MBS
#define CSIH3JOBE CSIH3.CTL0.JOBE
#define CSIH3RXE CSIH3.CTL0.RXE
#define CSIH3TXE CSIH3.CTL0.TXE
#define CSIH3PWR CSIH3.CTL0.PWR
#define CSIH3STR0 CSIH3.STR0
#define CSIH3STCR0 CSIH3.STCR0
#define CSIH3CTL1 CSIH3.CTL1
#define CSIH3CTL2 CSIH3.CTL2
#define CSIH3EMU CSIH3.EMU.UINT8
#define CSIH3SVSDIS CSIH3.EMU.SVSDIS
#define CSIH3MCTL1 CSIH3.MCTL1
#define CSIH3MCTL2 CSIH3.MCTL2
#define CSIH3TX0W CSIH3.TX0W
#define CSIH3TX0H CSIH3.TX0H
#define CSIH3RX0W CSIH3.RX0W
#define CSIH3RX0H CSIH3.RX0H
#define CSIH3MRWP0 CSIH3.MRWP0
#define CSIH3MCTL0 CSIH3.MCTL0
#define CSIH3CFG0 CSIH3.CFG0
#define CSIH3CFG1 CSIH3.CFG1
#define CSIH3CFG2 CSIH3.CFG2
#define CSIH3CFG3 CSIH3.CFG3
#define CSIH3BRS0 CSIH3.BRS0
#define CSIH3BRS1 CSIH3.BRS1
#define CSIH3BRS2 CSIH3.BRS2
#define CSIH3BRS3 CSIH3.BRS3
#define CSIG0CTL0 CSIG0.CTL0.UINT8
#define CSIG0RXE CSIG0.CTL0.RXE
#define CSIG0TXE CSIG0.CTL0.TXE
#define CSIG0PWR CSIG0.CTL0.PWR
#define CSIG0STR0 CSIG0.STR0
#define CSIG0STCR0 CSIG0.STCR0
#define CSIG0CTL1 CSIG0.CTL1
#define CSIG0CTL2 CSIG0.CTL2
#define CSIG0EMU CSIG0.EMU.UINT8
#define CSIG0SVSDIS CSIG0.EMU.SVSDIS
#define CSIG0BCTL0 CSIG0.BCTL0.UINT8
#define CSIG0SCE CSIG0.BCTL0.SCE
#define CSIG0TX0W CSIG0.TX0W
#define CSIG0TX0H CSIG0.TX0H
#define CSIG0RX0 CSIG0.RX0
#define CSIG0CFG0 CSIG0.CFG0
#define CSIG1CTL0 CSIG1.CTL0.UINT8
#define CSIG1RXE CSIG1.CTL0.RXE
#define CSIG1TXE CSIG1.CTL0.TXE
#define CSIG1PWR CSIG1.CTL0.PWR
#define CSIG1STR0 CSIG1.STR0
#define CSIG1STCR0 CSIG1.STCR0
#define CSIG1CTL1 CSIG1.CTL1
#define CSIG1CTL2 CSIG1.CTL2
#define CSIG1EMU CSIG1.EMU.UINT8
#define CSIG1SVSDIS CSIG1.EMU.SVSDIS
#define CSIG1BCTL0 CSIG1.BCTL0.UINT8
#define CSIG1SCE CSIG1.BCTL0.SCE
#define CSIG1TX0W CSIG1.TX0W
#define CSIG1TX0H CSIG1.TX0H
#define CSIG1RX0 CSIG1.RX0
#define CSIG1CFG0 CSIG1.CFG0
#define PIC0SST PIC0.SST
#define PIC0SSER0 PIC0.SSER0
#define PIC0SSER2 PIC0.SSER2
#define PIC0HIZCEN0 PIC0.HIZCEN0
#define PIC0ADTEN400 PIC0.ADTEN400
#define PIC0ADTEN401 PIC0.ADTEN401
#define PIC0ADTEN402 PIC0.ADTEN402
#define PIC0REG200 PIC0.REG200
#define PIC0REG201 PIC0.REG201
#define PIC0REG202 PIC0.REG202
#define PIC0REG203 PIC0.REG203
#define PIC0REG30 PIC0.REG30
#define PIC0REG31 PIC0.REG31
#define TAUD0CDR0 TAUD0.CDR0
#define TAUD0CDR1 TAUD0.CDR1
#define TAUD0CDR2 TAUD0.CDR2
#define TAUD0CDR3 TAUD0.CDR3
#define TAUD0CDR4 TAUD0.CDR4
#define TAUD0CDR5 TAUD0.CDR5
#define TAUD0CDR6 TAUD0.CDR6
#define TAUD0CDR7 TAUD0.CDR7
#define TAUD0CDR8 TAUD0.CDR8
#define TAUD0CDR9 TAUD0.CDR9
#define TAUD0CDR10 TAUD0.CDR10
#define TAUD0CDR11 TAUD0.CDR11
#define TAUD0CDR12 TAUD0.CDR12
#define TAUD0CDR13 TAUD0.CDR13
#define TAUD0CDR14 TAUD0.CDR14
#define TAUD0CDR15 TAUD0.CDR15
#define TAUD0TOL TAUD0.TOL
#define TAUD0RDT TAUD0.RDT
#define TAUD0RSF TAUD0.RSF
#define TAUD0TRO TAUD0.TRO
#define TAUD0TME TAUD0.TME
#define TAUD0TDL TAUD0.TDL
#define TAUD0TO TAUD0.TO
#define TAUD0TOE TAUD0.TOE
#define TAUD0CNT0 TAUD0.CNT0
#define TAUD0CNT1 TAUD0.CNT1
#define TAUD0CNT2 TAUD0.CNT2
#define TAUD0CNT3 TAUD0.CNT3
#define TAUD0CNT4 TAUD0.CNT4
#define TAUD0CNT5 TAUD0.CNT5
#define TAUD0CNT6 TAUD0.CNT6
#define TAUD0CNT7 TAUD0.CNT7
#define TAUD0CNT8 TAUD0.CNT8
#define TAUD0CNT9 TAUD0.CNT9
#define TAUD0CNT10 TAUD0.CNT10
#define TAUD0CNT11 TAUD0.CNT11
#define TAUD0CNT12 TAUD0.CNT12
#define TAUD0CNT13 TAUD0.CNT13
#define TAUD0CNT14 TAUD0.CNT14
#define TAUD0CNT15 TAUD0.CNT15
#define TAUD0CMUR0 TAUD0.CMUR0
#define TAUD0CMUR1 TAUD0.CMUR1
#define TAUD0CMUR2 TAUD0.CMUR2
#define TAUD0CMUR3 TAUD0.CMUR3
#define TAUD0CMUR4 TAUD0.CMUR4
#define TAUD0CMUR5 TAUD0.CMUR5
#define TAUD0CMUR6 TAUD0.CMUR6
#define TAUD0CMUR7 TAUD0.CMUR7
#define TAUD0CMUR8 TAUD0.CMUR8
#define TAUD0CMUR9 TAUD0.CMUR9
#define TAUD0CMUR10 TAUD0.CMUR10
#define TAUD0CMUR11 TAUD0.CMUR11
#define TAUD0CMUR12 TAUD0.CMUR12
#define TAUD0CMUR13 TAUD0.CMUR13
#define TAUD0CMUR14 TAUD0.CMUR14
#define TAUD0CMUR15 TAUD0.CMUR15
#define TAUD0CSR0 TAUD0.CSR0
#define TAUD0CSR1 TAUD0.CSR1
#define TAUD0CSR2 TAUD0.CSR2
#define TAUD0CSR3 TAUD0.CSR3
#define TAUD0CSR4 TAUD0.CSR4
#define TAUD0CSR5 TAUD0.CSR5
#define TAUD0CSR6 TAUD0.CSR6
#define TAUD0CSR7 TAUD0.CSR7
#define TAUD0CSR8 TAUD0.CSR8
#define TAUD0CSR9 TAUD0.CSR9
#define TAUD0CSR10 TAUD0.CSR10
#define TAUD0CSR11 TAUD0.CSR11
#define TAUD0CSR12 TAUD0.CSR12
#define TAUD0CSR13 TAUD0.CSR13
#define TAUD0CSR14 TAUD0.CSR14
#define TAUD0CSR15 TAUD0.CSR15
#define TAUD0CSC0 TAUD0.CSC0
#define TAUD0CSC1 TAUD0.CSC1
#define TAUD0CSC2 TAUD0.CSC2
#define TAUD0CSC3 TAUD0.CSC3
#define TAUD0CSC4 TAUD0.CSC4
#define TAUD0CSC5 TAUD0.CSC5
#define TAUD0CSC6 TAUD0.CSC6
#define TAUD0CSC7 TAUD0.CSC7
#define TAUD0CSC8 TAUD0.CSC8
#define TAUD0CSC9 TAUD0.CSC9
#define TAUD0CSC10 TAUD0.CSC10
#define TAUD0CSC11 TAUD0.CSC11
#define TAUD0CSC12 TAUD0.CSC12
#define TAUD0CSC13 TAUD0.CSC13
#define TAUD0CSC14 TAUD0.CSC14
#define TAUD0CSC15 TAUD0.CSC15
#define TAUD0TE TAUD0.TE
#define TAUD0TS TAUD0.TS
#define TAUD0TT TAUD0.TT
#define TAUD0CMOR0 TAUD0.CMOR0
#define TAUD0CMOR1 TAUD0.CMOR1
#define TAUD0CMOR2 TAUD0.CMOR2
#define TAUD0CMOR3 TAUD0.CMOR3
#define TAUD0CMOR4 TAUD0.CMOR4
#define TAUD0CMOR5 TAUD0.CMOR5
#define TAUD0CMOR6 TAUD0.CMOR6
#define TAUD0CMOR7 TAUD0.CMOR7
#define TAUD0CMOR8 TAUD0.CMOR8
#define TAUD0CMOR9 TAUD0.CMOR9
#define TAUD0CMOR10 TAUD0.CMOR10
#define TAUD0CMOR11 TAUD0.CMOR11
#define TAUD0CMOR12 TAUD0.CMOR12
#define TAUD0CMOR13 TAUD0.CMOR13
#define TAUD0CMOR14 TAUD0.CMOR14
#define TAUD0CMOR15 TAUD0.CMOR15
#define TAUD0TPS TAUD0.TPS
#define TAUD0BRS TAUD0.BRS
#define TAUD0TOM TAUD0.TOM
#define TAUD0TOC TAUD0.TOC
#define TAUD0TDE TAUD0.TDE
#define TAUD0TDM TAUD0.TDM
#define TAUD0TRE TAUD0.TRE
#define TAUD0TRC TAUD0.TRC
#define TAUD0RDE TAUD0.RDE
#define TAUD0RDM TAUD0.RDM
#define TAUD0RDS TAUD0.RDS
#define TAUD0RDC TAUD0.RDC
#define TAUD0EMU TAUD0.EMU
#define TAUB0CDR0 TAUB0.CDR0
#define TAUB0CDR1 TAUB0.CDR1
#define TAUB0CDR2 TAUB0.CDR2
#define TAUB0CDR3 TAUB0.CDR3
#define TAUB0CDR4 TAUB0.CDR4
#define TAUB0CDR5 TAUB0.CDR5
#define TAUB0CDR6 TAUB0.CDR6
#define TAUB0CDR7 TAUB0.CDR7
#define TAUB0CDR8 TAUB0.CDR8
#define TAUB0CDR9 TAUB0.CDR9
#define TAUB0CDR10 TAUB0.CDR10
#define TAUB0CDR11 TAUB0.CDR11
#define TAUB0CDR12 TAUB0.CDR12
#define TAUB0CDR13 TAUB0.CDR13
#define TAUB0CDR14 TAUB0.CDR14
#define TAUB0CDR15 TAUB0.CDR15
#define TAUB0TOL TAUB0.TOL
#define TAUB0RDT TAUB0.RDT
#define TAUB0RSF TAUB0.RSF
#define TAUB0TDL TAUB0.TDL
#define TAUB0TO TAUB0.TO
#define TAUB0TOE TAUB0.TOE
#define TAUB0CNT0 TAUB0.CNT0
#define TAUB0CNT1 TAUB0.CNT1
#define TAUB0CNT2 TAUB0.CNT2
#define TAUB0CNT3 TAUB0.CNT3
#define TAUB0CNT4 TAUB0.CNT4
#define TAUB0CNT5 TAUB0.CNT5
#define TAUB0CNT6 TAUB0.CNT6
#define TAUB0CNT7 TAUB0.CNT7
#define TAUB0CNT8 TAUB0.CNT8
#define TAUB0CNT9 TAUB0.CNT9
#define TAUB0CNT10 TAUB0.CNT10
#define TAUB0CNT11 TAUB0.CNT11
#define TAUB0CNT12 TAUB0.CNT12
#define TAUB0CNT13 TAUB0.CNT13
#define TAUB0CNT14 TAUB0.CNT14
#define TAUB0CNT15 TAUB0.CNT15
#define TAUB0CMUR0 TAUB0.CMUR0
#define TAUB0CMUR1 TAUB0.CMUR1
#define TAUB0CMUR2 TAUB0.CMUR2
#define TAUB0CMUR3 TAUB0.CMUR3
#define TAUB0CMUR4 TAUB0.CMUR4
#define TAUB0CMUR5 TAUB0.CMUR5
#define TAUB0CMUR6 TAUB0.CMUR6
#define TAUB0CMUR7 TAUB0.CMUR7
#define TAUB0CMUR8 TAUB0.CMUR8
#define TAUB0CMUR9 TAUB0.CMUR9
#define TAUB0CMUR10 TAUB0.CMUR10
#define TAUB0CMUR11 TAUB0.CMUR11
#define TAUB0CMUR12 TAUB0.CMUR12
#define TAUB0CMUR13 TAUB0.CMUR13
#define TAUB0CMUR14 TAUB0.CMUR14
#define TAUB0CMUR15 TAUB0.CMUR15
#define TAUB0CSR0 TAUB0.CSR0
#define TAUB0CSR1 TAUB0.CSR1
#define TAUB0CSR2 TAUB0.CSR2
#define TAUB0CSR3 TAUB0.CSR3
#define TAUB0CSR4 TAUB0.CSR4
#define TAUB0CSR5 TAUB0.CSR5
#define TAUB0CSR6 TAUB0.CSR6
#define TAUB0CSR7 TAUB0.CSR7
#define TAUB0CSR8 TAUB0.CSR8
#define TAUB0CSR9 TAUB0.CSR9
#define TAUB0CSR10 TAUB0.CSR10
#define TAUB0CSR11 TAUB0.CSR11
#define TAUB0CSR12 TAUB0.CSR12
#define TAUB0CSR13 TAUB0.CSR13
#define TAUB0CSR14 TAUB0.CSR14
#define TAUB0CSR15 TAUB0.CSR15
#define TAUB0CSC0 TAUB0.CSC0
#define TAUB0CSC1 TAUB0.CSC1
#define TAUB0CSC2 TAUB0.CSC2
#define TAUB0CSC3 TAUB0.CSC3
#define TAUB0CSC4 TAUB0.CSC4
#define TAUB0CSC5 TAUB0.CSC5
#define TAUB0CSC6 TAUB0.CSC6
#define TAUB0CSC7 TAUB0.CSC7
#define TAUB0CSC8 TAUB0.CSC8
#define TAUB0CSC9 TAUB0.CSC9
#define TAUB0CSC10 TAUB0.CSC10
#define TAUB0CSC11 TAUB0.CSC11
#define TAUB0CSC12 TAUB0.CSC12
#define TAUB0CSC13 TAUB0.CSC13
#define TAUB0CSC14 TAUB0.CSC14
#define TAUB0CSC15 TAUB0.CSC15
#define TAUB0TE TAUB0.TE
#define TAUB0TS TAUB0.TS
#define TAUB0TT TAUB0.TT
#define TAUB0CMOR0 TAUB0.CMOR0
#define TAUB0CMOR1 TAUB0.CMOR1
#define TAUB0CMOR2 TAUB0.CMOR2
#define TAUB0CMOR3 TAUB0.CMOR3
#define TAUB0CMOR4 TAUB0.CMOR4
#define TAUB0CMOR5 TAUB0.CMOR5
#define TAUB0CMOR6 TAUB0.CMOR6
#define TAUB0CMOR7 TAUB0.CMOR7
#define TAUB0CMOR8 TAUB0.CMOR8
#define TAUB0CMOR9 TAUB0.CMOR9
#define TAUB0CMOR10 TAUB0.CMOR10
#define TAUB0CMOR11 TAUB0.CMOR11
#define TAUB0CMOR12 TAUB0.CMOR12
#define TAUB0CMOR13 TAUB0.CMOR13
#define TAUB0CMOR14 TAUB0.CMOR14
#define TAUB0CMOR15 TAUB0.CMOR15
#define TAUB0TPS TAUB0.TPS
#define TAUB0TOM TAUB0.TOM
#define TAUB0TOC TAUB0.TOC
#define TAUB0TDE TAUB0.TDE
#define TAUB0RDE TAUB0.RDE
#define TAUB0RDM TAUB0.RDM
#define TAUB0RDS TAUB0.RDS
#define TAUB0RDC TAUB0.RDC
#define TAUB0EMU TAUB0.EMU
#define TAUB1CDR0 TAUB1.CDR0
#define TAUB1CDR1 TAUB1.CDR1
#define TAUB1CDR2 TAUB1.CDR2
#define TAUB1CDR3 TAUB1.CDR3
#define TAUB1CDR4 TAUB1.CDR4
#define TAUB1CDR5 TAUB1.CDR5
#define TAUB1CDR6 TAUB1.CDR6
#define TAUB1CDR7 TAUB1.CDR7
#define TAUB1CDR8 TAUB1.CDR8
#define TAUB1CDR9 TAUB1.CDR9
#define TAUB1CDR10 TAUB1.CDR10
#define TAUB1CDR11 TAUB1.CDR11
#define TAUB1CDR12 TAUB1.CDR12
#define TAUB1CDR13 TAUB1.CDR13
#define TAUB1CDR14 TAUB1.CDR14
#define TAUB1CDR15 TAUB1.CDR15
#define TAUB1TOL TAUB1.TOL
#define TAUB1RDT TAUB1.RDT
#define TAUB1RSF TAUB1.RSF
#define TAUB1TDL TAUB1.TDL
#define TAUB1TO TAUB1.TO
#define TAUB1TOE TAUB1.TOE
#define TAUB1CNT0 TAUB1.CNT0
#define TAUB1CNT1 TAUB1.CNT1
#define TAUB1CNT2 TAUB1.CNT2
#define TAUB1CNT3 TAUB1.CNT3
#define TAUB1CNT4 TAUB1.CNT4
#define TAUB1CNT5 TAUB1.CNT5
#define TAUB1CNT6 TAUB1.CNT6
#define TAUB1CNT7 TAUB1.CNT7
#define TAUB1CNT8 TAUB1.CNT8
#define TAUB1CNT9 TAUB1.CNT9
#define TAUB1CNT10 TAUB1.CNT10
#define TAUB1CNT11 TAUB1.CNT11
#define TAUB1CNT12 TAUB1.CNT12
#define TAUB1CNT13 TAUB1.CNT13
#define TAUB1CNT14 TAUB1.CNT14
#define TAUB1CNT15 TAUB1.CNT15
#define TAUB1CMUR0 TAUB1.CMUR0
#define TAUB1CMUR1 TAUB1.CMUR1
#define TAUB1CMUR2 TAUB1.CMUR2
#define TAUB1CMUR3 TAUB1.CMUR3
#define TAUB1CMUR4 TAUB1.CMUR4
#define TAUB1CMUR5 TAUB1.CMUR5
#define TAUB1CMUR6 TAUB1.CMUR6
#define TAUB1CMUR7 TAUB1.CMUR7
#define TAUB1CMUR8 TAUB1.CMUR8
#define TAUB1CMUR9 TAUB1.CMUR9
#define TAUB1CMUR10 TAUB1.CMUR10
#define TAUB1CMUR11 TAUB1.CMUR11
#define TAUB1CMUR12 TAUB1.CMUR12
#define TAUB1CMUR13 TAUB1.CMUR13
#define TAUB1CMUR14 TAUB1.CMUR14
#define TAUB1CMUR15 TAUB1.CMUR15
#define TAUB1CSR0 TAUB1.CSR0
#define TAUB1CSR1 TAUB1.CSR1
#define TAUB1CSR2 TAUB1.CSR2
#define TAUB1CSR3 TAUB1.CSR3
#define TAUB1CSR4 TAUB1.CSR4
#define TAUB1CSR5 TAUB1.CSR5
#define TAUB1CSR6 TAUB1.CSR6
#define TAUB1CSR7 TAUB1.CSR7
#define TAUB1CSR8 TAUB1.CSR8
#define TAUB1CSR9 TAUB1.CSR9
#define TAUB1CSR10 TAUB1.CSR10
#define TAUB1CSR11 TAUB1.CSR11
#define TAUB1CSR12 TAUB1.CSR12
#define TAUB1CSR13 TAUB1.CSR13
#define TAUB1CSR14 TAUB1.CSR14
#define TAUB1CSR15 TAUB1.CSR15
#define TAUB1CSC0 TAUB1.CSC0
#define TAUB1CSC1 TAUB1.CSC1
#define TAUB1CSC2 TAUB1.CSC2
#define TAUB1CSC3 TAUB1.CSC3
#define TAUB1CSC4 TAUB1.CSC4
#define TAUB1CSC5 TAUB1.CSC5
#define TAUB1CSC6 TAUB1.CSC6
#define TAUB1CSC7 TAUB1.CSC7
#define TAUB1CSC8 TAUB1.CSC8
#define TAUB1CSC9 TAUB1.CSC9
#define TAUB1CSC10 TAUB1.CSC10
#define TAUB1CSC11 TAUB1.CSC11
#define TAUB1CSC12 TAUB1.CSC12
#define TAUB1CSC13 TAUB1.CSC13
#define TAUB1CSC14 TAUB1.CSC14
#define TAUB1CSC15 TAUB1.CSC15
#define TAUB1TE TAUB1.TE
#define TAUB1TS TAUB1.TS
#define TAUB1TT TAUB1.TT
#define TAUB1CMOR0 TAUB1.CMOR0
#define TAUB1CMOR1 TAUB1.CMOR1
#define TAUB1CMOR2 TAUB1.CMOR2
#define TAUB1CMOR3 TAUB1.CMOR3
#define TAUB1CMOR4 TAUB1.CMOR4
#define TAUB1CMOR5 TAUB1.CMOR5
#define TAUB1CMOR6 TAUB1.CMOR6
#define TAUB1CMOR7 TAUB1.CMOR7
#define TAUB1CMOR8 TAUB1.CMOR8
#define TAUB1CMOR9 TAUB1.CMOR9
#define TAUB1CMOR10 TAUB1.CMOR10
#define TAUB1CMOR11 TAUB1.CMOR11
#define TAUB1CMOR12 TAUB1.CMOR12
#define TAUB1CMOR13 TAUB1.CMOR13
#define TAUB1CMOR14 TAUB1.CMOR14
#define TAUB1CMOR15 TAUB1.CMOR15
#define TAUB1TPS TAUB1.TPS
#define TAUB1TOM TAUB1.TOM
#define TAUB1TOC TAUB1.TOC
#define TAUB1TDE TAUB1.TDE
#define TAUB1RDE TAUB1.RDE
#define TAUB1RDM TAUB1.RDM
#define TAUB1RDS TAUB1.RDS
#define TAUB1RDC TAUB1.RDC
#define TAUB1EMU TAUB1.EMU
#define TAUJ0CDR0 TAUJ0.CDR0
#define TAUJ0CDR1 TAUJ0.CDR1
#define TAUJ0CDR2 TAUJ0.CDR2
#define TAUJ0CDR3 TAUJ0.CDR3
#define TAUJ0CNT0 TAUJ0.CNT0
#define TAUJ0CNT1 TAUJ0.CNT1
#define TAUJ0CNT2 TAUJ0.CNT2
#define TAUJ0CNT3 TAUJ0.CNT3
#define TAUJ0CMUR0 TAUJ0.CMUR0
#define TAUJ0CMUR1 TAUJ0.CMUR1
#define TAUJ0CMUR2 TAUJ0.CMUR2
#define TAUJ0CMUR3 TAUJ0.CMUR3
#define TAUJ0CSR0 TAUJ0.CSR0
#define TAUJ0CSR1 TAUJ0.CSR1
#define TAUJ0CSR2 TAUJ0.CSR2
#define TAUJ0CSR3 TAUJ0.CSR3
#define TAUJ0CSC0 TAUJ0.CSC0
#define TAUJ0CSC1 TAUJ0.CSC1
#define TAUJ0CSC2 TAUJ0.CSC2
#define TAUJ0CSC3 TAUJ0.CSC3
#define TAUJ0TE TAUJ0.TE
#define TAUJ0TS TAUJ0.TS
#define TAUJ0TT TAUJ0.TT
#define TAUJ0TO TAUJ0.TO
#define TAUJ0TOE TAUJ0.TOE
#define TAUJ0TOL TAUJ0.TOL
#define TAUJ0RDT TAUJ0.RDT
#define TAUJ0RSF TAUJ0.RSF
#define TAUJ0CMOR0 TAUJ0.CMOR0
#define TAUJ0CMOR1 TAUJ0.CMOR1
#define TAUJ0CMOR2 TAUJ0.CMOR2
#define TAUJ0CMOR3 TAUJ0.CMOR3
#define TAUJ0TPS TAUJ0.TPS
#define TAUJ0BRS TAUJ0.BRS
#define TAUJ0TOM TAUJ0.TOM
#define TAUJ0TOC TAUJ0.TOC
#define TAUJ0RDE TAUJ0.RDE
#define TAUJ0RDM TAUJ0.RDM
#define TAUJ0EMU TAUJ0.EMU
#define TAUJ1CDR0 TAUJ1.CDR0
#define TAUJ1CDR1 TAUJ1.CDR1
#define TAUJ1CDR2 TAUJ1.CDR2
#define TAUJ1CDR3 TAUJ1.CDR3
#define TAUJ1CNT0 TAUJ1.CNT0
#define TAUJ1CNT1 TAUJ1.CNT1
#define TAUJ1CNT2 TAUJ1.CNT2
#define TAUJ1CNT3 TAUJ1.CNT3
#define TAUJ1CMUR0 TAUJ1.CMUR0
#define TAUJ1CMUR1 TAUJ1.CMUR1
#define TAUJ1CMUR2 TAUJ1.CMUR2
#define TAUJ1CMUR3 TAUJ1.CMUR3
#define TAUJ1CSR0 TAUJ1.CSR0
#define TAUJ1CSR1 TAUJ1.CSR1
#define TAUJ1CSR2 TAUJ1.CSR2
#define TAUJ1CSR3 TAUJ1.CSR3
#define TAUJ1CSC0 TAUJ1.CSC0
#define TAUJ1CSC1 TAUJ1.CSC1
#define TAUJ1CSC2 TAUJ1.CSC2
#define TAUJ1CSC3 TAUJ1.CSC3
#define TAUJ1TE TAUJ1.TE
#define TAUJ1TS TAUJ1.TS
#define TAUJ1TT TAUJ1.TT
#define TAUJ1TO TAUJ1.TO
#define TAUJ1TOE TAUJ1.TOE
#define TAUJ1TOL TAUJ1.TOL
#define TAUJ1RDT TAUJ1.RDT
#define TAUJ1RSF TAUJ1.RSF
#define TAUJ1CMOR0 TAUJ1.CMOR0
#define TAUJ1CMOR1 TAUJ1.CMOR1
#define TAUJ1CMOR2 TAUJ1.CMOR2
#define TAUJ1CMOR3 TAUJ1.CMOR3
#define TAUJ1TPS TAUJ1.TPS
#define TAUJ1BRS TAUJ1.BRS
#define TAUJ1TOM TAUJ1.TOM
#define TAUJ1TOC TAUJ1.TOC
#define TAUJ1RDE TAUJ1.RDE
#define TAUJ1RDM TAUJ1.RDM
#define TAUJ1EMU TAUJ1.EMU
#define PWSA0CTL PWSA0.CTL
#define PWSA0STR PWSA0.STR
#define PWSA0STC PWSA0.STC
#define PWSA0EMU PWSA0.EMU
#define PWSA0QUE0 PWSA0.QUE0
#define PWSA0QUE1 PWSA0.QUE1
#define PWSA0QUE2 PWSA0.QUE2
#define PWSA0QUE3 PWSA0.QUE3
#define PWSA0QUE4 PWSA0.QUE4
#define PWSA0QUE5 PWSA0.QUE5
#define PWSA0QUE6 PWSA0.QUE6
#define PWSA0QUE7 PWSA0.QUE7
#define PWSA0PVCR00_01 PWSA0.PVCR00_01
#define PWSA0PVCR02_03 PWSA0.PVCR02_03
#define PWSA0PVCR04_05 PWSA0.PVCR04_05
#define PWSA0PVCR06_07 PWSA0.PVCR06_07
#define PWSA0PVCR08_09 PWSA0.PVCR08_09
#define PWSA0PVCR10_11 PWSA0.PVCR10_11
#define PWSA0PVCR12_13 PWSA0.PVCR12_13
#define PWSA0PVCR14_15 PWSA0.PVCR14_15
#define PWSA0PVCR16_17 PWSA0.PVCR16_17
#define PWSA0PVCR18_19 PWSA0.PVCR18_19
#define PWSA0PVCR20_21 PWSA0.PVCR20_21
#define PWSA0PVCR22_23 PWSA0.PVCR22_23
#define PWSA0PVCR24_25 PWSA0.PVCR24_25
#define PWSA0PVCR26_27 PWSA0.PVCR26_27
#define PWSA0PVCR28_29 PWSA0.PVCR28_29
#define PWSA0PVCR30_31 PWSA0.PVCR30_31
#define PWSA0PVCR32_33 PWSA0.PVCR32_33
#define PWSA0PVCR34_35 PWSA0.PVCR34_35
#define PWSA0PVCR36_37 PWSA0.PVCR36_37
#define PWSA0PVCR38_39 PWSA0.PVCR38_39
#define PWSA0PVCR40_41 PWSA0.PVCR40_41
#define PWSA0PVCR42_43 PWSA0.PVCR42_43
#define PWSA0PVCR44_45 PWSA0.PVCR44_45
#define PWSA0PVCR46_47 PWSA0.PVCR46_47
#define PWSA0PVCR48_49 PWSA0.PVCR48_49
#define PWSA0PVCR50_51 PWSA0.PVCR50_51
#define PWSA0PVCR52_53 PWSA0.PVCR52_53
#define PWSA0PVCR54_55 PWSA0.PVCR54_55
#define PWSA0PVCR56_57 PWSA0.PVCR56_57
#define PWSA0PVCR58_59 PWSA0.PVCR58_59
#define PWSA0PVCR60_61 PWSA0.PVCR60_61
#define PWSA0PVCR62_63 PWSA0.PVCR62_63
#define PWSA0PVCR64_65 PWSA0.PVCR64_65
#define PWSA0PVCR66_67 PWSA0.PVCR66_67
#define PWSA0PVCR68_69 PWSA0.PVCR68_69
#define PWSA0PVCR70_71 PWSA0.PVCR70_71
#define PWGA0CSDR PWGA0.CSDR
#define PWGA0CRDR PWGA0.CRDR
#define PWGA0CTDR PWGA0.CTDR
#define PWGA0RDT PWGA0.RDT
#define PWGA0RSF PWGA0.RSF
#define PWGA0CNT PWGA0.CNT
#define PWGA0CTL PWGA0.CTL
#define PWGA0CSBR PWGA0.CSBR
#define PWGA0CRBR PWGA0.CRBR
#define PWGA0CTBR PWGA0.CTBR
#define PWGA1CSDR PWGA1.CSDR
#define PWGA1CRDR PWGA1.CRDR
#define PWGA1CTDR PWGA1.CTDR
#define PWGA1RDT PWGA1.RDT
#define PWGA1RSF PWGA1.RSF
#define PWGA1CNT PWGA1.CNT
#define PWGA1CTL PWGA1.CTL
#define PWGA1CSBR PWGA1.CSBR
#define PWGA1CRBR PWGA1.CRBR
#define PWGA1CTBR PWGA1.CTBR
#define PWGA2CSDR PWGA2.CSDR
#define PWGA2CRDR PWGA2.CRDR
#define PWGA2CTDR PWGA2.CTDR
#define PWGA2RDT PWGA2.RDT
#define PWGA2RSF PWGA2.RSF
#define PWGA2CNT PWGA2.CNT
#define PWGA2CTL PWGA2.CTL
#define PWGA2CSBR PWGA2.CSBR
#define PWGA2CRBR PWGA2.CRBR
#define PWGA2CTBR PWGA2.CTBR
#define PWGA3CSDR PWGA3.CSDR
#define PWGA3CRDR PWGA3.CRDR
#define PWGA3CTDR PWGA3.CTDR
#define PWGA3RDT PWGA3.RDT
#define PWGA3RSF PWGA3.RSF
#define PWGA3CNT PWGA3.CNT
#define PWGA3CTL PWGA3.CTL
#define PWGA3CSBR PWGA3.CSBR
#define PWGA3CRBR PWGA3.CRBR
#define PWGA3CTBR PWGA3.CTBR
#define PWGA4CSDR PWGA4.CSDR
#define PWGA4CRDR PWGA4.CRDR
#define PWGA4CTDR PWGA4.CTDR
#define PWGA4RDT PWGA4.RDT
#define PWGA4RSF PWGA4.RSF
#define PWGA4CNT PWGA4.CNT
#define PWGA4CTL PWGA4.CTL
#define PWGA4CSBR PWGA4.CSBR
#define PWGA4CRBR PWGA4.CRBR
#define PWGA4CTBR PWGA4.CTBR
#define PWGA5CSDR PWGA5.CSDR
#define PWGA5CRDR PWGA5.CRDR
#define PWGA5CTDR PWGA5.CTDR
#define PWGA5RDT PWGA5.RDT
#define PWGA5RSF PWGA5.RSF
#define PWGA5CNT PWGA5.CNT
#define PWGA5CTL PWGA5.CTL
#define PWGA5CSBR PWGA5.CSBR
#define PWGA5CRBR PWGA5.CRBR
#define PWGA5CTBR PWGA5.CTBR
#define PWGA6CSDR PWGA6.CSDR
#define PWGA6CRDR PWGA6.CRDR
#define PWGA6CTDR PWGA6.CTDR
#define PWGA6RDT PWGA6.RDT
#define PWGA6RSF PWGA6.RSF
#define PWGA6CNT PWGA6.CNT
#define PWGA6CTL PWGA6.CTL
#define PWGA6CSBR PWGA6.CSBR
#define PWGA6CRBR PWGA6.CRBR
#define PWGA6CTBR PWGA6.CTBR
#define PWGA7CSDR PWGA7.CSDR
#define PWGA7CRDR PWGA7.CRDR
#define PWGA7CTDR PWGA7.CTDR
#define PWGA7RDT PWGA7.RDT
#define PWGA7RSF PWGA7.RSF
#define PWGA7CNT PWGA7.CNT
#define PWGA7CTL PWGA7.CTL
#define PWGA7CSBR PWGA7.CSBR
#define PWGA7CRBR PWGA7.CRBR
#define PWGA7CTBR PWGA7.CTBR
#define PWGA8CSDR PWGA8.CSDR
#define PWGA8CRDR PWGA8.CRDR
#define PWGA8CTDR PWGA8.CTDR
#define PWGA8RDT PWGA8.RDT
#define PWGA8RSF PWGA8.RSF
#define PWGA8CNT PWGA8.CNT
#define PWGA8CTL PWGA8.CTL
#define PWGA8CSBR PWGA8.CSBR
#define PWGA8CRBR PWGA8.CRBR
#define PWGA8CTBR PWGA8.CTBR
#define PWGA9CSDR PWGA9.CSDR
#define PWGA9CRDR PWGA9.CRDR
#define PWGA9CTDR PWGA9.CTDR
#define PWGA9RDT PWGA9.RDT
#define PWGA9RSF PWGA9.RSF
#define PWGA9CNT PWGA9.CNT
#define PWGA9CTL PWGA9.CTL
#define PWGA9CSBR PWGA9.CSBR
#define PWGA9CRBR PWGA9.CRBR
#define PWGA9CTBR PWGA9.CTBR
#define PWGA10CSDR PWGA10.CSDR
#define PWGA10CRDR PWGA10.CRDR
#define PWGA10CTDR PWGA10.CTDR
#define PWGA10RDT PWGA10.RDT
#define PWGA10RSF PWGA10.RSF
#define PWGA10CNT PWGA10.CNT
#define PWGA10CTL PWGA10.CTL
#define PWGA10CSBR PWGA10.CSBR
#define PWGA10CRBR PWGA10.CRBR
#define PWGA10CTBR PWGA10.CTBR
#define PWGA11CSDR PWGA11.CSDR
#define PWGA11CRDR PWGA11.CRDR
#define PWGA11CTDR PWGA11.CTDR
#define PWGA11RDT PWGA11.RDT
#define PWGA11RSF PWGA11.RSF
#define PWGA11CNT PWGA11.CNT
#define PWGA11CTL PWGA11.CTL
#define PWGA11CSBR PWGA11.CSBR
#define PWGA11CRBR PWGA11.CRBR
#define PWGA11CTBR PWGA11.CTBR
#define PWGA12CSDR PWGA12.CSDR
#define PWGA12CRDR PWGA12.CRDR
#define PWGA12CTDR PWGA12.CTDR
#define PWGA12RDT PWGA12.RDT
#define PWGA12RSF PWGA12.RSF
#define PWGA12CNT PWGA12.CNT
#define PWGA12CTL PWGA12.CTL
#define PWGA12CSBR PWGA12.CSBR
#define PWGA12CRBR PWGA12.CRBR
#define PWGA12CTBR PWGA12.CTBR
#define PWGA13CSDR PWGA13.CSDR
#define PWGA13CRDR PWGA13.CRDR
#define PWGA13CTDR PWGA13.CTDR
#define PWGA13RDT PWGA13.RDT
#define PWGA13RSF PWGA13.RSF
#define PWGA13CNT PWGA13.CNT
#define PWGA13CTL PWGA13.CTL
#define PWGA13CSBR PWGA13.CSBR
#define PWGA13CRBR PWGA13.CRBR
#define PWGA13CTBR PWGA13.CTBR
#define PWGA14CSDR PWGA14.CSDR
#define PWGA14CRDR PWGA14.CRDR
#define PWGA14CTDR PWGA14.CTDR
#define PWGA14RDT PWGA14.RDT
#define PWGA14RSF PWGA14.RSF
#define PWGA14CNT PWGA14.CNT
#define PWGA14CTL PWGA14.CTL
#define PWGA14CSBR PWGA14.CSBR
#define PWGA14CRBR PWGA14.CRBR
#define PWGA14CTBR PWGA14.CTBR
#define PWGA15CSDR PWGA15.CSDR
#define PWGA15CRDR PWGA15.CRDR
#define PWGA15CTDR PWGA15.CTDR
#define PWGA15RDT PWGA15.RDT
#define PWGA15RSF PWGA15.RSF
#define PWGA15CNT PWGA15.CNT
#define PWGA15CTL PWGA15.CTL
#define PWGA15CSBR PWGA15.CSBR
#define PWGA15CRBR PWGA15.CRBR
#define PWGA15CTBR PWGA15.CTBR
#define PWGA16CSDR PWGA16.CSDR
#define PWGA16CRDR PWGA16.CRDR
#define PWGA16CTDR PWGA16.CTDR
#define PWGA16RDT PWGA16.RDT
#define PWGA16RSF PWGA16.RSF
#define PWGA16CNT PWGA16.CNT
#define PWGA16CTL PWGA16.CTL
#define PWGA16CSBR PWGA16.CSBR
#define PWGA16CRBR PWGA16.CRBR
#define PWGA16CTBR PWGA16.CTBR
#define PWGA17CSDR PWGA17.CSDR
#define PWGA17CRDR PWGA17.CRDR
#define PWGA17CTDR PWGA17.CTDR
#define PWGA17RDT PWGA17.RDT
#define PWGA17RSF PWGA17.RSF
#define PWGA17CNT PWGA17.CNT
#define PWGA17CTL PWGA17.CTL
#define PWGA17CSBR PWGA17.CSBR
#define PWGA17CRBR PWGA17.CRBR
#define PWGA17CTBR PWGA17.CTBR
#define PWGA18CSDR PWGA18.CSDR
#define PWGA18CRDR PWGA18.CRDR
#define PWGA18CTDR PWGA18.CTDR
#define PWGA18RDT PWGA18.RDT
#define PWGA18RSF PWGA18.RSF
#define PWGA18CNT PWGA18.CNT
#define PWGA18CTL PWGA18.CTL
#define PWGA18CSBR PWGA18.CSBR
#define PWGA18CRBR PWGA18.CRBR
#define PWGA18CTBR PWGA18.CTBR
#define PWGA19CSDR PWGA19.CSDR
#define PWGA19CRDR PWGA19.CRDR
#define PWGA19CTDR PWGA19.CTDR
#define PWGA19RDT PWGA19.RDT
#define PWGA19RSF PWGA19.RSF
#define PWGA19CNT PWGA19.CNT
#define PWGA19CTL PWGA19.CTL
#define PWGA19CSBR PWGA19.CSBR
#define PWGA19CRBR PWGA19.CRBR
#define PWGA19CTBR PWGA19.CTBR
#define PWGA20CSDR PWGA20.CSDR
#define PWGA20CRDR PWGA20.CRDR
#define PWGA20CTDR PWGA20.CTDR
#define PWGA20RDT PWGA20.RDT
#define PWGA20RSF PWGA20.RSF
#define PWGA20CNT PWGA20.CNT
#define PWGA20CTL PWGA20.CTL
#define PWGA20CSBR PWGA20.CSBR
#define PWGA20CRBR PWGA20.CRBR
#define PWGA20CTBR PWGA20.CTBR
#define PWGA21CSDR PWGA21.CSDR
#define PWGA21CRDR PWGA21.CRDR
#define PWGA21CTDR PWGA21.CTDR
#define PWGA21RDT PWGA21.RDT
#define PWGA21RSF PWGA21.RSF
#define PWGA21CNT PWGA21.CNT
#define PWGA21CTL PWGA21.CTL
#define PWGA21CSBR PWGA21.CSBR
#define PWGA21CRBR PWGA21.CRBR
#define PWGA21CTBR PWGA21.CTBR
#define PWGA22CSDR PWGA22.CSDR
#define PWGA22CRDR PWGA22.CRDR
#define PWGA22CTDR PWGA22.CTDR
#define PWGA22RDT PWGA22.RDT
#define PWGA22RSF PWGA22.RSF
#define PWGA22CNT PWGA22.CNT
#define PWGA22CTL PWGA22.CTL
#define PWGA22CSBR PWGA22.CSBR
#define PWGA22CRBR PWGA22.CRBR
#define PWGA22CTBR PWGA22.CTBR
#define PWGA23CSDR PWGA23.CSDR
#define PWGA23CRDR PWGA23.CRDR
#define PWGA23CTDR PWGA23.CTDR
#define PWGA23RDT PWGA23.RDT
#define PWGA23RSF PWGA23.RSF
#define PWGA23CNT PWGA23.CNT
#define PWGA23CTL PWGA23.CTL
#define PWGA23CSBR PWGA23.CSBR
#define PWGA23CRBR PWGA23.CRBR
#define PWGA23CTBR PWGA23.CTBR
#define PWGA24CSDR PWGA24.CSDR
#define PWGA24CRDR PWGA24.CRDR
#define PWGA24CTDR PWGA24.CTDR
#define PWGA24RDT PWGA24.RDT
#define PWGA24RSF PWGA24.RSF
#define PWGA24CNT PWGA24.CNT
#define PWGA24CTL PWGA24.CTL
#define PWGA24CSBR PWGA24.CSBR
#define PWGA24CRBR PWGA24.CRBR
#define PWGA24CTBR PWGA24.CTBR
#define PWGA25CSDR PWGA25.CSDR
#define PWGA25CRDR PWGA25.CRDR
#define PWGA25CTDR PWGA25.CTDR
#define PWGA25RDT PWGA25.RDT
#define PWGA25RSF PWGA25.RSF
#define PWGA25CNT PWGA25.CNT
#define PWGA25CTL PWGA25.CTL
#define PWGA25CSBR PWGA25.CSBR
#define PWGA25CRBR PWGA25.CRBR
#define PWGA25CTBR PWGA25.CTBR
#define PWGA26CSDR PWGA26.CSDR
#define PWGA26CRDR PWGA26.CRDR
#define PWGA26CTDR PWGA26.CTDR
#define PWGA26RDT PWGA26.RDT
#define PWGA26RSF PWGA26.RSF
#define PWGA26CNT PWGA26.CNT
#define PWGA26CTL PWGA26.CTL
#define PWGA26CSBR PWGA26.CSBR
#define PWGA26CRBR PWGA26.CRBR
#define PWGA26CTBR PWGA26.CTBR
#define PWGA27CSDR PWGA27.CSDR
#define PWGA27CRDR PWGA27.CRDR
#define PWGA27CTDR PWGA27.CTDR
#define PWGA27RDT PWGA27.RDT
#define PWGA27RSF PWGA27.RSF
#define PWGA27CNT PWGA27.CNT
#define PWGA27CTL PWGA27.CTL
#define PWGA27CSBR PWGA27.CSBR
#define PWGA27CRBR PWGA27.CRBR
#define PWGA27CTBR PWGA27.CTBR
#define PWGA28CSDR PWGA28.CSDR
#define PWGA28CRDR PWGA28.CRDR
#define PWGA28CTDR PWGA28.CTDR
#define PWGA28RDT PWGA28.RDT
#define PWGA28RSF PWGA28.RSF
#define PWGA28CNT PWGA28.CNT
#define PWGA28CTL PWGA28.CTL
#define PWGA28CSBR PWGA28.CSBR
#define PWGA28CRBR PWGA28.CRBR
#define PWGA28CTBR PWGA28.CTBR
#define PWGA29CSDR PWGA29.CSDR
#define PWGA29CRDR PWGA29.CRDR
#define PWGA29CTDR PWGA29.CTDR
#define PWGA29RDT PWGA29.RDT
#define PWGA29RSF PWGA29.RSF
#define PWGA29CNT PWGA29.CNT
#define PWGA29CTL PWGA29.CTL
#define PWGA29CSBR PWGA29.CSBR
#define PWGA29CRBR PWGA29.CRBR
#define PWGA29CTBR PWGA29.CTBR
#define PWGA30CSDR PWGA30.CSDR
#define PWGA30CRDR PWGA30.CRDR
#define PWGA30CTDR PWGA30.CTDR
#define PWGA30RDT PWGA30.RDT
#define PWGA30RSF PWGA30.RSF
#define PWGA30CNT PWGA30.CNT
#define PWGA30CTL PWGA30.CTL
#define PWGA30CSBR PWGA30.CSBR
#define PWGA30CRBR PWGA30.CRBR
#define PWGA30CTBR PWGA30.CTBR
#define PWGA31CSDR PWGA31.CSDR
#define PWGA31CRDR PWGA31.CRDR
#define PWGA31CTDR PWGA31.CTDR
#define PWGA31RDT PWGA31.RDT
#define PWGA31RSF PWGA31.RSF
#define PWGA31CNT PWGA31.CNT
#define PWGA31CTL PWGA31.CTL
#define PWGA31CSBR PWGA31.CSBR
#define PWGA31CRBR PWGA31.CRBR
#define PWGA31CTBR PWGA31.CTBR
#define PWGA32CSDR PWGA32.CSDR
#define PWGA32CRDR PWGA32.CRDR
#define PWGA32CTDR PWGA32.CTDR
#define PWGA32RDT PWGA32.RDT
#define PWGA32RSF PWGA32.RSF
#define PWGA32CNT PWGA32.CNT
#define PWGA32CTL PWGA32.CTL
#define PWGA32CSBR PWGA32.CSBR
#define PWGA32CRBR PWGA32.CRBR
#define PWGA32CTBR PWGA32.CTBR
#define PWGA33CSDR PWGA33.CSDR
#define PWGA33CRDR PWGA33.CRDR
#define PWGA33CTDR PWGA33.CTDR
#define PWGA33RDT PWGA33.RDT
#define PWGA33RSF PWGA33.RSF
#define PWGA33CNT PWGA33.CNT
#define PWGA33CTL PWGA33.CTL
#define PWGA33CSBR PWGA33.CSBR
#define PWGA33CRBR PWGA33.CRBR
#define PWGA33CTBR PWGA33.CTBR
#define PWGA34CSDR PWGA34.CSDR
#define PWGA34CRDR PWGA34.CRDR
#define PWGA34CTDR PWGA34.CTDR
#define PWGA34RDT PWGA34.RDT
#define PWGA34RSF PWGA34.RSF
#define PWGA34CNT PWGA34.CNT
#define PWGA34CTL PWGA34.CTL
#define PWGA34CSBR PWGA34.CSBR
#define PWGA34CRBR PWGA34.CRBR
#define PWGA34CTBR PWGA34.CTBR
#define PWGA35CSDR PWGA35.CSDR
#define PWGA35CRDR PWGA35.CRDR
#define PWGA35CTDR PWGA35.CTDR
#define PWGA35RDT PWGA35.RDT
#define PWGA35RSF PWGA35.RSF
#define PWGA35CNT PWGA35.CNT
#define PWGA35CTL PWGA35.CTL
#define PWGA35CSBR PWGA35.CSBR
#define PWGA35CRBR PWGA35.CRBR
#define PWGA35CTBR PWGA35.CTBR
#define PWGA36CSDR PWGA36.CSDR
#define PWGA36CRDR PWGA36.CRDR
#define PWGA36CTDR PWGA36.CTDR
#define PWGA36RDT PWGA36.RDT
#define PWGA36RSF PWGA36.RSF
#define PWGA36CNT PWGA36.CNT
#define PWGA36CTL PWGA36.CTL
#define PWGA36CSBR PWGA36.CSBR
#define PWGA36CRBR PWGA36.CRBR
#define PWGA36CTBR PWGA36.CTBR
#define PWGA37CSDR PWGA37.CSDR
#define PWGA37CRDR PWGA37.CRDR
#define PWGA37CTDR PWGA37.CTDR
#define PWGA37RDT PWGA37.RDT
#define PWGA37RSF PWGA37.RSF
#define PWGA37CNT PWGA37.CNT
#define PWGA37CTL PWGA37.CTL
#define PWGA37CSBR PWGA37.CSBR
#define PWGA37CRBR PWGA37.CRBR
#define PWGA37CTBR PWGA37.CTBR
#define PWGA38CSDR PWGA38.CSDR
#define PWGA38CRDR PWGA38.CRDR
#define PWGA38CTDR PWGA38.CTDR
#define PWGA38RDT PWGA38.RDT
#define PWGA38RSF PWGA38.RSF
#define PWGA38CNT PWGA38.CNT
#define PWGA38CTL PWGA38.CTL
#define PWGA38CSBR PWGA38.CSBR
#define PWGA38CRBR PWGA38.CRBR
#define PWGA38CTBR PWGA38.CTBR
#define PWGA39CSDR PWGA39.CSDR
#define PWGA39CRDR PWGA39.CRDR
#define PWGA39CTDR PWGA39.CTDR
#define PWGA39RDT PWGA39.RDT
#define PWGA39RSF PWGA39.RSF
#define PWGA39CNT PWGA39.CNT
#define PWGA39CTL PWGA39.CTL
#define PWGA39CSBR PWGA39.CSBR
#define PWGA39CRBR PWGA39.CRBR
#define PWGA39CTBR PWGA39.CTBR
#define PWGA40CSDR PWGA40.CSDR
#define PWGA40CRDR PWGA40.CRDR
#define PWGA40CTDR PWGA40.CTDR
#define PWGA40RDT PWGA40.RDT
#define PWGA40RSF PWGA40.RSF
#define PWGA40CNT PWGA40.CNT
#define PWGA40CTL PWGA40.CTL
#define PWGA40CSBR PWGA40.CSBR
#define PWGA40CRBR PWGA40.CRBR
#define PWGA40CTBR PWGA40.CTBR
#define PWGA41CSDR PWGA41.CSDR
#define PWGA41CRDR PWGA41.CRDR
#define PWGA41CTDR PWGA41.CTDR
#define PWGA41RDT PWGA41.RDT
#define PWGA41RSF PWGA41.RSF
#define PWGA41CNT PWGA41.CNT
#define PWGA41CTL PWGA41.CTL
#define PWGA41CSBR PWGA41.CSBR
#define PWGA41CRBR PWGA41.CRBR
#define PWGA41CTBR PWGA41.CTBR
#define PWGA42CSDR PWGA42.CSDR
#define PWGA42CRDR PWGA42.CRDR
#define PWGA42CTDR PWGA42.CTDR
#define PWGA42RDT PWGA42.RDT
#define PWGA42RSF PWGA42.RSF
#define PWGA42CNT PWGA42.CNT
#define PWGA42CTL PWGA42.CTL
#define PWGA42CSBR PWGA42.CSBR
#define PWGA42CRBR PWGA42.CRBR
#define PWGA42CTBR PWGA42.CTBR
#define PWGA43CSDR PWGA43.CSDR
#define PWGA43CRDR PWGA43.CRDR
#define PWGA43CTDR PWGA43.CTDR
#define PWGA43RDT PWGA43.RDT
#define PWGA43RSF PWGA43.RSF
#define PWGA43CNT PWGA43.CNT
#define PWGA43CTL PWGA43.CTL
#define PWGA43CSBR PWGA43.CSBR
#define PWGA43CRBR PWGA43.CRBR
#define PWGA43CTBR PWGA43.CTBR
#define PWGA44CSDR PWGA44.CSDR
#define PWGA44CRDR PWGA44.CRDR
#define PWGA44CTDR PWGA44.CTDR
#define PWGA44RDT PWGA44.RDT
#define PWGA44RSF PWGA44.RSF
#define PWGA44CNT PWGA44.CNT
#define PWGA44CTL PWGA44.CTL
#define PWGA44CSBR PWGA44.CSBR
#define PWGA44CRBR PWGA44.CRBR
#define PWGA44CTBR PWGA44.CTBR
#define PWGA45CSDR PWGA45.CSDR
#define PWGA45CRDR PWGA45.CRDR
#define PWGA45CTDR PWGA45.CTDR
#define PWGA45RDT PWGA45.RDT
#define PWGA45RSF PWGA45.RSF
#define PWGA45CNT PWGA45.CNT
#define PWGA45CTL PWGA45.CTL
#define PWGA45CSBR PWGA45.CSBR
#define PWGA45CRBR PWGA45.CRBR
#define PWGA45CTBR PWGA45.CTBR
#define PWGA46CSDR PWGA46.CSDR
#define PWGA46CRDR PWGA46.CRDR
#define PWGA46CTDR PWGA46.CTDR
#define PWGA46RDT PWGA46.RDT
#define PWGA46RSF PWGA46.RSF
#define PWGA46CNT PWGA46.CNT
#define PWGA46CTL PWGA46.CTL
#define PWGA46CSBR PWGA46.CSBR
#define PWGA46CRBR PWGA46.CRBR
#define PWGA46CTBR PWGA46.CTBR
#define PWGA47CSDR PWGA47.CSDR
#define PWGA47CRDR PWGA47.CRDR
#define PWGA47CTDR PWGA47.CTDR
#define PWGA47RDT PWGA47.RDT
#define PWGA47RSF PWGA47.RSF
#define PWGA47CNT PWGA47.CNT
#define PWGA47CTL PWGA47.CTL
#define PWGA47CSBR PWGA47.CSBR
#define PWGA47CRBR PWGA47.CRBR
#define PWGA47CTBR PWGA47.CTBR
#define PWGA48CSDR PWGA48.CSDR
#define PWGA48CRDR PWGA48.CRDR
#define PWGA48CTDR PWGA48.CTDR
#define PWGA48RDT PWGA48.RDT
#define PWGA48RSF PWGA48.RSF
#define PWGA48CNT PWGA48.CNT
#define PWGA48CTL PWGA48.CTL
#define PWGA48CSBR PWGA48.CSBR
#define PWGA48CRBR PWGA48.CRBR
#define PWGA48CTBR PWGA48.CTBR
#define PWGA49CSDR PWGA49.CSDR
#define PWGA49CRDR PWGA49.CRDR
#define PWGA49CTDR PWGA49.CTDR
#define PWGA49RDT PWGA49.RDT
#define PWGA49RSF PWGA49.RSF
#define PWGA49CNT PWGA49.CNT
#define PWGA49CTL PWGA49.CTL
#define PWGA49CSBR PWGA49.CSBR
#define PWGA49CRBR PWGA49.CRBR
#define PWGA49CTBR PWGA49.CTBR
#define PWGA50CSDR PWGA50.CSDR
#define PWGA50CRDR PWGA50.CRDR
#define PWGA50CTDR PWGA50.CTDR
#define PWGA50RDT PWGA50.RDT
#define PWGA50RSF PWGA50.RSF
#define PWGA50CNT PWGA50.CNT
#define PWGA50CTL PWGA50.CTL
#define PWGA50CSBR PWGA50.CSBR
#define PWGA50CRBR PWGA50.CRBR
#define PWGA50CTBR PWGA50.CTBR
#define PWGA51CSDR PWGA51.CSDR
#define PWGA51CRDR PWGA51.CRDR
#define PWGA51CTDR PWGA51.CTDR
#define PWGA51RDT PWGA51.RDT
#define PWGA51RSF PWGA51.RSF
#define PWGA51CNT PWGA51.CNT
#define PWGA51CTL PWGA51.CTL
#define PWGA51CSBR PWGA51.CSBR
#define PWGA51CRBR PWGA51.CRBR
#define PWGA51CTBR PWGA51.CTBR
#define PWGA52CSDR PWGA52.CSDR
#define PWGA52CRDR PWGA52.CRDR
#define PWGA52CTDR PWGA52.CTDR
#define PWGA52RDT PWGA52.RDT
#define PWGA52RSF PWGA52.RSF
#define PWGA52CNT PWGA52.CNT
#define PWGA52CTL PWGA52.CTL
#define PWGA52CSBR PWGA52.CSBR
#define PWGA52CRBR PWGA52.CRBR
#define PWGA52CTBR PWGA52.CTBR
#define PWGA53CSDR PWGA53.CSDR
#define PWGA53CRDR PWGA53.CRDR
#define PWGA53CTDR PWGA53.CTDR
#define PWGA53RDT PWGA53.RDT
#define PWGA53RSF PWGA53.RSF
#define PWGA53CNT PWGA53.CNT
#define PWGA53CTL PWGA53.CTL
#define PWGA53CSBR PWGA53.CSBR
#define PWGA53CRBR PWGA53.CRBR
#define PWGA53CTBR PWGA53.CTBR
#define PWGA54CSDR PWGA54.CSDR
#define PWGA54CRDR PWGA54.CRDR
#define PWGA54CTDR PWGA54.CTDR
#define PWGA54RDT PWGA54.RDT
#define PWGA54RSF PWGA54.RSF
#define PWGA54CNT PWGA54.CNT
#define PWGA54CTL PWGA54.CTL
#define PWGA54CSBR PWGA54.CSBR
#define PWGA54CRBR PWGA54.CRBR
#define PWGA54CTBR PWGA54.CTBR
#define PWGA55CSDR PWGA55.CSDR
#define PWGA55CRDR PWGA55.CRDR
#define PWGA55CTDR PWGA55.CTDR
#define PWGA55RDT PWGA55.RDT
#define PWGA55RSF PWGA55.RSF
#define PWGA55CNT PWGA55.CNT
#define PWGA55CTL PWGA55.CTL
#define PWGA55CSBR PWGA55.CSBR
#define PWGA55CRBR PWGA55.CRBR
#define PWGA55CTBR PWGA55.CTBR
#define PWGA56CSDR PWGA56.CSDR
#define PWGA56CRDR PWGA56.CRDR
#define PWGA56CTDR PWGA56.CTDR
#define PWGA56RDT PWGA56.RDT
#define PWGA56RSF PWGA56.RSF
#define PWGA56CNT PWGA56.CNT
#define PWGA56CTL PWGA56.CTL
#define PWGA56CSBR PWGA56.CSBR
#define PWGA56CRBR PWGA56.CRBR
#define PWGA56CTBR PWGA56.CTBR
#define PWGA57CSDR PWGA57.CSDR
#define PWGA57CRDR PWGA57.CRDR
#define PWGA57CTDR PWGA57.CTDR
#define PWGA57RDT PWGA57.RDT
#define PWGA57RSF PWGA57.RSF
#define PWGA57CNT PWGA57.CNT
#define PWGA57CTL PWGA57.CTL
#define PWGA57CSBR PWGA57.CSBR
#define PWGA57CRBR PWGA57.CRBR
#define PWGA57CTBR PWGA57.CTBR
#define PWGA58CSDR PWGA58.CSDR
#define PWGA58CRDR PWGA58.CRDR
#define PWGA58CTDR PWGA58.CTDR
#define PWGA58RDT PWGA58.RDT
#define PWGA58RSF PWGA58.RSF
#define PWGA58CNT PWGA58.CNT
#define PWGA58CTL PWGA58.CTL
#define PWGA58CSBR PWGA58.CSBR
#define PWGA58CRBR PWGA58.CRBR
#define PWGA58CTBR PWGA58.CTBR
#define PWGA59CSDR PWGA59.CSDR
#define PWGA59CRDR PWGA59.CRDR
#define PWGA59CTDR PWGA59.CTDR
#define PWGA59RDT PWGA59.RDT
#define PWGA59RSF PWGA59.RSF
#define PWGA59CNT PWGA59.CNT
#define PWGA59CTL PWGA59.CTL
#define PWGA59CSBR PWGA59.CSBR
#define PWGA59CRBR PWGA59.CRBR
#define PWGA59CTBR PWGA59.CTBR
#define PWGA60CSDR PWGA60.CSDR
#define PWGA60CRDR PWGA60.CRDR
#define PWGA60CTDR PWGA60.CTDR
#define PWGA60RDT PWGA60.RDT
#define PWGA60RSF PWGA60.RSF
#define PWGA60CNT PWGA60.CNT
#define PWGA60CTL PWGA60.CTL
#define PWGA60CSBR PWGA60.CSBR
#define PWGA60CRBR PWGA60.CRBR
#define PWGA60CTBR PWGA60.CTBR
#define PWGA61CSDR PWGA61.CSDR
#define PWGA61CRDR PWGA61.CRDR
#define PWGA61CTDR PWGA61.CTDR
#define PWGA61RDT PWGA61.RDT
#define PWGA61RSF PWGA61.RSF
#define PWGA61CNT PWGA61.CNT
#define PWGA61CTL PWGA61.CTL
#define PWGA61CSBR PWGA61.CSBR
#define PWGA61CRBR PWGA61.CRBR
#define PWGA61CTBR PWGA61.CTBR
#define PWGA62CSDR PWGA62.CSDR
#define PWGA62CRDR PWGA62.CRDR
#define PWGA62CTDR PWGA62.CTDR
#define PWGA62RDT PWGA62.RDT
#define PWGA62RSF PWGA62.RSF
#define PWGA62CNT PWGA62.CNT
#define PWGA62CTL PWGA62.CTL
#define PWGA62CSBR PWGA62.CSBR
#define PWGA62CRBR PWGA62.CRBR
#define PWGA62CTBR PWGA62.CTBR
#define PWGA63CSDR PWGA63.CSDR
#define PWGA63CRDR PWGA63.CRDR
#define PWGA63CTDR PWGA63.CTDR
#define PWGA63RDT PWGA63.RDT
#define PWGA63RSF PWGA63.RSF
#define PWGA63CNT PWGA63.CNT
#define PWGA63CTL PWGA63.CTL
#define PWGA63CSBR PWGA63.CSBR
#define PWGA63CRBR PWGA63.CRBR
#define PWGA63CTBR PWGA63.CTBR
#define PWGA64CSDR PWGA64.CSDR
#define PWGA64CRDR PWGA64.CRDR
#define PWGA64CTDR PWGA64.CTDR
#define PWGA64RDT PWGA64.RDT
#define PWGA64RSF PWGA64.RSF
#define PWGA64CNT PWGA64.CNT
#define PWGA64CTL PWGA64.CTL
#define PWGA64CSBR PWGA64.CSBR
#define PWGA64CRBR PWGA64.CRBR
#define PWGA64CTBR PWGA64.CTBR
#define PWGA65CSDR PWGA65.CSDR
#define PWGA65CRDR PWGA65.CRDR
#define PWGA65CTDR PWGA65.CTDR
#define PWGA65RDT PWGA65.RDT
#define PWGA65RSF PWGA65.RSF
#define PWGA65CNT PWGA65.CNT
#define PWGA65CTL PWGA65.CTL
#define PWGA65CSBR PWGA65.CSBR
#define PWGA65CRBR PWGA65.CRBR
#define PWGA65CTBR PWGA65.CTBR
#define PWGA66CSDR PWGA66.CSDR
#define PWGA66CRDR PWGA66.CRDR
#define PWGA66CTDR PWGA66.CTDR
#define PWGA66RDT PWGA66.RDT
#define PWGA66RSF PWGA66.RSF
#define PWGA66CNT PWGA66.CNT
#define PWGA66CTL PWGA66.CTL
#define PWGA66CSBR PWGA66.CSBR
#define PWGA66CRBR PWGA66.CRBR
#define PWGA66CTBR PWGA66.CTBR
#define PWGA67CSDR PWGA67.CSDR
#define PWGA67CRDR PWGA67.CRDR
#define PWGA67CTDR PWGA67.CTDR
#define PWGA67RDT PWGA67.RDT
#define PWGA67RSF PWGA67.RSF
#define PWGA67CNT PWGA67.CNT
#define PWGA67CTL PWGA67.CTL
#define PWGA67CSBR PWGA67.CSBR
#define PWGA67CRBR PWGA67.CRBR
#define PWGA67CTBR PWGA67.CTBR
#define PWGA68CSDR PWGA68.CSDR
#define PWGA68CRDR PWGA68.CRDR
#define PWGA68CTDR PWGA68.CTDR
#define PWGA68RDT PWGA68.RDT
#define PWGA68RSF PWGA68.RSF
#define PWGA68CNT PWGA68.CNT
#define PWGA68CTL PWGA68.CTL
#define PWGA68CSBR PWGA68.CSBR
#define PWGA68CRBR PWGA68.CRBR
#define PWGA68CTBR PWGA68.CTBR
#define PWGA69CSDR PWGA69.CSDR
#define PWGA69CRDR PWGA69.CRDR
#define PWGA69CTDR PWGA69.CTDR
#define PWGA69RDT PWGA69.RDT
#define PWGA69RSF PWGA69.RSF
#define PWGA69CNT PWGA69.CNT
#define PWGA69CTL PWGA69.CTL
#define PWGA69CSBR PWGA69.CSBR
#define PWGA69CRBR PWGA69.CRBR
#define PWGA69CTBR PWGA69.CTBR
#define PWGA70CSDR PWGA70.CSDR
#define PWGA70CRDR PWGA70.CRDR
#define PWGA70CTDR PWGA70.CTDR
#define PWGA70RDT PWGA70.RDT
#define PWGA70RSF PWGA70.RSF
#define PWGA70CNT PWGA70.CNT
#define PWGA70CTL PWGA70.CTL
#define PWGA70CSBR PWGA70.CSBR
#define PWGA70CRBR PWGA70.CRBR
#define PWGA70CTBR PWGA70.CTBR
#define PWGA71CSDR PWGA71.CSDR
#define PWGA71CRDR PWGA71.CRDR
#define PWGA71CTDR PWGA71.CTDR
#define PWGA71RDT PWGA71.RDT
#define PWGA71RSF PWGA71.RSF
#define PWGA71CNT PWGA71.CNT
#define PWGA71CTL PWGA71.CTL
#define PWGA71CSBR PWGA71.CSBR
#define PWGA71CRBR PWGA71.CRBR
#define PWGA71CTBR PWGA71.CTBR
#define PWBA0BRS0 PWBA0.BRS0
#define PWBA0BRS1 PWBA0.BRS1
#define PWBA0BRS2 PWBA0.BRS2
#define PWBA0BRS3 PWBA0.BRS3
#define PWBA0TE PWBA0.TE
#define PWBA0TS PWBA0.TS
#define PWBA0TT PWBA0.TT
#define PWBA0EMU PWBA0.EMU
#define RTCA0CTL0 RTCA0.CTL0.UINT8
#define RTCA0SLSB RTCA0.CTL0.SLSB
#define RTCA0AMPM RTCA0.CTL0.AMPM
#define RTCA0CEST RTCA0.CTL0.CEST
#define RTCA0CE RTCA0.CTL0.CE
#define RTCA0CTL1 RTCA0.CTL1.UINT8
#define RTCA0CT0 RTCA0.CTL1.CT0
#define RTCA0CT1 RTCA0.CTL1.CT1
#define RTCA0CT2 RTCA0.CTL1.CT2
#define RTCA0EN1S RTCA0.CTL1.EN1S
#define RTCA0ENALM RTCA0.CTL1.ENALM
#define RTCA0EN1HZ RTCA0.CTL1.EN1HZ
#define RTCA0CTL2 RTCA0.CTL2.UINT8
#define RTCA0WAIT RTCA0.CTL2.WAIT
#define RTCA0WST RTCA0.CTL2.WST
#define RTCA0RSUB RTCA0.CTL2.RSUB
#define RTCA0RSST RTCA0.CTL2.RSST
#define RTCA0WSST RTCA0.CTL2.WSST
#define RTCA0WUST RTCA0.CTL2.WUST
#define RTCA0SUBC RTCA0.SUBC
#define RTCA0SRBU RTCA0.SRBU
#define RTCA0SEC RTCA0.SEC
#define RTCA0MIN RTCA0.MIN
#define RTCA0HOUR RTCA0.HOUR
#define RTCA0WEEK RTCA0.WEEK
#define RTCA0DAY RTCA0.DAY
#define RTCA0MONTH RTCA0.MONTH
#define RTCA0YEAR RTCA0.YEAR
#define RTCA0TIME RTCA0.TIME
#define RTCA0CAL RTCA0.CAL
#define RTCA0SUBU RTCA0.SUBU
#define RTCA0SCMP RTCA0.SCMP
#define RTCA0ALM RTCA0.ALM
#define RTCA0ALH RTCA0.ALH
#define RTCA0ALW RTCA0.ALW
#define RTCA0SECC RTCA0.SECC
#define RTCA0MINC RTCA0.MINC
#define RTCA0HOURC RTCA0.HOURC
#define RTCA0WEEKC RTCA0.WEEKC
#define RTCA0DAYC RTCA0.DAYC
#define RTCA0MONC RTCA0.MONC
#define RTCA0YEARC RTCA0.YEARC
#define RTCA0TIMEC RTCA0.TIMEC
#define RTCA0CALC RTCA0.CALC
#define RTCA0EMU RTCA0.EMU.UINT8
#define RTCA0SVSDIS RTCA0.EMU.SVSDIS
#define ENCA0CCR0 ENCA0.CCR0
#define ENCA0CCR1 ENCA0.CCR1
#define ENCA0CNT ENCA0.CNT
#define ENCA0FLG ENCA0.FLG
#define ENCA0FGC ENCA0.FGC
#define ENCA0TE ENCA0.TE
#define ENCA0TS ENCA0.TS
#define ENCA0TT ENCA0.TT
#define ENCA0IOC0 ENCA0.IOC0
#define ENCA0CTL ENCA0.CTL
#define ENCA0IOC1 ENCA0.IOC1
#define ENCA0EMU ENCA0.EMU
#define TAPA0FLG TAPA0.FLG
#define TAPA0ACWE TAPA0.ACWE
#define TAPA0ACTS TAPA0.ACTS
#define TAPA0ACTT TAPA0.ACTT
#define TAPA0OPHS TAPA0.OPHS
#define TAPA0OPHT TAPA0.OPHT
#define TAPA0CTL0 TAPA0.CTL0
#define TAPA0CTL1 TAPA0.CTL1
#define TAPA0EMU TAPA0.EMU
#define OSTM0CMP OSTM0.CMP
#define OSTM0CNT OSTM0.CNT
#define OSTM0TE OSTM0.TE
#define OSTM0TS OSTM0.TS
#define OSTM0TT OSTM0.TT
#define OSTM0CTL OSTM0.CTL
#define OSTM0EMU OSTM0.EMU
#define WDTA0WDTE WDTA0.WDTE
#define WDTA0EVAC WDTA0.EVAC
#define WDTA0REF WDTA0.REF
#define WDTA0MD WDTA0.MD
#define WDTA1WDTE WDTA1.WDTE
#define WDTA1EVAC WDTA1.EVAC
#define WDTA1REF WDTA1.REF
#define WDTA1MD WDTA1.MD
#define ADCA0VCR00 ADCA0.VCR00.UINT32
#define ADCA0VCR00L ADCA0.VCR00.UINT16[L]
#define ADCA0VCR00LL ADCA0.VCR00.UINT8[LL]
#define ADCA0VCR00LH ADCA0.VCR00.UINT8[LH]
#define ADCA0VCR01 ADCA0.VCR01.UINT32
#define ADCA0VCR01L ADCA0.VCR01.UINT16[L]
#define ADCA0VCR01LL ADCA0.VCR01.UINT8[LL]
#define ADCA0VCR01LH ADCA0.VCR01.UINT8[LH]
#define ADCA0VCR02 ADCA0.VCR02.UINT32
#define ADCA0VCR02L ADCA0.VCR02.UINT16[L]
#define ADCA0VCR02LL ADCA0.VCR02.UINT8[LL]
#define ADCA0VCR02LH ADCA0.VCR02.UINT8[LH]
#define ADCA0VCR03 ADCA0.VCR03.UINT32
#define ADCA0VCR03L ADCA0.VCR03.UINT16[L]
#define ADCA0VCR03LL ADCA0.VCR03.UINT8[LL]
#define ADCA0VCR03LH ADCA0.VCR03.UINT8[LH]
#define ADCA0VCR04 ADCA0.VCR04.UINT32
#define ADCA0VCR04L ADCA0.VCR04.UINT16[L]
#define ADCA0VCR04LL ADCA0.VCR04.UINT8[LL]
#define ADCA0VCR04LH ADCA0.VCR04.UINT8[LH]
#define ADCA0VCR05 ADCA0.VCR05.UINT32
#define ADCA0VCR05L ADCA0.VCR05.UINT16[L]
#define ADCA0VCR05LL ADCA0.VCR05.UINT8[LL]
#define ADCA0VCR05LH ADCA0.VCR05.UINT8[LH]
#define ADCA0VCR06 ADCA0.VCR06.UINT32
#define ADCA0VCR06L ADCA0.VCR06.UINT16[L]
#define ADCA0VCR06LL ADCA0.VCR06.UINT8[LL]
#define ADCA0VCR06LH ADCA0.VCR06.UINT8[LH]
#define ADCA0VCR07 ADCA0.VCR07.UINT32
#define ADCA0VCR07L ADCA0.VCR07.UINT16[L]
#define ADCA0VCR07LL ADCA0.VCR07.UINT8[LL]
#define ADCA0VCR07LH ADCA0.VCR07.UINT8[LH]
#define ADCA0VCR08 ADCA0.VCR08.UINT32
#define ADCA0VCR08L ADCA0.VCR08.UINT16[L]
#define ADCA0VCR08LL ADCA0.VCR08.UINT8[LL]
#define ADCA0VCR08LH ADCA0.VCR08.UINT8[LH]
#define ADCA0VCR09 ADCA0.VCR09.UINT32
#define ADCA0VCR09L ADCA0.VCR09.UINT16[L]
#define ADCA0VCR09LL ADCA0.VCR09.UINT8[LL]
#define ADCA0VCR09LH ADCA0.VCR09.UINT8[LH]
#define ADCA0VCR10 ADCA0.VCR10.UINT32
#define ADCA0VCR10L ADCA0.VCR10.UINT16[L]
#define ADCA0VCR10LL ADCA0.VCR10.UINT8[LL]
#define ADCA0VCR10LH ADCA0.VCR10.UINT8[LH]
#define ADCA0VCR11 ADCA0.VCR11.UINT32
#define ADCA0VCR11L ADCA0.VCR11.UINT16[L]
#define ADCA0VCR11LL ADCA0.VCR11.UINT8[LL]
#define ADCA0VCR11LH ADCA0.VCR11.UINT8[LH]
#define ADCA0VCR12 ADCA0.VCR12.UINT32
#define ADCA0VCR12L ADCA0.VCR12.UINT16[L]
#define ADCA0VCR12LL ADCA0.VCR12.UINT8[LL]
#define ADCA0VCR12LH ADCA0.VCR12.UINT8[LH]
#define ADCA0VCR13 ADCA0.VCR13.UINT32
#define ADCA0VCR13L ADCA0.VCR13.UINT16[L]
#define ADCA0VCR13LL ADCA0.VCR13.UINT8[LL]
#define ADCA0VCR13LH ADCA0.VCR13.UINT8[LH]
#define ADCA0VCR14 ADCA0.VCR14.UINT32
#define ADCA0VCR14L ADCA0.VCR14.UINT16[L]
#define ADCA0VCR14LL ADCA0.VCR14.UINT8[LL]
#define ADCA0VCR14LH ADCA0.VCR14.UINT8[LH]
#define ADCA0VCR15 ADCA0.VCR15.UINT32
#define ADCA0VCR15L ADCA0.VCR15.UINT16[L]
#define ADCA0VCR15LL ADCA0.VCR15.UINT8[LL]
#define ADCA0VCR15LH ADCA0.VCR15.UINT8[LH]
#define ADCA0VCR16 ADCA0.VCR16.UINT32
#define ADCA0VCR16L ADCA0.VCR16.UINT16[L]
#define ADCA0VCR16LL ADCA0.VCR16.UINT8[LL]
#define ADCA0VCR16LH ADCA0.VCR16.UINT8[LH]
#define ADCA0VCR17 ADCA0.VCR17.UINT32
#define ADCA0VCR17L ADCA0.VCR17.UINT16[L]
#define ADCA0VCR17LL ADCA0.VCR17.UINT8[LL]
#define ADCA0VCR17LH ADCA0.VCR17.UINT8[LH]
#define ADCA0VCR18 ADCA0.VCR18.UINT32
#define ADCA0VCR18L ADCA0.VCR18.UINT16[L]
#define ADCA0VCR18LL ADCA0.VCR18.UINT8[LL]
#define ADCA0VCR18LH ADCA0.VCR18.UINT8[LH]
#define ADCA0VCR19 ADCA0.VCR19.UINT32
#define ADCA0VCR19L ADCA0.VCR19.UINT16[L]
#define ADCA0VCR19LL ADCA0.VCR19.UINT8[LL]
#define ADCA0VCR19LH ADCA0.VCR19.UINT8[LH]
#define ADCA0VCR20 ADCA0.VCR20.UINT32
#define ADCA0VCR20L ADCA0.VCR20.UINT16[L]
#define ADCA0VCR20LL ADCA0.VCR20.UINT8[LL]
#define ADCA0VCR20LH ADCA0.VCR20.UINT8[LH]
#define ADCA0VCR21 ADCA0.VCR21.UINT32
#define ADCA0VCR21L ADCA0.VCR21.UINT16[L]
#define ADCA0VCR21LL ADCA0.VCR21.UINT8[LL]
#define ADCA0VCR21LH ADCA0.VCR21.UINT8[LH]
#define ADCA0VCR22 ADCA0.VCR22.UINT32
#define ADCA0VCR22L ADCA0.VCR22.UINT16[L]
#define ADCA0VCR22LL ADCA0.VCR22.UINT8[LL]
#define ADCA0VCR22LH ADCA0.VCR22.UINT8[LH]
#define ADCA0VCR23 ADCA0.VCR23.UINT32
#define ADCA0VCR23L ADCA0.VCR23.UINT16[L]
#define ADCA0VCR23LL ADCA0.VCR23.UINT8[LL]
#define ADCA0VCR23LH ADCA0.VCR23.UINT8[LH]
#define ADCA0VCR24 ADCA0.VCR24.UINT32
#define ADCA0VCR24L ADCA0.VCR24.UINT16[L]
#define ADCA0VCR24LL ADCA0.VCR24.UINT8[LL]
#define ADCA0VCR24LH ADCA0.VCR24.UINT8[LH]
#define ADCA0VCR25 ADCA0.VCR25.UINT32
#define ADCA0VCR25L ADCA0.VCR25.UINT16[L]
#define ADCA0VCR25LL ADCA0.VCR25.UINT8[LL]
#define ADCA0VCR25LH ADCA0.VCR25.UINT8[LH]
#define ADCA0VCR26 ADCA0.VCR26.UINT32
#define ADCA0VCR26L ADCA0.VCR26.UINT16[L]
#define ADCA0VCR26LL ADCA0.VCR26.UINT8[LL]
#define ADCA0VCR26LH ADCA0.VCR26.UINT8[LH]
#define ADCA0VCR27 ADCA0.VCR27.UINT32
#define ADCA0VCR27L ADCA0.VCR27.UINT16[L]
#define ADCA0VCR27LL ADCA0.VCR27.UINT8[LL]
#define ADCA0VCR27LH ADCA0.VCR27.UINT8[LH]
#define ADCA0VCR28 ADCA0.VCR28.UINT32
#define ADCA0VCR28L ADCA0.VCR28.UINT16[L]
#define ADCA0VCR28LL ADCA0.VCR28.UINT8[LL]
#define ADCA0VCR28LH ADCA0.VCR28.UINT8[LH]
#define ADCA0VCR29 ADCA0.VCR29.UINT32
#define ADCA0VCR29L ADCA0.VCR29.UINT16[L]
#define ADCA0VCR29LL ADCA0.VCR29.UINT8[LL]
#define ADCA0VCR29LH ADCA0.VCR29.UINT8[LH]
#define ADCA0VCR30 ADCA0.VCR30.UINT32
#define ADCA0VCR30L ADCA0.VCR30.UINT16[L]
#define ADCA0VCR30LL ADCA0.VCR30.UINT8[LL]
#define ADCA0VCR30LH ADCA0.VCR30.UINT8[LH]
#define ADCA0VCR31 ADCA0.VCR31.UINT32
#define ADCA0VCR31L ADCA0.VCR31.UINT16[L]
#define ADCA0VCR31LL ADCA0.VCR31.UINT8[LL]
#define ADCA0VCR31LH ADCA0.VCR31.UINT8[LH]
#define ADCA0VCR32 ADCA0.VCR32.UINT32
#define ADCA0VCR32L ADCA0.VCR32.UINT16[L]
#define ADCA0VCR32LL ADCA0.VCR32.UINT8[LL]
#define ADCA0VCR32LH ADCA0.VCR32.UINT8[LH]
#define ADCA0VCR33 ADCA0.VCR33.UINT32
#define ADCA0VCR33L ADCA0.VCR33.UINT16[L]
#define ADCA0VCR33LL ADCA0.VCR33.UINT8[LL]
#define ADCA0VCR33LH ADCA0.VCR33.UINT8[LH]
#define ADCA0VCR34 ADCA0.VCR34.UINT32
#define ADCA0VCR34L ADCA0.VCR34.UINT16[L]
#define ADCA0VCR34LL ADCA0.VCR34.UINT8[LL]
#define ADCA0VCR34LH ADCA0.VCR34.UINT8[LH]
#define ADCA0VCR35 ADCA0.VCR35.UINT32
#define ADCA0VCR35L ADCA0.VCR35.UINT16[L]
#define ADCA0VCR35LL ADCA0.VCR35.UINT8[LL]
#define ADCA0VCR35LH ADCA0.VCR35.UINT8[LH]
#define ADCA0VCR36 ADCA0.VCR36.UINT32
#define ADCA0VCR36L ADCA0.VCR36.UINT16[L]
#define ADCA0VCR36LL ADCA0.VCR36.UINT8[LL]
#define ADCA0VCR36LH ADCA0.VCR36.UINT8[LH]
#define ADCA0VCR37 ADCA0.VCR37.UINT32
#define ADCA0VCR37L ADCA0.VCR37.UINT16[L]
#define ADCA0VCR37LL ADCA0.VCR37.UINT8[LL]
#define ADCA0VCR37LH ADCA0.VCR37.UINT8[LH]
#define ADCA0VCR38 ADCA0.VCR38.UINT32
#define ADCA0VCR38L ADCA0.VCR38.UINT16[L]
#define ADCA0VCR38LL ADCA0.VCR38.UINT8[LL]
#define ADCA0VCR38LH ADCA0.VCR38.UINT8[LH]
#define ADCA0VCR39 ADCA0.VCR39.UINT32
#define ADCA0VCR39L ADCA0.VCR39.UINT16[L]
#define ADCA0VCR39LL ADCA0.VCR39.UINT8[LL]
#define ADCA0VCR39LH ADCA0.VCR39.UINT8[LH]
#define ADCA0VCR40 ADCA0.VCR40.UINT32
#define ADCA0VCR40L ADCA0.VCR40.UINT16[L]
#define ADCA0VCR40LL ADCA0.VCR40.UINT8[LL]
#define ADCA0VCR40LH ADCA0.VCR40.UINT8[LH]
#define ADCA0VCR41 ADCA0.VCR41.UINT32
#define ADCA0VCR41L ADCA0.VCR41.UINT16[L]
#define ADCA0VCR41LL ADCA0.VCR41.UINT8[LL]
#define ADCA0VCR41LH ADCA0.VCR41.UINT8[LH]
#define ADCA0VCR42 ADCA0.VCR42.UINT32
#define ADCA0VCR42L ADCA0.VCR42.UINT16[L]
#define ADCA0VCR42LL ADCA0.VCR42.UINT8[LL]
#define ADCA0VCR42LH ADCA0.VCR42.UINT8[LH]
#define ADCA0VCR43 ADCA0.VCR43.UINT32
#define ADCA0VCR43L ADCA0.VCR43.UINT16[L]
#define ADCA0VCR43LL ADCA0.VCR43.UINT8[LL]
#define ADCA0VCR43LH ADCA0.VCR43.UINT8[LH]
#define ADCA0VCR44 ADCA0.VCR44.UINT32
#define ADCA0VCR44L ADCA0.VCR44.UINT16[L]
#define ADCA0VCR44LL ADCA0.VCR44.UINT8[LL]
#define ADCA0VCR44LH ADCA0.VCR44.UINT8[LH]
#define ADCA0VCR45 ADCA0.VCR45.UINT32
#define ADCA0VCR45L ADCA0.VCR45.UINT16[L]
#define ADCA0VCR45LL ADCA0.VCR45.UINT8[LL]
#define ADCA0VCR45LH ADCA0.VCR45.UINT8[LH]
#define ADCA0VCR46 ADCA0.VCR46.UINT32
#define ADCA0VCR46L ADCA0.VCR46.UINT16[L]
#define ADCA0VCR46LL ADCA0.VCR46.UINT8[LL]
#define ADCA0VCR46LH ADCA0.VCR46.UINT8[LH]
#define ADCA0VCR47 ADCA0.VCR47.UINT32
#define ADCA0VCR47L ADCA0.VCR47.UINT16[L]
#define ADCA0VCR47LL ADCA0.VCR47.UINT8[LL]
#define ADCA0VCR47LH ADCA0.VCR47.UINT8[LH]
#define ADCA0VCR48 ADCA0.VCR48.UINT32
#define ADCA0VCR48L ADCA0.VCR48.UINT16[L]
#define ADCA0VCR48LL ADCA0.VCR48.UINT8[LL]
#define ADCA0VCR48LH ADCA0.VCR48.UINT8[LH]
#define ADCA0VCR49 ADCA0.VCR49.UINT32
#define ADCA0VCR49L ADCA0.VCR49.UINT16[L]
#define ADCA0VCR49LL ADCA0.VCR49.UINT8[LL]
#define ADCA0VCR49LH ADCA0.VCR49.UINT8[LH]
#define ADCA0PWDVCR ADCA0.PWDVCR.UINT32
#define ADCA0PWDVCRL ADCA0.PWDVCR.UINT16[L]
#define ADCA0PWDVCRLL ADCA0.PWDVCR.UINT8[LL]
#define ADCA0PWDVCRLH ADCA0.PWDVCR.UINT8[LH]
#define ADCA0DR00 ADCA0.DR00.UINT32
#define ADCA0DR00L ADCA0.DR00.UINT16[L]
#define ADCA0DR00H ADCA0.DR00.UINT16[H]
#define ADCA0DR02 ADCA0.DR02.UINT32
#define ADCA0DR02L ADCA0.DR02.UINT16[L]
#define ADCA0DR02H ADCA0.DR02.UINT16[H]
#define ADCA0DR04 ADCA0.DR04.UINT32
#define ADCA0DR04L ADCA0.DR04.UINT16[L]
#define ADCA0DR04H ADCA0.DR04.UINT16[H]
#define ADCA0DR06 ADCA0.DR06.UINT32
#define ADCA0DR06L ADCA0.DR06.UINT16[L]
#define ADCA0DR06H ADCA0.DR06.UINT16[H]
#define ADCA0DR08 ADCA0.DR08.UINT32
#define ADCA0DR08L ADCA0.DR08.UINT16[L]
#define ADCA0DR08H ADCA0.DR08.UINT16[H]
#define ADCA0DR10 ADCA0.DR10.UINT32
#define ADCA0DR10L ADCA0.DR10.UINT16[L]
#define ADCA0DR10H ADCA0.DR10.UINT16[H]
#define ADCA0DR12 ADCA0.DR12.UINT32
#define ADCA0DR12L ADCA0.DR12.UINT16[L]
#define ADCA0DR12H ADCA0.DR12.UINT16[H]
#define ADCA0DR14 ADCA0.DR14.UINT32
#define ADCA0DR14L ADCA0.DR14.UINT16[L]
#define ADCA0DR14H ADCA0.DR14.UINT16[H]
#define ADCA0DR16 ADCA0.DR16.UINT32
#define ADCA0DR16L ADCA0.DR16.UINT16[L]
#define ADCA0DR16H ADCA0.DR16.UINT16[H]
#define ADCA0DR18 ADCA0.DR18.UINT32
#define ADCA0DR18L ADCA0.DR18.UINT16[L]
#define ADCA0DR18H ADCA0.DR18.UINT16[H]
#define ADCA0DR20 ADCA0.DR20.UINT32
#define ADCA0DR20L ADCA0.DR20.UINT16[L]
#define ADCA0DR20H ADCA0.DR20.UINT16[H]
#define ADCA0DR22 ADCA0.DR22.UINT32
#define ADCA0DR22L ADCA0.DR22.UINT16[L]
#define ADCA0DR22H ADCA0.DR22.UINT16[H]
#define ADCA0DR24 ADCA0.DR24.UINT32
#define ADCA0DR24L ADCA0.DR24.UINT16[L]
#define ADCA0DR24H ADCA0.DR24.UINT16[H]
#define ADCA0DR26 ADCA0.DR26.UINT32
#define ADCA0DR26L ADCA0.DR26.UINT16[L]
#define ADCA0DR26H ADCA0.DR26.UINT16[H]
#define ADCA0DR28 ADCA0.DR28.UINT32
#define ADCA0DR28L ADCA0.DR28.UINT16[L]
#define ADCA0DR28H ADCA0.DR28.UINT16[H]
#define ADCA0DR30 ADCA0.DR30.UINT32
#define ADCA0DR30L ADCA0.DR30.UINT16[L]
#define ADCA0DR30H ADCA0.DR30.UINT16[H]
#define ADCA0DR32 ADCA0.DR32.UINT32
#define ADCA0DR32L ADCA0.DR32.UINT16[L]
#define ADCA0DR32H ADCA0.DR32.UINT16[H]
#define ADCA0DR34 ADCA0.DR34.UINT32
#define ADCA0DR34L ADCA0.DR34.UINT16[L]
#define ADCA0DR34H ADCA0.DR34.UINT16[H]
#define ADCA0DR36 ADCA0.DR36.UINT32
#define ADCA0DR36L ADCA0.DR36.UINT16[L]
#define ADCA0DR36H ADCA0.DR36.UINT16[H]
#define ADCA0DR38 ADCA0.DR38.UINT32
#define ADCA0DR38L ADCA0.DR38.UINT16[L]
#define ADCA0DR38H ADCA0.DR38.UINT16[H]
#define ADCA0DR40 ADCA0.DR40.UINT32
#define ADCA0DR40L ADCA0.DR40.UINT16[L]
#define ADCA0DR40H ADCA0.DR40.UINT16[H]
#define ADCA0DR42 ADCA0.DR42.UINT32
#define ADCA0DR42L ADCA0.DR42.UINT16[L]
#define ADCA0DR42H ADCA0.DR42.UINT16[H]
#define ADCA0DR44 ADCA0.DR44.UINT32
#define ADCA0DR44L ADCA0.DR44.UINT16[L]
#define ADCA0DR44H ADCA0.DR44.UINT16[H]
#define ADCA0DR46 ADCA0.DR46.UINT32
#define ADCA0DR46L ADCA0.DR46.UINT16[L]
#define ADCA0DR46H ADCA0.DR46.UINT16[H]
#define ADCA0DR48 ADCA0.DR48.UINT32
#define ADCA0DR48L ADCA0.DR48.UINT16[L]
#define ADCA0DR48H ADCA0.DR48.UINT16[H]
#define ADCA0PWDTSNDR ADCA0.PWDTSNDR.UINT32
#define ADCA0PWDTSNDRH ADCA0.PWDTSNDR.UINT16[H]
#define ADCA0DIR00 ADCA0.DIR00
#define ADCA0DIR01 ADCA0.DIR01
#define ADCA0DIR02 ADCA0.DIR02
#define ADCA0DIR03 ADCA0.DIR03
#define ADCA0DIR04 ADCA0.DIR04
#define ADCA0DIR05 ADCA0.DIR05
#define ADCA0DIR06 ADCA0.DIR06
#define ADCA0DIR07 ADCA0.DIR07
#define ADCA0DIR08 ADCA0.DIR08
#define ADCA0DIR09 ADCA0.DIR09
#define ADCA0DIR10 ADCA0.DIR10
#define ADCA0DIR11 ADCA0.DIR11
#define ADCA0DIR12 ADCA0.DIR12
#define ADCA0DIR13 ADCA0.DIR13
#define ADCA0DIR14 ADCA0.DIR14
#define ADCA0DIR15 ADCA0.DIR15
#define ADCA0DIR16 ADCA0.DIR16
#define ADCA0DIR17 ADCA0.DIR17
#define ADCA0DIR18 ADCA0.DIR18
#define ADCA0DIR19 ADCA0.DIR19
#define ADCA0DIR20 ADCA0.DIR20
#define ADCA0DIR21 ADCA0.DIR21
#define ADCA0DIR22 ADCA0.DIR22
#define ADCA0DIR23 ADCA0.DIR23
#define ADCA0DIR24 ADCA0.DIR24
#define ADCA0DIR25 ADCA0.DIR25
#define ADCA0DIR26 ADCA0.DIR26
#define ADCA0DIR27 ADCA0.DIR27
#define ADCA0DIR28 ADCA0.DIR28
#define ADCA0DIR29 ADCA0.DIR29
#define ADCA0DIR30 ADCA0.DIR30
#define ADCA0DIR31 ADCA0.DIR31
#define ADCA0DIR32 ADCA0.DIR32
#define ADCA0DIR33 ADCA0.DIR33
#define ADCA0DIR34 ADCA0.DIR34
#define ADCA0DIR35 ADCA0.DIR35
#define ADCA0DIR36 ADCA0.DIR36
#define ADCA0DIR37 ADCA0.DIR37
#define ADCA0DIR38 ADCA0.DIR38
#define ADCA0DIR39 ADCA0.DIR39
#define ADCA0DIR40 ADCA0.DIR40
#define ADCA0DIR41 ADCA0.DIR41
#define ADCA0DIR42 ADCA0.DIR42
#define ADCA0DIR43 ADCA0.DIR43
#define ADCA0DIR44 ADCA0.DIR44
#define ADCA0DIR45 ADCA0.DIR45
#define ADCA0DIR46 ADCA0.DIR46
#define ADCA0DIR47 ADCA0.DIR47
#define ADCA0DIR48 ADCA0.DIR48
#define ADCA0DIR49 ADCA0.DIR49
#define ADCA0PWDDIR ADCA0.PWDDIR
#define ADCA0ADHALTR ADCA0.ADHALTR.UINT32
#define ADCA0ADHALTRL ADCA0.ADHALTR.UINT16[L]
#define ADCA0ADHALTRLL ADCA0.ADHALTR.UINT8[LL]
#define ADCA0ADCR ADCA0.ADCR.UINT32
#define ADCA0ADCRL ADCA0.ADCR.UINT16[L]
#define ADCA0ADCRLL ADCA0.ADCR.UINT8[LL]
#define ADCA0SGSTR ADCA0.SGSTR.UINT32
#define ADCA0SGSTRL ADCA0.SGSTR.UINT16[L]
#define ADCA0MPXCURR ADCA0.MPXCURR.UINT32
#define ADCA0MPXCURRL ADCA0.MPXCURR.UINT16[L]
#define ADCA0MPXCURRLL ADCA0.MPXCURR.UINT8[LL]
#define ADCA0THSMPSTCR ADCA0.THSMPSTCR.UINT32
#define ADCA0THSMPSTCRL ADCA0.THSMPSTCR.UINT16[L]
#define ADCA0THSMPSTCRLL ADCA0.THSMPSTCR.UINT8[LL]
#define ADCA0THCR ADCA0.THCR.UINT32
#define ADCA0THCRL ADCA0.THCR.UINT16[L]
#define ADCA0THCRLL ADCA0.THCR.UINT8[LL]
#define ADCA0THAHLDSTCR ADCA0.THAHLDSTCR.UINT32
#define ADCA0THAHLDSTCRL ADCA0.THAHLDSTCR.UINT16[L]
#define ADCA0THAHLDSTCRLL ADCA0.THAHLDSTCR.UINT8[LL]
#define ADCA0THBHLDSTCR ADCA0.THBHLDSTCR.UINT32
#define ADCA0THBHLDSTCRL ADCA0.THBHLDSTCR.UINT16[L]
#define ADCA0THBHLDSTCRLL ADCA0.THBHLDSTCR.UINT8[LL]
#define ADCA0THACR ADCA0.THACR.UINT32
#define ADCA0THACRL ADCA0.THACR.UINT16[L]
#define ADCA0THACRLL ADCA0.THACR.UINT8[LL]
#define ADCA0THBCR ADCA0.THBCR.UINT32
#define ADCA0THBCRL ADCA0.THBCR.UINT16[L]
#define ADCA0THBCRLL ADCA0.THBCR.UINT8[LL]
#define ADCA0THER ADCA0.THER.UINT32
#define ADCA0THERL ADCA0.THER.UINT16[L]
#define ADCA0THERLL ADCA0.THER.UINT8[LL]
#define ADCA0THGSR ADCA0.THGSR.UINT32
#define ADCA0THGSRL ADCA0.THGSR.UINT16[L]
#define ADCA0THGSRLL ADCA0.THGSR.UINT8[LL]
#define ADCA0SFTCR ADCA0.SFTCR.UINT32
#define ADCA0SFTCRL ADCA0.SFTCR.UINT16[L]
#define ADCA0SFTCRLL ADCA0.SFTCR.UINT8[LL]
#define ADCA0ULLMTBR0 ADCA0.ULLMTBR0.UINT32
#define ADCA0ULLMTBR0L ADCA0.ULLMTBR0.UINT16[L]
#define ADCA0ULLMTBR0H ADCA0.ULLMTBR0.UINT16[H]
#define ADCA0ULLMTBR1 ADCA0.ULLMTBR1.UINT32
#define ADCA0ULLMTBR1L ADCA0.ULLMTBR1.UINT16[L]
#define ADCA0ULLMTBR1H ADCA0.ULLMTBR1.UINT16[H]
#define ADCA0ULLMTBR2 ADCA0.ULLMTBR2.UINT32
#define ADCA0ULLMTBR2L ADCA0.ULLMTBR2.UINT16[L]
#define ADCA0ULLMTBR2H ADCA0.ULLMTBR2.UINT16[H]
#define ADCA0ECR ADCA0.ECR.UINT32
#define ADCA0ECRL ADCA0.ECR.UINT16[L]
#define ADCA0ECRLL ADCA0.ECR.UINT8[LL]
#define ADCA0ULER ADCA0.ULER.UINT32
#define ADCA0ULERL ADCA0.ULER.UINT16[L]
#define ADCA0ULERLL ADCA0.ULER.UINT8[LL]
#define ADCA0ULERLH ADCA0.ULER.UINT8[LH]
#define ADCA0OWER ADCA0.OWER.UINT32
#define ADCA0OWERL ADCA0.OWER.UINT16[L]
#define ADCA0OWERLL ADCA0.OWER.UINT8[LL]
#define ADCA0DGCTL0 ADCA0.DGCTL0.UINT32
#define ADCA0DGCTL0L ADCA0.DGCTL0.UINT16[L]
#define ADCA0DGCTL0LL ADCA0.DGCTL0.UINT8[LL]
#define ADCA0DGCTL1 ADCA0.DGCTL1.UINT32
#define ADCA0DGCTL1L ADCA0.DGCTL1.UINT16[L]
#define ADCA0PDCTL1 ADCA0.PDCTL1.UINT32
#define ADCA0PDCTL1L ADCA0.PDCTL1.UINT16[L]
#define ADCA0PDCTL2 ADCA0.PDCTL2.UINT32
#define ADCA0PDCTL2L ADCA0.PDCTL2.UINT16[L]
#define ADCA0PDCTL2LL ADCA0.PDCTL2.UINT8[LL]
#define ADCA0PDCTL2LH ADCA0.PDCTL2.UINT8[LH]
#define ADCA0PDCTL2H ADCA0.PDCTL2.UINT16[H]
#define ADCA0PDCTL2HL ADCA0.PDCTL2.UINT8[HL]
#define ADCA0SMPCR ADCA0.SMPCR.UINT32
#define ADCA0SMPCRL ADCA0.SMPCR.UINT16[L]
#define ADCA0SMPCRLL ADCA0.SMPCR.UINT8[LL]
#define ADCA0EMU ADCA0.EMU
#define ADCA0SGSTCR1 ADCA0.SGSTCR1.UINT32
#define ADCA0SGSTCR1L ADCA0.SGSTCR1.UINT16[L]
#define ADCA0SGSTCR1LL ADCA0.SGSTCR1.UINT8[LL]
#define ADCA0SGCR1 ADCA0.SGCR1.UINT32
#define ADCA0SGCR1L ADCA0.SGCR1.UINT16[L]
#define ADCA0SGCR1LL ADCA0.SGCR1.UINT8[LL]
#define ADCA0SGVCSP1 ADCA0.SGVCSP1.UINT32
#define ADCA0SGVCSP1L ADCA0.SGVCSP1.UINT16[L]
#define ADCA0SGVCSP1LL ADCA0.SGVCSP1.UINT8[LL]
#define ADCA0SGVCEP1 ADCA0.SGVCEP1.UINT32
#define ADCA0SGVCEP1L ADCA0.SGVCEP1.UINT16[L]
#define ADCA0SGVCEP1LL ADCA0.SGVCEP1.UINT8[LL]
#define ADCA0SGMCYCR1 ADCA0.SGMCYCR1.UINT32
#define ADCA0SGMCYCR1L ADCA0.SGMCYCR1.UINT16[L]
#define ADCA0SGMCYCR1LL ADCA0.SGMCYCR1.UINT8[LL]
#define ADCA0SGSEFCR1 ADCA0.SGSEFCR1.UINT32
#define ADCA0SGSEFCR1L ADCA0.SGSEFCR1.UINT16[L]
#define ADCA0SGSEFCR1LL ADCA0.SGSEFCR1.UINT8[LL]
#define ADCA0SGTSEL1 ADCA0.SGTSEL1.UINT32
#define ADCA0SGTSEL1L ADCA0.SGTSEL1.UINT16[L]
#define ADCA0SGSTCR2 ADCA0.SGSTCR2.UINT32
#define ADCA0SGSTCR2L ADCA0.SGSTCR2.UINT16[L]
#define ADCA0SGSTCR2LL ADCA0.SGSTCR2.UINT8[LL]
#define ADCA0SGCR2 ADCA0.SGCR2.UINT32
#define ADCA0SGCR2L ADCA0.SGCR2.UINT16[L]
#define ADCA0SGCR2LL ADCA0.SGCR2.UINT8[LL]
#define ADCA0SGVCSP2 ADCA0.SGVCSP2.UINT32
#define ADCA0SGVCSP2L ADCA0.SGVCSP2.UINT16[L]
#define ADCA0SGVCSP2LL ADCA0.SGVCSP2.UINT8[LL]
#define ADCA0SGVCEP2 ADCA0.SGVCEP2.UINT32
#define ADCA0SGVCEP2L ADCA0.SGVCEP2.UINT16[L]
#define ADCA0SGVCEP2LL ADCA0.SGVCEP2.UINT8[LL]
#define ADCA0SGMCYCR2 ADCA0.SGMCYCR2.UINT32
#define ADCA0SGMCYCR2L ADCA0.SGMCYCR2.UINT16[L]
#define ADCA0SGMCYCR2LL ADCA0.SGMCYCR2.UINT8[LL]
#define ADCA0SGSEFCR2 ADCA0.SGSEFCR2.UINT32
#define ADCA0SGSEFCR2L ADCA0.SGSEFCR2.UINT16[L]
#define ADCA0SGSEFCR2LL ADCA0.SGSEFCR2.UINT8[LL]
#define ADCA0SGTSEL2 ADCA0.SGTSEL2.UINT32
#define ADCA0SGTSEL2L ADCA0.SGTSEL2.UINT16[L]
#define ADCA0SGSTCR3 ADCA0.SGSTCR3.UINT32
#define ADCA0SGSTCR3L ADCA0.SGSTCR3.UINT16[L]
#define ADCA0SGSTCR3LL ADCA0.SGSTCR3.UINT8[LL]
#define ADCA0SGCR3 ADCA0.SGCR3.UINT32
#define ADCA0SGCR3L ADCA0.SGCR3.UINT16[L]
#define ADCA0SGCR3LL ADCA0.SGCR3.UINT8[LL]
#define ADCA0SGVCSP3 ADCA0.SGVCSP3.UINT32
#define ADCA0SGVCSP3L ADCA0.SGVCSP3.UINT16[L]
#define ADCA0SGVCSP3LL ADCA0.SGVCSP3.UINT8[LL]
#define ADCA0SGVCEP3 ADCA0.SGVCEP3.UINT32
#define ADCA0SGVCEP3L ADCA0.SGVCEP3.UINT16[L]
#define ADCA0SGVCEP3LL ADCA0.SGVCEP3.UINT8[LL]
#define ADCA0SGMCYCR3 ADCA0.SGMCYCR3.UINT32
#define ADCA0SGMCYCR3L ADCA0.SGMCYCR3.UINT16[L]
#define ADCA0SGMCYCR3LL ADCA0.SGMCYCR3.UINT8[LL]
#define ADCA0SGSEFCR3 ADCA0.SGSEFCR3.UINT32
#define ADCA0SGSEFCR3L ADCA0.SGSEFCR3.UINT16[L]
#define ADCA0SGSEFCR3LL ADCA0.SGSEFCR3.UINT8[LL]
#define ADCA0SGTSEL3 ADCA0.SGTSEL3.UINT32
#define ADCA0SGTSEL3L ADCA0.SGTSEL3.UINT16[L]
#define ADCA0PWDSGCR ADCA0.PWDSGCR.UINT32
#define ADCA0PWDSGCRL ADCA0.PWDSGCR.UINT16[L]
#define ADCA0PWDSGCRLL ADCA0.PWDSGCR.UINT8[LL]
#define ADCA0PWDSGSEFCR ADCA0.PWDSGSEFCR.UINT32
#define ADCA0PWDSGSEFCRL ADCA0.PWDSGSEFCR.UINT16[L]
#define ADCA0PWDSGSEFCRLL ADCA0.PWDSGSEFCR.UINT8[LL]
#define ADCA1VCR00 ADCA1.VCR00.UINT32
#define ADCA1VCR00L ADCA1.VCR00.UINT16[L]
#define ADCA1VCR00LL ADCA1.VCR00.UINT8[LL]
#define ADCA1VCR00LH ADCA1.VCR00.UINT8[LH]
#define ADCA1VCR01 ADCA1.VCR01.UINT32
#define ADCA1VCR01L ADCA1.VCR01.UINT16[L]
#define ADCA1VCR01LL ADCA1.VCR01.UINT8[LL]
#define ADCA1VCR01LH ADCA1.VCR01.UINT8[LH]
#define ADCA1VCR02 ADCA1.VCR02.UINT32
#define ADCA1VCR02L ADCA1.VCR02.UINT16[L]
#define ADCA1VCR02LL ADCA1.VCR02.UINT8[LL]
#define ADCA1VCR02LH ADCA1.VCR02.UINT8[LH]
#define ADCA1VCR03 ADCA1.VCR03.UINT32
#define ADCA1VCR03L ADCA1.VCR03.UINT16[L]
#define ADCA1VCR03LL ADCA1.VCR03.UINT8[LL]
#define ADCA1VCR03LH ADCA1.VCR03.UINT8[LH]
#define ADCA1VCR04 ADCA1.VCR04.UINT32
#define ADCA1VCR04L ADCA1.VCR04.UINT16[L]
#define ADCA1VCR04LL ADCA1.VCR04.UINT8[LL]
#define ADCA1VCR04LH ADCA1.VCR04.UINT8[LH]
#define ADCA1VCR05 ADCA1.VCR05.UINT32
#define ADCA1VCR05L ADCA1.VCR05.UINT16[L]
#define ADCA1VCR05LL ADCA1.VCR05.UINT8[LL]
#define ADCA1VCR05LH ADCA1.VCR05.UINT8[LH]
#define ADCA1VCR06 ADCA1.VCR06.UINT32
#define ADCA1VCR06L ADCA1.VCR06.UINT16[L]
#define ADCA1VCR06LL ADCA1.VCR06.UINT8[LL]
#define ADCA1VCR06LH ADCA1.VCR06.UINT8[LH]
#define ADCA1VCR07 ADCA1.VCR07.UINT32
#define ADCA1VCR07L ADCA1.VCR07.UINT16[L]
#define ADCA1VCR07LL ADCA1.VCR07.UINT8[LL]
#define ADCA1VCR07LH ADCA1.VCR07.UINT8[LH]
#define ADCA1VCR08 ADCA1.VCR08.UINT32
#define ADCA1VCR08L ADCA1.VCR08.UINT16[L]
#define ADCA1VCR08LL ADCA1.VCR08.UINT8[LL]
#define ADCA1VCR08LH ADCA1.VCR08.UINT8[LH]
#define ADCA1VCR09 ADCA1.VCR09.UINT32
#define ADCA1VCR09L ADCA1.VCR09.UINT16[L]
#define ADCA1VCR09LL ADCA1.VCR09.UINT8[LL]
#define ADCA1VCR09LH ADCA1.VCR09.UINT8[LH]
#define ADCA1VCR10 ADCA1.VCR10.UINT32
#define ADCA1VCR10L ADCA1.VCR10.UINT16[L]
#define ADCA1VCR10LL ADCA1.VCR10.UINT8[LL]
#define ADCA1VCR10LH ADCA1.VCR10.UINT8[LH]
#define ADCA1VCR11 ADCA1.VCR11.UINT32
#define ADCA1VCR11L ADCA1.VCR11.UINT16[L]
#define ADCA1VCR11LL ADCA1.VCR11.UINT8[LL]
#define ADCA1VCR11LH ADCA1.VCR11.UINT8[LH]
#define ADCA1VCR12 ADCA1.VCR12.UINT32
#define ADCA1VCR12L ADCA1.VCR12.UINT16[L]
#define ADCA1VCR12LL ADCA1.VCR12.UINT8[LL]
#define ADCA1VCR12LH ADCA1.VCR12.UINT8[LH]
#define ADCA1VCR13 ADCA1.VCR13.UINT32
#define ADCA1VCR13L ADCA1.VCR13.UINT16[L]
#define ADCA1VCR13LL ADCA1.VCR13.UINT8[LL]
#define ADCA1VCR13LH ADCA1.VCR13.UINT8[LH]
#define ADCA1VCR14 ADCA1.VCR14.UINT32
#define ADCA1VCR14L ADCA1.VCR14.UINT16[L]
#define ADCA1VCR14LL ADCA1.VCR14.UINT8[LL]
#define ADCA1VCR14LH ADCA1.VCR14.UINT8[LH]
#define ADCA1VCR15 ADCA1.VCR15.UINT32
#define ADCA1VCR15L ADCA1.VCR15.UINT16[L]
#define ADCA1VCR15LL ADCA1.VCR15.UINT8[LL]
#define ADCA1VCR15LH ADCA1.VCR15.UINT8[LH]
#define ADCA1VCR16 ADCA1.VCR16.UINT32
#define ADCA1VCR16L ADCA1.VCR16.UINT16[L]
#define ADCA1VCR16LL ADCA1.VCR16.UINT8[LL]
#define ADCA1VCR16LH ADCA1.VCR16.UINT8[LH]
#define ADCA1VCR17 ADCA1.VCR17.UINT32
#define ADCA1VCR17L ADCA1.VCR17.UINT16[L]
#define ADCA1VCR17LL ADCA1.VCR17.UINT8[LL]
#define ADCA1VCR17LH ADCA1.VCR17.UINT8[LH]
#define ADCA1VCR18 ADCA1.VCR18.UINT32
#define ADCA1VCR18L ADCA1.VCR18.UINT16[L]
#define ADCA1VCR18LL ADCA1.VCR18.UINT8[LL]
#define ADCA1VCR18LH ADCA1.VCR18.UINT8[LH]
#define ADCA1VCR19 ADCA1.VCR19.UINT32
#define ADCA1VCR19L ADCA1.VCR19.UINT16[L]
#define ADCA1VCR19LL ADCA1.VCR19.UINT8[LL]
#define ADCA1VCR19LH ADCA1.VCR19.UINT8[LH]
#define ADCA1VCR20 ADCA1.VCR20.UINT32
#define ADCA1VCR20L ADCA1.VCR20.UINT16[L]
#define ADCA1VCR20LL ADCA1.VCR20.UINT8[LL]
#define ADCA1VCR20LH ADCA1.VCR20.UINT8[LH]
#define ADCA1VCR21 ADCA1.VCR21.UINT32
#define ADCA1VCR21L ADCA1.VCR21.UINT16[L]
#define ADCA1VCR21LL ADCA1.VCR21.UINT8[LL]
#define ADCA1VCR21LH ADCA1.VCR21.UINT8[LH]
#define ADCA1VCR22 ADCA1.VCR22.UINT32
#define ADCA1VCR22L ADCA1.VCR22.UINT16[L]
#define ADCA1VCR22LL ADCA1.VCR22.UINT8[LL]
#define ADCA1VCR22LH ADCA1.VCR22.UINT8[LH]
#define ADCA1VCR23 ADCA1.VCR23.UINT32
#define ADCA1VCR23L ADCA1.VCR23.UINT16[L]
#define ADCA1VCR23LL ADCA1.VCR23.UINT8[LL]
#define ADCA1VCR23LH ADCA1.VCR23.UINT8[LH]
#define ADCA1PWDVCR ADCA1.PWDVCR.UINT32
#define ADCA1PWDVCRL ADCA1.PWDVCR.UINT16[L]
#define ADCA1PWDVCRLL ADCA1.PWDVCR.UINT8[LL]
#define ADCA1PWDVCRLH ADCA1.PWDVCR.UINT8[LH]
#define ADCA1DR00 ADCA1.DR00.UINT32
#define ADCA1DR00L ADCA1.DR00.UINT16[L]
#define ADCA1DR00H ADCA1.DR00.UINT16[H]
#define ADCA1DR02 ADCA1.DR02.UINT32
#define ADCA1DR02L ADCA1.DR02.UINT16[L]
#define ADCA1DR02H ADCA1.DR02.UINT16[H]
#define ADCA1DR04 ADCA1.DR04.UINT32
#define ADCA1DR04L ADCA1.DR04.UINT16[L]
#define ADCA1DR04H ADCA1.DR04.UINT16[H]
#define ADCA1DR06 ADCA1.DR06.UINT32
#define ADCA1DR06L ADCA1.DR06.UINT16[L]
#define ADCA1DR06H ADCA1.DR06.UINT16[H]
#define ADCA1DR08 ADCA1.DR08.UINT32
#define ADCA1DR08L ADCA1.DR08.UINT16[L]
#define ADCA1DR08H ADCA1.DR08.UINT16[H]
#define ADCA1DR10 ADCA1.DR10.UINT32
#define ADCA1DR10L ADCA1.DR10.UINT16[L]
#define ADCA1DR10H ADCA1.DR10.UINT16[H]
#define ADCA1DR12 ADCA1.DR12.UINT32
#define ADCA1DR12L ADCA1.DR12.UINT16[L]
#define ADCA1DR12H ADCA1.DR12.UINT16[H]
#define ADCA1DR14 ADCA1.DR14.UINT32
#define ADCA1DR14L ADCA1.DR14.UINT16[L]
#define ADCA1DR14H ADCA1.DR14.UINT16[H]
#define ADCA1DR16 ADCA1.DR16.UINT32
#define ADCA1DR16L ADCA1.DR16.UINT16[L]
#define ADCA1DR16H ADCA1.DR16.UINT16[H]
#define ADCA1DR18 ADCA1.DR18.UINT32
#define ADCA1DR18L ADCA1.DR18.UINT16[L]
#define ADCA1DR18H ADCA1.DR18.UINT16[H]
#define ADCA1DR20 ADCA1.DR20.UINT32
#define ADCA1DR20L ADCA1.DR20.UINT16[L]
#define ADCA1DR20H ADCA1.DR20.UINT16[H]
#define ADCA1DR22 ADCA1.DR22.UINT32
#define ADCA1DR22L ADCA1.DR22.UINT16[L]
#define ADCA1DR22H ADCA1.DR22.UINT16[H]
#define ADCA1PWDTSNDR ADCA1.PWDTSNDR.UINT32
#define ADCA1PWDTSNDRH ADCA1.PWDTSNDR.UINT16[H]
#define ADCA1DIR00 ADCA1.DIR00
#define ADCA1DIR01 ADCA1.DIR01
#define ADCA1DIR02 ADCA1.DIR02
#define ADCA1DIR03 ADCA1.DIR03
#define ADCA1DIR04 ADCA1.DIR04
#define ADCA1DIR05 ADCA1.DIR05
#define ADCA1DIR06 ADCA1.DIR06
#define ADCA1DIR07 ADCA1.DIR07
#define ADCA1DIR08 ADCA1.DIR08
#define ADCA1DIR09 ADCA1.DIR09
#define ADCA1DIR10 ADCA1.DIR10
#define ADCA1DIR11 ADCA1.DIR11
#define ADCA1DIR12 ADCA1.DIR12
#define ADCA1DIR13 ADCA1.DIR13
#define ADCA1DIR14 ADCA1.DIR14
#define ADCA1DIR15 ADCA1.DIR15
#define ADCA1DIR16 ADCA1.DIR16
#define ADCA1DIR17 ADCA1.DIR17
#define ADCA1DIR18 ADCA1.DIR18
#define ADCA1DIR19 ADCA1.DIR19
#define ADCA1DIR20 ADCA1.DIR20
#define ADCA1DIR21 ADCA1.DIR21
#define ADCA1DIR22 ADCA1.DIR22
#define ADCA1DIR23 ADCA1.DIR23
#define ADCA1PWDDIR ADCA1.PWDDIR
#define ADCA1ADHALTR ADCA1.ADHALTR.UINT32
#define ADCA1ADHALTRL ADCA1.ADHALTR.UINT16[L]
#define ADCA1ADHALTRLL ADCA1.ADHALTR.UINT8[LL]
#define ADCA1ADCR ADCA1.ADCR.UINT32
#define ADCA1ADCRL ADCA1.ADCR.UINT16[L]
#define ADCA1ADCRLL ADCA1.ADCR.UINT8[LL]
#define ADCA1SGSTR ADCA1.SGSTR.UINT32
#define ADCA1SGSTRL ADCA1.SGSTR.UINT16[L]
#define ADCA1SFTCR ADCA1.SFTCR.UINT32
#define ADCA1SFTCRL ADCA1.SFTCR.UINT16[L]
#define ADCA1SFTCRLL ADCA1.SFTCR.UINT8[LL]
#define ADCA1ULLMTBR0 ADCA1.ULLMTBR0.UINT32
#define ADCA1ULLMTBR0L ADCA1.ULLMTBR0.UINT16[L]
#define ADCA1ULLMTBR0H ADCA1.ULLMTBR0.UINT16[H]
#define ADCA1ULLMTBR1 ADCA1.ULLMTBR1.UINT32
#define ADCA1ULLMTBR1L ADCA1.ULLMTBR1.UINT16[L]
#define ADCA1ULLMTBR1H ADCA1.ULLMTBR1.UINT16[H]
#define ADCA1ULLMTBR2 ADCA1.ULLMTBR2.UINT32
#define ADCA1ULLMTBR2L ADCA1.ULLMTBR2.UINT16[L]
#define ADCA1ULLMTBR2H ADCA1.ULLMTBR2.UINT16[H]
#define ADCA1ECR ADCA1.ECR.UINT32
#define ADCA1ECRL ADCA1.ECR.UINT16[L]
#define ADCA1ECRLL ADCA1.ECR.UINT8[LL]
#define ADCA1ULER ADCA1.ULER.UINT32
#define ADCA1ULERL ADCA1.ULER.UINT16[L]
#define ADCA1ULERLL ADCA1.ULER.UINT8[LL]
#define ADCA1ULERLH ADCA1.ULER.UINT8[LH]
#define ADCA1OWER ADCA1.OWER.UINT32
#define ADCA1OWERL ADCA1.OWER.UINT16[L]
#define ADCA1OWERLL ADCA1.OWER.UINT8[LL]
#define ADCA1DGCTL0 ADCA1.DGCTL0.UINT32
#define ADCA1DGCTL0L ADCA1.DGCTL0.UINT16[L]
#define ADCA1DGCTL0LL ADCA1.DGCTL0.UINT8[LL]
#define ADCA1DGCTL1 ADCA1.DGCTL1.UINT32
#define ADCA1DGCTL1L ADCA1.DGCTL1.UINT16[L]
#define ADCA1PDCTL1 ADCA1.PDCTL1.UINT32
#define ADCA1PDCTL1L ADCA1.PDCTL1.UINT16[L]
#define ADCA1PDCTL2 ADCA1.PDCTL2.UINT32
#define ADCA1PDCTL2L ADCA1.PDCTL2.UINT16[L]
#define ADCA1PDCTL2LL ADCA1.PDCTL2.UINT8[LL]
#define ADCA1SMPCR ADCA1.SMPCR.UINT32
#define ADCA1SMPCRL ADCA1.SMPCR.UINT16[L]
#define ADCA1SMPCRLL ADCA1.SMPCR.UINT8[LL]
#define ADCA1EMU ADCA1.EMU
#define ADCA1SGSTCR1 ADCA1.SGSTCR1.UINT32
#define ADCA1SGSTCR1L ADCA1.SGSTCR1.UINT16[L]
#define ADCA1SGSTCR1LL ADCA1.SGSTCR1.UINT8[LL]
#define ADCA1SGCR1 ADCA1.SGCR1.UINT32
#define ADCA1SGCR1L ADCA1.SGCR1.UINT16[L]
#define ADCA1SGCR1LL ADCA1.SGCR1.UINT8[LL]
#define ADCA1SGVCSP1 ADCA1.SGVCSP1.UINT32
#define ADCA1SGVCSP1L ADCA1.SGVCSP1.UINT16[L]
#define ADCA1SGVCSP1LL ADCA1.SGVCSP1.UINT8[LL]
#define ADCA1SGVCEP1 ADCA1.SGVCEP1.UINT32
#define ADCA1SGVCEP1L ADCA1.SGVCEP1.UINT16[L]
#define ADCA1SGVCEP1LL ADCA1.SGVCEP1.UINT8[LL]
#define ADCA1SGMCYCR1 ADCA1.SGMCYCR1.UINT32
#define ADCA1SGMCYCR1L ADCA1.SGMCYCR1.UINT16[L]
#define ADCA1SGMCYCR1LL ADCA1.SGMCYCR1.UINT8[LL]
#define ADCA1SGSEFCR1 ADCA1.SGSEFCR1.UINT32
#define ADCA1SGSEFCR1L ADCA1.SGSEFCR1.UINT16[L]
#define ADCA1SGSEFCR1LL ADCA1.SGSEFCR1.UINT8[LL]
#define ADCA1SGTSEL1 ADCA1.SGTSEL1.UINT32
#define ADCA1SGTSEL1L ADCA1.SGTSEL1.UINT16[L]
#define ADCA1SGSTCR2 ADCA1.SGSTCR2.UINT32
#define ADCA1SGSTCR2L ADCA1.SGSTCR2.UINT16[L]
#define ADCA1SGSTCR2LL ADCA1.SGSTCR2.UINT8[LL]
#define ADCA1SGCR2 ADCA1.SGCR2.UINT32
#define ADCA1SGCR2L ADCA1.SGCR2.UINT16[L]
#define ADCA1SGCR2LL ADCA1.SGCR2.UINT8[LL]
#define ADCA1SGVCSP2 ADCA1.SGVCSP2.UINT32
#define ADCA1SGVCSP2L ADCA1.SGVCSP2.UINT16[L]
#define ADCA1SGVCSP2LL ADCA1.SGVCSP2.UINT8[LL]
#define ADCA1SGVCEP2 ADCA1.SGVCEP2.UINT32
#define ADCA1SGVCEP2L ADCA1.SGVCEP2.UINT16[L]
#define ADCA1SGVCEP2LL ADCA1.SGVCEP2.UINT8[LL]
#define ADCA1SGMCYCR2 ADCA1.SGMCYCR2.UINT32
#define ADCA1SGMCYCR2L ADCA1.SGMCYCR2.UINT16[L]
#define ADCA1SGMCYCR2LL ADCA1.SGMCYCR2.UINT8[LL]
#define ADCA1SGSEFCR2 ADCA1.SGSEFCR2.UINT32
#define ADCA1SGSEFCR2L ADCA1.SGSEFCR2.UINT16[L]
#define ADCA1SGSEFCR2LL ADCA1.SGSEFCR2.UINT8[LL]
#define ADCA1SGTSEL2 ADCA1.SGTSEL2.UINT32
#define ADCA1SGTSEL2L ADCA1.SGTSEL2.UINT16[L]
#define ADCA1SGSTCR3 ADCA1.SGSTCR3.UINT32
#define ADCA1SGSTCR3L ADCA1.SGSTCR3.UINT16[L]
#define ADCA1SGSTCR3LL ADCA1.SGSTCR3.UINT8[LL]
#define ADCA1SGCR3 ADCA1.SGCR3.UINT32
#define ADCA1SGCR3L ADCA1.SGCR3.UINT16[L]
#define ADCA1SGCR3LL ADCA1.SGCR3.UINT8[LL]
#define ADCA1SGVCSP3 ADCA1.SGVCSP3.UINT32
#define ADCA1SGVCSP3L ADCA1.SGVCSP3.UINT16[L]
#define ADCA1SGVCSP3LL ADCA1.SGVCSP3.UINT8[LL]
#define ADCA1SGVCEP3 ADCA1.SGVCEP3.UINT32
#define ADCA1SGVCEP3L ADCA1.SGVCEP3.UINT16[L]
#define ADCA1SGVCEP3LL ADCA1.SGVCEP3.UINT8[LL]
#define ADCA1SGMCYCR3 ADCA1.SGMCYCR3.UINT32
#define ADCA1SGMCYCR3L ADCA1.SGMCYCR3.UINT16[L]
#define ADCA1SGMCYCR3LL ADCA1.SGMCYCR3.UINT8[LL]
#define ADCA1SGSEFCR3 ADCA1.SGSEFCR3.UINT32
#define ADCA1SGSEFCR3L ADCA1.SGSEFCR3.UINT16[L]
#define ADCA1SGSEFCR3LL ADCA1.SGSEFCR3.UINT8[LL]
#define ADCA1SGTSEL3 ADCA1.SGTSEL3.UINT32
#define ADCA1SGTSEL3L ADCA1.SGTSEL3.UINT16[L]
#define ADCA1PWDSGCR ADCA1.PWDSGCR.UINT32
#define ADCA1PWDSGCRL ADCA1.PWDSGCR.UINT16[L]
#define ADCA1PWDSGCRLL ADCA1.PWDSGCR.UINT8[LL]
#define ADCA1PWDSGSEFCR ADCA1.PWDSGSEFCR.UINT32
#define ADCA1PWDSGSEFCRL ADCA1.PWDSGSEFCR.UINT16[L]
#define ADCA1PWDSGSEFCRLL ADCA1.PWDSGSEFCR.UINT8[LL]
#define DCRA0CIN DCRA0.CIN
#define DCRA0COUT DCRA0.COUT
#define DCRA0CTL DCRA0.CTL
#define DCRA1CIN DCRA1.CIN
#define DCRA1COUT DCRA1.COUT
#define DCRA1CTL DCRA1.CTL
#define DCRA2CIN DCRA2.CIN
#define DCRA2COUT DCRA2.COUT
#define DCRA2CTL DCRA2.CTL
#define DCRA3CIN DCRA3.CIN
#define DCRA3COUT DCRA3.COUT
#define DCRA3CTL DCRA3.CTL
#define KR0KRM KR0.KRM.UINT8
#define KR0KRM0 KR0.KRM.KRM0
#define KR0KRM1 KR0.KRM.KRM1
#define KR0KRM2 KR0.KRM.KRM2
#define KR0KRM3 KR0.KRM.KRM3
#define KR0KRM4 KR0.KRM.KRM4
#define KR0KRM5 KR0.KRM.KRM5
#define KR0KRM6 KR0.KRM.KRM6
#define KR0KRM7 KR0.KRM.KRM7
#define CLMA0CTL0 CLMA0.CTL0
#define CLMA0CMPL CLMA0.CMPL
#define CLMA0CMPH CLMA0.CMPH
#define CLMA0PCMD CLMA0.PCMD
#define CLMA0PS CLMA0.PS
#define CLMA0EMU0 CLMA0.EMU0
#define CLMATEST CLMA.TEST
#define CLMATESTS CLMA.TESTS
#define CLMA1CTL0 CLMA1.CTL0
#define CLMA1CMPL CLMA1.CMPL
#define CLMA1CMPH CLMA1.CMPH
#define CLMA1PCMD CLMA1.PCMD
#define CLMA1PS CLMA1.PS
#define CLMA1EMU0 CLMA1.EMU0
#define CLMA2CTL0 CLMA2.CTL0
#define CLMA2CMPL CLMA2.CMPL
#define CLMA2CMPH CLMA2.CMPH
#define CLMA2PCMD CLMA2.PCMD
#define CLMA2PS CLMA2.PS
#define CLMA2EMU0 CLMA2.EMU0
#endif
