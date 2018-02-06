#!/bin/bash

export ECLIPSE_HOME=/opt/case/evidence/eclipse
export RTDRUID_ECLIPSE_HOME=/opt/case/evidence/eclipse
export CORTEX_AX_XENPV_GCCDIR=/usr/

#make FAKE_DRUID=1 $@
make $@
