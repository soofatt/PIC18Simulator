#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bc.h"

int bc(Bytecode *code){
	char operand1;
	int carryFlag;

	operand1 = code->operand1;
	
	if(operand1 < -128 || operand1 > 127){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	carryFlag = (FSR[STATUS] & 0x01);
	
	if(carryFlag == 1)
		return code->operand1;
	else
		return code->absoluteAddress+1;
}