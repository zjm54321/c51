#include <reg52.h>
#include <stdint.h>

void Delay500ms(void); //@11.0592MHz

int main(void)
{
    P2 = ((P2 & 0x1f) | 0x80);
    P0 = 0x00;

    // 实现跑马灯
    while (1) {
        for (uint8_t i = 0; i < 8; i++) {
            P0 = ~(0b10000000 >> i);
            Delay500ms();
        }
    }
}

void Delay500ms(void)
{
    uint8_t data i, j, k;

    __asm__("nop");
    __asm__("nop");
    i = 22;
    j = 3;
    k = 227;
    do {
        do {
            while (--k);
        } while (--j);
    } while (--i);
}
