#ifndef	__EXECUTE_H__
#define	__EXECUTE_H__

#define WREG	0xFE8
#define BSR		0xFE0
#define STATUS	0xFD8 //X X X N OV Z DC C (Bit 7 : 0)

extern unsigned char FSR[];
extern int PC;

typedef enum 	{
					ACCESS = -5,
					BANKED,
					F,
					W
				} Operand;

typedef enum 	{
					ERR_NO_ERROR,
					ERR_INVALID_OPERAND,
					ERR_INVALID_BSR_VALUE,
					ERR_INVALID_ADDRESS
				} ExceptionError;

void execute(Bytecode *code);
int operandCheckFor2Args(Bytecode *code);
int operandCheckFor3Args(Bytecode *code);
void isValidOperand2(Bytecode *code);
void isValidOperand3(Bytecode *code);

#endif	// __EXECUTE_H__