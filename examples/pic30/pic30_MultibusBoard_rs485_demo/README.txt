- RS485 half-duplex communication on FLEX + Multibus daughter board

HW Configuration:
	Two sets of FLEX Full board + Multibus Daughter board + RS485 module
	RS485 on UART2 slot (second to right on the multibus board)
	RS232 module on UART1 slot for Receiver

Development environment:
	RT-Druid 1.5.1
	Microchip C Compiler 3.0 for dsPIC DSCs
	MPLAB 8.50 or 8.66

Port assignment:
<Sender>
	UART1 - not used
	UART2 - RS485
<Receiver>
	UART1 - serial to console (PC hyperterminal)
	UART2 - RS485
	
Cable pin configuration:
	Node 1								Node 2
	MORS3 pin 1 <-> MORS3 pin 1 (485-)
	MORS3 pin 2 <-> MORS3 pin 2 (485+)
	MORS3 pin 3 <-> MORS3 pin 3 (GND, optional)

Role assignment: (cf. define.h)
	#define		RS485_PORT_UART2
	and
	#define		RS485_UART2_SENDER		// set as Transmitter
	#undef		RS485_UART2_SENDER		// set as Receiver

How to test the program:
<Sender>
Build the project by defining both RS485_PORT_UART2 and RS485_UART2_SENDER (by commenting out the #undef RS485_UART2_SENDER) in define.h.
The sender peridically sends "<H>" to the receiver via RS485. This is done by TaskSend by an alarm (AlarmSend) by a timer.

<Receiver>
Build the project by defining RS485_PORT_UART2 and undefing RS485_UART2_SENDER in define.h.
The receiver runs TaskDebug continuously. TaskDebug monitors input from UART2 (RS485) and relays it to UART1 (serial port to console). Communication activities in UART ports are all handled by interrupts. Those ISRs and TaskDebug share buffers protected by mutual exclusion (in this code, disable/enable interrupt).

Note:
	Init code for UART1 (EE_UART1_Init()) does not support this RS485 configuration. To use UART1 port for RS485, modify the init code accordingly.
	This project is borrowed from the Serial demo template in the RT-Druid C/C++ Project. 
