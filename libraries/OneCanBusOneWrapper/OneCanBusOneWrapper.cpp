// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "OneCanBusOneWrapper.hpp"

namespace teo
{

/************************************************************************/
OneCanBusOneWrapper::OneCanBusOneWrapper() { }

/************************************************************************/
bool OneCanBusOneWrapper::configure(ResourceFinder &rf) {

    if(rf.check("help")) {
        printf("OneCanBusOneWrapper options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        CD_DEBUG_NO_HEADER("%s\n",rf.toString().c_str());
        return false;
    }

    //################# MY MODIFICATIONS ######################

       // Print the content of ResourceFinder
       printf("CONTENT OF ResourceFinder OBJECT:\n%s\n\n",rf.toString().c_str());

       CD_DEBUG("MODE PASSED FOR PARAMETERS: %s\n", rf.find("mode").asString().c_str());

       // Variable that stores the mode
           std::string mode = rf.check("mode",Value("position"),"position/velocity mode").asString();
           CD_DEBUG("La variable MODE contiene: %s\n", mode.c_str());

    //#########################################################


    //-- /dev/can0 --
    Bottle devCan0 = rf.findGroup("devCan0");
    CD_DEBUG("%s\n",devCan0.toString().c_str());
    Property optionsDevCan0;
    optionsDevCan0.fromString(devCan0.toString());
    deviceDevCan0.open(optionsDevCan0);
    if (!deviceDevCan0.isValid()) {
        CD_ERROR("deviceDevCan0 instantiation not worked.\n");
        return false;
    }

    //-- wrapper0 --
    Bottle wrapper0 = rf.findGroup("wrapper0");
    CD_DEBUG("%s\n",wrapper0.toString().c_str());
    Property optionsWrapper0;
    optionsWrapper0.fromString(wrapper0.toString());
    deviceWrapper0.open(optionsWrapper0);
    if (!deviceWrapper0.isValid()) {
        CD_ERROR("deviceWrapper0 instantiation not worked.\n");
        return false;
    }

    IMultipleWrapper *iWrapper0;

    deviceWrapper0.view(iWrapper0);

    PolyDriverList list;
    list.push(&deviceDevCan0, "devCan0");
    iWrapper0->attachAll(list);

    return true;
}

/************************************************************************/

bool OneCanBusOneWrapper::updateModule() {
    //printf("OneCanBusOneWrapper alive...\n");
    return true;
}

/************************************************************************/

bool OneCanBusOneWrapper::close() {
    deviceWrapper0.close();

    deviceDevCan0.close();

    return true;
}

/************************************************************************/

}  // namespace teo
