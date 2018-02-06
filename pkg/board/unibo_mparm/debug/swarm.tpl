
########################################################
# Set Simulator constants
########################################################
SIM="mpsim.x"
#SIM="mpsim.x -nodataset -execute"

SWITCHES="-c $CORENUMBER"
#SWITCHES="-c $CORENUMBER --intc=x --is=9 --ds=9"
#SWITCHES="-c $CORENUMBER --intc=x -I 0 -H 0 -P 0"
#SWITCHES="-c $CORENUMBER --intc=a -d -cwp=b"
#SWITCHES="-c $CORENUMBER --intc=i -r 12 --ds=8 --is=8 -B 5"
#SWITCHES="-c $CORENUMBER --intc=x"
#SWITCHES="-c $CORENUMBER --intc=s -w -f -v -F0,1 -F2,1 -F3,1 -F4,1 -L0,10 -L1,30"
#SWITCHES="-c $CORENUMBER --intc=i -d --cmdl=xyzab" # -I 0 -H 0 -P 0"
#SWITCHES="-c $CORENUMBER --intc=i -c 1 -S -d"
#SWITCHES="-c $CORENUMBER --intc=i -B 2 -R 1"
#SWITCHES="-c $CORENUMBER --intc=i --cfile=$SWARMDIR/../config/12m_16s_2ahb_2b.cfg -w --is=9 --ds=9"
#SWITCHES="-c $CORENUMBER --intc=h -F0,1 -F1,6 -F2,4 -F3,5 -F4,2 -k 1"
#SWITCHES="-c $CORENUMBER --intc=i -o --tgtrace"
#SWITCHES="-c $CORENUMBER --intc=i -o --core=t -a"
#SWITCHES="-c $CORENUMBER --intc=s -w --is=14 --it=1 --ds=14 --dt=4"
#SWITCHES="-c $CORENUMBER --intc=s -w -F 0,1 -F 1,1 -F 2,1 -F 3,1 -F 4,1 --core=w --sfile=$BENCHNAME.stats.txt"
#SWITCHES="-c $CORENUMBER --ds=10 --is=12 --intc=a --i-s --i-size=12 -t -w"

########################################################
# Check CORENUMBER
########################################################
case $CORENUMBER in
  *[!0-9]*|"") echo
               echo Error: CORENUMBER input parameter must be numeric!
               echo
               exit 1 ;;
  *) ;;
esac

########################################################
# Check BENCHNAME
########################################################
if [ -z $BENCHNAME ]; then
	echo "No files given. Using defaults."
	BENCHNAME=mparm.elf
fi

########################################################
# Show Parameters
########################################################
echo Nodes = $CORENUMBER, Application = $BENCHNAME

########################################################
# Clean or create the app directory
########################################################
if test ! -d ./bench/ ; then
	echo
	echo Creating bench directory.
	mkdir ./bench
else
	echo
	echo Cleaning bench directory.
	rm -f ./bench/TargetMem_*.mem
fi

########################################################
# Create binary images of benchmarks
########################################################
COUNT=1
#make clean
#make
while [ $COUNT -le $CORENUMBER ]
do
	cp $BENCHNAME bench/TargetMem_$COUNT.mem
	if test $? -ne 0 ; then
		exit 1
	fi
	COUNT=`expr $COUNT + 1`
done

########################################################
#empty images for other system memories (e.g. shared), which must
#be initialized to zeroes
########################################################
echo -n > bench/TargetMem_$COUNT.mem
COUNT=`expr $COUNT + 1`
echo -n > bench/TargetMem_$COUNT.mem
COUNT=`expr $COUNT + 1`
echo -n > bench/TargetMem_$COUNT.mem

########################################################
# Create symbolic link to simulator
########################################################
if test ! -f ./bench/$SIM -o ! -x ./bench/$SIM ; then
	if test ! -f $SWARMDIR/bin/$SIM -o ! -x $SWARMDIR/bin/$SIM ; then
		echo
		echo Error: no simulator executable found.
		echo Please check your SWARMDIR [=$SWARMDIR] environment variable.
		echo
		exit 1
	else
		echo
		echo Create symlink to MPARM simulator.
		ln -s $SWARMDIR/bin/$SIM ./bench
	fi
fi


########################################################
#launch the simulation
########################################################
cd bench
echo
echo $SIM $SWITCHES $MPARMOPTIONS
echo
./$SIM $SWITCHES $MPARMOPTIONS
