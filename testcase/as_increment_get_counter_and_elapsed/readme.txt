Simple testcase to test the followings AUTOSAR extensions to OSEK/VDX:

- [OS383] GetCounterValue():	This service reads the current count value of a
				counter (returning either the hardware timer
				ticks if counter is driven by hardware or the
				software ticks when user drives counter).

- [OS392] GetElapsedValue():	This service gets the number of ticks between
				the current tick value and a previously read
				tick value.

- [OS399] IncrementCounter():	This service increments a software counter.

NOTE:	This test is Platform-Independent.