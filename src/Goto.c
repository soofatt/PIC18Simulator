#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Goto.h"

int goto_(Bytecode *code){

	if(code->operand1 < 0 || code->operand1 > 1048575){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	return code->operand1;
}
