Project - demo

Questa cartella contiene un esempio di come deve essere la struttura di un progetto per S12G basato su Erika.

Gli aspetti da tenere presente sono:

- la compilazione del progetto può essere avviata semplicemente cliccando due volte su 'compile.bat'.
  Tuttavia per poter visualizzare l'Help della utility 'compile.bat' e per fare il clean del progetto, con il 'compile.bat',
  è necessario avviare lo script da riga di comando utilizzando per esempio il prompt DOS dei comandi 
  (es. C:\> compile.bat help oppure C:\> compile.bat clean) oppure la shell di Cygwin (es. $ ./compile.bat help oppure $ ./compile.bat clean) 
  dopo aver modificato opportunamente la working directory con il comando 'cd'.  
  Il clean del progetto può anche essere fatto cliccando due volte su 'clean.bat' oppure 
  rimuovendo manualmente la cartella generata dal druido ('Application/output').

- Il kernel 'Erika RTOS' è contenuto all'interno della cartella 'OS_EE/ee_base' quindi è interno al progetto.
  Può essere spostato ma questo richiede una modifica allo script 'compile.sh' ('compile.sh' è di tipo bash 
  ed è chiamato da 'compile.bat').
  Il kernel contiene i files SVN (checkout anonimo del repository di Erika della versione 1603) perchè in questo modo 
  è molto più semplice controllare le modifiche apportate e effettuare aggiornamenti. Versioni precedenti del kernel, pur stabili,
  possono però dare errori di compilazione con questo progetto.

- Il software RT-Druid (OIL parser) è anch'esso interno al progetto (in 'OS_EE/RT-Druid') ed è chiamato dal makefile 
  contenuto in OS_EE. Al termine della generazione dei files operata dal druido, il makefile avvia la compilazione del progetto
  e per le successive compilazioni si basa sulle dipendenze calcolate con il compilatore. 
  Anche RT-Druid può essere spostato fuori dal progetto ma questo richiede una modifica allo script 'compile.sh'.  

- ### IMPORTANTE ### Per specificare il percorso del compilatore è necessario editare il file 'common_oil.pref' che si trova 
  in questa cartella 'OS_EE/RT-Druid/configuration'.

- i files di progetto possono anche essere esterni alla cartella 'Application'. Lo spostamento del file 'conf.oil' richiede però
  alcune modifiche algi script.
  (Tuttavia questo approccio è sconsigliato perchè si potrebbero avere problemi di compatibilità del codice a lungo termine.)
  Per specificare soltanto un include path o per aggiungere sorgenti da compilare è possibile utilizzare il file 'conf.oil'.
  Per maggiori informazioni consultare il manuale del druido, il wiki di Erika e leggere i commenti all'interno del file.

- Se si intende utilizzare un'architettura diversa (per esempio MC9S12GN16), si dovranno apportare alcune ovvie modifiche al codice
  (per esempio la funzione 'board_init', perchè il progetto di esempio contenuto in questa cartella è stato scritto per la board TWR-S12G128)
  ma soprattutto dovrà essere modificato il file OIL (in particolare i campi MCU_DATA e BOARD_DATA), oltre al fatto che dovrà essere aggiunto
  il linker script nella cartella 's12g' dell'applicazione.
  
- Le cartelle 'src', 'inc' e 's12g' all'interno di 'Application' non sono necessarie, servono solo per far vedere come devono essere specificati
  i sorgenti o il linker script nel 'conf.oil'.
  La cartella 'hiwave' contiene semplicemente dei files utili per l'uso del debugger.
