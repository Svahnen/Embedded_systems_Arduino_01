#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) {
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    Enable receiver and transmitter * /
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void uart_putchar(char chr) {
    // while (!(UCSRnA & (1 << UDREn))) {}
}
void uart_putstr(const char *str) {
    // UDRn = str;
}

char uart_getchar(void);

void uart_echo(void);