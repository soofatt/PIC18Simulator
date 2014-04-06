/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

typedef enum 	{
					COMF,
					SETF,
					INCFSZ,
					ADDLW,
					LFSR,
					BC,
					BNOV,
					GOTO_,
					RETLW,
					TBLRD_POSTDEC
				} Mnemonic;
				
typedef struct {
	Mnemonic	mnemonic;
	char *name;
} Instruction;

typedef struct {
	Instruction instruction;
	int operand1;
	int operand2;
	int operand3;
	int absoluteAddress;
} Bytecode;

#endif	// __BYTECODE_H__
