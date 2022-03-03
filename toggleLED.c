#include "toggleLED.h"

#include <avr/io.h>

void toggleLED(int LED) {
    PORTB ^= (1 << LED);
}