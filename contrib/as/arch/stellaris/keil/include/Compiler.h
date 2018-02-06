/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

/** @file	Compiler.h
 *  @brief	AUTOSAR Compiler Abstraction Header File.
 *
 *  This file contains all the macros for abstraction of compiler specific
 *  keywords used for addressing data and code with declarations and
 *  definitions for Texas Instruments Stellaris LM4f232XXXX and Keil compiler.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */

/*
 * COMPILER047:	The Compiler.h header file shall protect itself against multiple
 * 		inclusions.
 */
#ifndef	COMPILER_H
#define	COMPILER_H

/** @brief	Target Compiler
 *
 *  <b>COMPILER010:</b> The compiler abstraction shall define a symbol for the
 *  target compiler according to the following naming convention:<br>
 *  <tt>_\<COMPILERNAME\>_C_\<PLATFORMNAME\>_</tt>
 *
 *  @note	These defines can be used to switch between different
 *  		implementations for different compilers, e.g.<br>
 *  		- inline assembler fragments in drivers
 *  		- special pragmas for memory alignment control
 *  		- localization of function calls
 *  		- adaptions to memory models
 */
#define	_KEIL_C_STELLARIS_

/*
 * COMPILER030:	“Compiler.h” shall provide information of the supported compiler
 * vendor and the applicable compiler version.
 *
 * Keil
 * µVision V4.23.00.0
 * Copyright (C) 2011 ARM Ltd and ARM Germany GmbH. All rights reserved.
 * 
 * Tool Version Numbers:
 * Toolchain:		MDK-Lite 	Version: 4.23
 * Toolchain Path:	C:\Keil\ARM\BIN40
 * C Compiler:		Armcc.Exe	V4.1.0.894 [Evaluation]
 * Assembler:		Armasm.Exe	V4.1.0.894 [Evaluation]
 * Linker/Locator:	ArmLink.Exe	V4.1.0.894 [Evaluation]
 * Librarian:		ArmAr.Exe	V4.1.0.894 [Evaluation]
 * Hex Converter:	FromElf.Exe	V4.1.0.894 [Evaluation]
 * CPU DLL:		SARMCM3.DLL	V4.23
 * Dialog DLL:		DCM.DLL		V1.4.0.0
 * Target DLL:		lmidk-agdi.dll	V???
 * Dialog DLL:		TCM.DLL		V1.4.0.0
 */

/** @brief	memory class AUTOMATIC
 *
 *  <b>COMPILER046:</b> The memory class <tt>AUTOMATIC</tt> shall be provided as
 *  empty definition, used for the declaration of local pointers.
 */
#define	AUTOMATIC

/** @brief	memory class TYPEDEF
 *
 *  <b>COMPILER059:</b> The memory class <tt>TYPEDEF</tt> shall be provided as
 *  empty definition. This memory class shall be used within type definitions,
 *  where no memory qualifier can be specified. This can be necessary for
 *  defining pointer types, with e.g. <tt>P2VAR</tt>, where the macros require
 *  two parameters. First parameter can be specified in the type definition
 *  (distance to the memory location referenced by the pointer), but the second
 *  one (memory allocation of the pointer itself) cannot be defined at this
 *  time. Hence memory class TYPEDEF shall be applied.
 */
#define	TYPEDEF

/** @brief	NULL pointer
 *
 *  <b>COMPILER051:</b> The compiler abstraction shall provide the
 *  <tt>NULL_PTR</tt> define with a void pointer to zero definition.
 */
#define	NULL_PTR	((void *)0)

/** @brief	INLINE keyword
 *
 *  <b>COMPILER057:</b> The compiler abstraction shall provide the
 *  <tt>INLINE</tt> define for abstraction of the keyword inline.
 */
#define	INLINE	__inline

/** @brief	LOCAL_INLINE keyword
 *
 *  <b>COMPILER060:</b> The compiler abstraction shall provide the
 *  <tt>LOCAL_INLINE</tt> define for abstraction of the keyword inline in
 *  functions with "static" scope.
 *
 *  @note	Different compilers may require a different sequence of the
 *  		keywords "static" and "inline" if this is supported at all.
 */
#define	LOCAL_INLINE	static __inline

/** @brief	Functions Macro.
 *  @param	rettype		return type of the function
 *  @param	memclass	classification of the function itself
 *
 *  <b>COMPILER001:</b> The compiler abstraction shall define the <tt>FUNC</tt>
 *  macro for the declaration and definition of functions, that ensures correct
 *  syntax of function declarations as required by a specific compiler.
 *
 *  <b>COMPILER058:</b> In the parameter list of this macro no further Compiler
 *  Abstraction macros shall be nested. Instead use a previously defined type as
 *  return type. Example:<br>
 *  <code>
 *    typedef P2VAR(uint8, AUTOMATIC, _near) NearDataType;<br>
 *    FUNC(NearDataType, _far) FarFuncReturnsNearPtr(void);
 *  </code>
 */
/* #define	FUNC(rettype, memclass)	\
		memclass rettype */
#define	FUNC(rettype, memclass)	\
	rettype

/** @brief	Pointer to Variables Macro.
 *  @param	ptrtype		type of the referenced variable
 *  @param	memclass	classification of the pointer's variable itself
 *  @param	ptrclass	defines the classification of the pointer's
 *  				distance
 *
 *  <b>COMPILER006:</b> The compiler abstraction shall define the <tt>P2VAR</tt>
 *  			macro for the declaration and definition of pointers in
 *  			RAM, pointing to variables.
 *
 *  The pointer itself is modifiable (e.g. ExamplePtr++).<br>
 *  The pointer's target is modifiable (e.g. *ExamplePtr = 5).
 */
/* #define	P2VAR(ptrtype, memclass, ptrclass)	\
		ptrclass ptrtype * memclass */
#define	P2VAR(ptrtype, memclass, ptrclass)	\
	ptrtype *

/** @brief	Pointer to Constants Macro.
 *  @param	ptrtype		type of the referenced constant
 *  @param	memclass	classification of the pointer's variable itself
 *  @param	ptrclass	defines the classification of the pointer's
 *  				distance
 *
 *  <b>COMPILER013:</b> The compiler abstraction shall define the
 *  <tt>P2CONST</tt> macro for the declaration and definition of pointers in RAM
 *  pointing to constants
 *
 *  The pointer itself is modifiable (e.g. ExamplePtr++).<br>
 *  The pointer's target is not modifiable (read only).
 */
/*#define	P2CONST(ptrtype, memclass, ptrclass)	\
		ptrclass const ptrtype * memclass */
#define	P2CONST(ptrtype, memclass, ptrclass)	\
	const ptrtype *

/** @brief	Constant Pointer to Variables Macro.
 *  @param	ptrtype		type of the referenced variable
 *  @param	memclass	classification of the pointer's constant itself
 *  @param	ptrclass	defines the classification of the pointer's
 *  				distance
 *
 *  <b>COMPILER031:</b> The compiler abstraction shall define the
 *  <tt>CONSTP2VAR</tt> macro for the declaration and definition of constant
 *  pointers accessing variables.
 *
 *  The pointer itself is not modifiable (fix address).<br>
 *  The pointer's target is modifiable (e.g. *ExamplePtr = 18).
 */
/* #define	CONSTP2VAR(ptrtype, memclass, ptrclass)	\
		ptrclass ptrtype * const memclass */
#define	CONSTP2VAR(ptrtype, memclass, ptrclass)	\
	ptrtype * const

/** @brief	Constant Pointer to Constants Macro.
 *  @param	ptrtype		type of the referenced constant
 *  @param	memclass	classification of the pointer's variable itself
 *  @param	ptrclass	defines the classification of the pointer's
 *  				distance
 *
 *  <b>COMPILER032:</b> The compiler abstraction shall define the
 *  <tt>CONSTP2CONST</tt> macro for the declaration and definition of constant
 *  pointers accessing constants.
 *
 *  The pointer itself is not modifiable (fix address).<br>
 *  The pointer's target is not modifiable (read only).
 */
/* #define	CONSTP2CONST(ptrtype, memclass, ptrclass)	\
		ptrclass const ptrtype * const memclass */
#define	CONSTP2CONST(ptrtype, memclass, ptrclass)	\
	const ptrtype * const

/** @brief	Pointer to Function Macro.
 *  @param	rettype		return type of the function
 *  @param	ptrclass	defines the classification of the pointer's
 *  				distance
 *  @param	fctname		function name respectively name of the defined
 *  				type
 *
 *  <b>COMPILER039:</b> The compiler abstraction shall define the
 *  <tt>P2FUNC</tt> macro for the type definition of pointers to functions.
 */
/* #define	P2FUNC(rettype, ptrclass, fctname)	\
		rettype (*ptrclass fctname) */
#define	P2FUNC(rettype, ptrclass, fctname)	\
	rettype (* fctname)

/** @brief	Constant Macro.
 *  @param	consttype	type of the constant
 *  @param	memclass	classification of the constant itself
 *
 *  <b>COMPILER023:</b> The compiler abstraction shall define the <tt>CONST</tt>
 *  macro for the declaration and definition of constants.
 */
/* #define	CONST(consttype, memclass)	\
		const consttype memclass */
#define	CONST(consttype, memclass)	\
	const consttype

/** @brief	Variable Macro.
 *  @param	vartype		type of the variable
 *  @param	memclass	classification of the variable itself
 *
 *  <b>COMPILER026:</b> The compiler abstraction shall define the <tt>VAR</tt>
 *  macro for the declaration and definition of variables.
 */
/* #define	VAR(vartype, memclass)	\
		vartype memclass */
#define	VAR(vartype, memclass)	\
	vartype

#endif	/* COMPILER_H */
