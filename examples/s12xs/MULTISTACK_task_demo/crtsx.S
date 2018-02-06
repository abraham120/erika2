;	C STARTUP FOR S12X
;	WITH AUTOMATIC DATA/CODE INITIALISATION
;	Copyright (c) 2006 by COSMIC Software
;
	xdef	_exit, __stext
;	xref	_main
	xref	f_main
	xref	__sbss, __memory, __idesc__, __stack, __sdirect
	xref	__subsct, __eubsct, __sgdflt
	xref	_GPAGE, _RPAGE, _PPAGE, _DIRECT, _EPAGE
;
__stext:
	lds	#__stack				; initialize stack pointer
	movb	#$00, _EPAGE
	movb	#$FD,_RPAGE				; default ram configuration
	movb	#high(__sdirect),_DIRECT 	; direct page register
	movb	#page(__idesc__),_PPAGE		; allows banked descriptor
	ldx	#__idesc__				; descriptor address
	ldy	2,x+					; start address of prom data
ibcl:
	ldaa	5,x+					; test flag byte
	beq	zbss					; no more segment
	bpl	nopg					; page indicator
	leax	2,x					; skip it
nopg:
	bita	#$60					; test for moveable code segment
	bne	dseg					; no, copy it
	ldy	-2,x					; reload code address
	bra	ibcl					; and continue with next segment
dseg:
	pshx						; save pointer
	tsta						; global addresses
	bmi	glob					; yes, copy
	tfr	y,d					; start address
	subd	-2,x					; minus end address
	ldx	-4,x					; destination address
dbcl:
	movb	1,y+,1,x+				; copy from prom to ram
	ibne	d,dbcl				; count up and loop
	pulx						; reload pointer to desc
	bra	ibcl					; and loop
glob:
	ldd	-2,x					; end address
	pshd						; on the stack
	movb	-5,x,_GPAGE				; set page register
	ldx	-4,x					; destination address
xbcl:
	ldab	1,y+					; read data
	gstab	1,x+					; and write to ram
	cpy	0,s					; compare with end address
	blo	xbcl					; and loop back
	pulx						; clean stack
	pulx						; reload pointer to desc
	bra	ibcl					; and loop
zbss:
	ldx	#__sbss				; start of bss
	clrb						; complete zero
	bra	loop					; start loop
zbcl:
	std	2,x+					; clear word
loop:
	cpx	#__memory				; end of bss
	blo	zbcl					; no, continue
	ldx	#__subsct				; start of ubsct
	bra	uloop					; start loop
zubs:
	stab	1,x+					; clear byte
uloop:
	cpx	#__eubsct				; end of ubsct
	blo	zubs					; no continue
	movb	#phigh(__sgdflt),_GPAGE	 	; set global page default
;	jsr	_main					; execute main
	call	f_main				; in case main is banked
_exit:
	bra	_exit					; stay here
;
	end
