#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Setf.h"

int setf(Bytecode *code){
	int validOp = 0;
	
	validOp = operandCheckFor2Args(code);

	switch(validOp){
		case 1 : //Store in ACCESS
			FSR[code->operand1] = 0xFF;
			
			return 0;
			break;
			
		case 2 : //Store in BANKED
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F){
				Throw(ERR_INVALID_BSR_VALUE);}
			else{
				FSR[code->operand1+(FSR[BSR]<<8)] = 0xFF;
			}
			
			return 0;
			break;
			
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;			
	}
	
}