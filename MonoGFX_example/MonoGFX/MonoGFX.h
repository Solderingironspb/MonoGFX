/*
 * MonoGFX.h
 *
 *  Версия 1.1.(Общая графическая библиотека Волкова Олега)
 *  Переделан вывод символов на дисплей. В версии 1.1. имеется возможность вывода текста в любой точке по x и y.
 *
 *  Created on: Aug 16, 2021
 *      Author: Oleg Volkov
 *
 *  YouTube: https://www.youtube.com/channel/UCzZKTNVpcMSALU57G1THoVw
 *  GitHub: https://github.com/Solderingironspb/Lessons-Stm32/blob/master/README.md
 *  Группа ВК: https://vk.com/solderingiron.stm32
 *
 *  Кодировка UTF-8 Basic Latin: https://www.utf8-chartable.de/unicode-utf8-table.pl
 *  Кодировка UTF-8 Cyrillic: https://www.utf8-chartable.de/unicode-utf8-table.pl?start=1024&names=-&unicodeinhtml=hex
 *  Программа для конвертации изображения.bmp в bitmap: http://en.radzio.dxp.pl/bitmap_converter/
 */

#ifndef INC_MONOGFX_H_
#define INC_MONOGFX_H_

/*----------Выбор библиотеки----------*/
#define USE_CMSIS  // Работать на CMSIS
// #define USE_HAL   //Работать на HAL
/*----------Выбор библиотеки----------*/

/******************************** ВЫБОР ДРАЙВЕРА ДИСПЛЕЯ **********************************/
// ВАЖНО! Выбран должен быть только один драйвер! Остальное закккоментируем.
//#define ST7565r  // GMG12864-06D
#define ST7567   // GMG12864-03A



#if defined(USE_CMSIS)
#include "stm32f103xx_CMSIS.h"
#elif defined(USE_HAL)
#include "stm32f1xx_hal.h"
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*----------Макросы----------*/
#define CS_PORT GPIOA  // Порт ножки CS
#define CS_PIN  2      // Пин ножки CS

#define RST_PORT GPIOA  // Порт ножки Reset
#define RST_PIN  3      // Пин ножки Reset

#define DC_PORT GPIOA  // Порт ножки Data-command
#define DC_PIN  4      // Пин ножки Data-command

// NSS_ACTIVE_LOW
#define CS_ON  CS_PORT->BSRR = (1 << (CS_PIN + 16))  // CS вкл.
#define CS_OFF CS_PORT->BSRR = (1 << CS_PIN);        // CS выкл.

// RST_ACTIVE_LOW
#define RST_ON  RST_PORT->BSRR = (1 << (RST_PIN + 16))  // RST вкл.
#define RST_OFF RST_PORT->BSRR = (1 << RST_PIN);        // RST выкл.

// DC_ACTIVE_LOW
#define DC_ON  DC_PORT->BSRR = (1 << (DC_PIN + 16))  // DC вкл.
#define DC_OFF DC_PORT->BSRR = (1 << DC_PIN);        // DC выкл.

/******************************** ДРАЙВЕР ST7565r **********************************/
#if defined(ST7565r)
#define ST7565_SetX(x)                              \
    MonoGFX_Send_command(((x) & 0xf0) >> 4 | 0x10); \
    MonoGFX_Send_command((x) & 0x0f)
#define ST7565_SetY(y) MonoGFX_Send_command(((y) & 0x07) | 0xB0)

#define ST7565r_DISPLAY_ON       0xAF
#define ST7565r_DISPLAY_OFF      0xAE
#define ST7565r_SET_START_LINE   0x40
#define ST7565r_SEG_NORMAL       0xA0
#define ST7565r_SEG_REVERSE      0xA1
#define ST7565r_COLOR_NORMAL     0xA6
#define ST7565r_COLOR_INVERSE    0xA7
#define ST7565r_DISPLAY_DRAM     0xA4
#define ST7565r_DISPLAY_ALL_ON   0xA5
#define ST7565r_SW_RESET         0xE2
#define ST7565r_COM_NORMAL       0xC0
#define ST7565r_COM_REVERSE      0xC8
#define ST7565r_POWER_CONTROL    0x28
#define ST7565r_SET_RR           0x20
#define ST7565r_SET_EV_CMD       0x81
#define ST7565r_NOP              0xE3
#define ST7565r_PAGE_ADDR        0xB0
#define ST7565r_COL_ADDR_H       0x10
#define ST7565r_COL_ADDR_L       0x00
#define ST7565r_BIAS7            0xA3
#define ST7565r_BIAS9            0xA2
#define ST7565r_PWR_BOOSTER_ON   0x04
#define ST7565r_PWR_REGULATOR_ON 0x02
#define ST7565r_PWR_FOLLOWER_ON  0x01

#elif defined(ST7567)
#define ST7567_SetX(x)                              \
    MonoGFX_Send_command(((x) & 0xf0) >> 4 | 0x10); \
    MonoGFX_Send_command((x) & 0x0f)
#define ST7567_SetY(y) MonoGFX_Send_command(((y) & 0x07) | 0xB0)
#define ST7567A_DISPLAY_ON       0xAF
#define ST7567A_DISPLAY_OFF      0xAE
#define ST7567A_SET_START_LINE   0x40  // + line0 - line63
#define ST7567A_SEG_NORMAL       0xA0
#define ST7567A_SEG_REVERSE      0xA1
#define ST7567A_COLOR_NORMAL     0xA6
#define ST7567A_COLOR_INVERSE    0xA7
#define ST7567A_DISPLAY_DRAM     0xA4
#define ST7567A_DISPLAY_ALL_ON   0xA5
#define ST7567A_SW_RESET         0xE2
#define ST7567A_COM_NORMAL       0xC0
#define ST7567A_COM_REVERSE      0xC8
#define ST7567A_POWER_CONTROL    0x28
#define ST7567A_SET_RR           0x20  // + RR[2:0]; 3.0, 3.5, ..., 6.5
#define ST7567A_SET_EV_CMD       0x81
#define ST7567A_NOP              0xE3
#define ST7567A_PAGE_ADDR        0xB0  // + 0x0 - 0x7 -> page0 - page7
#define ST7567A_COL_ADDR_H       0x10  // + X[7:4]
#define ST7567A_COL_ADDR_L       0x00  // + X[3:0]
#define ST7567A_BIAS7            0xA3
#define ST7567A_BIAS9            0xA2
#define ST7567A_PWR_BOOSTER_ON   0x04
#define ST7567A_PWR_REGULATOR_ON 0x02
#define ST7567A_PWR_FOLLOWER_ON  0x01

typedef struct {
    uint8_t curr_x;
    uint8_t curr_y;
} ST7567A_pos_t;

#endif

/******************************** ШРИФТ. ЦВЕТ **********************************/
#define FONT_3X5      0
#define FONT_5X7      1
#define INVERSION_OFF 0
#define INVERSION_ON  1

void MonoGFX_logo_demonstration(void);
void MonoGFX_Init(void);
void MonoGFX_Clean_Frame_buffer(void);
void MonoGFX_Update(void);
void MonoGFX_DrawBitmap(const uint8_t *bitmap, int8_t x, int8_t y, int8_t w, int8_t h);
void MonoGFX_Draw_pixel(int16_t x, int16_t y, uint8_t color);
void MonoGFX_Print_symbol_5x7(uint8_t x, uint8_t y, uint16_t symbol, uint8_t inversion);
void MonoGFX_Print_symbol_3x5(uint8_t x, uint8_t y, uint16_t symbol, uint8_t inversion);
void MonoGFX_Decode_UTF8(uint8_t x, uint8_t y, uint8_t font, bool inversion, char *tx_buffer);
void MonoGFX_Inversion(uint16_t x_start, uint16_t x_end);
uint8_t MonoGFX_Value_for_Plot(int y_min, int y_max, float value);
void MonoGFX_Fill_the_array_Plot(uint8_t *counter, uint8_t *array, uint8_t size_array, uint8_t value);
void MonoGFX_Generate_a_Graph(uint8_t *counter, uint8_t *array, uint8_t size_array, int y_min, int y_max, uint8_t x_grid_time, uint8_t time_interval, bool grid);
void MonoGFX_Draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t color);
void MonoGFX_Draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void MonoGFX_Draw_rectangle_filled(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void MonoGFX_Draw_circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color);
void MonoGFX_Draw_circle_filled(int16_t x, int16_t y, int16_t radius, uint8_t color);
void MonoGFX_Draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t color);
void MonoGFX_Draw_triangle_filled(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t color);

/******************************** ШРИФТЫ **********************************/




#endif /* INC_MONOGFX_H_ */
