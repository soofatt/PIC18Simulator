#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Comf.h"

char FSR[0x1000];

void comf(Bytecode *code){
	if(code->operand1 < 0x00 || code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND);
	}
	if(code->operand2 < -5 || code->operand2 > 1){
		Throw(ERR_INVALID_OPERAND);
	}
	if(code->operand3 < -5 || code->operand3 > 1){
		Throw(ERR_INVALID_OPERAND);
	}
	else{
		if(code->operand2 == 0){
			if(code->operand3 == 0){
				if(code->operand1 < 0x80)
					FSR[WREG] = ~(FSR[code->operand1]);
				if(code->operand1 >= 0x80)
					FSR[WREG] = ~(FSR[code->operand1+(0xF00)]);
			}
			else if(code->operand3 == 1)
				FSR[WREG] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
		}
		else if(code->operand2 == 1){
			if(code->operand3 == 0){
				if(code->operand1 < 0x80)
					FSR[code->operand1] = ~(FSR[code->operand1]);
				if(code->operand1 >= 0x80)
					FSR[code->operand1+(0xF00)] = ~(FSR[code->operand1+(0xF00)]);
			}
			else if(code->operand3 == 1)
				FSR[code->operand1+(FSR[BSR]<<8)] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
		}
	}
	
}