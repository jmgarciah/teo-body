// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "InCvPort.hpp"

namespace teo
{

/************************************************************************/

void InCvPort::onRead(Bottle& b) {
//    if ( ! follow ) return;
    if (b.size() < 3) return;

    double x = b.get(0).asDouble();
    double y = b.get(1).asDouble();
    double z = b.get(2).asDouble();

/*    double x1, x2, x3, x4;
    double y1, y2, y3, y4;

    x4 = x3;
    x3 = x2;
    x2 = x1;
    x1 = x;

    y4 = y3;
    y3 = y2;
    y2 = y1;
    y1 = y;

    x_tmp = ((x1 + x2 + x3 + x4) / 4);
    y_tmp = ((y1 + y2 + y3 + y4) / 4); 

    double x_tmp, y_tmp,;
*/

    printf("%f %f %f\n",x,y,z);

    if( x > -150 ) iVelocityControl->velocityMove(0, 5); //Id motor. Velocity [deg/s].
    if( x > -170 ) iVelocityControl->velocityMove(0, 2);
    if( x > -190 ) iVelocityControl->velocityMove(0, 1);
    if( x < -220 ) iVelocityControl->velocityMove(0, -1);
    if( x < -240 ) iVelocityControl->velocityMove(0, -2);
    if( x < -260 ) iVelocityControl->velocityMove(0, -5);
    //
    if( y > -190 ) iVelocityControl->velocityMove(0, 5);
    if( y > -210 ) iVelocityControl->velocityMove(0, 2);
    if( y > -230 ) iVelocityControl->velocityMove(0, 1);
    if( y < -270 ) iVelocityControl->velocityMove(0, -1);
    if( y < -290 ) iVelocityControl->velocityMove(0, -2);
    if( y < -310 ) iVelocityControl->velocityMove(0, -5);

/*
    if( x > -150 ) iPositionControl->relativeMove(0, 4);
    if( x > -170 ) iPositionControl->relativeMove(0, 2);
    if( x > -190 ) iPositionControl->relativeMove(0, 1);
    if( x < -220 ) iPositionControl->relativeMove(0, -1);
    if( x < -240 ) iPositionControl->relativeMove(0, -2);
    if( x < -260 ) iPositionControl->relativeMove(0, -4);
    //
    if( y > -190 ) iPositionControl->relativeMove(1, 4);
    if( y > -210 ) iPositionControl->relativeMove(1, 2);
    if( y > -230 ) iPositionControl->relativeMove(1, 1);
    if( y < -270 ) iPositionControl->relativeMove(1, -1);
    if( y < -290 ) iPositionControl->relativeMove(1, -2);
    if( y < -310 ) iPositionControl->relativeMove(1, -4);
*/

}

/************************************************************************/

void InCvPort::setFollow(bool value)
{
    follow = value;
}

/************************************************************************/

}  // namespace teo

