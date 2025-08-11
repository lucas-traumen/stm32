
#ifndef __ST7735_H__
#define __ST7735_H__

#include <stdint.h>
#include "main.h"
#include "fonts.h"

#define LCD_INIT_END 0xFF

#define LCD_WIDTH 128  // ví d? LCD_WIDTH = 128
#define LCD_HEIGHT 160

typedef struct
{
SPI_HandleTypeDef *hspi;
GPIO_TypeDef *GPIO_portCs;
uint16_t GPIO_Pin_Cs;
GPIO_TypeDef *GPIO_portA0;
uint16_t GPIO_Pin_A0;
GPIO_TypeDef *GPIO_portRESET;
uint16_t GPIO_Pin_Reset;
}ST7735_Typedef;



void St7735_Init(ST7735_Typedef *st7735,SPI_HandleTypeDef *hspi,GPIO_TypeDef *GPIO_portCs,uint16_t GPIO_Pin_Cs,GPIO_TypeDef *GPIO_portA0,uint16_t GPIO_Pin_A0,GPIO_TypeDef *GPIO_portRESET,uint16_t GPIO_Pin_Reset);
void writeCMDTFT(ST7735_Typedef *st7735,uint8_t cmd);
void writeDataTFT(ST7735_Typedef *st7735,uint8_t data);
void write_init_list(ST7735_Typedef *st7735,const uint8_t* cmdlist);
void set_pos(ST7735_Typedef *st7735, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void initTFT(ST7735_Typedef *st7735);
void full_display(ST7735_Typedef *st7735,uint16_t color);
void drawpixel(ST7735_Typedef *st7735,uint8_t x, uint8_t y, uint16_t color);

//Font7x10
void drawchar_Font_7x10(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg);
void drawstring_Font_7x10(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg);
void clearChar_Font_7x10(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg);

//Font11x18
void drawchar_Font_11x18(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg);
void drawstring_Font_11x18(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg);
void clearChar_Font_11x18(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg);

//Font16x26
void drawchar_Font_16x26(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg);
void drawstring_Font_16x26(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg);
void clearChar_Font_16x26(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg);

void ST7735_FillRect(ST7735_Typedef *st7735,uint16_t startX, uint16_t startY, uint16_t width, uint16_t height, uint16_t color);
#endif // __ST7735_H__
