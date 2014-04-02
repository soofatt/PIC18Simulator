#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Addlw.h"

void addlw(Bytecode *code){
	int negFlag, operand1;
	unsigned char wreg;
	
	operand1 = code->operand1;
	wreg = FSR[WREG];

	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	if(code->operand1 < 0x00 || (code->operand1 > 0xFF && code->operand1 < 0xF80) || code->operand1 > 0xFFF){
		Throw(ERR_INVALID_OPERAND);
	}
	else{
		FSR[WREG] += code->operand1;
		negFlag = (FSR[WREG]>>7);
		
		if(carryCheck(wreg, operand1) == 1)
			FSR[STATUS] = (FSR[STATUS] | 0x01);
		
		if(digitalCarryCheck(wreg, operand1) == 1)
			FSR[STATUS] = (FSR[STATUS] | 0x02);
		
		if(FSR[WREG] == 0)
			FSR[STATUS] = (FSR[STATUS] | 0x04);
			
		if(overflowCheck(wreg, operand1) == 1)
			FSR[STATUS] = (FSR[STATUS] | 0x08);	
			
		if(negFlag == 1)
			FSR[STATUS] = (FSR[STATUS] | 0x10);	
	}
}

int overflowCheck(unsigned char wreg, int operand1){
	int carryOut_D7, carry_D6toD7;
	
	carryOut_D7 = ((wreg + operand1)>>8);
	
	wreg = (wreg & 0x7F);
	operand1 = (operand1 & 0x7F);
	
	carry_D6toD7 = ((wreg + operand1)>>7);
	
	if(carryOut_D7 == 1 && carry_D6toD7 == 0)
		return 1;
	else if(carryOut_D7 == 0 && carry_D6toD7 == 1)
		return 1;	
	else
		return 0;
	
}

int digitalCarryCheck(unsigned char wreg, int operand1){
	int carry_D3toD4;
	
	wreg = (wreg & 0x0F);
	operand1 = (operand1 & 0x0F);
	
	carry_D3toD4 = ((wreg + operand1)>>4);
	
	return carry_D3toD4;
}

int carryCheck(unsigned char wreg, int operand1){
	int carryOut_D7;
	
	carryOut_D7 = ((wreg + operand1)>>8);
	
	return carryOut_D7;
}

