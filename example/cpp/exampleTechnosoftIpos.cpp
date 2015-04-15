// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 * @ingroup teo_body_examples_cpp
 * \defgroup exampleTechnosoftIpos exampleTechnosoftIpos
 *
 * @brief This example.
 *
 * <b>Legal</b>
 *
 * Copyright: (C) 2010 Universidad Carlos III de Madrid;
 *            (C) 2010 RobotCub Consortium
 *
 * Author: Juan G Victores
 *
 * Contribs: Paul Fitzpatrick and Giacomo Spigler (YARP dev/motortest.cpp example)
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see license/LGPL.TXT
 *
 * <b>Building</b>
\verbatim
cd example/cpp
mkdir build; cd build; cmake ..
make -j3
\endverbatim
 *
 * <b>Running</b>
\verbatim
./exampleTechnosoftIpos
\endverbatim
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

int main(int argc, char *argv[]) {

    yarp::os::Network yarp;
    if (! yarp::os::Network::checkNetwork() ) {
        printf("Please start a yarp name server first\n");
        return(-1);
    }
    yarp::os::Property options;
    options.put("device","TechnosoftIpos");
    yarp::dev::PolyDriver dd(options);
    if(!dd.isValid()) {
      printf("RaveBot device not available.\n");
	  dd.close();
      yarp::os::Network::fini();
      return 1;
    }

    yarp::dev::IPositionControl *pos;
    bool ok = dd.view(pos);
    if (!ok) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] Acquired robot interface\n");
    pos->setPositionMode();

    printf("test positionMove(1,-35)\n");
    pos->positionMove(1, -35);

    printf("Delaying 5 seconds...\n");
    yarp::os::Time::delay(5);

    yarp::dev::IEncoders *enc;
    ok = dd.view(enc);

    yarp::dev::IVelocityControl *vel;
    ok = dd.view(vel);
    vel->setVelocityMode();
    printf("test velocityMove(0,10)\n");
    vel->velocityMove(0,10);

    printf("Delaying 5 seconds...\n");
    yarp::os::Time::delay(5);

    return 0;
}

