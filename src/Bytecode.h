#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

typedef enum 	{
					COMF,
					SETF,
					INCFSZ
				} Mnemonic;
				
typedef struct {
	Mnemonic	mnemonic;
	char *name;
} Instruction;

typedef struct {
	Instruction instruction;
	int operand1;
	int operand2;
	int operand3;
	int absoluteAddress;
} Bytecode;

#endif	// __BYTECODE_H__
