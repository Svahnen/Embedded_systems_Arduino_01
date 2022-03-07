#include "serial.h"

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#define BAUD 38400
#define FOSC 16000000
#include <util/setbaud.h>

void uart_init(void) {
    // Baud Rate Register uses 2 bytes, H and L for all its settings, some unused bytes in H needs to be set to 0 for things to work
    UBRR0H = UBRRH_VALUE;  // Right shifts 8 times
    UBRR0L = UBRRL_VALUE;

// Look for Double Speed (asynchronous mode only)
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    // Register information found in the data sheet and here: https://appelsiini.net/2011/simple-usart-with-avr-libc/#registers
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);        // 8-bit data = 011 (read from the right) they are set by UCSZ00 UCSZ01 and UCSZ02 (in UCSR0B)
    UCSR0C &= ~(1 << USBS0);                   // 0 = 1-bit, 1 = 2-bit
    UCSR0C &= ~((1 << UPM00) | (1 << UPM01));  // 00 = Parity mode none
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);          /* Enable RX and TX */
}

void uart_putchar(char chr) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    if (chr == '\n') {
        UDR0 = chr;
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = '\r';  // Add '\r' after '\n'
    } else {
        UDR0 = chr;
    }
}
void uart_putstr(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        uart_putchar(str[i]);
    }
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void uart_echo(void) {
    uart_putchar(uart_getchar());
}