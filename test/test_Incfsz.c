#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "Incfsz.h"

void setUp(){}
void tearDown(){}

void test_incfsz_should_increment_PC_by_4_if_skip_for_ACCESS_bank_address_less_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x040, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x040] to 0xFF
	FSR[code.operand1] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x040]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_ACCESS_bank_address_less_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x030, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x030] to 0x0F
	FSR[code.operand1] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0x030]);
	TEST_ASSERT_EQUAL(2, PC);
		
}

void test_incfsz_should_increment_PC_by_4_if_skip_for_ACCESS_bank_address_more_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0D0, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFD0] to 0xFF
	FSR[code.operand1+(0xF00)] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0xFD0]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_ACCESS_bank_address_more_than_0x80(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0A0, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFA0] to 0x0F
	FSR[code.operand1+(0xF00)] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0xFA0]);
	TEST_ASSERT_EQUAL(2, PC);
		
}

void test_incfsz_should_increment_PC_by_4_if_skip_for_GPR_bank(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x045, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x345] to 0xFF
	FSR[BSR] = 0x3;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[0x345]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_GPR_bank(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0C5, 
					 .operand2 = 1, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x2C5] to 0x0F
	FSR[BSR] = 0x2;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[0x2C5]);
	TEST_ASSERT_EQUAL(2, PC);
		
}

void test_incfsz_should_increment_PC_by_4_if_skip_for_ACCESS_bank_address_less_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x040, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x040] to 0xFF
	FSR[code.operand1] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_ACCESS_bank_address_less_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x030, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x030] to 0x0F
	FSR[code.operand1] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(2, PC);
		
}

void test_incfsz_should_increment_PC_by_4_if_skip_for_ACCESS_bank_address_more_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0D0, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFD0] to 0xFF
	FSR[code.operand1+(0xF00)] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_ACCESS_bank_address_more_than_0x80_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0A0, 
					 .operand2 = 0, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0xFA0] to 0x0F
	FSR[code.operand1+(0xF00)] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(2, PC);
		
}

void test_incfsz_should_increment_PC_by_4_if_skip_for_GPR_bank_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x045, 
					 .operand2 = 0, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x545] to 0xFF
	FSR[BSR] = 0x5;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0xFF;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[WREG]);
	TEST_ASSERT_EQUAL(4, PC);
		
}

void test_incfsz_should_increment_PC_by_2_if_not_skip_for_GPR_bank_and_store_in_WREG(){
	CEXCEPTION_T catchError;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = INCFSZ, .name = "incfsz"},
					 .operand1 = 0x0C5, 
					 .operand2 = 0, 
					 .operand3 = 1					
					};
				
	//Initialize FSR[0x4C5] to 0x0F
	FSR[BSR] = 0x4;
	FSR[code.operand1+(FSR[BSR]<<8)] = 0x0F;
	//Initialize PC to 0
	PC = 0;

	Try{
		incfsz(&code);
	}Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	};

	
	TEST_ASSERT_EQUAL_HEX8(0x10, FSR[WREG]);
	TEST_ASSERT_EQUAL(2, PC);
		
}