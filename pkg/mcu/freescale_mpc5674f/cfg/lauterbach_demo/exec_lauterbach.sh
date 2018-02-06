#!/bin/bash

# How to launch:
# ./exec_lauterbach usb (for lauterbach usb connection)
# ./exec_lauterbach (for lauterbach net connection)

# Exit immediately if a command exits with a nonzero exit status (set -e)
set -e

foundt32=0
foundcmd=

# the exp[re3ssion in if statement: -d, -r, etc are called primaries

for d in . output Debug Release debug; do
# if [ -d $d ] return true if $d exists and is a directory
    if [ -d $d ]; then

	for f in start.sh start_flash.sh; do
	    if [ -r $d/$f ]; then
		cd $d
                if [ "$1" = "usb" ]; then
		        foundcmd="bash ./$f usb"
                else
                        foundcmd="bash ./$f lauterbach"
                fi
		echo >&2 "Found $f in $d"
		break 2
	    fi
	done
	for sd in . master cpu0; do 
# if [ -r $d/$sd/t32.cmm ] return true if $d/$sd/t32.cmm exists and is readable
#echo "$d/$sd/t32.cmm"
	    if [ -r $d/$sd/t32.cmm ]; then
		cd $d/$sd
		foundt32=1
		echo >&2 "Found t32.cmm in $d/$sd"
		break 2
	    fi
	done
    fi
done

# if [ -r $d/$sd/t32.cmm ] return true if $d/$sd/t32.cmm exists and is readable



if [ $foundt32 == 0 -a "$foundcmd" == "" ]; then
    if [ -r ./t32.cmm ]; then
	echo >&2 "Found t32.cmm in the current directory"
    else
	echo >&2 "WARNING: no t32.cmm file found in known directories!"
    fi
fi

#read -p "Press any key to start backup..."


if [ -n "$foundcmd" ]; then
    exec $foundcmd
else
# Special Lauterbach executable used (Only!!!) for Simulated Demo
    exec t32mppc-qt
fi

