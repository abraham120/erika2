/** 
* @file lwip_debug.c
* @brief Debug Module Implementation
* @author Christian Nastasi, Dario Di Stefano
* @version 0.1
* @date 2009-06-22
*/

#include <util/lwip_debug.h>

#define MAXCHARS 128

#ifdef __LWIP_DEBUG__
static u8_t debug_initialized = 0; 
#endif

s8_t lwip_debug_init(void)
{
	#ifdef __LWIP_DEBUG__
	debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef __LWIP_DEBUG_SERIAL__
	des = console_serial_config(LWIP_DEBUG_SERIAL_PORT, 
								LWIP_DEBUG_SERIAL_BAUDRATE,
								LWIP_DEBUG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return LWIP_DEBUG_ERR;
	if (console_init(LWIP_DEBUG_CONSOLE, des) < 0)
		return LWIP_DEBUG_ERR;
	debug_initialized = 1;
	if(console_open(LWIP_DEBUG_CONSOLE) < 0)
		return LWIP_DEBUG_ERR;
	else
		return LWIP_DEBUG_OK;
	#else
	return LWIP_DEBUG_ERR;
	#endif /* LWIP_DEBUG */
}

s8_t lwip_debug_write(char *msg, u16_t len) 
{
	#ifdef __LWIP_DEBUG__
	if (debug_initialized)
		return console_write(LWIP_DEBUG_CONSOLE, (const u8_t *)msg, len);
	return LWIP_DEBUG_ERR;
	#else
	return LWIP_DEBUG_ERR;
	#endif /* LWIP_DEBUG */
}

s8_t lwip_debug_printf(const char* format, ...)
{
#ifdef __LWIP_DEBUG__
	char str[MAXCHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAXCHARS, format, args);
	va_end( args );
	return lwip_debug_write(str, strlen(str));
#else
	return LWIP_DEBUG_ERR;
#endif
}

s8_t lwip_debug_print_pbuf(const char *name, struct pbuf *p)
{
	#ifdef __LWIP_DEBUG__
	int i;
	struct pbuf *q;
	
	lwip_debug_printf(name);
	for(q = p; q != NULL; q = q->next) 
	{
		lwip_debug_printf("\npayload: %x, len: %d\n", q->payload, q->len);
		for(i=0; i<(q->len); i++)
		{
			lwip_debug_printf("q->payload[%d]:%x  ", i, ((u8_t*)q->payload)[i]);
		}
	}
	lwip_debug_printf("\n");
	return LWIP_DEBUG_OK;
	#else
	return LWIP_DEBUG_ERR;
	#endif
}

#ifdef DO_CASE_STRCPY 	
#undef DO_CASE_STRCPY 	
#endif

#define DO_CASE_STRCPY(x, out) 	\
case x:				\
strcpy((out), #x);		\
break;				\


