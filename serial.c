#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>
//#define F_CPU 16000000UL // May need this in the future in case the clock is different
#define BAUD 38400
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

    UCSR0C &= ~(1 << 1);  // UCSZ00
    UCSR0C |= (1 << 2);   // UCSZ01
    UCSR0B |= (1 << 2);   // UCSZ02
    // 8-bit data = 011

    UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* Enable RX and TX */
}

void uart_putchar(char chr) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = chr;
}
void uart_putstr(const char *str) {
    // UDRn = str;
}

char uart_getchar(void);

void uart_echo(void);