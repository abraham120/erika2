export EE_INSTALLDIR=`cygpath -ms \`reg query HKEY_LOCAL_MACHINE\\\\\\\\SOFTWARE\\\\\\\\Evidence /v EE_InstallPath | awk  '/EE_InstallPath/{ print $3 }'\` | xargs cygpath`

echo --------------------------------------------------------
echo Step 1: OIL parsing and code generation
echo
echo RT-Druid is parsing the OIL file to generate the 
echo makefiles used for the compilation 
echo --------------------------------------------------------

export PARAM1_WINNOSPACES=`echo ${EE_MPLAB_GENERATELIB_PARAM1} | awk '{ gsub(/"/, ""); print }' | cygpath -ms -f -`
#export PARAM2_WINNOSPACES=`echo ${EE_MPLAB_GENERATELIB_PARAM2} | awk '{ gsub(/"/, ""); print }' | cygpath -ms -f -`
export PARAM1=`echo ${EE_MPLAB_GENERATELIB_PARAM1} | awk '{ gsub(/"/, ""); print }' | cygpath -ms -f - | xargs cygpath`
export PARAM2=`echo ${EE_MPLAB_GENERATELIB_PARAM2} | awk '{ gsub(/"/, ""); print }' | cygpath -ms -f - | xargs cygpath`

mkdir -p ${PARAM2}/Debug

export PARAM2_DEBUG_WINNOSPACES=`echo ${PARAM2}/Debug | cygpath -ms -f -`
export ECLIPSE_HOME=`cygpath -ms ${EE_INSTALLDIR}/eclipse`

${EE_INSTALLDIR}/eclipse/evidence/rtd_launcher.bat --oil ${PARAM1_WINNOSPACES} --output ${PARAM2_DEBUG_WINNOSPACES}

# add MPLABIDE command to the makefile
echo GENERATE_MPLABIDE_LIBS:=TRUE > ${PARAM2}/Debug/makefile.temp
cat ${PARAM2}/Debug/makefile.temp ${PARAM2}/Debug/makefile > ${PARAM2}/Debug/makefile.temp2
mv ${PARAM2}/Debug/makefile.temp2 ${PARAM2}/Debug/makefile
rm ${PARAM2}/Debug/makefile.temp


echo --------------------------------------------------------
echo Step 2: Compiling the libraries
echo --------------------------------------------------------
cd ${PARAM2}/Debug
make

echo --------------------------------------------------------
echo Step 3: Generating the distribution
echo --------------------------------------------------------
mkdir -p ${PARAM2}/Files/lib
cp ${PARAM2}/Debug/*.a ${PARAM2}/Files/lib

for d in `cat ${EE_INSTALLDIR}/ee/pkg/cfg/arch/rules_microchip_pic30_mplab_dirs.txt`; do 
  echo Creating ${d};
  mkdir -p ${PARAM2}/Files/${d}; 
done;

for f in `cat ${EE_INSTALLDIR}/ee/pkg/cfg/arch/rules_microchip_pic30_mplab_files.txt`; do 
  echo Copying ${f};
  cp ${EE_INSTALLDIR}/ee/${f} ${PARAM2}/Files/${f}; 
done;

# if they exist, copy the pic30regs.* and the frommchp directory
if test -e ${PARAM2}/Debug/ee_pic30regs.h; then \
    echo Copying mplab register files; \
    cp ${PARAM2}/Debug/ee_pic30regs.h ${PARAM2}/Files/pkg/ee_pic30regs.h; \
    cp ${PARAM2}/Debug/ee_pic30regs.inc ${PARAM2}/Files/pkg/ee_pic30regs.inc; \
    cp -r ${PARAM2}/Debug/frommchp ${PARAM2}/Files/pkg; \
fi

echo Generating eecfg.h
cat ${PARAM2}/Debug/eeopt.h ${PARAM2}/Debug/eecfg.h >${PARAM2}/Files/pkg/eecfg.h

echo --------------------------------------------------------
echo Step 4: Generating the project file.
echo --------------------------------------------------------

cat > ${PARAM2}/Files/EE.mcp <<EOF
[HEADER] 
magic_cookie={66E99B07-E706-4689-9E80-9B2582898A13}
file_version=1.0
[PATH_INFO]
dir_src=
dir_bin=
dir_tmp=
dir_sin=
dir_inc=pkg
dir_lib=
dir_lkr=
[CAT_FILTERS]
filter_src=*.s;*.c
filter_inc=*.h;*.inc
filter_obj=*.o
filter_lib=*.a
filter_lkr=*.gld
[OTHER_FILES]
file_000=no
[FILE_INFO]
file_000=lib\libee.a
[SUITE_INFO]
suite_guid={479DDE59-4D56-455E-855E-FFF59A3DB57E}
suite_state=-omf=elf
[TOOL_SETTINGS]
TS{7D9C6ECE-785D-44CB-BA22-17BF2E119622}=-g
TS{25AC22BD-2378-4FDB-BFB6-7345A15512D3}=-g
TS{7DAC9A1D-4C45-45D6-B25A-D117C74E8F5A}=-o"$(TARGETBASE).$(TARGETSUFFIX)" -Map="$(TARGETBASE).map"
TS{509E5861-1E2A-483B-8B6B-CA8DB7F2DD78}=
EOF

echo --------------------------------------------------------
echo DONE... MPLAB Library successfully compiled!
echo
echo The Library is stored inside:
echo `echo ${EE_MPLAB_GENERATELIB_PARAM2} | awk '{ gsub(/"/, ""); print }'`\\Files\\lib
echo --------------------------------------------------------
