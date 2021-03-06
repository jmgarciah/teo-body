// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "TechnosoftIpos.hpp"

// ------------------- IControlModeRaw Related ------------------------------------

bool teo::TechnosoftIpos::setPositionModeRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    //*************************************************************
    uint8_t msg_position_mode[] = {0x2F,0x60,0x60,0x00,0x01};  // Position mode

    if( ! send( 0x600, 5, msg_position_mode) )
    {
        CD_ERROR("Could not send \"position_mode\". %s\n", msgToStr(0x600, 5, msg_position_mode).c_str() );
        return false;
    }
    CD_SUCCESS("Sent \"position_mode\". %s\n", msgToStr(0x600, 5, msg_position_mode).c_str() );
    //*************************************************************

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::setVelocityModeRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    //*************************************************************
    uint8_t msg_velocity_mode[]={0x2F,0x60,0x60,0x00,0x03}; // Velocity mode

    if( ! send( 0x600, 5, msg_velocity_mode) )
    {
        CD_ERROR("Could not send \"vel_mode\". %s\n", msgToStr(0x600, 5, msg_velocity_mode).c_str() );
        return false;
    }
    CD_SUCCESS("Sent \"vel_mode\". %s\n", msgToStr(0x600, 5, msg_velocity_mode).c_str() );
    //*************************************************************

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::setTorqueModeRaw(int j)  {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    //*************************************************************
    //-- External reference type. Slave receives reference through CAN (manual 208 of 263).
    uint8_t msg_ref_type[]={0x2B,0x1D,0x20,0x00,0x01,0x00,0x00,0x00};  //CAN

    if( ! send( 0x600, 8, msg_ref_type) )
    {
        CD_ERROR("Could not send \"ref_type\". %s\n", msgToStr(0x600, 8, msg_ref_type).c_str() );
        return false;
    }
    CD_SUCCESS("Sent \"ref_type\". %s\n", msgToStr(0x600, 8, msg_ref_type).c_str() );
    //*************************************************************
    //-- Mode -5 (manual 209 of 263).
    uint8_t msg_mode_torque[]={0x2F,0x60,0x60,0x00,0xFB,0x00,0x00,0x00};

    if( ! send( 0x600, 8, msg_mode_torque) )
    {
        CD_ERROR("Could not send \"mode_torque\". %s\n", msgToStr(0x600, 8, msg_mode_torque).c_str() );
        return false;
    }
    CD_SUCCESS("Sent \"mode_torque\". %s\n", msgToStr(0x600, 8, msg_mode_torque).c_str() );
    //*************************************************************
    //-- Control word (manual 215 of 263).
    uint8_t msg_torque_word[] = {0x1F,0x00};

    if( ! send( 0x200, 2, msg_torque_word) )
    {
        CD_ERROR("Could not send msg_torque_word. %s\n", msgToStr(0x200, 2, msg_torque_word).c_str() );
        return false;
    }
    CD_SUCCESS("Sent \"torque_word\". %s\n", msgToStr(0x200, 2, msg_torque_word).c_str() );
    //*************************************************************

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::setImpedancePositionModeRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (TechnosoftIpos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::setImpedanceVelocityModeRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (TechnosoftIpos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::setOpenLoopModeRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (TechnosoftIpos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::TechnosoftIpos::getControlModeRaw(int j, int *mode) {
    //CD_INFO("(%d)\n",j);  //-- Too verbose in controlboardwrapper2 stream

    //-- Check index within range
    if ( j != 0 ) return false;

    //*************************************************************
    uint8_t msgOperationDisplay[] = {0x40,0x61,0x60,0x00,0x00,0x00,0x00,0x00}; // Manual 6061h: Modes of Operation display
    if( ! send( 0x600, 8, msgOperationDisplay))
    {
        CD_ERROR("Could not send modes of operation display. %s\n", msgToStr(0x600, 8, msgOperationDisplay).c_str() );
        return false;
    }
    CD_SUCCESS("Sent modes of operation display. %s\n", msgToStr(0x600, 8, msgOperationDisplay).c_str() );
    //*************************************************************

    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Time::delay(DELAY);  // Must delay as it will be from same driver.
    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    getModeReady.wait();
    *mode = getMode;
    getModeReady.post();

    //-- Ya de paso...
    //*************************************************************
    //uint8_t msgStatusDisplay[] = {0x40,0x41,0x60,0x00,0x00,0x00,0x00,0x00}; // Manual 6041h: Status display word
    //if( ! send( 0x600, 8, msgStatus))
    //{
    //    CD_ERROR("Could not send status display query. %s\n", msgToStr(0x600, 8, msgStatusDisplay).c_str() );
    //    return false;
    //}
    //CD_SUCCESS("Sent status display query. %s\n", msgToStr(0x600, 8, msgStatusDisplay).c_str() );
    //*************************************************************

    //-- Ya de paso, aun mejor...
    //*************************************************************
    uint8_t msgManuStatus[] = {0x40,0x02,0x10,0x00,0x00,0x00,0x00,0x00}; // Manual 1002h contains "6041h Status word" plus Table 5.6
    if( ! send( 0x600, 8, msgManuStatus))
    {
        CD_ERROR("Could not send manufacturer status query. %s\n", msgToStr(0x600, 8, msgManuStatus).c_str() );
        return false;
    }
    CD_SUCCESS("Sent manufacturer status query. %s\n", msgToStr(0x600, 8, msgManuStatus).c_str() );
    //*************************************************************

    //-- Y ya de paso, por qué no...
    //*************************************************************
    uint8_t msgError[] = {0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00}; // Manual 2000h: Motion Error Register
    if( ! send( 0x600, 8, msgError))
    {
        CD_ERROR("Could not send Motion Error Register query. %s\n", msgToStr(0x600, 8, msgError).c_str() );
        return false;
    }
    CD_SUCCESS("Sent Motion Error Register query. %s\n", msgToStr(0x600, 8, msgError).c_str() );
    //*************************************************************

    //-- Y tb ya de paso, por qué no... // no info
    //*************************************************************
    uint8_t msgErrorDetail[] = {0x40,0x02,0x20,0x00,0x00,0x00,0x00,0x00}; // Manual 2002h: Detailed Error Register
    if( ! send( 0x600, 8, msgErrorDetail))
    {
        CD_ERROR("Could not send Detailed Error Register query. %s\n", msgToStr(0x600, 8, msgErrorDetail).c_str() );
        return false;
    }
    CD_SUCCESS("Sent Detailed Error Register query. %s\n", msgToStr(0x600, 8, msgErrorDetail).c_str() );
    //*************************************************************

    //-- Y... // no info (just a 000Fh)
    //*************************************************************
    /*uint8_t msgSw[] = {0x40,0x0A,0x10,0x00,0x00,0x00,0x00,0x00}; // Manual 100Ah: Manufacturer Software Version
    if( ! send( 0x600, 8, msgSw))
    {
        CD_ERROR("Could not send Manufacturer Software Version query. %s\n", msgToStr(0x600, 8, msgSw).c_str() );
        return false;
    }
    CD_SUCCESS("Sent Manufacturer Software Version query. %s\n", msgToStr(0x600, 8, msgSw).c_str() );*/
    //*************************************************************

    return true;
}

// -----------------------------------------------------------------------------
