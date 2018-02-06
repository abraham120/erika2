$CASE
$EXTEND
$EXTMEM
$MODEL(TINY)
$NONSEGMENTED

REGDEF   R0-R15

$INCLUDE(sethand.asm)

;setto la tabella degli interrupt
@EE_hal_set_handler(64, _EE_L_can_handler, 0FC20h)

END
