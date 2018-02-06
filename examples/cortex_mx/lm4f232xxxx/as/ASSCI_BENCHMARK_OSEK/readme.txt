ASSCI_BENCHMARK_OSEK

 Simple banchmark project for AUTOSAR "like" SCI Driver with OSEK/VDX Kernel.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

==============================================================================

Image component sizes

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Object Name

     0          0        248          0          0          0   Dio_Cfg.o
     0          0       1064          0          0          0   Mcu_Cfg.o
     0          0        716          0          0          0   Port_Cfg.o
     0          0        296          0          0          0   Sci_Cfg.o
   632        622          0          0       1024          0   ee_startup_keil.o
     0          0         48         80         16          0   eecfg.o
   296         20          0         40          0        236   main.o

----------------------------------------------------------------------
   928        642       2404        120       1040        236   Object Totals
     0          0         32          0          0          0   (incl. Generated)
     0          0          0          0          0          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Member Name

     8          0          0          0          0         68   __main.o
    52          8          0          0          0          0   __scatter.o
    26          0          0          0          0          0   __scatter_copy.o
    28          0          0          0          0          0   __scatter_zi.o
    12          0          0          0          0         72   exit.o
     6          0          0          0          0        152   heapauxi.o
     0          0          0          0          0          0   indicate_semi.o
     2          0          0          0          0          0   libinit.o
     2          0          0          0          0          0   libinit2.o
     2          0          0          0          0          0   libshutdown.o
     2          0          0          0          0          0   libshutdown2.o
     0          0          0          0          0          0   rtentry.o
    12          0          0          0          0          0   rtentry2.o
     8          4          0          0          0          0   rtentry5.o
     2          0          0          0          0          0   rtexit.o
    10          0          0          0          0          0   rtexit2.o
    12          4          0          0          0         68   sys_exit.o
     2          0          0          0          0         68   use_no_semi.o
   804         16          0          0          0        280   daddsub_clz.o
    90          4          0          0          0         92   dfixu.o
   156          4          0          0          0         92   dnaninf.o
    12          0          0          0          0         68   dretinf.o
    86          4          0          0          0         84   f2d.o
   450          8          0          0          0        236   faddsub_clz.o
    12          4          0          0          0         68   fcheck1.o
   388         76          0          0          0         96   fdiv.o
    62          4          0          0          0         84   ffixu.o
    38          0          0          0          0         68   fflt_clz.o
   140          4          0          0          0         84   fnaninf.o
    10          0          0          0          0         68   fretinf.o
   100          0          0          0          0         68   retnan.o
    76          0          0          0          0         68   scalbnf.o
    48          0          0          0          0         68   trapv.o
     0          0          0          0          0          0   usenofp.o
   788         10          0          8          0        348   Dio.o
    48          8         52          0          0         80   Hardware.o
   456         28          0          0         12        272   Mcu.o
   764         48          0          8          0        216   Port.o
  1896         50          0          8          0        532   Sci.o
   280         22          0          0          0        128   Sci_Irq.o
   180         36          0          0          0         84   ee_activate.o
    36          4          0          0          0        152   ee_context.o
     0          0          0          8          0          0   ee_hal_structs.o
   120         34          0          0          0        148   ee_irqendin.o
   128         34          0          0          0        132   ee_keil_change_context_isr.o
   128         12          0          0          0         84   ee_keil_oo.o
     0          0          0          4          0          0   ee_lookup.o
    36         12          0          0          0         68   ee_rq_exchg.o
    68         12          0          0          0         84   ee_rq_inser.o
   120         26          0          8          0         84   ee_startos.o
   200         46          0          0          0         88   ee_thendin.o
    16          6          0          0          0         72   ee_tnterm.o
    12          4          0          0          0         68   ee_tstub.o
    56         10          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  8004        542         52         44         12       4668   Library Totals
    14          0          0          0          0          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  2472        124          0          0          0       1524   fz_ws.l
  4232        166         52         24         12       1576   libas.a
  1100        236          0         20          0       1140   libee.a

----------------------------------------------------------------------
  8004        542         52         44         12       4668   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  8932       1184       2456        164       1052       2668   Grand Totals
  8932       1184       2456        164       1052       2668   ELF Image Totals
  8932       1184       2456        164          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                11388 (  11.12kB)
Total RW  Size (RW Data + ZI Data)              1216 (   1.19kB)
Total ROM Size (Code + RO Data + RW Data)      11552 (  11.28kB)

==============================================================================

