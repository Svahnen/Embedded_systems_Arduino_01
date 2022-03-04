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
        messageLength++;
        if (receivedChr == '\n') {
            message[messageLength] = '\0';
            if (strcmp(message, "BLUE\r\n") == 0) {
                // Send "BLUE\r\n" to toggle color
                toggleLED(BLUE);
            } else if (strcmp(message, "GREEN\r\n") == 0) {
                // Send "GREEN\r\n" to toggle color
                toggleLED(GREEN);
            } else if (strcmp(message, "RED\r\n") == 0) {
                // Send "RED\r\n" to toggle color
                toggleLED(RED);
            } else if (strcmp(message, "ON\r\n") == 0) {
                // Send "ON\r\n" to turn all colors on
                PORTB &= ~(1 << BLUE);
                PORTB &= ~(1 << GREEN);
                PORTB &= ~(1 << RED);
            } else if (strcmp(message, "OFF\r\n") == 0) {
                // Send "OFF\r\n" to turn all colors off
                PORTB |= (1 << BLUE);
                PORTB |= (1 << GREEN);
                PORTB |= (1 << RED);
            }
            messageLength = 0;
        }
    }
}