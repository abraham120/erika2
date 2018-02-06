# The makefile
#
#
# Usage:
#  make 
#  make all
#  make clean

export CC = gcc
export LD = gcc
export C_OPTS = -Wall -ggdb

# general rules

all: confparser_mux confparser_demux confparser_demux2

clean:
	rm -rf confparser_mux confparser_demux confparser_demux2 *.o

confparser_mux : confparser_mux.o
	$(LD) confparser_mux.o -o confparser_mux

confparser_demux : confparser_demux.o
	$(LD) confparser_demux.o -o confparser_demux

confparser_demux2 : confparser_demux2.o
	$(LD) confparser_demux2.o -o confparser_demux2

%.o : %.c
	$(CC) $(C_OPTS) -c $< -o $@
