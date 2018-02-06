#!/bin/bash

# This script filters only the error entries that do not correspond to accepted deviations. If this script returns a empty file (empty real_errors.report) the check is ok, otherwise there are new MISRA errors to be managed.

if [ $# -ne 2 ]
then
    echo "Error in ${0} - Invalid Argument Count"
    echo "Syntax: ${0} <file_to_filter> <filtered_file>"
    exit
fi

cp ${1} ${2}
cat ${2} | grep -v -E "(ppc/eval_misra/output_prot/eecfg.c)(.*)(\[MM-PWT 3: MISRA 11.4\])" > ${1}.tmp ; mv ${1}.tmp ${2}
cat ${2} | grep -v "\[MM-PWT 2: MISRA 20.2\]" > ${1}.tmp ; mv ${1}.tmp ${2}
cat ${2} | grep -v -E "(pkg/kernel/as/src/ee_osapp.c)(.*)(Error 818: Pointer parameter 'Value' of type 'ApplicationStateRefType' \(line)(.*)(\) could be declared as pointing to const \[MM-PWT 4: MISRA 16.7\])" > ${1}.tmp; mv ${1}.tmp ${2}
cat ${2} | grep -v -E "(pkg/kernel/oo/src/ee_getelapsedvalue.c)(.*)(Error 818: Pointer parameter 'Value' of type 'TickRefType' \(line)(.*)(\) could be declared as pointing to const \[MM-PWT 4: MISRA 16.7\])" > ${1}.tmp ; mv ${1}.tmp ${2}
cat ${2} | grep -v -E "(pkg/kernel/oo/inc/ee_common.h)(.*)(Error 960: Violates MISRA 2004 Required Rule 18.4, declaration of union type or object of union type: 'EE_oo_ErrorHook_parameters'  \[MM-PWT 2: MISRA 18.4\])" > ${1}.tmp; mv ${1}.tmp ${2}
cat ${2} | grep -v -E "(pkg/kernel/oo/src/ee_lookup.c)(.*)(Error 960: Violates MISRA 2004 Required Rule 18.4, declaration of union type or object of union type: 'EE_oo_ErrorHook_parameters'  \[MM-PWT 2: MISRA 18.4\])" > ${1}.tmp; mv ${1}.tmp ${2}
cat ${2} | grep -v -E "(pkg/kernel/rn/inc/ee_rn_internal.h)(.*)(Error 960: Violates MISRA 2004 Required Rule 18.4, declaration of union type or object of union type: '{...}'  \[MM-PWT 2: MISRA 18.4\])" > ${1}.tmp ; mv ${1}.tmp ${2}

echo "REPORT filtrato"
cat ${2}
echo "END"


