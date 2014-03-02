#include <stdio.h>
#include "Bytecode.h"
#include "Addlw.h"

char FSR[0x1000];

void addlw(Bytecode *code){
	FSR[WREG] += code->operand1;

}