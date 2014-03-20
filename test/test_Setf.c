#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Setf.h"

void setUp(){}
void tearDown(){}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_for_less_than_0x80(){
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x031, 
					 .operand2 = 0, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0x031] to 0xC2
	FSR[code.operand1] = 0xC2;
	
	setf(&code);
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x031]);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_for_more_than_0x80(){
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x096, 
					 .operand2 = 0, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0xF96] to 0xC2
	FSR[code.operand1+(0xF00)] = 0xC2;

	setf(&code);

	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0xF96]);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank(){
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x031, 
					 .operand2 = 1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0xC31] to 0x12
	FSR[BSR] = 0xC;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x12;
	
	setf(&code);

	//printf("File register: %#x\n", FSR[0xC31]);
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0xC31]);
	
}

void test_setf_should_throw_exception_if_invalid_operand1(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = -1, 
					 .operand2 = 1, 
					 .operand3 = -1					
					};
	
	Try{
		setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}

void test_setf_should_throw_exception_if_invalid_operand2(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x30, 
					 .operand2 = -7, 
					 .operand3 = -1					
					};
	
	Try{
		setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}

void test_setf_should_throw_exception_if_invalid_operand3(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x30, 
					 .operand2 = 0, 
					 .operand3 = 3					
					};
	
	Try{
		setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}