#!/bin/sh
for d in `ls -d */*/fake_druid`; do echo $d; cd $d; make clean; make; cd ../../..; done