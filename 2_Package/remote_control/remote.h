#ifndef REMOTE_H
#define REMOTE_H

#include "board_abstract.h"
#include "robot_abstract.h"
#include "bluetooth/bluetooth.h"
#include "remote_parameters.h"
#include "keyboard.h"

class Remote
{
public:
    Remote()
    {
        robot = NULL;
    }

    void init(RobotAbstract* robot_, double _maxspeed)
    {
        maxSpeed = _maxspeed;
        robot = robot_;
        keyboard.init();
        bluetooth.init();
    }

    void call(void);
    void getExpectRobotSpeed(void);
    void updataRobotSpeed(void);
    void updataGlobalSpeed(void);
    void clearCoordData(void);

private:
    void datatUpdate(void);

private:
    RobotAbstract* robot;
    Keyboard keyboard;
    Bluetooth bluetooth;
    double maxSpeed;
};

#endif // CHASSIS_H
