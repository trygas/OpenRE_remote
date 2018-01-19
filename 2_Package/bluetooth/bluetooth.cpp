#include "bluetooth.h"

void Bluetooth::bluetoothInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}

void Bluetooth::bluetoothControl(bool key)
{
    if(key != 0)
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
    else
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}
