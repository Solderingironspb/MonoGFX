#include "main.h"
#include "stm32f103xx_CMSIS.h"
#include "MonoGFX.h"
#include <stdio.h>
#include <string.h>

extern char MonoGFX_tx_buffer[128];  // Буфер для отправки текста на дисплей

int main(void) {
    CMSIS_Debug_init();
    CMSIS_RCC_SystemClock_72MHz();
    CMSIS_SysTick_Timer_init();
    CMSIS_SPI1_init();
    CMSIS_GPIO_init(GPIOA, 2, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);
    CMSIS_GPIO_init(GPIOA, 3, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);
    CMSIS_GPIO_init(GPIOA, 4, GPIO_GENERAL_PURPOSE_OUTPUT, GPIO_OUTPUT_PUSH_PULL, GPIO_SPEED_50_MHZ);
    MonoGFX_Init();
    MonoGFX_logo_demonstration();

    sprintf(MonoGFX_tx_buffer, "Привет Мир!");
    MonoGFX_Decode_UTF8(0, 0, FONT_5X7, INVERSION_OFF, MonoGFX_tx_buffer);
    MonoGFX_Update();
    

    
    while (1) {
    }
}