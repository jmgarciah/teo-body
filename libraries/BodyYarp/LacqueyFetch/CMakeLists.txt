# Copyright: (C) 2013 Universidad Carlos III de Madrid
# Author: Juan G. Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.6)

prepare_device(LacqueyFetch TYPE teo::LacqueyFetch INCLUDE LacqueyFetch.hpp)

IF (NOT SKIP_LacqueyFetch)

  find_package(YARP REQUIRED)

  # Include any directories needed for YARP
  include_directories(${YARP_INCLUDE_DIRS} ${TEO_BODY_INCLUDE_DIRS} ${COLOR_DEBUG_INCLUDE_DIRS})

  yarp_add_plugin(LacqueyFetch LacqueyFetch.cpp DeviceDriverImpl.cpp IControlLimitsRawImpl.cpp IControlModeRawImpl.cpp IEncodersRawImpl.cpp IEncodersTimedRawImpl.cpp IPositionControlRawImpl.cpp ICanBusSharerImpl.cpp )

  TARGET_LINK_LIBRARIES(LacqueyFetch ${YARP_LIBRARIES})
  install(TARGETS LacqueyFetch DESTINATION lib)

  # Exporting dependencies for TEO_BODYConfig.cmake quite manually for now... 
  set(TEO_BODY_LIBRARIES ${TEO_BODY_LIBRARIES} LacqueyFetch CACHE INTERNAL "appended libraries") 

ENDIF (NOT SKIP_LacqueyFetch)

