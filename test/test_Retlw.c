#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Retlw.h"

void setUp(){}
void tearDown(){}

void test_retlw_should_return_address_in_stack_and_add_operand1_to_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x23, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	//Initialize WREG to 0, STKPTR to 10, address in stack to 0x01B2C3
	FSR[WREG] = 0;
	FSR[STKPTR] = 10;
	PIC18Stack[FSR[STKPTR]] = 0x01B2C3;
	PIC18Stack[FSR[STKPTR]-1] = 0x02C3D9;
	FSR[TOSU] = ((PIC18Stack[FSR[STKPTR]] & 0xFF0000)>>16);
	FSR[TOSH] = ((PIC18Stack[FSR[STKPTR]] & 0x00FF00)>>8);
	FSR[TOSL] = ((PIC18Stack[FSR[STKPTR]] & 0x0000FF));
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}

	TEST_ASSERT_EQUAL_HEX8(0x01B2C3, result);
	TEST_ASSERT_EQUAL_HEX8(0x23, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x02, FSR[TOSU]); //New TOS values
	TEST_ASSERT_EQUAL_HEX8(0xC3, FSR[TOSH]); //
	TEST_ASSERT_EQUAL_HEX8(0xD9, FSR[TOSL]); //
	TEST_ASSERT_EQUAL(9, FSR[STKPTR]);
}

void test_retlw_should_return_address_in_stack_and_add_operand1_to_WREG_clear_TOS_if_stkptr_is_1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x35, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	//Initialize WREG to 0, STKPTR to 1, address in stack to 0x02D3E4
	FSR[WREG] = 0;
	FSR[STKPTR] = 1;
	PIC18Stack[FSR[STKPTR]] = 0x02D3E4;
	FSR[TOSU] = ((PIC18Stack[FSR[STKPTR]] & 0xFF0000)>>16);
	FSR[TOSH] = ((PIC18Stack[FSR[STKPTR]] & 0x00FF00)>>8);
	FSR[TOSL] = ((PIC18Stack[FSR[STKPTR]] & 0x0000FF));
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}

	TEST_ASSERT_EQUAL_HEX8(0x02D3E4, result);
	TEST_ASSERT_EQUAL_HEX8(0x35, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TOSU]); //New TOS values
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TOSH]); //
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TOSL]); //
	TEST_ASSERT_EQUAL_HEX8(0x00, PIC18Stack[FSR[STKPTR]]);
	TEST_ASSERT_EQUAL(1, FSR[STKPTR]);
}

void test_retlw_should_throw_error_if_invalid_stack_pointer(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x35, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	//Initialize stack pointer to -1
	FSR[STKPTR] = -1;
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_STK_PTR, catchError);
	}

}

void test_retlw_should_throw_error_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x435, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_retlw_should_throw_error_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x05, 
					 .operand2 = 3, 
					 .operand3 = -1					
					};
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_retlw_should_throw_error_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = RETLW, .name = "retlw"},
					 .operand1 = 0x25, 
					 .operand2 = -1, 
					 .operand3 = -5					
					};
	
	Try{
		result = retlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}
