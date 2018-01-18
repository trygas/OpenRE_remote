#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "board_abstract.h"
#include "robot_abstract.h"
#include "usart.h"

class Bluetooth
{
public:
    Bluetooth()
    {

    }

    void init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
    {
        GPIOX = GPIOx;
        GPIO_PIN = GPIO_Pin;
        bluetoothinit();
        for(int i = 0; i < 7; i++)
        {
            printf("%s ", Bluetoothmessage[i]);
            HF_USART_SendChar(1, Bluetoothmessage[i]);
            delay_ms(400);
        }
        bluetoothcontrol(1);
    }

private:
    void bluetoothinit(void)
    {
        GPIO_InitTypeDef  GPIO_InitStruct;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
        GPIO_InitStruct.GPIO_Pin = GPIO_PIN;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOX, &GPIO_InitStruct);
        GPIO_ResetBits(GPIOX, GPIO_PIN);
    }

    void bluetoothcontrol(bool key)
    {
        if(key != 0)
            GPIO_SetBits(GPIOX, GPIO_PIN);
        else
            GPIO_ResetBits(GPIOX, GPIO_PIN);
    }
    GPIO_TypeDef* GPIOX;
    uint16_t GPIO_PIN;
    unsigned char Bluetoothmessage[10][30]={
        "AT+PARI=0\r\n",                         // 0:无校验             1:EVEN    2:ODD   Default: 0 串口校验
        "AT+STOP=0\r\n",                        // 0:1停止位            1:2停止位         Default: 0 停止位
        "AT+NAME=hello\r\n",          // 最长 20 位数字或字母,含中划线和下划线,不建议用其它字符。 Default:BLECOM
        "AT+ROLE=M\r\n",                       //M: 主设备 S: 从设备 主从模式
        "AT+PASS=000000\r\n",              //x: 000000~999999 Default:000000 设置密码
        "AT+AUTH=0\r\n",                         //0: 连接不需要密码 1: 连接需要密码 Default: 0
        "AT+BAUD=115200\r\n"
    };
};

#endif // CHASSIS_H
