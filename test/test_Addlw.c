#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Addlw.h"

void setUp(){}
void tearDown(){}

void test_addlw_should_add_a_hex_value_to_WREG(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x20, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0x00 and add 0x20 to WREG
	FSR[WREG] = 0x00;
	
	Try{
		addlw(&code);
	} Catch(catchError){
			TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
			return;
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x20, FSR[WREG]);
	
	//Initialize WREG to 0xFF and add 0x20 to WREG
	FSR[WREG] = 0xFF;

	Try{
		addlw(&code);
	} Catch(catchError){
			TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
			return;
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x1F, FSR[WREG]);
	
}

void test_addlw_should_throw_exception_if_invalid_operand1(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}

void test_addlw_should_throw_exception_if_invalid_operand2(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = WREG, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}

void test_addlw_should_throw_exception_if_invalid_operand3(){
	int catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = BANKED					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
		return;
	}
}