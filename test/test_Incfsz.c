#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Incfsz.h"

void setUp(){}
void tearDown(){}

void test_incfsz_should_return_1_if_skip_for_ACCESS_bank_address_less_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x040, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x040] to 0xFF
	FSR[code.operand1] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x040]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_ACCESS_bank_address_less_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x030, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x030] to 0x0F
	FSR[code.operand1] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0x030]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_ACCESS_bank_address_more_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0D0, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFD0] to 0xFF
	FSR[code.operand1+(0xF00)] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0xFD0]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_ACCESS_bank_address_more_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0A0, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFA0] to 0x0F
	FSR[code.operand1+(0xF00)] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0xFA0]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_default_op3_bank_address_less_than_0x80(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x020, 
					 .operand2 = 1, 
					 .operand3 = -1					
					};
				
	//Initialize FSR[0x020] to 0xFF
	FSR[code.operand1] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x020]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_1_if_skip_for_GPR_bank(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x045, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x345] to 0xFF
	FSR[BSR] = 0x3;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x345]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_GPR_bank(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0C5, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x2C5] to 0x0F
	FSR[BSR] = 0x2;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0x2C5]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_ACCESS_bank_address_less_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x040, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x040] to 0xFF
	FSR[code.operand1] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_ACCESS_bank_address_less_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x030, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x030] to 0x0F
	FSR[code.operand1] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_ACCESS_bank_address_more_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0D0, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFD0] to 0xFF
	FSR[code.operand1+(0xF00)] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_ACCESS_bank_address_more_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0A0, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFA0] to 0x0F
	FSR[code.operand1+(0xF00)] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_GPR_bank_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x045, 
					 .operand2 = 0, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x545] to 0xFF
	FSR[BSR] = 0x5;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_0_if_not_skip_for_GPR_bank_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0C5, 
					 .operand2 = 0, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x4C5] to 0x0F
	FSR[BSR] = 0x4;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x0F;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(0, result);
		
}

void test_incfsz_should_return_1_if_skip_for_ACCESS_bank_if_operand1_is_0x350(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x350, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x050] to 0xFF, should increment FSR[0x50] instead of FSR[0x350]
	FSR[0x50] = 0xFF;

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x050]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_return_1_if_skip_for_GPR_bank_if_operand1_is_0x550(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x550, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x250] to 0xFF
	FSR[BSR] = 0x02;
	FSR[0x250] = 0xFF;
	//Should increment FSR[0x250] instead of FSR[0x550]

	Try{
		result = incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x250]);
	TEST_ASSERT_EQUAL(1, result);
		
}

void test_incfsz_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = -1, 
					 .operand2 = 0, 
					 .operand3 = 1					
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = 10, 
					 .operand3 = 1					
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = 0, 
					 .operand3 = -11					
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_operand2_is_F_operand3_is_W(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = F, 
					 .operand3 = W					
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_operand2_is_F_operand3_is_F(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = F, 
					 .operand3 = F					
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_operand2_is_ACCESS_operand3_is_BANKED(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = ACCESS, 
					 .operand3 = BANKED			
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_operand2_is_ACCESS_operand3_is_ACCESS(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = ACCESS, 
					 .operand3 = ACCESS			
					};

	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}
		
}

void test_incfsz_should_throw_exception_if_invalid_BSR_value(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x10, 
					 .operand2 = F, 
					 .operand3 = BANKED			
					};
	//Initialize FSR[BSR] to 0x5A	
	FSR[BSR] = 0x5A;
	
	Try{
		result = incfsz(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR_VALUE, catchError);
	}
		
}
