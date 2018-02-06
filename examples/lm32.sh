#!/bin/sh

# This script sets-up LatticeMico32 System environment.

if [ "${LM32_PATH:-notset}" != "notset" ]; then
  micoPath=$LM32_PATH
else
  micoPath=/usr/local/diamond/1.3/micosystem
fi

################################################################
# update environment
################################################################

PATH=$PATH:$micoPath/gtools/bin
export PATH

MOZILLA_FIVE_HOME=$micoPath/mozilla-seamonkey-1.0.1
export MOZILLA_FIVE_HOME

if [ "${LD_LIBRARY_PATH:-notset}" != "notset" ]; then
  LD_LIBRARY_PATH=$micoPath/gtools/bin:$micoPath/gtools/lib:$LD_LIBRARY_PATH
  LD_LIBRARY_PATH=${MOZILLA_FIVE_HOME}:$LD_LIBRARY_PATH
else
  LD_LIBRARY_PATH=$micoPath/gtools/bin:$micoPath/gtools/lib
  LD_LIBRARY_PATH=${MOZILLA_FIVE_HOME}:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

if [ "${PERL5LIB:-notset}" != "notset" ]; then
  PERL5LIB=$micoPath/utilities/perlscript:$PERL5LIB
else
  PERL5LIB=$micoPath/utilities/perlscript
fi
export PERL5LIB

if [ "${LD_ASSUME_KERNEL:-notset}" != "notset" ]; then
  unset LD_ASSUME_KERNEL
fi
