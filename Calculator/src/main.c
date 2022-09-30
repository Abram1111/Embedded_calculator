#include <std_types.h>
#include <Macros.h>
#include <cpu_freq.h>
#include <Keypad.h>
#include <Lcd.h>
#include <Calculator.h>

int main(void) {
	Lcd_Init();
	keypad_Init();
	Calculator_Run();
}
