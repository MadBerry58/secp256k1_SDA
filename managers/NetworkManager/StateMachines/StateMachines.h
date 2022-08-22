#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_SM_H

#include "../../../TypeDef.h"
#include "../NetworkManager.h"

#include "ClientSM/ClientSM.h"
#include "ClientHandlerSM/ClientHandlerSM.h"
#include "SatelliteSM/SatelliteSM.h"
#include "SatelliteHandlerSM/SatelliteHandlerSM.h"
#include "ServerFrontendSM/ServerFrontendSM.h"

std::thread *startClientSM(clientSMStruct &messageStruct);
unsigned int stopClientSM(clientSMStruct &messageStruct);

std::thread *startClientHandlerSM(clientHandlerSMStruct &messageStruct);
unsigned int stopClientHandlerSM(clientHandlerSMStruct &messageStruct);

std::thread *startSatelliteSM(satelliteSMStruct &messageStruct);
unsigned int stopSatelliteSM(satelliteSMStruct &messageStruct);

std::thread *startSatelliteHandlerSM(satelliteHandlerSMStruct &messageStruct);
unsigned int stopSatelliteHandlerSM(satelliteHandlerSMStruct &messageStruct);

std::thread *startServerFrontendSM(ServerFrontendSMStruct &messageStruct);
unsigned int stopServerFrontendSM(ServerFrontendSMStruct &messageStruct);

#endif