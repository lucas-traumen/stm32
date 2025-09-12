#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "RTE_Components.h"             // Component selection
#include "gpio.h"
#include "bitband.h"




void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
}

void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void delay( uint32_t timedelay )
{
    for( uint32_t i =0;i<timedelay;i++);
}

int main(void) {
	//RCC->APB2ENR |=((1<<4) |(1<<2));
	RCC_Config();
	GPIO_Config();
    while(1) {
        //Togglepin(GPIOC,GPIO_Pin_13);
				PCout(13) = 1;   // LED OFF (n?u board BluePill vì LED ngu?c)
        delay(500000);
        PCout(13) = 0;   // LED ON
        delay(500000);
		
    }
		return 0;
}
