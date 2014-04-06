/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Goto.h"

/**
 *Go to address signified by operand1
 *
 *Input:
 *	code :	The bytecode
 *
 *Return:
 *	code->operand1
 *
 *Throw:
 *	ERR_INVALID_OPERAND exception if encounter invalid operand
 *
 */
int goto_(Bytecode *code){

	if(code->operand1 < 0 || code->operand1 > 1048575){
		Throw(ERR_INVALID_OPERAND);
	}	
	if(code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND);
	}
	
	return code->operand1;
}
