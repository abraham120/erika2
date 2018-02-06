Notes on the usage of Nios2:

- to use onchip-ram/rom, you must:
  - use the __attribute__ ((section (".onchip_rom")))
  - use the -G0 option to avoid global pointer problems, but it gives slower code

- I used alt_irq_interruptible to map the remote notification. if I remove it from ee_start.c it happens that when the interrupt starts, and the irq are reenabled, the SAME interrupt starts again.

- cache coherency is not implemented in NiosII ---> currently I run tests with cache disabled, but probably I will need to test something like regenerating the names for the linker with the cache diable bit set...

 
