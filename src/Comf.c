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
#include "Comf.h"

/**
 *Complement the value inside a file register
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
int comf(Bytecode *code){
	int validOp = 0;
	unsigned char negFlag;
	
	validOp = operandCheckFor3Args(code);
	
	switch(validOp){
		case 1 : //Using ACCESS bank 
			FSR[code->operand1] = ~(FSR[code->operand1]);
			negFlag = (FSR[code->operand1]>>7);
			
			if(FSR[code->operand1] == 0)
				FSR[STATUS] = (FSR[STATUS] | 0x04);
			else
				FSR[STATUS] = (FSR[STATUS] & 0xFB);	
			if(negFlag == 1)
				FSR[STATUS] = (FSR[STATUS] | 0x10);
			else
				FSR[STATUS] = (FSR[STATUS] & 0xEF);	
				
			return code->absoluteAddress+1;
			break;
			
		case 2 : //Using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				FSR[code->operand1+(FSR[BSR]<<8)] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
				negFlag = (FSR[code->operand1+(FSR[BSR]<<8)]>>7);
			
				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					FSR[STATUS] = (FSR[STATUS] | 0x04);
				else
					FSR[STATUS] = (FSR[STATUS] & 0xFB);	
				if(negFlag == 1)
					FSR[STATUS] = (FSR[STATUS] | 0x10);
				else
					FSR[STATUS] = (FSR[STATUS] & 0xEF);	

			}
			return code->absoluteAddress+1;
			break;
			
		case 3 : //Store in WREG using ACCESS bank
			FSR[WREG] = ~(FSR[code->operand1]);
			negFlag = (FSR[WREG]>>7);
			
			if(FSR[WREG] == 0)
				FSR[STATUS] = (FSR[STATUS] | 0x04);
			else
				FSR[STATUS] = (FSR[STATUS] & 0xFB);	
			if(negFlag == 1)
				FSR[STATUS] = (FSR[STATUS] | 0x10);
			else
				FSR[STATUS] = (FSR[STATUS] & 0xEF);	
				
			return code->absoluteAddress+1;
			break;

		case 4 : //Store in WREG using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				FSR[WREG] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
				negFlag = (FSR[WREG]>>7);
			
				if(FSR[WREG] == 0)
					FSR[STATUS] = (FSR[STATUS] | 0x04);
				else
					FSR[STATUS] = (FSR[STATUS] & 0xFB);	
				if(negFlag == 1)
					FSR[STATUS] = (FSR[STATUS] | 0x10);
				else
					FSR[STATUS] = (FSR[STATUS] & 0xEF);	

			}
			return code->absoluteAddress+1;
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;
	}
}