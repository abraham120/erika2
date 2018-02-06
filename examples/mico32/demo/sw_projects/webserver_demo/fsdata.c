#include "fs.h"
#include "lwip/def.h"
#include "fsdata.h"
#include "sw.c"
#include "logo.c"
#include "lattice_logo.c"
#include "erika_bn.c"
#include "logo-footer.c"

/*
 * Copyright: 2010, Evidence Srl
 * Modified by: Alessandro Paolinelli
 * Description: Modified fs architecture and 
 * 				added JavaScript code in index.html
 * 				to support multiple images load ,dynamic 
 * 				links and events association.
 */

/* Tag code in htlm dinamic page */
#define TAG_LED1 "<!--led1-->"
#define TAG_LED2 "<!--led2-->"
#define TAG_LED3 "<!--led3-->"
#define TAG_LED4 "<!--led4-->"
#define TAG_LED5 "<!--led5-->"
#define TAG_LED6 "<!--led6-->"
#define TAG_LED7 "<!--led7-->"
#define TAG_LED8 "<!--led8-->"

#define MASK_SW1 0x01
#define MASK_SW2 0x02
#define MASK_SW3 0x04
#define MASK_SW4 0x08
#define MASK_SW5 0x10
#define MASK_SW6 0x20
#define MASK_SW7 0x40
#define MASK_SW8 0x80

#define MASK_LED1 0x01
#define MASK_LED2 0x02
#define MASK_LED3 0x04
#define MASK_LED4 0x08
#define MASK_LED5 0x10
#define MASK_LED6 0x20
#define MASK_LED7 0x40
#define MASK_LED8 0x80

#define REFRESH_HTLM_MS    1000
 
volatile unsigned char var = 0;


#define file_NULL (struct fsdata_file *) NULL

static const unsigned int dummy_align__404_html = 1;
static const unsigned char data__404_html[] = {
/* /404.html (10 chars) */
0x2f,0x34,0x30,0x34,0x2e,0x68,0x74,0x6d,0x6c,0x00,0x00,0x00,

/* HTTP header */
/* "HTTP/1.0 404 File not found
" (29 bytes) */
0x48,0x54,0x54,0x50,0x2f,0x31,0x2e,0x30,0x20,0x34,0x30,0x34,0x20,0x46,0x69,0x6c,
0x65,0x20,0x6e,0x6f,0x74,0x20,0x66,0x6f,0x75,0x6e,0x64,0x0d,0x0a,
/* "Server: lwIP/1.3.1 (http://savannah.nongnu.org/projects/lwip)
" (63 bytes) */
0x53,0x65,0x72,0x76,0x65,0x72,0x3a,0x20,0x6c,0x77,0x49,0x50,0x2f,0x31,0x2e,0x33,
0x2e,0x31,0x20,0x28,0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x73,0x61,0x76,0x61,0x6e,
0x6e,0x61,0x68,0x2e,0x6e,0x6f,0x6e,0x67,0x6e,0x75,0x2e,0x6f,0x72,0x67,0x2f,0x70,
0x72,0x6f,0x6a,0x65,0x63,0x74,0x73,0x2f,0x6c,0x77,0x69,0x70,0x29,0x0d,0x0a,
/* "Content-type: text/html

" (27 bytes) */
0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,0x70,0x65,0x3a,0x20,0x74,0x65,
0x78,0x74,0x2f,0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,0x0a,
/* raw file data (565 bytes) */
0x3c,0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,0x3c,0x68,0x65,0x61,0x64,0x3e,0x3c,0x74,
0x69,0x74,0x6c,0x65,0x3e,0x6c,0x77,0x49,0x50,0x20,0x2d,0x20,0x41,0x20,0x4c,0x69,
0x67,0x68,0x74,0x77,0x65,0x69,0x67,0x68,0x74,0x20,0x54,0x43,0x50,0x2f,0x49,0x50,
0x20,0x53,0x74,0x61,0x63,0x6b,0x3c,0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,0x3c,0x2f,
0x68,0x65,0x61,0x64,0x3e,0x0d,0x0a,0x3c,0x62,0x6f,0x64,0x79,0x20,0x62,0x67,0x63,
0x6f,0x6c,0x6f,0x72,0x3d,0x22,0x77,0x68,0x69,0x74,0x65,0x22,0x20,0x74,0x65,0x78,
0x74,0x3d,0x22,0x62,0x6c,0x61,0x63,0x6b,0x22,0x3e,0x0d,0x0a,0x0d,0x0a,0x20,0x20,
0x20,0x20,0x3c,0x74,0x61,0x62,0x6c,0x65,0x20,0x77,0x69,0x64,0x74,0x68,0x3d,0x22,
0x31,0x30,0x30,0x25,0x22,0x3e,0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x3c,0x74,
0x72,0x20,0x76,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x74,0x6f,0x70,0x22,0x3e,0x3c,
0x74,0x64,0x20,0x77,0x69,0x64,0x74,0x68,0x3d,0x22,0x38,0x30,0x22,0x3e,0x09,0x20,
0x20,0x0d,0x0a,0x09,0x20,0x20,0x3c,0x61,0x20,0x68,0x72,0x65,0x66,0x3d,0x22,0x68,
0x74,0x74,0x70,0x3a,0x2f,0x2f,0x77,0x77,0x77,0x2e,0x73,0x69,0x63,0x73,0x2e,0x73,
0x65,0x2f,0x22,0x3e,0x3c,0x69,0x6d,0x67,0x20,0x73,0x72,0x63,0x3d,0x22,0x2f,0x69,
0x6d,0x67,0x2f,0x73,0x69,0x63,0x73,0x2e,0x67,0x69,0x66,0x22,0x0d,0x0a,0x09,0x20,
0x20,0x62,0x6f,0x72,0x64,0x65,0x72,0x3d,0x22,0x30,0x22,0x20,0x61,0x6c,0x74,0x3d,
0x22,0x53,0x49,0x43,0x53,0x20,0x6c,0x6f,0x67,0x6f,0x22,0x20,0x74,0x69,0x74,0x6c,
0x65,0x3d,0x22,0x53,0x49,0x43,0x53,0x20,0x6c,0x6f,0x67,0x6f,0x22,0x3e,0x3c,0x2f,
0x61,0x3e,0x0d,0x0a,0x09,0x3c,0x2f,0x74,0x64,0x3e,0x3c,0x74,0x64,0x20,0x77,0x69,
0x64,0x74,0x68,0x3d,0x22,0x35,0x30,0x30,0x22,0x3e,0x09,0x20,0x20,0x0d,0x0a,0x09,
0x20,0x20,0x3c,0x68,0x31,0x3e,0x6c,0x77,0x49,0x50,0x20,0x2d,0x20,0x41,0x20,0x4c,
0x69,0x67,0x68,0x74,0x77,0x65,0x69,0x67,0x68,0x74,0x20,0x54,0x43,0x50,0x2f,0x49,
0x50,0x20,0x53,0x74,0x61,0x63,0x6b,0x3c,0x2f,0x68,0x31,0x3e,0x0d,0x0a,0x09,0x20,
0x20,0x3c,0x68,0x32,0x3e,0x34,0x30,0x34,0x20,0x2d,0x20,0x50,0x61,0x67,0x65,0x20,
0x6e,0x6f,0x74,0x20,0x66,0x6f,0x75,0x6e,0x64,0x3c,0x2f,0x68,0x32,0x3e,0x0d,0x0a,
0x09,0x20,0x20,0x3c,0x70,0x3e,0x0d,0x0a,0x09,0x20,0x20,0x20,0x20,0x53,0x6f,0x72,
0x72,0x79,0x2c,0x20,0x74,0x68,0x65,0x20,0x70,0x61,0x67,0x65,0x20,0x79,0x6f,0x75,
0x20,0x61,0x72,0x65,0x20,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x69,0x6e,0x67,0x20,
0x77,0x61,0x73,0x20,0x6e,0x6f,0x74,0x20,0x66,0x6f,0x75,0x6e,0x64,0x20,0x6f,0x6e,
0x20,0x74,0x68,0x69,0x73,0x0d,0x0a,0x09,0x20,0x20,0x20,0x20,0x73,0x65,0x72,0x76,
0x65,0x72,0x2e,0x20,0x0d,0x0a,0x09,0x20,0x20,0x3c,0x2f,0x70,0x3e,0x0d,0x0a,0x09,
0x3c,0x2f,0x74,0x64,0x3e,0x3c,0x74,0x64,0x3e,0x0d,0x0a,0x09,0x20,0x20,0x26,0x6e,
0x62,0x73,0x70,0x3b,0x0d,0x0a,0x09,0x3c,0x2f,0x74,0x64,0x3e,0x3c,0x2f,0x74,0x72,
0x3e,0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x3c,0x2f,0x74,0x61,0x62,0x6c,0x65,
0x3e,0x0d,0x0a,0x3c,0x2f,0x62,0x6f,0x64,0x79,0x3e,0x0d,0x0a,0x3c,0x2f,0x68,0x74,
0x6d,0x6c,0x3e,0x0d,0x0a,};

unsigned char state_led = 0;
char led1_check[]   = "<input type=\"checkbox\" name=\"Led1\" value=\"Led1_on\" checked > Led1";
char led1_uncheck[] = "<input type=\"checkbox\" name=\"Led1\" value=\"Led1_on\"         > Led1";
char led2_check[]   = "<input type=\"checkbox\" name=\"Led2\" value=\"Led2_on\" checked > Led2";
char led2_uncheck[] = "<input type=\"checkbox\" name=\"Led2\" value=\"Led2_on\"         > Led2";
char led3_check[]   = "<input type=\"checkbox\" name=\"Led3\" value=\"Led3_on\" checked > Led3";
char led3_uncheck[] = "<input type=\"checkbox\" name=\"Led3\" value=\"Led3_on\"         > Led3";
char led4_check[]   = "<input type=\"checkbox\" name=\"Led4\" value=\"Led4_on\" checked > Led4";
char led4_uncheck[] = "<input type=\"checkbox\" name=\"Led4\" value=\"Led4_on\"         > Led4";
char led5_check[]   = "<input type=\"checkbox\" name=\"Led5\" value=\"Led5_on\" checked > Led5";
char led5_uncheck[] = "<input type=\"checkbox\" name=\"Led5\" value=\"Led5_on\"         > Led5";
char led6_check[]   = "<input type=\"checkbox\" name=\"Led6\" value=\"Led6_on\" checked > Led6";
char led6_uncheck[] = "<input type=\"checkbox\" name=\"Led6\" value=\"Led6_on\"         > Led6";
char led7_check[]   = "<input type=\"checkbox\" name=\"Led7\" value=\"Led7_on\" checked > Led7";
char led7_uncheck[] = "<input type=\"checkbox\" name=\"Led7\" value=\"Led7_on\"         > Led7";
char led8_check[]   = "<input type=\"checkbox\" name=\"Led8\" value=\"Led8_on\" checked > Led8";
char led8_uncheck[] = "<input type=\"checkbox\" name=\"Led8\" value=\"Led8_on\"         > Led8";
char *pun;

static const unsigned char camera_640_480_png[] = "/img/camera_640x480.png";
static const unsigned char camera_320_240_png[] = "/img/camera_320x240.png";
static const unsigned char camera_160_120_png[] = "/img/camera_160x120.png";
static const unsigned char sw_on_png[]          = "/img/swon.png";
static const unsigned char sw_off_png[]         = "/img/swoff.png";
static const unsigned char logo_jpg[]           = "/img/logo.jpg";
static const unsigned char lattice_logo_jpg[]   = "/img/lattice_logo.jpg";
static const unsigned char erika_bn_jpg[]       = "/img/erika_bn.jpg";
static const unsigned char logo_footer_png[]    = "/img/logo-footer.png";
static const unsigned char sw_1_jpg[]           = "/img/sw1.jpg";
static const unsigned char sw_2_jpg[]           = "/img/sw2.jpg";
static const unsigned char sw_3_jpg[]           = "/img/sw3.jpg";
static const unsigned char sw_4_jpg[]           = "/img/sw4.jpg";
static const unsigned char sw_5_jpg[]           = "/img/sw5.jpg";
static const unsigned char sw_6_jpg[]           = "/img/sw6.jpg";
static const unsigned char sw_7_jpg[]           = "/img/sw7.jpg";
static const unsigned char sw_8_jpg[]           = "/img/sw8.jpg";

struct fsdata_file file_sw_8_jpg[] = { {
file_NULL,
sw_8_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_7_jpg[] = { {
file_sw_8_jpg,
sw_7_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_6_jpg[] = { {
file_sw_7_jpg,
sw_6_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_5_jpg[] = { {
file_sw_6_jpg,
sw_5_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_4_jpg[] = { {
file_sw_5_jpg,
sw_4_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_3_jpg[] = { {
file_sw_4_jpg,
sw_3_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_2_jpg[] = { {
file_sw_3_jpg,
sw_2_jpg,
NULL,
0,
1,
}};

struct fsdata_file file_sw_1_jpg[] = { {
file_sw_2_jpg,
sw_1_jpg,
0,
1,
}};

const struct fsdata_file file_logo_footer_png[] = { {
file_sw_1_jpg,
logo_footer_png,
logo_footer_data_png,
sizeof(logo_footer_data_png),
1,
}};

const struct fsdata_file file_erika_bn_jpg[] = { {
file_logo_footer_png,
erika_bn_jpg,
erika_bn_data_jpg,
sizeof(erika_bn_data_jpg),
1,
}};

const struct fsdata_file file_lattice_logo_jpg[] = { {
file_erika_bn_jpg,
lattice_logo_jpg,
lattice_logo_data_jpg,
sizeof(lattice_logo_data_jpg),
1,
}};

const struct fsdata_file file_logo_jpg[] = { {
file_lattice_logo_jpg,
logo_jpg,
logo_data_jpg,
sizeof(logo_data_jpg),
1,
}};

const struct fsdata_file file_camera_640_480_png[] = { {
file_logo_jpg,
camera_640_480_png,
NULL,
0,
1,
}};

const struct fsdata_file file_camera_320_240_png[] = { {
file_camera_640_480_png,
camera_320_240_png,
NULL,
0,
1,
}};

const struct fsdata_file file_camera_160_120_png[] = { {
file_camera_320_240_png,
camera_160_120_png,
NULL,
0,
1,
}};

const struct fsdata_file file__404_html[] = { {
file_camera_160_120_png,
data__404_html,
data__404_html + 12,
sizeof(data__404_html) - 12,
1,
}};

/* Dinamic page. */
static const unsigned char my_name__index_html[] = "/index.html";

static unsigned char my_data__index_html[] =
    /* Do not edit; automatically generated from "index.html" with the command
         ./html2c < index.html
    */
	"<HTML>\n"
	"<HEAD>\n"
	"<TITLE>Evidence Fpg-Eye Demo Control</TITLE>\n"
	"<style type=\"text/css\">\n"
	"body h1 p {\n"
	"	font-family: \"Arial Black\", Gadget, sans-serif;\n"
	"}\n"
	"body h3 p {\n"
	"	font-family: \"Arial Black\", Gadget, sans-serif;\n"
	"}\n"
	"</style>\n"
	"</HEAD>\n"
	"<script type=\"text/javascript\">\n"
	"function reload_image(id, file) {\n"
	"		now = new Date();\n"
	"		document.getElementById(id).src = file + '?' + now.getTime();\n"
	"}\n"
	"</script>\n"
	"<BODY>\n"
	"<body bgcolor=\"white\" text=\"black\">\n"
	"<H1>\n"
	"<P ALIGN=\"CENTER\">\n"
	"Evidence Fpg-Eye Demo Control\n"
	"</H1>"
	"<P ALIGN=\"CENTER\"><a href=\"http://www.evidence.eu.com\"><img src=\"/img/logo.jpg\" width=\"150\" height=\"150\"></a><a href=\"http://www.latticesemi.com\"><img src=\"/img/lattice_logo.jpg\" width=\"150\" height=\"150\"></a>\n"
	"<P ALIGN=\"CENTER\"><a href=\"http://erika.tuxfamily.org\"><img src=\"/img/erika_bn.jpg\" width=\"300\" height=\"59\" alt=\"Erika Enterprise\" longdesc=\"http://erika.tuxfamily.org\"></a>\n"
	"<H3>\n"
	"<P ALIGN=\"CENTER\">Dip Switches on Board\n"
	"</H3>"
	"<P ALIGN=\"CENTER\">"
	"<!--sw1-->"
	"<img src=\"/img/sw1.jpg\" border=\"0\"  id=\"SW1\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW1\\\', \\\'/img/sw1.jpg\\\')', 100)\">\n"
	"<!--sw2-->"
	"<img src=\"/img/sw2.jpg\" border=\"0\"  id=\"SW2\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW2\\\', \\\'/img/sw2.jpg\\\')', 100)\">\n"
	"<!--sw3-->"
 	"<img src=\"/img/sw3.jpg\" border=\"0\"  id=\"SW3\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW3\\\', \\\'/img/sw3.jpg\\\')', 100)\">\n"
	"<!--sw4-->"
	"<img src=\"/img/sw4.jpg\" border=\"0\"  id=\"SW4\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW4\\\', \\\'/img/sw4.jpg\\\')', 100)\">\n"
	"<!--sw5-->"
	"<img src=\"/img/sw5.jpg\" border=\"0\"  id=\"SW5\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW5\\\', \\\'/img/sw5.jpg\\\')', 100)\">\n"
	"<!--sw6-->"
	"<img src=\"/img/sw6.jpg\" border=\"0\"  id=\"SW6\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW6\\\', \\\'/img/sw6.jpg\\\')', 100)\">\n"
	"<!--sw7-->"
	"<img src=\"/img/sw7.jpg\" border=\"0\"  id=\"SW7\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW7\\\', \\\'/img/sw7.jpg\\\')', 100)\">\n"
	"<!--sw8-->"
	"<img src=\"/img/sw8.jpg\" border=\"0\"  id=\"SW8\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'SW8\\\', \\\'/img/sw8.jpg\\\')', 100)\">\n"
	"<P ALIGN=\"CENTER\">\n"
	"<H3><P ALIGN=\"CENTER\">Leds on Board</H3>\n"
	"<form name=\"myform\" action=\"\" method=\"POST\">\n"
	"<div align=\\center\\>\n"
	"<input type=\"hidden\" name=\"Led\" value=\"AAA\">"
	"<P ALIGN=\"CENTER\">\n"
	"<frameset rows=\"30%, 70%\">\n"
	"<!--led1-->"
	"<input type=\"checkbox\" name=\"Led1\" value=\"Led1_on\"         > Led1"
	"<!--led2-->"
	"<input type=\"checkbox\" name=\"Led2\" value=\"Led2_on\"         > Led2"
	"<!--led3-->"
	"<input type=\"checkbox\" name=\"Led3\" value=\"Led3_on\"         > Led3"
	"<!--led4-->"
	"<input type=\"checkbox\" name=\"Led4\" value=\"Led4_on\"         > Led4"
	"<!--led5-->"
	"<input type=\"checkbox\" name=\"Led5\" value=\"Led5_on\"         > Led5"
	"<!--led6-->"
	"<input type=\"checkbox\" name=\"Led6\" value=\"Led6_on\"         > Led6"
	"<!--led7-->"
	"<input type=\"checkbox\" name=\"Led7\" value=\"Led7_on\"         > Led7"
	"<!--led8-->"
	"<input type=\"checkbox\" name=\"Led8\" value=\"Led8_on\"         > Led8"
	"<br>"
	"<br>"
	"<input type=\"submit\" value=\"Send\"><br>"
	"</div>\n"
	"</form>\n"
	"<div align=\"center\">\n"
  	"<p ALIGN=\"CENTER\">\n" 
  		"<img src=\"/img/camera_320x240.png\" border=\"0\" id=\"cameraPng\"\n"
	"     onload=\"window.setTimeout('reload_image(\\\'cameraPng\\\', \\\'/img/camera_320x240.png\\\')', 1000)\">\n"
	"</div>\n"
	"<div align=\"center\">\n"
	"<p><a href=\"http://www.evidence.eu.com\"><img src=\"/img/logo-footer.png\" alt=\"Evidence\"></a><a href=\"http://www.evidence.eu.com\"><br>\n"
	"</a><a href=\"http://www.evidence.eu.com\">www.evidence.eu.com </a></p>\n"
	"</div>\n"
	"</body>\n"
	"</html>\n";

const struct fsdata_file file__index_html[] = { {
file__404_html,
my_name__index_html,
my_data__index_html,
sizeof(my_data__index_html),
1,
}};

void web_led_set(unsigned char led)
{
	state_led = led;
}

unsigned char web_led_get(void)
{
	return state_led;
}

void _T1Callback(void)
{
	static unsigned int ms = 0;
	if (ms++ == REFRESH_HTLM_MS){
		ActivateTask(sw_periodic);
		ms = 0;
	} else {
	}
}

int htlm_change(char* htlm, unsigned char sw) /*, unsigned char led)*/
{

	unsigned char led = web_led_get();

	/* Update switch. */
	if(sw & MASK_SW1){
		file_sw_1_jpg->data = sw_on_data_jpg;
		file_sw_1_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_1_jpg->data = sw_off_data_jpg;
		file_sw_1_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW2){
		file_sw_2_jpg->data = sw_on_data_jpg;
		file_sw_2_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_2_jpg->data = sw_off_data_jpg;
		file_sw_2_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW3){
		file_sw_3_jpg->data = sw_on_data_jpg;
		file_sw_3_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_3_jpg->data = sw_off_data_jpg;
		file_sw_3_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW4){
		file_sw_4_jpg->data = sw_on_data_jpg;
		file_sw_4_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_4_jpg->data = sw_off_data_jpg;
		file_sw_4_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW5){
		file_sw_5_jpg->data = sw_on_data_jpg;
		file_sw_5_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_5_jpg->data = sw_off_data_jpg;
		file_sw_5_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW6){
		file_sw_6_jpg->data = sw_on_data_jpg;
		file_sw_6_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_6_jpg->data = sw_off_data_jpg;
		file_sw_6_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW7){
		file_sw_7_jpg->data = sw_on_data_jpg;
		file_sw_7_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_7_jpg->data = sw_off_data_jpg;
		file_sw_7_jpg->len = sizeof(sw_off_data_jpg);
	}
	if(sw & MASK_SW8){
		file_sw_8_jpg->data = sw_on_data_jpg;
		file_sw_8_jpg->len = sizeof(sw_on_data_jpg);
	} else{
		file_sw_8_jpg->data = sw_off_data_jpg;
		file_sw_8_jpg->len = sizeof(sw_off_data_jpg);
	}
	myprintf("Update web state_led %d\r\n", led);
	/* Update led. */
	if(led & MASK_LED1){
		EE_led_on(0);
		pun = strstr(htlm, TAG_LED1);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED1)-1;
		memcpy ((void *) pun, (const void *) led1_check, (sizeof(led1_check) - 1));
	} else{
		EE_led_off(0);
		pun = strstr(htlm, TAG_LED1);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED1)-1;
		memcpy ((void *) pun, (const void *) led1_uncheck, (sizeof(led1_uncheck) - 1));
	} 

	if(led & MASK_LED2){
		EE_led_on(1);
		pun = strstr(htlm, TAG_LED2);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED2)-1;
		memcpy ((void *) pun, (const void *) led2_check, (sizeof(led2_check) - 1));
	} else{
		EE_led_off(1);
		pun = strstr(htlm, TAG_LED2);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED2)-1;
		memcpy ((void *) pun, (const void *) led2_uncheck, (sizeof(led2_uncheck) - 1));
	} 
	
	if(led & MASK_LED3){
		EE_led_on(2);
		pun = strstr(htlm, TAG_LED3);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED3)-1;
		memcpy ((void *) pun, (const void *) led3_check, (sizeof(led3_check) - 1));
	} else{
		EE_led_off(2);
		pun = strstr(htlm, TAG_LED3);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED3)-1;
		memcpy ((void *) pun, (const void *) led3_uncheck, (sizeof(led3_uncheck) - 1));
	} 
	
	if(led & MASK_LED4){
		EE_led_on(3);
		pun = strstr(htlm, TAG_LED4);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED4)-1;
		memcpy ((void *) pun, (const void *) led4_check, (sizeof(led4_check) - 1));
	} else{
		EE_led_off(3);
		pun = strstr(htlm, TAG_LED4);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED4)-1;
		memcpy ((void *) pun, (const void *) led4_uncheck, (sizeof(led4_uncheck) - 1));
	} 
	
	if(led & MASK_LED5){
		EE_led_on(4);
		pun = strstr(htlm, TAG_LED5);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED5)-1;
		memcpy ((void *) pun, (const void *) led5_check, (sizeof(led5_check) - 1));
	} else{
		EE_led_off(4);
		pun = strstr(htlm, TAG_LED5);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED5)-1;
		memcpy ((void *) pun, (const void *) led5_uncheck, (sizeof(led5_uncheck) - 1));
	} 
	
	if(led & MASK_LED6){
		EE_led_on(5);
		pun = strstr(htlm, TAG_LED6);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED6)-1;
		memcpy ((void *) pun, (const void *) led6_check, (sizeof(led6_check) - 1));
	} else{
		EE_led_off(5);
		pun = strstr(htlm, TAG_LED6);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED6)-1;
		memcpy ((void *) pun, (const void *) led6_uncheck, (sizeof(led6_uncheck) - 1));
	} 

	if(led & MASK_LED7){
		EE_led_on(6);
		pun = strstr(htlm, TAG_LED7);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED7)-1;
		memcpy ((void *) pun, (const void *) led7_check, (sizeof(led7_check) - 1));
	} else{
		EE_led_off(6);
		pun = strstr(htlm, TAG_LED7);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED7)-1;
		memcpy ((void *) pun, (const void *) led7_uncheck, (sizeof(led7_uncheck) - 1));
	} 

	if(led & MASK_LED8){
		EE_led_on(7);
		pun = strstr(htlm, TAG_LED8);
		if (pun == NULL) {
			return 1;
		}
		pun = pun + sizeof(TAG_LED8)-1;
		memcpy ((void *) pun, (const void *) led8_check, (sizeof(led8_check) - 1));
	} else{
		EE_led_off(7);
		pun = strstr(htlm, TAG_LED8);
		if (pun == NULL) {
			//printf("Nessuna corrispondenza\r\n");
			return 1;
		}
		pun = pun + sizeof(TAG_LED8)-1;
		memcpy ((void *) pun, (const void *) led8_uncheck, (sizeof(led8_uncheck) - 1));
	} 
	
	return 0;
}

void fun_task(void)
{
	unsigned int sw_rd;
	unsigned char sw_wr = 0;
	
	sw_rd = EE_switch_read_all();
	
	// SW8
	if( sw_rd & 0x0002 ) sw_wr |= MASK_SW8;
	else                 sw_wr &= ~MASK_SW8;
	// SW7
	if( sw_rd & 0x0004 ) sw_wr |= MASK_SW7;
	else                 sw_wr &= ~MASK_SW7;
	// SW6
	if( sw_rd & 0x0008 ) sw_wr |= MASK_SW6;
	else                 sw_wr &= ~MASK_SW6;
	// SW5
	if( sw_rd & 0x0010 ) sw_wr |= MASK_SW5;
	else                 sw_wr &= ~MASK_SW5;
	// SW4
	if( sw_rd & 0x0020 ) sw_wr |= MASK_SW4;
	else                 sw_wr &= ~MASK_SW4;
	// SW3
	if( sw_rd & 0x0040 ) sw_wr |= MASK_SW3;
	else                 sw_wr &= ~MASK_SW3;
	// SW2
	if( sw_rd & 0x0080 ) sw_wr |= MASK_SW2;
	else                 sw_wr &= ~MASK_SW2;
	// SW1
	if( sw_rd & 0x0100 ) sw_wr |= MASK_SW1;
	else                 sw_wr &= ~MASK_SW1;

	htlm_change((char*)my_data__index_html, sw_wr);

}

/* Task: update web-page */
TASK(sw_periodic)
{
	fun_task();
}


#define FS_ROOT file__index_html
#define FS_NUMFILES 3

