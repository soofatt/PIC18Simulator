#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Bc.h"

void setUp(){}
void tearDown(){}

void test_bc_should_return_1_if_branching(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BC, .name = "bc"},
					 .operand1 = 0x22, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[STATUS] to 0x01
	FSR[STATUS] = 0x01;
	
	Try{
		result = bc(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x01, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);

}

void test_bc_should_return_0_if_not_branching(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BC, .name = "bc"},
					 .operand1 = 0xA5, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[STATUS] to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = bc(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[STATUS]);
	TEST_ASSERT_EQUAL(0, result);

}

void test_bc_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BC, .name = "bc"},
					 .operand1 = 130, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = bc(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_bc_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BC, .name = "bc"},
					 .operand1 = 0xF2, 
					 .operand2 = BANKED, 
					 .operand3 = -1					
					};				
	
	Try{
		result = bc(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_bc_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = BC, .name = "bc"},
					 .operand1 = 0x56, 
					 .operand2 = -1, 
					 .operand3 = ACCESS					
					};				
	
	Try{
		result = bc(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}