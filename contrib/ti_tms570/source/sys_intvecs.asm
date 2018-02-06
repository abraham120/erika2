;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .sect ".intvecs"


;-------------------------------------------------------------------------------
; import reference for interrupt routines

    .ref _c_int00
    .ref _dabort
    .ref _irqDispatch
    .ref phantomInterrupt


;-------------------------------------------------------------------------------
; interrupt vectors

        b   _c_int00
undefEntry
        b   undefEntry
svcEntry
        b   svcEntry
prefetchEntry
        b   prefetchEntry
        b   _dabort
        b   phantomInterrupt
        b   _irqDispatch
        ldr pc,[pc,#-0x1b0]

    
;-------------------------------------------------------------------------------
