ASWDG_BENCHMARK

 Simple banchmark project for AUTOSAR "like" PIOSC WDG Driver with OSEK/VDX
 Kernel.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

NOTE:	In order to use watchdog 1, we have to enable the clock to another
	module that can use the PIOSC as a clock (UART, SSI, ADC).
	http://e2e.ti.com/support/microcontrollers/
		/stellaris_arm_cortex-m3_microcontroller/f/471/t/176487.aspx


==============================================================================

Image component sizes

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Object Name

     0          0        248          0          0          0   Dio_Cfg.o
     0          0       1064          0          0          0   Mcu_Cfg.o
     0          0        716          0          0          0   Port_Cfg.o
     0          0        340          0          0          0   Sci_Cfg.o
     0          0         44          0          0          0   Wdg_PIOscCfg.o
   632        622          0          0       1024          0   ee_startup_keil.o
     0          0         24         36          0          0   eecfg.o
   236         26          0         12          0        128   main.o

----------------------------------------------------------------------
   868        648       2468         48       1024        128   Object Totals
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
    24          0          0          0          0         68   fcmpi.o
   388         76          0          0          0         96   fdiv.o
    62          4          0          0          0         84   ffixu.o
    38          0          0          0          0         68   fflt_clz.o
   104          4          0          0          0         84   fleqf.o
   140          4          0          0          0         84   fnaninf.o
    10          0          0          0          0         68   fretinf.o
    98          0          0          0          0         68   frleqf.o
   100          0          0          0          0         68   retnan.o
    76          0          0          0          0         68   scalbnf.o
    48          0          0          0          0         68   trapv.o
     0          0          0          0          0          0   usenofp.o
   788         10          0          8          0        348   Dio.o
    48          8         52          0          0         80   Hardware.o
   456         28          0          0         12        272   Mcu.o
   764         48          0          8          0        216   Port.o
  1896         50          0          8          0        532   Sci.o
   532         30          0          8          0        180   WdgPIOsc.o
   180         18          0          0          0        120   Wdg_PIOscIrq.o
   192         42          0          0          0         84   ee_activate.o
    36          4          0          0          0        152   ee_context.o
     0          0          0          8          0          0   ee_hal_structs.o
   120         34          0          0          0        148   ee_irqendin.o
   128         34          0          0          0        132   ee_keil_change_context_isr.o
   128         12          0          0          0         84   ee_keil_oo.o
     0          0          0          8          0          0   ee_lookup.o
    36         12          0          0          0         68   ee_rq_exchg.o
    68         12          0          0          0         84   ee_rq_inser.o
   184         32          0          8          0         92   ee_startos.o
   200         46          0          0          0         88   ee_thendin.o
    16          6          0          0          0         72   ee_tnterm.o
    12          4          0          0          0         68   ee_tstub.o
    18          0          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  8704        574         52         56         16       5068   Library Totals
    18          0          0          0          4          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  2698        128          0          0          0       1744   fz_ws.l
  4664        192         52         32         12       1748   libas.a
  1138        238          0         24          0       1148   libee.a

----------------------------------------------------------------------
  8704        574         52         56         16       5068   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  9572       1222       2520        104       1040       2752   Grand Totals
  9572       1222       2520        104       1040       2752   ELF Image Totals
  9572       1222       2520        104          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                12092 (  11.81kB)
Total RW  Size (RW Data + ZI Data)              1144 (   1.12kB)
Total ROM Size (Code + RO Data + RW Data)      12196 (  11.91kB)

==============================================================================

