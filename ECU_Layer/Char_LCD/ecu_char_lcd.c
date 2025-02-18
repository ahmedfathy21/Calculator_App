/* 
 * File:   ecu_char_lcd.c
 * Author: Ahmed Fathy
 * Created on March 4, 2024, 6:40 PM
 */

#include "ecu_char_lcd.h"

static Std_ReturnType send_8bit_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 colomn);

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        
        for(uint8 pin = 0 ; pin < 8 ; pin++){
            ret = gpio_pin_intialize(&(lcd->data_lines[pin]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        
        ret = lcd_8bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, LCD_CURSOR_HOME);
        ret = lcd_8bit_send_command(lcd, LCD_INCREMENT_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        ret = lcd_8bit_send_command(lcd, LCD_DDRAM_START);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(uint8 line_data_pin = 0 ; line_data_pin < 8 ; line_data_pin++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_data_pin]), (command >> line_data_pin) & 0x01);
        }
        ret = send_8bit_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(uint8 line_data_pin = 0 ; line_data_pin < 8 ; line_data_pin++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_data_pin]), (data >> line_data_pin) & 0x01);
        }
        ret = send_8bit_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_8bit_set_cursor(lcd, row, colomn);
        ret = lcd_8bit_send_char(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && NULL != string){
        ret = E_OK;
        do{
            lcd_8bit_send_char(lcd, *string);
        } while(*(++string));
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_8bit_set_cursor(lcd, row, colomn);
        ret = lcd_8bit_send_string(lcd, string);
    }
    return ret;
}

static Std_ReturnType send_8bit_enable_signal(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 colomn){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && row <= NUMBER_OF_ROWS && colomn <= NUMBER_OF_COLOMNS){
        colomn--; //Start with index zero
        switch(row){
            case ROW1: ret = lcd_8bit_send_command(lcd, (0x80 + colomn));  break;
            case ROW2: ret = lcd_8bit_send_command(lcd, (0xc0 + colomn));  break;
            default:                                                       break;
        }
    }
    return ret; 
}
