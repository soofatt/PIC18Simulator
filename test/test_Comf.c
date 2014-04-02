#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Comf.h"

void setUp(){}
void tearDown(){}

void test_comf_should_complement_value_in_a_file_register_in_ACCESS_bank_if_less_than_0x80(){
	CEXCEPTION_T catchError;
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
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x5A, FSR[0x055]);
	
}

void test_comf_should_complement_value_in_a_file_register_in_ACCESS_bank_if_more_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x0D3, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFD3] to 0xFA
	FSR[code.operand1+(0xF00)] = 0xFA;

	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0x05, FSR[0xFD3]);
	
}

void test_comf_should_complement_value_in_a_file_register_in_GPR_bank(){
	CEXCEPTION_T catchError;
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
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	//printf("File register: %#x\n", code.operand1+(FSR[BSR]<<8));
	
	TEST_ASSERT_EQUAL_HEX8(0x0F, FSR[0xA35]);
	
}

void test_comf_should_complement_value_in_a_file_register_in_ACCESS_bank_and_store_in_WREG_if_less_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0x023, 
							.operand2 =	0, 
							.operand3 = 0					
					};
				
	//Initialize FSR[0x023] to 0xFF
	FSR[code.operand1] = 0xFF;
	
	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);

}

void test_comf_should_complement_value_in_a_file_register_in_ACCESS_bank_and_store_in_WREG_if_more_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0x0AC, 
							.operand2 =	0, 
							.operand3 = 0					
					};
				
	//Initialize FSR[0xFAC] to 0x88
	FSR[code.operand1+(0xF00)] = 0x88;
	
	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0x77, FSR[WREG]);

}

void test_comf_should_complement_value_in_a_file_register_in_GPR_bank_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0x04B, 
							.operand2 =	0, 
							.operand3 = 1					
					};
				
	//Initialize FSR[0x24B] to 0x63
	FSR[BSR] = 0x2;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x63;
	
	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};
	
	TEST_ASSERT_EQUAL_HEX8(0x9C, FSR[WREG]);

}

void test_comf_should_set_zero_flag_if_result_is_zero(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x025, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x025] to 0xFF
	FSR[code.operand1] = 0xFF;
	//Initialize FSR[STATUS] to 0x02
	FSR[STATUS] = 0x02;

	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x025]);
	TEST_ASSERT_EQUAL_HEX8(0x06, FSR[STATUS]);
	
}

void test_comf_should_set_negative_flag_if_result_is_negative(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x010, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x010] to 0x4A
	FSR[code.operand1] = 0x4A;
	//Initialize FSR[STATUS] to 0x02
	FSR[STATUS] = 0x02;

	Try{
		comf(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0xB5, FSR[0x010]);
	TEST_ASSERT_EQUAL_HEX8(0x12, FSR[STATUS]);
	
}

void test_comf_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
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
	}
}

void test_comf_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = -1, 
							.operand2 =	-8, 
							.operand3 = 0					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = -1, 
							.operand2 =	1, 
							.operand3 = 5					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_operand2_is_W_operand3_is_W(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0xFF, 
							.operand2 =	W, 
							.operand3 = W					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_operand2_is_F_operand3_is_W(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0xFF, 
							.operand2 =	F, 
							.operand3 = W					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_operand2_is_BANKED_operand3_is_BANKED(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0xFF, 
							.operand2 = BANKED, 
							.operand3 = BANKED					
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_operand2_is_BANKED_operand3_is_ACCESS(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0xFF, 
							.operand2 = BANKED, 
							.operand3 = ACCESS				
					};			
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
}

void test_comf_should_throw_exception_if_invalid_BSR_value(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = 0x58, 
							.operand2 = 1, 
							.operand3 = BANKED				
					};	
	//Initialize FSR[BSR] to 0x3A					
	FSR[BSR] = 0x3A;
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR_VALUE, catchError);
	}
}

void test_comf_should_throw_exception_if_invalid_address(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {{.mnemonic = COMF, .name = "comf"},
							.operand1 = WREG, 
							.operand2 = 1, 
							.operand3 = BANKED				
					};	
	//Initialize FSR[BSR] to 0xA					
	FSR[BSR] = 0xA;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x11;
	
	Try{
		comf(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS, catchError);
	}
}