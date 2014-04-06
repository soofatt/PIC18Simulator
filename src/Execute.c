#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include <stdio.h>

unsigned char FSR[0x1000];
unsigned int PIC18Stack[32];

void execute(Bytecode *code){
}

int operandCheckFor2Args(Bytecode *code){
	
	isValidOperand1(code);
	
	isValidOperand2(code);
	
	setOperandsFor2Args(code);
	
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(code->operand2 == 0 || code->operand2 == ACCESS || code->operand2 == -1){
		return 1;
	}
	
	else if(code->operand2 == 1 || code->operand2 == BANKED)
		return 2;	
		
	else
		Throw(ERR_INVALID_OPERAND);

}

int operandCheckFor3Args(Bytecode *code){

	isValidOperand1(code);
	
	isValidOperand2(code);
	
	isValidOperand3(code);
	
	setOperandsFor3Args(code);

	if(code->operand2 == 0 || code->operand2 == W){
		if(code->operand3 == 0 || code->operand3 == ACCESS || code->operand3 == -1){
			return 3;
		}
		else if(code->operand3 == 1 || code->operand3 == BANKED)
			return 4;
	}
	
	else if(code->operand2 == 1 || code->operand2 == F || code->operand2 == -1){
		if(code->operand3 == 0 || code->operand3 == ACCESS || code->operand3 == -1){
			return 1;
		}
		else if(code->operand3 == 1 || code->operand3 == BANKED)
			return 2;
	}
	
	else if(code->operand2 == ACCESS){
		return 1;
	}
	
	else if(code->operand2 == BANKED)
		return 2;	
}

void isValidOperand1(Bytecode *code){
	if(code->operand1 < 0x000 || code->operand1 > 0xFFF){
		Throw(ERR_INVALID_ADDRESS);
	}
	else if(code->operand1 > 0x0FF && code->operand1 < 0xF80){
		printf("Warning : Exceeded operand1 range(0x00 - 0xFF).\n");
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
	
	if(code->operand2 == ACCESS || code->operand2 == BANKED){
		if(code->operand3 != -1)
			Throw(ERR_INVALID_OPERAND);
	}
}

void isValidOperand3(Bytecode *code){
	if(code->operand3 != ACCESS && code->operand3 != BANKED){
		if(code->operand3 != 0 && code->operand3 != 1 && code->operand3 != -1)
			Throw(ERR_INVALID_OPERAND);
	}
}

void setOperandsFor2Args(Bytecode *code){
	if(code->operand2 == 0)
		code->operand2 = ACCESS;
		
	if(code->operand2 == 1)
		code->operand2 = BANKED;

	if(code->operand1 >= 0xF80 && code->operand1 < 0xFFF){
		if(code->operand2 == BANKED)
			code->operand1 = (code->operand1 & 0x0FF);
	}
	else if(code->operand1 >= 0x80 && code->operand1 < 0xFF){
		if(code->operand2 == ACCESS)
			code->operand1 = code->operand1+(0xF00);
		if(code->operand2 == -1)
			code->operand2 = BANKED;
	}	
}

void setOperandsFor3Args(Bytecode *code){
	if(code->operand2 == 0)
		code->operand2 = W;
		
	if(code->operand2 == 1)
		code->operand2 = F;
		
	if(code->operand3 == 0)
		code->operand3 = ACCESS;
		
	if(code->operand3 == 1)
		code->operand3 = BANKED;

	if(code->operand1 >= 0xF80 && code->operand1 < 0xFFF){
		if(code->operand3 == BANKED || code->operand2 == BANKED)
			code->operand1 = (code->operand1 & 0x0FF);
	}
	else if(code->operand1 >= 0x80 && code->operand1 < 0xFF){
		if(code->operand3 == -1)
			code->operand3 = BANKED;
		if(code->operand3 == ACCESS || code->operand2 == ACCESS)
			code->operand1 = code->operand1+(0xF00);
	}	
}