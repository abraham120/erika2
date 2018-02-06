###
### Setting EEOPT variable:
###

EEOPT =

## ROM data
##EEOPT += __NO_ROM_DATA__

## Stack
EEOPT += __MULTI__
##EEOPT += __MONO__

## Scheduling
EEOPT += __EDF__
##EEOPT += __FP__

## Time support
EEOPT += __TIME_SUPPORT__

## Architecture
EEOPT += __H8__

## Debug
##EEOPT += __DEBUG__

## Play melodies (buffer)
#EEOPT += __PLAY_BUFFER_SUPPORT__

## Play notes
EEOPT += __PLAY_NOTE_SUPPORT__

## motors with variable velox
##EEOPT += __MOTOR_C_PWM_USED__

## motors with precise variable velox
##EEOPT += __MOTOR_B_VP_USED__

## motors with fixed (maximum) velox
EEOPT += __MOTOR_A_PWM_USED__

## A/D converter
EEOPT += __AD_SUPPORT__

## timer A user function 
##EEOPT += __TIMER_A_USER_FUNCTION_USED__

## timer B user function 
EEOPT += __TIMER_B_USER_FUNCTION_USED__

## use timer A to activate periodic tasks 
#EEOPT += __TIMER_A_PERIODIC_TASK_USED__

## use signed fixed point number
##EEOPT += __SIGNED_FIXED_USED__

## use unsigned fixed point number
EEOPT += __UNSIGNED_FIXED_USED__

## use double fixed point number
##EEOPT += __DOUBLE_FIXED_USED__

## use signed fixed trigonometric functions
##EEOPT += __SF_TRIG_USED__

## use signed fixed trig. functions with no input range control (high speed)
##EEOPT += __SF_HIGH_SPEED_TRIG_USED__

## use double fixed trigonometric functions
##EEOPT += __DF_TRIG_USED__

## use double fixed trig. functions with no input range control (high speed)
##EEOPT += __DF_HIGH_SPEED_TRIG_USED__

APP_SRCS = code.c inithal.c initkern.c set_hand.s handlers.c

include $(EEBASE)/config/config.mak





