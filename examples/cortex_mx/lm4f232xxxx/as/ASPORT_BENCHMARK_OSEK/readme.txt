ASPORT_BENCHMARK_OSEK

 Simple benchmark project to AUTOSAR "like" PORT Driver with OSEK/VDX Kernel.
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
     0          0         12         36          0          0   eecfg.o
   308         40          0          8          0        260   main.o

----------------------------------------------------------------------
   940        662       1824         44       1024        260   Object Totals
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
   456         28          0          0         12        272   Mcu.o
   764         48          0          8          0        216   Port.o
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
    32          4          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  2536        330         52         28         16       2136   Library Totals
     6          0          0          0          4          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  1268         84         52          8         12        568   libas.a
  1076        230          0         20          0       1140   libee.a

----------------------------------------------------------------------
  2536        330         52         28         16       2136   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  3476        992       1876         72       1040       1252   Grand Totals
  3476        992       1876         72       1040       1252   ELF Image Totals
  3476        992       1876         72          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                 5352 (   5.23kB)
Total RW  Size (RW Data + ZI Data)              1112 (   1.09kB)
Total ROM Size (Code + RO Data + RW Data)       5424 (   5.30kB)

==============================================================================

