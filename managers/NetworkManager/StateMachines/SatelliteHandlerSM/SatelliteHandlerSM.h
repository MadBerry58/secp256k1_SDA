#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_SATELLITEHANDLER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_SATELLITEHANDLER_SM_H

#include "../../../../TypeDef.h"

unsigned int init_SatelliteHandlerSM(satelliteHandlerSMStruct *messageStruct);
unsigned int SatelliteHandlerSM(satelliteHandlerSMStruct *messageStruct);

#endif