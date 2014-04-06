/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bnov.h"

/**
 *Branch to given address if overflow flag is not set
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	code->absoluteAddress+1 if not branching
 *	code->operand1 if branching
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *
 */
int bnov(Bytecode *code){
	char operand1;
	int overflowFlag;

	operand1 = code->operand1;
	
	if(operand1 < -128 || operand1 > 127){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	overflowFlag = ((FSR[STATUS] & 0x08)>>3);
	
	if(overflowFlag == 0)
		return code->operand1;
	else
		return code->absoluteAddress+1;
}
