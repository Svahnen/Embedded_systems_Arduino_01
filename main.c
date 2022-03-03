#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "serial.h"
#define BLUE PB1

bool running = true;

int main(void) {
    DDRB |= (1 << BLUE);    // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 an output
    PORTB &= ~(1 << BLUE);  // Set PB1 in PORTB to 0 (low) since we need to connect to GND to turn on

    while (running) {
        PORTB ^= (1 << BLUE);  // Invert the state of BLUE
        _delay_ms(500);
    }
}
