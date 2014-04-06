#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "Execute.h"
#include "TblrdPostDec.h"

void setUp(){}
void tearDown(){}

void test_tblrd_postdec_should_read_data_from_TABLE_addr_0x03A526_and_store_in_TABLAT_then_decrement_tblptr(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
	//Initialize FSR[TABLAT] to 0, FSR[TBLPTRU] to 0x03, FSR[TBLPTRH] to 0xA5,
	//FSR[TBLPTRL] to 0x26,	TABLE[0x03A526] to 0x85			
	FSR[TABLAT] = 0;
	FSR[TBLPTRU] = 0x03;
	FSR[TBLPTRH] = 0xA5;
	FSR[TBLPTRL] = 0x26;
	TABLE[0x03A526] = 0x85;
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL(1, result);
	TEST_ASSERT_EQUAL_HEX8(0x85, FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX8(0x03, FSR[TBLPTRU]);
	TEST_ASSERT_EQUAL_HEX8(0xA5, FSR[TBLPTRH]);
	TEST_ASSERT_EQUAL_HEX8(0x25, FSR[TBLPTRL]);
}

void test_tblrd_postdec_should_read_data_from_TABLE_addr_0x000000_and_store_in_TABLAT_without_decrement_if_tblptr_is_0(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
	//Initialize FSR[TABLAT] to 0, FSR[TBLPTRU] to 0x00, FSR[TBLPTRH] to 0x00,
	//FSR[TBLPTRL] to 0x00,	TABLE[0x000000] to 0x65			
	FSR[TABLAT] = 0;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0x00;
	FSR[TBLPTRL] = 0x00;
	TABLE[0x000000] = 0x65;
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_FAIL_MESSAGE("Exception thrown when it should not have.");
	}
	
	TEST_ASSERT_EQUAL(1, result);
	TEST_ASSERT_EQUAL_HEX8(0x65, FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRU]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRH]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRL]);
}

void test_tblrd_postdec_should_throw_exception_if_invalid_table_pointer(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
	//Initialize FSR[TBLPTRU] to 0x03, FSR[TBLPTRH] to 0xA5, FSR[TBLPTRL] to 0x26,
	FSR[TBLPTRU] = 0x30;
	FSR[TBLPTRH] = 0xA4;
	FSR[TBLPTRL] = 0xC3;
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_TBL_PTR, catchError);
	}

}

void test_tblrd_postdec_should_throw_exception_if_invalid_operand1(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = 0x20, 
					 .operand2 = -1, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_tblrd_postdec_should_throw_exception_if_invalid_operand2(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = -1, 
					 .operand2 = ACCESS, 
					 .operand3 = -1,
					 .absoluteAddress = 0
					};
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}

void test_tblrd_postdec_should_throw_exception_if_invalid_operand3(){
	CEXCEPTION_T catchError;
	int result;
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_POSTDEC, .name = "tblrd_postdec"},
					 .operand1 = -1, 
					 .operand2 = -1, 
					 .operand3 = BANKED,
					 .absoluteAddress = 0
					};
	
	Try{
		result = tblrd_postdec(&code);
	} Catch(catchError){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, catchError);
	}

}