/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include <stdio.h>

unsigned char FSR[0x1000];
unsigned int PIC18Stack[32];
unsigned char TABLE[0x200000];

void execute(Bytecode *code){
}

/**
 *Check the operands for bytecodes that can only take in 2 operands
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	1 if code is using ACCESS bank
 *	2 if code is using GPR bank
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *
 */
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

/**
 *Check the operands for bytecodes that can only take in 3 operands
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	1 if code is using ACCESS bank
 *	2 if code is using GPR bank
 *	3 if save in WREG and code is using ACCESS bank
 *	4 if save in WREG and code is using GPR bank
 *
 *Throw:
 *	
 *
 */
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

/**
 *Check whether operand1 is a valid operand
 *
 *Input:
 *	code :	The bytecode
 *
 *Throw:
 *	ERR_INVALID_ADDRESS exception if given address is out of range
 *
 */
void isValidOperand1(Bytecode *code){
	if(code->operand1 < 0x000 || code->operand1 > 0xFFF){
		Throw(ERR_INVALID_ADDRESS);
	}
	else if(code->operand1 > 0x0FF && code->operand1 < 0xF80){
		printf("Warning : Exceeded operand1 range(0x00 - 0xFF).\n");
		code->operand1 = (code->operand1 & 0x0FF);
	}
}

/**
 *Check whether operand2 is a valid operand
 *
 *Input:
 *	code :	The bytecode
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *
 */
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

/**
 *Check whether operand3 is a valid operand
 *
 *Input:
 *	code :	The bytecode
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *
 */
void isValidOperand3(Bytecode *code){
	if(code->operand3 != ACCESS && code->operand3 != BANKED){
		if(code->operand3 != 0 && code->operand3 != 1 && code->operand3 != -1)
			Throw(ERR_INVALID_OPERAND);
	}
}

/**
 *To set the operand2 for instructions that can take in 2 operands
 *
 *Input:
 *	code :	The bytecode
 *
 *Throw:
 *
 */
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

/**
 *To set the operand2 and operand3 for instructions that can take in 3 operands
 *
 *Input:
 *	code :	The bytecode
 *
 *Throw:
 *
 */
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