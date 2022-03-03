#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#define BAUD 9600
#include <util/setbaud.h>

#include "serial.h"
#define BLUE PB1

bool running = true;

int main(void) {
    DDRB |= (1 << BLUE);    // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 an output
    PORTB &= ~(1 << BLUE);  // Set PB1 in PORTB to 0 (low) since we need to connect to GND to turn on
    // Baud Rate Register uses 2 bytes, H and L for all its settings, some unused bytes in H needs to be set to 0 for things to work
    UBRR0H = UBRRH_VALUE;  // Right shifts 8 times
    UBRR0L = UBRRL_VALUE;

// Look for Double Speed (asynchronous mode only)
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);  // 8-bit data
    UCSR0B = _BV(RXEN0);                 // Enable RX
    while (running) {
        loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
        UDR0 = 'a';
    }
}