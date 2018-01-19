#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "board_abstract.h"
#include "robot_abstract.h"
#include "usart.h"

class Bluetooth
{
public:
    Bluetooth()
    {

    }

    void init()
    {
        bluetoothInit();
        bluetoothControl(1);
    }

private:
    void bluetoothInit(void);
    void bluetoothControl(bool key);
};

#endif // CHASSIS_H
