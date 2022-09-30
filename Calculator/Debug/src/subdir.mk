################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Calculator.c \
../src/Dio.c \
../src/Keypad.c \
../src/Lcd.c \
../src/main.c 

OBJS += \
./src/Calculator.o \
./src/Dio.o \
./src/Keypad.o \
./src/Lcd.o \
./src/main.o 

C_DEPS += \
./src/Calculator.d \
./src/Dio.d \
./src/Keypad.d \
./src/Lcd.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\imt\eclipse_projects\Calculator\inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


