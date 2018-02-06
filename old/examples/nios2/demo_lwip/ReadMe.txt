Readme - ERIKA Enterprise port of the LWIP Web Server Software Example

This is a modified version of the LWIP Web Server Software Example distributed 
in the Nios Forum.

Please read the documentation distributed in PDF form with this modified demo.

Below you can find the original readme.

The Evidence Team.


Original Version
---------------------------------------------------------------------------

Readme - LWIP Web Server Software Example

DESCRIPTION:	
A standalone LWIP Web Server running from a filesystem in RAM memory.  Also
supports TCP echo on port 7, and IP fragmentation / reassembly.

REQUIREMENTS:
This example will run on the following Nios II designs, targeting the Nios
Stratix & Cyclone development boards:
- Standard
- Full Featured

PERIPHERALS USED:
This example exercises the following peripherals:
- Ethernet MAC (named "lan91c111" in SOPC Builder)
- STDOUT device (UART or JTAG UART)
- system timer

PERIPHERAL UPDATE REQUIRED:
The following peripheral (component) needs to be updated:
- altera_avalon_lan91c111: Replace the HAL subdirectory with the one 
  included with this kit.

SOFTWARE SOURCE FILES:
This example includes the following software source files:

- lwip_web_server.c: Contains main() which initializes the LWIP stack,
  and the http and TCPecho servers.  Polls the Ethernet device for input.
  Also sets the default IP address and network.

- mac_addr.c: Contains MAC address routine to program the Ethernet address.
  This is used by LWIP during initialization, but is implementation-specific
  (you set your MAC address to whatever you want.. or read it from your own 
  special non-volatile memory).

- lwipopts.h: Default values and features for building the LWIP stack.
  This set will work for most applications.  Care must be taken to fully
  understand the implications of changing any default value.  Refer to
  /lwip-0.7.1/src/include/lwip/opt.h for other features or values that can 
  have a default in lwipopts.h.

- .cdtbuild: Eclipse plugin default build file.  Normally generated, but
  included here to provide the default compiler include PATHs.  If the
  example will not build with this file, remove it, and add the following
  "Include Paths" to the nios-elf-gcc general configuration options (available
  in the "Properties" of the sample project):
    ../lwip-0.7.1/src/include
    ../lwip-0.7.1/src/include/ipv4
    ../lwip4hal/include
    ../apps

- apps/httpd.c: Implementation of an HTTP server including all necessary 
  rawapi callbacks to handle multiple connections and parsing basic HTTP 
  commands to handle GET requests. Requests for files via HTTP GET requests 
  direct the server to fetch the file, if available, from the RAM file system 
  and send it to the client requesting it.

- apps/httpd.h: Header information defining HTTP server implementation and
  common HTTP server strings & constants.

- apps/echo.c: Implementation of a TCP echo server including all necessary 
  rawapi callbacks to handle multuple connections.

- apps/echo.h: Header information defining TCP echo server implementation and 
  common TCP echo server strings & constants.

- apps/fs.c & fs.h fsdata.h: Provides simple access to the RAM filesystem.

- apps/fsdata.c: Generated file containing the RAM file system structure.

- apps/fs.zip: Zipped sample file system containing the web pages.  Generates
  an "fs/" directory.

- apps/makefsdata: Host utility for generating fsdata.c from a file system
  located in subdirectory "fs".  Unzip the fs.zip file for a sample web page
  file system.  Type "./makefsdata" from a shell with the current directory 
  set to "apps/" and the file system present in the "fs" subdirectory.

- lwip-0.7.1/: Directory containing the standard LWIP source files (less the
  socket API and the IP V6 subdirectories).

- lwip4hal/: Directory containing architecture (port) files for the Nios2 using
  the HAL OS option.


BOARD/HOST REQUIREMENTS:
This example requires an Ethernet cable connected to the development board's 
RJ-45 jack, and a JTAG connection with the development board. If the host 
communication settings are changed from JTAG UART (default) to use a
conventional UART, a serial cable between board DB-9 connector  and the host 
is required. 

ADDITIONAL INFORMATION:
This is an example HTTP server using LWIP in single-threaded environment.
The server can process basic requests to serve HTML, JPEG, and GIF files from 
the RAM file system. It is in no way a complete implementation of a 
full-featured HTTP server.

LWIP has two API's, a callback interface and "standard" sockets. This example
uses the callback (rawapi) interface.  
Refer to: lwip-0.7.1/doc/rawapi.txt.


     CONFIGURE WEB SERVER IP ADDRESS:
1. Create a new project from the LWIP Web Server example.  The main program
   will be opened.
2. Find and edit the IP address, network mask, and gateway address.  You will
   use this address from your web browser to test the application.

     RUN LWIP WEB SERVER EXECUTABLE:
1. Program the standard or full_featured design into the FPGA using the 
   Quartus programmer.
2. Build and run the application.  The configured IP address will be displayed
   in the terminal console window.
3. Browse the server using this IP address in the address bar of your browser.
4. Use a Telnet client to connect to TCP port 7 to exercise the echo function.
5. Use Ping with a length greater than 1500 and less than 5500 bytes to
   exercise the IP reassembly and fragmentation capability.

