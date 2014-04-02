#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Setf.h"

void setf(Bytecode *code){
	int validOp = 0;
	int regAddrCheck = 0;
	
	validOp = operandCheckFor2Args(code);
	
	regAddrCheck = code->operand1 + FSR[BSR];	
	
	switch(validOp){
		case 1 : //Store in ACCESS (address is <0x80)
			FSR[code->operand1] = 0xFF;
			PC += 2;
			break;
		case 2 : //Store in ACCESS (address is >0x80)
			FSR[code->operand1+(0xF00)] = 0xFF;
			PC += 2;
			break;
		case 3 : //Store in BANKED
			if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F){
				Throw(ERR_INVALID_BSR_VALUE);}
			else if(regAddrCheck > 0xFFF)
				Throw(ERR_INVALID_ADDRESS);
			else{
				FSR[code->operand1+(FSR[BSR]<<8)] = 0xFF;
			}
			PC += 2;
			break;
		default: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;			
	}
	
}