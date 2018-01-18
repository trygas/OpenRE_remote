/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: robot_top.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1    V1.0          creat this file
* mawenke       2015.7.1     V2.0          update this file
* Description:
***********************************************************************************************************************/
#include "remote_control.h"

/***********************************************************************************************************************
* Function:     void RobotControl::RobotControlCall(void)
*
* Scope:        public
*
* Description:  robot control interface, you must call it in a frequency , generaly  can set
*               be a half of pid frequency
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RemoteControl::call(void)
{
    datatUpdate();

    if(hf_link_node != NULL)
    {
        hfLinkNodeEvent(hf_link_node);
    }
        
//    oled.OLED_Show_Str(0,2,(unsigned char *)float2str(robot->measure_robot_speed.x,2,(char*)robot_speed.robot_x),0x01);
//    oled.OLED_Show_Str(36,2,(unsigned char *)float2str(robot->measure_robot_speed.y,2,(char*)robot_speed.robot_y),0x01);
//    oled.OLED_Show_Str(72,2,(unsigned char *)float2str(robot->measure_robot_speed.z,2,(char*)robot_speed.robot_z),0x01);

//   oled.OLED_Show_Str(0,6,(unsigned char *)float2str(robot->measure_global_speed.x,2,(char*)robot_speed.robot_x),0x01);
//    oled.OLED_Show_Str(36,6,(unsigned char *)float2str(robot->measure_global_speed.y,2,(char*)robot_speed.robot_y),0x01);
//    oled.OLED_Show_Str(72,6,(unsigned char *)float2str(robot->measure_global_speed.z,2,(char*)robot_speed.robot_z),0x01);

    remote.call();   
    hf_link_node->masterSendCommand(SET_ROBOT_SPEED);
}

void RemoteControl::hfLinkNodeEvent(HFLink* hf_link_node_)
{
    if(hf_link_node_->receive_package_renew[SET_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_MOTOR_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_CHASSIS_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_CHASSIS_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_HEAD_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_HEAD_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SAVE_HEAD_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_HEAD_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_ARM_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_ARM_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SAVE_ARM_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_ARM_PARAMETERS]=0;

    }
    if( hf_link_node_->receive_package_renew[SET_GLOBAL_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_GLOBAL_SPEED]=0;

    }
    if( hf_link_node_->receive_package_renew[SET_ROBOT_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_ROBOT_SPEED ]=0;

    }
    if( hf_link_node_->receive_package_renew[SET_MOTOR_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_MOTOR_SPEED] = 0;

    }
    if(hf_link_node_->receive_package_renew[CLEAR_COORDINATE_DATA]==1)
    {
        hf_link_node_->receive_package_renew[CLEAR_COORDINATE_DATA]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_HEAD_STATE]==1)
    {
        hf_link_node_->receive_package_renew[SET_HEAD_STATE]=0;

    }
    if( hf_link_node_->receive_package_renew[SET_ARM_STATE]==1 ){
        hf_link_node_->receive_package_renew[SET_ARM_STATE]=0;

    }
}

/***********************************************************************************************************************
* Function:     void RobotControl::datatUpdate(void)
*
* Scope:        private
*
* Description:  update the robot RobotAbstract ,only need a low call frequency , 20HZ is recommended
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RemoteControl::datatUpdate(void)
{
    //system info
    robot->system_info.battery_voltage = Board::getInstance()->battery_voltage;
    robot->system_info.cpu_temperature = Board::getInstance()->cpu_temperature;
    robot->system_info.cpu_usage = Board::getInstance()->cpu_usage;
    robot->system_info.system_time = Board::getInstance()->system_time;
    robot->system_info.power_remain = 1;
}


