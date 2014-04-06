#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bnov.h"

void setUp(){}
void tearDown(){}

void test_bnov_should_return_operand1_if_branching(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BNOV, .name = "bnov"},
					 .operand1 = 0xC3, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
				
	//Initialize FSR[STATUS] to 0x10
	FSR[STATUS] = 0x10;
	
	Try{
		result = bnov(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0xC3, result);
}

void test_bnov_should_return_absoluteaddress_plus_1_if_not_branching(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BNOV, .name = "bnov"},
					 .operand1 = 0x35, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 7
					};
				
	//Initialize FSR[STATUS] to 0x18
	FSR[STATUS] = 0x18;
	
	Try{
		result = bnov(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x18, FSR[STATUS]);
	TEST_ASSERT_EQUAL(8, result);
}

void test_bnov_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BNOV, .name = "bnov"},
					 .operand1 = 154, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = bnov(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}

void test_bnov_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BNOV, .name = "bnov"},
					 .operand1 = 0xD1, 
					 .operand2 = 3, 
					 .operand3 = -1					
					};
	
	Try{
		result = bnov(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}

void test_bnov_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BNOV, .name = "bnov"},
					 .operand1 = 0x13, 
					 .operand2 = -1, 
					 .operand3 = -8					
					};
	
	Try{
		result = bnov(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}