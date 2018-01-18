/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: chassis.cpp
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

#include "remote.h"
#include "remote_control.h"
#include "remote_parameters.h"

#define sudo 0.4

void Remote::call(void)
{
    if(robot == NULL) return;
    modelswitchchoose();
    keyboardchoose();
    datatUpdate(&remote_control_voltage, &remote_control_speed);

    printf("%f %f\n", robot->expect_robot_speed.x, robot->expect_robot_speed.z);
}

void Remote::getExpectRobotSpeed(RemoteControlVoltage *remote_control_voltage, RemoteControlSpeed *remote_control_speed)
{
    if(remote_control_voltage->right_y > 1.0) robot->expect_robot_speed.x = remote_control_voltage->right_y -1.0;
    else if(remote_control_voltage->right_y < 0.6) robot->expect_robot_speed.x = remote_control_voltage->right_y -0.6;
    else robot->expect_robot_speed.x = 0;

    if(remote_control_voltage->left_y > 1.0) robot->expect_robot_speed.y = remote_control_voltage->left_y-1.0;
    else if(remote_control_voltage->left_y < 0.6) robot->expect_robot_speed.y = remote_control_voltage->left_y-0.6;
    else robot->expect_robot_speed.y = 0;

    if(remote_control_voltage->right_x > 1.0) robot->expect_robot_speed.z = remote_control_voltage->right_x-1.0;
    else if(remote_control_voltage->right_x < 0.6) robot->expect_robot_speed.z = remote_control_voltage->right_x-0.6;
    else robot->expect_robot_speed.z = 0;

    robot->expect_robot_speed.x = robot->expect_robot_speed.x * sudo*2;
    robot->expect_robot_speed.y = - robot->expect_robot_speed.y * 0.2;
    robot->expect_robot_speed.z = -robot->expect_robot_speed.z * sudo*3.14*2;
}

void Remote::datatUpdate(RemoteControlVoltage *remote_control_voltage, RemoteControlSpeed *remote_control_speed)
{
    if(modelswitch[0] == 1)
    {
        printf("remote\n");
        getRemoteVoltage(remote_control_voltage);
        getExpectRobotSpeed(remote_control_voltage, remote_control_speed);
    }
    else
    {
        printf("keyboard\n");
        if(keyboard[0] == 0)  robot->expect_robot_speed.x = sudo;
        else if(keyboard[2] == 0)  robot->expect_robot_speed.x = -sudo;
        else robot->expect_robot_speed.x = 0;
        if(keyboard[1] == 0)  robot->expect_robot_speed.z = -sudo*3.14;
        else if(keyboard[3] == 0)  robot->expect_robot_speed.z = sudo*3.14;
        else robot->expect_robot_speed.z = 0;
        robot->expect_robot_speed.y = 0;
    }
}
