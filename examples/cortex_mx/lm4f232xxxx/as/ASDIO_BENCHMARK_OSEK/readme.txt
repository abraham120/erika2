ASDIO_BENCHMARK_OSEK

 Simple benchmark project to AUTOSAR "like" DIO Driver with OSEK/VDX Kernel.
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
   632        622          0          0       1024          0   ee_startup_keil.o
     0          0         64         44         16          0   eecfg.o
   196         16          0         12          0        104   main.o

----------------------------------------------------------------------
   828        638       2124         56       1040        104   Object Totals
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
   788         10          0          8          0        348   Dio.o
    48          8         52          0          0         80   Hardware.o
   456         28          0          0         12        272   Mcu.o
   764         48          0          8          0        216   Port.o
    96         10          0          0          0         80   ee_alsetrel.o
   504         54          0          0          0        216   ee_altick.o
    36          4          0          0          0        152   ee_context.o
     0          0          0          8          0          0   ee_hal_structs.o
   120         34          0          0          0        148   ee_irqendin.o
   128         34          0          0          0        132   ee_keil_change_context_isr.o
   128         12          0          0          0         84   ee_keil_oo.o
     0          0          0          8          0          0   ee_lookup.o
    36         12          0          0          0         68   ee_rq_exchg.o
    68         12          0          0          0         84   ee_rq_inser.o
   208         42          0          8          0         92   ee_startos.o
   180         16          0          0          0        164   ee_system_timer.o
   200         46          0          0          0         88   ee_thendin.o
    16          6          0          0          0         72   ee_tnterm.o
    12          4          0          0          0         68   ee_tstub.o
    18          0          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  4000        396         52         40         16       2868   Library Totals
     8          0          0          0          4          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  2056         94         52         16         12        916   libas.a
  1750        286          0         24          0       1524   libee.a

----------------------------------------------------------------------
  4000        396         52         40         16       2868   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  4828       1034       2176         96       1056       1620   Grand Totals
  4828       1034       2176         96       1056       1620   ELF Image Totals
  4828       1034       2176         96          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                 7004 (   6.84kB)
Total RW  Size (RW Data + ZI Data)              1152 (   1.13kB)
Total ROM Size (Code + RO Data + RW Data)       7100 (   6.93kB)

==============================================================================

