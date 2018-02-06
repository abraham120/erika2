#ifndef __TOUCH_H__
#define __TOUCH_H__

#define __FOUR_WIRES__
#define __LOW_LEVEL_MEASUREMENT__

#include "touch_compiler.h"
#include "touch_hal.h"

#ifdef __USE_TOUCH__
#include "touch_1_kal.h"
#endif // __USE_TOUCH__

#ifdef __USE_TOUCH_2__
#include "touch_2_kal.h"
#endif // __USE_TOUCH_2__

#define TOUCH_X_AXIS	0
#define TOUCH_Y_AXIS	1

// Measurement Settings
#define SAMPLES_FOR_ONE_TRUE_XY_PAIR    5             // Number of Measurements for one true X/Y-Coordinate
#define END_OF_ARRAY                    SAMPLES_FOR_ONE_TRUE_XY_PAIR-1
#define MEDIAN                          (SAMPLES_FOR_ONE_TRUE_XY_PAIR-1)/2      // odd-numbered: SAMPLES_FOR_ONE_TRUE_XY_PAIR
#define MAXIMUM_LOW_LEVEL			1000          // Invalid Measurement for Low_Level > MAXIMUM_LOW_LEVEL
#define RTOUCH_MAXIMUM_LEVEL		4000
#define MAXIMUM_UNTOUCH_CONDITIONS	100           // Number of (successive) Invalid Measurements till Untouch Condition
#define SLEEP_COUNTDOWN				2000
#define TOUCH_ACTIVATION_TIME		2000

#define TOUCH_ERROR_CONFIGURED		0
#define TOUCH_ERROR_NONE			0
#define TOUCH_ERROR_WRONG_AXIS		1
#define TOUCH_ERROR_RAW_NOT_READY 	2
#define TOUCH_ERROR_NOT_TUNED		3
#define TOUCH_ERROR_NOT_CONFIGURED	4

/****************************************************************************
  Type definition
****************************************************************************/

typedef struct {
	unsigned STANDBY:1;
	unsigned XPOS:1;
	unsigned YPOS:1;
	unsigned Z1MEAS:1;
	unsigned Z2MEAS:1;
	unsigned UNDEF1:1;
	unsigned UNDEF2:1;
	unsigned COMPLETE:1;
} TouchFlow;

typedef struct {
	uint16_t xt1;
	uint16_t yt1;
	uint16_t xt2;
	uint16_t yt2;
	uint16_t xt3;
	uint16_t yt3;
} tune_raw_t;

typedef struct {
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
} tune_t;

/****************************************************************************
  Function definitions
****************************************************************************/

#ifdef __USE_TOUCH__
int8_t touch_1_poll_raw_position(uint8_t, int16_t *);
int8_t touch_1_poll_u_position(uint8_t, int16_t *);
int8_t touch_1_poll_s_position(uint8_t, int16_t *);
int8_t touch_1_wait_raw_position(uint8_t, int16_t *);
int8_t touch_1_wait_u_position(uint8_t, int16_t *);
int8_t touch_1_wait_s_position(uint8_t, int16_t *);
int8_t touch_1_set_dimension(uint8_t, uint16_t);
void touch_1_raw_init(void);
void touch_1_tune(tune_raw_t *);

COMPILER_INLINE void touch_1_start(void)
{
	touch_1_timer_start();
}

COMPILER_INLINE void touch_1_stop(void)
{
	touch_1_timer_stop();
}
#endif // __USE_TOUCH__

#ifdef __USE_TOUCH_2__
int8_t touch_2_poll_raw_position(uint8_t, int16_t *);
int8_t touch_2_poll_u_position(uint8_t, int16_t *);
int8_t touch_2_poll_s_position(uint8_t, int16_t *);
int8_t touch_2_wait_raw_position(uint8_t, int16_t *);
int8_t touch_2_wait_u_position(uint8_t, int16_t *);
int8_t touch_2_wait_s_position(uint8_t, int16_t *);
int8_t touch_2_set_dimension(uint8_t, uint16_t);
void touch_2_raw_init(void);
void touch_2_tune(tune_raw_t *);

COMPILER_INLINE void touch_2_start(void)
{
	touch_2_timer_start();
}

COMPILER_INLINE void touch_2_stop(void)
{
	touch_2_timer_stop();
}
#endif // __USE_TOUCH_2__

#define touch_set_dimension(a, b)		touch_1_set_dimension(a, b) 
#define touch_raw_init()				touch_1_raw_init()
#define touch_start()					touch_1_start()
#define touch_wait_raw_position(a, b)	touch_1_wait_raw_position(a, b)
#define touch_tune(a)					touch_1_tune(a)
#define touch_poll_s_position(a, b) 	touch_1_poll_s_position(a, b)

#endif // __TOUCH_H__
