

#define HARDWARE

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
#include <MicoTimer.h>
/* Other libraries */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "hv7131gp.h"

#include "MicoCamera.h"

#define MAX_CHARS 128

//#define printf (void)
#define IMAGE_HEIGHT    		640
#define IMAGE_WIDTH     		480
#define IMAGE_BYTES_PER_PIXEL	1
#define IMAGE_SIZE (IMAGE_HEIGHT*IMAGE_WIDTH*IMAGE_BYTES_PER_PIXEL)

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

#define FILL 0xFE
#define OFFSET_SIZE 16
#define SRAM_DATA_SIZE (IMAGE_SIZE)
static unsigned char* const image_addr = (unsigned char*) (SDRAM_BASE_ADDRESS);
static unsigned char* const addr = (unsigned char*) (SDRAM_BASE_ADDRESS+OFFSET_SIZE);
volatile unsigned char sem_0 = 0;

unsigned char* pun_sdram=(unsigned char*)(SDRAM_BASE_ADDRESS);
//static void dump_memory_pages(void *base, unsigned size, unsigned page_size);

// Camera register structure.
MicoCamera_t* camera = (MicoCamera_t*)CAMERA_BASE_ADDRESS;
static MicoTimer_t * const freetimerc = (MicoTimer_t *)FREETIMER_BASE_ADDRESS;

void camera_isr(void)
{
	Mico_camera_clear_IRQ_flag(camera);
	sem_0 = 1;	
}

/* This function is used to send info by serial interface. */
void myprintf(const char *format, ...)
{
	char str[MAX_CHARS];
		
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer(str, strlen(str));
}

static int read_byte(void)
{
	EE_UINT8 data;
	int res;
	res = EE_uart_receive_byte(&data);
	if (res != 1)
		return -1;
	else
		return data;
}


__INLINE__ EE_UINT32 elapsed(EE_UINT32 from, EE_UINT32 to)
{
	/* Timers are decrementing */
	return from - to;
}

__INLINE__ EE_UINT32 get_time_stamp(void)
{
	return freetimerc->Snapshot;
}

static void msleep(EE_UINT32 ms)
{
	EE_UINT32 start, curr;
	start = get_time_stamp();
	do {
		curr = get_time_stamp();
	} while (elapsed(start, curr) < (ms * (EE_UINT32)(CPU_FREQUENCY / 1000)));
}

void init_camera_i2c(unsigned char demo)
{
	int init_camera_status;
		
	init_camera_status = hv7131gp_init();
	if (init_camera_status != HV7131GP_SUCCESS) {
		myprintf("Error init %d \n\r", init_camera_status);
    	while(1);
	}
				
	/* Configure the camera device */   
    init_camera_status = hv7131gp_configure_time_divisor(HV7131GP_T_1);
	if (init_camera_status != HV7131GP_SUCCESS) {
		myprintf("hv7131gp_configure_time_divisor %d \n\r", init_camera_status);
    	while(1);
	}

	init_camera_status = hv7131gp_configure_x_flip(0);
	if (init_camera_status != HV7131GP_SUCCESS) {
		myprintf("hv7131gp_configure_x_flip %d \n\r", init_camera_status);
    	while(1);
	}
		
	#if IMAGE_HEIGHT == 640
	init_camera_status = hv7131gp_configure_subsampling(HV7131GP_NO_SUB);
	#endif
	#if IMAGE_HEIGHT == 320
	init_camera_status = hv7131gp_configure_subsampling(HV7131GP_NO_SUB);
	#endif
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_subsampling %d \n\r", init_camera_status);
	   	while(1);
	}
		
	/* Color */
	#if IMAGE_BYTES_PER_PIXEL == 1
	init_camera_status = hv7131gp_configure_color(0);
	#else
	init_camera_status = hv7131gp_configure_color(1);
	#endif
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_color %d \n\r", init_camera_status);
	   	while(1);
	}
		
	switch (demo) {
		case 0:
			break;
		case 1:
			hv7131gp_reg_write(HV7131GP_REG_SCTRA, 0x90);
 			hv7131gp_reg_write(HV7131GP_REG_OUTFMT, 0x48);
			break;
		case 2:
			hv7131gp_reg_write(HV7131GP_REG_SCTRA, 0x80);
 			hv7131gp_reg_write(HV7131GP_REG_OUTFMT, 0x48);
			break;
	}
}


void send_image(volatile unsigned char* pun, unsigned int width, unsigned int height, unsigned int size)
{
	unsigned i, r;

	myprintf("P2\r\n"
		"%d %d \r\n"
		"255\r\n", width, height);
	
	r = 0;
	for (i=0; i < width*height; i++) {
		myprintf("%d ", *pun);
		++r;
		pun += IMAGE_BYTES_PER_PIXEL;
		if (r == width) {
			r = 0;
			myprintf("\r\n");
		}
	}
}

/*
 * MAIN TASK
 */
int main(void)
{	
	/* ------------------- */
	/* Disable IRQ         */
	/* ------------------- */
	EE_mico32_disableIRQ();
	
	/* -------------------------- */
	/* Uart configuration         */
	/* -------------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode

    read_byte();
	myprintf("\r\n    ---- CAMERA DEMO ----\r\n\r\n");
		
	unsigned int state, turn;
	myprintf("Reset Camera:... ");
	Mico_camera_reset(camera);
	turn = 0;
	do {
		msleep(10);
        myprintf(".");
		if (++turn == 300){
			myprintf("    error timeout.\r\n");
			break;
		}			
		state = Mico_camera_read_status_register(camera);
	} while (state != MICO_CAMERA_IDLE);
	myprintf("done.\r\n");	

	init_camera_i2c(0);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	mico32_enable_irq(CAMERA_IRQ);
	myprintf("    Camera is ready.\r\n");
	unsigned char ans;
	do {
		myprintf("    Get new picture? (y = yes, n = exit)....\r\n");
		ans = read_byte();
		if (ans != 'y' && ans != 'n' )
			continue;
		if (ans == 'n')
			break;
		Mico_camera_write_size(camera, 0);
		Mico_camera_write_address(camera, (char *)SDRAM_BASE_ADDRESS);		
		Mico_camera_start(camera);
		myprintf("       Start Acq:... ");
		turn = 0;
		do {
			/* Wait end of the frame. */
			state = Mico_camera_read_status_register(camera);
        	msleep(10);
        	myprintf(".");
			if (++turn == 300){
				myprintf("    error timeout.\r\n");
				break;
			}	
		} while (state != MICO_CAMERA_IDLE);	
	 	EE_hal_invalidate_dcache();		
		myprintf(" done\r\n");
    	myprintf("       Press a key to download the picture.\r\n");
    	read_byte();
    	send_image((volatile unsigned char*)(SDRAM_BASE_ADDRESS), 640, 480, 0);
    	read_byte();
    		
	} while(1);
	
	myprintf("End.\r\n");
	while (1);
		
	return 0;
}
