// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "LacqueyFetch.hpp"

// ------------------ IEncodersRaw Related -----------------------------------------

bool teo::LacqueyFetch::resetEncoderRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    return this->setEncoderRaw(j,0);
}

// -----------------------------------------------------------------------------

bool teo::LacqueyFetch::setEncoderRaw(int j, double val) {  // encExposed = val;
    CD_INFO("(%d,%f)\n",j,val);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (LacqueyFetch).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::LacqueyFetch::getEncoderRaw(int j, double *v) {
    //CD_INFO("%d\n",j);  //-- Too verbose in stream.

    //-- Check index within range
    if ( j != 0 ) return false;

    encoderReady.wait();
    *v = encoder;
    encoderReady.post();

    return true;
}

// -----------------------------------------------------------------------------

bool teo::LacqueyFetch::getEncoderSpeedRaw(int j, double *sp) {
    //CD_INFO("(%d)\n",j);  //-- Too verbose in controlboardwrapper2 stream.

    //-- Check index within range
    if ( j != 0 ) return false;

    //CD_WARNING("Not implemented yet (LacqueyFetch).\n");  //-- Too verbose in controlboardwrapper2 stream.
    *sp = 0;

    return true;
}

// -----------------------------------------------------------------------------

bool teo::LacqueyFetch::getEncoderAccelerationRaw(int j, double *spds) {
    //CD_INFO("(%d)\n",j);  //-- Too verbose in controlboardwrapper2 stream.

    //-- Check index within range
    if ( j = 0 ) return false;

    //CD_WARNING("Not implemented yet (LacqueyFetch).\n");  //-- Too verbose in controlboardwrapper2 stream.
    *spds = 0;

    return true;
}

// -----------------------------------------------------------------------------

