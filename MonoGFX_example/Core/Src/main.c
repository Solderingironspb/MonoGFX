#include "main.h"
#include "stm32f103xx_CMSIS.h"
#include "MonoGFX.h"
#include <stdio.h>
#include <string.h>

extern char MonoGFX_tx_buffer[128];  // Буфер для отправки текста на дисплей
extern volatile uint32_t SysTimer_ms;         // Переменная, аналогичная HAL_GetTick()

int main(void) {
    CMSIS_Debug_init();
    CMSIS_RCC_SystemClock_72MHz();
    CMSIS_SysTick_Timer_init();
    CMSIS_SPI1_init();
    CMSIS_GPIO_init(GPIOA, 2, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);  // CS
    CMSIS_GPIO_init(GPIOA, 3, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);  // RST
    //CMSIS_GPIO_init(GPIOA, 4, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);  // DC
    Delay_ms(100);

    MonoGFX_Init();
    Delay_ms(100);
    MonoGFX_logo_demonstration();



    while (1) {
        sprintf(MonoGFX_tx_buffer, "Привет Мир!");
        MonoGFX_Decode_UTF8(1, 1, FONT_5X7, INVERSION_OFF, MonoGFX_tx_buffer);
        sprintf(MonoGFX_tx_buffer, "Сист. таймер насчитал: %lu(ms)", SysTimer_ms);
        MonoGFX_Decode_UTF8(1, 20, FONT_3X5, INVERSION_OFF, MonoGFX_tx_buffer);
        MonoGFX_Update();
    }
}
