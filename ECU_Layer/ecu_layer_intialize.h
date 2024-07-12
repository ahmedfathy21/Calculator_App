/* 
 * File:   ecu_layer_intialize.h
 * Author: Ahmed Fathy
 * Created on March 4, 2024, 6:40 PM
 */

#ifndef ECU_LAYER_INTIALIZE_H
#define	ECU_LAYER_INTIALIZE_H

/* Includes */
#include "Keypad/ecu_keypad.h"
#include "Char_LCD/ecu_char_lcd.h"

/* Data Types Declarations */
extern keypad_t keypad;
extern lcd_8bit_t lcd;

/* Function Declarations */
Std_ReturnType ecu_layer_intialize();

#endif	/* ECU_LAYER_INTIALIZE_H */

