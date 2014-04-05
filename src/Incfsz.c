#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Incfsz.h"

int incfsz(Bytecode *code){
	int validOp = 0;
	
	validOp = operandCheckFor3Args(code);
	
	switch(validOp){
		case 1 : //Using ACCESS bank
			FSR[code->operand1]++;
			
			if(FSR[code->operand1] == 0)
				return 1;
			else
				return 0;
				
			break;
			
		case 2 : //Using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				FSR[code->operand1+(FSR[BSR]<<8)]++;

				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					return 1;
				else
					return 0;	
			}
			
			break;
			
		case 3 : //Store in WREG using ACCESS bank
			FSR[WREG] = ++FSR[code->operand1];
			
			if(FSR[code->operand1] == 0)
				return 1;
			else
				return 0;
				
			break;
			
		case 4 : //Store in WREG using BANKED bank
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
				Throw(ERR_INVALID_BSR_VALUE);
			else{
				//FSR[code->operand1+(FSR[BSR]<<8)]++;
				FSR[WREG] = ++FSR[code->operand1+(FSR[BSR]<<8)];

				if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
					return 1;
				else
					return 0;	
			}
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;
	}
}