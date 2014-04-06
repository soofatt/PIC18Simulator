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
#include "Incfsz.h"

/**
 *Increment the value inside a file register by 1 and skip the next instruction
 *if zero flag is set
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	code->absoluteAddress+1 if no skip
 *	code->absoluteAddress+2 if skip
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *	ERR_INVALID_BSR_VALUE exception if encounter invalid BSR value
 *
 */
int incfsz(Bytecode *code){
	int validOp = 0;
	
	validOp = operandCheckFor3Args(code);
	
	switch(validOp){
		case 1 : //Using ACCESS bank
			FSR[code->operand1]++;
			
			if(FSR[code->operand1] == 0)
				return code->absoluteAddress+2;
			else
				return code->absoluteAddress+1;
				
			break;
			
		case 2 : //Using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				FSR[code->operand1+(FSR[BSR]<<8)]++;

				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					return code->absoluteAddress+2;
				else
					return code->absoluteAddress+1;	
			}
			
			break;
			
		case 3 : //Store in WREG using ACCESS bank
			FSR[WREG] = ++FSR[code->operand1];
			
			if(FSR[code->operand1] == 0)
				return code->absoluteAddress+2;
			else
				return code->absoluteAddress+1;
				
			break;
			
		case 4 : //Store in WREG using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				//FSR[code->operand1+(FSR[BSR]<<8)]++;
				FSR[WREG] = ++FSR[code->operand1+(FSR[BSR]<<8)];

				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					return code->absoluteAddress+2;
				else
					return code->absoluteAddress+1;	
			}
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;
	}
}