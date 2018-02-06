#########################################################################################
#
# S12 Demo
#
#########################################################################################

DEBUG_DIRS=`find . -name "Debug_fake"`
echo "${DEBUG_DIRS}"
BASE_DIR=`pwd`
echo ${BASE_DIR}

if [ $1 = "make" ]
then
	echo "S12 Demo-Examples compilation."
	echo "Make in progress..."
	for file in ${DEBUG_DIRS}
	do
		echo " "
		echo "======================================================================"
		cd "$file"
		echo "$file"
  		make
  		cd ${BASE_DIR}
	done
	echo "======================================================================"
	echo "Make in progress...Done!!!"
elif [ $1 = "clean" ]
then
	echo "S12 Demo-Examples cleaning."
	echo "Clean in progress..."
	for file in ${DEBUG_DIRS}
	do
		echo " "
		echo "======================================================================"
		cd "$file"
		echo "$file"
  		make clean
  		cd ${BASE_DIR}
	done
	echo "======================================================================"
	echo "Clean in progress...Done!!!"
fi
	

