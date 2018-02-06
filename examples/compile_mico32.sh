#!/bin/sh

# this script is used to compile an application passed as parameter
# it is used during the regression tests for mico32 architecture.
# This script is not made to be run alone
#
# $1 = directory to test
# $2 = $(ECLIPSE_HOME)
# $3 = $(BATCH_TEMPLATE)
# $4 = $(BATCH_GENERATOR)
# $5 = $(MICO32_PLATFORM_LIB_PATH)
# $6 = $(LM32_PATH)

. ./lm32.sh

rm -rf regression/$1
mkdir -p regression/$1

printf "$1: START\n"
printf "$1: START\n" >>regression/output.log

printf "$1: template\n"
printf "$1: template\n" >>regression/output.log
cd regression/$1
$3 $2 $1 . >>output.log 2>&1 || exit
cd ../..

#~ printf "$1: OIL\n"
#~ printf "$1: OIL\n" >>regression/output.log
#~ cd regression/$1
#~ $4 $2 conf.oil Debug >>output.log 2>&1 || exit
#~ cd ../..

printf "$1: Compile\n"
printf "$1: Compile\n" >>regression/output.log
make PLATFORM_LIB_PATH=$5 -C regression/$1 >>regression/$1/output.log 2>&1 || \
exit

printf "$1: OK\n-------------------------------------\n"
printf "$1: OK\n-------------------------------------\n" >>regression/output.log
touch regression/$1/doneflag.txt
