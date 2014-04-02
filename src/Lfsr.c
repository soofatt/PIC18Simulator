#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Lfsr.h"

void lfsr(Bytecode *code){
	int highByte, lowByte;

	if(code->operand1 < 0 || code->operand1 > 2){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(code->operand2 < 0x000 || code->operand2 > 0xFFF){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	highByte = (code->operand2>>8);
	lowByte = (code->operand2 & 0x0FF);
	
	switch(code->operand1){
		case 0	:
			FSR[FSR0H] = highByte;
			FSR[FSR0L] = lowByte;
			break;
		case 1	:
			FSR[FSR1H] = highByte;
			FSR[FSR1L] = lowByte;
			break;
		case 2	:
			FSR[FSR2H] = highByte;
			FSR[FSR2L] = lowByte;
			break;
		default	: //if not within cases, throw error
			Throw(ERR_INVALID_OPERAND);
			break;
	}
}
