#include <reg52.h>
#include <stdint.h>

// 全局变量
uint16_t timer_count = 0; // 定时器中断计数器

void Timer0_Init(void);
void Delay500ms(void);

int main(void)
{
    P2 = ((P2 & 0x1f) | 0x80);
    P0 = 0x00;
    
    Timer0_Init(); // 初始化定时器T0

    // 实现跑马灯，两侧往中间亮,再从中间往两侧亮
    while (1) {
        for (uint8_t i = 0; i < 4; i++) {
            P0 = ~((1 << i) | (1 << (7 - i)));
            Delay500ms();
        }
        for (uint8_t i = 3; i > 0; i--) {
            P0 = ~((1 << i) | (1 << (7 - i)));
            Delay500ms();
        }
    }
}

// 定时器T0初始化函数 - 8位自动重装方式 1ms@12MHz
void Timer0_Init(void)
{
    TMOD &= 0xF0; // 清除T0控制位
    TMOD |= 0x02; // 设置T0为工作方式2（8位自动重装方式）
    
    TH0  = (65536 - 1000) >> 8;
    TL0  = (65536 - 1000) & 0xFF;
    
    ET0 = 1;  // 允许定时器T0中断
    EA = 1;   // 开启总中断
    TR0 = 1;  // 启动定时器T0
}

// 使用定时器T0中断实现500ms延时
void Delay500ms(void)
{
    while (timer_count != 1000); 
    timer_count = 0; // 清零计数器

}

// 定时器T0中断服务程序
void Timer0_ISR(void) interrupt 1
{
    timer_count++; // 每次中断计数器加1
    TH0  = (65536 - 1000) >> 8; // 重装初值
    TL0  = (65536 - 1000) & 0xFF;

    TF0 = 0; // 清除TF0标志
}
