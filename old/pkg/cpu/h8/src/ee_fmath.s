;;; Author: 2002 Davide Cantini
;;; CVS: $Id: ee_fmath.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

; ************************************************
; ***************  FIXED POINT MATH  *************
; ************************************************
 
.include "fmath_set.s"

;; --------------------------------
;; 16 bit fractional part of cosine
;; --------------------------------
    .equ cos0, 0x0000    
    .equ cos1, 0xFFF6
    .equ cos2, 0xFFD8
    .equ cos3, 0xFFA6
    .equ cos4, 0xFF60
    .equ cos5, 0xFF07
    .equ cos6, 0xFE99
    .equ cos7, 0xFE18
    .equ cos8, 0xFD82
    .equ cos9, 0xFCD9
    .equ cos10, 0xFC1C
    .equ cos11, 0xFB4C
    .equ cos12, 0xFA68
    .equ cos13, 0xF970
    .equ cos14, 0xF865
    .equ cos15, 0xF747
    .equ cos16, 0xF615
    .equ cos17, 0xF4D0
    .equ cos18, 0xF378
    .equ cos19, 0xF20E
    .equ cos20, 0xF090
    .equ cos21, 0xEEFF
    .equ cos22, 0xED5C
    .equ cos23, 0xEBA6
    .equ cos24, 0xE9DE
    .equ cos25, 0xE804
    .equ cos26, 0xE617
    .equ cos27, 0xE419
    .equ cos28, 0xE209
    .equ cos29, 0xDFE7
    .equ cos30, 0xDDB4
    .equ cos31, 0xDB6F
    .equ cos32, 0xD91A
    .equ cos33, 0xD6B3
    .equ cos34, 0xD43C
    .equ cos35, 0xD1B4
    .equ cos36, 0xCF1C
    .equ cos37, 0xCC73
    .equ cos38, 0xC9BB
    .equ cos39, 0xC6F3
    .equ cos40, 0xC41B
    .equ cos41, 0xC135
    .equ cos42, 0xBE3F
    .equ cos43, 0xBB3A
    .equ cos44, 0xB827
    .equ cos45, 0xB505
    .equ cos46, 0xB1D5
    .equ cos47, 0xAE97
    .equ cos48, 0xAB4C
    .equ cos49, 0xA7F3
    .equ cos50, 0xA48E
    .equ cos51, 0xA11B
    .equ cos52, 0x9D9C
    .equ cos53, 0x9A11
    .equ cos54, 0x9679
    .equ cos55, 0x92D6
    .equ cos56, 0x8F27
    .equ cos57, 0x8B6D
    .equ cos58, 0x87A9
    .equ cos59, 0x83DA
    .equ cos60, 0x8000
    .equ cos61, 0x7C1C
    .equ cos62, 0x782F
    .equ cos63, 0x7439
    .equ cos64, 0x7039
    .equ cos65, 0x6C31
    .equ cos66, 0x6820
    .equ cos67, 0x6407
    .equ cos68, 0x5FE6
    .equ cos69, 0x5BBE
    .equ cos70, 0x578F
    .equ cos71, 0x5358
    .equ cos72, 0x4F1C
    .equ cos73, 0x4AD9
    .equ cos74, 0x4690
    .equ cos75, 0x4242
    .equ cos76, 0x3DEF
    .equ cos77, 0x3996
    .equ cos78, 0x353A
    .equ cos79, 0x30D9
    .equ cos80, 0x2C74
    .equ cos81, 0x280C
    .equ cos82, 0x23A1
    .equ cos83, 0x1F33
    .equ cos84, 0x1AC2
    .equ cos85, 0x1650
    .equ cos86, 0x11DC
    .equ cos87, 0x0D66
    .equ cos88, 0x08EF
    .equ cos89, 0x0478
    .equ cos90, 0x0000
    .equ cos91, (-cos89)
    .equ cos92, (-cos88)
    .equ cos93, (-cos87)
    .equ cos94, (-cos86)
    .equ cos95, (-cos85)
    .equ cos96, (-cos84)
    .equ cos97, (-cos83)
    .equ cos98, (-cos82)
    .equ cos99, (-cos81)
    .equ cos100, (-cos80)
    .equ cos101, (-cos79)
    .equ cos102, (-cos78)
    .equ cos103, (-cos77)
    .equ cos104, (-cos76)
    .equ cos105, (-cos75)
    .equ cos106, (-cos74)
    .equ cos107, (-cos73)
    .equ cos108, (-cos72)
    .equ cos109, (-cos71)
    .equ cos110, (-cos70)
    .equ cos111, (-cos69)
    .equ cos112, (-cos68)
    .equ cos113, (-cos67)
    .equ cos114, (-cos66)
    .equ cos115, (-cos65)
    .equ cos116, (-cos64)
    .equ cos117, (-cos63)
    .equ cos118, (-cos62)
    .equ cos119, (-cos61)
    .equ cos120, (-cos60)
    .equ cos121, (-cos59)
    .equ cos122, (-cos58)
    .equ cos123, (-cos57)
    .equ cos124, (-cos56)
    .equ cos125, (-cos55)
    .equ cos126, (-cos54)
    .equ cos127, (-cos53)
    .equ cos128, (-cos52)
    .equ cos129, (-cos51)
    .equ cos130, (-cos50)
    .equ cos131, (-cos49)
    .equ cos132, (-cos48)
    .equ cos133, (-cos47)
    .equ cos134, (-cos46)
    .equ cos135, (-cos45)
    .equ cos136, (-cos44)
    .equ cos137, (-cos43)
    .equ cos138, (-cos42)
    .equ cos139, (-cos41)
    .equ cos140, (-cos40)
    .equ cos141, (-cos39)
    .equ cos142, (-cos38)
    .equ cos143, (-cos37)
    .equ cos144, (-cos36)
    .equ cos145, (-cos35)
    .equ cos146, (-cos34)
    .equ cos147, (-cos33)
    .equ cos148, (-cos32)
    .equ cos149, (-cos31)
    .equ cos150, (-cos30)      
    .equ cos151, (-cos29)
    .equ cos152, (-cos28)
    .equ cos153, (-cos27)
    .equ cos154, (-cos26)
    .equ cos155, (-cos25)
    .equ cos156, (-cos24)
    .equ cos157, (-cos23)
    .equ cos158, (-cos22)
    .equ cos159, (-cos21)
    .equ cos160, (-cos20)
    .equ cos161, (-cos19)
    .equ cos162, (-cos18)
    .equ cos163, (-cos17)
    .equ cos164, (-cos16)
    .equ cos165, (-cos15)
    .equ cos166, (-cos14)
    .equ cos167, (-cos13)
    .equ cos168, (-cos12)
    .equ cos169, (-cos11)
    .equ cos170, (-cos10)
    .equ cos171, (-cos9)
    .equ cos172, (-cos8)
    .equ cos173, (-cos7)
    .equ cos174, (-cos6)
    .equ cos175, (-cos5)
    .equ cos176, (-cos4)
    .equ cos177, (-cos3)
    .equ cos178, (-cos2)
    .equ cos179, (-cos1) 

    .equ cos0_25, 0xFFFF
    .equ cos0_5,  0xFFFE        
    .equ cos0_75, 0xFFFA
    .equ cos1_25, 0xFFF0
    .equ cos1_5,  0xFFEA        
    .equ cos1_75, 0xFFE1    
    .equ cos2_25, 0xFFCD
    .equ cos2_5,  0xFFC2       
    .equ cos2_75, 0xFFB5        
    .equ cos3_25, 0xFF97
    .equ cos3_5,  0xFF86     
    .equ cos3_75, 0xFF74    
    .equ cos4_25, 0xFF4C
    .equ cos4_5,  0xFF36        
    .equ cos4_75, 0xFF1F        
    .equ cos5_25, 0xFEED
    .equ cos5_5,  0xFED2        
    .equ cos5_75, 0xFEB6    
    .equ cos6_25, 0xFE7A
    .equ cos6_5,  0xFE5B        
    .equ cos6_75, 0xFE3A    
    .equ cos7_25, 0xFDF4
    .equ cos7_5,  0xFDCF        
    .equ cos7_75, 0xFDA9    
    .equ cos8_25, 0xFD5A
    .equ cos8_5,  0xFD30
    .equ cos8_75, 0xFD05    
    .equ cos9_25, 0xFCAC
    .equ cos9_5,  0xFC7D
    .equ cos9_75, 0xFC4D
    .equ cos10_25, 0xFBEA
    .equ cos10_5,  0xFBB7    
    .equ cos10_75, 0xFB82
    .equ cos11_25, 0xFB15
    .equ cos11_5,  0xFADC        
    .equ cos11_75, 0xFAA3
    .equ cos12_25, 0xFA2C
    .equ cos12_5,  0xF9EF    
    .equ cos12_75, 0xF9B0
    .equ cos13_25, 0xF92F
    .equ cos13_5,  0xF8ED
    .equ cos13_75, 0xF8AA
    .equ cos14_25, 0xF820
    .equ cos14_5,  0xF7D9    
    .equ cos14_75, 0xF790
    .equ cos15_25, 0xF6FC
    .equ cos15_5,  0xF6B0
    .equ cos15_75, 0xF663
    .equ cos16_25, 0xF5C6
    .equ cos16_5,  0xF575
    .equ cos16_75, 0xF523
    .equ cos17_25, 0xF47C
    .equ cos17_5,  0xF427
    .equ cos17_75, 0xF3D0
    .equ cos18_25, 0xF31F
    .equ cos18_5,  0xF2C5
    .equ cos18_75, 0xF26A
    .equ cos19_25, 0xF1B0
    .equ cos19_5,  0xF151
    .equ cos19_75, 0xF0F1
    .equ cos20_25, 0xF02D
    .equ cos20_5,  0xEFCA
    .equ cos20_75, 0xEF65
    .equ cos21_25, 0xEE98
    .equ cos21_5,  0xEE30
    .equ cos21_75, 0xEDC6
    .equ cos22_25, 0xECF0
    .equ cos22_5,  0xEC83
    .equ cos22_75, 0xEC15
    .equ cos23_25, 0xEB36
    .equ cos23_5,  0xEAC4
    .equ cos23_75, 0xEA52
    .equ cos24_25, 0xE969
    .equ cos24_5,  0xE8F3
    .equ cos24_75, 0xE87C
    .equ cos25_25, 0xE78A
    .equ cos25_5,  0xE710
    .equ cos25_75, 0xE694
    .equ cos26_25, 0xE599
    .equ cos26_5,  0xE51A
    .equ cos26_75, 0xE49A
    .equ cos27_25, 0xE397
    .equ cos27_5,  0xE313
    .equ cos27_75, 0xE28F
    .equ cos28_25, 0xE182
    .equ cos28_5,  0xE0FA
    .equ cos28_75, 0xE071
    .equ cos29_25, 0xDF5C
    .equ cos29_5,  0xDED0
    .equ cos29_75, 0xDE42
    .equ cos30_25, 0xDD24
    .equ cos30_5,  0xDC94
    .equ cos30_75, 0xDC02
    .equ cos31_25, 0xDADC
    .equ cos31_5,  0xDA47
    .equ cos31_75, 0xD9B1
    .equ cos32_25, 0xD882
    .equ cos32_5,  0xD7E9
    .equ cos32_75, 0xD74E
    .equ cos33_25, 0xD617
    .equ cos33_5,  0xD57A
    .equ cos33_75, 0xD4DB
    .equ cos34_25, 0xD39B
    .equ cos34_5,  0xD2FA
    .equ cos34_75, 0xD257
    .equ cos35_25, 0xD10F
    .equ cos35_5,  0xD06A
    .equ cos35_75, 0xCFC3
    .equ cos36_25, 0xCE73
    .equ cos36_5,  0xCDCA    
    .equ cos36_75, 0xCD1F
    .equ cos37_25, 0xCBC7
    .equ cos37_5,  0xCB19
    .equ cos37_75, 0xCA6B
    .equ cos38_25, 0xC90B
    .equ cos38_5,  0xC859
    .equ cos38_75, 0xC7A7
    .equ cos39_25, 0xC63F
    .equ cos39_5,  0xC589
    .equ cos39_75, 0xC4D3
    .equ cos40_25, 0xC363
    .equ cos40_5,  0xC2AA
    .equ cos40_75, 0xC1F0
    .equ cos41_25, 0xC079
    .equ cos41_5,  0xBFBC
    .equ cos41_75, 0xBEFE
    .equ cos42_25, 0xBD7F
    .equ cos42_5,  0xBCBE
    .equ cos42_75, 0xBBFD
    .equ cos43_25, 0xBA77
    .equ cos43_5,  0xB9B2
    .equ cos43_75, 0xB8ED
    .equ cos44_25, 0xB760
    .equ cos44_5,  0xB698
    .equ cos44_75, 0xB5CF
    .equ cos45_25, 0xB43A
    .equ cos45_5,  0xB36F
    .equ cos45_75, 0xB2A2
    .equ cos46_25, 0xB107
    .equ cos46_5,  0xB038
    .equ cos46_75, 0xAF68
    .equ cos47_25, 0xADC6
    .equ cos47_5,  0xACF3
    .equ cos47_75, 0xAC20
    .equ cos48_25, 0xAA77
    .equ cos48_5,  0xA9A1
    .equ cos48_75, 0xA8CB
    .equ cos49_25, 0xA71B
    .equ cos49_5,  0xA642
    .equ cos49_75, 0xA568
    .equ cos50_25, 0xA3B2
    .equ cos50_5,  0xA2D6
    .equ cos50_75, 0xA1F9
    .equ cos51_25, 0xA03D
    .equ cos51_5,  0x9F5D
    .equ cos51_75, 0x9E7D
    .equ cos52_25, 0x9CBA
    .equ cos52_5,  0x9BD8
    .equ cos52_75, 0x9AF5
    .equ cos53_25, 0x992C
    .equ cos53_5,  0x9846
    .equ cos53_75, 0x9760
    .equ cos54_25, 0x9591
    .equ cos54_5,  0x94A9
    .equ cos54_75, 0x93C0
    .equ cos55_25, 0x91EB
    .equ cos55_5,  0x9100
    .equ cos55_75, 0x9014
    .equ cos56_25, 0x8E3A
    .equ cos56_5,  0x8D4C
    .equ cos56_75, 0x8C5D
    .equ cos57_25, 0x8A7D
    .equ cos57_5,  0x898C
    .equ cos57_75, 0x889B
    .equ cos58_25, 0x86B6
    .equ cos58_5,  0x85C2
    .equ cos58_75, 0x84CE
    .equ cos59_25, 0x82E4
    .equ cos59_5,  0x81EE
    .equ cos59_75, 0x80F7
    .equ cos60_25, 0x7F08
    .equ cos60_5,  0x7E0F
    .equ cos60_75, 0x7D16
    .equ cos61_25, 0x7B22
    .equ cos61_5,  0x7A27
    .equ cos61_75, 0x792B
    .equ cos62_25, 0x7733
    .equ cos62_5,  0x7635
    .equ cos62_75, 0x7537
    .equ cos63_25, 0x733A
    .equ cos63_5,  0x723A
    .equ cos63_75, 0x713A
    .equ cos64_25, 0x6F38
    .equ cos64_5,  0x6E36
    .equ cos64_75, 0x6D34
    .equ cos65_25, 0x6B2D
    .equ cos65_5,  0x6A29
    .equ cos65_75, 0x6925
    .equ cos66_25, 0x671A
    .equ cos66_5,  0x6614
    .equ cos66_75, 0x650E
    .equ cos67_25, 0x62FF
    .equ cos67_5,  0x61F8
    .equ cos67_75, 0x60EF
    .equ cos68_25, 0x5EDD
    .equ cos68_5,  0x5DD3
    .equ cos68_75, 0x5CC9
    .equ cos69_25, 0x5AB3
    .equ cos69_5,  0x59A7
    .equ cos69_75, 0x589B
    .equ cos70_25, 0x5682
    .equ cos70_5,  0x5574
    .equ cos70_75, 0x5467
    .equ cos71_25, 0x524A
    .equ cos71_5,  0x513B
    .equ cos71_75, 0x502C
    .equ cos72_25, 0x4E0C
    .equ cos72_5,  0x4CFB
    .equ cos72_75, 0x4BEA
    .equ cos73_25, 0x49C7
    .equ cos73_5,  0x48B5
    .equ cos73_75, 0x47A3
    .equ cos74_25, 0x457D
    .equ cos74_5,  0x446A
    .equ cos74_75, 0x4356
    .equ cos75_25, 0x412E
    .equ cos75_5,  0x4019
    .equ cos75_75, 0x3F04
    .equ cos76_25, 0x3CD9
    .equ cos76_5,  0x3BC3
    .equ cos76_75, 0x3AAD
    .equ cos77_25, 0x3880
    .equ cos77_5,  0x3769
    .equ cos77_75, 0x3651
    .equ cos78_25, 0x3422
    .equ cos78_5,  0x330A
    .equ cos78_75, 0x31F1
    .equ cos79_25, 0x2FC0
    .equ cos79_5,  0x2EA7
    .equ cos79_75, 0x2D8E
    .equ cos80_25, 0x2B5A
    .equ cos80_5,  0x2A41
    .equ cos80_75, 0x2926
    .equ cos81_25, 0x26F2
    .equ cos81_5,  0x25D7
    .equ cos81_75, 0x24BC
    .equ cos82_25, 0x2286
    .equ cos82_5,  0x216A
    .equ cos82_75, 0x204F
    .equ cos83_25, 0x1E17
    .equ cos83_5,  0x1CFB
    .equ cos83_75, 0x1BDF
    .equ cos84_25, 0x19A6
    .equ cos84_5,  0x1889
    .equ cos84_75, 0x176D
    .equ cos85_25, 0x1533
    .equ cos85_5,  0x1416
    .equ cos85_75, 0x12F9
    .equ cos86_25, 0x10BE
    .equ cos86_5,  0x0FA1
    .equ cos86_75, 0x0E83
    .equ cos87_25, 0x0C48
    .equ cos87_5,  0x0B2B
    .equ cos87_75, 0x0A0D
    .equ cos88_25, 0x07D1
    .equ cos88_5,  0x06B4
    .equ cos88_75, 0x0596
    .equ cos89_25, 0x035A
    .equ cos89_5,  0x023C
    .equ cos89_75, 0x011E
        

.ifdef __UNSIGNED_FIXED_USED__
    ;; ******************
    ;; * UNSIGNED FIXED *
    ;; ******************
	.global	_EE_uint2uf
	.global	_EE_uf2uint	
	.global _EE_uf_mul
	.global _EE_uf_div	
					
	.equ UF_ROUND,	(1<<(EE_UF_NUM_BIT_FRAC-1))			
	
	.section .text
	
	.align 1
_EE_uf2uint:
	    ;; transform fixed fa into integer and return it (in r0)
	    ;; r0=ufa	    
	mov.w	#UF_ROUND, r1
	add.w	r1,r0	
    .rep EE_UF_NUM_BIT_FRAC
	shlr	r0h
	rotxr	r0l    
    .endr
	rts
	
			
	.align 1
_EE_uint2uf:   ;; transform integer i into fixed point and return it (in r0)
	    ;; r0=i	    
    .rep EE_UF_NUM_BIT_FRAC	
	shll	r0l
	rotxl	r0h
    .endr
	rts
					

	.align 1
_EE_uf_mul:	
	    ;; calculate (ufa * ufb) and return it (in r0)
	    ;; r0=ufa
	    ;; r1=ufb	    
	push 	r4
	push	r5
	push	r6
	mov.w 	r0,r6
	;; extend a on 32 bit
	sub.w	r5,r5
	mov.w	r1,r4
	;; extend b on 32 bit
	sub.w	r3,r3		
	jsr	@0x01FE	
	;; r5r6 is now a*b*2^EE_UF_NUM_BIT_FRAC, so shift to obtain the right result (a*b)

    .rept EE_UF_NUM_BIT_FRAC
	shlr	r5h
	rotxr	r5l
	rotxr	r6h
	rotxr	r6l	
    .endr    
	mov.w	r6,r0    
	pop	r6
	pop	r5
	pop	r4
	rts

	
	.align 1
_EE_uf_div:
	    ;; calculate (ufa / ufb) and return it (in r0)
	    ;; r0=ufa
	    ;; r1=ufb	    
	push 	r4
	push	r5
	push	r6
	mov.w 	r0,r6  
	;; extend a on 32 bit
	sub.w	r5,r5
    .rept EE_UF_NUM_BIT_FRAC
	shal	r6l
	rotxl	r6h
	rotxl	r5l
	rotxl	r5h	
    .endr            
	mov.w	r1,r4
	;; extend b on 32 bit
    	sub.w	r3,r3		
	;; calculate (a<<EE_UF_NUM_BIT_FRAC) / b
	jsr	@0x0306	;; a*FP_SIZE/b
	mov.w	r6, r0 			
	pop 	r6
	pop	r5
	pop	r4
	rts	
	
.endif /* __UNSIGNED_FIXED_USED__ */




.ifdef __SIGNED_FIXED_USED__
    ;; ****************
    ;; * SIGNED FIXED *
    ;; ****************


    	.global	_EE_int2sf
	.global	_EE_sf2int
	.global _EE_sf_mul
	.global _EE_sf_div
	.global _EE_sf_negate

	
	.equ SF_ROUND,	(1<<(EE_SF_NUM_BIT_FRAC-1))	
	
	

.ifdef __SF_TRIG_USED__

	.global _EE_sf_sin
	.global _EE_sf_cos
	
	.equ K,  (16-EE_SF_NUM_BIT_FRAC)	   ;; shift	
	.equ K1, (1<<(16-EE_SF_NUM_BIT_FRAC-1)) ;; round before shift	
	.equ Kn, (0xFFFF << EE_SF_NUM_BIT_FRAC) ;; add if value is negative	

	.section .rodata

	.global	_EE_sf_table_cos	
	
    _EE_sf_table_cos:
        .int 1 << EE_SF_NUM_BIT_FRAC	;; cos(0)=1
	.int (cos1+K1)>>K,   (cos2+K1)>>K,   (cos3+K1)>>K,   (cos4+K1)>>K,   (cos5+K1)>>K
	.int (cos6+K1)>>K,   (cos7+K1)>>K,   (cos8+K1)>>K,   (cos9+K1)>>K	
	.int (cos10+K1)>>K,  (cos11+K1)>>K,  (cos12+K1)>>K,  (cos13+K1)>>K,  (cos14+K1)>>K
	.int (cos15+K1)>>K,  (cos16+K1)>>K,  (cos17+K1)>>K,  (cos18+K1)>>K,  (cos19+K1)>>K
	.int (cos20+K1)>>K,  (cos21+K1)>>K,  (cos22+K1)>>K,  (cos23+K1)>>K,  (cos24+K1)>>K
	.int (cos25+K1)>>K,  (cos26+K1)>>K,  (cos27+K1)>>K,  (cos28+K1)>>K,  (cos29+K1)>>K
	.int (cos30+K1)>>K,  (cos31+K1)>>K,  (cos32+K1)>>K,  (cos33+K1)>>K,  (cos34+K1)>>K
	.int (cos35+K1)>>K,  (cos36+K1)>>K,  (cos37+K1)>>K,  (cos38+K1)>>K,  (cos39+K1)>>K
	.int (cos40+K1)>>K,  (cos41+K1)>>K,  (cos42+K1)>>K,  (cos43+K1)>>K,  (cos44+K1)>>K
	.int (cos45+K1)>>K,  (cos46+K1)>>K,  (cos47+K1)>>K,  (cos48+K1)>>K,  (cos49+K1)>>K
	.int (cos50+K1)>>K,  (cos51+K1)>>K,  (cos52+K1)>>K,  (cos53+K1)>>K,  (cos54+K1)>>K
	.int (cos55+K1)>>K,  (cos56+K1)>>K,  (cos57+K1)>>K,  (cos58+K1)>>K,  (cos59+K1)>>K
	.int (cos60+K1)>>K,  (cos61+K1)>>K,  (cos62+K1)>>K,  (cos63+K1)>>K,  (cos64+K1)>>K
	.int (cos65+K1)>>K,  (cos66+K1)>>K,  (cos67+K1)>>K,  (cos68+K1)>>K,  (cos69+K1)>>K
	.int (cos70+K1)>>K,  (cos71+K1)>>K,  (cos72+K1)>>K,  (cos73+K1)>>K,  (cos74+K1)>>K
	.int (cos75+K1)>>K,  (cos76+K1)>>K,  (cos77+K1)>>K,  (cos78+K1)>>K,  (cos79+K1)>>K
	.int (cos80+K1)>>K,  (cos81+K1)>>K,  (cos82+K1)>>K,  (cos83+K1)>>K,  (cos84+K1)>>K
	.int (cos85+K1)>>K,  (cos86+K1)>>K,  (cos87+K1)>>K,  (cos88+K1)>>K,  (cos89+K1)>>K
	.int 0x0000			;; (cos(90)=0  
	.int (cos91+K1)>>K|Kn,  (cos92+K1)>>K|Kn,  (cos93+K1)>>K|Kn,  (cos94+K1)>>K|Kn,  (cos95+K1)>>K|Kn
	.int (cos96+K1)>>K|Kn,  (cos97+K1)>>K|Kn,  (cos98+K1)>>K|Kn,  (cos99+K1)>>K|Kn
	.int (cos100+K1)>>K|Kn, (cos101+K1)>>K|Kn, (cos102+K1)>>K|Kn, (cos103+K1)>>K|Kn, (cos104+K1)>>K|Kn
	.int (cos105+K1)>>K|Kn, (cos106+K1)>>K|Kn, (cos107+K1)>>K|Kn, (cos108+K1)>>K|Kn, (cos109+K1)>>K|Kn
	.int (cos110+K1)>>K|Kn, (cos111+K1)>>K|Kn, (cos112+K1)>>K|Kn, (cos113+K1)>>K|Kn, (cos114+K1)>>K|Kn
	.int (cos115+K1)>>K|Kn, (cos116+K1)>>K|Kn, (cos117+K1)>>K|Kn, (cos118+K1)>>K|Kn, (cos119+K1)>>K|Kn
	.int (cos120+K1)>>K|Kn, (cos121+K1)>>K|Kn, (cos122+K1)>>K|Kn, (cos123+K1)>>K|Kn, (cos124+K1)>>K|Kn
	.int (cos125+K1)>>K|Kn, (cos126+K1)>>K|Kn, (cos127+K1)>>K|Kn, (cos128+K1)>>K|Kn, (cos129+K1)>>K|Kn
	.int (cos130+K1)>>K|Kn, (cos131+K1)>>K|Kn, (cos132+K1)>>K|Kn, (cos133+K1)>>K|Kn, (cos134+K1)>>K|Kn
	.int (cos135+K1)>>K|Kn, (cos136+K1)>>K|Kn, (cos137+K1)>>K|Kn, (cos138+K1)>>K|Kn, (cos139+K1)>>K|Kn
	.int (cos140+K1)>>K|Kn, (cos141+K1)>>K|Kn, (cos142+K1)>>K|Kn, (cos143+K1)>>K|Kn, (cos144+K1)>>K|Kn
	.int (cos145+K1)>>K|Kn, (cos146+K1)>>K|Kn, (cos147+K1)>>K|Kn, (cos148+K1)>>K|Kn, (cos149+K1)>>K|Kn
	.int (cos150+K1)>>K|Kn, (cos151+K1)>>K|Kn, (cos152+K1)>>K|Kn, (cos153+K1)>>K|Kn, (cos154+K1)>>K|Kn
	.int (cos155+K1)>>K|Kn, (cos156+K1)>>K|Kn, (cos157+K1)>>K|Kn, (cos158+K1)>>K|Kn, (cos159+K1)>>K|Kn
	.int (cos160+K1)>>K|Kn, (cos161+K1)>>K|Kn, (cos162+K1)>>K|Kn, (cos163+K1)>>K|Kn, (cos164+K1)>>K|Kn
	.int (cos165+K1)>>K|Kn, (cos166+K1)>>K|Kn, (cos167+K1)>>K|Kn, (cos168+K1)>>K|Kn, (cos169+K1)>>K|Kn
	.int (cos170+K1)>>K|Kn, (cos171+K1)>>K|Kn, (cos172+K1)>>K|Kn, (cos173+K1)>>K|Kn, (cos174+K1)>>K|Kn
	.int (cos175+K1)>>K|Kn, (cos176+K1)>>K|Kn, (cos177+K1)>>K|Kn, (cos178+K1)>>K|Kn, (cos179+K1)>>K|Kn
	.int 0xFFFF << EE_SF_NUM_BIT_FRAC	;; cos(180)=-1

	.section .text


	.align 1
__sfr0mod360:	
	    ;; (called by _EE_sf_EE_sin, _EE_sf_cos, df_trig)
	    ;; calculate (r0 mod 360) and return it (in r0)
	    ;; r0 is an integer
	push	r5
	push	r6	
	mov.w	#360, r5
	mov.w	r0, r6
	jsr	@0x0188		;; this ROM routine changes r5 without saving it!!!!!
	mov.w	r6,r0
	bpl	sfr0m_go1
	mov.w	#360, r5	
	add.w	r5,r6		
    sfr0m_go1:
	mov.w	r6,r0
	pop	r6
	pop	r5
	rts
	
	
	.align 1	
_EE_sf_sin:
	    ;; calculate sin(theta) and return it (in r0)	    
	    ;; r0= theta (integer)
	    ;; NOTE: if you define __SF_HIGH_SPEED_TRIG_USED__, it is assumed that
	    ;;       0<= theta < 360
	    ;; if you can't assure it, don't define that macro, or wrong result will come!
	    
.ifndef __SF_HIGH_SPEED_TRIG_USED__
	jsr	@__sfr0mod360
.endif		
	;; sin(x)=cos(x-90)
	mov.w	#90, r1
	sub.w	r1,r0
	bcc	sftrig_go0
	mov.w	#360,r1
	add.w	r1, r0	
	bt	sftrig_go0
	;; N.B. _EE_sf_sin dosn't return and start calculating cos(x-90) (optimization)

_EE_sf_cos:	
	    ;; calculate cos(theta) and return it (in r0)	    
	    ;; r0= theta  (integer)
	    ;; NOTE: if you define __SF_HIGH_SPEED_TRIG_USED__, it is assumed that
	    ;;       0<= theta < 360
	    ;; if you can't assure it, don't define that macro, or wrong result will come!

.ifndef __SF_HIGH_SPEED_TRIG_USED__
	jsr	@__sfr0mod360
.endif			

    sftrig_go0:			
	add.w	r0,r0		;; r0 used as index of table; each element is 2bytes (r0*2)
	mov.w	#360, r1
	cmp.w	r1, r0
	bhi	sftrig_go1
	;; 0 <= theta <= 180	
	mov.w	@(_EE_sf_table_cos, r0), r0
	bt	sftrig_end
    sftrig_go1:
	;; 180 < theta < 360
	sub.w	r1,r1
	sub.w	r0,r1
	mov.w	@(_EE_sf_table_cos+720, r1), r0	
    sftrig_end:
	rts
.endif /* __SF_TRIG_USED__ */


	
	.align 1
_EE_sf2int:
	    ;; transform fixed fa into integer and return it
	    ;; r0=fa
	    ;; result in r0
	mov.w	#SF_ROUND, r1
	add.w	r1,r0	
    .rept EE_SF_NUM_BIT_FRAC
	shar	r0h
	rotxr	r0l
    .endr
    	rts
	
		
	.align 1
_EE_int2sf:
	    ;; transform integer i into fixed point and return it (in r0)
	    ;; r0= integer to be converted	    
    .rept EE_SF_NUM_BIT_FRAC
	shll	r0l
	rotxl	r0h
    .endr
	rts
	
	
	.align 1
_EE_sf_negate:
	    ;; change sign of sfa
	    ;; r0=sfa
	    ;; result in r0	    
	not	r0l
	not	r0h
	adds	#1,r0
	rts		    		


	.align 1
_EE_sf_mul:	
	    ;; calculate (fa * fb) and return it (in r0)
	    ;; r0=fa
	    ;; r1=fb	    
	push 	r4
	push	r5
	push	r6
	mov.w 	r0,r6
	;; extend a on 32 bit: if MSB==1 => r5=0xFFFF else r5=0x0000
	sub.w	r5,r5
	btst	#7,r6h
	beq	fmbeq1
	mov.w	#0xFFFF,r5
	;; now r5r6 is a expressed on 32bit
    fmbeq1:				
	mov.w	r1,r4
	;; extend b on 32 bit: if MSB==1 => r3=0xFFFF else r3=0x0000
    	sub.w	r3,r3	
	btst	#7,r4h
	beq	fmbeq2
	mov.w	#0xFFFF,r3
	;; now r3r4 is b expressed on 32bit
    fmbeq2:						
	jsr	@0x01FE	
	;; r5r6 is now a*b*2^EE_SF_NUM_BIT_FRAC, so shift to obtain the right result (a*b)
    .rept EE_SF_NUM_BIT_FRAC
	shar	r5h
	rotxr	r5l
	rotxr	r6h
	rotxr	r6l	
    .endr    
	mov.w	r6,r0    
	pop	r6
	pop	r5
	pop	r4
    rts


    .align 1
_EE_sf_div:
	    ;; calculate (fa / fb) := (fa<<EE_SF_NUM_BIT_FRAC)/fb and return it (in r0)
	    ;; r0=fa
	    ;; r1=fb	
	push	r4
	push	r5
	push	r6
	mov.w 	r0,r6  
	;; extend a on 32 bit: if MSB==1 => r5=0xFFFF else r5=0x0000
	sub.w	r5,r5
	btst	#7,r6h
	beq	fdbeq1
	mov.w	#0xFFFF,r5
	;; shift r5r6
    fdbeq1:		
    .rept EE_SF_NUM_BIT_FRAC	
	shal	r6l
	rotxl	r6h
	rotxl	r5l
	rotxl	r5h	
    .endr
	mov.w	r1,r4
	;; extend b on 32 bit: if MSB==1 => r3=0xFFFF else r3=0x0000
    	sub.w	r3,r3	
	btst	#7,r4h
	beq	fdbeq2
	mov.w	#0xFFFF,r3	
    fdbeq2:						
	;; calculate (a<<EE_SF_NUM_BIT_FRAC) / b
	jsr	@0x026E	;; a*FP_SIZE/b (r5r6=r5r6/r3r4)
	mov.w	r6, r0 			
	pop 	r6
	pop	r5
	pop	r4
	rts	
.endif /* __SIGNED_FIXED_USED__ */
	
	

.ifdef __DOUBLE_FIXED_USED__	
    
    ;; *************************
    ;; * DOUBLE FIXED (signed) *
    ;; *************************

	.global _EE_int2df
	.global _EE_df2int
	.global _EE_df_cmp
	.global _EE_df_negate	
	.global _EE_df_add    
	.global _EE_df_sub    	
	.global _EE_df_mul	
	.global _EE_df_div		
				    	
	.equ	DF_NUM_BIT_FRAC, 16	;; this value can't be modified (16bit IP, 16bit FP)
	.equ	DF_ROUND, (1<<(DF_NUM_BIT_FRAC-1))
	
.ifdef __DF_TRIG_USED__	

	/* const used by trigonometric functions */
	.equ	n, 4	;; number of intervals into base interval (0,1) degrees
	.equ	quad1, 90 * n * 2
	.equ	quad2,180 * n * 2
	.equ 	quad3,270 * n * 2
	.equ	quad4,360 * n * 2
	
	.section .rodata
	
	.global	_EE_df_table_cos
    _EE_df_table_cos:    ;; ((90*n)) elements (here n=4: 360elements*2byte = 720bytes needed)
	    .int cos0,  cos0_25,  cos0_5,  cos0_75,  cos1,  cos1_25,  cos1_5,  cos1_75
	    .int cos2,  cos2_25,  cos2_5,  cos2_75,  cos3,  cos3_25,  cos3_5,  cos3_75	    
	    .int cos4,  cos4_25,  cos4_5,  cos4_75,  cos5,  cos5_25,  cos5_5,  cos5_75	    
	    .int cos6,  cos6_25,  cos6_5,  cos6_75,  cos7,  cos7_25,  cos7_5,  cos7_75	    
	    .int cos8,  cos8_25,  cos8_5,  cos8_75,  cos9,  cos9_25,  cos9_5,  cos9_75	    
	    .int cos10, cos10_25, cos10_5, cos10_75, cos11, cos11_25, cos11_5, cos11_75	    
	    .int cos12, cos12_25, cos12_5, cos12_75, cos13, cos13_25, cos13_5, cos13_75	    
	    .int cos14, cos14_25, cos14_5, cos14_75, cos15, cos15_25, cos15_5, cos15_75
	    .int cos16, cos16_25, cos16_5, cos16_75, cos17, cos17_25, cos17_5, cos17_75
	    .int cos18, cos18_25, cos18_5, cos18_75, cos19, cos19_25, cos19_5, cos19_75	    
	    .int cos20, cos20_25, cos20_5, cos20_75, cos21, cos21_25, cos21_5, cos21_75	    
	    .int cos22, cos22_25, cos22_5, cos22_75, cos23, cos23_25, cos23_5, cos23_75	    
	    .int cos24, cos24_25, cos24_5, cos24_75, cos25, cos25_25, cos25_5, cos25_75	    
	    .int cos26, cos26_25, cos26_5, cos26_75, cos27, cos27_25, cos27_5, cos27_75	    
	    .int cos28, cos28_25, cos28_5, cos28_75, cos29, cos29_25, cos29_5, cos29_75	    
	    .int cos30, cos30_25, cos30_5, cos30_75, cos31, cos31_25, cos31_5, cos31_75
	    .int cos32, cos32_25, cos32_5, cos32_75, cos33, cos33_25, cos33_5, cos33_75
	    .int cos34, cos34_25, cos34_5, cos34_75, cos35, cos35_25, cos35_5, cos35_75	    
	    .int cos36, cos36_25, cos36_5, cos36_75, cos37, cos37_25, cos37_5, cos37_75	    
	    .int cos38, cos38_25, cos38_5, cos38_75, cos39, cos39_25, cos39_5, cos39_75	    
	    .int cos40, cos40_25, cos40_5, cos40_75, cos41, cos41_25, cos41_5, cos41_75	    
	    .int cos42, cos42_25, cos42_5, cos42_75, cos43, cos43_25, cos43_5, cos43_75	    
	    .int cos44, cos44_25, cos44_5, cos44_75, cos45, cos45_25, cos45_5, cos45_75	    
	    .int cos46, cos46_25, cos46_5, cos46_75, cos47, cos47_25, cos47_5, cos47_75
	    .int cos48, cos48_25, cos48_5, cos48_75, cos49, cos49_25, cos49_5, cos49_75
	    .int cos50, cos50_25, cos50_5, cos50_75, cos51, cos51_25, cos51_5, cos51_75	    
	    .int cos52, cos52_25, cos52_5, cos52_75, cos53, cos53_25, cos53_5, cos53_75	    
	    .int cos54, cos54_25, cos54_5, cos54_75, cos55, cos55_25, cos55_5, cos55_75	    
	    .int cos56, cos56_25, cos56_5, cos56_75, cos57, cos57_25, cos57_5, cos57_75	    
	    .int cos58, cos58_25, cos58_5, cos58_75, cos59, cos59_25, cos59_5, cos59_75	    
	    .int cos60, cos60_25, cos60_5, cos60_75, cos61, cos61_25, cos61_5, cos61_75	    
	    .int cos62, cos62_25, cos62_5, cos62_75, cos63, cos63_25, cos63_5, cos63_75
	    .int cos64, cos64_25, cos64_5, cos64_75, cos65, cos65_25, cos65_5, cos65_75
	    .int cos66, cos66_25, cos66_5, cos66_75, cos67, cos67_25, cos67_5, cos67_75	    
	    .int cos68, cos68_25, cos68_5, cos68_75, cos69, cos69_25, cos69_5, cos69_75	    
	    .int cos70, cos70_25, cos70_5, cos70_75, cos71, cos71_25, cos71_5, cos71_75	    
	    .int cos72, cos72_25, cos72_5, cos72_75, cos73, cos73_25, cos73_5, cos73_75	    
	    .int cos74, cos74_25, cos74_5, cos74_75, cos75, cos75_25, cos75_5, cos75_75	    
	    .int cos76, cos76_25, cos76_5, cos76_75, cos77, cos77_25, cos77_5, cos77_75	    
	    .int cos78, cos78_25, cos78_5, cos78_75, cos79, cos79_25, cos79_5, cos79_75
	    .int cos80, cos80_25, cos80_5, cos80_75, cos81, cos81_25, cos81_5, cos81_75
	    .int cos82, cos82_25, cos82_5, cos82_75, cos83, cos83_25, cos83_5, cos83_75	    
	    .int cos84, cos84_25, cos84_5, cos84_75, cos85, cos85_25, cos85_5, cos85_75	    
	    .int cos86, cos86_25, cos86_5, cos86_75, cos87, cos87_25, cos87_5, cos87_75	    
	    .int cos88, cos88_25, cos88_5, cos88_75, cos89, cos89_25, cos89_5, cos89_75	    
	    .int cos90
	    
	.section .text

	.global __df_trigon

	.align 1
__df_trigon:
	    ;; calculate cos(dftheta) or sin(dftheta) and store it into dfs
	    ;; r0= address of dfs
	    ;; r1= address of dftheta (no limitation: -oo <= dftheta <= +oo)	    
	    ;; r2= 0 (if you want calculate cos), 90 (if you want calculate sin)

	push	r5
	push	r6
	mov.w 	@(2,r1), r3	;; dftheta.fp
	mov.w	@r1, r6		;; dftheta.ip

.ifndef __DF_HIGH_SPEED_TRIG_USED__
	mov.w	#360, r5	
	;; r6=(r6 mod r5)
	jsr	@0x0188		;; this ROM routine changes r5 without saving it!!!!!
	btst	#7,r6h
	beq	dfr0m_go1
	mov.w	#360, r5	
	add.w	r5,r6		
    dfr0m_go1:	
.endif
	cmp.b	#0,r2l
	beq	dftrig_go00	;; branch if cos is needed
	sub.w	r2,r6
	bcc	dftrig_go00
	mov.w	#360, r2
	add.w	r2,r6
    dftrig_go00:

	;; calculate (n*dftheta). (granularity = 1/n)
    .rept (2)	;; log n = 2 (n=4)
	shll  	r3l
	rotxl	r3h
	rotxl	r6l
	rotxl	r6h
    .endr
	;; round(n * dftheta)
	mov.w	#DF_ROUND, r5
	add.w	r5,r3
	bcc	dftrig_go1
	adds	#1,r6
    dftrig_go1:
	;; r6 is now index of df_table_cos 
	;; each element of table is 2 byte so multiply r6 by 2
	add.w	r6,r6
	bne	dftrig_go11
	;; dftheta==0
	mov.w	#1,r5
	sub.w	r1,r1
	bt	dftrig_end				;; cos(0)=1
    dftrig_go11:
    ;; get result from table
	mov.w	#quad1, r3
	cmp.w	r3, r6
	bhi	dftrig_go2
        ;; 0 < dftheta <= 90
	sub.w	r5, r5					;; r5 stores dfs.ip
	mov.w	@(_EE_df_table_cos,r6), r1			;; r1 stores dfs.fp	
	bt	dftrig_end
    dftrig_go2:
	mov.w   #quad2, r3
	cmp.w	r3, r6	
	bhi	dftrig_go3
	;; 90 < dftheta <= 180	
	sub.w	r3,r3
	sub.w	r6,r3
	mov.w	@(_EE_df_table_cos+(180*n*2),r3), r1	;; r1 stores dfs.fp	
	bt	dftrig_compl
    dftrig_go3:
	mov.w   #quad3, r3
	cmp.w	r3, r6
	bcc	dftrig_go4
	;; 180 < dftheta < 270	
	mov.w	@(_EE_df_table_cos-(180*n*2),r6), r1	;; r1 stores dfs.fp		
	bt	dftrig_compl
    dftrig_go4:        
	;; 270 <= dftheta < 360
	sub.w	r5,r5					;; r5 stores dfs.ip			;; r5 stores dfs.ip
	sub.w	r3,r3
	sub.w	r6,r3    
	mov.w	@(_EE_df_table_cos+(360*n*2),r3), r1	;; r1 stores dfs.fp	    	
	bt	dftrig_end
    dftrig_compl:
	;; dfs.ip=-1
	mov.w	#0xFFFF, r5
	;; complement dfs.fp
	sub.w	r3,r3
	sub.w	r1,r3	
	mov.w	r3,r1
    dftrig_end:	
	mov.w	r5, @r0
	mov.w	r1, @(2,r0)
	pop	r6
	pop	r5
	rts
.endif /* __DF_TRIG_USED__ */

		
	.align 1
_EE_df2int:
	    ;; convert dfa into 16 bit signed integer and return it (in r0)
	    ;; r0= address of dfa	    
	    
	mov.w	#DF_ROUND, r1
	mov.w	@(2,r0), r2
	add.w	r1,r2
	mov.w	@r0, r0
	bcc	df2i_go1
	adds	#1, r0
    df2i_go1:
	rts



	.align 1
_EE_int2df:
	    ;; convert 16 bit signed integer into double fixed and store it into dfa
	    ;; r0= address of dfa	    
	    ;; r1= integer to convert
	mov.w 	r1, @r0
	sub.w	r1, r1
	mov.w	r1, @(2,r0)
	rts
	
	    
	.align 1
_EE_df_negate:
	    ;; change sign of dfa
	    ;; r0= address of result (dfc)
	    ;; r1= address of dfa	    

	mov.w	@(2,r1), r2
	sub.w	r3,r3
	sub.w	r2, r3
	mov.w	r3, @(2,r0)	;; store res.fp
	mov.w	@r1, r2
	bcc	dfn_go1
	adds	#1,r2
    dfn_go1:
	sub.w	r3,r3
	sub.w	r2,r3	
	mov.w	r3,@r0		;; store res.ip
	rts	
	
	
	.align 1
_EE_df_cmp:
	    ;; compare dfa,dfb and return (in r0): -1,0,1 if dfa<dfb,dfa==dfb,dfa>dfb
	    ;; r0= address of dfa
	    ;; r1= address of dfb	    
    
	mov.w	@(2,r0), r2
	mov.w   @(2,r1), r3
	sub.w	r3,r2		;; dfa.fp-dfb.fp
	mov.w	@r0, r2
	mov.w	@r1,r3
	bcc	dfc_go1
	adds	#1, r3
    dfc_go1:
	sub.w	r3, r2		;; dfa.ip-dfb.ip	
	bgt	dfc_greater
	blt	dfc_less
	sub.w	r0, r0
	bt	dfc_end
    dfc_greater:
	mov.w	#1, r0
	bt	dfc_end
    dfc_less:
	mov.w	#-1, r0		
    dfc_end:
	rts	

	.align 1
_EE_df_add:
	    ;; store into dfc, (dfa+dfb) 
	    ;; r0= address of result (dfc)
	    ;; r1= address of dfa
	    ;; r2= address of dfb

	push	r4
	mov.w	@(2,r1), r3
	mov.w	@(2,r2), r4
	add.w	r3,r4
	mov.w	r4,@(2,r0)	;; store res.fp
	mov.w	@r1, r3
	mov.w	@r2, r4
	bcc	dfa_go1
	adds	#1, r3
    dfa_go1:
	add.w	r3,r4
	mov.w	r4,@r0		;; store res.ip	
	pop	r4
	rts	


	.align 1
_EE_df_sub:
	    ;; store into dfc, (dfa-dfb) 
	    ;; r0= address of result (dfc)
	    ;; r1= address of dfa
	    ;; r2= address of dfb
	push	r4		
	mov.w	@(2,r1), r3
	mov.w	@(2,r2), r4
	sub.w	r4,r3
	mov.w	r3,@(2,r0)	;; store res.fp
	mov.w	@r1, r3
	mov.w	@r2, r4
	bcc	dfs_go1
	adds	#1, r4
    dfs_go1:
	sub.w	r4,r3
	mov.w	r3,@r0		;; store res.ip	
	pop	r4
	rts	
				

	.align 1
_EE_df_mul:
	    ;; calculate (dfa * dfb) and store it into dfc
	    ;; r0= address of result (dfc)
	    ;; r1= address of dfa
	    ;; r2= address of dfb
	    
	push	r6
	mov.w	r7,r6
	mov.w	#8,r3
	sub.w	r3,sp
	push	r4
	push	r5	
	push	r0

	mov.w	@(2,r1),r0
	mov.w	r0,@(-2,r6)	;; @(-2,r6)=dfa.fp

	mov.w	@(2,r2),r0
	mov.w	r0,@(-6,r6)	;; @(-6,r6)=dfb.fp

	mov.w	@r1,r0
	bld	#7, r0h		;; sign of dfa into carry		
	mov.w	r0,@(-4,r6)	;; @(-4,r6)=dfa.ip

	mov.w	@r2,r0
	bxor	#7, r0h		;; (sign(dfa) xor sign(dfb)) into carry
	bst	#0,r3l		
	push	r3		;; store sign of result into bit 0 of a pushed word 
	mov.w	r0,@(-8,r6)	;; @(-8,r6)=dfb.ip	
	    
        ;; abs dfa
        mov.w	@(-4,r6), r0
	btst	#7, r0h
	beq	dfm_go1
	;; negate dfa
	mov.w	@(-2,r6), r0
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-2,r6)
	mov.w	@(-4,r6), r0
	bcc	dfm_go2
	adds	#1, r0
    dfm_go2:	
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-4,r6)
    dfm_go1:
        ;; abs dfb
	mov.w	@(-8,r6), r0
	btst	#7, r0h
	beq	dfm_go3
	;; negate dfb
	mov.w	@(-6,r6), r0
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-6,r6)
	mov.w	@(-8,r6), r0
	bcc	dfm_go4
	adds	#1, r0
    dfm_go4:
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-8,r6)
    dfm_go3:
    	;; use r2 instead of r6 (used by multiplication ROM routine)
	mov 	r6, r2
    ;; -----------------------------------------------	
    ;; calculate result: four multiplication needed
    ;; -----------------------------------------------    	    		
        ;; dfa.fp * dfb.fp (r5r6 = r5r6 * r3r4)
	mov.w 	@(-6,r2),r4	// @(-6,r2)= dfb.fp
	sub.w	r3,r3	    			
	mov.w	@(-2,r2), r6	// @(-2,r2)= dfa.fp
	sub.w	r5,r5
	jsr	@0x01FE			
	mov.w	r5, r1	// r1= dfres.fp
	        ;; dfa.ip * dfb.fp (r5r6 = r5r6 * r3r4)
	mov.w 	@(-6,r2),r4	// @(-6,r2)= dfb.fp 	
	sub.w	r3,r3	    			
	mov.w	@(-4,r2), r6	// @(-4,r2)= dfa.ip
	sub.w	r5, r5	
	jsr	@0x01FE
	add.w	r6, r1		;; r1=dfres.fp
	addx	#0, r5l
	addx	#0, r5h
	mov.w	r5, r0		;; r0=dfres.ip
	
        ;; dfa.fp * dfb.ip (r5r6 = r5r6 * r3r4)
	mov.w 	@(-8,r2),r4	// @(-8,r2)= dfb.ip
	sub.w	r3,r3	    			
	mov.w	@(-2,r2), r6	// @(-2,r2)= dfa.fp
	sub.w	r5, r5	
	jsr	@0x01FE
	add.w	r6, r1		
	addx	#0, r5l
	addx	#0, r5h
	add.w	r5, r0
        ;; dfa.ip * dfb.ip (r5r6 = r5r6 * r3r4)
	mov.w 	@(-8,r2),r4	// @(-8,r2)= dfb.ip
	sub.w	r3,r3	    			
	mov.w	@(-4,r2), r6	// @(-4,r2)= dfa.ip
	sub.w	r5, r5	
	jsr	@0x01FE
	add.w	r6, r0				

    ;; -------------
    ;; return result
    ;; -------------		    			
	;; check if result must be negative (that is stored in r2 (0:pos,1:neg)	
	pop	r3		;; resume sign from stack	
	pop	r2		;; resume address of result (originally in r0)
	btst	#0, r3l
	bne	dfm_go5
	mov.w	r0, r3
	mov.w	r1, r4	
	bt	dfm_end
    dfm_go5:	
	;; complement result (r0=res.ip; r1=res.fp)	
	sub.w	r4,r4
	sub.w	r1,r4		
	bcc	dfm_go6
	adds	#1, r0
    dfm_go6:
	sub.w	r3,r3
	sub.w	r0,r3
    dfm_end:

	mov.w	r3, @r2
	mov.w	r4, @(2,r2)	    	
	pop	r5
	pop	r4
	mov.w	#8,r3
	add.w	r3,sp
	pop	r6
	rts
			

	.align 1
_EE_df_div:
	    ;; calculate (dfa / dfb) and store it into dfc
	    ;; r0= address of result (dfc)
	    ;; r1= address of dfa
	    ;; r2= address of dfb

	push	r6
	mov.w	r7,r6
	mov.w	#12,r3
	sub.w	r3,sp
	push	r4
	push	r5
	
	push	r0

	mov.w	@(2,r1),r0
	mov.w	r0,@(-6,r6)	;; @(-6,r6)=dfa.fp

	mov.w	@(2,r2),r0
	mov.w	r0,@(-10,r6)	;; @(-10,r6)=dfb.fp

	mov.w	@r1,r0
	bld	#7, r0h		;; sign of dfa into carry		
	mov.w	r0,@(-8,r6)	;; @(-8,r6)=dfa.ip

	mov.w	@r2,r0
	bxor	#7, r0h		;; (sign(dfa) xor sign(dfb)) into carry
	bst	#0,r3l		
	push	r3		;; store sign of result into bit 0 of a pushed word 
	mov.w	r0,@(-12,r6)	;; @(-12,r6)=dfb.ip	
	    
        ;; abs dfa
	mov.w	@(-8,r6), r0
	btst	#7, r0h
	beq	dfd_go19
	;; negate dfa
	mov.w	@(-6,r6), r0
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-6,r6)
	mov.w	@(-8,r6), r0
	bcc	dfd_go29
	adds	#1, r0
    dfd_go29:	
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-8,r6)
    dfd_go19:
    
        ;; abs dfb
	mov.w	@(-12,r6), r0
	btst	#7, r0h
	beq	dfd_go39
	;; negate dfb
	mov.w	@(-10,r6), r0
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-10,r6)
	mov.w	@(-12,r6), r0
	bcc	dfd_go49
	adds	#1, r0
    dfd_go49:
	sub.w	r3,r3
	sub.w	r0,r3
	mov.w	r3, @(-12,r6)
    dfd_go39:
				
	;; ----------------------------------    
	;; calculate integer part of division
	;; ----------------------------------
    	mov.w	@(-10,r6),r4	// @(-10,r6)= dfb.fp
	mov.w	@(-12,r6),r3	// @(-12,r6)= dfb.ip
	mov.w 	@(-8,r6),r5	// @(-8,r6)= dfa.ip
	push	r6
	mov.w	@(-6,r6),r6	// @(-6,r6)= dfa.fp
	jsr	@0x0306	;; 32bit division(unsigned)						
	mov.w	r6, r4
	pop	r6		
	;; now we have that: r5=quoz16MSB  r4=quoz16LSB
	;; store dfres.ip (signed)				
	push	r4		// push ip part of result 
	
	;; ----------------------------------------------------
	;; calculate fractional part of division
	;; I procede comparing rest of division with divisor:
	;; if rest>=divisor 1 is a digit of quozient, else 0.
	;; It is just like you make manual division, I think...
	;; ----------------------------------------------------		
			    		
    	;; calculate r=abs(dfa)-(abs(dfb)*abs(quoz))
	  ;; mov.w  r4,r4		; r4= quoz16LSB
 	mov.w	r5,r3	 	; r5= quoz16MSB	
	mov.w 	@(-12,r6),r5	// @(-12,r6)= dfb.ip		
	push	r6
	mov.w	@(-10,r6),r6	// @(-10,r6)= dfb.fp
	jsr	@0x01FE
 	mov.w	r6,r4
	pop	r6
	mov.w	r5,@(-4,r6)	// @(-4,r6)= r.ip
	mov.w	r4,@(-2,r6)	// @(-2,r6)= r.fp			    		

	mov.w  	@(-8,r6), r2	// @(-8,r6)=dfa.ip						
	mov.w  	@(-6,r6), r1	// @(-6,r6)=dfa.fp		
	sub.w	r4, r1	 
	bcc	dfd_go11
	adds	#1, r5  	;; if borrow then increment r4
				;; see NOTE more over about this operation
    dfd_go11:
	sub.w	r5, r2  		
	;; now we have that: r2=r.ip  r1=r.fp
		
	;; init r3 
	mov.w	@(-10,r6), r3	// @(-10,r6)= dfb.fp (used to store dfb.fp)
	;; init r0 (used to store dfres.ip)
	sub.w	r0,r0
		
	;; To reduce as much as possible execution time two cycles are used.
	;; Optimizations showed whereas they are.		

	;; first cycle
	;; init cycle counter
	mov.b #7, r5h				    
    dfd_cycle1:				
	mov.w	@(-12,r6), r4	// @(-12,r6)= dfb.ip								
	shal	r1l
	rotxl	r1h
	rotxl	r2l
	rotxl	r2h
	bst	#0, r5l
	push 	r1
	push	r2
			
	sub.w	r3, r1	;; (r.fp<<1) - dfb.fp
	bcc	dfd_go33
	adds	#1, r4  	;; if borrow then increment r4
				;; NOTE: this add never causes a carry since MSB of r4 is 0.
				;; (so even if you store bit sign somewhere else, be sure that
				;;  you don't use this bit to increase the range of your fixed
				;;  number,becouse it will not work properly... and you will
				;;  get the same problem that if you would make subs #1,r2 instead
				;;  of adds #1,r4. The problem is that a carry could be lost....
    dfd_go33:				
	sub.w	r4, r2  	;; (r.ip<<1) - dfb.ip)
	biand	#0,r5l		;; carry = (~Mbit & carry)
				;; where: - Mbit is the MSB of r.ip before shift (stored in r5l)
				;;	  - carry is setted by sub.w r4,r2
				;; if carry==0 then quozient=1 else quozient=0
	bcs	dfd_quoz0
    dfd_quoz1: 
    	;; (r.ip<<1)>=dfb.ip => quozient bit = 1
	bset	r5h, r0h		
	adds	#2, sp
	adds	#2, sp		
	bt	dfd_go34;; bt is faster than jmp
    dfd_quoz0:
	;;(r.ip<<1)<dfb.ip => quozient bit = 0
	pop	r2
	pop	r1	
    dfd_go34:	
	dec	r5h
	bpl	dfd_cycle1
	;; end first cycle
	    	
        ;; second cycle
	;; init cycle counter
	mov.b #7, r5h			
    dfd_cycle2:				

	mov.w	@(-12,r6), r4	// @(-12,r6)= dfb.ip
	shal	r1h		;; Optimize: r1l is all 0s so don't shift it
	rotxl	r2l
	rotxl	r2h
	bst	#0, r5l
	push 	r1
	push	r2

	sub.w	r3, r1		;; (r.fp<<1) - dfb.fp
	bcc	dfd_go332
	adds	#1, r4  	;; if borrow then increment r4
					;; see NOTE before about this operation
    dfd_go332:				
	sub.w	r4, r2		;; (r.ip<<1) - dfb.ip)
	biand	#0,r5l
	bcs	dfd_quoz02
    dfd_quoz12: 
    	;; (r.ip<<1)>=dfb.ip => quozient bit = 1
	bset	r5h,r0l 	;; Optimize: more instructions needed if r5h excedds 7
	adds	#2, sp
	adds	#2, sp		
	bt	dfd_go342	;; bt is faster than jmp		
    dfd_quoz02:
	;; (r.ip<<1)<dfb.ip => quozient bit = 0
	pop	r2
	pop	r1
    dfd_go342:	
	dec	r5h
	bpl	dfd_cycle2
        ;; end second cycle
	;; here r0 contains fp result	    

	;; -------------
        ;; return result
	;; -------------
	mov.w	r0,r1		;; fp of result    
	pop	r0		;; ip of result
	pop	r3		;; sign of result
	pop	r2		;; address of result
		
	btst	#0, r3l
	bne	dfd_go5
	mov.w	r0, r3
	mov.w	r1, r4	
	bt	dfd_end
    dfd_go5:	
	;; complement result (r0=res.ip; r1=res.fp)	
	sub.w	r4,r4
	sub.w	r1,r4		
	bcc	dfd_go6
	adds	#1, r0
    dfd_go6:
	sub.w	r3,r3
	sub.w	r0,r3
    dfd_end:
	mov.w	r3, @r2
	mov.w	r4, @(2,r2)	    			
	pop	r5
	pop	r4
	mov.w	#12,r3
	add.w	r3,sp
	pop	r6	
	rts
.endif	/* __DOUBLE_FIXED_USED__ */				
	
