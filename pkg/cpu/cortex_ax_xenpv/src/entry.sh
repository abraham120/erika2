#!/bin/bash

cat << EOF;
#ifndef EE_GIC_PRIO_TABLE_H__
#define EE_GIC_PRIO_TABLE_H__

#define EE_CAX_ISR1_PRI(x) (((127-x) < 0) ? 0 : (((127-x) > 127) ? 127 : (127-x)))
#define EE_CAX_ISR2_PRI(x) (((255-x) < 128) ? 128 : (((255-x) > 255) ? 255 : (255-x)))

struct {
  unsigned int intID;
  unsigned char prio;
} prio_table = {
EOF
for i in `seq 0 1029`; do
cat << EOF;
#if (defined(EE_CAX_${i}_ISR) && (EE_CAX_MAX_ISR_ID >= $i) && (EE_CAX_MAX_ARCH_ISR_ID >= $i))
#if (EE_CAX_${i}_ISR_CAT == 2)
 { ${i}, EE_CAX_ISR2_PRI(EE_CAX_${i}_ISR_PRI) },
#else
 { ${i}, EE_CAX_ISR1_PRI(EE_CAX_${i}_ISR_PRI) },
#endif
#endif
EOF
done
cat << EOF;
};

#endif /* EE_GIC_PRIO_TABLE_H__ */
EOF

exit 0

echo "/* externs ... */"
for i in `seq 0 1029`; do
cat << EOF;
#if ((EE_CAX_MAX_ISR_ID >= $i) && (EE_CAX_MAX_ARCH_ISR_ID >= $i) && defined(EE_CAX_${i}_ISR))
extern void EE_CAX_${i}_ISR (void);
#endif
EOF
done
echo
echo
echo "EE_ADDR EE_IRQ_HANDLER_TABLE2[] = {"
for i in `seq 0 1029`; do
cat << EOF;
#if ((EE_CAX_MAX_ISR_ID >= $i) && (EE_CAX_MAX_ARCH_ISR_ID >= $i))
#if defined(EE_CAX_${i}_ISR)
EE_CAX_${i}_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

EOF
done
echo "};"
echo

exit 0
