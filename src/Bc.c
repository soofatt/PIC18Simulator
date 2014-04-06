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
#include "Bc.h"

/**
 *Branch to given address if carry flag is set
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
int bc(Bytecode *code){
	char operand1;
	int carryFlag;

	operand1 = code->operand1;
	
	if(operand1 < -128 || operand1 > 127){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	carryFlag = (FSR[STATUS] & 0x01);
	
	if(carryFlag == 1)
		return code->operand1;
	else
		return code->absoluteAddress+1;
}