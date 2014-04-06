#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Goto.h"

void setUp(){}
void tearDown(){}

void test_goto__should_return_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = GOTO_, .name = "goto_"},
					 .operand1 = 0x1C2D3, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = goto_(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}

	TEST_ASSERT_EQUAL_HEX8(0x1C2D3, result);
}

void test_goto__should_throw_exception_if_invalid_operand1_given_operand1_is_negative_456(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = GOTO_, .name = "goto_"},
					 .operand1 = -456, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = goto_(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_goto__should_throw_exception_if_invalid_operand1_given_operand1_is_2000000(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = GOTO_, .name = "goto_"},
					 .operand1 = 2000000, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = goto_(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_goto__should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = GOTO_, .name = "goto_"},
					 .operand1 = 0x345, 
					 .operand2 = 6, 
					 .operand3 = -1					
					};
	
	Try{
		result = goto_(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_goto__should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = GOTO_, .name = "goto_"},
					 .operand1 = 0x0A3F2, 
					 .operand2 = -1, 
					 .operand3 = -6					
					};
	
	Try{
		result = goto_(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}


