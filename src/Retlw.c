#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Retlw.h"

int retlw(Bytecode *code){
	int returnAddr;
	int tosUpper = 0, tosHigh = 0, tosLow = 0;
	
	if(code->operand1 < 0x00 || code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	if(FSR[STKPTR] < 0 || FSR[STKPTR] > 31){
		Throw(ERR_INVALID_STK_PTR);
	}
	
	if(FSR[STKPTR] == 1){
		tosUpper = (FSR[TOSU]<<16);
		tosHigh = (FSR[TOSH]<<8);
		tosLow = FSR[TOSL];
		
		PIC18Stack[FSR[STKPTR]] = 0;
		
		FSR[TOSU] = 0;
		FSR[TOSH] = 0;
		FSR[TOSL] = 0;
	}
	
	else{
		tosUpper = (FSR[TOSU]<<16);
		tosHigh = (FSR[TOSH]<<8);
		tosLow = FSR[TOSL];
		
		PIC18Stack[FSR[STKPTR]] = 0;
		
		FSR[STKPTR]--;

		FSR[TOSU] = ((PIC18Stack[FSR[STKPTR]] & 0xFF0000)>>16);
		FSR[TOSH] = ((PIC18Stack[FSR[STKPTR]] & 0x00FF00)>>8);
		FSR[TOSL] = ((PIC18Stack[FSR[STKPTR]] & 0x0000FF));
	}
	
	returnAddr = tosUpper + tosHigh + tosLow;
	FSR[WREG] += code->operand1;
	
	return returnAddr;
}