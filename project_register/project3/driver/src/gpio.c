#include "gpio.h"





void Writepin(GPIO_TypeDef *gpio, uint16_t pin ,uint8_t mode)
{
    if(mode ==0){
        GPIO_ResetBits(gpio,pin);
    }else{
				GPIO_SetBits(gpio,pin);
    }  
}
uint8_t Readpin(GPIO_TypeDef *gpio, uint16_t pin)
{
	return GPIO_ReadInputDataBit(gpio,pin);
}
void Togglepin(GPIO_TypeDef *gpio, uint16_t pin)
{
     gpio->ODR ^= pin;

}

