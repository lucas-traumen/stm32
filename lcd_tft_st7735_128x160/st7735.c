#include<st7735.h>


/*
				#define CS_PIN_Pin GPIO_PIN_0
				#define CS_PIN_GPIO_Port GPIOB
				#define A0_PIN_Pin GPIO_PIN_1
				#define A0_PIN_GPIO_Port GPIOB
				#define RESET_PIN_Pin GPIO_PIN_10
				#define RESET_PIN_GPIO_Port GPIOB
*/


static const uint8_t u8InitCmdList[] ={
//		CMD			length		Data
			0xB1,		0x03,			0x01,0x2C,0x2D, //Frame rate control(Normal mode)
			0xB2,		0x03,			0x01,0x2C,0x2D, //Frame rate control(Idle mode)
			0xB3,		0x06,			0x01,0x2C,0x2D,0x01,0x2C,0x2D, //Frame rate control(Partial mode)
			0xB4,		0x01,			0x07, 					//Display inversion control
			0xC0,		0x03,			0xA2,0x02,0x84, //Power control 1
			0xC1,		0x01,			0xC5,						//Power control 2
			0xC3,		0x02,			0x8A,0x2A,			//Power control 3
			0xC4,		0x02,			0x8A,0xEE,			//Power control 4
			0xC5,		0x01,			0x0E,						//Power control 5
			0xE0,		0x16,			0x02,0x1C,0x07,0x12,0x37,0x32,0x29,0x2D,0x29,0x25,0x2B,0x39,0x00,0x01,0x03,0x10, //Gamma adjustment(+ polarity)
			0xE1,		0x16,			0x03,0x1D,0x07,0x06,0x2E,0x2C,0x29,0x2D,0x2E,0x2E,0x37,0x3F,0x00,0x00,0x02,0x10, //Gamma adjustment(- polarity)
			LCD_INIT_END,LCD_INIT_END
	
};


void writeCMDTFT(ST7735_Typedef *st7735,uint8_t cmd)
{
	HAL_GPIO_WritePin(st7735->GPIO_portCs,st7735->GPIO_Pin_Cs,GPIO_PIN_RESET); //CS=0
	HAL_GPIO_WritePin(st7735->GPIO_portA0,st7735->GPIO_Pin_A0,GPIO_PIN_RESET); //CMD
	HAL_SPI_Transmit(st7735->hspi,&cmd,1,1000);
	HAL_GPIO_WritePin(st7735->GPIO_portCs,st7735->GPIO_Pin_Cs,GPIO_PIN_SET); //CS=1
}

void writeDataTFT(ST7735_Typedef *st7735,uint8_t data)
{
		HAL_GPIO_WritePin(st7735->GPIO_portCs,st7735->GPIO_Pin_Cs,GPIO_PIN_RESET); //CS=0
	HAL_GPIO_WritePin(st7735->GPIO_portA0,st7735->GPIO_Pin_A0,GPIO_PIN_SET); //Data
	HAL_SPI_Transmit(st7735->hspi,&data,1,1000);
	HAL_GPIO_WritePin(st7735->GPIO_portCs,st7735->GPIO_Pin_Cs,GPIO_PIN_SET); //CS=1
}
void St7735_Init(ST7735_Typedef *st7735,SPI_HandleTypeDef *hspi,GPIO_TypeDef *GPIO_portCs,uint16_t GPIO_Pin_Cs,GPIO_TypeDef *GPIO_portA0,uint16_t GPIO_Pin_A0,GPIO_TypeDef *GPIO_portRESET,uint16_t GPIO_Pin_Reset)
{
		st7735->hspi=hspi;
		st7735->GPIO_portCs=GPIO_portCs;
		st7735->GPIO_Pin_Cs=GPIO_Pin_Cs;
		st7735->GPIO_portA0=GPIO_portA0;
		st7735->GPIO_Pin_A0=GPIO_Pin_A0;
		st7735->GPIO_portRESET=GPIO_portRESET;
		st7735->GPIO_Pin_Reset=GPIO_Pin_Reset;
		
		initTFT(st7735);
}
void write_init_list(ST7735_Typedef *st7735,const uint8_t* cmdlist)
{
	uint8_t cmd= 0;
	uint8_t len= 0;
	
	while(1)
	{
		
		cmd = *cmdlist++;
    if (cmd == LCD_INIT_END) break;
    len = *cmdlist++;
    if (len == LCD_INIT_END) break;

    writeCMDTFT(st7735, cmd);
    for (int i = 0; i < len; i++) {
        writeDataTFT(st7735, *cmdlist++);
			
	
		}
	
	}
}
void set_pos(ST7735_Typedef *st7735, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	writeCMDTFT(st7735,0x2A);
	writeDataTFT(st7735,0x00);
	writeDataTFT(st7735,x1);
	writeDataTFT(st7735,0x00);
	writeDataTFT(st7735,x2);
	
	writeCMDTFT(st7735,0x2B);
	writeDataTFT(st7735,0x00);
	writeDataTFT(st7735,y1);
	writeDataTFT(st7735,0x00);
	writeDataTFT(st7735,y2);
	
}
void initTFT(ST7735_Typedef *st7735)
{
	HAL_GPIO_WritePin(st7735->GPIO_portRESET,st7735->GPIO_Pin_Reset,GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(st7735->GPIO_portRESET,st7735->GPIO_Pin_Reset,GPIO_PIN_SET);
	HAL_Delay(100);
	
writeCMDTFT(st7735,0x01); // Software reset
HAL_Delay(150);

writeCMDTFT(st7735,0x11); // Sleep out
HAL_Delay(500);
	
	
	write_init_list(st7735,u8InitCmdList);
	
	writeCMDTFT(st7735,0x36);
	writeDataTFT(st7735,0x00); //rgb

	writeCMDTFT(st7735,0x3A);
	writeDataTFT(st7735,0x05);
	
	writeCMDTFT(st7735,0x20);
	set_pos(st7735,0,0,128,160);
		
writeCMDTFT(st7735,0x29);		
		HAL_Delay(100);
}
void full_display(ST7735_Typedef *st7735,uint16_t color)
{
	writeCMDTFT(st7735,0x2C);
	int i;
	for (i=0;i<128*160;i++){
		
	uint8_t data []={color >>8,color & 0xFF};
			writeDataTFT(st7735,data[0]);
			writeDataTFT(st7735,data[1]);
			
			
					
	}
}
void drawpixel(ST7735_Typedef *st7735,uint8_t x, uint8_t y, uint16_t color)
{
	    // Ch?n pixel ngo�i v�ng hi?n th?
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) return;

    // G?i l?nh ch?n v�ng (1 pixel duy nh?t)
    set_pos(st7735, x, y, x, y);
	writeCMDTFT(st7735,0x2C);
	
	uint8_t data []={color >>8,color & 0xFF};
			writeDataTFT(st7735,data[0]);
			writeDataTFT(st7735,data[1]);	
	
	
}
void drawchar_Font_7x10(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg)
{
	uint32_t i,j=0;
	uint32_t pixel_data;
	for( i =0;i < Font_7x10.height;i++){
		 pixel_data=Font_7x10.data[(chr-32)*Font_7x10.height+i];
			for( j=0;j<Font_7x10.width;j++){
				if((pixel_data<<j) & 0x8000)
					drawpixel(st7735,x+j,y+i,color);
				else
					drawpixel(st7735,x+j,y+i,bg);
				}
		}
}
void drawstring_Font_7x10(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg)
{
	while(*str !='\0'){
		drawchar_Font_7x10(st7735,x,y,*str,color,bg);
		x+=Font_7x10.width;
		//y+=Font_7x10.height;
		str++;
	}
}
void clearChar_Font_7x10(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg) {
    for (uint8_t i = 0; i < Font_7x10.height; i++) {
        for (uint8_t j = 0; j < Font_7x10.width; j++) {
            drawpixel(st7735, x + j, y + i, bg);
        }
    }
}		
void ST7735_FillRect(ST7735_Typedef *st7735,uint16_t startX, uint16_t startY, uint16_t width, uint16_t height, uint16_t color)
{
    if ((startX >= LCD_WIDTH) || (startY >= LCD_HEIGHT)) return;
    if ((startX + width - 1) >= LCD_WIDTH)  width  = LCD_WIDTH - startX;
    if ((startY + height - 1) >= LCD_HEIGHT) height = LCD_HEIGHT - startY;

    // Set v�ng c?n v?
    set_pos(st7735,startX, startY, startX + width - 1, startY + height - 1);
writeCMDTFT(st7735,0x2C);
    // Chu?n b? buffer m�u (RGB565)
    uint8_t data[2] = { color >> 8, color & 0xFF };

    // G?i d? li?u
    for (uint32_t i = 0; i < width * height; i++)
    {
      writeDataTFT(st7735,data[0]);
			writeDataTFT(st7735,data[1]);	
	
    }
}
void drawchar_Font_11x18(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg)
{
	uint32_t i,j=0;
	uint32_t pixel_data;
	for( i =0;i < Font_11x18.height;i++){
		 pixel_data=Font_11x18.data[(chr-32)*Font_11x18.height+i];
			for( j=0;j<Font_11x18.width;j++){
				if((pixel_data<<j) & 0x8000)
					drawpixel(st7735,x+j,y+i,color);
				else
					drawpixel(st7735,x+j,y+i,bg);
				}
		}
}
void drawstring_Font_11x18(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg)
{
	while(*str !='\0'){
		drawchar_Font_11x18(st7735,x,y,*str,color,bg);
		x+=Font_11x18.width;
		//y+=Font_11x18.height;
		str++;
	}
}
void clearChar_Font_11x18(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg) {
    for (uint8_t i = 0; i < Font_11x18.height; i++) {
        for (uint8_t j = 0; j < Font_11x18.width; j++) {
            drawpixel(st7735, x + j, y + i, bg);
        }
    }
}
void drawchar_Font_16x26(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char chr, uint16_t color, uint16_t bg)
{
	uint32_t i,j=0;
	uint32_t pixel_data;
	for( i =0;i < Font_16x26.height;i++){
		 pixel_data=Font_16x26.data[(chr-32)*Font_16x26.height+i];
			for( j=0;j<Font_16x26.width;j++){
				if((pixel_data<<j) & 0x8000)
					drawpixel(st7735,x+j,y+i,color);
				else
					drawpixel(st7735,x+j,y+i,bg);
				}
		}
}
void drawstring_Font_16x26(ST7735_Typedef *st7735, uint8_t x ,uint8_t y, char *str, uint16_t color, uint16_t bg)
{
	while(*str !='\0'){
		drawchar_Font_16x26(st7735,x,y,*str,color,bg);
		x+=Font_16x26.width;
		//y+=Font_16x26.height;
		str++;
	}
}
void clearChar_Font_16x26(ST7735_Typedef *st7735, uint8_t x, uint8_t y, uint16_t bg) {
    for (uint8_t i = 0; i < Font_16x26.height; i++) {
        for (uint8_t j = 0; j < Font_16x26.width; j++) {
            drawpixel(st7735, x + j, y + i, bg);
        }
    }
}	
