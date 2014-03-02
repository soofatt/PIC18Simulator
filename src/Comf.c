#include <stdio.h>
#include "Bytecode.h"
#include "Comf.h"

char FSR[0x1000];

void comf(Bytecode *code){
	if(code->operand2 == 0)
		FSR[WREG] = ~(FSR[code->operand1]);
	if(code->operand2 == 1)
		FSR[code->operand1] = ~(FSR[code->operand1]);

}