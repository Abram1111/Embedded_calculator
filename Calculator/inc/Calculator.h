/*
 * Calculator.h
 *
 *  Created on: Sep 12, 2022
 *      Author: abram
 */

#ifndef INC_CALCULATOR_H_
#define INC_CALCULATOR_H_
/* Calculator Buttons
7   8   9   +
4   5   6   -
1   2   3   *
C   0   =   /
*/

#define CALC_BUTTON_0       KEYPAD_B13
#define CALC_BUTTON_1       KEYPAD_B08
#define CALC_BUTTON_2       KEYPAD_B09
#define CALC_BUTTON_3       KEYPAD_B10
#define CALC_BUTTON_4       KEYPAD_B04
#define CALC_BUTTON_5       KEYPAD_B05
#define CALC_BUTTON_6       KEYPAD_B06
#define CALC_BUTTON_7       KEYPAD_B00
#define CALC_BUTTON_8       KEYPAD_B01
#define CALC_BUTTON_9       KEYPAD_B02
#define CALC_BUTTON_PLUS    KEYPAD_B03
#define CALC_BUTTON_MINUS   KEYPAD_B07
#define CALC_BUTTON_MUL     KEYPAD_B11
#define CALC_BUTTON_DIV     KEYPAD_B15
#define CALC_BUTTON_EQUAL   KEYPAD_B14
#define CALC_BUTTON_CLR     KEYPAD_B12

void Calculator_Init(void);
void Calculator_Run(void);


#endif /* INC_CALCULATOR_H_ */
