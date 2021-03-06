// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __CAN_BUS_HICO__
#define __CAN_BUS_HICO__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>  // just for ::write
#include <err.h>
#include <errno.h>
#include <assert.h>
#include <string>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#include "hico_api.h"

#include "ColorDebug.hpp"

using namespace yarp::os;
using namespace yarp::dev;

#define DEFAULT_CAN_DEVICE "/dev/can0"
#define DEFAULT_CAN_BITRATE BITRATE_1000k

#define DELAY 0.001  // Was DELAY2. Required when using same driver.

namespace teo
{

/**
 *
 * @ingroup CanBusHico
 * @brief Specifies the HicoCan (hcanpci) behaviour and specifications.
 *
 */
class CanBusHico : public DeviceDriver {

    public:

        /** Initialize the CAN device.
         * @param device is the device path, such as "/dev/can0".
         * @param bitrate is the bitrate, such as BITRATE_100k.
         * @return true/false on success/failure.
         */
        bool open(yarp::os::Searchable& config);

        /** Close the CAN device. */
        bool close();

        /**
         * Write message to the CAN buffer.
         * @param id Message's COB-id
         * @param len Data field length
         * @param msgData Data to send
         * @return true/false on success/failure.
         */
        bool sendRaw(uint32_t id, uint16_t len, uint8_t * msgData);

        /** Read data.
         * @return Number on got, 0 on timeout, and errno on fail. */
        int read_timeout(struct can_msg *buf, unsigned int timeout);

    protected:

        /** CAN file descriptor */
        int fileDescriptor;

        yarp::os::Semaphore canBusReady;

};

}  // namespace teo

#endif  // __CAN_BUS_HICO__

