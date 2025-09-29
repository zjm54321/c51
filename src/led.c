#include <reg52.h>
#include <stdint.h>

void LED_set(uint8_t state)
{
    P2 = ((P2 & 0x1f) | 0x80);
    P0 = state;
}