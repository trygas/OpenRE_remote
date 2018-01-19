/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: BSP_TOP.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2016.7.1    V2.0           creat this file
*
***********************************************************************************************************************/

#include "board.h"

Board::Board() : BoardAbstract()
{
    battery_voltage_alarm_ = 10.50 ;
    battery_proportion_ = 11.00 ;

#ifndef DEBUG_PRINTF_INTERFACE
    device_type[USART_DEBUG] = 0x10;    
#else
    if(DEBUG_PRINTF_INTERFACE == 1){
        device_type[USART_DEBUG] = 0x10;
    }
    else if(DEBUG_PRINTF_INTERFACE == 2){
        device_type[USART_DEBUG] = 0x20;
    }
    else if(DEBUG_PRINTF_INTERFACE == 3){
        device_type[USART_DEBUG] = 0x30;
    }
    else if(DEBUG_PRINTF_INTERFACE == 4){
        device_type[USART_DEBUG] = 0x40;
    }
    else if(DEBUG_PRINTF_INTERFACE == 5){
        device_type[USART_DEBUG] = 0x50;
    }
    else if(DEBUG_PRINTF_INTERFACE == 6){
        device_type[USART_DEBUG] = 0x60;
    }
    else { device_type[USART_DEBUG] = 0x10;}
#endif

#ifndef PC_INTERFACE
    device_type[USART_PC] = 0x10;
#else
    if(PC_INTERFACE == 1){
        device_type[USART_PC] = 0x10;
    }
    else if(PC_INTERFACE == 2){
        device_type[USART_PC] = 0x20;
    }
    else if(PC_INTERFACE == 3){
        device_type[USART_PC] = 0x30;
    }
    if(PC_INTERFACE == 4){
        device_type[USART_PC] = 0x40;
    }
    else if(PC_INTERFACE == 5){
        device_type[USART_PC] = 0x50;
    }
    else if(PC_INTERFACE == 6){
        device_type[USART_PC] = 0x60;
    }
    else { device_type[USART_PC] = 0x10;}
#endif

#ifndef RADIO_INTERFACE
    device_type[USART_RADIO] = 0x40;
#else
    if(RADIO_INTERFACE == 1){
        device_type[USART_RADIO] = 0x10;
    }
    else if(RADIO_INTERFACE == 2){
        device_type[USART_RADIO] = 0x20;
    }
    else if(RADIO_INTERFACE == 3){
        device_type[USART_RADIO] = 0x30;
    }
    else if(RADIO_INTERFACE == 4){
        device_type[USART_RADIO] = 0x40;
    }
    else if(RADIO_INTERFACE == 5){
        device_type[USART_RADIO] = 0x50;
    }
    else if(RADIO_INTERFACE == 6){
        device_type[USART_RADIO] = 0x60;
    }
    else { device_type[USART_RADIO] = 0x40;}
#endif

    device_type[USART_GPS] = 0x32;
    device_type[USART_SBUS] = 0x21;
    device_type[USART_DIGITAL_SERVO] = 0x32;
    device_type[USART_IMU] = 0x50;
    device_type[IIC_IMU] = 0x40;
    device_type[IIC_AT24CXX] = 0x10;
    device_type[IIC_OLED] = 0x00;
    device_type[SPI_IMU] = 0x00;
    device_type[SPI_NRF24L01] = 0x00;
    device_type[SPI_LCD] = 0x00;
    device_type[CAN_IMU] = 0x00;
    device_type[CAN_PAN_AND_TILT] = 0x00;
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::ledInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOC , &GPIO_InitStruct);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA , &GPIO_InitStruct);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB , &GPIO_InitStruct);
}

void Board::setLedState(uint8_t led_id, uint8_t operation)
{
    if ( led_id == 0){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_6);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_6);}
        else if(operation == 2){GPIO_ToggleBits(GPIOC , GPIO_Pin_6);}
    }

    if ( led_id == 1){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_8);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_8);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_8);}
    }

    if ( led_id == 2){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_9);}
        if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_9);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_9);}
    }

    if ( led_id == 3){
        if(operation == 0) { GPIO_SetBits(GPIOA , GPIO_Pin_15);}
        if(operation == 1) { GPIO_ResetBits(GPIOA , GPIO_Pin_15);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOA , GPIO_Pin_15);}
    }

    if ( led_id == 4){
        if(operation == 0) { GPIO_SetBits(GPIOB , GPIO_Pin_15);}
        if(operation == 1) { GPIO_ResetBits(GPIOB , GPIO_Pin_15);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOB , GPIO_Pin_15);}
    }
}

void Board::beepInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
}

void Board::setBeepState(uint8_t operation)
{
    if(operation == 0) { GPIO_ResetBits(GPIOA , GPIO_Pin_1);}
    else if(operation == 1) { GPIO_SetBits(GPIOA , GPIO_Pin_1);}
    else if(operation == 2) { GPIO_ToggleBits(GPIOA , GPIO_Pin_1);}
}

void Board::keyInit(void)
{

}

void Board::keyStateRenew(void)
{

}

/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::motorInterfaceInit(uint8_t mode , uint8_t motor_id , float motor_pwm_t)
{
   
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::motorEnable(uint8_t mode , uint8_t motor_id)
{
 
}

void Board::motorDisable(uint8_t mode , uint8_t motor_id)
{
  
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::motorSetPWM(uint8_t mode , uint8_t motor_id , int pwm_value)
{
   
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
float Board::getMotorEncoderCNT(uint8_t motor_id)
{
    return 0;
}

float Board::getMotorCurrent(uint8_t motor_id)
{
    return 0;
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::axServoInterfaceInit(void)
{

}

void Board::axServoTxModel(void)
{

}

void Board::axServoRxModel(void)
{

}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void Board::pwmInterfaceInit(uint8_t channel_x , uint8_t mode)
{
    return;
}

void Board::setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value)
{
    return;
}

uint16_t Board::readPWMInterfaceValue(uint8_t channel_x)
{

}

/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/

void Board::adcInit(void)
{
    HF_ADC_Moder_Init(0xAf00, 6, 3.3);  //ADC init
}

void Board::timerInit(void)
{
    HF_Timer_Init(TIM6 , 1000);  //timer6 init , 1000us
}

float Board::getBatteryVoltage(void)
{
    //0.33 is the loss voltage of diode
    battery_voltage_ = 0.8f * battery_voltage_+ 0.2f*(float)(0.33f + HF_Get_ADC_Output(1) * battery_proportion_ );
    return battery_voltage_ ;
}

void Board::getCPUInfo(void)
{
    //get ID of CPU and capacity of Flash
    chipUniqueID[0]  = *(__IO u32 *)(0X1FFFF7F0); // MSB
    chipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC);  //
    chipUniqueID[2] = *(__IO u32 *)(0X1FFFF7E8);  // LSB
    flashSize =  *(__IO u16 *)(0X1FFFF7E0);       //Unit:KB
}
