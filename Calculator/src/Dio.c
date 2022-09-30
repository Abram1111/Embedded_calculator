/*
 * Dio.c
 *
 *  Created on: Aug 27, 2022
 *      Author: ahmad
 */
#include <Macros.h>
#include <Registers.h>
#include <std_types.h>
#include <Dio.h>

void Dio_SetPinMode(Dio_PortType port, Dio_PinType pin, Dio_PinModeType mode)
{
    if (mode == DIO_PIN_OUTPUT)
    {
        switch (port)
        {
        case DIO_PORTA:
            SET_BIT(DDRA, pin);
            break;
        case DIO_PORTB:
            SET_BIT(DDRB, pin);
            break;
        case DIO_PORTC:
            SET_BIT(DDRC, pin);
            break;
        case DIO_PORTD:
            SET_BIT(DDRD, pin);
            break;

        default:
            break;
        }
    }
    else if (mode == DIO_PIN_INPUT_FLOATING)
    {
        switch (port)
        {
        case DIO_PORTA:
            CLR_BIT(DDRA, pin);
            CLR_BIT(PORTA, pin);
            break;
        case DIO_PORTB:
            CLR_BIT(DDRB, pin);
            CLR_BIT(PORTB, pin);
            break;
        case DIO_PORTC:
            CLR_BIT(DDRC, pin);
            CLR_BIT(PORTC, pin);
            break;
        case DIO_PORTD:
            CLR_BIT(DDRD, pin);
            CLR_BIT(PORTD, pin);
            break;
        default:
            break;
        }
    }
    else if (mode == DIO_PIN_INPUT_PULLUP)
    {
        switch (port)
        {
        case DIO_PORTA:
            CLR_BIT(DDRA, pin);
            SET_BIT(PORTA, pin);
            break;
        case DIO_PORTB:
            CLR_BIT(DDRB, pin);
            SET_BIT(PORTB, pin);
            break;
        case DIO_PORTC:
            CLR_BIT(DDRC, pin);
            SET_BIT(PORTC, pin);
            break;
        case DIO_PORTD:
            CLR_BIT(DDRD, pin);
            SET_BIT(PORTD, pin);
            break;
        default:
            break;
        }
    }
}

void Dio_SetPinLevel(Dio_PortType port, Dio_PinType pin, Dio_PinLevelType level)
{
    if (level == STD_HIGH)
    {
        switch (port)
        {
        case DIO_PORTA:
            SET_BIT(PORTA, pin);
            break;
        case DIO_PORTB:
            SET_BIT(PORTB, pin);
            break;
        case DIO_PORTC:
            SET_BIT(PORTC, pin);
            break;
        case DIO_PORTD:
            SET_BIT(PORTD, pin);
            break;
        default:
            break;
        }
    }
    else if (level == STD_LOW)
    {
        switch (port)
        {
        case DIO_PORTA:
            CLR_BIT(PORTA, pin);
            break;
        case DIO_PORTB:
            CLR_BIT(PORTB, pin);
            break;
        case DIO_PORTC:
            CLR_BIT(PORTC, pin);
            break;
        case DIO_PORTD:
            CLR_BIT(PORTD, pin);
            break;
        default:
            break;
        }
    }
}

Dio_PinLevelType Dio_FlipPinLevel(Dio_PortType port, Dio_PinType pin)
{
    Dio_PinLevelType level;
    switch (port)
    {
    case DIO_PORTA:
        TOG_BIT(PORTA, pin);
        level = GET_BIT(PORTA, pin);
        break;
    case DIO_PORTB:
        TOG_BIT(PORTB, pin);
        level = GET_BIT(PORTB, pin);
        break;
    case DIO_PORTC:
        TOG_BIT(PORTC, pin);
        level = GET_BIT(PORTC, pin);
        break;
    case DIO_PORTD:
        TOG_BIT(PORTD, pin);
        level = GET_BIT(PORTD, pin);
        break;
    default:
        break;
    }
    return level;
}

Dio_PinLevelType Dio_ReadPinLevel(Dio_PortType port, Dio_PinType pin)
{
    Dio_PinLevelType level = STD_LOW;
    switch (port)
    {
    case DIO_PORTA:
        if (GET_BIT(PINA, pin) == 1)
        {
            level = STD_HIGH;
        }
        break;
    case DIO_PORTB:
        if (GET_BIT(PINB, pin) == 1)
        {
            level = STD_HIGH;
        }
        break;
    case DIO_PORTC:
        if (GET_BIT(PINC, pin) == 1)
        {
            level = STD_HIGH;
        }
        break;
    case DIO_PORTD:
        if (GET_BIT(PIND, pin) == 1)
        {
            level = STD_HIGH;
        }
        break;
    default:
        break;
    }
    return level;
}

void Dio_SetPortMode(Dio_PortType port, Dio_PortModeType mode)
{
    switch (port)
    {
    case DIO_PORTA:
        DDRA = mode;
        break;
    case DIO_PORTB:
        DDRB = mode;
        break;
    case DIO_PORTC:
        DDRC = mode;
        break;
    case DIO_PORTD:
        DDRD = mode;
        break;
    default:
        break;
    }
}
void Dio_SetPortLevel(Dio_PortType port, Dio_PortLevelType level)
{
    switch (port)
    {
    case DIO_PORTA:
        PORTA = level;
        break;
    case DIO_PORTB:
        PORTB = level;
        break;
    case DIO_PORTC:
        PORTC = level;
        break;
    case DIO_PORTD:
        PORTD = level;
        break;
    default:
        break;
    }
}

Dio_PortLevelType Dio_ReadPortLevel(Dio_PortType port)
{
    Dio_PortLevelType level = DIO_PORT_LOW;
    switch (port)
    {
    case DIO_PORTA:
        level = PINA;
        break;
    case DIO_PORTB:
        level = PINB;
        break;
    case DIO_PORTC:
        level = PINC;
        break;
    case DIO_PORTD:
        level = PIND;
        break;
    default:
        break;
    }
    return level;
}
