#include <stdio.h>
#include "Bytecode.h"
#include "Comf.h"

char FSR[0x1000];

void comf(Bytecode *code){
	if(code->operand2 == 0)
		FSR[WREG] = ~(FSR[code->operand1]);
	if(code->operand2 == 1){
		if(code->operand3 == 0)
			FSR[code->operand1] = ~(FSR[code->operand1]);
		else if(code->operand3 == 1)
			FSR[code->operand1+(FSR[BSR]<<8)] = ~(FSR[code->operand1+(FSR[BSR]<<8)]);
	}
	
}