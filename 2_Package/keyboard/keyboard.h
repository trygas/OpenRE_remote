#ifndef KEYBOARD
#define KEYBOARD

#include "board_abstract.h"
#include "remote_parameters.h"
#include "adc_dac.h"

class Keyboard
{
public:
    Keyboard()
    {

    }

    void init()
    {
        modelswitchInit();
        keyboardInit();
    }

    void call();

public:
    RemoteControlVoltage out_remote_control_voltage;

private:
    RemoteControlVoltage remote_control_voltage;
    char modelswitch[2];
    char keyboard[6];

private:
    void dataUpdate(void);
    void modelswitchChoose(void);
    void modelswitchInit(void);
    void keyboardInit(void);
    void getKeyboardVoltage(void);
    void getRemoteVoltage(void);
};

#endif
