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

    if( x > -150 ) {
        iVelocityControl->velocityMove(0, 8.0); //Id motor. Velocity [deg/s].
    }
    else if( x > -170 && x < -150) {
        iVelocityControl->velocityMove(0, 3.0);
    }
    else if( x > -190 && x < -170 ) {
        iVelocityControl->velocityMove(0, 1.0);
    }
    else if( x > -220 && x < -190 ) {
        iVelocityControl->velocityMove(0, 0.0);
    }
    else if( x < -220 && x > -240 ) {
        iVelocityControl->velocityMove(0, -1.0);
    }
    else if( x < -240 && x > -260 ) {
        iVelocityControl->velocityMove(0, -3.0);
    }
    else if( x < -260 ) {
        iVelocityControl->velocityMove(0, -8.0);
    }

    if( y > -190 ) {
        iVelocityControl->velocityMove(0, 8.0); //Id motor. Velocity [deg/s].
    }
    else if( y > -210 && x < -190) {
        iVelocityControl->velocityMove(0, 3.0);
    }
    else if( y > -230 && x < -210 ) {
        iVelocityControl->velocityMove(0, 1.0);
    }
    else if( y > -270 && x < -220 ) {
        iVelocityControl->velocityMove(0, 0.0);
    }
    else if( y < -270 && x > -290 ) {
        iVelocityControl->velocityMove(0, -1.0);
    }
    else if( y < -290 && x > -310 ) {
        iVelocityControl->velocityMove(0, -3.0);
    }
    else if( y < -310 ) {
        iVelocityControl->velocityMove(0, -8.0);
    }

}

/************************************************************************/

void InCvPort::setFollow(bool value)
{
    follow = value;
}

/************************************************************************/

}  // namespace teo

