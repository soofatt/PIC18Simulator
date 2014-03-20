#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

typedef enum 	{
					ACCESS = -5,
					BANKED,
					FILEREG,
					WREG
				} Operand;

typedef enum 	{
					NO_ERROR,
					ERR_INVALID_OPERAND
				} ExceptionError;

typedef enum 	{
					ADDLW
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
