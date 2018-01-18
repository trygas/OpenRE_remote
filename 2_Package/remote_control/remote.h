#ifndef REMOTE_H
#define REMOTE_H

#include "board_abstract.h"
#include "robot_abstract.h"
#include "bluetooth/bluetooth.h"
#include "remote_parameters.h"
#include "adc_dac.h"
#include "usart.h"

class Remote
{
public:
    Remote()
    {
        robot = NULL;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        call_frequency = 20;
    }

    void init(RobotAbstract* robot_  )
    {
        robot = robot_;
        memset(&remote_control_voltage , 0 , sizeof(remote_control_voltage));
        memset(&remote_control_speed , 0 , sizeof(remote_control_speed));
        keyboardinit();
        modelswitchinit();
        bluetooth.init(GPIOC, GPIO_Pin_7);
    }

    void call(void);

    void getExpectRobotSpeed(RemoteControlVoltage *remote_control_voltage, RemoteControlSpeed *remote_control_speed);

    void updataRobotSpeed(void)
    {
        robot->measure_robot_speed.x=0;
        robot->measure_robot_speed.y=0;
        robot->measure_robot_speed.z=0;
    }

    void updataGlobalSpeed(void)
    {
        robot->measure_global_speed.x=0;
        robot->measure_global_speed.y=0;
        robot->measure_global_speed.z=0;
    }

    void clearCoordData(void)
    {
        robot->measure_global_coordinate.x=0;
        robot->measure_global_coordinate.y=0;
        robot->measure_global_coordinate.z=0;
        robot->measure_robot_coordinate.x=0;
        robot->measure_robot_coordinate.y=0;
        robot->measure_robot_coordinate.z=0;
    }

public:
    RemoteControlSpeed remote_control_speed;

private:
    RemoteControlVoltage remote_control_voltage;
    RobotAbstract* robot;
    Bluetooth bluetooth;
    char modelswitch[2];
    char keyboard[6];
    float degree_to_radian ,  radian_to_degree;
    float call_frequency;
    float control_quality;

    void datatUpdate(RemoteControlVoltage *remote_control_voltage, RemoteControlSpeed *remote_control_speed);

    void modelswitchchoose(void)
    {
        modelswitch[0] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
        modelswitch[1] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
    }

    void modelswitchinit(void)
    {
        GPIO_InitTypeDef  GPIO_InitStruct;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
        //GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
    }

    void keyboardinit(void)
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

    void keyboardchoose(void)
    {
        keyboard[0] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
        keyboard[1] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
        keyboard[2] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
        keyboard[3] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
        keyboard[4] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3);
        keyboard[5] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
    }

    void getRemoteVoltage(RemoteControlVoltage* remotecontrolvoltage)
    {
        remotecontrolvoltage->right_x = HF_Get_ADC_Output(1);
        remotecontrolvoltage->right_y = HF_Get_ADC_Output(2);
        remotecontrolvoltage->left_x = HF_Get_ADC_Output(3);
        remotecontrolvoltage->left_y = HF_Get_ADC_Output(4);
        remotecontrolvoltage->slide_rheostat = HF_Get_ADC_Output(6);
    }
};

#endif // CHASSIS_H
