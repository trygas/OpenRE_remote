#ifndef REMOTE_PARAMETERS_H
#define REMOTE_PARAMETERS_H

typedef struct {
    float right_x;
    float right_y;
    float left_x;
    float left_y;
    float slide_rheostat;
}RemoteControlVoltage;

typedef struct {
    unsigned char robot_x[4];
    unsigned char robot_y[4];
    unsigned char robot_z[4];
}RemoteControlSpeed;

typedef struct {
    float  x;
    float  y;
    float  z;
}RemoteCoord;

#endif // REMOTE_PARAMETERS_H
