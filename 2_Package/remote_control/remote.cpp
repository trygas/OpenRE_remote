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

void Remote::call(void)
{
    if(robot == NULL) return;
    datatUpdate();

    printf("%f %f\n", robot->expect_robot_speed.x, robot->expect_robot_speed.z);
}

void Remote::datatUpdate(void)
{
    keyboard.call();
    getExpectRobotSpeed();
}

void Remote::getExpectRobotSpeed(void)
{
    robot->expect_robot_speed.x = maxSpeed * keyboard.out_remote_control_voltage.right_y;
    robot->expect_robot_speed.y = maxSpeed * keyboard.out_remote_control_voltage.left_y;
    robot->expect_robot_speed.z = maxSpeed * keyboard.out_remote_control_voltage.right_x * 3.14;
}

void Remote::updataRobotSpeed()
{
    robot->measure_robot_speed.x=0;
    robot->measure_robot_speed.y=0;
    robot->measure_robot_speed.z=0;
}

void Remote::updataGlobalSpeed()
{
    robot->measure_global_speed.x=0;
    robot->measure_global_speed.y=0;
    robot->measure_global_speed.z=0;
}

void Remote::clearCoordData()
{
    robot->measure_global_coordinate.x=0;
    robot->measure_global_coordinate.y=0;
    robot->measure_global_coordinate.z=0;
    robot->measure_robot_coordinate.x=0;
    robot->measure_robot_coordinate.y=0;
    robot->measure_robot_coordinate.z=0;
}
