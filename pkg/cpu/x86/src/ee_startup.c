//!< i386 specific startup code

//! Address of the first global constructor (Defined by the linker script)
extern void (*__CTORS_START)(void);
//! Address of the last global constructor (Defined by the linker script)
extern void (*__CTORS_END)(void);

void run_constructors(void) {
    //! Call constructors of all global object instances.
    //! @note Ensure that your linker script places
    //!       all `CTORS` between `__CTORS_START` and
    //! `__CTORS_END`
    for( void (** volatile ctor)() = &__CTORS_START; ctor != &__CTORS_END; ++ctor )
    {
        (*ctor)();
    }
}

extern int main(void);


#include "mcu/x86/inc/ee_mcu.h"


void arch_startup()
{
    run_constructors();

    EE_mcu_x86_init();

	// Proceed to generic initialisation
	main();

    __builtin_unreachable();
}
