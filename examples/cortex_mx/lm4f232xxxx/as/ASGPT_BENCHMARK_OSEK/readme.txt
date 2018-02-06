ASGPT_BENCHMARK_OSEK

 Simple banchmark project for AUTOSAR "like" GPT Driver with OSEK/VDX Kernel.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

==============================================================================

Image component sizes

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Object Name

     0          0        248          0          0          0   Dio_Cfg.o
     0          0        136          0          0          0   Gpt_Cfg.o
     0          0       1064          0          0          0   Mcu_Cfg.o
     0          0        716          0          0          0   Port_Cfg.o
   632        622          0          0       1024          0   ee_startup_keil.o
     0          0         48         64         12          0   eecfg.o
   328         26          0         12          0        212   main.o

----------------------------------------------------------------------
   960        648       2244         76       1036        212   Object Totals
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
  2660         42          0          0         16        644   Gpt.o
   348         26          0          0          0        168   Gpt_Irq.o
    48          8         52          0          0         80   Hardware.o
   456         28          0          0         12        272   Mcu.o
   764         48          0          8          0        216   Port.o
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
    84         10          0          0          0         76   ee_utils.o

----------------------------------------------------------------------
  6460        426         52         40         32       3304   Library Totals
     6          0          0          0          4          0   (incl. Padding)

----------------------------------------------------------------------

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

   186         16          0          0          0        428   c_w.l
  5064        162         52         16         28       1728   libas.a
  1204        248          0         24          0       1148   libee.a

----------------------------------------------------------------------
  6460        426         52         40         32       3304   Library Totals

----------------------------------------------------------------------

==============================================================================

  Code (inc. data)   RO Data    RW Data    ZI Data      Debug

  7420       1074       2296        116       1068       2216   Grand Totals
  7420       1074       2296        116       1068       2216   ELF Image Totals
  7420       1074       2296        116          0          0   ROM Totals

==============================================================================

Total RO  Size (Code + RO Data)                 9716 (   9.49kB)
Total RW  Size (RW Data + ZI Data)              1184 (   1.16kB)
Total ROM Size (Code + RO Data + RW Data)       9832 (   9.60kB)

==============================================================================

