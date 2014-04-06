#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "TblrdPostDec.h"

int tblrd_postdec(Bytecode *code){
	int tablePtr = 0;
	int tblptrUpper, tblptrHigh, tblptrLow;

	if(code->operand1 != -1 || code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	tblptrUpper = (FSR[TBLPTRU]<<16);
	tblptrHigh = (FSR[TBLPTRH]<<8);
	tblptrLow = FSR[TBLPTRL];
	
	tablePtr = tblptrUpper + tblptrHigh + tblptrLow;
	
	if(tablePtr < 0x00 || tablePtr > 0x200000){
		Throw(ERR_INVALID_TBL_PTR);
	}
	
	FSR[TABLAT] = TABLE[tablePtr];
	
	if(tablePtr == 0){
		tablePtr = tablePtr;
	}
	else{
		tablePtr--;
	}
	
	FSR[TBLPTRU] = ((tablePtr & 0xFF0000)>>16);
	FSR[TBLPTRH] = ((tablePtr & 0x00FF00)>>8);
	FSR[TBLPTRL] = (tablePtr & 0x0000FF);
	
	return code->absoluteAddress+1;
}