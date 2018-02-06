/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#include "BswCommon.h"
#include "ErrorCfg.h"



#define SetErrorDevelop(errId, reported)    if (reported) { \
                                                while(1) \
													; \
                                            }

#define SetErrorFatal(errId, reported)      if (reported) { \
                                                while(1) \
													; \
                                            }

#define SetError(errId, reported)           0; \
                                            /*if (reported) { \
                                                while(1) \
													; \
                                            }*/


#define SetSymptom(sympt)
#define SetEnvParameters(index, value)
#define _SetError(errId, reported, lineNr)
#define _SetErrorFatal( errId, lineNr)
#define ErrorInit()
#define LoadErrorsFromFlash()
#define SaveErrorsToFlash()                 STD_OK
#define GetErrorConfirmed(errId)
#define GetErrorStored(errId)
#define GetNumberOfStoredErrors()           0
#define ErrorRead_Reset()
#define ErrorRead_Next()                    STD_NOT_OK
#define ErrorRead_GetErrId()
#define ErrorRead_GetReported()
#define ErrorRead_GetConfirmed()
#define ErrorRead_GetStored()
#define ErrorRead_GetEraseCounter()
#define ErrorRead_GetConfirmationCounter()
#define ErrorRead_GetDetailsAvailable()
#define ErrorRead_GetDtc()                  0
#define ErrorRead_GetTimestamp1()
#define ErrorRead_GetTimestamp2()
#define ErrorRead_GetLineNumber()
#define ErrorRead_GetSymptom()
#define ErrorRead_GetEnvPars()



#endif      // _ERROR_H_
