#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Goto.h"

int goto_(Bytecode *code){
	int operand1;

	operand1 = code->operand1;

	if(operand1 < 0 || operand1 > 1048575){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	return 1;
}
