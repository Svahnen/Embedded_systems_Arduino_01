#include <avr/io.h>

#include "serial.h"

void main(void) {
    DDRB |= (1 << PB1);    // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 and output
    PORTB &= ~(1 << PB1);  // Set PB1 in PORTB to 0 (low) since we need to connect to GND to turn on
}
