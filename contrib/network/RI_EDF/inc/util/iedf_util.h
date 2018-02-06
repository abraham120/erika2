/**
 * @file iedf_util.h
 * @brief Implicit-EDF Utilities (Header)
 * @author Simone Madeo
 * @version 0.1
 * @date 2011-10-10
 */

#ifndef __iedf_util_h__
#define __iedf_util_h__

#include <math.h>
#include "phy/iedf_phy.h"

#define N_NODES             10

/* Timer2 setup */
void iedf_DEBUG_timer_set();

/* Check the size of operation (x * y) */
uint8_t check_size(uint32_t x, uint32_t y);

/* Calculate least common multiple between x and y */
uint32_t lcm(uint32_t x, uint32_t y);

/* Calculate ceiling(x / y) */
uint32_t ceiling(uint32_t x, uint32_t y);

/* Calculate floor(x / y) */
int32_t get_floor(int32_t x, int32_t y);

/* Send a string to serial port */
void iedf_DEBUG_serial(const char *s);

/* Convert an unsigned int to string. It returns byte size */
uint8_t iedf_DEBUG_serial_int2str(uint32_t x, char *str);

/* Send an unsigned int to serial port */
void iedf_DEBUG_serial_int(uint32_t x);

/* Send three unsigned int to serial port */
void iedf_DEBUG_serial_int3(uint32_t x, uint32_t y, uint32_t z);

/* Send a double to serial port */
void iedf_DEBUG_serial_double(double x);

/* Return relative time between t1 and t2 */
uint16_t iedf_DEBUG_time(uint16_t t1, uint16_t t2);

/* Convert a double into a fraction (C/T) */
void double2frac(double d, uint16_t *C, uint16_t *T);

/* UUniFast Algorithm - Generate the stream utilizations (C/T)
 * Return the total utilization */
double UUniFast(uint16_t n, double max_util, uint16_t *C, uint16_t *T);

/* Initialize deadlline miss test & hyperperiod values */
uint32_t store_miss_values(uint16_t *dst, uint8_t umax, uint8_t iter);

#endif
