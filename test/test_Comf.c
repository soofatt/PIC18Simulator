#include "unity.h"
#include "Bytecode.h"
#include "Comf.h"

void setUp(){}
void tearDown(){}

void test_comf_should_complement_value_in_a_file_register(){
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = COMF, .name = "comf"},
					 .operand1 = 0x055, 
					 .operand2 = 1, 
					 .operand3 = 0					
					};
				
	//Initialize FSR[0x055] to 0xA5
	FSR[code.operand1] = 0xA5;
	comf(&code);
	
	TEST_ASSERT_EQUAL_HEX8(0x5A, FSR[code.operand1]);
	
}