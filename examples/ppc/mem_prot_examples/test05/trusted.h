#ifndef TRUSTED_H
#define TRUSTED_H

void TRUSTED_MyTaskTrustedService(TrustedFunctionIndexType index,
	TrustedFunctionParameterRefType ref);
void TRUSTED_MyIsrTrustedService(TrustedFunctionIndexType index,
	TrustedFunctionParameterRefType ref);
EE_INT32 TRUSTED_MyQuickTrustedService(EE_INT32 arg);

#endif /* TRUSTED_H */
