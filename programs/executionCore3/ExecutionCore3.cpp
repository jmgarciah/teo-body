// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "ExecutionCore3.hpp"
#include "InCvPort.hpp"

namespace teo
{

/************************************************************************/

bool ExecutionCore3::configure(ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("ExecutionCore3 options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("ExecutionCore1 using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //
    Property headOptions;
    headOptions.put("device","remote_controlboard");
    headOptions.put("local","/executionCore3/head");
    headOptions.put("remote","/teo/head");
    headDevice.open(headOptions);
    if( ! headDevice.isValid() ) {
        printf("head remote_controlboard instantiation not worked.\n");
        return false;
    }

//    yarp::dev::IVelocityControl *iVelocityControl;
    if( ! headDevice.view(iVelocityControl) ) {
        printf("view(iVelocityControl) not worked.\n");
        return false;
    }
//    inCvPort.setIVelocityControl(iVelocityControl);
    iVelocityControl->setVelocityMode();
    inCvPort.setIVelocityControl(iVelocityControl);
    //-----------------OPEN LOCAL PORTS------------//
 //   inSrPort.setInCvPortPtr(&inCvPort);
    inCvPort.useCallback();
 //   inSrPort.useCallback();
 //   inSrPort.open("/executionCore3/dialogueManager/command:i");
    inCvPort.open("/executionCore3/cv/state:i");

    return true;
}

/************************************************************************/
double ExecutionCore3::getPeriod() {
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/
bool ExecutionCore3::updateModule() {
    //printf("StateMachine in state [%d]. ExecutionCore1 alive...\n", stateMachine.getMachineState());
    return true;
}

/************************************************************************/

bool ExecutionCore3::interruptModule() {
    printf("ExecutionCore3 closing...\n");
    inCvPort.disableCallback();
//    inSrPort.disableCallback();
    inCvPort.interrupt();
//    inSrPort.interrupt();
    inCvPort.close();
//    inSrPort.close();
    return true;
}

/************************************************************************/

}  // namespace teo
