#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "serial.h"
#include "toggleLED.h"
#define BLUE PB1
#define GREEN PB2
#define RED PB3

bool running = true;

int main(void) {
    DDRB |= (1 << BLUE);  // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 1, this makes PB1 an output
    DDRB |= (1 << GREEN);
    DDRB |= (1 << RED);

    uart_init();

    // char *name = "Jonny Svahn\n";
    while (running) {
        toggleLED(BLUE);
        _delay_ms(1000);
    }
}