#!/bin/bash

echo "=== Monostack ==="

for i in $(seq 1 8) ; do
	echo "---- Running EEtest0$i ----"
	cd EEtest0$i
	make clean > /dev/null 2>&1
	make run | grep TEST
	make clean > /dev/null 2>&1
	cd - > /dev/null 2>&1
	echo "--------------------------"
done
