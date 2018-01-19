#ifndef REMOTE_TOP_H
#define REMOTE_TOP_H

//#include "imu_top.h"
#include "robot_abstract.h"
#include "board.h"
#include "board_abstract.h"
#include "remote_parameters.h"
#include "remote.h"
#include "hf_link.h"
#include <stdlib.h>
#include <stdio.h>

class RemoteControl
{
private:
    RemoteControl()
    {
        robot =NULL;
        hf_link_node = NULL;
    }

public:
    static RemoteControl* getInstance()
    {
       static RemoteControl instance;
       return &instance;
    }

    void init(RobotAbstract* robot_, double _maxspeed)
    {
        robot = robot_;
        remote.init(robot, _maxspeed);
    }

    void setHFLinkNodePointer(HFLink* hf_link_node_)
    {
        hf_link_node_device = (DeviceType)hf_link_node_->port_num;
        hf_link_node = hf_link_node_ ;
    }
 
    void call(void);

public:
    HFLink* hf_link_node;
    DeviceType hf_link_node_device;

private:
    RobotAbstract* robot;
    void hfLinkNodeEvent(HFLink* hf_link_node_);
    void datatUpdate(void);
    Remote remote;
};

#endif  // #ifndef ROBOT_TOP_H

