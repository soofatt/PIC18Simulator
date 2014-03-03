#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Setf.h"

char FSR[0x1000];

void setf(Bytecode *code){
	if(code->operand1 < 0x00 || code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND);
	}
	else{
		if(code->operand2 == 0)
			FSR[code->operand1] = 0xFF;
		else if(code->operand2 == 1)
			FSR[code->operand1+(FSR[BSR]<<8)] = 0xFF;
	}
	
}