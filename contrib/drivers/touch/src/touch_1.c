#include "touch.h"
#include "touch_1_kal.h"

#ifdef __USE_TOUCH__

/****************************************************************************
  Global variables
****************************************************************************/

#define STATIC static
//#define STATIC

STATIC uint16_t horiz_width;
STATIC uint16_t vert_height;
STATIC uint16_t u_X_pos;
STATIC uint16_t u_Y_pos;
STATIC int16_t s_X_pos;
STATIC int16_t s_Y_pos;
STATIC volatile uint8_t is_raw_initialized;
STATIC volatile uint8_t is_raw_ready;
STATIC volatile uint8_t is_final_ready;
STATIC volatile uint8_t is_tuned;
STATIC uint16_t X_raw;
STATIC uint16_t Y_raw;
STATIC uint16_t touch_tick_us;
STATIC tune_raw_t tune_raw;
STATIC tune_t tune;

// Touch state variable
STATIC volatile TouchFlow tf;
// Array index
STATIC uint8_t i_array;
// Array for X-Coordinates
STATIC uint16_t Reading_X[SAMPLES_FOR_ONE_TRUE_XY_PAIR];
// Array for Y-Coordinates
STATIC uint16_t Reading_Y[SAMPLES_FOR_ONE_TRUE_XY_PAIR];
STATIC uint16_t Reading_low_level;
STATIC uint16_t untouch_conditions;

COMPILER_INLINE void touch_1_calibrate(tune_raw_t *t)
{
	int32_t tmp;
        // touch input P1 (90%,50%)
        uint16_t xd1 = (uint16_t)(0.9*horiz_width);
        uint16_t yd1 = (uint16_t)(0.5*vert_height);
        // touch input P2 (50%,10%)
        uint16_t xd2 = (uint16_t)(0.5*horiz_width);
        uint16_t yd2 = (uint16_t)(0.9*vert_height);
        // touch input P3 (10%,90%)
        uint16_t xd3 = (uint16_t)(0.1*horiz_width);
        uint16_t yd3 = (uint16_t)(0.1*vert_height);

        tune.a = (int32_t)t->yt1*xd3-(int32_t)t->yt1*xd2;
	tune.a += -(int32_t)t->yt2*xd3+(int32_t)xd2*t->yt3;
	tune.a += -(int32_t)xd1*t->yt3+(int32_t)xd1*t->yt2;
	tmp = -(int32_t)t->xt1*t->yt3+(int32_t)t->xt2*t->yt3;
	tmp += -(int32_t)t->xt2*t->yt1+(int32_t)t->xt3*t->yt1;
	tmp += -(int32_t)t->xt3*t->yt2+(int32_t)t->xt1*t->yt2;
	tune.a /= tmp;
	tune.b = tune.a*((double)t->xt3-t->xt2)+xd2-xd3;
        tune.b /= (t->yt2-t->yt3);
	tune.c = xd3-tune.a*t->xt3-tune.b*t->yt3;

	tune.d = -(int32_t)t->yt2*yd3+(int32_t)t->yt2*yd1;
	tune.d += (int32_t)t->yt1*yd3+(int32_t)t->yt3*yd2;
	tune.d += -(int32_t)t->yt3*yd1-(int32_t)t->yt1*yd2;
	tmp = -(int32_t)t->yt2*t->xt3+(int32_t)t->yt2*t->xt1;
	tmp += (int32_t)t->yt1*t->xt3+(int32_t)t->yt3*t->xt2;
	tmp += -(int32_t)t->yt3*t->xt1-(int32_t)t->yt1*t->xt2;
        tune.d /= tmp;
        tune.e = tune.d*((double)t->xt3-t->xt2)+yd2-yd3;
        tune.e /= t->yt2-t->yt3;
        tune.f = yd3-tune.d*t->xt3-tune.e*t->yt3;
}

int8_t touch_1_set_dimension(
		uint8_t touch_axis,
		uint16_t touch_range)
{
	if(touch_axis == TOUCH_X_AXIS)
	{
		horiz_width = touch_range;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		vert_height = touch_range;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	if(is_raw_initialized)
		touch_1_calibrate(&tune_raw);

	return TOUCH_ERROR_NONE;
}

COMPILER_INLINE void touch_1_set_adc(void)
{
	CLEARBIT(EE_1_TOUCH_EN_A_TRIS);
	CLEARBIT(EE_1_TOUCH_EN_B_TRIS);
	CLEARBIT(EE_1_TOUCH_EN_C_TRIS);
	SETBIT(EE_1_TOUCH_BOTTOM_TRIS);
	SETBIT(EE_1_TOUCH_RIGHT_TRIS);
	CLEARBIT(EE_1_TOUCH_BOTTOM_AD);
	CLEARBIT(EE_1_TOUCH_RIGHT_AD);

	STANDBY_1_CONFIGURATION;
	tf.STANDBY = 1;

	ADC_1_SELECTED_PIN = STANDBY_PIN_1;
	SETBIT(ADC_1_ASAM);
	ADC_1_FORM = 0;
	ADC_1_SSRC = 0;
	SETBIT(ADC_1_AD12B);
	ADC_1_CON2 = 0;
	ADC_1_SAMC = 16;
	ADC_1_ADRC = 0;
	ADC_1_ADCS = 3;

	// reset ADC interrupt flag
	CLEARBIT(ADC_1_INTERRUPT_FLAG);
	// enable ADC interrupts, disable this interrupt if the DMA is enabled
	SETBIT(ADC_1_INTERRUPT_ENABLE);
	// turn on ADC
	ADC_1_TURN_ON;
}

COMPILER_INLINE void touch_1_set_act_time(uint16_t _touch_tick_us)
{
	touch_tick_us = _touch_tick_us;
}

void touch_1_raw_init(void)
{
	if(is_raw_initialized)
		return;

	// Global variables reset
	untouch_conditions = 0;

	X_raw = 0;
	Y_raw = 0;

	u_X_pos = horiz_width/2;
	u_Y_pos = vert_height/2;

	s_X_pos = 0;
	s_Y_pos = 0;

	is_raw_ready = 0;
	is_tuned = 0;
	is_final_ready = 0;
	i_array = 0;

	touch_1_set_adc();
	touch_1_set_act_time(TOUCH_ACTIVATION_TIME);
	touch_1_kal_init(touch_tick_us);

	is_raw_initialized = 1;
}

void touch_1_tune(tune_raw_t *t)
{
	tune_raw = *t;
	touch_1_calibrate(&tune_raw);
	is_tuned = 1;
}

static void sorted_insertion(uint16_t Array[])
{
	int8_t i;
	uint8_t j;
	uint16_t current;

	// Sort Array[]
	for(j=1; j<SAMPLES_FOR_ONE_TRUE_XY_PAIR; j++)
	{
		current = Array[j];
		i = j - 1;
		while(i>=0 && Array[i]>current)
		{
			Array[i+1] = Array[i];
			i--;
		}
		Array[i+1] = current;
	}
}

static void store_valid_data(void)
{
    // Store valid Data in Array

	if(i_array==(END_OF_ARRAY))
	{
		// Array Management

		// Sort X/Y Readings To Get Median
		sorted_insertion(Reading_X);
		sorted_insertion(Reading_Y);

		X_raw = Reading_X[MEDIAN];
		Y_raw = Reading_Y[MEDIAN];
		is_raw_ready = 1;

		//GetResource(mutex_posRead);

		if(is_tuned)
		{
			u_X_pos = (uint16_t)(tune.a*X_raw+tune.b*Y_raw+tune.c);
			u_Y_pos = (uint16_t)(tune.d*X_raw+tune.e*Y_raw+tune.f);

			if(u_X_pos<0)
				u_X_pos = 0;
			else if(u_X_pos>horiz_width-1)
				u_X_pos = horiz_width-1;

			if(u_Y_pos<0)
				u_Y_pos = 0;
			else if(u_Y_pos>vert_height-1)
				u_Y_pos = vert_height-1;

			s_X_pos = (int16_t)u_X_pos - horiz_width/2;
			s_Y_pos = (int16_t)u_Y_pos - vert_height/2;
			is_final_ready = 1;
		}

		//ReleaseResource(mutex_posRead);

		i_array = 0;

    } else i_array++;
}

#ifdef __LOW_LEVEL_MEASUREMENT__
TASK(TASK_TOUCH_MANAGER_1)
{
	if(ADC_1_CONVERSION_DONE)
	{
		ADC_1_CONVERSION_RESET;
		if(tf.STANDBY)
		{
			Reading_low_level = ADC_1_RESULT_BUFFER;
			if(Reading_low_level < MAXIMUM_LOW_LEVEL)
			{
				tf.STANDBY = 0;
				tf.YPOS = 1;
				if(tf.COMPLETE)
				{
					store_valid_data();
				}
				Y_POS_1_CONFIGURATION;
				ADC_1_SELECTED_PIN = ADC_Y_1;
				untouch_conditions = 0;
			} else
			{
				tf.COMPLETE = 0;
				if(MAXIMUM_UNTOUCH_CONDITIONS == untouch_conditions )
				{
					is_raw_ready = 0;
					//X_raw = 0;
					//Y_raw = 0;
					is_final_ready = 0;
				} else untouch_conditions++;
			}

		} else if(tf.YPOS)
		{
			Reading_Y[i_array] = ADC_1_RESULT_BUFFER;
			tf.YPOS = 0;
			tf.XPOS = 1;
			X_POS_1_CONFIGURATION;
			ADC_1_SELECTED_PIN = ADC_X_1;
		} else if(tf.XPOS)
		{
			Reading_X[i_array] = ADC_1_RESULT_BUFFER;
			tf.XPOS = 0;
			tf.STANDBY = 1;
			tf.COMPLETE = 1;
			STANDBY_1_CONFIGURATION;
			ADC_1_SELECTED_PIN = STANDBY_PIN_1;
		}
	} else
	{
		ADC_1_CONVERSION_START;
	}
}
#endif // __LOW_LEVEL_MEASUREMENT__

ISR2(ADC_1_INTERRUPT_NAME)
{
	CLEARBIT(ADC_1_INTERRUPT_FLAG);
	ActivateTask(TASK_TOUCH_MANAGER_1);
}

int8_t touch_1_poll_raw_position(
		uint8_t touch_axis,
		int16_t *raw_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	if(touch_axis == TOUCH_X_AXIS)
	{
		*raw_choord = X_raw;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*raw_choord = Y_raw;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	return TOUCH_ERROR_NONE;
}

int8_t touch_1_poll_u_position(
		uint8_t touch_axis,
		int16_t *u_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	if(!is_tuned)
		return -TOUCH_ERROR_NOT_TUNED;

	if(touch_axis == TOUCH_X_AXIS)
	{
		*u_choord = u_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*u_choord = u_Y_pos;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	return TOUCH_ERROR_NONE;
}

int8_t touch_1_poll_s_position(
		uint8_t touch_axis,
		int16_t *s_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	if(!is_tuned)
		return -TOUCH_ERROR_NOT_TUNED;

	if(touch_axis == TOUCH_X_AXIS)
	{
		*s_choord = s_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*s_choord = s_Y_pos;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	return TOUCH_ERROR_NONE;
}

int8_t touch_1_wait_raw_position(
		uint8_t touch_axis,
		int16_t *raw_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	while(!is_raw_ready);

	if(touch_axis == TOUCH_X_AXIS)
	{
		*raw_choord = X_raw;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*raw_choord = Y_raw;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	return TOUCH_ERROR_NONE;
}

int8_t touch_1_wait_u_position(
		uint8_t touch_axis,
		int16_t *u_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	if(!is_tuned)
		return -TOUCH_ERROR_NOT_TUNED;

	while(!is_final_ready);

	if(touch_axis == TOUCH_X_AXIS)
	{
		*u_choord = u_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*u_choord = u_Y_pos;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	is_final_ready = 0;

	return TOUCH_ERROR_NONE;
}

int8_t touch_1_wait_s_position(
		uint8_t touch_axis,
		int16_t *s_choord)
{
	if(!is_raw_initialized)
		return -TOUCH_ERROR_NOT_CONFIGURED;

	if(!is_tuned)
		return -TOUCH_ERROR_NOT_TUNED;

	while(!is_final_ready);

	if(touch_axis == TOUCH_X_AXIS)
	{
		*s_choord = s_X_pos;
	}
	else if(touch_axis == TOUCH_Y_AXIS)
	{
		*s_choord = s_Y_pos;
	} else return -TOUCH_ERROR_WRONG_AXIS;

	is_final_ready = 0;

	return TOUCH_ERROR_NONE;
}

#else

TASK(TASK_TOUCH_MANAGER_1)
{
}

#endif // __USE_TOUCH__
