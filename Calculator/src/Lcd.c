/*
 * Lcd.c
 *
 *  Created on: Sep 2, 2022
 *      Author: abram
 */
#include "std_types.h"
#include "Macros.h"
#include "Dio.h"
#include "Lcd_cfg.h"
#include "Lcd.h"
#include "cpu_freq.h"

static void Lcd_InitPins(void);
static void Lcd_SendCommand(u8 comand);
static void Lcd_SendData(u8 data);
/*************************************************/
void Lcd_Init(void)
{
    Lcd_InitPins();
    _delay_ms(30);
    Lcd_DisplayControlType display = {
        LCD_DISPLAY_STATUS,
        LCD_CURSOR_STATUS,
        LCD_LINE_STATUS,
        LCD_FONT_STATUS};
    Lcd_DisplayControl(display);
    Lcd_DisplayClear();
}
/*************************************************/

void Lcd_DisplayClear(void)
{
    Lcd_SendCommand(0b00000001);
}
/*************************************************/

static void Lcd_SendCommand(u8 comand)
{
    Dio_SetPinLevel(LCD_PIN_RS, STD_LOW);
    Dio_SetPinLevel(LCD_PIN_RW, STD_LOW);
    Dio_SetPinLevel(LCD_PIN_D0, GET_BIT(comand, 0));
    Dio_SetPinLevel(LCD_PIN_D1, GET_BIT(comand, 1));
    Dio_SetPinLevel(LCD_PIN_D2, GET_BIT(comand, 2));
    Dio_SetPinLevel(LCD_PIN_D3, GET_BIT(comand, 3));
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(comand, 4));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(comand, 5));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(comand, 6));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(comand, 7));
    Dio_SetPinLevel(LCD_PIN_EN, STD_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, STD_LOW);
}
/*************************************************/

static void Lcd_SendData(u8 data)
{
    Dio_SetPinLevel(LCD_PIN_RS, STD_HIGH);
    Dio_SetPinLevel(LCD_PIN_RW, STD_LOW);
    Dio_SetPinLevel(LCD_PIN_D0, GET_BIT(data, 0));
    Dio_SetPinLevel(LCD_PIN_D1, GET_BIT(data, 1));
    Dio_SetPinLevel(LCD_PIN_D2, GET_BIT(data, 2));
    Dio_SetPinLevel(LCD_PIN_D3, GET_BIT(data, 3));
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(data, 4));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(data, 5));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(data, 6));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(data, 7));
    Dio_SetPinLevel(LCD_PIN_EN, STD_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, STD_LOW);
}
/*************************************************/

static void Lcd_InitPins(void)
{
    Dio_SetPinMode(LCD_PIN_RS, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_RW, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_EN, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D0, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D1, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D2, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D3, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D4, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D5, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D6, DIO_PIN_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D7, DIO_PIN_OUTPUT);
}
/*************************************************/

void Lcd_DisplayCharacter(u8 character)
{
    Lcd_SendData(character);
}
/*************************************************/

void Lcd_DisplayString(u8 *str)
{
    while (*str != 0)
    {
        Lcd_SendData(*str);
        str++;
    }
}
/*************************************************/

void Lcd_DisplayNumber(s32 number)
{
    u32 reversed = 0;
    u8 counter = 0;
    if (number < 0)
    {
        Lcd_SendData('-');
        number *= -1;
    }
    do
    {
        reversed = (reversed * 10) + (number % 10);
        number = number / 10;
        counter++;
    } while (number != 0);
    do
    {
        Lcd_SendData((reversed % 10) + '0');
        reversed = (reversed / 10);
        counter--;
    } while (counter != 0);
}
/*************************************************/

void Lcd_DisplayControls(Lcd_ControlListType comand)
{
    Lcd_SendCommand(comand);
}
/*************************************************/

void Lcd_SetCursorPosition(u8 row, u8 col)
{
    u8 add;
    add = col + (row * 0x40);
    SET_BIT(add, 7);
    Lcd_SendCommand(add);
}
/*************************************************/

void Lcd_DisplayControl(Lcd_DisplayControlType display)
{
    /* Set Lines and Font */
    u8 command = 0b00110000;
    if (display.line_status == LCD_TWO_LINES)
    {
        SET_BIT(command, 3);
    }
    if (display.font_status == LCD_FONT_5X10)
    {
        SET_BIT(command, 2);
    }
    Lcd_SendCommand(command);

    /* Set Display and Cursor */
    if (display.display_status == LCD_DISPLAY_OFF)
    {
        Lcd_SendCommand(0b00001000);
    }
    else if (display.display_status == LCD_DISPLAY_ON)
    {
        switch (display.cursor_status)
        {
        case LCD_CURSOR_OFF:
            Lcd_SendCommand(0b00001100);
            break;
        case LCD_CURSOR_ON_BLINK:
            Lcd_SendCommand(0b00001111);
            break;
        case LCD_CURSOR_ON_NOT_BLINK:
            Lcd_SendCommand(0b00001110);
            break;
        default:
            break;
        }
    }
}
