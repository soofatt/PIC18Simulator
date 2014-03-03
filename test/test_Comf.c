#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Comf.h"

void setUp(){}
void tearDown(){}

void test_comf_should_complement_value_in_a_file_register_in_ACCESS_bank(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x055, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x055] to 0xA5
	FSR[code.operand1] = 0xA5;
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x5A, FSR[code.operand1]);
	
}

void test_comf_should_complement_value_in_a_file_register_in_GPR_bank(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x035, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0xA35] to 0xF0
	FSR[BSR] = 0xA;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0xF0;
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
	
	//printf("File register: %#x\n", code.operand1+(FSR[BSR]<<8));
	
	TEST_ASSERT_EQUAL_HEX8(0x0F, FSR[code.operand1+(FSR[BSR]<<8)]);
	
}

void test_comf_should_complement_value_in_a_file_register_and_store_in_WREG(){
	int catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0x08A, 
							.operand2 =	0, 
							.operand3 = 0					
					};
				
	//Initialize FSR[0x08A] to 0xFF
	FSR[code.operand1] = 0xFF;
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);

}

void test_comf_should_throw_exception_if_invalid_operand(){
	int catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = -1, 
							.operand2 =	1, 
							.operand3 = 0					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);

	
}