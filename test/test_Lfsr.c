#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Lfsr.h"

void setUp(){}
void tearDown(){}

void test_lfsr_should_load_0x4A2_into_LFSR0(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 0, 
					 .operand2 = 0x4A2, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
				
	//Initialize FSR[FSR0L] and FSR[FSR0H] to 0
	FSR[FSR0H] = 0x00;
	FSR[FSR0L] = 0x00;
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x04, FSR[FSR0H]);
	TEST_ASSERT_EQUAL_HEX8(0xA2, FSR[FSR0L]);
	TEST_ASSERT_EQUAL(1, result);
	
}

void test_lfsr_should_load_0xC38_into_LFSR1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 1, 
					 .operand2 = 0xC38, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize FSR[FSR1L] and FSR[FSR1H] to 0
	FSR[FSR1H] = 0x00;
	FSR[FSR1L] = 0x00;
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x0C, FSR[FSR1H]);
	TEST_ASSERT_EQUAL_HEX8(0x38, FSR[FSR1L]);
	TEST_ASSERT_EQUAL(1, result);
	
}

void test_lfsr_should_load_0x4DA_into_LFSR2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 2, 
					 .operand2 = 0x4DA, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize FSR[FSR2L] and FSR[FSR2H] to 0
	FSR[FSR2H] = 0x00;
	FSR[FSR2L] = 0x00;
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x04, FSR[FSR2H]);
	TEST_ASSERT_EQUAL_HEX8(0xDA, FSR[FSR2L]);
	TEST_ASSERT_EQUAL(1, result);
	
}

void test_lfsr_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 3, 
					 .operand2 = 0x2A1, 
					 .operand3 = -1					
					};
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}

void test_lfsr_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 1, 
					 .operand2 = 0x3F6D, 
					 .operand3 = -1					
					};
	//Initialize FSR[FSR1L] and FSR[FSR1H] to 0
	FSR[FSR1H] = 0x00;
	FSR[FSR1L] = 0x00;
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}

void test_lfsr_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = LFSR, .name = "lfsr"},
					 .operand1 = 2, 
					 .operand2 = 0x8FF, 
					 .operand3 = 2					
					};
	
	Try{
		result = lfsr(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
	
}