#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) {
}

void uart_putchar(char chr) {
    // while (!(UCSRnA & (1 << UDREn))) {}
}
void uart_putstr(const char *str) {
    // UDRn = str;
}

char uart_getchar(void);

void uart_echo(void);