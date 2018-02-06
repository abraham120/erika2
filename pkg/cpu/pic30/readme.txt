ERIKA Enterprise per DSPIC
Quick install guide e note sparse
---------------------------------

Per installare:
- installate cygwin (serve make, cat, mkdir, test e poco altro)

- installare Java

- scompattare il megapacchetto dentro c:\Programmi\Evidence; se abbiamo fatto l'installer, installare dall'installer, e verificare che Eclipse parta correttamente.

- scaricare la documentazione sulla API di Erika per nios II (ovviamente la parte di Nios II vi interessa poco, ma per ora è l'unica docuemntazione che c'e'). se volete, è utile anche la documentazione di www.osek-vdx.org, in particolare la parte OS e la parte OIL. buona parte comunque è contenuta anche nei manuali di erika.

- per compilare: dentro lo zip trovat delle directory dentro eclipse/workspace.
  ci sono dei file lancia.bat, che chiamano eclipse da riga di comando, e generano una sottodirectory Debug con tutto il necessario. spostarsi li dentro e scrivere make per generare un elf

--- esempio: cut & paste da una compilazione reale
pj@TOM /cygdrive/c/Programmi/Evidence/eclipse/workspace/pic30_prova1
$ ./lancia.bat 

c:\Programmi\Evidence\eclipse\workspace\pic30_prova1>set CLASSPATH="C:\Programmi\j2sdk1.4.2_05\lib\tools.jar;C:\Programmi\Evidence\eclipse\startup.jar" 

c:\Programmi\Evidence\eclipse\workspace\pic30_prova1>java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner 
Buildfile: c:\Programmi\Evidence\eclipse\workspace\pic30_prova1\build.xml

all:

[rtdruid.Oil.Configurator] [LOAD      conf.oil]
[rtdruid.Oil.Configurator] [WORKING   Prepare configuration's files]
[rtdruid.Oil.Configurator] [PIC30, __MONO__, BCC1, __OO_EXTENDED_STATUS__, __OO_HAS_STARTUPHOOK__, __OO_HAS_USERESSCHEDULER__, __OO_HAS_STARTUPSYNC__]
[rtdruid.Oil.Configurator] WARNING > Not found any value for MASTER_CPU. Using default value.
[rtdruid.Oil.Configurator] [          Start to save]
[rtdruid.Oil.Configurator] [WRITE     Debug\\eecfg.h]
[rtdruid.Oil.Configurator] [WRITE     Debug\\makefile]
[rtdruid.Oil.Configurator] [WRITE     Debug\\eecfg.c]
BUILD SUCCESSFUL

BUILD SUCCESSFUL
Total time: 1 second

pj@TOM /cygdrive/c/Programmi/Evidence/eclipse/workspace/pic30_prova1
$ cd Debug/

pj@TOM /cygdrive/c/Programmi/Evidence/eclipse/workspace/pic30_prova1/Debug
$ make
DEP eecfg.c
DEP ../T1.S
DEP ../code.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal.S
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal_c.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/crt0.S
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_oo.S
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_activate.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_schedule.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_force_schedule.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_terminat.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_thendin.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_irqendin.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_tstub.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lookup.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_exchg.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_first.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_inser.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_shtdown.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_startos.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_chaintas.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lockres.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_ulockres.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alcancel.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_algetbase.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alget.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetabs.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetrel.c
DEP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_altick.c
GEN deps
CPP eecfg.c
ASM eecfg.c
PRE ../T1.S
ASM ../T1.S
CPP ../code.c
c:/Programmi/Evidence/eclipse/workspace/pic30_prova1/code.c:81: warning: return type of `main' is not `int'
ASM ../code.c
LOC
PRE /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal.S
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal.S
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal_c.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_hal_c.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/crt0.S
PRE /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_oo.S
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/cpu/pic30/src/ee_oo.S
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_activate.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_activate.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_schedule.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_schedule.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_force_schedule.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_force_schedule.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_terminat.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_terminat.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_thendin.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_thendin.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_irqendin.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_irqendin.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_tstub.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_tstub.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lookup.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lookup.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_exchg.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_exchg.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_first.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_first.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_inser.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_rq_inser.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_shtdown.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_shtdown.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_startos.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_startos.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_chaintas.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_chaintas.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lockres.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_lockres.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_ulockres.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_ulockres.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alcancel.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alcancel.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_algetbase.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_algetbase.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alget.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alget.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetabs.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetabs.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetrel.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_alsetrel.c
CPP /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_altick.c
ASM /cygdrive/c/Programmi/Evidence/eclipse/../pic30/ee/pkg/kernel/oo/src/ee_altick.c
AR libee.a
LD

pj@TOM /cygdrive/c/Programmi/Evidence/eclipse/workspace/pic30_prova1/Debug
$ 
---


- debugging: una volta generato l'elf, da mplabide fare file/import. MPLAB riconosce la posizione dei file ecc... per cui dovreste vedere anche il sorgente

- il file OIL è la chiave di tutta la configurazione, contiene la specifica dei task, risorse, ecc...

- quando si usa il multistack, è possibile abilitare il controllo dello stack con SPLIM agendo sull'opportuno flag

- supporto di altri chip dspic: bisogna cambiare lo script di linking nel file OIL

- scrittura degli interrupt: ci sono 2 tipi di interrupt:
  - ISR di tipo 1 --> ottenuti con le macro del compilatore - non potete chiamare primitive di erika dentro ma sono MOLTO veloci. devono avere priorità + alta degli ISR2. tipicamente hanno la priorità 7
  - ISR di tipo 2. + lenti, ma potete chiamare primitive di sistema operativo per, esempio, attivare dei task/allarmi/ecc... hanno priorità dino a 6 -->ovvero, in altre parole, ERIKA usa l'istruzione DISI per disabilitare gli interrupt

- scrittura dei driver:
  i vari driver che verranno scritti vanno messi nelle directory pkg/mcu e pkg/board. mettete file ed include, poi aggiungete il cfg.mk
  CPU contiene la parte del core
  MCU sono i driver relativi al particolare dispositivo (ex. seriale, timer, ...)
  BOARD sono i driver di + alto livello. esempio, voglio accendere un led sulla board (internamente userà i pin di I/O giusti chiamando le funzioni della MCU


- da fare:
  - crt0.S è quello di Microchip: bisogna copiarlo durante l'installazione e non distribuirlo
  - file .h in C per i registri - vanno scritti, al momento di fatto ci sono solo in assembler perchè sono nel linker script
  - i driver di tutte le periferiche :-(
