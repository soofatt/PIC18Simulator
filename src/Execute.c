#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include <stdio.h>

void execute(Bytecode *code){
}

int operandCheckFor2Args(Bytecode *code){
	if(code->operand1 < 0x00 || code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND);
	}
	
	isValidOperand2(code);
	
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	else{
		if(code->operand2 == 0){
			if(code->operand1 < 0x80)
				return 1;
			else if(code->operand1 >= 0x80)
				return 2;
		}
		else if(code->operand2 == 1)
			return 3;
	}
}

void isValidOperand2(Bytecode *code){
	if(code->operand2 != ACCESS && code->operand2 != BANKED){
		if(code->operand2 != W && code->operand2 != F){
			if(code->operand2 != 0 && code->operand2 != 1)
				Throw(ERR_INVALID_OPERAND);
		}
	}
}