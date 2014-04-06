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
#include "Setf.h"

/**
 *Set the value inside a file register to 0xFF
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	code->absoluteAddress+1
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *	ERR_INVALID_BSR_VALUE exception if encounter invalid BSR value
 *
 */
int setf(Bytecode *code){
	int validOp = 0;
	
	validOp = operandCheckFor2Args(code);

	switch(validOp){
		case 1 : //Store in ACCESS
			FSR[code->operand1] = 0xFF;
			
			return code->absoluteAddress+1;
			break;
			
		case 2 : //Store in BANKED
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F){
				Throw(ERR_INVALID_BSR_VALUE);}
			else{
				FSR[code->operand1+(FSR[BSR]<<8)] = 0xFF;
			}
			
			return code->absoluteAddress+1;
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;			
	}
	
}