#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_SATELLITEHANDLER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_SATELLITEHANDLER_SM_H

#include "../SatelliteHandler.h"

unsigned int init_SatelliteHandlerSM(satelliteHandlerSM_Struct *messageStruct);
unsigned int SatelliteHandlerSM(satelliteHandlerSM_Struct *messageStruct);

#endif