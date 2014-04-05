#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Setf.h"

void setUp(){}
void tearDown(){}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_for_less_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x031, 
					 .operand2 = 0, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0x031] to 0xC2
	FSR[code.operand1] = 0xC2;
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x031]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_for_more_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x096, 
					 .operand2 = 0, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0xF96] to 0xC2
	FSR[code.operand1+(0xF00)] = 0xC2;

	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0xF96]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank_for_more_than_0x80_if_operand2_is_default(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x096, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0x296] to 0xC2
	FSR[0x296] = 0xC2;
	FSR[BSR] = 0x2;

	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x296]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_default_op2_bank_for_less_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x035, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0x035] to 0xA2
	FSR[code.operand1] = 0xA2;
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x035]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x031, 
					 .operand2 = 1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0xC31] to 0x12
	FSR[BSR] = 0xC;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x12;
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	//printf("File register: %#x\n", FSR[0xC31]);
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0xC31]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_if_operand1_is_0x250(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x250, 
					 .operand2 = ACCESS, 
					 .operand3 = -1					
					};
				
	//Should set FSR[0x050] to 0xFF instead of FSR[0x250];
	FSR[0x050] = 0x01;
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x050]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank_if_operand1_is_0x250(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x250, 
					 .operand2 = BANKED, 
					 .operand3 = -1					
					};
	//Initialize FSR[0x350] to 0x20
	FSR[BSR] = 0x3;
	FSR[0x350] = 0x20;			
	//Should set FSR[0x350] to 0xFF instead of FSR[0x250];
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x350]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank_if_operand1_is_0x085_and_operand2_is_default(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x085, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	//Initialize FSR[0x385] to 0x20
	FSR[BSR] = 0x3;
	FSR[0x385] = 0x20;			
	//Should set FSR[0x385]
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x385]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_GPR_bank_if_operand1_is_WREG_and_operand2_is_banked(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = WREG, 
					 .operand2 = BANKED, 
					 .operand3 = -1					
					};
	//Initialize FSR[0x3E8] to 0x20
	FSR[WREG] = 0x20;
	FSR[BSR] = 0x3;
	//Should set FSR[0x3E8]
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[0x3E8]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_if_operand1_is_WREG_and_operand2_is_access(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = WREG, 
					 .operand2 = ACCESS, 
					 .operand3 = -1					
					};
	//Initialize FSR[WREG] to 0x20
	FSR[WREG] = 0x20;
	//Should set FSR[WREG]
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[WREG]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_set_the_value_in_a_file_register_to_0xFF_in_ACCESS_bank_if_operand1_is_WREG_and_operand2_is_default(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = WREG, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
	//Initialize FSR[WREG] to 0x20
	FSR[WREG] = 0x20;
	//Should set FSR[WREG]
	
	Try{
		result = setf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0xFF, FSR[WREG]);
	TEST_ASSERT_EQUAL(0, result);
	
}

void test_setf_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = -1, 
					 .operand2 = 1, 
					 .operand3 = -1					
					};
	
	Try{
		result = setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS, catchError);
	}
}

void test_setf_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x30, 
					 .operand2 = -7, 
					 .operand3 = -1					
					};
	
	Try{
		result = setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_setf_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x30, 
					 .operand2 = 0, 
					 .operand3 = 3					
					};
	
	Try{
		result = setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_setf_should_throw_exception_if_invalid_BSR_value(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = SETF, .name = "setf"},
					 .operand1 = 0x30, 
					 .operand2 = 0, 
					 .operand3 = -1					
					};
	//Initialize FSR[BSR] to 0x35				
	FSR[BSR] = 0x35;
	
	Try{
		result = setf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR_VALUE, catchError);
	}
}
