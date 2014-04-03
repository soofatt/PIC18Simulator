#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Comf.h"

int comf(Bytecode *code){
	int validOp = 0;
	int regAddrCheck = 0;
	unsigned char negFlag;
	
	validOp = operandCheckFor3Args(code);
	
	regAddrCheck = code->operand1 + FSR[BSR];
	
	switch(validOp){
		case 1 : //Using ACCESS bank (address is <0x80)
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
				
			return 0;
			break;
			
		case 2 : //Using ACCESS bank (address is >0x80)
			FSR[code->operand1+(0xF00)] = ~(FSR[code->operand1+(0xF00)]);
			negFlag = (FSR[code->operand1+(0xF00)]>>7);
			
			if(FSR[code->operand1+(0xF00)] == 0)
				FSR[STATUS] = (FSR[STATUS] | 0x04);
			if(negFlag == 1)
				FSR[STATUS] = (FSR[STATUS] | 0x10);
				
			return 0;
			break;
			
		case 3 : //Using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else if(regAddrCheck > 0xFFF)
				Throw(ERR_INVALID_ADDRESS);
			else{
				FSR[code->operand1+(FSR[BSR]<<8)] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
				negFlag = (FSR[code->operand1+(FSR[BSR]<<8)]>>7);
			
				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					FSR[STATUS] = (FSR[STATUS] | 0x04);
				if(negFlag == 1)
					FSR[STATUS] = (FSR[STATUS] | 0x10);

			}
			return 0;
			break;
			
		case 4 : //Store in WREG using ACCESS bank (address is <0x80)
			FSR[WREG] = ~(FSR[code->operand1]);
			negFlag = (FSR[WREG]>>7);
			
			if(FSR[WREG] == 0)
				FSR[STATUS] = (FSR[STATUS] | 0x04);
			if(negFlag == 1)
				FSR[STATUS] = (FSR[STATUS] | 0x10);
				
			return 0;
			break;
			
		case 5 : //Store in WREG using ACCESS bank (address is >0x80)
			FSR[WREG] = ~(FSR[code->operand1+(0xF00)]);
			negFlag = (FSR[WREG]>>7);
			
			if(FSR[WREG] == 0)
				FSR[STATUS] = (FSR[STATUS] | 0x04);
			if(negFlag == 1)
				FSR[STATUS] = (FSR[STATUS] | 0x10);

			return 0;
			break;
			
		case 6 : //Store in WREG using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else if(regAddrCheck > 0xFFF)
				Throw(ERR_INVALID_ADDRESS);
			else{
				FSR[WREG] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
				negFlag = (FSR[WREG]>>7);
			
				if(FSR[WREG] == 0)
					FSR[STATUS] = (FSR[STATUS] | 0x04);
				if(negFlag == 1)
					FSR[STATUS] = (FSR[STATUS] | 0x10);

			}
			return 0;
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;
	}
}