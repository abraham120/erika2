

#########################################################################################
#
# NO CHANGES BELOW THIS LINE!
#
#########################################################################################
BASE_DIR=`pwd`

export RTDRUID_ECLIPSE_HOME=`cygpath -ms ${BASE_DIR}/OS_EE/RT-Druid`
export ERIKA_FILES=`cygpath -ms ${BASE_DIR}/OS_EE/ee_base`

# To support different derivatives in the same project use this environment variable
# export APP_DEVICE=s12gn16_
# ATT! You need an OIL file named: 's12gn16_conf.oil' 
# ATT! A folder named s12gn16_output will be created.

cd OS_EE

if [ -z "$1" ]
then
	make
	cd ${BASE_DIR}
	exit 1;
fi

if [ $1 = "make" ]
then
	make
	cd ${BASE_DIR}
	exit 1;
fi

if [ $1 = "clean" ]
then
	make clean
	cd ${BASE_DIR}
	exit 1;
fi
