/* ------------------------------------------------------*
*                                                        *
* Copyright (c) 2013, Jarek Zok <jarek.zok@fwioo.pl>     *
* All rights reserved.                                   *
*                                                        *
* This program is free software; you can redistribute it *
* and/or modify it under the terms of the GNU General    *
* Public License as published by the Free Software       *
* Foundation; either version 2 of the License, or        *
* (at your option) any later version.                    *
*                                                        *
* This program is distributed in the hope that it will   *
* be useful, but WITHOUT ANY WARRANTY; without even the  *
* implied warranty of MERCHANTABILITY or FITNESS FOR A   *
* PARTICULAR PURPOSE.  See the GNU General Public        *
* License for more details.                              *
*                                                        *
* You should have received a copy of the GNU General     *
* Public License along with this program; if not, write  *
* to the Free Software Foundation, Inc.,                 *
* 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA *
*                                                        *
* Licence can be viewed at                               *
* http://www.fsf.org/licenses/gpl.txt                    *
*                                                        *
*                                                        *
**********************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            53
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 34 : -1)

#if defined(__AVR_ATmega128__)
#define digitalPinHasPWM(p) ((p)==4 || (p)==5 || (p)==6 || (p)==7 || (p)==8 || (p)==9)
#endif

static const uint8_t SS = 10;
static const uint8_t SCK = 11;
static const uint8_t MOSI = 12;
static const uint8_t MISO = 13;
static const uint8_t SCL = 27;
static const uint8_t SDA = 28;
static const uint8_t LED_BUILTIN = 31;

// Analog inputs definition
static const uint8_t A0 = 34;
static const uint8_t A1 = 35;
static const uint8_t A2 = 36;
static const uint8_t A3 = 37;
static const uint8_t A4 = 38;
static const uint8_t A5 = 39;
static const uint8_t A6 = 40;
static const uint8_t A7 = 41;

// End of analog inputs definition
/////////////////////

// A majority of the pins are NOT PCINTs, SO BE WARNED (i.e. you cannot use them as receive pins)
// Only pins available for RECEIVE (TRANSMIT can be on any pin):
// (I've deliberately left out pin mapping to the Hardware USARTs - seems senseless to me)
// E. Lins: changed this stuff to match the ATmega128, but it doesn't have PCINTs at all
// I eventually added the regular external interrupt stuff, but this has to be adapted in the core code
// Pins: 4, 5, 6, 7, 16, 17, 18, 19

#define digitalPinToPCICR(p)    ( (((p) >= 4) && ((p) <= 7)) ? (&EICRB) : \
                                  (((p) >= 16) && ((p) <= 19)) ? (&EICRA) : ((uint8_t *)0) )

#define digitalPinToPCICRbit(p) ( (((p) >= 4) && ((p) <= 7)) || (((p) >= 16) && ((p) <= 19)) ? 0 : 0 )

#define digitalPinToPCMSK(p)    ( (((p) >= 4) && ((p) <= 7)) || (((p) >= 16) && ((p) <= 19)) ? (&EIMSK) : \
                                ((uint8_t *)0) )

#define digitalPinToPCMSKbit(p) ( (((p) >= 4) && ((p) <= 7)) ? ((p)) : \
                                ( (((p) >= 16) && ((p) <= 19))) ? ((p - 16)) : \
                                0 )
/////////////////////


#ifdef ARDUINO_MAIN

    // these arrays map port names (e.g. port B) to the
    // appropriate addresses for various functions (e.g. reading
    // and writing)
    
const uint16_t PROGMEM port_to_mode_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &DDRA,
    (uint16_t) &DDRB,
    (uint16_t) &DDRC,
    (uint16_t) &DDRD,
    (uint16_t) &DDRE,
    (uint16_t) &DDRF,
    (uint16_t) &DDRG,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PORTA,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
    (uint16_t) &PORTE,
    (uint16_t) &PORTF,
    (uint16_t) &PORTG,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PINA,
    (uint16_t) &PINB,
    (uint16_t) &PINC,
    (uint16_t) &PIND,
    (uint16_t) &PINE,
    (uint16_t) &PINF,
    (uint16_t) &PING,
};
const uint8_t PROGMEM digital_pin_to_port_PGM[] = {

    // -- PORTE --
    PE, //** 0 ** PE0 - RXD0 - JP6.3
    PE, //** 1 ** PE1 - TXD0 - JP6.2

    // -- PORTD --
    PD, //** 2 ** PD2 - RXD1 - SV1.5
    PD, //** 3 ** PD3 - TXD1 - SV1.3

    // -- PORTB --
    PB, //** 4 ** PB5 - TIMER1A,PWM - JP1.16 (PWM)
    PB, //** 5 ** PB6 - TIMER1B,PWM - JP1.17 (PWM)
    PB, //** 6 ** PB7 - PWM - JP1.18 (PWM)

    // -- PORTE --
    PE, //** 7 ** PE3 - TIMER3A,PWM - IC3.D1 (PWM)
    PE, //** 8 ** PE4 - TIMER3B,PWM - IC1.D1 (PWM)
    PE, //** 9 ** PE5 - TIMER3C,PWM - JP1.8 (PWM)

    // -- PORTB --
    PB, //** 10 ** PB0 - SS - JP1.11
    PB, //** 11 ** PB1 - SCK - JP1.12
    PB, //** 12 ** PB2 - MOSI - JP1.13
    PB, //** 13 ** PB3 - MISO - JP1.14
    PB, //** 14 ** PB4 - -- - JP1.15

    // -- PORTC --
    PC, //** 15 ** PC0 - -- - JP2.8
    PC, //** 16 ** PC1 - -- - JP2.9
    PC, //** 17 ** PC2 - -- - JP2.10
    PC, //** 18 ** PC3 - -- - JP2.11
    PC, //** 19 ** PC4 - -- - JP2.12
    PC, //** 20 ** PC5 - -- - JP2.13
    PC, //** 21 ** PC6 - -- - JP2.14
    PC, //** 22 ** PC7 - -- - JP2.15

    // -- PORTA --
    PA, //** 23 ** PA3 - -- - IC1.IN1
    PA, //** 24 ** PA4 - -- - IC1.IN2
    PA, //** 25 ** PA5 - -- - IC3.IN1
    PA, //** 26 ** PA6 - -- - IC3.IN2

    // -- PORTD --
    PD, //** 27 ** PD0 - SCL - JP1.22 (SONAR.9)
    PD, //** 28 ** PD1 - SDA - JP1.21 (SONAR.7)
    PD, //** 29 ** PD6 - -- - LED2
    PD, //** 30 ** PD7 - -- - LED1

    // -- PORTE --
    PE, //** 31 ** PE2 - LED_BUILTIN - LED4
    PE, //** 32 ** PE6 - -- - LED5
    PE, //** 33 ** PE7 - -- - JP1.10 JP8.2

    // -- PORTF --
    PF, //** 34 ** PF0 - ADC0 - GND
    PF, //** 35 ** PF1 - ADC1 - IC1.F/B
    PF, //** 36 ** PF2 - ADC2 - GND
    PF, //** 37 ** PF3 - ADC3 - IC3.F/B
    PF, //** 38 ** PF4 - ADC4 - JP2.24
    PF, //** 39 ** PF5 - ADC5 - JP2.23
    PF, //** 40 ** PF6 - ADC6 - JP2.22
    PF, //** 41 ** PF7 - ADC7 - JP2.21

    // -- PORTG --
    PG, //** 42 ** PG0 - -- - JP2.6
    PG, //** 43 ** PG1 - -- - JP2.7
    PG, //** 44 ** PG2 - -- - JP2.16
    PG, //** 45 ** PG3 - -- - JP1.19; IC1.EN; IC3.EN
    PG, //** 46 ** PG4 - -- - JP1.20; IC1.EN; IC3.EN

    // -- PORTA --
    PA, //** 47 ** PA0 - -- - JP2.20
    PA, //** 48 ** PA1 - -- - JP2.19
    PA, //** 49 ** PA2 - -- - JP2.18
    PA, //** 50 ** PA7 - -- - JP2.17
    // -- PORTD --
    PD, //** 51 ** PD4 - -- - JP2.17
    PD, //** 52 ** PD5 - -- - JP2.17
    
    
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {

    // -- PORTE --
    _BV(0), // ** 0 ** PE0 - RXD0 - JP6.3
    _BV(1), // ** 1 ** PE1 - TXD0 - JP6.2

    // -- PORTD --
    _BV(2), // ** 2 ** PD2 - RXD1 - SV1.5
    _BV(3), // ** 3 ** PD3 - TXD1 - SV1.3

    // -- PORTB --
    _BV(5), // ** 4 ** PB5 - TIMER1A,PWM - JP1.16 (PWM)
    _BV(6), // ** 5 ** PB6 - TIMER1B,PWM - JP1.17 (PWM)
    _BV(7), // ** 6 ** PB7 - PWM - JP1.18 (PWM)

    // -- PORTE --
    _BV(3), // ** 7 ** PE3 - TIMER3A,PWM - IC3.D1 (PWM)
    _BV(4), // ** 8 ** PE4 - TIMER3B,PWM - IC1.D1 (PWM)
    _BV(5), // ** 9 ** PE5 - TIMER3C,PWM - JP1.8 (PWM)

    // -- PORTB --
    _BV(0), // ** 10 ** PB0 - SS - JP1.11
    _BV(1), // ** 11 ** PB1 - SCK - JP1.12
    _BV(2), // ** 12 ** PB2 - MOSI - JP1.13
    _BV(3), // ** 13 ** PB3 - MISO - JP1.14
    _BV(4), // ** 14 ** PB4 - -- - JP1.15

    // -- PORTC --
    _BV(0), // ** 15 ** PC0 - -- - JP2.8
    _BV(1), // ** 16 ** PC1 - -- - JP2.9
    _BV(2), // ** 17 ** PC2 - -- - JP2.10
    _BV(3), // ** 18 ** PC3 - -- - JP2.11
    _BV(4), // ** 19 ** PC4 - -- - JP2.12
    _BV(5), // ** 20 ** PC5 - -- - JP2.13
    _BV(6), // ** 21 ** PC6 - -- - JP2.14
    _BV(7), // ** 22 ** PC7 - -- - JP2.15

    // -- PORTA --
    _BV(3), // ** 23 ** PA3 - -- - IC1.IN1
    _BV(4), // ** 24 ** PA4 - -- - IC1.IN2
    _BV(5), // ** 25 ** PA5 - -- - IC3.IN1
    _BV(6), // ** 26 ** PA6 - -- - IC3.IN2

    // -- PORTD --
    _BV(0), // ** 27 ** PD0 - SCL - JP1.22 (SONAR.9)
    _BV(1), // ** 28 ** PD1 - SDA - JP1.21 (SONAR.7)
    _BV(6), // ** 29 ** PD6 - -- - LED2
    _BV(7), // ** 30 ** PD7 - -- - LED1

    // -- PORTE --
    _BV(2), // ** 31 ** PE2 - LED_BUILTIN - LED4
    _BV(6), // ** 32 ** PE6 - -- - LED5
    _BV(7), // ** 33 ** PE7 - -- - JP1.10 JP8.2

    // -- PORTF --
    _BV(0), // ** 34 ** PF0 - ADC0 - GND
    _BV(1), // ** 35 ** PF1 - ADC1 - IC1.F/B
    _BV(2), // ** 36 ** PF2 - ADC2 - GND
    _BV(3), // ** 37 ** PF3 - ADC3 - IC3.F/B
    _BV(4), // ** 38 ** PF4 - ADC4 - JP2.24
    _BV(5), // ** 39 ** PF5 - ADC5 - JP2.23
    _BV(6), // ** 40 ** PF6 - ADC6 - JP2.22
    _BV(7), // ** 41 ** PF7 - ADC7 - JP2.21

    // -- PORTG --
    _BV(0), // ** 42 ** PG0 - -- - JP2.6
    _BV(1), // ** 43 ** PG1 - -- - JP2.7
    _BV(2), // ** 44 ** PG2 - -- - JP2.16
    _BV(3), // ** 45 ** PG3 - -- - JP1.19; IC1.EN; IC3.EN
    _BV(4), // ** 46 ** PG4 - -- - JP1.20; IC1.EN; IC3.EN

    // -- PORTA --
    _BV(0), // ** 47 ** PA0 - -- - JP2.20
    _BV(1), // ** 48 ** PA1 - -- - JP2.19
    _BV(2), // ** 49 ** PA2 - -- - JP2.18
    _BV(7), // ** 50 ** PA7 - -- - JP2.17
    
    // -- PORTD --
    _BV(4), // ** 51 ** PD4 - -- - 
    _BV(5), // ** 52 ** PD5 - -- - 
    
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {

    // -- PORTE --
    NOT_ON_TIMER, // ** 0 ** PE0 - RXD0 - JP6.3
    NOT_ON_TIMER, // ** 1 ** PE1 - TXD0 - JP6.2

    // -- PORTD --
    NOT_ON_TIMER, // ** 2 ** PD2 - RXD1 - SV1.5
    NOT_ON_TIMER, // ** 3 ** PD3 - TXD1 - SV1.3

    // -- PORTB --
    TIMER1A, // ** 4 ** PB5 - TIMER1A,PWM - JP1.16 (PWM)
    TIMER1B, // ** 5 ** PB6 - TIMER1B,PWM - JP1.17 (PWM)
    NOT_ON_TIMER, // ** 6 ** PB7 - PWM - JP1.18 (PWM)

    // -- PORTE --
    TIMER3A, // ** 7 ** PE3 - TIMER3A,PWM - IC3.D1 (PWM)
    TIMER3B, // ** 8 ** PE4 - TIMER3B,PWM - IC1.D1 (PWM)
    TIMER3C, // ** 9 ** PE5 - TIMER3C,PWM - JP1.8 (PWM)

    // -- PORTB --
    NOT_ON_TIMER, // ** 10 ** PB0 - SS - JP1.11
    NOT_ON_TIMER, // ** 11 ** PB1 - SCK - JP1.12
    NOT_ON_TIMER, // ** 12 ** PB2 - MOSI - JP1.13
    NOT_ON_TIMER, // ** 13 ** PB3 - MISO - JP1.14
    NOT_ON_TIMER, // ** 14 ** PB4 - -- - JP1.15

    // -- PORTC --
    NOT_ON_TIMER, // ** 15 ** PC0 - -- - JP2.8
    NOT_ON_TIMER, // ** 16 ** PC1 - -- - JP2.9
    NOT_ON_TIMER, // ** 17 ** PC2 - -- - JP2.10
    NOT_ON_TIMER, // ** 18 ** PC3 - -- - JP2.11
    NOT_ON_TIMER, // ** 19 ** PC4 - -- - JP2.12
    NOT_ON_TIMER, // ** 20 ** PC5 - -- - JP2.13
    NOT_ON_TIMER, // ** 21 ** PC6 - -- - JP2.14
    NOT_ON_TIMER, // ** 22 ** PC7 - -- - JP2.15

    // -- PORTA --
    NOT_ON_TIMER, // ** 23 ** PA3 - -- - IC1.IN1
    NOT_ON_TIMER, // ** 24 ** PA4 - -- - IC1.IN2
    NOT_ON_TIMER, // ** 25 ** PA5 - -- - IC3.IN1
    NOT_ON_TIMER, // ** 26 ** PA6 - -- - IC3.IN2

    // -- PORTD --
    NOT_ON_TIMER, // ** 27 ** PD0 - SCL - JP1.22 (SONAR.9)
    NOT_ON_TIMER, // ** 28 ** PD1 - SDA - JP1.21 (SONAR.7)
    NOT_ON_TIMER, // ** 29 ** PD6 - -- - LED2
    NOT_ON_TIMER, // ** 30 ** PD7 - -- - LED1

    // -- PORTE --
    NOT_ON_TIMER, // ** 31 ** PE2 - LED_BUILTIN - LED4
    NOT_ON_TIMER, // ** 32 ** PE6 - -- - LED5
    NOT_ON_TIMER, // ** 33 ** PE7 - -- - JP1.10 JP8.2

    // -- PORTF --
    NOT_ON_TIMER, // ** 34 ** PF0 - ADC0 - GND
    NOT_ON_TIMER, // ** 35 ** PF1 - ADC1 - IC1.F/B
    NOT_ON_TIMER, // ** 36 ** PF2 - ADC2 - GND
    NOT_ON_TIMER, // ** 37 ** PF3 - ADC3 - IC3.F/B
    NOT_ON_TIMER, // ** 38 ** PF4 - ADC4 - JP2.24
    NOT_ON_TIMER, // ** 39 ** PF5 - ADC5 - JP2.23
    NOT_ON_TIMER, // ** 40 ** PF6 - ADC6 - JP2.22
    NOT_ON_TIMER, // ** 41 ** PF7 - ADC7 - JP2.21

    // -- PORTG --
    NOT_ON_TIMER, // ** 42 ** PG0 - -- - JP2.6
    NOT_ON_TIMER, // ** 43 ** PG1 - -- - JP2.7
    NOT_ON_TIMER, // ** 44 ** PG2 - -- - JP2.16
    NOT_ON_TIMER, // ** 45 ** PG3 - -- - JP1.19; IC1.EN; IC3.EN
    NOT_ON_TIMER, // ** 46 ** PG4 - -- - JP1.20; IC1.EN; IC3.EN

    // -- PORTA --
    NOT_ON_TIMER, // ** 47 ** PA0 - -- - JP2.20
    NOT_ON_TIMER, // ** 48 ** PA1 - -- - JP2.19
    NOT_ON_TIMER, // ** 49 ** PA2 - -- - JP2.18
    NOT_ON_TIMER, // ** 50 ** PA7 - -- - JP2.17
    
    // -- PORTD --
    NOT_ON_TIMER, // ** 51 ** PD4 - -- - 
    NOT_ON_TIMER, // ** 52 ** PD5 - -- - 
};

#endif
#endif
