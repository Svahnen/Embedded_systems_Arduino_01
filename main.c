#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "serial.h"
#define BLUE PB1
#define BAUD 9600                               // define baud
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)  // set baud rate value for UBRR

bool running = true;

int main(void) {
    DDRB |= (1 << BLUE);    // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 an output
    PORTB &= ~(1 << BLUE);  // Set PB1 in PORTB to 0 (low) since we need to connect to GND to turn on

    UBRR0H = (BAUDRATE >> 8);                                  // shift the register right by 8 bits
    UBRR0L = BAUDRATE;                                         // set baud rate
    UCSR0B |= (1 << TXEN0);                                    // enable RX
    UCSR0C |= (1 << UMSEL00) | (1 << UCSZ00) | (1 << UCSZ01);  // 8bit data format
    while (running) {
        while (!(UCSR0A & (1 << UDRE0))) {
        }            // wait while register is free
        UDR0 = 'a';  // load data in the register
    }
}
