/* 
 * File:   Calculator_App.h
 * Author: Ahmed Fathy
 * Created on July 12, 2024, 10:16 PM
 */

#ifndef CALCULATOR_APP_H
#define	CALCULATOR_APP_H
/* Section: Includes */
#include"../ECU_Layer/ecu_layer_intialize.h"

/* Macro Definitions */
#define DEBOUNE_TIME    200

/* Function Declarations */
void application_intialize();
uint8 keypad_read_value();
void calculate_display_result(uint8* operation, uint8 len);
uint8 isInputValid(uint8* operation, uint8 len);
uint8 get_operation_after_mult_div(uint8* operarion, uint8 len);
void get_two_operands_result(uint8* num1_text, uint8* num2_text, uint8 op, uint8* num1_len);

#endif	/* CALCULATOR_H */

