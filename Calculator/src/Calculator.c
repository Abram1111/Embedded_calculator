/*
 * Calculator.c
 *
 *  Created on: Sep 12, 2022
 *      Author: abram
 */

#include <std_types.h>
#include <Macros.h>
#include <Lcd.h>
#include <Keypad.h>
#include <Calculator.h>
#include <util/delay.h>
static u8 Calculator_GetActualNumber(u8 button);

void Calculator_Init(void)
{
    keypad_Init();
    Lcd_Init();
}

void Calculator_Run(void)
{
    u8 input_counter = 0;
    s32 number = 0;
    s32 result = 0;
    u8 operation = 0;
    u8 button = KEYPAD_INVALID;
    u8 actual_number;
    u8 last_element = 0;
    u8 syntax_flag = 0;
    u8 math_flag = 0;
    u8 minus_flag = 0;
    u8 floating_digt = 0;
    u8 lock_keypad_flag = 0;
    u8 floating_digt_minus_flag = 0;
    u8 print_flag = 0;
    while (1)
    {

        do
        {
            button = Keypad_GetPressedButtonPolling();
        } while (button == KEYPAD_INVALID);

        actual_number = Calculator_GetActualNumber(button);

        if (button == CALC_BUTTON_CLR)
        {
            Lcd_DisplayClear();
            Lcd_DisplayControls(DISPLAY_ON_CURSOR_ON_BLINKING);
            number = 0;
            result = 0;
            operation = 0;
            input_counter = 0;
            syntax_flag = 0;
            last_element = 0;
            math_flag = 0;
            minus_flag = 0;
            floating_digt = 0;
            lock_keypad_flag = 0;
            floating_digt_minus_flag = 0;
            print_flag = 0;
        }
        else if ((actual_number >= 0) && (actual_number <= 9))
        {
            if (last_element == '=')
            {
                Lcd_DisplayClear();
                Lcd_DisplayControls(DISPLAY_ON_CURSOR_ON_BLINKING);
                number = 0;
                result = 0;
                operation = 0;
                input_counter = 0;
                syntax_flag = 0;
                last_element = 0;
                math_flag = 0;
                minus_flag = 0;
                floating_digt = 0;
                lock_keypad_flag = 0;
                floating_digt_minus_flag = 0;
                print_flag = 0;
            }
            if (lock_keypad_flag == 0)
            {
                if (last_element == '/' && (actual_number == 0))
                {
                    math_flag = 1;
                }
                Lcd_DisplayNumber(actual_number);
                input_counter++;
                number = number * 10 + actual_number;
                if (minus_flag == 1)
                {
                    number *= -1;
                    minus_flag = 0;
                }
                last_element = actual_number;
            }
        }
        else
        {
            /**************check for key pad status**************/
            if (lock_keypad_flag == 0)
            {
                if (last_element == '=')
                {
                    Lcd_DisplayClear();
                    Lcd_SetCursorPosition(0, 0);
                    Lcd_DisplayString((u8 *)"Ans");
                    input_counter = 3;
                    switch (operation)
                    {
                    case '+':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result += (number * 100);
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result += (number * 100);
                        }
                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;
                        break;
                    case '-':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result -= (number * 100);
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result -= (number * 100);
                        }
                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }

                        break;
                    case '*':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result *= number;
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result *= number;
                        }

                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;

                        break;
                    case '/':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result = result / number;
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result = result / number;
                        }
                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;
                        break;
                    default:
                        break;
                    }
                    operation = actual_number;
                }
                Lcd_DisplayCharacter(actual_number);
                input_counter++;
                if (input_counter == 1)
                {
                    switch (actual_number)
                    {
                    case '*':
                        syntax_flag = 1;
                        break;
                    case '/':
                        syntax_flag = 1;
                        break;
                    case '-':
                        minus_flag = 1;
                        last_element = actual_number;
                        break;
                    default:
                        break;
                    }
                }

                if (((last_element >= 0) && (last_element <= 9)))
                {
                    switch (operation)
                    {
                    case '+':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result += (number * 100);
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result += (number * 100);
                        }

                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;
                        break;
                    case '-':

                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result -= (number * 100);
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result -= (number * 100);
                        }

                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;

                        break;
                    case '*':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result *= number;
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result *= number;
                        }

                        if (result < 0)
                        {
                            floating_digt = (result * -1) % 100;
                            print_flag = 1;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;
                        break;
                    case '/':
                        if (floating_digt_minus_flag == 1 || result < 0)
                        {
                            result = result * 100 - floating_digt;
                            result = result / number;
                            floating_digt_minus_flag = 0;
                        }
                        else
                        {
                            result = result * 100 + floating_digt;
                            result = result / number;
                        }

                        if (result < 0)
                        {
                            print_flag = 1;
                            floating_digt = (result * -1) % 100;
                        }
                        else
                        {
                            floating_digt = (result) % 100;
                            print_flag = 0;
                        }
                        result /= 100;
                        break;
                    default:
                        result = number;
                        break;
                    }
                    operation = actual_number;
                }
                else
                {
                    switch (last_element)
                    {
                    case '+':
                        if (actual_number == '*' || actual_number == '/')
                        {
                            syntax_flag = 1;
                        }
                        else
                        {
                            switch (actual_number)
                            {
                            case '+':
                                operation = '+';
                                break;
                            case '-':
                                operation = '-';
                                break;
                            case '=':
                                syntax_flag = 1;
                                operation = '=';
                                break;
                            default:
                                break;
                            }
                        }

                        break;
                    /***************************************************/
                    case '-':
                        if (actual_number == '*' || actual_number == '/')
                        {
                            syntax_flag = 1;
                        }
                        else
                        {
                            switch (actual_number)
                            {
                            case '+':
                                operation = '-';
                                break;
                            case '-':
                                operation = '+';
                                break;
                            case '=':
                                syntax_flag = 1;
                                operation = '=';
                                break;
                            default:
                                break;
                            }
                        }

                        break;
                        /*********************************************/
                    case '*':
                        switch (actual_number)
                        {
                        case '/':
                            syntax_flag = 1;
                            break;
                        case '*':
                            syntax_flag = 1;
                            break;
                        case '-':
                            operation = '*';
                            if (minus_flag)
                            {
                                minus_flag = 0;
                            }
                            else
                            {
                                minus_flag = 1;
                            }
                            break;
                        case '+':
                            operation = '*';
                            break;
                        case '=':
                            syntax_flag = 1;
                            operation = '=';
                            break;
                        default:
                            break;
                        }
                        break;
                    /********************************************************/
                    case '/':
                        switch (actual_number)
                        {
                        case '/':
                            syntax_flag = 1;
                            break;
                        case '*':
                            syntax_flag = 1;
                            break;
                        case '-':
                            operation = '/';
                            if (minus_flag)
                            {
                                minus_flag = 0;
                            }
                            else
                            {
                                minus_flag = 1;
                            }
                            break;
                        case '+':
                            operation = '/';
                            break;
                        case '=':
                            syntax_flag = 1;
                            operation = '=';
                            break;
                        default:
                            break;
                        }
                        break;

                    default:
                        break;
                    }
                }

                last_element = operation;
                number = 0;
            }

            if (input_counter >= 16)
            {
                Lcd_DisplayControls(DISPLAY_SHIT_LEFT);
            }
            if (operation == '=')
            {

                Lcd_DisplayControls(DISPLAY_ON_CURSOR_OFF);
                if (syntax_flag == 1)
                {
                    Lcd_SetCursorPosition(1, 0);
                    Lcd_DisplayString((u8 *)"syntax error");
                    Lcd_DisplayControls(HOME_RETURN);
                    lock_keypad_flag = 1;
                }
                else if (math_flag == 1)
                {
                    Lcd_SetCursorPosition(1, 0);
                    Lcd_DisplayString((u8 *)"math error");
                    Lcd_DisplayControls(HOME_RETURN);
                    lock_keypad_flag = 1;
                }

                else
                {
                    Lcd_SetCursorPosition(1, 0);
                    if (result == 0 && floating_digt != 0 && print_flag == 1)
                    {
                        Lcd_DisplayCharacter('-');
                        floating_digt_minus_flag = 1;
                    }
                    Lcd_DisplayNumber(result);
                    Lcd_DisplayCharacter('.');
                    if (floating_digt == 0)
                    {
                        Lcd_DisplayCharacter('0');
                        Lcd_DisplayCharacter('0');
                    }
                    else
                    {
                        Lcd_DisplayNumber(floating_digt);
                    }

                    Lcd_DisplayControls(HOME_RETURN);
                }
                last_element = '=';
            }
        }
    }
}

static u8 Calculator_GetActualNumber(u8 button)
{
    u8 number = 0;
    switch (button)
    {
    case CALC_BUTTON_0:
        number = 0;
        break;
    case CALC_BUTTON_1:
        number = 1;
        break;
    case CALC_BUTTON_2:
        number = 2;
        break;
    case CALC_BUTTON_3:
        number = 3;
        break;
    case CALC_BUTTON_4:
        number = 4;
        break;
    case CALC_BUTTON_5:
        number = 5;
        break;
    case CALC_BUTTON_6:
        number = 6;
        break;
    case CALC_BUTTON_7:
        number = 7;
        break;
    case CALC_BUTTON_8:
        number = 8;
        break;
    case CALC_BUTTON_9:
        number = 9;
        break;
    case CALC_BUTTON_PLUS:
        number = '+';
        break;
    case CALC_BUTTON_MINUS:
        number = '-';
        break;
    case CALC_BUTTON_MUL:
        number = '*';
        break;
    case CALC_BUTTON_DIV:
        number = '/';
        break;
    case CALC_BUTTON_EQUAL:
        number = '=';
        break;
    default:
        break;
    }
    return number;
}
