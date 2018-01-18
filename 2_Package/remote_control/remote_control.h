#ifndef REMOTE_TOP_H
#define REMOTE_TOP_H

//#include "imu_top.h"
#include "oled_iic_driver.h"
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
        unsigned char robot_speed[] = "robot speed:";
        unsigned char global_speed[] = "global speed:";
        robot =NULL;
        hf_link_node = NULL;

        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        oled.OLED_Show_Str(0,0,robot_speed,0x01);
        oled.OLED_Show_Str(0,4,global_speed,0x01);
    }

char * float2str(float val, int precision, char *buf)  
{  
    char *cur, *end;  
      
    sprintf(buf, "%.6f", val);  
    if (precision < 6) {  
        cur = buf + strlen(buf) - 1;  
        end = cur - 6 + precision;   
        while ((cur > end) && (*cur == '0')) {  
            *cur = '\0';  
            cur--;  
        }  
    }  
    return buf;  
}  

public:
    static RemoteControl* getInstance()
    {
       static RemoteControl instance;
       return &instance;
    }

    void init(RobotAbstract* robot_)
    {
        robot = robot_;
        oled.OLED_Init();
        remote.init(robot);
    }
    void call(void);

    void setHFLinkNodePointer(HFLink* hf_link_node_)
    {
        hf_link_node_device = (DeviceType)hf_link_node_->port_num;
        hf_link_node = hf_link_node_ ;
    }
 
public:
    HFLink* hf_link_node;
    DeviceType hf_link_node_device;

private:
    RobotAbstract* robot;
    void hfLinkNodeEvent(HFLink* hf_link_node_);
    void datatUpdate(void);
    OLED oled;
    Remote remote;
    float degree_to_radian ,  radian_to_degree;
    RemoteControlSpeed robot_speed ;
    RemoteControlSpeed global_speed;
};

#endif  // #ifndef ROBOT_TOP_H

