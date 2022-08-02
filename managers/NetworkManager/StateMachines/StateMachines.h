#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_SM_H

#include "../../../TypeDef.h"

#include "ClientSM/ClientSM.h"
#include "ClientHandlerSM/ClientHandlerSM.h"
#include "SatelliteSM/SatelliteSM.h"
#include "SatelliteHandlerSM/SatelliteHandlerSM.h"
#include "ServerFrontendSM/ServerFrontendSM.h"

unsigned int startDummySM(std::string messageStruct);
unsigned int startClientSM(std::string message);
unsigned int startClientHandlerSM(std::string message);
unsigned int startSatelliteSM(std::string message);
unsigned int startSatelliteHandlerSM(std::string message);
unsigned int startServerFrontendSM(std::string message);

#endif