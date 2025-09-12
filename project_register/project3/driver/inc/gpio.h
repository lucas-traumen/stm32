#ifndef _GPIO_H_
#define _GPIO_H_

#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h" 
#include "Device/Include/stm32f10x.h"   // Device header
#include "RTE_Device.h"                 // Keil::Device:Startup

#ifdef __cplusplus
 extern "C" {
#endif
	 
void Writepin(GPIO_TypeDef *gpio, uint16_t pin,uint8_t mode);
uint8_t Readpin(GPIO_TypeDef *gpio, uint16_t pin);
void Togglepin(GPIO_TypeDef *gpio, uint16_t pin);
	 
#ifdef __cplusplus
}
#endif


#endif



