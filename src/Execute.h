/**
 * Author: Soo Fatt
 * Email: soofatt93@gmail.com
 * Date: 29/3/2014
 * Project name: PIC18 simulator
 * Programme: Microelectronics with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
#ifndef	__EXECUTE_H__
#define	__EXECUTE_H__

#define WREG	0xFE8
#define BSR		0xFE0
#define STATUS	0xFD8 //X X X N OV Z DC C (Bit 7 : 0)
#define FSR0H	0xFEA
#define FSR0L	0xFE9
#define FSR1H	0xFE2
#define FSR1L	0xFE1
#define FSR2H	0xFDA
#define FSR2L	0xFD9
#define STKPTR	0xFFC
#define TOSU	0xFFF
#define TOSH	0xFFE
#define TOSL	0xFFD
#define TBLPTRU	0xFF8
#define TBLPTRH	0xFF7
#define TBLPTRL	0xFF6
#define TABLAT	0xFF5

extern unsigned char FSR[];
extern unsigned int PIC18Stack[];
unsigned extern char TABLE[];

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
					ERR_INVALID_ADDRESS,
					ERR_INVALID_STK_PTR,
					ERR_INVALID_TBL_PTR
				} ExceptionError;

void execute(Bytecode *code);
int operandCheckFor2Args(Bytecode *code);
int operandCheckFor3Args(Bytecode *code);
void isValidOperand1(Bytecode *code);
void isValidOperand2(Bytecode *code);
void isValidOperand3(Bytecode *code);
void setOperandsFor2Args(Bytecode *code);
void setOperandsFor3Args(Bytecode *code);

#endif	// __EXECUTE_H__
