#ifndef	__ADDLW_H__
#define	__ADDLW_H__

#define WREG  0xFE8

extern char FSR[];

void addlw(Bytecode *code);

#endif	// __ADDLW_H__