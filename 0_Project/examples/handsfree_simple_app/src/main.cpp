/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:
***********************************************************************************************************************/

#include "main_config.h"
#include "stm32f10x_usart.h"
#include "board.h"
#include "stdlib.h"
#include "robot_model.h"
#include "remote_control/remote_control.h"
#include "hf_link.h"
#include "usart.h"

int main(void)
{
    Board *board = Board::getInstance();
    board->boardBasicInit();

    RobotModel robot_model;
    RobotAbstract robot;
    robot.para = robot_model;
    HFLink hf_link_pc_node(&robot , 0x01 , 0x11 , (unsigned char)USART_PC);
    HFLink hf_link_debug_node(&robot , 0x01 , 0x11 , (unsigned char)USART_DEBUG);

    RemoteControl *remote_control_p = RemoteControl::getInstance();
    remote_control_p->setHFLinkNodePointer(&hf_link_pc_node);
    remote_control_p->init(&robot, 0.4);
    printf("welcome to handsfree \r\n");

    while(1)
    {
//        if(board->usartDeviceReadData(remote_control_p->hf_link_node_device)->emptyCheck() == 0){
//            HF_USART_Put_Char(1, board->usartDeviceReadData(
//                                  remote_control_p->hf_link_node_device)->getData());
//        }
//        if(board->usartDeviceReadData(USART_DEBUG)->emptyCheck() == 0){
//            HF_USART_Put_Char(4, board->usartDeviceReadData(USART_DEBUG)->getData());
//        }
        if(board->usartDeviceReadData(remote_control_p->hf_link_node_device)->emptyCheck() == 0){
            remote_control_p->hf_link_node->byteAnalysisCall(
                        board->usartDeviceReadData(
                            remote_control_p->hf_link_node_device)->getData() );
        }

        if ( board->cnt_1ms >= 1 )    // 1000hz
        {
            //imu.topCall();
            board->cnt_1ms=0;
        }
        if ( board->cnt_2ms >= 2 )    // 500hz
        {
            board->cnt_2ms=0;
        }
        if ( board->cnt_5ms >= 5 )    // 200hz
        {
            board->cnt_5ms=0;
        }
        if ( board->cnt_10ms >= 10 )  // 100hz
        {
            board->cnt_10ms=0;
            //board->boardBasicCall();   // need time stm32f1 35us
        }
        if ( board->cnt_20ms >= 20 )  // 50hz
        {
            board->setLedState(0,2);
            board->setLedState(3,2);
            board->setLedState(2,2);
            board->setLedState(4,2);
            board->cnt_20ms = 0 ;
        }
        if ( board->cnt_50ms >= 50)  // 20hz
        {
            board->cnt_50ms = 0 ;
            remote_control_p->call();
            board->setLedState(1,2);
            //printf("battery_v = %.4f , temperature = %.4f \n" , board->battery_voltage , board->cpu_temperature);
        }
    }
}

