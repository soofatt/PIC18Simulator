#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Addlw.h"

void setUp(){}
void tearDown(){}

void test_addlw_should_add_a_hex_value_to_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x20, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
				
	//Initialize WREG to 0x00 and add 0x20 to WREG
	FSR[WREG] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x20, FSR[WREG]);
	TEST_ASSERT_EQUAL(1, result);
	
	//Initialize WREG to 0xFF and add 0x20 to WREG
	FSR[WREG] = 0xFF;
	
	result = 0;

	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x1F, FSR[WREG]);
	TEST_ASSERT_EQUAL(1, result);
	
}

void test_addlw_should_set_carry_flag(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0xC2, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x40 and add 0xC2 to WREG
	FSR[WREG] = 0x40;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x02, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x01, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);
}

void test_addlw_should_set_digital_carry_flag(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x08, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x08 and add 0x08 to WREG
	FSR[WREG] = 0x08;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x02, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);
}

void test_addlw_should_set_zero_flag(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x00, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x00 and add 0x00 to WREG
	FSR[WREG] = 0x00;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x04, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);
}

void test_addlw_should_set_overflow_flag(){
	CEXCEPTION_T catchError;
	int result, result2;
	//Test fixture 1
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x40, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x60 and add 0x40 to WREG
	FSR[WREG] = 0x60;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA0, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x18, FSR[STATUS]); // 0x18 = 0001 1000, negative flag is also set
	TEST_ASSERT_EQUAL(1, result);
	
	//Test fixture 2
	Bytecode code2 = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x84, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x80 and add 0x84 to WREG
	FSR[WREG] = 0x80;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result2 = addlw(&code2);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x04, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x09, FSR[STATUS]); // 0x09 = 0000 1001, carry flag is also set
	TEST_ASSERT_EQUAL(1, result2);
}

void test_addlw_should_set_negative_flag(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x62, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x80 and add 0x62 to WREG
	FSR[WREG] = 0x80;
	//Initialize STATUS to 0x00
	FSR[STATUS] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xE2, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);
}

void test_addlw_should_clear_all_status_flag(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x01, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0					
					};
				
	//Initialize WREG to 0x00 and add 0x01 to WREG
	FSR[WREG] = 0x00;
	//Initialize STATUS to 0x04
	FSR[STATUS] = 0x1F;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x01, FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[STATUS]);
	TEST_ASSERT_EQUAL(1, result);
}

void test_addlw_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_addlw_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = WREG, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_addlw_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = BANKED					
					};
				
	//Initialize WREG to 0
	FSR[WREG] = 0x00;
	
	Try{
		result = addlw(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}