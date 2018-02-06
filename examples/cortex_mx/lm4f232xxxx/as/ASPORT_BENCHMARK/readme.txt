ASPORT_BENCHMARK

 Simple benchmark project to AUTOSAR "like" PORT Driver.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

==============================================================================

Image component sizes

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Object Name

     0          0       1064          0          0          0   Mcu_Cfg.o
     0          0        716          0          0          0   Port_Cfg.o
   632        622          0          0       1024          0   ee_startup_keil.o
     0          0         12         20          0          0   eecfg.o
   284         40          0          8          0        252   main.o

----------------------------------------------------------------------
   916        662       1824         28       1024        252   Object Totals
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
    48          8         52          0          0         80   Hardware.o
   464         28          0          0         12        276   Mcu.o
   764         48          0          8          0        216   Port.o
    44          8          0          0          0        152   ee_context.o
     0          0          0          8          0          0   ee_hal_structs.o
    72         22          0          0          0         76   ee_irqsc.o
   128         34          0          0          0        132   ee_keil_change_context_isr.o
    36         12          0          0          0         68   ee_rqexchg.o
    68         12          0          0          0         84   ee_rqinsert.o
   116         26          0          0          0         80   ee_thact.o
   124         32          0          0          0         80   ee_thendin.o
    32          4          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  2088        250         52         16         12       1748   Library Totals
     6          0          0          0          0          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  1276         84         52          8         12        572   libas.a
   620        150          0          8          0        748   libee.a

----------------------------------------------------------------------
  2088        250         52         16         12       1748   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  3004        912       1876         44       1036       1116   Grand Totals
  3004        912       1876         44       1036       1116   ELF Image Totals
  3004        912       1876         44          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                 4880 (   4.77kB)
Total RW  Size (RW Data + ZI Data)              1080 (   1.05kB)
Total ROM Size (Code + RO Data + RW Data)       4924 (   4.81kB)

==============================================================================
