#! /bin/bash

set -e

if [ "$1" = "USB" -o "$1" = "usb" ]; then
    dev=USB
elif [ "$1" != "" ]; then
    dev="NET NODE=$1 PACKLEN=1024"
else
    echo >&2 "Usage: $0  <remote_device> | usb"
    exit 2
fi

# first step: write flash (only)
t32mppc -c config-mc.t32,rom_multi.cmm 10000 e200z4-Master $dev CORE=1

# second step: exewcute two instances (GUIs) of t32
t32mppc -c config-mc.t32,start-mc.cmm 10000 e200z4-Master $dev CORE=1
