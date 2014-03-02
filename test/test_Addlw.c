#include "unity.h"
#include "Bytecode.h"
#include "Addlw.h"

void setUp(){}
void tearDown(){}

void test_addlw_should_add_a_hex_value_to_WREG(){
	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = ADDLW, .name = "addlw"},
					 .operand1 = 0x20, 
					 .operand2 = -1, 
					 .operand3 = -1					
					};
				
	//Initialize WREG to 0 and add 0x20 to WREG
	FSR[WREG] = 0x00;
	addlw(&code);
	
	TEST_ASSERT_EQUAL_HEX8(0x20, FSR[WREG]);
	
	//Initialize WREG to FF and add 0x20 to WREG
	FSR[WREG] = 0xFF;

	addlw(&code);
	
	TEST_ASSERT_EQUAL_HEX8(0x1F, FSR[WREG]);
	
}