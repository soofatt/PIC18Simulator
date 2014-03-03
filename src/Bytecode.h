#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

#define WREG	0xFE8
#define BSR		0xFE0

extern char FSR[];

typedef enum 	{
					NO_ERROR,
					ERR_INVALID_OPERAND
				} ExceptionError;

typedef enum 	{
					COMF,
					SETF
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
} Bytecode;

#endif	// __BYTECODE_H__
