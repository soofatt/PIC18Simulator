#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include <stdio.h>

unsigned char FSR[0x1000];

void execute(Bytecode *code){
}

int operandCheckFor2Args(Bytecode *code){
	
	isValidOperand1(code);
	
	isValidOperand2(code);
	
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(code->operand2 == 0 || code->operand2 == ACCESS || code->operand2 == -1){
		if(code->operand1 < 0x80)
			return 1;
		else if(code->operand1 >= 0x80)
			return 2;
	}
	
	else if(code->operand2 == 1 || code->operand2 == BANKED)
		return 3;	

}

int operandCheckFor3Args(Bytecode *code){
	
	isValidOperand1(code);
	
	isValidOperand2(code);
	
	isValidOperand3(code);
	

	if(code->operand2 == 0 || code->operand2 == W){
		if(code->operand3 == 0 || code->operand3 == ACCESS || code->operand3 == -1){
			if(code->operand1 < 0x80)
				return 4;
			else if(code->operand1 >= 0x80)
				return 5;
		}
		else if(code->operand3 == 1 || code->operand3 == BANKED)
			return 6;
	}
	
	else if(code->operand2 == 1 || code->operand2 == F || code->operand2 == -1){
		if(code->operand3 == 0 || code->operand3 == ACCESS || code->operand3 == -1){
			if(code->operand1 < 0x80)
				return 1;
			else if(code->operand1 >= 0x80)
				return 2;
		}
		else if(code->operand3 == 1 || code->operand3 == BANKED)
			return 3;
	}
	
	else if(code->operand2 == 0 || code->operand2 == ACCESS){
		if(code->operand1 < 0x80)
			return 1;
		else if(code->operand1 >= 0x80)
			return 2;
	}
	
	else if(code->operand2 == 1 || code->operand2 == BANKED)
		return 3;	
}

void isValidOperand1(Bytecode *code){
	if(code->operand1 < 0x000 || code->operand1 > 0xFFF){
		Throw(ERR_INVALID_OPERAND);
	}
	else if(code->operand1 > 0x0FF && code->operand1 < 0xF80){
		printf("Warning : Exceeded operand1 range.\n");
		code->operand1 = (code->operand1 & 0x0FF);
	}
}

void isValidOperand2(Bytecode *code){
	if(code->operand2 != ACCESS && code->operand2 != BANKED){
		if(code->operand2 != W && code->operand2 != F){
			if(code->operand2 != 0 && code->operand2 != 1 && code->operand2 != -1)
				Throw(ERR_INVALID_OPERAND);
		}
	}
}

void isValidOperand3(Bytecode *code){
	if(code->operand3 != ACCESS && code->operand3 != BANKED){
		if(code->operand3 != W && code->operand3 != F){
			if(code->operand3 != 0 && code->operand3 != 1 && code->operand3 != -1)
				Throw(ERR_INVALID_OPERAND);
		}
	}
	
	if(code->operand2 == -1){
		if(code->operand3 != -1){
			Throw(ERR_INVALID_OPERAND);
		}
	}
	
	if(code->operand2 == ACCESS || code->operand2 == BANKED){
		if(code->operand3 != -1){
			Throw(ERR_INVALID_OPERAND);
		}
	}
	
	if(code->operand2 == W || code->operand2 == F){
		if(code->operand3 == W || code->operand3 == F){
			Throw(ERR_INVALID_OPERAND);
		}
	}
}