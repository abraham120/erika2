;; 
;; C Run-time startup module for dsPIC30 C compiler.
;; (c) Copyright 2002,2004,2007 Microchip Technology, All rights reserved
;;
;; Primary version, with data initialization support.
;; The linker loads this version when the --data-init
;; option is selected.
;; 
;; See file crt1.s for the alternate version without
;; data initialization support.
;; 
;; Entry __reset takes control at device reset and
;; performs the following:
;;
;;  1. initialize stack and stack limit register
;;  2. initialize PSV window if __const_length > 0
;;  3. process the data initialization template
;;  4. call the .user_init section, if it exists
;;  5. call the user's _main entry point
;;
;; Assigned to section .init, which may be allocated
;; at a specific address in linker scripts. 
;;
;; If a local copy of this file is customized, be sure
;; to choose a file name other than crt0.s or crt1.s.
;;
        

        .section .init,code

        .global __resetPRI
        .ifdef __C30ELF
        .type   __resetPRI,@function
        .endif
__resetPRI:     
        .weak  __reset
        .ifdef __C30ELF
        .type   __reset,@function
        .endif
__reset:
;;
;; Initialize stack, PSV, and data
;; 
;; registers used:  w0
;;
;; Inputs (defined by user or linker):
;;  __SP_init
;;  __SPLIM_init
;; 
;; Outputs:
;;  (does not return - resets the processor)
;; 
;; Calls:
;;  __psv_init
;;  __data_init
;;  _main
;; 

        .weak    __user_init, __has_user_init
        
        mov      #__SP_init,w15    ; initialize w15
        mov      #__SPLIM_init,w0  ; 
        mov      w0,_SPLIM         ; initialize SPLIM
        nop                        ; wait 1 cycle

        rcall    __psv_init        ; initialize PSV
        rcall    __data_init       ; initialize data

        mov      #__has_user_init,w0
        cp0      w0                ; user init functions?
        bra      eq,1f             ; br if not
        call     __user_init       ; else call them
1:
        call  _main                ; call user's main()

        .pword 0xDA4000            ; halt the simulator
        reset                      ; reset the processor


        .global __psv_init
__psv_init:
;; 
;; Initialize PSV window if _constlen > 0
;; 
;; Registers used:  w0
;; 
;; Inputs (defined by linker):
;;  __const_length
;;  __const_psvpage
;; 
;; Outputs:
;;  (none)
;; 
	.equiv   PSV, 0x0002

        bclr     _CORCON,#PSV        ; disable PSV (default)
        mov      #__const_length,w0  ; 
        cp0      w0                  ; test length of constants
        bra      z,1f                ; br if zero

        mov      #__const_psvpage,w0 ; 
        mov      w0,_PSVPAG          ; PSVPAG = psvpage(constants)
        bset     _CORCON,#PSV        ; enable PSV

1:      return                       ;  and exit

        
        .global __data_init
__data_init:
;; 
;; Process data init template
;;
;; The template is null-terminated, with records
;; in the following format:
;;
;; struct data_record {
;;  char *dst;        /* destination address  */
;;  int  len;         /* length in bytes      */
;;  int  format;      /* format code          */
;;  char dat[0];      /* variable length data */
;; };
;; 
;; Registers used:  w0 w1 w2 w3 w4 w5
;; 
;; Inputs (defined by linker):
;;  __dinit_tbloffset
;;  __dinit_tblpage
;; 
;; Outputs:
;;  (none)
;;
;; Calls:
;;  __memcpypd3
;; 
        .equiv   FMT_CLEAR,0    ;  format codes
        .equiv   FMT_COPY2,1    ; 
        .equiv   FMT_COPY3,2    ; 

        mov      #__dinit_tbloffset,w0 ; w0,w1 = template
        mov      #__dinit_tblpage,w1   ;
        bra      4f                    ; br to continue

1:      add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)

        tblrdl.w [w0],w3        ; w3 = len 
        add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)

        tblrdl.w [w0],w5        ; w5 = format
        add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        clr      w4             ; upper = FALSE (default)

        cp       w5,#FMT_CLEAR  ; test format
        bra      nz,2f          ; br if not FMT_CLEAR

        ;; FMT_CLEAR - clear destination memory
9:      clr.b    [w2++]         ; clear memory
        dec      w3,w3          ; done?
        bra      gtu,9b         ; loop if not
        bra      4f             ; br to continue

        ;; FMT_COPY2, FMT_COPY3 - copy bytes
2:      cp       w5,#FMT_COPY2  ; test format
        bra      z,3f           ; br if FMT_COPY2

        setm     w4             ; upper = TRUE

3:      rcall    __memcpypd3    ; copy 2 or 3 bytes

4:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)
        tblrdl.w [w0],w2        ; w2 = next dst      
        cp0      w2             ; 
        bra      nz,1b          ; loop on non-zero dst

        retlw    #0,w0          ; exit (clears ARGC also)

        
__memcpypd3:
;; 
;; Copy data from program memory to data memory
;; 
;; Registers used:  w0 w1 w2 w3 w4 w5
;; 
;; Inputs:
;;  w0,w1 = source address   (24 bits)
;;  w2 = destination address (16 bits)
;;  w3 = number of bytes (even or odd)
;;  w4 = upper byte flag   (0 = false)
;; 
;; Outputs:
;;  w0,w1 = next source address (24 bits)
;; 

1:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(src)
        mov      w0,w5          ; w5 =   tbloffset(src)
        add      w0,#2,w0       ; src+=2
        addc     w1,#0,w1       ;

        tblrdl.b [w5++],[w2++]  ; dst++ = lo byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        tblrdl.b [w5--],[w2++]  ; dst++ = hi byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        cp0      w4             ; test upper flag
        bra      z,1b           ; br if false

        tblrdh.b [w5],[w2++]    ; dst++ = upper byte
        dec      w3,w3          ; num--
        bra      nz,1b          ; br if not done

2:      return                  ; exit

        .end

