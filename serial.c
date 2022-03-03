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

    // Register information found in the data sheet and here: https://appelsiini.net/2011/simple-usart-with-avr-libc/#registers
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);        // 8-bit data = 011
    UCSR0C |= (1 << USBS0);                    // USART Stop Bit Select. Set to select 1 stop bit. Unset to select 2 stop bits.
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
    // UDRn = str;
}

char uart_getchar(void);

void uart_echo(void);