# this script is used to compile an application passed as parameter
# it is used during the regreswsion tests.
# This script is not made to be run alone
#
# $1 = directory to test
# $2 = $(ECLIPSE_HOME)
# $3 = $(BATCH_TEMPLATE)
# $4 = $(BATCH_GENERATOR)

rm -rf regression/$1
mkdir -p regression/$1

printf "$1: START\n"
printf "$1: START\n" >>regression/output.log

printf "$1: template\n"
printf "$1: template\n" >>regression/output.log
cd regression/$1

export ECLIPSE_HOME=$2
$3 --template $1 --output . >>output.log 2>&1 || exit
cd ../..

printf "$1: OIL\n"
printf "$1: OIL\n" >>regression/output.log
cd regression/$1
export ECLIPSE_HOME=$2
$4 --template $1 --output . >>output.log 2>&1 || exit
cd ../..

printf "$1: Compile\n"
printf "$1: Compile\n" >>regression/output.log
make -C regression/$1/Debug >>regression/$1/output.log 2>&1 || exit

printf "$1: OK\n-------------------------------------\n"
printf "$1: OK\n-------------------------------------\n" >>regression/output.log
touch regression/$1/doneflag.txt
