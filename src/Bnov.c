#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bnov.h"

int bnov(Bytecode *code){
	char operand1;
	int overflowFlag;

	operand1 = code->operand1;
	
	if(operand1 < -128 || operand1 > 127){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	overflowFlag = ((FSR[STATUS] & 0x08)>>3);
	
	if(overflowFlag == 0)
		return code->operand1;
	else
		return code->absoluteAddress+1;
}
