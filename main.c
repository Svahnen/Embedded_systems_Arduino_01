#include <avr/io.h>
#include <stdbool.h>

#include "serial.h"
#define BLUE PB1

bool running = true;

int main(void) {
    DDRB |= (1 << BLUE);    // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 an output
    PORTB &= ~(1 << BLUE);  // Set PB1 in PORTB to 0 (low) since we need to connect to GND to turn on
    uint8_t timerOverflowCount = 0;
    TCNT0 = 0x00;  // Clear the counter
    TCCR0B = (1 << CS00) | (1 << CS02);

    while (1) {                        // A modified version of this: https://exploreembedded.com/wiki/AVR_Timer_programming
        while ((TIFR0 & 0x01) == 0) {  // Monitor the TOV0 flag in the TIFR0 register to check if the timer has over-flowed
        }
        TCNT0 = 0x00;  // Clear the counter
        TIFR0 = 0x01;  // clear timer1 overflow flag
        timerOverflowCount++;
        if (timerOverflowCount >= 100) {
            PORTB ^= (1 << BLUE);  // Invert the state of BLUE
            timerOverflowCount = 0;
        }
    }
}
