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
    printf("%f %f %f\n",x,y,z);
    if( x > -200 ) iPositionControl->relativeMove(0, 1);
    if( x < -210 ) iPositionControl->relativeMove(0, -1);
    //
    if( y > -240 ) iPositionControl->relativeMove(1, 1);
    if( y < -260 ) iPositionControl->relativeMove(1, -1);

}

/************************************************************************/

void InCvPort::setFollow(bool value)
{
    follow = value;
}

/************************************************************************/

}  // namespace teo

