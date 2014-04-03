#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bc.h"

int bc(Bytecode *code){
	char operand1;
	int statusFlag;

	operand1 = code->operand1;
	
	if(operand1 < -128 || operand1 > 127){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	statusFlag = (FSR[STATUS] & 0x01);
	
	if(statusFlag == 1)
		return 1;
	else
		return 0;
}