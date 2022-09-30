/*
 * Lcd.h
 *
 *  Created on: Sep 2, 2022
 *      Author: abram
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
typedef enum
{
    DISPLAY_CLEAR                 = 0x01,
    HOME_RETURN                   = 0x02,
    ENTERY_MODE                   = 0x06,
    DISPLAY_ON_CURSOR_ON_BLINKING = 0x0F,
    DISPLAY_ON_CURSOR_ON          = 0x0E,
    DISPLAY_ON_CURSOR_OFF         = 0x0C,
    DISPLAY_OFF_CURSOR_OFF        = 0x08,
    DISPLAY_SHIFT_RIGHT           = 0x1C,
    DISPLAY_SHIT_LEFT             = 0x18,
    CURSOR_SHIFT_RIGHT            = 0x14,
    CURSOR_SHIFT_LEFT             = 0x10
} Lcd_ControlListType;
/********************************************/
typedef enum {
    LCD_DISPLAY_OFF,
    LCD_DISPLAY_ON
} Lcd_DisplayType;
/********************************************/
typedef enum {
    LCD_CURSOR_OFF,
    LCD_CURSOR_ON_BLINK,
    LCD_CURSOR_ON_NOT_BLINK,
} Lcd_CursorType;
/********************************************/
typedef enum {
    LCD_ONE_LINE,
    LCD_TWO_LINES
} Lcd_LineType;
/********************************************/
typedef enum {
    LCD_FONT_5X7,
    LCD_FONT_5X10
} Lcd_FontType;
/********************************************/
typedef struct 
{
    Lcd_DisplayType display_status;
    Lcd_CursorType cursor_status;
    Lcd_LineType line_status;
    Lcd_FontType font_status;
} Lcd_DisplayControlType;

void Lcd_Init(void);
void Lcd_DisplayString(u8 *str);
void Lcd_DisplayNumber(s32 number);
void Lcd_DisplayControls(Lcd_ControlListType comand);
void Lcd_DisplayControl(Lcd_DisplayControlType display);
void Lcd_SetCursorPosition(u8 row, u8 col);
void Lcd_DisplayCharacter(u8 character);
void Lcd_DisplayClear(void);
#endif /* INC_LCD_H_ */
