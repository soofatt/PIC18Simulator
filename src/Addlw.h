/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#ifndef	__ADDLW_H__
#define	__ADDLW_H__

int addlw(Bytecode *code);
int overflowCheck(unsigned char wreg, int operand1);
int digitalCarryCheck(unsigned char wreg, int operand1);
int carryCheck(unsigned char wreg, int operand1);

#endif	// __ADDLW_H__