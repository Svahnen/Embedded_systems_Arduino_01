#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
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

    PORTB |= (1 << BLUE);  // Set PB1 in PORTB to initial 1 (high) so it is off
    PORTB |= (1 << GREEN);
    PORTB |= (1 << RED);

    uart_init();

    char message[99];
    int messageLength = 0;
    while (running) {
        char receivedChr = uart_getchar();
        message[messageLength] = receivedChr;
        if (receivedChr == '\n') {
            message[messageLength + 1] = '\0';
            uart_putchar('?');
            if (strcmp(message, "ON\r\n") == 0) {
                uart_putchar('!');
            }

            /* for (size_t i = 0; i < messageLength; i++) {
                // TODO: Output the whole message so i can start using it to look for commands
                uart_putchar(message[i]);
            } */
            messageLength = 0;
        }
        messageLength++;
    }
}