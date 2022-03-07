#include "serial.h"

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define BAUD 38400
#define FOSC 16000000
#include <util/setbaud.h>

void uart_init(void) {
    // Enable Transmitter:
    UCSR0B |= _BV(TXEN0);
    // Enable Receiver:
    UCSR0B |= _BV(RXEN0);

    // 8N1 Mode: (Controlled by UCSR0C register, see datasheet ch. 24.12.4 p. 249-250)
    // 8-bit data
    UCSR0C |= _BV(UCSZ01);
    UCSR0C |= _BV(UCSZ00);
    // No parity
    UCSR0C &= ~_BV(UPM01) & ~_BV(UPM00);  // Detta funkar!!!
    // UCSR0C &= ~_BV(UPM01); // Men kan goras i steg!!!
    // UCSR0C &= ~_BV(UPM00);
    // 1 stop bit
    UCSR0C &= ~_BV(USBS0);

    // Set baudrate: (see datasheet ch. 24

    uint16_t ubrrn = FOSC / (16 * BAUD) - 1;
    // UBRR0H = ubrrn & OxFF00; // High bits of 16 bit number
    // UBRR0L = ubrrn &0x00FF; // Low bits of 16 bit number
    UBRR0 = ubrrn;
}

void uart_init_old(void) {
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