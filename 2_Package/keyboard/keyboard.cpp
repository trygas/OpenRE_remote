#include "keyboard.h"

void Keyboard::call()
{
    modelswitchChoose();
    dataUpdate();
}

void Keyboard::dataUpdate(void)
{
    if(modelswitch[0] == 1)
    {
        getRemoteVoltage();
        printf("remote\n");

        if(remote_control_voltage.right_y > 1.0) out_remote_control_voltage.right_y = remote_control_voltage.right_y -1.0;
        else if(remote_control_voltage.right_y < 0.6) out_remote_control_voltage.right_y = remote_control_voltage.right_y -0.6;
        else  out_remote_control_voltage.right_y = 0;

        if(remote_control_voltage.left_y > 1.0) out_remote_control_voltage.left_y = remote_control_voltage.left_y-1.0;
        else if(remote_control_voltage.left_y < 0.6) out_remote_control_voltage.left_y = remote_control_voltage.left_y-0.6;
        else remote_control_voltage.left_y = 0;

        if(remote_control_voltage.right_x > 1.0) out_remote_control_voltage.right_x = remote_control_voltage.right_x-1.0;
        else if(remote_control_voltage.right_x < 0.6) out_remote_control_voltage.right_x = remote_control_voltage.right_x-0.6;
        else out_remote_control_voltage.right_x = 0;

        out_remote_control_voltage.right_y *= 2;
        out_remote_control_voltage.left_y *= 2;
        out_remote_control_voltage.right_x *= 2;
    }
    else
    {
        getKeyboardVoltage();
        printf("keyboard\n");

        if(keyboard[0] == 0) out_remote_control_voltage.right_y = 1;
        else if(keyboard[2] == 0) out_remote_control_voltage.right_y = -1;
        else out_remote_control_voltage.right_y = 0;

        if(keyboard[1] == 0) out_remote_control_voltage.right_x = 1;
        else if(keyboard[3] == 0) out_remote_control_voltage.right_x = -1;
        else out_remote_control_voltage.right_x = 0;

        out_remote_control_voltage.left_y = 0;
    }
}

void Keyboard::getRemoteVoltage()
{
    remote_control_voltage.right_x = HF_Get_ADC_Output(1);
    remote_control_voltage.right_y = HF_Get_ADC_Output(2);
    remote_control_voltage.left_x = HF_Get_ADC_Output(3);
    remote_control_voltage.left_y = HF_Get_ADC_Output(4);
    remote_control_voltage.slide_rheostat = HF_Get_ADC_Output(6);
}

void Keyboard::getKeyboardVoltage()
{
    keyboard[0] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
    keyboard[1] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
    keyboard[2] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
    keyboard[3] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
    keyboard[4] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3);
    keyboard[5] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
}

void Keyboard::keyboardInit()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Keyboard::modelswitchChoose()
{
    modelswitch[0] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
    modelswitch[1] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
}

void Keyboard::modelswitchInit()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}
