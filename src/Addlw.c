#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Addlw.h"

char FSR[0x1000];

void addlw(Bytecode *code){
	if(code->operand1 < 0x00 || code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND);
	}
	else{
		FSR[WREG] += code->operand1;
	}

}