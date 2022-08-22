#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_CLIENTHANDLER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_CLIENTHANDLER_SM_H

#include "../../../../TypeDef.h"

unsigned int init_ClientHandlerSM(clientHandlerSMStruct *messageStruct);
unsigned int ClientHandlerSM(clientHandlerSMStruct *messageStruct);


#endif