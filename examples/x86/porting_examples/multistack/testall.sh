#!/bin/bash

echo "=== Multistack ==="

for i in $(seq 0 6) ; do
	echo "---- Running EEtest0$i ----"
	cd EEtest0$i
	make clean > /dev/null 2>&1
	make run | grep TEST
	make clean > /dev/null 2>&1
	cd - > /dev/null 2>&1
	echo "--------------------------"
done
