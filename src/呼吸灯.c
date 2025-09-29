#include <reg52.h>
#include <stdint.h>
uint8_t pwm_duty        = 0;
uint8_t pwm_count       = 0;
uint16_t breath_counter = 0;
int8_t direction        = 1;
void Timer0_set(uint16_t time);
int main(void)
{
    P2 = ((P2 & 0x1f) | 0x80);
    P0 = 0x00;
    while (1) {
        Timer0_set(10);
        pwm_count++;
        P0 = (pwm_count < pwm_duty ? 0b11111111 : 0b11111110);
        breath_counter++;
        if (breath_counter >= 200) {
            breath_counter = 0;
            pwm_duty += direction;
            if (pwm_duty == 250 || pwm_duty == 0) { direction = -direction; }
        }
        while (!TF0);
    }
}
void Timer0_set(uint16_t time)
{
    TMOD = 0x01;
    TH0  = (65536 - time) >> 8;
    TL0  = (65536 - time) & 0xFF;
    TR0  = 1;
    TF0  = 0;
}