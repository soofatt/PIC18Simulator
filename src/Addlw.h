#ifndef	__ADDLW_H__
#define	__ADDLW_H__

void addlw(Bytecode *code);
int overflowCheck(unsigned char wreg, int operand1);
int digitalCarryCheck(unsigned char wreg, int operand1);
int carryCheck(unsigned char wreg, int operand1);

#endif	// __ADDLW_H__